#!/usr/bin/env python3
#
# SVD -> C++ header generator
#

import itertools
import re
import cmsis_svd
from cmsis_svd.parser import SVDParser


def sline(code, comment=None):
    buf = code
    if comment is not None:
        while len(buf) < 72:
            buf += " "
        buf += "// " + comment
    return buf + "\n"


class Register:
    def __init__(self, svd_register):
        self._svd = svd_register

    def gen_decl(self, args):
        if ((len(self.fields) == 0) or
            not args.bitfields or
            ((self.fields[0].bit_offset == 0) and
             (self.fields[0].bit_width == self.size))):
            qualified_typename = f"{'const ' if self._read_only else ''}{self.typename}"
            text = sline(f"    {qualified_typename:20} {self.name};", self.description)
        else:
            text = sline(f"\n    // {self.description}")
            text += sline(f"    {'const ' if self._read_only else ''}struct {self.name}_reg {'{'}")
            bit_offset = 0
            for f in self.fields:
                anon_width = f.bit_offset - bit_offset
                if anon_width > 0:
                    text += sline(f"        {self.typename} :{anon_width};")
                    bit_offset += anon_width
                qualified_typename = f"{'const ' if not self._read_only and f.access == 'read-only' else ''}{self.typename}"
                text += sline(f"        {qualified_typename:16} {f.name:12}:{f.bit_width};", f.description)
                bit_offset += f.bit_width
            anon_width = self.size - bit_offset
            if anon_width > 0:
                text += sline(f"        uint{self.size}_t :{anon_width};")
            text += sline(f"    {'}'} {self.name};\n")
        return text

    def gen_defines(self, parent_name, args):
        text = ""
        if ((len(self.fields) > 0) and (self.fields[0].bit_width != self.size)):
            for f in self.fields:
                name = f"{parent_name}_{self.name}_{f.name}"
                if (args.defines):
                    if f.bit_width == 1:
                        text += sline(f"#define {name:40} ((uint{self.size}_t)1 << {f.bit_offset})", f.description)
                    else:
                        cast = f"(uint{self.size}_t)"
                        mask = ((1 << f.bit_width) - 1)
                        mask_in_place = mask << f.bit_offset
                        if not self._read_only:
                            valname = f"{name}(_n)"
                            text += sline(f"#define {valname:40} ({cast}(_n) << {f.bit_offset})", f.description)
                            defname = f"{name}_INSERT(_v, _n)"
                            text += sline(f"#define {defname:44} (((_v) & ~{mask_in_place:#x}) | ({cast}(_n) & {mask:#x}) << {f.bit_offset})")
                        else:
                            text += sline("", f.description)
                        if not self._write_only:
                            defname = f"{name}_EXTRACT(_v)"
                            text += sline(f"#define {defname:44} (((_v) >> {f.bit_offset}) & {mask:#x})")
                if args.enumerations and f.enumerated_values is not None:
                    for e in f.enumerated_values:
                        ename = f"{name}_{e.name}"
                        text += sline(f"#define   {ename:38} (uint{self.size}_t){e.value:#x}", e.description)
            text += "\n"
        return text

    @property
    def typename(self):
        return f"uint{self.size}_t"

    @property
    def _read_only(self):
        return self.access == "read-only"

    @property
    def _write_only(self):
        return self.access == "write-only"

    def __getattr__(self, attr):
        return getattr(self._svd, attr)


class Peripheral:
    _index = {}

    def __init__(self, svd_peripheral, args):
        self._svd = svd_peripheral
        self._aliases = []
        self._aliased = None

        # is the peripheral type unique, or an alias?
        for p in self._index.values():
            if self._can_alias(p, args.force_alias):
                p._aliases.append(self)
                self._aliased = p
                break

        self._index[self.name] = self

    @classmethod
    @property
    def list(cls):
        return cls._index.keys()

    @classmethod
    @property
    def peripherals(cls):
        return cls._index.values()

    @classmethod
    def gen_pointers(cls, args):
        text = ""
        for p in cls._index.values():
            text += f"static auto &{p.name:12} = *(volatile {p._type_name}_regs *){p.base_address:#x};\n"
        return text

    @classmethod
    def gen_structs(cls, args):
        text = ""
        for p in cls._index.values():
            if not p.aliased:
                text += p.gen_struct(args)
        return text

    def gen_struct(self, args):
        text = sline("", "--------------------")
        text += sline("", self.description)
        text += sline(f"struct {self._name_fixup(self.name)}_regs", "--------------------")
        text += sline("{")
        res_reg_counter = 0
        reg_offset = 0
        for r in self.registers:
            reg = Register(r)
            res_width = reg.address_offset - reg_offset
            if res_width > 0:
                text += f"    uint8_t _res{res_reg_counter}[{res_width}];\n"
                reg_offset += res_width
                res_reg_counter += 1
            text += reg.gen_decl(args)
            text += reg.gen_defines(self._name_fixup(self.name), args)
            reg_offset += int(reg.size / 8)
        text += "};\n"

        return text

    @classmethod
    def gen_vectors(cls, args):
        text = """
typedef enum {
    Reset_IRQn                     = -15,
    NonMaskableInt_IRQn            = -14,
    HardFault_IRQn                 = -13,
    MemoryManagement_IRQn          = -12,
    BusFault_IRQn                  = -11,
    UsageFault_IRQn                = -10,
    SVCall_IRQn                    =  -5,
    DebugMonitor_IRQn              =  -4,
    PendSV_IRQn                    =  -2,
    SysTick_IRQn                   =  -1,
"""
        interrupts = {}
        for p in cls.peripherals:
            for i in p.interrupts:
                interrupts[i.value] = i
        for i in sorted(interrupts.values(), key=lambda x: x.value):
            name = f"{i.name}_IRQn"
            text += f"    {name:30} = {i.value},\n"
        text += "} IRQn_Type;\n"
        return text

    @property
    def aliased(self):
        return self._aliased is not None

    def _name_fixup(self, sym):
        if sym.startswith(self.name):
            return self._type_name + sym[len(self.name):]
        return sym

    @property
    def _type_name(self):
        if self._aliased is not None:
            # aliased to another peripheral, find its type
            return self._aliased._type_name
        elif len(self._aliases) > 0:
            # find longest common prefix for aliases
            pfx = self.name[:-1]
            while len(pfx) > 0:
                common = True
                for alias in self._aliases:
                    if not alias.name.startswith(pfx):
                        common = False
                        break
                if common:
                    return pfx
                pfx = pfx[:-1]
        # not aliased or can't find a common prefix, use name
        return self.name

    def _can_alias(self, p2, force):
        """decide whether two peripherals are sufficiently similar to share
           a register struct - this could be more strict, or it could try to
           detect subsets and do something sensible there"""
        if force is not None and f"{self.name}={p2.name}" in force:
            return True
        if len(self.registers) != len(p2.registers):
            return False
        for (p1reg, p2reg) in zip(self.registers, p2.registers):
            if p1reg.name != p2reg.name:
                return False
            if p1reg.size != p2reg.size:
                return False
            if p1reg.address_offset != p2reg.address_offset:
                return False
        return True

    def __str__(self):
        return self.name

    def __getattr__(self, attr):
        return getattr(self._svd, attr)


def should_enable(name, args):
    if args.disable is not None:
        for pat in args.disable:
            if re.match(pat, name) is not None:
                return False
    if args.enable is None:
        return True
    for pat in args.enable:
        if re.match(pat, name) is not None:
            return True
    return False


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description="ARM CMSIS-SVD C++ code generator")
    parser.add_argument("--enable",
                        type=str,
                        nargs="*",
                        metavar="PERIPHERAL-NAME",
                        help="include peripherals in output (default is all)")
    parser.add_argument("--disable",
                        type=str,
                        nargs="*",
                        metavar="PERIPHERAL-NAME",
                        help="do not include peripheral in output (default is none)")
    parser.add_argument("--force-alias",
                        type=str,
                        nargs="*",
                        metavar="ALIAS-FROM=ALIAS-TO",
                        help="force the ALIAS-FROM peripheral (and anything that aliases it) to alias the register type of ALIAS-TO")
    parser.add_argument("--outfile",
                        type=str,
                        metavar="OUTPUT-FILE",
                        help="write output to file")
    stylegroup = parser.add_mutually_exclusive_group()
    stylegroup.add_argument("--bitfields",
                            action="store_true",
                            help="generate bitfields")
    stylegroup.add_argument("--defines",
                            action="store_true",
                            help="generate #defines for register fields")
    parser.add_argument("--enumerations",
                        action="store_true",
                        help="generate #defines for register field enumerated values")
    parser.add_argument("svd_file",
                        type=str,
                        metavar="SVD-FILE",
                        help="SVD file to process")
    actiongroup = parser.add_mutually_exclusive_group(required=True)
    actiongroup.add_argument("--emit-header",
                             action="store_true",
                             help="emit a header file")
    actiongroup.add_argument("--list",
                             action="store_true",
                             help="list peripherals")

    args = parser.parse_args()
    device = SVDParser.for_xml_file(args.svd_file).get_device()

    for p in device.peripherals:
        if should_enable(p.name, args):
            Peripheral(p, args)

    if args.list:
        for p in Peripheral.peripherals:
            print(p)

    if args.emit_header:
        text = f"""//
// AUTOMATICALLY GENERATED BY svd2cpp.py - DO NOT EDIT
//
// vendor      : {device.vendor}
// name        : {device.name}
// version     : {device.version}
// description : {device.description}
//

#pragma once
{Peripheral.gen_vectors(args)}

#define __CM4_REV               0x0001U
#define __NVIC_PRIO_BITS        {device.cpu.nvic_prio_bits}
#define __Vendor_SysTickConfig  0
#define __MPU_PRESENT           {int(device.cpu.mpu_present and should_enable("ARM_MPU", args))}
#define __FPU_PRESENT           {int(device.cpu.fpu_present and should_enable("ARM_FPU", args))}

#include <CMSIS/core_cm4.h>

{Peripheral.gen_structs(args)}
{Peripheral.gen_pointers(args)}
"""
        if args.outfile is None:
            print(text)
        else:
            with open(args.outfile, "w") as f:
                f.write(text)

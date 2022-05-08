#!/usr/bin/env python3
#
# Console monitor
#

import can


class Console(can.Listener):
    def __init__(self, interface, emit=print):
        self._line = ''
        interface.add_listener(self)
        self._emit = emit

    def on_message_received(self, message):
        if message.is_extended_id and message.arbitration_id == 0x1ffffffe:
            self._line += bytes(message.data).decode()
            if self._line.endswith('\0'):
                self._emit(self._line)
                self._line = ''


if __name__ == '__main__':
    import argparse
    import time
    from interface import Interface

    parser = argparse.ArgumentParser(description='CC16_core console logger')
    parser.add_argument('--interface-name',
                        type=str,
                        metavar='INTERFACE',
                        default='anagate',
                        help='name of the interface as known to python-can')
    parser.add_argument('--interface-channel',
                        type=str,
                        metavar='CHANNEL',
                        required=True,
                        help='interface channel name (e.g. for Anagate units, hostname:portname')
    parser.add_argument('--bitrate',
                        type=int,
                        default=500,
                        metavar='BITRATE_KBPS',
                        help='CAN bitrate (kBps')

    args = parser.parse_args()
    try:
        intf = Interface(args)
        cons = Console(intf)
        intf.set_power_on()

        print(f'Console @ {args.interface_channel}')
        while True:
            msg = input("> ")
            payload = (msg + '\0').ascii()
            while len(payload):
                intf.send(can.Message(arbitration_id=0x1ffffffe,
                                      extended_id=True,
                                      data=payload[:8]))
                payload = payload[8:]
    except KeyboardInterrupt:
        intf.set_power_off()

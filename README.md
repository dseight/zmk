# Zephyr™ Mechanical Keyboard (ZMK) Firmware

This is a fork of ZMK with support for a custom tidbit-like numpad. The
differences from original tidbit are:
- usage of Gateron switches
- Waveshare RP2040-Zero instead of custom MCU board

The build is based on [Zephyr 3.7.1 with RP2040-Zero support](https://github.com/dseight/zephyr/tree/zephyr-v3.7.1-rp2040-zero).

To build, run:

    west build -p -b rp2040_zero -- -DSHIELD=tidbit_gateron

---

[ZMK Firmware](https://zmk.dev/) is an open source ([MIT](LICENSE)) keyboard firmware built on the [Zephyr™ Project](https://www.zephyrproject.org/) Real Time Operating System (RTOS). ZMK's goal is to provide a modern, wireless, and powerful firmware free of licensing issues.

Check out the website to learn more: https://zmk.dev/.

You can also come join our [ZMK Discord Server](https://zmk.dev/community/discord/invite).

To review features, check out the [feature overview](https://zmk.dev/docs/). ZMK is under active development, and new features are listed with the [enhancement label](https://github.com/zmkfirmware/zmk/issues?q=is%3Aissue+is%3Aopen+label%3Aenhancement) in GitHub. Please feel free to add 👍 to the issue description of any requests to upvote the feature.

# Keychron C2 Pro 8K

![Keychron C2 Pro 8K](https://cdn.shopify.com/s/files/1/0059/0630/1017/files/Keychron-C2-Pro-8K-QMK-Wired-Mechanical-Keyboard-2.jpg)

A customizable full size (100%) keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron C2 Pro 8K
* Hardware Availability: [Keychron](https://www.keychron.com/products/keychron-c2-pro-8k-qmk-via-wired-mechanical-keyboard)

## Option A: Build And Flash Firmware

Make example for this keyboard (after setting up your build environment):

    make keychron/c2_pro_8k/ansi:vial

This target creates a UF2 firmware file for the TinyUF2 bootloader. Enter the
keyboard's TinyUF2 mode, then copy the generated `.uf2` file to the keyboard's
USB mass-storage drive.

The keyboard must already have a compatible TinyUF2 bootloader installed.
The stock AT32 DFU bootloader is not a USB mass-storage drive and cannot flash
UF2 files.

## bootloader

Enter TinyUF2 mode using the bootloader's supported reset procedure.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Option B: Use Keychron Launcher (no code required)

If you just want to remap keys, configure layers, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, and adjust lighting - changes apply instantly

Keychron Launcher works out of the box with no JSON import required, providing a simpler browser-based setup flow for supported boards. Safari and other non-Chromium browsers will not work with Keychron Launcher.

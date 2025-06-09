#!/bin/bash

export QTDIR=/mnt/workspace/labs/qt5-lab/images/qt5-x86_64-5.11.2
export QT_PLUGIN_PATH="${QTDIR}/plugins"
export QT_QPA_FONTDIR="${QTDIR}/lib/fonts"
export QT_QPA_PLATFORM_PLUGIN_PATH="${QTDIR}/plugins/platforms"
export QT_QPA_PLATFORM="linuxfb:fb=/dev/fb0"
export QT_QPA_GENERIC_PLUGINS=evdevtouch,evdevmouse,evdevkeyboard
export QT_QPA_EVDEV_KEYBOARD_PARAMETERS=grab=1

./hello_world

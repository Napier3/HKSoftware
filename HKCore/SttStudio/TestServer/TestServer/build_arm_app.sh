##!/bin/bash
###############################################################################
#
#Company : Liyang Milian Electronic Technology Co., Ltd.
#Brand: 米联客(msxbo)
#Technical forum:uisrc.com
#taobao: osrc.taobao.com
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
###############################################################################


# => Setting The Development Environment Variables
if [ ! "${QT_CONFIG_DONE}" ];then
    echo "[ERROR] 请进入 scripts 目录执行“source cfg_qt.sh” 命令。" && exit 1
fi

# => Filename of the running script.
QT_SCRIPT_NAME="$(basename ${BASH_SOURCE})"

###############################################################################
# => The beginning
echo_info "[ $(date "+%Y/%m/%d %H:%M:%S") ] Starting ${QT_SCRIPT_NAME}"

export QMAKESPEC=${QTDIR}/mkspecs/$ARCHXPLATFOR
export PATH=$PATH:${QTDIR}/bin/

qmake && make
#qmake CONFIG+=debug && make

# => The end
echo_info "[ $(date "+%Y/%m/%d %H:%M:%S") ] Finished ${QT_SCRIPT_NAME}"
###############################################################################

#ifndef CSTTDEVICE_H
#define CSTTDEVICE_H

#include <QObject>
#include "QtCore"
#include "QMap"
#include "QList"
#include "../../SttTest/PTU/define.h"
#include "stdafx.h"
#include "../SttDeviceBase.h"
#include "SttDriverOper.h"
#include "../../SttTest/PTU/protobuf/DeviceInnerPara.pb.h"
#include "../../SttTest/PTU/protobuf/hqyBinaryInSetting.pb.h"
#include<fstream>
#include "../../SttTest/PTU/tmt_set_parameter.h"


#define MAXCHANELNUM 6
#define TEMPCOUNT 20
#define HARMCOUNT  63
#define MaxNum 65536

//DAPara Send to Driver
typedef struct{
	unsigned long nvolt;
	unsigned long ncurrent;
}DeviceDAPara;

union ConverStruct {
	unsigned char b[4];
	unsigned long l;
	float f;
};//4涓
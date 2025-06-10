#pragma once

#define LOCAL_LIVEUPDATE_NAME			_T("LiveUpdate.exe")
#define LOCAL_LIVEUPDATE_NEWNAME		_T("LiveUpdate_new.exe")
#define STT_LIVEUPDATE_NAME				_T("SttLiveUpdate")

#define UPDATEPARAS_TYPE_REQUEST		_T("request")
#define UPDATEPARAS_TYPE_LOCAL			_T("local")
#define UPDATEPARAS_TYPE_REMOTE			_T("remote")
#define UPDATEPARAS_TYPE_MOBILE			_T("mobile")
#define UPDATEPARAS_TYPE_FILE			_T("file")
#define UPDATEPARAS_TYPE_STOP			_T("stop")
#define UPDATEPARAS_TYPE_ROLLBACK		_T("rollback")

#define UPDATESTYLE_NONE				0x00
#define UPDATESTYLE_LOCAL				0x01
#define UPDATESTYLE_REMOTE				0x02
#define UPDATESTYLE_MOBILE				0x03
#define UPDATESTYLE_NATIVE				0x04
#define UPDATESTYLE_ROLLBACK			0x05	//测试仪回滚
//
//liveupdate path
//#define STTNATIVE_PATH_ROOT			_T("/home/zynq/SttNative/")	//本机调试路径
#define STTNATIVE_PATH_ROOT				_T("/mnt/Stt/")				//底层测试仪路径

#define LIVEUPDATE_PATH_ROOT			_T("LiveUpdate/")
#define LIVEUPDATE_PATH_UNZIP			_T("LiveUpdate/verunzip/")
#define LIVEUPDATE_PATH_BK				_T("LiveUpdate/verbk/")
#define LIVEUPDATE_PATH_TEMP			_T("LiveUpdate/vertemp/")
#define LIVEUPDATE_PATH_SELFTEMP		_T("LiveUpdate/liveupdatetemp")

#define LIVEUPDATE_CFG_BASE				_T("VerUpdateConfig.xml")
#define LIVEUPDATE_CFG_HIS				_T("VerUpdateHistory.xml")
#define LIVEUPDATE_CFG_NATIVE			_T("SttNativeCfg.xml")

#define LIVEUPDATE_LOCAL				0x01
#define LIVEUPDATE_TESTAPP				0x02
#define LIVEUPDATE_MOBILE				0x03

#define LIVEUPDATE_NEWEST_VERINDEX		0x7FFFFFFE

#define CLOUDSERVER_IP					_T("47.111.12.170")
#define CLOUDSERVER_PORT_CMD			9900
#define CLOUDSERVER_PORT_FILE			9994

#define STTTESTSERVER_PORT				19814	//测试仪测试服务端口
#define LIVEUPDATE_PORT					19817	//底层版本更新的端口

#define ID_VERUPDATE_DEFAULT_USER		0xFFFFFE

#define OPTYPE_NONE						0x00
#define OPTYPE_UPDATE					0x01	
#define OPTYPE_ROLLBACK					0x02

typedef enum {
	MODE_DIRECT,							
	MODE_SHELL_LOCAL,
	MODE_SHELL_TESTAPP
}START_MODE;

typedef enum{
	STATE_NONE,
	STATE_WAITINITDRIVER,
	STATE_WAITPARASRECV,
	STATE_WAITFILERECV,
	STATE_WAITUPDATERESULT
}STATE_UPDATE;


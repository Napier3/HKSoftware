
#pragma once

#include "PxiDeviceCommCmdMessage.h"

enum _tagEngineSystemDefine
{//2020-5-21  lijunqing
    engineConnectDeviceFailed= 1, //0,
    engineConnectDeviceSuccessful=2, //1,
    engineCommError = 3, //2,
    engineCommFinish = 4, //3,
    engineCommCmdError=5, //4
    engineException=6, //5
	engineDvmEnumFinish=7
} ;//_enumEngineSystemDefine;

#define PXI_DATA_ID_EngineSysState                  _T("EngineSysState")
//ConnectFailed	����ʧ��
#define EngineSysState_ConnectFailed               _T("ConnectFailed")
//ConnectSuccess	�����ɹ�
#define EngineSysState_ConnectSuccessful      _T("ConnectSuccess")
//CommError	ͨ�Ŵ���
#define EngineSysState_CommError                    _T("CommError")
//CommFinish	ͨ�����
#define EngineSysState_CommFinish                  _T("CommFinish")
#define EngineSysState_CommBegin                  _T("CommBegin")
//CommCmdError	ͨ���������
#define EngineSysState_CmdError                     _T("CommCmdError")
//CommOverTime	ͨ�ų�ʱ
#define EngineSysState_CommOverTime           _T("CommOverTime")
//Exception	ͨ���쳣
#define EngineSysState_Exception                       _T("Exception")
//Step ͨ�Ž���  2023-1-29   lijunqing
#define EngineSysState_CommStep                  _T("CommStep")
#define EngineSysState_DvmEnumFinish                  _T("DvmEnumFinish")
//�¼����棺SOE
#define  EngineEvent_Report                          _T("Report")


inline CString pxi_get_engine_sys_state(int nEngineSysState)
{
    switch (nEngineSysState)
    {
    case engineConnectDeviceFailed:
        return EngineSysState_ConnectFailed;
    case engineConnectDeviceSuccessful:
        return EngineSysState_ConnectSuccessful;
    case engineCommError:
        return EngineSysState_CommError;
    case engineCommFinish:
        return EngineSysState_CommFinish;
    case engineCommCmdError:
        return EngineSysState_CmdError;
    default:
        return EngineSysState_CommBegin;
    }
}

typedef struct _pxi_procedure_step_msg_
{
	int nSteps;
	int nStep;
	char strDatasetID[128];
	char strInfor[128];
}PXIPROCEDURESTEOPMSG, *PPXIPROCEDURESTEOPMSG;

//Ϊ�˷�����ԣ�����PPxiDeviceCommCmdMessage.h/.cpp�ļ������������ƶ������ļ�
//shaolei 2023-11-2
// class CPxiDeviceCommCmdMessage
// {
// public:
// 	virtual void OnCommCmdMessage(WPARAM wParam, LPARAM lParam) = 0;
// 	virtual void OnSysMessage(WPARAM wParam, LPARAM lParam) = 0;
// 	
// 	//2023-2-1  lijunqing
// 	virtual void OnEventMessage(WPARAM wParam, LPARAM lParam){};
// 
//     //2020-11-24  lijunqing LINUX  post msg to ats
//     virtual void OnEngineDataDeleted(const CString &strDeviceID){};
// 
// 	//2023-3-5  lijunqing
// 	virtual void OnReportMessage(WPARAM wParam, LPARAM lParam){};
// 
// };


class CPoDeviceProcedureInterface
{
public:
	CPoDeviceProcedureInterface()			{	}
	virtual ~CPoDeviceProcedureInterface()	{	}

public:
	virtual void OnProcedureEnd(const CString &strProcedure, WPARAM wParam, LPARAM lParam) = 0;
	virtual void OnSystemMsg(WPARAM wParam, LPARAM lParam) = 0;
};

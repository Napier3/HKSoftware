#pragma once


#include "../../Module/DataMngr/DataGroup.h"


#define MODEL_DEVICE_ID_Attr		_T("dsDeviceAttr")
#define ATS_ID_ItemPath				_T("item-path")


class CSttMqttCmdExecBase : public CExBaseList
{
public:
	CSttMqttCmdExecBase();
	virtual ~CSttMqttCmdExecBase();

	CString m_strCurItemPath;			//��ǰ������

	
	virtual void OnTestItemFinish() = 0;
	//m_strName:�������ƣ�m_strID:����ID

public:
	BOOL IsSuspendThread();
	BOOL IsTestItemFinish();
	void SetSuspendThread();


};


CString GetIDFromPath(const CString &strPath,char chSeperator='$');
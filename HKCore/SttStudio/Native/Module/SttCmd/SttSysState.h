//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSysState.h  CSttSysState

#pragma once

#include "SttCmdDefineGlobal.h"

#include "SttCmdBase.h"
#include "../../../Module/BaseClass/XObjectRefBase.h"

//////////////////////////////////////////////////////////////////////////
//move to SttSysState.h   2022-8-1  lijunqing

class CSttSysState : public CSttCmdBase, public CXObjectRefBase
{
public:
	CSttSysState();
	CSttSysState(const CString &strRetType);
	virtual ~CSttSysState();

	static CXObjectRefBase* New()
	{
		return new CSttSysState();
	}

	CString  m_strMater_Host;  //??????????????????????? 是否应该为  master-host
	CString m_strRetType; //返回的类型
	CString m_strRetSttCmd;

//重载函数
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTSYSSTATE;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttSysStateKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	void UpdateSysStateHead(CSttCmdBase *pCmd);
	BOOL IsReply()		{	return m_strRetType == SYS_STATE_RETTYPE_REPLY;	}
	BOOL IsReporting()	{	return m_strRetType == SYS_STATE_RETTYPE_REPORT;	}
	void SetReply()			{	m_strRetType = SYS_STATE_RETTYPE_REPLY;	}
	void SetReporting()	{	m_strRetType = SYS_STATE_RETTYPE_REPORT;	}
	void SetEvent()			{	m_strRetType = SYS_STATE_RETTYPE_EVENT;	}
	void SetRtData() {m_strRetType = SYS_STATE_RETTYPE_RTDATA;}
	void SetPacket()	{	m_strRetType = SYS_STATE_RETTYPE_PACKAGE;	}
	void SetUpdate()			{	m_strRetType = SYS_STATE_RETTYPE_UPDATE;	}
	void SetRetType(const CString &strRetType)	{	m_strRetType = strRetType;	};
	void SetRetType(const char *strRetType)		{	m_strRetType = strRetType;	};

//系统状态通用数据
public:
	BOOL Get_IOverLoad();
	void Set_IOverLoad(BOOL b);
	BOOL Get_UOverLoad();
	void Set_UOverLoad(BOOL b);
	BOOL Get_OverHeat();
	void Set_OverHeat(BOOL b);
	BOOL Get_IBreak();
	void Set_IBreak(BOOL b);
	BOOL Get_UShort();
	void Set_UShort(BOOL b);
	long Get_ExecStatus();
	void Set_ExecStatus(long nVal);
	long Get_ConnectState();
	void Set_ConnectState(long nVal);
	long Get_OutputState();
	void Set_OutputState(long nVal);
	long Get_CurrStateIndex();
	void Set_CurrStateIndex(long nVal);
	BOOL Get_ErrCmd();
	void Set_ErrCmd(BOOL b);
	BOOL Get_DataNotExist();
	void Set_DataNotExist(BOOL b);
    CString Get_DataNotExist_String();
    void Set_DataNotExist(const CString &strData);
    BOOL Get_IsSuccess();
	void Set_IsSuccess(BOOL b);
	long Get_TestTimeLong();
	void Set_TestTimeLong(long nVal);
	long Get_TestState();
	void Set_TestState(long nVal);

	void Set_ExecStatus_Ack();
	void Set_ExecStatus_Failure();
	void Set_ExecStatus_Success();
};

CString Global_GetEventName(const CString &strEventID);

//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSysState.cpp  CSttSysState


#include "stdafx.h"
#include "SttSysState.h"
#ifndef NOT_USE_XLANGUAGE
//#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../AutoTest/Module/XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttSysState::CSttSysState()
{
	SetReply();
}

CSttSysState::CSttSysState(const CString &strRetType)
{
	m_strRetType = strRetType;
}

CSttSysState::~CSttSysState()
{
}

long CSttSysState::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdBase::XmlReadOwn(oNode, pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMater_HostKey, oNode, m_strMater_Host);
	xml_GetAttibuteValue(pXmlKeys->m_strRetTypeKey, oNode, m_strRetType);
	xml_GetAttibuteValue(pXmlKeys->m_strRetCmdKey, oNode, m_strRetSttCmd);

	return 0;
}

long CSttSysState::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMater_HostKey, oElement, m_strMater_Host);
	xml_SetAttributeValue(pXmlKeys->m_strRetTypeKey, oElement, m_strRetType);
	xml_SetAttributeValue(pXmlKeys->m_strRetCmdKey, oElement, m_strRetSttCmd);

	return 0;
}

long CSttSysState::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttCmdBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMater_Host);
		BinarySerializeCalLen(oBinaryBuffer, m_strRetType);
		BinarySerializeCalLen(oBinaryBuffer, m_strRetSttCmd);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMater_Host);
		BinarySerializeRead(oBinaryBuffer, m_strRetType);
		BinarySerializeRead(oBinaryBuffer, m_strRetSttCmd);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMater_Host);
		BinarySerializeWrite(oBinaryBuffer, m_strRetType);
		BinarySerializeWrite(oBinaryBuffer, m_strRetSttCmd);
	}

	return 0;
}

BOOL CSttSysState::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttCmdBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttSysState *p = (CSttSysState*)pObj;

	if(m_strMater_Host != p->m_strMater_Host)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttSysState::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttCmdBase::CopyOwn(pDest);

	CSttSysState *p = (CSttSysState*)pDest;

	p->m_strMater_Host = m_strMater_Host;
	p->m_strRetType = m_strRetType;
	p->m_strRetSttCmd = m_strRetSttCmd;

	return TRUE;
}

CBaseObject* CSttSysState::Clone()
{
	CSttSysState *p = new CSttSysState();
	Copy(p);
	return p;
}

CBaseObject* CSttSysState::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttSysState *p = new CSttSysState();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttSysState::CanPaste(UINT nClassID)
{
	return FALSE;
}

void CSttSysState::UpdateSysStateHead(CSttCmdBase *pCmd)
{
	if (pCmd == NULL)
	{
		return;
	}

	m_strID = pCmd->m_strID;
	m_strRetSttCmd = pCmd->GetXmlElementKey();
    m_nIDTester = pCmd->m_nIDTester;
    m_nPkgSendIndex = pCmd->m_nPkgSendIndex;
	m_strToSN = pCmd->m_strFromSN;
}

//////////////////////////////////////////////////////////////////////////
BOOL CSttSysState::Get_IOverLoad()
{
	return GetParaValue(STT_SYS_STATE_ID_IOverLoad, 0) > 0;
}

void CSttSysState::Set_IOverLoad(BOOL b)
{
	AddNewParasData(STT_SYS_STATE_ID_IOverLoad, b);
}

BOOL CSttSysState::Get_UOverLoad()
{
	return GetParaValue(STT_SYS_STATE_ID_UOverLoad, 0) > 0;
}

void CSttSysState::Set_UOverLoad(BOOL b)
{
	AddNewParasData(STT_SYS_STATE_ID_UOverLoad, b);
}

BOOL CSttSysState::Get_OverHeat()
{
	return GetParaValue(STT_SYS_STATE_ID_OverHeat, 0) > 0;
}

void CSttSysState::Set_OverHeat(BOOL b)
{
	AddNewParasData(STT_SYS_STATE_ID_OverHeat, b);
}

BOOL CSttSysState::Get_IBreak()
{
	return GetParaValue(STT_SYS_STATE_ID_IBreak, 0) > 0;
}

void CSttSysState::Set_IBreak(BOOL b)
{
	AddNewParasData(STT_SYS_STATE_ID_IBreak, b);
}

BOOL CSttSysState::Get_UShort()
{
	return GetParaValue(STT_SYS_STATE_ID_UShort, 0) > 0;
}

void CSttSysState::Set_UShort(BOOL b)
{
	AddNewParasData(STT_SYS_STATE_ID_UShort, b);
}

long CSttSysState::Get_ExecStatus()
{
	return GetParaValue(STT_SYS_STATE_ID_ExecStatus, 0);
}

void CSttSysState::Set_ExecStatus(long nVal)
{
	SetParasDataAttr(STT_SYS_STATE_ID_ExecStatus, nVal);
}

long CSttSysState::Get_ConnectState()
{
	return GetParaValue(STT_SYS_STATE_ID_ConnectState, 0);
}

void CSttSysState::Set_ConnectState(long nVal)
{
	AddNewParasData(STT_SYS_STATE_ID_ConnectState, nVal);
}

long CSttSysState::Get_OutputState()
{
	return GetParaValue(STT_SYS_STATE_ID_OutputState, 0);
}

void CSttSysState::Set_OutputState(long nVal)
{
	AddNewParasData(STT_SYS_STATE_ID_OutputState, nVal);
}

long CSttSysState::Get_CurrStateIndex()
{
	return GetParaValue(STT_SYS_STATE_ID_CurrStateIndex, -1);
}

void CSttSysState::Set_CurrStateIndex(long nVal)
{
	AddNewParasData(STT_SYS_STATE_ID_CurrStateIndex, nVal);
}

BOOL CSttSysState::Get_ErrCmd()
{
	return GetParaValue(STT_SYS_STATE_ID_ErrCmd, 0) > 0;
}

void CSttSysState::Set_ErrCmd(BOOL b)
{
	AddNewParasData(STT_SYS_STATE_ID_ErrCmd, b);
}

BOOL CSttSysState::Get_DataNotExist()
{
	return GetParaValue(STT_SYS_STATE_ID_DataNotExist, 0) > 0;
}

void CSttSysState::Set_DataNotExist(BOOL b)
{
	AddNewParasData(STT_SYS_STATE_ID_DataNotExist, b);
}

CString CSttSysState::Get_DataNotExist_String()
{
    CString strData;
    GetParasDataValueByID(STT_SYS_STATE_ID_DataNotExist, strData);

    return strData;
}

void CSttSysState::Set_DataNotExist(const CString &strData)
{
     SetParasDataAttr(STT_SYS_STATE_ID_DataNotExist, strData);
}

BOOL CSttSysState::Get_IsSuccess()
{
	return GetParaValue(STT_SYS_STATE_ID_IsSuccess, 0);
}


void CSttSysState::Set_IsSuccess(BOOL b)
{
	AddNewParasData(STT_SYS_STATE_ID_IsSuccess, b);
}

long CSttSysState::Get_TestTimeLong()
{
	return GetParaValue(STT_SYS_STATE_ID_TestTimeLong, 0);
}

void CSttSysState::Set_TestTimeLong(long nVal)
{
	AddNewParasData(STT_SYS_STATE_ID_TestTimeLong, nVal);
}

long CSttSysState::Get_TestState()
{
	return GetParaValue(STT_SYS_STATE_ID_TestState, 0);
}

void CSttSysState::Set_TestState(long nVal)
{
	AddNewParasData(STT_SYS_STATE_ID_TestState, nVal);
}

void CSttSysState::Set_ExecStatus_Ack()
{
	Set_ExecStatus(STT_CMD_ExecStatus_ACK);
}

void CSttSysState::Set_ExecStatus_Failure()
{
	Set_ExecStatus(STT_CMD_ExecStatus_FAILURE);
}

void CSttSysState::Set_ExecStatus_Success()
{
	Set_ExecStatus(STT_CMD_ExecStatus_SUCCESS);
}

CString Global_GetEventName(const CString &strEventID)
{
	CString strRet = strEventID;
#ifdef NOT_USE_XLANGUAGE
	if (strEventID == SYS_STATE_EVENT_OnTestStarted)
	{
		strRet = _T("开始输出");
	}
	else if (strEventID == SYS_STATE_EVENT_OnTestStoped)
	{
		strRet = _T("停止测试");
	}
	else if (strEventID == SYS_STATE_EVENT_OnTestFinished)
	{
		strRet = _T("测试完成");
	}
	else if (strEventID == SYS_STATE_EXCEPTION)
	{
		strRet = _T("测试异常");
	}
	else if (strEventID == SYS_STATE_UNEXCEPTION)
	{
		strRet = _T("解除测试异常");
	}
	else if (strEventID == SYS_STATE_REPORT_OnStateChanged)
	{
		strRet = _T("状态切换");
	}
	else if (strEventID == SYS_STATE_REPORT_OnUdcChanged)
	{
		strRet = _T("辅助直流切换");
	}
	else if (strEventID == SYS_STATE_REPORT_OnSwichInChanged)
	{
		strRet = _T("开入变位");
	}
	else if (strEventID == SYS_STATE_REPORT_OnSwichOutChanged)
	{
		strRet = _T("开出变位");
	}
	else if (strEventID == SYS_STATE_RETTYPE_UPDATE)
	{
		strRet = _T("参数更新");
	}
#else
//	xlang_GetLangStrByFile(strRet, "sStrRet");
	if (strEventID == SYS_STATE_EVENT_OnTestStarted)
	{
		strRet = g_sLangTxt_Native_StartOutput;
	}
	else if (strEventID == SYS_STATE_EVENT_OnTestStoped)
	{
		strRet = g_sLangTxt_StopTest;
	}
	else if (strEventID == SYS_STATE_EVENT_OnTestFinished)
	{
		strRet = g_sLangTxt_TestComplete;
	}
	else if (strEventID == SYS_STATE_EXCEPTION)
	{
		strRet = g_sLangTxt_Native_TestAnomalies;
	}
	else if (strEventID == SYS_STATE_UNEXCEPTION)
	{
        strRet = g_sLangTxt_Native_RelieveTestAnomalies;
	}
	else if (strEventID == SYS_STATE_REPORT_OnStateChanged)
	{
		strRet = g_sLangTxt_Native_StateSwitch;
	}
	else if (strEventID == SYS_STATE_REPORT_OnUdcChanged)
	{
		strRet = g_sLangTxt_Native_SupDCSwitch;
	}
	else if (strEventID == SYS_STATE_REPORT_OnSwichInChanged)
	{
		strRet = g_sLangTxt_Native_BinDisPlace;
	}
	else if (strEventID == SYS_STATE_REPORT_OnSwichOutChanged)
	{
		strRet = g_sLangTxt_Native_BoutDisPlace;
	}
	else if (strEventID == SYS_STATE_RETTYPE_UPDATE)
	{
		strRet = g_sLangTxt_Native_ParaUpdata;
	}
// 	else
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("strEventID[%s]不存在."));
// 	}
#endif
	return strRet;
}

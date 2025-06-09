//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttCmdBase.cpp  CSttCmdBase


#include "stdafx.h"
#include "SttCmdBase.h"
#include "../../../Module/System/TickCount32.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../XLangResource_Native.h"                              
#endif

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString g_strIDSoft = _T("");

CSttCmdBase::CSttCmdBase()
{
	m_pRefSocketDataBase = NULL;

	//初始化属性
	//m_nFrameHead = STT_PKT_FRAMEHEAD;
	m_nType_Cmd = 0;
    m_nIDTester = 0;
    m_nPkgSendIndex = 0;
	m_nCompress = 0;
	m_nDataLen = 0;	

	m_nMid = 0;

	m_strTime = _T("1970-01-01 00:00:00");
#ifndef _PSX_QT_LINUX_
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	SystemTime_To_String(tm,m_strTime);
#endif

	//初始化成员变量
    m_bCreateMacroChild = true;
    m_bXml_Pkg_With_Name  = FALSE;

	//2021-8-3  lijunqing
	m_pCmmOptrInterface = NULL;
}

CSttCmdBase::~CSttCmdBase()
{
}

long CSttCmdBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdData::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMidKey, oNode, m_nMid);
	xml_GetAttibuteValue(pXmlKeys->m_strTimeKey, oNode, m_strTime);
	return 0;
}

long CSttCmdBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMidKey, oElement, m_nMid);
	xml_SetAttributeValue(pXmlKeys->m_strTimeKey, oElement, m_strTime);
	return 0;
}

long CSttCmdBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttCmdData::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

BOOL CSttCmdBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttCmdBase *p = (CSttCmdBase*)pObj;

	return TRUE;
}

BOOL CSttCmdBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttCmdBase *p = (CSttCmdBase*)pDest;

	//p->m_nFrameHead = m_nFrameHead;
	p->m_nType_Cmd = m_nType_Cmd;
    p->m_nIDTester = m_nIDTester;
    p->m_nPkgSendIndex = m_nPkgSendIndex;
	p->m_nCompress = m_nCompress;
	p->m_nDataLen = m_nDataLen;
	p->m_strFromSN = m_strFromSN;
	p->m_strToSN = m_strToSN;

	return TRUE;
}


CBaseObject* CSttCmdBase::Clone()
{
	CSttCmdBase *p = new CSttCmdBase();
	Copy(p);
	return p;
}

CBaseObject* CSttCmdBase::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttCmdBase *p = new CSttCmdBase();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CSttCmdBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttParasKey)
	{
		m_pSttParas = NewSttParas();
		pNew = m_pSttParas;
	}
	else if (strClassID == pXmlKeys->m_strCSttMacroKey)
	{
		CSttMacro *pNewMacro = new CSttMacro();
		pNew = pNewMacro;
		pNewMacro->SetCreateMacroChild(m_bCreateMacroChild);
	}
	else if (strClassID == pXmlKeys->m_strCSttMsgsKey)
	{
		m_pSttMsgs = new CSttMsgs();
		pNew = m_pSttMsgs;
	}
#ifndef STT_CMD_NOT_USE_IOT
	else if (strClassID == pXmlKeys->m_strCSttIotTopoKey)
	{
		m_pSttIotTopo = new CSttIotTopo();
		pNew = m_pSttIotTopo;
	}
	else if (strClassID == pXmlKeys->m_strCSttIotDevicesKey)
	{
		m_pSttIotDevices = new CSttIotDevices();
		pNew = m_pSttIotDevices;
	}
#endif

	return pNew;
}

CExBaseObject* CSttCmdBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTCMDCLASSID_CSTTPARAS)
	{
		pNew = NewSttParas();
	}
	else if (nClassID == STTCMDCLASSID_CSTTMACRO)
	{
		pNew = new CSttMacro();
	}
	else if (nClassID == STTCMDCLASSID_CSTTMSGS)
	{
		pNew = new CSttMsgs();
	}
#ifndef STT_CMD_NOT_USE_IOT
	else if (nClassID == STTCMDCLASSID_CSTTIOTTOPO)
	{
		pNew = new CSttIotTopo();
	}
	else if (nClassID == STTCMDCLASSID_CSTTIOTDEVICES)
	{
		pNew = new CSttIotDevices();
	}
#endif

	return pNew;
}

BOOL CSttCmdBase::GetXml_Pkg(char **ppszBuffer, long &nLen, long nSttCmdDataFormat)
{
    if (m_bXml_Pkg_With_Name)
    {
        nLen = GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, ppszBuffer, STT_PKG_HEAD_LEN, nSttCmdDataFormat);
    }
    else
    {
        CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
        nLen = GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, ppszBuffer, STT_PKG_HEAD_LEN, nSttCmdDataFormat);
        CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
    }

	return TRUE;
}

BOOL CSttCmdBase::ParsePkgHead(BYTE *pPkgBuffer)
{
	//m_nFrameHead = Stt_GetFrameHead(pTemp);
	m_nType_Cmd = stt_pkg_get_cmd_type(pPkgBuffer);
    m_nIDTester = (unsigned int)(pPkgBuffer[STT_PKG_INDEX_IDTESTER+3]<<24);
    m_nIDTester += (unsigned int)(pPkgBuffer[STT_PKG_INDEX_IDTESTER+2]<<16);
    m_nIDTester += (unsigned int)(pPkgBuffer[STT_PKG_INDEX_IDTESTER+1]<<8);
    m_nIDTester += (unsigned int)(pPkgBuffer[STT_PKG_INDEX_IDTESTER]);

    //m_nIDTester = stt_pkg_get_idtester(pPkgBuffer);
    m_nPkgSendIndex = stt_pkg_get_send_index(pPkgBuffer);
//	m_nCompress = stt_pkg_get_compress(pPkgBuffer);
	m_nDataLen = stt_pkg_get_data_len(pPkgBuffer);

    return TRUE;
}


BOOL CSttCmdBase::ParsePkgXml(BYTE *pPkgBuffer, long nLen, char *pszDestBuffer, const long &nXmlRWType )
{
   ParsePkgHead(pPkgBuffer);
   //pPkgBuffer[nLen] = 0;
	memcpy(pszDestBuffer, pPkgBuffer, nLen);
	pszDestBuffer[nLen] = 0;
	pszDestBuffer[nLen+1] = 0;
	pszDestBuffer[nLen+2] = 0;

   ++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
   BOOL bRet = SetXml_UTF8((char*)(pszDestBuffer+STT_PKG_HEAD_LEN), nLen - STT_PKG_HEAD_LEN
	   , CSttCmdDefineXmlRWKeys::g_pXmlKeys, nXmlRWType);
   --CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

   return bRet;
}

char* CSttCmdBase::ParsePkgOnly(BYTE *pPkgBuffer)
{
    ParsePkgHead(pPkgBuffer);
    return (char*)(pPkgBuffer+STT_PKG_HEAD_LEN);
}

void CSttCmdBase::ProducePkgHead(BYTE *pPkgBuffer)
{
    stt_pkg_set_head(pPkgBuffer);
    stt_pkg_set_cmd_type(pPkgBuffer, GetCmdType());
    stt_pkg_set_idtester(pPkgBuffer, m_nIDTester);
    stt_pkg_set_send_index(pPkgBuffer, m_nPkgSendIndex);
//    stt_pkg_set_compress(pPkgBuffer, m_nCompress);
    stt_pkg_set_data_len_cmd_other(pPkgBuffer, m_nDataLen);
}

long CSttCmdBase::GetCmdType()
{
	UINT nClassID = GetClassID();
	long nCmdType = 0;

	switch (nClassID)
	{
		case STTCMDCLASSID_CSTTSYSTEMCMD:
		{
			nCmdType = STT_CMD_TYPE_SYSTEM;
			break;
		}
		case STTCMDCLASSID_CSTTTESTCMD:
		{
			nCmdType = STT_CMD_TYPE_TEST;
			break;
		}
		case STTCMDCLASSID_CSTTDEBUGCMD:
		{
			nCmdType = STT_CMD_TYPE_DEBUG;
			break;
		}
		case STTCMDCLASSID_CSTTREMOTECMD:
		{
			nCmdType = STT_CMD_TYPE_REMOTE;
			break;
		}
		case STTCMDCLASSID_CSTTATSCMD:
		{
			nCmdType = STT_CMD_TYPE_ATS;
			break;
		}
		case STTCMDCLASSID_CSTTASSISTCMD:
		{
			nCmdType = STT_CMD_TYPE_ASSIST;
			break;
		}
		case STTCMDCLASSID_CSTTSYSSTATE:
		{
			nCmdType = STT_CMD_TYPE_SYSSTATE;
			break;
		}
		case STTCMDCLASSID_CSTTADJUSTCMD:
		{
			nCmdType = STT_CMD_TYPE_ADJUST;
			break;
		}
		case STTCMDCLASSID_CSTTIOTCMD:
		{
			nCmdType = STT_CMD_TYPE_IOT;
			break;
		}
		default:
			break;
	}

	return nCmdType;
}

DWORD CSttCmdBase::GetIDTest()
{
	GetParasDataValueByID(STT_CMD_PARA_IDTESTER, m_nIDTester);
	return m_nIDTester;
}

long CSttCmdBase::DoWait(CSttSocketDataBase_File *pSocket,STT_CMD_INFO *pCmdInfo,long nTimeOut,CSttCmdData *pRetData,BOOL bDoEvents)
{
	long nExecStatus = STT_CMD_ExecStatus_NULL;

// 	STT_CMD_INFO *pCmdInfo = CSttCmdOverTimeTool::AddSttCmd(pSocket,m_nType_Cmd,m_strID,0, 0, NULL);
// 	if (pCmdInfo == NULL)
// 	{
// 		return nExecStatus;
// 	}

	CTickCount32 oTickCount32;
	long nTickCountLong = 0;


	while(TRUE)
	{
		if (pCmdInfo->pSocketRef == NULL)
		{
			nExecStatus = STT_CMD_ExecStatus_SocketClose;
	
			break;
		}

		if (pCmdInfo->IsCmdExecState_Failure() 
			|| pCmdInfo->IsCmdExecState_Success())
		{
			nExecStatus = pCmdInfo->m_nCmdExecState;

			if ((pCmdInfo->pSysState != NULL) && (pRetData != NULL))
			{
				pRetData->AppendEx(*pCmdInfo->pSysState);
				pRetData->InitAfterRead();
				pCmdInfo->pSysState->RemoveAll();
			}

			nTickCountLong = oTickCount32.GetTickCountLong(FALSE);

			break;
		}

		if (bDoEvents)
		{
			CTickCount32 oTick(FALSE);
			oTick.DoEvents(5);
		}
		else
		{
			Sleep(5);
		}
		
		if (nTimeOut > 0)
		{
			nTickCountLong = oTickCount32.GetTickCountLong(FALSE);

			if (nTickCountLong >= nTimeOut)
			{
				nExecStatus = STT_CMD_ExecStatus_TIMEOUT;
//#ifdef NOT_USE_XLANGUAGE
//				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s命令：超时"),m_strID.GetString());
//#else
                CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s(Cmd)：timeout"),m_strID.GetString());    //zhouhj 2025.3.5
//#endif
				break;
			}
		}
	}

	pCmdInfo->SetUsed(0);

	return nExecStatus;
}

void CSttCmdBase::PraseCmdBuf(char *pBuf,long nLen, char *pszDestBuffer,const CString &strFormat)
{
	if (strFormat == MQTT_DATA_FORMAT_JSON)
	{
		++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
		SetXml_UTF8(pBuf,nLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys,_JSON_TYPE_);
		--CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	}
	else
	{//XML
		ASSERT(pszDestBuffer != NULL);
		memcpy(pszDestBuffer, pBuf, nLen);
		pszDestBuffer[nLen] = 0;
		pszDestBuffer[nLen+1] = 0;

		++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
		SetXml_UTF8(pszDestBuffer, nLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		--CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	}
}


void CSttCmdBase::PraseCmdBuf(char *pBuf,long nLen, char *pszDestBuffer, UINT nFormatType)
{
	if (_JSON_TYPE_ == nFormatType)
	{
		++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
		SetXml_UTF8(pBuf,nLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys,_JSON_TYPE_);
		--CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	}
	else
	{//XML
		ASSERT(pszDestBuffer != NULL);
		memcpy(pszDestBuffer, pBuf, nLen);
		pszDestBuffer[nLen] = 0;
		pszDestBuffer[nLen+1] = 0;

		++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
		SetXml_UTF8(pszDestBuffer, nLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys, nFormatType);
		--CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	}
}


void CSttCmdBase::SetParameter(const CString &strMacroID, CDataGroup *pParas)
{
	if (strMacroID.GetLength() > 0)
	{
		CSttMacro *pMacro = GetSttMacro();
		pMacro->SetParameter(strMacroID, pParas);
	}
	else
	{
		GetSttParas();

		if (pParas != NULL)
		{
			m_pSttParas->AttachParas(pParas);
		}
	}
}


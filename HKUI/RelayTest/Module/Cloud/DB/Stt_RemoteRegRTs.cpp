//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Stt_RemoteRegRTs.cpp  CStt_RemoteRegRTs


#include "stdafx.h"
#include "Stt_RemoteRegRTs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CStt_RemoteRegRTs::CStt_RemoteRegRTs()
{
	//初始化属性

	//初始化成员变量
}

CStt_RemoteRegRTs::~CStt_RemoteRegRTs()
{
}

long CStt_RemoteRegRTs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CStt_RemoteRegRTs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CStt_RemoteRegRTs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CStt_RemoteRegRTs::InitAfterRead()
{
}

BOOL CStt_RemoteRegRTs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStt_RemoteRegRTs *p = (CStt_RemoteRegRTs*)pObj;

	return TRUE;
}

BOOL CStt_RemoteRegRTs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStt_RemoteRegRTs *p = (CStt_RemoteRegRTs*)pDest;

	return TRUE;
}

CBaseObject* CStt_RemoteRegRTs::Clone()
{
	CStt_RemoteRegRTs *p = new CStt_RemoteRegRTs();
	Copy(p);
	return p;
}

CBaseObject* CStt_RemoteRegRTs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CStt_RemoteRegRTs *p = new CStt_RemoteRegRTs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CStt_RemoteRegRTs::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTT_REMOTEREGRT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CStt_RemoteRegRTs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CRemoteCtrlMngrXmlRWKeys *pXmlKeys = (CRemoteCtrlMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCStt_RemoteRegRTKey)
	{
		pNew = new CStt_RemoteRegRT();
	}

	return pNew;
}

CExBaseObject* CStt_RemoteRegRTs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTT_REMOTEREGRT)
	{
		pNew = new CStt_RemoteRegRT();
	}

	return pNew;
}
CExBaseObject* CStt_RemoteRegRTs::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CStt_RemoteRegRT();

	return pNew;
}

void CStt_RemoteRegRTs::GenerateQuerySysState(CSttSysState &oSysState)
{
	POS pos = GetHeadPosition();
	CStt_RemoteRegRT *p = NULL;

	while(pos != NULL)
	{
		p = (CStt_RemoteRegRT *)GetNext(pos);

		CDvmData* pNewData = oSysState.AddNewParasData(STT_TERMINAL_TYPE_REMOTE, 1);
		
		pNewData->AddValue(ID_STT_USER_ATTR_Code_Register, p->m_strCode_Register);
		pNewData->AddValue(ID_STT_USER_ATTR_SN_TestApp, p->m_strSN_TestApp);
		pNewData->AddValue(ID_STT_REGISTER_ATTR_Model_TestApp, p->m_strModel_TestApp);
		pNewData->AddValue(ID_STT_REGISTER_ATTR_Model_Dv, p->m_strModel_Dv);
		pNewData->AddValue(ID_STT_USER_ATTR_Name_Cop, p->m_strName_Cop);
		pNewData->AddValue(ID_STT_USER_ATTR_Name_User, p->m_strName_User);
		pNewData->AddValue(ID_STT_REGISTER_ATTR_Description, p->m_strDescription);

		pNewData->AddValue(ID_STT_REGISTER_ATTR_Ver_PpMmsEngine, p->m_strVer_PpMmsEngine);
		pNewData->AddValue(ID_STT_REGISTER_ATTR_Ver_PpEngine, p->m_strVer_PpEngine);
		pNewData->AddValue(ID_STT_REGISTER_ATTR_Ver_SttTestStudio, p->m_strVer_SttTestStudio);
		pNewData->AddValue(ID_STT_REGISTER_ATTR_Ver_SttTestCntr, p->m_strVer_SttTestCntr);
		pNewData->AddValue(ID_STT_REGISTER_ATTR_Ver_Iec61850Config, p->m_strVer_Iec61850Config);
		pNewData->AddValue(ID_STT_REGISTER_ATTR_Ver_DvmTest, p->m_strVer_DvmTest);
		pNewData->AddValue(ID_STT_REGISTER_ATTR_Ver_SmartTest, p->m_strVer_SmartTest);
		pNewData->AddValue(ID_STT_REGISTER_ATTR_Ver_TestServer, p->m_strVer_TestServer);
	}
}
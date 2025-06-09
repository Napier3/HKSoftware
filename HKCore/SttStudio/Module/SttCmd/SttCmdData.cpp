//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttCmdData.cpp  CSttCmdData


#include "stdafx.h"
#include "SttCmdData.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttCmdData::CSttCmdData()
{
	//初始化属性

	//初始化成员变量
	m_pSttParas = NULL;
#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
	m_pSttMacro = NULL;
#endif
	m_pSttMsgs = NULL;
#ifndef STT_CMD_NOT_USE_IOT
	m_pSttIotTopo = NULL;
	m_pSttIotDevices = NULL;
#endif
}

CSttCmdData::~CSttCmdData()
{
}

void CSttCmdData::Free()
{
	DeleteAll();
	m_pSttParas = NULL;
#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
	m_pSttMacro = NULL;
#endif
	m_pSttMsgs = NULL;
}

CSttParas* CSttCmdData::GetSttParas()
{	
	if (m_pSttParas == NULL)
	{
		m_pSttParas = NewSttParas();
		AddNewChild(m_pSttParas);
	}

	return m_pSttParas;
}

BOOL CSttCmdData::HasSttParas()
{
	return m_pSttParas != NULL;
}

CSttMsgs* CSttCmdData::GetSttMsgs()
{	
	if (m_pSttMsgs == NULL)
	{
		m_pSttMsgs = new CSttMsgs();
		AddNewChild(m_pSttMsgs);
	}

	return m_pSttMsgs;
}

#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
CSttMacro* CSttCmdData::GetSttMacro(BOOL bInitParas, BOOL bInitResults,BOOL bInitSearchResults)
{
	if (m_pSttMacro == NULL)
	{
		m_pSttMacro = new CSttMacro();
		AddNewChild(m_pSttMacro);
	}

	if (bInitParas)
	{
		m_pSttMacro->GetParas();
	}

	if (bInitResults)
	{
		m_pSttMacro->GetResults();
	}

	if (bInitSearchResults)
	{
		m_pSttMacro->GetSearchResults();
	}

	return m_pSttMacro;
}
#endif

#ifndef STT_CMD_NOT_USE_IOT
CSttIotTopo* CSttCmdData::GetSttIotTopo()
{	
	if (m_pSttIotTopo == NULL)
	{
		m_pSttIotTopo = new CSttIotTopo();
		AddNewChild(m_pSttIotTopo);
	}

	return m_pSttIotTopo;	
}

CSttIotDevices* CSttCmdData::GetSttIotDevices()	
{	
	if (m_pSttIotDevices == NULL)
	{
		m_pSttIotDevices = new CSttIotDevices();
		AddNewChild(m_pSttIotDevices);
	}

	return m_pSttIotDevices;	
}
#endif

long CSttCmdData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttCmdData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttCmdData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CSttCmdData::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == STTCMDCLASSID_CSTTPARAS)
		{
			m_pSttParas = (CSttParas*)p;
		}
#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
		else if (nClassID == STTCMDCLASSID_CSTTMACRO)
		{
			m_pSttMacro = (CSttMacro*)p;
		}
#endif
		else if (nClassID == STTCMDCLASSID_CSTTMSGS)
		{
			m_pSttMsgs = (CSttMsgs*)p;
		}
#ifndef STT_CMD_NOT_USE_IOT
		else if (nClassID == STTCMDCLASSID_CSTTIOTTOPO)
		{
			m_pSttIotTopo = (CSttIotTopo*)p;
		}
		else if (nClassID == STTCMDCLASSID_CSTTIOTDEVICES)
		{
			m_pSttIotDevices = (CSttIotDevices*)p;
		}
#endif
	}
}

BOOL CSttCmdData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttCmdData *p = (CSttCmdData*)pObj;

	return TRUE;
}

BOOL CSttCmdData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttCmdData *p = (CSttCmdData*)pDest;

	return TRUE;
}


CBaseObject* CSttCmdData::Clone()
{
	CSttCmdData *p = new CSttCmdData();
	Copy(p);
	return p;
}

CBaseObject* CSttCmdData::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttCmdData *p = new CSttCmdData();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttCmdData::CanPaste(UINT nClassID)
{
	if (nClassID == STTCMDCLASSID_CSTTPARAS)
	{
		return TRUE;
	}

	if (nClassID == STTCMDCLASSID_CSTTMACRO)
	{
		return TRUE;
	}

	if (nClassID == STTCMDCLASSID_CSTTMSGS)
	{
		return TRUE;
	}

	if (nClassID == STTCMDCLASSID_CSTTIOTTOPO)
	{
		return TRUE;
	}

	if (nClassID == STTCMDCLASSID_CSTTIOTDEVICES)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttCmdData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttParasKey)
	{
		m_pSttParas = NewSttParas();
		pNew = m_pSttParas;
	}
#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
	else if (strClassID == pXmlKeys->m_strCSttMacroKey)
	{
		CSttMacro *pNewMacro = new CSttMacro();
		pNew = pNewMacro;
	}
#endif
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

CExBaseObject* CSttCmdData::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTCMDCLASSID_CSTTPARAS)
	{
		pNew = NewSttParas();
	}
#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
	else if (nClassID == STTCMDCLASSID_CSTTMACRO)
	{
		pNew = new CSttMacro();
	}
#endif
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

//xxy 20200516:pszBuffer为utf-8字节流
BOOL CSttCmdData::SetXml(char *pszBuffer, long nLen, wchar_t *pwszDestBuffer)
{
	long nDestLen = 0;

#ifdef _PSX_QT_LINUX_          //周宏军  20200516解决编码方式问题
    str_char_to_wchar(pwszDestBuffer, pszBuffer, nLen);
#else
    charUtf8_to_wcharGBK(pszBuffer,nLen, pwszDestBuffer,nDestLen);
#endif
	++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	BOOL bRet = CBaseObject::SetXml(pwszDestBuffer, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	--CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
    
	return bRet;
}

void CSttCmdData::GetXml(CXmlRWKeys *pXmlRWKeys, CString &bstrXml,const long &nXmlRWType)
{
	CExBaseObject::GetXml(pXmlRWKeys, bstrXml, nXmlRWType);

	if (m_pSttParas == NULL)
	{
		return;
	}

	if (m_pSttParas->m_nLenTextParas > 1)
	{
		long nPos = bstrXml.Find(_T("</paras>"));

		if (nPos > 0)
		{
			CString strRight = bstrXml.Mid(nPos);
			bstrXml = bstrXml.Left(nPos);
			bstrXml += m_pSttParas->m_pszTextParas;
			bstrXml += strRight;
		}
	}
}

//xxy 20200516:生成ppszRetBuffer为utf-8字节流
long CSttCmdData::GetXml(CXmlRWKeys *pXmlRWKeys, char **ppszRetBuffer, long nOffset,const long &nXmlRWType)
{
	long nRet = CExBaseObject::GetXml(pXmlRWKeys, ppszRetBuffer, nOffset, nXmlRWType);

	if (m_pSttParas == NULL)
	{
		return nRet;
	}

	if (m_pSttParas->m_nLenTextParas > 1)
	{
		char *pPos = strstr(*ppszRetBuffer, "</paras>");

		if (pPos)
		{
			long nLeft = pPos - *ppszRetBuffer;
			long nTextLen = m_pSttParas->m_nLenTextParas;
			long nTotalLen = nTextLen + nRet + 10;

			char *pNewBuffer = new char [nTotalLen];
			memset(pNewBuffer, 0, nTotalLen);
			memcpy(pNewBuffer, *ppszRetBuffer, nLeft);
			memcpy(pNewBuffer + nLeft, m_pSttParas->m_pszTextParas, nTextLen);
			memcpy(pNewBuffer + nLeft + nTextLen, *ppszRetBuffer + nLeft, nRet - nLeft);
			char *p = *ppszRetBuffer;
			*ppszRetBuffer = pNewBuffer;
			delete p;
			nRet = nRet + nTextLen;
			pNewBuffer[nRet] = 0;
		}
	}

	return nRet;
}

CSttParas* CSttCmdData::NewSttParas()
{
	return new CSttParas();
}


BOOL CSttCmdData::GetParasDataValueByID(const char* strValueID, CString &strValue)
{
	if (m_pSttParas == NULL)
	{
		return FALSE;
	}

	return stt_GetDataValueByID(m_pSttParas, strValueID, strValue);
}

BOOL CSttCmdData::GetParasDataValueByID(const char* strValueID, long &nValue)
{
	if (m_pSttParas == NULL)
	{
		return FALSE;
	}

	CString strValue;
	BOOL bRet = GetParasDataValueByID(strValueID, strValue);

	if (bRet)
	{
	nValue = CString_To_long(strValue);
	}

	return bRet;
}

BOOL CSttCmdData::GetParasDataValueByID(const char* strValueID, int &nValue)
{
	if (m_pSttParas == NULL)
	{
		return FALSE;
	}

	CString strValue;
	BOOL bRet = GetParasDataValueByID(strValueID, strValue);

	if (bRet)
	{
	nValue = CString_To_long(strValue);
	}

	return bRet;
}

BOOL CSttCmdData::GetParasDataValueByID(const char* strValueID, DWORD &nValue)
{
	if (m_pSttParas == NULL)
	{
		return FALSE;
	}

	CString strValue;
	BOOL bRet = GetParasDataValueByID(strValueID, strValue);

	if (bRet)
	{
	nValue = (DWORD)CString_To_ulong(strValue);
	}

	return bRet;
}

BOOL CSttCmdData::GetParasDataValueByID(const CString &strValueID, CString &strValue)
{
	if (m_pSttParas == NULL)
	{
		return FALSE;
	}

	return stt_GetDataValueByID(m_pSttParas, strValueID, strValue);
}

BOOL CSttCmdData::GetParasDataValueByID(const CString &strValueID, long &nValue)
{
	if (m_pSttParas == NULL)
	{
		return FALSE;
	}

	CString strValue;
	BOOL bRet = GetParasDataValueByID(strValueID, strValue);
	if (bRet)
	{
	nValue = CString_To_long(strValue);
	}

	return bRet;
}

BOOL CSttCmdData::GetParasDataValueByID(const CString &strValueID, DWORD &nValue)
{
	if (m_pSttParas == NULL)
	{
		return FALSE;
	}

	CString strValue;
	BOOL bRet = GetParasDataValueByID(strValueID, strValue);
	if (bRet)
	{
	nValue = (DWORD)CString_To_ulong(strValue);
	}

	return bRet;
}
long CSttCmdData::GetParaValue(const CString &strValueID, long nDefaultValue)
{
	return stt_GetDataValueByID2(m_pSttParas, strValueID, nDefaultValue);
}

CDvmData* CSttCmdData::AddNewParasData(const CString &strID, const CString &strValue)
{
	GetSttParas();

	return m_pSttParas->AddNewData(strID, strValue, TRUE);
}

CDvmData* CSttCmdData::AddNewParasData(const CString &strID, long nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);

	return AddNewParasData(strID, strValue);
}

CDvmData* CSttCmdData::SetParasDataAttr(const CString &strID, const CString &strValue)
{
	GetSttParas();

	return m_pSttParas->SetDataAttr(strID, strValue);
}

CDvmData* CSttCmdData::SetParasDataAttr(const CString &strID, long nValue)
{
	GetSttParas();

	return m_pSttParas->SetDataAttr(strID, nValue);
}

void CSttCmdData::AppendParas(CSttCmdData &oSrcCmd)
{
	GetSttParas();

	CSttParas *pSrcParas = oSrcCmd.GetSttParas();
	m_pSttParas->AppendEx(*pSrcParas);
	pSrcParas->RemoveAll();

#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
	//暂时不考虑SttMacro
	if (oSrcCmd.m_pSttMacro == NULL)
	{
		return;
	}
#endif
}

void CSttCmdData::AddNewParas(CExBaseList *pList)
{
	if (pList == NULL)
	{
		return;
	}

	GetSttParas();
	m_pSttParas->AddNewChild((CExBaseList *)pList->Clone());
}

void CSttCmdData::AppendParas2(CExBaseList &oList, BOOL bClone)
{
	GetSttParas();

	if (bClone)
	{
		m_pSttParas->AppendCloneEx(oList, TRUE);
	}
	else
	{
		m_pSttParas->AppendEx(oList, FALSE);
		oList.RemoveAll();
	}
}

void CSttCmdData::AppendMsgs(CExBaseList &oList)
{
	GetSttMsgs();

	m_pSttMsgs->AppendEx(oList, FALSE);
	oList.RemoveAll();
}

void CSttCmdData::RemoveMsgs()
{
	if (m_pSttMsgs == NULL)
	{
		return;
	}

	m_pSttMsgs->RemoveAll();
}

void CSttCmdData::DeleteParasDataByID(const CString &strValueID)
{
	GetSttParas();
	m_pSttParas->DeleteByID(strValueID);
}

CDvmData *CSttCmdData::FindParasDataByID(const CString &strValueID)
{
	GetSttParas();
	return (CDvmData *)(m_pSttParas->FindByID(strValueID));
}

CDvmDataset* CSttCmdData::GetDataset()
{
    if (m_pSttParas == NULL)
    {
        return NULL;
    }

    return m_pSttParas->GetDvmDataset();
}

CDvmDatasetGroup* CSttCmdData::GetDatasetGroup()
{
	if (m_pSttParas == NULL)
	{
		return NULL;
	}

	return m_pSttParas->GetDvmDatasetGroup();
}


//2021-8-4  lijunqing
CExBaseObject* CSttCmdData::FindInParasByID(const CString &strID)
{
	GetSttParas();
	return m_pSttParas->FindByID(strID);
}

BOOL CSttCmdData::SetParasDataValueByID(const CString &strValueID, const CString &strValue)
{
	return stt_SetDataValueByID(m_pSttParas, strValueID, strValue);
}


void CSttCmdData::AddMsg(const CString &strID, const CString &strMsg)
{
	CSttMsgs *pMsgs = GetSttMsgs();
	pMsgs->AddMsg(strID, strMsg);
}


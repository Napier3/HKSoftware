#include "stdafx.h"
#include "PpDeviceRefs.h"

//2021-1-5  lijunqing 简化版本的处理
#include "TCtrlCntrConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
CPpDeviceRef::CPpDeviceRef()
{
#ifndef  _not_use_autotest_
	m_bConnected = FALSE;
	m_bPpDeviceCommError = FALSE;
	m_dwID = 0;
	m_bIsInConnecting = FALSE;
	m_oPpDevice = NULL;
#endif
}

CPpDeviceRef::~CPpDeviceRef()
{
#ifndef  _not_use_autotest_
		ReleaseDevice();
#endif
}

long CPpDeviceRef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

    xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpTemplateFileKey,oNode,m_strPpTemplateFile);
    xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_stDeviceModelFileKey,oNode,m_strDeviceModelFile);
    xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpEngineProgIDKey,oNode,m_strPpEngineProgID);

	return 0;
}

long CPpDeviceRef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

    xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpTemplateFileKey,oElement,m_strPpTemplateFile);
    xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_stDeviceModelFileKey,oElement,m_strDeviceModelFile);
    xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpEngineProgIDKey,oElement,m_strPpEngineProgID);

	return 0;
}

BOOL CPpDeviceRef::IsDeviceConnectSucc()
{
#ifndef  _not_use_autotest_
	if (m_oPpDevice == NULL)
	{
		return FALSE;
	}

	try
	{
		m_bConnected = m_oPpDevice->IsConnectSuccessful();
	}
	catch (...)
	{
		m_bConnected = FALSE;
	}
	
	return m_bConnected;

#else
	return FALSE;
#endif
}

BOOL CPpDeviceRef::IsPpDeviceCommError()
{
#ifndef  _not_use_autotest_
	return m_bPpDeviceCommError;
#else
	return FALSE;
#endif
}

void CPpDeviceRef::ValidatePpEngineProgID(const CString &strPpEngineProgID)
{
	if (m_strPpEngineProgID.GetLength() == 0)
	{
		m_strPpEngineProgID = strPpEngineProgID;
	}
}

/*
测试模板编辑的时候，会使用原始的设备数据模型，执行测试的时候，会选择实际的模型
这两个模型可能是不同的文件。对于不同的设备数据模型文件，可能需要使用模型映射关系文件
调用PpDevice.CommConfig方法：规约引擎程序就是处理这件事情

2017-4-5:MMS规约引擎支持上述模式
    在多装置多组的测试模式中，通讯配置需要通过CmmConfig进行
*/
#ifndef  _not_use_autotest_
long CPpDeviceRef::SetCommConfig(CDataGroup *pCmmConfig)
{
#ifndef _PSX_QT_LINUX_
	m_oCommConfig.DeleteAll();
	m_oCommConfig.AppendClone(*pCmmConfig);
#endif
/*
    m_pCommConfig = pCmmConfig;
	if (pCmmConfig->GetCount() == 0)
	{
		return 0;
	}

	CString strCommConfig;
	pCmmConfig->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strCommConfig);
	SetCommConfig(strCommConfig);
*/
	return 0;
}

long CPpDeviceRef::SetCommConfig(const CString &strCommConfig)
{
	m_oPpDevice->SetCommConfig(strCommConfig);
	return 0;
}

void CPpDeviceRef::CommConfig()
{
	if (m_bIsInConnecting)
	{
		return;
	}

	m_bIsInConnecting = TRUE;
	CString strConfig;
	strConfig = GetCommConfigEx();   //shaolei 2023-9-12
	m_oPpDevice->m_strID = m_strID;

	try
	{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
#ifndef _PSX_QT_LINUX_
		m_oPpDevice->InitCommConfig(&m_oCommConfig);
#endif
#else
#endif
		m_oPpDevice->CommConfig(strConfig);
	}
	catch(...)
	{

	}
}

CString CPpDeviceRef::GetCommConfig()
{
	CDvmDataset oDataset;
	CDvmData *pData = oDataset.AddNewData(_T("DvmFile"), _T("DvmFile"), _T("string"), _T(""));

	CBufferBase oBuffer;
	oBuffer.InitBuffer(m_strSrcDeviceModelFile);
	oBuffer.FormatBuffer('\r');
	oBuffer.FormatBuffer('\n');
	char *p = oBuffer.GetString();
	CString strFile;

	while (oBuffer.IsPoiterInBuffer())
	{
		p = oBuffer.GetString();
		strFile = p;

		if (strFile.GetLength() > 4)
		{
			pData->SetAttr(strFile, strFile);
		}

		p = oBuffer.NextString();
	}

	//2021-1-5  lijunqing 简化版本的处理
	if (CTCtrlCntrConfig::IsSimpleTestMode())
	{
		CTCtrlCntrConfig::GetIP_Device(&oDataset);
	}

	CString strXml;
	oDataset.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strXml);

	return strXml;
}

//shaolei 2023-9-12
/*
pDevice->GetDataValue(STT_CMD_PARA_EngineMode, pRef->m_strEngineMode);
pDevice->GetDataValue(STT_CMD_PARA_EngineProgID, pRef->m_strPpEngineProgID);
pDevice->GetDataValue(STT_CMD_PARA_DeviceSN, pRef->m_strID);
pDevice->GetDataValue(STT_CMD_PARA_DvmFile, pRef->m_strDeviceModelFile);
pDevice->GetDataValue(XPARA_ID_PPXMLFILE, pRef->m_strPpTemplateFile);
*/
CString CPpDeviceRef::GetCommConfigEx()
{
	CDataGroup oDataGrp;
	oDataGrp.AddNewData(_T("EngineProgID")/*STT_CMD_PARA_EngineProgID*/, m_strPpEngineProgID);
	oDataGrp.AddNewData(_T("DeviceSN")/*STT_CMD_PARA_DeviceSN*/, m_strID);
	oDataGrp.AddNewData(_T("dvm-file")/*STT_CMD_PARA_DvmFile*/, m_strDeviceModelFile);
	oDataGrp.AddNewData(XPARA_ID_PPXMLFILE, m_strPpTemplateFile);

	CString strXml;
	oDataGrp.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strXml);

	return strXml;
}

void CPpDeviceRef::SetConnectState(BOOL bState)
{
	m_bIsInConnecting = FALSE;
	m_bConnected = bState;
}

void CPpDeviceRef::SetPpDeviceCommError(BOOL bState)
{
	m_bPpDeviceCommError = bState;
}

#endif


BOOL CPpDeviceRef::CopyOwn(CBaseObject* pDest)
{
	CPpDeviceRef *p = (CPpDeviceRef*)pDest;

	CExBaseObject::CopyOwn(pDest);
	
	p->m_strPpTemplateFile = m_strPpTemplateFile;
	p->m_strDeviceModelFile = m_strDeviceModelFile;
	p->m_strPpEngineProgID = m_strPpEngineProgID;
	p->m_strSrcDeviceModelFile = m_strSrcDeviceModelFile;
	p->m_strEngineMode = m_strEngineMode;

	return TRUE;
}

CBaseObject* CPpDeviceRef::Clone()
{
	CPpDeviceRef *p = new CPpDeviceRef();
	Copy(p);
	return p;
}

CBaseObject* CPpDeviceRef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPpDeviceRef *p = new CPpDeviceRef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}



CPpDeviceRefs::CPpDeviceRefs()
{
	m_bPpxmlAdvance = FALSE;
	m_nInitBy = DeviceRefs_InitBy_NONE;	
}

void CPpDeviceRefs::CreateAllDeviceForEdit(CExBaseList &oListCpus, const CString &strPpEngineID)
{
	long nOldCount = GetCount();
	long nCurrCount = oListCpus.GetCount();
	CPpDeviceRef *pPpDeviceRef = NULL;

	if (nOldCount > nCurrCount)
	{
		while (nOldCount>nCurrCount)
		{
			DeleteTail();
			nOldCount--;
		}
	}
	else if (nOldCount < nCurrCount)
	{
		while (nOldCount<nCurrCount)
		{
			pPpDeviceRef = new CPpDeviceRef();
			AddTail(pPpDeviceRef);
			nOldCount++;
		}
	}

	POS pos = oListCpus.GetHeadPosition();
	CCpus *pCpus = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		pCpus = (CCpus *)oListCpus.GetNext(pos);
		pPpDeviceRef = (CPpDeviceRef*)GetAtIndex(nIndex);
		pPpDeviceRef->m_strID = pCpus->m_strID;
		pPpDeviceRef->m_strName = pCpus->m_strName;
		pPpDeviceRef->m_strPpEngineProgID = pCpus->m_strPpEngineProgID;
		pPpDeviceRef->ValidatePpEngineProgID(strPpEngineID);

#ifndef  _not_use_autotest_
		pPpDeviceRef->m_dwID = nIndex;
#endif

		nIndex++;
	}
}

void CPpDeviceRefs::ReleaseAllDevice()
{
	POS pos = GetHeadPosition();
	CPpDeviceRef *pDevice = NULL;

	while (pos != NULL)
	{
		pDevice = (CPpDeviceRef*)GetNext(pos);
		pDevice->ReleaseDevice();
	}
}

#ifndef  _not_use_autotest_

BOOL CPpDeviceRefs::IsAllDeviceConnectSucc()
{
	POS pos = GetHeadPosition();
	CPpDeviceRef *pDevice = NULL;
	BOOL bSucc = TRUE;

	while (pos != NULL)
	{
		pDevice = (CPpDeviceRef*)GetNext(pos);

		if (!pDevice->IsDeviceConnectSucc())
		{
			bSucc = FALSE;
			break;
		}
	}

	return bSucc;
}

void CPpDeviceRefs::CreateAllDevice(CExBaseList &oListCpus, const CString &strPpEngineID
									, const CString &strPpTemplateFile, const CString &strDeviceFile
									, const CString &strEngineMode, BOOL bUseOwn)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("++++for debug+  CPpDeviceRefs::CreateAllDevice +++ %s  \r\n %s \r\n  %s  \r\n %s  \r\n %d   ")
	//	, strPpEngineID, strPpTemplateFile, strDeviceFile, strEngineMode, (long)bUseOwn);
	POS pos = oListCpus.GetHeadPosition();
	CCpus *pCpus = NULL;
	CPpDeviceRef *pPpDeviceRef = NULL;
	long nIndex = 0;
	CDevice *pDevice = NULL;

	while (pos != NULL)
	{
		pCpus = (CCpus *)oListCpus.GetNext(pos);
		pPpDeviceRef = new CPpDeviceRef();
		pPpDeviceRef->m_strID = pCpus->m_strID;
		pPpDeviceRef->m_strName = pCpus->m_strName;
		pPpDeviceRef->m_dwID = nIndex;
		pDevice = (CDevice *)pCpus->GetAncestor(GBCLASSID_DEVICE);
		pPpDeviceRef->m_strSrcDeviceModelFile = pDevice->m_strSrcDeviceModelFile;

		if (bUseOwn)
		{
			pPpDeviceRef->m_strPpTemplateFile = pCpus->m_strPpTemplateFile;
			pPpDeviceRef->m_strDeviceModelFile = pCpus->m_strDeviceModelFile;
			pPpDeviceRef->m_strPpEngineProgID = pCpus->m_strPpEngineProgID;

            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("++111++for debug  CPpDeviceRefs::CreateAllDevice+++ bUseOwn++++%s+++%s+++%s")
                                       , pCpus->m_strPpEngineProgID.GetString(), pCpus->m_strPpTemplateFile.GetString(), pCpus->m_strDeviceModelFile.GetString());
		}
		else
		{
			pPpDeviceRef->m_strPpTemplateFile = strPpTemplateFile;
			pPpDeviceRef->m_strDeviceModelFile = strDeviceFile;
			pPpDeviceRef->m_strPpEngineProgID = strPpEngineID;
			pPpDeviceRef->m_strEngineMode = strEngineMode;

			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("++121++for debug  CPpDeviceRefs::CreateAllDevice++++%s+++%s+++%s+++%s")
				, strPpEngineID.GetString(), strPpTemplateFile.GetString(), strDeviceFile.GetString(), strEngineMode.GetString());

		}
		
		if (pCpus->m_strDeviceModelFile.GetLength() > 0 && strDeviceFile.GetLength() == 0)
		{
			pPpDeviceRef->m_strPpTemplateFile = pCpus->m_strPpTemplateFile;
			pPpDeviceRef->m_strDeviceModelFile = pCpus->m_strDeviceModelFile;
			pPpDeviceRef->m_strPpEngineProgID = pCpus->m_strPpEngineProgID;

			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("++++for debug  CPpDeviceRefs::CreateAllDevice+++ 1++++%s"), pCpus->m_strPpEngineProgID.GetString());
		}

		if (pPpDeviceRef->m_strDeviceModelFile.GetLength() == 0)
		{
			pPpDeviceRef->m_strPpTemplateFile = strPpTemplateFile;
			pPpDeviceRef->m_strDeviceModelFile = strDeviceFile;
			pPpDeviceRef->m_strPpEngineProgID = strPpEngineID;

            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("++222++for debug  CPpDeviceRefs::CreateAllDevice+++ 2++++%s+++%s+++%s")
                                       , pCpus->m_strPpEngineProgID.GetString(), pCpus->m_strPpTemplateFile.GetString(), pCpus->m_strDeviceModelFile.GetString());
		}

		AddTail(pPpDeviceRef);
		nIndex++;
	}
}

CPpDeviceRef* CPpDeviceRefs::FindPpDeviceRef(DWORD dwID)
{
	POS pos = GetHeadPosition();
	CPpDeviceRef *pDevice = NULL;
	CPpDeviceRef *pFind = NULL;
	BOOL bSucc = TRUE;

	while (pos != NULL)
	{
		pDevice = (CPpDeviceRef*)GetNext(pos);

		if (pDevice->m_dwID == dwID)
		{
			pFind = pDevice;
			break;
		}
	}

	return pFind;
}

CProtocolDeviceInterface* CPpDeviceRefs::FindByID(DWORD dwID)
{
	CPpDeviceRef *pFind = FindPpDeviceRef(dwID);
	ASSERT (pFind != NULL);
	
	if (pFind == NULL)
	{
		return NULL;
	}
	else
	{
		return pFind->m_oPpDevice;
	}
}

CPpDeviceRef* CPpDeviceRefs::GetPpDeviceRefToConnect()
{
	POS pos = GetHeadPosition();
	CPpDeviceRef *pDevice = NULL;
	CPpDeviceRef *pFind = NULL;
	BOOL bSucc = TRUE;

	while (pos != NULL)
	{
		pDevice = (CPpDeviceRef*)GetNext(pos);

		if (!pDevice->IsDeviceConnectSucc())
		{
			pFind = pDevice;
			break;
		}
	}

	return pFind;
}

CPpDeviceRef* CPpDeviceRefs::GetPpDeviceConnecting()
{
	POS pos = GetHeadPosition();
	CPpDeviceRef *pDevice = NULL;
	CPpDeviceRef *pFind = NULL;
	BOOL bSucc = TRUE;

	while (pos != NULL)
	{
		pDevice = (CPpDeviceRef*)GetNext(pos);

		if (pDevice->m_bIsInConnecting)
		{
			pFind = pDevice;
			break;
		}
	}

	return pFind;
}

CProtocolDeviceInterface* CPpDeviceRefs::Find(long nDeviceIndex, long nCommCmdCurrDeviceIndex)
{
	CPpDeviceRef *pFind = NULL;

	if (nDeviceIndex == DSID_ALL_DVM)
	{
		pFind = (CPpDeviceRef*)GetAtIndex(nCommCmdCurrDeviceIndex);
	}
	else
	{
		pFind = (CPpDeviceRef*)GetAtIndex(nDeviceIndex);
	}

	//避免多设备数据模型拷贝到单模型下带来的问题
	ASSERT (pFind != NULL);

	if (pFind == NULL)
	{
		pFind = (CPpDeviceRef*)GetHead();
	}

	if (pFind == NULL)
	{
		return NULL;
	}
	else
	{
		return pFind->m_oPpDevice;
	}
}

BOOL CPpDeviceRefs::ValidatePpDeviceRefs()
{
	POS pos = GetHeadPosition();
	CPpDeviceRef *pDevice = NULL;
	BOOL bSucc = TRUE;

	while (pos != NULL)
	{
		pDevice = (CPpDeviceRef*)GetNext(pos);

		if (pDevice->m_strPpEngineProgID.GetLength() == 0)
		{
			bSucc = FALSE;
			break;
		}
		if (pDevice->m_strPpEngineProgID == g_strPpEngineProgIDMms || pDevice->m_strPpEngineProgID == g_strPpEngineProgIDDlt)
		{
			if (pDevice->m_strDeviceModelFile.GetLength() == 0)
			{
				bSucc = FALSE;
				break;
			}
		}
		else 
		{
			if (pDevice->m_strPpTemplateFile.GetLength() == 0
				|| pDevice->m_strDeviceModelFile.GetLength() == 0)
			{
				bSucc = FALSE;
				break;
			}
		}

// 		if (pDevice->m_strPpEngineProgID != g_strPpEngineProgIDMms)
// 		{
// 			if (pDevice->m_strPpTemplateFile.GetLength() == 0
// 				|| pDevice->m_strDeviceModelFile.GetLength() == 0)
// 			{
// 				bSucc = FALSE;
// 				break;
// 			}
// 		}
// 		else 
// 		{
// 			if (pDevice->m_strDeviceModelFile.GetLength() == 0)
// 			{
// 				bSucc = FALSE;
// 				break;
// 			}
// 		}
	}

	return bSucc;
}
#endif


long CPpDeviceRefs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CPpDeviceRefs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

BOOL CPpDeviceRefs::CopyOwn(CBaseObject* pDest)
{
	CPpDeviceRefs *p = (CPpDeviceRefs*)pDest;
	p->m_nInitBy = m_nInitBy;
	p->m_bPpxmlAdvance = m_bPpxmlAdvance;

	return TRUE;
}


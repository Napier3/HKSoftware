#include "StdAfx.h"
#include "Device.h"
#include "Items.h"
#include "SysParas.h"
#include "Cpus.h"
#include "../XLanguageResourceAts.h"
#include "../../../Module/API/FileApi.h"

#ifdef _use_CDataChangeMsgTool
#include "DeviceModelChangeTool.h"
#endif
#include "../../../Module/API/MathApi.h"

CDevice::CDevice(void)
{
	m_pCpus = NULL;
	m_pSysParas = NULL;
	m_pCharacteristics = NULL;
	m_pTestParas = NULL;
#ifndef _PSX_QT_LINUX_
    m_pGbtDataInterfaces = NULL;
#endif

	m_strDeviceType = _T("");
	m_strFactory = _T("");
	m_nIsTimeSetsUnit_ms = 1;

#ifdef _use_CDataChangeMsgTool
	CDvmDataChangeMsgTool::Register(this);
#endif

	m_nDsvTextWithValue = 1;
	m_nDsvTextWithUtcTime = 1;
}

CDevice::~CDevice(void)
{
#ifdef _use_CDataChangeMsgTool
	CDvmDataChangeMsgTool::UnRegister(this);
#endif
}

void CDevice::InitAfterReadGb()
{
	if(m_pSysParas == NULL)
	{
		m_pSysParas = new CSysParas();
		AddHead(m_pSysParas);
		m_pSysParas->m_strName =g_sLangTxt_TestPara/* L"���Բ���"*/;
		m_pSysParas->m_strID = g_strwSysPara;
		m_pSysParas->SetParent(this);
	}

	if(m_pCpus == NULL)
	{
		m_pCpus = new CCpus();
		AddHead(m_pCpus);
		m_pCpus->SetParent(this);
	}

#ifndef _PSX_QT_LINUX_
    if (m_pGbtDataInterfaces != NULL)
	{
		Delete(m_pGbtDataInterfaces);
		m_pGbtDataInterfaces = NULL;
	}
#endif
}

void CDevice::InitAfterReadGbt()
{
	if(m_pSysParas == NULL)
	{
		m_pSysParas = new CSysParas();
		AddHead(m_pSysParas);
		m_pSysParas->m_strName = g_sLangTxt_TestPara/*L"���Բ���"*/;
		m_pSysParas->m_strID = g_strwSysPara;
		m_pSysParas->SetParent(this);
	}

#ifndef _PSX_QT_LINUX_
    if(m_pGbtDataInterfaces == NULL)
	{
		m_pGbtDataInterfaces = new CGbtDataInterfaces();
		AddHead(m_pGbtDataInterfaces);
		m_pGbtDataInterfaces->SetParent(this);
		m_pGbtDataInterfaces->InitAfterRead();
	}
#endif

    if (m_pCpus != NULL)
	{
		Delete(m_pCpus);
		m_pCpus = NULL;
	}
}

void CDevice::RemoveExpandDatas(CDvmDataset *pDatas)
{
	POS pos = pDatas->GetHeadPosition();
	CDvmData *pData = NULL;
	POS posFind = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDatas->GetNext(pos);
		posFind = m_pSysParas->FindPosByID(pData->m_strID);

		if (posFind != NULL)
		{
			m_pSysParas->DeleteAt(posFind);
		}
	}
}

void CDevice::ImportExpandDatas(CDvmDataset *pDatas)
{
	POS pos = pDatas->GetHeadPosition();
	CDvmData *pData = NULL;
	POS posFind = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDatas->GetNext(pos);
		m_pSysParas->AddNewDataObj(pData);
	}
}

void CDevice::UpdateSysPara(CExBaseList *pSrcList, BOOL bCreateNew)
{
	if (bCreateNew)
	{
		if(m_pSysParas == NULL)
		{
			m_pSysParas = new CSysParas();
			AddHead(m_pSysParas);
			m_pSysParas->m_strName =g_sLangTxt_TestPara/* L"���Բ���"*/;
			m_pSysParas->m_strID = g_strwSysPara;
			m_pSysParas->SetParent(this);
		}
	}

	if (m_pSysParas == NULL)
	{
		return;
	}

	POS pos = pSrcList->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pSrcList->GetNext(pos);

		if (bCreateNew)
		{
			m_pSysParas->AddNewDataObj(pData);
		}
		else
		{
			CDataObj *pDataObj = (CDataObj *)m_pSysParas->FindByID(pData->m_strID);

			if (pDataObj == NULL)
			{
				continue;
			}

			pDataObj->m_strName = pData->m_strName;
			pDataObj->m_strDataType = pData->m_strDataType;
			pDataObj->m_strUnit = pData->m_strUnit;
			pDataObj->m_strDefaultValue = pData->m_strValue;
			pDataObj->m_strValue = pData->m_strValue;
		}
		
	}
}

//2024-2-21 �����²��Բ�����value����
void CDevice::SetSysParaValue(CExBaseList *pSrcList, BOOL bCreateNew)
{
	if (pSrcList == NULL)
	{
		return;
	}

	if (bCreateNew)
	{
		if(m_pSysParas == NULL)
		{
			m_pSysParas = new CSysParas();
			AddHead(m_pSysParas);
			m_pSysParas->m_strName =g_sLangTxt_TestPara/* L"���Բ���"*/;
			m_pSysParas->m_strID = g_strwSysPara;
			m_pSysParas->SetParent(this);
		}
	}

	if (m_pSysParas == NULL)
	{
		return;
	}

	POS pos = pSrcList->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pSrcList->GetNext(pos);

		if (bCreateNew)
		{
			m_pSysParas->AddNewDataObj(pData);
		}
		else
		{
			CDataObj *pDataObj = (CDataObj *)m_pSysParas->FindByID(pData->m_strID);

			if (pDataObj != NULL)
			{
				pDataObj->m_strValue = pData->m_strValue;
				continue;
			}

			pDataObj = (CDataObj *)m_pSysParas->FindByName(pData->m_strName);

			if (pDataObj != NULL)
			{
				pDataObj->m_strValue = pData->m_strValue;
				continue;
			}
			
		}

	}
}

void CDevice::AddSrcDeviceModelFile(const CString &strFile)
{
	CString strTemp;
	CString strLibrary;
	strLibrary = _P_GetLibraryPath();
	strTemp = strFile;
	strTemp.Replace(strLibrary, _T(""));

	CString strName;
	strName = GetPathFileNameFromFilePathName(strFile);

	m_strSrcDeviceModelFile.Replace(strLibrary, _T(""));

	if (m_strSrcDeviceModelFile.GetLength() < 4)
	{
		m_strSrcDeviceModelFile = strFile;
	}
	else
	{
		if (m_strSrcDeviceModelFile.Find(strName) < 0)
		{
            m_strSrcDeviceModelFile.AppendFormat(_T("\r\n%s"), strTemp.GetString());
		}
	}
}

void CDevice::ReadAttr(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	XmlReadOwn(oNode,CGbXMLKeys::g_pGbXMLKeys);

	CXmlRWNodeListBase *oNodes = oNode.GetChildNodes();
	long nCount = oNodes->GetNodeNum();
	long nIndex = 0;
	CExBaseObject *pNew = NULL;
	CXmlRWNodeBase *oChild = NULL;
	BOOL bAddToTail = TRUE;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oChild = oNodes->GetChild(nIndex);
		CString strNodeName = oChild->GetNodeName();

		if ( (strNodeName == CGbXMLKeys::g_pGbXMLKeys->m_strCpusKey)
			|| (strNodeName == CGbXMLKeys::g_pGbXMLKeys->m_strDeviceModelKey) )
		{
			pNew = new CCpus;
			AddNewChild(pNew);
			pNew->XmlReadOwn(*oChild, pXmlRWKeys);
		}
	}
}

long CDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strFactoryKey,oNode,m_strFactory);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDeviceTypeKey,oNode,m_strDeviceType);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strIsTimeSetsUnit_ms_Key,oNode,m_nIsTimeSetsUnit_ms);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strSrcDeviceModelFileKey,oNode,m_strSrcDeviceModelFile);
	
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsvTextWithValueKey,oNode,m_nDsvTextWithValue);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsvTextWithUtcTimeKey,oNode,m_nDsvTextWithUtcTime);
	
	return 0;
}

long CDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	if (g_bGbSaveGbStruDscFile)
	{
		return 0;
	}

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strFactoryKey, oElement,   m_strFactory);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDeviceTypeKey, oElement, m_strDeviceType);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strIsTimeSetsUnit_ms_Key, oElement,m_nIsTimeSetsUnit_ms);

	if (!g_bGbExportXmlReportFile)
	{
		xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strSrcDeviceModelFileKey, oElement, m_strSrcDeviceModelFile);
	}

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsvTextWithValueKey, oElement,m_nDsvTextWithValue);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsvTextWithUtcTimeKey, oElement,m_nDsvTextWithUtcTime);

	return 0;
}

long CDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbItemBase::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_strFactory);
		BinarySerializeCalLen(oBinaryBuffer,m_nIsTimeSetsUnit_ms);
		BinarySerializeCalLen(oBinaryBuffer,m_nDsvTextWithValue);
		BinarySerializeCalLen(oBinaryBuffer,m_strSrcDeviceModelFile);
		BinarySerializeCalLen(oBinaryBuffer,m_nDsvTextWithUtcTime);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer,m_strFactory);

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_7)
		{
			BinarySerializeRead(oBinaryBuffer,m_nIsTimeSetsUnit_ms);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_19)
		{
			BinarySerializeRead(oBinaryBuffer,m_nDsvTextWithValue);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_23)
		{
			BinarySerializeRead(oBinaryBuffer,m_strSrcDeviceModelFile);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_25)
		{
			BinarySerializeRead(oBinaryBuffer, m_nDsvTextWithUtcTime);
		}
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_strFactory);
		BinarySerializeWrite(oBinaryBuffer,m_nIsTimeSetsUnit_ms);
		BinarySerializeWrite(oBinaryBuffer,m_nDsvTextWithValue);
		BinarySerializeWrite(oBinaryBuffer,m_strSrcDeviceModelFile);
		BinarySerializeWrite(oBinaryBuffer,m_nDsvTextWithUtcTime);
	}

	return TRUE;
}

CExBaseObject* CDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCpusKey)
	{
		m_pCpus = new CCpus;
		return m_pCpus;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strDeviceModelKey)
	{
		m_pCpus = new CCpus;
		return m_pCpus;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strSysParasKey)
	{
		m_pSysParas = new CSysParas();
		return m_pSysParas;
	}
// 	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strTestParasKey)
// 	{
// 		m_pTestParas = new CTestParas();
// 		return m_pTestParas;
// 	}
#ifndef _PSX_QT_LINUX_
    else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataInterfacesKey)
	{
		m_pGbtDataInterfaces = new CGbtDataInterfaces();
		return m_pGbtDataInterfaces;
	}
#endif
    else if (strClassID == CCharacteristicXmlRWKeys::g_pXmlKeys->m_strCCharacteristicsKey)
	{
		m_pCharacteristics = new CCharacteristics();
		return m_pCharacteristics;
	}

	CExBaseObject *p = GbItems_CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);

	if (p != NULL)
	{
		return p;
	}

	return CGbItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
	//return GbItems_CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CDevice::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_CPUS)
	{
		m_pCpus = new CCpus;
		//m_pCpus->m_strName = this->m_strName;
		return m_pCpus;
	}
	else if (nClassID == GBCLASSID_DEVICE_SYSPARAS)
	{
		return new CSysParas();
	}
	else if (nClassID == GBCLASSID_DEVICE_TESTPARAS)
	{
		return new CTestParas();
	}
	else if (nClassID == CHARCLASSID_CCHARACTERISTICS)
	{
		m_pCharacteristics = new CCharacteristics;
		return m_pCharacteristics;
	}
	else if (nClassID == GBCLASSID_GBTDATAINTERFACES)
	{
#ifndef _PSX_QT_LINUX_
        m_pGbtDataInterfaces = new CGbtDataInterfaces;
		return m_pGbtDataInterfaces;
#endif
    }

	CExBaseObject *p = GbItems_CreateNewChild(nClassID);

	if (p != NULL)
	{
		return p;
	}

	return CGbItemBase::CreateNewChild(nClassID);
}

BOOL CDevice::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);
	if(pDest == this)
		return TRUE;
	
	CDevice* pDevice = (CDevice*)pDest;
	pDevice->m_strFactory = m_strFactory;
	pDevice->m_nIsTimeSetsUnit_ms = m_nIsTimeSetsUnit_ms;
	pDevice->m_nDsvTextWithValue = m_nDsvTextWithValue;
	pDevice->m_nDsvTextWithUtcTime = m_nDsvTextWithUtcTime;

	CExBaseObject::CopyOwn(pDevice);

	return TRUE;
}

CBaseObject* CDevice::Clone()
{
	CDevice* pDevice = new CDevice();
	Copy(pDevice);

	return pDevice;
}


BOOL CDevice::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_SAFETY || nClassID == GBCLASSID_MACROTEST || nClassID == GBCLASSID_SYSPARAEDIT
		|| nClassID == GBCLASSID_COMMCMD || nClassID == GBCLASSID_ITEMS)
	{
		return TRUE;
	}

	return FALSE;
}

void CDevice::InitAfterRead()
{
	CGbItemBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CExBaseObject* p = NULL;
	UINT nClassID = 0;
	CExBaseList oListCpu;
	
	while(pos)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case GBCLASSID_DEVICE_SYSPARAS:
			m_pSysParas = (CSysParas*)p;
			break;
		case GBCLASSID_DEVICE_TESTPARAS:
			m_pTestParas = (CTestParas*)p;
			break;
		case GBCLASSID_CPUS:
			oListCpu.AddTail(p);
			break;
		case GBCLASSID_GBTDATAINTERFACE:
#ifndef _PSX_QT_LINUX_
            m_pGbtDataInterfaces = (CGbtDataInterfaces*)p;
#endif
            break;
		case CHARCLASSID_CCHARACTERISTICS:
			m_pCharacteristics = (CCharacteristics*)p;
			break;
		}
	}
	
	//��ʼ��סCPU
	m_pCpus = (CCpus*)oListCpu.GetHead();
	
	if(m_pCharacteristics == NULL)
	{
		m_pCharacteristics = new CCharacteristics();
		AddHead(m_pCharacteristics);
		m_pCharacteristics->SetParent(this);
	}

	if (Gb_IsGuideBookTemplate(this))
	{
		InitAfterReadGbt();
	}
	else
	{
		InitAfterReadGb();
	}

	//BringToHead(m_pTestParas);

	if (m_pTestParas != NULL)
	{
		Delete(m_pTestParas);
		m_pTestParas = m_pSysParas;
	}

	BringToHead(m_pCharacteristics);
	BringToHead(m_pSysParas);
	m_pSysParas->m_strID = g_strwSysPara;

	pos = oListCpu.GetTailPosition();
	while (pos != NULL)
	{
		p = oListCpu.GetPrev(pos);
		BringToHead(p);
	}

	oListCpu.RemoveAll();

	//m_pCharacteristics->InitVariableValues();
}

long CDevice::GetCpusList(CExBaseList &oListCpu, BOOL bAppend)
{
	POS pos = GetHeadPosition();
	CExBaseObject* p = NULL;

	if (!bAppend)
	{
		oListCpu.RemoveAll();
	}

	while(pos)
	{
		p = GetNext(pos);
		if (GBCLASSID_CPUS == p->GetClassID())
		{
			oListCpu.AddTail(p);
		}
	}

	return oListCpu.GetCount();
}

CCpus* CDevice::GetCpusEx(long nCpusIndex)
{
	CExBaseList oListCpu;
	GetCpusList(oListCpu);
	CCpus *pCpus = NULL;

	if (nCpusIndex == DSID_ALL_DVM)
	{
		pCpus = GetCpus();
	}
	else
	{
		pCpus = (CCpus *)oListCpu.GetAtIndex(nCpusIndex);

		if (pCpus == NULL)
		{
			pCpus = GetCpus();
		}
	}

	oListCpu.RemoveAll();

	return pCpus;
}

// CSet* CDevice::GetSetAtIndex(long nIndex)
// {
// 	CSet *pSet = NULL;
// 	POS pos = m_pCpus->GetHeadPosition();
// 	CCpu *pCpu = NULL;
// 	long nTemp = nIndex;
// 	long nCount = 0;
// 
// 	while (pos != NULL)
// 	{
// 		pCpu = (CCpu*)m_pCpus->GetNext(pos);
// 		nCount = pCpu->m_pSets->GetCount();
// 
// 		if (nTemp - nCount < 0)
// 		{
// 			pSet = (CSet*)pCpu->m_pSets->GetAtIndex(nTemp);
// 			break;
// 		}
// 		else
// 		{
// 			nTemp = nTemp - nCount;
// 		}
// 	}
// 
// 	return pSet;
// }
// 
// CSet* CDevice::FindSetByID(const CString &strID)
// {
// 	CSet *pFind = NULL;
// 	CCpu *pCpu = NULL;
// 	long nPos = strID.Find(_T("."));
// 
// 	if (nPos < 0)
// 	{
// 		nPos = strID.Find(_P_FOLDER_PATH_SEPARATOR_);
// 	}
// 
// 	if (nPos > 0)
// 	{
// 		CString strCpu = strID.Left(nPos);
// 		CString strSet = strID.Mid(nPos+1);
// 
// 		pCpu = (CCpu*)m_pCpus->FindByID(strCpu);
// 
// 		if (pCpu != NULL)
// 		{
// 			pFind = (CSet *)pCpu->m_pSets->FindByID(strSet);
// 		}
// 	}
// 	else
// 	{
// 		POS pos = m_pCpus->GetHeadPosition();
// 
// 		while (pos != NULL)
// 		{
// 			pCpu = (CCpu*)m_pCpus->GetNext(pos);
// 			pFind = (CSet*)pCpu->m_pSets->FindByID(strID);
// 
// 			if (pFind != NULL)
// 			{
// 				break;
// 			}
// 		}
// 
// 	}
// 
// 	return pFind;
// }
// 
// CSet* CDevice::FindSetByName(const CString &strName)
// {
// 	CSet *pFind = NULL;
// 	CCpu *pCpu = NULL;
// 
// 	POS posCpu = m_pCpus->GetHeadPosition();
// 
// 	while (posCpu != NULL)
// 	{
// 		pCpu = (CCpu *)m_pCpus->GetNext(posCpu);
// 		pFind = (CSet *)pCpu->FindBySetName(strName);
// 
// 		if (pFind != NULL)
// 		{
// 			break;
// 		}
// 	}
// 
// 	return pFind;
// }

//2019-12-31  lijunqing
CDataObj* CDevice::SelectDataObj(const CString &strPath)
{
	long nDvIndex = Gb_GetDvmIndexFromPath(strPath);

	return FindDataObjByID(strPath, nDvIndex);
}

long CDevice::SelectDataObj(const CString &strPath, CExBaseList &listDatas)
{
	long nDvIndex = Gb_GetDvmIndexFromPath(strPath);
	CDataObj *pFind = NULL;

	if (nDvIndex < 0)
	{
		pFind = (CDataObj*)m_pSysParas->FindByID(strPath);

		if (pFind != NULL)
		{
			listDatas.AddTail(pFind);
			return 1;
		}
	}

	CCpus *pCpus = m_pCpus;

	if (nDvIndex >= 0)
	{
		pCpus = GetCpusEx(nDvIndex);
	}

	pCpus->SelectDataObj(strPath, listDatas);

	return listDatas.GetCount();
}

CDataObj* CDevice::FindDataObjByID(const CString &strPath, long nDeviceModelIndex)
{
	CDataObj *pFind = NULL;

	//2020-1-1  lijunqing   ���豸����ģ�͵Ĵ���
	long nDvIndex = Gb_GetDvmIndexFromPath(strPath);

	if (nDvIndex > 0)
	{
		nDeviceModelIndex = nDvIndex;
	}

	//2020-1-1  lijunqing  ���豸����ģ�͵Ĵ���  ����Ĵ��벻��
	if(Gb_IsGuideBookTemplate(this))
	{
		pFind = (CDataObj*)m_pSysParas->FindByID(strPath);

		if (pFind == NULL)
		{
#ifndef _PSX_QT_LINUX_
            ASSERT (m_pGbtDataInterfaces->m_pGbtDatas != NULL);
			pFind = (CDataObj*)m_pGbtDataInterfaces->m_pGbtDatas->FindByID(strPath);
#endif
        }
	}
	else
	{
		if (DS_InStringDataPath(strPath))  //�˴�Ҫ��strPath��û������ �ŷ���TRUE  shaolei
		{
			CCpus *pCpus = m_pCpus;

			if (nDeviceModelIndex >= 0)
			{
				pCpus = GetCpusEx(nDeviceModelIndex);

				if (pCpus == NULL)
				{
					pCpus = m_pCpus;
				}
			}

			pFind = pCpus->SelectDataObj(strPath);

			if (pFind == NULL)
			{
				pFind = pCpus->FindDataObjByID(strPath);
			}

			if (pFind == NULL)
			{
				pFind = (CDataObj*)m_pSysParas->FindByID(strPath);
			}
		}
		else
		{
			pFind = (CDataObj*)m_pSysParas->FindByID(strPath);

			//shaolei 2019.06.20
			if (pFind == NULL)
			{
				pFind = m_pCpus->SelectDataObj(strPath);
			}

			if (pFind == NULL)
			{
				pFind = m_pCpus->FindDataObjByID(strPath);
			}
		}
	}

	return pFind;
}

CDataObj* CDevice::FindDataObjByName(const CString &strName)
{
#ifndef _PSX_QT_LINUX_
    ASSERT (m_pCpus != NULL || m_pGbtDataInterfaces != NULL);
#endif

	if (m_pCpus != NULL)
	{
		CDataObj *pFind = m_pCpus->FindDataObjByName(strName);

		if (pFind == NULL)
		{
			pFind = (CDataObj*)m_pSysParas->FindByName(strName);
		}

		return pFind;
	}

#ifndef _PSX_QT_LINUX_
    if (m_pGbtDataInterfaces != NULL)
	{
		return (CDataObj*)m_pGbtDataInterfaces->m_pGbtDatas->FindByID(strName);
	}
#endif

	return NULL;
}

CExBaseObject* CDevice::FindDvmDataObj(const CString &strID)
{
	if (m_pCpus != NULL)
	{
		return m_pCpus->FindChildByIDEx(strID);
	}

#ifndef _PSX_QT_LINUX_
    if (m_pGbtDataInterfaces != NULL)
	{
		return (CDataObj*)m_pGbtDataInterfaces->m_pGbtDatas->FindChildByIDEx(strID);
	}
#endif

	return NULL;
}

void CDevice::InsertSetsToComboBox(CComboBox *pComboBox)
{
// 	if (m_pCpus == NULL)
// 	{
// 		return;
// 	}
// 
// 	POS pos = m_pCpus->GetHeadPosition();
// 	CCpu* pCpu = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pCpu = (CCpu*)m_pCpus->GetNext(pos);
// 
// 		if (pCpu->m_pSets != NULL)
// 		{
// 			pComboBox->ResetContent();
// 			pCpu->m_pSets->InsertChildreComboBox(pComboBox);
// 		}
// 	}
}

void CDevice::InsertSysParasToComboBox(CComboBox *pComboBox)
{
	if (m_pSysParas == NULL)
	{
		return;
	}

	pComboBox->ResetContent();
	m_pSysParas->InsertChildreComboBox(pComboBox);
}


BOOL CDevice::GetVariableValue(const CString &strVariable, CString &strValue, BOOL bShowLog)
{
	if (m_pSysParas == NULL)
	{
		return FALSE;
	}

	CDataObj *pPara = (CDataObj*)m_pSysParas->FindByID(strVariable);

	if (pPara != NULL)
	{
		strValue = pPara->m_strValue;
		return TRUE;
	}

	CExBaseObject *pObj = FindDataObjByID(strVariable, -1);

	if (pObj != NULL)
	{
		if (pObj->GetClassID() == GBCLASSID_DATAOBJ)
		{
			CDataObj *pSet = (CDataObj *)pObj;
			strValue = pSet->m_strValue;
		}
		else if (pObj->GetClassID() == GBCLASSID_DATAOBJ_VALUE)
		{
			CDataObjValue *pSet = (CDataObjValue *)pObj;
		strValue = pSet->m_strValue;
		}

		return TRUE;
	}

	if (bShowLog)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Variable [%s] not exist!"), strVariable.GetString());
	}

	return FALSE;
}

BOOL CDevice::GetVariableValue(const CString &strVariable, double &dValue, BOOL bShowLog)
{
	CString strValue;

	if (GetVariableValue(strVariable, strValue, bShowLog))
	{
		dValue = CString_To_double(strValue);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDevice::GetVariableValue2(const CString &strVariable, CString &strValue, BOOL bShowLog)
{
	CDataObj *pPara = (CDataObj*)m_pSysParas->FindByID(strVariable);

	if (pPara != NULL)
	{
		strValue = pPara->m_strValue;
		return TRUE;
	}

	CExBaseObject *pFind = m_pCpus->FindChildByIDEx(strVariable);

	if (pFind != NULL)
	{
		UINT nClassID = pFind->GetClassID();
		if (nClassID == GBCLASSID_DATAOBJ)
		{
			strValue = ((CDataObj*)pFind)->m_strValue;
		}
		else if (nClassID == GBCLASSID_DATAVALUE)
		{
			strValue = ((CDataObjValue*)pFind)->m_strValue;
		}
		else
		{
			ASSERT (FALSE);
		}

		return TRUE;
	}

	if (bShowLog)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Variable [%s] not exist!"), strVariable.GetString());
	}

	return FALSE;
}

BOOL CDevice::GetVariableValue2(const CString &strVariable, double &dValue, BOOL bShowLog)
{
	CString strValue;

	if (GetVariableValue2(strVariable, strValue, bShowLog))
	{
		dValue = CString_To_double(strValue);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CExBaseList* CDevice::GetDeviceModelDatasById(const CString &strCpuID, const CString &strDeviceModelTypeID)
{
	if (strDeviceModelTypeID == _T(""))
	{
		return NULL;
	}

	if (g_strDeviceModel_SysPara == strDeviceModelTypeID)
	{
		return m_pSysParas;
	}
	else if (g_strDeviceModel_TestPara == strDeviceModelTypeID)
	{
		return m_pSysParas;
	}
	else
	{
		if (m_pCpus != NULL)
		{
			return m_pCpus->GetDeviceModelDatasById(strCpuID, strDeviceModelTypeID);
		}
		else
		{
			return NULL;
		}
	}
}

long CDevice::GetDataSetList(const CString &strKey, CExBaseList &oListDataSet, long nCpusIndex)
{	
	if (Gb_IsGuideBookTemplate(this))
	{
#ifndef _PSX_QT_LINUX_
        ASSERT (m_pGbtDataInterfaces != NULL);
		ASSERT (m_pGbtDataInterfaces->m_pGbtDatas != NULL);
		oListDataSet.AddTail(m_pGbtDataInterfaces->m_pGbtDatas);
#endif
        return 1;
	}
	else
	{
		CCpus *pCpus = GetCpusEx(nCpusIndex);
		return pCpus->GetDataSetList(strKey, oListDataSet);
	}
}

CExBaseList* CDevice::GetDeviceDodelDatas(long nCpusIndex)
{
	if (Gb_IsGuideBookTemplate(this))
	{
#ifndef _PSX_QT_LINUX_
        ASSERT (m_pGbtDataInterfaces != NULL);
		ASSERT(m_pGbtDataInterfaces->m_pGbtDatas != NULL);
		return m_pGbtDataInterfaces->m_pGbtDatas;
#else
        return NULL;
#endif
    }
	else
	{
		CCpus *pCpus = GetCpusEx(nCpusIndex);
		ASSERT (pCpus != NULL);
		return pCpus;
	}
}

long CDevice::SelectDataSetList(const CString &strIDPath, CExBaseList &oListDataSet, long nCpusIndex)
{
	CExBaseObject *p = NULL;
	CDataSet *pDataSetHead = NULL;
	CString strDatasetNamePath;

	//ϵͳ����
	if (strIDPath == g_strwSysPara)
	{
		oListDataSet.AddTail(m_pSysParas);
	}
	else
	{
		if (Gb_IsGuideBookTemplate(this))
		{
			//m_pGbtDataInterfaces->m_pGbtDatas->SelectDatas(strIDPath, oListDataSet, _T("$"));
		}
		else
		{
			CCpus *pCpus = GetCpusEx(nCpusIndex);
			pCpus->SelectDatas(strIDPath, oListDataSet, _T("$"));

			if (oListDataSet.GetCount() == 0)
			{
				CDataSet *pDataset = pCpus->SelectDatasetByKey(strIDPath);

				if (pDataset != NULL)
				{
					oListDataSet.AddTail(pDataset);
				}
			}

		}
	}

	return oListDataSet.GetCount();
}

long CDevice::SelectDataSetListEx(const CString &strIDPath, CExBaseList &oListDataSet, long nCpusIndex)
{
	CExBaseObject *p = NULL;
	CDataSet *pDataSetHead = NULL;
	CString strDatasetNamePath;

	//ϵͳ����
	if (strIDPath == g_strwSysPara)
	{
		oListDataSet.AddTail(m_pSysParas);
	}
	else
	{
		if (Gb_IsGuideBookTemplate(this))
		{
#ifndef _PSX_QT_LINUX_
            oListDataSet.AddTail(m_pGbtDataInterfaces->m_pGbtDatas);
#endif
        }
		else
		{
			CCpus *pCpus = GetCpusEx(nCpusIndex);
			pCpus->SelectDatas(strIDPath, oListDataSet, _T("$"));

			if (oListDataSet.GetCount() == 0)
			{
				CDataSet *pDataset = pCpus->SelectDatasetByKey(strIDPath);

				if (pDataset != NULL)
				{
					oListDataSet.AddTail(pDataset);
				}
			}
		}
	}

	return oListDataSet.GetCount();
}

//2014-12-14  full path
long CDevice::SelectDataSetEx(const CString &strIDPath, CExBaseList &oListDataSet)
{
	CExBaseObject *p = NULL;
	CDataSet *pDataSetHead = NULL;
	CString strDatasetNamePath;

	//ϵͳ����
	if (strIDPath == g_strwSysPara)
	{
		oListDataSet.AddTail(m_pSysParas);
	}
	else
	{
		if (Gb_IsGuideBookTemplate(this))
		{
#ifndef _PSX_QT_LINUX_
            oListDataSet.AddTail(m_pGbtDataInterfaces->m_pGbtDatas);
#endif
        }
		else
		{
			SelectDatas(strIDPath, oListDataSet, _T("$"));
		}
	}

	return oListDataSet.GetCount();
}

CDataSet* CDevice::SelectDataSet(const CString &strIDPath, long nCpusIndex)
{
	CDataSet *pFind = NULL;
	CExBaseList oList;
	SelectDataSetListEx(strIDPath, oList, nCpusIndex);

	if (oList.GetCount() == 1)
	{
		pFind = (CDataSet *)oList.GetHead();
	}

	oList.RemoveAll();

	return pFind;
}

//2014-12-14  full path
CDataSet* CDevice::SelectDataSetEx(const CString &strIDPath)
{
	CDataSet *pFind = NULL;
	CExBaseList oList;
	SelectDataSetListEx(strIDPath, oList, 0);

	if (oList.GetCount() == 1)
	{
		pFind = (CDataSet *)oList.GetHead();
	}

	oList.RemoveAll();

	return pFind;
}

CExBaseList* CDevice::SelectDataSetList(const CString &strIDPath, long nCpusIndex)
{
	CExBaseList oList;
	SelectDataSetList(strIDPath, oList, nCpusIndex);
	CExBaseList *pDatas = NULL;

	if (oList.GetCount() > 0)
	{
		pDatas = (CExBaseList *)oList.GetHead();
	}

	return pDatas;
}

long CDevice::SelectAllRootItem(CExBaseList &oList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_SAFETY || nClassID == GBCLASSID_MACROTEST
			|| nClassID == GBCLASSID_COMMCMD || nClassID == GBCLASSID_SYSPARAEDIT
			|| nClassID == GBCLASSID_ITEMS)
		{
			oList.AddTail(p);
		}
	}

	return oList.GetCount();
}

CExBaseList* CDevice::CreateItemsDirectories(const CString &strNamePath, const CString &strIDPath)
{
	return CreateItemsDirectories(this, strNamePath, strIDPath);
}

CExBaseList* CDevice::CreateItemsDirectories(CExBaseList *pParent, const CString &strNamePath, const CString &strIDPath)
{
	CString strNameLeft, strNameRight;
	CString strIDLeft, strIDRight;
	GetSplit(strNamePath, strNameLeft, strNameRight);
	GetSplit(strIDPath, strIDLeft, strIDRight);

	if (strNamePath.GetLength() == 0 || strIDPath.GetLength() == 0)
	{
		return pParent;
	}

	CExBaseObject *pFind = pParent->FindByID(strIDLeft);

	if (pFind != NULL)
	{
		if (pFind->GetClassID() != GBCLASSID_ITEMS)
		{
			pFind = NULL;
		}
	}

	if (pFind == NULL)
	{
		pFind = new CItems();
		pParent->AddNewChild(pFind, TRUE);
		pFind->m_strID = strIDLeft;
		pFind->m_strName = strNameLeft;
		return CreateItemsDirectories((CExBaseList*)pFind, strNameRight, strIDRight);
	}
	else
	{
		return CreateItemsDirectories((CExBaseList*)pFind, strNameRight, strIDRight);
	}
}

BOOL CDevice::GetSplit(const CString &strPath, CString &strLeft, CString &strRight)
{
	if (strPath.GetLength() == 0)
	{
		return FALSE;
	}

	long nPos = strPath.Find('$');

	if (nPos > 0)
	{
		strLeft = strPath.Left(nPos);
		strRight = strPath.Mid(nPos+1);
	}
	else
	{
		strLeft = strPath;
		strRight.Empty();
	}

	return TRUE;
}


void CDevice::AddSysPara(const CString &strID, const CString &strValue)
{
	if (m_pSysParas == NULL)
	{
		return;
	}

	CDataObj *pData = (CDataObj*)m_pSysParas->FindByID(strID);

	if (pData == NULL)
	{
		pData = new CDataObj();
		pData->m_strID = strID;
		pData->m_strName = strID;
		m_pSysParas->AddNewChild(pData);
	}

	pData->m_strValue = strValue;
}



BOOL Gb_GetDeviceSysparasTime(CExBaseObject *pGbObj, CExBaseList *pTimeList)
{
	pTimeList->Append(g_pListTimeLong);
	BOOL bRet = FALSE;
	ASSERT(pGbObj != NULL);

	CDevice *pDevice = (CDevice *)pGbObj->GetAncestor(GBCLASSID_DEVICE);

	if (pDevice != NULL && pDevice->GetSysParas()->FindTimeParas(pTimeList))
	{
		bRet = TRUE;
	}

	return bRet;
}

void CDevice::GbxmlToStxml(CExBaseList &listDatas)
{
#ifndef _PSX_QT_LINUX_
    if (m_pGbtDataInterfaces == NULL)
	{
		m_pGbtDataInterfaces = new CGbtDataInterfaces();
		AddNewChild(m_pGbtDataInterfaces);
		BringToHead(m_pGbtDataInterfaces);
	}

	CGbtDatas *pGbtDatas = m_pGbtDataInterfaces->CreateGbtDatas(&listDatas);
	//m_pGbtDataInterfaces->CreateGbtDataInterface();
#endif

	Remove(m_pCpus);
	delete m_pCpus;
	m_pCpus = NULL;
}

BOOL CDevice::IsDeviceHasDvm()
{
	if (m_pCpus == NULL)
	{
		return FALSE;
	}

	return (m_pCpus->GetCount() > 0);
}

CItems* CDevice::FindFirstRootTypeItem()
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CItems *pFind = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			continue;
		}

		CItems *pItems = (CItems *)pObj;

		if (pItems->IsTypeRootNode())
		{
			return pItems;
		}
	}

	return NULL;
}
//2022-9-25  lijunqing ���ʽ����
//CXExprCalInterface
//2023-11-8 �����β� CString &strValRet�����ڷ����ַ�����������硰δ������
BOOL CDevice::ExprCal(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, double &dValRet, CString &strValRet, const CString &strDataType)
{
	if (strType == _T("dataset"))
	{
		return ExprCal_dataset(pExprParent, strType, strExpression, strParentPath, dValRet, strDataType);
	}
	else if (strType == _T("sys-para"))
	{
		return ExprCal_sys_para(pExprParent, strType, strExpression, dValRet, strDataType);
	}
	else if (strType == _T("global-para"))
	{
		return ExprCal_global_para(pExprParent, strType, strExpression, dValRet, strDataType);
	}
	else if (strType == _T("report"))
	{
		return ExprCal_report(pExprParent, strType, strExpression, strParentPath, dValRet, strValRet, strDataType);
	}
	else if (strType == _T("number"))
	{
		//strExpression������ID��������������numberʱ���˴�����ֵ����ȷ
		dValRet = CString_To_double(strExpression);   
		return TRUE;
	}
	else if (strType == _T("script"))
	{
		return ExprCal_script(pExprParent, strType, strExpression, dValRet, strDataType);
	}
	else
	{
		return ExprCal_script(pExprParent, strType, strExpression, dValRet, strDataType);
	}
}

BOOL CDevice::ExprRsltBind(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strDataName, const CString &strParentPath, const CString &strValue)
{
	if (strType == _T("dataset"))
	{
		return ExprRsltBind_dataset(pExprParent, strType, strExpression, strDataName, strParentPath, strValue);
	}
	else if (strType == _T("sys-para"))
	{
		return ExprRsltBind_sys_para(pExprParent, strType, strExpression, strValue);
	}
	else if (strType == _T("global-para"))
	{
		return ExprRsltBind_global_para(pExprParent, strType, strExpression, strValue);
	}
	else if (strType == _T("report"))
	{
		return ExprRsltBind_report(pExprParent, strType, strExpression, strDataName, strParentPath, strValue);
	}
	else if (strType == _T("number"))
	{
		return TRUE;
	}
	else if (strType == _T("script"))
	{
		return ExprRsltBind_script(pExprParent, strType, strExpression, strValue);
	}
	else
	{
		return ExprRsltBind_script(pExprParent, strType, strExpression, strValue);
	}
}

//strExpressionΪ���ݼ�����·��
BOOL CDevice::ExprCal_dataset(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, double &dValRet, const CString &strDataType)
{
	//���ȴӱ����л�ȡ���������в�����ʱ���ٴ�ģ���л�ȡ 2024-12-17
	CGbItemBase *pItem = (CGbItemBase*)pExprParent;  //���ʽ�ĸ�����
	CReport *pReport = NULL;

	CGbItemBaseList oDestList;
	//ͨ����Ŀ���·����������Ŀ
	pItem->SelectItems(strParentPath, oDestList);
	long nCount = oDestList.GetCount();

	if (nCount != 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("��Ŀ��%s�����ҽ����Ψһ���ҵ���%d����Ŀ����Ŀ"), strParentPath.GetString(), nCount);
		oDestList.RemoveAll();
		return FALSE;
	}

	CGbItemBase *pDestItem = (CGbItemBase *)oDestList.GetHead();
	pReport = pDestItem->GetReport(-1);
	oDestList.RemoveAll();

	if (pReport == NULL)
	{
		return FALSE;
	}

	if (strDataType == _T("utc_time"))
	{
		//����UTC_TIMEʱ�����⴦��
		return ExprCal_dataset_UTCTIME(strExpression, pReport->m_pRptDvmDataset, dValRet);
	}
	else if(strDataType == _T("din_account_all") || strDataType == _T("din_account_1") || strDataType == _T("din_account_0"))
	{
		//����ң�ű�λ����ʱ�����⴦��
		return ExprCal_dataset_Account(strExpression, strDataType, pReport->m_pRptDvmDataset, dValRet);
	}
	else if (strDataType == _T("sys_time"))
	{
		//���ڲ�ң����������ʱ�����⴦��
		return ExprCal_dataset_SysTime(strExpression, pReport->m_pRptDvmDataset, dValRet);
	}
	else if (strDataType == _T("$t"))
	{
		//���ڲ�ң�Ŷ�ʱ����ʱ�����⴦��
		return ExprCal_dataset_$t(strExpression, pReport->m_pRptDvmDataset, dValRet);
	}

	CDvmData *pFind = (CDvmData*)pReport->m_pRptDvmDataset->FindByID(strExpression);

	if (pFind != NULL)
	{
		if (strExpression.Find(_T("$")) >= 0)
		{
			//������·������Ҫ��Ƕ�׵�CDvmValue����ȡ
			CDvmValue *pValue = (CDvmValue *)pReport->m_pRptDvmDataset->SelectData(strExpression);

			if (pValue != NULL)
			{
				dValRet = CString_To_double(pValue->m_strValue);
				return TRUE;
			}
		}

		dValRet = CString_To_double(pFind->m_strValue);
		return ExprCal_dataset_Ain(strExpression, dValRet);
	}

	if (strParentPath.IsEmpty() && strDataType != _T("utc_time")//UTC_TIME��ֱ�Ӵӱ�����ȡֵ
		&& strDataType != _T("din_account_all") && strDataType != _T("din_account_1") && strDataType != _T("din_account_0")//ң�ű�λ���ļ����ģ����⴦��
		&& strDataType != _T("sys_time")//ϵͳʱ�䣬��ʾ��ң���������ͣ����⴦��
		&& strDataType != _T("$t")) //$t����ʾ��ң��ʱ�䣬��Ҫת���ɺ���ֵ�����ڶ�ʱ����
	{
		//���·��Ϊ�յģ�ֱ�Ӵ�ģ���л�ȡ������ӱ����е�datasetȡ*
		CDataObj *pFind = m_pCpus->SelectDataObj(strExpression);

		if (pFind != NULL)
		{
			double dValue = CString_To_double(pFind->m_strValue);

			if (m_nIsTimeSetsUnit_ms == 1)
			{
				//ʱ�䶨ֵ�ĵ�λ��ms
				//������λ���������ǽ��յ��Ķ���ʱ������sΪ��λ����˴˴���Ҫ���¼���ֵ��ֵת��Ϊs
				if (pFind->m_dStepVal == 10.0) 
				{
					//JinJian˵������Ϊ10�ģ���λ����ms��ʱ�䶨ֵ
					dValue = dValue/1000;
				}
			}

			dValRet = dValue/*CString_To_double(pFind->m_strValue)*/;
			return ExprCal_dataset_Ain(strExpression, dValRet);
		}
	}

	return FALSE;
}

BOOL CDevice::ExprCal_sys_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, double &dValRet, const CString &strDataType)
{
	CDataObj *pFind = (CDataObj*)m_pSysParas->FindByID(strExpression);

	if (pFind != NULL)
	{
		dValRet = CString_To_double(pFind->m_strValue);
	}

	return pFind != NULL;
}

#include "GuideBook.h"

BOOL CDevice::ExprCal_global_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, double &dValRet, const CString &strDataType)
{
	CGuideBook *pGuideBook = (CGuideBook*)GetParent();
	CDvmData *pFind = (CDvmData*)pGuideBook->m_pGlobalDatas->FindByID(strExpression);

	if (pFind != NULL)
	{
		dValRet = CString_To_double(pFind->m_strValue);
	}

	return pFind != NULL;
}

//2023-11-8 �����β� CString &strValRet�����ڷ����ַ�����������硰δ������
BOOL CDevice::ExprCal_report(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, double &dValRet, CString &strValRet, const CString &strDataType)
{
	CGbItemBase *pItem = (CGbItemBase*)pExprParent;  //���ʽ�ĸ�����
	CReport *pReport = NULL;

	if (strParentPath.IsEmpty())
	{
		pReport = pItem->GetReport(-1);
	}
	else 
	{
		CGbItemBaseList oDestList;
		//ͨ����Ŀ���·����������Ŀ
		pItem->SelectItems(strParentPath, oDestList);
		long nCount = oDestList.GetCount();

		if (nCount != 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("��Ŀ��%s�����ҽ����Ψһ���ҵ���%d����Ŀ����Ŀ"), strParentPath.GetString(), nCount);
			oDestList.RemoveAll();
			return FALSE;
		}

		CGbItemBase *pDestItem = (CGbItemBase *)oDestList.GetHead();
		pReport = pDestItem->GetReport(-1);
		oDestList.RemoveAll();
	}

	if (pReport == NULL)
	{
		return FALSE;
	}

	CValue *pFind = (CValue*)pReport->m_pValues->FindByID(strExpression);

	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pFind->m_strValue == _T("δ����"))
	{
		strValRet = pFind->m_strValue;
		dValRet = 0.0;  //�÷���ֵ�����жϿɿ������������������������㣬�ʴ˴������ַ�������ֵ
		return TRUE;
	}

	if (pFind->m_strValue == _T("����"))
	{
		dValRet = 1.0;
	}
	else
	{
		dValRet = CString_To_double(pFind->m_strValue);
	}

	return TRUE;
}

BOOL CDevice::ExprCal_script(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, double &dValRet, const CString &strDataType)
{
	return Gb_CalParaExpression(strExpression, this, dValRet, FALSE);
}

/*
<group id="AinRatios" name="���������Ϣ">
	<data name="װ�ò���" id="DevMeas" value="1" data-type=""/>��װ�ò�����һ��ֵ�����Ƕ���ֵ��ȡֵ��1|2��
	<data name="PTһ�β�" id="PtPrimary" value="220" data-type=""/>��PTһ�β൥λΪkV��
	<data name="Pt���β�" id="PtSecondary" value="100" data-type=""/>��PT���β൥λΪV��
	<data name="Ctһ�β�" id="CtPrimary" value="" data-type=""/>
	<data name="Ct���β�" id="CtSecondary" value="" data-type=""/>��CTһ�Ρ����β൥λ��ΪA��
</group>
*/
//�β�dValRet������ʱ���Ѿ������ݼ����ҵ��˶�Ӧ��ֵ�ˣ��˴�������������¸�ֵ��dValRet����
BOOL CDevice::ExprCal_dataset_Ain(const CString &strExpression, double &dValRet)
{
	CGuideBook *pGuideBook = (CGuideBook *)GetParent();
	CDataGroup *pAinRatios = pGuideBook->GetAinRatios();
	CDataGroup *pAinDataMapCfg = pGuideBook->GetAinDataMapCfg();

	if (pAinDataMapCfg == NULL)
	{
		//˵������ң����������������⴦��
		return TRUE;
	}

	CDvmData *pMap = pAinDataMapCfg->FindDataByValue(strExpression);  //ӳ������

	if (pMap == NULL)
	{
		//˵������ң����������������⴦��
		return TRUE;
	}

	if (pAinRatios == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���װ�ò�����Ϣ���á���"));
		return FALSE;
	}

	CDvmData *pDevMeas = (CDvmData *)pAinRatios->FindByID(ID_PARA_DevMeas);

	if (pDevMeas == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���װ�ò���������һ��ֵ���Ƕ���ֵ�����á���"));
		return FALSE;
	}

	if (pDevMeas->m_strValue == "2")
	{
		//����ֵ�����ø��ݱ�Ȼ���
		return TRUE;
	}

	//ң�����ӳ��ʱ�����ǹ̶�IDӳ��
	if (pMap->m_strID == _T("MIa")
		|| pMap->m_strID == _T("MIb")
		|| pMap->m_strID == _T("MIc"))
	{
		return ExprCal_dataset_Ain_I(pAinRatios, dValRet);
	}
	else if (pMap->m_strID == _T("MUa")
			|| pMap->m_strID == _T("MUb")
			|| pMap->m_strID == _T("MUc"))
	{
		return ExprCal_dataset_Ain_U(pAinRatios, dValRet);
	}
	else if (pMap->m_strID == _T("P")
		|| pMap->m_strID == _T("Q"))
	{
		return ExprCal_dataset_Ain_PQ(pAinRatios, dValRet);
	}
	else
	{
		//ʣ��Ĺ������غ�Ƶ�ʣ����û���
		return TRUE;
	}
}

BOOL CDevice::ExprCal_dataset_Ain_I(CDataGroup *pAinRatios, double &dValRet)
{
	CDvmData *pCtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���CT���һ��ֵ����"));
		return FALSE;
	}

	CDvmData *pCtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���CT��ȶ���ֵ����"));
		return FALSE;
	}

	double dPrimary = CString_To_double(pCtPrimary->m_strValue);
	double dSecondary = CString_To_double(pCtSecondary->m_strValue);
	double dRatio = dPrimary / dSecondary;

	dValRet = dValRet / dRatio;
	return TRUE;
}

BOOL CDevice::ExprCal_dataset_Ain_U(CDataGroup *pAinRatios, double &dValRet)
{
	CDvmData *pPtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtPrimary);

	if (pPtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���PT���һ��ֵ����"));
		return FALSE;
	}

	CDvmData *pPtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���PT��ȶ���ֵ����"));
		return FALSE;
	}

	double dPrimary = CString_To_double(pPtPrimary->m_strValue);
	double dSecondary = CString_To_double(pPtSecondary->m_strValue);
	//PT����� kV / V��
	double dRatio = dPrimary * 1000 / dSecondary;  

	//װ�ò���һ��ֵʱ����ѹ��λΪkV
	dValRet = dValRet * 1000 / dRatio;
	return TRUE;
}

BOOL CDevice::ExprCal_dataset_Ain_PQ(CDataGroup *pAinRatios, double &dValRet)
{
	CDvmData *pCtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���CT���һ��ֵ����"));
		return FALSE;
	}

	CDvmData *pCtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���CT��ȶ���ֵ����"));
		return FALSE;
	}

	CDvmData *pPtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtPrimary);

	if (pPtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���PT���һ��ֵ����"));
		return FALSE;
	}

	CDvmData *pPtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���PT��ȶ���ֵ����"));
		return FALSE;
	}

	double dCtPrimary = CString_To_double(pCtPrimary->m_strValue);
	double dCtSecondary = CString_To_double(pCtSecondary->m_strValue);
	double dPtPrimary = CString_To_double(pPtPrimary->m_strValue);
	double dPtSecondary = CString_To_double(pPtSecondary->m_strValue);
	//PT����� kV / V��
	double dRatio = (dCtPrimary / dCtSecondary) * (dPtPrimary * 1000 / dPtSecondary);  

	//װ�ò���һ��ֵʱ����ѹ��λΪkV�����ʵĵ�λ��MW��MVAr
	dValRet = dValRet * 1000000 / dRatio;
	return TRUE;
}

BOOL CDevice::ExprCal_dataset_UTCTIME(const CString &strExpression, CExBaseList *pDataset, double &dValRet)
{
	//TODO������ж���ң�ţ�Ȼ����Ҫ��ң��ֵ=1ȥ����m_pRptDvmDataset->m_strID==report��
	CDvmData *pFind = NULL;
	if (pDataset->m_strID.Find(_T("report")) >=0 || pDataset->m_strID.Find(_T("soe")) >=0)
	{
		//��ʱ��Ϊ������ң��SOE���ԣ����ж�ң��ֵΪ1��
		POS pos = pDataset->GetTailPosition();  //�Ӻ���ǰ�������µ�һ��

		while (pos != NULL)
		{
			CDvmData *pData = (CDvmData *)pDataset->GetPrev(pos);

			if (pData->m_strID == strExpression && pData->m_strValue == _T("1"))
			{
				pFind = pData;
				break;
			}
		}
	}
	else
	{
		pFind = (CDvmData*)pDataset->FindByID(strExpression);
	}

	if (pFind == NULL)
	{
		return FALSE;
	}

	SYSTEMTIME oTm;
	CDvmValue *pT = (CDvmValue *)pFind->FindByID(_T("$t"));//$tΪң��ʱ��
	ASSERT(pT != NULL);

	if (pT == NULL)
	{
		return FALSE;
	}

	CString_To_SystemTime(pT->m_strValue, oTm);

	//��ȡ�ܵ�ms���˴���Ϊ���ж�ʱ�������ʱ����������
// 	dValRet = oTm.wDay * 24;
// 	dValRet = (dValRet + oTm.wHour) * 60;
// 	dValRet = (dValRet + oTm.wMinute) * 60;
// 	dValRet += oTm.wSecond;
// 	dValRet = dValRet * 1000 + oTm.wMilliseconds;
	unsigned long long nTm = 0;
	TransTimer_To_LongTime_ms(nTm, oTm.wYear, oTm.wMonth, oTm.wDay, oTm.wHour, oTm.wMinute, oTm.wSecond, oTm.wMilliseconds);
	dValRet = nTm;

	return TRUE;
}

BOOL CDevice::ExprCal_dataset_Account(const CString &strExpression, const CString &strAcountID, CExBaseList *pDataset, double &dValRet)
{
	CDvmData *pFind = (CDvmData*)pDataset->FindByID(strExpression);

	if (pFind == NULL)
	{
		return FALSE;
	}

	CString strID;
	
	if (strAcountID == _T("din_account_all"))
	{
		strID = _T("$st_all");
	}
	else if (strAcountID == _T("din_account_1"))
	{
		strID = _T("$st_1");
	}
	else if (strAcountID == _T("din_account_0"))
	{
		strID = _T("$st_0");
	}
	else
	{
		return FALSE;
	}

	CDvmValue *pAccount = (CDvmValue *)pFind->FindByID(strID);//$tΪң��ʱ��
	ASSERT(pAccount != NULL);

	if (pAccount == NULL)
	{
		return FALSE;
	}

	dValRet = CString_To_double(pAccount->m_strValue);

	return TRUE;
}

//ң���������ͣ�$systime����ppxml�н��յ�ң��ʱ��������ֵ��
BOOL CDevice::ExprCal_dataset_SysTime(const CString &strExpression, CExBaseList *pDataset, double &dValRet)
{
	CDvmData *pFind = NULL;
	if (pDataset->m_strID.Find(_T("report")) >=0 || pDataset->m_strID.Find(_T("soe")) >=0)
	{
		//ң���������ͣ��õ���SOE���ݼ������ǰ�����ң���һ��ֵΪ1��ң�ţ�
		POS pos = pDataset->GetHeadPosition();  //��ǰ���������ȵ�һ��

		while (pos != NULL)
		{
			CDvmData *pData = (CDvmData *)pDataset->GetNext(pos);

			if (pData->m_strID == strExpression && pData->m_strValue != _T("0"))
			{
				//ң�����������ǣ�Ia��ң�ŵ�ֵ���ǲ���ֵ������0 �� 1
				pFind = pData;
				break;
			}
		}
	}
	else
	{
		pFind = (CDvmData*)pDataset->FindByID(strExpression);
	}

	if (pFind == NULL)
	{
		return FALSE;
	}

	SYSTEMTIME oTm;
	CDvmValue *pT = (CDvmValue *)pFind->FindByID(_T("$systime"));//$systimeΪppxml��¼��ʱ��
	ASSERT(pT != NULL);

	if (pT == NULL)
	{
		return FALSE;
	}

	CString_To_SystemTime(pT->m_strValue, oTm);

	//��ȡ�ܵ�ms���˴���Ϊ���ж�ʱ�������ʱ����������
	// 	dValRet = oTm.wDay * 24;
	// 	dValRet = (dValRet + oTm.wHour) * 60;
	// 	dValRet = (dValRet + oTm.wMinute) * 60;
	// 	dValRet += oTm.wSecond;
	// 	dValRet = dValRet * 1000 + oTm.wMilliseconds;
	unsigned long long nTm = 0;
	TransTimer_To_LongTime_ms(nTm, oTm.wYear, oTm.wMonth, oTm.wDay, oTm.wHour, oTm.wMinute, oTm.wSecond, oTm.wMilliseconds);
	dValRet = nTm;

	return TRUE;
}

BOOL CDevice::ExprCal_dataset_$t(const CString &strExpression, CExBaseList *pDataset, double &dValRet)
{
	//��ʱ���ܣ�Ŀǰ������������ʱ��ͬ����Ȼ��ң�ؿ��غϣ��յ���Ӧң��(���磺Din_43)valueΪ1ʱ��$systime��$t���5s��
	CDvmData *pFind = NULL;
	if (pDataset->m_strID.Find(_T("report")) >=0 || pDataset->m_strID.Find(_T("soe")) >=0)
	{
		//ң�Ŷ�ʱ���ԣ��õ���SOE���ݼ������ǰ�����ң���һ��ֵΪ1��ң�ţ�
		POS pos = pDataset->GetHeadPosition();  //��ǰ���������ȵ�һ��

		while (pos != NULL)
		{
			CDvmData *pData = (CDvmData *)pDataset->GetNext(pos);

			if (pData->m_strID == strExpression && pData->m_strValue == _T("1"))
			{
				pFind = pData;
				break;
			}
		}
	}
	else
	{
		pFind = (CDvmData*)pDataset->FindByID(strExpression);
	}

	if (pFind == NULL)
	{
		return FALSE;
	}

	SYSTEMTIME oTm;
	CDvmValue *pT = (CDvmValue *)pFind->FindByID(_T("$t"));//$tΪң��ʱ��
	ASSERT(pT != NULL);

	if (pT == NULL)
	{
		return FALSE;
	}

	CString_To_SystemTime(pT->m_strValue, oTm);

	//��ȡ�ܵ�ms���˴���Ϊ���ж�ʱ�������ʱ����������
	// 	dValRet = oTm.wDay * 24;
	// 	dValRet = (dValRet + oTm.wHour) * 60;
	// 	dValRet = (dValRet + oTm.wMinute) * 60;
	// 	dValRet += oTm.wSecond;
	// 	dValRet = dValRet * 1000 + oTm.wMilliseconds;
	unsigned long long nTm = 0;
	TransTimer_To_LongTime_ms(nTm, oTm.wYear, oTm.wMonth, oTm.wDay, oTm.wHour, oTm.wMinute, oTm.wSecond, oTm.wMilliseconds);
	dValRet = nTm;

	return TRUE;
}

BOOL CDevice::ExprRsltBind_dataset(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strDataName, const CString &strParentPath, const CString &strValue)
{
	if (strParentPath.IsEmpty())
	{
		//��Ŀ���·����Ϊ��ʱ���󶨵�ģ�͡�����󶨵������Ŀ�����ݼ�����
		CDataObj *pFind = m_pCpus->SelectDataObj(strExpression);

		if (pFind == NULL)
		{
			return FALSE;
		}

		pFind->m_strValue = strValue;
		return TRUE;
	}
	
	CGbItemBase *pItem = (CGbItemBase*)pExprParent;  //���ʽ�ĸ�����
	CReport *pReport = NULL;
	CGbItemBaseList oDestList;
	//ͨ����Ŀ���·����������Ŀ
	pItem->SelectItems(strParentPath, oDestList);
	long nCount = oDestList.GetCount();

	if (nCount != 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("��Ŀ��%s�����ҽ����Ψһ���ҵ���%d����Ŀ����Ŀ"), strParentPath.GetString(), nCount);
		oDestList.RemoveAll();
		return FALSE;
	}

	CGbItemBase *pDestItem = (CGbItemBase *)oDestList.GetHead();
	pReport = pDestItem->GetReport(-1);

	if (pReport == NULL)
	{
		oDestList.RemoveAll();
		return FALSE;
	}

	CDvmData *pFind = (CDvmData*)pReport->m_pRptDvmDataset->FindByID(strExpression);

	//�Ҳ�����������������½�һ��CDvmData����Ҫ��name������
	if (pFind == NULL)
	{
		pFind = new CDvmData();
		pReport->m_pRptDvmDataset->AddNewChild(pFind);
		pReport->m_pRptDvmDataset->BringToHead(pFind);
		pFind->m_strID = strExpression;
		pFind->m_strName = strDataName;
	}

	pFind->m_strValue = strValue;

	oDestList.RemoveAll();
	return TRUE;
}

BOOL CDevice::ExprRsltBind_sys_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strValue)
{
	CDataObj *pFind = (CDataObj*)m_pSysParas->FindByID(strExpression);

	if (pFind == NULL)
	{
		return FALSE;
	}

	pFind->m_strValue = strValue;
	return TRUE;
}

BOOL CDevice::ExprRsltBind_global_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strValue)
{
	CGuideBook *pGuideBook = (CGuideBook*)GetParent();
	CDvmData *pFind = (CDvmData*)pGuideBook->m_pGlobalDatas->FindByID(strExpression);

	if (pFind != NULL)
	{
		return FALSE;
	}

	pFind->m_strValue = strValue;
	return TRUE;
}

BOOL CDevice::ExprRsltBind_report(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strDataName, const CString &strParentPath, const CString &strValue)
{
	CGbItemBase *pItem = (CGbItemBase*)pExprParent;  //���ʽ�ĸ�����

	CReport *pReport = NULL;

	if (strParentPath.IsEmpty())
	{
		pReport = pItem->GetReport(-1);
	}
	else 
	{
		CGbItemBaseList oDestList;
		//ͨ����Ŀ���·����������Ŀ
		pItem->SelectItems(strParentPath, oDestList);
		long nCount = oDestList.GetCount();

		if (nCount != 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("��Ŀ��%s�����ҽ����Ψһ���ҵ���%d����Ŀ����Ŀ"), strParentPath.GetString(), nCount);
			oDestList.RemoveAll();
			return FALSE;
		}

		CGbItemBase *pDestItem = (CGbItemBase *)oDestList.GetHead();
		pReport = pDestItem->GetReport(-1);
		oDestList.RemoveAll();
	}

	if (pReport == NULL)
	{
		return FALSE;
	}

	CValue *pFind = (CValue*)pReport->m_pValues->FindByID(strExpression);

	//�Ҳ�����������������½�һ��CValue����Ҫ��name������
	//����ID��Я��$���Ĳ���������ȡ$�����һ�Σ��򵥽��д������磺״̬���н��������rslt_evaluation$rslt_evaluation1$Ttrip_AbsErr
	if (pFind == NULL)
	{
		pFind = new CValue();
		pReport->m_pValues->AddNewChild(pFind);
		pReport->m_pValues->BringToHead(pFind);

		//����ΪɶҪ��ô���ˣ�ע�͵���2023-8-31
// 		CString strID = strExpression;
// 		long nPos = strID.Find(_T("$"));
// 
// 		if (nPos >= 0)
// 		{
// 			strID = strID.Mid(nPos + 1);
// 		}
// 
 		pFind->m_strID = strExpression;
		pFind->m_strName = strDataName;
		/*return FALSE;*/
	}

	pFind->m_strValue = strValue;

	return TRUE;
}

BOOL CDevice::ExprRsltBind_script(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strValue)
{
	return FALSE;
}

void CDevice::ExprCal_GetReportsForCal(CExBaseList* pListReportsForCal, long nCurrTestTimes, long nRepeatTimes, CExBaseObject* pExprParent)
{
	CGbItemBase *pItemBase = (CGbItemBase *)pExprParent;
	CReports *pReports = pItemBase->GetReports();
	long nIndex = 0;

	POS pos = pReports->GetTailPosition();

	while (pos != NULL)
	{
		CReport *pReport = (CReport *)pReports->GetPrev(pos);

		//��nCurrTestTimes > nRepeatTimesʱ����ʾ���һ�ݱ����Ǽ��㱨��
		if (nRepeatTimes < nCurrTestTimes && pReport->IsCalReport())
		{
			continue;
		}

		pListReportsForCal->AddTail(pReport);

		nIndex++;

		if (nIndex >= nCurrTestTimes)
		{
			break;
		}
	}
}

BOOL CDevice::ExprCal_Min(CExBaseList* pListReportsForCal, const CString &strExpression, double &dValRet)
{
	BOOL bRet = TRUE;
	long nIndex = 0;
	double dMin = 0;
	double dMinAbs = 0;
	CValue *pFind = NULL;
	double dFind = 0.0;
	POS pos = pListReportsForCal->GetHeadPosition();
	BOOL bFind = FALSE;  //�Ƿ���ҵ�һ����Ч�������

	while (pos != NULL)
	{
		CReport *pRpt = (CReport *)pListReportsForCal->GetNext(pos);
		pFind = pRpt->FindReportData(strExpression);

		if (pFind != NULL)
		{
			if (pFind->m_strValue == _T("--") || pFind->m_strValue == _T("δ����"))
			{
				continue;
			}

			bFind = TRUE;

			if (nIndex == 0)
			{
				dMin = CString_To_double(pFind->m_strValue.GetString());
				dMinAbs = fabs(dMin);
			}
			else
			{
				dFind = CString_To_double(pFind->m_strValue.GetString());

				if (fabs(dFind) < dMinAbs)
				{
					dMin = dFind;
					dMinAbs = fabs(dMin);
				}
			}

			nIndex++;
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�Ҳ����������ݡ�%s��"), strExpression.GetString());
			bRet = FALSE;
		}
	}

	if (bFind == FALSE)
	{
		//��û�ҵ�һ����Ч�������
		bRet = FALSE;
	}

	dValRet = dMin;
	return bRet;
}

BOOL CDevice::ExprCal_Max(CExBaseList* pListReportsForCal, const CString &strExpression, double &dValRet)
{
	BOOL bRet = TRUE;
	long nIndex = 0;
	double dMax = 0;
	double dMaxAbs = 0;
	CValue *pFind = NULL;
	double dFind = 0.0;
	BOOL bFind = FALSE;  //�Ƿ���ҵ�һ����Ч�������
	POS pos = pListReportsForCal->GetHeadPosition();

	while (pos != NULL)
	{
		CReport *pRpt = (CReport *)pListReportsForCal->GetNext(pos);
		pFind = pRpt->FindReportData(strExpression);

		if (pFind != NULL)
		{
			if (pFind->m_strValue == _T("--") || pFind->m_strValue == _T("δ����"))
			{
				continue;
			}

			bFind = TRUE;

			if (nIndex == 0)
			{
				dMax = CString_To_double(pFind->m_strValue.GetString());
				dMaxAbs = fabs(dMax);
			}
			else
			{
				dFind = CString_To_double(pFind->m_strValue.GetString());

				if (fabs(dFind) > dMaxAbs)
				{
					dMax = dFind;
					dMaxAbs = fabs(dMax);
				}
			}

			nIndex++;
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�Ҳ����������ݡ�%s��"), strExpression.GetString());
			bRet = FALSE;
		}
	}

	if (bFind == FALSE)
	{
		//��û�ҵ�һ����Ч�������
		bRet = FALSE;
	}

	dValRet = dMax;
	return bRet;
}

BOOL CDevice::ExprCal_SRpt(CExBaseObject *pExprParent, const CString &strSrcIDHas, const CString &strCalMode, double &dValRet)
{
	CGbItemBase *pItemBase = (CGbItemBase *)pExprParent;
	CReport *pRpt = pItemBase->GetReport(-1);

	if (pRpt == NULL)
	{
		return FALSE;
	}

	if (pRpt->m_pValues == NULL)
	{
		return FALSE;
	}

	CExBaseList oListValuesForCal;
	POS pos = pRpt->m_pValues->GetHeadPosition();

	while (pos != NULL)
	{
		CValue *pValue = (CValue *)pRpt->m_pValues->GetNext(pos);

		if (pValue->m_strID.Find(strSrcIDHas) >= 0)
		{
			oListValuesForCal.AddTail(pValue);
		}
	}

	if (oListValuesForCal.GetCount() == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("do not find report values need to cal [%s]"), strSrcIDHas.GetString());
		return FALSE;
	}

	double dCal = 0.0;
	double dFind = 0.0;
	long nIndex = 0;

	if (strCalMode == _T("max"))
	{
		pos = oListValuesForCal.GetHeadPosition();

		while (pos != NULL)
		{
			CValue *pValue = (CValue *)oListValuesForCal.GetNext(pos);
			dFind = CString_To_double(pValue->m_strValue);

			if (nIndex == 0)
			{
				dCal = dFind;
			}
			else
			{
				if (dFind > dCal)
				{
					dCal = dFind;
				}
			}

			nIndex++;
		}
	}
	else if (strCalMode == _T("min"))
	{
		pos = oListValuesForCal.GetHeadPosition();

		while (pos != NULL)
		{
			CValue *pValue = (CValue *)oListValuesForCal.GetNext(pos);
			dFind = CString_To_double(pValue->m_strValue);

			if (nIndex == 0)
			{
				dCal = dFind;
			}
			else
			{
				if (dFind < dCal)
				{
					dCal = dFind;
				}
			}

			nIndex++;
		}
	}
	else if (strCalMode == _T("avg"))
	{
		pos = oListValuesForCal.GetHeadPosition();
		double dCount = 0.0;

		while (pos != NULL)
		{
			CValue *pValue = (CValue *)oListValuesForCal.GetNext(pos);
			dFind = CString_To_double(pValue->m_strValue);
			dCount += dFind;
		}

		dCal = dCount / oListValuesForCal.GetCount();
	}

	oListValuesForCal.RemoveAll();
	dValRet = dCal;

	return TRUE;
}
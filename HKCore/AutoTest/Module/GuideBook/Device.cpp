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
		m_pSysParas->m_strName =g_sLangTxt_TestPara/* L"测试参数"*/;
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
		m_pSysParas->m_strName = g_sLangTxt_TestPara/*L"测试参数"*/;
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
			m_pSysParas->m_strName =g_sLangTxt_TestPara/* L"测试参数"*/;
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

//2024-2-21 仅更新测试参数的value属性
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
			m_pSysParas->m_strName =g_sLangTxt_TestPara/* L"测试参数"*/;
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
	
	//初始化住CPU
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

	//2020-1-1  lijunqing   多设备数据模型的处理
	long nDvIndex = Gb_GetDvmIndexFromPath(strPath);

	if (nDvIndex > 0)
	{
		nDeviceModelIndex = nDvIndex;
	}

	//2020-1-1  lijunqing  多设备数据模型的处理  后面的代码不变
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
		if (DS_InStringDataPath(strPath))  //此处要求strPath中没有中文 才返回TRUE  shaolei
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

	//系统参数
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

	//系统参数
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

	//系统参数
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
//2022-9-25  lijunqing 表达式计算
//CXExprCalInterface
//2023-11-8 新增形参 CString &strValRet。用于返回字符串结果，例如“未动作”
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
		//strExpression是数据ID，当数据类型是number时，此处返回值不正确
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

//strExpression为数据集数据路径
BOOL CDevice::ExprCal_dataset(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, double &dValRet, const CString &strDataType)
{
	//优先从报告中获取，当报告中不存在时，再从模型中获取 2024-12-17
	CGbItemBase *pItem = (CGbItemBase*)pExprParent;  //表达式的父对象
	CReport *pReport = NULL;

	CGbItemBaseList oDestList;
	//通过项目相对路径，查找项目
	pItem->SelectItems(strParentPath, oDestList);
	long nCount = oDestList.GetCount();

	if (nCount != 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("项目【%s】查找结果不唯一！找到【%d】个目标项目"), strParentPath.GetString(), nCount);
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
		//仅在UTC_TIME时，特殊处理
		return ExprCal_dataset_UTCTIME(strExpression, pReport->m_pRptDvmDataset, dValRet);
	}
	else if(strDataType == _T("din_account_all") || strDataType == _T("din_account_1") || strDataType == _T("din_account_0"))
	{
		//仅在遥信变位计数时，特殊处理
		return ExprCal_dataset_Account(strExpression, strDataType, pReport->m_pRptDvmDataset, dValRet);
	}
	else if (strDataType == _T("sys_time"))
	{
		//仅在测遥信优先上送时，特殊处理
		return ExprCal_dataset_SysTime(strExpression, pReport->m_pRptDvmDataset, dValRet);
	}
	else if (strDataType == _T("$t"))
	{
		//仅在测遥信对时功能时，特殊处理
		return ExprCal_dataset_$t(strExpression, pReport->m_pRptDvmDataset, dValRet);
	}

	CDvmData *pFind = (CDvmData*)pReport->m_pRptDvmDataset->FindByID(strExpression);

	if (pFind != NULL)
	{
		if (strExpression.Find(_T("$")) >= 0)
		{
			//可能是路径，需要从嵌套的CDvmValue里面取
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

	if (strParentPath.IsEmpty() && strDataType != _T("utc_time")//UTC_TIME。直接从报告里取值
		&& strDataType != _T("din_account_all") && strDataType != _T("din_account_1") && strDataType != _T("din_account_0")//遥信变位报文计数的，特殊处理
		&& strDataType != _T("sys_time")//系统时间，表示做遥信优先上送，额外处理
		&& strDataType != _T("$t")) //$t，表示是遥信时间，需要转换成毫秒值，用于对时测试
	{
		//相对路径为空的，直接从模型中获取，否则从报告中的dataset取*
		CDataObj *pFind = m_pCpus->SelectDataObj(strExpression);

		if (pFind != NULL)
		{
			double dValue = CString_To_double(pFind->m_strValue);

			if (m_nIsTimeSetsUnit_ms == 1)
			{
				//时间定值的单位是ms
				//由于上位机，测试仪接收到的动作时间是以s为单位，因此此处需要将事件定值的值转换为s
				if (pFind->m_dStepVal == 10.0) 
				{
					//JinJian说，步长为10的，单位就是ms的时间定值
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

//2023-11-8 新增形参 CString &strValRet。用于返回字符串结果，例如“未动作”
BOOL CDevice::ExprCal_report(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, double &dValRet, CString &strValRet, const CString &strDataType)
{
	CGbItemBase *pItem = (CGbItemBase*)pExprParent;  //表达式的父对象
	CReport *pReport = NULL;

	if (strParentPath.IsEmpty())
	{
		pReport = pItem->GetReport(-1);
	}
	else 
	{
		CGbItemBaseList oDestList;
		//通过项目相对路径，查找项目
		pItem->SelectItems(strParentPath, oDestList);
		long nCount = oDestList.GetCount();

		if (nCount != 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("项目【%s】查找结果不唯一！找到【%d】个目标项目"), strParentPath.GetString(), nCount);
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

	if (pFind->m_strValue == _T("未动作"))
	{
		strValRet = pFind->m_strValue;
		dValRet = 0.0;  //该返回值用于判断可靠不动作。但不能用于误差计算，故此处增加字符串返回值
		return TRUE;
	}

	if (pFind->m_strValue == _T("动作"))
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
<group id="AinRatios" name="采样变比信息">
	<data name="装置采样" id="DevMeas" value="1" data-type=""/>【装置采样是一次值、还是二次值。取值：1|2】
	<data name="PT一次侧" id="PtPrimary" value="220" data-type=""/>【PT一次侧单位为kV】
	<data name="Pt二次侧" id="PtSecondary" value="100" data-type=""/>【PT二次侧单位为V】
	<data name="Ct一次侧" id="CtPrimary" value="" data-type=""/>
	<data name="Ct二次侧" id="CtSecondary" value="" data-type=""/>【CT一次、二次侧单位均为A】
</group>
*/
//形参dValRet。传入时，已经从数据集查找到了对应的值了，此处经过换算后，重新赋值给dValRet返回
BOOL CDevice::ExprCal_dataset_Ain(const CString &strExpression, double &dValRet)
{
	CGuideBook *pGuideBook = (CGuideBook *)GetParent();
	CDataGroup *pAinRatios = pGuideBook->GetAinRatios();
	CDataGroup *pAinDataMapCfg = pGuideBook->GetAinDataMapCfg();

	if (pAinDataMapCfg == NULL)
	{
		//说明不是遥测参数，不用作额外处理
		return TRUE;
	}

	CDvmData *pMap = pAinDataMapCfg->FindDataByValue(strExpression);  //映射数据

	if (pMap == NULL)
	{
		//说明不是遥测参数，不用作额外处理
		return TRUE;
	}

	if (pAinRatios == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到装置采样信息配置……"));
		return FALSE;
	}

	CDvmData *pDevMeas = (CDvmData *)pAinRatios->FindByID(ID_PARA_DevMeas);

	if (pDevMeas == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到装置采样数据是一次值还是二次值的配置……"));
		return FALSE;
	}

	if (pDevMeas->m_strValue == "2")
	{
		//二次值，不用根据变比换算
		return TRUE;
	}

	//遥测参数映射时，都是固定ID映射
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
		//剩余的功率因素和频率，不用换算
		return TRUE;
	}
}

BOOL CDevice::ExprCal_dataset_Ain_I(CDataGroup *pAinRatios, double &dValRet)
{
	CDvmData *pCtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到CT变比一次值……"));
		return FALSE;
	}

	CDvmData *pCtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到CT变比二次值……"));
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
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到PT变比一次值……"));
		return FALSE;
	}

	CDvmData *pPtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到PT变比二次值……"));
		return FALSE;
	}

	double dPrimary = CString_To_double(pPtPrimary->m_strValue);
	double dSecondary = CString_To_double(pPtSecondary->m_strValue);
	//PT变比是 kV / V。
	double dRatio = dPrimary * 1000 / dSecondary;  

	//装置采样一次值时，电压单位为kV
	dValRet = dValRet * 1000 / dRatio;
	return TRUE;
}

BOOL CDevice::ExprCal_dataset_Ain_PQ(CDataGroup *pAinRatios, double &dValRet)
{
	CDvmData *pCtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到CT变比一次值……"));
		return FALSE;
	}

	CDvmData *pCtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到CT变比二次值……"));
		return FALSE;
	}

	CDvmData *pPtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtPrimary);

	if (pPtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到PT变比一次值……"));
		return FALSE;
	}

	CDvmData *pPtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到PT变比二次值……"));
		return FALSE;
	}

	double dCtPrimary = CString_To_double(pCtPrimary->m_strValue);
	double dCtSecondary = CString_To_double(pCtSecondary->m_strValue);
	double dPtPrimary = CString_To_double(pPtPrimary->m_strValue);
	double dPtSecondary = CString_To_double(pPtSecondary->m_strValue);
	//PT变比是 kV / V。
	double dRatio = (dCtPrimary / dCtSecondary) * (dPtPrimary * 1000 / dPtSecondary);  

	//装置采样一次值时，电压单位为kV。功率的单位是MW，MVAr
	dValRet = dValRet * 1000000 / dRatio;
	return TRUE;
}

BOOL CDevice::ExprCal_dataset_UTCTIME(const CString &strExpression, CExBaseList *pDataset, double &dValRet)
{
	//TODO：如何判断是遥信？然后需要用遥信值=1去处理。m_pRptDvmDataset->m_strID==report？
	CDvmData *pFind = NULL;
	if (pDataset->m_strID.Find(_T("report")) >=0 || pDataset->m_strID.Find(_T("soe")) >=0)
	{
		//暂时认为仅用于遥信SOE测试，需判断遥信值为1；
		POS pos = pDataset->GetTailPosition();  //从后往前，找最新的一条

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
	CDvmValue *pT = (CDvmValue *)pFind->FindByID(_T("$t"));//$t为遥信时间
	ASSERT(pT != NULL);

	if (pT == NULL)
	{
		return FALSE;
	}

	CString_To_SystemTime(pT->m_strValue, oTm);

	//获取总的ms。此处是为了判断时间差，因此暂时不考虑年月
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

	CDvmValue *pAccount = (CDvmValue *)pFind->FindByID(strID);//$t为遥信时间
	ASSERT(pAccount != NULL);

	if (pAccount == NULL)
	{
		return FALSE;
	}

	dValRet = CString_To_double(pAccount->m_strValue);

	return TRUE;
}

//遥信优先上送，$systime。是ppxml中接收到遥信时，进行填值的
BOOL CDevice::ExprCal_dataset_SysTime(const CString &strExpression, CExBaseList *pDataset, double &dValRet)
{
	CDvmData *pFind = NULL;
	if (pDataset->m_strID.Find(_T("report")) >=0 || pDataset->m_strID.Find(_T("soe")) >=0)
	{
		//遥信优先上送，用的是SOE数据集。需从前往后找，第一条值为1的遥信；
		POS pos = pDataset->GetHeadPosition();  //从前往后，找最先的一条

		while (pos != NULL)
		{
			CDvmData *pData = (CDvmData *)pDataset->GetNext(pos);

			if (pData->m_strID == strExpression && pData->m_strValue != _T("0"))
			{
				//遥信优先上送是，Ia的遥信的值，是采样值，不是0 或 1
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
	CDvmValue *pT = (CDvmValue *)pFind->FindByID(_T("$systime"));//$systime为ppxml记录的时间
	ASSERT(pT != NULL);

	if (pT == NULL)
	{
		return FALSE;
	}

	CString_To_SystemTime(pT->m_strValue, oTm);

	//获取总的ms。此处是为了判断时间差，因此暂时不考虑年月
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
	//对时功能，目前做法是先设置时间同步，然后遥控开关合，收到对应遥信(例如：Din_43)value为1时，$systime和$t相差5s内
	CDvmData *pFind = NULL;
	if (pDataset->m_strID.Find(_T("report")) >=0 || pDataset->m_strID.Find(_T("soe")) >=0)
	{
		//遥信对时测试，用的是SOE数据集。需从前往后找，第一条值为1的遥信；
		POS pos = pDataset->GetHeadPosition();  //从前往后，找最先的一条

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
	CDvmValue *pT = (CDvmValue *)pFind->FindByID(_T("$t"));//$t为遥信时间
	ASSERT(pT != NULL);

	if (pT == NULL)
	{
		return FALSE;
	}

	CString_To_SystemTime(pT->m_strValue, oTm);

	//获取总的ms。此处是为了判断时间差，因此暂时不考虑年月
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
		//项目相对路径不为空时，绑定到模型。否则绑定到相对项目的数据集报告
		CDataObj *pFind = m_pCpus->SelectDataObj(strExpression);

		if (pFind == NULL)
		{
			return FALSE;
		}

		pFind->m_strValue = strValue;
		return TRUE;
	}
	
	CGbItemBase *pItem = (CGbItemBase*)pExprParent;  //表达式的父对象
	CReport *pReport = NULL;
	CGbItemBaseList oDestList;
	//通过项目相对路径，查找项目
	pItem->SelectItems(strParentPath, oDestList);
	long nCount = oDestList.GetCount();

	if (nCount != 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("项目【%s】查找结果不唯一！找到【%d】个目标项目"), strParentPath.GetString(), nCount);
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

	//找不到结果参数，可以新建一个CDvmData。需要把name传进来
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
	CGbItemBase *pItem = (CGbItemBase*)pExprParent;  //表达式的父对象

	CReport *pReport = NULL;

	if (strParentPath.IsEmpty())
	{
		pReport = pItem->GetReport(-1);
	}
	else 
	{
		CGbItemBaseList oDestList;
		//通过项目相对路径，查找项目
		pItem->SelectItems(strParentPath, oDestList);
		long nCount = oDestList.GetCount();

		if (nCount != 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("项目【%s】查找结果不唯一！找到【%d】个目标项目"), strParentPath.GetString(), nCount);
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

	//找不到结果参数，可以新建一个CValue。需要把name传进来
	//对于ID中携带$符的参数，可以取$符最后一段，简单进行处理。例如：状态序列结果评估：rslt_evaluation$rslt_evaluation1$Ttrip_AbsErr
	if (pFind == NULL)
	{
		pFind = new CValue();
		pReport->m_pValues->AddNewChild(pFind);
		pReport->m_pValues->BringToHead(pFind);

		//忘记为啥要这么干了，注释掉。2023-8-31
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

		//当nCurrTestTimes > nRepeatTimes时，表示最后一份报告是计算报告
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
	BOOL bFind = FALSE;  //是否查找到一个有效结果参数

	while (pos != NULL)
	{
		CReport *pRpt = (CReport *)pListReportsForCal->GetNext(pos);
		pFind = pRpt->FindReportData(strExpression);

		if (pFind != NULL)
		{
			if (pFind->m_strValue == _T("--") || pFind->m_strValue == _T("未动作"))
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
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("找不到报告数据【%s】"), strExpression.GetString());
			bRet = FALSE;
		}
	}

	if (bFind == FALSE)
	{
		//若没找到一个有效结果参数
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
	BOOL bFind = FALSE;  //是否查找到一个有效结果参数
	POS pos = pListReportsForCal->GetHeadPosition();

	while (pos != NULL)
	{
		CReport *pRpt = (CReport *)pListReportsForCal->GetNext(pos);
		pFind = pRpt->FindReportData(strExpression);

		if (pFind != NULL)
		{
			if (pFind->m_strValue == _T("--") || pFind->m_strValue == _T("未动作"))
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
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("找不到报告数据【%s】"), strExpression.GetString());
			bRet = FALSE;
		}
	}

	if (bFind == FALSE)
	{
		//若没找到一个有效结果参数
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
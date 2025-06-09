//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGuideBook.cpp  CSttGuideBook


#include "stdafx.h"
#include "SttGuideBook.h"
#ifdef _PSX_IDE_QT_
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGuideBook::CSttGuideBook()
{
	//初始化属性
	m_nTestControlMode = 0;
	m_nReadOnly = 0;
	m_nIsSaveRptToDB = 0;

	//初始化成员变量
	m_pGlobalDatas = NULL;
	m_pItemsTec = NULL;
	m_pAinDataMapCfg = NULL;
	m_pTestGlobalDatasMngr = NULL;
}

CSttGuideBook::~CSttGuideBook()
{
}

long CSttGuideBook::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTestMacroFileIDKey, oNode, m_strTestMacroFileID);
	xml_GetAttibuteValue(pXmlKeys->m_strTestTypeFileKey, oNode, m_strTestTypeFile);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDevID);
	xml_GetAttibuteValue(pXmlKeys->m_strDevByKey, oNode, m_strDevBy);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strCommCmdConfigFileKey, oNode, m_strCommCmdConfigFile);
	xml_GetAttibuteValue(pXmlKeys->m_strPpTemplateFileKey, oNode, m_strPpTemplateFile);
	xml_GetAttibuteValue(pXmlKeys->m_strScriptMngrFileKey, oNode, m_strScriptMngrFile);
	xml_GetAttibuteValue(pXmlKeys->m_strPpEngineProgIDKey, oNode, m_strPpEngineProgID);
	xml_GetAttibuteValue(pXmlKeys->m_strDvmFileKey, oNode, m_strDvmFile);
	xml_GetAttibuteValue(pXmlKeys->m_strStandNameFileKey, oNode, m_strStandNameFile);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceModelFileKey, oNode, m_strDeviceModelFile);
	xml_GetAttibuteValue(pXmlKeys->m_strTestControlModeKey, oNode, m_nTestControlMode);
	xml_GetAttibuteValue(pXmlKeys->m_strExpandConfigFileKey, oNode, m_strExpandConfigFile);
	xml_GetAttibuteValue(pXmlKeys->m_strIecfgFileKey, oNode, m_strIecfgFile);
	xml_GetAttibuteValue(pXmlKeys->m_strReadOnlyKey, oNode, m_nReadOnly);
	xml_GetAttibuteValue(pXmlKeys->m_strSaveRptToDBKey, oNode, m_nIsSaveRptToDB);
	xml_GetAttibuteValue(pXmlKeys->m_strAuthoritySNKey, oNode, m_strAuthoritySN);
	xml_GetAttibuteValue(pXmlKeys->m_strAuthorityCopKey, oNode, m_strAuthorityCop);
	xml_GetAttibuteValue(pXmlKeys->m_strScriptTypeKey, oNode, m_strScriptType);
	return 0;
}

long CSttGuideBook::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTestMacroFileIDKey, oElement, m_strTestMacroFileID);
	xml_SetAttributeValue(pXmlKeys->m_strTestTypeFileKey, oElement, m_strTestTypeFile);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDevID);
	xml_SetAttributeValue(pXmlKeys->m_strDevByKey, oElement, m_strDevBy);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
	xml_SetAttributeValue(pXmlKeys->m_strCommCmdConfigFileKey, oElement, m_strCommCmdConfigFile);
	xml_SetAttributeValue(pXmlKeys->m_strPpTemplateFileKey, oElement, m_strPpTemplateFile);
	xml_SetAttributeValue(pXmlKeys->m_strScriptMngrFileKey, oElement, m_strScriptMngrFile);
	xml_SetAttributeValue(pXmlKeys->m_strPpEngineProgIDKey, oElement, m_strPpEngineProgID);
	xml_SetAttributeValue(pXmlKeys->m_strDvmFileKey, oElement, m_strDvmFile);
	xml_SetAttributeValue(pXmlKeys->m_strStandNameFileKey, oElement, m_strStandNameFile);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceModelFileKey, oElement, m_strDeviceModelFile);
	xml_SetAttributeValue(pXmlKeys->m_strTestControlModeKey, oElement, m_nTestControlMode);
	xml_SetAttributeValue(pXmlKeys->m_strExpandConfigFileKey, oElement, m_strExpandConfigFile);
	xml_SetAttributeValue(pXmlKeys->m_strIecfgFileKey, oElement, m_strIecfgFile);
	xml_SetAttributeValue(pXmlKeys->m_strReadOnlyKey, oElement, m_nReadOnly);
	xml_SetAttributeValue(pXmlKeys->m_strSaveRptToDBKey, oElement, m_nIsSaveRptToDB);
	xml_SetAttributeValue(pXmlKeys->m_strAuthoritySNKey, oElement, m_strAuthoritySN);
	xml_SetAttributeValue(pXmlKeys->m_strAuthorityCopKey, oElement, m_strAuthorityCop);
	xml_SetAttributeValue(pXmlKeys->m_strScriptTypeKey, oElement, m_strScriptType);
	return 0;
}

long CSttGuideBook::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttItemBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTestMacroFileID);
		BinarySerializeCalLen(oBinaryBuffer, m_strTestTypeFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strDevID);
		BinarySerializeCalLen(oBinaryBuffer, m_strDevBy);
		BinarySerializeCalLen(oBinaryBuffer, m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strCommCmdConfigFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strPpTemplateFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strScriptMngrFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strPpEngineProgID);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvmFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strStandNameFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceModelFile);
		BinarySerializeCalLen(oBinaryBuffer, m_nTestControlMode);
		BinarySerializeCalLen(oBinaryBuffer, m_strExpandConfigFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strIecfgFile);
		BinarySerializeCalLen(oBinaryBuffer, m_nReadOnly);
		BinarySerializeCalLen(oBinaryBuffer, m_nIsSaveRptToDB);
		BinarySerializeCalLen(oBinaryBuffer, m_strAuthoritySN);
		BinarySerializeCalLen(oBinaryBuffer, m_strAuthorityCop);
		BinarySerializeCalLen(oBinaryBuffer, m_strScriptType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTestMacroFileID);
		BinarySerializeRead(oBinaryBuffer, m_strTestTypeFile);
		BinarySerializeRead(oBinaryBuffer, m_strDevID);
		BinarySerializeRead(oBinaryBuffer, m_strDevBy);
		BinarySerializeRead(oBinaryBuffer, m_strVersion);
		BinarySerializeRead(oBinaryBuffer, m_strCommCmdConfigFile);
		BinarySerializeRead(oBinaryBuffer, m_strPpTemplateFile);
		BinarySerializeRead(oBinaryBuffer, m_strScriptMngrFile);
		BinarySerializeRead(oBinaryBuffer, m_strPpEngineProgID);
		BinarySerializeRead(oBinaryBuffer, m_strDvmFile);
		BinarySerializeRead(oBinaryBuffer, m_strStandNameFile);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceModelFile);
		BinarySerializeRead(oBinaryBuffer, m_nTestControlMode);
		BinarySerializeRead(oBinaryBuffer, m_strExpandConfigFile);
		BinarySerializeRead(oBinaryBuffer, m_strIecfgFile);
		BinarySerializeRead(oBinaryBuffer, m_nReadOnly);
		BinarySerializeRead(oBinaryBuffer, m_nIsSaveRptToDB);
		BinarySerializeRead(oBinaryBuffer, m_strAuthoritySN);
		BinarySerializeRead(oBinaryBuffer, m_strAuthorityCop);
		BinarySerializeRead(oBinaryBuffer, m_strScriptType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTestMacroFileID);
		BinarySerializeWrite(oBinaryBuffer, m_strTestTypeFile);
		BinarySerializeWrite(oBinaryBuffer, m_strDevID);
		BinarySerializeWrite(oBinaryBuffer, m_strDevBy);
		BinarySerializeWrite(oBinaryBuffer, m_strVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strCommCmdConfigFile);
		BinarySerializeWrite(oBinaryBuffer, m_strPpTemplateFile);
		BinarySerializeWrite(oBinaryBuffer, m_strScriptMngrFile);
		BinarySerializeWrite(oBinaryBuffer, m_strPpEngineProgID);
		BinarySerializeWrite(oBinaryBuffer, m_strDvmFile);
		BinarySerializeWrite(oBinaryBuffer, m_strStandNameFile);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceModelFile);
		BinarySerializeWrite(oBinaryBuffer, m_nTestControlMode);
		BinarySerializeWrite(oBinaryBuffer, m_strExpandConfigFile);
		BinarySerializeWrite(oBinaryBuffer, m_strIecfgFile);
		BinarySerializeWrite(oBinaryBuffer, m_nReadOnly);
		BinarySerializeWrite(oBinaryBuffer, m_nIsSaveRptToDB);
		BinarySerializeWrite(oBinaryBuffer, m_strAuthoritySN);
		BinarySerializeWrite(oBinaryBuffer, m_strAuthorityCop);
		BinarySerializeWrite(oBinaryBuffer, m_strScriptType);
	}
	return 0;
}

void CSttGuideBook::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATASET)
		{
			if (p->m_strID == g_strGbGlobalDatasID)
			{
				m_pGlobalDatas = (CDvmDataset*)p;
				continue;
			}	
		}

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			if (p->m_strID == ID_ITEMS_TEC)
			{
				m_pItemsTec = (CDataGroup *)p;
			}
			else if (p->m_strID == ID_AIN_DATA_MAP_CFG)
			{
				m_pAinDataMapCfg = (CDataGroup *)p;
			}

			continue;
		}	

		if (nClassID == STTGBXMLCLASSID_TESTGLOBALDATASMNGR)
		{
			m_pTestGlobalDatasMngr = (CSttTestGlobalDatasMngr *)p;
			continue;
		}
	}

	CSttItemBase::InitAfterRead();
}

BOOL CSttGuideBook::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttGuideBook *p = (CSttGuideBook*)pObj;

	if(m_strTestMacroFileID != p->m_strTestMacroFileID)
	{
		return FALSE;
	}

	if(m_strTestTypeFile != p->m_strTestTypeFile)
	{
		return FALSE;
	}

	if(m_strDevID != p->m_strDevID)
	{
		return FALSE;
	}

	if(m_strDevBy != p->m_strDevBy)
	{
		return FALSE;
	}

	if(m_strVersion != p->m_strVersion)
	{
		return FALSE;
	}

	if(m_strCommCmdConfigFile != p->m_strCommCmdConfigFile)
	{
		return FALSE;
	}

	if(m_strPpTemplateFile != p->m_strPpTemplateFile)
	{
		return FALSE;
	}

	if(m_strScriptMngrFile != p->m_strScriptMngrFile)
	{
		return FALSE;
	}

	if(m_strPpEngineProgID != p->m_strPpEngineProgID)
	{
		return FALSE;
	}

	if(m_strDvmFile != p->m_strDvmFile)
	{
		return FALSE;
	}

	if(m_strStandNameFile != p->m_strStandNameFile)
	{
		return FALSE;
	}

	if(m_strDeviceModelFile != p->m_strDeviceModelFile)
	{
		return FALSE;
	}

	if(m_nTestControlMode != p->m_nTestControlMode)
	{
		return FALSE;
	}

	if(m_strExpandConfigFile != p->m_strExpandConfigFile)
	{
		return FALSE;
	}

	if(m_strIecfgFile != p->m_strIecfgFile)
	{
		return FALSE;
	}

	if(m_nReadOnly != p->m_nReadOnly)
	{
		return FALSE;
	}

	if(m_nIsSaveRptToDB != p->m_nIsSaveRptToDB)
	{
		return FALSE;
	}

	if(m_strAuthoritySN != p->m_strAuthoritySN)
	{
		return FALSE;
	}

	if(m_strAuthorityCop != p->m_strAuthorityCop)
	{
		return FALSE;
	}

	if(m_strScriptType != p->m_strScriptType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttGuideBook::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttItemBase::CopyOwn(pDest);

	CSttGuideBook *p = (CSttGuideBook*)pDest;

	p->m_strTestMacroFileID = m_strTestMacroFileID;
	p->m_strTestTypeFile = m_strTestTypeFile;
	p->m_strDevID = m_strDevID;
	p->m_strDevBy = m_strDevBy;
	p->m_strVersion = m_strVersion;
	p->m_strCommCmdConfigFile = m_strCommCmdConfigFile;
	p->m_strPpTemplateFile = m_strPpTemplateFile;
	p->m_strScriptMngrFile = m_strScriptMngrFile;
	p->m_strPpEngineProgID = m_strPpEngineProgID;
	p->m_strDvmFile = m_strDvmFile;
	p->m_strStandNameFile = m_strStandNameFile;
	p->m_strDeviceModelFile = m_strDeviceModelFile;
	p->m_nTestControlMode = m_nTestControlMode;
	p->m_strExpandConfigFile = m_strExpandConfigFile;
	p->m_strIecfgFile = m_strIecfgFile;
	p->m_nReadOnly = m_nReadOnly;
	p->m_nIsSaveRptToDB = m_nIsSaveRptToDB;
	p->m_strAuthoritySN = m_strAuthoritySN;
	p->m_strAuthorityCop = m_strAuthorityCop;
	p->m_strScriptType = m_strScriptType;
	return TRUE;
}

CBaseObject* CSttGuideBook::Clone()
{
	CSttGuideBook *p = new CSttGuideBook();
	Copy(p);
	return p;
}

CBaseObject* CSttGuideBook::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGuideBook *p = new CSttGuideBook();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGuideBook::CanPaste(UINT nClassID)
{
	if (nClassID == STTGBXMLCLASSID_CSTTJOBGUIDE)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTDEVICE)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_TESTGLOBALDATASMNGR)
	{
		return TRUE;
	}

	if (nClassID == DTMCLASSID_CDATAGROUP)
	{
		return TRUE;
	}

	if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGuideBook::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttJobGuideKey)
	{
		pNew = new CSttJobGuide();
	}
	else if (strClassID == pXmlKeys->m_strCSttDeviceKey)
	{
		pNew = new CSttDevice();
	}
	else if (strClassID == pXmlKeys->m_strCDataGroupKey)
	{
		pNew = new CDataGroup();
	}
	else if (strClassID == pXmlKeys->m_strCDvmDatasetKey)
	{
		pNew = new CDvmDataset();
	}
	else if (strClassID == pXmlKeys->m_strTestGlobalDatasMngrKey)
	{
		pNew = new CSttTestGlobalDatasMngr();
	}
	else
	{
		return CSttItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
	}

	return pNew;
}

CExBaseObject* CSttGuideBook::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTGBXMLCLASSID_CSTTJOBGUIDE)
	{
		pNew = new CSttJobGuide();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTDEVICE)
	{
		pNew = new CSttDevice();
	}
	else if (nClassID == DTMCLASSID_CDATAGROUP)
	{
		pNew = new CDataGroup();
	}
	else if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		pNew = new CDvmDataset();
	}
	else if (nClassID == STTGBXMLCLASSID_TESTGLOBALDATASMNGR)
	{
		pNew = new CSttTestGlobalDatasMngr();
	}
	else
	{
		return CSttItemBase::CreateNewChild(nClassID);
	}

	return pNew;
}

//2022-9-13  lijunqing
void CSttGuideBook::SetGuideBookName(const CString &strName)
{
	m_strName = strName;
	m_strID = strName;

	CSttDevice *pDevice = GetDevice(TRUE);
	pDevice->m_strName = strName;
	pDevice->m_strID = strName;
}

CString CSttGuideBook::GetGuideBookName()
{
	CSttDevice *pDevice = GetDevice(FALSE);

	if (pDevice == NULL)
	{
		return m_strName;
	}

	return pDevice->m_strName;
}

//2022-1-11  lijunqing
CSttDevice* CSttGuideBook::GetDevice(BOOL bCreate)
{
	CSttDevice *pFind = (CSttDevice*)FindByClassID(STTGBXMLCLASSID_CSTTDEVICE);

	if (pFind == NULL)
	{
		if (bCreate)
		{
			pFind = new CSttDevice();
			AddNewChild(pFind);
		}
	}

	return pFind;
}

CDvmDataset* CSttGuideBook::GetGlobalDatas(BOOL bCreateNew)
{
	if (m_pGlobalDatas != NULL)
	{
		return m_pGlobalDatas;
	}

	m_pGlobalDatas = (CDvmDataset*)FindByID(g_strGbGlobalDatasID);

	if (m_pGlobalDatas == NULL)
	{
		if (bCreateNew)
		{
			m_pGlobalDatas = new CDvmDataset();
			m_pGlobalDatas->m_strName = g_strGbGlobalDatasID;
			m_pGlobalDatas->m_strID = g_strGbGlobalDatasID;
			AddNewChild(m_pGlobalDatas);
		}
	}
	
	return m_pGlobalDatas;
}

void CSttGuideBook::InitGlobalDatas(CDvmDataset *pGlobalDatas)
{
	if (m_pGlobalDatas == NULL)
	{
		m_pGlobalDatas = (CDvmDataset *)pGlobalDatas->Clone();
		AddNewChild(m_pGlobalDatas);
	}
	else
	{
		m_pGlobalDatas->InitValue(pGlobalDatas, TRUE);
	}
}

void CSttGuideBook::ClearGuideBook()
{
	/*if (m_pGlobalDatas != NULL)
	{
		Remove(m_pGlobalDatas);
		DeleteAll();
		AddNewChild(m_pGlobalDatas);
	}
	else
	{
		DeleteAll();
	}*/

	DeleteAll();//修改原有写法：清空之后需AppendEx的话需调用InitAfterRead赋值正确指针
	m_pItemsTec = NULL;
	m_pAinDataMapCfg = NULL;
	m_pGlobalDatas = NULL;
}

void CSttGuideBook::InitDevice()
{
	CSttDevice *pSttDevice = GetDevice();

	if (pSttDevice == NULL)
	{
		pSttDevice = new CSttDevice();
		AddNewChild(pSttDevice);
		pSttDevice->m_strName = _T("新测试");
		pSttDevice->m_strID = _T("Device");
		pSttDevice->InitAfterRead();
	}
}

long CSttGuideBook::GetGbItemCount()
{
	CSttDevice *pDevice = GetDevice(FALSE);

	if (pDevice == NULL)
	{
		return 0;
	}

	return pDevice->GetGbItemCount();
}

void CSttGuideBook::GetProcess(long &nIndexCurrent, long &nCountTotal)
{
	CSttDevice *pDevice = GetDevice(FALSE);

	if (pDevice == NULL)
	{
		return;
	}

	long nEligibleCount, nInlegibleCount = 0;
	
	pDevice->GetItemsCountByItemsType(nCountTotal, nEligibleCount, nInlegibleCount);
	nIndexCurrent = nInlegibleCount + nEligibleCount;
}

void CSttGuideBook::GetFirstTwoItemsByItemsType(CString &strFirst, CString &strSecond)
{
	CSttDevice *pDevice = GetDevice(FALSE);

	if (pDevice == NULL)
	{
		return;
	}

	pDevice->GetFirstTwoItemsByItemsType(strFirst, strSecond);
}

void CSttGuideBook::GetAllItemsByItemsType(CExBaseList &oList)
{
	CSttDevice *pDevice = GetDevice(FALSE);

	if (pDevice == NULL)
	{
		return;
	}

	pDevice->GetAllItemsByItemsType(oList);
}

//2022-3-30  lijunqing
void CSttGuideBook::SaveFile()
{
	
}

void CSttGuideBook::SaveFile(const CString &strPath, const CString &strFileName)
{
	m_strPath = strPath;
	m_strFile = strFileName;

	CString strFile;
	ValidatePath(m_strPath);
}

//如果pParent下，有相同ID的项目，则需要删除原项目。此时，插入项目后需要刷新显示pParent。故增加bUpdateParent以示区分
CSttItemBase* CSttGuideBook::InsertItems(const CString &strParentPath, CSttItems *pItems, BOOL &bUpdateParent)
{
	if (pItems == NULL)
	{
		return NULL;
	}

	CSttDevice *pSttDevice = GetDevice(TRUE);
	CSttItemBase *pParent = stt_gb_find_itembase(this, strParentPath);

	if (pParent == NULL)
	{
		pSttDevice->AddNewChild(pItems);
		pParent = pSttDevice;
	}
	else
	{
		CSttItems *pFind = (CSttItems*)pParent->FindByID(pItems->m_strID);

		if (pFind == NULL)
		{
			pParent->AddNewChild(pItems);
		}
		else
		{
			POS pos = pParent->Find(pFind);
			pParent->SetAt(pos, pItems);
			pItems->SetParent(pParent);
			delete pFind;
			bUpdateParent = TRUE;
		}
	}

	//修改为返回父节点  shaolei 2023-8-12
	//return pItems;
	return pParent;
}

//在同一个位置，批量插入项目：pItemsList是需要插入的项目列表
BOOL CSttGuideBook::InsertItemsEx(const CString &strParentPath, CExBaseList *pItemsList, BOOL &bUpdateParent)
{
	CSttItemBase *pParent = stt_gb_find_itembase(this, strParentPath);

	if (pParent == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("向项目树中插入项目失败！找不到父项目【%s】"), strParentPath.GetString());
		return FALSE;
	}

	POS pos = pItemsList->GetHeadPosition();

	while (pos != NULL)
	{
		CSttItemBase *pItem = (CSttItemBase *)pItemsList->GetNext(pos);
		CSttItemBase *pFind = (CSttItemBase*)pParent->FindByID(pItem->m_strID);

		if (pFind == NULL)
		{
			pParent->AddNewChild(pItem);
		}
		else
		{
			POS pos = pParent->Find(pFind);
			pParent->SetAt(pos, pItem);
			pItem->SetParent(pParent);
			delete pFind;
			bUpdateParent = TRUE;
		}
	}

	return TRUE;
}

CSttItems* CSttGuideBook::FindFirstItems(const CString &strType, BOOL bCheckType)
{
	CSttDevice *pDevice = GetDevice();

	if (pDevice == NULL)
	{
		return NULL;
	}

	return (CSttItems *)pDevice->FindFirstItems(strType, bCheckType);
}

//2023-2-8  lijunqing
CDvmData* CSttGuideBook::FindDataByID(const CString &strID)
{
	CDvmData *pFind = NULL;

	if (m_pGlobalDatas != NULL)
	{
		pFind = (CDvmData*)m_pGlobalDatas->FindByID(strID);

		if (pFind != NULL)
		{
			return pFind;
		}
	}

	return pFind;
}

BOOL CSttGuideBook::GetDataValueByID(const CString &strID, float &fValue)
{
	CDvmData *pFind = FindDataByID(strID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	fValue = CString_To_double(pFind->m_strValue);

	return TRUE;
}

void CSttGuideBook::AddTimeSettingCoef(long nTSettingUnitMs)
{
	GetGlobalDatas(TRUE);
	CString strValue = _T("1");

	if (nTSettingUnitMs == 1)
	{
		 strValue = _T("0.001");
	}
	
	CDvmData *pFind = (CDvmData*)m_pGlobalDatas->FindByID(GbGlobalData_Time_Setting_Coef);

	if (pFind == NULL)
	{
		pFind = new CDvmData();
#ifdef _PSX_IDE_QT_
		xlang_GetLangStrByFile(pFind->m_strName, "Native_TimeSettingCoef");
#else
		pFind->m_strName = _T("时间定值比例系数");
#endif
		pFind->m_strID = GbGlobalData_Time_Setting_Coef;
		pFind->m_strDataType = _T("float");
		m_pGlobalDatas->AddNewChild(pFind);
	}

	pFind->m_strValue = strValue;
}

void CSttGuideBook::UpdateSysPara(CExBaseList *pSrcList, BOOL bCreateNew)
{
	CSttDevice *pDevice = GetDevice(FALSE);

	if (pDevice != NULL)
	{
		pDevice->UpdateSysPara(pSrcList, bCreateNew);
	}
}

CDataGroup* CSttGuideBook::GetItemsTec()
{
	return m_pItemsTec;
}

void CSttGuideBook::SetItemsTec(CDataGroup *pItemsTec)
{
	if (m_pItemsTec != NULL)
	{
		Delete(m_pItemsTec);
	}

	if (pItemsTec == NULL)
	{
		m_pItemsTec = NULL;
		return;
	}

	m_pItemsTec = (CDataGroup*)pItemsTec->CloneEx(TRUE, TRUE);
	m_pItemsTec->m_strName = ID_ITEMS_TEC;
	m_pItemsTec->m_strID = ID_ITEMS_TEC;
	AddNewChild(m_pItemsTec);
	BringToHead(m_pItemsTec);
}

CDataGroup* CSttGuideBook::GetAinDataMapCfg()
{
	return m_pAinDataMapCfg;
}

void CSttGuideBook::SetAinDataMapCfg(CDataGroup *pAinDataMapCfg)
{
	if (m_pAinDataMapCfg != NULL)
	{
		Delete(m_pAinDataMapCfg);
	}

	if (pAinDataMapCfg == NULL)
	{
		m_pAinDataMapCfg = NULL;
		return;
	}

	m_pAinDataMapCfg = (CDataGroup*)pAinDataMapCfg->CloneEx(TRUE, TRUE);
	m_pAinDataMapCfg->m_strName = ID_AIN_DATA_MAP_CFG;
	m_pAinDataMapCfg->m_strID = ID_AIN_DATA_MAP_CFG;
	AddNewChild(m_pAinDataMapCfg);
	BringToHead(m_pAinDataMapCfg);
}

BOOL CSttGuideBook::IsAinDataMapValid()
{
	if (m_pAinDataMapCfg == NULL)
	{
		return FALSE;
	}

	POS pos = m_pAinDataMapCfg->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pDataMap = (CDvmData *)m_pAinDataMapCfg->GetNext(pos);

		if (pDataMap->m_strDataType.GetLength() > 0
			&& pDataMap->m_strValue.GetLength() > 0)
		{
			//包含一个有效配置，则认为配置有效；
			return TRUE;
		}
	}

	return FALSE;
}

/*
#define ID_PARA_DevMeas    _T("DevMeas")  //装置采样信息，是一次值还是二次值。1|2
#define ID_PARA_PtPrimary    _T("PtPrimary")  //PT一次值
#define ID_PARA_PtSecondary    _T("PtSecondary")  //PT二次值
#define ID_PARA_CtPrimary    _T("CtPrimary")   //CT一次值
#define ID_PARA_CtSecondary    _T("CtSecondary")   //CT二次值
*/

CDataGroup* CSttGuideBook::GetAinRatios()
{
	CDvmDataset *pGlobalDatas = GetGlobalDatas(FALSE);

	if (pGlobalDatas == NULL)
	{
		return NULL;
	}

	CDataGroup *pNewGrp = new CDataGroup();
	pNewGrp->m_strID = ID_AIN_RATIOS;
	pNewGrp->m_strName = ID_AIN_RATIOS;

	CDvmData *pDevMeas = (CDvmData *)pGlobalDatas->FindByID(ID_PARA_DevMeas);

	if (pDevMeas != NULL)
	{
		pNewGrp->AddNewChild((CDvmData *)pDevMeas->CloneEx());
	}

	CDvmData *pPtPrimary = (CDvmData *)pGlobalDatas->FindByID(ID_PARA_PtPrimary);

	if (pPtPrimary != NULL)
	{
		pNewGrp->AddNewChild((CDvmData *)pPtPrimary->CloneEx());
	}

	CDvmData *pPtSecondary = (CDvmData *)pGlobalDatas->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary != NULL)
	{
		pNewGrp->AddNewChild((CDvmData *)pPtSecondary->CloneEx());
	}

	CDvmData *pCtPrimary = (CDvmData *)pGlobalDatas->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary != NULL)
	{
		pNewGrp->AddNewChild((CDvmData *)pCtPrimary->CloneEx());
	}

	CDvmData *pCtSecondary = (CDvmData *)pGlobalDatas->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary != NULL)
	{
		pNewGrp->AddNewChild((CDvmData *)pCtSecondary->CloneEx());
	}

	return pNewGrp;
}

void CSttGuideBook::SetAinRatios(CDataGroup *pAinRatios)
{
	CDvmDataset *pGlobalDatas = GetGlobalDatas(TRUE);
	POS pos = pAinRatios->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pAinRatios->GetNext(pos);
		CDvmData *pFind = (CDvmData *)pGlobalDatas->FindByID(pData->m_strID);

		if (pFind == NULL)
		{
			pGlobalDatas->AddNewChild((CDvmData *)pData->Clone());
		}
		else
		{
			pFind->m_strValue = pData->m_strValue;
		}
	}
}

CSttItemBase* stt_gb_find_itembase(CSttGuideBook *pSttGuideBook, const CString &strItemPath)
{
	CSttDevice *pDevice = pSttGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return NULL;
	}

	if (strItemPath.GetLength() == 0)
	{
		return pDevice;
	}

	CExBaseList listDest;
	CExBaseObject *pFind = NULL;
	CString strPath = strItemPath;
	pDevice->FindByPathChildren(strPath, listDest, '$');

	if (listDest.GetCount() == 0)
	{
		return NULL;
	}

	pFind = (CExBaseObject *)listDest.GetHead();
	listDest.RemoveAll();

	//CExBaseObject *pFind = pDevice->FindByIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE, strItemPath);

	if (pFind == NULL)
	{
		return NULL;
	}

	if (! stt_gb_is_a_itembase(pFind))
	{
		return NULL;
	}

	return (CSttItemBase*)pFind;
}

CSttItemBase* stt_gb_find_itembase_ex(CSttGuideBook *pSttGuideBook, const CString &strItemPath)
{
	if (pSttGuideBook == NULL)
	{
		return NULL;
	}

	if (strItemPath.GetLength() == 0)
	{
		return pSttGuideBook;
	}

	CExBaseList listDest;
	CExBaseObject *pFind = NULL;
	CString strPath = strItemPath;
	pSttGuideBook->FindByPathChildren(strPath, listDest, '$');

	if (listDest.GetCount() == 0)
	{
		return stt_gb_find_itembase(pSttGuideBook, strItemPath);
	}

	pFind = (CExBaseObject *)listDest.GetHead();
	listDest.RemoveAll();

	if (pFind == NULL)
	{
		return NULL;
	}

	if (! stt_gb_is_a_itembase(pFind))
	{
		return NULL;
	}

	return (CSttItemBase*)pFind;
}

void stt_gb_get_itempath_id(CSttItemBase *pSttItemBase, CString &strItemPath, UINT nRootClassID)
{
	CExBaseObject *pParent = NULL;
	strItemPath = pSttItemBase->m_strID;

	pParent = (CExBaseObject*)pSttItemBase->GetParent();

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == nRootClassID)
		{
			break;
		}

		strItemPath = pParent->m_strID + _T("$") + strItemPath;

		pParent = (CExBaseObject*)pParent->GetParent();
	}
}

void stt_gb_get_itempath_name(CSttItemBase *pSttItemBase, CString &strItemPath, UINT nRootClassID)
{
	CExBaseObject *pParent = NULL;
	strItemPath = pSttItemBase->m_strName;

	pParent = (CExBaseObject*)pSttItemBase->GetParent();

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == nRootClassID)
		{
			break;
		}

		strItemPath = pParent->m_strName + _T("$") + strItemPath;

		pParent = (CExBaseObject*)pParent->GetParent();
	}
}

// bRecursion：是否递归删除子项目
void stt_gb_delete_childitem_commcmd(CSttItemBase *pSttItemBase, BOOL bRecursion)
{
	pSttItemBase->DeleteChildItem_Commcmd(bRecursion);
}

void stt_gb_get_all_child_title_itembase(CSttItemBase *pSttItemBase,CDataGroup *pDataGroup,const CString &strRootItemsID)
{
	if (pSttItemBase == NULL)
	{
		return;
	}

	POS pos = pSttItemBase->GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;
	CSttItemBase *pChildItemBase = NULL;
	CString strPath;
	CDvmData *pData = NULL;

	while(pos)
	{
		pCurrObj = pSttItemBase->GetNext(pos);

		if ((pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)||(pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTCOMMCMD)
			||(pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)||(pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROCHARITEMS))
		{
			pChildItemBase = (CSttItemBase *)pCurrObj;
			strPath = pChildItemBase->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

			if (strPath.GetLength() > strRootItemsID.GetLength())
			{
				pData = new CDvmData;
				pData->m_strID = strPath.Mid(strRootItemsID.GetLength());
				pData->m_strName = pChildItemBase->m_strName;
				pData->m_strValue = pChildItemBase->m_strName;
				pDataGroup->AddNewChild(pData);
			} 

			stt_gb_get_all_child_title_itembase(pChildItemBase,pDataGroup,strRootItemsID);
		}
	}
}

#ifndef _PSX_IDE_QT_
void getItems(CSttItems* pItem, CList<CSttItems*>& list)
{
    CExBaseObject *pObj = NULL;	
    POS pos = pItem->GetHeadPosition();

    while (pos != NULL)
    {
        pObj = pItem->GetNext(pos);

        //节点不是items类型
        if (pObj->GetClassID() != STTGBXMLCLASSID_CSTTITEMS)
        {
            continue;
        }

        CSttItems *pItems = (CSttItems *)pObj;
        list.AddTail(pItems);

        getItems(pItems, list);
        
    }
}
#endif

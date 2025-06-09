//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDevice.cpp  CDvmDevice


#include "stdafx.h"
#include "DvmDevice.h"
#include "../API/FileApi.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CDvmCmpKeyDataTypes* CDvmDevice::g_pDvmCmpKeyDataTypes = NULL;
long CDvmDevice::g_nDvmCmpKeyDataTypesRef = 0;

void CDvmDevice::CreateDvmCmpKeyDataTypes()
{
	g_nDvmCmpKeyDataTypesRef++;

	if (g_nDvmCmpKeyDataTypesRef == 1)
	{
		g_pDvmCmpKeyDataTypes = new CDvmCmpKeyDataTypes();
		g_pDvmCmpKeyDataTypes->OpenKeyDataTypesFile(_T(""));
	}
}

void CDvmDevice::ReleaseDvmCmpKeyDataTypes()
{
	g_nDvmCmpKeyDataTypesRef--;

	if (g_nDvmCmpKeyDataTypesRef == 0)
	{
		delete g_pDvmCmpKeyDataTypes;
		g_pDvmCmpKeyDataTypes = NULL;
	}
}

CDvmDevice::CDvmDevice()
{
	//初始化属性
#ifdef NOT_USE_XLANGUAGE
    m_strName = _T("device-model");
#else
	m_strName = g_sLangTxt_EquipDataModel;//_T("设备数据模型");
#endif
	m_strID = _T("device-model");
	//初始化成员变量

	m_pDeviceAttr = NULL;
	m_bModifiedFlag = FALSE;
	
	m_nFormatUseMode = DVM_FORMART_USE_MODE_VAL;
}

CDvmDevice::~CDvmDevice()
{
	FreeAttrs();
}

long CDvmDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDvmDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDvmDevice::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	if (m_pDeviceAttr != NULL)
	{
		m_pDeviceAttr->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

long CDvmDevice::Serialize(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::Serialize(oBinaryBuffer);

	return 0;
}

long CDvmDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CDvmDevice::FreeAttrs()
{
	if (m_pDeviceAttr != NULL)
	{
		delete m_pDeviceAttr;
		m_pDeviceAttr = NULL;
	}
}

void CDvmDevice::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseList oList;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			oList.AddTail(p);
		}
	}

	FreeAttrs();
	
	if (oList.GetCount() == 0)
	{
		m_pDeviceAttr = new CDvmDataset();

#ifdef NOT_USE_XLANGUAGE
        m_pDeviceAttr->m_strName = _T("device-attr");;//
#else
		m_pDeviceAttr->m_strName = g_sLangTxt_DevAtrbDefin;//_T("设备属性定义");
#endif

		m_pDeviceAttr->m_strID   = _T("device-attr");
		m_pDeviceAttr->SetParent(this);
	}
	else
	{
		m_pDeviceAttr = (CDvmDataset*)oList.GetHead();
		Remove(m_pDeviceAttr);
		oList.Remove(m_pDeviceAttr);

		pos = oList.GetHeadPosition();

		while (pos != NULL)
		{
			p = oList.GetNext(pos);
			Delete(p);
		}

		oList.RemoveAll();
	}

	InitFormatUseMode();
}

void CDvmDevice::InitFormatUseMode()
{
	//2023-4-21  lijunqing 增加Data数据对象对formart属性的使用模式
	CDvmData *pFind = (CDvmData*)m_pDeviceAttr->FindByID(DVM_FORMART_USE_MODE_KEY);
	m_nFormatUseMode = DVM_FORMART_USE_MODE_VAL;

	if (pFind == NULL)
	{
		return;
	}

	InitFormatUseMode(pFind->m_strValue);
}

void CDvmDevice::InitFormatUseMode(const CString &strValue)
{
	if (strValue.GetLength() == 0)
	{
		return;
	}

	if (strValue == _T("1"))
	{
		m_nFormatUseMode = DVM_FORMART_USE_MODE_EXPR;
		return;
	}

	if (strValue == DVM_FORMART_USE_MODE_ID_EXPR)
	{
		m_nFormatUseMode = DVM_FORMART_USE_MODE_EXPR;
		return;
	}
}

BOOL CDvmDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDvmDevice *p = (CDvmDevice*)pObj;

	return TRUE;
}

BOOL CDvmDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDvmDevice *p = (CDvmDevice*)pDest;

	return TRUE;
}

CBaseObject* CDvmDevice::Clone()
{
	CDvmDevice *p = new CDvmDevice();
	Copy(p);
	return p;
}

BOOL CDvmDevice::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CDVMLOGICDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDvmDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmLogicDeviceKey)
	{
		pNew = new CDvmLogicDevice();
		return pNew;
	}

	if (strClassID == pXmlKeys->m_strCDvmDatasetKey)
	{
		pNew = new CDvmDataset();
		return pNew;
	}

	return pNew;
}

CExBaseObject* CDvmDevice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DVMCLASSID_CDVMLOGICDEVICE)
	{
		pNew = new CDvmLogicDevice();
	}

	return pNew;
}

CDvmData* CDvmDevice::GetAttr(const CString &strAttrID)
{
	CDvmDataset *pAttrs = GetDeviceAttrs();
	CDvmData *pData = (CDvmData*)pAttrs->FindByID(strAttrID);

	if (pData == NULL)
	{
		pData = new CDvmData();
		pData->m_strID = strAttrID;
		pData->m_strName = strAttrID;
		pAttrs->AddNewChild(pData);
	}

	return pData;
}

BOOL CDvmDevice::GetDeviceAttribute(const CString &strAttrTag, CString &strAttrValue)
{
	CDvmData *pAttr = GetAttr(strAttrTag);
	ASSERT (pAttr != NULL);
	strAttrValue = pAttr->m_strValue;

	return TRUE;
}

BOOL CDvmDevice::SetDeviceAttribute(const CString &strAttrTag, const CString &strAttrValue)
{
	CDvmData *pAttr = GetAttr(strAttrTag);

	if (pAttr == NULL)
	{
		return FALSE;
	}

	ASSERT (pAttr != NULL);
#ifdef _DVM_VALUE_USE_CHAR_
#ifdef UNICODE
	wcscpy(pAttr->m_strValue, strAttrValue);
#else
	BSTR bstr = strAttrValue.AllocSysString();
	wcscpy(pAttr->m_strValue, bstr);
	::SysFreeString(bstr);
#endif
#else
	pAttr->m_strValue = strAttrValue;
#endif

	if (strAttrTag == DVM_FORMART_USE_MODE_KEY)
	{
		InitFormatUseMode(strAttrValue);
	}

	return TRUE;
}

CDvmLogicDevice* CDvmDevice::AddNewLogicDevice(CDvmLogicDevice *pSrc)
{
	CDvmLogicDevice *pData = NULL;

	if (pSrc != NULL)
	{
		pData = (CDvmLogicDevice *)pSrc->Clone();
	}
	else
	{
		pData = new CDvmLogicDevice();
	}

	AddNewChild(pData);

	return pData;
}

CDvmLogicDevice* CDvmDevice::FindByIndex(long nIndex)
{
	CDvmLogicDevice *p = NULL;
	CDvmLogicDevice *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmLogicDevice *)GetNext(pos);

		if (p->m_nIndex == nIndex)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDvmDataset* CDvmDevice::GetDeviceAttrs()
{
	if (m_pDeviceAttr == NULL)
	{
		m_pDeviceAttr = new CDvmDataset();
	}

	return m_pDeviceAttr;
}


//////////////////////////////////////////////////////////////////////////
//2020-6-18  lijunqing  增加通用的功能
CDvmDataset* CDvmDevice::FindDataset(const CString &strDatasetID)
{
	CDvmDataset *pFind = NULL;
	CDvmLogicDevice *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmLogicDevice *)GetNext(pos);
		pFind = (CDvmDataset *)p->FindByID(strDatasetID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

//2022-11-21 lijunqing
CDvmDataset* CDvmDevice::FindDatasetByPath(const CString &strDatasetIDPath)
{
	long nSepPos = strDatasetIDPath.Find('$');	

	if (nSepPos == -1)
	{
		return NULL;
	}
	
	CString strLdID, strDsID;
	strLdID = strDatasetIDPath.Left(nSepPos);
	strDsID = strDatasetIDPath.Mid(nSepPos+1);
	CExBaseList *pLdevice = (CExBaseList *)FindByID(strLdID);

	if (pLdevice == NULL)
	{
		return NULL;
	}

	CDvmDataset *pFind = (CDvmDataset*)pLdevice->FindByID(strDsID);

	return pFind;
}

long CDvmDevice::GetDatasetList(const CString &strKey, CExBaseList &oListDataset)
{
	POS pos = GetHeadPosition();
	CDvmLogicDevice *pLd = NULL;

	while (pos != NULL)
	{
		pLd = (CDvmLogicDevice *)GetNext(pos);
		pLd->GetDatasetList(strKey, oListDataset);
	}

	return oListDataset.GetCount();
}

long CDvmDevice::GetDatasetList(CStringArray &strKeyArray, CExBaseList &oListDataset)
{
	CString strKey;

	for (int n=0; n<strKeyArray.GetCount();n++)
	{
		strKey = strKeyArray.GetAt(n);
		GetDatasetList(strKey, oListDataset);
	}

	return oListDataset.GetCount();
}

CDvmDataset* CDvmDevice::GetDataset(const CString &strLdID, const CString &strDsID, BOOL bCreateNew)
{
	CDvmLogicDevice *pLdDevice = (CDvmLogicDevice*)FindByID(strLdID);

	if (pLdDevice == NULL)
	{
		if (bCreateNew)
		{
			pLdDevice = new CDvmLogicDevice();
			pLdDevice->m_strName = strLdID;
			pLdDevice->m_strID = strLdID;
			AddNewChild(pLdDevice);
		}
		else
		{
			return NULL;
		}
	}

	CDvmDataset *pDataset = (CDvmDataset*)pLdDevice->FindByID(strDsID);

	if (pDataset== NULL)
	{
		if (bCreateNew)
		{
			pDataset = new CDvmDataset();
			pLdDevice->AddNewChild(pDataset);
			pDataset->m_strName = strDsID;
			pDataset->m_strID = strDsID;
			return pDataset;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return pDataset;
	}
}

//2023-4-18  lijunqing
long CDvmDevice::GetDatasetCount()
{
	POS pos = GetHeadPosition();
	CDvmLogicDevice *pLd = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pLd = (CDvmLogicDevice *)GetNext(pos);
		
		if (pLd->GetClassID() == DVMCLASSID_CDVMLOGICDEVICE)
		{
			nCount += pLd->GetCount();
		}
	}

	return nCount;
}


CDvmData* CDvmDevice::SelectDataObj(const CString &strPath)
{
	CDvmData *pFind = NULL;

	CExBaseList oListData;
	SelectDatas(strPath, oListData, _T("$"));

	if (oListData.GetCount() == 1)
	{
		pFind = (CDvmData *)oListData.GetHead();
	}
	else if (oListData.GetCount() > 1)
	{
		ASSERT(FALSE);
		pFind = (CDvmData *)oListData.GetHead();
	}

	if (pFind == NULL)
	{
		pFind = FindDataObjByID(strPath);

		if (pFind == NULL)
		{
			pFind = FindDataObjByID_Has(strPath);
		}
	}

	oListData.RemoveAll();

	return pFind;
}

long CDvmDevice::SelectDataObj(const CString &strPath, CExBaseList &listDatas)
{
	CDvmData *pFind = NULL;

	SelectDatas(strPath, listDatas, _T("$"));

	if (listDatas.GetCount() == 0)
	{
		if (FindDataObjByID(strPath, listDatas) == 0)
		{
			FindDataObjByID_Has(strPath, listDatas);
		}
	}

	return listDatas.GetCount();
}

long CDvmDevice::SelectDataObj(const CString &strDatasetPath, const CString &strPath, CExBaseList &listDatas)
{
	SelectDatas_FilterByPath(strDatasetPath, strPath, listDatas, _T("$"));

	if (listDatas.GetCount() == 0)
	{
		if (FindDataObjByID(strPath, listDatas) == 0)
		{
			FindDataObjByID_Has(strPath, listDatas);
		}
	}

	return listDatas.GetCount();
}


CDvmData* CDvmDevice::FindDataObjByID_Has(const CString &strID)
{
	CDvmLogicDevice *pCpu = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pCpu = (CDvmLogicDevice *)GetNext(pos);
		pFind = (CDvmData *)pCpu->FindDataObjByID_Has(strID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

long CDvmDevice::FindDataObjByID_Has(const CString &strID, CExBaseList &listDatas)
{
	CDvmLogicDevice *pCpu = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pCpu = (CDvmLogicDevice *)GetNext(pos);
		pCpu->FindDataObjByID_Has(strID, listDatas);
	}

	return listDatas.GetCount();
}


long CDvmDevice::SelectDatas_FilterByPath(const CString &strDatasetPath, const CString &strIDPath, CExBaseList &oListDest, const CString &strSeperator)
{
	CDvmLogicDevice *pCpu = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pCpu = (CDvmLogicDevice *)GetNext(pos);

		if (strDatasetPath.Find(pCpu->m_strID) < 0)
		{
			continue;
		}

		pCpu->FindDataObjByID(strIDPath, oListDest);
	}

	return oListDest.GetCount();
}


CDvmData* CDvmDevice::FindDataObjByID(const CString &strID)
{
	CDvmLogicDevice *pCpu = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pCpu = (CDvmLogicDevice *)GetNext(pos);
		pFind = (CDvmData *)pCpu->FindDataObjByID(strID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

CDvmData* CDvmDevice::FindDataObjByID(const CString &strCpuID, const CString &strDsID, const CString &strDataID)
{
	CDvmLogicDevice *pCpu = (CDvmLogicDevice*)FindByID(strCpuID);

	if (pCpu == NULL)
	{
		return NULL;
	}

	CDvmDataset *pDataset = (CDvmDataset*)pCpu->FindByID(strDsID);

	if (pDataset == NULL)
	{
		return NULL;
	}

	return (CDvmData*)pDataset->FindByID(strDataID);
}

long CDvmDevice::FindDataObjByID(const CString &strID, CExBaseList &listDatas)
{
	CDvmLogicDevice *pCpu = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pCpu = (CDvmLogicDevice *)GetNext(pos);
		pCpu->FindDataObjByID(strID, listDatas);
	}

	return listDatas.GetCount();
}


CDvmDataset* CDvmDevice::SelectDatasetByKey(const CString &strIDPath)
{
	long nLdKeyFind = g_pDvmCmpKeyDataTypes->GetLdeviceKey(strIDPath);
	long nDsKeyFind = g_pDvmCmpKeyDataTypes->GetDatasetKey(strIDPath);

	if (nDsKeyFind < 0 || nLdKeyFind < 0)
	{
		return NULL;
	}

	CDvmLogicDevice *pCpu = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pCpu = (CDvmLogicDevice *)GetNext(pos);

		if (nLdKeyFind == g_pDvmCmpKeyDataTypes->GetLdeviceKey(pCpu->m_strID))
		{
			POS posDs = pCpu->GetHeadPosition();
			CDvmDataset *pDs = NULL;

			while (posDs != NULL)
			{
				pDs = (CDvmDataset *)pCpu->GetNext(posDs);

				if (nDsKeyFind == g_pDvmCmpKeyDataTypes->GetDatasetKey(pDs->m_strID))
				{
					return pDs;
				}
			}
		}
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//
void dvm_SetModifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	CDvmDevice *pDvmDevice = (CDvmDevice*)pData->GetAncestor(DVMCLASSID_CDVMDEVICE);
	ASSERT (pDvmDevice != NULL);

	if (pDvmDevice == NULL)
	{
		return;
	}

	pDvmDevice->m_bModifiedFlag = bModified;
}

#ifndef _PSX_IDE_QT_

BOOL ats_GetDeviceModeleFiles(CString &strDeviceFile, CWnd *pParent, const CString &strCaption)
{
#ifdef NOT_USE_XLANGUAGE
	CString strFilter = _T("设备点表文件(*.xml)|*.xml||");
#else
	CString strFilter = g_sLangTxt_ItemPrtcFile/*_T("设备点表文件(*.xml)|*.xml||")*/;
#endif

	if (strCaption.GetLength() == 0)
	{
#ifdef NOT_USE_XLANGUAGE
		return PopupOpenFileDialog(pParent, strDeviceFile, strFilter, _T("xml"), _T("选择设备数据模型文件"));
#else
		return PopupOpenFileDialog(pParent, strDeviceFile, strFilter, _T("xml"), g_sLangTxt_SelDevDaModFile/*_T("选择设备数据模型文件")*/);
#endif
	}
	else
	{
		return PopupOpenFileDialog(pParent, strDeviceFile, strFilter, _T("xml"), strCaption);
	}
}
#endif

long dvm_GetLdIndex(const CString &strLdevice)
{
	long nPos = strLdevice.GetLength() - 1;
	long nLastPos = nPos;

	if (nPos <= 0)
	{
		return -1;
	}

	long nIndex = -1;
	char ch = 0;
	BOOL bFind = FALSE;

	while (TRUE)
	{
		ch = strLdevice[nPos];

		if ('0' <= ch && ch <= '9')
		{
			nLastPos = nPos;
			bFind = TRUE;
			nPos--;
		}
		else
		{
			break;
		}
	}

	if (bFind)
	{
		CString strIndex = strLdevice.Mid(nLastPos);
		nIndex = CString_To_long(strIndex);
	}

	return nIndex;
}

CDvmLogicDevice* dvm_FindByLdIndex(CDvmDevice *pDevice, long nLdIndex)
{
	POS pos = pDevice->GetHeadPosition();
	CDvmLogicDevice *p = NULL, *pFind = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		p = (CDvmLogicDevice *)pDevice->GetNext(pos);
		nIndex = dvm_GetLdIndex(p->m_strID);

		if (nIndex == nLdIndex)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmLogicDevice.cpp  CDvmLogicDevice


#include "stdafx.h"
#include "DvmLogicDevice.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CDvmLogicDevice::CDvmLogicDevice()
{
#ifdef NOT_USE_XLANGUAGE
	m_strName = _T("逻辑设备(CPU)");
#else
	m_strName = /*g_sLangTxt_LogicdevCPU*/_T("逻辑设备(CPU)");
#endif
	m_strID = _T("CPU");

	//初始化属性
	m_nIndex = 0;

	//初始化成员变量
	m_pRptCtrls = NULL;
	m_pLogCtrls = NULL;
// 	m_pDvmLogControl = NULL;
}

CDvmLogicDevice::~CDvmLogicDevice()
{
}

long CDvmLogicDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
	
	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);

	return 0;
}

long CDvmLogicDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);

	return 0;
}

long CDvmLogicDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CDvmLogicDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDvmLogicDevice *p = (CDvmLogicDevice*)pObj;

	return TRUE;
}

BOOL CDvmLogicDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDvmLogicDevice *p = (CDvmLogicDevice*)pDest;

	return TRUE;
}

CBaseObject* CDvmLogicDevice::Clone()
{
	CDvmLogicDevice *p = new CDvmLogicDevice();
	Copy(p);
	return p;
}

CExBaseObject* CDvmLogicDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmDatasetKey)
	{
		pNew = new CDvmDataset();
	}
	else if (strClassID == pXmlKeys->m_strCDvmDatasetGroupKey)
	{
		pNew = new CDvmDatasetGroup();
	}
	else if (strClassID == pXmlKeys->m_strCRptCtrlsKey)
	{
		pNew = new CRptCtrls();
	}
	else if (strClassID == pXmlKeys->m_strCLogCtrlsKey)
	{
		pNew = new CLogCtrls();
	}
	else if (strClassID == pXmlKeys->m_strCDvmLogsKey)
	{
		pNew = new CDvmLogs();
	}

	//子对象需要新增CDataGroup、CDvmFolder
	//CDvmFolder子对象有：CDvmFolder、CDvmFile

	return pNew;
}

CExBaseObject* CDvmLogicDevice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		pNew = new CDvmDataset();
	}
	else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
	{
		pNew = new CDvmDatasetGroup();
	}
	else if (nClassID == DVMCLASSID_CRPTCTRLS)
	{
		pNew = new CRptCtrls();
	}
	else if (nClassID == DVMCLASSID_CLOGCTRLS)
	{
		pNew = new CLogCtrls();
	}
	else if (nClassID == DVMCLASSID_CDVMLOGS)
	{
		pNew = new CDvmLogs();
	}
// 	else if (nClassID == DVMCLASSID_CDVMLOGCTRL)
// 	{
// 		m_pDvmLogControl = new CDvmDataset();
// 		pNew = m_pDvmLogControl;
// 	}

	return pNew;
}

BOOL CDvmLogicDevice::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		return TRUE;
	}

	return FALSE;
}

CDvmDataset* CDvmLogicDevice::AddNewDataset(CDvmDataset *pSrc)
{
	CDvmDataset *pData = NULL;

	if (pSrc != NULL)
	{
		pData = (CDvmDataset *)pSrc->Clone();
	}
	else
	{
		pData = new CDvmDataset();
	}

	AddNewChild(pData);

	return pData;
}

CDvmDataset* CDvmLogicDevice::AddNewDataset(const CString &strName, const CString &strID)
{
	CDvmDataset *pDataset = new CDvmDataset();
	pDataset->m_strName = strName;
	pDataset->m_strID = strID;
	AddNewChild(pDataset);
	return pDataset;
}

CDvmDatasetGroup* CDvmLogicDevice::AddNewDatasetGroup(CDvmDatasetGroup *pSrc)
{
	CDvmDatasetGroup *pNew = NULL;

	if (pSrc != NULL)
	{
		pNew = (CDvmDatasetGroup *)pSrc->Clone();
	}
	else
	{
		pNew = new CDvmDatasetGroup();
	}

	AddNewChild(pNew);

	return pNew;
}

CDvmDatasetGroup* CDvmLogicDevice::AddNewDatasetGroup(const CString &strName, const CString &strID)
{
	CDvmDatasetGroup *pDatasetGroup = new CDvmDatasetGroup();
	pDatasetGroup->m_strName = strName;
	pDatasetGroup->m_strID = strID;
	AddNewChild(pDatasetGroup);
	return pDatasetGroup;
}

CDvmDataset* CDvmLogicDevice::FindByIndex(long nIndex)
{
	CDvmDataset *p = NULL;
	CDvmDataset *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmDataset *)GetNext(pos);

		if (p->m_nIndex == nIndex)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

BOOL CDvmLogicDevice::HasValueID(const CString &strValueID)
{
	if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strNameKey)
	{
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strIDKey)
	{
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strIndexKey)
	{
		return TRUE;
	}
	
	return FALSE;
}

BOOL CDvmLogicDevice::SetAttr(const CString &strAttrID, const CString &strValue)
{
	if (strAttrID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strNameKey)
	{
		m_strName = strValue;
		return TRUE;
	}

	if (strAttrID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strIDKey)
	{
		m_strID = strValue;
		return TRUE;
	}

	if (strAttrID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strIndexKey)
	{
        m_nIndex = CString_To_long(strValue);
		return TRUE;
	}

	return FALSE;
}


void CDvmLogicDevice::InitAfterRead()
{
// 	POS pos = GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 	POS posLG = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		posLG = pos;
// 		p = GetNext(pos);
// 
// 		if (p->m_strID == CDataMngrXmlRWKeys::CDvmLogControlKey())
// 		{
// 			m_pDvmLogControl = (CDvmLogControl *)p;
// 			break;
// 		}
// 	}
}

long CDvmLogicDevice::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

long CDvmLogicDevice::SerializeChildren(CBinarySerialBuffer &oBinaryBuffer)
{
	return CExBaseList::SerializeChildren(oBinaryBuffer);
}

CRptCtrls*  CDvmLogicDevice::GetRptCtrls()
{
	if (m_pRptCtrls == NULL)
	{
		m_pRptCtrls = new CRptCtrls();
		AddNewChild(m_pRptCtrls);

		m_pRptCtrls->m_strName = m_strName;
		m_pRptCtrls->m_strID   = m_strID;
	}

	return m_pRptCtrls;
}

CLogCtrls*  CDvmLogicDevice::GetLogCtrls()
{
	if (m_pLogCtrls == NULL)
	{
		m_pLogCtrls = new CLogCtrls();
		AddNewChild(m_pLogCtrls);

		m_pLogCtrls->m_strName = m_strName;
		m_pLogCtrls->m_strID   = m_strID;
	}

	return m_pLogCtrls;
}

CDvmDataset *CDvmLogicDevice::FindByNameAndClassID(const CString& strName,long nClassID)
{
	CExBaseObject *p = NULL;
	CDvmDataset *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);
		if (nClassID == DVMCLASSID_CDVMDATASET && p->m_strName == strName)
		{
			pFind = (CDvmDataset *)p;
			break;
		}
	}

	return pFind;
}

long CDvmLogicDevice::GetDatasetList(const CString &strKey, CExBaseList &oListDataset)
{
	POS pos = GetHeadPosition();
	CDvmDataset *p = NULL;

	if (strKey.GetLength() <= 1 || strKey == _T("all") )
	{
		while (pos != NULL)
		{
			p = (CDvmDataset *)GetNext(pos);
			oListDataset.AddTail(p);
		}
	}
	else
	{
		while (pos != NULL)
		{
			p = (CDvmDataset *)GetNext(pos);

			if (p->m_strID.Find(strKey) >= 0)
			{
				if (oListDataset.Find(p) == NULL)
				{
					oListDataset.AddTail(p);
				}
			}
		}
	}

	return oListDataset.GetCount();
}

#ifndef _PSX_IDE_QT_
//add by masj 2022-06-08
void CDvmLogicDevice::FindByIDEX(const CString &strID, CList<CDvmDataset*>& _list)
{
    CDvmDataset* pTemp = NULL;
    CDvmDataset* pFind = NULL;

    POS pos = GetHeadPosition();

    while (pos != NULL)
    {
        pTemp = (CDvmDataset*)GetNext(pos);

        if ( pTemp->m_strID.Find(strID) >= 0)
        {
            pFind = pTemp;
            _list.AddTail(pFind);
        }
    }

}
#endif


CDvmData* CDvmLogicDevice::FindDataObjByName(const CString &strName)
{
	CDvmDataset *pDataSet = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pDataSet = (CDvmDataset *)GetNext(pos);
		pFind = (CDvmData *)pDataSet->FindByName(strName);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

CDvmData* CDvmLogicDevice::FindDataObjByID(const CString &strID)
{
	CDvmDataset *pDataSet = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pDataSet = (CDvmDataset *)GetNext(pos);
		pFind = (CDvmData *)pDataSet->FindByID(strID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

long CDvmLogicDevice::FindDataObjByID(const CString &strID, CExBaseList &listDatas)
{
	CDvmDataset *pDataSet = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pDataSet = (CDvmDataset *)GetNext(pos);
		pFind = (CDvmData *)pDataSet->FindByID(strID);

		if (pFind != NULL)
		{
			listDatas.AddTail(pFind);
		}
	}

	return listDatas.GetCount();
}


CDvmData* CDvmLogicDevice::FindDataObjByID_Has(const CString &strID)
{
	CDvmDataset *pDataSet = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pDataSet = (CDvmDataset *)GetNext(pos);
		pFind = (CDvmData *)pDataSet->FindDataObjByID_Has(strID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

long CDvmLogicDevice::FindDataObjByID_Has(const CString &strID, CExBaseList &listDatas)
{
	CDvmDataset *pDataSet = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pDataSet = (CDvmDataset *)GetNext(pos);
		pFind = (CDvmData *)pDataSet->FindDataObjByID_Has(strID);

		if (pFind != NULL)
		{
			listDatas.AddTail(pFind);
		}
	}

	return listDatas.GetCount();
}



CDvmDataset* dvm_FindDataset(CDvmLogicDevice *pLdevice, const CString &strID)
{
	POS pos = pLdevice->GetHeadPosition();
	CDvmDataset *p = NULL, *pDataset = NULL;

	while (pos != NULL)
	{
		p = (CDvmDataset *)pLdevice->GetNext(pos);
		CString strTemp = p->m_strID;
		strTemp.MakeLower();

		if (strTemp == strID)
		{
			pDataset = p;
			break;
		}
	}

	return pDataset;
}

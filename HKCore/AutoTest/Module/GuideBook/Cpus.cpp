#include "StdAfx.h"
#include "Cpus.h"
#include "Cpu.h"
#include "GbItemBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void Gb_GetNewCpusID(CExBaseList &oListCpus, CString &strID)
{
	CCpus *pCpus = (CCpus*)oListCpus.GetHead();

	if (pCpus == NULL)
	{
		CString strName;
		Gb_InitCpusNameAndID(strName, strID);
		return;
	}

	strID = pCpus->m_strID;
	long nIndex=0;
	long nPos = strID.ReverseFind('.');
	CString strTemp;

	if (nPos >= 0)
	{
		strTemp = strID.Mid(nPos+1);
		nIndex = CString_To_long(strTemp);
		strTemp = strID.Left(nPos+1);
	}
	else
	{
		long nLen = strID.GetLength();

		if (nLen > 0)
		{
			CHAR ch = strID.GetAt(nLen - 1);

			if ('0' <= ch && ch <= '9')
			{
				nIndex=ch - '0';
				strTemp = strID.Left(nLen - 1);
			}
		}

		strTemp = strID;
	}

	while (TRUE)
	{
        strID.Format(_T("%s%d"), strTemp.GetString(), nIndex);

		if (oListCpus.FindByID(strID) == NULL)
		{
			break;
		}

		nIndex++;

		if (nIndex >= 255)
		{
			nIndex = 100;
		}
	}
}


CDvmCmpKeyDataTypes* CCpus::g_pDvmCmpKeyDataTypes = NULL;
long CCpus::g_nDvmCmpKeyDataTypesRef = 0;

void CCpus::CreateDvmCmpKeyDataTypes()
{
	g_nDvmCmpKeyDataTypesRef++;

	if (g_nDvmCmpKeyDataTypesRef == 1)
	{
		g_pDvmCmpKeyDataTypes = new CDvmCmpKeyDataTypes();
		g_pDvmCmpKeyDataTypes->OpenKeyDataTypesFile(_T(""));
	}
}

void CCpus::ReleaseDvmCmpKeyDataTypes()
{
	g_nDvmCmpKeyDataTypesRef--;

	if (g_nDvmCmpKeyDataTypesRef == 0)
	{
		delete g_pDvmCmpKeyDataTypes;
		g_pDvmCmpKeyDataTypes = NULL;
	}
}

CCpus::CCpus(void)
{
	CreateDvmCmpKeyDataTypes();
	Gb_InitCpusNameAndID(m_strName, m_strID);
	m_strPpEngineProgID = g_strPpEngineProgIDMms;
}

CCpus::~CCpus(void)
{
	ReleaseDvmCmpKeyDataTypes();
	//DeleteAll();
}


long CCpus::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbXMLKeys *pGbXmlKeys = (CGbXMLKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pGbXmlKeys->m_strPpTemplateFileKey,oNode,m_strPpTemplateFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strDvmFileKey,oNode,m_strDeviceModelFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strPpEngineProgIDKey,oNode,m_strPpEngineProgID);

	return 0;
}

long CCpus::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pGbXmlKeys = (CGbXMLKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pGbXmlKeys->m_strPpEngineProgIDKey,oElement,m_strPpEngineProgID);
	xml_SetAttributeValue(pGbXmlKeys->m_strPpTemplateFileKey,oElement,m_strPpTemplateFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strDeviceModelFileKey,oElement,m_strDeviceModelFile);

	return 0;
}

long CCpus::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
	{
		CExBaseList::SerializeOwn(oBinaryBuffer);

		BinarySerializeCalLen(oBinaryBuffer,m_strPpEngineProgID);
		BinarySerializeCalLen(oBinaryBuffer,m_strPpTemplateFile);
		BinarySerializeCalLen(oBinaryBuffer,m_strDeviceModelFile);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_9)
		{
			CExBaseList::SerializeOwn(oBinaryBuffer);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_12)
		{
			BinarySerializeRead(oBinaryBuffer,m_strPpEngineProgID);
			BinarySerializeRead(oBinaryBuffer,m_strPpTemplateFile);
			BinarySerializeRead(oBinaryBuffer,m_strDeviceModelFile);
		}
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		CExBaseList::SerializeOwn(oBinaryBuffer);

		BinarySerializeWrite(oBinaryBuffer,m_strPpEngineProgID);
		BinarySerializeWrite(oBinaryBuffer,m_strPpTemplateFile);
		BinarySerializeWrite(oBinaryBuffer,m_strDeviceModelFile);
	}

	return 0;
}

CExBaseObject* CCpus::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCpuKey)
	{
		CCpu* pCpu = new CCpu;
		return pCpu;
	}

	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strLDeviceKey)
	{
		CCpu* pCpu = new CCpu;
		return pCpu;
	}

	return NULL;
}

CExBaseObject* CCpus::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_CPU)
	{
		CCpu* pCpu = new CCpu;
		return pCpu;
	}

	return NULL;
}

CBaseObject* CCpus::Clone()
{
	CCpus* pCpus = new CCpus();
	Copy(pCpus);

	return pCpus;
}

CBaseObject* CCpus::CloneEx(BOOL bCopyOwn/*=TRUE*/,BOOL bCopyChildren/*=FALSE*/)
{
	CCpus *p = new CCpus();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CCpus::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_CPU)
	{
		return TRUE;
	}

	return FALSE;
}

CCpu* CCpus::SelectCpu(const CString &strPath, CString &strLeft, CString &strRight)
{
	CCpu *pCpu = NULL;
	long nPos = -1;
    nPos = strPath.Find(_P_FOLDER_PATH_SEPARATOR_);

	if (nPos < 0)
	{
		nPos = strPath.Find(_T("/"));
	}

	if (nPos >= 0)
	{
		strLeft = strPath.Left(nPos);
		strRight = strPath.Mid(nPos+1);
		pCpu = (CCpu*)FindByID(strLeft);

		if (pCpu == NULL)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("String (%s) in Path[%s] is not a CPU id"), strLeft.GetString(), strPath.GetString());
		}
	}
	else
	{
		pCpu = (CCpu*)GetHead();
		strRight = strPath;
	}

	return pCpu;
}

// CSet* CCpus::SelectSet(const CString &strPath)
// {
// 	CString strLeft, strRight;
// 	CCpu *pCpu = SelectCpu(strPath, strLeft, strRight);
// 
// 	if (pCpu == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CSet *pSet = NULL;
// 	pSet = (CSet*)pCpu->m_pSets->FindByID(strRight);
// 
// 	if (pSet == NULL)
// 	{
// 		pSet = (CSet*)pCpu->m_pSets->FindByName(strRight);
// 	}
// 
// 	return pSet;
// }

CDataObj* CCpus::SelectDataObj(const CString &strPath)
{
	CDataObj *pFind = NULL;

	CExBaseList oListData;
	SelectDatas(strPath, oListData, _T("$"));

	if (oListData.GetCount() == 1)
	{
		pFind = (CDataObj *)oListData.GetHead();
	}
	else if (oListData.GetCount() > 1)
	{
		ASSERT(FALSE);
		pFind = (CDataObj *)oListData.GetHead();
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

long CCpus::SelectDataObj(const CString &strPath, CExBaseList &listDatas)
{
	CDataObj *pFind = NULL;

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

long CCpus::SelectDataObj(const CString &strDatasetPath, const CString &strPath, CExBaseList &listDatas)
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

long CCpus::SelectDatas_FilterByPath(const CString &strDatasetPath, const CString &strIDPath, CExBaseList &oListDest, const CString &strSeperator)
{
	CCpu *pCpu = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pCpu = (CCpu *)GetNext(pos);

		if (strDatasetPath.Find(pCpu->m_strID) < 0)
		{
			continue;
		}

		pCpu->FindDataObjByID(strIDPath, oListDest);
	}

	return oListDest.GetCount();
}

long CCpus::GetDataSetList(const CString &strKey, CExBaseList &oListDataSet)
{
	POS pos = GetHeadPosition();
	CCpu *pCpu = NULL;

	while (pos != NULL)
	{
		pCpu = (CCpu *)GetNext(pos);
		pCpu->GetDataSet(strKey, oListDataSet, NULL);
	}

	return oListDataSet.GetCount();
}
// 
// CSet* CCpus::SelectCtrlWord(const CString &strPath)
// {
// 	CString strLeft, strRight;
// 	CCpu *pCpu = SelectCpu(strPath, strLeft, strRight);
// 
// 	if (pCpu == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CSet *pSet = NULL;
// 	pSet = (CSet*)pCpu->m_pCtrlWords->FindByID(strRight);
// 
// 	if (pSet == NULL)
// 	{
// 		pSet = (CSet*)pCpu->m_pCtrlWords->FindByName(strRight);
// 	}
// 
// 	return pSet;
// }
// 
// CSet* CCpus::SelectSoftSwitch(const CString &strPath)
// {
// 	CString strLeft, strRight;
// 	CCpu *pCpu = SelectCpu(strPath, strLeft, strRight);
// 
// 	if (pCpu == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CSet *pSet = NULL;
// 	pSet = (CSet*)pCpu->m_pSoftSwitchs->FindByID(strRight);
// 
// 	if (pSet == NULL)
// 	{
// 		pSet = (CSet*)pCpu->m_pSoftSwitchs->FindByName(strRight);
// 	}
// 
// 	return pSet;
// }
// 
// CAnalog* CCpus::SelectAnalog(const CString &strPath)
// {
// 	CString strLeft, strRight;
// 	CCpu *pCpu = SelectCpu(strPath, strLeft, strRight);
// 
// 	if (pCpu == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CAnalog *pAnalog = NULL;
// 	pAnalog = (CAnalog*)pCpu->m_pAnalogs->FindByID(strRight);
// 
// 	if (pAnalog == NULL)
// 	{
// 		pAnalog = (CAnalog*)pCpu->m_pAnalogs->FindByName(strRight);
// 	}
// 
// 	return pAnalog;
// }

CCpu* CCpus::GetCpu(const CString &strPath)
{
	CString strLeft, strRight;
	CCpu *pCpu = SelectCpu(strPath, strLeft, strRight);

	return pCpu;
}

void CCpus::InitAfterRead()
{
	//if( GetCount() == 0)
	//{
	//	CCpu* pCpu = new CCpu();
	//	pCpu->m_strName = _T("CPU");
	//	pCpu->m_strID = _T("CPU");
	//	AddTail(pCpu);
	//	pCpu->SetParent(this);
	//}
}

CExBaseList* CCpus::GetDeviceModelDatasById(const CString &strCpuID, const CString &strDeviceModelTypeID)
{
	CCpu *pCpu = (CCpu*)FindByID(strCpuID);

	if (pCpu == NULL)
	{
		pCpu = (CCpu *)GetHead();
	}

	if (pCpu == NULL)
	{
		return NULL;
	}

	return pCpu->GetDeviceModelDatasById(strDeviceModelTypeID);
}

BOOL CCpus::OpenModelFile(const CString &strXmlFile)
{
	DeleteAll();
	return OpenXmlFile(strXmlFile, GetXmlElementKey(), CGbXMLKeys::g_pGbXMLKeys);
}

BOOL CCpus::SaveModelFile(const CString &strXmlFile)
{
	return SaveXmlFile(strXmlFile, CGbXMLKeys::g_pGbXMLKeys);
}

//模型更新  shaolei 20220716
void CCpus::UpdataModelValue(CCpus *pSrcCpus, BOOL bNewNotExist)
{
	POS pos = pSrcCpus->GetHeadPosition();
	CCpu *pSrcCpu = NULL;
	CCpu *pDstCpu = NULL;
	CString strSrcID;

	while (pos != NULL)
	{
		pSrcCpu = (CCpu *)pSrcCpus->GetNext(pos);
		strSrcID = pSrcCpu->m_strID;
		pDstCpu = (CCpu *)FindByID(strSrcID);

		if (pDstCpu == NULL)
		{
			if (bNewNotExist)
			{
				pDstCpu = (CCpu *)pSrcCpu->CloneEx(TRUE,TRUE);
				AddNewChild(pDstCpu);
				continue;
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("设备数据模型更新，逻辑设备【%s】未找到"), strSrcID.GetString());
				continue;
			}
		}
		else
		{
			pDstCpu->UpdateDataSetValue(pSrcCpu, bNewNotExist);
		}
	}
}

CDataObj* CCpus::FindDataObjByName(const CString &strName)
{
	CCpu *pCpu = NULL;
	POS pos = GetHeadPosition();
	CDataObj *pFind = NULL;

	while (pos != NULL)
	{
		pCpu = (CCpu *)GetNext(pos);
		pFind = (CDataObj *)pCpu->FindDataObjByName(strName);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

CDataObj* CCpus::FindDataObjByID(const CString &strID)
{
	CCpu *pCpu = NULL;
	POS pos = GetHeadPosition();
	CDataObj *pFind = NULL;

	while (pos != NULL)
	{
		pCpu = (CCpu *)GetNext(pos);
		pFind = (CDataObj *)pCpu->FindDataObjByID(strID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

CDataObj* CCpus::FindDataObjByID(const CString &strCpuID, const CString &strDsID, const CString &strDataID)
{
	CCpu *pCpu = (CCpu*)FindByID(strCpuID);

	if (pCpu == NULL)
	{
		return NULL;
	}

	CDataSet *pDataset = (CDataSet*)pCpu->FindByID(strDsID);

	if (pDataset == NULL)
	{
		return NULL;
	}

	return (CDataObj*)pDataset->FindByID(strDataID);
}
//20231106 huangliang 没有父级的情况
CDataSet* CCpus::FindDataObjByID(const CString &strCpuID, const CString &strDsID)	
{
	CCpu *pCpu = (CCpu*)FindByID(strCpuID);

	if (pCpu == NULL)
	{
		return NULL;
	}

	return (CDataSet*)pCpu->FindByID(strDsID);
}

long CCpus::FindDataObjByID(const CString &strID, CExBaseList &listDatas)
{
	CCpu *pCpu = NULL;
	POS pos = GetHeadPosition();
	CDataObj *pFind = NULL;

	while (pos != NULL)
	{
		pCpu = (CCpu *)GetNext(pos);
		pCpu->FindDataObjByID(strID, listDatas);
	}

	return listDatas.GetCount();
}

CDataObj* CCpus::FindDataObjByID_Has(const CString &strID)
{
	CCpu *pCpu = NULL;
	POS pos = GetHeadPosition();
	CDataObj *pFind = NULL;

	while (pos != NULL)
	{
		pCpu = (CCpu *)GetNext(pos);
		pFind = (CDataObj *)pCpu->FindDataObjByID_Has(strID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

long CCpus::FindDataObjByID_Has(const CString &strID, CExBaseList &listDatas)
{
	CCpu *pCpu = NULL;
	POS pos = GetHeadPosition();
	CDataObj *pFind = NULL;

	while (pos != NULL)
	{
		pCpu = (CCpu *)GetNext(pos);
		pCpu->FindDataObjByID_Has(strID, listDatas);
	}

	return listDatas.GetCount();
}

CDataSet* CCpus::SelectDataset(const CString &strIDPath, const CString &strSeperator)
{
	CDataSet *pFind = NULL;
	CExBaseList oList;
	SelectDatas(strIDPath, oList, strSeperator);

	if (oList.GetCount() == 1)
	{
		pFind = (CDataSet *)oList.GetHead();

		if (pFind->GetClassID() != GBCLASSID_DATASET)
		{
			pFind = NULL;
		}
	}

	oList.RemoveAll();

	return pFind;
}

CDataSet* CCpus::SelectDatasetByKey(const CString &strIDPath)
{
	long nLdKeyFind = g_pDvmCmpKeyDataTypes->GetLdeviceKey(strIDPath);
	long nDsKeyFind = g_pDvmCmpKeyDataTypes->GetDatasetKey(strIDPath);

	if (nDsKeyFind < 0 || nLdKeyFind < 0)
	{
		return NULL;
	}

	CCpu *pCpu = NULL;
	POS pos = GetHeadPosition();
	CDataObj *pFind = NULL;

	while (pos != NULL)
	{
		pCpu = (CCpu *)GetNext(pos);
		
		if (nLdKeyFind == g_pDvmCmpKeyDataTypes->GetLdeviceKey(pCpu->m_strID))
		{
			POS posDs = pCpu->GetHeadPosition();
			CDataSet *pDs = NULL;

			while (posDs != NULL)
			{
				pDs = (CDataSet *)pCpu->GetNext(posDs);

				if (nDsKeyFind == g_pDvmCmpKeyDataTypes->GetDatasetKey(pDs->m_strID))
				{
					return pDs;
				}
			}
		}
	}

	return NULL;
}


void CCpus::ResetDvmValue()
{
	POS pos = GetHeadPosition();
	CCpu *p = NULL;

	while (pos != NULL)
	{
		p = (CCpu *)GetNext(pos);
		p->ResetDvmValue();
	}
}

void CCpus::GetDataObjsByNameHas(const CString &strDsIDHas, const CString &strDataNameHas, CExBaseList *pList)
{
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CCpu *pCpu = (CCpu *)GetNext(pos);
		pCpu->GetDataObjsByNameHas(strDsIDHas, strDataNameHas, pList);
	}
}

CDataSet* CCpus::GetDataSetByKey(const CString &strKey)
{
	CCpu *pCurCpu = NULL;
	CDataSet *pFindDataset = NULL;
	POS pos_cpu = GetHeadPosition();

	while(pos_cpu)
	{
		pCurCpu = (CCpu*)GetNext(pos_cpu);

		if (pCurCpu->GetClassID() != GBCLASSID_CPU)
		{
			continue;
		}

		pFindDataset = pCurCpu->GetDataSetByKey(strKey);

		if (pFindDataset != NULL)
		{
			break;;
		}
	}

	return pFindDataset;
}

CDataSet* CCpus::GetDataSet_Setting()
{
	CDataSet *pDataset_Setting = GetDataSetByKey(_T("dsSetting"));

	if (pDataset_Setting == NULL)
	{
		CCpu *pCpu = (CCpu*)GetHead();

		if (pCpu == NULL)
		{
			pCpu = new CCpu;
			pCpu->m_strID = _T("Prot");
			pCpu->m_strName = pCpu->m_strID;
			pCpu->m_nIndex = 1;
			AddNewChild(pCpu);
		}

		pDataset_Setting = new CDataSet;
		pDataset_Setting->m_strName = _T("dsSetting");
		pDataset_Setting->m_strID = pDataset_Setting->m_strName;
		pCpu->AddNewChild(pDataset_Setting);
	}

	return pDataset_Setting;
}

BOOL CCpus::GetAllDatasByDatasetKey(CDataSet *pDatasetRef,const CString &strKey)
{
	CCpu *pCurCpu = NULL;
	POS pos_cpu = GetHeadPosition();

	while(pos_cpu)
	{
		pCurCpu = (CCpu*)GetNext(pos_cpu);

		if (pCurCpu->GetClassID() == GBCLASSID_CPU)
		{
			pCurCpu->GetAllDatasByDatasetKey(pDatasetRef,strKey);
		}
	}

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//
#ifdef GUIDEBOOK_DEV_MODE

void CCpus::DvmReplaceByMap(CDvmDeviceMap *pDvmDeviceMap)
{
	CCpus oCpus;
	oCpus.OpenModelFile(pDvmDeviceMap->m_strMapID);

	DeleteAll();
	AppendEx(oCpus);
	oCpus.RemoveAll();

// 	POS pos = pDvmDeviceMap->GetHeadPosition();
// 	CDvmLDeviceMap *pLdMap = NULL;
// 	CCpu *pSrc = NULL, *pDest = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pLdMap = (CDvmLDeviceMap *)pDvmDeviceMap->GetNext(pos);
// 		pSrc = (CCpu *)FindByID(pLdMap->m_strID);
// 		pDest = (CCpu *)oCpus.FindByID(pLdMap->m_strMapID);
// 	}
}

#endif

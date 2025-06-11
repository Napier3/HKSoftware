#include "stdafx.h"
#include "Cpu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCpu::CCpu(void)
{
// 	m_pAnalogs = NULL;
// 	m_pSets = NULL;
// 	m_pCtrlWords = NULL;
// 	m_pSoftSwitchs = NULL;
// 	m_pBinaryIns = NULL;
// 	m_pBinaryOuts = NULL;
// 	m_pSoes = NULL;

	m_nIndex = 1;
	m_pReport = NULL;

	m_nDsParameter = 0;
	m_nDsSetting = 0;
	m_nDsEna = 0;
	m_nDsAin = 0;
	m_nDsDin = 0;
	m_nDsRec = 0;
	m_nDsTripInfo = 0;
	m_nDsAlarm = 0;
	m_nDsWarning = 0;
	m_nDsSoe = 0;
	m_nDsSV = 0;
	m_nDsGOOSE = 0;
	m_pLogCtrls = NULL;
}

CCpu::~CCpu(void)
{
	if (m_pLogCtrls != NULL)
	{
		delete m_pLogCtrls;
		m_pLogCtrls = NULL;
	}
}

long CCpu::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strIndexKey,oNode,m_nIndex);

// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsParameterKey, oNode,m_nDsParameter);
// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsSettingKey, oNode,m_nDsSetting);
// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsEnaKey, oNode,m_nDsEna);
// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsAinKey, oNode,m_nDsAin);
// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsDinKey, oNode,m_nDsDin);
// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsRecKey, oNode,m_nDsRec);
// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsTripInfoKey, oNode,m_nDsTripInfo);
// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsAlarmKey, oNode,m_nDsAlarm);
// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsWarningKey, oNode,m_nDsWarning);
// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsSoeKey, oNode,m_nDsSoe);
// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsSVKey, oNode,m_nDsSV);
// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDsGOOSEKey, oNode,m_nDsGOOSE);

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	return 0;
}

long CCpu::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strIndexKey, oElement,m_nIndex);

	return 0;
}

long CCpu::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_nIndex);

// 		BinarySerializeCalLen(oBinaryBuffer, m_nYC);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nYB);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nYX);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nYK);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nYT);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nKZ);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nDZ);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer,m_nIndex);

// 		BinarySerializeRead(oBinaryBuffer, m_nYC);
// 		BinarySerializeRead(oBinaryBuffer, m_nYB);
// 		BinarySerializeRead(oBinaryBuffer, m_nYX);
// 		BinarySerializeRead(oBinaryBuffer, m_nYK);
// 		BinarySerializeRead(oBinaryBuffer, m_nYT);
// 		BinarySerializeRead(oBinaryBuffer, m_nKZ);
// 		BinarySerializeRead(oBinaryBuffer, m_nDZ);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_nIndex);

// 		BinarySerializeWrite(oBinaryBuffer, m_nYC);
// 		BinarySerializeWrite(oBinaryBuffer, m_nYB);
// 		BinarySerializeWrite(oBinaryBuffer, m_nYX);
// 		BinarySerializeWrite(oBinaryBuffer, m_nYK);
// 		BinarySerializeWrite(oBinaryBuffer, m_nYT);
// 		BinarySerializeWrite(oBinaryBuffer, m_nKZ);
// 		BinarySerializeWrite(oBinaryBuffer, m_nDZ);
	}

	return 0;
}

CExBaseObject* CCpu::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{

// 	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strAnalogsKey)
// 	{
// 		m_pAnalogs = new CAnalogs();
// 		return m_pAnalogs;
// 	}
// 	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strSetsKey)
// 	{
// 		m_pSets = new CSets;
// 		return m_pSets;
// 	}
// 	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCtrlWordsKey)
// 	{
// 		m_pCtrlWords = new CCtrlWords;
// 		return m_pCtrlWords;
// 	}
// 	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strBinaryInsKey)
// 	{
// 		m_pBinaryIns = new CBinaryIns;
// 		return m_pBinaryIns;
// 	}
// 	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strBinaryOutsKey)
// 	{
// 		m_pBinaryOuts = new CBinaryOuts ;
// 		return m_pBinaryOuts;
// 	}
// 	else if (strClassID ==CGbXMLKeys::g_pGbXMLKeys->m_strSoftSwitchsKey)
// 	{
// 		m_pSoftSwitchs = new CSoftSwitchs;
// 		return m_pSoftSwitchs;
// 	}
// 	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strSoesKey)
// 	{
// 		m_pSoes = new CSoes;
// 		return m_pSoes;
// 	}
// 	else
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey)
	{
		return new CDataSet;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strDataSetGroupKey)
	{
		return new CDataSetGroup;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strLogCtrlsKey)
	{//2018-3-3  lijq
		bAddToTail = FALSE;
		m_pLogCtrls = new CGbLogCtrls;
		return m_pLogCtrls;
	}

	return NULL;
}

CExBaseObject* CCpu::CreateNewChild(long nClassID)
{
// 	if (nClassID == GBCLASSID_ANALOGS)
// 	{
// 		m_pAnalogs = new CAnalogs;
// 		return m_pAnalogs;
// 	}
// 	else if (nClassID == GBCLASSID_SETS)
// 	{
// 		m_pSets = new CSets;
// 		return m_pSets;
// 	}
// 	else if (nClassID == GBCLASSID_BINARYINS)
// 	{
// 		m_pBinaryIns = new CBinaryIns;
// 		return m_pBinaryIns;
// 	}
// 	else if (nClassID == GBCLASSID_BINARYOUTS)
// 	{
// 		m_pBinaryOuts = new CBinaryOuts ;
// 		return m_pBinaryOuts;
// 	}
// 	else if (nClassID == GBCLASSID_SOFTSWITCHS)
// 	{
// 		m_pSoftSwitchs = new CSoftSwitchs;
// 		return m_pSoftSwitchs;
// 	}
// 	else if (nClassID ==  GBCLASSID_CTRLWORDS)
// 	{
// 		m_pCtrlWords = new CCtrlWords;
// 		return m_pCtrlWords;
// 	}
// 	else if (nClassID ==  GBCLASSID_SOES)
// 	{
// 		m_pSoes = new CSoes;
// 		return m_pSoes;
// 	}
// 	else
	if (nClassID ==  GBCLASSID_REPORT)
	{
		m_pReport = new CReport;
		return m_pReport;
	}
	else if (nClassID ==  GBCLASSID_DATASET)
	{
		return new CDataSet;
	}
	else if (nClassID ==  GBCLASSID_DATASETGROUP)
	{
		return new CDataSetGroup;
	}

	return NULL;
}

CBaseObject* CCpu::Clone()
{
	CCpu* pCpu = new CCpu();
	Copy(pCpu);

	return pCpu;
}

CBaseObject* CCpu::CloneEx(BOOL bCopyOwn/*=TRUE*/,BOOL bCopyChildren/*=FALSE*/)
{
	CCpu *p = new CCpu();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CCpu::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	if (m_pLogCtrls != NULL)
	{
		m_pLogCtrls->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

void CCpu::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch(nClassID)
		{
// 		case GBCLASSID_ANALOGS:
// 			m_pAnalogs = (CAnalogs*)p;
// 			m_pAnalogs->m_strID = m_strID;
// 			break;
// 		case GBCLASSID_SETS:
// 			m_pSets = (CSets*)p;
// 			m_pSets->m_strID = m_strID;
// 			break;
// 		case GBCLASSID_CTRLWORDS:
// 			m_pCtrlWords = (CCtrlWords*)p;
// 			m_pCtrlWords->m_strID = m_strID;
// 			break;
// 		case GBCLASSID_SOFTSWITCHS:
// 			m_pSoftSwitchs = (CSoftSwitchs*)p;
// 			m_pSoftSwitchs->m_strID = m_strID;
// 			break;
// 		case GBCLASSID_BINARYINS:
// 			m_pBinaryIns = (CBinaryIns*)p;
// 			m_pBinaryIns->m_strID = m_strID;
// 			break;
// 		case GBCLASSID_BINARYOUTS:
// 			m_pBinaryOuts = (CBinaryOuts*)p;
// 			m_pBinaryOuts->m_strID = m_strID;
// 			break;
// 		case GBCLASSID_SOES:
// 			m_pSoes = (CSoes*)p;
// 			m_pSoes->m_strID = m_strID;
// 			break;
		case GBCLASSID_REPORTS:
			m_pReport = (CReport*)p;
			break;
		}
	}	


#ifdef _use_device_model_ds
	TransToDataSet();
#else
// 	if (m_pAnalogs == NULL)
// 	{
// 		m_pAnalogs = new CAnalogs();
// 		AddNewChild(m_pAnalogs);
// 	}
// 
// 	if (m_pSets == NULL)
// 	{
// 		m_pSets = new CSets();
// 		AddNewChild(m_pSets);
// 	}
// 
// 	if (m_pCtrlWords == NULL)
// 	{
// 		m_pCtrlWords = new CCtrlWords();
// 		AddNewChild(m_pCtrlWords);
// 	}
// 
// 	if (m_pSoftSwitchs == NULL)
// 	{
// 		m_pSoftSwitchs = new CSoftSwitchs();
// 		AddNewChild(m_pSoftSwitchs);
// 	}
// 
// 	if (m_pBinaryIns == NULL)
// 	{
// 		m_pBinaryIns = new CBinaryIns();
// 		AddNewChild(m_pBinaryIns);
// 	}
// 
// 	if (m_pBinaryOuts == NULL)
// 	{
// 		m_pBinaryOuts = new CBinaryOuts();
// 		AddNewChild(m_pBinaryOuts);
// 	}
// 
// 	if (m_pSoes == NULL)
// 	{
// 		m_pSoes = new CSoes();
// 		AddNewChild(m_pSoes);
// 	}

	if (m_pReport == NULL)
	{
		m_pReport = new CReport;
		AddNewChild(m_pReport);
	}
#endif

	//2018-03-05
	if (m_pLogCtrls != NULL)
	{
		m_pLogCtrls->m_strName = m_strName;
		m_pLogCtrls->m_strID = m_strID;
	}
}

void CCpu::TransToDataSet()
{
	CDataSet *pDataSet = NULL;

// 	if (m_pBinaryOuts != NULL)
// 	{
// 		pDataSet = new CDataSet();
// 		m_pBinaryIns->InitDataSet(pDataSet);
// 		pDataSet->m_strName = g_strDataSetID[DSID_dsDout];
// 		pDataSet->m_strID = g_strDataSetID[DSID_dsDout];
// 		pDataSet->m_strType = g_strDataSetID[DSID_dsDout];
// 		AddNewChild(pDataSet);
// 		Delete(m_pBinaryOuts);
// 		m_pBinaryOuts = NULL;
// 	}
// 
// 	if (m_pBinaryIns != NULL)
// 	{
// 		pDataSet = new CDataSet();
// 		m_pBinaryIns->InitDataSet(pDataSet);
// 		pDataSet->m_strName = g_strDataSetID[DSID_dsDin];
// 		pDataSet->m_strID = g_strDataSetID[DSID_dsDin];
// 		pDataSet->m_strType = g_strDataSetID[DSID_dsDin];
// 		AddNewChild(pDataSet);
// 		Delete(m_pBinaryIns);
// 		m_pBinaryIns = NULL;
// 	}
// 
// 	if (m_pSoftSwitchs != NULL)
// 	{
// 		pDataSet = new CDataSet();
// 		m_pSoftSwitchs->InitDataSet(pDataSet);
// 		pDataSet->m_strName = g_strDataSetName[DSID_dsEna];
// 		pDataSet->m_strID = g_strDataSetID[DSID_dsEna];
// 		pDataSet->m_strType = g_strDataSetID[DSID_dsEna];
// 		AddNewChild(pDataSet);
// 		Delete(m_pSoftSwitchs);
// 		m_pSoftSwitchs = NULL;
// 	}
// 
// 	if (m_pCtrlWords != NULL)
// 	{
// 		pDataSet = new CDataSet();
// 		m_pCtrlWords->InitDataSet(pDataSet);
// 		pDataSet->m_strName = g_strDataSetName[DSID_dsEna];
// 		pDataSet->m_strID = g_strDataSetID[DSID_dsEna];
// 		pDataSet->m_strType = g_strDataSetID[DSID_dsEna];
// 		AddNewChild(pDataSet);
// 		Delete(m_pCtrlWords);
// 		m_pCtrlWords = NULL;
// 	}
// 
// 	if (m_pSets != NULL)
// 	{
// 		pDataSet = new CDataSet();
// 		m_pSets->InitDataSet(pDataSet);
// 		pDataSet->m_strName = g_strDataSetName[DSID_dsSetting];
// 		pDataSet->m_strID = g_strDataSetID[DSID_dsSetting];
// 		pDataSet->m_strType = g_strDataSetID[DSID_dsSetting];
// 		AddNewChild(pDataSet);
// 		Delete(m_pSets);
// 		m_pSets = NULL;
// 	}
// 
// 	if (m_pAnalogs != NULL)
// 	{
// 		pDataSet = new CDataSet();
// 		m_pAnalogs->InitDataSet(pDataSet);
// 		pDataSet->m_strName = g_strDataSetName[DSID_dsAin];
// 		pDataSet->m_strID = g_strDataSetID[DSID_dsAin];
// 		pDataSet->m_strType = g_strDataSetID[DSID_dsAin];
// 		AddNewChild(pDataSet);
// 		Delete(m_pAnalogs);
// 		m_pAnalogs = NULL;
// 	}
}

CReport* CCpu::GetReport()
{
	if (m_pReport == NULL)
	{
		m_pReport = new CReport;
	}

	CValues *pValues = m_pReport->m_pValues;
	pValues->DeleteAll();
// 	POS pos = m_pAnalogs->GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		CExBaseObject* pObj = m_pAnalogs->GetNext(pos);
// 		pValues->AddNew(pObj->m_strID,_T("0"));
// 	}

	Gb_AddResultJudgeKey(pValues,0);

	return m_pReport;
}



long CCpu::GetDataSet(const CString &strType, CExBaseList &oListDataSet, CDataSet **pDataSet)
{
//	oListDataSet.RemoveAll();
	POS pos = GetHeadPosition();
	CDataSet *p = NULL;

	if (strType.GetLength() <= 1 || strType == _T("all") )
	{
		while (pos != NULL)
		{
			p = (CDataSet *)GetNext(pos);
			oListDataSet.AddTail(p);
		}
	}
	else if (strType == _T("log"))
	{
		if (m_pLogCtrls != NULL)
		{
			oListDataSet.Append(m_pLogCtrls);
		}
	}
	else
	{
		while (pos != NULL)
		{
			p = (CDataSet *)GetNext(pos);

			if (p->m_strID.Find(strType) >= 0)
			{
				if (oListDataSet.Find(p) == NULL)
				{
					oListDataSet.AddTail(p);
				}
			}
		}
	}

	long nCount = oListDataSet.GetCount();

	if (pDataSet != NULL)
	{
		if (nCount == 1)
		{
			*pDataSet = (CDataSet *)oListDataSet.GetHead();
		}
		else
		{
			*pDataSet = NULL;
		}
	}

	return nCount;
}
/*
CExBaseObject *pObj = NULL;
POS pos = GetHeadPosition();
CString strTemp;

while (pos != NULL)
{
pObj = GetNext(pos);

if (strIDPath.CompareNoCase(pObj->m_strID) == 0)
{
oListDest.AddTail(pObj);
}
else
{
if (pObj->IsBaseList())
{
strTemp = pObj->m_strID + strSeperator;

if (str_n_compare(strTemp, strIDPath, strTemp.GetLength()) == 0)
{
strTemp = strIDPath.Mid(strTemp.GetLength());
((CExBaseList*)pObj)->SelectDatas(strTemp, oListDest, strSeperator);
}

}
else
{
if (pObj->m_strID == strIDPath)
{
oListDest.AddTail(pObj);
}
}
}
}*/

//shaolei 20220330
//模型替换时，根据数据集路径过滤，暂时只考虑CDataset部分
long CCpu::SelectDatas_FilterByPath(const CString &strDatasetPath, const CString &strIDPath, CExBaseList &oListDest, const CString &strSeperator)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();
		
		if (nClassID != GBCLASSID_DATASET)
		{
			continue;
		}

		CDataSet *pDataSet = (CDataSet *)pObj;

		if (strDatasetPath.Find(pDataSet->m_strID) < 0)
		{
			continue;
		}

		pDataSet->SelectDatas(strIDPath, oListDest, strSeperator);
	}

	return oListDest.GetCount();
}

CDataSet* CCpu::GetDataSet(const CString &strType)
{
	POS pos = GetHeadPosition();
	CDataSet *p = NULL;
	CDataSet *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDataSet *)GetNext(pos);

		if (p->m_strID == strType)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}


CDataSet* CCpu::GetDataSetByKey(const CString &strKey)
{
	POS pos = GetHeadPosition();
	CDataSet *p = NULL;
	CDataSet *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDataSet *)GetNext(pos);

		if (p->m_strID.Find(strKey) >= 0)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

BOOL CCpu::GetAllDatasByDatasetKey(CDataSet *pDatasetRef,const CString &strKey)
{
	POS pos = GetHeadPosition();
	CDataSet *p = NULL;
	CDataSet *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDataSet *)GetNext(pos);

		if (p->GetClassID() != GBCLASSID_DATASET)
		{
			continue;
		}

		if (p->m_strID.Find(strKey) >= 0)
		{
			pDatasetRef->Append(p);
		}
	}

	return TRUE;
}


CExBaseList* CCpu::GetDeviceModelDatasById(const CString &strDeviceModelTypeID)
{
// 	if (strDeviceModelTypeID == g_strDeviceModel_Sets)
// 	{
// 		return m_pSets;
// 	}
// 	else if (strDeviceModelTypeID == g_strDeviceModel_SoftSwitchs)
// 	{
// 		return m_pSoftSwitchs;
// 	}
// 	else if (strDeviceModelTypeID == g_strDeviceModel_Analogs)
// 	{
// 		return m_pAnalogs;
// 	}
// 	else if (strDeviceModelTypeID == g_strDeviceModel_BinaryOuts)
// 	{
// 		return m_pBinaryOuts;
// 	}
// 	else
	{
		return NULL;
	}
}


CExBaseList* CCpu::GetDeviceModelDatasById(const CString &strCpuID, const CString &strDeviceModelTypeID)
{
	if (strCpuID != m_strID)
	{
		return NULL;
	}

	return GetDeviceModelDatasById(strDeviceModelTypeID);
}

// CSet* CCpu::FindBySetName(const CString &strName)
// {
// 	CSet *pSet = NULL;
// 	CSet *pFind = NULL;
// 	POS pos = m_pSets->GetHeadPosition();
// 	CString strTemp;
// 
// 	while (pos != NULL)
// 	{
// 		pSet = (CSet *)m_pSets->GetNext(pos);
// 		Gb_GetSetName(strTemp, pSet);
// 
// 		if (strTemp == strName)
// 		{
// 			pFind = pSet;
// 			break;
// 		}
// 	}
// 
// 	return pFind;
// }


CDataObj* CCpu::FindDataObjByName(const CString &strName)
{
	CDataSet *pDataSet = NULL;
	POS pos = GetHeadPosition();
	CDataObj *pFind = NULL;

	while (pos != NULL)
	{
		pDataSet = (CDataSet *)GetNext(pos);
		pFind = (CDataObj *)pDataSet->FindByName(strName);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

CDataObj* CCpu::FindDataObjByID(const CString &strID)
{
	CDataSet *pDataSet = NULL;
	POS pos = GetHeadPosition();
	CDataObj *pFind = NULL;

	while (pos != NULL)
	{
		pDataSet = (CDataSet *)GetNext(pos);
		pFind = (CDataObj *)pDataSet->FindByID(strID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

long CCpu::FindDataObjByID(const CString &strID, CExBaseList &listDatas)
{
	CDataSet *pDataSet = NULL;
	POS pos = GetHeadPosition();
	CDataObj *pFind = NULL;

	while (pos != NULL)
	{
		pDataSet = (CDataSet *)GetNext(pos);
		pFind = (CDataObj *)pDataSet->FindByID(strID);

		if (pFind != NULL)
		{
			listDatas.AddTail(pFind);
		}
	}

	return listDatas.GetCount();
}


CDataObj* CCpu::FindDataObjByID_Has(const CString &strID)
{
	CDataSet *pDataSet = NULL;
	POS pos = GetHeadPosition();
	CDataObj *pFind = NULL;

	while (pos != NULL)
	{
		pDataSet = (CDataSet *)GetNext(pos);
		pFind = (CDataObj *)pDataSet->FindDataObjByID_Has(strID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

long CCpu::FindDataObjByID_Has(const CString &strID, CExBaseList &listDatas)
{
	CDataSet *pDataSet = NULL;
	POS pos = GetHeadPosition();
	CDataObj *pFind = NULL;

	while (pos != NULL)
	{
		pDataSet = (CDataSet *)GetNext(pos);
		pFind = (CDataObj *)pDataSet->FindDataObjByID_Has(strID);

		if (pFind != NULL)
		{
			listDatas.AddTail(pFind);
		}
	}

	return listDatas.GetCount();
}


void CCpu::ResetDvmValue()
{
	POS pos = GetHeadPosition();
	CDataSet *p = NULL;

	while (pos != NULL)
	{
		p = (CDataSet *)GetNext(pos);
		p->ResetDvmValue();
	}
}

void CCpu::GetDataObjsByNameHas(const CString &strDsIDHas, const CString &strDataNameHas, CExBaseList *pList)
{
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_DATASET)
		{
			//暂时只考虑CDataSet
			continue;
		}

		if (pObj->m_strID.Find(strDsIDHas) < 0)
		{
			continue;
		}

		CDataSet *pDataSet = (CDataSet *)pObj;
		pDataSet->GetDataObjsByNameHas(strDataNameHas, pList);
	}
}	

//模型更新  shaolei 20220716
void CCpu::UpdateDataSetValue(CCpu *pSrcCpu, BOOL bNewNotExist)
{
	POS pos = pSrcCpu->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CDataSet *pSrcDataSet = NULL;
	CDataSet *pDstDataSet = NULL;
	CString strSrcID;

	while (pos != NULL)
	{
		pObj = pSrcCpu->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_DATASET)
		{
			//暂时只考虑CDataSet
			continue;
		}

		pSrcDataSet = (CDataSet *)pObj;
		strSrcID = pSrcDataSet->m_strID;
		pDstDataSet = (CDataSet *)FindByID(strSrcID);

		if (pDstDataSet == NULL)
		{
			if (bNewNotExist)
			{
				pDstDataSet = (CDataSet *)pSrcDataSet->CloneEx(TRUE,TRUE);
				AddNewChild(pDstDataSet);
				continue;
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("设备数据模型更新，数据集【%s】未找到"), strSrcID.GetString());
				continue;
			}
		}
		else
		{
			pDstDataSet->UpdateDataObjValue(pSrcDataSet, bNewNotExist);
		}
	}
}

void Gb_GetDeviceParaDataPath(CExBaseObject *pData, CString &strPath)
{
	CCpu *pCpu = (CCpu*)pData->GetAncestor(GBCLASSID_CPU);

	if (pCpu == NULL)
	{
        strPath.Format(_T("/%s"), pData->m_strID.GetString());
	}
	else
	{
        strPath.Format(_T("%s/%s"), pCpu->m_strID.GetString(), pData->m_strID.GetString());
	}
}

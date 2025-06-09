#include "stdafx.h"
#include "SysParaEditGroupMngr.h"

//////////////////////////////////////////////////////////////////////////
//CSysParaEditGroups

CSysParaEditGroup::CSysParaEditGroup()
{
	m_nClassID = 0;
	m_pObjectRef = NULL;
}


CSysParaEditGroup::~CSysParaEditGroup()
{
	
}

long CSysParaEditGroup::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CSysParaEditGroup::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,CGbXMLKeys::g_pGbXMLKeys);

	return 0;
}

long CSysParaEditGroup::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,CGbXMLKeys::g_pGbXMLKeys);

	return 0;
}

CExBaseObject* CSysParaEditGroup::CreateNewChild(long nClassID)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == GBCLASSID_SET)
	{
		pNew = new CSet;
	}
	else if (nClassID == DTMCLASSID_CSHORTDATA)
	{
		pNew = new CShortData();
	}

	return pNew;
}

CExBaseObject* CSysParaEditGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew = NULL;
	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strSetKey)
	{
		pNew = new CSet;
	}
	else if (strClassID == pXmlKeys->CShortDataKey())
	{
		pNew = new CShortData();
	}

	return pNew;
}


void CSysParaEditGroup::Release(BOOL bDatasIsRef)
{
	if (bDatasIsRef)
	{
		RemoveAll();
	}
	else
	{
		DeleteAll();
	}
}

void CSysParaEditGroup::AddToValues(CValues *pValues)
{
	if (m_nClassID == GBCLASSID_SETS)
	{
		AddToValues_Sets(pValues);
	}
	else
	{
		AddToValues_Datas(pValues);
	}
}

void CSysParaEditGroup::InitValues(CSysParaEditGroup *pSrcGroup)
{
	if (pSrcGroup == NULL)
	{
		return;
	}

	if (m_nClassID == GBCLASSID_SETS)
	{
		InitValues_Sets(pSrcGroup);
	}
	else
	{
		InitValues_Datas(pSrcGroup);
	}
}

void CSysParaEditGroup::AddToValues_Sets(CValues *pValues)
{
	POS pos = GetHeadPosition();
	CSet *pSet = NULL;

	while (pos != NULL)
	{
		pSet = (CSet *)GetNext(pos);
		pValues->AddValue(pSet->m_strID, pSet->m_strValue);
	}
}

void CSysParaEditGroup::AddToValues_Datas(CValues *pValues)
{
	POS pos = GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)GetNext(pos);
		pValues->AddValue(pData->m_strID, pData->m_strValue);
	}
}

void CSysParaEditGroup::InitValues_Sets(CSysParaEditGroup *pSrcGroup)
{
	POS pos = GetHeadPosition();
	CSet *pSet = NULL;
	CSet *pFind = NULL;

	while (pos != NULL)
	{
		pSet = (CSet *)GetNext(pos);
		pFind = (CSet *)pSrcGroup->FindByID(pSet->m_strID);

		if (pFind != NULL)
		{
			pSet->m_strValue = pFind->m_strValue;
		}
	}
}

void CSysParaEditGroup::InitValues_Datas(CSysParaEditGroup *pSrcGroup)
{
	POS pos = GetHeadPosition();
	CShortData *pData = NULL;
	CShortData *pFind = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)GetNext(pos);
		pFind = (CShortData *)pSrcGroup->FindByID(pData->m_strID);

		if (pFind != NULL)
		{
			pData->m_strValue = pFind->m_strValue;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//CSysParaEditGroups

CSysParaEditGroups::CSysParaEditGroups()
{
	m_pValues = NULL;
	m_pSysParaEdit = NULL;
}


CSysParaEditGroups::~CSysParaEditGroups()
{
	if (m_pValues != NULL)
	{
		delete m_pValues;
		m_pValues = NULL;
	}
}

long CSysParaEditGroups::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CSysParaEditGroups::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,CGbXMLKeys::g_pGbXMLKeys);

	return 0;
}

long CSysParaEditGroups::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,CGbXMLKeys::g_pGbXMLKeys);

	return 0;
}

CExBaseObject* CSysParaEditGroups::CreateNewChild(long nClassID)
{
	CExBaseObject *pNew = NULL;

	if (nClassID == GBCLASSID_SYSPARAEDITGROUP)
	{
		pNew = new CSysParaEditGroup;
	}

	return pNew;
}

CExBaseObject* CSysParaEditGroups::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew = NULL;

	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strSysParaEditGroupKey)
	{
		pNew = new CSysParaEditGroup;
	}

	return pNew;
}

void CSysParaEditGroups::InitSysParaEditGroups(CSysParaEdit *pSysParaEdit)
{
	DeleteAll();
	m_pSysParaEdit = pSysParaEdit;
	CString strType = m_pSysParaEdit->GetDatasetPath();

	if(strType == g_strrSets || strType == g_strrSoftswitchs || strType == g_strrCtrlWords
		|| strType == g_strwSets || strType == g_strwSoftswitchs || strType == g_strwCtrlWords)
	{
		InitMngr();
		InitMngrDatas_Sets(strType);
	}
	else// if(m_strType == g_strwSysPara)else if(m_strType == g_strwTestPara)
	{
		InitMngrDatas_ShortDatas(strType);
	}
}

void CSysParaEditGroups::Release(BOOL bDatasIsRef)
{
	CSysParaEditGroup *pGroup = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pGroup = (CSysParaEditGroup *)GetNext(pos);
		pGroup->Release(bDatasIsRef);
	}

	DeleteAll();
}

CValues* CSysParaEditGroups::GetReportValues()
{
	if (m_pValues == NULL)
	{
		m_pValues = new CValues();
	}

	m_pValues->DeleteAll();

	CSysParaEditGroup *pGroup = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pGroup = (CSysParaEditGroup *)GetNext(pos);
		pGroup->AddToValues(m_pValues);
	}

	return m_pValues;
}

void CSysParaEditGroups::InitValues(CSysParaEditGroups *pSrcGroups)
{
	CSysParaEditGroup *pFind = NULL;
	CSysParaEditGroup *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSysParaEditGroup *)GetNext(pos);
		pFind = (CSysParaEditGroup *)pSrcGroups->FindByID(p->m_strID);
		p->InitValues(pFind);
	}
}

void CSysParaEditGroups::InitMngr()
{
	CDevice *pCurDevice = (CDevice*)m_pSysParaEdit->GetAncestor(GBCLASSID_DEVICE);
	ASSERT(pCurDevice != NULL);
	CCpus* pCpus = pCurDevice->GetCpus();
	CCpu* pCpu = NULL;
	POS pos = pCpus->GetHeadPosition();

	while (pos != NULL)
	{
		pCpu = (CCpu*)pCpus->GetNext(pos);
		CSysParaEditGroup *pNew = new CSysParaEditGroup();
		pNew->m_strName = pCpu->m_strName;
		pNew->m_strID = pCpu->m_strID;
		pNew->m_nClassID = GBCLASSID_SETS;
		AddNewChild(pNew);
	}
}

void CSysParaEditGroups::InitMngrDatas_Sets(const CString &strType)
{
	CDevice *pCurDevice = (CDevice*)m_pSysParaEdit->GetAncestor(GBCLASSID_DEVICE);
	CCpus* pCpus = pCurDevice->GetCpus();
	CValues * pValues = m_pSysParaEdit->GetParas();
	CValue * pValue = NULL;
	CCpu* pCpu = NULL;
	CExBaseList *pList = NULL;
	POS pos = NULL;
	long nIndex = 0;
	CSet *pSet = NULL;

	if (pValues->GetCount() == 0)
	{//全部定值数据
		pos = pCpus->GetHeadPosition();

		while (pos != NULL)
		{
			pCpu = (CCpu*)pCpus->GetNext(pos);
			pList = (CExBaseList*)FindByID(pCpu->m_strID);

			if (pList != NULL)
			{
				pList->Append(pCpu->GetSets());
			}
		}

		return;
	}

	pos = pValues->GetHeadPosition();

	while (pos != NULL)
	{
		pValue = (CValue *)pValues->GetNext(pos);
		pCpu = pCpus->GetCpu(pValue->m_strID);

		if(pCpu != NULL)
		{
			pList = (CExBaseList*)FindByID(pCpu->m_strID);

			if (pList == NULL)
			{
				continue;
			}

			pSet = SelectSet(strType, pCpus, pValue->m_strID, pList);

			if(pSet != NULL)
			{
				pSet->m_dwItemData = (DWORD)pValue;
			}
		}
	}

	pos = GetHeadPosition();
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		pList = (CExBaseList*)GetNext(pos);

		if (pList->GetCount() == 0)
		{
			RemoveAt(posPrev);
			delete pList;
		}
	}
}

CSet* CSysParaEditGroups::SelectSet(const CString &strType, CCpus *pCpus, const CString &strPath, CExBaseList *pList)
{
	CSet *pSet = NULL;

	if(strType == g_strrSets || strType == g_strwSets)
	{
		pSet = pCpus->SelectSet(strPath);
	}
	else if(strType == g_strrSoftswitchs || strType == g_strwSoftswitchs)
	{
		pSet = pCpus->SelectSoftSwitch(strPath);
	}
	else if(strType == g_strrCtrlWords || strType == g_strwCtrlWords)
	{
		pSet = pCpus->SelectCtrlWord(strPath);
	}

	if(pSet != NULL)
	{
		pList->AddTail(pSet);
	}

	return pSet;
}

void CSysParaEditGroups::InitMngrDatas_ShortDatas(const CString &strType)
{
// 	CShortDatas *pDatas = NULL;
// 	CShortData *pData = NULL;
// 	CSysParaEditGroup *pSysParaEditGroup = NULL;
// 	CDevice *pCurDevice = (CDevice*)m_pSysParaEdit->GetAncestor(GBCLASSID_DEVICE);
// 
// 	if(strType == g_strwSysPara)
// 	{
// 		pSysParaEditGroup = AddNewGroup(_T("系统参数编辑"), strType, GBCLASSID_DEVICE_SYSPARAS);
// 		pDatas = pCurDevice->GetSysParas()->GetDatas();
// 	}
// 	else// if(m_strType == g_strwTestPara)
// 	{
// 		pSysParaEditGroup = AddNewGroup(_T("试验参数编辑"), strType, GBCLASSID_DEVICE_SYSPARAS);
// 		pDatas = pCurDevice->GetTestParas()->GetDatas();
// 	}
// 
// 	CValues * pValues = m_pSysParaEdit->GetParas();
// 	CValue * pValue = NULL;
// 
// 	if (pValues->GetCount() == 0)
// 	{
// 		pSysParaEditGroup->Append(pDatas);
// 	}
// 	else
// 	{
// 		POS pos = pValues->GetHeadPosition();
// 
// 		while (pos != NULL)
// 		{
// 			pValue = (CValue *)pValues->GetNext(pos);
// 			pData = (CShortData *)pDatas->FindByID(pValue->m_strID);
// 			pSysParaEditGroup->AddTail(pData);
// 			pData->m_dwItemData = (DWORD)pValue;
// 		}
// 	}
}

CSysParaEditGroup* CSysParaEditGroups::AddNewGroup(const CString &strName, const CString &strID, UINT nClassID)
{
	CSysParaEditGroup *pNew = new CSysParaEditGroup();
	pNew->m_strName = strName;
	pNew->m_strID = strID;
	pNew->m_nClassID = nClassID;
	AddNewChild(pNew);
	return pNew;
}


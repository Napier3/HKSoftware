#include "StdAfx.h"
#include "PpPackage.h"
#include "ProtocolXmlRWKeys.h"
#include "PpTtPackage.h"
#include "PpTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpPackage::CPpPackage(void)
{
	m_pDataInterface = NULL;
	m_pVariables = NULL;
	m_pInitScript = NULL;
	m_pEndScript = NULL;
	m_pTtPackage = NULL;
	m_nPkgLen = 0;
	m_nPkgNum = 0;
#ifdef _PP_DEV_MODE_
	m_pPpPackageText = NULL;
	m_pPpPackageTexts = NULL;
#endif

	m_bValid = TRUE;
}

CPpPackage::~CPpPackage(void)
{
	m_oAllVariables.RemoveAll();
	m_oDataQuery.DeleteAll();
}

long CPpPackage::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKeys->m_stT_IDKey, oNode, m_strTID);

	return 0;
}

long CPpPackage::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	xml_SetAttributeValue(((CProtocolXmlRWKeys*)pXmlRWKeys)->m_stT_IDKey, oElement, m_strTID);
	
	return 0;
}

CExBaseObject* CPpPackage::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey)
	{
		m_pDataInterface = new CBbVariables(strClassID);
		return m_pDataInterface;
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey)
	{
		m_pInitScript = new CPpScript(strClassID);
		return m_pInitScript;
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strEndScriptKey)
	{
		m_pEndScript = new CPpScript(strClassID);
		return m_pEndScript;
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVarialblesKey)
	{
		m_pVariables = new CBbVariables(strClassID);
		return m_pVariables;
	}

#ifdef _PP_DEV_MODE_
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageTextKey)
	{
		m_pPpPackageText = new CPpPackageText();
		return m_pPpPackageText;
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageTextsKey)
	{
		m_pPpPackageTexts = new CPpPackageTexts();
		return m_pPpPackageTexts;
	}
#endif

	return NULL;
}

CExBaseObject* CPpPackage::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{

	return NULL;
} 

/*
		2010-12-15 添加
		验证m_pTtPackage是否有效
*/
BOOL CPpPackage::VerifyTtPackage()
{
// 	if(m_pTtPackage == NULL)
// 	{
// 		return FALSE;
// 	}

	CPpTemplate* pPpTemplate = (CPpTemplate*)this->GetAncestor(PPCLASSID_PPTEMPLATE);
	if(pPpTemplate != NULL)
	{
		if(pPpTemplate->m_pPackages != NULL)
		{
			m_pTtPackage = (CPpTtPackage*)pPpTemplate->m_pPackages->FindByID(m_strTID);

			if (m_pTtPackage != NULL)
			{
				if (m_pTtPackage->GetClassID() != PPCLASSID_PPTTPACKAGE)
				{
					m_pTtPackage = NULL;
				}
				else
				{
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

void CPpPackage::InitTtPackage()
{
	CPpTemplate* pPpTemplate = (CPpTemplate*)this->GetAncestor(PPCLASSID_PPTEMPLATE);

	if(pPpTemplate != NULL)
	{
		if(pPpTemplate->m_pPackages != NULL)
		{
			m_pTtPackage = (CPpTtPackage*)pPpTemplate->m_pPackages->FindByID(m_strTID);
		

			if (m_pTtPackage != NULL)
			{
				if (m_pTtPackage->GetClassID() != PPCLASSID_PPTTPACKAGE)
				{
					m_pTtPackage = NULL;
				}
				else
				{
					m_pTtPackage->m_listPackages.AddTail(this);
				}
			}
		}
	}
}

#ifdef _DVM_VALUE_USE_CHAR_
void CPpPackage::GetTmString(wchar_t *strTm)
{
    swprintf(strTm, _T("%d-%d-%d %d:%d:%d %d"), m_tm.wYear, m_tm.wMonth, m_tm.wDay
		, m_tm.wHour, m_tm.wMinute, m_tm.wSecond, m_tm.wMilliseconds);
}
#endif

void CPpPackage::InitAfterRead()
{
	//初始化m_pDataInterface等子对象指针
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject*)GetNext(pos);

		UINT nClassID = p->GetClassID();

		switch (nClassID)
		{
		case PPCLASSID_BBVARIABLES:
			{
				CBbVariables *pVariables = (CBbVariables*)p;

				if (pVariables->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey)
				{
					m_pDataInterface = pVariables;
				}
				else if (pVariables->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVariablesKey)
				{
					m_pVariables = pVariables;
				}
				else
				{

				}
			}

			break;
			
		case PPCLASSID_PPSCRIPT:
			{
				CPpScript *pScript = (CPpScript*)p;

				if (pScript->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strEndScriptKey)
				{
					m_pEndScript = pScript;
				}
				else if(pScript->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey)
				{
					m_pInitScript = pScript;
				}
			}
			break;

#ifdef _PP_DEV_MODE_
		case PPCLASSID_PPPAKAGE_TEXT:
			m_pPpPackageText = (CPpPackageText *)p;
			break;

		case PPCLASSID_PPPAKAGE_TEXTS:
			m_pPpPackageTexts = (CPpPackageTexts *)p;
			break;
#endif
		default:
			break;
		}
	}

#ifdef _PP_DEV_MODE_
	if (m_pPpPackageTexts == NULL)
	{
		m_pPpPackageTexts = new CPpPackageTexts();
		AddNewChild(m_pPpPackageTexts);
	}

	if (m_pPpPackageText != NULL)
	{
		m_pPpPackageText->SetParent(m_pPpPackageTexts);
		m_pPpPackageTexts->AddHead(m_pPpPackageText);
		Remove(m_pPpPackageText);
	}

#endif
	//InitOwnAllVariables(TRUE);
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpPackage::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	return CExBaseList::IsEqualOwn(pObj);
}

CBaseObject* CPpPackage::Clone()
{
	CPpPackage* pNew = new CPpPackage();
	Copy(pNew);

	pNew->InitTtPackage();
	pNew->InitOwnAllVariables(TRUE);

	return pNew;
}

BOOL CPpPackage::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpPackage*)pDest)->m_strTID = m_strTID;

	return CExBaseList::CopyOwn(pDest);
}

#ifdef _PP_DEV_MODE_
CPpPackageText* CPpPackage::GetPackageText()
{
	if (m_pPpPackageText != NULL)
	{
		return m_pPpPackageText;
	}

	m_pPpPackageText = (CPpPackageText*)m_pPpPackageTexts->GetHead();

	if (m_pPpPackageText == NULL)
	{
		m_pPpPackageText = new CPpPackageText();
		m_pPpPackageTexts->AddNewChild(m_pPpPackageText);
	}

	return m_pPpPackageText;
}

CPpPackageTexts* CPpPackage::GetPackageTexts()
{
	if (m_pPpPackageTexts != NULL)
	{
		return m_pPpPackageTexts;
	}

	m_pPpPackageTexts = new CPpPackageTexts();
	AddNewChild(m_pPpPackageTexts);
	return m_pPpPackageTexts;
}
#endif

void CPpPackage::GetAllVariables(CExBaseList &oDestList)
{
	if (m_pDataInterface != NULL)
	{
		oDestList.Append(*m_pDataInterface);
	}

	if (m_pVariables != NULL)
	{
		oDestList.Append(*m_pVariables);
	}

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (PpIsByteBlock(p))
		{
			CByteBlock *pByteBlock = (CByteBlock*)p;
			pByteBlock->GetAllVariables(oDestList);
		}
// 		else if (PpIsByteBlock(p))
// 		{
// 			CByteBlocks *pByteBlocks = (CByteBlocks*)p;
// 			pByteBlocks->GetAllVariables(oDestList);
// 		}
		else
		{
		}
	}
}

void CPpPackage::GetDataInterface(CExBaseList &oDestList)
{
	if (m_pDataInterface != NULL)
	{
		m_pDataInterface->Append(oDestList);
	}
	
	//验证m_pTtPackage是否有效
	VerifyTtPackage();

	if (m_pTtPackage != NULL)
	{
		m_pTtPackage->GetDataInterface(oDestList);
	}

}

long CPpPackage::InitOwnAllVariables(BOOL bIncludeTtPkg)
{
	m_oAllVariables.RemoveAll();
	GetAllVariables(m_oAllVariables);

	if (bIncludeTtPkg)
	{
		//验证m_pTtPackage是否有效
		VerifyTtPackage();

		if (m_pTtPackage != NULL)
		{
			m_pTtPackage->GetAllVariables(m_oAllVariables);
		}
	}

	return m_oAllVariables.GetCount();
}

void PpCloneBbVariables(CBbVariables *pVariablesSrc, CExBaseList &oDestList)
{
	if (pVariablesSrc == NULL)
	{
		return;
	}

	POS pos = pVariablesSrc->GetHeadPosition();
	CBbVariable *pVariable = NULL;
	CBbVariable *pNew = NULL;
	CString strTemp;

	while (pos != NULL)
	{
		pVariable = (CBbVariable*)pVariablesSrc->GetNext(pos);
		pNew = (CBbVariable*)pVariable->Clone();
		oDestList.AddTail(pNew);
	}
}

void CPpPackage::GetPackageVaraibles(CExBaseList &oDestList, BOOL bClone)
{
	if (bClone)
	{
		PpCloneBbVariables(m_pVariables, oDestList);
		PpCloneBbVariables(m_pDataInterface, oDestList);

		if (m_pTtPackage != NULL)
		{
			PpCloneBbVariables(m_pTtPackage->m_pDataInterface, oDestList);
			PpCloneBbVariables(m_pTtPackage->m_pTtVariables, oDestList);
		}
	}
	else
	{
		if (m_pVariables != NULL)
		{
			m_pVariables->Append(oDestList);
		}

		if (m_pDataInterface != NULL)
		{
			m_pDataInterface->Append(oDestList);
		}

		if (m_pTtPackage != NULL)
		{
			if (m_pTtPackage->m_pTtVariables != NULL)
			{
				m_pTtPackage->m_pTtVariables->Append(oDestList);
			}

			if (m_pTtPackage->m_pDataInterface != NULL)
			{
				m_pTtPackage->m_pDataInterface->Append(oDestList);
			}
		}
	}
	
}

CPpPackage* PpFindPackageByID(const CString &strPackageID, CExBaseObject *pPpData)
{
	CPpPackage *pPackage = NULL;
	CPpTemplate *pTemplate = (CPpTemplate*)pPpData->GetAncestor(PPCLASSID_PPTEMPLATE);

	ASSERT (pTemplate != NULL);

	if (pTemplate == NULL)
	{
		return NULL;
	}

	pPackage = pTemplate->FindPackagebyID(strPackageID);

	return pPackage;
}

CExBaseObject* PpFindPackage(CExBaseObject* pPpData)
{
	UINT nClassID = pPpData->GetClassID();

	if (PPCLASSID_PPPARSEPACKGE == nClassID || PPCLASSID_PPPRODUCEPACKGE== nClassID
		|| PPCLASSID_PPTTPACKAGE == nClassID)
	{
		return pPpData;
	}

	CExBaseObject* pFind = NULL;
	pFind = (CExBaseObject*)pPpData->GetAncestor(PPCLASSID_PPPARSEPACKGE);

	if(pFind == NULL)
	{
		pFind = (CExBaseObject*)pPpData->GetAncestor(PPCLASSID_PPPRODUCEPACKGE);
		if(pFind == NULL)
		{
			pFind = (CExBaseObject*)pPpData->GetAncestor(PPCLASSID_PPTTPACKAGE);
		}
	}

	return pFind;
}

CBbVariable* CPpPackage::FindVariableByName(const CString &strName)
{
	CBbVariable *p = (CBbVariable*)m_oAllVariables.FindByName(strName);
	return p;
}

CBbVariable* CPpPackage::FindVariableByID(const CString &strID)
{
	CBbVariable *p = (CBbVariable*)m_oAllVariables.FindByID(strID);
	return p;
}

BOOL  CPpPackage::GetVariableValue(const CString &strVariable, long &nValue)
{
    if (IsStringNumber(strVariable.GetString()))
	{
#ifdef UNICODE
		nValue = _wtol(strVariable);
#else
        nValue = atol(strVariable.GetString());
#endif
	}
	else
	{
		CBbVariable *p = FindVariableByID(strVariable);

		if (p == NULL)
		{
			nValue = 0;
		}
		else
		{
			GetVariableValue(p->m_strValue, nValue);
		}
	}

	return TRUE;
}

BOOL CPpPackage::GetVariableValue(const CString &strVariable, CString &strValue)
{
	CBbVariable *p = FindVariableByID(strVariable);

	if (p == NULL)
	{
		strValue = L"";
		return FALSE;
	}
	else
	{
		strValue = p->m_strValue;
		return TRUE;
	}
}


BOOL  CPpPackage::SetVariableValue(const CString &strVariable, const  long &nValue)
{
	CBbVariable *p = FindVariableByID(strVariable);

	if (p == NULL)
	{
		return FALSE;
	}
	else
	{
		p->m_strValue.Format(_T("%d"), nValue);
		return TRUE;
	}

}


BOOL  CPpPackage::SetVariableValue(const CString &strVariable, const double &dValue)
{
	CBbVariable *p = FindVariableByID(strVariable);

	if (p == NULL)
	{
		return FALSE;
	}
	else
	{
		p->m_strValue.Format(_T("%f"), dValue);
		return TRUE;
	}
}

BOOL CPpPackage::SetVariableValue(const CString &strVariable, const CString &strValue)
{
	CBbVariable *p = FindVariableByID(strVariable);

	if (p == NULL)
	{
		return FALSE;
	}
	else
	{
		p->m_strValue = strValue;
		return TRUE;
	}
}

/*
2010-12-06 添加
*/
BOOL CPpPackage::AddSystemVariables()
{
	return TRUE;
}

void CPpPackage::RunInitScript()
{
	if (m_pInitScript != NULL)
	{
		m_pInitScript->Run();
	}
}

void CPpPackage::RunEndScript()
{
	if (m_pEndScript != NULL)
	{
		m_pEndScript->Run();
	}
}

CBbVariable* PpFindVariableByID_Pkg(CExBaseObject* pObj, const CString &strID)
{
// 	CExBaseObject* pObj = PpFindPackage(pPpCurrData);
	CPpPackage *pPackage = NULL;
	CPpTtPackage *pTPackage = NULL;

	if (pObj == NULL)
	{
		return NULL;
	}

	CBbVariable* pVariable = NULL;

	if (pObj->GetClassID() == PPCLASSID_PPTTPACKAGE)
	{
		pTPackage = (CPpTtPackage*)pObj;
		pVariable = pTPackage->FindVariableByID(strID);
	}
	else
	{
		pPackage = (CPpPackage*)pObj;
		pVariable = pPackage->FindVariableByID(strID);
	}

	return pVariable;
}

CBbVariable* PpFindVariableByID_Procedure(CExBaseObject* pObj, const CString &strID)
{
	CPpProcedure *pProcedure = (CPpProcedure*)pObj;

	return pProcedure->FindVariableByID(strID);
}

CBbVariable* PpFindVariableByID_Node(CExBaseObject* pObj, const CString &strID)
{
	CPpNode *pNode = (CPpNode*)pObj;

	if (pNode->m_pPackageRef == NULL)
	{
		return NULL;
	}

	CPpPackage *pPackage =  PpFindPackageByID(pNode->m_pPackageRef->m_strPkgID, pNode);

	if (pPackage != NULL)
	{
		return PpFindVariableByID_Pkg(pPackage, strID);
	}
	
	return NULL;
}

//查找Data所在的Package的变量
CBbVariable* PpFindVariableByID(CExBaseObject* pPpCurrData, const CString &strID)
{
	CExBaseObject* pObj = PpFindPackage(pPpCurrData);

	if (pObj != NULL)
	{
		return PpFindVariableByID_Pkg(pObj, strID);
	}


	pObj = (CExBaseObject*)pPpCurrData->GetAncestor(PPCLASSID_PPPROCEDURE);

	if (pObj != NULL)
	{
		CBbVariable *pFind  = PpFindVariableByID_Procedure(pObj, strID);

		if (pFind != NULL)
		{
			return pFind;
		}
	}

#ifdef _PP_DEV_MODE_
	pObj = (CExBaseObject*)pPpCurrData->GetAncestor(PPCLASSID_PPNODE);

	if (pObj != NULL)
	{
		return PpFindVariableByID_Node(pObj, strID);
	}

#endif

	return NULL;
}

void PpUpdatePackageAllVariables(CExBaseObject* pPpCurrData)
{
	CExBaseObject *p = (CExBaseObject*)PpFindPackage(pPpCurrData);
	
	if (p == NULL)
	{
		return;
	}
	
	UINT nClassID = p->GetClassID();
	
	if (nClassID == PPCLASSID_PPPRODUCEPACKGE)
	{
		CPpParsePackage *pPkg = (CPpParsePackage*)p;
		pPkg->InitOwnAllVariables(TRUE);
	}
	else if (nClassID == PPCLASSID_PPTTPACKAGE)
	{
		CPpTtPackage *pPkg = (CPpTtPackage*)p;
		pPkg->InitOwnAllVariables();
	}
	else if (nClassID == PPCLASSID_PPPARSEPACKGE)
	{
		CPpParsePackage *pPkg = (CPpParsePackage*)p;
		pPkg->InitOwnAllVariables(TRUE);
	}
	else
	{
	}
}


BOOL PpIsPackage(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	return PpIsPackage(pObj->GetClassID());
}

BOOL PpIsPackage(UINT nClassID)
{
	return (nClassID == PPCLASSID_PPPAKAGE || nClassID == PPCLASSID_PPPARSEPACKGE 
		|| nClassID == PPCLASSID_PPPRODUCEPACKGE || nClassID == PPCLASSID_PPTTPACKAGE);
}

//////////////////////////////////////////////////////////////////////////
//校验部分
DWORD Pp_Check(CExBaseList *pDetail, CExBaseObject *pChkByteBlock)
{
	if (pChkByteBlock == NULL)
	{
		return 0;
	}

	DWORD dwRet = 0;
	CByteBlock *pBbChk = (CByteBlock*)pChkByteBlock;

	if (pBbChk->m_strDataType == g_strBbDataTypeSumCheck)
	{
		dwRet = Pp_SumCheck(pDetail, pChkByteBlock);
	}
		
	else if (pBbChk->m_strDataType == g_strBbDataTypeCrcCheck) 
	{
		dwRet = Pp_Crc16Check(pDetail, pChkByteBlock, 0x0000);
	}

	else if (pBbChk->m_strDataType == g_strBbDataTypeCrcCheckFF) 
	{
		dwRet = Pp_Crc16Check(pDetail, pChkByteBlock, 0xFFFF);
	}

	else if (pBbChk->m_strDataType == g_strBbDataTypeCrcCheckTable) 
	{
		dwRet = Pp_Crc16CheckTable(pDetail, pChkByteBlock);
	}
	else
	{
		return PpProduceError();
	}

	pBbChk->RunScript();

	return dwRet;
}

BOOL Pp_GetCheckBeginAndEnd(CExBaseList *pDetail, CByteBlock *pBbChk, CByteBlock **ppChkBegin, CByteBlock **ppChkEnd)
{
	if (pBbChk->m_pRanges == NULL)
	{
		return FALSE;
	}

	if(pBbChk->m_pRanges->GetCount() != 2)
	{
		return FALSE;
	}

	CBbDataRange * pRangeHead = (CBbDataRange*)pBbChk->m_pRanges->GetAtIndex(0);
	CBbDataRange * pRangeTail = (CBbDataRange*)pBbChk->m_pRanges->GetAtIndex(1);


	*ppChkBegin = (CByteBlock*)pDetail->FindByID(pRangeHead->m_strValue);
	*ppChkEnd = (CByteBlock*)pDetail->FindByID(pRangeTail->m_strValue);

	if (*ppChkBegin == NULL || *ppChkEnd  == NULL)
	{
		return FALSE;
	}

	return TRUE;
}

DWORD Pp_SumCheck(CExBaseList *pDetail, CExBaseObject *pChkByteBlock)
{
	CByteBlock *pBbChk = (CByteBlock*)pChkByteBlock;
	CByteBlock *pByteBlock = NULL;
	POS pos = NULL;

	CByteBlock *pByteBlockHead = NULL;
	CByteBlock *pByteBlockTail = NULL;

	if (!Pp_GetCheckBeginAndEnd(pDetail, pBbChk, &pByteBlockHead, &pByteBlockTail))
	{
		return PpProduceError();
	}

	pos = pDetail->GetHeadPosition();
	unsigned long nSum = 0;
	BOOL bOnSumState = FALSE;
	while (pos != NULL)
	{
		pByteBlock = (CByteBlock*)pDetail->GetNext(pos);
	
		if (pByteBlock == pChkByteBlock)
		{//遇到当前Check的字节块
			break;
		}

		if (pByteBlock == pByteBlockHead)
		{//开始
			bOnSumState = TRUE;
		}

		if (bOnSumState)
		{
			nSum += pByteBlock->GetBufferSum();
		}

		if (pByteBlock == pByteBlockTail)
		{//结束
			break;
		}
	}

	//nSum = nSum % 256;
	long nLength = pBbChk->GetByteBlockLength2();

	if (pBbChk->m_pBuffer != NULL && ( nLength == 1 || nLength == 2) )
	{
		if (nLength == 1)
		{
			*(pBbChk->m_pBuffer) = (BYTE)(nSum & 0xFF);
		}
		else
		{
			*((WORD*)pBbChk->m_pBuffer) = (WORD) ( nSum & 0xFFFF );
		}

		return 0;
	}
	else
	{
		return PpProduceError();
	}
}

DWORD Pp_Crc16Check(CByteBlock *pByteBlock, WORD &nCrc)
{
	BYTE *pBuffer = pByteBlock->m_pBuffer;
	long nLength = pByteBlock->GetByteBlockLength2();
	long nIndex = 0;

	for (nIndex=0; nIndex<nLength; nIndex++)
	{
		unsigned int c = (WORD)( *(pBuffer+nIndex) );
		nCrc^=c;

		for(int j=0;j<8;j++)
		{
			if (nCrc & 0x0001)
			{
				nCrc>>=1;
				nCrc^=0xA001;
			}
			else
			{
				nCrc>>=1;
			}
		}
	}

	return nCrc;
}

DWORD Pp_Crc16Check(CExBaseList *pDetail, CExBaseObject *pChkByteBlock, WORD wValue)
{
	CByteBlock *pBbChk = (CByteBlock*)pChkByteBlock;
	CByteBlock *pByteBlock = NULL;
	POS pos = NULL;

	CByteBlock *pByteBlockHead = NULL;
	CByteBlock *pByteBlockTail = NULL;

	if (!Pp_GetCheckBeginAndEnd(pDetail, pBbChk, &pByteBlockHead, &pByteBlockTail))
	{
		return PpProduceError();
	}

	pos = pDetail->GetHeadPosition();
	WORD nCRC = wValue;
	BOOL bOnSumState = FALSE;

	while (pos != NULL)
	{
		pByteBlock = (CByteBlock*)pDetail->GetNext(pos);
	
		if (pByteBlock == pChkByteBlock)
		{//遇到当前Check的字节块
			break;
		}

		if (pByteBlock == pByteBlockHead)
		{//开始
			bOnSumState = TRUE;
		}

		if (bOnSumState)
		{
			Pp_Crc16Check(pByteBlock, nCRC);
		}

		if (pByteBlock == pByteBlockTail)
		{//结束
			break;
		}
	}

	long nLength = pBbChk->GetByteBlockLength2();

	if (pBbChk->m_pBuffer != NULL && ( nLength == 1 || nLength == 2) )
	{
		if (nLength == 1)
		{
			*(pBbChk->m_pBuffer) = (BYTE)(nCRC & 0xFF);
		}
		else
		{
			*((WORD*)pBbChk->m_pBuffer) = (WORD) ( nCRC & 0xFFFF );
		}

		return 0;
	}
	else
	{
		return PpProduceError();
	}
}

DWORD Pp_Crc16CheckTable(CByteBlock *pByteBlock, WORD &nCrc)
{
	static BYTE	crc_t1[]=
	{
		0x00,0x00,0xC1,0xC0,0x81,0xC1,0x40,0x01,0x01,0xC3,0xC0,0x03,0x80,0x02,0x41,0xC2,
		0x01,0xC6,0xC0,0x06,0x80,0x07,0x41,0xC7,0x00,0x05,0xC1,0xC5,0x81,0xC4,0x40,0x04
	};
	static BYTE	crc_t2[]=
	{
		0x00,0x00,0x01,0xCC,0x01,0xD8,0x00,0x14,0x01,0xF0,0x00,0x3C,0x00,0x28,0x01,0xE4,
		0x01,0xA0,0x00,0x6C,0x00,0x78,0x01,0xB4,0x00,0x50,0x01,0x9C,0x01,0x88,0x00,0x44
	};

	BYTE *pBuffer = pByteBlock->m_pBuffer;
	long nLength = pByteBlock->GetByteBlockLength2();
	long nIndex = 0;
//	WORD VX = 0;

	for (nIndex=0; nIndex<nLength; nIndex++)
	{
		unsigned int c = (WORD)( *(pBuffer+nIndex) );
		BYTE dzl;
		BYTE dzh;
		BYTE VXL = (BYTE)(nCrc % 256);
		BYTE VXH = (BYTE)(nCrc / 256);

		dzl = ((c ^ VXL) & 0x0F) * 2;
		dzh = ((c ^ VXL) & 0xF0) / 8;

		VXL = (crc_t1[dzl] ^ crc_t2[dzh]) ^ VXH;
		VXH = crc_t1[dzl + 1] ^ crc_t2[dzh + 1];

		nCrc = VXH * 256 + VXL;
	}

	return nCrc;
}
// WORD GetCRCCode(BYTE *pBuffer,int nSize)
// {
// 	BYTE *p = pBuffer;
// 	WORD VX = 0;
// 	for(int i = 0 ; i < nSize-2 ; i++)
// 	{
// 		BYTE dzl;
// 		BYTE dzh;
// 		BYTE VXL = (BYTE)(VX % 256);
// 		BYTE VXH = (BYTE)(VX / 256);
// 		dzl = ((p[i] ^ VXL) & 0x0F) * 2;
// 		dzh = ((p[i] ^ VXL) & 0xF0) / 8;
// 		VXL = (crc_t1[dzl] ^ crc_t2[dzh]) ^ VXH;
// 		VXH = crc_t1[dzl + 1] ^ crc_t2[dzh + 1];
// 		VX = VXH * 256 + VXL;
// 	}
// 	return VX;
// }

DWORD Pp_Crc16CheckTable(CExBaseList *pDetail, CExBaseObject *pChkByteBlock, WORD wValue)
{

	CByteBlock *pBbChk = (CByteBlock*)pChkByteBlock;
	CByteBlock *pByteBlock = NULL;
	POS pos = NULL;

	CByteBlock *pByteBlockHead = NULL;
	CByteBlock *pByteBlockTail = NULL;

	if (!Pp_GetCheckBeginAndEnd(pDetail, pBbChk, &pByteBlockHead, &pByteBlockTail))
	{
		return PpProduceError();
	}

	pos = pDetail->GetHeadPosition();
	WORD nCRC = wValue;
	BOOL bOnSumState = FALSE;

	while (pos != NULL)
	{
		pByteBlock = (CByteBlock*)pDetail->GetNext(pos);

		if (pByteBlock == pChkByteBlock)
		{//遇到当前Check的字节块
			break;
		}

		if (pByteBlock == pByteBlockHead)
		{//开始
			bOnSumState = TRUE;
		}

		if (bOnSumState)
		{
			Pp_Crc16CheckTable(pByteBlock, nCRC);
		}

		if (pByteBlock == pByteBlockTail)
		{//结束
			break;
		}
	}

	long nLength = pBbChk->GetByteBlockLength2();

	if (pBbChk->m_pBuffer != NULL && ( nLength == 1 || nLength == 2) )
	{
		if (nLength == 1)
		{
			*(pBbChk->m_pBuffer) = (BYTE)(nCRC & 0xFF);
		}
		else
		{
			*((WORD*)pBbChk->m_pBuffer) = (WORD) ( nCRC & 0xFFFF );
		}

		return 0;
	}
	else
	{
		return PpProduceError();
	}
}

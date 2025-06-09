//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GenRule.cpp  CGenRule


#include "stdafx.h"
#include "GenRule.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CGenRule::CGenRule()
{
	//初始化属性

	//初始化成员变量
	m_pSmvRule = NULL;
	m_pGinRule = NULL;
	m_pGoutRule = NULL;
}

CGenRule::~CGenRule()
{
}

long CGenRule::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGenRule::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGenRule::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CGenRule::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *pCurObj = NULL;

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == MNGRCLASSID_CSMVRULE)
		{
			m_pSmvRule = (CSmvRule*)pCurObj;
		}
		else if (pCurObj->GetClassID() == MNGRCLASSID_CGINRULE)
		{
			m_pGinRule = (CGinRule*)pCurObj;
		}
		else if (pCurObj->GetClassID() == MNGRCLASSID_CGOUTRULE)
		{
			m_pGoutRule = (CGoutRule*)pCurObj;
		}
	}
}

BOOL CGenRule::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGenRule *p = (CGenRule*)pObj;

	return TRUE;
}

BOOL CGenRule::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CGenRule *p = (CGenRule*)pDest;

	return TRUE;
}

CBaseObject* CGenRule::Clone()
{
	CGenRule *p = new CGenRule();
	Copy(p);
	return p;
}

CBaseObject* CGenRule::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGenRule *p = new CGenRule();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CGenRule::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSMVRULE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CGINRULE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CGOUTRULE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CGenRule::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSmvRuleKey)
	{
		pNew = new CSmvRule();
	}
	else if (strClassID == pXmlKeys->m_strCGinRuleKey)
	{
		pNew = new CGinRule();
	}
	else if (strClassID == pXmlKeys->m_strCGoutRuleKey)
	{
		pNew = new CGoutRule();
	}

	return pNew;
}

CExBaseObject* CGenRule::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSMVRULE)
	{
		pNew = new CSmvRule();
	}
	else if (nClassID == MNGRCLASSID_CGINRULE)
	{
		pNew = new CGinRule();
	}
	else if (nClassID == MNGRCLASSID_CGOUTRULE)
	{
		pNew = new CGoutRule();
	}

	return pNew;
}
long CGenRule::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	return 0;
}

long CGenRule::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	return 0;
}

BOOL CGenRule::GenarateIecCfgDatasMngr(CIecCfgDatasMngr *pIecCfgDatasMngr)
{
	ASSERT(pIecCfgDatasMngr);
	pIecCfgDatasMngr->m_strID = m_strID;
	pIecCfgDatasMngr->m_strName = m_strName;

	CIecCfgDatasSMV *pSmvMngr = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas* pGoutMngr = pIecCfgDatasMngr->GetGoutMngr();
	CIecCfgGinDatas *pIecCfgGinDatas = pIecCfgDatasMngr->GetGinMngr();
	pSmvMngr->SetSelectState_AllCtrlBlock(0);
	pGoutMngr->SetSelectState_AllCtrlBlock(0);
	pIecCfgGinDatas->SetSelectState_AllCtrlBlock(0);

	if (GetSmvRule())
	{
		m_pSmvRule->GenarateIecCfgDatasSMV(pSmvMngr);
	}

	if (GetGinRule())
	{
		m_pGinRule->GenarateIecCfgGinDatas(pIecCfgGinDatas);
	}

	if (GetGoutRule())
	{
		m_pGoutRule->GenarateIecCfgGoutDatas(pGoutMngr);
	}

	return TRUE;
}

CSmvRule* CGenRule::GetSmvRule()
{
	if (m_pSmvRule != NULL)
	{
		return m_pSmvRule;
	}

	m_pSmvRule = (CSmvRule*)FindByClassID(MNGRCLASSID_CSMVRULE);
	return m_pSmvRule;
}

CGinRule* CGenRule::GetGinRule()
{
	if (m_pGinRule != NULL)
	{
		return m_pGinRule;
	}

	m_pGinRule = (CGinRule*)FindByClassID(MNGRCLASSID_CGINRULE);
	return m_pGinRule;
}

CGoutRule* CGenRule::GetGoutRule()
{
	if (m_pGoutRule != NULL)
	{
		return m_pGoutRule;
	}

	m_pGoutRule = (CGoutRule*)FindByClassID(MNGRCLASSID_CGOUTRULE);
	return m_pGoutRule;
}
//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenClass.cpp  CItemsGenBase


#include "stdafx.h"
#include "ItemsGenBase.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenBase::CItemsGenBase()
{
	//初始化属性

	//初始化成员变量
	m_pItemsGenInterface = NULL;
	m_pItemsGenInterface_BK = NULL;
	m_pItemsGenEnable = NULL;
	m_pItemsGenParasMap = NULL;
	m_pCharItemLine = NULL;
	m_pRsltExpr = NULL;
}

CItemsGenBase::~CItemsGenBase()
{
	if (m_pItemsGenInterface_BK != NULL)
	{
		delete m_pItemsGenInterface_BK;
		m_pItemsGenInterface_BK = NULL;
	}
}

long CItemsGenBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CItemsGenBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CItemsGenBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CItemsGenBase::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENINTERFACE)
		{
			m_pItemsGenInterface = (CItemsGenInterface*)p;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENENABLE)
		{
			m_pItemsGenEnable = (CItemsGenEnable*)p;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
		{
			m_pItemsGenParasMap = (CItemsGenParasMap*)p;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENCHARITEMLINE)
		{
			m_pCharItemLine = (CItemsGenCharItemLine*)p;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENRSLTEXPR)
		{
			m_pRsltExpr = (CItemGenRsltExpr*)p;
		}
	}

	if (m_pItemsGenInterface == NULL)
	{
		m_pItemsGenInterface = (CItemsGenInterface*)AddNewChild(new CItemsGenInterface());
	}

	if (m_pItemsGenEnable == NULL)
	{
		m_pItemsGenEnable = (CItemsGenEnable*)AddNewChild(new CItemsGenEnable());
	}

	if (m_pItemsGenParasMap == NULL)
	{
		m_pItemsGenParasMap = (CItemsGenParasMap*)AddNewChild(new CItemsGenParasMap());
	}

	if (m_pItemsGenInterface_BK == NULL)
	{
		m_pItemsGenInterface_BK = new CItemsGenInterface;
	}

	m_pItemsGenInterface_BK->DeleteAll();
	m_pItemsGenInterface_BK->AppendClone(m_pItemsGenInterface);

	//可以没有特性曲线部分，故注释
// 	if (m_pCharItemLine == NULL)
// 	{
// 		m_pCharItemLine = (CItemsGenCharItemLine*)AddNewChild(new CItemsGenCharItemLine());
// 	}
}

BOOL CItemsGenBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CItemsGenBase *p = (CItemsGenBase*)pObj;

	return TRUE;
}

BOOL CItemsGenBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CItemsGenBase *p = (CItemsGenBase*)pDest;

	return TRUE;
}

CBaseObject* CItemsGenBase::Clone()
{
	CItemsGenBase *p = new CItemsGenBase();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenBase::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenBase *p = new CItemsGenBase();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenBase::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENENABLE)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENINTERFACE)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENCHARITEMLINE)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENRSLTEXPR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CItemsGenBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCItemsGenEnableKey)
	{
		pNew = new CItemsGenEnable();
	}
	else if (strClassID == pXmlKeys->m_strCItemsGenInterfaceKey)
	{
		pNew = new CItemsGenInterface();
	}
	else if (strClassID == pXmlKeys->m_strCItemsGenParasMapKey)
	{
		pNew = new CItemsGenParasMap();
	}
	else if (strClassID == pXmlKeys->m_strCMacroCharItemLineDefKey)
	{
		pNew = new CItemsGenCharItemLine();
	}
	else if (strClassID == pXmlKeys->m_strCItemRsltExprKey)
	{
		pNew = new CItemGenRsltExpr();
	}

	return pNew;
}

CExBaseObject* CItemsGenBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENENABLE)
	{
		pNew = new CItemsGenEnable();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENINTERFACE)
	{
		pNew = new CItemsGenInterface();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
	{
		pNew = new CItemsGenParasMap();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENCHARITEMLINE)
	{
		pNew = new CItemsGenParasMap();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENRSLTEXPR)
	{
		pNew = new CItemGenRsltExpr();
	}

	return pNew;
}

BOOL CItemsGenBase::IsEnable()
{
	return m_pItemsGenEnable->IsEnable(m_pItemsGenInterface);
}

void CItemsGenBase::InitParasMapByUIParas(CDataGroup *pUIParas)
{
	if (m_pItemsGenParasMap == NULL)
	{
		return;
	}

	m_pItemsGenParasMap->InitParaValueByUIParas(pUIParas);
	//m_pItemsGenParasMap->LogParasMapError();

	//通过界面参数初始化参数映射后，初始化相应的Interface下的数据
	m_pItemsGenInterface->InitDataValue(m_pItemsGenParasMap);
}
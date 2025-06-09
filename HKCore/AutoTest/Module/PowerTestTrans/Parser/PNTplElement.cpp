//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PNTplElement.cpp  CPNTplElement


#include "stdafx.h"
#include "PNTplElement.h"

CPNTplElement::CPNTplElement()
{
	//初始化属性

	//初始化成员变量
}

CPNTplElement::~CPNTplElement()
{
}

long CPNTplElement::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPNTplMngrXmlRWKeys *pXmlKeys = (CPNTplMngrXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CPNTplElement::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPNTplMngrXmlRWKeys *pXmlKeys = (CPNTplMngrXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

long CPNTplElement::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPNTplElement::InitAfterRead()
{
}

BOOL CPNTplElement::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPNTplElement *p = (CPNTplElement*)pObj;

	return TRUE;
}

BOOL CPNTplElement::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPNTplElement *p = (CPNTplElement*)pDest;

	return TRUE;
}

CBaseObject* CPNTplElement::Clone()
{
	CPNTplElement *p = new CPNTplElement();
	Copy(p);
	return p;
}

BOOL CPNTplElement::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CPNTPLELEMENT)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CPNTPLEQUATION)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CPNTPLGROUP)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CPNTPLTEXT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPNTplElement::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CPNTplMngrXmlRWKeys *pXmlKeys = (CPNTplMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPNTplElementKey)
	{
		pNew = new CPNTplElement();
	}
	else if (strClassID == pXmlKeys->m_strCPNTplEquationKey)
	{
		pNew = new CPNTplEquation();
	}
	else if (strClassID == pXmlKeys->m_strCPNTplGroupKey)
	{
		pNew = new CPNTplGroup();
	}
	else if (strClassID == pXmlKeys->m_strCPNTplTextKey)
	{
		pNew = new CPNTplText();
	}

	return pNew;
}

CExBaseObject* CPNTplElement::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CPNTPLELEMENT)
	{
		pNew = new CPNTplElement();
	}
	else if (nClassID == MNGRCLASSID_CPNTPLEQUATION)
	{
		pNew = new CPNTplEquation();
	}
	else if (nClassID == MNGRCLASSID_CPNTPLGROUP)
	{
		pNew = new CPNTplGroup();
	}
	else if (nClassID == MNGRCLASSID_CPNTPLTEXT)
	{
		pNew = new CPNTplText();
	}

	return pNew;
}

CPNTplEquation* CPNTplElement::FindEquation(const CString &strVarID)
{
#ifdef _DEBUG
	CExBaseObject *p = GetHead();

	if (p != NULL)
	{
		ASSERT(p->GetClassID() == MNGRCLASSID_CPNTPLEQUATION);
	}
#endif

	CPNTplEquation *pFind = (CPNTplEquation*)FindByName(strVarID);

	return pFind;
}

CPNTplEquation* CPNTplElement::FindEquationEx(const CString &strVarID)
{
#ifdef _DEBUG
	CExBaseObject *p = GetHead();

	if (p != NULL)
	{
		ASSERT(p->GetClassID() == MNGRCLASSID_CPNTPLGROUP);
	}
#endif

	CPNTplEquation *pFind = NULL;
	CPNTplGroup *pGroup = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pGroup = (CPNTplGroup *)GetNext(pos);
		pFind = pGroup->FindValueByID(strVarID);

		if (pFind != NULL)
		{
			break;
		}
	}
	
	return pFind;
}

CPNTplGroup* CPNTplElement::FindGroupByValueID(const CString &strVarID)
{
#ifdef _DEBUG
	CExBaseObject *p = GetHead();

	if (p != NULL)
	{
		ASSERT(p->GetClassID() == MNGRCLASSID_CPNTPLGROUP);
	}
#endif

	CPNTplGroup *pFind = NULL;
	CPNTplGroup *pGroup = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pGroup = (CPNTplGroup *)GetNext(pos);

		if (pGroup->FindValueByID(strVarID) != NULL)
		{
			pFind = pGroup;
			break;
		}
	}

	return pFind;
}

CPNTplEquation* CPNTplElement::FindEquationByValue(const CString &strValue)
{
	CPNTplEquation *pFind = NULL;
	CExBaseObject *pCurObj = NULL;
	CPNTplEquation *pCurEquation = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() != MNGRCLASSID_CPNTPLEQUATION)
		{
			continue;
		}

		pCurEquation = (CPNTplEquation*)pCurObj;


		if (pCurEquation->m_strValue == strValue)
		{
			pFind = pCurEquation;
			break;
		}
	}

	return pFind;
}

BOOL CPNTplElement::HasProtectionRelayParent()
{
	CExBaseObject *pCurParent = (CExBaseObject*)GetParent();
	BOOL bFind = FALSE;

	while(pCurParent)
	{
		if (pCurParent->GetClassID()==CLASSID_BASECLASS)
		{
			break;
		}

		if (pCurParent->m_strName == _T("ProtectionRelay"))
		{
			bFind = TRUE;
			break;
		}

		pCurParent = (CExBaseObject*)pCurParent->GetParent();
	}

	return bFind;
}

BOOL CPNTplElement::IsRepeatNode(const CString &strCurNodeName)
{
	if ((m_strName != strCurNodeName)||(GetCount()>0))
	{
		return FALSE;
	}

	if (!HasProtectionRelayParent())
	{
		return FALSE;
	}

	if ((strCurNodeName != _T("Report"))&&(strCurNodeName != _T("Character")))
	{
		return FALSE;
	}

	return TRUE;
}
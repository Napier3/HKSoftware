//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DLLFunction.cpp  CDLLFunction


#include "stdafx.h"
#include "DLLFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDLLFunction::CDLLFunction()
{
	//初始化属性

	//初始化成员变量
	m_pParas = NULL;
	m_pResults = NULL;
}

CDLLFunction::~CDLLFunction()
{
}

long CDLLFunction::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDllCallXmlRWKeys *pXmlKeys = (CDllCallXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDLLFunction::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDllCallXmlRWKeys *pXmlKeys = (CDllCallXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDLLFunction::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CDLLFunction::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DLCLCLASSID_CFUNCPARAS)
		{
			m_pParas = (CFuncParas*)p;
		}
		else if (nClassID == DLCLCLASSID_CFUNCRESULTS)
		{
			m_pResults = (CFuncResults*)p;
		}
	}

	if (m_pParas == NULL)
	{
		m_pParas = (CFuncParas*)AddNewChild(new CFuncParas());
	}

	if (m_pResults == NULL)
	{
		m_pResults = (CFuncResults*)AddNewChild(new CFuncResults());
	}

}

BOOL CDLLFunction::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDLLFunction *p = (CDLLFunction*)pObj;

	return TRUE;
}

BOOL CDLLFunction::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDLLFunction *p = (CDLLFunction*)pDest;

	return TRUE;
}

CBaseObject* CDLLFunction::Clone()
{
	CDLLFunction *p = new CDLLFunction();
	Copy(p);
	return p;
}

BOOL CDLLFunction::CanPaste(UINT nClassID)
{
	if (nClassID == DLCLCLASSID_CFUNCPARAS)
	{
		return TRUE;
	}

	if (nClassID == DLCLCLASSID_CFUNCRESULTS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDLLFunction::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDllCallXmlRWKeys *pXmlKeys = (CDllCallXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCFuncParasKey)
	{
		pNew = new CFuncParas();
	}
	else if (strClassID == pXmlKeys->m_strCFuncResultsKey)
	{
		pNew = new CFuncResults();
	}

	return pNew;
}

CExBaseObject* CDLLFunction::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DLCLCLASSID_CFUNCPARAS)
	{
		pNew = new CFuncParas();
	}
	else if (nClassID == DLCLCLASSID_CFUNCRESULTS)
	{
		pNew = new CFuncResults();
	}

	return pNew;
}

CFuncParas* CDLLFunction::GetParas()
{
	return m_pParas;
}

CFuncResults* CDLLFunction::GetResults()
{
	return m_pResults;
}

void CDLLFunction::GetParas(CString &strParas)
{
	strParas.Empty();

	if (m_pParas == NULL)
	{
		return;
	}
	
	POS pos = m_pParas->GetHeadPosition();
	CDvmValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)m_pParas->GetNext(pos);
		strParas.AppendFormat(_T("%s=%s;"), pValue->m_strID, pValue->m_strValue);
	}
}

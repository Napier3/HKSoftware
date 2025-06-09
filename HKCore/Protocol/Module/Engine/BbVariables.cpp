#include "StdAfx.h"
#include "BbVariables.h"
#include "PpParsePackage.h"
#include "PpProducePackage.h"
#include "PpProcedure.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBbVariables::CBbVariables(CString strXmlKey)
{
	m_strXmlKey=strXmlKey;
}

CBbVariables::~CBbVariables(void)
{
    //m_strXmlKey.ReleaseBuffer();
}


CExBaseObject* CBbVariables::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVariableKey)
	{
		CBbVariable* pVar = new CBbVariable();
		return pVar;
	}

	return NULL;
}

long CBbVariables::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn( oNode, pXmlRWKeys);
	
	return 0;
}
long CBbVariables::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

CExBaseObject* CBbVariables::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{

	return NULL;
}

CBbVariable* CBbVariables::AddVariable(const CString &strID, const CString &strDataType)
{
	CBbVariable *pVar = new CBbVariable();

	pVar->m_strID = strID;
	pVar->m_strName = strID;
	pVar->m_strType = strDataType;
	AddTail(pVar);
	pVar->SetParent(this);

	return pVar;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CBbVariables::IsEqualOwn(CBaseObject* pObj)
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

	if (m_strXmlKey != ((CBbVariables*)pObj)->m_strXmlKey)
	{
		return FALSE;
	}

	return CExBaseList::IsEqualOwn(pObj);
}

CBaseObject* CBbVariables::Clone()
{
	CBbVariables* pNew = new CBbVariables(_T(""));
	Copy(pNew);
	return pNew;
}

BOOL CBbVariables::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CBbVariables*)pDest)->m_strXmlKey = m_strXmlKey;

	return CExBaseList::CopyOwn(pDest);
}

void CBbVariables::GetVariablesString(CString &strVariables)
{
	POS pos = GetHeadPosition();
	CBbVariable *pVariable = NULL;
	CString strTemp;

	while (pos != NULL)
	{
		pVariable = (CBbVariable*)GetNext(pos);
        strTemp.Format(_T("%s=%s;\r\n"), pVariable->m_strID.GetString(), pVariable->m_strValue.GetString());
		strVariables += strTemp;
	}
}

void CBbVariables::Append(CExBaseList &oDestList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		oDestList.AddTail(p);
	}
}

void CBbVariables::CloneAppend(CExBaseList &oDestList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pNew = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		pNew = (CExBaseObject*)p->Clone();
		oDestList.AddTail(pNew);
	}
}

long CBbVariables::FindVariableByID(const CString &strID, CExBaseList &oDestList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		
		if (strID == p->m_strID)
		{
			oDestList.AddTail(p);
		}
	}

	return oDestList.GetCount();
}

long CBbVariables::FindVariableByName(const CString &strName, CExBaseList &oDestList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (strName == p->m_strName)
		{
			oDestList.AddTail(p);
		}
	}

	return oDestList.GetCount();
}


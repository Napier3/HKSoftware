#include "stdafx.h"
#include "MacroTestParaData.h"
#include "Script/GbScriptFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CMacroTestParaDataUser::CMacroTestParaDataUser()
{

}

CMacroTestParaDataUser::~CMacroTestParaDataUser()
{

}

long CMacroTestParaDataUser::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetCDATA(oNode, m_strExpression);

	return 0;
}

long CMacroTestParaDataUser::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetCDATA(oXMLDoc, oElement, m_strExpression);

	return 0;
}

BSTR CMacroTestParaDataUser::GetXmlElementKey()	
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strFaultParaTableParaUserKey;
}

long CMacroTestParaDataUser::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strExpression);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strExpression);
	}
	else
	{
		BinarySerializeWrite(oBinaryBuffer, m_strExpression);
	}

	return 0;
}


BOOL CMacroTestParaDataUser::IsEqual(CBaseObject* pObj)
{
	if (this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqual(pObj))
	{
		return FALSE;
	}

	if (m_strExpression != ( (CMacroTestParaDataUser*)pObj)->m_strExpression)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMacroTestParaDataUser::CopyOwn(CBaseObject* pDesObj)
{
	if (pDesObj == this)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDesObj);

	( (CMacroTestParaDataUser*)pDesObj)->m_strExpression = m_strExpression;

	return 0;
}

CBaseObject* CMacroTestParaDataUser::Clone()
{
	CMacroTestParaDataUser *pNew = new CMacroTestParaDataUser();
	
	Copy(pNew);

	return pNew;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CMacroTestParaData::CMacroTestParaData()
{

}

CMacroTestParaData::~CMacroTestParaData()
{
	
}

long CMacroTestParaData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	xml_GetCDATA(oNode, m_strExpression);
	m_strExpressionBack = m_strExpression;

	return 0;
}

long CMacroTestParaData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	xml_SetCDATA(oXMLDoc, oElement, m_strExpression);

	return 0;
}

long CMacroTestParaData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strExpression);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strExpression);
	}
	else
	{
		BinarySerializeWrite(oBinaryBuffer, m_strExpression);
	}

	return 0;
}

BSTR CMacroTestParaData::GetXmlElementKey()
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strFaultParaTableParaKey;
}

CExBaseObject* CMacroTestParaData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strFaultParaTableParaUserKey)
	{
		return new CMacroTestParaDataUser();
	}

	return NULL;
}

CExBaseObject* CMacroTestParaData::CreateNewChild(long nClassID)
{
	if(nClassID == GBCLASSID_FAULTPARAS_PARA_USER)
	{	
		return new CMacroTestParaDataUser();
	}

	return NULL;
}



BOOL CMacroTestParaData::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CMacroTestParaData::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);

	if(pDesObj == this)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDesObj);

	( (CMacroTestParaData*) pDesObj)->m_strExpression = m_strExpression;
	( (CMacroTestParaData*) pDesObj)->m_strExpressionBack = m_strExpressionBack;

	return TRUE;
}

CBaseObject* CMacroTestParaData::Clone()
{
	CMacroTestParaData* pFaultPara = new CMacroTestParaData();

	Copy(pFaultPara);

	return pFaultPara;
}

void CMacroTestParaData::SetToDataValue(CShortData  *pData)
{
	pData->m_strValue = m_strExpression;
}

void CMacroTestParaData::InsertNewDataUser(const CString &strExpression)
{
	CMacroTestParaDataUser *pNew = NULL;
	pNew = new CMacroTestParaDataUser();
	pNew->m_strExpression = strExpression;
	AddTail(pNew);
	pNew->SetParent(this);
}

void CMacroTestParaData::AddMacroTestParaDataUser(const CString &strExpression)
{
	CMacroTestParaDataUser *pNew = NULL;

	//第一次修改，将原始的数据添加到列表中
	if (GetCount() == 0)
	{
		InsertNewDataUser(m_strExpression);
	}
	else
	{
	}

	pNew = FindByExpression(strExpression);

	if (pNew == NULL)
	{
		InsertNewDataUser(strExpression);
	}

	m_strExpression = strExpression;
}

CMacroTestParaDataUser* CMacroTestParaData::FindByExpression(const CString &strExpression)
{
	CMacroTestParaDataUser *pUser = NULL;
	CMacroTestParaDataUser *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pUser = (CMacroTestParaDataUser*)GetNext(pos);

		if (pUser->m_strExpression == strExpression)
		{
			pFind = pUser;
			break;
		}
	}

	return pFind;
}


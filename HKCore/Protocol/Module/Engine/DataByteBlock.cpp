#include "StdAfx.h"
#include "DataByteBlock.h"
#include "BbVariable.h"
#include "PpDataBinds.h"
#include "PpScript.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDataByteBlock::CDataByteBlock(void)
{
	//m_pVariables = NULL;
}

CDataByteBlock::~CDataByteBlock(void)
{
}

long CDataByteBlock::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CByteBlock::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDataByteBlock::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CByteBlock::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

long CDataByteBlock::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CDataByteBlock::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVarialblesKey)
	{
		m_pVariables = new CBbVariables(strClassID);
		return m_pVariables;
		//return new  CBbVariables(strClassID);
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey)
	{
		m_pScript = new CPpScript(strClassID);
		return m_pScript;
		//return new CPpScript(strClassID);
	}

	return NULL;
}

CExBaseObject* CDataByteBlock::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CDataByteBlock::IsEqualOwn(CBaseObject* pObj)
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

	return CByteBlock::IsEqualOwn(pObj);
}

CBaseObject* CDataByteBlock::Clone()
{
	CDataByteBlock* pNew = new CDataByteBlock();
	Copy(pNew);
	return pNew;
}

BOOL CDataByteBlock::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CByteBlock::CopyOwn(pDest);
}
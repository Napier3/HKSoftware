//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmmMacthTool.cpp  CSmmMacthTool


#include "stdafx.h"
#include "SmmMacthTool.h"

CSmmMacthTool::CSmmMacthTool()
{
	//��ʼ������

	//��ʼ����Ա����
}

CSmmMacthTool::~CSmmMacthTool()
{
}

long CSmmMacthTool::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmmMacthTool::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmmMacthTool::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSmmMacthTool::InitAfterRead()
{
}

BOOL CSmmMacthTool::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmmMacthTool *p = (CSmmMacthTool*)pObj;

	return TRUE;
}

BOOL CSmmMacthTool::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmmMacthTool *p = (CSmmMacthTool*)pDest;

	return TRUE;
}

CBaseObject* CSmmMacthTool::Clone()
{
	CSmmMacthTool *p = new CSmmMacthTool();
	Copy(p);
	return p;
}

BOOL CSmmMacthTool::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CSmmMacthTool::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CSmmMacthTool::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PNTplText.cpp  CPNTplText


#include "stdafx.h"
#include "PNTplText.h"

CPNTplText::CPNTplText()
{
	//��ʼ������

	//��ʼ����Ա����
}

CPNTplText::~CPNTplText()
{
}

long CPNTplText::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPNTplMngrXmlRWKeys *pXmlKeys = (CPNTplMngrXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	return 0;
}

long CPNTplText::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPNTplMngrXmlRWKeys *pXmlKeys = (CPNTplMngrXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	return 0;
}

long CPNTplText::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPNTplText::InitAfterRead()
{
}

BOOL CPNTplText::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPNTplText *p = (CPNTplText*)pObj;

	return TRUE;
}

BOOL CPNTplText::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPNTplText *p = (CPNTplText*)pDest;

	return TRUE;
}

CBaseObject* CPNTplText::Clone()
{
	CPNTplText *p = new CPNTplText();
	Copy(p);
	return p;
}


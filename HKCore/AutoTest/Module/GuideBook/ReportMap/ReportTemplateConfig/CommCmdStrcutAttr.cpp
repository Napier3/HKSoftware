//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CommCmdStrcutAttr.cpp  CCommCmdStrcutAttr


#include "stdafx.h"
#include "CommCmdStrcutAttr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCommCmdStrcutAttr::CCommCmdStrcutAttr()
{
	//��ʼ������

	//��ʼ����Ա����
}

CCommCmdStrcutAttr::~CCommCmdStrcutAttr()
{
}

long CCommCmdStrcutAttr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCommCmdStrcutAttr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CCommCmdStrcutAttr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CCommCmdStrcutAttr *p = (CCommCmdStrcutAttr*)pDest;

	return TRUE;
}

CBaseObject* CCommCmdStrcutAttr::Clone()
{
	CCommCmdStrcutAttr *p = new CCommCmdStrcutAttr();
	Copy(p);
	return p;
}


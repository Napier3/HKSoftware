//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpAnalyseMngr.cpp  CEpAnalyseMngr


#include "stdafx.h"
#include "EpAnalyseMngr.h"

CEpAnalyseMngr::CEpAnalyseMngr()
{
	//��ʼ������

	//��ʼ����Ա����
}

CEpAnalyseMngr::~CEpAnalyseMngr()
{
}

long CEpAnalyseMngr::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpAnalyseStringXmlRWKeys *pXmlKeys = (CEpAnalyseStringXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpAnalyseMngr::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpAnalyseStringXmlRWKeys *pXmlKeys = (CEpAnalyseStringXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CEpAnalyseMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpAnalyseStringXmlRWKeys *pXmlKeys = (CEpAnalyseStringXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpAnalyseStringKey)
	{
		pNew = new CEpAnalyseString();
	}

	return pNew;
}

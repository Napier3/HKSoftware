//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PdfDBHead.h  CPdfDBHead

#pragma once

#include "PdfHLParseGlobal.h"



class CPdfDBHead : public CExBaseObject
{
public:
	CPdfDBHead();
	virtual ~CPdfDBHead();


	long  m_nNameHead;
	long  m_nDWHead;
	long  m_nValueHead;
	long  m_nExistHead;
//���غ���
public:
	virtual UINT GetClassID() {    return PDF_CLASSID_CPDFDBHEAD;   }
	virtual BSTR GetXmlElementKey()  {      return CPdfHLParseXmlRWKeys::CPdfDBHeadKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


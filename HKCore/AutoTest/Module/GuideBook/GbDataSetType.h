//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbDataSetType.h  CGbDataSetType

#pragma once

#include "GuideBookDefine.h"



class CGbDataSetType : public CExBaseObject
{
public:
	CGbDataSetType();
	virtual ~CGbDataSetType();


	long  m_nCanWrite;
//���غ���
public:
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::CGbDataSetTypeKey();     }
	virtual UINT GetClassID() {    return GBCLASSID_GBDATASETTYPE;   }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbDataSetTypes.h  CGbDataSetTypes

#pragma once

#include "GuideBookDefine.h"



class CGbDataSetTypes : public CExBaseList
{
public:
	CGbDataSetTypes();
	virtual ~CGbDataSetTypes();


//���غ���
public:
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::CGbDataSetTypesKey();     }
	virtual UINT GetClassID() {    return GBCLASSID_GBDATASETTYPE;   }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XMatchDatasetRef.h  CXMatchDatasetRef

#pragma once

#include "KeyDbGlobal.h"



class CXMatchDatasetRef : public CExBaseObject
{
public:
	CXMatchDatasetRef();
	virtual ~CXMatchDatasetRef();


//���غ���
public:
	virtual UINT GetClassID() {    return XMCFGCLASSID_CXMATCHDATASETREF;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXMatchDatasetRefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


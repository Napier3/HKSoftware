//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XMatchDataref.h  CXMatchDataref

#pragma once

#include "KeyDbGlobal.h"



class CXMatchDataref : public CExBaseObject
{
public:
	CXMatchDataref();
	virtual ~CXMatchDataref();


	CString  m_strSrcPath;
	CString  m_strDestPath;
//���غ���
public:
	virtual UINT GetClassID() {    return XMCFGCLASSID_CXMATCHDATAREF;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXMatchDatarefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


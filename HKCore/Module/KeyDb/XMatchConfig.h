//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XMatchConfig.h  CXMatchConfig

#pragma once

#include "KeyDbGlobal.h"


#include "XMatchDatarefs.h"
#include "XMatchDatasetRefs.h"

class CXMatchConfig : public CExBaseList
{
public:
	CXMatchConfig();
	virtual ~CXMatchConfig();


	CString  m_strSrcDatasetPath;
//���غ���
public:
	virtual UINT GetClassID() {    return XMCFGCLASSID_CXMATCHCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXMatchConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CXMatchDatarefs *m_pXMatchDatarefs;
	CXMatchDatasetRefs *m_pXMatchDatasetRefs;

	virtual void InitAfterRead();
 
};


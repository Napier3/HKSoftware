//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XMatchDatasetRefs.h  CXMatchDatasetRefs

#pragma once

#include "KeyDbGlobal.h"


#include "XMatchDatasetRef.h"

class CXMatchDatasetRefs : public CExBaseList
{
public:
	CXMatchDatasetRefs();
	virtual ~CXMatchDatasetRefs();


	CString  m_strMmsDvmFile;
//���غ���
public:
	virtual UINT GetClassID() {    return XMCFGCLASSID_CXMATCHDATASETREFS;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXMatchDatasetRefsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CXMatchDatasetRef* AddNewDataset(const CString &strID);
};


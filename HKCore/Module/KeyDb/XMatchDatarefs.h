//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XMatchDatarefs.h  CXMatchDatarefs

#pragma once

#include "KeyDbGlobal.h"


#include "XMatchDataref.h"

class CXMatchDatarefs : public CExBaseList
{
public:
	CXMatchDatarefs();
	virtual ~CXMatchDatarefs();


//���غ���
public:
	virtual UINT GetClassID() {    return XMCFGCLASSID_CXMATCHDATAREFS;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXMatchDatarefsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CXMatchDataref* FindBySrcPath(const CString &strPath);
	CXMatchDataref* FindByDestPath(const CString &strPath);

	CXMatchDataref* AddNewDataRef(const CString &strSrcIDPath, const CString &strDestIDPath);
};


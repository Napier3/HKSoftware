//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DinWzdFromSclGinChs.h  CDinWzdFromSclGinChs

#pragma once

#include "DinWzdFromSclGinCh.h"

class CDinWzdFromSclGinChs : public CExBaseList
{
public:
	CDinWzdFromSclGinChs();
	virtual ~CDinWzdFromSclGinChs();


//���غ���
public:
	virtual UINT GetClassID() {    return GBWZDCLASSID_CDINWZDFROMSCLGINCHS;   }
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CDinWzdFromSclGinChsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


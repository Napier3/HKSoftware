//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TagsMngr.h  CTagsMngr

#pragma once

#include "DataMngrGlobal.h"


#include "Tags.h"

class CTagsMngr : public CExBaseList
{
public:
	CTagsMngr();
	virtual ~CTagsMngr();


//���غ���
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CTAGSMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CTagsMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CTags* AddNewTags()
	{
		CTags *p = (CTags*)AddNewChild(new CTags());
		return p;
	}
};


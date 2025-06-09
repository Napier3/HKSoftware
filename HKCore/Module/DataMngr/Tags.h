//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Tags.h  CTags

#pragma once

#include "DataMngrGlobal.h"


#include "Tag.h"

class CTags : public CExBaseList
{
public:
	CTags();
	virtual ~CTags();


//���غ���
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CTAGS;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CTagsKey();     }
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

public:
	CTag* FindByDataType(const CString &strDataType);
	CTag* AddNew(const CString &strID, const CString &strValue, const CString &strDataType);
	CTag* FindByTagID(const CString &strTagID);
	CTag* FindByTagIDIcmp(const CString &strTagID);
};


//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Tags.h  CTags

#pragma once

#include "DataMngrGlobal.h"


#include "Tag.h"

class CTags : public CExBaseList
{
public:
	CTags();
	virtual ~CTags();


//重载函数
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

//私有成员变量
private:

//私有成员变量访问方法
public:

public:
	CTag* FindByDataType(const CString &strDataType);
	CTag* AddNew(const CString &strID, const CString &strValue, const CString &strDataType);
	CTag* FindByTagID(const CString &strTagID);
	CTag* FindByTagIDIcmp(const CString &strTagID);
};


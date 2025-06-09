//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DataType.h  CDataType

#pragma once

#include "DataMngrGlobal.h"


#include "DataTypeValue.h"

class CDataType : public CExBaseList
{
public:
	CDataType();
	virtual ~CDataType();


//重载函数
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CDATATYPE;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDataTypeKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	CDataTypeValue* FindByIndex(long nIndex);
	CDataTypeValue* FindByIndex(const CString &strIndex);
	CDataTypeValue* AddNewValue(const CString &strName, const CString &strID, long nIndex);
	CDataTypeValue* AddNewValue(const CString &strName, const CString &strID, const CString &strIndex);
	
	//2021-5-4  lijunqing
	CDataTypeValue* AddNewValue(const CString &strID, long nIndex);
	CDataTypeValue* AddNewValue(const CString &strID, const CString &strIndex);
};


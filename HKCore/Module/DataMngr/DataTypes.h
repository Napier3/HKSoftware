//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DataTypes.h  CDataTypes

#pragma once

#include "DataMngrGlobal.h"


#include "DataType.h"

class CDataTypes : public CExBaseList
{
public:
	CDataTypes();
	virtual ~CDataTypes();


//重载函数
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CDATATYPES;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDataTypesKey();     }
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

//其他方法
public:
	CDataType* AddNew2(const CString &strName, const CString &strID)
	{
		CDataType *pDataType = new CDataType();
		pDataType->m_strName = strName;
		pDataType->m_strID = strID;
		pDataType->SetParent(this);
		AddTail(pDataType);
		return pDataType;
	}

	BOOL Open(const CString &strFile, CXmlRWKeys *pXmlKeys);
};


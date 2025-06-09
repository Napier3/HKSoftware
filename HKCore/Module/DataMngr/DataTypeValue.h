//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DataTypeValue.h  CDataTypeValue

#pragma once

#include "DataMngrGlobal.h"



class CDataTypeValue : public CExBaseObject
{
public:
	CDataTypeValue();
	virtual ~CDataTypeValue();


	CString  m_strIndex;
//重载函数
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CDATATYPEVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDataTypeValueKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

//私有成员变量
private:

//私有成员变量访问方法
public:
	long GetIndex()
	{
		return CString_To_long(m_strIndex);
	}
	void SetIndex(long nIndex)
	{
		m_strIndex.Format(_T("%d"), nIndex);
	}
};


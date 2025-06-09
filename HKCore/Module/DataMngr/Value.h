//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Value.h  CValue

#pragma once

#include "DataMngrGlobal.h"



class CValue : public CExBaseList  //CExBaseObject  //2015-3-17修改
{
public:
	CValue();
	virtual ~CValue();


	CString  m_strValue;
//重载函数
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CValueKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	
	//缓冲区串行化
	virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);

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

//其他方法
public:
	void PutID(const CString &strID)
	{
		m_strID = strID;
	}

	void PutValue(const CString &strValue)
	{
		m_strValue = strValue;
	}

	void PutName(const CString &strName)
	{
		m_strName = strName;
	}
};


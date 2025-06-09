//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptBatchItemMaps.h  CRptBatchItemMaps

#pragma once

#include "RptBkmkBatchAddGlobal.h"


#include "RptBatchItemMap.h"

class CRptBatchItemMaps : public CExBaseList
{
public:
	CRptBatchItemMaps();
	virtual ~CRptBatchItemMaps();


//重载函数
public:
	virtual UINT GetClassID() {    return RBACLASSID_CRPTBATCHITEMMAPS;   }
	virtual BSTR GetXmlElementKey()  {      return CRptBkmkBatchAddXmlRWKeys::CRptBatchItemMapsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	void ClearMaps();
	CExBaseObject* GetFirstMapItem();
};


class CRptBatchItemMapsListCtrl : public CExBaseListListCtrl
{
public:
	CRptBatchItemMapsListCtrl();
	virtual ~CRptBatchItemMapsListCtrl();

public:
	virtual void InitCollumns();
	virtual void UpdateListCtrl(CExBaseObject *pObj, long nIndex);

};
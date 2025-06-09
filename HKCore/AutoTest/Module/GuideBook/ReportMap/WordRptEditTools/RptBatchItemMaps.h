//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptBatchItemMaps.h  CRptBatchItemMaps

#pragma once

#include "RptBkmkBatchAddGlobal.h"


#include "RptBatchItemMap.h"

class CRptBatchItemMaps : public CExBaseList
{
public:
	CRptBatchItemMaps();
	virtual ~CRptBatchItemMaps();


//���غ���
public:
	virtual UINT GetClassID() {    return RBACLASSID_CRPTBATCHITEMMAPS;   }
	virtual BSTR GetXmlElementKey()  {      return CRptBkmkBatchAddXmlRWKeys::CRptBatchItemMapsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
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
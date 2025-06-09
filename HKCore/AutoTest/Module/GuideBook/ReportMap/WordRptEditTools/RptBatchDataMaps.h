//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptBatchDataMaps.h  CRptBatchDataMaps

#pragma once

#include "RptBkmkBatchAddGlobal.h"


#include "RptBatchDataMap.h"
#include "../ReportTemplateConfig/ReportTemplateConfig.h"

class CRptBatchDataMaps : public CExBaseList
{
public:
	CRptBatchDataMaps();
	virtual ~CRptBatchDataMaps();


//重载函数
public:
	virtual UINT GetClassID() {    return RBACLASSID_CRPTBATCHDATAMAPS;   }
	virtual BSTR GetXmlElementKey()  {      return CRptBkmkBatchAddXmlRWKeys::CRptBatchDataMapsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	void ClearMaps();
};


#define RPTBATCH_DATA_COL_ATTR    3
#define RPTBATCH_DATA_COL_REPEAT  4
#define RPTBATCH_DATA_COL_PROCESS 5

class CRptBatchDataMapsListCtrl : public CExBaseListListCtrl
{
public:
	CRptBatchDataMapsListCtrl();
	virtual ~CRptBatchDataMapsListCtrl();

	void SetBkmkDataProcessMngr(CBkmkDataProcessMngr *p)	{	m_pBkmkDataProcessMngr = p;	}

private:
	CBkmkDataProcessMngr *m_pBkmkDataProcessMngr;

public:
	virtual void InitCollumns();
	virtual void UpdateListCtrl(CExBaseObject *pObj, long nIndex);

};
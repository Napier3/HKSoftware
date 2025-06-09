//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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


//���غ���
public:
	virtual UINT GetClassID() {    return RBACLASSID_CRPTBATCHDATAMAPS;   }
	virtual BSTR GetXmlElementKey()  {      return CRptBkmkBatchAddXmlRWKeys::CRptBatchDataMapsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
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
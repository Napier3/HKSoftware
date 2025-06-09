//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptBatchConfig.h  CRptBatchConfig

#pragma once

#include "RptBkmkBatchAddGlobal.h"


#include "RptBatchDataMaps.h"
#include "RptBatchItemMaps.h"
#include "RptBkmkBatchCell.h"

#define RPTBATCH_MODE_ROWITEM_COLDATA             0
#define RPTBATCH_MODE_ROWDATA_COLITEM             1
#define RPTBATCH_MODE_ROWREPEAT_COLDATA_ITEMROW   2

class CRptBatchConfig : public CExBaseList
{
public:
	CRptBatchConfig();
	virtual ~CRptBatchConfig();



//重载函数
public:
	virtual UINT GetClassID() {    return RBACLASSID_CRPTBATCHCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CRptBkmkBatchAddXmlRWKeys::CRptBatchConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

//私有成员变量
private:
	CRptBatchDataMaps *m_pDataMaps;
	CRptBatchItemMaps *m_pItemMaps;
	long  m_nMode;

//私有成员变量访问方法
public:
	BOOL IsRowItemColDataMode()				{	return m_nMode == RPTBATCH_MODE_ROWITEM_COLDATA;	}
	BOOL IsRowDataColItemMode()				{	return m_nMode == RPTBATCH_MODE_ROWDATA_COLITEM;	}
	BOOL IsRowRepeatColDataItemRowMode()	{	return m_nMode == RPTBATCH_MODE_ROWREPEAT_COLDATA_ITEMROW;	}
	UINT GetMode()				{	return m_nMode;										}
	void SetMode(UINT nMode)	{	m_nMode = nMode;									}
	CRptBatchDataMaps* GetRptBatchDataMaps()	{	return m_pDataMaps;	}
	CRptBatchItemMaps* GetRptBatchItemMaps()	{	return m_pItemMaps;	}
	void ClearMaps();
};

static const CString g_strRptBatchFilePostFix = _T("rptbc");
static const CString g_strRptBatchFileName = _T("报告模板批量插入标签映射配置文件");
CString wzd_GetRptBatchFilePath();
CString wzd_GetRptBatchFileDlgFilter();


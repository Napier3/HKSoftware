//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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



//���غ���
public:
	virtual UINT GetClassID() {    return RBACLASSID_CRPTBATCHCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CRptBkmkBatchAddXmlRWKeys::CRptBatchConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

//˽�г�Ա����
private:
	CRptBatchDataMaps *m_pDataMaps;
	CRptBatchItemMaps *m_pItemMaps;
	long  m_nMode;

//˽�г�Ա�������ʷ���
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
static const CString g_strRptBatchFileName = _T("����ģ�����������ǩӳ�������ļ�");
CString wzd_GetRptBatchFilePath();
CString wzd_GetRptBatchFileDlgFilter();


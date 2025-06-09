#pragma once

//功能描述 用来管理映射文件

#include "RptData.h"
#include "RptArea.h"
#include "RptMapRepeat.h"
//class CRptMapBase;

extern long g_nCloneReportMapInCopy;

class CReportMap : public CRptMapBase
{
public:
	CReportMap(void);
	CReportMap(const CString strFilePath);
	virtual ~CReportMap(void);

//属性
public:
	CRptArea *m_pArea;

private:
	CRptMapRepeat* AddRptMapRepeat(long nRepeatIndex);
	void SelectAllRptData(CExBaseList *pDatas, CExBaseList &listDatas);

//公共接口
public:
	CRptArea* AddArea(const CString &strAreaType=_T(""));
	CRptData* AddNewData(const CString  &strName, const CString  &strID, const CString &strPrecision, long nRepeatIndex);
	CRptData* FindRptData(const CString  &strID, long nRepeatIndex);
	CRptMapRepeat* FindRptMapRepeat(long nRepeatIndex);
	void SelectAllRptData(CExBaseList &listDatas);

//重写父类方法
public:
	virtual UINT GetClassID() {        return RPTCLASSID_RPTREPORTMAP;             }     
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::g_pGbXMLKeys->m_strReportMapKey;     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual void InitAfterRead();
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	void AddRptDataClone(CRptData *pRptData);

};

inline CString Gb_GetRptMapRepeatName(CExBaseObject *pObj)
{
	if (pObj->GetClassID() == RPTCLASSID_RPTMAPREPEAT)
	{
		CString strName;
		//strName.Format(_T("第%d次测试"), ((CRptMapRepeat*)pObj)->m_nIndex);
		strName = ( (CRptMapRepeat*)pObj)->GetRptMapRepeatName();
		return strName;
	}
	else
	{
		return pObj->m_strName;
	}
}
inline void Gb_GetRptMapRepeatName(CExBaseObject *pObj, CString &strName)
{
	if (pObj->GetClassID() == RPTCLASSID_RPTMAPREPEAT)
	{
		//strName.Format(_T("第%d次测试"), ((CRptMapRepeat*)pObj)->m_nIndex);
		strName = ( (CRptMapRepeat*)pObj)->GetRptMapRepeatName();
	}
	else
	{
		strName = pObj->m_strName;
	}
}

void Gb_GetRptBkmkNamePathString(CRptBkmk *pBkmk, CString &strPath);

inline CString Gb_GetRptBkmkNamePathString(CRptBkmk *pBkmk)
{
	CString strPath;
	Gb_GetRptBkmkNamePathString(pBkmk,strPath);
	return strPath;
}	


//CExBaseObject* _FindTheItemByID(CExBaseList *pList, CString strID);
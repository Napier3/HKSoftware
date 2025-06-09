#pragma once

#include "GuideBookMmsModelReplace.h"

class CGuideBookMmsModelsReplace : public CGuideBookMmsModelReplace
{
public:
	CGuideBookMmsModelsReplace();
	virtual ~CGuideBookMmsModelsReplace();

public:
	void ResetDatasets()	{	m_oListDatasetRef.RemoveAll();	m_oListDatasetRef.RemoveAll();	}
	CExBaseList* GetListDatasetOpened()	{	return &m_oListDatasetRef;	}
	CExBaseList* GetListDatasOpened()	{	return &m_oListDatasOpened;		}
	
	BOOL AddDataset(CExBaseList *pDataset);
	BOOL RemoveDataset(CExBaseList *pDataset);

protected:
	CExBaseList m_oListDatasOpened;
	long m_nCommCmdCount;

protected:
	virtual void XMatchRead(CXMatchConfig *pConfig);
	virtual BOOL XMatch(BOOL bShowMatch=TRUE);
	virtual void ReplaceDataSet(CThreadProgressInterface *pThreadProgress);
	virtual void RelpaceID(const CString &strSrcID, const CString &strDestID);
	virtual void AfterReplace();
	virtual void InitXMatchConfigDataset(CXMatchConfig *pXMatchConfig);
	virtual void InitListDatasetRef();

	virtual void SplitCommCmd(CExBaseList *pList);
	virtual void SplitCommCmd(CCommCmd *pCommCmd);

	virtual BOOL MatchFrom(CExBaseObject *pCurrFrom, CExBaseObject *pRefFrom);

};
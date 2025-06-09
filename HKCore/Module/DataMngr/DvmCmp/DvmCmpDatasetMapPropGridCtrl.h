#pragma once
#include <list>
#include "afxwin.h"

#include "DvmCmpBasePropGridCtrl.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//CDvmCmpDsMapPropGridProperty
class CDvmCmpDsPropGridProperty : public CDvmCmpPropGridProperty
{
public:
	DECLARE_DYNAMIC(CDvmCmpDsPropGridProperty)

	CDvmCmpDsPropGridProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	// Simple property
	CDvmCmpDsPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);

	virtual ~CDvmCmpDsPropGridProperty(){}

public:
	virtual void OnDrawName(CDC* pDC, CRect rect);
	virtual void OnDrawValue(CDC* pDC, CRect rect);

};

//CDvmCmpDsPropGridCtrl
class CDvmCmpDsPropGridCtrl :	public CDvmCmpBasePropGridCtrl
{
public:
	CDvmCmpDsPropGridCtrl();
	virtual ~CDvmCmpDsPropGridCtrl();

public:
	CDvmDeviceMap  *m_pDvmDeviceMap;
	CDvmDatasetMap *m_pDatasetMap;
	CDvmDataset    *m_pDataset;

public:
	virtual void ShowDatasetMap(CDvmDatasetMap *pDvmDataset);
	virtual void ShowDatasetMap(CDvmDeviceMap *pDeviceMap, CDvmDatasetMap *pDvmDataset);
	virtual void ShowDatasets(){};
	virtual CExBaseObject* GetSelDvmObject()	{	return NULL;	}

	CDvmMapObject* GetSelMapObject();
	CExBaseList* GetDvmDsMapStand()	{	return &m_listDvmDsMapStand;	}
	CDvmDataset* GetDvmDatasetStand();

protected:
	CExBaseList m_listDvmDsMapStand;

	virtual void InitDvmDsMapStand();
	virtual CDvmCmpDsPropGridProperty* NewDvmDataProp(CDvmData *pDvmData, long nIndex);
	virtual void NewDvmValuesProp(CExBaseList *pDvmValues, CDvmCmpDsPropGridProperty *pParent);

};


//////////////////////////////////////////////////////////////////////////
//CDvmCmpDsStandPropGridProperty
class CDvmCmpDsStandPropGridProperty : public CDvmCmpDsPropGridProperty
{
public:
	DECLARE_DYNAMIC(CDvmCmpDsStandPropGridProperty)

	CDvmCmpDsStandPropGridProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	// Simple property
	CDvmCmpDsStandPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);

	virtual ~CDvmCmpDsStandPropGridProperty(){}

public:
	virtual void OnDrawName(CDC* pDC, CRect rect);
	virtual void OnDrawValue(CDC* pDC, CRect rect);

};
//////////////////////////////////////////////////////////////////////////
//CDvmCmpDsMapPropGridCtrl
class CDvmCmpDsStandPropGridCtrl :	public CDvmCmpDsPropGridCtrl
{
public:
	CDvmCmpDsStandPropGridCtrl();
	virtual ~CDvmCmpDsStandPropGridCtrl();

	virtual void OnChangeSelection(CMFCPropertyGridProperty* /*pNewSel*/, CMFCPropertyGridProperty* /*pOldSel*/);

public:
	virtual void ShowDatasets();
	virtual CExBaseObject* GetSelDvmObject();
	virtual void DeleteMap(CExBaseObject *pDvmObject);
	virtual void ConfirmMap(CExBaseObject *pDvmObject);
	virtual void UpdateMap(CExBaseObject *pDvmObject);

protected:
	virtual CDvmCmpDsPropGridProperty* NewDvmDataProp(CDvmData *pDvmData, long nIndex);
	virtual void NewDvmValuesProp(CExBaseList *pDvmValues, CDvmCmpDsPropGridProperty *pParent);

public:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

};


//////////////////////////////////////////////////////////////////////////
//CDvmCmpDsMapPropGridProperty
class CDvmCmpDsMapPropGridProperty : public CDvmCmpDsPropGridProperty
{
public:
	DECLARE_DYNAMIC(CDvmCmpDsMapPropGridProperty)

	CDvmCmpDsMapPropGridProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	// Simple property
	CDvmCmpDsMapPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);

	virtual ~CDvmCmpDsMapPropGridProperty(){}

public:
	virtual void OnDrawName(CDC* pDC, CRect rect);
	virtual void OnDrawValue(CDC* pDC, CRect rect);

};

//////////////////////////////////////////////////////////////////////////
//CDvmCmpDsMapPropGridCtrl
class CDvmCmpDsMapPropGridCtrl :	public CDvmCmpDsPropGridCtrl
{
public:
	CDvmCmpDsMapPropGridCtrl();
	virtual ~CDvmCmpDsMapPropGridCtrl();

	virtual void OnChangeSelection(CMFCPropertyGridProperty* /*pNewSel*/, CMFCPropertyGridProperty* /*pOldSel*/);

public:
	virtual void ShowDatasets();

	//20231025 huangliang 此加此数据集内容
	virtual void ShowDatasetMap(CDvmDatasetMap *pDvmDataset);	

	virtual CExBaseObject* GetSelDvmObject();

	virtual void DeleteMap(CExBaseObject *pDvmObject);
	virtual void UpdateMap(CExBaseObject *pDvmObject);
	virtual void ConfirmMap(CExBaseObject *pDvmObject);

protected:
	void ShowDataset(CDvmDataset *pDataset, CDvmCmpDsPropGridProperty *pParent);
	virtual CDvmCmpDsPropGridProperty* NewDvmDataProp(CDvmData *pDvmData, long nIndex);
	virtual void NewDvmValuesProp(CExBaseList *pDvmValues, CDvmCmpDsPropGridProperty *pParent);
	virtual void InitDvmDsMapStand();

public:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

};


#pragma once
#include <list>
#include "afxwin.h"

#include "DvmMapTool.h"


#define WM_MACRO_PARA_VALUE_CHANGED (WM_USER + 6007)
#define WM_MACRO_PARA_SEL_CHANGED   (WM_USER + 6008)

#define WM_DVMCMPGRIDSTAND_SELDEST	(WM_USER+929)
#define WM_DVMCMPGRIDDEST_SELSTAND	(WM_USER+930)
#define WM_DVMCMPGRIDSTAND_POPDEST	(WM_USER+931)
#define WM_DVMCMPGRIDDEST_POPSTAND	(WM_USER+932)


class CDvmCmpPropGridProperty : public CMFCPropertyGridProperty
{
public:
	DECLARE_DYNAMIC(CDvmCmpPropGridProperty)

	CDvmCmpPropGridProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	// Simple property
	CDvmCmpPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);

	virtual ~CDvmCmpPropGridProperty(){}

	void SetIsValueList(BOOL b);

public:
	virtual void OnDrawName(CDC* pDC, CRect rect);
	virtual void OnDrawValue(CDC* pDC, CRect rect);
	virtual CWnd* CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat);
	virtual void SetValue(const COleVariant& varValue);
	virtual void SetModifyFlagEx(BOOL bFlag);

	virtual void SetCombBoxType();
};

//////////////////////////////////////////////////////////////////////////
//CDvmCmpBasePropGridCtrl
class CDvmCmpBasePropGridCtrl :	public CMFCPropertyGridCtrl
{
public:
	CDvmCmpBasePropGridCtrl()
	{
		m_bIngnoreSetCurrSel = FALSE;
		m_pDvmCmpBasePropGridCtrlRef = NULL;
	}
	virtual ~CDvmCmpBasePropGridCtrl()	{};

	void AttachDvmCmpBasePropGridCtrlRef(CDvmCmpBasePropGridCtrl *p)	
	{
		m_pDvmCmpBasePropGridCtrlRef = p;
	}

public:
	CExBaseObject*  GetSelectData();
	BOOL m_bIngnoreSetCurrSel;

	CDvmCmpBasePropGridCtrl *m_pDvmCmpBasePropGridCtrlRef;

public:
	void EnsurePropVisible(CMFCPropertyGridProperty* pProp, BOOL bExpandParents = FALSE);

};


//////////////////////////////////////////////////////////////////////////
//CDvmCmpCatalogPropGridCtrl
class CDvmCmpCatalogPropGridCtrl :	public CDvmCmpBasePropGridCtrl
{
public:
	CDvmCmpCatalogPropGridCtrl();
	virtual ~CDvmCmpCatalogPropGridCtrl();

public:
	void SetDevice(CDvmDevice *pDvmDevice);
	void UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) const ;
	void UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) ;
	void AttachMsgRcvWnd(CWnd *pWnd)			{	m_pMsgRcvWnd = pWnd;	}

private:
	void AddDvmLdevice(CDvmLogicDevice  *pDvmLdevice, CDvmCmpPropGridProperty *pParent);
	void SetDvmCmp(CShortDatas  *pDatas, CDvmCmpPropGridProperty *pParent);

protected:
	CDvmDeviceMap *m_pDvmDeviceMap;
	CDvmDevice *m_pDvmDevice;
	CWnd *m_pMsgRcvWnd;

public:
	virtual void OnLButtonDblClkMsg()=0;

public:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

//////////////////////////////////////////////////////////////////////////
//CDvmCmpCatalogStandPropGridCtrl
class CDvmCmpCatalogStandPropGridCtrl : public CDvmCmpCatalogPropGridCtrl
{
public:
	CDvmCmpCatalogStandPropGridCtrl();
	virtual~CDvmCmpCatalogStandPropGridCtrl();

	virtual void OnChangeSelection(CMFCPropertyGridProperty* /*pNewSel*/, CMFCPropertyGridProperty* /*pOldSel*/);
	virtual void OnLButtonDblClkMsg();

public:
	void ShowDvmCmpCatalog(CDvmDeviceMap *pDvmDeviceMap);

private:
	void AddDvmLdevice(CDvmLDeviceMap  *pDvmLdevice, CDvmCmpPropGridProperty *pParent);

};


//////////////////////////////////////////////////////////////////////////
//CDvmCmpCatalogMapPropGridCtrl
class CDvmCmpCatalogMapPropGridCtrl : public CDvmCmpCatalogPropGridCtrl
{
public:
	CDvmCmpCatalogMapPropGridCtrl();
	virtual~CDvmCmpCatalogMapPropGridCtrl();

	virtual void OnChangeSelection(CMFCPropertyGridProperty* /*pNewSel*/, CMFCPropertyGridProperty* /*pOldSel*/);
	virtual void OnLButtonDblClkMsg();

public:
	void ShowDvmCmpCatalog(CDvmDeviceMap *pDvmDeviceMap);

private:
	void AddDvmLdevice(CDvmLogicDevice  *pDvmLdevice, CDvmCmpPropGridProperty *pParent);
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//CDvmCmpDsMapPropGridProperty
class CDvmCmpDsMapPropGridProperty : public CDvmCmpPropGridProperty
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

protected:
	CExBaseList m_listDvmDsMapStand;

	void InitDvmDsMapStand();
	virtual CDvmCmpDsMapPropGridProperty* NewDvmDataProp(CDvmData *pDvmData, long nIndex);
	virtual void NewDvmValuesProp(CExBaseList *pDvmValues, CDvmCmpDsMapPropGridProperty *pParent);

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

protected:
	virtual CDvmCmpDsMapPropGridProperty* NewDvmDataProp(CDvmData *pDvmData, long nIndex);
	virtual void NewDvmValuesProp(CExBaseList *pDvmValues, CDvmCmpDsMapPropGridProperty *pParent);

public:
	DECLARE_MESSAGE_MAP()
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

public:
	CExBaseObject*  GetSelectData();

protected:
	void ShowDataset(CDvmDataset *pDataset, CDvmCmpDsMapPropGridProperty *pParent);
	virtual CDvmCmpDsMapPropGridProperty* NewDvmDataProp(CDvmData *pDvmData, long nIndex);
	virtual void NewDvmValuesProp(CExBaseList *pDvmValues, CDvmCmpDsMapPropGridProperty *pParent);


public:
	DECLARE_MESSAGE_MAP()
};


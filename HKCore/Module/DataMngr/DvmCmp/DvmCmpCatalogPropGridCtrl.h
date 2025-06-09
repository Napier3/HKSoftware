#pragma once
#include <list>
#include "afxwin.h"

#include "DvmCmpBasePropGridCtrl.h"


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
	CDvmDevice* GetDvmDevice()					{	return m_pDvmDevice;	}

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
	virtual void DeleteMap();
	virtual void DeleteMap(CDvmDatasetMap *pDatasetMap);
	CDvmDatasetMap* AddDatasetMap(CDvmDataset *pDestDataset, BOOL bNewStandDataset = FALSE);
	CDvmDatasetMap* AddDatasetMap(CDvmDataset *pStandDataset, CDvmDataset *pDestDataset);

public:
	void ShowDvmCmpCatalog(CDvmDeviceMap *pDvmDeviceMap);

private:
	void AddDvmLdevice(CDvmLDeviceMap  *pDvmLdevice, CDvmCmpPropGridProperty *pParent);
	CDvmCmpPropGridProperty* NewDatasetProp(CDvmDatasetMap *pDatasetMap);
	void InitDatasetProp(CDvmDatasetMap *pDatasetMap, CDvmCmpPropGridProperty *pDsProp);

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

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
	virtual void DeleteMap();

	CDvmDatasetMap* GetCurrDatasetMap();
	CDvmDatasetMap* AddDatasetMap(CDvmDataset *pStandDataset);

public:
	void ShowDvmCmpCatalog(CDvmDeviceMap *pDvmDeviceMap);

private:
	void AddDvmLdevice(CDvmLogicDevice  *pDvmLdevice, CDvmCmpPropGridProperty *pParent);
	void InitDsProperty(CDvmDatasetMap *pDatasetMap, CDvmDataset *pDvmDataset);

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};

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

// #define ID_DVMMAP_CREATEDATASETMAP_STAND        34790
// #define ID_DVMMAP_CREATEDATASETMAP_DEST         34791
// #define ID_DVMMAP_DELETEDATASETMAP_STAND        34792
// #define ID_DVMMAP_DELETEDATASETMAP_DEST         34793

#define ID_DVMMAP_CREATEDATAMAP_STAND           34790
#define ID_DVMMAP_CREATEDATAMAP_DEST            34791
#define ID_DVMMAP_DELETEDATAMAP_STAND           34792
#define ID_DVMMAP_DELETEDATAMAP_DEST            34793

#define ID_DVMMAP_MODIFYDATAMAP_STAND            34794
#define ID_DVMMAP_CONFIRMDATAMAP_STAND           34795

#define ID_DVMMAP_MODIFYDATAMAP_DEST            34796
#define ID_DVMMAP_CONFIRMDATAMAP_DEST           34797

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

	void SetNameEx(CDvmDatasetMap *pDatasetMap);
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
	CExBaseObject*  GetSelectData(UINT nClassID);
	BOOL m_bIngnoreSetCurrSel;

	CDvmCmpBasePropGridCtrl *m_pDvmCmpBasePropGridCtrlRef;

public:
	void EnsurePropVisible(CMFCPropertyGridProperty* pProp, BOOL bExpandParents = FALSE);

public:
	virtual void DeleteMap()	{	}
	virtual void DeleteMap(CExBaseObject *pDvmObject)	{	}
	virtual void UpdateMap(CExBaseObject *pDvmObject)	{	}
};

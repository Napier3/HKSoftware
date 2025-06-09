#pragma once

class CXMFCRibbonBarEx;

class CXMFCRibbonCategoryEx : public CMFCRibbonCategory
{
	friend class CXMFCRibbonBarEx;
	friend class CMFCRibbonBar;

	DECLARE_DYNCREATE(CXMFCRibbonCategoryEx)

protected:
	CXMFCRibbonCategoryEx();

	CXMFCRibbonCategoryEx(CMFCRibbonBar* pParentRibbonBar, LPCTSTR lpszName, UINT uiSmallImagesResID,
		UINT uiLargeImagesResID, CSize sizeSmallImage = CSize(16, 16), CSize sizeLargeImage = CSize(32, 32));


public:
	void LoadBmpFile(const CString &strBmpFile_Large, const CString &strBmpFile_Small);

};


class CXMFCRibbonBarEx : public CMFCRibbonBar
{
	friend class CXMFCRibbonCategoryEx;
	friend class CMFCRibbonCategory;

public:
	CXMFCRibbonBarEx(BOOL bReplaceFrameCaption = TRUE);

	CXMFCRibbonCategoryEx* AddCategory(LPCTSTR lpszName, UINT uiSmallImagesResID, UINT uiLargeImagesResID,
		CSize sizeSmallImage = CSize(16, 16), CSize sizeLargeImage = CSize(32, 32), int nInsertAt = -1, CRuntimeClass* pRTI = NULL);

protected:
	CString m_strBmpFile_Large;
	CString m_strBmpFile_Small;
};
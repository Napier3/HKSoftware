// XMFCRibbonBarEx.cpp
//

#include "stdafx.h"
#include "XMFCRibbonBarEx.h"

IMPLEMENT_DYNCREATE(CXMFCRibbonCategoryEx, CMFCRibbonCategory)

CXMFCRibbonCategoryEx::CXMFCRibbonCategoryEx()
{

}

CXMFCRibbonCategoryEx::CXMFCRibbonCategoryEx(CMFCRibbonBar* pParentRibbonBar, LPCTSTR lpszName, UINT uiSmallImagesResID,
											 UINT uiLargeImagesResID, CSize sizeSmallImage, CSize sizeLargeImage)
											 : CMFCRibbonCategory(pParentRibbonBar, lpszName, uiSmallImagesResID,
											 uiLargeImagesResID, sizeSmallImage, sizeLargeImage)
{

}


void CXMFCRibbonCategoryEx::LoadBmpFile(const CString &strBmpFile_Large, const CString &strBmpFile_Small)
{
	if (!IsFileExist(strBmpFile_Large))
	{
		return;
	}

	if (!IsFileExist(strBmpFile_Small))
	{
		return;
	}

	m_
}
//////////////////////////////////////////////////////////////////////////
//

CXMFCRibbonBarEx::CXMFCRibbonBarEx(BOOL bReplaceFrameCaption)
: CMFCRibbonBar(bReplaceFrameCaption)
{

}

CXMFCRibbonCategoryEx* CXMFCRibbonBarEx::AddCategory(LPCTSTR lpszName, UINT uiSmallImagesResID, UINT uiLargeImagesResID,
								   CSize sizeSmallImage, CSize sizeLargeImage, int nInsertAt, CRuntimeClass* pRTI)
{
	ASSERT_VALID(this);
	ENSURE(lpszName != NULL);

	CXMFCRibbonCategoryEx* pCategory = NULL;

	if (pRTI != NULL)
	{
		pCategory = DYNAMIC_DOWNCAST(CXMFCRibbonCategoryEx, pRTI->CreateObject());

		if (pCategory == NULL)
		{
			ASSERT(FALSE);
			return NULL;
		}

		pCategory->CommonInit(this, lpszName, uiSmallImagesResID, uiLargeImagesResID, sizeSmallImage, sizeLargeImage);
	}
	else
	{
		pCategory = new CXMFCRibbonCategoryEx(this, lpszName, uiSmallImagesResID, uiLargeImagesResID, sizeSmallImage, sizeLargeImage);
	}

	if (nInsertAt < 0)
	{
		m_arCategories.Add(pCategory);
	}
	else
	{
		m_arCategories.InsertAt(nInsertAt, pCategory);
	}

	if (m_pActiveCategory == NULL)
	{
		m_pActiveCategory = pCategory;
		//m_pActiveCategory->m_bIsActive = TRUE;
	}

	m_bRecalcCategoryHeight = TRUE;
	m_bRecalcCategoryWidth = TRUE;

	return pCategory;
}

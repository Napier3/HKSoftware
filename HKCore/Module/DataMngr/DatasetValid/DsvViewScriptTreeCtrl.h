#pragma once


// CDsvViewScriptTreeCtrl
#include "DsvScript.h"
#include "DsvViewDatasetGrid.h"

class CDsvViewScriptTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CDsvViewScriptTreeCtrl)

public:
	CDsvViewScriptTreeCtrl();
	virtual ~CDsvViewScriptTreeCtrl();
	void ShowDsvScript(CDsvScript *pDsvScript);
	CDsvViewDatasetGrid *m_pDatasetListCtrl;
	void SetImageListBmp(UINT nImageList);

private:
	void ShowDsvObjects(CExBaseList *pList, HTREEITEM hParent);
	CImageList m_oImageList;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};



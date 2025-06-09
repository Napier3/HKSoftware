#pragma once

#include "../../../../61850/Module/SCL/SclIedsGrid.h"
#include <map>

class CIEDSelGrid : public CSclIedsGrid
{
	DECLARE_DYNCREATE(CIEDSelGrid)
public:
	CIEDSelGrid();
	virtual ~CIEDSelGrid();

	//��д������Ҫ�õ����ֶ���ͼ����
public:
	long m_nCurSelect;
	long m_nCurHotRow;//��ǰ������
	BOOL m_bHotLight;//��������
	COLORREF m_crHot;
	std::map<long, CImage*> m_imageList;//CImageList�����ڴ�й©,����ʹ��map����

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowData_Ied(CExBaseObject *pObj,int &nRow);
	virtual long AddNewImage(const CString& strFilePath);
	virtual void ClearImageList();
	virtual BOOL DrawFixedCell(CGridCells &oCells, CDC *pDC, int nRow, int nCol, CRect rect, BOOL bCalMerge = TRUE, BOOL bEraseBk = FALSE);
	virtual void DrawTransparent(CDC* pDC, HBITMAP hBitmap, CRect rc);

	CExBaseObject* GetCurrSelIED(long nStateForCol=0);
	static void EndEditCell_Check (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

public:
	virtual void OnDraw(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};
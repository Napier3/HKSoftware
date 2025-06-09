
// StationTestMainView.h : CStationTestMainView ��Ľӿ�
//


#pragma once
#include "..\..\..\61850\Module\scl\SclIecCfgDatas.h"
#include "..\..\..\61850\Module\ScdDraw\XScdDrawViewStationThumbnail.h"
#include "..\..\..\Module\BaseClass\MemBufferDC.H"
#include "..\..\..\61850\Module\ScdDraw\XscdViewMain.h"

#include "StationTestOptrBase.h"

class CStationTestGraphDoc;

class CStationTestIedThumbView : public CXscdViewIedThumbMain, public CStationTestOptrBase
{
public: // �������л�����
	CStationTestIedThumbView();
	DECLARE_DYNCREATE(CStationTestIedThumbView)

public:
	void UpdateIedTestState();

	virtual void OnXScdElementLDblClk(CXDrawElement *pElement);
	virtual BOOL  OnXScdElementRButtonDown(UINT nFlags, CPoint point);

// ����
public:
	CStationTestGraphDoc* GetDocument() const;
	CXScdDrawIedThumbnail *m_pXScdDrawIedThumb;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

protected:

// ʵ��
public:
	virtual ~CStationTestIedThumbView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnStationTest_Iec61850Config();
	afx_msg void OnStationTest_DvmTest();
	afx_msg void OnStationTest_VTermTest();
	afx_msg void OnStationTest_ProtTest();
	afx_msg void OnStationTest_LinkTest();
	afx_msg void OnStationTest_ExportRpt();
	afx_msg void OnStationTest_UploadRpt();
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // StationTestMainView.cpp �еĵ��԰汾
inline CStationTestGraphDoc* CStationTestIedThumbView::GetDocument() const
   { return reinterpret_cast<CStationTestGraphDoc*>(m_pDocument); }
#endif


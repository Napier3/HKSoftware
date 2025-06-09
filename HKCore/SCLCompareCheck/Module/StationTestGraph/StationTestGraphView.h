
// StationTestMainView.h : CStationTestMainView 类的接口
//


#pragma once
#include "..\..\..\61850\Module\scl\SclIecCfgDatas.h"
#include "..\..\..\61850\Module\ScdDraw\XScdDrawViewStationThumbnail.h"
#include "..\..\Module\BaseClass\MemBufferDC.H"
#include "..\..\..\61850\Module\ScdDraw\XscdViewMain.h"

#include "StationTestOptrBase.h"

class CStationTestGraphDoc;

class CStationTestGraphView : public CXscdViewStationThumbMain, public CStationTestOptrBase
{
public: // 仅从序列化创建
	CStationTestGraphView();
	DECLARE_DYNCREATE(CStationTestGraphView)

public:
	void UpdateIedTestState();

	CXScdDrawIedThumbnail * GetScdDrawIedByID(CString strID);

	virtual void OnXScdElementLDblClk(CXDrawElement *pElement);
	virtual BOOL  OnXScdElementRButtonDown(UINT nFlags, CPoint point);

// 属性
public:
	CStationTestGraphDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
//	BOOL IsIedNeedTest(CString &strIedId);
//	CStationIedTest* GetCurrIedTest();

protected:

// 实现
public:
	virtual ~CStationTestGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
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

#ifndef _DEBUG  // StationTestMainView.cpp 中的调试版本
inline CStationTestGraphDoc* CStationTestGraphView::GetDocument() const
   { return reinterpret_cast<CStationTestGraphDoc*>(m_pDocument); }
#endif


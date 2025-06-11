#ifndef QSttIecSmvMeterAxisWidget_H
#define QSttIecSmvMeterAxisWidget_H

#include <QWidget>
#include <QToolButton>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QToolButton>
#include <QFont>

#include "SttIecRcdFuncInterface.h"
#include "../../../../Module/Axis/MeterAxis.h"
#include "../../../../Module/BaseClass/MemBufferDC.H"


//////////////////////////////////////////////////////////////////////////
//CSttSttIecSmvMeterAxisDraw
class CSttSttIecSmvMeterAxisDraw : public CExBaseObject
{
public:
	CSttSttIecSmvMeterAxisDraw();
	virtual ~CSttSttIecSmvMeterAxisDraw();

	CRect m_rcMeterAxis;
	CMeterAxis m_oMeterAxis;
	CDvmValue *m_pAvgValueRef;
	CString m_strChName;
	BOOL m_bEnable;

public:
	void InitByData(CDvmData *pData);
	void SetBoder(const CRect &rcBoder);
	void DrawMeter(CDC *pDC, unsigned long crText = RGB(255,255, 255), unsigned long crBack=RGB(0, 0, 0));
	void DrawValue(CDC *pDC);
};

//////////////////////////////////////////////////////////////////////////
//QSttIecSmvMeterAxisWidget
class QSttIecSmvMeterAxisWidget : public QWidget, public CSttIecRcdFuncInterface
{
    //Q_OBJECT
public:
	explicit QSttIecSmvMeterAxisWidget(QWidget *parent = 0);
	virtual ~QSttIecSmvMeterAxisWidget();

public://CSttIecRcdFuncInterface
	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();

	virtual BOOL NeedNextAndPrev();
	virtual void NextPage();
	virtual void PrevPage();

protected:
	long m_nCurrPageIndex;
	CExBaseList m_listPolarDraw;
	CExBaseList m_oPageDraw;

	long m_nRows, m_nCols ;
	long m_nHorzGap, m_nVertGap;
	long m_nHeightDraw, m_nWidthDraw;
	
	CMemBufferDC m_oMeterDrawDC;
	CDC *m_pDC;
	unsigned long m_crBkColor;

	void CreateDC();
	void CreateMemDC();
	void DrawCurrValues(CDC *pDC);
	void DrawBackgroud();

	void CalDrawPages(const CRect &rcBorder);
	void SetPageDrawCount(long nNewCount);
	void InitMeterPage();
	void InitCurrPageDraw();

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *);

	BOOL m_bIsDrawing;

// public:
// 
// signals:
// 
// public slots:

};

#endif // QSttIecSmvMeterAxisWidget_H

#ifndef _DCDifferCharacPlot_H
#define	_DCDifferCharacPlot_H

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_plot_marker.h>
#include <qwt_point_data.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_text.h>
#include <qwt_symbol.h>
#include <qwt_math.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_intervalcurve.h>
#include <QEvent>
#include <QMouseEvent>
#include <qwt_plot_renderer.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_layout.h>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include "../../Module/SttTest/Common/DC/tmt_dc_differ_test.h"
#include "../../Module/SttTest/Common/tmt_test_mngr.h"

#define TEST_DIFF_QD	0x00
#define TEST_DIFF_CURVE	0x01

#define TEST_DIFF_ZD2	0x02
#define TEST_DIFF_ZD2_2	0x03
#define TEST_DIFF_ZD3	0x04
#define TEST_DIFF_ZD3_2	0x05

struct DCMakerLine
{
	tmt_DcDifferCurTest* m_pCurrThrTest;
	QwtPlotCurve* PlotCurve;
	QwtPlotMarker* PlotMaker;

	DCMakerLine()
	{
		m_pCurrThrTest = NULL;
		PlotCurve = NULL;
		PlotMaker = NULL;
	}

	DCMakerLine &operator = (const DCMakerLine &right)
	{
		m_pCurrThrTest = right.m_pCurrThrTest;
		PlotCurve = right.PlotCurve;
		PlotMaker = right.PlotMaker;
	}
};

class DCDifferCharacPlot: public QwtPlot
{
	Q_OBJECT

public:
	DCDifferCharacPlot( QWidget *parent =NULL);
	void setData(TMT_PARAS_MNGR* pTmtTestMngr);

	void updatePlot();
	void updatePlotPos(tmt_DcDifferCurTest* pCurrThrTest);
	void updateSymbolPos(tmt_DcDifferCurTest* pCurrThrTest,bool bEnd=true);
	void clearSymbolPos(tmt_DcDifferCurTest* pCurrThrTest);
	void updateLabelTest(tmt_DcDifferCurTest* pCurrThrTest);

	void clearResultAll();
	void clearResult(tmt_DcDifferCurTest* pCurrThrTest);
	virtual bool eventFilter( QObject *, QEvent * );

	void start(){ bstartFlag = true; }
	void stop(){ bstartFlag = false; }

	void creatMaker();  //根据数据创建PlotMaker
	void setValueByInfo(tmt_DcDifferCurTest* pCurrThrTest, float fx, float fy);

	// 2022.5.13 caoxc
	float calcId(float fIr);

	//void SavePng(CString strPath);
	QPixmap SavePng();   //2023.8.28 zhangyq 将特性图内容生成图片
	void GetSearchingPng(CString& strBase64);  //2023.8.30 zhangyq 将图片生成base64的数据

signals:
	void sig_PlotDoubleClicked(float fx,float fy);
	void sig_PlotRightClicked(float fx,float fy);

	public slots:
		void slot_AddOneTest(tmt_DcDifferCurTest* pCurrThrTest);
		void slot_DelOneTest(tmt_DcDifferCurTest* pCurrThrTest);
		void slot_DelAllTest(tmt_DcDifferCurTest* pCurrThrTest);
		void slot_AddTestItem();

private:
	void init();
	void initPlot(); 

	void PlotDoubleClicked(float fx,float fy);
	void MouseMoved(float x,float y);
	void PlotRightClicked(float fx,float fy);
	void generateErrorRangeData(QVector<QPointF> &points,QVector<QwtIntervalSample> &rangeData,float fe);
	QString getValueByMarker(DCMakerLine info);
	QwtPlotMarker *getMarkerByTestInfo(tmt_DcDifferCurTest* pCurrThrTest);
	QwtPlotCurve *getCurveByTestInfo(tmt_DcDifferCurTest* pCurrThrTest);

	void insertErrorBars( const QString &title,const QVector<QwtIntervalSample> &,const QColor &color );
	void updateErrorBars(float fe);

	QwtPlotCurve *m_curve;
	QVector<QPointF> m_curvePoints;
	QwtPlotIntervalCurve *d_intervalCurve;

	QwtPlotPicker *d_picker;
	QLabel *m_PlotLabelText;
	QList<DCMakerLine> m_PlotMarker;
	QwtPlotMarker *m_CurPos;
	float m_CurXScale;
	float m_CurYScale;

	bool bstartFlag;

	float m_fPointX,m_fPointY;
	QMenu* m_popupMenu;
	QAction* m_addAction;

	tmt_DcDifferCurTest* m_pCommonParaTest;
	TMT_PARAS_MNGR* m_pTmtTestMngr;
};

#endif
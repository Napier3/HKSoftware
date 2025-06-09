#ifndef _BPCharacPlot_H
#define _BPCharacPlot_H

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
#include "../../Module/SttTest/Common/Diff/BP2_Diff/tmt_bp2_diff_test.h"
#include "../../Module/SttTest/Common/tmt_test_mngr.h"

#define XRADIO		4.5
#define YRADIO		1.2

#define TEST_QD		0x00
#define TEST_CURVE	0x01

#define TEST_ZD1	0x00
#define TEST_ZD1_2	0x01
#define TEST_ZD2	0x02
#define TEST_ZD2_2	0x03

struct MakerLine
{
	tmt_BP2DiffThrTest* pCurrThrTest;
	QwtPlotCurve* PlotCurve;
	QwtPlotMarker* PlotMaker;
	QwtPlotMarker* PlotMakerEx;

	MakerLine()
	{
		pCurrThrTest = NULL;
		PlotCurve = NULL;
		PlotMaker = NULL;
		PlotMakerEx = NULL;
	}

	MakerLine &operator = (const MakerLine &right)
	{
		pCurrThrTest = right.pCurrThrTest;
		PlotCurve = right.PlotCurve;
		PlotMaker = right.PlotMaker;
		PlotMakerEx = right.PlotMakerEx;
	}
};

class CBPDifferCharacPlot: public QwtPlot
{
    Q_OBJECT

public:
    CBPDifferCharacPlot( QWidget *parent =NULL);
	void setData(TMT_PARAS_MNGR* pTmtTestMngr);

	void updatePlot();
	void updatePlotPos(tmt_BP2DiffThrTest* pCurrThrTest);
	void updateSymbolPos(tmt_BP2DiffThrTest* pCurrThrTest,bool bEnd=true);
	void clearSymbolPos(tmt_BP2DiffThrTest* pCurrThrTest);
	void updateLabelTest(tmt_BP2DiffThrTest* pCurrThrTest);
	
	void clearResultAll();
	void clearResult(tmt_BP2DiffThrTest* pCurrThrTest);
	virtual bool eventFilter( QObject *, QEvent * );
	
	void start(){ bstartFlag = true; }
	void stop(){ bstartFlag = false; }

	void creatMaker();  //根据数据创建PlotMaker
	void setValueByInfo(tmt_BP2DiffThrTest* pCurrThrTest, float fx, float fy);

signals:
	void sig_PlotDoubleClicked(float fx,float fy);
	void sig_PlotRightClicked(float fx,float fy);

public slots:
   	void slot_AddOneTest(tmt_BP2DiffThrTest* pCurrThrTest);
	void slot_DelOneTest(tmt_BP2DiffThrTest* pCurrThrTest);
	void slot_DelAllTest(tmt_BP2DiffThrTest* pCurrThrTest);
	void slot_AddTestItem();

private:
	void init();
	void initPlot(); 

	void PlotDoubleClicked(float fx,float fy);
	void MouseMoved(float x,float y);
	void PlotRightClicked(float fx,float fy);
	void generateErrorRangeData(QVector<QPointF> &points,QVector<QwtIntervalSample> &rangeData,float fe);
	
	QwtPlotMarker *getMarkerByTestInfo(tmt_BP2DiffThrTest* pCurrThrTest);
	QwtPlotCurve *getCurveByTestInfo(tmt_BP2DiffThrTest* pCurrThrTest);

	void insertErrorBars( const QString &title,const QVector<QwtIntervalSample> &,const QColor &color );
	void updateErrorBars(float fe);

	QwtPlotCurve *m_curve;
	QVector<QPointF> m_curvePoints;
	QwtPlotIntervalCurve *d_intervalCurve;
	QwtPlotCanvas *canvas;

	QwtPlotPicker *d_picker;
	QLabel *m_PlotLabelText;
	QList<MakerLine> m_PlotMarker;
	QwtPlotMarker *m_CurPos;
	float m_CurXScale;
	float m_CurYScale;
	
	bool bstartFlag;
	
	float m_fPointX,m_fPointY;
	QMenu* m_popupMenu;
	QAction* m_addAction;

	tmt_BP2DiffThrTest* m_pCommonParaTest;
	TMT_PARAS_MNGR* m_pTmtTestMngr;

	float fIrId,fId;
	CString strLabel,strIrId,strId;
};

#endif
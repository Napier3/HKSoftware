#ifndef STTMUTESTFIRSTCWWIDGET_H
#define STTMUTESTFIRSTCWWIDGET_H

#include <qwt_plot.h>
#include <qwt_interval.h>
#include <qwt_system_clock.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_picker.h>
#include <qwt_math.h>
#include <qwt_scale_engine.h>
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qwt_plot_panner.h>
#include <qregexp.h>
#include <qapplication.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_canvas.h>
#include <qwt_painter.h>
#include <qwt_plot_layout.h>
#include <qwt_point_data.h>
#include <qwt_system_clock.h>
#include <qwt_plot_directpainter.h>
#include <qwt_curve_fitter.h>
#include <qwt_plot_renderer.h>
#include "../../SttRecordChComparePlot.h"
#include <QTabWidget>
#include "../../SmartCap/61850Cap/CapDevice/CapDevice92.h"
#include "../../SttIecRcdFuncInterface.h"
#include "../../SmartCap/61850Cap/CapDevice/CapDeviceBase.h"

enum FirstCircleWaveType{WAVETYPE_V=0,WAVETYPE_I};


class QSttMUTestFirstCwWidget:public QWidget,public CSttIecRcdFuncInterface
{
	Q_OBJECT
public:
	QSttMUTestFirstCwWidget(/*CCapDevice92 *pCapDevice92,*/ QWidget * = NULL );
	virtual ~QSttMUTestFirstCwWidget();
	
	QSttRecordChComparePlot *m_pPlot[255];
	QTabWidget *m_pFCPlotGroup;
	CCapDevice92 *m_pCapDevice92;
//	void initTitles();
	void initPlots();//初始化所有的首周波
	void initPlotsby61850CapBase();//开始测试之前根据原始数据来初始化首周波
	void updatePlots(long nChSetModifyType);//根据接收的是哪几个通道来显示对应的首周波
	void initAllFCWaves();//初始化所有首周波
	void UpdateFCWave(QSttRecordChComparePlot *pSttRecordChComparePlot ,long nChIndex);//根据通道号刷新对应的首周波
	void UpdateFCWaves();//根据接收的是哪几个通道来刷新对应的首周波
	void UpdateCapDevice();//IEC配置更改后刷新所有

	void ClearAllPlots();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();

//	void InitTestUI();//测试用
//	void insertTestCurve();//测试用

private:
//	QString m_strTitle[255];
public slots:
};
#endif
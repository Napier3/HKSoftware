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
	void initPlots();//��ʼ�����е����ܲ�
	void initPlotsby61850CapBase();//��ʼ����֮ǰ����ԭʼ��������ʼ�����ܲ�
	void updatePlots(long nChSetModifyType);//���ݽ��յ����ļ���ͨ������ʾ��Ӧ�����ܲ�
	void initAllFCWaves();//��ʼ���������ܲ�
	void UpdateFCWave(QSttRecordChComparePlot *pSttRecordChComparePlot ,long nChIndex);//����ͨ����ˢ�¶�Ӧ�����ܲ�
	void UpdateFCWaves();//���ݽ��յ����ļ���ͨ����ˢ�¶�Ӧ�����ܲ�
	void UpdateCapDevice();//IEC���ø��ĺ�ˢ������

	void ClearAllPlots();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();

//	void InitTestUI();//������
//	void insertTestCurve();//������

private:
//	QString m_strTitle[255];
public slots:
};
#endif
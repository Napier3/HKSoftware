#pragma once

#include <QWidget>
#include <QMap>
#include <QVector>
#include <QObject>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QGridLayout>
#include <qwt.h>
#include <qwt_plot_multi_barchart.h>
#include "SttIecSmvHistogramChartAxis.h"
#include "SttIecRcdFuncInterface.h"
#include "SttIecRecordDetectWidget.h"
#include "SttIecRecordCbWidget.h"

class CSttIecSmvWidget_Harm_Histogram : public QWidget , public CSttIecRcdFuncInterface
{
	Q_OBJECT
public:
	explicit CSttIecSmvWidget_Harm_Histogram(QWidget *parent = 0);
	virtual ~CSttIecSmvWidget_Harm_Histogram();

	void InitUI();	
	void InitYAxis();
	void InitYAxisData(CCapDeviceBase *pCapDevice,long nNum);
	void ShowValue(CDvmData *pData,const CString &str);

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();
	virtual BOOL NeedNextAndPrev();
	virtual void NextPage();
	virtual void PrevPage();
	void UpdateData();


protected:
	QSttIecSmvAxisPlot *m_pDiscretChart;
	CCapDeviceBase *m_pCurrCapDevice;
	QVBoxLayout *m_pVBoxLayout;
	QStringList m_StringListName;
	QVector<double> m_dValue;//一根柱子的值
    QVector<QVector<double> > m_dValues; //存储多根柱子
	
	long m_nUpdateCount;//减少刷新次数
	QList<QSttIecSmvAxisPlot *>m_pDiscretChartAxisPlot;

	long m_nCurrChIndex;
	long m_nChans;
	bool m_bUpdateFlag;

	QSttIecRecordCbWidget *m_pSttIecRecordCbWidget;
};


#ifndef QSttIecSmvDiscretCharWidget_H
#define QSttIecSmvDiscretCharWidget_H

#include <QWidget>
#include <QMap>
#include <QVector>
#include <QObject>
#include <qwt.h>
#include <qwt_plot_multi_barchart.h>
#include "SttIecSmvDiscretChartAxis.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceBase.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDevice92.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DISCRETCHARCOLUMN 7 //����ͼ���Ӹ���

class QSttIecSmvDiscretCharWidget : public QWidget
{//��״ͼ��ͼ
	Q_OBJECT
public:
	QSttIecSmvDiscretCharWidget(QWidget* parent = 0);
	~QSttIecSmvDiscretCharWidget();
	QSttIecSmvDiscretChartAxis *m_pDiscretChart;

	virtual void resizeEvent(QResizeEvent *pReSizeEvent);
	/*virtual void timerEvent(QTimerEvent *event);*/
	void InitAxisTitle(QString xlabel, QString ylabel);
	void PrepareData();
	void GetMaxTimeDiscrete(CCapDeviceBase *pCapDevice);
	void SetMaxTimeDiscreteCount();
	void GetMaxPkgCount();//��ȡ�������
	CCapDevice92 *m_pCapDevice92;
	int m_nMaxPkgNum;
private:
	int m_nDisCretNum[DISCRETCHARCOLUMN];

};

#endif

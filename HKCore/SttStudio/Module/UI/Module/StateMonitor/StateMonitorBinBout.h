#ifndef STATEMONITORBINBOUT_H
#define STATEMONITORBINBOUT_H

#include "StateMonitorPlot.h"

class QStateMonitorBinBout: public QStateMonitorPlot
{
	Q_OBJECT
private:
    int SwitchYTick[40];
	long m_nBinNum;
	long *m_pBinData;		//������ʵʱ״̬����:�Ͽ�0���ϲ�1
	long m_nBoutNum;
	long *m_pBoutData;		//������ʵʱ״̬����:�Ͽ�0���ϲ�1

	long m_arrBinBout[MAX_BINARYIN_COUNT + MAX_BINARYOUT_COUNT];	//�ϴο�����״̬:�Ͽ�0���ϲ�1

private:
	void InitCurve();

public:
	QStateMonitorBinBout(QWidget* parent = 0);
	virtual ~QStateMonitorBinBout();

public:
	void InitBinBoutPoint(double fTime);
	void AddBinBoutPoint(long nIndex, double x, double y);
	void setBinBoutData(long *pBinData, long nBinNum, long *pBoutData, long nBoutNum);
	virtual void UpdateCurve(long nIndex, const QVector<QPointF>& points);//����ÿ��QwtPlotCurve
};

#endif //!STATEMONITORBINBOUT_H
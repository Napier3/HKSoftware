#ifndef _BinTimeResponsePlot_H
#define _BinTimeResponsePlot_H

#include "TimeResponsePlotBase.h"

class CBinTimeSignal : public CExBaseObject
{
public:
	double m_dLastTime;					//���ʱ��
};

class CBinBoutTimeResponsePlot: public CTimeResponsePlotBase
{
	Q_OBJECT
public:
	CBinBoutTimeResponsePlot(QWidget * = NULL );
	virtual ~CBinBoutTimeResponsePlot();

	void setBinBoutData(long *pBinData, long nBinNum, long *pBoutData, long nBoutNum);

	virtual void start();
	virtual void initCurve();
	virtual void updateCurve(double fv);
	virtual void onTimerEvent( QTimerEvent * ); 

	CAutoCriticSection m_oCriticSection;
	CExBaseList m_oSignalList;
	void AppendSignalData(double dTime);
	void AppenSignalInfo(CBinTimeSignal *pSignalInfo);
	void GetSignalInfo(CExBaseList &oSignalInfoList);

private:
	int SwitchYTick[20];
	long m_nBinNum;
	long *m_pBinData;		//������ʵʱ״̬����:�Ͽ�0���ϲ�1
	long m_nBoutNum;
	long *m_pBoutData;		//������ʵʱ״̬����:�Ͽ�0���ϲ�1

	public slots:
		void slot_UpdateBinCurve();
};

#endif
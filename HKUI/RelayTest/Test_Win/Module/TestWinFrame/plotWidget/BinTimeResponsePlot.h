#ifndef _BinTimeResponsePlot_H
#define _BinTimeResponsePlot_H

#include "TimeResponsePlotBase.h"

class CBinTimeSignal : public CExBaseObject
{
public:
	double m_dLastTime;					//相对时间
};

class CBinTimeResponsePlot: public CTimeResponsePlotBase
{
	Q_OBJECT
public:
	CBinTimeResponsePlot(QWidget * = NULL );
	virtual ~CBinTimeResponsePlot();

	void setBinData(long *pBinData,long nBinNum,long nBinChlType);

	virtual void start();
	virtual void initCurve();
	virtual void updateCurve(double fTimeValue);
	virtual void onTimerEvent( QTimerEvent * ); 

	CAutoCriticSection m_oCriticSection;
	CExBaseList m_oSignalList;
	void AppendSignalData(double dTime);
	void AppenSignalInfo(CBinTimeSignal *pSignalInfo);
	void GetSignalInfo(CExBaseList &oSignalInfoList);

	void InitBinBoutPoint(double fTime);
	void AddBinBoutPoint(long nIndex, double x, double y);
	virtual void UpdateCurve(long nIndex, const QVector<QPointF>& points);//更新每个QwtPlotCurve
	virtual void UpdateCurves();

private:
	long m_nBinChlType;		//0:字符通道,1:数组通道
	long m_nBinNum;
	long *m_pBinData;		//开关量实时状态数组:断开0，合并1

	//20230613 zhouhj
	long m_arrBinBout[MAX_BINARYIN_COUNT];	//上次开关量状态:断开0，合并1

public slots:
	void slot_UpdateBinCurve();
};

#endif
#ifndef _ChlTimeResponsePlotEx_H
#define _ChlTimeResponsePlotEx_H

#include "TimeResponsePlotBase.h"

#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../Module/SttTestResourceMngr/RtDataMngr/SttMacroChannels.h"

#define NANOSECOND 1.0e9

class CChlTimeSignal : public CExBaseObject
{
public:
	double m_dLastTime;					//相对时间
	QList<tmt_RtDataCh*> m_rtDataList;	//实时数据通道列表

	void init()
	{
		m_dLastTime = 0;
		m_rtDataList.clear();
	}

	void clearRtDataList()
	{
		for (int i=0;i<m_rtDataList.size();i++)
		{
			delete m_rtDataList[i];
		}
		m_rtDataList.clear();
	}

	CChlTimeSignal()
	{
		init();
	}

	virtual ~CChlTimeSignal()
	{
		clearRtDataList();
	}
};

class CChlTimeResponsePlotEx: public CTimeResponsePlotBase
{
	Q_OBJECT
public:
	CChlTimeResponsePlotEx(QWidget * = NULL );
	virtual ~CChlTimeResponsePlotEx();

	void setChlData(CExBaseList &oChlUDatasList,CExBaseList &oChlIDatasList);
	void setChlData(CExBaseList &oChlUDatasList,CExBaseList &oChlIDatasList
		,double fUMin,double fUMax,double fIMin,double fIMax);
	virtual void start();
	virtual void stop();
	virtual void initCurve();
	
//	void updateXScale(float f1, float f2);
	void updateYScale(changed_type type,QString str,float f1,float f2);
	void updateYTtile(QString str);
	void setYLeftRightScale(changed_type type,float fstart,float fend,int num);
	void InitYTick(double fUMin,double fUMax,double fIMin,double fIMax);
	void setData(int nChannel, int type, bool bStart);
	void setData(CExBaseList &oChlDatasList, int type, bool bStart);
	CSttMacroChannel* GetMacroChannel(int nChannel); //博电旧模块方案
	void GetMacroChannelEx(int nChannel);

	//当前信号点数据
	QList<tmt_RtDataCh*> m_rtDataList;	//实时数据通道列表
	void clearRtDataList();
	bool m_bInited;

	CAutoCriticSection m_oCriticSection;
	CExBaseList m_oSignalList;
	CChlTimeSignal* NewSignal();
	void AppendSignalData(CChlTimeSignal* pSignal,double dTime,tmt_RtDataCh* pCh);
	void AppenSignalInfo(CChlTimeSignal *pSignalInfo);
	void GetSignalInfo(CExBaseList &oSignalInfoList);
	void updateCurve(double fv);
	void updateSignal(CChlTimeSignal* pSignalInfo);

	virtual void onTimerEvent( QTimerEvent * ); 
public:
	CExBaseList m_oChlUDatasList;
	CExBaseList m_oChlIDatasList;

	CExBaseList m_oMacroChannels;

	QVector<QLabel *> m_vecChlULabel;
	QVector<QLabel *> m_vecChlILabel;

	int m_nChannel;
	int m_ChangeType;

	QwtSystemClock d_clock;

	QwtPlotPicker *d_picker;
	QwtPlotMarker *d_origin;
	QLabel *m_PlotLabelText;

	bool m_bStart;

public slots:
	void slot_UpdateCurveEx();
};

#endif
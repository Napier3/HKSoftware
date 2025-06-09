#ifndef _ChlTimeResponsePlot_H
#define _ChlTimeResponsePlot_H

#include "TimeResponsePlotBase.h"
#include "../../../../Module/SttTestResourceMngr/RtDataMngr/SttMacroChannels.h"

class QStateMonitorData : public CExBaseList
{
public:
	QPointF m_oPoint;

	QStateMonitorData() {}
	virtual ~QStateMonitorData() {}
};

class CChlTimeResponsePlot: public CTimeResponsePlotBase
{
	Q_OBJECT
public:
	CChlTimeResponsePlot(QWidget * = NULL );
	virtual ~CChlTimeResponsePlot();

	void setChlData(CExBaseList &oChlUDatasList,CExBaseList &oChlIDatasList
		,double fUMin,double fUMax
		,double fIMin,double fIMax
		,int type = 0);

	virtual void start();
	virtual void initCurve();
	virtual void updateCurve(double fv);
	void InitYTick(double fUMin,double fUMax,double fIMin,double fIMax);

	void ChangeType(int nType);
	void AddPoint(CSttMacroChannels* pMacroChs);
	void UpdateValueText();

private:
	CExBaseList m_oChlUDatasList;
	CExBaseList m_oChlIDatasList;

	QVector<QLabel *> m_vecChlULabel;
	QVector<QLabel *> m_vecChlILabel;

	int m_nType;//0--幅值 1--相位 2--频率
	CExBaseList* m_pLastPoints;

	void FreeChlDatasList();

protected slots:
	void slot_UpdateCurve();
};

#endif
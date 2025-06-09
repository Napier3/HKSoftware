#ifndef STATEMONITORVOLTCUR_H
#define STATEMONITORVOLTCUR_H

#include <qcolor.h>
#include <QLabel>
#include "StateMonitorPlot.h"
#include "../../../SttTestResourceMngr/RtDataMngr/SttMacroChannels.h"

class Background: public QwtPlotItem
{
public:
	Background()
	{
		setZ( 0.0 );
	}

	virtual int rtti() const
	{
		return QwtPlotItem::Rtti_PlotUserItem;
	}

	virtual void draw( QPainter *painter,
		const QwtScaleMap &, const QwtScaleMap &yMap,
		const QRectF &canvasRect ) const
	{
		QColor c( QColor( 167, 183, 165 ) );
		QColor c2( Qt::black);
		QRectF r = canvasRect;
		painter->fillRect( r, c );
	}
};

class QStateMonitorVoltCur: public QStateMonitorPlot
{
	Q_OBJECT
private:
	int m_nChannel;
	int m_ChangeType;

	CExBaseList m_oMacroChannels;

	QLabel m_labelText;
	QLabel m_labelValue;
	QVector<QLabel*> m_vecChlLabel;
	QVector<QLabel*> m_vecChlValue;

private:
	CSttMacroChannel* GetCurMacroChannelClone(int nChannel);
	CSttMacroChannel* GetVoltMacroChannelClone(int nChannel);

	CSttMacroChannel* GetImpMacroChannelClone();//故障阻抗 add wangtao 20240913
	CSttMacroChannel* GetUfMacroChannelClone();//故障电压
	CSttMacroChannel* GetIfMacroChannelClone();//故障电流

public:
	QStateMonitorVoltCur(QWidget* parent = 0);
	virtual ~QStateMonitorVoltCur();

public:
	void InitYTick(double fUMin, double fUMax, double fIMin, double fIMax);
	void SetSingleTitle(const CString& strTitle);
	void InitCurve(CExBaseList* pChlUDatasList, CExBaseList* pChlIDatasList);
	void UpdateSingleChannel(int nChannel, int nType, bool bStart);
	void AddPoint(CSttMacroChannels* pMacroChs);
	void GetMacroChannel(int nChannel);
	void UpdateValueText();

	void ChangeType(int type);
	void ManagePointData(CSttMacroChannel* pMacroCh, int index);//add wangtao 20240911 处理绘图节点，提取自AddPoint()函数中的公共代码

};

#endif //!STATEMONITORVOLTCUR_H
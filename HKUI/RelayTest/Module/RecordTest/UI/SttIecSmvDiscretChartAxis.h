#ifndef QSttIecSmvDiscretChartAxis_H
#define QSttIecSmvDiscretChartAxis_H

#include <qwt_plot.h>
#include <qwt_plot_multi_barchart.h>
#include <qwt_column_symbol.h>
#include <qwt_scale_draw.h>
#include <QVector>
#include "stdafx.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapAnalysisConfig.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDevice92.h"

//static const char *colors[] = {"blue"};

class QSttIecSmvDiscretChartDraw : public QwtScaleDraw
{
public:
	QSttIecSmvDiscretChartDraw(Qt::Orientation orientation, const QStringList &labels);
	virtual QwtText label(double value)const;//显示y轴标签
private:
	QStringList m_pLabel;

};

//绘制柱子以及柱子的值
class QSttIecSmvDiscretChartColumnSymbol : public QwtColumnSymbol
{
public:
	QSttIecSmvDiscretChartColumnSymbol(double hit, QColor color, double Maxhit);
	virtual void draw(QPainter *p, const QwtColumnRect &rect)const;//显示柱子的值

private:
	int m_nhit;
	QColor m_pColor;
	int m_nMaxhit;

};

//绘制柱子
class QSttIecSmvDiscretChartPlot : public QwtPlotMultiBarChart
{
public:
	QSttIecSmvDiscretChartPlot();
	QwtColumnSymbol* specialSymbol(int sampleIndex, int valueIndex)const;
        QVector<QVector<double> > m_pBarValue;
	int m_nPkgMaxNumPlot;
};

class QSttIecSmvDiscretChartAxis : public QwtPlot
{
	Q_OBJECT
public:
	QSttIecSmvDiscretChartAxis(QWidget *parent = NULL);
	~QSttIecSmvDiscretChartAxis();
	QwtColumnSymbol *m_pColumnSymbol;
	QSttIecSmvDiscretChartPlot *m_pMultiBar;

public:
    void InitBarChat(int oritention, QVector<QVector<double> > series, QStringList m_list,CCapDevice92 *pCapDevice, int nPkgMaxNum);
	void setOrientation(int orientation, QStringList m_list, CCapDevice92 *pCapDevice);

};
#endif

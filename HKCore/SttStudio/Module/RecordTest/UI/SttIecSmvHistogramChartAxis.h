#pragma once

#include <qwt_plot.h>
#include <qwt_plot_multi_barchart.h>
#include <qwt_column_symbol.h>
#include <qwt_scale_draw.h>
#include <QVector>
#include "stdafx.h"

class QSttIecSmvHistogramChartAxis : public QwtScaleDraw
{
public:
	QSttIecSmvHistogramChartAxis(const QStringList &labels);
	virtual QwtText label(double value)const;//�ػ�������y�̶�ֵ
private:
	QStringList m_pLabel;

};

//�������ӱ�ǩ
class QSttIecSmvColumnSymbol : public QwtColumnSymbol
{
public:
	QSttIecSmvColumnSymbol(double dValue, QColor color);
	virtual void draw(QPainter *p, const QwtColumnRect &rect)const;

private:
	double m_dValue;
	QColor m_pColor;

};

//��������
class QSttIecSmvMultiBarChart : public QwtPlotMultiBarChart
{
public:
	QSttIecSmvMultiBarChart();
	QwtColumnSymbol* specialSymbol(int sampleIndex, int valueIndex)const;
        QVector<QVector<double> > m_pBarValue;
};

class QSttIecSmvAxisPlot : public QwtPlot
{
	Q_OBJECT
public:
	QSttIecSmvAxisPlot(QWidget *parent = NULL);
	~QSttIecSmvAxisPlot();
	QwtColumnSymbol *m_pColumnSymbol;
	QSttIecSmvMultiBarChart *m_pMultiBar;

public:
        void InitBarChat(QVector<QVector<double> > series, QStringList Stringlist);
	void setOrientation(QStringList Stringlist);

};

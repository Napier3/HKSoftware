#include "SttIecSmvDiscretCharWidget.h"
#include <qwt_plot_grid.h>
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapAnalysisConfig.h"
#include "../../XLangResource_Native.h"

QSttIecSmvDiscretCharWidget::QSttIecSmvDiscretCharWidget(QWidget* parent)
 : QWidget(parent)
{
	for (int i = 0; i < DISCRETCHARCOLUMN; i++)
	{
		m_nDisCretNum[i] = 0;
	}
	CString strText;
	strText = /*_T("SV报文离散度视图")*/g_sLangTxt_Native_SVMsgDispersView;
	m_pCapDevice92 = NULL;
	m_pDiscretChart = new QSttIecSmvDiscretChartAxis(this);
	m_pDiscretChart->setAxisTitle(QwtPlot::xBottom, strText);
	//设置网格
	QwtPlotGrid *grid = new QwtPlotGrid;
	grid->setMajorPen(QColor(193, 193, 193), 1, Qt::SolidLine);
	grid->attach(m_pDiscretChart);
}

QSttIecSmvDiscretCharWidget::~QSttIecSmvDiscretCharWidget()
{


}


void QSttIecSmvDiscretCharWidget::resizeEvent(QResizeEvent *pReSizeEvent)
{
	QRect rc = geometry();
	m_pDiscretChart->resize(rc.width(), rc.height());

}

// void QSttIecSmvDiscretCharWidget::timerEvent(QTimerEvent *event)
// {
// 	PrepareData();
// 	QWidget::timerEvent( event );
// }

void QSttIecSmvDiscretCharWidget::InitAxisTitle(QString xlabel, QString ylabel)
{
	m_pDiscretChart->setAxisTitle(QwtPlot::xBottom, xlabel);
	m_pDiscretChart->setAxisTitle(QwtPlot::yLeft, ylabel);

}

void QSttIecSmvDiscretCharWidget::GetMaxTimeDiscrete(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice92 = (CCapDevice92 *)pCapDevice;
}

void QSttIecSmvDiscretCharWidget::SetMaxTimeDiscreteCount()
{
	for (int i = 0; i < DISCRETCHARCOLUMN; i++)
	{
		m_nDisCretNum[i] = m_pCapDevice92->m_nDisCretNum[i];
	}
	GetMaxPkgCount();
}

void QSttIecSmvDiscretCharWidget::PrepareData()
{
    QVector<QVector<double> > values;
	QStringList strList;
	int orientation = 1;//1为绘制横向柱形图
	
	SetMaxTimeDiscreteCount();
	for (int i = 0; i < DISCRETCHARCOLUMN; i++)
	{
		QVector<double> val;
		if (i == 6)
		{
			val += m_nDisCretNum[0];
		}
		else if (i == 5)
		{
			val += m_nDisCretNum[1];
		}
		else if (i == 4)
		{
			val += m_nDisCretNum[2];
		}
		else if (i == 3)
		{
			val += m_nDisCretNum[3];
		}
		else if (i == 2)
		{
			val += m_nDisCretNum[4];
		}
		else if (i == 1)
		{
			val += m_nDisCretNum[5];
		}
		else if (i == 0)
		{
			val += m_nDisCretNum[6];
		}	

		values += val;
	}
	strList << "10-250us" << "1-10us" << "0-1us" << "0us" << "-1-0us" << "-10--1us" << "-250--10us";
	m_pDiscretChart->InitBarChat(orientation, values, strList, m_pCapDevice92, m_nMaxPkgNum);
}

void QSttIecSmvDiscretCharWidget::GetMaxPkgCount()
{
	QVector<double> nPkgCount;
	for (int i = 0; i < DISCRETCHARCOLUMN; i++)
	{
		nPkgCount.push_back(m_nDisCretNum[i]);
	}
	qSort(nPkgCount.begin(), nPkgCount.end());
	if (nPkgCount.size() > 0)
	{
		m_nMaxPkgNum = nPkgCount.at(nPkgCount.size() - 1);
	}
}

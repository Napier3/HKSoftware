#include "SttMUTestFirstCwWidget.h"

#include <QDir>
#include <QMessageBox>
#include <QLayout>
#include "../../SmartCap/XSttCap_61850.h"
#include "../../SmartCap/XSmartCapInterface.h"
#include "../../SmartCap/XSmartCapMngr.h"
#include "../../SmartCap/61850Cap/CapDevice/CapDeviceChBase.h"
#include "../SttIecRecordCbInterface.h"

#define PI 3.14159265

QSttMUTestFirstCwWidget::QSttMUTestFirstCwWidget(/*CCapDevice92 *pCapDevice92,*/QWidget * /* = NULL */ )
{
	for (int i = 0;i < 255;i++)
	{
		m_pPlot[i] = NULL;
	}

	m_pCapDevice92 = NULL;
	m_pFCPlotGroup = new QTabWidget;
	QHBoxLayout *pLayout = new QHBoxLayout;
	pLayout->addWidget(m_pFCPlotGroup);
	this->setLayout(pLayout);
//	insertTestCurve();//测试用
	
}

QSttMUTestFirstCwWidget::~QSttMUTestFirstCwWidget()
{
	for (int i = 0;i < 255;i++)
	{
		if (m_pPlot[i])
		{
			delete m_pPlot[i];
		}
		m_pPlot[i] = NULL;
	}
	delete m_pFCPlotGroup;
	m_pFCPlotGroup = NULL;
}


// void QSttMUTestFirstCwWidget::initTitles()
// {
// 	for (int i = 0; i < m_nChCnt; i++)
// 	{
// 		m_strTitle[i] = QString::fromLocal8Bit("通道%1").arg(i+1);
// 	}
// }


void QSttMUTestFirstCwWidget::UpdateFCWave(QSttRecordChComparePlot *pSttRecordChComparePlot ,long nChIndex)
{
	pSttRecordChComparePlot->clearCurve();

	double *pdValue = NULL;
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if (pXSttCap_61850 != NULL)
	{
		if (m_pCapDevice92 != NULL)
		{
			long nChDataIndex = m_pCapDevice92->GetFirstCW_ChDatasIndex(nChIndex);

			if (nChDataIndex>=0)
			{
				pdValue = pXSttCap_61850->m_oStdSrcDatas_FirstCW[nChDataIndex];
			}
		}
	}

	pSttRecordChComparePlot->insertInputCurve(pdValue, 800);

	if (m_pCapDevice92 != NULL)
	{
		pSttRecordChComparePlot->insertOutputCurve(m_pCapDevice92->m_oFirstCW_RcdDatas[nChIndex],800);
	}
}

void QSttMUTestFirstCwWidget::ClearAllPlots()
{
	for (int i = 0; i < 255; i++)
	{
		if (m_pPlot[i] != NULL)
		{
			m_pPlot[i]->clearCurve();
			delete m_pPlot[i];
			m_pPlot[i] = NULL;
		}
	}  
}

void QSttMUTestFirstCwWidget::initAllFCWaves()
{
	ClearAllPlots();

	if ((m_pCapDevice92 == NULL)||(m_pCapDevice == NULL))
	{
		return;
	}

	POS pos = m_pCapDevice92->GetHeadPosition();
	CCapDeviceChBase *pCapDeviceChBase = NULL;
	long nChIndex = 0,nPlotIndex = 0;

	while(pos)
	{
		pCapDeviceChBase = (CCapDeviceChBase *)m_pCapDevice92->GetNext(pos);
		if (pCapDeviceChBase->m_nSelect)
		{
			if (m_pCapDevice92->m_nChType[nChIndex] == CAPDEVICE_CHTYPE_U
				||m_pCapDevice92->m_nChType[nChIndex] ==CAPDEVICE_CHTYPE_I)
			{
				m_pPlot[nPlotIndex] = new QSttRecordChComparePlot(SttRecordChType(m_pCapDevice92->m_nChType[nChIndex]),this);

				{
					m_pFCPlotGroup->addTab(m_pPlot[nPlotIndex], pCapDeviceChBase->m_strName);
				}

				UpdateFCWave(m_pPlot[nPlotIndex],nChIndex);
				nPlotIndex++;
			}
		}

		nChIndex++;
	}  
}

void QSttMUTestFirstCwWidget::Release()
{
	delete this;
}

void QSttMUTestFirstCwWidget::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	if (pXSttCap_61850->m_bFirstCWDatasChanged == true)//如果参数改变了再进行刷新
	{
		UpdateFCWaves();
		pXSttCap_61850->m_bFirstCWDatasChanged = false;
	}

	return;
}

void QSttMUTestFirstCwWidget::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;

	if (m_pCapDevice92 == NULL || m_pCapDevice92 != (CCapDevice92 *)pCapDevice)
	{
		m_pCapDevice92 = (CCapDevice92 *)pCapDevice;
		UpdateCapDevice();
	}

	UpdateFCWaves();
//	updatePlots();
}

void QSttMUTestFirstCwWidget::initPlots()
{
	if(m_pCapDevice92 == NULL)
	{
		return;
	}
	m_pCapDevice92->SetDeviceChMaps();
// 	m_nChCnt = m_pCapDevice92->GetCount();
// 	initTitles();
	initAllFCWaves();
}

void QSttMUTestFirstCwWidget::updatePlots(long nChSetModifyType)
{
	if (m_pCapDevice92 == NULL)
	{
		return;
	}

	if (nChSetModifyType == STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc)
	{
		m_pFCPlotGroup->clear();

		POS pos = m_pCapDevice92->GetHeadPosition();
		CCapDeviceChBase *pCapDeviceChBase = NULL;
		long nChIndex = 0,nPlotIndex = 0;

		while(pos)
		{
			pCapDeviceChBase = (CCapDeviceChBase *)m_pCapDevice92->GetNext(pos);

			if (pCapDeviceChBase->m_nSelect)
			{
				if (m_pCapDevice92->m_nChType[nChIndex] == CAPDEVICE_CHTYPE_U
					||m_pCapDevice92->m_nChType[nChIndex] ==CAPDEVICE_CHTYPE_I)
				{

					if (m_pPlot[nPlotIndex] == NULL)
					{
						break;
					}

					m_pFCPlotGroup->addTab(m_pPlot[nPlotIndex], pCapDeviceChBase->m_strName);
					UpdateFCWave(m_pPlot[nPlotIndex],nChIndex);
					nPlotIndex++;
				}
			}

			nChIndex++;
		} 
	}
}

void QSttMUTestFirstCwWidget::UpdateFCWaves()
{
	if (m_pCapDevice92 == NULL)
	{
		return;
	}

	POS pos = m_pCapDevice92->GetHeadPosition();
	CCapDeviceChBase *pCapDeviceChBase = NULL;
	long nChIndex = 0,nPlotIndex = 0;

	while(pos)
	{
		pCapDeviceChBase = (CCapDeviceChBase *)m_pCapDevice92->GetNext(pos);
		if (pCapDeviceChBase->m_nSelect)
		{
			if (m_pCapDevice92->m_nChType[nChIndex] == CAPDEVICE_CHTYPE_U
				||m_pCapDevice92->m_nChType[nChIndex] ==CAPDEVICE_CHTYPE_I)
			{

				if (m_pPlot[nPlotIndex] == NULL)
				{
					break;
				}

				UpdateFCWave(m_pPlot[nPlotIndex],nChIndex);
				nPlotIndex++;
			}
		}

		nChIndex++;
	} 
}

void QSttMUTestFirstCwWidget::UpdateCapDevice()
{
	initPlots();
//	updatePlots();
}

// void QSttMUTestFirstCwWidget::insertTestCurve()
// {
// 	InitTestUI();
// 	double testsInput[1200];
// 	double testsOutput[1200];
// 	for (int i = 0; i < 1200; i++)
// 	{
// 		testsInput[i] = 150*sin(double(i*PI/180));
// 	}
// 	m_pPlot[0]->insertInputCurve(testsInput,sizeof(testsInput)/sizeof(double));
// 	for (int i = 0; i < 1200; i++)
// 	{
// 		testsOutput[i] = 150*sin(double((i+100)*PI/180));
// 	}
// 	m_pPlot[0]->insertOutputCurve(testsOutput,sizeof(testsOutput)/sizeof(double));
// }

// void QSttMUTestFirstCwWidget::InitTestUI()
// {	
// 	m_pPlot[0] = new QSttRecordChComparePlot(STT_RECORD_CH_TYPE_U,this);
// 	m_strTitle[0] = QString::fromLocal8Bit(("测试"));
// 	m_pFCPlotGroup->addTab(m_pPlot[0], m_strTitle[0]);
// }

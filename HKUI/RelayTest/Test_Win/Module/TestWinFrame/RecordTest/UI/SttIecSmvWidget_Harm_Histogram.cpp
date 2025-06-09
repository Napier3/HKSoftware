#include "SttIecSmvWidget_Harm_Histogram.h"
#include <qwt_plot_grid.h>
#include "../../../../Module/SmartCap/XSmartCapMngr.h"

CSttIecSmvWidget_Harm_Histogram::CSttIecSmvWidget_Harm_Histogram(QWidget *parent)
   : QWidget(parent)
{
	m_pIecRcdFuncWidget = this;
	m_pDiscretChart = NULL;
	m_pVBoxLayout = NULL;
	

	InitYAxis();
	m_nUpdateCount = 0;
	m_nCurrChIndex = 0;
	m_nChans = 0;
	m_bUpdateFlag = FALSE;

	m_pSttIecRecordCbWidget = (QSttIecRecordCbWidget *)g_pSttIecRecordCbWidget;
	m_pSttIecRecordCbWidget->BtnPreNextEnabled(0);
}

CSttIecSmvWidget_Harm_Histogram::~CSttIecSmvWidget_Harm_Histogram()
{
	qDeleteAll(m_pDiscretChartAxisPlot);
	m_pDiscretChartAxisPlot.clear();
}


void CSttIecSmvWidget_Harm_Histogram::InitUI()
{
	QGridLayout* pMainGridLayout = new QGridLayout;
	QScrollArea *pScrollArea = new QScrollArea(this);

	pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	if (m_StringListName.size() > 12 )
	{
		pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	}

	QWidget * pWgt = new QWidget(pScrollArea);
	pScrollArea->setWidgetResizable(true);// 自动调整大小
	m_pVBoxLayout = new QVBoxLayout(this);

	InitYAxisData(m_pCurrCapDevice,2);

	pWgt->setLayout(m_pVBoxLayout);
	pScrollArea->setWidget(pWgt);
	pMainGridLayout->addWidget(pScrollArea);
	setLayout(pMainGridLayout);
}

BOOL CSttIecSmvWidget_Harm_Histogram::NeedNextAndPrev()
{
	return TRUE;
}

void CSttIecSmvWidget_Harm_Histogram::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
	m_pCurrCapDevice = pCapDevice;

	InitUI();
}

 void CSttIecSmvWidget_Harm_Histogram::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
 {
	 CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	 CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	 pXSttCap_61850->UpdateDvmDeviceDatas();

	 m_nUpdateCount++;
	 if ((m_nUpdateCount%2) != 0)
	 {
		 return;
	 }

	if (m_bUpdateFlag)
	{	
		UpdateData();
	} 
 }

void CSttIecSmvWidget_Harm_Histogram::Release()
{
	delete this;
}


void CSttIecSmvWidget_Harm_Histogram::InitYAxis()
{
	m_StringListName.clear();
	CString strTemp;
	strTemp = _T("基波");

	m_StringListName.append(strTemp);
	strTemp = _T("次谐波");
	CString strNum[24] = {"","3", "", "5", "", "7"
		,"", "9", "", "11", "", "13", "", "15"
		,"", "17", "", "19", "", "21", "", "23"
		,"", "25"};


	for (int i=0; i<25;i++)
	{
		if (i%2 == 0)
		{	
			m_StringListName.append(strNum[i]);
		}
		else
		{
			m_StringListName.append(strNum[i] + strTemp);
		}
	}
}


	
void CSttIecSmvWidget_Harm_Histogram::InitYAxisData(CCapDeviceBase *pCapDevice,long nNum)
{
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();
	POS pos = pDvmDataset->GetHeadPosition();
	CExBaseObject *pObj = NULL;	

	while (pos != NULL)
	{	
		pObj = pDvmDataset->GetAtIndex(m_nCurrChIndex);
		if(m_nCurrChIndex >= nNum)
		{
			m_bUpdateFlag = TRUE;
			if (m_pDiscretChartAxisPlot.count() == 2)
			{
				for (int i = 0;i < 2; i++)
				{
					m_pDiscretChartAxisPlot[i]->setFixedHeight(150);
				}
			}

			return;
		}
		CString strChName ;
		CDvmData *pDvmData = (CDvmData*)pObj;
		if (pDvmData == NULL)
		{
			strChName.Format(_T("通道%d"),m_nCurrChIndex+1);//没有导入SCD文件
		}
		else
		{
			strChName = pDvmData->m_strName;//导入SCD文件
		}
		
		m_pDiscretChart = new QSttIecSmvAxisPlot(this);
		m_pDiscretChartAxisPlot.append(m_pDiscretChart);

		m_pDiscretChart->setAxisTitle(QwtPlot::yLeft, strChName);
		QwtPlotGrid *grid = new QwtPlotGrid;//设置格网
		grid->setMajorPen(QColor(193, 193, 193), 1, Qt::SolidLine);
		grid->attach(m_pDiscretChart);
		m_pVBoxLayout->addWidget(m_pDiscretChart);

		for (int nHarm =0; nHarm < 25; nHarm++)
		{
			m_dValue.clear();
			CString strID;
			if(nHarm == 0)
			{
				ShowValue(pDvmData,_T("$Base"));//基波
			}
			else
			{
				strID.Format(_T("$h%d"), nHarm+1);//谐波
				ShowValue(pDvmData, strID);
			}

			m_dValues += m_dValue;
		}

		m_pDiscretChart->InitBarChat(m_dValues, m_StringListName);
		m_dValue.clear();
		m_dValues.clear(); 

		m_nCurrChIndex++;
	}
}


void CSttIecSmvWidget_Harm_Histogram::UpdateData()
{
	CDvmDataset *pDvmDataset = m_pCurrCapDevice->GetDvmDataset();
	POS pos = pDvmDataset->GetHeadPosition();
	CExBaseObject *pObj = NULL;	
	
	long nIndex = 0;
	long nCurrChIndex = 0;
	if (m_pDiscretChartAxisPlot.count() == 1)
	{
		nCurrChIndex = m_nCurrChIndex-1;
	}
	else
	{
		nCurrChIndex = m_nCurrChIndex-2;
	}
	
	while (pos != NULL)
	{	
		pObj = pDvmDataset->GetAtIndex(nCurrChIndex);

		if(nCurrChIndex >= m_nCurrChIndex)
		{
			if (m_pDiscretChartAxisPlot.count() == 2)
			{
				for (int i = 0;i < 2; i++)
				{
					m_pDiscretChartAxisPlot[i]->setFixedHeight(150);
				}
			}
			return;
		}
		CDvmData *pDvmData = (CDvmData*)pObj;

		for (int nHarm=0; nHarm<25;nHarm++)
		{
			m_dValue.clear();
			CString strID;
			if(nHarm == 0)
			{
				ShowValue(pDvmData,_T("$Base"));
			}
			else
			{
				strID.Format(_T("$h%d"), nHarm+1);
				ShowValue(pDvmData, strID);
			}

			m_dValues += m_dValue;
		}
		m_pDiscretChartAxisPlot[nIndex]->InitBarChat(m_dValues, m_StringListName);
		m_dValue.clear();
		m_dValues.clear(); 	
		nIndex++;
		nCurrChIndex++;
	}
}


void CSttIecSmvWidget_Harm_Histogram::ShowValue(CDvmData *pData,const CString &str)
{
	double dValue= 0;

	if (pData != NULL)
	{
		CString strID = pData->m_strID + str;
		CDvmValue *pFind = (CDvmValue*)pData->FindByID(strID);
		if (pFind == NULL)
		{
			//return;
		}
		else
		{
			dValue= CString_To_double(pFind->m_strValue);
		}
	}
	
	m_dValue += dValue;	
}


void CSttIecSmvWidget_Harm_Histogram::NextPage()
{	
	m_bUpdateFlag = FALSE;

	m_pSttIecRecordCbWidget->BtnPreNextEnabled(1);

	for (int i = 0; i < m_pDiscretChartAxisPlot.size(); ++i) 
	{ 
		delete m_pDiscretChartAxisPlot.at(i);
	} 
	m_pDiscretChartAxisPlot.clear();

	m_nChans = m_nCurrChIndex + 2;
	long nCount = m_pCurrCapDevice->GetCount();
	if (m_nChans >= nCount)
	{
		m_nCurrChIndex = m_nCurrChIndex;
		m_nChans = nCount;
		m_pSttIecRecordCbWidget->BtnPreNextEnabled(2);
	} 
	InitYAxisData(m_pCurrCapDevice,m_nChans);
}

void CSttIecSmvWidget_Harm_Histogram::PrevPage()
{
	m_bUpdateFlag = FALSE;

	m_pSttIecRecordCbWidget->BtnPreNextEnabled(1);

	if(m_pDiscretChartAxisPlot.count() == 1)
	{
		m_nCurrChIndex = m_nCurrChIndex -3 ;
	}
	else
	{
		m_nCurrChIndex = m_nCurrChIndex - 4 ;
	}

	if (m_nCurrChIndex == 0)
	{
		m_nChans = 2;
		m_pSttIecRecordCbWidget->BtnPreNextEnabled(0);
	}
	else
	{
		m_nChans = m_nCurrChIndex +2;	
	}

	for (int i = 0; i < m_pDiscretChartAxisPlot.size(); ++i) 
	{ 
		delete m_pDiscretChartAxisPlot.at(i);
	} 
	m_pDiscretChartAxisPlot.clear();

	InitYAxisData(m_pCurrCapDevice,m_nChans);
}

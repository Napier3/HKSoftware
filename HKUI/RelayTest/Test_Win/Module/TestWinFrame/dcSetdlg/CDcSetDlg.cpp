#include "CDcSetDlg.h"
#include "../../../Module/Log/LogPrint.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../Module/TestWinFrame/channelParaset/QBasicTestParaSet.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

extern TMT_SYSTEM_DEFAULT_OUTPUT_PARAS g_oDefaultOutputPara;

CDcSetDlg::CDcSetDlg(QWidget *pParent)
:QDialog(pParent)
{
	m_pParaTab = NULL;
	m_pSyncParaSet = NULL;
	m_plbDcValue = NULL;
	m_pedtDcValue = NULL;
	m_pbtnDCStart = NULL;
	m_pbtnDCEnd = NULL;
	m_pbtnACStart = NULL;
	m_pbtnACEnd = NULL;
	m_pMainLayout = NULL;
	
	m_bDCStarted = false;
	m_bACStarted = false;
	initUI(); 
	initSignalSlots();
}

CDcSetDlg::~CDcSetDlg()
{

}

void CDcSetDlg::initUI()
{
	if(g_oSttTestResourceMngr.IsAsyncMode())
	{
		if (m_pParaTab == NULL)
		{
			m_pParaTab =  new ParaTab(this);
		}
	}
	else
	{
		if (m_pSyncParaSet == NULL)
		{
			m_pSyncParaSet = new QBasicTestParaSet(this);
		}
	}
	
	if (m_plbDcValue == NULL)
	{
		m_plbDcValue = new QLabel(/*tr("辅助直流电压(V)")*/g_sLangTxt_Native_auxiliary_DCvol);
	}

	if (m_pedtDcValue == NULL)
	{
		m_pedtDcValue = new QLineEdit();
	}

	if (m_pbtnDCStart == NULL)
	{
		m_pbtnDCStart = new QPushButton(/*tr("开始直流输出")*/g_sLangTxt_Native_start_DC_output);
	}

	if (m_pbtnDCEnd == NULL)
	{
		m_pbtnDCEnd = new QPushButton(/*tr("停止直流输出")*/g_sLangTxt_Native_stop_DC_output);
	}

	if (m_pbtnACStart == NULL)
	{
		m_pbtnACStart = new QPushButton(/*tr("开始稳态量输出")*/g_sLangTxt_Native_start_steadyoutput);
	}

	if (m_pbtnACEnd == NULL)
	{
		m_pbtnACEnd = new QPushButton(/*tr("停止稳态量输出")*/g_sLangTxt_Native_stop_steadyoutput);
	}

	if (m_pMainLayout == NULL)
	{
		QHBoxLayout *pHLay1 = new QHBoxLayout;
		pHLay1->addWidget(m_plbDcValue);
		pHLay1->addWidget(m_pedtDcValue);
		pHLay1->addStretch();
		pHLay1->addWidget(m_pbtnDCStart);
		pHLay1->addWidget(m_pbtnDCEnd);

		QHBoxLayout *pHLay2 = new QHBoxLayout;
		pHLay2->addStretch();
		pHLay2->addWidget(m_pbtnACStart);
		pHLay2->addWidget(m_pbtnACEnd);
		pHLay2->addStretch();

		m_pMainLayout=new QVBoxLayout;
		m_pMainLayout->addLayout(pHLay1);
		if(g_oSttTestResourceMngr.IsAsyncMode())
		{
			m_pMainLayout->addWidget(m_pParaTab);
		}
		else
		{
			m_pMainLayout->addWidget(m_pSyncParaSet);
		}
		m_pMainLayout->addLayout(pHLay2);	
		setLayout(m_pMainLayout); 
	}

	m_plbDcValue->hide();
	m_pedtDcValue->hide();
	m_pbtnDCStart->hide();
	m_pbtnDCEnd->hide();

	if(g_oSttTestResourceMngr.IsAsyncMode())
	{
		m_pParaTab->initUI();
	}

	setWindowTitle(/*tr("交直流稳态输出")*/g_sLangTxt_Native_AC_DC_steadyoutput);

	Qt::WindowFlags flags= this->windowFlags();
	setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);
}

void CDcSetDlg::setData(bool bACStarted,bool bDCStarted)
{ 
	if(g_oSttTestResourceMngr.IsAsyncMode())
	{
		if (g_oSystemParas.m_nHasAnalog)
		{
			m_pParaTab->getAnaParaSet()->setPropertyOfParaSet(P_Analog,g_oSttTestResourceMngr.m_pTestResouce
				,g_oDefaultOutputPara.m_uiVOL,g_oDefaultOutputPara.m_uiCUR);
			m_pParaTab->getAnaParaSet()->setMaxMinAndEDVal();
		}

		if (g_oSystemParas.m_nHasDigital)
		{
			m_pParaTab->getDigParaSet()->setPropertyOfParaSet(P_Digit,g_oSttTestResourceMngr.m_pTestResouce
				,g_oDefaultOutputPara.m_uiVOL,g_oDefaultOutputPara.m_uiCUR);	
			m_pParaTab->getDigParaSet()->setMaxMinAndEDVal();
		}

		if (g_oSystemParas.m_nHasWeek)
		{
			m_pParaTab->getLowSParaSet()->setPropertyOfParaSet(P_LowSignal,g_oSttTestResourceMngr.m_pTestResouce
				,g_oDefaultOutputPara.m_uiVOL,g_oDefaultOutputPara.m_uiCUR);	
			m_pParaTab->getLowSParaSet()->setMaxMinAndEDVal();
		}
	}
	else
	{
		if (m_pSyncParaSet)
		{
			m_pSyncParaSet->setPropertyOfParaSet(P_Common,g_oSttTestResourceMngr.m_pTestResouce,g_oDefaultOutputPara.m_uiVOL,g_oDefaultOutputPara.m_uiCUR);
			m_pSyncParaSet->setMaxMinAndEDVal();
		}
	}

	m_pedtDcValue->setText("0");
	setAusDCOutputState(bACStarted,bDCStarted);
}

void CDcSetDlg::initSignalSlots()
{
	connect(m_pbtnDCStart, SIGNAL(clicked()), this, SLOT(slot_DCStartClicked()));
	connect(m_pbtnDCEnd, SIGNAL(clicked()), this, SLOT(slot_DCEndClicked()));
	connect(m_pbtnACStart, SIGNAL(clicked()), this, SLOT(slot_ACStartClicked()));
	connect(m_pbtnACEnd, SIGNAL(clicked()), this, SLOT(slot_ACEndClicked()));
}

void CDcSetDlg::slot_DCStartClicked()
{
	QString str = m_pedtDcValue->text();
	float fDcVal = 0;
	if (str.isEmpty())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,/*_T("辅助直流输出不可为空")*/g_sLangTxt_Native_auxiDC_output_notempty.GetString());
		return;
	}

	fDcVal = str.toFloat();
	if (fDcVal <= EPSINON)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,/*_T("要求：辅助直流输出>0")*/g_sLangTxt_Native_auxiDC_output_positive.GetString());
		return;
	}

// 	g_oDefaultOutputPara.m_bKeepLoad = m_bACStarted;
// 	g_oDefaultOutputPara.m_fVolAux = fDcVal;

	emit sig_DCStartClicked();
}

void CDcSetDlg::slot_DCEndClicked()
{
// 	g_oDefaultOutputPara.m_bKeepLoad = m_bACStarted;
// 	g_oDefaultOutputPara.m_fVolAux = 0;
	emit sig_DCEndClicked();
}

void CDcSetDlg::slot_ACStartClicked()
{
// 	if (!m_bDCStarted)
// 	{
// 		g_oDefaultOutputPara.m_fVolAux = 0;
// 	}
	g_oDefaultOutputPara.m_bUseSysOutput = true;
	emit sig_ACStartClicked();
}

void CDcSetDlg::slot_ACEndClicked()
{
// 	if (!m_bDCStarted)
// 	{
// 		g_oDefaultOutputPara.m_fVolAux = 0;
// 	}

	g_oDefaultOutputPara.m_bUseSysOutput = false;
	emit sig_ACEndClicked();
}

void CDcSetDlg::setAusDCOutputState(bool bACStarted,bool bDCStarted)
{
	m_bDCStarted = bDCStarted;
	m_bACStarted = bACStarted;

	if(g_oSttTestResourceMngr.IsAsyncMode())
	{
		m_pParaTab->setDisabled(bACStarted);
	}
	else
	{
		m_pSyncParaSet->setDisabled(bACStarted);
	}

	m_pbtnACStart->setDisabled(bACStarted);
	m_pbtnACEnd->setDisabled(!bACStarted);

	m_pedtDcValue->setDisabled(bDCStarted);
	m_pbtnDCStart->setDisabled(bDCStarted);
	m_pbtnDCEnd->setDisabled(!bDCStarted);
}

void CDcSetDlg::keyPressEvent(QKeyEvent *event)
{
	int key = event->key();
	if (key == Qt::Key_Enter||key == Qt::Key_Return)
	{
		slot_ACStartClicked();
	}
}
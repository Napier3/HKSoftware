#include "StateButtonWidget.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../SttTestCntrFrameBase.h"

QStateButtonWidget::QStateButtonWidget(bool bHorizontal,QWidget *parent)
	: QWidget(parent)
{
	m_bHorizontal = bHorizontal;
	m_nCurStateIndex = 0;
	initUI();
	SetStateButtonFont();
	
}

QStateButtonWidget::~QStateButtonWidget()
{
	
}

void QStateButtonWidget::SetStateButtonFont()
{
    //m_pPasteStateBF->setFont(*g_pSttGlobalFont);
	m_pPreviosState->setFont(*g_pSttGlobalFont);
	m_pNextState->setFont(*g_pSttGlobalFont);
	m_pInsertStateBF->setFont(*g_pSttGlobalFont);
	m_pInsertStateAF->setFont(*g_pSttGlobalFont);
	//m_pPasteStateAF->setFont(*g_pSttGlobalFont);
	//m_pCopyState->setFont(*g_pSttGlobalFont);
	m_pDeleteState->setFont(*g_pSttGlobalFont);
	m_pStatesComBox->setFont(*g_pSttGlobalFont);
}

void QStateButtonWidget::AddPushButton(QPushButton** ppBtn,QString strName,int nFontSize)
{
	(*ppBtn) = new QPushButton(strName);
	QFont font = (*ppBtn)->font();
	font.setPixelSize(nFontSize);
	(*ppBtn)->setFont(font);
}

void QStateButtonWidget::AddComBox(QScrollComboBox** ppComBox,int nFontSize)
{
	(*ppComBox) = new QScrollComboBox();
	QFont font = (*ppComBox)->font();
	font.setPixelSize(nFontSize);
	(*ppComBox)->setFont(font);
}

void QStateButtonWidget::initUI()
{
    //AddPushButton(&m_pPasteStateBF,QString(tr("Õ³Ìù×´Ì¬¡ªÇ°")),18);
	//AddPushButton(&m_pInsertStateBF,QString(tr("²åÈë×´Ì¬¡ªÇ°")),18);
	CString strText;
	strText = _T("ÉÏÒ»×´Ì¬");
	AddPushButton(&m_pPreviosState,strText/*QString(tr("ÉÏÒ»×´Ì¬"))*/,18);
	AddComBox(&m_pStatesComBox,18);
	strText = _T("ÏÂÒ»×´Ì¬");
	AddPushButton(&m_pNextState,strText/*QString(tr("ÏÂÒ»×´Ì¬"))*/,18);
	strText = _T("²åÈë×´Ì¬¡ªÇ°");
	AddPushButton(&m_pInsertStateBF,strText/*QString(tr("²åÈë×´Ì¬¡ªÇ°"))*/,18);
	strText = _T("²åÈë×´Ì¬¡ªºó");
	AddPushButton(&m_pInsertStateAF,strText/*QString(tr("²åÈë×´Ì¬¡ªºó"))*/,18);
	//AddPushButton(&m_pPasteStateAF,QString(tr("Õ³Ìù×´Ì¬¡ªºó")),18);
	//AddPushButton(&m_pCopyState,QString(tr("¿½±´µ±Ç°×´Ì¬")),18);
	strText = _T("É¾³ýµ±Ç°×´Ì¬");
	AddPushButton(&m_pDeleteState,strText/*QString(tr("É¾³ýµ±Ç°×´Ì¬"))*/,18);
	
    //xlang_SetLangStrToWidget(m_pPasteStateBF, "State_PasteStateBf", XLang_Ctrls_QPushButton);
// 	xlang_SetLangStrToWidget(m_pPreviosState, "State_PreviosState", XLang_Ctrls_QPushButton);
//     xlang_SetLangStrToWidget(m_pNextState, "State_NextState", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pInsertStateBF, "State_InsertStateBf", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pInsertStateAF, "State_InsertStateAf", XLang_Ctrls_QPushButton);
    //xlang_SetLangStrToWidget(m_pPasteStateAF, "State_PasteStateAf", XLang_Ctrls_QPushButton);
	//xlang_SetLangStrToWidget(m_pCopyState, "State_CopyCurState", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pDeleteState, "State_DeleteCurState", XLang_Ctrls_QPushButton);

	QBoxLayout* pLayout = NULL;
	if (m_bHorizontal)
	{
		pLayout = new QHBoxLayout;
	}
	else
	{
		pLayout = new QVBoxLayout;
	}
    //pLayout->addWidget(m_pPasteStateBF);
	pLayout->addWidget(m_pPreviosState);
	pLayout->addWidget(m_pStatesComBox);
    pLayout->addWidget(m_pNextState);
	pLayout->addWidget(m_pInsertStateBF);
	pLayout->addWidget(m_pInsertStateAF);
	//pLayout->addWidget(m_pPasteStateAF);
	//pLayout->addWidget(m_pCopyState);
	pLayout->addWidget(m_pDeleteState);

	setLayout(pLayout);	
}

void QStateButtonWidget::setData(tmt_state_test* pStateTest)
{
	m_pStateTest = pStateTest;
	initBaseData();
}

void QStateButtonWidget::initBaseData()
{
	ASSERT(m_pStateTest != NULL);

	tmt_StatePara* m_pStatePara = NULL;
    CString strTmp;
	CString strState,strNo;
	xlang_GetLangStrByFile(strState,"Native_State");

	QStringList listStates;
	for (int i=0;i<m_pStateTest->m_oStateParas.m_nStateNumbers;i++)
	{
		m_pStatePara = &m_pStateTest->m_oStateParas.m_paraState[i];
		CString strStateName = (CString)m_pStatePara->m_strName;
		if (strStateName.GetLength()>0)
		{
			strTmp = QString::fromLocal8Bit(m_pStatePara->m_strName);
		}
		else
		{
			if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
			{
//              strTmp.Format("×´Ì¬%d",i+1);
				strNo.Format(_T("%d"),i+1);
				strTmp = strState;
				strTmp += strNo;
			}
			else
			{
				strTmp = QString("state%1").arg(i+1);
			}
		}

		listStates << strTmp;
	}

	m_pStatesComBox->clear();
	m_pStatesComBox->addItems(listStates);

	m_pStatesComBox->setCurrentIndex(m_nCurStateIndex);
}

void QStateButtonWidget::startInit()
{
	m_pPreviosState->setDisabled(true);
	m_pNextState->setDisabled(true);
	//m_pPasteStateBF->setDisabled(true);
	m_pInsertStateBF->setDisabled(true);
	m_pInsertStateAF->setDisabled(true);
	//m_pPasteStateAF->setDisabled(true);
	//m_pCopyState->setDisabled(true);
	m_pDeleteState->setDisabled(true);
	m_pStatesComBox->setDisabled(true);
}

void QStateButtonWidget::stopInit(BOOL bHasPasteState)
{
/*if (bHasPasteState)
	{
		m_pPasteStateBF->setDisabled(false);
		m_pPasteStateAF->setDisabled(false);
	} 
	else
	{
		m_pPasteStateBF->setDisabled(true);
		m_pPasteStateAF->setDisabled(true);
	}
*/
	m_pPreviosState->setDisabled(false);
	m_pNextState->setDisabled(false);
	m_pInsertStateBF->setDisabled(false);
	m_pInsertStateAF->setDisabled(false);
    //m_pCopyState->setDisabled(false);
	m_pDeleteState->setDisabled(false);
	m_pStatesComBox->setDisabled(false);
}

void QStateButtonWidget::UpdateStateCombox()
{
	initBaseData();
}

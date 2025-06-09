#include "StateButtonWidget.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
//#include "../SttTestCntrFrameBase.h"
#include "../../Module/XLangResource_Native.h"
#include "../../Module/SttTest/Common/PrimFreq/tmt_prim_freq_state_test.h"


QStateButtonWidget::QStateButtonWidget(bool bHorizontal,QWidget *parent, bool bFrimFreqModel)
	: QWidget(parent)
{
    m_pnCurStateIndex = NULL;
	m_bHorizontal = bHorizontal;
	initUI(bFrimFreqModel);
	SetStateButtonFont();
   
	//2023-2-3  lijunqing ±ÜÃâ³õÊ¼»¯Ê±¶à´Îµ÷ÓÃ  slot_StatesIndexChanged
	m_bEnable_slot_StatesIndexChanged = false;
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
	m_pBtnEditState->setFont(*g_pSttGlobalFont);
	//m_pPasteStateAF->setFont(*g_pSttGlobalFont);
	//m_pCopyState->setFont(*g_pSttGlobalFont);
	m_pDeleteState->setFont(*g_pSttGlobalFont);
	m_pStatesComBox->setFont(*g_pSttGlobalFont);
}

void QStateButtonWidget::EnableButtons()
{
	int nCurStateIndex = m_pStatesComBox->currentIndex();

	if (nCurStateIndex <= 0)
	{
		m_pPreviosState->setEnabled(false);
	}
	else
	{
		m_pPreviosState->setEnabled(true);
	}

	long nMaxState = m_pStatesComBox->count();

	if((nCurStateIndex+1) >= nMaxState)
	{
		m_pNextState->setEnabled(false);
	}
	else
	{
		m_pNextState->setEnabled(true);
	}
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

void QStateButtonWidget::initUI( bool bFrimFreq)
{
    //AddPushButton(&m_pPasteStateBF,QString(tr("Õ³Ìù×´Ì¬¡ªÇ°")),18);
	//AddPushButton(&m_pInsertStateBF,QString(tr("²åÈë×´Ì¬¡ªÇ°")),18);
	//CString strText;
	//strText = _T("ÉÏÒ»×´Ì¬");

	AddPushButton(&m_pPreviosState,g_sLangTxt_State_PreviosState/*QString(tr("ÉÏÒ»×´Ì¬"))*/,18);//ÉÏÒ»×´Ì¬-LCQ
	AddComBox(&m_pStatesComBox,18);
	//strText = _T("ÏÂÒ»×´Ì¬");
	AddPushButton(&m_pNextState,g_sLangTxt_State_NextState/*QString(tr("ÏÂÒ»×´Ì¬"))*/,18);//ÏÂÒ»×´Ì¬-LCQ
	//strText = _T("²åÈë×´Ì¬¡ªÇ°");
	AddPushButton(&m_pInsertStateBF,g_sLangTxt_State_InsertStateBf/*QString(tr("²åÈë×´Ì¬¡ªÇ°"))*/,18);//²åÈë×´Ì¬¡ªÇ°-LCQ
	//strText = _T("²åÈë×´Ì¬¡ªºó");
	AddPushButton(&m_pInsertStateAF,g_sLangTxt_State_InsertStateAf/*QString(tr("²åÈë×´Ì¬¡ªºó"))*/,18);//²åÈë×´Ì¬-ºó-LCQ
	//AddPushButton(&m_pPasteStateAF,QString(tr("Õ³Ìù×´Ì¬¡ªºó")),18);
	//AddPushButton(&m_pCopyState,QString(tr("¿½±´µ±Ç°×´Ì¬")),18);
	//strText = _T("É¾³ýµ±Ç°×´Ì¬");
	AddPushButton(&m_pDeleteState,g_sLangTxt_State_DeleteCurState/*QString(tr("É¾³ýµ±Ç°×´Ì¬"))*/,18);//É¾³ýµ±Ç°×´Ì¬-LCQ
	//strText = _T("×´Ì¬±à¼­");
	AddPushButton(&m_pBtnEditState, g_sLangTxt_State_StatusEdition,18);//×´Ì¬±à¼­-LCQ
	
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

#ifndef _PSX_QT_LINUX_
	if(!bFrimFreq)
	{
	pLayout->addWidget(m_pBtnEditState);
	}
#endif

	setLayout(pLayout);	
}

void QStateButtonWidget::setData(tmt_state_paras* pStateParas, bool bFrimFreq)
{	
	m_pStateParas = pStateParas;

	initBaseData(bFrimFreq);
}

void QStateButtonWidget::initBaseData(bool bFrimFreq )
{
	ASSERT(m_pStateParas != NULL);

    CString strTmp;
	CString strState,strNo;
	xlang_GetLangStrByFile(strState,"sState");

	QStringList listStates;

	tmt_PrimFreqStateParas *pPrimParas = NULL;
	if (bFrimFreq)
	{
		pPrimParas = (tmt_PrimFreqStateParas *)m_pStateParas;
	}

	int nStateNumbers = bFrimFreq ? pPrimParas->m_nStateNumbers : m_pStateParas->m_nStateNumbers;
	tmt_StatePara* pStatePara = NULL;
	tmt_PrimFreqStatePara *pPrimFreqPara = NULL;

	for (int i = 0; i < nStateNumbers; i++)
	{
// 		tmt_StatePara* pStatePara = bFrimFreq ? &pPrimParas->m_paraPrimFreqState[i] : &m_pStateParas->m_paraState[i];
		CString strStateName;
		QString strTmp;
		if(bFrimFreq)
		{
			pPrimFreqPara = &pPrimParas->m_paraPrimFreqState[i];
			strStateName = (CString)pPrimFreqPara->m_strName;
			strTmp;

			if (strStateName.GetLength() > 0)
			{
				strTmp = QString::fromLocal8Bit(pPrimFreqPara->m_strName);
			}
			else
			{
				QString strNo = QString::number(i + 1);
				if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
				{
					strTmp = strState + strNo;
				}
				else
				{
					strTmp = QString("state%1").arg(i + 1);
				}
			}
// 			listStates << strTmp;
		}
		else
		{
			pStatePara = &m_pStateParas->m_paraState[i];
			strStateName = (CString)pStatePara->m_strName;
			strTmp;

			if (strStateName.GetLength() > 0)
		{
				strTmp = QString::fromLocal8Bit(pStatePara->m_strName);
		}
		else
		{
				QString strNo = QString::number(i + 1);
			if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
			{
					strTmp = strState + strNo;
			}
			else
			{
					strTmp = QString("state%1").arg(i + 1);
				}
			}
		}

		listStates << strTmp;
	}

	m_pStatesComBox->clear();
	m_pStatesComBox->addItems(listStates);

	m_bEnable_slot_StatesIndexChanged = true;
	m_pStatesComBox->setCurrentIndex(*m_pnCurStateIndex); 
}

void QStateButtonWidget::startInit()
{
	setEnabled(false);
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
	setEnabled(true);
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
// 	m_pPreviosState->setDisabled(false);
// 	m_pNextState->setDisabled(false);
	m_pInsertStateBF->setDisabled(false);
	m_pInsertStateAF->setDisabled(false);
    //m_pCopyState->setDisabled(false);
	m_pDeleteState->setDisabled(false);
	m_pStatesComBox->setDisabled(false);
	EnableButtons();
}

void QStateButtonWidget::UpdateStateCombox( bool bFrimFreq)
{
	initBaseData(bFrimFreq);
}

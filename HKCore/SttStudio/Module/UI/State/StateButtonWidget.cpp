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
   
	//2023-2-3  lijunqing �����ʼ��ʱ��ε���  slot_StatesIndexChanged
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
    //AddPushButton(&m_pPasteStateBF,QString(tr("ճ��״̬��ǰ")),18);
	//AddPushButton(&m_pInsertStateBF,QString(tr("����״̬��ǰ")),18);
	//CString strText;
	//strText = _T("��һ״̬");

	AddPushButton(&m_pPreviosState,g_sLangTxt_State_PreviosState/*QString(tr("��һ״̬"))*/,18);//��һ״̬-LCQ
	AddComBox(&m_pStatesComBox,18);
	//strText = _T("��һ״̬");
	AddPushButton(&m_pNextState,g_sLangTxt_State_NextState/*QString(tr("��һ״̬"))*/,18);//��һ״̬-LCQ
	//strText = _T("����״̬��ǰ");
	AddPushButton(&m_pInsertStateBF,g_sLangTxt_State_InsertStateBf/*QString(tr("����״̬��ǰ"))*/,18);//����״̬��ǰ-LCQ
	//strText = _T("����״̬����");
	AddPushButton(&m_pInsertStateAF,g_sLangTxt_State_InsertStateAf/*QString(tr("����״̬����"))*/,18);//����״̬-��-LCQ
	//AddPushButton(&m_pPasteStateAF,QString(tr("ճ��״̬����")),18);
	//AddPushButton(&m_pCopyState,QString(tr("������ǰ״̬")),18);
	//strText = _T("ɾ����ǰ״̬");
	AddPushButton(&m_pDeleteState,g_sLangTxt_State_DeleteCurState/*QString(tr("ɾ����ǰ״̬"))*/,18);//ɾ����ǰ״̬-LCQ
	//strText = _T("״̬�༭");
	AddPushButton(&m_pBtnEditState, g_sLangTxt_State_StatusEdition,18);//״̬�༭-LCQ
	
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

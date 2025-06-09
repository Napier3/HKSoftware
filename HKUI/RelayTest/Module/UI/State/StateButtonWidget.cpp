#include "StateButtonWidget.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
//#include "../SttTestCntrFrameBase.h"
#include "../../Module/XLangResource_Native.h"
#include "SttMacroParaEditViewState.h"

QStateButtonWidget::QStateButtonWidget(bool bHorizontal,QWidget *parent)
	: QWidget(parent)
{
    m_pnCurStateIndex = NULL;
	m_bHorizontal = bHorizontal;
	initUI();
	SetStateButtonFont();
   
	//2023-2-3  lijunqing 避免初始化时多次调用  slot_StatesIndexChanged
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

void QStateButtonWidget::initUI()
{
    //AddPushButton(&m_pPasteStateBF,QString(tr("粘贴状态—前")),18);
	//AddPushButton(&m_pInsertStateBF,QString(tr("插入状态—前")),18);
	//CString strText;
	//strText = _T("上一状态");

	AddPushButton(&m_pPreviosState,g_sLangTxt_State_PreviosState/*QString(tr("上一状态"))*/,18);//上一状态-LCQ
	AddComBox(&m_pStatesComBox,18);
	//strText = _T("下一状态");
	AddPushButton(&m_pNextState,g_sLangTxt_State_NextState/*QString(tr("下一状态"))*/,18);//下一状态-LCQ
	//strText = _T("插入状态—前");
	AddPushButton(&m_pInsertStateBF,g_sLangTxt_State_InsertStateBf/*QString(tr("插入状态—前"))*/,18);//插入状态—前-LCQ
	//strText = _T("插入状态—后");
	AddPushButton(&m_pInsertStateAF,g_sLangTxt_State_InsertStateAf/*QString(tr("插入状态—后"))*/,18);//插入状态-后-LCQ
	//AddPushButton(&m_pPasteStateAF,QString(tr("粘贴状态—后")),18);
	//AddPushButton(&m_pCopyState,QString(tr("拷贝当前状态")),18);
	//strText = _T("删除当前状态");
	AddPushButton(&m_pDeleteState,g_sLangTxt_State_DeleteCurState/*QString(tr("删除当前状态"))*/,18);//删除当前状态-LCQ
	//strText = _T("状态编辑");
	AddPushButton(&m_pBtnEditState, g_sLangTxt_State_StatusEdition,18);//状态编辑-LCQ
	
    //xlang_SetLangStrToWidget(m_pPasteStateBF, "State_PasteStateBf", XLang_Ctrls_QPushButton);
// 	xlang_SetLangStrToWidget(m_pPreviosState, "State_PreviosState", XLang_Ctrls_QPushButton);
//     xlang_SetLangStrToWidget(m_pNextState, "State_NextState", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pInsertStateBF, "State_InsertStateBf", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pInsertStateAF, "State_InsertStateAf", XLang_Ctrls_QPushButton);
    //xlang_SetLangStrToWidget(m_pPasteStateAF, "State_PasteStateAf", XLang_Ctrls_QPushButton);
	//xlang_SetLangStrToWidget(m_pCopyState, "State_CopyCurState", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pDeleteState, "State_DeleteCurState", XLang_Ctrls_QPushButton);

	//2024-8-9 wuxy 修改控件统一高度
#ifdef _PSX_QT_WINDOWS_
	int nFixHeight = 25;
	m_pPreviosState->setMinimumHeight(nFixHeight);
	m_pStatesComBox->setMinimumHeight(nFixHeight);
	m_pInsertStateBF->setMinimumHeight(nFixHeight);
	m_pNextState->setMinimumHeight(nFixHeight);
	m_pInsertStateAF->setMinimumHeight(nFixHeight);
	m_pDeleteState->setMinimumHeight(nFixHeight);
	m_pBtnEditState->setMinimumHeight(nFixHeight);
#endif


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
	pLayout->addWidget(m_pBtnEditState);
#endif

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

	tmt_StatePara* pStatePara = NULL;
    CString strTmp;
	CString strState,strNo;
	xlang_GetLangStrByFile(strState,"sState");

	g_pStateTest->m_SelStateList.clear();

	QStringList listStates;
	for (int i=0;i<m_pStateTest->m_oStateParas.m_nStateNumbers;i++)
	{
		pStatePara = &m_pStateTest->m_oStateParas.m_paraState[i];

		//2024-8-27 wuxinyi 按需求状态不勾选时下拉框中不可显示
		if (!pStatePara->m_bSelected)
		{
			continue;
		}
		g_pStateTest->m_SelStateList.append(i);

		CString strStateName = (CString)pStatePara->m_strName;
		if (strStateName.GetLength()>0)
		{
			strTmp = QString::fromLocal8Bit(pStatePara->m_strName);
		}
		else
		{
			if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
			{
//              strTmp.Format("状态%d",i+1);
				strNo.Format(_T("%d"),i+1);
				strTmp = strState;
				strTmp += strNo;
			}
			else
			{
				strTmp = QString("state%1").arg(i+1);
			}
			CString_to_char(strTmp, pStatePara->m_strName);
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

void QStateButtonWidget::UpdateStateCombox()
{
	initBaseData();
}

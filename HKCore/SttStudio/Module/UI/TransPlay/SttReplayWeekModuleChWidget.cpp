#include "SttReplayWeekModuleChWidget.h"
// #include "../../Module/XLangResource_Native.h"
// #include"../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "SttReplayParaSetWidget.h"

extern QFont *g_pSttGlobalFont;

CSttReplayWeekModuleChWidget::CSttReplayWeekModuleChWidget(int nModuleIndex,CSttModuleComtradeBind *pModuleInfo,QWidget *pParent)
:CSttReplayModuleChWidget(nModuleIndex,pModuleInfo,pParent)
{
	// 	initUI();
}

CSttReplayWeekModuleChWidget::~CSttReplayWeekModuleChWidget()
{

}

void CSttReplayWeekModuleChWidget::initSignalSlots()
{
	CSttReplayModuleChWidget::initSignalSlots();

	for(int i=0; i<m_WeekChSelTypeList.size(); i++)
	{
		connect(m_WeekChSelTypeList.at(i), SIGNAL(currentIndexChanged(int)), this, SLOT(slot_WeekChSelTypeChanged(int)));
	}

}


void CSttReplayWeekModuleChWidget::uninitSignalSlots()
{
	CSttReplayModuleChWidget::uninitSignalSlots();

	for(int i=0; i<m_WeekChSelTypeList.size(); i++)
	{
		disconnect(m_WeekChSelTypeList.at(i), SIGNAL(currentIndexChanged(int)), this, SLOT(slot_WeekChSelTypeChanged(int)));
	}
}

void CSttReplayWeekModuleChWidget::SetChSelectList(const QStringList &oUChList,const QStringList &oIChList/*QStringList &oChSelectList*/)
{
	QStringList oUChListNew,oIChListNew;
	oUChListNew = oUChList;
	oIChListNew = oIChList;
	oUChListNew.insert(0,_T("0"));
	oIChListNew.insert(0,_T("0"));

	m_oIChList.clear();
	m_oUChList.clear();
	m_oIChList = oIChListNew;
	m_oUChList = oUChListNew;

	//更新界面
	uninitSignalSlots();

	QScrollComboBox *pAChSel = NULL;
	QScrollComboBox *pBChSel = NULL;
	QScrollComboBox *pWeekChTypeSel = NULL;
	CSttModuleChComtradeBind *pCh = NULL;
	CDvmData *pChData = NULL;

	int nChNum = m_ChSelList.size();
	long nValue = 0;
	long nChIndexA = 0,nChIndexB = 0;

	for(int nIndex=0; nIndex<nChNum; nIndex++)
	{
		pCh = (CSttModuleChComtradeBind *)m_pModuleInfo->GetAt(nIndex);
		pAChSel = m_AChSelList.at(nIndex);
		pBChSel = m_BChSelList.at(nIndex);
		pAChSel->clear();
		pBChSel->clear();
		//更新通道数据

		int nEleType = pCh->GetEleTypeIndex();

		m_ChSelList.at(nIndex)->setChecked(pCh->m_nChSelected);

		if(nEleType == REPLAY_WEEK_CH_ELETYPE_VOL)
		{
			pAChSel->addItems(oUChListNew);
			pBChSel->addItems(oUChListNew);
			nChIndexA = oUChListNew.indexOf(pCh->m_strComtradeChID_A);
			nChIndexB = oUChListNew.indexOf(pCh->m_strComtradeChID_B);
		} 
		else
		{
			pAChSel->addItems(oIChListNew);
			pBChSel->addItems(oIChListNew);
			nChIndexA = oIChListNew.indexOf(pCh->m_strComtradeChID_A);
			nChIndexB = oIChListNew.indexOf(pCh->m_strComtradeChID_B);
		}

		if (nChIndexA<0)
		{
			nChIndexA = 0;
		}

		if (nChIndexB<0)
		{
			nChIndexB = 0;
		}

		pAChSel->setCurrentIndex(nChIndexA);
		pBChSel->setCurrentIndex(nChIndexB);
		m_KEditList.at(nIndex)->setText(QString::number(pCh->m_dK, 'f', 2));
	}

	m_pPTPrim_Edit->SetValue(m_pModuleInfo->m_fPTRatio[0]);
	m_pPTSecond_Edit->SetValue(m_pModuleInfo->m_fPTRatio[1]);
	m_pCTPrim_Edit->SetValue(m_pModuleInfo->m_fCTRatio[0]);
	m_pCTSecond_Edit->SetValue(m_pModuleInfo->m_fCTRatio[1]);

	initSignalSlots();
}


void CSttReplayWeekModuleChWidget::SetWeekEeType()
{
	CSttModuleChComtradeBind *pCh = NULL;
	CDvmData *pChData = NULL;
	QScrollComboBox *pWeekChTypeSel = NULL;
	int nChNum = m_WeekChSelTypeList.size();
	int nEeType = 0;

	for(int nIndex=0; nIndex<nChNum; nIndex++)
	{
		pCh = (CSttModuleChComtradeBind *)m_pModuleInfo->GetAt(nIndex);
		pWeekChTypeSel = m_WeekChSelTypeList.at(nIndex);
		//pWeekChTypeSel->clear();

		nEeType = pCh->GetEleTypeIndex();
		if(nEeType >= 0)
		{
			pWeekChTypeSel->setCurrentIndex(nEeType);
		}

	}

}

void CSttReplayWeekModuleChWidget::setEnableStateUI(bool bEnable)
{
	CSttReplayModuleChWidget::setEnableStateUI(bEnable);

	for(int nIndex=0; nIndex<m_WeekChSelTypeList.size(); nIndex++)
	{
		m_WeekChSelTypeList.at(nIndex)->setEnabled(bEnable);
	}
}

void CSttReplayWeekModuleChWidget::slot_ChangedPT1()
{
	m_pModuleInfo->m_fPTRatio[0] = m_pPTPrim_Edit->GetValue();
	g_theBigComtradeTransPlay->m_oBigComtradeFileRead.OnPTChanged();
	((CSttReplayParaSetWidget*)GetParaSetWidget())->UpdateUIMax();
	emit sig_ModuleChRangeChanged();
}

void CSttReplayWeekModuleChWidget::slot_ChangedPT2()
{
	m_pModuleInfo->m_fPTRatio[1] = m_pPTSecond_Edit->GetValue();
	g_theBigComtradeTransPlay->m_oBigComtradeFileRead.OnPTChanged();
	((CSttReplayParaSetWidget*)GetParaSetWidget())->UpdateUIMax();
	emit sig_ModuleChRangeChanged();
}

void CSttReplayWeekModuleChWidget::slot_ChangedCT1()
{
	m_pModuleInfo->m_fCTRatio[0] = m_pCTPrim_Edit->GetValue();
	g_theBigComtradeTransPlay->m_oBigComtradeFileRead.OnCTChanged();
	((CSttReplayParaSetWidget*)GetParaSetWidget())->UpdateUIMax();
	emit sig_ModuleChRangeChanged();
}

void CSttReplayWeekModuleChWidget::slot_ChangedCT2()
{
	m_pModuleInfo->m_fCTRatio[1] = m_pCTSecond_Edit->GetValue();
	g_theBigComtradeTransPlay->m_oBigComtradeFileRead.OnCTChanged();
	((CSttReplayParaSetWidget*)GetParaSetWidget())->UpdateUIMax();
	emit sig_ModuleChRangeChanged();
}

void CSttReplayWeekModuleChWidget::UpdatePT_CT_Rates()
{
	m_pPTPrim_Edit->SetValue(m_pModuleInfo->m_fPTRatio[0]);
	m_pPTSecond_Edit->SetValue(m_pModuleInfo->m_fPTRatio[1]);
	m_pCTPrim_Edit->SetValue(m_pModuleInfo->m_fCTRatio[0]);
	m_pCTSecond_Edit->SetValue(m_pModuleInfo->m_fCTRatio[1]);
}

void CSttReplayWeekModuleChWidget::slot_WeekChSelTypeChanged( int nIndex )
{
	if(!m_pModuleInfo->IsWeekTypeModule())
	{
		return;
	}

	QScrollComboBox *pWeekChSelType = (QScrollComboBox *)sender();
	int nChIndex = m_WeekChSelTypeList.indexOf(pWeekChSelType);
	int nEleType = pWeekChSelType->currentIndex();

	CSttModuleChComtradeBind *pCh = (CSttModuleChComtradeBind *)m_pModuleInfo->GetAt(nChIndex);
	if(!pCh)
	{
		return;
	}

	pCh->SetEleType(nEleType);
	UpdateABChSelCmbChange(nChIndex, nEleType);
	// 	OnModuleChChanged()

}

void CSttReplayWeekModuleChWidget::UpdateABChSelCmbChange( int nChIndex, int nEleType )
{
	if(nChIndex < 0 || nEleType < 0)
	{
		return;
	}

	QScrollComboBox *pWeekChSelCmb = m_WeekChSelTypeList.at(nChIndex);
	QScrollComboBox *pAChSelCmb = m_AChSelList.at(nChIndex); 
	QScrollComboBox *pBChSelCmb = m_BChSelList.at(nChIndex);
	int nAChSel = pAChSelCmb->currentIndex();
	int nBChSel = pBChSelCmb->currentIndex();

	pAChSelCmb->clear();
	pBChSelCmb->clear();

	if(nEleType == REPLAY_WEEK_CH_ELETYPE_CURR)
	{
		pAChSelCmb->addItems(m_oIChList);
		pBChSelCmb->addItems(m_oIChList);
	}
	else if(nEleType == REPLAY_WEEK_CH_ELETYPE_VOL)
	{
		pAChSelCmb->addItems(m_oUChList);
		pBChSelCmb->addItems(m_oUChList);
	}

	pAChSelCmb->setCurrentIndex(nAChSel);
	pBChSelCmb->setCurrentIndex(nBChSel);

}

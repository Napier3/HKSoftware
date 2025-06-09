#include "QModuleSetWidget.h"
#include "../../Module/XLangResource_Native.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../SttSystemConfig/SttSystemConfig.h"

extern CFont *g_pSttGlobalFont;  
#define  STT_MODULE_L336D          "L336D"

QModuleSetWidget::QModuleSetWidget(QWidget *parent)
	: QWidget(parent)
{
//	m_nCurModuleNum = 0;
	m_pSysParas = NULL;
	m_nOldModuleSelIndex = 0;
}

QModuleSetWidget::~QModuleSetWidget()
{
	ReleaseUI();
}

void QModuleSetWidget::initUI(STT_SystemParas *pSysParas)
{
	ReleaseUI();
	m_pSysParas = pSysParas;
	m_pModuleSet_VBoxLayout = new QVBoxLayout(this);//整个通道映射的布局控件
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 	m_pStdValues_GroupBox = new QGroupBox(this);//第一行所有控件，放入该Group下
// 	m_pModuleSet_VBoxLayout->addWidget(m_pStdValues_GroupBox);
// 	m_pStdValues_GroupBox->setTitle(tr("额定值"));
// 	m_pStdValues_GridLayout = new QGridLayout(m_pStdValues_GroupBox);//在Group内部增加表格布局，表格布局中包含第一行全部控件
// 	m_pStdValues_GridLayout->setSpacing(10);//设置行间距
// 
// 	m_pStdVol_Label = new QLabel(m_pStdValues_GroupBox);
// 	m_pStdVol_Label->setText(tr("额定电压(V):"));
// 	m_pStdValues_GridLayout->addWidget(m_pStdVol_Label, 0, 0, 1, 1);
// 
// 	m_pStdVol_LineEdit = new QFloatLineEdit(m_pStdValues_GroupBox);
// 	m_pStdVol_LineEdit->InitCoverage(0,1000);
// 	m_pStdValues_GridLayout->addWidget(m_pStdVol_LineEdit, 0, 1, 1, 1);
// 
// 	m_pStdCur_Label = new QLabel(m_pStdValues_GroupBox);
// 	m_pStdCur_Label->setText(tr("额定电流(A):"));
// 	m_pStdValues_GridLayout->addWidget(m_pStdCur_Label, 0, 2, 1, 1);
// 
// 	m_pStdCur_LineEdit = new QFloatLineEdit(m_pStdValues_GroupBox);
// 	m_pStdCur_LineEdit->InitCoverage(0,100);
// 	m_pStdValues_GridLayout->addWidget(m_pStdCur_LineEdit, 0, 3, 1, 1);
// 
// 	m_pStdFre_Label = new QLabel(m_pStdValues_GroupBox);
// 	m_pStdFre_Label->setText(tr("额定频率(Hz):"));
// 	m_pStdValues_GridLayout->addWidget(m_pStdFre_Label, 1, 0, 1, 1);
// 
// 	m_pStdFre_LineEdit = new QFloatLineEdit(m_pStdValues_GroupBox);
// 	m_pStdFre_LineEdit->InitCoverage(0,3000);
// 	m_pStdValues_GridLayout->addWidget(m_pStdFre_LineEdit, 1, 1, 1, 1);
// 
// 	m_pAntiShakeTime_Label = new QLabel(m_pStdValues_GroupBox);
// 	m_pAntiShakeTime_Label->setText(tr("防抖时间(s):"));
// 	m_pStdValues_GridLayout->addWidget(m_pAntiShakeTime_Label, 1, 2, 1, 1);
// 
// 	m_pAntiShakeTime_LineEdit = new QFloatLineEdit(m_pStdValues_GroupBox);
// 	m_pAntiShakeTime_LineEdit->InitCoverage(0,10000);
// 	m_pStdValues_GridLayout->addWidget(m_pAntiShakeTime_LineEdit, 1, 3, 1, 1);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CString strText;
	//strText = _T("电流模块");
	m_pCurModule_GroupBox = new QSttGroupBox(this);
	m_pModuleSet_VBoxLayout->addWidget(m_pCurModule_GroupBox);
	m_pCurModule_GroupBox->setTitle(g_sLangTxt_Currentmodule); //lcq
	m_pCurModule_GridLayout = new QGridLayout(m_pCurModule_GroupBox);

	//strText = _T("电流模块选择:");
	m_pCurModuleSel_Label = new QLabel(m_pCurModule_GroupBox);
	m_pCurModuleSel_Label->setText(g_sLangTxt_CurrModuleSelect); //lcq
	m_pCurModule_GridLayout->setSpacing(10);//设置行间距
	m_pCurModule_GridLayout->addWidget(m_pCurModuleSel_Label, 0, 0, 1, 1);

	m_pCurModuleSel_ComboBox = new QComboBox(m_pCurModule_GroupBox);
	m_pCurModule_GridLayout->addWidget(m_pCurModuleSel_ComboBox, 0, 1, 1, 1);

	//strText = _T("电流档位设置:");
	m_pCurGear_Label = new QLabel(m_pCurModule_GroupBox);
	m_pCurModuleSel_Label->setText(g_sLangTxt_CurrModuleSelect); //lcq
	m_pCurGear_Label->setText(g_sLangTxt_Gradient_CurGSetting); 
	m_pCurModule_GridLayout->addWidget(m_pCurGear_Label, 1, 0, 1, 1);

	m_pCurGear_ComboBox = new QComboBox(m_pCurModule_GroupBox);
	m_pCurModule_GridLayout->addWidget(m_pCurGear_ComboBox, 1, 1, 1, 1);

	//strText = _T("最大端口电压(Vrms):");
	m_pCurMaxPortVol_Label = new QLabel(m_pCurModule_GroupBox);
	m_pCurModuleSel_Label->setText(g_sLangTxt_CurrModuleSelect); //lcq
	m_pCurMaxPortVol_Label->setText(g_sLangTxt_Maximumport); 
	m_pCurModule_GridLayout->addWidget(m_pCurMaxPortVol_Label, 2, 0, 1, 1);

	m_pCurMaxPortVol_LineEdit = new QFloatLineEdit(m_pCurModule_GroupBox);
	m_pCurMaxPortVol_LineEdit->InitCoverage(0,20);
	m_pCurModule_GridLayout->addWidget(m_pCurMaxPortVol_LineEdit, 2, 1, 1, 1);

	//strText = _T("合并电流端子输出(6I合并为3I或采用大电流端子输出)");
	m_pLargeCurTerminal_CheckBox = new QSttCheckBox(m_pCurModule_GroupBox);
	m_pCurModuleSel_Label->setText(g_sLangTxt_CurrModuleSelect); //lcq
	m_pLargeCurTerminal_CheckBox->setText(g_sLangTxt_Combinedcurrent); 
	m_pCurModule_GridLayout->addWidget(m_pLargeCurTerminal_CheckBox, 3, 0, 1, 2);

	//strText = _T("大电流输出端口:");
	m_pLargeCurOutTerm_Label = new QLabel(m_pCurModule_GroupBox);
	m_pCurModuleSel_Label->setText(g_sLangTxt_CurrModuleSelect); //lcq
	m_pLargeCurOutTerm_Label->setText(g_sLangTxt_Gradient_HighCurPort); 
	m_pCurModule_GridLayout->addWidget(m_pLargeCurOutTerm_Label, 4, 0, 1, 1);

	m_pLargeCurOutTerm_ComboBox = new QComboBox(m_pCurModule_GroupBox);
	m_pCurModule_GridLayout->addWidget(m_pLargeCurOutTerm_ComboBox, 4, 1, 1, 1);

// 	m_p6ITo3I_CheckBox = new QCheckBox(m_pCurModule_GroupBox);
// 	m_p6ITo3I_CheckBox->setText(tr("电流6I合并3I输出"));
// 	m_pCurModule_GridLayout->addWidget(m_p6ITo3I_CheckBox, 4, 0, 1, 1);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	InitDatas();

//	m_pStdValues_GroupBox->raise();
	m_pCurModule_GroupBox->raise();
	m_pModuleSet_VBoxLayout->addStretch();
// 	m_pModuleSet_GridLayout->setRowStretch(0,1);//设置第一行的占比
// 	m_pModuleSet_GridLayout->setRowStretch(1,2);//设置第二行的占比
	UpdateCurSelModuleUI();
	SetModuleFont();

	connect(m_pCurModuleSel_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeCurModuleSel(int)));
	connect(m_pCurGear_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeCurGear(int)));
	connect(m_pLargeCurOutTerm_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeLargeCurOutTerm(int)));
	connect(m_pLargeCurTerminal_CheckBox,SIGNAL(stateChanged(int)),this,SLOT(slot_stateChangedLargeCurTerminal(int)));
}

void QModuleSetWidget::SetModuleFont()
{
	m_pCurModuleSel_Label->setFont(*g_pSttGlobalFont);
	m_pCurGear_Label->setFont(*g_pSttGlobalFont);
	m_pCurMaxPortVol_Label->setFont(*g_pSttGlobalFont);
	m_pCurMaxPortVol_LineEdit->setFont(*g_pSttGlobalFont);
	m_pLargeCurOutTerm_Label->setFont(*g_pSttGlobalFont);
	

}

void QModuleSetWidget::UpdateCurSelModuleUI()
{
	int nCurrIndex = m_pCurModuleSel_ComboBox->currentIndex();

	if ((nCurrIndex<0)&&(nCurrIndex >= m_pSysParas->m_oGearSetCurModules.m_nCurModuleNum))
	{
		return;
	}

	tmt_CurModuleGear *pCurGear = &m_pSysParas->m_oGearSetCurModules.m_oCurModuleGear[nCurrIndex];
	m_pCurGear_ComboBox->setCurrentIndex(pCurGear->m_nIPowerMode);
	m_pCurMaxPortVol_LineEdit->SetValue(pCurGear->m_fVoltSet);

	if (pCurGear->m_nIPowerMode == STT_CurrentMODULE_POWER_OTHER)
	{
		m_pCurMaxPortVol_LineEdit->setDisabled(false);
		m_pCurMaxPortVol_Label->setDisabled(false);
	}
	else
	{
		m_pCurMaxPortVol_LineEdit->setDisabled(true);
		m_pCurMaxPortVol_Label->setDisabled(true);
	}

	if (pCurGear->m_nMergeCurTerminal == STT_LARGE_CURRENT_MERGE_NOT_SUPPORT)//不支持合并输出
	{
		m_pLargeCurTerminal_CheckBox->setDisabled(true);
		m_pLargeCurOutTerm_Label->setDisabled(true);
		m_pLargeCurOutTerm_ComboBox->setDisabled(true);
		return;
	}
	else if ((pCurGear->m_nMergeCurTerminal == STT_LARGE_CURRENT_MERGE_NOT_MERGE)&&(pCurGear->m_nLargeCurOutTerm == STT_LARGE_CUR_OUT_NULL))//支持合并输出,当前不设置合并,且不需要选择输出端子
	{
		m_pLargeCurTerminal_CheckBox->setDisabled(FALSE);
		m_pLargeCurTerminal_CheckBox->setCheckState(Qt::Unchecked);
		m_pLargeCurOutTerm_Label->setDisabled(true);
		m_pLargeCurOutTerm_ComboBox->setDisabled(true);
	}
	else if (pCurGear->m_nMergeCurTerminal == STT_LARGE_CURRENT_MERGE_NOT_MERGE)//支持合并输出,当前不设置合并,需要设置输出端子
	{
		m_pLargeCurTerminal_CheckBox->setDisabled(FALSE);
		m_pLargeCurTerminal_CheckBox->setCheckState(Qt::Unchecked);
		m_pLargeCurOutTerm_Label->setDisabled(FALSE);
		m_pLargeCurOutTerm_ComboBox->setDisabled(FALSE);
		m_pLargeCurOutTerm_ComboBox->setCurrentIndex(pCurGear->m_nLargeCurOutTerm-1);
	}
	else if (pCurGear->m_nMergeCurTerminal == STT_LARGE_CURRENT_MERGE_THREE_CH)//支持合并输出,当前设置为6i-3I
	{
		m_pLargeCurTerminal_CheckBox->setDisabled(FALSE);
		m_pLargeCurTerminal_CheckBox->setCheckState(Qt::Checked);
		m_pLargeCurOutTerm_Label->setDisabled(true);
		m_pLargeCurOutTerm_ComboBox->setDisabled(true);
	}
	else if (pCurGear->m_nMergeCurTerminal == STT_LARGE_CURRENT_MERGE_ONE_CH)//支持合并输出,当前设置为单通道,大电流输出
	{
		m_pLargeCurTerminal_CheckBox->setDisabled(FALSE);
		m_pLargeCurTerminal_CheckBox->setCheckState(Qt::Checked);
		m_pLargeCurOutTerm_Label->setDisabled(FALSE);
		m_pLargeCurOutTerm_ComboBox->setDisabled(FALSE);
		ASSERT((pCurGear->m_nLargeCurOutTerm-1)>=0);
		m_pLargeCurOutTerm_ComboBox->setCurrentIndex(pCurGear->m_nLargeCurOutTerm-1);
	}
}

void QModuleSetWidget::slot_changeCurModuleSel(int nCurComboxIndex)
{
	if ((m_nOldModuleSelIndex>=0)&&(m_nOldModuleSelIndex < m_pSysParas->m_oGearSetCurModules.m_nCurModuleNum))
	{
		m_pSysParas->m_oGearSetCurModules.m_oCurModuleGear[m_nOldModuleSelIndex].m_fVoltSet = m_pCurMaxPortVol_LineEdit->GetValue();
	}

	m_nOldModuleSelIndex = nCurComboxIndex;
	UpdateCurSelModuleUI();
}

void QModuleSetWidget::slot_changeCurGear(int nCurComboxIndex)
{
	int nCurrIndex = m_pCurModuleSel_ComboBox->currentIndex();

	if ((nCurrIndex<0)&&(nCurrIndex >= m_pSysParas->m_oGearSetCurModules.m_nCurModuleNum))
	{
		return;
	}

	m_pSysParas->m_oGearSetCurModules.m_oCurModuleGear[nCurrIndex].m_nIPowerMode = nCurComboxIndex;

	if (nCurComboxIndex == STT_CurrentMODULE_POWER_OTHER)
	{
		m_pCurMaxPortVol_LineEdit->setDisabled(false);
		m_pCurMaxPortVol_Label->setDisabled(false);
	}
	else
	{
		m_pCurMaxPortVol_LineEdit->setDisabled(true);
		m_pCurMaxPortVol_Label->setDisabled(true);
	}
}

void QModuleSetWidget::slot_changeLargeCurOutTerm(int nCurComboxIndex)
{
	int nCurrIndex = m_pCurModuleSel_ComboBox->currentIndex();

	if ((nCurrIndex<0)&&(nCurrIndex >= m_pSysParas->m_oGearSetCurModules.m_nCurModuleNum))
	{
		return;
	}

	m_pSysParas->m_oGearSetCurModules.m_oCurModuleGear[nCurrIndex].m_nLargeCurOutTerm = (nCurComboxIndex+1);
}

void QModuleSetWidget::slot_stateChangedLargeCurTerminal(int nStateIndex)
{
	tmt_CurModuleGear *pCurModuleGear = &m_pSysParas->m_oGearSetCurModules.m_oCurModuleGear[m_pCurModuleSel_ComboBox->currentIndex()];

	if (nStateIndex == Qt::Checked)
	{
		if (pCurModuleGear->m_nLargeCurOutTerm == STT_LARGE_CUR_OUT_NULL)
		{
			pCurModuleGear->m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_THREE_CH;
		}
		else
		{
			pCurModuleGear->m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_ONE_CH;
		}
	}
	else
	{
		pCurModuleGear->m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_NOT_MERGE;
	}
}

void QModuleSetWidget::ReleaseUI()
{

}

void QModuleSetWidget::InitDatas()
{
//	m_pStdVol_LineEdit->SetValue(m_pSysParas->m_fVNom);
//	m_pStdCur_LineEdit->SetValue(m_pSysParas->m_fINom);
//	m_pStdFre_LineEdit->SetValue(m_pSysParas->m_fFNom);
//	m_pAntiShakeTime_LineEdit->SetValue(m_pSysParas->m_fStabTime);

	CString strTmp;
	m_pCurModuleSel_ComboBox->clear();
    xlang_GetLangStrByFile(strTmp,"Currentmodule"); //电流模块

	for (int nIndex = 0;nIndex<m_pSysParas->m_oGearSetCurModules.m_nCurModuleNum;nIndex++)
	{
		CString strIndex;
		strIndex.Format(_T("%d"), nIndex + 1);
		//strTmp = QString(tr("电流模块%1")).arg(nIndex+1);
		//strTmp = _T("电流模块");
		strTmp += strIndex;
		m_pCurModuleSel_ComboBox->insertItem(nIndex,strTmp);
	}

	m_nOldModuleSelIndex = m_pCurModuleSel_ComboBox->currentIndex();
	m_pCurGear_ComboBox->clear();

	//20240520 suyang L336D 三档修改为0.3Ω/10A，0.7Ω/10A，1.5Ω/10A
#ifdef _PSX_QT_LINUX_
	CString strModel,strL336DName;
	strModel = g_oSttSystemConfig.GetDevModel();
	strL336DName = strModel.Left(5);

	if (strL336DName == STT_MODULE_L336D)
	{
		m_pCurGear_ComboBox->insertItem(0,g_sLangTxt_Currentlevel1);
		m_pCurGear_ComboBox->insertItem(1,g_sLangTxt_Currentlevel2);
		m_pCurGear_ComboBox->insertItem(2,g_sLangTxt_Currentlevel3);
	}
	else
	{
	//strTmp = _T("1档(0.2Ω/10A)");
    xlang_GetLangStrByFile(strTmp,"Gradient_FirstFile"); //lcq
	m_pCurGear_ComboBox->insertItem(0,strTmp);
	//strTmp = _T("2档(0.3Ω/10A)");
	xlang_GetLangStrByFile(strTmp,"Gradient_SecondFile");//lcq
	m_pCurGear_ComboBox->insertItem(1,strTmp);
	//strTmp = _T("3档(0.7Ω/10A)");
	xlang_GetLangStrByFile(strTmp,"Gradient_ThirdFile"); //lcq
	m_pCurGear_ComboBox->insertItem(2,strTmp);
	}
#else

	//strTmp = _T("1档(0.2Ω/10A)");
	xlang_GetLangStrByFile(strTmp,"Gradient_FirstFile"); //lcq
	m_pCurGear_ComboBox->insertItem(0,strTmp);
	//strTmp = _T("2档(0.3Ω/10A)");
	xlang_GetLangStrByFile(strTmp,"Gradient_SecondFile");//lcq
	m_pCurGear_ComboBox->insertItem(1,strTmp);
	//strTmp = _T("3档(0.7Ω/10A)");
	xlang_GetLangStrByFile(strTmp,"Gradient_ThirdFile"); //lcq
	m_pCurGear_ComboBox->insertItem(2,strTmp);

#endif

	//strTmp = _T("其他");
	xlang_GetLangStrByFile(strTmp,"else");// 其他 lcq
	m_pCurGear_ComboBox->insertItem(3,strTmp);
	m_pCurGear_ComboBox->setCurrentIndex(m_pSysParas->m_oGearSetCurModules.m_oCurModuleGear[0].m_nIPowerMode);
	m_pCurMaxPortVol_LineEdit->SetValue(m_pSysParas->m_oGearSetCurModules.m_oCurModuleGear[0].m_fVoltSet);
	m_pLargeCurOutTerm_ComboBox->clear();

	for (int nIndex = 0;nIndex<3;nIndex++)
	{
		strTmp = QString(tr("I%1")).arg(nIndex+1);
		m_pLargeCurOutTerm_ComboBox->insertItem(nIndex,strTmp);
	}
}

void QModuleSetWidget::SaveDatas()
{
//	m_pSysParas->m_fVNom = m_pStdVol_LineEdit->GetValue();
//	m_pSysParas->m_fINom = m_pStdCur_LineEdit->GetValue();
//	m_pSysParas->m_fFNom = m_pStdFre_LineEdit->GetValue();
//	m_pSysParas->m_fStabTime = m_pAntiShakeTime_LineEdit->GetValue();

	int nCurrIndex = m_pCurModuleSel_ComboBox->currentIndex();

	if ((nCurrIndex<0)&&(nCurrIndex >= m_pSysParas->m_oGearSetCurModules.m_nCurModuleNum))
	{
		return;
	}

	m_pSysParas->m_oGearSetCurModules.m_oCurModuleGear[nCurrIndex].m_fVoltSet = m_pCurMaxPortVol_LineEdit->GetValue();
}



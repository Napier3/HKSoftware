#include "stdafx.h"
#include "RemoteMeasWidget.h"

#include "../Module/CommonMethod/commonMethod.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "SttMacroParaEditViewRemoteMeas.h"
#include "../SttTestCntrFrameBase.h"
#include "../../Module/XLangResource_Native.h"

QRemoteMeasWidget::QRemoteMeasWidget(QWidget *pParent): QWidget(pParent)
{
    m_pStepValue_LineEdit = NULL;
    m_pStartValue_LineEdit = NULL;
	m_pEndValue_LineEdit = NULL;
    m_pStepTime_LineEdit = NULL;
    m_pChSelect_ComboBox = NULL;
    m_pChGradientType_ComboBox = NULL;
    m_pChangedType_ComboBox = NULL;
	//m_pRemoteMeasParaTable = NULL;

    m_pAuto_CheckBox = NULL;
	m_nChanneType = 0;
	m_nUnitType = 0;
}

QRemoteMeasWidget::~QRemoteMeasWidget()
{

}

void QRemoteMeasWidget::InitUI()
{
	m_pMainGridLayout = new QGridLayout(this);
	//m_pTelemeterTab = new QSttTabWidget(this);
	//m_pMainGridLayout->addWidget(m_pTelemeterTab, 0, 0, 1, 10);

	//m_pVolCurr_Widget = new QWidget();
	//m_pVolCurr_Widget->setObjectName(QString::fromUtf8("m_layoutIV"));
	CString strText;
	////strText = _T("遥测");
	//m_pTelemeterTab->addTab(m_pVolCurr_Widget,g_sLangTxt_remotemeas);

	//strText = _T("通道选择:");
	m_pChSelect_Label = new QLabel(g_sLangTxt_Manual_Channel,this);
	m_pChSelect_ComboBox = new QScrollComboBox(this);
	m_pChGradientType_ComboBox = new QScrollComboBox(this);

	//strText = _T("步长(V):");
	m_pStepValue_Label = new QLabel(g_sLangTxt_Manual_Step  ,this);
	m_pStepValue_LineEdit = new QSttLineEdit(this);

	strText = _T("+");
	m_pAdd_PushButton = new QPushButton(strText,this);

	strText = _T("-");
	m_pMinus_PushButton = new QPushButton(strText,this);

	//strText = _T("自动");
	m_pAuto_CheckBox = new QSttCheckBox(g_sLangTxt_Manual_Auto,this);

	//strText = _T("始值(V):");
	m_pStartValue_Label = new QLabel(g_sLangTxt_Manual_InitVal,this);
	m_pStartValue_LineEdit = new QSttLineEdit(this);

	//strText = _T("终值(V):");
	m_pEndValue_Label = new QLabel(g_sLangTxt_Manual_FinishVal,this);
	m_pEndValue_LineEdit = new QSttLineEdit(this);

	//strText = _T("步长时间:");
	m_pStepTime_Label = new QLabel(g_sLangTxt_steplength,this);
	m_pStepTime_LineEdit = new QSttLineEdit(this);

	//strText = _T("变化方式:");
	m_pChangedType_Label = new QLabel(g_sLangTxt_Manual_ChangeType,this);
	m_pChangedType_ComboBox = new QScrollComboBox(this);

	//2023/10/9 - wjs 开出量宽度改小，使其他按钮内容可以显示全
	//m_pBoutGroupBox->setFixedWidth(110);
	//2023/10/9 - wjs 设置为可动态调整
	QSizePolicy sizePolicy;
	sizePolicy.setHorizontalPolicy(QSizePolicy::Preferred);
	m_pStartValue_Label->setSizePolicy(sizePolicy);
	m_pStartValue_LineEdit->setSizePolicy(sizePolicy);
	m_pEndValue_Label->setSizePolicy(sizePolicy);
	m_pEndValue_LineEdit->setSizePolicy(sizePolicy);
	m_pStepValue_Label->setSizePolicy(sizePolicy);
	m_pStepValue_LineEdit->setSizePolicy(sizePolicy);
	m_pChangedType_Label->setSizePolicy(sizePolicy);
	m_pChangedType_ComboBox->setSizePolicy(sizePolicy);

	//strText = _T("锁");
	m_pLock_PushButton = new QPushButton(g_sLangTxt_Manual_Lock,this);

	m_pMainGridLayout->addWidget(m_pChSelect_Label, 1, 0, 1, 1);
	m_pMainGridLayout->addWidget(m_pChSelect_ComboBox, 1, 1, 1, 1);
	m_pMainGridLayout->addWidget(m_pChGradientType_ComboBox, 1, 2, 1, 2);
	m_pMainGridLayout->addWidget(m_pStepValue_Label, 1, 4, 1, 1);
	m_pMainGridLayout->addWidget(m_pStepValue_LineEdit, 1, 5, 1, 1);
	m_pMainGridLayout->addWidget(m_pAdd_PushButton, 1, 6, 1, 1);
	m_pMainGridLayout->addWidget(m_pMinus_PushButton, 1, 7, 1, 1);
	m_pMainGridLayout->addWidget(m_pAuto_CheckBox, 1, 8, 1, 1);

	m_pMainGridLayout->addWidget(m_pStartValue_Label, 2, 0, 1, 1);
	m_pMainGridLayout->addWidget(m_pStartValue_LineEdit, 2, 1, 1, 1);
	m_pMainGridLayout->addWidget(m_pEndValue_Label, 2, 2, 1, 1);
	m_pMainGridLayout->addWidget(m_pEndValue_LineEdit, 2, 3, 1, 1);
	m_pMainGridLayout->addWidget(m_pStepTime_Label, 2, 4, 1, 1);
	m_pMainGridLayout->addWidget(m_pStepTime_LineEdit, 2, 5, 1, 1);
	m_pMainGridLayout->addWidget(m_pChangedType_Label, 2, 6, 1, 1);
	m_pMainGridLayout->addWidget(m_pChangedType_ComboBox, 2, 7, 1, 1);
	m_pMainGridLayout->addWidget(m_pLock_PushButton, 2, 8, 1, 1);

	m_pMainGridLayout->setContentsMargins(0, 0, 0, 0); 
	m_pMainGridLayout->setVerticalSpacing(2);

	m_bControlLock = false;
	m_pManualParas = NULL;
	m_nVChNums = m_nIChNums = 0;
	m_pEvent = NULL;
	xlang_GetLangStrByFile(strText, "Native_Amplitude");
	m_pChGradientType_ComboBox->addItem(strText);
	xlang_GetLangStrByFile(strText, "Native_Angle");
	m_pChGradientType_ComboBox->addItem(strText);
 	xlang_GetLangStrByFile(strText, "Native_Freq");
 	m_pChGradientType_ComboBox->addItem(strText);

	xlang_GetLangStrByFile(strText, "Manual_S_E");
	m_pChangedType_ComboBox->addItem(strText);
	xlang_GetLangStrByFile(strText, "Manual_S_E_S");
	m_pChangedType_ComboBox->addItem(strText);

	m_pAdd_PushButton->setDisabled(true);
	m_pMinus_PushButton->setDisabled(true);
	m_pLock_PushButton->setDisabled(true);

#ifdef _PSX_QT_WINDOWS_
	CString strImagePath = _P_GetResourcePath();
	m_imgLock.addFile(strImagePath + "Lock.png");
	m_imgUnlock.addFile(strImagePath + "Unlock.png");
#else
	CString strImagePath ;
	strImagePath = ":/ctrls/images/Lock.png";
	m_imgLock.addFile(strImagePath);
	strImagePath = ":/ctrls/images/Unlock.png";
	m_imgUnlock.addFile(strImagePath);
#endif

	m_pLock_PushButton->setIcon(m_imgUnlock);
	m_pLock_PushButton->setIconSize(QSize(m_pAdd_PushButton->height(), m_pAdd_PushButton->height()));
	//2023/10/9 wjs 取消对按钮“锁”的固定
	//m_pLock_PushButton->setFixedWidth(m_pAdd_PushButton->width());
	m_pLock_PushButton->setText("");
}

void QRemoteMeasWidget::InitConnect()
{
}

void QRemoteMeasWidget::SetData(CSttTestResourceBase *pSttTestResource,tmt_ManualParas* pManualParas,CEventResult* pEvent)
{
	m_pTestResource = pSttTestResource;
	m_pManualParas = pManualParas;
	m_pEvent = pEvent;

	UpdateData();
}

void QRemoteMeasWidget::SetUnitType (int index)
{
	QString strText;
	switch(index)
	{
	case 0: 
		if(m_nChanneType)
		{
			strText = "A"; 
		}
		else
		{
			strText = "V"; 
		}
		break;
	case 1:	strText = "°"; 
#ifndef _PSX_QT_LINUX_
		strText = QString::fromLocal8Bit("°");
#endif	
		break;
	case 2:	strText = "Hz"; break;
	default:
		break;
	}

    CString strTemp;
	xlang_GetLangStrByFile(strTemp, "Manual_Step");
	m_pStepValue_Label->setText(strTemp.mid(0, m_pStepValue_Label->text().lastIndexOf("(") + 1) + strText + "):");
	xlang_GetLangStrByFile(strTemp, "Manual_InitVal");
	m_pStartValue_Label->setText(strTemp.mid(0, m_pStartValue_Label->text().lastIndexOf("(") + 1) + strText + "):");
	xlang_GetLangStrByFile(strTemp, "Manual_FinishVal");
	m_pEndValue_Label->setText(strTemp.mid(0, m_pEndValue_Label->text().lastIndexOf("(") + 1) + strText + "):");
};

void QRemoteMeasWidget::UpdateData()
{
	if(m_pManualParas == NULL || m_pTestResource == NULL)
	{
		return;
	}

	m_nVChNums = m_pTestResource->m_oVolChRsListRef.GetCount();
	m_nIChNums = m_pTestResource->m_oCurChRsListRef.GetCount();

	bool bAuto = m_pManualParas->m_bAuto;
	m_pStartValue_LineEdit->setDisabled(!bAuto);
	m_pEndValue_LineEdit->setDisabled(!bAuto);
	m_pStepTime_LineEdit->setDisabled(!bAuto);

	g_theTestCntrFrame->SetVectorGradient(m_pManualParas->m_bAuto);

	//递变参数
	InitGradientData();
	slot_lne_startChanged();
	slot_lne_endChanged();
	slot_lne_stepChanged();

	m_pAdd_PushButton->setDisabled(bAuto);
	m_pMinus_PushButton->setDisabled(bAuto);

	//老化、直流、自动
	m_pAuto_CheckBox->setChecked(m_pManualParas->m_bAuto);
}

void QRemoteMeasWidget::InitGradientData()
{
	if (m_pManualParas->m_nGradientTpSelect == phasor_type)
	{
		m_pStartValue_LineEdit->setText(QString::number(m_pManualParas->m_manuGradient.fStart,'f',1));
		m_pEndValue_LineEdit->setText(QString::number(m_pManualParas->m_manuGradient.fEnd,'f',1));
		m_pStepValue_LineEdit->setText(QString::number(m_pManualParas->m_manuGradient.fStep,'f',1));
	}
	else
	{
		m_pStartValue_LineEdit->setText(QString::number(m_pManualParas->m_manuGradient.fStart,'f',3));  //有效位数改为三位 20210912 sf
		m_pEndValue_LineEdit->setText(QString::number(m_pManualParas->m_manuGradient.fEnd,'f',3));
		m_pStepValue_LineEdit->setText(QString::number(m_pManualParas->m_manuGradient.fStep,'f',3));
	}

	m_pStepTime_LineEdit->setText(QString::number(m_pManualParas->m_manuGradient.fStepTime,'f',3));

	m_pChangedType_ComboBox->setCurrentIndex(m_pManualParas->m_manuGradient.nMode);

	para_type var = getParaTypeByInt(m_pManualParas->m_nGradientChSelect);
	InitGradientVarList();
	InitGradientVar(var);

	switch (m_pManualParas->m_nGradientTpSelect)
	{
	case amplitude_type:
		m_pChGradientType_ComboBox->setCurrentIndex(0);
		break;
	case phasor_type:
		m_pChGradientType_ComboBox->setCurrentIndex(1);
		break;
	case fre_type:
		m_pChGradientType_ComboBox->setCurrentIndex(2);
		break;
	default:
		break;
	}
}

void QRemoteMeasWidget::InitGradientVarList()
{
	m_pChSelect_ComboBox->clear();

	if (m_pTestResource == NULL)
	{
		return;
	}

	m_pTestResource->AddGradientRemoteMeasChs(m_oGradientChs);

	CDataTypeValue *pCurTypeValue = NULL;
	POS pos = m_oGradientChs.GetHeadPosition();

	while(pos)
	{
		pCurTypeValue = (CDataTypeValue *)m_oGradientChs.GetNext(pos);
		m_pChSelect_ComboBox->addItem(pCurTypeValue->m_strID.GetString());
	}
}

void QRemoteMeasWidget::InitGradientVar(para_type vartype)
{
	CDataTypeValue *pCurSelData = m_oGradientChs.FindByIndex(vartype);

	if (pCurSelData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_selectchannel.GetString(),vartype);
		return;
	}
	else
	{
		long nIndex = m_oGradientChs.FindIndex(pCurSelData);
		ASSERT(nIndex>=0);
		m_pChSelect_ComboBox->setCurrentIndex(nIndex);
	}
}

float QRemoteMeasWidget::slot_lne_Changed(QLineEdit* pLineEdit)
{
	float fv = pLineEdit->text().toFloat();
	QString strvar = m_pChSelect_ComboBox->currentText();
	int index = m_pChGradientType_ComboBox->currentIndex();
	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
	float fDcVMax = g_oLocalSysPara.m_fDC_VolMax;
	float fDcIMax = g_oLocalSysPara.m_fDC_CurMax;
	switch (index)
	{
	case 0:
		{
			if (strvar.contains("U"))
			{
				if (fv>fAcVMax)
				{
					fv = fAcVMax;
				}

				if (fv<0)
				{
					fv = 0;
				}
			}
			else if (strvar.contains("I"))
			{
				if (fv>fAcIMax)
				{
					fv = fAcIMax;
				}

				if (fv<0)
				{
					fv = 0;
				}
			}
		}
		break;
	case 1:
		{
			fv = setAngleLimit(fv);
		}
		break;
	case 2:
		{
			fv = setLimit(10,Global_GetMaxFreq(),fv);
		}
		break;
	default:
		break;
	}

	if (index==1)
	{
		pLineEdit->setText(QString::number(fv,'f',1));
	}
	else
	{
		pLineEdit->setText(QString::number(fv,'f',3));
	}

	return fv;
}

void QRemoteMeasWidget::slot_lne_startChanged()
{
	m_pManualParas->m_manuGradient.fStart = slot_lne_Changed(m_pStartValue_LineEdit);

	if(m_pChSelect_ComboBox->currentText().contains("U"))
	{
		g_theTestCntrFrame->UpdateVectorRange(m_pManualParas->m_manuGradient.fStart,
			m_pManualParas->m_manuGradient.fEnd, 0, 0);
	}
	else
	{
		g_theTestCntrFrame->UpdateVectorRange(0, 0, m_pManualParas->m_manuGradient.fStart,
			m_pManualParas->m_manuGradient.fEnd);
	}
}

void QRemoteMeasWidget::slot_lne_endChanged()
{
	m_pManualParas->m_manuGradient.fEnd = slot_lne_Changed(m_pEndValue_LineEdit);

	if(m_pChSelect_ComboBox->currentText().contains("U"))
	{
		g_theTestCntrFrame->UpdateVectorRange(m_pManualParas->m_manuGradient.fStart,
			m_pManualParas->m_manuGradient.fEnd, 0, 0);
	}
	else
	{
		g_theTestCntrFrame->UpdateVectorRange(0, 0, m_pManualParas->m_manuGradient.fStart,
			m_pManualParas->m_manuGradient.fEnd);
	}
}

void QRemoteMeasWidget::slot_lne_stepChanged()
{
	float fv = m_pStepValue_LineEdit->text().toFloat();
	if (qAbs(fv)<=EPSINON)
	{
		fv = 0.001;
	}

	QString strvar = m_pChSelect_ComboBox->currentText();
	int index = m_pChGradientType_ComboBox->currentIndex();
	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
	float fDcVMax = g_oLocalSysPara.m_fDC_VolMax;
	float fDcIMax = g_oLocalSysPara.m_fDC_CurMax;

	switch (index)
	{
	case 0:
		{
			if (strvar.contains("U"))
			{
				if (fv>fAcVMax)
				{
					fv = fAcVMax;
				}

				if (fv<0)
				{
					fv = 0.001;
				}
			}
			else if (strvar.contains("I"))
			{
				if (fv>fAcIMax)
				{
					fv = fAcIMax;
				}

				if (fv<0)
				{
					fv = 0.001;
				}
			}
		}
		break;
	case 1:
		{
			fv = setAngleLimit(fv);
			if (fv < 0.1)
			{
				fv = 0.1;
			}
		}
		break;
	case 2:
		{
			fv = setLimit(0.001,Global_GetMaxFreq(),fv);
			if (fv < 0.001)
			{
				fv = 0.001;
			}
		}
		break;
	default:
		break;
	}

	m_pManualParas->m_manuGradient.fStep = fv;

	if (index==1)
	{
		m_pStepValue_LineEdit->setText(QString::number(fv,'f',1));
	}
	else
	{
		m_pStepValue_LineEdit->setText(QString::number(fv,'f',3));
	}
}

void QRemoteMeasWidget::slot_lne_steptimeChanged()
{
	float fv = m_pStepTime_LineEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);

	if (m_pManualParas->m_manuGradient.fStepTime != fv)
	{
		m_pManualParas->m_manuGradient.fStepTime = fv;
	}

	m_pStepTime_LineEdit->setText(QString::number(fv,'f',3));
}


void QRemoteMeasWidget::slot_btn_LockClicked()
{
	if (m_pManualParas->m_bLockChanged)
	{
		m_bControlLock = true;
		m_pManualParas->m_bLockChanged = false;
		//xlang_SetLangStrToWidget(m_pBtnLock, "Manual_Lock", XLang_Ctrls_QPushButton);
		m_pLock_PushButton->setIcon(m_imgUnlock);
	}
	else
	{
		m_bControlLock = false;
		m_pManualParas->m_bLockChanged = true;
		//xlang_SetLangStrToWidget(m_pBtnLock, "Manual_UnLock", XLang_Ctrls_QPushButton);
		m_pLock_PushButton->setIcon(m_imgLock);
	}

	m_pManualParas->m_bBinStop = TRUE;
}

void QRemoteMeasWidget::slot_btn_AddClicked()
{
	QString str = m_pChSelect_ComboBox->currentText();
	int index = m_pChGradientType_ComboBox->currentIndex();
	float fstep = m_pManualParas->m_manuGradient.fStep;

	switch (index)
	{
	case amplitude_type:
	case phasor_type:
	case fre_type:
		if (str.length()<=3)
		{
			emit sig_ChannelTableItemValue(str,fstep,index,1,false);
		}
		else
		{
			QStringList chanelist = str.split(",");
			for (int i=0;i<chanelist.size();i++)
			{
				QString ch = chanelist.at(i);
				emit sig_ChannelTableItemValue(ch,fstep,index,1,false);
			}
		}
		break;
	default:
		break;
	}
}

void QRemoteMeasWidget::slot_btn_MinusClicked()
{
	QString str = m_pChSelect_ComboBox->currentText();
	int index = m_pChGradientType_ComboBox->currentIndex();
	float fstep = m_pManualParas->m_manuGradient.fStep;

	switch (index)
	{
	case amplitude_type:
	case phasor_type:
	case fre_type:
		if (str.length()<=3)
		{
			emit sig_ChannelTableItemValue(str,fstep,index,-1,false);
		}
		else
		{
			QStringList chanelist = str.split(",");
			for (int i=0;i<chanelist.size();i++)
			{
				QString ch = chanelist.at(i);
				emit sig_ChannelTableItemValue(ch,fstep,index,-1,false);
			}
		}
		break;
	default:
		break;
	}
}

void QRemoteMeasWidget::slot_cb_AutoClicked()
{
	bool bIsChecked = false;
	if (m_pAuto_CheckBox->isChecked())
	{
		m_bControlLock = false;
		bIsChecked = true;
		m_pAdd_PushButton->setDisabled(true);
		m_pMinus_PushButton->setDisabled(true);	}
	else
	{
		m_bControlLock = false;
		bIsChecked = false;	
		m_pAdd_PushButton->setDisabled(false);
		m_pMinus_PushButton->setDisabled(false);	}

	if(m_pManualParas->m_bAuto != bIsChecked)
	{
		m_pManualParas->m_bAuto = bIsChecked;
	}

	m_pStartValue_LineEdit->setDisabled(!m_pManualParas->m_bAuto);
	m_pEndValue_LineEdit->setDisabled(!m_pManualParas->m_bAuto);
	m_pStepTime_LineEdit->setDisabled(!m_pManualParas->m_bAuto);

	g_oSttTestResourceMngr.m_oRtDataMngr.SetAutoMode(m_pManualParas->m_bAuto);
}

void QRemoteMeasWidget::slot_cbb_SelectChanged(int index)
{
	m_pManualParas->m_nGradientTpSelect = index;
	SetUnitType(index);
	UpdateData();
}

void QRemoteMeasWidget::slot_cbb_ChannelChanged(int index)
{
	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oGradientChs.GetAtIndex(index);

	if(!pCurDataTypeValue)
	{
		return;
	}

	m_pManualParas->m_nGradientChSelect = pCurDataTypeValue->GetIndex();

	m_nChanneType = 1;

	if(m_pChSelect_ComboBox->currentText().indexOf("U") != -1)
	{
		m_nChanneType = 0;
	}

	SetUnitType(m_pChGradientType_ComboBox->currentIndex());
};

void QRemoteMeasWidget::slot_cbb_ChangeTypeChanged(int index)
{
	m_pManualParas->m_manuGradient.nMode = index;
}

void QRemoteMeasWidget::StartInit()
{
	m_bControlLock = false;
	m_pManualParas->m_bLockChanged = m_bControlLock;

	bool bAuto = m_pManualParas->m_bAuto;

	m_pAdd_PushButton->setDisabled(bAuto);
	m_pMinus_PushButton->setDisabled(bAuto);
	m_pLock_PushButton->setDisabled(bAuto);

	m_pChangedType_ComboBox->setDisabled(bAuto);
	m_pChSelect_ComboBox->setDisabled(bAuto);
	m_pChGradientType_ComboBox->setDisabled(bAuto);
	m_pStepValue_LineEdit->setDisabled(bAuto);

	m_pStepTime_LineEdit->setDisabled(true);
	m_pStartValue_LineEdit->setDisabled(true);
	m_pEndValue_LineEdit->setDisabled(true);

	m_pAuto_CheckBox->setDisabled(true);
}

void QRemoteMeasWidget::StopInit()
{
	m_bControlLock = true;
	m_pManualParas->m_bLockChanged = false;
	m_pLock_PushButton->setIcon(m_imgUnlock);
	m_pLock_PushButton->setDisabled(true);

	m_pAdd_PushButton->setDisabled(m_pManualParas->m_bAuto);
	m_pMinus_PushButton->setDisabled(m_pManualParas->m_bAuto);

	m_pChSelect_ComboBox->setDisabled(false);
	m_pChGradientType_ComboBox->setDisabled(false);
	m_pChangedType_ComboBox->setDisabled(false);
	m_pStepValue_LineEdit->setDisabled(false);

	m_pStepTime_LineEdit->setDisabled(!m_pManualParas->m_bAuto);
	m_pStartValue_LineEdit->setDisabled(!m_pManualParas->m_bAuto);
	m_pEndValue_LineEdit->setDisabled(!m_pManualParas->m_bAuto);

	m_pAuto_CheckBox->setDisabled(false);

	m_pManualParas->m_bLockChanged = false;		

}

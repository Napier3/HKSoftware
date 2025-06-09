//#include "stdafx.h"
#include "ManualView_Paras.h"
#include "../../../Module/XLangResource_Native.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "SttMacroParaEditViewManual.h"
//#include "QSttManualBinBoutDlg.h"
#include "../SttTestCntrFrameBase.h"

QManualView_Paras::QManualView_Paras()
{
    //m_pEditDelayed = 0;
    m_pEditStep = 0;
    m_pEditInitVal = 0;
	m_pEditFinishVal = 0;
    m_pEditTime = 0;
    m_pCbbChannel = 0;
    m_pCbbSelect = 0;
    m_pCbbChangeType = 0;
    m_pCbOut1 = 0;
    m_pCbOut2 = 0;
    m_pCbOut3 = 0;
    m_pCbOut4 = 0;
	m_pEditUdc = 0;
    /*m_pCbOut5 = 0;
    m_pCbOut6 = 0;
    m_pCbOut7 = 0;
    m_pCbOut8 = 0;
	m_pCbOut9 = 0;
	m_pCbOut10 = 0;
	m_pCbInA = 0;
	m_pCbInB = 0;
	m_pCbInC = 0;
	m_pCbInD = 0;
	m_pCbInE = 0;
	m_pCbInF = 0;
	m_pCbInG = 0;
	m_pCbInH = 0;
	m_pCbInI = 0;
	m_pCbInJ = 0;*/
//	m_pBtnAnd = 0;
//	m_pBtnOr = 0;

    m_pCbOld = 0;
    m_pCbAuto = 0;
    m_pCbDC = 0;
	m_nChanneType = 0;
	m_nUnitType = 0;
}

QManualView_Paras::~QManualView_Paras()
{

}

void QManualView_Paras::Init()
{
	m_bControlLock = false;
	m_pManualParas = NULL;
	m_nVChNums = m_nIChNums = 0;
	m_pEvent = NULL;

    CString strText;
	xlang_GetLangStrByFile(strText, "Native_Amplitude");
	m_pCbbSelect->setItemText(0, strText);
	xlang_GetLangStrByFile(strText, "Native_Angle");
	m_pCbbSelect->setItemText(1, strText);
	xlang_GetLangStrByFile(strText, "Native_Freq");
	m_pCbbSelect->setItemText(2, strText);

	xlang_GetLangStrByFile(strText, "Manual_S_E");
	m_pCbbChangeType->setItemText(0, strText);
	xlang_GetLangStrByFile(strText, "Manual_S_E_S");
	m_pCbbChangeType->setItemText(1, strText);

	m_pBtnAdd->setDisabled(true);
	m_pBtnMinus->setDisabled(true);
	m_pBtnLock->setDisabled(true);
//	m_pCheckBoxHarm->setDisabled(false);
	m_pComboBoxHarm->setDisabled(true);
	m_pComboBoxHarm->setFixedWidth(120);

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

	m_pBtnLock->setIcon(m_imgUnlock);
	m_pBtnLock->setIconSize(QSize(m_pBtnAdd->height(), m_pBtnAdd->height()));
	//2023/10/8 wjs 取消对lock按钮的固定大小
	//m_pBtnLock->setFixedWidth(m_pBtnAdd->width());
	m_pBtnLock->setText("");
}

void QManualView_Paras::InitHarmCombox()
{
	m_pComboBoxHarm->clear();
	CString strHarmDesc,strID;
	strHarmDesc = /*"次谐波"*/g_sLangTxt_State_HarmCount.GetString(); //lcq
	long nMaxHarmCount = g_oLocalSysPara.m_nMaxHarmCount;

	if (g_oSystemParas.m_nHasDigital)
	{
		nMaxHarmCount--;
	}

	for (int nIndex = 2;nIndex<= nMaxHarmCount;nIndex++)
	{
		strID.Format("%d",nIndex);
		strID += strHarmDesc;
		m_pComboBoxHarm->addItem(strID/*.GetString()*/);
	}
}

/*
void QManualView_Paras::UpdateResult(float fActValue,float fActTime,float fReturnValue,float fReturnTime)
{
	if (fActValue>0)
	{
		m_pEditAction->setText(QString::number(fActValue,'f',3));
	}
	else
	{
		m_pEditAction->setText("");
	}

	if (fActTime>0)
	{
		m_pEditActionTime->setText(QString::number(fActTime,'f',4));
	}
	else
	{
		m_pEditActionTime->setText("");
	}

	if (fReturnValue>0)
	{
		m_pEditReturn->setText(QString::number(fReturnValue,'f',3));
	}
	else
	{
		m_pEditReturn->setText("");
	}

	if (fReturnTime>0)
	{
		m_pEditReturnTime->setText(QString::number(fReturnTime,'f',4));
	}
	else
	{
		m_pEditReturnTime->setText("");
	}
}

void QManualView_Paras::UpdateResult(const CString& strActValue, const CString& strActTime,
				  const CString& strReturnValue, const CString& strReturnTime)
{
	if (CString_To_double(strActValue)>0)
	{
		m_pEditAction->setText(strActValue);
	}

	if (CString_To_double(strActTime)>0)
	{
		m_pEditActionTime->setText(strActTime);
	}

	if (CString_To_double(strReturnValue)>0)
	{
		m_pEditReturn->setText(strReturnValue);
	}

	if (CString_To_double(strReturnTime)>0)
	{
		m_pEditReturnTime->setText(strReturnTime);
	}
}
*/

void QManualView_Paras::SetData(CSttTestResourceBase *pSttTestResource,tmt_ManualParas* pManualParas,CEventResult* pEvent)
{
	m_pTestResource = pSttTestResource;
	m_pManualParas = pManualParas;
	m_pEvent = pEvent;

	UpdateData();
}

void QManualView_Paras::SetUnitType (int index)
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
	m_pLabStep->setText(strTemp.mid(0, m_pLabStep->text().lastIndexOf("(") + 1) + strText + "):");
	xlang_GetLangStrByFile(strTemp, "Manual_InitVal");
	m_pLabInitVal->setText(strTemp.mid(0, m_pLabInitVal->text().lastIndexOf("(") + 1) + strText + "):");
	xlang_GetLangStrByFile(strTemp, "Manual_FinishVal");
	m_pLabFinishVal->setText(strTemp.mid(0, m_pLabFinishVal->text().lastIndexOf("(") + 1) + strText + "):");
	/*
	xlang_GetLangStrByFile(strTemp, "Native_Action");
	m_pLabAction->setText(strTemp.mid(0, m_pLabAction->text().lastIndexOf("(") + 1) + strText + "):");
	xlang_GetLangStrByFile(strTemp, "Native_ReturnVal");
	m_pLabReturn->setText(strTemp.mid(0, m_pLabReturn->text().lastIndexOf("(") + 1) + strText + "):");
	*/
};

void QManualView_Paras::UpdateData()
{
	if(m_pManualParas == NULL || m_pTestResource == NULL)
	{
		return;
	}

	m_nVChNums = m_pTestResource->m_oVolChRsListRef.GetCount();
	m_nIChNums = m_pTestResource->m_oCurChRsListRef.GetCount();

	bool bAuto = m_pManualParas->m_bAuto;
	m_pEditInitVal->setDisabled(!bAuto);
	m_pEditFinishVal->setDisabled(!bAuto);
	m_pEditTime->setDisabled(!bAuto);
	m_pCbbChangeType->setDisabled(!m_pManualParas->m_bAuto);

	g_theTestCntrFrame->SetVectorGradient(m_pManualParas->m_bAuto);

	//递变参数
	InitGradientData();
	slot_lne_startChanged();
	slot_lne_endChanged();
	slot_lne_stepChanged();

	m_pBtnAdd->setDisabled(bAuto);
	m_pBtnMinus->setDisabled(bAuto);
	//开出量设置
// 	m_pCbOut1->setChecked(m_pManualParas->m_binOut[0].nState);
// 	m_pCbOut2->setChecked(m_pManualParas->m_binOut[1].nState);
// 	m_pCbOut3->setChecked(m_pManualParas->m_binOut[2].nState);
// 	m_pCbOut4->setChecked(m_pManualParas->m_binOut[3].nState);
// 	m_pCbOut5->setChecked(m_pManualParas->m_binOut[4].nState);
// 	m_pCbOut6->setChecked(m_pManualParas->m_binOut[5].nState);
// 	m_pCbOut7->setChecked(m_pManualParas->m_binOut[6].nState);
// 	m_pCbOut8->setChecked(m_pManualParas->m_binOut[7].nState);
// 	if (g_nBoutCount == 10)
// 	{
// 		m_pCbOut9->setChecked(m_pManualParas->m_binOut[8].nState);
// 		m_pCbOut10->setChecked(m_pManualParas->m_binOut[9].nState);
// 	}

	GlobalSetQcheckState_BinaryOut(m_pCbOut1,m_pManualParas->m_binOut,0);
	GlobalSetQcheckState_BinaryOut(m_pCbOut2,m_pManualParas->m_binOut,1);
	GlobalSetQcheckState_BinaryOut(m_pCbOut3,m_pManualParas->m_binOut,2);
	GlobalSetQcheckState_BinaryOut(m_pCbOut4,m_pManualParas->m_binOut,3);
	/*GlobalSetQcheckState_BinaryOut(m_pCbOut5,m_pManualParas->m_binOut,4);
	GlobalSetQcheckState_BinaryOut(m_pCbOut6,m_pManualParas->m_binOut,5);
	GlobalSetQcheckState_BinaryOut(m_pCbOut7,m_pManualParas->m_binOut,6);
	GlobalSetQcheckState_BinaryOut(m_pCbOut8,m_pManualParas->m_binOut,7);
	GlobalSetQcheckState_BinaryOut(m_pCbOut9,m_pManualParas->m_binOut,8);
	GlobalSetQcheckState_BinaryOut(m_pCbOut10,m_pManualParas->m_binOut,9);*/

	//开入量设置
	Global_CheckBinSelect(m_pManualParas->m_binIn,g_nBinCount, m_pManualParas->m_nBinLogic);

	/*GlobalSetQcheckState_BinaryIn(m_pCbInA,m_pManualParas->m_binIn,0);
	GlobalSetQcheckState_BinaryIn(m_pCbInB,m_pManualParas->m_binIn,1);
	GlobalSetQcheckState_BinaryIn(m_pCbInC,m_pManualParas->m_binIn,2);
	GlobalSetQcheckState_BinaryIn(m_pCbInD,m_pManualParas->m_binIn,3);
	GlobalSetQcheckState_BinaryIn(m_pCbInE,m_pManualParas->m_binIn,4);
	GlobalSetQcheckState_BinaryIn(m_pCbInF,m_pManualParas->m_binIn,5);
	GlobalSetQcheckState_BinaryIn(m_pCbInG,m_pManualParas->m_binIn,6);
	GlobalSetQcheckState_BinaryIn(m_pCbInH,m_pManualParas->m_binIn,7);
	GlobalSetQcheckState_BinaryIn(m_pCbInI,m_pManualParas->m_binIn,8);
	GlobalSetQcheckState_BinaryIn(m_pCbInJ,m_pManualParas->m_binIn,9);*/

// 	m_pCbInA->setChecked(m_pManualParas->m_binIn[0].nSelect);
// 	m_pCbInB->setChecked(m_pManualParas->m_binIn[1].nSelect);
// 	m_pCbInC->setChecked(m_pManualParas->m_binIn[2].nSelect);
// 	m_pCbInD->setChecked(m_pManualParas->m_binIn[3].nSelect);
// 	m_pCbInE->setChecked(m_pManualParas->m_binIn[4].nSelect);
// 	m_pCbInF->setChecked(m_pManualParas->m_binIn[5].nSelect);
// 	m_pCbInG->setChecked(m_pManualParas->m_binIn[6].nSelect);
// 	m_pCbInH->setChecked(m_pManualParas->m_binIn[7].nSelect);
// 	if (g_nBinCount == 10)
// 	{
// 		m_pCbInI->setChecked(m_pManualParas->m_binIn[8].nSelect);
// 		m_pCbInJ->setChecked(m_pManualParas->m_binIn[9].nSelect);
// 	}

// 	if(	m_pManualParas->m_nBinLogic)
// 	{
// 		m_pBtnAnd->setChecked(true);
// 	}
// 	else
// 	{
// 		m_pBtnOr->setChecked(true);
// 	}

	//老化、直流、自动
	m_pCbOld->setChecked(m_pManualParas->m_bAging);
	m_pCbAuto->setChecked(m_pManualParas->m_bAuto);

	if (m_pManualParas->m_bDC)
	{
		m_pCbDC->setCheckState(Qt::Checked);
	}
	else
	{
		m_pCbDC->setCheckState(Qt::Unchecked);
	}

	if (g_oSystemParas.m_fAuxDC_Vol == 0)
	{
		m_pEditUdc->setDisabled(false);
		//m_pEditUdc->setText(QString::number(m_pManualParas->m_fVolAux,'f',3));	//20240624 huangliang
		((QSettingLineEdit*)m_pEditUdc)->UpdateStructText(CVariantDataAddress(&m_pManualParas->m_fVolAux), 3);
	}
	else
	{
		m_pEditUdc->setDisabled(true);
		//m_pEditUdc->setText(QString::number(g_oSystemParas.m_fAuxDC_Vol,'f',3));	//20240624 huangliang
		((QSettingLineEdit*)m_pEditUdc)->UpdateStructText(CVariantDataAddress(&g_oSystemParas.m_fAuxDC_Vol), 3);
	}

	/*m_pEditDelayed->setText(QString::number(m_pManualParas->m_manuGradient.fTrigDelay,'f',2));
	m_pEditDelayed->setDisabled(bAuto);*/
}

void QManualView_Paras::InitGradientData()
{
	if (m_pManualParas->m_nGradientTpSelect == phasor_type)
	{
		//20240624 huangliang
		//m_pEditInitVal->setText(QString::number(m_pManualParas->m_manuGradient.fStart,'f',1));
		((QSettingLineEdit*)m_pEditInitVal)->UpdateStructText(CVariantDataAddress(&m_pManualParas->m_manuGradient.fStart), 1);
		//m_pEditFinishVal->setText(QString::number(m_pManualParas->m_manuGradient.fEnd,'f',1));
		((QSettingLineEdit*)m_pEditFinishVal)->UpdateStructText(CVariantDataAddress(&m_pManualParas->m_manuGradient.fEnd), 1);
		//m_pEditStep->setText(QString::number(m_pManualParas->m_manuGradient.fStep,'f',1));
		((QSettingLineEdit*)m_pEditStep)->UpdateStructText(CVariantDataAddress(&m_pManualParas->m_manuGradient.fStep), 1);
	}
	else
	{
		//20240624 huangliang
		//m_pEditInitVal->setText(QString::number(m_pManualParas->m_manuGradient.fStart,'f',3));  //有效位数改为三位 20210912 sf
		((QSettingLineEdit*)m_pEditInitVal)->UpdateStructText(CVariantDataAddress(&m_pManualParas->m_manuGradient.fStart), 3);
		//m_pEditFinishVal->setText(QString::number(m_pManualParas->m_manuGradient.fEnd,'f',3));
		((QSettingLineEdit*)m_pEditFinishVal)->UpdateStructText(CVariantDataAddress(&m_pManualParas->m_manuGradient.fEnd), 3);
		//m_pEditStep->setText(QString::number(m_pManualParas->m_manuGradient.fStep,'f',3));
		((QSettingLineEdit*)m_pEditStep)->UpdateStructText(CVariantDataAddress(&m_pManualParas->m_manuGradient.fStep), 3);
	}

	//20240624 huangliang
	//m_pEditTime->setText(QString::number(m_pManualParas->m_manuGradient.fStepTime,'f',3));
	((QSettingLineEdit*)m_pEditTime)->UpdateStructText(CVariantDataAddress(&m_pManualParas->m_manuGradient.fStepTime), 3);

	m_pCbbChangeType->setCurrentIndex(m_pManualParas->m_manuGradient.nMode);

	para_type var = getParaTypeByInt(m_pManualParas->m_nGradientChSelect);
	InitGradientVarList();
	InitGradientVar(var);

	switch (m_pManualParas->m_nGradientTpSelect)
	{
	case amplitude_type:
		m_pCbbSelect->setCurrentIndex(0);
		break;
	case phasor_type:
		m_pCbbSelect->setCurrentIndex(1);
		break;
	case fre_type:
		m_pCbbSelect->setCurrentIndex(2);
		break;
	default:
		break;
	}
}

void QManualView_Paras::InitGradientVarList()
{
	m_pCbbChannel->clear();

	if (m_pTestResource == NULL)
	{
		return;
	}

	m_pTestResource->AddGradientChs(m_oGradientChs,TRUE);

	CDataTypeValue *pCurTypeValue = NULL;
	POS pos = m_oGradientChs.GetHeadPosition();

	while(pos)
	{
		pCurTypeValue = (CDataTypeValue *)m_oGradientChs.GetNext(pos);
#ifndef _PSX_QT_LINUX_
		m_pCbbChannel->addItem(pCurTypeValue->m_strID);
#else
		m_pCbbChannel->addItem(pCurTypeValue->m_strID.GetString());
#endif
	}
}

void QManualView_Paras::InitGradientVar(para_type vartype)
{
	CDataTypeValue *pCurSelData = m_oGradientChs.FindByIndex(vartype);

	if (pCurSelData == NULL)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前选择的递变通道(Index=%d)未查找到."),vartype);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_Gradient_CurselinNotFound.GetString(),vartype);//lcq 3.13 当前选择的递变通道(Index=%d)未查找到
		return;
	}
	else
	{
		long nIndex = m_oGradientChs.FindIndex(pCurSelData);
		ASSERT(nIndex>=0);
		m_pCbbChannel->setCurrentIndex(nIndex);
	}
}

float QManualView_Paras::slot_lne_Changed(QLineEdit* pLineEdit)
{
	//20240703 huangliang 
	if (pLineEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if(((QSettingLineEdit*)pLineEdit)->IsSetting())
		{
			float fv = ((QSettingLineEdit*)pLineEdit)->GetValue().toFloat();
			return fv;
		}		
	}

	float fv = pLineEdit->text().toFloat();
	QString strvar = m_pCbbChannel->currentText();
	int index = m_pCbbSelect->currentIndex();
	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
	float fDcVMax = g_oLocalSysPara.m_fDC_VolMax;
	float fDcIMax = g_oLocalSysPara.m_fDC_CurMax;
	switch (index)
	{
	case 0:
		{
			if (m_pManualParas->m_bDC)
			{
				if (strvar.contains("U"))
				{
					if (fv>fDcVMax)
					{
						fv = fDcVMax;
					}
					if (fv<(fDcVMax*(-1)))
					{
						fv = fDcVMax*(-1);
					}
				}
				else if (strvar.contains("I"))
				{
					if (fv>fDcIMax)
					{
						fv = fDcIMax;
					}
					if (fv<(fDcIMax*(-1)))
					{
						fv = fDcIMax*(-1);
					}
				}
			}
			else
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

void QManualView_Paras::slot_lne_startChanged()
{
	m_pManualParas->m_manuGradient.fStart = slot_lne_Changed(m_pEditInitVal);

	if(m_pCbbChannel->currentText().contains("U"))
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

void QManualView_Paras::slot_lne_endChanged()
{
	m_pManualParas->m_manuGradient.fEnd = slot_lne_Changed(m_pEditFinishVal);

	if(m_pCbbChannel->currentText().contains("U"))
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

//void QManualView_Paras::slot_lne_delayedChanged()
//{
//	QString str = m_pEditDelayed->text();
//	float fv = str.toFloat();
//	fv=setLimit(0,999.999,fv);
//
//	if (m_pManualParas->m_manuGradient.fTrigDelay != fv)
//	{
//		m_pManualParas->m_manuGradient.fTrigDelay = fv;
//	}
//
//	m_pEditDelayed->setText(QString::number(m_pManualParas->m_manuGradient.fTrigDelay,'f',2));
//}

void QManualView_Paras::slot_lne_stepChanged()
{
	//20240703 huangliang 
	if (m_pEditStep->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if(((QSettingLineEdit*)m_pEditStep)->IsSetting())
		{
			return ;
		}		
	}

	float fv = m_pEditStep->text().toFloat();
	if (qAbs(fv)<=EPSINON)
	{
		fv = 0.001;
	}

	QString strvar = m_pCbbChannel->currentText();
	int index = m_pCbbSelect->currentIndex();
	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
	float fDcVMax = g_oLocalSysPara.m_fDC_VolMax;
	float fDcIMax = g_oLocalSysPara.m_fDC_CurMax;

	switch (index)
	{
	case 0:
		{
			if (m_pManualParas->m_bDC)
			{
				if (strvar.contains("U"))
				{
					if (fv>fDcVMax)
					{
						fv = fDcVMax;
					}

					if (fv<(fDcVMax*(-1)))
					{
						fv = fDcVMax*(-1);
					}
				}
				else if (strvar.contains("I"))
				{
					if (fv>fDcIMax)
					{
						fv = fDcIMax;
					}

					if (fv<(fDcIMax*(-1)))
					{
						fv = fDcIMax*(-1);
					}
				}
			}
			else
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
		m_pEditStep->setText(QString::number(fv,'f',1));
	}
	else
	{
		m_pEditStep->setText(QString::number(fv,'f',3));
	}
}

void QManualView_Paras::slot_lne_steptimeChanged()
{
	//20240703 huangliang 
	if (m_pEditTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if(((QSettingLineEdit*)m_pEditTime)->IsSetting())
		{
			return ;
		}		
	}

	float fv = m_pEditTime->text().toFloat();
	fv = setLimit(0,999.999,fv);

	if (m_pManualParas->m_manuGradient.fStepTime != fv)
	{
		m_pManualParas->m_manuGradient.fStepTime = fv;
	}

	m_pEditTime->setText(QString::number(fv,'f',3));
}

void QManualView_Paras::slot_lne_UdcChanged()
{
	//20240703 huangliang 
	if (m_pEditUdc->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if(((QSettingLineEdit*)m_pEditUdc)->IsSetting())
		{
			return ;
		}		
	}

	float fv = m_pEditUdc->text().toFloat();
	
	if (fv < 110)
	{
		
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("辅助直流输出最小值110V。"));
		fv = m_pManualParas->m_fVolAux;
	}

	if (fv > 300)
	{

		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("输入值(%.3f)超出辅助直流输出最大值300V。"),fv);
		fv = m_pManualParas->m_fVolAux;
	}

	if ( m_pManualParas->m_fVolAux!= fv)
	{
		 m_pManualParas->m_fVolAux= fv;
	}

	m_pEditUdc->setText(QString::number(fv,'f',3));


}

void QManualView_Paras::slot_btn_LockClicked()
{
	if (m_pManualParas->m_bLockChanged)
	{
		m_bControlLock = true;
		m_pManualParas->m_bLockChanged = false;
		//xlang_SetLangStrToWidget(m_pBtnLock, "Manual_Lock", XLang_Ctrls_QPushButton);
		m_pBtnLock->setIcon(m_imgUnlock);
	}
	else
	{
		m_bControlLock = false;
		m_pManualParas->m_bLockChanged = true;
		//xlang_SetLangStrToWidget(m_pBtnLock, "Manual_UnLock", XLang_Ctrls_QPushButton);
		m_pBtnLock->setIcon(m_imgLock);
	}

	m_pManualParas->m_bBinStop = TRUE;
}

void QManualView_Paras::ChannelTableItemValue_AllFreq(float fstep,int AddOrMinus,bool bDC)
{
	if (m_pTestResource != NULL)
	{
		CString strChID;
		CExBaseObject *pChObj = NULL;

		for (int nChIndex = 0;nChIndex<6;nChIndex++ )
		{
			strChID.Format(_T("U%ld"),nChIndex+1);
			pChObj = m_pTestResource->m_oVolChRsListRef.FindByID(strChID);

			if (pChObj != NULL)
			{
				emit sig_ChannelTableItemValue(pChObj->m_strName,fstep,fre_type,AddOrMinus,bDC);
			}

			strChID.Format(_T("I%ld"),nChIndex+1);
			pChObj = m_pTestResource->m_oCurChRsListRef.FindByID(strChID);

			if (pChObj != NULL)
			{
				emit sig_ChannelTableItemValue(pChObj->m_strName,fstep,fre_type,AddOrMinus,bDC);
			}
		}
	}
}

void QManualView_Paras::slot_btn_AddClicked()
{
	QString str = m_pCbbChannel->currentText();
	int index = m_pCbbSelect->currentIndex();
	float fstep = m_pManualParas->m_manuGradient.fStep;
	CDataTypeValue *pDataTypeValue = (CDataTypeValue*)m_oGradientChs.GetAtIndex(m_pCbbChannel->currentIndex());

	if (pDataTypeValue != NULL)
	{
		if (pDataTypeValue->GetIndex() == freAll_type)//对于修改前两组频率的模式,单独处理
		{
			ChannelTableItemValue_AllFreq(fstep,1,m_pManualParas->m_bDC);
			return;
		}
	}

	switch (index)
	{
	case amplitude_type:
	case phasor_type:
	case fre_type:
		if (str.length()<=3)
		{
			emit sig_ChannelTableItemValue(str,fstep,index,1,m_pManualParas->m_bDC);
		}
		else
		{
			QStringList chanelist = str.split(",");
			for (int i=0;i<chanelist.size();i++)
			{
				QString ch = chanelist.at(i);
				emit sig_ChannelTableItemValue(ch,fstep,index,1,m_pManualParas->m_bDC);
			}
		}
		break;
	default:
		break;
	}
}

void QManualView_Paras::slot_btn_MinusClicked()
{
	QString str = m_pCbbChannel->currentText();
	int index = m_pCbbSelect->currentIndex();
	float fstep = m_pManualParas->m_manuGradient.fStep;
	CDataTypeValue *pDataTypeValue = (CDataTypeValue*)m_oGradientChs.GetAtIndex(m_pCbbChannel->currentIndex());

	if (pDataTypeValue != NULL)
	{
		if (pDataTypeValue->GetIndex() == freAll_type)//对于修改前两组频率的模式,单独处理
		{
			ChannelTableItemValue_AllFreq(fstep,-1,m_pManualParas->m_bDC);
			return;
		}
	}

	switch (index)
	{
	case amplitude_type:
	case phasor_type:
	case fre_type:
		if (str.length()<=3)
		{
			emit sig_ChannelTableItemValue(str,fstep,index,-1,m_pManualParas->m_bDC);
		}
		else
		{
			QStringList chanelist = str.split(",");
			for (int i=0;i<chanelist.size();i++)
			{
				QString ch = chanelist.at(i);
				emit sig_ChannelTableItemValue(ch,fstep,index,-1,m_pManualParas->m_bDC);
			}
		}
		break;
	default:
		break;
	}
}

void QManualView_Paras::slot_cb_OldClicked()
{
	bool bIsChecked = m_pCbOld->isChecked();
	if(m_pManualParas->m_bAging != bIsChecked)
	{
		m_pManualParas->m_bAging = bIsChecked;
	}
}

void QManualView_Paras::slot_cb_AutoClicked()
{
	bool bIsChecked = false;
	if (m_pCbAuto->isChecked())
	{
		m_bControlLock = false;
		bIsChecked = true;
		m_pBtnAdd->setDisabled(true);
		m_pBtnMinus->setDisabled(true);
		//m_pEditAction->setDisabled(false);
		//m_pEditDelayed->setDisabled(true);
	}
	else
	{
		m_bControlLock = false;
		bIsChecked = false;	
		m_pBtnAdd->setDisabled(false);
		m_pBtnMinus->setDisabled(false);
		//m_pEditAction->setDisabled(true);
		//m_pEditDelayed->setDisabled(false);
	}

	if(m_pManualParas->m_bAuto != bIsChecked)
	{
		m_pManualParas->m_bAuto = bIsChecked;
	}

	m_pEditInitVal->setDisabled(!m_pManualParas->m_bAuto);
	m_pEditFinishVal->setDisabled(!m_pManualParas->m_bAuto);
	m_pCbbChangeType->setDisabled(!m_pManualParas->m_bAuto);
	m_pEditTime->setDisabled(!m_pManualParas->m_bAuto);

	g_oSttTestResourceMngr.m_oRtDataMngr.SetAutoMode(m_pManualParas->m_bAuto);
}

void QManualView_Paras::slot_cb_DCClicked()
{
	bool bIsChecked = false;
	bool bOldIsChecked = m_pManualParas->m_bDC;

	if (m_pCbDC->isChecked())
	{
		bIsChecked = true;

		if (m_pCbbSelect->currentIndex() != 0)
		{
			m_pManualParas->m_bDC = true;
			slot_cbb_SelectChanged(0);
		}
	}

	m_pCbbSelect->setDisabled(bIsChecked);

	if (bOldIsChecked != bIsChecked)
	{
		m_pManualParas->setDC(bIsChecked, true);
	}
}

void QManualView_Paras::slot_cbb_SelectChanged(int index)
{
	m_pManualParas->m_nGradientTpSelect = index;
	SetUnitType(index);
	UpdateData();
}

void QManualView_Paras::slot_cbb_ChannelChanged(int index)
{
	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oGradientChs.GetAtIndex(index);

	if(!pCurDataTypeValue)
	{
		return;
	}

	if ((pCurDataTypeValue->GetIndex() == freAll_type)&&(m_pCbDC->isChecked()))
	{
		m_pCbbChannel->setCurrentIndex(0);
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("当前为直流输出模式,不可切换为频率递变."));
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_CurinDCincrement.GetString());  //lcq 3.13 当前为直流输出模式,不可切换为频率递变.
		return;
	}

	int nChanneType = 1;
	m_pManualParas->m_nGradientChSelect = pCurDataTypeValue->GetIndex();

// 	m_nChanneType = 1;

	if(m_pCbbChannel->currentText().indexOf("U") != -1)
	{
		//m_nChanneType = 0;
		nChanneType = 0;
	}

	if ((pCurDataTypeValue->GetIndex() == freAll_type)
		&&(m_pCbbSelect->currentIndex() != 2))
	{
		m_pCbbSelect->setCurrentIndex(2);
	} 

//2024-9-29 wuxinyi 修改通道，始值和终值自动修改到对应最大值
	if (nChanneType != m_nChanneType)
	{
		m_nChanneType = nChanneType;

		slot_lne_endChanged();
		slot_lne_startChanged();

		float fStartValue = m_pEditInitVal->text().toFloat();
		float fEndValue = m_pEditFinishVal->text().toFloat();

		if ((fEndValue - fStartValue) <= 0.00001)
		{
			m_pEditInitVal->setText(_T("0.000"));
			slot_lne_startChanged();
		}
	}



	SetUnitType(m_pCbbSelect->currentIndex());
};

void QManualView_Paras::slot_cbb_ChangeTypeChanged(int index)
{
	m_pManualParas->m_manuGradient.nMode = index;
}

void QManualView_Paras::slot_ck_Out1StateChanged()
{
	if (m_pCbOut1->checkState() == Qt::Checked)
	{
		m_pManualParas->m_binOut[0].nState = 1;
	}
	else
	{
		m_pManualParas->m_binOut[0].nState = 0;
	}
}

void QManualView_Paras::slot_ck_Out2StateChanged()
{
	if (m_pCbOut2->checkState() == Qt::Checked)
	{
		m_pManualParas->m_binOut[1].nState = 1;
	}
	else
	{
		m_pManualParas->m_binOut[1].nState = 0;
	}
}

void QManualView_Paras::slot_ck_Out3StateChanged()
{
	if (m_pCbOut3->checkState() == Qt::Checked)
	{
		m_pManualParas->m_binOut[2].nState = 1;
	}
	else
	{
		m_pManualParas->m_binOut[2].nState = 0;
	}
}

void QManualView_Paras::slot_ck_Out4StateChanged()
{
	if (m_pCbOut4->checkState() == Qt::Checked)
	{
		m_pManualParas->m_binOut[3].nState = 1;
	}
	else
	{
		m_pManualParas->m_binOut[3].nState = 0;
	}
}

//void QManualView_Paras::slot_ck_Out5StateChanged()
//{
//}
//
//void QManualView_Paras::slot_ck_Out6StateChanged()
//{
//	
//}
//
//void QManualView_Paras::slot_ck_Out7StateChanged()
//{
//	
//}
//
//void QManualView_Paras::slot_ck_Out8StateChanged()
//{
//	
//}
//
//void QManualView_Paras::slot_ck_Out9StateChanged()
//{
//	
//}
//
//void QManualView_Paras::slot_ck_Out10StateChanged()
//{
//	
//}

//void QManualView_Paras::ValidBinSelect()
//{
//	if (!Global_CheckBinSelect(m_pManualParas->m_binIn,g_nBinCount))
//	{
//		stt_GetBinaryConfig()->m_binIn[0].nSelect = 1;
//	}
//}
//
//void QManualView_Paras::slot_ck_InAStateChanged()
//{
//	ValidBinSelect();
//}
//
//void QManualView_Paras::slot_ck_InBStateChanged()
//{
//	ValidBinSelect();
//}
//
//void QManualView_Paras::slot_ck_InCStateChanged()
//{
//	ValidBinSelect();
//}
//
//void QManualView_Paras::slot_ck_InDStateChanged()
//{
//	ValidBinSelect();
//}
//
//void QManualView_Paras::slot_ck_InEStateChanged()
//{
//	ValidBinSelect();
//}
//
//void QManualView_Paras::slot_ck_InFStateChanged()
//{
//	ValidBinSelect();
//}
//
//void QManualView_Paras::slot_ck_InGStateChanged()
//{
//	ValidBinSelect();
//}
//
//void QManualView_Paras::slot_ck_InHStateChanged()
//{
//	ValidBinSelect();
//}
//
//void QManualView_Paras::slot_ck_InIStateChanged()
//{
//	ValidBinSelect();
//}
//
//void QManualView_Paras::slot_ck_InJStateChanged()
//{
//	ValidBinSelect();
//}

//void QManualView_Paras::slot_rb_RdAndStateChanged()
//{
//		
//}
//
//void QManualView_Paras::slot_rb_RdOrStateChanged()
//{
//	
//}

void QManualView_Paras::StartInit()
{
	m_bControlLock = false;
	m_pManualParas->m_bLockChanged = m_bControlLock;

	//m_pEditAction->setText("");
	//m_pEditActionTime->setText("");
	//m_pEditReturn->setText("");
	//m_pEditReturnTime->setText("");

	bool bAuto = m_pManualParas->m_bAuto;

	m_pBtnAdd->setDisabled(bAuto);
	m_pBtnMinus->setDisabled(bAuto);
	m_pBtnLock->setDisabled(bAuto);

	m_pCbbChangeType->setDisabled(bAuto);
	m_pCbbChannel->setDisabled(bAuto);
	m_pCbbSelect->setDisabled(bAuto);
	m_pEditStep->setDisabled(bAuto);

	if(m_pCbDC->isChecked())
	{
		m_pCbbSelect->setDisabled(true);
	}

	m_pEditUdc->setDisabled(true);

	//m_pEditDelayed->setDisabled(true);

// 	m_pCbOut1->setDisabled(bAuto);
// 	m_pCbOut2->setDisabled(bAuto);
// 	m_pCbOut3->setDisabled(bAuto);
// 	m_pCbOut4->setDisabled(bAuto);
// 	m_pCbOut5->setDisabled(bAuto);
// 	m_pCbOut6->setDisabled(bAuto);
// 	m_pCbOut7->setDisabled(bAuto);
// 	m_pCbOut8->setDisabled(bAuto);
// 	if (g_nBoutCount == 10)
// 	{
// 		m_pCbOut9->setDisabled(bAuto);
// 		m_pCbOut10->setDisabled(bAuto);
// 	}

	GlobalSetQcheckEnable_Binary(m_pCbOut1,0,g_nBoutCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbOut2,1,g_nBoutCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbOut3,2,g_nBoutCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbOut4,3,g_nBoutCount,!bAuto);
	/*GlobalSetQcheckEnable_Binary(m_pCbOut5,4,g_nBoutCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbOut6,5,g_nBoutCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbOut7,6,g_nBoutCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbOut8,7,g_nBoutCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbOut9,8,g_nBoutCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbOut10,9,g_nBoutCount,!bAuto);

	GlobalSetQcheckEnable_Binary(m_pCbInA,0,g_nBinCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbInB,1,g_nBinCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbInC,2,g_nBinCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbInD,3,g_nBinCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbInE,4,g_nBinCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbInF,5,g_nBinCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbInG,6,g_nBinCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbInH,7,g_nBinCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbInI,8,g_nBinCount,!bAuto);
	GlobalSetQcheckEnable_Binary(m_pCbInJ,9,g_nBinCount,!bAuto);*/
// 	m_pCbInA->setDisabled(true);
// 	m_pCbInB->setDisabled(true);
// 	m_pCbInC->setDisabled(true);
// 	m_pCbInD->setDisabled(true);
// 	m_pCbInE->setDisabled(true);
// 	m_pCbInF->setDisabled(true);
// 	m_pCbInG->setDisabled(true);
// 	m_pCbInH->setDisabled(true);
// 	if (g_nBinCount == 10)
// 	{
// 		m_pCbInI->setDisabled(true);
// 		m_pCbInJ->setDisabled(true);
// 	}

	/*m_pBtnAnd->setDisabled(true);
	m_pBtnOr->setDisabled(true);*/

	m_pEditTime->setDisabled(true);
	m_pEditInitVal->setDisabled(true);
	m_pEditFinishVal->setDisabled(true);
	m_pCbbChangeType->setDisabled(TRUE);

#ifdef _PSX_QT_LINUX_
	m_pCbOld->setDisabled(true);//zhouhj 在脱机模式下,固定将老化不可编辑
#else
	m_pCbOld->setDisabled(true);
#endif
	m_pCbAuto->setDisabled(true);
	m_pCbDC->setDisabled(true);
}

void QManualView_Paras::StopInit()
{
	m_bControlLock = true;
	m_pManualParas->m_bLockChanged = false;
	//xlang_SetLangStrToWidget(m_pBtnLock, "Manual_Lock", XLang_Ctrls_QPushButton);
	m_pBtnLock->setIcon(m_imgUnlock);
	m_pBtnLock->setDisabled(true);

	m_pBtnAdd->setDisabled(m_pManualParas->m_bAuto);
	m_pBtnMinus->setDisabled(m_pManualParas->m_bAuto);

	m_pCbbChannel->setDisabled(false);
	m_pCbbSelect->setDisabled(false);
	//m_pCbbChangeType->setDisabled(false);
	m_pEditStep->setDisabled(false);

	if(m_pCbDC->isChecked())
	{
		m_pCbbSelect->setDisabled(true);
	}

	m_pEditTime->setDisabled(!m_pManualParas->m_bAuto);
	m_pEditInitVal->setDisabled(!m_pManualParas->m_bAuto);
	m_pEditFinishVal->setDisabled(!m_pManualParas->m_bAuto);
	m_pCbbChangeType->setDisabled(!m_pManualParas->m_bAuto);

	m_pCbAuto->setDisabled(false);

	if (g_oSystemParas.m_fAuxDC_Vol == 0)
	{
		m_pEditUdc->setDisabled(false);
	}
	//m_pEditUdc->setDisabled(false);

#ifdef _PSX_QT_LINUX_
	m_pCbOld->setDisabled(true);//zhouhj 在脱机模式下,固定将老化不可编辑
#else
	m_pCbOld->setDisabled(false);
#endif

	m_pCbDC->setDisabled(false);
	//m_pEditDelayed->setDisabled(false);

	m_pManualParas->m_bLockChanged = false;		

// 	m_pCbOut1->setDisabled(false);
// 	m_pCbOut2->setDisabled(false);
// 	m_pCbOut3->setDisabled(false);
// 	m_pCbOut4->setDisabled(false);
// 	m_pCbOut5->setDisabled(false);
// 	m_pCbOut6->setDisabled(false);
// 	m_pCbOut7->setDisabled(false);
// 	m_pCbOut8->setDisabled(false);
// 	if (g_nBoutCount == 10)
// 	{
// 		m_pCbOut9->setDisabled(false);
// 		m_pCbOut10->setDisabled(false);
// 	}
// 
// 	m_pCbInA->setDisabled(false);
// 	m_pCbInB->setDisabled(false);
// 	m_pCbInC->setDisabled(false);
// 	m_pCbInD->setDisabled(false);
// 	m_pCbInE->setDisabled(false);
// 	m_pCbInF->setDisabled(false);
// 	m_pCbInG->setDisabled(false);
// 	m_pCbInH->setDisabled(false);
// 	if (g_nBinCount == 10)
// 	{
// 		m_pCbInI->setDisabled(false);
// 		m_pCbInJ->setDisabled(false);
// 	}

	GlobalSetQcheckEnable_Binary(m_pCbOut1,0,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbOut2,1,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbOut3,2,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbOut4,3,g_nBoutCount,true);
	/*GlobalSetQcheckEnable_Binary(m_pCbOut5,4,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbOut6,5,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbOut7,6,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbOut8,7,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbOut9,8,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbOut10,9,g_nBoutCount,true);

	GlobalSetQcheckEnable_Binary(m_pCbInA,0,g_nBinCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbInB,1,g_nBinCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbInC,2,g_nBinCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbInD,3,g_nBinCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbInE,4,g_nBinCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbInF,5,g_nBinCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbInG,6,g_nBinCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbInH,7,g_nBinCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbInI,8,g_nBinCount,true);
	GlobalSetQcheckEnable_Binary(m_pCbInJ,9,g_nBinCount,true);*/

	/*m_pBtnAnd->setDisabled(false);
	m_pBtnOr->setDisabled(false);*/
}

void QManualView_Paras::slot_UpdateUdcEditEnabled()
{
	if (g_oSystemParas.m_fAuxDC_Vol == 0)
	{
		m_pEditUdc->setDisabled(false);
	}
	else
	{
		m_pEditUdc->setDisabled(true);
	}

	//20240624 huangliang
	//m_pEditUdc->setText(QString::number(g_oSystemParas.m_fAuxDC_Vol,'f',3));
	((QSettingLineEdit*)m_pEditUdc)->UpdateStructText(CVariantDataAddress(&g_oSystemParas.m_fAuxDC_Vol), 3);
}
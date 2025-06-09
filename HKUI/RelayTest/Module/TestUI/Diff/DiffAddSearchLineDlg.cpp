#include "DiffAddSearchLineDlg.h"
#include "ui_DiffAddSearchLineDlg.h"
extern CFont *g_pSttGlobalFont;
QDiffAddSearchLineDlg::QDiffAddSearchLineDlg(QWidget *parent) :
m_pAddMult_UI(new Ui::QDiffAddSearchLineDlg)
{
	m_pAddMult_UI->setupUi(this);
	InitUI();
	m_dBeginVal = 0.100;
    m_dEndVal = 5.000;
	m_dStep = 0.100;
	m_dTime = 0.200;
	m_nPoints = 50;

	m_nErrorLogic = 0;			//误差逻辑
	m_dAbsErr = 2.000;			//差动曲线搜索-绝对误差
	m_dRelErr = 0.020;			//差动曲线搜索-相对误差

	m_Isbcheck_FaultType[0] = true;
	for (int i = 1; i < 7;i++)
	{
		m_Isbcheck_FaultType[i] = false;
	}
}

QDiffAddSearchLineDlg::~QDiffAddSearchLineDlg()
{
	delete m_pAddMult_UI;
}
void QDiffAddSearchLineDlg::on_m_btnSave_clicked()
{
	this->done(Accepted);
}

void QDiffAddSearchLineDlg::on_m_btnClose_clicked()
{
	this->close();
}
void QDiffAddSearchLineDlg::InitUI()
{
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);
	m_pAddMult_UI->m_labTips->setVisible(false);
	CString strText;

	m_pAddMult_UI->m_cmbErrorLogic->addItem(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError);
	m_pAddMult_UI->m_cmbErrorLogic->addItem(/*"相对误差"*/g_sLangTxt_StateEstimate_RelError);

	strText = g_sLangTxt_StateEstimate_AbsError + "or" + g_sLangTxt_StateEstimate_RelError;
	m_pAddMult_UI->m_cmbErrorLogic->addItem(/*"相对误差or绝对误差"*/strText);

	strText = g_sLangTxt_StateEstimate_AbsError + "&" + g_sLangTxt_StateEstimate_RelError;
	m_pAddMult_UI->m_cmbErrorLogic->addItem(/*"相对误差&绝对误差"*/strText);
	m_pAddMult_UI->m_cmbErrorLogic->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);

	m_pAddMult_UI->m_labSL_Time->setText(/*最大故障时间(s)*/g_sLangTxt_Diff_FaultTime);
	if (!m_pAddMult_UI->m_labSL_Time->text().contains(":"))
	{
		m_pAddMult_UI->m_labSL_Time->setText(m_pAddMult_UI->m_labSL_Time->text() + ":");
	}
	m_pAddMult_UI->m_labSL_Points->setText(/*测试点数*/g_sLangTxt_Diff_Points);
	if (!m_pAddMult_UI->m_labSL_Points->text().contains(":"))
	{
		m_pAddMult_UI->m_labSL_Points->setText(m_pAddMult_UI->m_labSL_Points->text() + ":");
	}
	m_pAddMult_UI->groupBox->setTitle(/*故障类型*/g_sLangTxt_Gradient_FailType);
	m_pAddMult_UI->groupBox_2->setTitle(/*结果判断*/g_sLangTxt_Native_ResultJudge);
	m_pAddMult_UI->m_lbErrorLogic->setText(/*误差类型*/g_sLangTxt_StateEstimate_ErrorType);
	if (!m_pAddMult_UI->m_lbErrorLogic->text().contains(":"))
	{
		m_pAddMult_UI->m_lbErrorLogic->setText(m_pAddMult_UI->m_lbErrorLogic->text() + ":");
	}
	m_pAddMult_UI->m_lbActRelErr->setText(/*动作值相对误差(%)*/g_sLangTxt_Diff_ActRelErr);
	if (!m_pAddMult_UI->m_lbActRelErr->text().contains(":"))
	{
		m_pAddMult_UI->m_lbActRelErr->setText(m_pAddMult_UI->m_lbActRelErr->text() + ":");
	}
	m_pAddMult_UI->m_btnSave->setText(/*确定*/g_sLangTxt_OK);
	m_pAddMult_UI->m_btnClose->setText(/*取消*/g_sLangTxt_Cancel);
	setWindowTitle(/*添加搜索线*/g_sLangTxt_Diff_AddSearchLine);
}

void QDiffAddSearchLineDlg::GetPageToValue(CDvmData *pData)
{
	if(pData == NULL)
		return;
	bool bvalue;

	if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_BEGINVAL)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtSL_BeginVal->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_ENDVAL)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtSL_EndVal->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_STEP)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtSL_Step->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_TIME)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtSL_Time->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_POINTS)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtSL_Points->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_AN)
	{
		bvalue = m_pAddMult_UI->m_check_AN->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_BN)
	{
		bvalue = m_pAddMult_UI->m_check_BN->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_CN)
	{
		bvalue = m_pAddMult_UI->m_check_CN->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_AB)
	{
		bvalue = m_pAddMult_UI->m_check_AB->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_BC)
	{
		bvalue = m_pAddMult_UI->m_check_BC->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_CA)
	{
		bvalue = m_pAddMult_UI->m_check_CA->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_ABC)
	{
		bvalue = m_pAddMult_UI->m_check_ABC->isChecked();
		pData->m_strValue.setNum(bvalue);
	}
}
void QDiffAddSearchLineDlg::SetValueToPage(CDvmData *pData)
{
	if(pData == NULL)
		return;

	if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_BEGINVAL)
	{
		m_pAddMult_UI->m_txtSL_BeginVal->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_ENDVAL)
	{
		m_pAddMult_UI->m_txtSL_EndVal->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_STEP)
	{
		m_pAddMult_UI->m_txtSL_Step->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_TIME)
	{
		m_pAddMult_UI->m_txtSL_Time->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_POINTS)
	{
		m_pAddMult_UI->m_txtSL_Points->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_AN)
	{
		m_pAddMult_UI->m_check_AN->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_BN)
	{
		m_pAddMult_UI->m_check_BN->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_CN)
	{
		m_pAddMult_UI->m_check_CN->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_AB)
	{
		m_pAddMult_UI->m_check_AB->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_BC)
	{
		m_pAddMult_UI->m_check_BC->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_CA)
	{
		m_pAddMult_UI->m_check_CA->setChecked(pData->m_strValue == "1");
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_ABC)
	{
		m_pAddMult_UI->m_check_ABC->setChecked(pData->m_strValue == "1");
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_MINAXIS)
	{
		UpdateMinaxis(pData->m_strValue == "1");
	}
}

void QDiffAddSearchLineDlg::on_m_txtSL_BeginVal_editingFinished()
{
	m_pAddMult_UI->m_txtSL_BeginVal->setText(CheckDataMinMax(m_pAddMult_UI->m_txtSL_BeginVal->text(),999.999,0,3));
	m_dBeginVal = m_pAddMult_UI->m_txtSL_BeginVal->text().toDouble();
	UpdatePoints();
}
void QDiffAddSearchLineDlg::on_m_txtSL_EndVal_editingFinished()
{
	m_pAddMult_UI->m_txtSL_EndVal->setText(CheckDataMinMax(m_pAddMult_UI->m_txtSL_EndVal->text(),999.999,0,3));
	m_dEndVal = m_pAddMult_UI->m_txtSL_EndVal->text().toDouble();
	UpdatePoints();
}
void QDiffAddSearchLineDlg::on_m_txtSL_Step_editingFinished()
{
	m_pAddMult_UI->m_txtSL_Step->setText(CheckDataMinMax(m_pAddMult_UI->m_txtSL_Step->text(),999.999,0,3));
	m_dStep = m_pAddMult_UI->m_txtSL_Step->text().toDouble();
	UpdatePoints();
}
void QDiffAddSearchLineDlg::on_m_txtSL_Time_editingFinished()
{
	m_pAddMult_UI->m_txtSL_Time->setText(CheckDataMinMax(m_pAddMult_UI->m_txtSL_Time->text(),999.999,0,3));
	m_dTime = m_pAddMult_UI->m_txtSL_Time->text().toDouble();
}
void QDiffAddSearchLineDlg::on_m_txtSL_Points_editingFinished()
{
	m_pAddMult_UI->m_txtSL_Points->setText(CheckDataMinMax(m_pAddMult_UI->m_txtSL_Points->text(),999.999,0,0));
}

void QDiffAddSearchLineDlg::on_m_cmbErrorLogic_currentIndexChanged(int index)
{
	if (index ==4)
	{
		m_nErrorLogic = 5;
	}
	else
	{
		m_nErrorLogic = index;
	}
}
void QDiffAddSearchLineDlg::on_m_editActAbsErr_editingFinished()
{
	m_pAddMult_UI->m_editActAbsErr->setText(CheckDataMinMax(m_pAddMult_UI->m_editActAbsErr->text(), 999.999, 0, 3));
	m_dAbsErr = m_pAddMult_UI->m_editActAbsErr->text().toDouble();
}
void QDiffAddSearchLineDlg::on_m_editActRelErr_editingFinished()
{
	m_pAddMult_UI->m_editActRelErr->setText(CheckDataMinMax(m_pAddMult_UI->m_editActRelErr->text(), 100, 0, 3));
	m_dRelErr = m_pAddMult_UI->m_editActRelErr->text().toDouble();
}

bool QDiffAddSearchLineDlg::CheckSectionState()//20240613 luozibing 最少选择一个故障区段
{
	if (!m_pAddMult_UI->m_check_AN->isChecked()&&\
		!m_pAddMult_UI->m_check_BN->isChecked()&&\
		!m_pAddMult_UI->m_check_CN->isChecked()&&\
		!m_pAddMult_UI->m_check_AB->isChecked()&&\
		!m_pAddMult_UI->m_check_BC->isChecked()&&\
		!m_pAddMult_UI->m_check_CA->isChecked()&&\
		!m_pAddMult_UI->m_check_ABC->isChecked())
	{
		m_pAddMult_UI->m_check_AN->setChecked(true);
		SetApplyTips(/*_T("请至少勾选一个故障区段")*/g_sLangTxt_MaintainatLeastOneFault);
		return true;
	}

	return false;
}
void QDiffAddSearchLineDlg::SetApplyTips(CString strTips)
{
	m_pAddMult_UI->m_labTips->setText(strTips);
	m_pAddMult_UI->m_labTips->setVisible(true);
	m_nTipsTime = startTimer(TIPS_DISPLAY_TIME);
}
void QDiffAddSearchLineDlg::timerEvent(QTimerEvent* ev)
{
	if(ev->timerId() == m_nTipsTime){
		m_pAddMult_UI->m_labTips->setVisible(false);
	}
}

void QDiffAddSearchLineDlg::on_m_check_AN_clicked(bool checked)
{
	if(CheckSectionState())
	{
		return;
	}
	m_Isbcheck_FaultType[0] = checked;
}
void QDiffAddSearchLineDlg::on_m_check_BN_clicked(bool checked)
{
	if(CheckSectionState())
	{
		return;
	}
	m_Isbcheck_FaultType[1] = checked;
}
void QDiffAddSearchLineDlg::on_m_check_CN_clicked(bool checked)
{
	if(CheckSectionState())
	{
		return;
	}
	m_Isbcheck_FaultType[2] = checked;
}
void QDiffAddSearchLineDlg::on_m_check_AB_clicked(bool checked)
{
	if(CheckSectionState())
	{
		return;
	}
	m_Isbcheck_FaultType[3] = checked;
}
void QDiffAddSearchLineDlg::on_m_check_BC_clicked(bool checked)
{
	if(CheckSectionState())
	{
		return;
	}
	m_Isbcheck_FaultType[4] = checked;
}
void QDiffAddSearchLineDlg::on_m_check_CA_clicked(bool checked)
{
	if(CheckSectionState())
	{
		return;
	}
	m_Isbcheck_FaultType[5] = checked;
}
void QDiffAddSearchLineDlg::on_m_check_ABC_clicked(bool checked)
{
	if(CheckSectionState())
	{
		return;
	}
	m_Isbcheck_FaultType[6] = checked;
}

void QDiffAddSearchLineDlg::SetDatas(CDataGroup *pParas)
{
	if (pParas == NULL)
		return;

	m_pCurrDataGroup = pParas;
	CheckAllPresence();
	POS pos = pParas->GetHeadPosition();
	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
		SetValueToPage(pData);
	}
	CheckSectionState();
}

void QDiffAddSearchLineDlg::GetDatas(CDataGroup *pParas)
{
	if (pParas == NULL)
	{
		return;
	}

	m_pCurrDataGroup = pParas;
	CheckAllPresence();

	POS pos = pParas->GetHeadPosition();
	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}

void QDiffAddSearchLineDlg::CheckAllPresence()
{
	//20240624 luozibing 检查ID是否存在
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_BEGINVAL);	//制动电流始值()
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_ENDVAL);	//制动电流终值()
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_STEP);	//变化步长()
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_TIME);	//动作时间()
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_POINTS);	//测试点数

	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_AN);	//故障选择-A-E
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_BN);	//故障选择-B-E
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_CN);	//故障选择-C-E
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_AB);	//故障选择-A-B
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_BC);	//故障选择-B-C
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_CA);	//故障选择-C-A
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_ABC);	//故障选择-ABC
}

void QDiffAddSearchLineDlg::DiffCheckForPresence(CString strID)
{
	//CDvmData 检查ID对应数据是否存在、不存在则添加
	if (m_pCurrDataGroup == NULL)
		return;
	CDvmData *pData = (CDvmData *)m_pCurrDataGroup->FindByID(strID);
	if (pData == NULL)
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strID;
		pNew->m_strID = strID;
		pNew->m_strValue = "0";
		m_pCurrDataGroup->AddNewChild(pNew);
	}
}
void QDiffAddSearchLineDlg::UpdatePoints()
{
	float fstart = m_pAddMult_UI->m_txtSL_BeginVal->text().toFloat();
	float fEnd   = m_pAddMult_UI->m_txtSL_EndVal->text().toFloat();
	float fStep  = m_pAddMult_UI->m_txtSL_Step->text().toFloat();

	int num = 0;
	if (/*fstart > fEnd*/fstart - fEnd > 0.0001)
	{
		while (/*fstart > fEnd*/ fstart - fEnd > 0.0001)
		{
			num++;
			fstart -= fStep;
			if ((/*fstart < fEnd */fEnd - fstart > 0.0001) || (/*fstart == fEnd */fstart - fEnd< 0.0001))
			{
				num++;
			}
		}
	}
	else if (fEnd - fstart> 0.0001)
	{
		while (/*fEnd  > fstart */fEnd - fstart > 0.0001)
		{
			num++;
			fstart += fStep;
			if ((/*fstart > fEnd */fstart - fEnd > 0.0001) || (/*fstart == fEnd */fEnd - fstart <0.0001))
			{
				num++;
			}
		}
	}
	else
	{
		num = 1;
	}

	m_pAddMult_UI->m_txtSL_Points->setText(QString("%1").arg(num));
	m_nPoints = m_pAddMult_UI->m_txtSL_Points->text().toInt();
}
void QDiffAddSearchLineDlg::UpdateMinaxis(int nMinaxis)//0:有名值(A) 1:标幺值(In)
{
	if (nMinaxis)
	{
		m_pAddMult_UI->m_labSL_BeginVal->setText(/*制动电流始值*/g_sLangTxt_Diff_RateBeginVal + "(Ie):");
		m_pAddMult_UI->m_labSL_EndVal->setText(/*制动电流终值*/g_sLangTxt_Diff_RateEndVal + "(Ie):");
		m_pAddMult_UI->m_labSL_Step->setText(/*变化步长*/g_sLangTxt_Diff_Step + "(Ie):");
		m_pAddMult_UI->m_lbActAbsErr->setText(/*动作值绝对误差*/g_sLangTxt_Diff_ActAbsErr + "(Ie):");
	}
	else
	{
		m_pAddMult_UI->m_labSL_BeginVal->setText(/*制动电流始值*/g_sLangTxt_Diff_RateBeginVal + "(A):");
		m_pAddMult_UI->m_labSL_EndVal->setText(/*制动电流终值*/g_sLangTxt_Diff_RateEndVal + "(A):");
		m_pAddMult_UI->m_labSL_Step->setText(/*变化步长*/g_sLangTxt_Diff_Step + "(A):");
		m_pAddMult_UI->m_lbActAbsErr->setText(/*动作值绝对误差*/g_sLangTxt_Diff_ActAbsErr + "(A):");
	}
}
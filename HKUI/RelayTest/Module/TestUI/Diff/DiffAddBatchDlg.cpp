#include "DiffAddBatchDlg.h"
#include "ui_DiffAddBatchDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
extern CFont *g_pSttGlobalFont;

#define GROUPGRID_COLS 3

QDiffAddBatchDlg::QDiffAddBatchDlg(QWidget *parent) :
m_pAddMult_UI(new Ui::QDiffAddBatchDlg)
{
    m_pAddMult_UI->setupUi(this);
	m_pRateGrid = NULL;
	m_pHarmGrid = NULL;
	m_nHarmCustomPoint = 0;
    InitUI();
}

QDiffAddBatchDlg::~QDiffAddBatchDlg()
{
    delete m_pAddMult_UI;
}
void QDiffAddBatchDlg::on_m_btnSave_clicked()
{
    this->done(Accepted);
}

void QDiffAddBatchDlg::on_m_btnClose_clicked()
{
    this->close(); 
}
void QDiffAddBatchDlg::InitUI()
{
    m_pAddMult_UI->m_labTips->setVisible(false);
	m_pRateGrid = new QDiffCharGrid(this);
	m_pRateGrid->InitGrid();
	m_pAddMult_UI->VLayout_Rate->addWidget(m_pRateGrid);

	m_pHarmGrid = new QDiffCharGrid(this);
	m_pHarmGrid->InitGrid();
	m_pAddMult_UI->VLayout_Harm->addWidget(m_pHarmGrid);

	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);

	m_pRateGrid->setFont(*g_pSttGlobalFont);
	m_pRateGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pHarmGrid->setFont(*g_pSttGlobalFont);
	m_pHarmGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);	

	m_pAddMult_UI->m_check_Rate->setText(/*差动搜索*/g_sLangTxt_Diff_RateSearch);
	m_pAddMult_UI->m_check_Harm->setText(/*谐波制动搜索*/g_sLangTxt_Diff_Harm);
	m_pAddMult_UI->m_check_Time->setText(/*动作时间*/g_sLangTxt_DistanceSearch_ActionTime);
	m_pAddMult_UI->m_labTime_ld_2->setText(/*最大故障时间(s)*/g_sLangTxt_Diff_FaultTime);
	if (!m_pAddMult_UI->m_labTime_ld_2->text().contains(":"))
	{
		m_pAddMult_UI->m_labTime_ld_2->setText(m_pAddMult_UI->m_labTime_ld_2->text() + ":");
	}
	m_pAddMult_UI->groupBox->setTitle(/*故障类型*/g_sLangTxt_Gradient_FailType);
	m_pAddMult_UI->tabWidget->setTabText(0, /*差动搜索*/g_sLangTxt_Diff_RateSearch);
	m_pAddMult_UI->tabWidget->setTabText(1, /*谐波制动搜索*/g_sLangTxt_Diff_Harm);
	m_pAddMult_UI->m_btnResEvaluat->setText(/*结果评估*/g_sLangTxt_StateEstimate_ResultEstimate);
	m_pAddMult_UI->m_btnSave->setText(/*确定*/g_sLangTxt_OK);
	m_pAddMult_UI->m_btnClose->setText(/*取消*/g_sLangTxt_Cancel);
	setWindowTitle(g_sLangTxt_Button_AddMultBatch);
}

void QDiffAddBatchDlg::GetPageToValue(CDvmData *pData)
{
    if(pData == NULL)
        return;
    bool bvalue;

    if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_IR)
    {
        pData->m_strValue = m_pAddMult_UI->m_txtTime_lr->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_ID)
    {
        pData->m_strValue = m_pAddMult_UI->m_txtTime_ld->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_RATE)
    {
        bvalue = m_pAddMult_UI->m_check_Rate->isChecked();
        pData->m_strValue.setNum(bvalue);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_HARM)
    {
        bvalue = m_pAddMult_UI->m_check_Harm->isChecked();
        pData->m_strValue.setNum(bvalue);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_TIME)
    {
        bvalue = m_pAddMult_UI->m_check_Time->isChecked();
        pData->m_strValue.setNum(bvalue);
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
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTIME)
	{
		pData->m_strValue = m_pAddMult_UI->m_txtMaxFaultTime->text();
	}
}
void QDiffAddBatchDlg::SetValueToPage(CDvmData *pData)
{
    if(pData == NULL)
        return;

    if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_IR)
    {
        m_pAddMult_UI->m_txtTime_lr->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_ID)
    {
        m_pAddMult_UI->m_txtTime_ld->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_RATE)
    {
        m_pAddMult_UI->m_check_Rate->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_HARM)
    {
        m_pAddMult_UI->m_check_Harm->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_TIME)
    {
        m_pAddMult_UI->m_check_Time->setChecked(pData->m_strValue == "1");
		on_m_check_Time_clicked(pData->m_strValue == "1");
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
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTIME)
	{
		m_pAddMult_UI->m_txtMaxFaultTime->setText(CheckDataMinMax(pData->m_strValue, 999, 0, 3));
	}
}

void QDiffAddBatchDlg::on_m_txtTime_lr_editingFinished()
{
	m_pAddMult_UI->m_txtTime_lr->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTime_lr->text(), 999.999, 0.001, 3));
}
void QDiffAddBatchDlg::on_m_txtTime_ld_editingFinished()
{
	m_pAddMult_UI->m_txtTime_ld->setText(CheckDataMinMax(m_pAddMult_UI->m_txtTime_ld->text(), 999.999, 0.001, 3));
}
void QDiffAddBatchDlg::on_m_txtMaxFaultTime_editingFinished()
{
	m_pAddMult_UI->m_txtMaxFaultTime->setText(CheckDataMinMax(m_pAddMult_UI->m_txtMaxFaultTime->text(), 999.999, 0, 3));
}
bool QDiffAddBatchDlg::CheckSectionState()//20240613 luozibing 最少选择一个故障区段
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
		SetApplyTips(/*_T("请至少勾选一个故障区段！")*/g_sLangTxt_MaintainatLeastOneFault);
        return true;
    }

    return false;
}
bool QDiffAddBatchDlg::CheckFuncState()//至少选择一个功能模块
{
    if (!m_pAddMult_UI->m_check_Rate->isChecked()&&\
        !m_pAddMult_UI->m_check_Harm->isChecked()&&\
        !m_pAddMult_UI->m_check_Time->isChecked())
    {
        m_pAddMult_UI->m_check_Rate->setChecked(true);
		SetApplyTips(/*_T("请至少勾选一个功能模块！")*/g_sLangTxt_MaintainatLeastOneFunc);
        return true;
    }

    return false;
}
void QDiffAddBatchDlg::SetApplyTips(CString strTips)
{
    m_pAddMult_UI->m_labTips->setText(strTips);
    m_pAddMult_UI->m_labTips->setVisible(true);
    m_nTipsTime = startTimer(TIPS_DISPLAY_TIME);
}
void QDiffAddBatchDlg::timerEvent(QTimerEvent* ev)
{
    if(ev->timerId() == m_nTipsTime){
        m_pAddMult_UI->m_labTips->setVisible(false);
    }
}
void QDiffAddBatchDlg::on_m_check_Rate_clicked(bool checked)
{
    if(CheckFuncState())
    {
        return;
    }
}
void QDiffAddBatchDlg::on_m_check_Harm_clicked(bool checked)
{
    if(CheckFuncState())
    {
        return;
    }
}
void QDiffAddBatchDlg::on_m_check_Time_clicked(bool checked)
{
	m_pAddMult_UI->m_txtTime_lr->setEnabled(checked);
	m_pAddMult_UI->m_txtTime_ld->setEnabled(checked);
    if(CheckFuncState())
    {
        return;
    }
}
void QDiffAddBatchDlg::on_m_check_AN_clicked(bool checked)
{
    if(CheckSectionState())
    {
        return;
    }
}
void QDiffAddBatchDlg::on_m_check_BN_clicked(bool checked)
{
    if(CheckSectionState())
    {
        return;
    }
}
void QDiffAddBatchDlg::on_m_check_CN_clicked(bool checked)
{
    if(CheckSectionState())
    {
        return;
    }
}
void QDiffAddBatchDlg::on_m_check_AB_clicked(bool checked)
{
    if(CheckSectionState())
    {
        return;
    }
}
void QDiffAddBatchDlg::on_m_check_BC_clicked(bool checked)
{
    if(CheckSectionState())
    {
        return;
    }
}
void QDiffAddBatchDlg::on_m_check_CA_clicked(bool checked)
{
    if(CheckSectionState())
    {
        return;
    }
}
void QDiffAddBatchDlg::on_m_check_ABC_clicked(bool checked)
{
    if(CheckSectionState())
    {
        return;
    }
}

void QDiffAddBatchDlg::SetDatas(CDataGroup *pParas)
{
	if (pParas == NULL)
		return;

	m_pCurrDataGroup = pParas;
	POS pos = pParas->GetHeadPosition();
	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
		SetValueToPage(pData);
	}
	SetDiffCharGrid();
	CheckFuncState();
	CheckSectionState();
}
void QDiffAddBatchDlg::GetDatas(CDataGroup *pParas)
{
    if (pParas == NULL)
    {
        return;
    }
 
	//m_pCurrDataGroup = pParas;
	CheckAllPresence();

	POS pos = pParas->GetHeadPosition();
	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
	GetDateFromCurrDataGroup(pParas);
}

void QDiffAddBatchDlg::CheckAllPresence()
{
    //20240624 luozibing 检查ID是否存在
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_RATE);	//功能选择-差动曲线搜索
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_HARM);	//功能选择-谐波制动搜索
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_TIME);	//功能选择-动作时间
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_IR);	//功能选择-比率制动制动电流
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_ID);	//功能选择-比率制动差动电流
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTIME);	//最大故障时间

	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_AN);	//故障选择-A-E
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_BN);	//故障选择-B-E
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_CN);	//故障选择-C-E
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_AB);	//故障选择-A-B
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_BC);	//故障选择-B-C
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_CA);	//故障选择-C-A
	DiffCheckForPresence(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_CHECK_ABC);	//故障选择-ABC

}
void QDiffAddBatchDlg::DiffCheckForPresence(CString strID)
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
void QDiffAddBatchDlg::UpdateMinaxis(int nMinaxis)//0:有名值(A) 1:标幺值(In)
{
	if (nMinaxis)
	{
		m_pAddMult_UI->m_labTime_lr->setText(CString("Ir(Ie):"));
		m_pAddMult_UI->m_labTime_ld->setText(CString("Id(Ie):"));
	}
	else
	{
		m_pAddMult_UI->m_labTime_lr->setText(CString("Ir(A):"));
		m_pAddMult_UI->m_labTime_ld->setText(CString("Id(A):"));
	}
}
void QDiffAddBatchDlg::on_m_btnResEvaluat_clicked()
{
	//结果评估
	QDiffResultEstimateDlg oResultDlg(m_pCurrDataGroup, this);
	oResultDlg.setWindowTitle(g_sLangTxt_StateEstimate_ResultEstimate);
	oResultDlg.setWindowModality(Qt::WindowModal);
	oResultDlg.exec();
}

void QDiffAddBatchDlg::SetDiffCharGrid()
{
	if (m_oRateList.GetCount() != 0)
	{
		m_oRateList.DeleteAll();
	}
	if (m_oHarmList.GetCount() != 0)
	{
		m_oHarmList.DeleteAll();
	}
	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_StartCurrPointNum, m_nPointNum[0]);
	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef1PointNum, m_nPointNum[1]);
	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef2PointNum, m_nPointNum[2]);
	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef3PointNum, m_nPointNum[3]);
	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_QuickCurrPointNum, m_nPointNum[4]);

	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_StartCurrErrorBand, m_fErrorBand[0]);
	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef1ErrorBand, m_fErrorBand[1]);
	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef2ErrorBand, m_fErrorBand[2]);
	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef3ErrorBand, m_fErrorBand[3]);
	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_QuickCurrErrorBand, m_fErrorBand[4]);

	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_StartCurr_Check, m_nLineChecked[0]);
	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef1_Check, m_nLineChecked[1]);
	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef2_Check, m_nLineChecked[2]);
	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef3_Check, m_nLineChecked[3]);
	stt_GetDataValueByID(m_pCurrDataGroup, STT_MULTI_MACRO_DIFF_PARAS_ID_QuickCurr_Check, m_nLineChecked[4]);

	QStringList strRateNameList;
	CString strStartCurr, strRatiobraking, strParagraph, strTripping, strHarmBrake;
	xlang_GetLangStrByFile(strStartCurr, "CharLib_StartCurr");
	xlang_GetLangStrByFile(strRatiobraking, "CharLib_Ratiobraking");
	xlang_GetLangStrByFile(strParagraph, "CharLib_Paragraph");
	xlang_GetLangStrByFile(strTripping, "CharLib_Tripping");
	xlang_GetLangStrByFile(strHarmBrake, "State_Harmonicbraking");

	strRateNameList << /*启动*/g_sLangTxt_Diff_Start << /*比率制动1段*/g_sLangTxt_CharLib_Ratiobraking + "1" + g_sLangTxt_CharLib_Paragraph
		<< /*比率制动2段*/g_sLangTxt_CharLib_Ratiobraking + "2" + g_sLangTxt_CharLib_Paragraph
		<< /*比率制动3段*/g_sLangTxt_CharLib_Ratiobraking + "3" + g_sLangTxt_CharLib_Paragraph
		<< /*速断*/g_sLangTxt_Diff_IQuick;

	QDiffRateData* pData = new QDiffRateData;
	pData->m_strName = /*谐波制动*/g_sLangTxt_State_Harmonicbraking;
	pData->m_nPointNum = &m_nHarmCustomPoint;
	pData->m_fErrorBand = &m_fErrorBand[1];
	m_oHarmList.AddNewChild(pData);
	for (int i = 0; i < 5; i++)
	{
		QDiffRateData* pData = new QDiffRateData;
		pData->m_strName = strRateNameList[i];
		pData->m_nPointNum = &m_nPointNum[i];
		pData->m_fErrorBand = &m_fErrorBand[i];
		if (m_nLineChecked[i] == 1)
		{
			m_oRateList.AddNewChild(pData);
		}
	}
	
	m_pRateGrid->ShowDatas(&m_oRateList);
	
}
void QDiffAddBatchDlg::on_tabWidget_currentChanged(int index)
{
	m_pRateGrid->UpdateDatas();
	m_pHarmGrid->ShowDatas(&m_oHarmList);
}
void QDiffAddBatchDlg::GetDateFromCurrDataGroup(CDataGroup *pParas)
{
	pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_StartCurrPointNum, m_nPointNum[0], TRUE);
	pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef1PointNum, m_nPointNum[1], TRUE);
	pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef2PointNum, m_nPointNum[2], TRUE);
	pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef3PointNum, m_nPointNum[3], TRUE);
	pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_QuickCurrPointNum, m_nPointNum[4], TRUE);

	pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_StartCurrErrorBand, m_fErrorBand[0], TRUE);
	pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef1ErrorBand, m_fErrorBand[1], TRUE);
	pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef2ErrorBand, m_fErrorBand[2], TRUE);
	pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_RateCoef3ErrorBand, m_fErrorBand[3], TRUE);
	pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_QuickCurrErrorBand, m_fErrorBand[4], TRUE);
	
	CDvmData *pData = NULL;
	
	pData = (CDvmData *)m_pCurrDataGroup->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_RSLTEVAL);
	if (pData != NULL)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_RSLTEVAL, pData->m_strValue, TRUE);
	}

	pData = (CDvmData *)m_pCurrDataGroup->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_RSLTEVAL);
	if (pData != NULL)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_RSLTEVAL, pData->m_strValue, TRUE);
	}

	pData = (CDvmData *)m_pCurrDataGroup->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_RSLTEVAL);
	if (pData != NULL)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_RSLTEVAL, pData->m_strValue, TRUE);
	}

	pData = (CDvmData *)m_pCurrDataGroup->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_ABSERR);
	if (pData != NULL)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_ABSERR, pData->m_strValue, TRUE);
	}

	pData = (CDvmData *)m_pCurrDataGroup->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_RELERR);
	if (pData != NULL)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_RELERR, pData->m_strValue, TRUE);
	}

	pData = (CDvmData *)m_pCurrDataGroup->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_RELERR);
	if (pData != NULL)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_RELERR, pData->m_strValue, TRUE);
	}

	pData = (CDvmData *)m_pCurrDataGroup->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_ABSERRPOS);
	if (pData != NULL)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_ABSERRPOS, pData->m_strValue, TRUE);
	}

	pData = (CDvmData *)m_pCurrDataGroup->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_ABSERRNEG);
	if (pData != NULL)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_ABSERRNEG, pData->m_strValue, TRUE);
	}

	pData = (CDvmData *)m_pCurrDataGroup->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_RELERR);
	if (pData != NULL)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_RELERR, pData->m_strValue, TRUE);
	}

	pData = (CDvmData *)m_pCurrDataGroup->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_ABSERRPOS);
	if (pData != NULL)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_ABSERRPOS, pData->m_strValue, TRUE);
	}

	pData = (CDvmData *)m_pCurrDataGroup->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_ABSERRNEG);
	if (pData != NULL)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_ABSERRNEG, pData->m_strValue, TRUE);
	}

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//曲线参数接口表
QDiffCharGrid::QDiffCharGrid(QWidget* pParent) : QExBaseListGridBase(pParent)
{
	connect(this, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(slot_doubleClicked(int, int)), Qt::UniqueConnection);
}

QDiffCharGrid::~QDiffCharGrid()
{

}

void QDiffCharGrid::InitGridTitle()
{
	CString astrGridTitle[GROUPGRID_COLS] = { /*扫描线段*/g_sLangTxt_State_Scanlinesegments, /*自定义点数*/g_sLangTxt_Native_Custompoints, /*搜索带*/g_sLangTxt_Diff_SearchBand };
	int iGridWidth[GROUPGRID_COLS] = { 100, 100, 100 };
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, GROUPGRID_COLS);
}
void QDiffCharGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	QDiffRateData* pRateData = (QDiffRateData*)pData;
	Show_StaticString(pData, nRow, 0, pRateData->m_strName);
	Show_Long(pData, nRow, 1, pRateData->m_nPointNum, 1);
	Show_Float(pData, nRow, 2, 3, pRateData->m_fErrorBand, 1);
	nRow++;
}

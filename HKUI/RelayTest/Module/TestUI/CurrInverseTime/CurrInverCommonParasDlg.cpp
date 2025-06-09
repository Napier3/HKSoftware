#include "CurrInverCommonParasDlg.h"
#include "ui_CurrInverCommonParasDlg.h"
#include "../Distance/DistanceCommonParasDlg.h"
#include "../../XLangResource_Native.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

extern CFont *g_pSttGlobalFont;
extern void  Stt_Global_SettingParent(QWidget *parent);		//20240802 huangliang

QCurrInverseCommonParasDlg::QCurrInverseCommonParasDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCurrInverseCommonParasDlg)
{
    Stt_Global_SettingParent(this);	//20240802 huangliang
    ui->setupUi(this);
	m_pParas = NULL;
    m_nModify= 0;
	InitUI();
	InitLanuage();
    initConnections();
}

QCurrInverseCommonParasDlg::~QCurrInverseCommonParasDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
    delete ui;
}

void QCurrInverseCommonParasDlg::InitUI()
{
	ui->m_cmbValue->addItems(QStringList()<<"In"<<"In*Ip");
	ui->m_cmbCTPos->addItems(QStringList()<<g_sLangTxt_CBOperate_TPos1/*"指向线路"*/<<g_sLangTxt_CBOperate_CTPos1/*"指向母线"*/);

	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);
}

void QCurrInverseCommonParasDlg::initConnections()
{
	connect(ui->m_cmbValue, SIGNAL(currentIndexChanged ( int ) ), this, SLOT(slot_cmb_Value_currentIndexChanged(int)));
	connect(ui->m_cmbCTPos, SIGNAL(currentIndexChanged ( int ) ), this, SLOT(slot_cmb_CTPos_Changed(int)));

	connect(ui->m_txtPreFaultTime,SIGNAL(editingFinished()), this, SLOT(slot_lne_PreFaultTime_editingFinished()));
	connect(ui->m_txtFaultVolt,SIGNAL(editingFinished()), this, SLOT(slot_lne_FaultVolt_editingFinished()));
	connect(ui->m_txtFaultCurr,SIGNAL(editingFinished()), this, SLOT(slot_lne_FaultCurr_editingFinished()));
	connect(ui->m_txtAng,SIGNAL(editingFinished()), this, SLOT(slot_lne_Ang_editingFinished()));
	connect(ui->m_txtHz,SIGNAL(editingFinished()), this, SLOT(slot_lne_Hz_editingFinished()));
	connect(ui->m_txtIn,SIGNAL(editingFinished()), this, SLOT(slot_lne_In_editingFinished()));
	connect(ui->m_txtIp,SIGNAL(editingFinished()), this, SLOT(slot_lne_Ip_editingFinished()));
	connect(ui->m_txtFaultTime,SIGNAL(editingFinished()), this, SLOT(slot_lne_FaultTime_editingFinished()));
}

void QCurrInverseCommonParasDlg::InitLanuage()
{
	xlang_SetLangStrToWidget(ui->groupBox, g_sLangID_Curr_FaultBeforeOutput, XLang_Ctrls_QGroupBox);//故障前输出

	CString strtemp;
	ui->m_labPreFaultTime->setText(GetLangStrByFileAddSuffix(g_sLangID_Gradient_FailBeforeTime));//故障前时间(s):
	xlang_SetLangStrToWidget(ui->m_labPreFaultTime, g_sLangID_Gradient_FailBeforeTime, XLang_Ctrls_QLabel);//故障前时间(s):
	xlang_SetLangStrToWidget(ui->m_labFaultVolt, g_sLangID_Gradient_FailVol, XLang_Ctrls_QLabel);//故障前电压(V):
	xlang_SetLangStrToWidget(ui->m_labFaultCurr, g_sLangID_Gradient_FailCur, XLang_Ctrls_QLabel);//故障前电流(A):
	xlang_GetLangStrByFile(strtemp, g_sLangID_Gradient_Phase);//相位差(°):
	strtemp += QString::fromLocal8Bit("(°)");
	ui->m_labAng->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Frequency);//频率(Hz):
	strtemp += ":";
	ui->m_labHz->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_ReferenceValue);//基准值:
	strtemp += ":";
	ui->label->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_EDCurrent);//额定电流(In):
	strtemp += "(In):";
	ui->label_2->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_CTPolarityPositive);//CT正极性
	strtemp += ":";
	ui->label_3->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Gradient_StartCur);//启动电流(Ip) :
	strtemp += "(Ip):";
	ui->label_4->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_FaultTimeMargin);//故障时间裕度(s):
	strtemp += QString::fromLocal8Bit("(s):");
	ui->label_5->setText(strtemp);
	xlang_SetLangStrToWidget(ui->m_btnOK, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->m_btnCancel, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消
	
	CString strTile;
	xlang_GetLangStrByFile(strTile, g_sLangID_Gradient_CommonParas);//通用参数设置
	setWindowTitle(strTile);
}

CString QCurrInverseCommonParasDlg::GetLangStrByFileAddSuffix(CString strID)
{
	CString strtemp;
	xlang_GetLangStrByFile(strtemp, strID);//故障前时间(s):
	if (strtemp.Find(":") == -1)
	{
		strtemp += ":";
	}
	return strtemp;
}

void QCurrInverseCommonParasDlg::SetDatas(CExBaseList *pParas)
{
	//读取数据转换到界面中
	if(pParas == NULL)
		return;
	m_pParas = pParas;
	CheckAllPresence(m_pParas);

	POS pos = m_pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)m_pParas->GetNext(pos);
		SetValueToPage(pData);
	}
}

void QCurrInverseCommonParasDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreFaultTime)
	{
		ui->m_txtPreFaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		//ui->m_txtPreFaultTime->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_UPre)
	{
		ui->m_txtFaultVolt->setText(CheckDataMinMax(pData->m_strValue,120,0,3));
		//ui->m_txtFaultVolt->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 120, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_IPre)
	{
		ui->m_txtFaultCurr->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
		//ui->m_txtFaultCurr->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 20, 0, 3));
	}
	if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreAngle)
	{
		ui->m_txtAng->setText(CheckDataMinMax(pData->m_strValue,360,-360,2));
		//ui->m_txtAng->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 360, -360, 1));
	}
	if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreFre)
	{
		ui->m_txtHz->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		//ui->m_txtHz->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RefValueType)
	{
		ui->m_cmbValue->setCurrentIndex(pData->m_strValue.toInt());
	}
	if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_In)
	{
		//ui->m_txtIn->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
		ui->m_txtIn->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 20, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CTPos)
	{
		ui->m_cmbCTPos->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Ipu)
	{
		//ui->m_txtIp->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
		ui->m_txtIp->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 20, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultTime)
	{
		ui->m_txtFaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		//ui->m_txtFaultTime->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
}

void QCurrInverseCommonParasDlg::GetDatas(CExBaseList *pParas)
{
	//将界面设置参数填到链表
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}

void QCurrInverseCommonParasDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreFaultTime)
	{
		pData->m_strValue = ui->m_txtPreFaultTime->text();
		//pData->m_strValue = ui->m_txtPreFaultTime->GetText();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_UPre)
	{
		pData->m_strValue = ui->m_txtFaultVolt->text();
		//pData->m_strValue = ui->m_txtFaultVolt->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_IPre)
	{
		pData->m_strValue = ui->m_txtFaultCurr->text();
		//pData->m_strValue = ui->m_txtFaultCurr->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreAngle)
	{
		pData->m_strValue = ui->m_txtAng->text();
		//pData->m_strValue = ui->m_txtAng->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreFre)
	{
		pData->m_strValue = ui->m_txtHz->text();
		//pData->m_strValue = ui->m_txtHz->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RefValueType)
	{
		pData->m_strValue.Format("%d",ui->m_cmbValue->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_In)
	{
		//pData->m_strValue = ui->m_txtIn->text();
		pData->m_strValue = ui->m_txtIn->GetText();
	}
	if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CTPos)
	{
		pData->m_strValue.Format("%d",ui->m_cmbCTPos->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Ipu)
	{
		//pData->m_strValue = ui->m_txtIp->text();
		pData->m_strValue = ui->m_txtIp->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultTime)
	{
		pData->m_strValue = ui->m_txtFaultTime->text();
		//pData->m_strValue = ui->m_txtFaultTime->GetText();
	}
}

void QCurrInverseCommonParasDlg::slot_lne_PreFaultTime_editingFinished()
{
	//if (ui->m_txtPreFaultTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_txtPreFaultTime)->IsSetting())
	//	{
	//		return;
	//	}
	//}

//	ui->m_txtPreFaultTime->setText(CheckDataMinMax(ui->m_txtPreFaultTime->text(),999.999,0,3));
    float fv = ui->m_txtPreFaultTime->text().toFloat();
    fv = setLimit(0,999.999,fv);
    ui->m_txtPreFaultTime->setText(QString::number(fv,'f',3));
}

void QCurrInverseCommonParasDlg::slot_lne_FaultVolt_editingFinished()
{
	//if (ui->m_txtFaultVolt->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_txtFaultVolt)->IsSetting())
	//	{
	//		return;
	//	}
	//}

    //ui->m_txtFaultVolt->setText(CheckDataMinMax(ui->m_txtFaultVolt->text(),120,0,3));
    float fv = ui->m_txtFaultVolt->text().toFloat();
    fv = setLimit(0,120,fv);
    ui->m_txtFaultVolt->setText(QString::number(fv,'f',3));
}

void QCurrInverseCommonParasDlg::slot_lne_FaultCurr_editingFinished()
{
	//if (ui->m_txtFaultCurr->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_txtFaultCurr)->IsSetting())
	//	{
	//		return;
	//	}
	//}

    //ui->m_txtFaultCurr->setText(CheckDataMinMax(ui->m_txtFaultCurr->text(),20,0,3));
    float fv = ui->m_txtFaultCurr->text().toFloat();
    fv = setLimit(0,20,fv);
    ui->m_txtFaultCurr->setText(QString::number(fv,'f',3));
}

void QCurrInverseCommonParasDlg::slot_lne_Ang_editingFinished()
{
	//if (ui->m_txtAng->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_txtAng)->IsSetting())
	//	{
	//		return;
	//	}
	//}

    //ui->m_txtAng->setText(CheckDataMinMax(ui->m_txtAng->text(),360,-360,1));
    float fv = ui->m_txtAng->text().toFloat();
    fv = setLimit(-360,360,fv);
    ui->m_txtAng->setText(QString::number(fv,'f',2));
}

void QCurrInverseCommonParasDlg::slot_lne_Hz_editingFinished()
{
	//if (ui->m_txtHz->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_txtHz)->IsSetting())
	//	{
	//		return;
	//	}
	//}

    //ui->m_txtHz->setText(CheckDataMinMax(ui->m_txtHz->text(),999.999,0,3));
    float fv = ui->m_txtHz->text().toFloat();
    fv = setLimit(0,999.999,fv);
    ui->m_txtHz->setText(QString::number(fv,'f',3));
}

void QCurrInverseCommonParasDlg::slot_lne_In_editingFinished()
{
	if (ui->m_txtIn->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtIn)->IsSetting())
		{
			return;
		}
	}

    //ui->m_txtIn->setText(CheckDataMinMax(ui->m_txtIn->text(),20,0,3));
    float fv = ui->m_txtIn->text().toFloat();
    fv = setLimit(0,20,fv);
    ui->m_txtIn->setText(QString::number(fv,'f',3));
}

void QCurrInverseCommonParasDlg::slot_lne_Ip_editingFinished()
{
	if (ui->m_txtIp->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_txtIp)->IsSetting())
		{
			return;
		}
	}

    //ui->m_txtIp->setText(CheckDataMinMax(ui->m_txtIp->text(),20,0,3));
    float fv = ui->m_txtIp->text().toFloat();
    fv = setLimit(0,20,fv);
    ui->m_txtIp->setText(QString::number(fv,'f',3));
}

void QCurrInverseCommonParasDlg::slot_lne_FaultTime_editingFinished()
{	
	//if (ui->m_txtFaultTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)ui->m_txtFaultTime)->IsSetting())
	//	{
	//		return;
	//	}
	//}

    //ui->m_txtFaultTime->setText(CheckDataMinMax(ui->m_txtFaultTime->text(),999.999,0,3));
    float fv = ui->m_txtFaultTime->text().toFloat();
    fv = setLimit(0,999.999,fv);
    ui->m_txtFaultTime->setText(QString::number(fv,'f',3));
}

void QCurrInverseCommonParasDlg::slot_cmb_Value_currentIndexChanged(int index)
{

}

void QCurrInverseCommonParasDlg::slot_cmb_CTPos_Changed(int index)
{

}

void QCurrInverseCommonParasDlg::on_m_btnOK_clicked()
{
	this->done(Accepted);
}

void QCurrInverseCommonParasDlg::on_m_btnCancel_clicked()
{
	this->close();
}

void QCurrInverseCommonParasDlg::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreFaultTime);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_UPre);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_IPre);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreAngle);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreFre);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RefValueType);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_In);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CTPos);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Ipu);
	CheckForPresence(pParas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultTime);
}

//void QCurrInverseCommonParasDlg::UpdateCurrentCommonParas(CExBaseList *pItem)
//{
//	CSttMacroTest *pSttMacroTest = NULL;

//	pSttMacroTest = (CSttMacroTest *)pItem;
//	pSttMacroTest->m_nModified = 1;
//	CheckAllPresence(pItem);
//	GetDatas(pItem);

//	return;
//}

void QCurrInverseCommonParasDlg::UpdataAllCommonParas(CExBaseList *pAllItems)
{//通用参数修改后，修改表格中所有项数据通用参数
	CSttMacroTest *pSttMacroTest = NULL;
	CExBaseList *pItem = NULL;
	CSttMacroTestParaDatas *pParaDatas = NULL;

	POS pos = pAllItems->GetHeadPosition();
	while (pos!= NULL)
	{
		pItem = (CExBaseList*)pAllItems->GetNext(pos);
		if(pItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
		{
			pSttMacroTest = (CSttMacroTest *)pItem;
			pSttMacroTest->m_nModified = 1;
			pParaDatas = pSttMacroTest->GetSttMacroTestParaDatas(FALSE,"");

			if(pParaDatas != NULL)
			{
				CheckAllPresence(pParaDatas);
				GetDatas(pParaDatas);
			}
		}
	}
}

BOOL QCurrInverseCommonParasDlg::CheckItemsModify(CExBaseList *pItem)
{
    if (pItem == NULL)
    {
        return FALSE;
    }
    CSttMacroTestParaDatas paraDatas;
    CheckAllPresence(&paraDatas);
    GetDatas(&paraDatas);
    POS pos = pItem->GetHeadPosition();
    while(pos != NULL)
    {
        CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pItem->GetNext(pos);
        CSttMacroTestParaData *pData_New = (CSttMacroTestParaData *)paraDatas.FindByID(pData->m_strID);
        if (pData_New == NULL)
        {
            continue;
        }
        if(pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RefValueType||pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CTPos)
        {
            if (pData->m_strValue != pData_New->m_strValue)
            {
                m_nModify = 1;
                return TRUE;
            }

        }
        else
        {//浮点数判断差值的绝对值
            if (fabs(pData->m_strValue.toFloat() - pData_New->m_strValue.toFloat())>0.0001)
            {
                m_nModify = 1;
                return TRUE;
            }
        }

    }
    return FALSE;
}

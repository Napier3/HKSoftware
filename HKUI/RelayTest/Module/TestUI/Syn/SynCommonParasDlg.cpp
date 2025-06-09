#include "SynCommonParasDlg.h"
#include "ui_SynCommonParasDlg.h"
#include "../../XLangResource_Native.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

extern CFont *g_pSttGlobalFont;
extern void  Stt_Global_SettingParent(QWidget *parent);		//20240802 huangliang

QSynCommonParasDlg::QSynCommonParasDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSynCommonParasDlg)
{
    Stt_Global_SettingParent(this);	//20240802 huangliang
    ui->setupUi(this);

	m_pParas = NULL;
    m_nModify = 0;
	InitUI();
	InitLanuage();
}

QSynCommonParasDlg::~QSynCommonParasDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
    delete ui;
}

void QSynCommonParasDlg::InitUI()
{	
    ui->m_cmbUgConnectDef->addItems(QStringList()<<g_sLangTxt_Syn_UDefineOne/*"系统->Ua1,待并->Ub1"*/<<g_sLangTxt_Syn_UDefineTwo/*"系统->Ua1,待并->Ubc1"*/<<g_sLangTxt_Syn_UDefineThree/*"系统->Ua2/Uz,待并->Uabc1"*/<<g_sLangTxt_Syn_UDefineFour/*"系统->Uabc1,待并->Uabc2"*/);
	ui->m_cmbVref->addItems(QStringList()<<"Ua1"<<"Ub1"<<"Uc1"<<"Uab1"<<"Ubc1"<<"Uca1");
//	ui->m_cmbTansConnect->addItems(QStringList()<<"Y"<<"Δ");
//	ui->m_cmbTansConnect_2->addItems(QStringList()<<"Y"<<"Δ");
	ui->m_cmbPointNum->addItems(QStringList() << "12" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10" << "11");

	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);
}

void QSynCommonParasDlg::InitLanuage()
{
	CString strtemp;
	xlang_GetLangStrByFile(strtemp, g_sLangID_System_Rated_Voltage); //系统侧额定电压(V) :
	strtemp += "(V) :";
	ui->m_labUs->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_System_Rated_Frequency); //系统侧额定频率(Hz):
	strtemp += "(Hz):";
	ui->m_labFs->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Grid_Rated_Voltage); //待并测额定电压(V):
	strtemp += "(V):";
	ui->m_labUg->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_volDefinition1); //电压定义:
	strtemp += ":";
	ui->m_labUgConnectDef->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_refphase); //参考项:
	strtemp += ":";
	ui->m_labVref->setText(strtemp);
	xlang_SetLangStrToWidget(ui->m_labPointNum, g_sLangID_Sys_PointNum, XLang_Ctrls_QLabel);//钟点数:
	xlang_SetLangStrToWidget(ui->m_labAng, g_sLangID_Sys_PhaseDiff, XLang_Ctrls_QLabel);//两侧相位差(°):
	xlang_SetLangStrToWidget(ui->m_labTmax, g_sLangID_Native_maxSyncTime, XLang_Ctrls_QLabel);//最大同步时间(s):
	

	xlang_SetLangStrToWidget(ui->m_btnOK, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->m_btnCancel, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消

	CString strTile;
	xlang_GetLangStrByFile(strTile, g_sLangID_Gradient_CommonParas);//通用参数设置
	setWindowTitle(strTile);
}

void QSynCommonParasDlg::SetDatas(CExBaseList *pParas)
{
	//20240617 luozibing 读取数据转换到界面中
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

void QSynCommonParasDlg::SetValueToPage(CSttMacroTestParaData *pData)
{

	if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Us)
	{
		//ui->m_lineUs->setText(CheckDataMinMax(pData->m_strValue,120,0,3));
		ui->m_lineUs->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Fs)
	{
		//ui->m_lineFs->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		ui->m_lineFs->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Ug)
	{
		//ui->m_lineUg->setText(CheckDataMinMax(pData->m_strValue,120,0,3));
		ui->m_lineUg->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_UgConnectDef)
	{
		ui->m_cmbUgConnectDef->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Vref)
	{
		ui->m_cmbVref->setCurrentIndex(pData->m_strValue.toInt());
	}
//	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_TansConnect)
//	{
//		ui->m_cmbTansConnect->setCurrentIndex(pData->m_strValue.toInt());
//	}
//	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_TansConnect_2)
//	{
//		ui->m_cmbTansConnect_2->setCurrentIndex(pData->m_strValue.toInt());
//	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_PointNum)
	{
		ui->m_cmbPointNum->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Angle)
	{
		ui->m_lineAng->setText(CheckDataMinMax(pData->m_strValue,360,-360,2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Tmax)
	{
		ui->m_lineTmax->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}

}

void QSynCommonParasDlg::GetDatas(CExBaseList *pParas)
{
	//20240617 luozibing 将界面设置参数填到链表
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}

void QSynCommonParasDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Us)
	{
		//pData->m_strValue = ui->m_lineUs->text();
		pData->m_strValue = ui->m_lineUs->GetText();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Fs)
	{
		//pData->m_strValue = ui->m_lineFs->text();
		pData->m_strValue = ui->m_lineFs->GetText();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Ug)
	{
		//pData->m_strValue = ui->m_lineUg->text();
		pData->m_strValue = ui->m_lineUg->GetText();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_UgConnectDef)
	{
		pData->m_strValue.Format("%d",ui->m_cmbUgConnectDef->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Vref)
	{
		pData->m_strValue.Format("%d",ui->m_cmbVref->currentIndex());
	}
//	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_TansConnect)
//	{
//		pData->m_strValue.Format("%d",ui->m_cmbTansConnect->currentIndex());
//	}
//	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_TansConnect_2)
//	{
//		pData->m_strValue.Format("%d",ui->m_cmbTansConnect_2->currentIndex());
//	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_PointNum)
	{
		pData->m_strValue.Format("%d",ui->m_cmbPointNum->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Angle)
	{
		pData->m_strValue = ui->m_lineAng->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Tmax)
	{
		pData->m_strValue = ui->m_lineTmax->text();
	}	
}

void QSynCommonParasDlg::on_m_lineUs_editingFinished()
{
	if (ui->m_lineUs->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineUs)->IsSetting())
		{
			return;
		}
	}

//	ui->m_lineUs->setText(CheckDataMinMax(ui->m_lineUs->text(),120,0,3));
    float fv = ui->m_lineUs->text().toFloat();
    fv = setLimit(0,120,fv);
    ui->m_lineUs->setText(QString::number(fv,'f',3));
}

void QSynCommonParasDlg::on_m_lineFs_editingFinished()
{
	if (ui->m_lineFs->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineFs)->IsSetting())
		{
			return;
		}
	}

//	ui->m_lineFs->setText(CheckDataMinMax(ui->m_lineFs->text(),999.999,0,3));
    float fv = ui->m_lineFs->text().toFloat();
    fv = setLimit(0,999.999,fv);
    ui->m_lineFs->setText(QString::number(fv,'f',3));
}

void QSynCommonParasDlg::on_m_lineUg_editingFinished()
{
	if (ui->m_lineUg->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_lineUg)->IsSetting())
		{
			return;
		}
	}

//	ui->m_lineUg->setText(CheckDataMinMax(ui->m_lineUg->text(),120,0,3));
    float fv = ui->m_lineUg->text().toFloat();
    fv = setLimit(0,120,fv);
    ui->m_lineUg->setText(QString::number(fv,'f',3));
}

void QSynCommonParasDlg::on_m_cmbUgConnectDef_currentIndexChanged(int index)
{

}

void QSynCommonParasDlg::on_m_cmbVref_currentIndexChanged(int index)
{

}

void QSynCommonParasDlg::on_m_cmbTansConnect_currentIndexChanged(int index)
{

}

void QSynCommonParasDlg::on_m_cmbTansConnect_2_currentIndexChanged(int index)
{

}

void QSynCommonParasDlg::on_m_cmbPointNum_currentIndexChanged(int index)
{

}

void QSynCommonParasDlg::on_m_lineAng_editingFinished()
{
//	ui->m_lineAng->setText(CheckDataMinMax(ui->m_lineAng->text(),360,-360,1));
    float fv = ui->m_lineAng->text().toFloat();
    fv = setLimit(-360,360,fv);
    ui->m_lineAng->setText(QString::number(fv,'f',2));
}

void QSynCommonParasDlg::on_m_lineTmax_editingFinished()
{
//	ui->m_lineTmax->setText(CheckDataMinMax(ui->m_lineTmax->text(),999.999,0,3));
    float fv = ui->m_lineTmax->text().toFloat();
    fv = setLimit(0,999.999,fv);
    ui->m_lineTmax->setText(QString::number(fv,'f',3));
}

void QSynCommonParasDlg::on_m_btnOK_clicked()
{
    this->done(Accepted);
}

void QSynCommonParasDlg::on_m_btnCancel_clicked()
{
    this->close();
}

void QSynCommonParasDlg::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_Us);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_Fs);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_Ug);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_UgConnectDef);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_Vref);
//	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_TansConnect);
//	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_TansConnect_2);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_PointNum);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_Angle);
	CheckForPresence(pParas,STT_MULTI_MACRO_SYN_PARAS_ID_Tmax);
}

void QSynCommonParasDlg::UpdataAllCommonParas(CExBaseList *pAllItems)
{//20240625 luozibing 通用参数修改后，修改表格中所有项数据通用参数
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
			pParaDatas = pSttMacroTest->GetSttMacroTestParaDatas(FALSE, "");

			if (pParaDatas != NULL)
			{
				CheckAllPresence(pParaDatas);
				GetDatas(pParaDatas);
			}
		}
	}
}

BOOL QSynCommonParasDlg::CheckItemsModify(CExBaseList *pItem)
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
        if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_UgConnectDef ||
            pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Vref ||
            pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_PointNum)
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

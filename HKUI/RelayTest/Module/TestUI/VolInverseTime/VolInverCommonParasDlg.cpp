#include "VolInverCommonParasDlg.h"
#include "ui_VolInverCommonParasDlg.h"
#include "../Distance/DistanceCommonParasDlg.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

extern CFont *g_pSttGlobalFont;

QVolInverseCommonParasDlg::QVolInverseCommonParasDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QVolInverseCommonParasDlg)
{
    ui->setupUi(this);
	m_pParas = NULL;
	m_nModify= 0;
	InitUI();
	InitLanuage();
	initConnections();
}

QVolInverseCommonParasDlg::~QVolInverseCommonParasDlg()
{
    delete ui;
}

void QVolInverseCommonParasDlg::InitUI()
{
	ui->m_cmbCTPos->addItems(QStringList()<<g_sLangTxt_CBOperate_CTPos1/*("指向母线")*/<<g_sLangTxt_CBOperate_TPos1/*("指向线路")*/);
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);
}

void QVolInverseCommonParasDlg::initConnections()
{
	//connect(ui->m_cmbValue, SIGNAL(currentIndexChanged ( int ) ), this, SLOT(slot_cmb_Value_currentIndexChanged(int)));
	connect(ui->m_cmbCTPos, SIGNAL(currentIndexChanged ( int ) ), this, SLOT(slot_cmb_CTPos_Changed(int)));

	connect(ui->m_txtPreFaultTime,SIGNAL(editingFinished()), this, SLOT(slot_lne_PreFaultTime_editingFinished()));
	connect(ui->m_txtFaultVolt,SIGNAL(editingFinished()), this, SLOT(slot_lne_FaultVolt_editingFinished()));
	connect(ui->m_txtFaultCurr,SIGNAL(editingFinished()), this, SLOT(slot_lne_FaultCurr_editingFinished()));
	connect(ui->m_txtAng,SIGNAL(editingFinished()), this, SLOT(slot_lne_Ang_editingFinished()));
	connect(ui->m_txtHz,SIGNAL(editingFinished()), this, SLOT(slot_lne_Hz_editingFinished()));
	connect(ui->m_txtFaultTime,SIGNAL(editingFinished()), this, SLOT(slot_lne_FaultTime_editingFinished()));
}

void QVolInverseCommonParasDlg::InitLanuage()
{
	CString strtemp;
	ui->m_labPreFaultTime->setText(GetLangStrByFileAddSuffix(g_sLangID_Native_FaultPreTimeS));//故障前时间(s):
	xlang_SetLangStrToWidget(ui->m_labPreFaultTime, g_sLangID_Gradient_FailBeforeTime, XLang_Ctrls_QLabel);//故障前时间(s):
	xlang_GetLangStrByFile(strtemp, g_sLangID_Native_FaultTimeMargin);//故障时间裕度(s):
	strtemp +="(s):";
	ui->label_5->setText(strtemp);
	xlang_SetLangStrToWidget(ui->m_labFaultVolt, g_sLangID_Gradient_FailVol, XLang_Ctrls_QLabel);//故障前电压(V):
	xlang_SetLangStrToWidget(ui->m_labFaultCurr, g_sLangID_Gradient_FailCur, XLang_Ctrls_QLabel);//故障前电流(A):
	xlang_GetLangStrByFile(strtemp, g_sLangID_Gradient_Phase);//相位差(°):
	strtemp += QString::fromLocal8Bit("(°):");
	ui->m_labAng->setText(strtemp); 
	xlang_GetLangStrByFile(strtemp, g_sLangID_Frequency);//频率(Hz):
	strtemp += ":";
	ui->m_labHz->setText(strtemp);
	xlang_SetLangStrToWidget(ui->label_3, g_sLangID_Native_CTPolarityPositive, XLang_Ctrls_QLabel);//CT正极性
	xlang_SetLangStrToWidget(ui->m_btnOK, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->m_btnCancel, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消

	CString strTile;
	xlang_GetLangStrByFile(strTile, g_sLangID_Gradient_CommonParas);//通用参数设置
	setWindowTitle(strTile);
}

CString QVolInverseCommonParasDlg::GetLangStrByFileAddSuffix(CString strID)
{
	CString strtemp;
	xlang_GetLangStrByFile(strtemp, strID);//故障前时间(s):
	if (strtemp.Find(":") == -1)
	{
		strtemp += ":";
	}
	return strtemp;
}

void QVolInverseCommonParasDlg::SetDatas(CExBaseList *pParas)
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

void QVolInverseCommonParasDlg::SetDatas(CDataGroup *pParas)
{
	if (pParas == NULL)
		return;
	m_pParas = pParas;

	CheckAllPresence(m_pParas);

	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		SetValueToPage(pData);
	}
}

void QVolInverseCommonParasDlg::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_PreFaultTime)
	{
		ui->m_txtPreFaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_UPre)
	{
		ui->m_txtFaultVolt->setText(CheckDataMinMax(pData->m_strValue,120,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_IPre)
	{
		ui->m_txtFaultCurr->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
	}
	if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_PreAngle)
	{
		ui->m_txtAng->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
	}
	if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_NORMHZ)
	{
		ui->m_txtHz->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CTPos)
	{
		ui->m_cmbCTPos->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultTime)
	{
		ui->m_txtFaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
}

void QVolInverseCommonParasDlg::GetDatas(CExBaseList *pParas)
{
	//将界面设置参数填到链表
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}

void QVolInverseCommonParasDlg::GetPageToValue(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_PreFaultTime)
	{
		pData->m_strValue = ui->m_txtPreFaultTime->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_UPre)
	{
		pData->m_strValue = ui->m_txtFaultVolt->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_IPre)
	{
		pData->m_strValue = ui->m_txtFaultCurr->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_PreAngle)
	{
		pData->m_strValue = ui->m_txtAng->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_NORMHZ)
	{
		pData->m_strValue = ui->m_txtHz->text();
	}
	if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CTPos)
	{
		pData->m_strValue.Format("%d",ui->m_cmbCTPos->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultTime)
	{
		pData->m_strValue = ui->m_txtFaultTime->text();
	}
}

void QVolInverseCommonParasDlg::slot_lne_PreFaultTime_editingFinished()
{
	//ui->m_txtPreFaultTime->setText(CheckDataMinMax(ui->m_txtPreFaultTime->text(),999.999,0,3));
	float fv = ui->m_txtPreFaultTime->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_txtPreFaultTime->setText(QString::number(fv,'f',3));
}

void QVolInverseCommonParasDlg::slot_lne_FaultVolt_editingFinished()
{
	//ui->m_txtFaultVolt->setText(CheckDataMinMax(ui->m_txtFaultVolt->text(),120,0,3));
	float fv = ui->m_txtFaultVolt->text().toFloat();
	fv = setLimit(0,120,fv);
	ui->m_txtFaultVolt->setText(QString::number(fv,'f',3));
}

void QVolInverseCommonParasDlg::slot_lne_FaultCurr_editingFinished()
{
	//ui->m_txtFaultCurr->setText(CheckDataMinMax(ui->m_txtFaultCurr->text(),20,0,3));
	float fv = ui->m_txtFaultCurr->text().toFloat();
	fv = setLimit(0,20,fv);
	ui->m_txtFaultCurr->setText(QString::number(fv,'f',3));
}

void QVolInverseCommonParasDlg::slot_lne_Ang_editingFinished()
{
	//ui->m_txtAng->setText(CheckDataMinMax(ui->m_txtAng->text(),360,-360,1));
	float fv = ui->m_txtAng->text().toFloat();
	fv = setAngleLimitEx(fv);
	ui->m_txtAng->setText(QString::number(fv,'f',1));
}

void QVolInverseCommonParasDlg::slot_lne_Hz_editingFinished()
{
	//ui->m_txtHz->setText(CheckDataMinMax(ui->m_txtHz->text(),999.999,0,3));
	float fv = ui->m_txtHz->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_txtHz->setText(QString::number(fv,'f',3));
}

void QVolInverseCommonParasDlg::slot_lne_FaultTime_editingFinished()
{	
	//ui->m_txtFaultTime->setText(CheckDataMinMax(ui->m_txtFaultTime->text(),999.999,0,3));
	float fv = ui->m_txtFaultTime->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_txtFaultTime->setText(QString::number(fv,'f',3));
}

void QVolInverseCommonParasDlg::slot_cmb_Value_currentIndexChanged(int index)
{

}

void QVolInverseCommonParasDlg::slot_cmb_CTPos_Changed(int index)
{

}

void QVolInverseCommonParasDlg::on_m_btnOK_clicked()
{
	this->done(Accepted);
}

void QVolInverseCommonParasDlg::on_m_btnCancel_clicked()
{
	this->close();
}

void QVolInverseCommonParasDlg::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_PreFaultTime);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_UPre);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_IPre);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_PreAngle);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_NORMHZ);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_CTPos);
	CheckForPresence(pParas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultTime);
}

void QVolInverseCommonParasDlg::UpdataAllCommonParas(CExBaseList *pAllItems)
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

BOOL QVolInverseCommonParasDlg::CheckItemsModify(CExBaseList *pItem)
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
		if(pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CTPos)
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

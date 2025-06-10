#include "DistanceCommonParasDlg.h"
#include "ui_DistanceCommonParasDlg.h"
extern QFont *g_pSttGlobalFont;

QDistanceCommonParasDlg::QDistanceCommonParasDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDistanceCommonParasDlg)
{
    ui->setupUi(this);
	m_pParas = NULL;
	InitUI();
}

QDistanceCommonParasDlg::~QDistanceCommonParasDlg()
{
    delete ui;
}
void QDistanceCommonParasDlg::InitUI()
{	//20340617 luozibing 添加页面显示数据
	ui->m_cmbFaultTrig->addItems(QStringList()<<"时间触发"<<"手动触发"<<"开入量触发");
	ui->m_cmbPTPos->addItems(QStringList()<<"母线侧"<<"线路侧");
	ui->m_cmbCTPos->addItems(QStringList()<<"指向母线"<<"指向线路");
	ui->m_cmbBreaker->addItems(QStringList()<<"不模拟"<<"模拟");
	ui->m_cmbVzDefine->addItems(QStringList()<<"0"<<"Ua"<<"Ub"<<"Uc"<<_T("√3×3U0")<<"3U0"<<"-3U0");
	ui->m_cmbPsuVzRef->addItems(QStringList()<<"Ua相位"<<"Ub相位"<<"Uc相位"<<"Uab相位"<<"Ubc相位"<<"Uca相位");

	setFont(*g_pSttGlobalFont);
}
void QDistanceCommonParasDlg::SetDatas(CDataGroup *pParas)
{
	//20240617 luozibing 读取数据转换到界面中
	if(m_pParas != NULL)
	{
		m_pParas->DeleteAll();
		delete m_pParas;
		m_pParas = NULL;
	}
	m_pParas = pParas;

	POS pos = m_pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CShortData *pData = (CShortData*)m_pParas->GetNext(pos);
		SetValueToPage(pData);
	}
}
void QDistanceCommonParasDlg::SetValueToPage(CShortData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_PREFAULTTIME)
	{
		ui->m_txtPreFaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTIME)
	{
		ui->m_txtFaultTime->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TIMEAFTERTRIGGER)
	{
		ui->m_txtTimeAfter->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTRIGMODE)
	{
		ui->m_cmbFaultTrig->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_PTPOS)
	{
		ui->m_cmbPTPos->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_CTPOS)
	{
		ui->m_cmbCTPos->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOAD)
	{
		ui->m_txtILoad->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOADPH)
	{
		ui->m_txtILoadPh->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_SIMULATEBREAKERDELAY)
	{
		ui->m_cmbBreaker->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKBREAKTIME)
	{
		ui->m_txtBreakTime->setText(CheckDataMinMax(pData->m_strValue,999999,0,0));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKCLOSETIME)
	{
		ui->m_txtCloseTime->setText(CheckDataMinMax(pData->m_strValue,999999,0,0));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZDEFINE)
	{
		ui->m_cmbVzDefine->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPHDEFINE)
	{
		ui->m_cmbPsuVzRef->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPH)
	{
		ui->m_txtVzPh->setText(CheckDataMinMax(pData->m_strValue,999999,0,0));
	}
}
void QDistanceCommonParasDlg::GetDatas(CDataGroup *pParas)
{
	//20240617 luozibing 将界面设置参数填到链表
	POS pos = m_pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CShortData *pData = (CShortData*)m_pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}
void QDistanceCommonParasDlg::GetPageToValue(CShortData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_PREFAULTTIME)
	{
		pData->m_strValue = ui->m_txtPreFaultTime->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTIME)
	{
		pData->m_strValue = ui->m_txtFaultTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TIMEAFTERTRIGGER)
	{
		pData->m_strValue = ui->m_txtTimeAfter->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTRIGMODE)
	{
		pData->m_strValue.Format("%d",ui->m_cmbFaultTrig->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_PTPOS)
	{
		pData->m_strValue.Format("%d",ui->m_cmbPTPos->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_CTPOS)
	{
		pData->m_strValue.Format("%d",ui->m_cmbCTPos->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOAD)
	{
		pData->m_strValue = ui->m_txtILoad->text();
	}
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOADPH)
	{
		pData->m_strValue = ui->m_txtILoadPh->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_SIMULATEBREAKERDELAY)
	{
		pData->m_strValue.Format("%d",ui->m_cmbBreaker->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKBREAKTIME)
	{
		pData->m_strValue = ui->m_txtBreakTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKCLOSETIME)
	{
		pData->m_strValue = ui->m_txtCloseTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZDEFINE)
	{
		pData->m_strValue.Format("%d",ui->m_cmbVzDefine->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPHDEFINE)
	{
		pData->m_strValue.Format("%d",ui->m_cmbPsuVzRef->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPH)
	{
		pData->m_strValue = ui->m_txtVzPh->text();
	}
}
void QDistanceCommonParasDlg::on_m_txtPreFaultTime_editingFinished()
{
	ui->m_txtPreFaultTime->setText(CheckDataMinMax(ui->m_txtPreFaultTime->text(),999.999,0,3));
}
void QDistanceCommonParasDlg::on_m_txtFaultTime_editingFinished()
{
	ui->m_txtFaultTime->setText(CheckDataMinMax(ui->m_txtFaultTime->text(),999.999,0,3));
}
void QDistanceCommonParasDlg::on_m_txtTimeAfter_editingFinished()
{
	ui->m_txtTimeAfter->setText(CheckDataMinMax(ui->m_txtTimeAfter->text(),999.999,0,3));
}

void QDistanceCommonParasDlg::on_m_txtILoad_editingFinished()
{
	ui->m_txtILoad->setText(CheckDataMinMax(ui->m_txtILoad->text(),20,0,3));
}

void QDistanceCommonParasDlg::on_m_txtILoadPh_editingFinished()
{
	ui->m_txtILoadPh->setText(CheckDataMinMax(ui->m_txtILoadPh->text(),360,-360,1));
}

void QDistanceCommonParasDlg::on_m_txtBreakTime_editingFinished()
{
	ui->m_txtBreakTime->setText(CheckDataMinMax(ui->m_txtBreakTime->text(),999999,0,0));
}

void QDistanceCommonParasDlg::on_m_txtCloseTime_editingFinished()
{
	ui->m_txtCloseTime->setText(CheckDataMinMax(ui->m_txtCloseTime->text(),999999,0,0));
}

void QDistanceCommonParasDlg::on_m_txtVzPh_editingFinished()
{	
	ui->m_txtVzPh->setText(CheckDataMinMax(ui->m_txtVzPh->text(),360,-360,0));
}
void QDistanceCommonParasDlg::on_m_cmbBreaker_currentIndexChanged(int index)
{
	if(index == 0)
	{
		ui->m_txtBreakTime->setEnabled(false);
		ui->m_txtCloseTime->setEnabled(false);
	}
	else
	{
		ui->m_txtBreakTime->setEnabled(true);
		ui->m_txtCloseTime->setEnabled(true);
	}
}

void QDistanceCommonParasDlg::on_m_cmbVzDefine_currentIndexChanged(int index)
{
	if(index == 1||index == 2 ||index == 3)
	{
		ui->m_cmbPsuVzRef->setEnabled(true);
		ui->m_txtVzPh->setEnabled(true);
	}
	else
	{
		ui->m_cmbPsuVzRef->setEnabled(false);
		ui->m_txtVzPh->setEnabled(false);
	}
}
void QDistanceCommonParasDlg::on_m_btnOK_clicked()
{
	this->done(Accepted);
}

void QDistanceCommonParasDlg::on_m_btnCancel_clicked()
{
	this->close();
}
CString CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint)
{	
	if (strValue.toFloat()<nMin)
	{
		strValue.setNum(nMin);
	}
	if(strValue.toFloat()>nMax)
	{
		strValue.setNum(nMax);
	}
	int num = 0;
	int nPoint = strValue.indexOf(".");
	if(nPoint == -1)
	{
		if (strValue == "")
		{
			strValue = "0";
		}
		if(nAfterPoint>0)
			strValue += ".";
	}
	else
	{
		num = strValue.length()-nPoint-1;
		if (num>nAfterPoint)
		{
			if(nAfterPoint >0)
				strValue = strValue.left(nPoint+1+nAfterPoint);
			else
				strValue = strValue.left(nPoint+nAfterPoint);
			num = nAfterPoint;
		}
	}
	for (int i=num;i<nAfterPoint;i++)
	{
		strValue+="0";
	}
	return strValue;
}
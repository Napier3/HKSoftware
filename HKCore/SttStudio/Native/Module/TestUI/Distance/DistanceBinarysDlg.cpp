#include "DistanceBinarysDlg.h"
#include "ui_DistanceBinarysDlg.h"

extern QFont *g_pSttGlobalFont;

QDistanceBinarysDlg::QDistanceBinarysDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDistanceBinarysDlg)
{
    ui->setupUi(this);
	m_pParas = NULL;
	InitUI();
}

QDistanceBinarysDlg::~QDistanceBinarysDlg()
{
    delete ui;
}
void QDistanceBinarysDlg::InitUI()
{	//20340617 luozibing 添加页面显示数据
	setFont(*g_pSttGlobalFont);
	ui->m_cmbSel->addItems(QStringList()<<"开入A-B-C-D"<<"开入E-F-G-H");
	QStringList list_Input;
	list_Input.append("单跳");
	list_Input.append("三跳");
	list_Input.append("重合");
	ui->m_cmbA->addItems(list_Input);
	ui->m_cmbB->addItems(list_Input);
	ui->m_cmbC->addItems(list_Input);
	ui->m_cmbD->addItems(list_Input);
	ui->m_cmbE->addItems(list_Input);
	ui->m_cmbF->addItems(list_Input);
	ui->m_cmbG->addItems(list_Input);
	ui->m_cmbH->addItems(list_Input);
	QStringList list_Out;
	list_Out.append("断开");
	list_Out.append("闭合");
	ui->m_cmb_B01->addItems(list_Out);
	ui->m_cmb_B02->addItems(list_Out);
	ui->m_cmb_B03->addItems(list_Out);
	ui->m_cmb_B04->addItems(list_Out);
	ui->m_cmb_B05->addItems(list_Out);
	ui->m_cmb_B06->addItems(list_Out);
	ui->m_cmb_B07->addItems(list_Out);
	ui->m_cmb_B08->addItems(list_Out);
	ui->m_cmb_SwitchMode->addItems(QStringList()<<"时间启动"<<"开入量启动");
}
void QDistanceBinarysDlg::SetDatas(CDataGroup *pParas)
{
	//20240617 luozibing 读取数据转换到界面中
	if(pParas == NULL)
		return;

	m_pParas = pParas;

	POS pos = m_pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CShortData *pData = (CShortData*)m_pParas->GetNext(pos);
		SetValueToPage(pData);
	}
}
void QDistanceBinarysDlg::SetValueToPage(CShortData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_BINSELECT)
	{
		ui->m_cmbSel->setCurrentIndex(pData->m_strValue.toInt());
		CheckInputSel(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_A)
	{
		ui->m_cmbA->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_B)
	{
		ui->m_cmbB->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_C)
	{
		ui->m_cmbC->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_D)
	{
		ui->m_cmbD->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_E)
	{
		ui->m_cmbE->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_F)
	{
		ui->m_cmbF->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_G)
	{
		ui->m_cmbG->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_H)
	{
		ui->m_cmbH->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B01)
	{
		ui->m_cmb_B01->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B02)
	{
		ui->m_cmb_B02->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B03)
	{
		ui->m_cmb_B03->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B04)
	{
		ui->m_cmb_B04->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B05)
	{
		ui->m_cmb_B05->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B06)
	{
		ui->m_cmb_B06->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B07)
	{
		ui->m_cmb_B07->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B08)
	{
		ui->m_cmb_B08->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTSWITCHMODE)
	{
		ui->m_cmb_SwitchMode->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTKEEPTIME)
	{
		ui->m_txtKeepTime->setText(CheckDataMinMax(pData->m_strValue,100000,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTDELAYTIME)
	{
		ui->m_txtDelayTime->setText(CheckDataMinMax(pData->m_strValue,100000,0,3));
	}
}
void QDistanceBinarysDlg::GetDatas(CDataGroup *pParas)
{
	//20240617 luozibing 将界面设置参数填到链表
	POS pos = m_pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CShortData *pData = (CShortData*)m_pParas->GetNext(pos);
		GetPageToValue(pData);
	}
}
void QDistanceBinarysDlg::GetPageToValue(CShortData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_BINSELECT)
	{
		pData->m_strValue.Format("%d",ui->m_cmbSel->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_A)
	{
		pData->m_strValue.Format("%d",ui->m_cmbA->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_B)
	{
		pData->m_strValue.Format("%d",ui->m_cmbB->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_C)
	{
		pData->m_strValue.Format("%d",ui->m_cmbC->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_D)
	{
		pData->m_strValue.Format("%d",ui->m_cmbD->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_E)
	{
		pData->m_strValue.Format("%d",ui->m_cmbE->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_F)
	{
		pData->m_strValue.Format("%d",ui->m_cmbF->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_G)
	{
		pData->m_strValue.Format("%d",ui->m_cmbG->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_H)
	{
		pData->m_strValue.Format("%d",ui->m_cmbH->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B01)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B01->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B02)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B02->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B03)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B03->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B04)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B04->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B05)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B05->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B06)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B06->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B07)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B07->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__B08)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_B08->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTSWITCHMODE)
	{
		pData->m_strValue.Format("%d",ui->m_cmb_SwitchMode->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTKEEPTIME)
	{
		pData->m_strValue = ui->m_txtKeepTime->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTDELAYTIME)
	{
		pData->m_strValue = ui->m_txtDelayTime->text();
	}
	
}
void QDistanceBinarysDlg::on_m_cmbSel_currentIndexChanged(int index)
{
	CheckInputSel(index);
}
void QDistanceBinarysDlg::CheckInputSel(int index)
{
	if(index == 0)
	{
		ui->m_cmbA->setEnabled(true);
		ui->m_cmbB->setEnabled(true);
		ui->m_cmbC->setEnabled(true);
		ui->m_cmbD->setEnabled(true);
		ui->m_cmbE->setEnabled(false);
		ui->m_cmbF->setEnabled(false);
		ui->m_cmbG->setEnabled(false);
		ui->m_cmbH->setEnabled(false);
	}
	else
	{
		ui->m_cmbA->setEnabled(false);
		ui->m_cmbB->setEnabled(false);
		ui->m_cmbC->setEnabled(false);
		ui->m_cmbD->setEnabled(false);
		ui->m_cmbE->setEnabled(true);
		ui->m_cmbF->setEnabled(true);
		ui->m_cmbG->setEnabled(true);
		ui->m_cmbH->setEnabled(true);
	}
}
void QDistanceBinarysDlg::on_m_cmb_SwitchMode_currentIndexChanged(int index)
{
	if (index == 0)
	{
		ui->m_txtKeepTime->setEnabled(true);
	} 
	else
	{
		ui->m_txtKeepTime->setEnabled(false);
	}
}
void QDistanceBinarysDlg::on_m_txtDelayTime_editingFinished()
{
	ui->m_txtDelayTime->setText(CheckDataMinMax(ui->m_txtDelayTime->text(),100000,0,3));
}

void QDistanceBinarysDlg::on_m_txtKeepTime_editingFinished()
{
	ui->m_txtKeepTime->setText(CheckDataMinMax(ui->m_txtKeepTime->text(),100000,0,3));
}
void QDistanceBinarysDlg::on_m_btnOK_clicked()
{
	this->done(Accepted);
}

void QDistanceBinarysDlg::on_m_btnCancel_clicked()
{
	this->close();
}
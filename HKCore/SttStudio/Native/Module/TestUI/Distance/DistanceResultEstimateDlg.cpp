#include "DistanceResultEstimateDlg.h"
#include "ui_DistanceResultEstimateDlg.h"
#include "../../UI/SttTestCntrFrameBase.h"

QDistanceResultEstimateDlg::QDistanceResultEstimateDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDistanceResultEstimateDlg)
{
    ui->setupUi(this);
	setWindowTitle("结果评估");
}

QDistanceResultEstimateDlg::~QDistanceResultEstimateDlg()
{
    delete ui;
}
void QDistanceResultEstimateDlg::InitUI()
{
	setFont(*g_pSttGlobalFont);
}
void QDistanceResultEstimateDlg::SetValueToPage(int nRow)
{
	CString strNameZonne,strAbs,strRel,strLogic;
	strAbs.Format("Zone%d_AbsErr",nRow);
	strRel.Format("Zone%d_RelErr",nRow);
	strLogic.Format("Zone%d_ErrorLogic",nRow);
	QComboBox *pcmb;
	QLineEdit *ptxtAbs;
	QLineEdit *ptxtRel;
	switch(nRow)
	{
	case 1:
		pcmb = ui->m_cmb1;
		ptxtAbs = ui->m_txtAbs1;
		ptxtRel = ui->m_txtRel1;
		break;
	case 2:
		pcmb = ui->m_cmb2;
		ptxtAbs = ui->m_txtAbs2;
		ptxtRel = ui->m_txtRel2;
		break;
	case 3:
		pcmb = ui->m_cmb3;
		ptxtAbs = ui->m_txtAbs3;
		ptxtRel = ui->m_txtRel3;
		break;
	case 4:
		pcmb = ui->m_cmb4;
		ptxtAbs = ui->m_txtAbs4;
		ptxtRel = ui->m_txtRel4;
		break;
	}
	pcmb->addItem(_T("绝对误差"));
	pcmb->addItem(_T("相对误差"));
	pcmb->addItem(_T("绝对or相对"));
	pcmb->addItem(_T("绝对&相对"));
	pcmb->addItem(_T("组合误差"));
	pcmb->setCurrentIndex(0);

	CDvmData * pData = (CDvmData *)m_pParas->FindByID(strLogic);
	if (pData != NULL)
	{
		pcmb->setCurrentIndex(pData->m_strValue.toInt());
	}

	pData = (CDvmData *)m_pParas->FindByID(strAbs);
	if (pData != NULL)
	{
		ptxtAbs->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
	}
	pData = (CDvmData *)m_pParas->FindByID(strRel);
	if (pData != NULL)
	{
		ptxtRel->setText(CheckDataMinMax(pData->m_strValue,100,0,3));
	}

	if(!CheckZone(nRow))
	{
		pcmb->setEnabled(false);
		ptxtAbs->setEnabled(false);
		ptxtRel->setEnabled(false);
	}
	else
	{
		pcmb->setEnabled(true);
		ptxtAbs->setEnabled(true);
		ptxtRel->setEnabled(true);
	}
	
}

void QDistanceResultEstimateDlg::SetDatas(CDataGroup *pParas)
{//Set将读取数据转换到界面
	m_pParas = pParas;

	InitUI();

	for (int i=1;i<5;i++)
	{
		SetValueToPage(i);
	}
}
bool QDistanceResultEstimateDlg::CheckZone(int nZone)
{
	CString strLN,strLL;
	strLN.Format("LNZone%d_Check",nZone);
	strLL.Format("LLZone%d_Check",nZone);

	CDvmData *pDataLN = (CDvmData *)m_pParas->FindByID(strLN);
	CDvmData *pDataLL= (CDvmData *)m_pParas->FindByID(strLL);
	if (pDataLL != NULL&&pDataLN != NULL)
	{
		return (pDataLN->m_strValue == "1"||pDataLL->m_strValue == "1");
	}
	return false;
}
void QDistanceResultEstimateDlg::GetPageToValue(int nRow)
{
	CString strNameZonne,strAbs,strRel,strLogic;
	strAbs.Format("Zone%d_AbsErr",nRow);
	strRel.Format("Zone%d_RelErr",nRow);
	strLogic.Format("Zone%d_ErrorLogic",nRow);
	QComboBox *pcmb;
	QLineEdit *ptxtAbs;
	QLineEdit *ptxtRel;
	switch(nRow)
	{
	case 1:
		pcmb = ui->m_cmb1;
		ptxtAbs = ui->m_txtAbs1;
		ptxtRel = ui->m_txtRel1;
		break;
	case 2:
		pcmb = ui->m_cmb2;
		ptxtAbs = ui->m_txtAbs2;
		ptxtRel = ui->m_txtRel2;
		break;
	case 3:
		pcmb = ui->m_cmb3;
		ptxtAbs = ui->m_txtAbs3;
		ptxtRel = ui->m_txtRel3;
		break;
	case 4:
		pcmb = ui->m_cmb4;
		ptxtAbs = ui->m_txtAbs4;
		ptxtRel = ui->m_txtRel4;
		break;
	}
	if(!pcmb->isEnabled())
		return;

	CDvmData * pData = (CDvmData *)m_pParas->FindByID(strLogic);
	if (pData != NULL)
	{
		CString strTmp;
		strTmp.Format("%d",pcmb->currentIndex());
		pData->m_strValue = strTmp;
	}

	pData = (CDvmData *)m_pParas->FindByID(strAbs);
	if (pData != NULL)
	{
		pData->m_strValue = ptxtAbs->text();
	}
	pData = (CDvmData *)m_pParas->FindByID(strRel);
	if (pData != NULL)
	{
		pData->m_strValue = ptxtRel->text();
	}
}
void QDistanceResultEstimateDlg::GetDatas(CDataGroup *pParas)
{//Get将界面设置参数填到链表
	for (int i=1;i<5;i++)
	{
		GetPageToValue(i);
	}
}
void QDistanceResultEstimateDlg::on_m_btnOK_clicked()
{
	this->done(Accepted);
}

void QDistanceResultEstimateDlg::on_m_btnCancel_clicked()
{
	this->close();
}
void QDistanceResultEstimateDlg::on_m_txtRel1_editingFinished()
{
	ui->m_txtRel1->setText(CheckDataMinMax(ui->m_txtRel1->text(),100,0,3));
}

void QDistanceResultEstimateDlg::on_m_txtAbs1_editingFinished()
{
	ui->m_txtAbs1->setText(CheckDataMinMax(ui->m_txtAbs1->text(),200,0,3));
}

void QDistanceResultEstimateDlg::on_m_txtRel2_editingFinished()
{
	ui->m_txtRel2->setText(CheckDataMinMax(ui->m_txtRel2->text(),100,0,3));
}

void QDistanceResultEstimateDlg::on_m_txtAbs2_editingFinished()
{
	ui->m_txtAbs2->setText(CheckDataMinMax(ui->m_txtAbs2->text(),200,0,3));
}

void QDistanceResultEstimateDlg::on_m_txtRel3_editingFinished()
{
	ui->m_txtRel3->setText(CheckDataMinMax(ui->m_txtRel3->text(),100,0,3));
}

void QDistanceResultEstimateDlg::on_m_txtAbs3_editingFinished()
{
	ui->m_txtAbs3->setText(CheckDataMinMax(ui->m_txtAbs3->text(),200,0,3));
}

void QDistanceResultEstimateDlg::on_m_txtRel4_editingFinished()
{
	ui->m_txtRel4->setText(CheckDataMinMax(ui->m_txtRel4->text(),100,0,3));
}

void QDistanceResultEstimateDlg::on_m_txtAbs4_editingFinished()
{
	ui->m_txtAbs4->setText(CheckDataMinMax(ui->m_txtAbs4->text(),200,0,3));
}


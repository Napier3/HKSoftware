#include "DistanceResultEstimateDlg.h"
#include "ui_DistanceResultEstimateDlg.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../UI/Controls/SettingCtrls/QSettingLineEdit.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240802 huangliang 

QDistanceResultEstimateDlg::QDistanceResultEstimateDlg(QWidget *parent) :
	QDialog(parent),
    ui(new Ui::QDistanceResultEstimateDlg)
{
	Stt_Global_SettingParent(this);	//20240802 huangliang 
    ui->setupUi(this);
	setWindowTitle(g_sLangTxt_StateEstimate_ResultEstimate/*("结果评估")*/);
}

QDistanceResultEstimateDlg::~QDistanceResultEstimateDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
    delete ui;
}
void QDistanceResultEstimateDlg::InitUI()
{
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setFont(*g_pSttGlobalFont);
	CExBaseList *pListTemp = (CExBaseList  *)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_PARAS_DATATYPE_ID_RltErrorLogic_Time);//显示动作时误差类型
	ui->m_cmb1->SetBaseList(pListTemp);
	ui->m_cmb2->SetBaseList(pListTemp);
	ui->m_cmb3->SetBaseList(pListTemp);
	ui->m_cmb4->SetBaseList(pListTemp);
	ui->m_cmb5->SetBaseList(pListTemp);
}
void QDistanceResultEstimateDlg::SetValueToPage(int nRow)
{
	CString strNameZonne,strPlus,strMinus,strRel,strLogic;
	QComboBox *pcmb;
	QSettingLineEdit *ptxtPlus;
	QSettingLineEdit *ptxtMinus;
	QSettingLineEdit *ptxtRel;
	switch(nRow)
	{
	case 1:
		pcmb = ui->m_cmb1;
		ptxtPlus = ui->m_txtPlus_1;
		ptxtMinus = ui->m_txtMinus_1;
		ptxtRel = ui->m_txtRel1;
		strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1;
		strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1;
		strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1;
		strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1;
		break;
	case 2:
		pcmb = ui->m_cmb2;
		ptxtPlus = ui->m_txtPlus_2;
		ptxtMinus = ui->m_txtMinus_2;
		ptxtRel = ui->m_txtRel2;
		strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2;
		strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2;
		strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2;
		strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2;
		break;
	case 3:
		pcmb = ui->m_cmb3;
		ptxtPlus = ui->m_txtPlus_3;
		ptxtMinus = ui->m_txtMinus_3;
		ptxtRel = ui->m_txtRel3;
		strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3;
		strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3;
		strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3;
		strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3;
		break;
	case 4:
		pcmb = ui->m_cmb4;
		ptxtPlus = ui->m_txtPlus_4;
		ptxtMinus = ui->m_txtMinus_4;
		ptxtRel = ui->m_txtRel4;
		strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4;
		strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4;
		strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4;
		strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4;
		break;
	case 5:
		pcmb = ui->m_cmb5;
		ptxtPlus = ui->m_txtPlus_5;
		ptxtMinus = ui->m_txtMinus_5;
		ptxtRel = ui->m_txtRel5;
		strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5;
		strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5;
		strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5;
		strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5;
		break;
	}
	//pcmb->addItem(g_sLangTxt_Distance_ErrorNot/*("不评估")*/);
	//pcmb->addItem(g_sLangTxt_StateEstimate_RelError/*("相对误差")*/);
	//pcmb->addItem(g_sLangTxt_StateEstimate_AbsError/*("绝对误差")*/);
	//pcmb->addItem(g_sLangTxt_Distance_ErrorRelAndAbs/*("相对误差与绝对误差")*/);
	//pcmb->addItem(g_sLangTxt_Distance_ErrorRelorAbs/*("相对误差或绝对误差")*/);
	//pcmb->addItem(g_sLangTxt_StateEstimate_CombinationError/*("组合误差")*/);
	pcmb->setCurrentIndex(0);

	CDvmData * pData = (CDvmData *)m_pParas->FindByID(strLogic);
	if (pData != NULL)
	{
		pcmb->setCurrentIndex((int)pData->m_strValue.toDouble());
	}
	else
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strLogic;
		pNew->m_strID = strLogic;
		pNew->m_strValue = STT_MULTI_MACRO_DISTANCE_PARAS_ID_DEFAULT;
		m_pParas->AddNewChild(pNew);
		pcmb->setCurrentIndex(pNew->m_strValue.toInt());
	}

	pData = (CDvmData *)m_pParas->FindByID(strPlus);
	if (pData != NULL)
	{
		ptxtPlus->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
	}
	else
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strPlus;
		pNew->m_strID = strPlus;
		pNew->m_strValue = STT_MULTI_MACRO_DISTANCE_PARAS_ID_DEFAULT;
		m_pParas->AddNewChild(pNew);
		ptxtPlus->setText(CheckDataMinMax(pNew->m_strValue,200,0,3));
	}
	pData = (CDvmData *)m_pParas->FindByID(strMinus);
	if (pData != NULL)
	{
		ptxtMinus->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
	}
	else
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strMinus;
		pNew->m_strID = strMinus;
		pNew->m_strValue = STT_MULTI_MACRO_DISTANCE_PARAS_ID_DEFAULT;
		m_pParas->AddNewChild(pNew);
		ptxtMinus->setText(CheckDataMinMax(pNew->m_strValue,200,0,3));
	}
	pData = (CDvmData *)m_pParas->FindByID(strRel);
	if (pData != NULL)
	{
		ptxtRel->setText(CheckDataMinMax(pData->m_strValue,100,0,3));
	}
	else
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strRel;
		pNew->m_strID = strRel;
		pNew->m_strValue = STT_MULTI_MACRO_DISTANCE_PARAS_ID_DEFAULT;
		m_pParas->AddNewChild(pNew);
		ptxtRel->setText(CheckDataMinMax(pNew->m_strValue,100,0,3));
	}

	if(!CheckZone(nRow))
	{
		pcmb->setEnabled(false);
		ptxtPlus->setEnabled(false);
		ptxtMinus->setEnabled(false);
		ptxtRel->setEnabled(false);
	}
	else
	{
		pcmb->setEnabled(true);
		ptxtPlus->setEnabled(true);
		ptxtMinus->setEnabled(true);
		ptxtRel->setEnabled(true);
	}

}

void QDistanceResultEstimateDlg::SetDatas(CDataGroup *pParas)
{//Set将读取数据转换到界面
	if (pParas == NULL)
	{
		return;
	}
	m_pParas = pParas;
	InitUI();

	for (int i=1;i<6;i++)
	{
		SetValueToPage(i);
	}
}
bool QDistanceResultEstimateDlg::CheckZone(int nZone)
{
	//20240903 luozibing 结果评估中设置的值在曲线编辑页面 曲线参数中设置
	return false;
	CString strLN,strLL;
	/*strLN.Format("LNZone%d_Check",nZone);
	strLL.Format("LLZone%d_Check",nZone);*/

	switch (nZone)
	{
	case 1:
		strLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK;
		strLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK;
		break;
	case 2:
		strLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK;
		strLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE2_CHECK;
		break;
	case 3:
		strLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK;
		strLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE3_CHECK;
		break;
	case 4:
		strLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK;
		strLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE4_CHECK;
		break;
	case 5:
		strLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK;
		strLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE5_CHECK;
		break;
	}

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
	CString strNameZonne, strPlus, strMinus, strRel, strLogic;
	QComboBox *pcmb;
    QSettingLineEdit *ptxtPlus;     //20240723 huangliang
    QSettingLineEdit *ptxtMinus;
    QSettingLineEdit *ptxtRel;
	switch(nRow)
	{
	case 1:
		pcmb = ui->m_cmb1;
		ptxtPlus = ui->m_txtPlus_1;
		ptxtMinus = ui->m_txtMinus_1;
		ptxtRel = ui->m_txtRel1;
		strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1;
		strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1;
		strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1;
		strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1;
		break;
	case 2:
		pcmb = ui->m_cmb2;
		ptxtPlus = ui->m_txtPlus_2;
		ptxtMinus = ui->m_txtMinus_2;
		ptxtRel = ui->m_txtRel2;
		strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2;
		strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2;
		strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2;
		strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2;
		break;
	case 3:
		pcmb = ui->m_cmb3;
		ptxtPlus = ui->m_txtPlus_3;
		ptxtMinus = ui->m_txtMinus_3;
		ptxtRel = ui->m_txtRel3;
		strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3;
		strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3;
		strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3;
		strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3;
		break;
	case 4:
		pcmb = ui->m_cmb4;
		ptxtPlus = ui->m_txtPlus_4;
		ptxtMinus = ui->m_txtMinus_4;
		ptxtRel = ui->m_txtRel4;
		strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4;
		strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4;
		strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4;
		strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4;
		break;
	case 5:
		pcmb = ui->m_cmb5;
		ptxtPlus = ui->m_txtPlus_5;
		ptxtMinus = ui->m_txtMinus_5;
		ptxtRel = ui->m_txtRel5;
		strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5;
		strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5;
		strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5;
		strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5;
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
	else
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strLogic;
		pNew->m_strID = strLogic;
		pNew->m_strValue = STT_MULTI_MACRO_DISTANCE_PARAS_ID_DEFAULT;
		m_pParas->AddNewChild(pNew);
		pcmb->setCurrentIndex(pNew->m_strValue.toInt());
	}

	pData = (CDvmData *)m_pParas->FindByID(strPlus);
	if (pData != NULL)
	{
		pData->m_strValue = ptxtPlus->text();
	}
	else
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strPlus;
		pNew->m_strID = strPlus;
		pNew->m_strValue = STT_MULTI_MACRO_DISTANCE_PARAS_ID_DEFAULT;
		m_pParas->AddNewChild(pNew);
		ptxtPlus->setText(CheckDataMinMax(pNew->m_strValue,200,0,3));
	}

	pData = (CDvmData *)m_pParas->FindByID(strMinus);
	if (pData != NULL)
	{
		pData->m_strValue = ptxtMinus->text();
	}
	else
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strMinus;
		pNew->m_strID = strMinus;
		pNew->m_strValue = STT_MULTI_MACRO_DISTANCE_PARAS_ID_DEFAULT;
		m_pParas->AddNewChild(pNew);
		ptxtMinus->setText(CheckDataMinMax(pNew->m_strValue,200,0,3));
	}
	pData = (CDvmData *)m_pParas->FindByID(strRel);
	if (pData != NULL)
	{
		pData->m_strValue = ptxtRel->text();
	}
	else
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strRel;
		pNew->m_strID = strRel;
		pNew->m_strValue = STT_MULTI_MACRO_DISTANCE_PARAS_ID_DEFAULT;
		m_pParas->AddNewChild(pNew);
		ptxtRel->setText(CheckDataMinMax(pNew->m_strValue,100,0,3));
	}
}
void QDistanceResultEstimateDlg::GetDatas(CDataGroup *pParas)
{//Get将界面设置参数填到链表
	if(pParas == NULL)
		return;
	m_pParas = pParas;
	for (int i=1;i<6;i++)
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

void QDistanceResultEstimateDlg::on_m_txtPlus_1_editingFinished()
{
	ui->m_txtPlus_1->setText(CheckDataMinMax(ui->m_txtPlus_1->text(),200,0,3));
}
void QDistanceResultEstimateDlg::on_m_txtMinus_1_editingFinished()
{
	ui->m_txtMinus_1->setText(CheckDataMinMax(ui->m_txtMinus_1->text(),200,0,3));
}

void QDistanceResultEstimateDlg::on_m_txtRel2_editingFinished()
{
	ui->m_txtRel2->setText(CheckDataMinMax(ui->m_txtRel2->text(),100,0,3));
}

void QDistanceResultEstimateDlg::on_m_txtPlus_2_editingFinished()
{
	ui->m_txtPlus_2->setText(CheckDataMinMax(ui->m_txtPlus_2->text(),200,0,3));
}
void QDistanceResultEstimateDlg::on_m_txtMinus_2_editingFinished()
{
	ui->m_txtMinus_2->setText(CheckDataMinMax(ui->m_txtMinus_2->text(),200,0,3));
}

void QDistanceResultEstimateDlg::on_m_txtRel3_editingFinished()
{
	ui->m_txtRel3->setText(CheckDataMinMax(ui->m_txtRel3->text(),100,0,3));
}

void QDistanceResultEstimateDlg::on_m_txtPlus_3_editingFinished()
{
	ui->m_txtPlus_3->setText(CheckDataMinMax(ui->m_txtPlus_3->text(),200,0,3));
}
void QDistanceResultEstimateDlg::on_m_txtMinus_3_editingFinished()
{
	ui->m_txtMinus_3->setText(CheckDataMinMax(ui->m_txtMinus_3->text(),200,0,3));
}

void QDistanceResultEstimateDlg::on_m_txtRel4_editingFinished()
{
	ui->m_txtRel4->setText(CheckDataMinMax(ui->m_txtRel4->text(),100,0,3));
}

void QDistanceResultEstimateDlg::on_m_txtPlus_4_editingFinished()
{
	ui->m_txtPlus_4->setText(CheckDataMinMax(ui->m_txtPlus_4->text(),200,0,3));
}
void QDistanceResultEstimateDlg::on_m_txtMinus_4_editingFinished()
{
	ui->m_txtMinus_4->setText(CheckDataMinMax(ui->m_txtMinus_4->text(),200,0,3));
}
void QDistanceResultEstimateDlg::on_m_txtRel5_editingFinished()
{
	ui->m_txtRel5->setText(CheckDataMinMax(ui->m_txtRel5->text(),100,0,3));
}
void QDistanceResultEstimateDlg::on_m_txtPlus_5_editingFinished()
{
	ui->m_txtPlus_5->setText(CheckDataMinMax(ui->m_txtPlus_5->text(),200,0,3));
}
void QDistanceResultEstimateDlg::on_m_txtMinus_5_editingFinished()
{
	ui->m_txtMinus_5->setText(CheckDataMinMax(ui->m_txtMinus_5->text(),200,0,3));
}
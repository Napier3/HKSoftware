#include "DistanceItemParaEditWidget.h"
#include "ui_DistanceItemParaEditWidget.h"

QDistanceItemParaEditWidget::QDistanceItemParaEditWidget(QWidget *parent) :
	QItemParaEditWidgetBase(parent),
    m_pParaUI(new Ui::QDistanceItemParaEditWidget)
{
    m_pParaUI->setupUi(this);
	InitUI();
}

QDistanceItemParaEditWidget::~QDistanceItemParaEditWidget()
{
    delete m_pParaUI;
}
void QDistanceItemParaEditWidget::InitUI()
{
	m_pParaUI->m_cmb_ErrorType->addItems(QStringList()<<"A相接地"<<"B相接地"<<"C相接地"<<"AB短路"\
		<<"BC短路"<<"CA短路"<<"AB接地短路"<<"BC接地短路"<<"CA接地短路"<<"三相短路"<<"单相阻抗");
	m_pParaUI->m_cmb_RSC->addItems(QStringList()<<"Z-Phi"<<"R-X");
	m_pParaUI->m_cmb_ErrorDirc->addItems(QStringList()<<"反向"<<"正向");
	m_pParaUI->m_cmb_ErrorNature->addItems(QStringList()<<"瞬时"<<"永久");
	m_pParaUI->m_cmbK0Mode->addItems(QStringList()<<"|K0|,Phi(K0)"<<"RERL,XEXL"<<"|Z0/Z1|,Phi(Z0/Z1)");
}
void QDistanceItemParaEditWidget::SetDatas(CExBaseList *pParas)
{//20240619 luozibing 将读取数据转换到界面
	if(pParas == NULL)
		return;
	m_pCurrMacroTest = (CSttMacroTest *)pParas;
	POS pos = m_pCurrMacroTest->GetHeadPosition();
	while (pos!= NULL)
	{
		CShortData *pData = (CShortData*)m_pCurrMacroTest->GetNext(pos);
		SetValueToPage(pData);
	}
}
void QDistanceItemParaEditWidget::SetValueToPage(CShortData *pData)
{
	if(pData == NULL)
		return;
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE)
	{
		m_pParaUI->m_cmbK0Mode->setCurrentIndex(pData->m_strValue.toInt());
		SetModeText(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR)
	{
		m_pParaUI->m_txtKlKr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX)
	{
		m_pParaUI->m_txtAngKx->setText(CheckDataMinMax(pData->m_strValue,999.999,0,2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE)
	{
		m_pParaUI->m_cmb_ErrorType->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING)
	{
		m_pParaUI->m_txtZSetting->setText(CheckDataMinMax(pData->m_strValue,999.999,0.001,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG)
	{
		m_pParaUI->m_txtZAng->setText(CheckDataMinMax(pData->m_strValue,360,-360,1));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE)
	{
		m_pParaUI->m_txtRate->setText(CheckDataMinMax(pData->m_strValue,10,0.01,2));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_IMPREFTYPE)
	{
		m_pParaUI->m_cmb_RSC->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT)
	{
		m_pParaUI->m_txtFaultCurrent->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTDIRECTION)
	{
		m_pParaUI->m_cmb_ErrorDirc->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE1)
	{
		m_pParaUI->m_cmb_ErrorNature->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING)
	{
		m_pParaUI->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
	}
	
}
void QDistanceItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
{//20240620 luozibing 更新数据 将最新链表数据更新到页面
	SetDatas(pSttMacroTest);
}
void QDistanceItemParaEditWidget::GetDatas(CExBaseList *pParas)
{//20240619 luozibing 将界面设置参数填到链表
	POS pos = m_pCurrMacroTest->GetHeadPosition();
	while (pos!= NULL)
	{
		CShortData *pData = (CShortData*)m_pCurrMacroTest->GetNext(pos);
		GetPageToValue(pData);
	}
}
void QDistanceItemParaEditWidget::GetPageToValue(CShortData *pData)
{
	if(pData == NULL)
		return;
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE)
	{
		pData->m_strValue.setNum(m_pParaUI->m_cmbK0Mode->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR)
	{
		pData->m_strValue = m_pParaUI->m_txtKlKr->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX)
	{
		pData->m_strValue = m_pParaUI->m_txtAngKx->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE)
	{
		pData->m_strValue.setNum(m_pParaUI->m_cmb_ErrorType->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING)
	{
		pData->m_strValue = m_pParaUI->m_txtZSetting->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG)
	{
		pData->m_strValue = m_pParaUI->m_txtZAng->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE)
	{
		pData->m_strValue = m_pParaUI->m_txtRate->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT)
	{
		pData->m_strValue = m_pParaUI->m_txtFaultCurrent->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTDIRECTION)
	{
		pData->m_strValue.setNum(m_pParaUI->m_cmb_ErrorDirc->currentIndex()); 
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE1)
	{
		pData->m_strValue.setNum(m_pParaUI->m_cmb_ErrorNature->currentIndex());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING)
	{
		pData->m_strValue = m_pParaUI->m_txtTSetting->text();
	}

}
void QDistanceItemParaEditWidget::on_m_cmb_RSC_currentIndexChanged(int index)
{
	//20240618 luozibing 阻抗切换显示
	//int dummy1, dummy2,nrow,ncol;
	if (index == IMPREFTYPE_Z_PHI)
	{
		m_pParaUI->m_labZSetting->setText("阻抗定值(Ω)");
		m_pParaUI->m_labZAng->setText("阻抗角");
	} 
	else
	{
		m_pParaUI->m_labZSetting->setText("电阻定值(Ω)");
		m_pParaUI->m_labZAng->setText("电抗定值(Ω)");
	}
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_IMPREFTYPE,strTmp);
}

void QDistanceItemParaEditWidget::on_m_cmbK0Mode_currentIndexChanged(int index)
{
	SetModeText(index);
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE,strTmp);
}
void QDistanceItemParaEditWidget::SetModeText(int nIndex)
{
	CString strTmp = m_pParaUI->m_cmbK0Mode->itemText(nIndex);
	QStringList words = strTmp.split(",");
	m_pParaUI->m_labKlKr->setText(words[0]);
	m_pParaUI->m_labAngKx->setText(words[1]);
}
void QDistanceItemParaEditWidget::on_m_cmb_ErrorType_currentIndexChanged(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE,strTmp);
}
void QDistanceItemParaEditWidget::on_m_cmb_ErrorDirc_currentIndexChanged(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTDIRECTION,strTmp);
}
void QDistanceItemParaEditWidget::on_m_cmb_ErrorNature_currentIndexChanged(int index)
{
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE1,strTmp);
}
void QDistanceItemParaEditWidget::UpdatePara(CString strID,CString strValue)
{
	if(m_pCurrMacroTest == NULL)
		return;
	CShortData *pData = (CShortData *)m_pCurrMacroTest->FindByID(strID);
	if(pData != NULL)
	{
		pData->m_strValue = strValue;
	}
}
void QDistanceItemParaEditWidget::on_m_txtZSetting_editingFinished()
{
	m_pParaUI->m_txtZSetting->setText(CheckDataMinMax(m_pParaUI->m_txtZSetting->text(),999.999,0.001,3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING,m_pParaUI->m_txtZSetting->text());
}
void QDistanceItemParaEditWidget::on_m_txtZAng_editingFinished()
{
	m_pParaUI->m_txtZAng->setText(CheckDataMinMax(m_pParaUI->m_txtZAng->text(),360,-360,1));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG,m_pParaUI->m_txtZAng->text());
}
void QDistanceItemParaEditWidget::on_m_txtRate_editingFinished()
{
	m_pParaUI->m_txtRate->setText(CheckDataMinMax(m_pParaUI->m_txtRate->text(),10,0.01,2));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE,m_pParaUI->m_txtRate->text());
}
void QDistanceItemParaEditWidget::on_m_txtKlKr_editingFinished()
{
	m_pParaUI->m_txtKlKr->setText(CheckDataMinMax(m_pParaUI->m_txtKlKr->text(),999.999,0,2));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR,m_pParaUI->m_txtKlKr->text());
}
void QDistanceItemParaEditWidget::on_m_txtAngKx_editingFinished()
{
	m_pParaUI->m_txtAngKx->setText(CheckDataMinMax(m_pParaUI->m_txtAngKx->text(),999.999,0,2));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX,m_pParaUI->m_txtAngKx->text());
}
void QDistanceItemParaEditWidget::on_m_txtFaultCurrent_editingFinished()
{
	m_pParaUI->m_txtFaultCurrent->setText(CheckDataMinMax(m_pParaUI->m_txtFaultCurrent->text(),20,0,3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT,m_pParaUI->m_txtFaultCurrent->text());
}
void QDistanceItemParaEditWidget::on_m_txtTSetting_editingFinished()
{
	m_pParaUI->m_txtTSetting->setText(CheckDataMinMax(m_pParaUI->m_txtTSetting->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING,m_pParaUI->m_txtTSetting->text());
}
void QDistanceItemParaEditWidget::on_m_txtAbsErr_editingFinished()
{

}
void QDistanceItemParaEditWidget::on_m_txtRelErr_editingFinished()
{

}

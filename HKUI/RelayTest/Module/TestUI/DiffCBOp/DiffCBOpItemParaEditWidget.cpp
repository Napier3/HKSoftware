#include "DiffCBOpItemParaEditWidget.h"
#include "ui_DiffCBOpItemParaEditWidget.h"
#include "SttMultiMacroDiffCBOpParasDefine.h"
#include "../../../../Module/API/GlobalConfigApi.h"

#define isnan(x) ((x) != (x))  //2024.10.17 zhangyq

extern CFont *g_pSttGlobalFont;
QDiffCBOpItemParaEditWidget::QDiffCBOpItemParaEditWidget(QWidget *parent) :
QItemParaEditWidgetBase(parent),m_pParaUI(new Ui::QDiffCBOpItemParaEditWidget)
{
    m_pParaUI->setupUi(this);
    m_nModify = 0;
    //InitUI();
	m_pCurLabel = m_pParaUI->m_pLabCurrent;
	m_pCurCmbAdoptWind = m_pParaUI->m_pCmbFaultLocation;
	InitUI();
	InitLanuage();
}

QDiffCBOpItemParaEditWidget::~QDiffCBOpItemParaEditWidget()
{
    delete m_pParaUI;
}

void QDiffCBOpItemParaEditWidget::InitUI()
{
	m_pParaUI->m_pCmbFaultType->addItems(QStringList() <</*"A相接地"*/g_sLangTxt_Native_GndA << /*"B相接地"*/g_sLangTxt_Native_GndB <</* "C相接地" */g_sLangTxt_Native_GndC << /*"AB短路"*/g_sLangTxt_Native_ShortAB
		<</*"BC短路"*/g_sLangTxt_Native_ShortBC << g_sLangTxt_Native_ShortCA/*"CA短路"*/ <</* "ABC短路"*/g_sLangTxt_Native_ShortABC);
	m_pParaUI->m_pCmbFaultLocation->addItems(QStringList() <</*"高压侧(区内)"*/g_sLangTxt_DiffCBOp_FauleInH <</* "高压侧(区外)" */g_sLangTxt_DiffCBOp_FauleOutH << /*"低压侧(区内)"*/g_sLangTxt_DiffCBOp_FauleInL <</* "低压侧(区外)"*/g_sLangTxt_DiffCBOp_FauleOutL);
}

void QDiffCBOpItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	
    if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTYPE)
    {
        m_pParaUI->m_pCmbFaultType->setCurrentIndex(pData->m_strValue.toInt());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CURENT)
    {
        m_pParaUI->m_pEditCurent->setText(CheckDataMinMax(pData->m_strValue,100.000,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTLOCATION)
    {
        m_pParaUI->m_pCmbFaultLocation->setCurrentIndex(pData->m_strValue.toInt());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_KCAL)
    {
		on_m_pChkKph_clicked(pData->m_strValue.toInt());
        m_pParaUI->m_pChkKph->setChecked(pData->m_strValue.toInt());
		nKph = pData->m_strValue.toInt();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FREP)
    {
        m_pParaUI->m_pEditFrep->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVKPH)
    {
		m_pParaUI->m_pEditTransfHvKph->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999.999, 0, 3));
        //m_pParaUI->m_pEditTransfHvKph->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVVOL)
    {
		m_pParaUI->m_pEditTransfHvVol->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999.999, 0, 3));
       //m_pParaUI->m_pEditTransfHvVol->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVCUR)
    {
		m_pParaUI->m_pEditTransfHvCur->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999.999, 0, 3));
        //m_pParaUI->m_pEditTransfHvCur->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVCT)
    {
		m_pParaUI->m_pEditTransfHvCT->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999.999, 0, 3));
        //m_pParaUI->m_pEditTransfHvCT->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVKVA)
    {
		m_pParaUI->m_pEditTransfHvKVA->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999.999, 0, 3));
        //m_pParaUI->m_pEditTransfHvKVA->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVKPM)
    {
		m_pParaUI->m_pEditTransfMvKpm->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999.999, 0, 3));
        //m_pParaUI->m_pEditTransfMvKpm->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVVOL)
    {
		m_pParaUI->m_pEditTransfMvVol->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999.999, 0, 3));
        //m_pParaUI->m_pEditTransfMvVol->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVCUR)
    {
		m_pParaUI->m_pEditTransfMvCur->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999.999, 0, 3));
        //m_pParaUI->m_pEditTransfMvCur->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVCT)
    {
		m_pParaUI->m_pEditTransfMvCT->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999.999, 0, 3));
        //m_pParaUI->m_pEditTransfMvCT->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVKPL)
    {
		m_pParaUI->m_pEditTransfLvKpl->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999.999, 0, 3));
        //m_pParaUI->m_pEditTransfLvKpl->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVVOL)
    {
		m_pParaUI->m_pEditTransfLvVol->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999.999, 0, 3));
        //m_pParaUI->m_pEditTransfLvVol->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVCUR)
    {
		m_pParaUI->m_pEditTransfLvCur->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999.999, 0, 3));
        //m_pParaUI->m_pEditTransfLvCur->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVCT)
    {
		m_pParaUI->m_pEditTransfLvCT->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999999.999, 0, 3));
        //m_pParaUI->m_pEditTransfLvCT->setText(CheckDataMinMax(pData->m_strValue,100.000,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRSUM)
    {
		m_pParaUI->m_pEditAbsErrSum->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 100.000, 0, 3));
        //m_pParaUI->m_pEditAbsErrSum->setText(CheckDataMinMax(pData->m_strValue,100.000,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRREDUCE)
    {
		m_pParaUI->m_pEditAbsErrReduce->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 100.000, 0, 3));
		//m_pParaUI->m_pEditAbsErrReduce->setText(CheckDataMinMax(pData->m_strValue,100.000,0,3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRRELERR)
    {
		m_pParaUI->m_pEditRelErr->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 100.000, 0, 3));
        //m_pParaUI->m_pEditRelErr->setText(CheckDataMinMax(pData->m_strValue,100.000,0,3));
    }
}


CString QDiffCBOpItemParaEditWidget::CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint)
{
	float fvalue = strValue.toFloat();

	if (fvalue<nMin)
	{
		fvalue = nMin;
	}
	else if (fvalue>nMax)
	{
		fvalue = nMax;
	}
	return QString::number(fvalue, 'f', nAfterPoint);
}

void QDiffCBOpItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
{
	QItemParaEditWidgetBase::UpdateParas(pSttMacroTest);

	if (m_pSingleMacroRef == NULL)
	{
		return;
	}
	if (m_pCurrMacroTest_External != NULL)
	{
		CSttMacroTestParaDatas *pDstDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
		CheckAllPresence(pDstDatas_External);
	}

	CSttMacroTestParaDatas *pDstDatas = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	CheckAllPresence(pDstDatas);
	POS pos = pDstDatas->GetHeadPosition();

	while (pos != NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pDstDatas->GetNext(pos);
		SetValueToPage(pData);
	}
	if (m_pCurrMacroTest_External == NULL)
	{
		return;
	}
}

void QDiffCBOpItemParaEditWidget::on_m_pCmbFaultType_currentIndexChanged(int index)
{
    CString strTmp;
    strTmp.setNum(index);
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTYPE,strTmp);
}

void QDiffCBOpItemParaEditWidget::on_m_pCmbFaultLocation_currentIndexChanged(int index)
{
    CString strTmp;
    strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTLOCATION, strTmp);
    QString strImagePath;
    if (index == 0)
    {
#ifdef _PSX_QT_WINDOWS_
        strImagePath = _P_GetResourcePath();
        strImagePath = strImagePath + _T("DiffCBOpHIn.png");
#else
        strImagePath = ":/ctrls/images/DiffCBOpHIn.png";
#endif
    }
    else if (index == 1)
    {
#ifdef _PSX_QT_WINDOWS_
        strImagePath = _P_GetResourcePath();
        strImagePath = strImagePath + _T("DiffCBOpHOut.png");
#else
        strImagePath = ":/ctrls/images/DiffCBOpHOut.png";
#endif
    }
    else if (index == 2)
    {
#ifdef _PSX_QT_WINDOWS_
        strImagePath = _P_GetResourcePath();
        strImagePath = strImagePath + _T("DiffCBOpLIn.png");
#else
        strImagePath = ":/ctrls/images/DiffCBOpLIn.png";
#endif
    }
    else if (index == 3)
    {
#ifdef _PSX_QT_WINDOWS_
        strImagePath = _P_GetResourcePath();
        strImagePath = strImagePath + _T("DiffCBOpLOut.png");
#else
        strImagePath = ":/ctrls/images/DiffCBOpLOut.png";
#endif
    }
    emit sig_strImagePath(strImagePath);
}

void QDiffCBOpItemParaEditWidget::on_m_pEditCurent_editingFinished()
{
    m_pParaUI->m_pEditCurent->setText(CheckDataMinMax(m_pParaUI->m_pEditCurent->text(),100.000,0,3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CURENT,m_pParaUI->m_pEditCurent->text());
}

void QDiffCBOpItemParaEditWidget::on_m_pEditFrep_editingFinished()
{
    m_pParaUI->m_pEditFrep->setText(CheckDataMinMax(m_pParaUI->m_pEditFrep->text(),999.999,0,3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FREP,m_pParaUI->m_pEditFrep->text());
}

void QDiffCBOpItemParaEditWidget::on_m_pEditTransfHvKph_editingFinished()
{
	if (m_pParaUI->m_pEditTransfHvKph->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditTransfHvKph)->IsSetting())
		{
			return;
		}
	}
	m_pParaUI->m_pEditTransfHvKph->setText(CheckDataMinMax(m_pParaUI->m_pEditTransfHvKph->text(), 999999.999, 0, 3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVKPH,m_pParaUI->m_pEditTransfHvKph->text());
	AutoCalcKpx();
}
void QDiffCBOpItemParaEditWidget::on_m_pEditTransfHvVol_editingFinished()
{
	if (m_pParaUI->m_pEditTransfHvVol->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditTransfHvVol)->IsSetting())
		{
			return;
		}
	}
	m_pParaUI->m_pEditTransfHvVol->setText(CheckDataMinMax(m_pParaUI->m_pEditTransfHvVol->text(), 999999.999, 0, 3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVVOL,m_pParaUI->m_pEditTransfHvVol->text());
	AutoCalcKpx();
}
void QDiffCBOpItemParaEditWidget::on_m_pEditTransfHvCur_editingFinished()
{
	if (m_pParaUI->m_pEditTransfHvCur->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditTransfHvCur)->IsSetting())
		{
			return;
		}
	}
	m_pParaUI->m_pEditTransfHvCur->setText(CheckDataMinMax(m_pParaUI->m_pEditTransfHvCur->text(), 999999.999, 0, 3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVCUR,m_pParaUI->m_pEditTransfHvCur->text());
	AutoCalcKpx();
}
void QDiffCBOpItemParaEditWidget::on_m_pEditTransfHvCT_editingFinished()
{
	if (m_pParaUI->m_pEditTransfHvCT->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditTransfHvCT)->IsSetting())
		{
			return;
		}
	}
	m_pParaUI->m_pEditTransfHvCT->setText(CheckDataMinMax(m_pParaUI->m_pEditTransfHvCT->text(), 999999.999, 0, 3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVCT,m_pParaUI->m_pEditTransfHvCT->text());
	AutoCalcKpx();
}
void QDiffCBOpItemParaEditWidget::on_m_pEditTransfHvKVA_editingFinished()
{
	if (m_pParaUI->m_pEditTransfHvKVA->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditTransfHvKVA)->IsSetting())
		{
			return;
		}
	}
	m_pParaUI->m_pEditTransfHvKVA->setText(CheckDataMinMax(m_pParaUI->m_pEditTransfHvKVA->text(), 999999.999, 0, 3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVKVA,m_pParaUI->m_pEditTransfHvKVA->text());
	AutoCalcKpx();
}

void QDiffCBOpItemParaEditWidget::on_m_pEditTransfMvKpm_editingFinished()
{
	if (m_pParaUI->m_pEditTransfMvKpm->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditTransfMvKpm)->IsSetting())
		{
			return;
		}
	}
	m_pParaUI->m_pEditTransfMvKpm->setText(CheckDataMinMax(m_pParaUI->m_pEditTransfMvKpm->text(), 999999.999, 0, 3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVKPM,m_pParaUI->m_pEditTransfMvKpm->text());
	AutoCalcKpx();
}
void QDiffCBOpItemParaEditWidget::on_m_pEditTransfMvVol_editingFinished()
{
	if (m_pParaUI->m_pEditTransfMvVol->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditTransfMvVol)->IsSetting())
		{
			return;
		}
	}
	m_pParaUI->m_pEditTransfMvVol->setText(CheckDataMinMax(m_pParaUI->m_pEditTransfMvVol->text(), 999999.999, 0, 3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVVOL,m_pParaUI->m_pEditTransfMvVol->text());
	AutoCalcKpx();
}
void QDiffCBOpItemParaEditWidget::on_m_pEditTransfMvCur_editingFinished()
{
	if (m_pParaUI->m_pEditTransfMvCur->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditTransfMvCur)->IsSetting())
		{
			return;
		}
	}
	m_pParaUI->m_pEditTransfMvCur->setText(CheckDataMinMax(m_pParaUI->m_pEditTransfMvCur->text(), 999999.999, 0, 3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVCUR,m_pParaUI->m_pEditTransfMvCur->text());
	AutoCalcKpx();
}
void QDiffCBOpItemParaEditWidget::on_m_pEditTransfMvCT_editingFinished()
{
	if (m_pParaUI->m_pEditTransfMvCT->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditTransfMvCT)->IsSetting())
		{
			return;
		}
	}
	m_pParaUI->m_pEditTransfMvCT->setText(CheckDataMinMax(m_pParaUI->m_pEditTransfMvCT->text(), 999999.999, 0, 3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVCT,m_pParaUI->m_pEditTransfMvCT->text());
	AutoCalcKpx();
}
void QDiffCBOpItemParaEditWidget::on_m_pEditTransfLvKpl_editingFinished()
{
	if (m_pParaUI->m_pEditTransfLvKpl->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditTransfLvKpl)->IsSetting())
		{
			return;
		}
	}
	m_pParaUI->m_pEditTransfLvKpl->setText(CheckDataMinMax(m_pParaUI->m_pEditTransfLvKpl->text(), 999999.999, 0, 3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVKPL,m_pParaUI->m_pEditTransfLvKpl->text());
	AutoCalcKpx();
}
void QDiffCBOpItemParaEditWidget::on_m_pEditTransfLvVol_editingFinished()
{
	if (m_pParaUI->m_pEditTransfLvVol->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditTransfLvVol)->IsSetting())
		{
			return;
		}
	}
	m_pParaUI->m_pEditTransfLvVol->setText(CheckDataMinMax(m_pParaUI->m_pEditTransfLvVol->text(), 999999.999, 0, 3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVVOL,m_pParaUI->m_pEditTransfLvVol->text());
	AutoCalcKpx();
}
void QDiffCBOpItemParaEditWidget::on_m_pEditTransfLvCur_editingFinished()
{
	if (m_pParaUI->m_pEditTransfLvCur->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditTransfLvCur)->IsSetting())
		{
			return;
		}
	}
	m_pParaUI->m_pEditTransfLvCur->setText(CheckDataMinMax(m_pParaUI->m_pEditTransfLvCur->text(), 999999.999, 0, 3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVCUR,m_pParaUI->m_pEditTransfLvCur->text());
	AutoCalcKpx();
}
void QDiffCBOpItemParaEditWidget::on_m_pEditTransfLvCT_editingFinished()
{
	if (m_pParaUI->m_pEditTransfLvCT->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditTransfLvCT)->IsSetting())
		{
			return;
		}
	}
	m_pParaUI->m_pEditTransfLvCT->setText(CheckDataMinMax(m_pParaUI->m_pEditTransfLvCT->text(), 999999.999, 0, 3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVCT,m_pParaUI->m_pEditTransfLvCT->text());
	AutoCalcKpx();
}
void QDiffCBOpItemParaEditWidget::on_m_pEditAbsErrSum_editingFinished()
{
	if (m_pParaUI->m_pEditAbsErrSum->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditAbsErrSum)->IsSetting())
		{
			return;
		}
	}
    m_pParaUI->m_pEditAbsErrSum->setText(CheckDataMinMax(m_pParaUI->m_pEditAbsErrSum->text(),100.000,0,3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRSUM,m_pParaUI->m_pEditAbsErrSum->text());

	return;
}
void QDiffCBOpItemParaEditWidget::on_m_pEditAbsErrReduce_editingFinished()
{
	if (m_pParaUI->m_pEditAbsErrReduce->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditAbsErrReduce)->IsSetting())
		{
			return;
		}
	}
    m_pParaUI->m_pEditAbsErrReduce->setText(CheckDataMinMax(m_pParaUI->m_pEditAbsErrReduce->text(),100.000,0,3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRREDUCE,m_pParaUI->m_pEditAbsErrReduce->text());

	return;
}
void QDiffCBOpItemParaEditWidget::on_m_pEditRelErr_editingFinished()
{
	if (m_pParaUI->m_pEditRelErr->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pParaUI->m_pEditRelErr)->IsSetting())
		{
			return;
		}
	}
    m_pParaUI->m_pEditRelErr->setText(CheckDataMinMax(m_pParaUI->m_pEditRelErr->text(),100.000,0,3));
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRRELERR,m_pParaUI->m_pEditRelErr->text());

	return;
}

void QDiffCBOpItemParaEditWidget::on_m_pChkKph_clicked(bool nState)
{
    CString strTmp;
    strTmp.setNum(nState);
	m_pParaUI->m_pChkKph->setChecked(nState);
	nKph = nState;
    UpdatePara(STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_KCAL, strTmp);
	if (nState)
	{
		m_pParaUI->m_pEditTransfHvKph->setEnabled(true);
		m_pParaUI->m_pEditTransfMvKpm->setEnabled(true);
		m_pParaUI->m_pEditTransfLvKpl->setEnabled(true);
		m_pParaUI->m_pEditTransfHvVol->setEnabled(false);
		m_pParaUI->m_pEditTransfMvVol->setEnabled(false);
		m_pParaUI->m_pEditTransfLvVol->setEnabled(false);
		m_pParaUI->m_pEditTransfHvCur->setEnabled(false);
		m_pParaUI->m_pEditTransfMvCur->setEnabled(false);
		m_pParaUI->m_pEditTransfLvCur->setEnabled(false);
		m_pParaUI->m_pEditTransfHvCT->setEnabled(false);
		m_pParaUI->m_pEditTransfMvCT->setEnabled(false);
		m_pParaUI->m_pEditTransfLvCT->setEnabled(false);
		m_pParaUI->m_pEditTransfHvKVA->setEnabled(false);
		AutoCalcKpx();
	}
	else
	{
		m_pParaUI->m_pEditTransfHvKph->setEnabled(false);
		m_pParaUI->m_pEditTransfMvKpm->setEnabled(false);
		m_pParaUI->m_pEditTransfLvKpl->setEnabled(false);
		m_pParaUI->m_pEditTransfHvVol->setEnabled(true);
		m_pParaUI->m_pEditTransfMvVol->setEnabled(true);
		m_pParaUI->m_pEditTransfLvVol->setEnabled(true);
		m_pParaUI->m_pEditTransfHvCur->setEnabled(true);
		m_pParaUI->m_pEditTransfMvCur->setEnabled(true);
		m_pParaUI->m_pEditTransfLvCur->setEnabled(true);
		m_pParaUI->m_pEditTransfHvCT->setEnabled(true);
		m_pParaUI->m_pEditTransfMvCT->setEnabled(true);
		m_pParaUI->m_pEditTransfLvCT->setEnabled(true);
		m_pParaUI->m_pEditTransfHvKVA->setEnabled(true);
	}
//	AutoCalcKpx();
}

void QDiffCBOpItemParaEditWidget::UpdatePara(CString strID,CString strValue)
{
	CSttMacroTestParaDatas *pSttMacroTestParaDatas_External = NULL;

	if (m_pSingleMacroRef == NULL)
	{
		return;
	}
	if (m_pCurrMacroTest_External != NULL)
	{
		pSttMacroTestParaDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	}

	CSttMacroTestParaDatas *pSttMacroTestParaDatas_Inner = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	CSttMacroTestParaData *pDataInner = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(strID);

	if (pDataInner != NULL)
	{
		pDataInner->m_strValue = strValue;
		if (pSttMacroTestParaDatas_External != NULL)
		{
			pSttMacroTestParaDatas_External->SetDataValue(strID, strValue, TRUE);
			emit sig_UpdateCurrSelGridData(m_pCurrMacroTest_External);
		}
	}

	POS pos = pSttMacroTestParaDatas_Inner->GetHeadPosition();

	while (pos)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->GetNext(pos);
		if (pData != NULL)
		{
			if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ADOPTWIND)
			{
				m_nAdoptWind = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_INSEL)
			{
				m_nInSel = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_INSET)
			{
				m_fIbase = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_COORDINATE)
			{
				m_bMinAxis = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_PHCORRECTMODE)
			{
				m_nPhCorrectMode = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ILOADPH)
			{
				m_nIbiasCal = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDH)
			{
				m_nWindH = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDM)
			{
				m_nWindM = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_WINDL)
			{
				m_nWindL = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K1)
			{
				m_nK1 = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_K2)
			{
				m_nK2 = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSGROUPMODE)
			{
				m_nConnectMode = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTYPE)
			{
				m_nPhase = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CT)
			{
				m_nCT = CString_To_long(pData->m_strValue);
			}
			else if (pData->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_BALANCETERMS)
			{
				m_nBalanceterms = CString_To_long(pData->m_strValue);
			}
		}
	}
}

void QDiffCBOpItemParaEditWidget::InitLanuage()
{
	m_pParaUI->m_pLabFaultType->setText(g_sLangTxt_State_FaultType);
	m_pParaUI->m_pLabFaultLocation->setText(g_sLangTxt_DiffCBOp_FaultLocation);
	m_pParaUI->m_pLabCurrent->setText(g_sLangTxt_Native_Current + "(In)");
	m_pParaUI->m_pLabFrep->setText(g_sLangTxt_Native_Freq);
	m_pParaUI->m_pGroupSystemParas->setTitle(g_sLangTxt_SystemPara);
	m_pParaUI->m_pLabTransfHvKph->setText(g_sLangTxt_DiffCBOp_TransfHvKph);
	m_pParaUI->m_pLabTransfHvKpm->setText(g_sLangID_DiffCBOp_TransfHvKpm);
	m_pParaUI->m_pLabTransfHvKpl->setText(g_sLangTxt_DiffCBOp_TransfHvKpl);
	m_pParaUI->m_pLabBalCoeff->setText(g_sLangTxt_Native_BalCoeff);
	m_pParaUI->m_pLabVnom->setText(g_sLangTxt_Report_Vnom + "(kv)");
	m_pParaUI->m_pLabEDCurrent->setText(g_sLangTxt_Native_EDCurrent + "(A)");
	m_pParaUI->m_pLabCT->setText(g_sLangTxt_CT);
	m_pParaUI->m_pLabTransfRatedCapacity->setText(g_sLangTxt_DiffCBOp_TransfRatedCapacity + "(MVA)");
	m_pParaUI->m_pChkKph->setText(g_sLangTxt_DiffCBOp_SetKph);
	m_pParaUI->m_pLabAbsErr->setText(g_sLangTxt_StateEstimate_AbsError + "(s)+");
	m_pParaUI->m_pLabAbsErrMinus->setText(g_sLangTxt_StateEstimate_AbsError + "(s)-");
	m_pParaUI->m_pLabRelErr->setText(g_sLangTxt_StateEstimate_RelError_Percent);
}

void QDiffCBOpItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTYPE);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTLOCATION);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_CURENT);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FREP);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVKPH);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVVOL);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVCUR);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVCT);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFHVKVA);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVKPM);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVVOL);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVCUR);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFMVCT);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVKPL);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVVOL);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVCUR);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TRANSFLVCT);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRSUM);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRREDUCE);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ABSERRRELERR);
    CheckForPresence(pParas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_KCAL);
}

void QDiffCBOpItemParaEditWidget::CheckForPresence(CExBaseList *pParas,CString strID)
{
    if(pParas == NULL)
        return;
    CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pParas->FindByID(strID);
    if(pData == NULL)
    {
        CSttMacroTestParaData *pNew = new CSttMacroTestParaData();
        pNew->m_strName = strID;
        pNew->m_strID = strID;
        pNew->m_strValue = STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_DEFAULT;
        pParas->AddNewChild(pNew);
    }
}

CExBaseList * QDiffCBOpItemParaEditWidget::GetMacroTestParaDatas()
{
    if(m_pCurrMacroTest_External != NULL)
    {
        return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
    }
    return NULL;
}
// CExBaseList * QDiffCBOpItemParaEditWidget::GetMacroTestParaDatas_Inner()
// {
//     if(m_oSttMacroTest_Inner.GetCount() != 0)
//     {
//         return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//     }
//     return NULL;
// }


void QDiffCBOpItemParaEditWidget::AutoCalcKpx()
{
	if (nKph == 0)//自动计算平衡系数
	{
		float fValue = 0.000f;
		m_oDiffCBOpCalTool.Init();

		if (m_nAdoptWind == 0)
		{
			fValue = m_pParaUI->m_pEditTransfHvKph->GetText().toFloat();
		}
		else if (m_nAdoptWind == 1)
		{
			fValue = m_pParaUI->m_pEditTransfMvKpm->GetText().toFloat();
		}
		else if (m_nAdoptWind == 2)
		{
			fValue = m_pParaUI->m_pEditTransfLvKpl->GetText().toFloat();
		}

		m_oDiffCBOpCalTool.InitParas6I(m_nInSel, m_fIbase, NULL, m_bMinAxis, m_nPhCorrectMode, m_nIbiasCal,
			m_nWindH, m_nWindM, m_nWindL, m_nAdoptWind, m_nK1, m_nK2, m_nConnectMode, m_nPhase, m_nCT, m_nBalanceterms);

		m_oDiffCBOpCalTool.InitParas_AutoCalBalanceFactors(m_pParaUI->m_pEditTransfHvKVA->GetText().toFloat(), m_pParaUI->m_pEditTransfHvVol->GetText().toFloat(), m_pParaUI->m_pEditTransfMvVol->GetText().toFloat(),
			m_pParaUI->m_pEditTransfLvVol->GetText().toFloat(), m_pParaUI->m_pEditTransfHvCT->GetText().toFloat(), 1.0f, m_pParaUI->m_pEditTransfMvCT->GetText().toFloat(),
			1.0f, m_pParaUI->m_pEditTransfLvCT->GetText().toFloat(), 1.0f);
		m_oDiffCBOpCalTool.GetKps(m_fKph, m_fKpm, m_fKpl);

		if (m_nAdoptWind == 0)
		{
			if (fValue != m_fKpm)
			{
				m_fKpm = fValue;
			}
		}

		else if (m_nAdoptWind == 1)
		{
			m_fKpm = m_fKpl;

			if (fValue != m_fKpl)
			{
				m_fKpl = fValue;
			}
		}
		else if (m_nAdoptWind == 2)
		{
			m_fKpm = m_fKph;

			if (m_fKph != fValue)
			{
				m_fKph = fValue;
			}
		}
		if (!isnan(m_fKph) && !isinf(m_fKph))//判断是否为有效数字
		{
		m_pParaUI->m_pEditTransfHvKph->setText(CheckDataMinMax(QString::number(m_fKph), 999.999, 0, 3));			//高压侧差动平衡系数
		}
		else
		{
			m_pParaUI->m_pEditTransfHvKph->setText("0.000");
		}

		if (!isnan(m_fKpm) && !isinf(m_fKpm))//判断是否为有效数字
		{
		m_pParaUI->m_pEditTransfMvKpm->setText(CheckDataMinMax(QString::number(m_fKpm), 999.999, 0, 3));			//中压侧差动平衡系数
		}
		else
		{
			m_pParaUI->m_pEditTransfMvKpm->setText("0.000");
		}

		if (!isnan(m_fKpl) && !isinf(m_fKpl))//判断是否为有效数字
		{
		m_pParaUI->m_pEditTransfLvKpl->setText(CheckDataMinMax(QString::number(m_fKpl), 999.999, 0, 3));			//低压侧差动平衡系数
	}
		else
		{
			m_pParaUI->m_pEditTransfLvKpl->setText("0.000");
		}
	}
}

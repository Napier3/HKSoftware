#include "DistanceItemParaEditWidget.h"
#include "ui_DistanceItemParaEditWidget.h"
#include "../../../../AutoTest/Module/Characteristic/CharacteristicGlobal.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../../../AutoTest/Module/Characteristic/Characteristics.h"
#include "../../UI/SttTestCntrFrameApi.h"
QDistanceItemParaEditWidget::QDistanceItemParaEditWidget(QWidget *parent) :
	QItemParaEditWidgetBase(parent),
    m_pParaUI(new Ui::QDistanceItemParaEditWidget)
{
    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QDistanceItemParaEditWidget::QDistanceItemParaEditWidge : 1"));

    m_pParaUI->setupUi(this);
    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QDistanceItemParaEditWidget::QDistanceItemParaEditWidge : 2"));
        InitUI();
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QDistanceItemParaEditWidget::QDistanceItemParaEditWidge : 3"));
        InitLanuage();
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QDistanceItemParaEditWidget::QDistanceItemParaEditWidge : 4"));
        ConnectAll_SigSlot();
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QDistanceItemParaEditWidget::QDistanceItemParaEditWidge : 5"));
}

QDistanceItemParaEditWidget::~QDistanceItemParaEditWidget()
{
    delete m_pParaUI;
}
void QDistanceItemParaEditWidget::InitUI()
{
	
	m_pParaUI->m_cmb_ErrorDirc->addItems(QStringList()<<g_sLangTxt_CBOperate_Reverse/*("反向")*/<<g_sLangTxt_CBOperate_Positive/*("正向")*/);
	m_pParaUI->m_cmb_ErrorNature->addItems(QStringList()<<g_sLangTxt_CBOperate_Instan/*("瞬时")*/<<g_sLangTxt_CBOperate_Perpetual/*("永久")*/);
	m_pParaUI->m_cmbK0Mode->addItems(QStringList()<<_T("|K0|,Phi(K0)")<<_T("RERL,XEXL")<<_T("|Z0/Z1|,Phi(Z0/Z1)"));

        //CExBaseList  *pListTemp = (CExBaseList  *)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_PARAS_DATATYPE_ID_SystemFault);//故障类型
        //m_pParaUI->m_cmb_ErrorType->SetBaseList(pListTemp);
}
void QDistanceItemParaEditWidget::InitLanuage()
{
	//if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
	//{
	//	return;
	//}
	CString strtemp;
	xlang_SetLangStrToWidget(m_pParaUI->m_labErrType, g_sLangID_State_FaultType, XLang_Ctrls_QLabel);//故障类型:
	xlang_SetLangStrToWidget(m_pParaUI->m_labZSetting, g_sLangID_Distance_ZImpValue, XLang_Ctrls_QLabel);//阻抗(Ω):
	xlang_SetLangStrToWidget(m_pParaUI->m_labZAng, g_sLangID_Gradient_ImpAngle, XLang_Ctrls_QLabel);//阻抗角(°):
	xlang_SetLangStrToWidget(m_pParaUI->m_labRate,g_sLangID_Distance_Percent, XLang_Ctrls_QLabel);//百分比(%):
	xlang_SetLangStrToWidget(m_pParaUI->m_labZoneType, g_sLangID_Distance_ZoneSel, XLang_Ctrls_QLabel);//区段选择:
	xlang_SetLangStrToWidget(m_pParaUI->m_labPlus, g_sLangID_ActionTime_AbsErrPos, XLang_Ctrls_QLabel);//绝对误差(s)+:
	xlang_SetLangStrToWidget(m_pParaUI->m_labMinus, g_sLangID_ActionTime_AbsErrNeg, XLang_Ctrls_QLabel);//绝对误差(s)-:
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_RelError_Percent);//相对误差(%):
	if (strtemp.Find(":") == -1)
	{
		strtemp += ":";
	}
	m_pParaUI->m_labRelErr->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_State_ZeroCoeff);//零序补偿系数:
	if (strtemp.Find(":") == -1)
	{
		strtemp += ":";
	}
	m_pParaUI->m_labK0Mode->setText(strtemp);
	xlang_SetLangStrToWidget(m_pParaUI->m_lablne_TSetting, g_sLangID_Distance_TSetting, XLang_Ctrls_QLabel);//时间定值(s):
	xlang_SetLangStrToWidget(m_pParaUI->m_lab_ErrorNature, g_sLangID_Native_FaultProp, XLang_Ctrls_QLabel);//故障性质:
	
	xlang_GetLangStrByFile(strtemp, g_sLangID_Gradient_FailDirect);//故障方向:
	if (strtemp.Find(":") == -1)
	{
		strtemp += ":";
	}
	m_pParaUI->m_lab_ErrorDirc->setText(strtemp);
	xlang_SetLangStrToWidget(m_pParaUI->m_labFaultCurrent, g_sLangID_State_ShortI, XLang_Ctrls_QLabel);//短路电流(A):
}
void QDistanceItemParaEditWidget::ConnectAll_SigSlot()
{
	connect(m_pParaUI->m_cmb_ZoneType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ZoneTypeCurrentIndexChanged(int)));
}
void QDistanceItemParaEditWidget::DisConnectAll_SigSlot()
{
	disconnect(m_pParaUI->m_cmb_ZoneType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ZoneTypeCurrentIndexChanged(int)));
}
void QDistanceItemParaEditWidget::SetPageFont(CFont oPageFont)
{//20240807 luozibing 测试字体使用
	/*CString strFont;
	strFont.Format(_T("%d,%d;"), oPageFont.pixelSize(), oPageFont.pointSize());
	CFont oLeft;
	oLeft.setPixelSize(oPageFont.pixelSize()-1);
	m_pParaUI->m_labErrType->setFont(oLeft);
	m_pParaUI->m_cmb_ErrorType->setFont(oLeft);
	m_pParaUI->m_labZSetting->setFont(oLeft);
	m_pParaUI->m_txtZSetting->setFont(oLeft);
	m_pParaUI->m_labZAng->setFont(oLeft);
	m_pParaUI->m_txtZAng->setFont(oLeft);
	m_pParaUI->m_labR->setFont(oLeft);
	m_pParaUI->m_txtR->setFont(oLeft);
	m_pParaUI->m_labX->setFont(oLeft);
	m_pParaUI->m_txtX->setFont(oLeft);
	m_pParaUI->m_labRate->setFont(oLeft);
	m_pParaUI->m_txtRate->setFont(oLeft);
	m_pParaUI->m_labZoneType->setFont(oLeft);
	m_pParaUI->m_cmb_ZoneType->setFont(oLeft);
	m_pParaUI->m_labPlus->setFont(oLeft);
	m_pParaUI->m_txtPlus->setFont(oLeft);
	m_pParaUI->m_labRelErr->setFont(oLeft);
	m_pParaUI->m_txtRelErr->setFont(oLeft);

	oLeft.setPixelSize(oPageFont.pixelSize() - 2);
	m_pParaUI->m_labFaultCurrent->setFont(oLeft);
	m_pParaUI->m_txtFaultCurrent->setFont(oLeft);
	m_pParaUI->m_lab_ErrorDirc->setFont(oLeft);
	m_pParaUI->m_cmb_ErrorDirc->setFont(oLeft);
	m_pParaUI->m_lab_ErrorNature->setFont(oLeft);
	m_pParaUI->m_cmb_ErrorNature->setFont(oLeft);
	m_pParaUI->m_lablne_TSetting->setFont(oLeft);
	m_pParaUI->m_txtTSetting->setFont(oLeft);
	m_pParaUI->m_labK0Mode->setFont(oLeft);
	m_pParaUI->m_cmbK0Mode->setFont(oLeft);
	m_pParaUI->m_labKlKr->setFont(oLeft);
	m_pParaUI->m_txtKlKr->setFont(oLeft);
	m_pParaUI->m_labAngKx->setFont(oLeft);
	m_pParaUI->m_txtAngKx->setFont(oLeft);
	m_pParaUI->m_labMinus->setFont(oLeft);
	m_pParaUI->m_txtMinus->setFont(oLeft);
*/
}
void QDistanceItemParaEditWidget::SetValueToPage(CSttMacroTestParaData *pData)
{
	if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE)
	{
		m_pParaUI->m_cmbK0Mode->setCurrentIndex(CString_To_long(pData->m_strValue));
		SetModeText(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR)
	{		
		//m_pParaUI->m_txtKlKr->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtKlKr->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));//20240722 huangliang 设置对象地址
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX)
	{
		//m_pParaUI->m_txtAngKx->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		m_pParaUI->m_txtAngKx->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, 999.999, 0, 3));//20240722 huangliang 设置对象地址
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE)
	{
		UpdZoneTypeCmbParas(pData,CString_To_long(pData->m_strValue));
		//m_pParaUI->m_cmb_ErrorType->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE)
	{
		double nrate = CString_To_double(pData->m_strValue);
		CString strTmp;
		strTmp.setNum(nrate*100);
		m_pParaUI->m_txtRate->setText(CheckDataMinMax(strTmp,0,0,1));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT)
	{
		m_pParaUI->m_txtFaultCurrent->setText(CheckDataMinMax(pData->m_strValue,20,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTDIRECTION)
	{
		m_pParaUI->m_cmb_ErrorDirc->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE1)
	{
		m_pParaUI->m_cmb_ErrorNature->setCurrentIndex(CString_To_long(pData->m_strValue));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING)
	{
		m_pParaUI->m_txtTSetting->setText(CheckDataMinMax(pData->m_strValue,999.999,0,3));
		if (pData->m_strValue != m_pParaUI->m_txtTSetting->text())
		{
			UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING,m_pParaUI->m_txtTSetting->text());
		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS)
	{
		m_pParaUI->m_txtPlus->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS)
	{
		m_pParaUI->m_txtMinus->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR)
	{
		m_pParaUI->m_txtRelErr->setText(CheckDataMinMax(pData->m_strValue,100,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING)
	{
		//20240809 luozibing 根据ZSetting和Rate计算出阻抗值
		CSttMacroTestParaDatas *pParent = (CSttMacroTestParaDatas *)pData->GetParent();
		CSttMacroTestParaData *pRate = (CSttMacroTestParaData*)pParent->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
		double dImp = CString_To_double(pData->m_strValue)*CString_To_double(pRate->m_strValue);
		CString strImp;
		strImp.Format("%lf", dImp);
		m_pParaUI->m_txtZSetting->setText(CheckDataMinMax(strImp, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));

		//通过阻抗值和角阻抗计算出R、X
		CSttMacroTestParaData *pZAng = (CSttMacroTestParaData*)pParent->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
		m_pParaUI->m_txtZAng->setText(CheckDataMinMax(pZAng->m_strValue, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));//20241008 luozibing 角度保留2位小数
		CString strNewR, StrNewX;
		CheckRxValue(strNewR, StrNewX, m_pParaUI->m_txtZSetting->text(), m_pParaUI->m_txtZAng->text());
		m_pParaUI->m_txtR->setText(CheckDataMinMax(strNewR, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
		m_pParaUI->m_txtX->setText(CheckDataMinMax(StrNewX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
		UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETTING, m_pParaUI->m_txtR->text());
		UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETTING, m_pParaUI->m_txtX->text());
//		//20240722 huangliang  设置对象地址
//		m_pParaUI->m_txtZSetting->UpdateObjectText(pData, CheckDataMinMax(pData->m_strValue, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3));
//		CString sValue = m_pParaUI->m_txtZSetting->GetValue();
//		if (pData->m_strValue != sValue)
//		{
//			UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING, sValue);
//		}
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE)
	{//20240905 luozibing 区段和故障类型一起设置
		/*m_pParaUI->m_cmb_ZoneType->setCurrentIndex(CString_To_long(pData->m_strValue));
		UpdateBtnEnable(m_pParaUI->m_cmb_ZoneType->currentText() == g_sLangTxt_Distance_ZoneLine);*/
	}
}
void QDistanceItemParaEditWidget::UpdateBtnEnable(BOOL bEnable)
{
	m_pParaUI->m_txtTSetting->setEnabled(bEnable);
	m_pParaUI->m_txtPlus->setEnabled(bEnable);
	m_pParaUI->m_txtMinus->setEnabled(bEnable);
	m_pParaUI->m_txtRelErr->setEnabled(bEnable);
}
void QDistanceItemParaEditWidget::UpdateParas(CSttMacroTest *pSttMacroTest)
{//20240620 luozibing 更新数据 将最新链表数据更新到页面
	QItemParaEditWidgetBase::UpdateParas(pSttMacroTest);

	if (m_pSingleMacroRef == NULL)
	{
		return;
	}

	if(m_pCurrMacroTest_External != NULL)
	{
		CSttMacroTestParaDatas *pDstDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
		CheckAllPresence(pDstDatas_External);
	}

	CSttMacroTestParaDatas *pDstDatas = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	CheckAllPresence(pDstDatas);
	POS pos = pDstDatas->GetHeadPosition();
	while (pos!= NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pDstDatas->GetNext(pos);
		SetValueToPage(pData);
	}
	if (m_pCurrMacroTest_External == NULL)
	{
		return;
	}
	update();
}

void QDistanceItemParaEditWidget::on_m_cmbK0Mode_currentIndexChanged(int index)
{
	SetModeText(index);
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE,strTmp);
}
void QDistanceItemParaEditWidget::SetModeText(int nIndex)
{//20240807 luozibing 根据8.3需要优化的内容添加 :
	CString strTmp = m_pParaUI->m_cmbK0Mode->itemText(nIndex);
	QStringList words = strTmp.split(",");
	CString strShow = words[0];
	strShow += ":";
	m_pParaUI->m_labKlKr->setText(strShow);
	strShow = words[1];
	strShow += ":";
	m_pParaUI->m_labAngKx->setText(strShow);
}
void QDistanceItemParaEditWidget::on_m_cmb_ErrorType_currentIndexChanged(int index)
{
//20240906 luozibing 更新故障类型时刷新区段显示
	if (m_pSingleMacroRef == NULL)
	{
		return;
	}
	CString strTmp;
	strTmp.setNum(index);
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE, strTmp);

	CSttMacroTestParaDatas *pSttMacroTestParaDatas_Inner = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	if (pSttMacroTestParaDatas_Inner == NULL)
	{
		return;
	}
	CSttMacroTestParaData *pDataInner = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
	UpdZoneTypeCmbParas(pDataInner, CString_To_long(pDataInner->m_strValue));
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
void QDistanceItemParaEditWidget::slot_ZoneTypeCurrentIndexChanged(int index)
{
	if (index == -1)
	{
		return;
	}
	UpdateBtnEnable(m_pParaUI->m_cmb_ZoneType->currentText() == g_sLangTxt_Distance_ZoneLine);
	CString strTmp;
	CExBaseList *pZoneType = m_pParaUI->m_cmb_ZoneType->GetBaseList();
	if (pZoneType == NULL)
		return;
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE, pZoneType->GetAt(index)->m_strID);

	GetZSettingValueFromParas();
}
CString QDistanceItemParaEditWidget::GetParaDataByID(CString strID)
{//20240809 luozibing 根据ID找到ID对应的值,选中测试项时从选中项查找，否则从_Inner中查找
	CSttMacroTestParaDatas *pSttMacroTestParaDatas_External = NULL;
	CSttMacroTestParaData *pData;
	if (m_pSingleMacroRef == NULL)
	{
		return "";
	}
	if (m_pCurrMacroTest_External != NULL)
	{
		pSttMacroTestParaDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
		pData = (CSttMacroTestParaData *)pSttMacroTestParaDatas_External->FindByID(strID);
	}
	else
	{
		CSttMacroTestParaDatas *pSttMacroTestParaDatas_Inner = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
		pData = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(strID);
	}
	if (pData != NULL)
	{
		return pData->m_strValue;
	}

	return "";
}
void QDistanceItemParaEditWidget::UpdatePara(CString strID,CString strValue)
{
	CSttMacroTestParaDatas *pSttMacroTestParaDatas_External = NULL;

	if (m_pSingleMacroRef == NULL)
	{
		return;
	}
	if(m_pCurrMacroTest_External != NULL)
	{
		pSttMacroTestParaDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	}

	CSttMacroTestParaDatas *pSttMacroTestParaDatas_Inner = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	CSttMacroTestParaData *pDataInner = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(strID);

	if(pDataInner != NULL)
	{
		if(strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE)
		{
			CString strTmp;
			strTmp.setNum(CString_To_double(strValue)/ 100);
			strValue = strTmp;//20240820 luozibing 保存Rate数据到链表时不保留小数位数
			//strValue = CheckDataMinMax(strTmp,0,0,3);
		}
		if (pDataInner->m_strValue == strValue)
		{
			return;
		}
		pDataInner->m_strValue = strValue;
		//20240920 luozibing 编辑界面显示测试项时发送信号
		if (pSttMacroTestParaDatas_External != NULL/*&&m_pCurrMacroTest_External != &m_oSttMacroTest_Inner*/)
		{
			pSttMacroTestParaDatas_External->SetDataValue(strID, pDataInner->m_strValue, TRUE);
			emit sig_UpdateCurrSelGridData(m_pCurrMacroTest_External);
		}
		else
		{
			if (strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE || strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG||\
				strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE)
			{//20241012 luozibing 未选中测试项时 改变故障类型 区段 阻抗角 对应阻抗定值改变 刷新编辑界面
				emit sig_UpdateCurrSelGridData(NULL);
			}
		}
	}
}
void QDistanceItemParaEditWidget::CheckAllPresence(CExBaseList *pParas)
{
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_K0MODE);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTDIRECTION);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE1);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR);
	CheckForPresence(pParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
	CheckForPresence(pParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETTING);
	CheckForPresence(pParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETTING);
}
void QDistanceItemParaEditWidget::on_m_txtZSetting_editingFinished()
{
//	////20240722 huangliang 判断是否为定值，是定值就不需要处理
//	//if (m_pParaUI->m_txtZSetting->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
//	//{
//	//	if (((QSettingLineEdit*)m_pParaUI->m_txtZSetting)->IsSetting())
//	//	{
//	//		return;
//	//	}
//	//}
//	//20240805 huangliang
//	if (Stt_Global_IsSetting(m_pParaUI->m_txtZSetting))
//	{
//		return;
//	}
	//202240809 luozibing 阻抗值修改->修改R、X->根据阻抗定值修改Rate
	m_pParaUI->m_txtZSetting->setText(CheckDataMinMax(m_pParaUI->m_txtZSetting->text(), STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));
	CString strNewR,StrNewX;
	CheckRxValue(strNewR,StrNewX,m_pParaUI->m_txtZSetting->text(),m_pParaUI->m_txtZAng->text());
	m_pParaUI->m_txtR->setText(CheckDataMinMax(strNewR, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	m_pParaUI->m_txtX->setText(CheckDataMinMax(StrNewX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETTING, m_pParaUI->m_txtR->text());
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETTING, m_pParaUI->m_txtX->text());

	//根据新阻抗值除以阻抗定值得到Rate并更新到链表
	CString strNewRate,strDataRate;
	CString strZSeting = GetParaDataByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
	
	double dNew_Z = CString_To_double(m_pParaUI->m_txtZSetting->text());
	double dNewRate = dNew_Z / CString_To_double(strZSeting);
	strNewRate.Format("%lf",dNewRate*100);
	strDataRate.Format("%f", dNewRate * 100);
	m_pParaUI->m_txtRate->setText(CheckDataMinMax(strNewRate,0,0, 1));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE, strDataRate);
}
void QDistanceItemParaEditWidget::on_m_txtZAng_editingFinished()
{
//	////20240722 huangliang 判断是否为定值，是定值就不需要处理
//	//if (m_pParaUI->m_txtZAng->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
//	//{
//	//	if (((QSettingLineEdit*)m_pParaUI->m_txtZAng)->IsSetting())
//	//	{
//	//		return;
//	//	}
//	//}
//	//20240805 huangliang
//	if (Stt_Global_IsSetting(m_pParaUI->m_txtZAng))
//	{
//		return;
//	}
	
	//202240809 luozibing 阻抗角修改->修改R、X->更新最新阻抗角到链表
	m_pParaUI->m_txtZAng->setText(CheckDataMinMax(m_pParaUI->m_txtZAng->text(), STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	GetZSettingValueFromParas();
	CString strNewR,StrNewX;
	CheckRxValue(strNewR,StrNewX,m_pParaUI->m_txtZSetting->text(),m_pParaUI->m_txtZAng->text());
	m_pParaUI->m_txtR->setText(CheckDataMinMax(strNewR, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	m_pParaUI->m_txtX->setText(CheckDataMinMax(StrNewX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG,m_pParaUI->m_txtZAng->text());
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETTING, m_pParaUI->m_txtR->text());
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETTING, m_pParaUI->m_txtX->text());
}
void QDistanceItemParaEditWidget::GetZSettingValueFromParas()
{//编辑界面未选中测试项时计算交点及其阻抗定值
	if (m_pCurrMacroTest_External != NULL&&m_pCurrMacroTest_External != &m_oSttMacroTest_Inner)
	{
		return;
	}
	CSttMacroTestParaDatas *pSttMacroTestParaDatas_Inner = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	if (pSttMacroTestParaDatas_Inner == NULL)
	{
		return;
	}
	CSttMacroTestParaData *pDataInner_Zone = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
	CSttMacroTestParaData *pDataInner_Fault = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
	CSttMacroTestParaData *pDataInner_ZSet = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
	CSttMacroTestParaData *pDataInner_ZAng = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
	double dZSePara = -1;
	//20241009 luozibing 根据区段值 故障值 角阻抗值 计算阻抗定值
	CSttMacroTestParaData *pData_ZSetByAng = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZsetByZAng);
	if (pData_ZSetByAng == NULL)
	{
		CheckForPresence(pSttMacroTestParaDatas_Inner, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZsetByZAng);
		pData_ZSetByAng = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZsetByZAng);
	}
	CString strCharFault = Global_GetCharFaultTypeStringByFaultType(CString_To_long(pDataInner_Fault->m_strValue));
	CString strTempName = strCharFault;
	strTempName += pDataInner_Zone->m_strValue;
	if (pData_ZSetByAng->m_strValue != pDataInner_ZAng->m_strValue || pData_ZSetByAng->m_strName != strTempName)
	{
		if (Global_GetZSettingValueFromCharacteristics(stt_Frame_Characteristics(), CString_To_long(pDataInner_Zone->m_strValue), CString_To_long(pDataInner_Fault->m_strValue), \
			CString_To_double(m_pParaUI->m_txtZAng->text()), dZSePara))
		{
			//保存当前交点对应数据到ZsetByZAng参数
			pData_ZSetByAng->m_strValue = pDataInner_ZAng->m_strValue;
			pData_ZSetByAng->m_strName = strCharFault;
			pData_ZSetByAng->m_strName += pDataInner_Zone->m_strValue;
			if (fabs(CString_To_double(pDataInner_ZSet->m_strValue) - dZSePara) > STT_MULTI_MACRO_ZSet_MIN)
			{
				CString strTemp;
				strTemp.setNum(dZSePara);
				strTemp = CheckDataMinMax(strTemp, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3);
				m_pParaUI->m_txtZSetting->setText(strTemp);
				UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING, strTemp);
			}
		}
	}
	
}
void QDistanceItemParaEditWidget::on_m_txtR_editingFinished()
{
	//202240809 luozibing R修改->修改阻抗角和阻抗->更新最新阻抗角到链表->根据最新阻抗修改Rate
	m_pParaUI->m_txtR->setText(CheckDataMinMax(m_pParaUI->m_txtR->text(), STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETTING, m_pParaUI->m_txtR->text());

	CString strNewZ,StrNewZAng;
	CheckZSettingAndZAng(m_pParaUI->m_txtR->text(),m_pParaUI->m_txtX->text(),strNewZ,StrNewZAng);
	m_pParaUI->m_txtZSetting->setText(CheckDataMinMax(strNewZ, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));
	m_pParaUI->m_txtZAng->setText(CheckDataMinMax(StrNewZAng, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG, m_pParaUI->m_txtZAng->text());

	//根据新阻抗值除以阻抗定值得到Rate并更新到链表
	CString strNewRate,strDaraRate;
	CString strZSeting = GetParaDataByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
	
	double dNew_Z = CString_To_double(m_pParaUI->m_txtZSetting->text());
	double dNewRate = dNew_Z / CString_To_double(strZSeting);
	strNewRate.Format("%lf", dNewRate*100);
	strDaraRate.Format("%f", dNewRate * 100);
	m_pParaUI->m_txtRate->setText(CheckDataMinMax(strNewRate, 0, 0, 1));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE, strDaraRate);
}
void QDistanceItemParaEditWidget::on_m_txtX_editingFinished()
{
	//202240809 luozibing X修改->修改阻抗角和阻抗->更新最新阻抗角到链表->根据最新阻抗修改Rate
	m_pParaUI->m_txtX->setText(CheckDataMinMax(m_pParaUI->m_txtX->text(), STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETTING, m_pParaUI->m_txtX->text());
	CString strNewZ,StrNewZAng;
	CheckZSettingAndZAng(m_pParaUI->m_txtR->text(), m_pParaUI->m_txtX->text(), strNewZ, StrNewZAng);
	m_pParaUI->m_txtZSetting->setText(CheckDataMinMax(strNewZ, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));
	m_pParaUI->m_txtZAng->setText(CheckDataMinMax(StrNewZAng, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG,m_pParaUI->m_txtZAng->text());

	//根据新阻抗值除以阻抗定值得到Rate并更新到链表
	CString strNewRate,strDataRate;
	CString strZSeting = GetParaDataByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
	double dNew_Z = CString_To_double(m_pParaUI->m_txtZSetting->text());
	double dNewRate = dNew_Z / CString_To_double(strZSeting);
	strNewRate.Format("%lf", dNewRate*100);
	strDataRate.Format("%f", dNewRate * 100);
	m_pParaUI->m_txtRate->setText(CheckDataMinMax(strNewRate, 0, 0, 1));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE, strDataRate);
}
void QDistanceItemParaEditWidget::on_m_txtRate_editingFinished()
{
	//202240809 luozibing Rate修改->修改阻抗->根据阻抗修改R、X
	m_pParaUI->m_txtRate->setText(CheckDataMinMax(m_pParaUI->m_txtRate->text(),0,0,1));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE,m_pParaUI->m_txtRate->text());

	CString strNewZ;
	CString strRate = GetParaDataByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
	CString strZSeting = GetParaDataByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
	double dNewZ = CString_To_double(strZSeting)*CString_To_double(strRate);
	strNewZ.Format("%lf", dNewZ);
	m_pParaUI->m_txtZSetting->setText(CheckDataMinMax(strNewZ, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3));

	CString strNewR, StrNewX;
	CheckRxValue(strNewR, StrNewX, m_pParaUI->m_txtZSetting->text(), m_pParaUI->m_txtZAng->text());
	m_pParaUI->m_txtR->setText(CheckDataMinMax(strNewR, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	m_pParaUI->m_txtX->setText(CheckDataMinMax(StrNewX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETTING, m_pParaUI->m_txtR->text());
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETTING, m_pParaUI->m_txtX->text());
}
void QDistanceItemParaEditWidget::on_m_txtKlKr_editingFinished()
{
	////20240722 huangliang 判断是否为定值，是定值就不需要处理
	//if (m_pParaUI->m_txtKlKr->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)m_pParaUI->m_txtKlKr)->IsSetting())
	//	{
	//		UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR, m_pParaUI->m_txtKlKr->GetText());
	//		return;
	//	}
	//}
	//20240805 huangliang 
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR, m_pParaUI->m_txtKlKr))
		{
			return;
		}

	m_pParaUI->m_txtKlKr->setText(CheckDataMinMax(m_pParaUI->m_txtKlKr->text(),999.999,0,3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_KLKR,m_pParaUI->m_txtKlKr->text());
}
void QDistanceItemParaEditWidget::on_m_txtAngKx_editingFinished()
{
	////20240722 huangliang 判断是否为定值，是定值就不需要处理
	//if (m_pParaUI->m_txtAngKx->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)m_pParaUI->m_txtAngKx)->IsSetting())
	//	{
	//		return;
	//	}
	//}
	//20240805 huangliang 
	if (UpdateParaForLineEdit(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX, m_pParaUI->m_txtAngKx))
		{
			return;
		}

	m_pParaUI->m_txtAngKx->setText(CheckDataMinMax(m_pParaUI->m_txtAngKx->text(),999.999,0,3));

	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ANGKX,m_pParaUI->m_txtAngKx->text());
}
void QDistanceItemParaEditWidget::on_m_txtFaultCurrent_editingFinished()
{
	m_pParaUI->m_txtFaultCurrent->setText(CheckDataMinMax(m_pParaUI->m_txtFaultCurrent->text(), STT_MULTI_MACRO_CURR_MAX, STT_MULTI_MACRO_CURR_MIN, STT_MULTI_MACRO_PLACES_3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTCURRENT,m_pParaUI->m_txtFaultCurrent->text());
}
void QDistanceItemParaEditWidget::on_m_txtTSetting_editingFinished()
{
	m_pParaUI->m_txtTSetting->setText(CheckDataMinMax(m_pParaUI->m_txtTSetting->text(), STT_MULTI_MACRO_TSet_MAX, STT_MULTI_MACRO_TSet_MIN, STT_MULTI_MACRO_PLACES_3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING,m_pParaUI->m_txtTSetting->text());
}
void QDistanceItemParaEditWidget::on_m_txtPlus_editingFinished()
{
	m_pParaUI->m_txtPlus->setText(CheckDataMinMax(m_pParaUI->m_txtPlus->text(), STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS,m_pParaUI->m_txtPlus->text());
}
void QDistanceItemParaEditWidget::on_m_txtMinus_editingFinished()
{
	m_pParaUI->m_txtMinus->setText(CheckDataMinMax(m_pParaUI->m_txtMinus->text(), STT_MULTI_MACRO_PARAS_AbsErrorMaxValue, STT_MULTI_MACRO_PARAS_AbsErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS,m_pParaUI->m_txtMinus->text());
}
void QDistanceItemParaEditWidget::on_m_txtRelErr_editingFinished()
{
	m_pParaUI->m_txtRelErr->setText(CheckDataMinMax(m_pParaUI->m_txtRelErr->text(), STT_MULTI_MACRO_PARAS_RelErrorMaxValue, STT_MULTI_MACRO_PARAS_RelErrorMinValue, STT_MULTI_MACRO_PLACES_3));
	UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR,m_pParaUI->m_txtRelErr->text());
}
CExBaseList * QDistanceItemParaEditWidget::GetMacroTestParaDatas()
{
	if(m_pCurrMacroTest_External != NULL)
	{
		return m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE,"");
	}
	return NULL;
}
// CExBaseList * QDistanceItemParaEditWidget::GetMacroTestParaDatas_Inner()
//{
//	if(m_oSttMacroTest_Inner.GetCount() != 0)
//	{
//		return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE,"");
//	}
//	return NULL;
//}
void QDistanceItemParaEditWidget::UpdZoneTypeCmbParas(CSttMacroTestParaData *pData,int nFaultType)
{//20240906 luozibing 根据故障类型值得到最新区段显示下拉框数据
	//CExBaseListComboBox
	
	CString strFaultType;
	strFaultType = Global_GetCharFaultTypeStringByFaultType(nFaultType);//20240906 luozibing 使用新增全局函数

	CString strTypeId = STT_MULTI_MACRO_PARAS_DATATYPE_ID_SystemZone;
	strTypeId += "_";
	strTypeId += strFaultType;
	CDataType *pDataType = (CDataType *)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(strTypeId);
	if (pDataType == NULL)
	{
		return;
	}

	CString strZoneValue;
	CExBaseList *pParas = (CExBaseList *)pData->GetParent();
	CSttMacroTestParaData *pDataZone = (CSttMacroTestParaData *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);

	CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByID(pDataZone->m_strValue);
 	if (pValue == NULL)
 	{
		CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(STT_MULTI_MACRO_ZONELine);//未找到对应区段设置为线路长度
 		if (pValue != NULL)
 		{
 			pDataZone->m_strValue = pValue->m_strID;
 			UpdatePara(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE, pDataZone->m_strValue);
 		}
 	}
	strZoneValue = pDataZone->m_strValue;
	DisConnectAll_SigSlot();
	m_pParaUI->m_cmb_ZoneType->SetBaseList(pDataType);
	ConnectAll_SigSlot();
 
 	if (pValue != NULL)
 	{
		m_pParaUI->m_cmb_ZoneType->SetSelByID(strZoneValue);
 	}
	m_pParaUI->m_cmb_ErrorType->setCurrentIndex(CString_To_long(pData->m_strValue));
	
}

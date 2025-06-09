#include "CharEditWidget_Diff_Eng.h"
#include "../../../SttTestCntrFrameBase.h"
#include "../../../Module/CommonMethod/commonMethod.h"
#include "../../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../../Module/DataMngr/DvmValues.h"
#include "../../../../XLangResource_Native.h"
#include "../../../../../../Module/XLanguage/XLanguageResource.h"
#include "../QCharEditRadioHarmWidget.h"
#include "../QCharEditRadioNormalWidget.h"

//////////////////////////////////////////////////////////////////////////
//QCharEditGrid_Character
QCharEditGrid_DiffLine_Eng::QCharEditGrid_DiffLine_Eng(QWidget* pParent) : QCharEditGridBase(pParent)
{
	connect(this, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(slot_doubleClicked(int, int)), Qt::UniqueConnection);
}

QCharEditGrid_DiffLine_Eng::~QCharEditGrid_DiffLine_Eng()
{

}

void QCharEditGrid_DiffLine_Eng::InitGridTitle()
{
	CString astrGridTitle[DIFF_GRID_CLOS] = { _T("扫描线段"), _T("系统点数"), _T("自定义点数") };
	xlang_GetLangStrByFile(astrGridTitle[0], "State_Scanlinesegments");
	xlang_GetLangStrByFile(astrGridTitle[1], "Native_SyStempoints");
	xlang_GetLangStrByFile(astrGridTitle[2], "Native_Custompoints");
	int iGridWidth[DIFF_GRID_CLOS] = { 110, 110, 110};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, DIFF_GRID_CLOS);
}

void QCharEditGrid_DiffLine_Eng::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCharElementLined* pLine = (CCharElementLined*)pData;

	if (pLine->m_strName.GetLength())
	{
		Show_StaticString(pData, nRow, 0, pData->m_strName);
		Show_Long(pData, nRow, 1, pLine->GetTestPointsRef(), TRUE, _T(""), EndEditCell_TestPoints);
		CString strUserPoints;
		strUserPoints.Format("%d", pLine->GetUserTestPoints());
		Show_StaticString(pData, nRow, 2, strUserPoints);
		//Show_String(pData, nRow, 3, &pLine->m_strErrLength, EndEditCell_ErrorBand);

		nRow++;
	}
}

void QCharEditGrid_DiffLine_Eng::EndEditCell_TestPoints(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	long nCurrPoints = CString_To_long(pCell->text());

	if (*(pVCellData->pnValue) != nCurrPoints)
	{
		*(pVCellData->pnValue) = nCurrPoints;
		((QCharEditGrid_DiffLine*)pGrid)->EmitTestPointsErrorBandChanged();
	}
}

void QCharEditGrid_DiffLine_Eng::EndEditCell_ErrorBand(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	if (*(pVCellData->pString) != pCell->text())
	{
		*(pVCellData->pString) = pCell->text();
		((QCharEditGrid_DiffLine*)pGrid)->EmitTestPointsErrorBandChanged();
	}
}

void QCharEditGrid_DiffLine_Eng::EmitTestPointsErrorBandChanged()
{
	emit sig_TestPointsErrorBandChanged();
}

void QCharEditGrid_DiffLine_Eng::EmitCharChanged()
{
	emit sig_DiffCharChanged();
}


void QCharEditGrid_DiffLine_Eng::slot_doubleClicked(int nRow, int nCol)
{
	GridDoubleClicked_ShowKeyBoard(nRow, nCol);
}


void QCharEditGrid_DiffLine_Eng::GridDoubleClicked_ShowKeyBoard(int nRow, int nCol)
{
	if (nCol <= 0)
	{
		return;
	}

	QGV_ITEM *pParamItem = GetCell(nRow, nCol);


	if (pParamItem == NULL)
	{
		return;
	}

	switch (nCol)
	{

	case 1:
	case 2:
	{
			  QString strValue = pParamItem->text();
			  GetWidgetBoard_DigitData(4, strValue, pParamItem, parentWidget()->parentWidget());
			  //pParamItem->setText(strValue);
	}
		break;
	default:
		break;

	}

}

void QCharEditGrid_DiffLine_Eng::slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	if (currentRow == previousRow)
	{
		return;
	}

	if (currentRow >= 0)
	{
		OnDataSelChanged(currentRow, currentColumn);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//曲线参数接口表
QCharEditGrid_Param_Diff::QCharEditGrid_Param_Diff(QWidget* pParent) : QCharEditGridBase(pParent)
{
	connect(this, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(slot_doubleClicked(int, int)), Qt::UniqueConnection);
}

QCharEditGrid_Param_Diff::~QCharEditGrid_Param_Diff()
{

}

void QCharEditGrid_Param_Diff::InitGridTitle()
{
	CString strName, strID, strNum, strAttach;
	xlang_GetLangStrByFile(strName, "sName");
	strID = "ID";
	xlang_GetLangStrByFile(strNum, "sValue");
	//	xlang_GetLangStrByFile(strAttach, "CharLib_AttachSetting");

	CString astrGridTitle[DIFF_GRID_PARAM_CLOS] = { strName, strID, strNum/*, strAttach*/ };
	int iGridWidth[DIFF_GRID_PARAM_CLOS] = { 100, 100, 100/*, 200*/ };
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, DIFF_GRID_PARAM_CLOS);

	QExBaseListComBoxDelegBase* pZoomIndexDelegate = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(2, pZoomIndexDelegate);
}
void QCharEditGrid_Param_Diff::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCharInterfaceVariable* pCurObj = (CCharInterfaceVariable*)pData;

	Show_StaticString(pData, nRow, 0, &pCurObj->m_strName);
	Show_StaticString(pData, nRow, 1, &pCurObj->m_strID);
	Show_String(pData, nRow, 2, &pCurObj->m_strValue, EndEditCell_String);


	//	Show_StaticString(pData, nRow, 3, &pCurObj->m_strScript/*, EndEditCell_String*/);//2022-10-28  修改为不可编辑

	nRow++;
}
void QCharEditGrid_Param_Diff::slot_doubleClicked(int nRow, int nCol)
{
	GridDoubleClicked_ShowKeyBoard(nRow, nCol);
}


void QCharEditGrid_Param_Diff::GridDoubleClicked_ShowKeyBoard(int nRow, int nCol)
{
	if (nCol <= 0)
	{
		return;
	}

	QGV_ITEM *pParamItem = GetCell(nRow, nCol);


	if (pParamItem == NULL)
	{
		return;
	}

	switch (nCol)
	{

	case 2:
	{
			  QString strValue = pParamItem->text();
			  GetWidgetBoard_DigitData(4, strValue, pParamItem, parentWidget()->parentWidget());
			  //pParamItem->setText(strValue);
	}
		break;
	default:
		break;

	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//曲线参数接口表
QCharEditGrid_Section_Diff::QCharEditGrid_Section_Diff(QWidget* pParent) : QCharEditGridBase(pParent)
{
	connect(this, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(slot_doubleClicked(int, int)), Qt::UniqueConnection);
}

QCharEditGrid_Section_Diff::~QCharEditGrid_Section_Diff()
{

}

void QCharEditGrid_Section_Diff::InitGridTitle()
{

	CString astrGridTitle[DIFF_GRID_SECTION_CLOS] = { /*区段*/g_sLangTxt_Diff_Section, /*公式*/g_sLangTxt_Diff_Expression };
	int iGridWidth[DIFF_GRID_SECTION_CLOS] = { 200, 700 };
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, DIFF_GRID_SECTION_CLOS);
	//horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QExBaseListComBoxDelegBase* pZoomIndexDelegate = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(2, pZoomIndexDelegate);
}
void QCharEditGrid_Section_Diff::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{

	if (pData->GetClassID() == CHARCLASSID_CCHARELEMENTEXPR)
	{
		CCharElementExpr* pLine = (CCharElementExpr*)pData;
		CString strItem = /*曲线*/g_sLangTxt_Native_Curve + CString(",(%1.%2),(%3.%4)").arg(pLine->m_strXb.toDouble(), 0, 'f', 3).arg(pLine->m_strYb.toDouble(), 0, 'f', 3).arg(pLine->m_strXe.toDouble(), 0, 'f', 3).arg(pLine->m_strYe.toDouble(), 0, 'f', 3);
		Show_StaticString(pData, nRow, 0, strItem);
		Show_StaticString(pData,nRow, 1, pLine->m_strExpr);
	}
	else if (pData->GetClassID() == CHARCLASSID_CCHARELEMENTLINED)
	{
		CCharElementLined* pLine = (CCharElementLined*)pData;
		CString strItem = /*直线*/ g_sLangTxt_Diff_StraightLine + CString(",(%1.%2),(%3.%4)").arg(pLine->m_strXb.toDouble(), 0, 'f', 3).arg(pLine->m_strYb.toDouble(), 0, 'f', 3).arg(pLine->m_strXe.toDouble(), 0, 'f', 3).arg(pLine->m_strYe.toDouble(), 0, 'f', 3);
		Show_StaticString(pData,nRow, 0, strItem);
		Show_StaticString(pData, nRow, 1,"");
	}

	nRow++;
}
void QCharEditGrid_Section_Diff::slot_doubleClicked(int nRow, int nCol)
{
	GridDoubleClicked_ShowKeyBoard(nRow, nCol);
}


void QCharEditGrid_Section_Diff::GridDoubleClicked_ShowKeyBoard(int nRow, int nCol)
{
	if (nCol <= 0)
	{
		return;
	}

	QGV_ITEM *pParamItem = GetCell(nRow, nCol);


	if (pParamItem == NULL)
	{
		return;
	}

	switch (nCol)
	{

	case 2:
	{
			  QString strValue = pParamItem->text();
			  GetWidgetBoard_DigitData(4, strValue, pParamItem, parentWidget()->parentWidget());
			  //pParamItem->setText(strValue);
	}
		break;
	default:
		break;

	}
}
///////////////////////////////////////////////////////////////变压器差动///////////////////////////////////////////////////////////////////////////////////////
//QCharEditWidget_Diff_Eng_Eng
QCharEditWidget_Diff_Eng::QCharEditWidget_Diff_Eng(QWidget *parent)
: QWidget(parent)
{
	m_pCharEditWidget = this;
	ui.setupUi(this);
	m_pCharacteristics_Inner = NULL;
	m_pGridParam = NULL;
	m_pGridSection = NULL;

	m_strIDPath = _P_GetConfigPath();
	m_strIDPath += _T("CharLib-diff.xml");
	m_bIsCustomswitch = false;
	m_nFaultType = 0;
	m_nTransGroupMode = 0;
	m_bIsCharRaised = false;
	m_pCurrCharacteristic = NULL;
	/*m_pGridCharLine = new QCharEditGrid_DiffLine_Eng(this);
	m_pGridCharLine->InitGrid();
	m_pGridCharLine->AttachDataViewOptrInterface(this);

	ui.m_layoutVert->insertWidget(1, m_pGridCharLine);*/

	m_pMainWidget = (QCharEditMainDialog*)parentWidget();

	InitUI();
	InitConnect();
	//InitChar();
	//	UpdateChar(FALSE,FALSE,FALSE); //2023.4.23 zhouhj 在获取特性曲线后,再刷新相关界面
	SetDiffFont();
}

QCharEditWidget_Diff_Eng::~QCharEditWidget_Diff_Eng()
{
	long bChanged = m_oDiffCharCal.m_oPoints.GetCount();
}

void QCharEditWidget_Diff_Eng::InitUI()
{
	ui.m_cbSettingMinAxis->ShowDataType(CTestDataTypeMngrConstGlobal::FindTestDataType(_T("DifferMarkType")));
	ui.m_cbSettingMinAxis->setItemText(0,/*有名值*/g_sLangTxt_Diff_ActualVal);
	ui.m_cbSettingMinAxis->setItemText(1,/*标幺值*/g_sLangTxt_Diff_PerUnitVal);
	ui.m_cbSettingMinAxis2->ShowDataType(CTestDataTypeMngrConstGlobal::FindTestDataType(_T("DifferMarkType")));
	ui.m_cbSettingMinAxis2->setItemText(0,/*有名值*/g_sLangTxt_Diff_ActualVal);
	ui.m_cbSettingMinAxis2->setItemText(1,/*标幺值*/g_sLangTxt_Diff_PerUnitVal);

	ui.m_cbInSel->ShowDataType(CTestDataTypeMngrConstGlobal::FindTestDataType(_T("BasicCurrSelect")));
	ui.m_cbInSel->setItemText(0,/*高侧额定二次电流*/g_sLangTxt_Diff_HSecondaryCur);
	ui.m_cbInSel->setItemText(1,/*设定值*/g_sLangTxt_Diff_CurrSet);
	ui.m_cbInSel->setItemText(2,/*各侧二次额定电流*/g_sLangTxt_Diff_EverySecondaryCur);
	ui.m_cbInSel2->ShowDataType(CTestDataTypeMngrConstGlobal::FindTestDataType(_T("BasicCurrSelect")));
	ui.m_cbInSel2->setItemText(0,/*高侧额定二次电流*/g_sLangTxt_Diff_HSecondaryCur);
	ui.m_cbInSel2->setItemText(1,/*设定值*/g_sLangTxt_Diff_CurrSet);
	ui.m_cbInSel2->setItemText(2,/*各侧二次额定电流*/g_sLangTxt_Diff_EverySecondaryCur);

	ui.m_cmbZeroSeqElimiType->addItems(QStringList() <</*"无"*/g_sLangTxt_without
													  <</*"线电流-零序电流"*/g_sLangTxt_Diff_LineCur + "-" + g_sLangTxt_PowerDir_FaultPhase_ZeroCur
													  <<CString("YD辅助CT"));
	ui.m_cmbZeroSeqElimiType2->addItems(QStringList() <</*"无"*/g_sLangTxt_without
		<</*"线电流-零序电流"*/g_sLangTxt_Diff_LineCur + "-" + g_sLangTxt_PowerDir_FaultPhase_ZeroCur
		<< CString("YD辅助CT"));
	ui.m_cmbCombinedFeature->addItems(QStringList() <</*"否"*/g_sLangTxt_State_No <</*"是"*/g_sLangTxt_State_Yes);
	ui.m_cmbCombinedFeature2->addItems(QStringList() <</*"否"*/g_sLangTxt_State_No <</*"是"*/g_sLangTxt_State_Yes);
	ui.m_cbHarmIndex->addItems(QStringList() <</*2次谐波*/"2" + g_sLangTxt_State_HarmCount
		<</*3次谐波*/"3" + g_sLangTxt_State_HarmCount <</*4次谐波*/"4" + g_sLangTxt_State_HarmCount <</*5次谐波*/"5" + g_sLangTxt_State_HarmCount
		<</*自定义*/g_sLangTxt_Diff_Custom);

	//ui.m_cbHarmIndex->ShowDataType(CTestDataTypeMngrConstGlobal::FindTestDataType(_T("DiffHarmIndex")));
	//CString strHarBrkCoef = "4次谐波";
	//ui.m_cbHarmIndex->insertItem(2,strHarBrkCoef);
	
	initMaxPositiveEdit(ui.m_edtSet_Istart);
	initMaxPositiveEdit(ui.m_edtSet_Ip1);
	initMaxPositiveEdit(ui.m_edtSet_Ip2);
	initMaxPositiveEdit(ui.m_edtSet_Ip3);
	initMaxPositiveEdit(ui.m_edtSet_Isd);
	initMaxPositiveEdit(ui.m_edtSet_Kstart);
	initMaxPositiveEdit(ui.m_edtSet_K1);
	initMaxPositiveEdit(ui.m_edtSet_K2);
	initMaxPositiveEdit(ui.m_edtSet_K3);
	initMaxPositiveEdit(ui.m_editInSet);
	initMaxPositiveEdit(ui.m_editInSet2);
	initMaxPositiveEdit(ui.m_editHarmCoef);
	initPositiveIntegerLne(ui.m_editCustomHarmIndex);


	ui.m_chkStart->setEnabled(false);
	ui.m_chkLine1->setEnabled(false);
	//	ui.m_chkLineSd->setEnabled(false);
	ui.m_chkStart->setChecked(true);
	ui.m_chkLine1->setChecked(true);
	ui.m_chkLineSd->setChecked(true);
	ui.m_edtSet_Ip2->setEnabled(false);
	ui.m_edtSet_K2->setEnabled(false);
	ui.m_edtSet_Ip3->setEnabled(false);
	ui.m_edtSet_K3->setEnabled(false);

	m_pGridParam = new QCharEditGrid_Param_Diff(this);
	m_pGridParam->InitGrid();
	ui.verticalLayout_4->addWidget(m_pGridParam);

	m_pGridSection = new QCharEditGrid_Section_Diff(this);
	m_pGridSection->InitGrid();
	ui.verticalLayout_4->addWidget(m_pGridSection);

	ui.m_DiffTypeTab->setTabText(0, /*比率差动*/g_sLangTxt_Gradient_RatioDiff);
	ui.m_DiffTypeTab->setTabText(1, /*谐波制动*/g_sLangTxt_State_Harmonicbraking);

	ui.m_lbSettingMinAxis->setText(/*定值整定方式:*/g_sLangTxt_Native_DevSetMethod + ":");
	ui.m_lbSettingMinAxis2->setText(/*定值整定方式:*/g_sLangTxt_Native_DevSetMethod + ":");
	ui.m_lbInSel->setText(/*基准电流选择:*/g_sLangTxt_Native_RefCurrentSel + ":");
	ui.m_lbInSel2->setText(/*基准电流选择:*/g_sLangTxt_Native_RefCurrentSel + ":");
	ui.m_lbInSet->setText(/*基准电流(其它):*/g_sLangTxt_Diff_InSet + ":");
	ui.m_lbInSet2->setText(/*基准电流(其它):*/g_sLangTxt_Diff_InSet + ":");
	ui.m_labCombinedFeature->setText(/*复合特性:*/g_sLangTxt_Diff_CombinedFeature + ":");
	ui.m_labCombinedFeature2->setText(/*复合特性:*/g_sLangTxt_Diff_CombinedFeature + ":");
	ui.m_labZeroSeqElimiType->setText(/*零序消除方式:*/g_sLangTxt_Diff_ZeroSeqElimiType + ":");
	ui.m_labZeroSeqElimiType2->setText(/*零序消除方式:*/g_sLangTxt_Diff_ZeroSeqElimiType + ":");

	ui.m_radioSetting->setText(/*整定定值*/g_sLangTxt_Diff_Setting);
	ui.m_radioUser->setText(/*自定义*/g_sLangTxt_Diff_Custom);
	ui.m_lbTypeSel->setText(/*选择类型:*/g_sLangTxt_Diff_TypeSel + ":");


	ui.m_lbName->setText(/*_T("名称")*/g_sLangTxt_Name);
	ui.m_lbSetting->setText(/*_T("定值")*/g_sLangTxt_FixedValue);
	ui.m_lblTitleK->setText( /*_T("斜率")*/g_sLangTxt_Gradient_Slope);

	ui.m_chkStart->setText(/*_T("启动电流")*/g_sLangTxt_Gradient_StartCur);
	ui.m_chkLine1->setText( /*_T("第一段")*/g_sLangTxt_Native_FirstPart);
	ui.m_chkLine2->setText( /*_T("第二段")*/g_sLangTxt_Native_SecondPart);
	ui.m_chkLine3->setText( /*_T("第三段")*/g_sLangTxt_Native_ThirdPart);
	ui.m_chkLineSd->setText( /*_T("速断")*/g_sLangTxt_Diff_QuickBreak);
	ui.m_lblTitleStart->setText(/*_T("门槛值")*/g_sLangTxt_Native_Threshold);
	ui.m_lblTitleLine1->setText( /*_T("拐点1")*/g_sLangTxt_Native_Inflection1);
	ui.m_lblTitleLine2->setText( /*_T("拐点2")*/g_sLangTxt_Native_InflectionPoint2);
	ui.m_lblTitleLine3->setText( /*_T("拐点3")*/g_sLangTxt_Native_InflectionPoint3);
	ui.m_lblTitleLineSd->setText( /*_T("速断定值")*/g_sLangTxt_Native_QuickBreak);

	ui.m_lbHarmIndex->setText( /*谐波次数:*/g_sLangTxt_Native_harmonicOrder);
	ui.m_lbHarmIndex_2->setText( /*自定义谐波次数:*/g_sLangTxt_Diff_CustomHarmIndex);
	ui.m_lbHarmCoef->setText( /*谐波制动系数:")*/g_sLangTxt_State_HarmonicBrakingcoefficient);
}
void QCharEditWidget_Diff_Eng::SetDiffFont()
{
	/*m_pGridCharLine->setFont(*g_pSttGlobalFont);
	m_pGridCharLine->horizontalHeader()->setFont(*g_pSttGlobalFont);*/

	ui.m_edtSet_Istart->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Kstart->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleStart->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleCurr->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleK->setFont(*g_pSttGlobalFont);
	ui.m_chkLine1->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Ip1->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleLine1->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_K1->setFont(*g_pSttGlobalFont);
	ui.m_chkStart->setFont(*g_pSttGlobalFont);
	ui.m_chkLine3->setFont(*g_pSttGlobalFont);
	ui.m_chkLine2->setFont(*g_pSttGlobalFont);
	ui.m_chkLineSd->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleLine2->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleLine3->setFont(*g_pSttGlobalFont);
	ui.m_lblTitleLineSd->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Ip2->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Ip3->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_Isd->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_K2->setFont(*g_pSttGlobalFont);
	ui.m_edtSet_K3->setFont(*g_pSttGlobalFont);

	ui.m_lbSettingMinAxis->setFont(*g_pSttGlobalFont);
	ui.m_lbSettingMinAxis2->setFont(*g_pSttGlobalFont);
	ui.m_cbSettingMinAxis->setFont(*g_pSttGlobalFont);
	ui.m_cbSettingMinAxis2->setFont(*g_pSttGlobalFont);
	ui.m_labZeroSeqElimiType->setFont(*g_pSttGlobalFont);
	ui.m_labZeroSeqElimiType2->setFont(*g_pSttGlobalFont);
	ui.m_cmbZeroSeqElimiType->setFont(*g_pSttGlobalFont);
	ui.m_cmbZeroSeqElimiType2->setFont(*g_pSttGlobalFont);
	ui.m_labCombinedFeature->setFont(*g_pSttGlobalFont);
	ui.m_labCombinedFeature2->setFont(*g_pSttGlobalFont);
	ui.m_cmbCombinedFeature->setFont(*g_pSttGlobalFont);
	ui.m_cmbCombinedFeature2->setFont(*g_pSttGlobalFont);

	ui.m_lbInSel->setFont(*g_pSttGlobalFont);
	ui.m_cbInSel->setFont(*g_pSttGlobalFont);
	ui.m_lbInSel2->setFont(*g_pSttGlobalFont);
	ui.m_cbInSel2->setFont(*g_pSttGlobalFont);
	ui.m_lbInSet->setFont(*g_pSttGlobalFont);
	ui.m_editInSet->setFont(*g_pSttGlobalFont);
	ui.m_lbInSet2->setFont(*g_pSttGlobalFont);
	ui.m_editInSet2->setFont(*g_pSttGlobalFont);

	ui.m_lbName->setFont(*g_pSttGlobalFont);
	ui.m_lbSetting->setFont(*g_pSttGlobalFont);

	ui.m_lbHarmIndex->setFont(*g_pSttGlobalFont);
	ui.m_cbHarmIndex->setFont(*g_pSttGlobalFont);
	ui.m_lbHarmCoef->setFont(*g_pSttGlobalFont);
	ui.m_editHarmCoef->setFont(*g_pSttGlobalFont);

	m_pGridParam->setFont(*g_pSttGlobalFont);
	m_pGridParam->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pGridSection->setFont(*g_pSttGlobalFont);
	m_pGridSection->horizontalHeader()->setFont(*g_pSttGlobalFont);
}

void QCharEditWidget_Diff_Eng::OnLeftButtonDown()
{
	//if (IsNotHarm())
	//{
	//	m_pMainWidget->m_pImpCharactWidget->CalPointVertHorzLine(0, CHAR_TESTLINE_MODE_ID_VERT);
	//}
	//else
	//{
	//	m_pMainWidget->m_pImpCharactWidget->CalPointVertHorzLine(0, CHAR_TESTLINE_MODE_ID_HORZ);
	//}
	//UpdateEdit_IrValueUserPoint();
}

void QCharEditWidget_Diff_Eng::InitConnect()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	connect(this, SIGNAL(sig_CharChanged(CExBaseObject *, int)), m_pMainWidget, SLOT(slot_UpdateDrawCharacters(CExBaseObject *, int)), Qt::QueuedConnection);
	connect(m_pGridParam, SIGNAL(sig_CharChanged(CExBaseObject *)), this, SLOT(slot_ShowGridDatas_EmitCharChanged(CExBaseObject *)), Qt::QueuedConnection);
	/*connect(m_pGridCharLine, SIGNAL(sig_CharChanged(CExBaseObject *)), m_pMainWidget, SLOT(slot_UpdateDrawCharacters(CExBaseObject *)));

	connect(m_pGridCharLine, SIGNAL(sig_TestPointsErrorBandChanged()), this, SLOT(slot_TestPointsErrorBandChanged()));
	connect(m_pGridCharLine, SIGNAL(sig_DiffCharChanged()), this, SLOT(slot_DiffCharChanged()));*/

	//connect(ui.m_radioNormal, SIGNAL(clicked()), this, SLOT(slot_radioNormal_Clicked()));//比率差动
	//connect(ui.m_radioHarm, SIGNAL(clicked()), this, SLOT(slot_radioHarm_Clicked()));//谐波制动

	connect(ui.m_cbSettingMinAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbSettingMinAxisIndexChanged(int)));
	connect(ui.m_cbInSel, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbInSeIndexChanged(int)));
	connect(ui.m_editInSet, SIGNAL(editingFinished()), this, SLOT(slot_InSet_editingFinished()));

	connect(ui.m_cbSettingMinAxis2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbSettingMinAxis2IndexChanged(int)));
	connect(ui.m_cbInSel2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbInSeIndex2Changed(int)));
	connect(ui.m_editInSet2, SIGNAL(editingFinished()), this, SLOT(slot_InSet2_editingFinished())); 

	connect(ui.m_cbHarmIndex, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbHarmIndexChanged(int)));
	connect(ui.m_editHarmCoef, SIGNAL(editingFinished()), this, SLOT(slot_HarmCoef_editingFinished()));
	connect(ui.m_DiffTypeTab, SIGNAL(currentChanged(int)), this, SLOT(slot_Currm_DiffTypeTabChanged(int)));
	connect(ui.m_cbTypeSel, SIGNAL(currentTextChanged(QString)), this, SLOT(slot_m_cbTypeSel_currentIndexChanged(QString)));

	connect(ui.m_radioUser, SIGNAL(toggled(bool)), this, SLOT(slot_m_radioUser_toggled(bool)));
	connect(ui.m_editIDoor, SIGNAL(editingFinished()), this, SLOT(slot_m_editIDoor_editingFinished()));
	connect(ui.m_editIQuick, SIGNAL(editingFinished()), this, SLOT(slot_m_editIQuick_editingFinished()));

	connect(ui.m_cmbCombinedFeature, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbCombinedFeatureIndexChanged(int)));
	connect(ui.m_cmbCombinedFeature, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_UpdateCharByCombinedFeature()));
	connect(ui.m_cmbCombinedFeature2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbCombinedFeature2IndexChanged(int)));
	connect(ui.m_cmbZeroSeqElimiType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbZeroSeqElimiTypeIndexChanged(int)));
	connect(ui.m_cmbZeroSeqElimiType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_UpdateCharByCombinedFeature()));
	connect(ui.m_cmbZeroSeqElimiType2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbZeroSeqElimiType2IndexChanged(int)));
	
#ifdef _PSX_QT_LINUX_

	connect(ui.m_edtSet_Istart, SIGNAL(clicked()), this, SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Ip1, SIGNAL(clicked()), this, SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Ip2, SIGNAL(clicked()), this, SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Ip3, SIGNAL(clicked()), this, SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Isd, SIGNAL(clicked()), this, SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_Kstart, SIGNAL(clicked()), this, SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_K1, SIGNAL(clicked()), this, SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_K2, SIGNAL(clicked()), this, SLOT(on_m_onlineEdit_Changed()));
	connect(ui.m_edtSet_K3, SIGNAL(clicked()), this, SLOT(on_m_onlineEdit_Changed()));

#endif

}


void QCharEditWidget_Diff_Eng::slot_CmbSettingMinAxisIndexChanged(int nIndex)//定值整定方式
{
	m_oDiffCharCal.m_nMinAxis = ui.m_cbSettingMinAxis->GetSelectIndex2();
	UpdateEditsDisEnable();
	InitUI_Unit();
	emit sig_CharChanged(GetCurrentCharacter(), TRUE);
	m_pMainWidget->m_bCharChanged = TRUE;
	disconnect(ui.m_cbSettingMinAxis2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbSettingMinAxis2IndexChanged(int)));
	ui.m_cbSettingMinAxis2->setCurrentIndex(nIndex);
	connect(ui.m_cbSettingMinAxis2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbSettingMinAxis2IndexChanged(int)));
}

void QCharEditWidget_Diff_Eng::slot_CmbSettingMinAxis2IndexChanged(int nIndex)//谐波制动定值整定方式
{
	ui.m_cbSettingMinAxis->setCurrentIndex(nIndex);
}

void QCharEditWidget_Diff_Eng::slot_CmbCombinedFeatureIndexChanged(int nIndex)//复合特性
{
	m_nComBineFeature = nIndex;
	disconnect(ui.m_cmbCombinedFeature2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbCombinedFeature2IndexChanged(int)));
	ui.m_cmbCombinedFeature2->setCurrentIndex(nIndex);
	connect(ui.m_cmbCombinedFeature2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbCombinedFeature2IndexChanged(int)));
}

void QCharEditWidget_Diff_Eng::slot_CmbCombinedFeature2IndexChanged(int nIndex)//谐波制动复合特性
{
	ui.m_cmbCombinedFeature->setCurrentIndex(nIndex);
}

void QCharEditWidget_Diff_Eng::slot_CmbZeroSeqElimiTypeIndexChanged(int nIndex)//零序消除方式
{
	m_nZeroSeqElimiType = nIndex;
	disconnect(ui.m_cmbZeroSeqElimiType2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbZeroSeqElimiType2IndexChanged(int)));
	ui.m_cmbZeroSeqElimiType2->setCurrentIndex(nIndex);
	connect(ui.m_cmbZeroSeqElimiType2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbZeroSeqElimiType2IndexChanged(int)));
}

void QCharEditWidget_Diff_Eng::slot_CmbZeroSeqElimiType2IndexChanged(int nIndex)//谐波制动零序消除方式
{
	ui.m_cmbZeroSeqElimiType->setCurrentIndex(nIndex);
}

void QCharEditWidget_Diff_Eng::slot_CmbInSeIndexChanged(int nIndex)//基准电流选择
{
	m_oDiffCharCal.m_nInsel = ui.m_cbInSel->GetSelectIndex2();
	UpdateEditsDisEnable();
	m_pMainWidget->m_bCharChanged = TRUE;
	disconnect(ui.m_cbInSel2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbInSe2IndexChanged(int)));
	ui.m_cbInSel2->setCurrentIndex(nIndex);
	connect(ui.m_cbInSel2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbInSe2IndexChanged(int)));
}

void QCharEditWidget_Diff_Eng::slot_CmbInSe2IndexChanged(int nIndex)//谐波制动基准电流选择
{
	ui.m_cbInSel->setCurrentIndex(nIndex);
}

void QCharEditWidget_Diff_Eng::slot_CmbHarmIndexChanged(int nIndex)//谐波次数
{
	if (nIndex != ui.m_cbHarmIndex->count() - 1)
	{
		m_oDiffCharCal.m_nHarmIndex = nIndex;
		ui.m_editCustomHarmIndex->setEnabled(false);
	}
	else
	{
		if (ui.m_editCustomHarmIndex->text().toInt()> 2)
		{
			m_oDiffCharCal.m_nHarmIndex = ui.m_editCustomHarmIndex->text().toInt() - 2;
		}
		else
		{
			m_oDiffCharCal.m_nHarmIndex = 0;
		}
		ui.m_editCustomHarmIndex->setEnabled(true);
	}
	
	m_pMainWidget->m_bCharChanged = TRUE;
}

void QCharEditWidget_Diff_Eng::slot_InSet_editingFinished()
{
	SetParaI(ui.m_editInSet, m_oDiffCharCal.m_fInSet);
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->m_bCharChanged = TRUE;
	disconnect(ui.m_editInSet2, SIGNAL(editingFinished()), this, SLOT(slot_InSet2_editingFinished()));
	ui.m_editInSet2->setText(ui.m_editInSet->text());
	connect(ui.m_editInSet2, SIGNAL(editingFinished()), this, SLOT(slot_InSet2_editingFinished()));
}

void QCharEditWidget_Diff_Eng::slot_InSet2_editingFinished()
{
	ui.m_editInSet->setText(ui.m_editInSet2->text());
}

void QCharEditWidget_Diff_Eng::slot_HarmCoef_editingFinished()
{
	SetParaI(ui.m_editHarmCoef, m_oDiffCharCal.m_fHarmCoef);
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->m_bCharChanged = TRUE;
	UpdateChar();
}
void QCharEditWidget_Diff_Eng::slot_Currm_DiffTypeTabChanged(int nType)
{
	if (nType == 0)//比率差动
	{

		for (int i = 0; i<ui.m_layGridParas->count(); i++)
		{
			QWidget *w = ui.m_layGridParas->itemAt(i)->widget();
			if (w != NULL)
			{
				w->setVisible(true);
			}
		}

		CCharacteristic* pChar = GetCurrentCharacter();
		pChar->m_strTestLineMode = CHAR_TESTLINE_MODE_ID_VERT;
		//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
		m_pMainWidget->UpdateAxisDesc(_T("Ir(A)"), _T("Id(A)"), _T(" "), _T("A"), _T("A"));
		OnLeftButtonDown();
		UpdateChar(TRUE, TRUE);
		if (ui.m_radioUser->isChecked())
		{
			m_pGridParam->setHidden(false);
			m_pGridSection->setHidden(false);
		}
	}
	else//谐波制动
	{

		for (int i = 0; i<ui.m_layGridParas->count(); i++)
		{
			QWidget *w = ui.m_layGridParas->itemAt(i)->widget();
			if (w != NULL)
			{
				w->setVisible(false);
			}
		}

		CCharacteristic* pChar = GetCurrentCharacter();
		pChar->m_strTestLineMode = CHAR_TESTLINE_MODE_ID_HORZ;
		//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
		m_pMainWidget->UpdateAxisDesc(_T("(%)"), _T("Id(A)"), _T(" "), _T("%"), _T("A"));
		OnLeftButtonDown();

		UpdateChar(TRUE, TRUE);
		m_pGridParam->setHidden(true);
		m_pGridSection->setHidden(true);
	}
}
void QCharEditWidget_Diff_Eng::slot_m_radioUser_toggled(bool checked)
{
	ui.m_cbTypeSel->setEnabled(checked);
	ui.frame->setHidden(checked);
	m_pGridParam->setHidden(!checked);
	m_pGridSection->setHidden(!checked);
	if (checked)
	{
		slot_m_cbTypeSel_currentIndexChanged(ui.m_cbTypeSel->currentText());
	}
	else
	{
		UpdateChar();
	}
	//TODO
}

void QCharEditWidget_Diff_Eng::EnableEdit(long nIndex)
{
	// 	ui.m_edtSet_Ip2->setEnabled(false);
	// 	ui.m_edtSet_K2->setEnabled(false);
	// 	ui.m_edtSet_Ip3->setEnabled(false);
	// 	ui.m_edtSet_K3->setEnabled(false);

	switch (nIndex)
	{
	case CharDiff_RateCoef2_Index:
		ui.m_edtSet_Ip2->setEnabled(true);
		ui.m_edtSet_K2->setEnabled(true);

		if (!ui.m_chkLine2->isChecked())
		{
			ui.m_chkLine2->setChecked(true);
		}

		m_oDiffCharCal.m_nKneePoints = nIndex;
		break;
	case CharDiff_RateCoef3_Index:

		ui.m_edtSet_Ip2->setEnabled(true);
		ui.m_edtSet_K2->setEnabled(true);

		if (!ui.m_chkLine2->isChecked())
		{
			ui.m_chkLine2->setChecked(true);
		}

		ui.m_edtSet_Ip3->setEnabled(true);
		ui.m_edtSet_K3->setEnabled(true);

		if (!ui.m_chkLine3->isChecked())
		{
			ui.m_chkLine3->setChecked(true);
		}

		m_oDiffCharCal.m_nKneePoints = nIndex;
		break;
	case CharDiff_QuickCurr_Index:
		ui.m_edtSet_Isd->setEnabled(true);
		m_oDiffCharCal.m_nSelectSd = 1;
		break;

	default:
		break;
	}

	UpdateChar();
}

void QCharEditWidget_Diff_Eng::DisableEdit(long nIndex)
{
	switch (nIndex)
	{
	case CharDiff_RateCoef2_Index:
		ui.m_edtSet_Ip2->setEnabled(false);
		ui.m_edtSet_K2->setEnabled(false);

		if (ui.m_chkLine2->isChecked())
		{
			ui.m_chkLine2->setChecked(false);
		}

		ui.m_edtSet_Ip3->setEnabled(false);
		ui.m_edtSet_K3->setEnabled(false);

		if (ui.m_chkLine3->isChecked())
		{
			ui.m_chkLine3->setChecked(false);
		}

		m_oDiffCharCal.m_nKneePoints = nIndex - 1;
		break;
	case CharDiff_RateCoef3_Index:

		ui.m_edtSet_Ip3->setEnabled(false);
		ui.m_edtSet_K3->setEnabled(false);

		if (ui.m_chkLine3->isChecked())
		{
			ui.m_chkLine3->setChecked(false);
		}

		m_oDiffCharCal.m_nKneePoints = nIndex - 1;
		break;
	case CharDiff_QuickCurr_Index:
		ui.m_edtSet_Isd->setEnabled(false);
		m_oDiffCharCal.m_nSelectSd = 0;
		break;

	default:
		break;
	}

	UpdateChar();
}

void QCharEditWidget_Diff_Eng::on_m_onlineEdit_Changed()
{
	QSttLineEdit* pEditLine = qobject_cast<QSttLineEdit*>(sender());

	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->text();
	GetWidgetBoard_DigitData(4, str, pEditLine, this);

	if (str.right(1).contains("."))
	{
		str.append("000");
	}

	m_pMainWidget->m_bCharChanged = TRUE;
	// 	pEditLine->setText(str);
	// 	pEditLine->SetEditFinished();
}

void QCharEditWidget_Diff_Eng::slot_m_cbTypeSel_currentIndexChanged(const QString &strText)
{
	CCharacteristic* pFind = NULL;
	CCharacteristicLib oCharacteristicLib;
	if (strText == /*当前曲线*/g_sLangTxt_Diff_CurrChar)
	{
		pFind = m_pCurrCharacteristic;
	}
	if (pFind == NULL)
	{
		oCharacteristicLib.OpenXmlFile(m_strIDPath, CCharacteristicXmlRWKeys::CCharacteristicLibKey(), CCharacteristicXmlRWKeys::g_pXmlKeys);
		pFind = (CCharacteristic *)oCharacteristicLib.FindByName(strText);
	}
	
    if(pFind != NULL)
    {
		if (m_pCharacteristics_Inner == NULL)
		{
			return;
		}
		CCharacteristic* pChar = (CCharacteristic*)m_pCharacteristics_Inner->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
		if (pChar == NULL)
		{
			return;
		}
		CCharacterArea* pArea = pChar->GetCharacterArea();
		CCharacterArea* pFindArea = ((CCharacteristic*)pFind)->GetCharacterArea();

		CExBaseList *pParas = pChar->GetCharInterface();
		pParas->RemoveAll();
		CExBaseList *pFindParas = ((CCharacteristic*)pFind)->GetCharInterface();
		pFindParas->Copy(pParas);

		CExBaseList* pLine = (CExBaseList*)pFindArea->GetTail();
		if (pLine->GetClassID() == CHARCLASSID_CCHARELEMENTEXPR)
		{			
			pChar->m_fXMax = ((CCharElementExpr*)pLine)->m_strXe.toDouble()*1.5;
			pChar->m_fYMax = ((CCharElementExpr*)pLine)->m_strYe.toDouble()*1.5;
		}
		else if (pLine->GetClassID() == CHARCLASSID_CCHARELEMENTLINED)
		{
			pChar->m_fXMax = ((CCharElementLined*)pLine)->m_strXe.toDouble()*1.5;
			pChar->m_fYMax = ((CCharElementLined*)pLine)->m_strYe.toDouble()*1.5;
		}
		else
		{
			pChar->m_fXMax = 10;
			pChar->m_fYMax = 10;
		}

		pChar->m_bXMin = TRUE;
		pChar->m_bXMax = TRUE;
		pChar->m_bYMin = TRUE;
		pChar->m_bYMax = TRUE;
		pChar->m_fXMin = 0.0f;
		pChar->m_fYMin = 0.0f;
		pChar->m_strXMin = _T("0.0");
		pChar->m_strYMin = _T("0.0");
		pChar->m_strXMax.Format(_T("%lf"), pChar->m_fXMax);
		pChar->m_strYMax.Format(_T("%lf"), pChar->m_fYMax);

		pArea->RemoveAll();
		pFindArea->Copy(pArea);

		ShowGridDatas_CharVariables();
		m_bIsCustomswitch = true;
		emit sig_CharChanged(pChar, TRUE);
        m_pMainWidget->m_bCharChanged = TRUE;
    }
}

void QCharEditWidget_Diff_Eng::slot_TestPointsErrorBandChanged()
{
	GetTestPointNumErrorBand();
	emit sig_CharChanged(GetCurrentCharacter(), TRUE);
}

void QCharEditWidget_Diff_Eng::slot_DiffCharChanged()
{
	emit sig_CharChanged(GetCurrentCharacter(), TRUE);
}


void QCharEditWidget_Diff_Eng::UpdateEdit_IrValueUserPoint()
{
	//CXDrawLine* pLine = stt_Frame_GetCharLibLeftButtonLine();
	CXDrawLine* pLine = m_pMainWidget->m_pImpCharactWidget->GetLeftButtonLine();
	CXDrawPoint* pPoint = (CXDrawPoint*)pLine->GetHead();

	if (!pPoint)
	{
		return;
	}

	CString strValue;
	if (IsNotHarm())
	{
		strValue.Format(_T("%.03f"), pPoint->m_fX);
	}
	else
	{
		strValue.Format(_T("%.03f"), pPoint->m_fY);
	}
}

void QCharEditWidget_Diff_Eng::slot_radioNormal_Clicked()//比率差动
{
	ui.m_lblTitleLine1->setVisible(true);
	ui.m_edtSet_Ip1->setVisible(true);

	ui.m_lbHarmIndex->setVisible(false);
	ui.m_cbHarmIndex->setVisible(false);
	ui.m_lbHarmCoef->setVisible(false);
	ui.m_editHarmCoef->setVisible(false);

	//  	CString strText = "拐点1";
	//  	ui.m_lblTitleLine1->setText(strText);
	ui.m_lbName->setVisible(true);
	ui.m_chkStart->setVisible(true);
	ui.m_chkLine1->setVisible(true);
	ui.m_chkLineSd->setVisible(true);

	ui.m_lblTitleK->setVisible(true);
	ui.m_edtSet_Kstart->setVisible(true);
	ui.m_edtSet_K1->setVisible(true);
	//	ui.m_lblTitleLine1->setVisible(true);
	ui.m_edtSet_Ip1->setText(QString::number(m_oDiffCharCal.m_fIp1));

	ui.m_chkLine2->setVisible(true);
	ui.m_edtSet_Ip2->setVisible(true);
	ui.m_edtSet_K2->setVisible(true);
	ui.m_lblTitleLine2->setVisible(true);

	ui.m_chkLine3->setVisible(true);
	ui.m_edtSet_Ip3->setVisible(true);
	ui.m_edtSet_K3->setVisible(true);
	ui.m_lblTitleLine3->setVisible(true);

	CCharacteristic* pChar = GetCurrentCharacter();
	pChar->m_strTestLineMode = CHAR_TESTLINE_MODE_ID_VERT;
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->UpdateAxisDesc(_T("Ir(A)"), _T("Id(A)"), _T(" "), _T("A"), _T("A"));
	OnLeftButtonDown();
	UpdateChar(TRUE, TRUE);
}

void QCharEditWidget_Diff_Eng::slot_radioHarm_Clicked()//谐波制动
{
	ui.m_lblTitleLine1->setVisible(false);
	ui.m_edtSet_Ip1->setVisible(false);

	ui.m_lbHarmIndex->setVisible(true);
	ui.m_cbHarmIndex->setVisible(true);
	ui.m_lbHarmCoef->setVisible(true);
	ui.m_editHarmCoef->setVisible(true);

	// 	CString strText = "谐波制动系数";
	// 	ui.m_lblTitleLine1->setText(strText);
	ui.m_lbName->setVisible(false);
	ui.m_chkStart->setVisible(false);
	ui.m_chkLine1->setVisible(false);
	ui.m_chkLineSd->setVisible(false);
	ui.m_lblTitleK->setVisible(false);
	ui.m_edtSet_Kstart->setVisible(false);
	ui.m_edtSet_K1->setVisible(false);
	//	ui.m_lblTitleLine1->setVisible(false);
	//	ui.m_edtSet_Ip1->setText(QString::number(m_oDiffCharCal.m_fHarmCoef));

	ui.m_chkLine2->setVisible(false);
	ui.m_edtSet_Ip2->setVisible(false);
	ui.m_edtSet_K2->setVisible(false);
	ui.m_lblTitleLine2->setVisible(false);

	ui.m_chkLine3->setVisible(false);
	ui.m_edtSet_Ip3->setVisible(false);
	ui.m_edtSet_K3->setVisible(false);
	ui.m_lblTitleLine3->setVisible(false);

	CCharacteristic* pChar = GetCurrentCharacter();
	pChar->m_strTestLineMode = CHAR_TESTLINE_MODE_ID_HORZ;
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->UpdateAxisDesc(_T("(%)"), _T("Id(A)"), _T(" "), _T("%"), _T("A"));
	OnLeftButtonDown();

	UpdateChar(TRUE, TRUE);
}

void QCharEditWidget_Diff_Eng::on_m_chkStart_clicked()
{
	if (!ui.m_chkStart->isChecked())
	{
		ui.m_chkStart->setChecked(true);
	}
}

void QCharEditWidget_Diff_Eng::on_m_chkLine1_clicked()
{
	if (!ui.m_chkLine1->isChecked())
	{
		ui.m_chkLine1->setChecked(true);
	}
}

void QCharEditWidget_Diff_Eng::on_m_chkLine2_clicked()
{
	if (ui.m_chkLine2->isChecked())
	{
		EnableEdit(CharDiff_RateCoef2_Index);
	}
	else
	{
		DisableEdit(CharDiff_RateCoef2_Index);
	}
}

void QCharEditWidget_Diff_Eng::on_m_chkLine3_clicked()
{
	if (ui.m_chkLine3->isChecked())
	{
		EnableEdit(CharDiff_RateCoef3_Index);
	}
	else
	{
		DisableEdit(CharDiff_RateCoef3_Index);
	}
}

void QCharEditWidget_Diff_Eng::on_m_chkLineSd_clicked()
{
	if (ui.m_chkLineSd->isChecked())
	{
		EnableEdit(CharDiff_QuickCurr_Index);
		//		ui.m_chkLineSd->setChecked(true);
	}
	else
	{
		DisableEdit(CharDiff_QuickCurr_Index);
	}
}

float QCharEditWidget_Diff_Eng::SetParaI(QLineEdit* pEdit, float& fv)
{
	if (pEdit->text().isEmpty())
	{
		pEdit->setText("0.000");
	}

	QString str = pEdit->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	fv = str.toFloat();
	fv = SetLimit(0, 999.999, fv);
	pEdit->setText(QString::number(fv, 'f', 3));
	return fv;
}



void QCharEditWidget_Diff_Eng::InitDiffData()
{
	disconnect(ui.m_cbSettingMinAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbSettingMinAxisIndexChanged(int)));
	disconnect(ui.m_cbInSel, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbInSeIndexChanged(int)));
	disconnect(ui.m_cbSettingMinAxis2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbSettingMinAxis2IndexChanged(int)));
	disconnect(ui.m_cbInSel2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbInSe2IndexChanged(int)));
	disconnect(ui.m_cbHarmIndex, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbHarmIndexChanged(int)));
	disconnect(ui.m_cbTypeSel, SIGNAL(currentTextChanged(QString)), this, SLOT(slot_m_cbTypeSel_currentIndexChanged(QString)));
	disconnect(ui.m_radioUser, SIGNAL(toggled(bool)), this, SLOT(slot_m_radioUser_toggled(bool)));
	disconnect(ui.m_cmbCombinedFeature, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbCombinedFeatureIndexChanged(int)));
	disconnect(ui.m_cmbCombinedFeature, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_UpdateCharByCombinedFeature()));
	disconnect(ui.m_cmbCombinedFeature2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbCombinedFeature2IndexChanged(int)));
	disconnect(ui.m_cmbZeroSeqElimiType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbZeroSeqElimiTypeIndexChanged(int)));
	disconnect(ui.m_cmbZeroSeqElimiType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_UpdateCharByCombinedFeature()));
	disconnect(ui.m_cmbZeroSeqElimiType2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbZeroSeqElimiType2IndexChanged(int)));
	ui.m_cbSettingMinAxis->SetSelByIndex(m_oDiffCharCal.m_nMinAxis);
	ui.m_cbInSel->SetSelByIndex(m_oDiffCharCal.m_nInsel);
	ui.m_cbSettingMinAxis2->SetSelByIndex(m_oDiffCharCal.m_nMinAxis);
	ui.m_cbInSel2->SetSelByIndex(m_oDiffCharCal.m_nInsel);

	if (m_oDiffCharCal.m_nHarmIndex < 3)
	{
		ui.m_cbHarmIndex->setCurrentIndex(m_oDiffCharCal.m_nHarmIndex);
		ui.m_editCustomHarmIndex->setEnabled(false);
		ui.m_editCustomHarmIndex->setText(QString::number(m_oDiffCharCal.m_nHarmIndex+2));
	}
	else
	{
		ui.m_cbHarmIndex->setCurrentIndex(ui.m_cbHarmIndex->count()-1);
		ui.m_editCustomHarmIndex->setEnabled(true);
		ui.m_editCustomHarmIndex->setText(QString::number(m_oDiffCharCal.m_nHarmIndex+2));
	}

	ui.m_radioUser->setChecked(m_nCustomChar);
	ui.m_cbTypeSel->setEnabled(m_nCustomChar);
	ui.frame->setHidden(m_nCustomChar);
	m_pGridParam->setHidden(!m_nCustomChar);
	m_pGridSection->setHidden(!m_nCustomChar);

	if (!m_strIDPath.isEmpty())
	{
		ui.m_cbTypeSel->clear();
		QStringList TypeSelList;
		if (m_nCustomChar == TRUE)
		{
			TypeSelList << /*当前曲线*/g_sLangTxt_Diff_CurrChar;
			CCharacteristic* pChar = GetCurrentCharacter();
			if (pChar)
			{
				m_pCurrCharacteristic = (CCharacteristic*)pChar->Clone();
			}
			ShowGridDatas_CharVariables();
		}
		CCharacteristicLib oCharacteristicLib;
		oCharacteristicLib.OpenXmlFile(m_strIDPath, CCharacteristicXmlRWKeys::CCharacteristicLibKey(), CCharacteristicXmlRWKeys::g_pXmlKeys);

		POS pos = oCharacteristicLib.GetHeadPosition();

		while (pos)
		{
			CExBaseList* pList = (CExBaseList*)oCharacteristicLib.GetNext(pos);
			if (pList->GetClassID() == CHARCLASSID_CCHARACTERISTIC)
			{
				CCharacteristic* pCharacteristic = (CCharacteristic*)pList;
				TypeSelList << pCharacteristic->m_strName;
			}
		}
		ui.m_cbTypeSel->addItems(TypeSelList);
	}
	
	CString strText;

	strText.Format("%.3f", m_oDiffCharCal.m_fInSet);
	ui.m_editInSet->setText(strText);
	ui.m_editInSet2->setText(strText);

	strText.Format("%.3f", m_oDiffCharCal.m_fHarmCoef);
	ui.m_editHarmCoef->setText(strText);

	strText.Format("%.3f", m_oDiffCharCal.m_fIcdqd);
	ui.m_edtSet_Istart->setText(strText);
	ui.m_editIDoor->setText(strText);
	strText.Format("%.3f", m_oDiffCharCal.m_fIsd);
	ui.m_edtSet_Isd->setText(strText);
	ui.m_editIQuick->setText(strText);

	strText.Format("%.3f", m_oDiffCharCal.m_fIp2);
	ui.m_edtSet_Ip2->setText(strText);
	strText.Format("%.3f", m_oDiffCharCal.m_fIp3);
	ui.m_edtSet_Ip3->setText(strText);

	strText.Format("%.3f", m_oDiffCharCal.m_fKid0);
	ui.m_edtSet_Kstart->setText(strText);
	strText.Format("%.3f", m_oDiffCharCal.m_fKid1);
	ui.m_edtSet_K1->setText(strText);
	strText.Format("%.3f", m_oDiffCharCal.m_fKid2);
	ui.m_edtSet_K2->setText(strText);
	strText.Format("%.3f", m_oDiffCharCal.m_fKid3);
	ui.m_edtSet_K3->setText(strText);

	strText.Format("%.3f", m_oDiffCharCal.m_fIp1);
	ui.m_edtSet_Ip1->setText(strText);

	ui.m_cmbCombinedFeature->setCurrentIndex(m_nComBineFeature);
	ui.m_cmbZeroSeqElimiType->setCurrentIndex(m_nZeroSeqElimiType);
	ui.m_cmbCombinedFeature2->setCurrentIndex(m_nComBineFeature);
	ui.m_cmbZeroSeqElimiType2->setCurrentIndex(m_nZeroSeqElimiType);

	InitUI_Unit();

	connect(ui.m_cbSettingMinAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbSettingMinAxisIndexChanged(int)));
	connect(ui.m_cbInSel, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbInSeIndexChanged(int)));
	connect(ui.m_cbSettingMinAxis2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbSettingMinAxis2IndexChanged(int)));
	connect(ui.m_cbInSel2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbInSe2IndexChanged(int)));
	connect(ui.m_cbHarmIndex, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbHarmIndexChanged(int)));
	connect(ui.m_cbTypeSel, SIGNAL(currentTextChanged(QString)), this, SLOT(slot_m_cbTypeSel_currentIndexChanged(QString)));
	connect(ui.m_radioUser, SIGNAL(toggled(bool)), this, SLOT(slot_m_radioUser_toggled(bool)));
	connect(ui.m_cmbCombinedFeature, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbCombinedFeatureIndexChanged(int)));
	connect(ui.m_cmbCombinedFeature, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_UpdateCharByCombinedFeature()));
	connect(ui.m_cmbCombinedFeature2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbCombinedFeature2IndexChanged(int)));
	connect(ui.m_cmbZeroSeqElimiType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbZeroSeqElimiTypeIndexChanged(int)));
	connect(ui.m_cmbZeroSeqElimiType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_UpdateCharByCombinedFeature()));
	connect(ui.m_cmbZeroSeqElimiType2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbZeroSeqElimiType2IndexChanged(int)));
}

void QCharEditWidget_Diff_Eng::InitUI_Unit()
{
	CString strText, strText_IrAxis, strText_IdAxis, strCustomText;

	if (IsNotHarm())
	{
		if (m_oDiffCharCal.m_nMinAxis)
		{
			strText = /*_T("电流(Ie)")*/g_sLangTxt_State_Iecurrent;
			strText_IrAxis = _T("Ir(Ie)");
			strText_IdAxis = _T("Id(Ie)");
			strCustomText = /*_T("制动电流(Ie)")*/g_sLangTxt_Native_Iecurrent;
		}
		else
		{
			strText = /*_T("电流(A)")*/g_sLangTxt_State_Acurrent;
			strText_IrAxis = _T("Ir(A)");
			strText_IdAxis = _T("Id(A)");
			strCustomText = /*_T("制动电流(A)")*/g_sLangTxt_Native_Acurrent;
		}

		ui.m_lblTitleCurr->setText(strText);
	}
	else
	{
		strText_IrAxis = _T("%");

		if (m_oDiffCharCal.m_nMinAxis)
		{
			strText = /*_T("电流(Ie)")*/g_sLangTxt_State_Iecurrent;

			strText_IdAxis = _T("Id(Ie)");
		}
		else
		{
			strText = /*_T("电流(A)")*/g_sLangTxt_State_Acurrent;
			strText_IdAxis = _T("Id(A)");
		}

		ui.m_lblTitleCurr->setText(strText);
	}

	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();

	if (m_pMainWidget != NULL)
	{
		m_pMainWidget->m_pImpCharactWidget->SetAxisName(strText_IrAxis, strText_IdAxis, _T(" "));
	}
	if (m_oDiffCharCal.m_nMinAxis)
	{
		ui.m_lbIDoor->setText(/*门槛值(Ie):*/g_sLangTxt_Native_Threshold + "(Ie):");
		ui.m_lbIQuick->setText(/*速断值(Ie):*/g_sLangTxt_Diff_QuickBreakVal + "(Ie):");
	}
	else
	{
		ui.m_lbIDoor->setText(/*门槛值(Ie):*/g_sLangTxt_Native_Threshold + "(A):");
		ui.m_lbIQuick->setText(/*速断值(Ie):*/g_sLangTxt_Diff_QuickBreakVal + "(A):");
	}
}

void QCharEditWidget_Diff_Eng::InitChar()
{
	//QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	m_pMainWidget->UpdateCharAxisType(AXIS_TYPE_ID_CARTES, FALSE);
	m_pMainWidget->m_pImpCharactWidget->SetChangePlot(TRUE);
	m_pMainWidget->m_pImpCharactWidget->EnableSetting(FALSE);
	m_pMainWidget->m_pImpCharactWidget->setObjectName(QString::fromUtf8("QDiffCurr6ICharactWidget"));
	m_pMainWidget->m_pImpCharactWidget->SetAxisName(_T("Ir(A)"), _T("Id(A)"), _T(" "));
	m_pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T("A"), _T("A"));
	m_pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
	m_pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowAng(false);

	if (m_pCharacteristics_Inner == NULL)
	{
		//为空时获取父窗口内部对象
		m_pCharacteristics_Inner = m_pMainWidget->GetCharacteristics_Inner();
	}

	CCharacteristic* pChar = GetCurrentCharacter();

	if (!pChar)
	{
		//没有配置文件,则初始化
		stt_Frame_Characteristics()->InitEmptyCharacter(AXIS_TYPE_ID_CARTES);
		pChar = GetCurrentCharacter();
		pChar->InitAfterRead();
		pChar->m_strTestLineMode = CHAR_TESTLINE_MODE_ID_VERT;
	}
	else
	{
		CCharacterArea* pArea = pChar->GetCharacterArea();
		pChar->m_strTestLineMode = CHAR_TESTLINE_MODE_ID_VERT;
		if (pArea->GetCount() == 0)
		{
			stt_Frame_Characteristics()->InitEmptyCharacter(AXIS_TYPE_ID_CARTES);
			pChar = GetCurrentCharacter();
			pChar->InitAfterRead();
			
		}
		else
		{
			
			/*if (ui.m_radioUser->isChecked())
			{
				InitDiffData();
				return;
			}
			//设置门槛值
			CCharElementLined* pLine = (CCharElementLined*)pArea->GetHead();
			m_oDiffCharCal.m_fIcdqd = CString_To_double(pLine->m_strYb);
			m_oDiffCharCal.m_fKid0 = CalLineK(pLine);

			//设置拐点
			switch (pArea->GetCount())
			{
			case 5:
				pLine = (CCharElementLined*)pArea->GetAt((long)3);
				m_oDiffCharCal.m_fKid3 = CalLineK(pLine);
				m_oDiffCharCal.m_fIp3 = CString_To_double(pLine->m_strXb);
				ui.m_chkLine3->setChecked(true);
				ui.m_edtSet_Ip3->setEnabled(true);
				ui.m_edtSet_K3->setEnabled(true);
			case 4:
				pLine = (CCharElementLined*)pArea->GetAt((long)2);
				m_oDiffCharCal.m_fKid2 = CalLineK(pLine);
				m_oDiffCharCal.m_fIp2 = CString_To_double(pLine->m_strXb);
				ui.m_chkLine2->setChecked(true);
				ui.m_edtSet_Ip2->setEnabled(true);
				ui.m_edtSet_K2->setEnabled(true);
			case 3:
				pLine = (CCharElementLined*)pArea->GetAt((long)1);
				m_oDiffCharCal.m_fKid1 = CalLineK(pLine);
				m_oDiffCharCal.m_fIp1 = CString_To_double(pLine->m_strXb);
				break;
			default:
				break;
			}

			m_oDiffCharCal.m_nKneePoints = pArea->GetCount() - 2;

			//设置速断
			pLine = (CCharElementLined*)pArea->GetTail();
			m_oDiffCharCal.m_fIsd = CString_To_double(pLine->m_strYb);*/
		}	
	}

	InitDiffData();
}

void QCharEditWidget_Diff_Eng::UpdateEditsDisEnable()
{
	switch (m_oDiffCharCal.m_nKneePoints)
	{
	case 3:
		ui.m_edtSet_Ip2->setEnabled(true);
		ui.m_edtSet_K2->setEnabled(true);
		ui.m_edtSet_Ip3->setEnabled(true);
		ui.m_edtSet_K3->setEnabled(true);
		break;
	case 2:
		ui.m_edtSet_Ip2->setEnabled(true);
		ui.m_edtSet_K2->setEnabled(true);
		ui.m_edtSet_Ip3->setEnabled(false);
		ui.m_edtSet_K3->setEnabled(false);
		break;
	case 1:
		ui.m_edtSet_Ip2->setEnabled(false);
		ui.m_edtSet_K2->setEnabled(false);
		ui.m_edtSet_Ip3->setEnabled(false);
		ui.m_edtSet_K3->setEnabled(false);
		break;
	default:
		ui.m_edtSet_Ip2->setEnabled(false);
		ui.m_edtSet_K2->setEnabled(false);
		ui.m_edtSet_Ip3->setEnabled(false);
		ui.m_edtSet_K3->setEnabled(false);
		break;
	}

	if (m_oDiffCharCal.m_nMinAxis == 0)
	{
		ui.m_cbInSel->setEnabled(false);
		ui.m_editInSet->setEnabled(false);
		ui.m_cbInSel2->setEnabled(false);
		ui.m_editInSet2->setEnabled(false);
	}
	else
	{
		ui.m_cbInSel->setEnabled(true);
		ui.m_cbInSel2->setEnabled(true);

		if (m_oDiffCharCal.m_nInsel == 1)
		{
			ui.m_editInSet->setEnabled(true);
			ui.m_editInSet2->setEnabled(true);
		}
		else
		{
			ui.m_editInSet->setEnabled(false);
			ui.m_editInSet2->setEnabled(false);
		}
	}
}

void QCharEditWidget_Diff_Eng::UpdateChar(BOOL bUpdateTable, BOOL bCharTypeChanged, BOOL bParasChanged)
{
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}

	if (ui.m_radioUser->isChecked() && IsNotHarm())
	{
		emit sig_CharChanged(pChar, TRUE);
		m_pMainWidget->m_bCharChanged = TRUE;
		return;
	}
	//yzj 2023/11/3
	//bChanged判断不准确,初始2段以上的特性图都会存在这个问题
	//切换和添加新的测试功能都会保留之前的点数,而新建的Area没有与其匹配的段数
	//long bChanged = m_oDiffCharCal.m_oPoints.GetCount();
	if (IsNotHarm())
	{
		m_oDiffCharCal.Cal();
	}
	else
	{
		m_oDiffCharCal.CalHarm();
	}

	pChar->m_bXMin = TRUE;
	pChar->m_bXMax = TRUE;
	pChar->m_bYMin = TRUE;
	pChar->m_bYMax = TRUE;
	pChar->m_fXMin = 0.0f;
	pChar->m_fYMin = 0.0f;
	pChar->m_fXMax = m_oDiffCharCal.m_fXMax;
	pChar->m_fYMax = m_oDiffCharCal.m_fYMax;
	pChar->m_strXMin = _T("0.0");
	pChar->m_strYMin = _T("0.0");
	pChar->m_strXMax.Format(_T("%lf"), pChar->m_fXMax);
	pChar->m_strYMax.Format(_T("%lf"), pChar->m_fYMax);
	CCharacterArea* pArea = pChar->GetCharacterArea();

	long bChanged = pArea->GetCount() + 1;//线段+1等于点数
	if (((!bCharTypeChanged) && (bChanged != m_oDiffCharCal.m_oPoints.GetCount())) || m_bIsCustomswitch)
	{
		//段数改变
		pArea->DeleteAll();
		CCharElement *pCharElement = pArea->GetCharBisector();

		if (pCharElement != NULL)//20230206 zhouhj  拐点等线段也删除
		{
			pCharElement->DeleteAll();
		}

		POS pos = m_oDiffCharCal.m_oPoints.GetHeadPosition();
		CXDrawData_Point* pLast = NULL;
		CString strFX, strFY;
		long nLineIndex = 0;

		while (pos)
		{
			CXDrawData_Point* pt = (CXDrawData_Point*)m_oDiffCharCal.m_oPoints.GetNext(pos);

			if (pLast)
			{
				CCharElementLined* pLine = new CCharElementLined;
				strFX.Format("%.3f", pLast->m_fX);
				strFY.Format("%.3f", pLast->m_fY);
				pLine->SetBeginPoint(strFX, strFY);
				strFX.Format("%.3f", pt->m_fX);
				strFY.Format("%.3f", pt->m_fY);
				pLine->SetEndPoint(strFX, strFY);
				pArea->AddNewChild(pLine);
				nLineIndex++;
			}

			pLast = pt;
		}
		if (!m_bIsCustomswitch)
		{
			ShowDatas_Table();
		}
		m_bIsCustomswitch = false;
	}
	else
	{
		POS pos = m_oDiffCharCal.m_oPoints.GetHeadPosition();//每条线的端点
		CXDrawData_Point* pLast = NULL;
		CString strFX, strFY;
		long nIndex = 0;
		while (pos)
		{
			CXDrawData_Point* pt = (CXDrawData_Point*)m_oDiffCharCal.m_oPoints.GetNext(pos);
			if (pLast)
			{
				CCharElementLined* pLine = (CCharElementLined*)pArea->GetAt((long)nIndex);
				strFX.Format("%.3f", pLast->m_fX);
				strFY.Format("%.3f", pLast->m_fY);
				pLine->SetBeginPoint(strFX, strFY);
				strFX.Format("%.3f", pt->m_fX);
				strFY.Format("%.3f", pt->m_fY);
				pLine->SetEndPoint(strFX, strFY);
				nIndex++;
			}
			pLast = pt;
		}

		if (bUpdateTable)
		{
			ShowDatas_Table();
		}
	}

	emit sig_CharChanged(GetCurrentCharacter(), bParasChanged);
}

void QCharEditWidget_Diff_Eng::ShowDatas_Table()
{
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}


	CCharacterArea* pArea = pChar->GetCharacterArea();

	if (pArea == NULL)
	{
		return;
	}

	CCharElementLined* pLine1 = (CCharElementLined*)pArea->GetHead();
	CCharElementLined* pLineSd = NULL;
	CCharElementLined* pCurrLine = NULL;

	if (m_oDiffCharCal.m_nSelectSd > 0)
	{
		pLineSd = (CCharElementLined*)pArea->GetTail();
	}

	CString strStartCurr, strRatiobraking, strParagraph, strTripping, strHarmBrake;
	xlang_GetLangStrByFile(strStartCurr, "CharLib_StartCurr");
	xlang_GetLangStrByFile(strRatiobraking, "CharLib_Ratiobraking");
	xlang_GetLangStrByFile(strParagraph, "CharLib_Paragraph");
	xlang_GetLangStrByFile(strTripping, "CharLib_Tripping");
	xlang_GetLangStrByFile(strHarmBrake, "State_Harmonicbraking");

	if (IsNotHarm())
	{
		//line本身Name是其类型的名称,不是所需要的段名
		pLine1->m_strName = strStartCurr;
		pLine1->SetTestPoint(m_oDiffCharCal.m_nPointNum[0]);
		pLine1->m_strErrLength.Format(_T("%.03f"), m_oDiffCharCal.m_fErrorBand[0]);
		POS pos = pArea->GetHeadPosition();
		pArea->GetNext(pos);
		long nIndex = 1;
		CString strAppend;

		while (pos)
		{
			pCurrLine = (CCharElementLined*)pArea->GetNext(pos);

			if (pCurrLine == pLineSd)
			{
				break;
			}

			pCurrLine->m_strName = strRatiobraking;
			strAppend.Format(_T("%ld"), nIndex);
			pCurrLine->m_strName += strAppend;
			//pCurrLine->m_strName.AppendFormat(_T("%ld"),nIndex);
			pCurrLine->m_strName += _T(strParagraph);
			pCurrLine->SetTestPoint(m_oDiffCharCal.m_nPointNum[nIndex]);
			pCurrLine->m_strErrLength.Format(_T("%.03f"), m_oDiffCharCal.m_fErrorBand[nIndex]);
			nIndex++;
		}

		if (m_oDiffCharCal.m_nSelectSd)
		{
			pLineSd->m_strName = strTripping;
			pLineSd->SetTestPoint(m_oDiffCharCal.m_nPointNum[4]);
			pLineSd->m_strErrLength.Format(_T("%.03f"), m_oDiffCharCal.m_fErrorBand[4]);
		}
	}
	else
	{
		pLine1->m_strName = "";

		pCurrLine = (CCharElementLined*)pArea->GetAt(1);
		pCurrLine->m_strName = strHarmBrake;
		pCurrLine->SetTestPoint(*pCurrLine->GetTestPointsRef());
		pCurrLine->m_strErrLength.Format(_T("%.03f"), m_oDiffCharCal.m_fErrorBand[1]);

		if (m_oDiffCharCal.m_nSelectSd)
		{
			pLineSd->m_strName = "";
		}
	}

	//m_pGridCharLine->ShowDatas(pArea);
}

CCharacteristic* QCharEditWidget_Diff_Eng::GetCurrentCharacter()
{
	if (IsNotHarm())
	{
		return (CCharacteristic*)m_pCharacteristics_Inner->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
	}

	return m_pCharacteristics_Inner->GetTail_Char();
}

bool QCharEditWidget_Diff_Eng::IsNotHarm()
{
	return (ui.m_DiffTypeTab->currentIndex() == 0);
	//return ui.m_radioNormal->isChecked();
}

void QCharEditWidget_Diff_Eng::GetTestPointNumErrorBand()
{
	return;//wangtao???
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar == NULL)
	{
		return;
	}

	CCharacterArea* pArea = pChar->GetCharacterArea();

	if (pArea == NULL)
	{
		return;
	}

	//line本身Name是其类型的名称,不是所需要的段名
	CCharElementLined* pLine1 = (CCharElementLined*)pArea->GetHead();
	CCharElementLined* pLineSd = (CCharElementLined*)pArea->GetTail();
	CCharElementLined* pCurrLine = NULL;
	if (IsNotHarm())
	{
		m_oDiffCharCal.m_nPointNum[0] = *pLine1->GetTestPointsRef();
		m_oDiffCharCal.m_fErrorBand[0] = CString_To_double(pLine1->m_strErrLength);
		POS pos = pArea->GetHeadPosition();
		pArea->GetNext(pos);
		long nIndex = 1;

		while (pos)
		{
			pCurrLine = (CCharElementLined*)pArea->GetNext(pos);

			//zhouhj 2023.11.24 如果已经是最后一段,并且选择了速断,则不需要再赋值,防止误覆盖,导致参数比对不一致
			if ((pos == NULL) && (m_oDiffCharCal.m_nSelectSd))
			{
				break;
			}

			m_oDiffCharCal.m_nPointNum[nIndex] = *pCurrLine->GetTestPointsRef();
			m_oDiffCharCal.m_fErrorBand[nIndex] = CString_To_double(pCurrLine->m_strErrLength);
			nIndex++;
		}

		if (m_oDiffCharCal.m_nSelectSd)
		{
			m_oDiffCharCal.m_nPointNum[4] = *pLineSd->GetTestPointsRef();
			m_oDiffCharCal.m_fErrorBand[4] = CString_To_double(pLineSd->m_strErrLength);
		}
	}
	else
	{
		pCurrLine = (CCharElementLined*)pArea->GetAt(1);
		m_oDiffCharCal.m_fErrorBand[1] = CString_To_double(pCurrLine->m_strErrLength);
	}
}

void QCharEditWidget_Diff_Eng::on_m_edtSet_Istart_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_Istart, m_oDiffCharCal.m_fIcdqd);
	UpdateChar();
	disconnect(ui.m_editIDoor, SIGNAL(editingFinished()), this, SLOT(slot_m_editIDoor_editingFinished()));
	ui.m_editIDoor->setText(ui.m_edtSet_Istart->text());
	connect(ui.m_editIDoor, SIGNAL(editingFinished()), this, SLOT(slot_m_editIDoor_editingFinished()));
}
void QCharEditWidget_Diff_Eng::slot_m_editIDoor_editingFinished()
{
	ui.m_edtSet_Istart->setText(ui.m_editIDoor->text());
	on_m_edtSet_Istart_editingFinished();
}

void QCharEditWidget_Diff_Eng::on_m_edtSet_Kstart_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_Kstart, m_oDiffCharCal.m_fKid0);
	UpdateChar();
}

void QCharEditWidget_Diff_Eng::on_m_edtSet_Ip1_editingFinished()
{
	SetParaI(ui.m_edtSet_Ip1, m_oDiffCharCal.m_fIp1);
	UpdateChar();
}

void QCharEditWidget_Diff_Eng::on_m_edtSet_K1_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_K1, m_oDiffCharCal.m_fKid1);
	UpdateChar();
}

void QCharEditWidget_Diff_Eng::on_m_edtSet_Ip2_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_Ip2, m_oDiffCharCal.m_fIp2);
	UpdateChar();
}

void QCharEditWidget_Diff_Eng::on_m_edtSet_K2_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_K2, m_oDiffCharCal.m_fKid2);
	UpdateChar();
}

void QCharEditWidget_Diff_Eng::on_m_edtSet_K3_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_K3, m_oDiffCharCal.m_fKid3);
	UpdateChar();
}

void QCharEditWidget_Diff_Eng::on_m_edtSet_Ip3_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_Ip3, m_oDiffCharCal.m_fIp3);
	UpdateChar();
}

void QCharEditWidget_Diff_Eng::on_m_edtSet_Isd_editingFinished()
{
	float fv = SetParaI(ui.m_edtSet_Isd, m_oDiffCharCal.m_fIsd);
	UpdateChar();
	disconnect(ui.m_editIQuick, SIGNAL(editingFinished()), this, SLOT(slot_m_editIQuick_editingFinished()));
	ui.m_editIQuick->setText(ui.m_edtSet_Isd->text());
	connect(ui.m_editIQuick, SIGNAL(editingFinished()), this, SLOT(slot_m_editIQuick_editingFinished()));
}
void QCharEditWidget_Diff_Eng::slot_m_editIQuick_editingFinished()
{
	ui.m_edtSet_Isd->setText(ui.m_editIQuick->text());
	on_m_edtSet_Isd_editingFinished();
}

float QCharEditWidget_Diff_Eng::SetLimit(float min, float max, float val)
{
	if (val<min)
	{
		val = min;
	}
	else if (val>max)
	{
		val = max;
	}
	return val;
}

float QCharEditWidget_Diff_Eng::CalLineK(CCharElementLined* pLine)
{
	float fXb, fXe, fYb, fYe;
	fXb = CString_To_double(pLine->m_strXb);
	fXe = CString_To_double(pLine->m_strXe);
	fYb = CString_To_double(pLine->m_strYb);
	fYe = CString_To_double(pLine->m_strYe);
	return (fYe - fYb) / (fXe - fXb);
}

void QCharEditWidget_Diff_Eng::GroupDatasToChar(CDataGroup *pDatas)
{
	stt_GetDataValueByID(pDatas, CharDiff_ID_IDoor, m_oDiffCharCal.m_fIcdqd);
	stt_GetDataValueByID(pDatas, CharDiff_ID_IQuickSetting, m_oDiffCharCal.m_fIsd);
	stt_GetDataValueByID(pDatas, CharDiff_ID_Limp1, m_oDiffCharCal.m_fIp1);
	stt_GetDataValueByID(pDatas, CharDiff_ID_Limp2, m_oDiffCharCal.m_fIp2);
	stt_GetDataValueByID(pDatas, CharDiff_ID_Limp3, m_oDiffCharCal.m_fIp3);
	stt_GetDataValueByID(pDatas, CharDiff_ID_StartCurr_Kid, m_oDiffCharCal.m_fKid0);
	stt_GetDataValueByID(pDatas, CharDiff_ID_RateCoef_Kid1, m_oDiffCharCal.m_fKid1);
	stt_GetDataValueByID(pDatas, CharDiff_ID_RateCoef_Kid2, m_oDiffCharCal.m_fKid2);
	stt_GetDataValueByID(pDatas, CharDiff_ID_RateCoef_Kid3, m_oDiffCharCal.m_fKid3);
	stt_GetDataValueByID(pDatas, CharDiff_ID_RateHarm, m_oDiffCharCal.m_fHarmCoef);
	m_oDiffCharCal.m_fHarmCoef = QString::number(m_oDiffCharCal.m_fHarmCoef, 'f', 3).toFloat();
	stt_GetDataValueByID(pDatas, CharDiff_ID_MinAxis, m_oDiffCharCal.m_nMinAxis);
	stt_GetDataValueByID(pDatas, CharDiff_ID_Insel, m_oDiffCharCal.m_nInsel);
	stt_GetDataValueByID(pDatas, CharDiff_ID_In, m_oDiffCharCal.m_fInSet);

	stt_GetDataValueByID(pDatas, CharDiff_ID_HarmIndex, m_oDiffCharCal.m_nHarmIndex);

	stt_GetDataValueByID(pDatas, CharDiff_ID_StartCurrPointNum, m_oDiffCharCal.m_nPointNum[0]);
	stt_GetDataValueByID(pDatas, CharDiff_ID_RateCoef1PointNum, m_oDiffCharCal.m_nPointNum[1]);
	stt_GetDataValueByID(pDatas, CharDiff_ID_RateCoef2PointNum, m_oDiffCharCal.m_nPointNum[2]);
	stt_GetDataValueByID(pDatas, CharDiff_ID_RateCoef3PointNum, m_oDiffCharCal.m_nPointNum[3]);
	stt_GetDataValueByID(pDatas, CharDiff_ID_QuickCurrPointNum, m_oDiffCharCal.m_nPointNum[4]);

	stt_GetDataValueByID(pDatas, CharDiff_ID_StartCurrErrorBand, m_oDiffCharCal.m_fErrorBand[0]);
	stt_GetDataValueByID(pDatas, CharDiff_ID_RateCoef1ErrorBand, m_oDiffCharCal.m_fErrorBand[1]);
	stt_GetDataValueByID(pDatas, CharDiff_ID_RateCoef2ErrorBand, m_oDiffCharCal.m_fErrorBand[2]);
	stt_GetDataValueByID(pDatas, CharDiff_ID_RateCoef3ErrorBand, m_oDiffCharCal.m_fErrorBand[3]);
	stt_GetDataValueByID(pDatas, CharDiff_ID_QuickCurrErrorBand, m_oDiffCharCal.m_fErrorBand[4]);

	long nStartCurrCheck = 1, nRateCoef1Check = 1, nRateCoef2Check = 1, nRateCoef3Check = 1, nQuickCurrCheck = 1, nCustomChar = 0;
	stt_GetDataValueByID(pDatas, CharDiff_ID_StartCurr_Check, nStartCurrCheck);
	stt_GetDataValueByID(pDatas, CharDiff_ID_RateCoef1_Check, nRateCoef1Check);
	stt_GetDataValueByID(pDatas, CharDiff_ID_RateCoef2_Check, nRateCoef2Check);
	stt_GetDataValueByID(pDatas, CharDiff_ID_RateCoef3_Check, nRateCoef3Check);
	stt_GetDataValueByID(pDatas, CharDiff_ID_QuickCurr_Check, m_oDiffCharCal.m_nSelectSd);
	stt_GetDataValueByID(pDatas, CharDiff_ID_CustomChar, m_nCustomChar);

	m_oDiffCharCal.m_nKneePoints = nRateCoef1Check + nRateCoef2Check + nRateCoef3Check;
	ui.m_chkLine2->setChecked(nRateCoef2Check);
	ui.m_chkLine3->setChecked(nRateCoef3Check);
	ui.m_chkLineSd->setChecked(m_oDiffCharCal.m_nSelectSd);



	stt_GetDataValueByID(pDatas, CharDiff_ID_ComBineFeature, m_nComBineFeature);
	stt_GetDataValueByID(pDatas, CharDiff_ID_ZeroSeqElimiType, m_nZeroSeqElimiType);
	stt_GetDataValueByID(pDatas, CharDiff_ID_FaultType, m_nFaultType);
	stt_GetDataValueByID(pDatas, CharDiff_ID_TransGroupMode, m_nTransGroupMode);
	
	m_oDiffCharCal.m_nIsCharRaised = 0;
	m_oDiffCharCal.m_nIsCharRaised = m_oDiffCharCal.CalCombinedFeature(m_nComBineFeature, m_nZeroSeqElimiType, m_nTransGroupMode, m_nFaultType, FALSE);
	
	//InitDiffData();
	UpdateEditsDisEnable();
	InitChar();
	UpdateChar(TRUE, FALSE, FALSE);
}

void QCharEditWidget_Diff_Eng::CharToGroupDatas(CDataGroup *pDatas)
{
	//GetTestPointNumErrorBand();
	pDatas->SetDataValue(CharDiff_ID_IDoor, m_oDiffCharCal.m_fIcdqd, TRUE);
	pDatas->SetDataValue(CharDiff_ID_IQuickSetting, m_oDiffCharCal.m_fIsd, TRUE);
	pDatas->SetDataValue(CharDiff_ID_Limp1, m_oDiffCharCal.m_fIp1, TRUE);
	pDatas->SetDataValue(CharDiff_ID_Limp2, m_oDiffCharCal.m_fIp2, TRUE);
	pDatas->SetDataValue(CharDiff_ID_Limp3, m_oDiffCharCal.m_fIp3, TRUE);
	pDatas->SetDataValue(CharDiff_ID_StartCurr_Kid, m_oDiffCharCal.m_fKid0, TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef_Kid1, m_oDiffCharCal.m_fKid1, TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef_Kid2, m_oDiffCharCal.m_fKid2, TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef_Kid3, m_oDiffCharCal.m_fKid3, TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateHarm, m_oDiffCharCal.m_fHarmCoef, TRUE);

	pDatas->SetDataValue(CharDiff_ID_MinAxis, m_oDiffCharCal.m_nMinAxis, TRUE);
	pDatas->SetDataValue(CharDiff_ID_Insel, m_oDiffCharCal.m_nInsel, TRUE);
	pDatas->SetDataValue(CharDiff_ID_HarmIndex, m_oDiffCharCal.m_nHarmIndex, TRUE);
	pDatas->SetDataValue(CharDiff_ID_In, m_oDiffCharCal.m_fInSet, TRUE);

	pDatas->SetDataValue(CharDiff_ID_StartCurrPointNum, m_oDiffCharCal.m_nPointNum[0], TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef1PointNum, m_oDiffCharCal.m_nPointNum[1], TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef2PointNum, m_oDiffCharCal.m_nPointNum[2], TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef3PointNum, m_oDiffCharCal.m_nPointNum[3], TRUE);
	pDatas->SetDataValue(CharDiff_ID_QuickCurrPointNum, m_oDiffCharCal.m_nPointNum[4], TRUE);

	pDatas->SetDataValue(CharDiff_ID_StartCurrErrorBand, m_oDiffCharCal.m_fErrorBand[0], TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef1ErrorBand, m_oDiffCharCal.m_fErrorBand[1], TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef2ErrorBand, m_oDiffCharCal.m_fErrorBand[2], TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef3ErrorBand, m_oDiffCharCal.m_fErrorBand[3], TRUE);
	pDatas->SetDataValue(CharDiff_ID_QuickCurrErrorBand, m_oDiffCharCal.m_fErrorBand[4], TRUE);

	long nStartCurrCheck = 1, nRateCoef1Check = 1, nRateCoef2Check = 1, nRateCoef3Check = 1, nQuickCurrCheck = m_oDiffCharCal.m_nSelectSd, nCustomChar = 0;

	if (m_oDiffCharCal.m_nKneePoints == 2)
	{
		nRateCoef3Check = 0;
	}
	else if (m_oDiffCharCal.m_nKneePoints == 1)
	{
		nRateCoef2Check = 0;
		nRateCoef3Check = 0;
	}

	nCustomChar = ui.m_radioUser->isChecked();

	pDatas->SetDataValue(CharDiff_ID_StartCurr_Check, nStartCurrCheck, TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef1_Check, nRateCoef1Check, TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef2_Check, nRateCoef2Check, TRUE);
	pDatas->SetDataValue(CharDiff_ID_RateCoef3_Check, nRateCoef3Check, TRUE);
	pDatas->SetDataValue(CharDiff_ID_QuickCurr_Check, nQuickCurrCheck, TRUE);
	pDatas->SetDataValue(CharDiff_ID_CustomChar, nCustomChar, TRUE);
	pDatas->SetDataValue(CharDiff_ID_ComBineFeature, m_nComBineFeature, TRUE);
	pDatas->SetDataValue(CharDiff_ID_ZeroSeqElimiType, m_nZeroSeqElimiType, TRUE);
}

void QCharEditWidget_Diff_Eng::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	//CCharElement *pCurrSelElement = (CCharElement*)m_pGridCharLine->GetCurrSelData();

	//if (pCurrSelElement == NULL)
	//{
	//	return;
	//}

	////QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();

	//if (m_pMainWidget != NULL)
	//{
	//	m_pMainWidget->UI_SetActiveElement((CXDrawElement*)pCurrSelElement->m_pDataRef);
	//}
}
void QCharEditWidget_Diff_Eng::ImportChar()
{
	if (!ui.m_radioUser->isChecked())
	{
		disconnect(ui.m_cbTypeSel, SIGNAL(currentTextChanged(QString)), this, SLOT(slot_m_cbTypeSel_currentIndexChanged(QString)));
	}

	CString strIDPath;
	strIDPath = _P_GetConfigPath();
	QString fileName = QFileDialog::getOpenFileName(this, CString("选择文件"), strIDPath, "(*.xml)");
	if (!fileName.isEmpty()) 
	{
		m_strIDPath = fileName;
		ui.m_cbTypeSel->clear();
		QStringList TypeSelList;

		CCharacteristicLib oCharacteristicLib;
		oCharacteristicLib.OpenXmlFile(m_strIDPath, CCharacteristicXmlRWKeys::CCharacteristicLibKey(), CCharacteristicXmlRWKeys::g_pXmlKeys);

		POS pos = oCharacteristicLib.GetHeadPosition();

		while (pos)
		{
			CExBaseList* pList = (CExBaseList*)oCharacteristicLib.GetNext(pos);
			if (pList->GetClassID() == CHARCLASSID_CCHARACTERISTIC)
			{
				CCharacteristic* pCharacteristic = (CCharacteristic*)pList;
				TypeSelList << pCharacteristic->m_strID;
			}
		}
		ui.m_cbTypeSel->addItems(TypeSelList);
	}
	connect(ui.m_cbTypeSel, SIGNAL(currentTextChanged(QString)), this, SLOT(slot_m_cbTypeSel_currentIndexChanged(QString)), Qt::UniqueConnection);
}
void QCharEditWidget_Diff_Eng::ShowGridDatas_CharVariables()
{
	CCharacteristic* pChar = GetCurrentCharacter();

	if (pChar)
	{
		CExBaseList *pParas = pChar->GetCharInterface();
		m_pGridParam->ShowDatas(pParas);
		pParas = pChar->GetCharacterArea();
		m_pGridSection->ShowDatas(pParas);
	}
	else
	{
		m_pGridParam->ShowDatas(NULL);
		m_pGridSection->ShowDatas(NULL);
	}
}
void QCharEditWidget_Diff_Eng::slot_ShowGridDatas_EmitCharChanged(CExBaseObject *)
{
	emit sig_CharChanged(GetCurrentCharacter(), TRUE);
}
void QCharEditWidget_Diff_Eng::UpDataParas()
{
	//切换两个曲线页，保证共有参数一致
	ui.m_DiffTypeTab->setCurrentIndex(!ui.m_DiffTypeTab->currentIndex());
}
void QCharEditWidget_Diff_Eng::on_m_editCustomHarmIndex_editingFinished()
{
	if (ui.m_editCustomHarmIndex->text().toInt()>10)
	{
		ui.m_editCustomHarmIndex->setText("10");
	}
	m_oDiffCharCal.m_nHarmIndex = ui.m_editCustomHarmIndex->text().toInt()-2;
}
void QCharEditWidget_Diff_Eng::slot_UpdateCharByCombinedFeature()
{
	if (m_oDiffCharCal.CalCombinedFeature(ui.m_cmbCombinedFeature->currentIndex(), ui.m_cmbZeroSeqElimiType->currentIndex(), m_nTransGroupMode, m_nFaultType))
	{
		CalByCombinedFeature(m_oDiffCharCal.m_nIsCharRaised);
	}
	UpdateChar();
}

void QCharEditWidget_Diff_Eng::CalByCombinedFeature(BOOL bIsCharRaise)
{
	if (bIsCharRaise)
	{
		ui.m_edtSet_Istart->setText(QString::number(ui.m_edtSet_Istart->text().toFloat() * 2, 'f', 3));
		ui.m_edtSet_Ip1->setText(QString::number(ui.m_edtSet_Ip1->text().toFloat() * 2, 'f', 3));
		ui.m_edtSet_Ip2->setText(QString::number(ui.m_edtSet_Ip2->text().toFloat() * 2, 'f', 3));
		ui.m_edtSet_Ip3->setText(QString::number(ui.m_edtSet_Ip3->text().toFloat() * 2, 'f', 3));
	}
	else
	{
		ui.m_edtSet_Istart->setText(QString::number(ui.m_edtSet_Istart->text().toFloat() / 2, 'f', 3));
		ui.m_edtSet_Ip1->setText(QString::number(ui.m_edtSet_Ip1->text().toFloat() / 2, 'f', 3));
		ui.m_edtSet_Ip2->setText(QString::number(ui.m_edtSet_Ip2->text().toFloat() / 2, 'f', 3));
		ui.m_edtSet_Ip3->setText(QString::number(ui.m_edtSet_Ip3->text().toFloat() / 2, 'f', 3));
	}
}
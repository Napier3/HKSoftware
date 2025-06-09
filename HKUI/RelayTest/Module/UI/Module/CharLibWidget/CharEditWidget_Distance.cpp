#include "CharEditWidget_Distance.h"
#include "../ZKCharaCurve/QCharElementDlg.h"
#include "../ZKCharaCurve/QZKFeatureAddDig.h"
#include "../../SttTestCntrFrameAPI.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "QCharacteristicEditDlg.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/XLanguage/XLanguageResource.h"
#include "../../../../../AutoTest/Module/XLanguageResourceAts.h"

#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "CharEditMainWidget.h"
#include "../../../../../Module/System/TickCount32.h"
#include <QProcess>

#include "../../../TestUI/Distance/SttMultiMacroDistanceParasDefine.h"

#define GRID_CHAR_COLS		        3
#define GRID_PARAM_COLS		        3//4  20230411 暂时去除关联定值列
#define GRID_TESTPOINT_COLS         4

//////////////////////////////////////////////////////////////////////////
//曲线分段表
QCharEditGrid_Character::QCharEditGrid_Character(QWidget* pParent) : QCharEditGridBase(pParent)
{

}

QCharEditGrid_Character::~QCharEditGrid_Character()
{

}

void QCharEditGrid_Character::InitGridTitle()
{
	CString strZoomIndex, strFaultPhase, strName;
	xlang_GetLangStrByFile(strZoomIndex, "CharLib_ZoomIndex");
	xlang_GetLangStrByFile(strFaultPhase, "CharLib_FaultPhase");
	xlang_GetLangStrByFile(strName, "sName");

	CString astrGridTitle[GRID_CHAR_COLS] = {strZoomIndex, strFaultPhase, strName};
	int iGridWidth[GRID_CHAR_COLS]={80, 100, 180};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, GRID_CHAR_COLS);

	QExBaseListComBoxDelegBase* pZoomIndexDelegate = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(0, pZoomIndexDelegate);
	QExBaseListComBoxDelegBase* pFaultPhaseDelegate = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(1, pFaultPhaseDelegate);
}

void QCharEditGrid_Character::InitDataTypes()
{//20241011 luozibing 根据最新MacroTestDataType.xml配置文件区段值修改
	CDataType* pDataType = m_oTestDataTypes.AddNew2(_T("ZoomIndex"), _T("ZoomIndex"));
	pDataType->AddNewValue(_T("I"), _T("I"), _T("2"));
	pDataType->AddNewValue(_T("II"), _T("II"), _T("3"));
	pDataType->AddNewValue(_T("III"), _T("III"), _T("4"));
	pDataType->AddNewValue(_T("IV"), _T("IV"), _T("5"));
	pDataType->AddNewValue(_T("V"), _T("V"), _T("6"));

	pDataType = m_oTestDataTypes.AddNew2(_T("FaultPhase"), _T("FaultPhase"));
	pDataType->AddNewValue(_T("ALL"), _T("ALL"), _T("0"));
	pDataType->AddNewValue(_T("LN"), _T("LN"), _T("1"));
	pDataType->AddNewValue(_T("LL"), _T("LL"), _T("2"));
}

void QCharEditGrid_Character::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
	{
		return;
	}

	CCharacteristic* pChar = (CCharacteristic*)pData;

	Show_DataType_Index(pData, nRow, 0, "ZoomIndex", &pChar->m_strIndex, EndEditCell_ZoomIndex);
	Show_DataType_Val(pData, nRow, 1, "FaultPhase", &pChar->m_strID, EndEditCell_DataType_Val);
	Show_StaticString(pData, nRow, 2, pChar->m_strName);

	nRow++;
}

void QCharEditGrid_Character::slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	if(currentRow == previousRow)
	{
		return;
	}

	if (currentRow>=0)
	{
		OnDataSelChanged(currentRow,currentColumn);
	}

    QExBaseListGridBase::slot_CurrentCellChanged(currentRow, currentColumn, previousRow, previousColumn);

//	emit cellClicked(currentRow, currentColumn);
}

void QCharEditGrid_Character::EndEditCell_ZoomIndex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	if (pVCellData->pExBaseList == NULL)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Row=%d  Col=%d  数据类型对象不存在"), nRow, nCol);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DataTypeUnExist.GetString() , nRow, nCol); //数据类型对象不存在 lcq 3.14
		return;
	}

	CDataType *pDataType = (CDataType*)pVCellData->pExBaseList;
	ASSERT (pDataType != NULL);
	CString strTmp = pCell->text();

	CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByName(strTmp);

	if (pValue == NULL)
	{
	}
	else
	{
		*(pVCellData->pString) = pValue->m_strIndex;
		((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	}


// 	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
// 	ASSERT(pVCellData != NULL);
// 	ASSERT(pVCellData->pObj != NULL);
// 	CCharacteristic* pCurObj = (CCharacteristic*)pVCellData->pObj;
// 	pCurObj->m_strIndex = pCell->text();
}

void QCharEditGrid_Character::EndEditCell_FaultPhase(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CCharacteristic* pCurObj = (CCharacteristic*)pVCellData->pObj;
	pCurObj->m_strID = pCell->text();
}

//////////////////////////////////////////////////////////////////////////
//曲线参数接口表
QCharEditGrid_Param::QCharEditGrid_Param(QWidget* pParent) : QCharEditGridBase(pParent)
{
connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

QCharEditGrid_Param::~QCharEditGrid_Param()
{

}

void QCharEditGrid_Param::InitGridTitle()
{
	CString strName, strID, strNum, strAttach;
	xlang_GetLangStrByFile(strName, "sName");
	strID = "ID";
	xlang_GetLangStrByFile(strNum, "sValue");
//	xlang_GetLangStrByFile(strAttach, "CharLib_AttachSetting");

	CString astrGridTitle[GRID_PARAM_COLS] = {strName, strID, strNum/*, strAttach*/};
	int iGridWidth[GRID_PARAM_COLS]={100, 100, 100/*, 200*/};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, GRID_PARAM_COLS);

	QExBaseListComBoxDelegBase* pZoomIndexDelegate = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(2, pZoomIndexDelegate);
}
void QCharEditGrid_Param::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCharInterfaceVariable* pCurObj = (CCharInterfaceVariable*)pData;

	Show_StaticString(pData, nRow, 0, &pCurObj->m_strName);
	Show_StaticString(pData, nRow, 1, &pCurObj->m_strID);
	Show_String(pData, nRow, 2, &pCurObj->m_strValue, EndEditCell_String);

	
//	Show_StaticString(pData, nRow, 3, &pCurObj->m_strScript/*, EndEditCell_String*/);//2022-10-28  修改为不可编辑

	nRow++;
}
void QCharEditGrid_Param::slot_doubleClicked(int nRow,int nCol)
{
	GridDoubleClicked_ShowKeyBoard(nRow,nCol);
}


void QCharEditGrid_Param::GridDoubleClicked_ShowKeyBoard(int nRow,int nCol)
{
	if (nCol <= 0)
	{
		return;
	}

	QGV_ITEM *pParamItem = GetCell(nRow,nCol); 


	if (pParamItem == NULL)
	{
		return;
	}

	switch(nCol)
	{

	case 2: 
		{
			QString strValue = pParamItem->text();
			GetWidgetBoard_DigitData(4,strValue,pParamItem, parentWidget()->parentWidget());
			//pParamItem->setText(strValue);
		}
		break;
	default:
		break;

	}

}

//////////////////////////////////////////////////////////////////////////
//曲线测试点定义表
QCharEditGrid_TestPoint::QCharEditGrid_TestPoint(QWidget* pParent) : QCharEditGridBase(pParent)
{
	connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

QCharEditGrid_TestPoint::~QCharEditGrid_TestPoint()
{

}

void QCharEditGrid_TestPoint::InitGridTitle()
{
	CString strType, strCount, strErr, strInfo;
	xlang_GetLangStrByFile(strType, "sEdgeType");
	xlang_GetLangStrByFile(strCount, "sTestPoint");
	xlang_GetLangStrByFile(strErr, "sErrorBand");
	xlang_GetLangStrByFile(strInfo, "sEdgeDetails");

	CString astrGridTitle[GRID_TESTPOINT_COLS] = {strType, strCount, strErr, strInfo};
	int iGridWidth[GRID_TESTPOINT_COLS]={100, 75, 75, 700};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, GRID_TESTPOINT_COLS);

	QExBaseListComBoxDelegBase* pEdgeTypeDelegate = new QExBaseListComBoxDelegBase(this);
	pEdgeTypeDelegate->SetEditable(FALSE);
	setItemDelegateForColumn(0, pEdgeTypeDelegate);

}

void QCharEditGrid_TestPoint::InitDataTypes()
{
	CDataType* pDataType = m_oTestDataTypes.AddNew2(_T("EdgeType"), _T("EdgeType"));
// 	pDataType->AddNewValue(_T("线段(lined)"), CHAR_ELEMENT_ID_LINED, _T("0"));
// 	pDataType->AddNewValue(_T("圆(mho)"), CHAR_ELEMENT_ID_MHO, _T("1"));
// 	pDataType->AddNewValue(_T("透镜(lens)"), CHAR_ELEMENT_ID_LENS, _T("2"));
// 	pDataType->AddNewValue(_T("射线(liner)"), CHAR_ELEMENT_ID_LINER, _T("3"));
// 	pDataType->AddNewValue(_T("直线(line)"), CHAR_ELEMENT_ID_LINE, _T("4"));
// 	pDataType->AddNewValue(_T("圆弧(arc)"), CHAR_ELEMENT_ID_ARC, _T("5"));
// 	pDataType->AddNewValue(_T("圆弧(arcp)"), CHAR_ELEMENT_ID_ARCP, _T("6"));


	pDataType->AddNewValue(g_sLangTxt_Lined, CHAR_ELEMENT_ID_LINED, STT_CHAR_ELEMENT_TYPE_LINED); //线段 lcq 3.14
	pDataType->AddNewValue(g_sLangTxt_Mho, CHAR_ELEMENT_ID_MHO, STT_CHAR_ELEMENT_TYPE_MHO); //圆 lcq 3.14
	pDataType->AddNewValue(g_sLangTxt_Lens, CHAR_ELEMENT_ID_LENS, STT_CHAR_ELEMENT_TYPE_LENS); //透镜 lcq 3.14
	pDataType->AddNewValue(g_sLangTxt_Liner, CHAR_ELEMENT_ID_LINER,STT_CHAR_ELEMENT_TYPE_LINER); //射线 lcq 3.14
	pDataType->AddNewValue(g_sLangTxt_Line, CHAR_ELEMENT_ID_LINE, STT_CHAR_ELEMENT_TYPE_LINE); //直线 lcq 3.14
	pDataType->AddNewValue(g_sLangTxt_Arcp, CHAR_ELEMENT_ID_ARC, STT_CHAR_ELEMENT_TYPE_ARC); //圆弧 lcq 3.14
	pDataType->AddNewValue(g_sLangTxt_Arcp, CHAR_ELEMENT_ID_ARCP, STT_CHAR_ELEMENT_TYPE_ARCP); //圆弧 lcq 3.14

}

void QCharEditGrid_TestPoint::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CString strText;
	CCharElement* pCurObj = (CCharElement*)pData;
	Show_DataType_Val(pData, nRow, 0, FindTestDataType("EdgeType"), &pCurObj->m_strID);
	Show_Long(pData, nRow, 1, pCurObj->GetTestPointsRef(), TRUE, _T(""), EndEditCell_Long);
	Show_StaticString(pData, nRow, 2, &pCurObj->m_strErrLength/*, EndEditCell_String*/);//2022-10-28  修改为不可编辑
	strText = pCurObj->ReturnXml();
	Show_StaticString(pData, nRow, 3, strText);

	
	nRow++;
}

void QCharEditGrid_TestPoint::slot_doubleClicked(int nRow,int nCol)
{
	GridDoubleClicked_ShowKeyBoard(nRow,nCol);


}


void QCharEditGrid_TestPoint::GridDoubleClicked_ShowKeyBoard(int nRow,int nCol)
{
	if (nCol <= 0)
	{
		return;
	}

	QGV_ITEM *pTestPointItem = GetCell(nRow,nCol); 

	if (pTestPointItem ==NULL)
	{
		return;
	}

	switch(nCol)
	{

	case 1: 
		{
			QString strValue = pTestPointItem->text();
			GetWidgetBoard_DigitData(4,strValue,pTestPointItem, parentWidget()->parentWidget());
			//pTestPointItem->setText(strValue);
		}
		break;
	default:
		break;

	}


}

//////////////////////////////////////////////////////////////////////////
//距离widget
QCharEditWidget_Distance::QCharEditWidget_Distance(QWidget* pParent /* = NULL */) : QWidget(pParent)
{
	m_pMain_VLayout = NULL;
	m_pCharAddHLayout = NULL;
	m_pAddCharPushButton = NULL;
	m_pDeleteCharPushButton = NULL;
	m_pEditCharPushButton = NULL;
	m_pCustom_GroupBox = NULL;
	m_pImpCustomPointsGrid = NULL;

	m_pCharEditWidget = this;

	m_pGridCharacter = NULL;

	InitUI();
	InitConnect();
	InitChar();
	UpdateCharacters(FALSE);
	SetDistanceFont();
	UpdateBtnEnable();
}

QCharEditWidget_Distance::~QCharEditWidget_Distance()
{

}

void QCharEditWidget_Distance::InitUI()
{
	CString strText;
	m_pMain_VLayout = new QVBoxLayout(this);
	m_pCharAddHLayout = new QHBoxLayout(this);

	strText = /*_T("添加")*/g_sLangTxt_Add; //lcq
	m_pAddCharPushButton = new QPushButton(strText);
	strText = /*_T("编辑")*/g_sLangTxt_Edit; //lcq
	m_pEditCharPushButton = new QPushButton(strText);	
	strText = /*_T("删除")*/g_sLangTxt_Delete; //lcq
	m_pDeleteCharPushButton = new QPushButton(strText);

	m_pCharAddHLayout->addWidget(m_pAddCharPushButton);
	m_pCharAddHLayout->addWidget(m_pEditCharPushButton);
	m_pCharAddHLayout->addWidget(m_pDeleteCharPushButton);

	m_pMain_VLayout->addLayout(m_pCharAddHLayout);

	m_pGridCharacter = new QCharEditGrid_Character(this);
	m_pGridCharacter->InitGrid();
	m_pGridCharacter->AttachDataViewOptrInterface(this);
	m_pMain_VLayout->addWidget(m_pGridCharacter);

	strText = /*_T("自定义测试点")*/g_sLangTxt_Gradient_Custestp; //lcq
	m_pCustom_GroupBox = new QGroupBox(strText,this);
	m_pCustom_VLayout = new QVBoxLayout(m_pCustom_GroupBox);
	m_pCustom_GroupBox->setLayout(m_pCustom_VLayout);
	m_pCustomAdd_HLayout = new QHBoxLayout(m_pCustom_GroupBox);

	m_pImpCustomPointsGrid = new QImpCustomPointsGrid(this);
	m_pImpCustomPointsGrid->InitGrid();

	strText = /*_T("添加自定义点")*/g_sLangTxt_Gradient_AddCusp;//lcq
	m_pAddCustomPoint_PushButton = new QPushButton(strText);
	m_pCustomAdd_HLayout->addWidget(m_pAddCustomPoint_PushButton);

	strText = /*_T("阻抗表达方式")*/g_sLangTxt_Gradient_Impedance;//lcq
	m_pRXType_Label = new QLabel(strText);
	m_pCustomAdd_HLayout->addWidget(m_pRXType_Label);

	m_pZPhi_Radio = new QRadioButton(tr("Z,Phi"),this);
	m_pCustomAdd_HLayout->addWidget(m_pZPhi_Radio);

	m_pRX_Radio = new QRadioButton(tr("R,X"),this);
	m_pCustomAdd_HLayout->addWidget(m_pRX_Radio);

	m_pCustom_VLayout->addWidget(m_pImpCustomPointsGrid);
	m_pCustom_VLayout->addLayout(m_pCustomAdd_HLayout);
	m_pMain_VLayout->addWidget(m_pCustom_GroupBox);
}


void QCharEditWidget_Distance::InitConnect()
{
	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	connect(m_pAddCharPushButton, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnAddClicked()));
	connect(m_pEditCharPushButton, SIGNAL(clicked ()), this, SLOT(slot_btnEditCharClicked()));
	connect(m_pDeleteCharPushButton, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnDelClicked()));
	connect(this, SIGNAL(sig_CharChanged(CExBaseObject *,int)), pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *,int)));
}

void QCharEditWidget_Distance::InitChar()
{
	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	pMainWidget->UpdateCharAxisType(AXIS_TYPE_ID_CARTES,TRUE);
	pMainWidget->m_pImpCharactWidget->EnableSetting(TRUE);
	pMainWidget->m_pImpCharactWidget->setObjectName(QString::fromUtf8("QImpCharactWidget"));
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetAxisName(_T("R"),_T("X"),_T("R-X(omg)"));
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T("Ω"), _T("°"));
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(true);
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowAng(true);
}


void QCharEditWidget_Distance::slot_ZkAddChar(CCharacteristic *pObj)
{
	CCharacteristic *pNew = (CCharacteristic*)pObj->Clone();
	CCharacterArea *pCharArea = (CCharacterArea *)pNew->GetCharacterArea();
	CCharElement *pElement = (CCharElement*)pCharArea->GetAtIndex(0);
	if (pElement != NULL)
	{
		if (pElement->GetClassID()>=CHARCLASSID_CCHARELEMENTI2T && pElement->GetClassID()<=CHARCLASSID_CCHARELEMENTIEEE)
		{
            stt_Frame_Characteristics()->RemoveAll();
            stt_Frame_Characteristics()->AddNewChild(pNew);
			UpdateCharacters(TRUE);
		}
		else
		{
            stt_Frame_Characteristics()->AddNewChild(pNew);
			AddCharacter();
		}
	}
	UpdateZKFeature(/*pNew,*/ TRUE);
	emit sig_CharChanged(NULL,TRUE);
}

void QCharEditWidget_Distance::slot_ZkPbnAddClicked()
{
	m_pDeleteCharPushButton->setDisabled(false);

	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	QZKFeatureAddDig dig(stt_Frame_TestMacroUI()->m_strCharlibFile);
	dig.setFont(*g_pSttGlobalFont);
	// 	connect(&dig,SIGNAL(sig_clickOK(CCharacteristic*)),this,SLOT(slot_ZkAddChar(CCharacteristic*)));
	// 	dig.exec();
	// 	disconnect(&dig,SIGNAL(sig_clickOK(CCharacteristic*)),this,SLOT(slot_ZkAddChar(CCharacteristic*)));

	if (dig.exec() != QDialog::Accepted)
	{
		return;
	}

	slot_ZkAddChar(dig.GetSelectedChar());
}

void QCharEditWidget_Distance::slot_btnEditCharClicked()
{
	CCharacteristic *pCurrCharaObj =  (CCharacteristic*)m_pGridCharacter->GetCurrSelData();

	if (pCurrCharaObj == NULL)
	{
		return;
	}

	QCharacteristicEditDlg oCharacteristicEditDlg(pCurrCharaObj,this);
	oCharacteristicEditDlg.InitUI();

	if (oCharacteristicEditDlg.exec() == QDialog::Accepted)
	{
	}
}

void QCharEditWidget_Distance::slot_ZkPbnDelClicked()
{
	if (m_pGridCharacter == NULL)
	{
		return;
	}

	CExBaseObject *pCurrObj =  m_pGridCharacter->GetCurrSelData();

	if (pCurrObj == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ASSIST,/*_T("请先选择需要删除的特性曲线")*/g_sLangTxt_Gradient_SelectCur.GetString());
		return;
	}
	//删除功能有错误,原因是目前lib库和配置文件内的图形ID都是一致的(故障相)
	//除非每个图的故障相不一致,删除才正确

	m_pGridCharacter->DeleteDataRow(pCurrObj);
	UpdateZKFeature(TRUE);
	UpdateBtnEnable();
	emit sig_CharChanged(NULL,TRUE);
}

void QCharEditWidget_Distance::UpdateZKFeature(BOOL bSetting)
{
	if (m_pGridCharacter == NULL)
	{
		return;
	}

	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();

	pMainWidget->m_bSetting = bSetting;
}

void QCharEditWidget_Distance::UpdateCharacters(BOOL bCharChaged)
{
	CCharacteristic *pChar = NULL;
	m_pGridCharacter->setRowCount(0);
    m_pGridCharacter->ShowDatas(stt_Frame_Characteristics());
	int rowCount = m_pGridCharacter->rowCount();
	m_pGridCharacter->setFocus();
	m_pGridCharacter->SelectRow(1);

	UpdateZKFeature(TRUE);
	emit sig_CharChanged(NULL,bCharChaged);
}

void QCharEditWidget_Distance::AddCharacter()
{
	int rowCount = m_pGridCharacter->rowCount();
    m_pGridCharacter->ShowDatas(stt_Frame_Characteristics());
	m_pGridCharacter->setFocus();
	m_pGridCharacter->setCurrentCell(rowCount,2);
}

void QCharEditWidget_Distance::SetDistanceFont()
{
	m_pGridCharacter->setFont(*g_pSttGlobalFont);
	m_pGridCharacter->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pImpCustomPointsGrid->setFont(*g_pSttGlobalFont);
	m_pImpCustomPointsGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);

	m_pAddCharPushButton->setFont(*g_pSttGlobalFont);
	m_pDeleteCharPushButton->setFont(*g_pSttGlobalFont);
	m_pEditCharPushButton->setFont(*g_pSttGlobalFont);

	m_pCustom_GroupBox->setFont(*g_pSttGlobalFont);
	m_pRXType_Label->setFont(*g_pSttGlobalFont);
	m_pZPhi_Radio->setFont(*g_pSttGlobalFont);
	m_pRX_Radio->setFont(*g_pSttGlobalFont);
	m_pAddCustomPoint_PushButton->setFont(*g_pSttGlobalFont);
}

void QCharEditWidget_Distance::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	UpdateBtnEnable();
	if (m_pGridCharacter == NULL)
	{
		return;
	}

	if (pGridCtrl == m_pGridCharacter)
	{
		UpdateZKFeature(TRUE);
	}
}

void QCharEditWidget_Distance::UpdateBtnEnable()
{
	if (m_pGridCharacter != NULL)
	{
		if (m_pGridCharacter->GetCurrSelData() != NULL)
		{
			m_pDeleteCharPushButton->setEnabled(true);
		} 
		else
		{
			m_pDeleteCharPushButton->setEnabled(false);
		}
	}
	else
	{
		m_pDeleteCharPushButton->setEnabled(false);
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//距离widget
QCharEditWidget_DistanceSearch::QCharEditWidget_DistanceSearch(QWidget* pParent /* = NULL */) : QWidget(pParent)
{
	m_pMain_VLayout = NULL;
	m_pCharAddHLayout = NULL;
	m_pCharElementHLayout = NULL;
	m_pAddCharPushButton = NULL;
	m_pDeleteCharPushButton = NULL;
	m_pEditCharPushButton = NULL;
	m_pInsert_Button = NULL;
	m_pModify_Button = NULL;
	m_pDelete_Button = NULL;

	m_pCharEditWidget = this;
//	ui.setupUi(this);

	m_pGridCharacter = 0;
	m_pGridParam = 0;
	m_pGridTestPoint = 0;

	InitUI();
	InitConnect();
	InitChar();
	UpdateCharacters(FALSE);

#ifdef _PSX_QT_LINUX_
	m_pEditCharPushButton->hide();
#endif
	SetDistanceFont();
	UpdateBtnEnable();
}

QCharEditWidget_DistanceSearch::~QCharEditWidget_DistanceSearch()
{
	m_oLineCache.DeleteAll();
}

void QCharEditWidget_DistanceSearch::InitUI()
{
	CString strText;
	m_pMain_VLayout = new QVBoxLayout(this);
	m_pCharAddHLayout = new QHBoxLayout(this);

	strText = /*_T("添加")*/g_sLangTxt_Add; //lcq
	m_pAddCharPushButton = new QPushButton(strText);
	strText = /*_T("删除")*/g_sLangTxt_Delete; //lcq
	m_pDeleteCharPushButton = new QPushButton(strText);
	strText = /*_T("曲线编辑")*/g_sLangTxt_Gradient_CurveEditing; //lcq
	m_pEditCharPushButton = new QPushButton(strText);
	m_pCharAddHLayout->addWidget(m_pAddCharPushButton);
	m_pCharAddHLayout->addWidget(m_pDeleteCharPushButton);
	m_pCharAddHLayout->addWidget(m_pEditCharPushButton);

	m_pCharElementHLayout = new QHBoxLayout(this);
	m_pMain_VLayout->addLayout(m_pCharAddHLayout);

	m_pGridCharacter = new QCharEditGrid_Character(this);
	m_pGridCharacter->InitGrid();
	m_pGridCharacter->AttachDataViewOptrInterface(this);
	m_pMain_VLayout->insertWidget(1, m_pGridCharacter);

	m_pGridParam = new QCharEditGrid_Param(this);
	m_pGridParam->InitGrid();
	m_pMain_VLayout->insertWidget(2, m_pGridParam);

	m_pGridTestPoint = new QCharEditGrid_TestPoint(this);
	m_pGridTestPoint->InitGrid();
	m_pGridTestPoint->AttachDataViewOptrInterface(this);
	m_pMain_VLayout->insertWidget(3, m_pGridTestPoint);

	strText = /*_T("插入元素")*/g_sLangTxt_Gradient_InsertElement;//lcq
	m_pInsert_Button = new QPushButton(strText);
	strText = /*_T("修改元素")*/g_sLangTxt_Gradient_ModifyElement;//lcq
	m_pModify_Button = new QPushButton(strText);
	strText = /*_T("删除元素")*/g_sLangTxt_Gradient_DeleteElement; //lcq
	m_pDelete_Button = new QPushButton(strText);
	m_pCharElementHLayout->addWidget(m_pInsert_Button);
	m_pCharElementHLayout->addWidget(m_pModify_Button);
	m_pCharElementHLayout->addWidget(m_pDelete_Button);

	m_pMain_VLayout->addLayout(m_pCharElementHLayout);
}


void QCharEditWidget_DistanceSearch::InitConnect()
{
	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	connect(m_pAddCharPushButton, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnAddClicked()));
	connect(m_pEditCharPushButton, SIGNAL(clicked ()), this, SLOT(slot_btnEditCharClicked()));
	connect(m_pDeleteCharPushButton, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnDelClicked()));
	connect(m_pInsert_Button, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnInsertClicked()));
	connect(m_pDelete_Button, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnRemoveClicked()));
	connect(m_pModify_Button, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnEditClicked()));
	connect(this, SIGNAL(sig_CharChanged(CExBaseObject *,int)), pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *,int)));
	connect(m_pGridParam, SIGNAL(sig_CharChanged(CExBaseObject *)), pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *)));
	connect(m_pGridTestPoint, SIGNAL(sig_CharChanged(CExBaseObject *)), pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *)));
}

void QCharEditWidget_DistanceSearch::InitChar()
{
	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	pMainWidget->UpdateCharAxisType(AXIS_TYPE_ID_CARTES,TRUE);
	pMainWidget->m_pImpCharactWidget->EnableSetting(TRUE);
	pMainWidget->m_pImpCharactWidget->setObjectName(QString::fromUtf8("QImpCharactWidget"));
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetAxisName(_T("R"),_T("X"),_T("R-X(omg)"));
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T("Ω"), _T("°"));
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(true);
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowAng(true);
}


void QCharEditWidget_DistanceSearch::slot_ZkAddChar(CCharacteristic *pObj)
{
	CCharacteristic *pNew = (CCharacteristic*)pObj->Clone();
	CCharacterArea *pCharArea = (CCharacterArea *)pNew->GetCharacterArea();
	CCharElement *pElement = (CCharElement*)pCharArea->GetAtIndex(0);
	if (pElement != NULL)
	{
		if (pElement->GetClassID()>=CHARCLASSID_CCHARELEMENTI2T && pElement->GetClassID()<=CHARCLASSID_CCHARELEMENTIEEE)
		{
            stt_Frame_Characteristics()->RemoveAll();
            stt_Frame_Characteristics()->AddNewChild(pNew);
			UpdateCharacters(TRUE);
		}
		else
		{
            stt_Frame_Characteristics()->AddNewChild(pNew);
			AddCharacter();
		}
	}
	UpdateZKFeature(/*pNew,*/ TRUE);
	emit sig_CharChanged(NULL,TRUE);
}

void QCharEditWidget_DistanceSearch::slot_ZkPbnAddClicked()
{
 	m_pDeleteCharPushButton->setDisabled(false);

	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	QZKFeatureAddDig dig(stt_Frame_TestMacroUI()->m_strCharlibFile);
	dig.setFont(*g_pSttGlobalFont);
// 	connect(&dig,SIGNAL(sig_clickOK(CCharacteristic*)),this,SLOT(slot_ZkAddChar(CCharacteristic*)));
// 	dig.exec();
// 	disconnect(&dig,SIGNAL(sig_clickOK(CCharacteristic*)),this,SLOT(slot_ZkAddChar(CCharacteristic*)));

	if (dig.exec() != QDialog::Accepted)
	{
		return;
	}

	slot_ZkAddChar(dig.GetSelectedChar());
}

void QCharEditWidget_DistanceSearch::slot_btnEditCharClicked()
{
#ifndef _PSX_QT_LINUX_
	m_pEditCharPushButton->setEnabled(false);
	CTickCount32 oTickCount;
	oTickCount.DoEvents(10);
	QProcess oProcess;
	QStringList astrList;
	CString strStartExe,strSendMsg;
	strStartExe = _P_GetInstallPath();
	strStartExe+= _T("e-Report/Bin/CharLibDev.exe");

	strSendMsg = _P_GetConfigPath();
	strSendMsg += _T("CharLib-distance.xml");

	astrList<<strSendMsg;
	oProcess.execute(strStartExe, astrList);
	m_pEditCharPushButton->setEnabled(true);
#endif
}

void QCharEditWidget_DistanceSearch::slot_ZkPbnDelClicked()
{
	if (m_pGridCharacter == NULL)
	{
		return;
	}

	CExBaseObject *pCurrObj =  m_pGridCharacter->GetCurrSelData();

	if (pCurrObj == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ASSIST,/*_T("请先选择需要删除的特性曲线")*/g_sLangTxt_Gradient_SelectCur.GetString());
		return;
	}
	//删除功能有错误,原因是目前lib库和配置文件内的图形ID都是一致的(故障相)
	//除非每个图的故障相不一致,删除才正确

	m_pGridCharacter->DeleteDataRow(pCurrObj);
	UpdateZKFeature(TRUE);
	UpdateBtnEnable();
	emit sig_CharChanged(NULL,TRUE);
}

void QCharEditWidget_DistanceSearch::slot_ZkPbnInsertClicked()
{
	CCharacteristic *pCurrCharaObj =  (CCharacteristic*)m_pGridCharacter->GetCurrSelData();

	if (pCurrCharaObj == NULL)
	{
		return;
	}

	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	QCharElementDlg dlg(NULL,this);
	dlg.InitParaCache(&m_oLineCache);
	dlg.setFont(*g_pSttGlobalFont);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg,Keyboard::NUMBER);
#endif

	if (dlg.exec() != QDialog::Accepted)
	{
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::ReAttachObj();
#endif
		return;
	}
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif

	CCharacterArea *pCharArea = pCurrCharaObj->GetCharacterArea();
	CCharElement *pNew = dlg.GetNewElement();
	CCharElement *pCurrSelElement = (CCharElement*)m_pGridTestPoint->GetCurrSelData();

	if (pNew->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
	{
		pCharArea->DeleteChildren();
		pCharArea->AddNewChild(pNew);
	}
	else if (pCurrSelElement != NULL)
	{
		pCharArea->InsertAfter(pCharArea->Find(pCurrSelElement),pNew);
		pNew->SetParent(pCharArea);
	} 
	else
	{
	pCharArea->AddNewChild(pNew);
	}

	int rowCount = m_pGridTestPoint->rowCount();
	m_pGridTestPoint->ShowDatas(pCharArea);
	m_pGridTestPoint->setFocus();
	m_pGridTestPoint->setCurrentCell(rowCount,2);
	emit sig_CharChanged(NULL,TRUE);

	m_pDelete_Button->setEnabled(true);
};

void QCharEditWidget_DistanceSearch::slot_ZkPbnRemoveClicked()
{
	CExBaseObject *pCurrLine = m_pGridTestPoint->GetCurrSelData();
	CCharacteristic *pCurrCharaOb =  (CCharacteristic*)m_pGridCharacter->GetCurrSelData();

	if ((pCurrCharaOb == NULL)||(pCurrLine == NULL))
	{
		return;
	}

	CCharacterArea *pCharArea = pCurrCharaOb->GetCharacterArea();
	m_pGridTestPoint->DeleteDataRow(pCurrLine);

	emit sig_CharChanged(NULL,TRUE);
	m_pGridTestPoint->setCurrentCell(0,2);	
	UpdateBtnEnable();
}

void QCharEditWidget_DistanceSearch::slot_ZkPbnEditClicked()
{
	CCharElement *pObj = (CCharElement*)m_pGridTestPoint->GetCurrSelData();
	CCharacteristic *pCurrCharaOb =  (CCharacteristic*)m_pGridCharacter->GetCurrSelData();

	if ((pObj == NULL)||(pCurrCharaOb == NULL))
	{
		return;
	}

	CCharacterArea *pCharArea = pCurrCharaOb->GetCharacterArea();

	QCharElementDlg dlg(pObj,this);
	dlg.setFont(*g_pSttGlobalFont);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg,Keyboard::NUMBER);
#endif

	if (dlg.exec() != QDialog::Accepted)
	{
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::ReAttachObj();
#endif
		return;
	}
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif

	if (dlg.GetNewElement()->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
	{
		pCharArea->DeleteChildren();
		pCharArea->AddNewChild(dlg.GetNewElement());
	}
	else if (pObj->GetClassID() == dlg.GetNewElement()->GetClassID())
		{
			dlg.GetNewElement()->Copy(pObj);
		}
		else
		{
		CCharElement* pNewElement = dlg.GetNewElement();
		pCharArea->InsertAfter(pCharArea->Find(pObj),pNewElement);
			pCharArea->Delete(pObj);
		pNewElement->SetParent(pCharArea);

// 		pCharArea->Delete(pObj);
// 		pCharArea->AddNewChild(dlg.GetNewElement());
	}

	m_pGridTestPoint->ShowDatas(pCharArea);
	emit sig_CharChanged(NULL,TRUE);
}

void QCharEditWidget_DistanceSearch::UpdateZKFeature(BOOL bSetting)
{
	if (m_pGridCharacter == NULL)
	{
		return;
	}

	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();

	pMainWidget->m_bSetting = bSetting;
	ShowGridDatas_CharElements();
	ShowGridDatas_CharVariables();
}

void QCharEditWidget_DistanceSearch::UpdateCharacters(BOOL bCharChaged)
{
	CCharacteristic *pChar = NULL;
	m_pGridCharacter->setRowCount(0);
    m_pGridCharacter->ShowDatas(stt_Frame_Characteristics());
	int rowCount = m_pGridCharacter->rowCount();
	m_pGridCharacter->setFocus();
	m_pGridCharacter->SelectRow(1);

	UpdateZKFeature(TRUE);
	emit sig_CharChanged(NULL,bCharChaged);
}

void QCharEditWidget_DistanceSearch::AddCharacter()
{
	int rowCount = m_pGridCharacter->rowCount();
    m_pGridCharacter->ShowDatas(stt_Frame_Characteristics());
	m_pGridCharacter->setFocus();
	m_pGridCharacter->setCurrentCell(rowCount,2);
}

void QCharEditWidget_DistanceSearch::ShowGridDatas_CharElements()
{
	CCharacteristic *pCurrCharaOb =  (CCharacteristic*)m_pGridCharacter->GetCurrSelData();

	if (pCurrCharaOb)
	{
		m_pGridTestPoint->ShowDatas(pCurrCharaOb->GetCharacterArea());
	} 
	else
	{
		m_pGridTestPoint->ShowDatas(NULL);
	}
	
}

void QCharEditWidget_DistanceSearch::ShowGridDatas_CharVariables()
{
	CCharacteristic *pCurrCharaOb =  (CCharacteristic*)m_pGridCharacter->GetCurrSelData();

	if (pCurrCharaOb)
	{
		m_pGridParam->ShowDatas(pCurrCharaOb->GetCharInterface());
	}
	else
	{
		m_pGridParam->ShowDatas(NULL);
	}
}

void QCharEditWidget_DistanceSearch::SetDistanceFont()
{
	m_pGridCharacter->setFont(*g_pSttGlobalFont);
	m_pGridCharacter->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pGridParam->setFont(*g_pSttGlobalFont);
	m_pGridParam->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pGridTestPoint->setFont(*g_pSttGlobalFont);
	m_pGridTestPoint->horizontalHeader()->setFont(*g_pSttGlobalFont);

	m_pAddCharPushButton->setFont(*g_pSttGlobalFont);
	m_pDeleteCharPushButton->setFont(*g_pSttGlobalFont);
	m_pDelete_Button->setFont(*g_pSttGlobalFont);
	m_pInsert_Button->setFont(*g_pSttGlobalFont);
	m_pEditCharPushButton->setFont(*g_pSttGlobalFont);
	m_pModify_Button->setFont(*g_pSttGlobalFont);
}

void QCharEditWidget_DistanceSearch::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	UpdateBtnEnable();
	CCharElement *pCurrSelElement = (CCharElement*)m_pGridTestPoint->GetCurrSelData();
	if (pCurrSelElement == NULL)
	{
		return;
	}

	if (m_pGridCharacter == NULL)
	{
		return;
	}

	if (pGridCtrl == m_pGridCharacter)
	{
		UpdateZKFeature(TRUE);
	}

	//20230731 wxy 激活线段
	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	
	if (pMainWidget != NULL)
	{
		pMainWidget->UI_SetActiveElement((CXDrawElement*)pCurrSelElement->m_pDataRef);
	}

}

void QCharEditWidget_DistanceSearch::UpdateBtnEnable()
{
	if (m_pGridCharacter != NULL)
	{
		if (m_pGridCharacter->GetCurrSelData() != NULL)
		{
			m_pDeleteCharPushButton->setEnabled(true);
		} 
		else
		{
			m_pDeleteCharPushButton->setEnabled(false);
		}
	}
	else
	{
		m_pDeleteCharPushButton->setEnabled(false);
	}
	
	if (m_pGridTestPoint->GetCurrSelData() != NULL)
	{
		m_pModify_Button->setEnabled(true);
		m_pDelete_Button->setEnabled(true);
	} 
	else
	{
		m_pModify_Button->setEnabled(false);
		m_pDelete_Button->setEnabled(false);
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QCharEditWidget_DistSearchOne::QCharEditWidget_DistSearchOne(QWidget* pParent ) : QWidget(pParent)
{
	m_pCharEditWidget = this;
	m_pMain_VLayout = NULL;
	m_pSelectHLayout = NULL;
	m_pCharElementHLayout = NULL;
	m_pInsert_Button = NULL;
	m_pModify_Button = NULL;
	m_pDelete_Button = NULL;

	m_pGridParam = 0;
	m_pGridTestPoint = 0;

	InitUI();
	InitConnect();
	InitChar();
	UpdateCharacters(FALSE);

// #ifdef _PSX_QT_LINUX_
// 	ui.m_btnEditChar->hide();
// #endif
	SetDistanceFont();
	UpdateBtnEnable();
}

QCharEditWidget_DistSearchOne::~QCharEditWidget_DistSearchOne()
{
	m_oLineCache.DeleteAll();
}

void QCharEditWidget_DistSearchOne::InitUI()
{
	CString strText;
	m_pMain_VLayout = new QVBoxLayout(this);
	m_pSelectHLayout = new QHBoxLayout(this);

	strText = /*_T("名称")*/g_sLangTxt_Name; //lcq
	m_pNameLabel = new QLabel(strText);
	m_pNameEdit = new QSttLineEdit;
	strText = /*_T("选择")*/g_sLangTxt_Select; //lcq
	m_pSelectPushButton = new QPushButton(strText);
	m_pSelectHLayout->addWidget(m_pNameLabel);
	m_pSelectHLayout->addWidget(m_pNameEdit);
	m_pSelectHLayout->addWidget(m_pSelectPushButton);
	m_pCharElementHLayout = new QHBoxLayout(this);
 	m_pMain_VLayout->addLayout(m_pSelectHLayout);

	strText = /*_T("插入元素")*/g_sLangTxt_Gradient_InsertElement; //lcq
	m_pInsert_Button = new QPushButton(strText);
	strText = /*_T("修改元素")*/g_sLangTxt_Gradient_ModifyElement; //lcq
	m_pModify_Button = new QPushButton(strText);
	strText = /*_T("删除元素")*/g_sLangTxt_Gradient_DeleteElement; //lcq
	m_pDelete_Button = new QPushButton(strText);
	m_pCharElementHLayout->addWidget(m_pInsert_Button);
	m_pCharElementHLayout->addWidget(m_pModify_Button);
	m_pCharElementHLayout->addWidget(m_pDelete_Button);

 	m_pMain_VLayout->addLayout(m_pCharElementHLayout);

	m_pGridTestPoint = new QCharEditGrid_TestPoint(this);
	m_pGridTestPoint->InitGrid();
	m_pGridTestPoint->AttachDataViewOptrInterface(this);
	m_pMain_VLayout->addWidget(m_pGridTestPoint);

	m_pGridParam = new QCharEditGrid_Param(this);
	m_pGridParam->InitGrid();
	m_pMain_VLayout->addWidget(m_pGridParam);
}

CCharacteristic* QCharEditWidget_DistSearchOne::GetCharacteristic()
{
    if (stt_Frame_Characteristics() == NULL)
	{
		return NULL;
	}

    CCharacteristic *pCharacteristic = (CCharacteristic*)stt_Frame_Characteristics()->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
	return pCharacteristic;
}


void QCharEditWidget_DistSearchOne::InitConnect()
{
	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	connect(m_pSelectPushButton, SIGNAL(clicked()), this, SLOT(slot_ZkPbnAddClicked()));
//	connect(ui.m_btnEditChar, SIGNAL(clicked ()), this, SLOT(slot_btnEditCharClicked()));
	connect(m_pInsert_Button, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnInsertClicked()));
	connect(m_pDelete_Button, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnRemoveClicked()));
	connect(m_pModify_Button, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnEditClicked()));
	connect(this, SIGNAL(sig_CharChanged(CExBaseObject *,int)), pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *,int)));
	connect(m_pGridParam, SIGNAL(sig_CharChanged(CExBaseObject *)), pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *)));
	connect(m_pGridTestPoint, SIGNAL(sig_CharChanged(CExBaseObject *)), pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *)));
	connect(m_pNameEdit, SIGNAL(editingFinished()), this, SLOT(slot_Name_editingFinished()));
}

void QCharEditWidget_DistSearchOne::InitChar()
{
	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	pMainWidget->UpdateCharAxisType(AXIS_TYPE_ID_CARTES,TRUE);
	pMainWidget->m_pImpCharactWidget->EnableSetting(TRUE);
	pMainWidget->m_pImpCharactWidget->setObjectName(QString::fromUtf8("QImpCharactWidget"));
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetAxisName(_T("R"),_T("X"),_T("R-X(omg)"));
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T("Ω"), _T("°"));
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(true);
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowAng(true);
}


void QCharEditWidget_DistSearchOne::slot_ZkAddChar(CCharacteristic *pObj)
{
	CCharacteristic *pNew = (CCharacteristic*)pObj->Clone();
    stt_Frame_Characteristics()->DeleteAll();
    stt_Frame_Characteristics()->AddNewChild(pNew);
	UpdateZKFeature(/*pNew,*/ TRUE);
	emit sig_CharChanged(NULL,TRUE);
}

void QCharEditWidget_DistSearchOne::slot_ZkPbnAddClicked()
{
//	ui.m_btnDel->setDisabled(false);

	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	QZKFeatureAddDig dig(stt_Frame_TestMacroUI()->m_strCharlibFile);
	dig.setFont(*g_pSttGlobalFont);
//	connect(&dig,SIGNAL(sig_clickOK(CCharacteristic*)),this,SLOT(slot_ZkAddChar(CCharacteristic*)));

	if (dig.exec() != QDialog::Accepted)
	{
		return;
	}

	slot_ZkAddChar(dig.GetSelectedChar());
//	disconnect(&dig,SIGNAL(sig_clickOK(CCharacteristic*)),this,SLOT(slot_ZkAddChar(CCharacteristic*)));
}

void QCharEditWidget_DistSearchOne::slot_btnEditCharClicked()
{
// #ifndef _PSX_QT_LINUX_
// 	ui.m_btnEditChar->setEnabled(false);
// 	CTickCount32 oTickCount;
// 	oTickCount.DoEvents(10);
// 	QProcess oProcess;
// 	QStringList astrList;
// 	CString strStartExe,strSendMsg;
// 	strStartExe = _P_GetInstallPath();
// 	strStartExe+= _T("e-Report/Bin/CharLibDev.exe");
// 
// 	strSendMsg = _P_GetConfigPath();
// 	strSendMsg += _T("CharLib-distance.xml");
// 
// 	astrList<<strSendMsg;
// 	oProcess.execute(strStartExe, astrList);
// 	ui.m_btnEditChar->setEnabled(true);
// #endif
}


void QCharEditWidget_DistSearchOne::slot_ZkPbnInsertClicked()
{
	CCharacteristic *pCurrCharaObj = GetCharacteristic();

	if (pCurrCharaObj == NULL)
	{
		return;
	}

	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	QCharElementDlg dlg(NULL,this);
	dlg.InitParaCache(&m_oLineCache);
	dlg.setFont(*g_pSttGlobalFont);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg,Keyboard::NUMBER);
#endif

	if (dlg.exec() != QDialog::Accepted)
	{
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::ReAttachObj();
#endif
		return;
	}
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif

	CCharacterArea *pCharArea = pCurrCharaObj->GetCharacterArea();
	CCharElement *pNew = dlg.GetNewElement();
	CCharElement *pCurrSelElement = (CCharElement*)m_pGridTestPoint->GetCurrSelData();
	//记录用户输入
	if(m_oLineCache.FindByID(pNew->m_strID))
	{
		m_oLineCache.DeleteByID(pNew->m_strID);
	}
	m_oLineCache.AddNewChild((CCharElement*)pNew->Clone());

	if (pNew->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
	{
		pCharArea->DeleteChildren();
		pCharArea->AddNewChild(pNew);
	}
	else if (pCurrSelElement == NULL)
	{
	pCharArea->AddNewChild(pNew);
	}
	else
	{
		pCharArea->InsertAfter(pCharArea->Find(pCurrSelElement),pNew);
		pNew->SetParent(pCharArea);
	}

	int rowCount = m_pGridTestPoint->rowCount();
	m_pGridTestPoint->ShowDatas(pCharArea);
	m_pGridTestPoint->setFocus();
	m_pGridTestPoint->setCurrentCell(rowCount,2);
	emit sig_CharChanged(NULL,TRUE);

	m_pDelete_Button->setEnabled(true);
};

void QCharEditWidget_DistSearchOne::slot_ZkPbnRemoveClicked()
{
	CCharacteristic *pCurrCharaOb = GetCharacteristic();
	CExBaseObject *pCurrLine = m_pGridTestPoint->GetCurrSelData();

	if ((pCurrCharaOb == NULL)||(pCurrLine == NULL))
	{
		return;
	}

	CCharacterArea *pCharArea = pCurrCharaOb->GetCharacterArea();
	m_pGridTestPoint->DeleteDataRow(pCurrLine);

	emit sig_CharChanged(NULL,TRUE);

	m_pGridTestPoint->setCurrentCell(0,2);	
	UpdateBtnEnable();
}

void QCharEditWidget_DistSearchOne::slot_ZkPbnEditClicked()
{
	CCharElement *pObj = (CCharElement*)m_pGridTestPoint->GetCurrSelData();

	if (pObj == NULL)
	{
		return;
	}

	CCharacteristic *pCurrCharaOb = GetCharacteristic();
	CCharacterArea *pCharArea = pCurrCharaOb->GetCharacterArea();
	QCharElementDlg dlg(pObj,this);
	dlg.setFont(*g_pSttGlobalFont);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg,Keyboard::NUMBER);
#endif

	if (dlg.exec() != QDialog::Accepted)
	{
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::ReAttachObj();
#endif
		return;
	}
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif

	if (dlg.GetNewElement()->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
	{
		pCharArea->DeleteChildren();
		pCharArea->AddNewChild(dlg.GetNewElement());
	}
	else if (pObj->GetClassID() == dlg.GetNewElement()->GetClassID())
		{
			dlg.GetNewElement()->Copy(pObj);
		}
		else
		{
		CCharElement* pNewElement = dlg.GetNewElement();
		pCharArea->InsertAfter(pCharArea->Find(pObj),pNewElement);
			pCharArea->Delete(pObj);
		pNewElement->SetParent(pCharArea);
		//pCharArea->AddNewChild();
	}

	m_pGridTestPoint->ShowDatas(pCharArea);
	emit sig_CharChanged(NULL,TRUE);
}

void QCharEditWidget_DistSearchOne::slot_Name_editingFinished()
{
	CCharacteristic *pCurrCharaOb = GetCharacteristic();

	if (pCurrCharaOb != NULL)
	{
		pCurrCharaOb->m_strName = m_pNameEdit->text();
	}
}

void QCharEditWidget_DistSearchOne::UpdateZKFeature(BOOL bSetting)
{
	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();
	CCharacteristic *pCurrCharaOb = GetCharacteristic();

	if (pCurrCharaOb != NULL)
	{
		m_pNameEdit->setText(pCurrCharaOb->m_strName);
	}

	pMainWidget->m_bSetting = bSetting;
	ShowGridDatas_CharElements();
	ShowGridDatas_CharVariables();
}

void QCharEditWidget_DistSearchOne::UpdateCharacters(BOOL bCharChaged)
{
	UpdateZKFeature( TRUE);
	emit sig_CharChanged(NULL,bCharChaged);
}

void QCharEditWidget_DistSearchOne::ShowGridDatas_CharElements()
{
	CCharacteristic *pCurrCharaOb = GetCharacteristic();

	if (pCurrCharaOb)
	{
		m_pGridTestPoint->ShowDatas(pCurrCharaOb->GetCharacterArea());
	} 
	else
	{
		m_pGridTestPoint->ShowDatas(NULL);
	}

}

void QCharEditWidget_DistSearchOne::ShowGridDatas_CharVariables()
{
	CCharacteristic *pCurrCharaOb = GetCharacteristic();

	if (pCurrCharaOb)
	{
		m_pGridParam->ShowDatas(pCurrCharaOb->GetCharInterface());
	}
	else
	{
		m_pGridParam->ShowDatas(NULL);
	}
}

void QCharEditWidget_DistSearchOne::SetDistanceFont()
{
	m_pGridParam->setFont(*g_pSttGlobalFont);
	m_pGridParam->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pGridTestPoint->setFont(*g_pSttGlobalFont);
	m_pGridTestPoint->horizontalHeader()->setFont(*g_pSttGlobalFont);

	m_pSelectPushButton->setFont(*g_pSttGlobalFont);
	m_pNameEdit->setFont(*g_pSttGlobalFont);
	m_pDelete_Button->setFont(*g_pSttGlobalFont);
	m_pInsert_Button->setFont(*g_pSttGlobalFont);
	m_pNameLabel->setFont(*g_pSttGlobalFont);
	m_pModify_Button->setFont(*g_pSttGlobalFont);
}

void QCharEditWidget_DistSearchOne::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	UpdateBtnEnable();
	CCharElement *pCurrSelElement = (CCharElement*)m_pGridTestPoint->GetCurrSelData();

	if (pCurrSelElement == NULL)
	{
		return;
	}

	QCharEditMainWidget* pMainWidget = (QCharEditMainWidget*)parentWidget();

	if (pMainWidget != NULL)
	{
		pMainWidget->UI_SetActiveElement((CXDrawElement*)pCurrSelElement->m_pDataRef);
	}
}

void QCharEditWidget_DistSearchOne::UpdateBtnEnable()
{
	if (m_pGridTestPoint->GetCurrSelData() != NULL)
	{
		m_pModify_Button->setEnabled(true);
		m_pDelete_Button->setEnabled(true);
	} 
	else
	{
		m_pModify_Button->setEnabled(false);
		m_pDelete_Button->setEnabled(false);
	}
}

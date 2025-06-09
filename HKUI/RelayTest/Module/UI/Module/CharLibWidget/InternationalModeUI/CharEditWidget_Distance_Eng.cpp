#include "CharEditWidget_Distance_Eng.h"
#include "../../ZKCharaCurve/QCharElementDlg.h"
#include "../../ZKCharaCurve/QZKFeatureAddDig.h"
#include "../../../SttTestCntrFrameAPI.h"
#include "../../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/CommonMethod/commonMethod.h"
#include "../QCharacteristicEditDlg.h"
#include "../../../../XLangResource_Native.h"
#include "../../../../../../Module/XLanguage/XLanguageResource.h"
#include "../../../../../../AutoTest/Module/XLanguageResourceAts.h"

#ifdef _USE_SoftKeyBoard_
#include "../../../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "CharEditMainDialog.h"
#include "../../../../../../Module/System/TickCount32.h"
#include <QProcess>
#include"../../../../TestUI/SttMultiMacroParasDefine.h"
//#include "../../../../TestUI/Distance/SttMultiMacroDistanceParasDefine.h"
//#include "../../../../TestUI/DistanceSearch/SttMultiMacroDistanceSearchParasDefine.h"
#include "../../../../UI/SttTestCntrCmdDefine.h"
#include <QMessageBox>
#include <QSplitter>
#include "../../../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "QSingleCharCurveEditDlg.h"

//zhouhj 2024.10.1 各模块公共宏定义移到公共位置,其它宏定义各模块负责人自己处理
//#define STT_MULTI_MACRO_PARAS_RelErrorMaxValue 100//20240929 luozibing 设置相对误差绝对误差取值范围
//#define STT_MULTI_MACRO_PARAS_RelErrorMinValue 0
//#define STT_MULTI_MACRO_PARAS_AbsErrorMaxValue 200
//#define STT_MULTI_MACRO_PARAS_AbsErrorMinValue 0
//////////////////////////////////////////////////////////////////////////
//曲线分段表
QCharEditGrid_Character_Eng::QCharEditGrid_Character_Eng(QWidget* pParent) :
	QCharEditGrid_Character(pParent)
{
}

QCharEditGrid_Character_Eng::~QCharEditGrid_Character_Eng()
{

}

void QCharEditGrid_Character_Eng::InitGridTitle()
{
	CString strZoomIndex, strFaultPhase, strName,strUseZone;
	xlang_GetLangStrByFile(strZoomIndex, "CharLib_ZoomIndex");
	xlang_GetLangStrByFile(strFaultPhase, "CharLib_FaultPhase");
	xlang_GetLangStrByFile(strName, "sName");
	xlang_GetLangStrByFile(strUseZone, "CharacterEng_UseZone");

	CString astrGridTitle[4] = {strZoomIndex, strFaultPhase, strName,strUseZone};
	int iGridWidth[4]={80, 80, 100, 80};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 4);

	QExBaseListComBoxDelegBase* pZoomIndexDelegate = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(0, pZoomIndexDelegate);
	QExBaseListComBoxDelegBase* pFaultPhaseDelegate = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(1, pFaultPhaseDelegate);
	QExBaseListCheckBoxDelegate* pUseZoneDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(3, pUseZoneDelegate);
}

void QCharEditGrid_Character_Eng::InitDataTypes()
{
	CDataType* pDataType = m_oTestDataTypes.AddNew2(_T("ZoomIndex"), _T("ZoomIndex"));
	pDataType->AddNewValue(_T("I"), _T("I"), _T("2"));
	pDataType->AddNewValue(_T("II"), _T("II"), _T("3"));
	pDataType->AddNewValue(_T("III"), _T("III"), _T("4"));
	pDataType->AddNewValue(_T("IV"), _T("IV"), _T("5"));
	pDataType->AddNewValue(_T("V"), _T("V"), _T("6"));

	//20240903 luozibing 曲线故障相分为LN/LL/LLN/LLL
	pDataType = m_oTestDataTypes.AddNew2(_T("FaultPhase"), _T("FaultPhase"));
	pDataType->AddNewValue(CHAR_DISTANCE_FAULT_TYPE_LN, CHAR_DISTANCE_FAULT_TYPE_LN, _T("0"));//距离保护故障类型-单相接地故障/单相阻抗
	pDataType->AddNewValue(CHAR_DISTANCE_FAULT_TYPE_LL, CHAR_DISTANCE_FAULT_TYPE_LL, _T("1"));//距离保护故障类型-相间故障
	pDataType->AddNewValue(CHAR_DISTANCE_FAULT_TYPE_LLN, CHAR_DISTANCE_FAULT_TYPE_LLN, _T("2"));//距离保护故障类型-相间接地故障
	pDataType->AddNewValue(CHAR_DISTANCE_FAULT_TYPE_LLL, CHAR_DISTANCE_FAULT_TYPE_LLL, _T("3"));//距离保护故障类型-三相故障
	pDataType->AddNewValue(CHAR_DISTANCE_FAULT_TYPE_ALL, CHAR_DISTANCE_FAULT_TYPE_ALL, _T("4"));//距离保护故障类型-三相故障
}
void QCharEditGrid_Character_Eng::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_oInitCharacter.DeleteAll();
	QCharEditGrid_Character::ShowDatas(pDatas,bResetScrollBars);
}
void QCharEditGrid_Character_Eng::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
	{
		return;
	}

	CCharacteristic* pChar = (CCharacteristic*)pData;
	
// 	CDataType* pFaultPhaseType = (CDataType*)m_oTestDataTypes.FindByID("FaultPhase");
// 	if (pFaultPhaseType->FindByID(pChar->m_strID) == NULL)
// 	{
// 		pChar->m_strID = pFaultPhaseType->GetHead()->m_strID;
// 	}
	Show_DataType_Index(pData, nRow, 0, "ZoomIndex", &pChar->m_strIndex, EndEditCell_ZoomIndex_Eng);
	Show_DataType_Val(pData, nRow, 1, "FaultPhase", &pChar->m_strID, EndEditCell_FaultPhase_Eng);
	Show_StaticString(pData, nRow, 2, pChar->m_strName);

	CExBaseList *pDatas = GetDatas();
	CExBaseObject *pCurrObj = NULL;
	POS pos = pDatas->GetHeadPosition();
	while(pos != NULL)
	{
		pCurrObj = pDatas->GetNext(pos);

		if (pCurrObj->GetClassID() != CHARCLASSID_CCHARACTERISTIC || pCurrObj == pChar)
		{
			continue;
		}
		CCharacteristic* pOtherChar = (CCharacteristic*)pCurrObj;
		if (pOtherChar->m_nUse == 0)
		{
			continue;
		}
		if (pChar->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL)//20240914 luozibing 当前选择曲线id为ALL有相同id则认为相同
		{
			if (pOtherChar->m_strIndex == pChar->m_strIndex\
				&&pOtherChar->m_nUse == 1 && pChar->m_nUse == 1)
		{
				pChar->m_nUse = 0;
			}
		}
		else
		{
		if (pOtherChar->m_strID == pChar->m_strID &&pOtherChar->m_strIndex == pChar->m_strIndex\
				&&pOtherChar->m_nUse == 1 && pChar->m_nUse != 0)
		{
				pChar->m_nUse = 0;
		}
	}
	}
	Show_Check(pData, nRow, 3, (long*)(&pChar->m_nUse), EndEditCell_Check_UseZone_Eng);

	QGV_ITEM *pCell = GetCell(nRow,0);
	m_oInitCharacter.AddNew(pCell->text(),pChar->m_strID);
	nRow++;
}
void QCharEditGrid_Character_Eng::EndEditCell_ZoomIndex_Eng(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	//存在相同区段与故障项不修改
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	QCharEditGrid_Character_Eng *pEngGrid = (QCharEditGrid_Character_Eng *)pGrid;

	CDataType* pDataType = (CDataType*)pEngGrid->m_oTestDataTypes.FindByID("ZoomIndex");
	CExBaseObject *pData = pEngGrid->m_oInitCharacter.GetAt(nRow);
	//20240723 luozibing 根据OMICRON增强距离,具有相同区段相同故障类型时,不能修改
	int nOtherRow = pEngGrid->FindTheSameZoomAndFault(nRow,pGrid);
	if (nOtherRow != -1)
	{
		CCharacteristic* pChar = (CCharacteristic*)pGrid->GetData(nRow,nCol);
		pChar->m_strIndex = pData->m_strName;
		pCell->setText(pData->m_strName);
		return;
	}
	pData->m_strName = pCell->text();
	QCharEditGrid_Character::EndEditCell_ZoomIndex(nRow,nCol,pCell,pGrid);
}
void QCharEditGrid_Character_Eng::EndEditCell_FaultPhase_Eng(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	//存在相同区段与故障项不修改
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	QCharEditGrid_Character_Eng *pEngGrid = (QCharEditGrid_Character_Eng *)pGrid;
	CExBaseObject *pData = pEngGrid->m_oInitCharacter.GetAt(nRow);
	//20240723 luozibing 根据OMICRON增强距离,具有相同区段相同故障类型时,弹出提示并不允许修改
	int nOtherRow = pEngGrid->FindTheSameZoomAndFault(nRow,pGrid);
	if (nOtherRow != -1)
	{
		CCharacteristic* pChar = (CCharacteristic*)pGrid->GetData(nRow,nCol);
		pChar->m_strID = pData->m_strID;
		pCell->setText(pData->m_strID);
		QMessageBox::warning(NULL,g_sLangTxt_CharacterEng_FaulTipTile,g_sLangTxt_CharacterEng_FaulTips);
		return;
	}
	pData->m_strID = pCell->text();
	QCharEditGrid_Character::EndEditCell_DataType_Val(nRow,nCol,pCell,pGrid);
}
void QCharEditGrid_Character_Eng::EndEditCell_Check_UseZone_Eng(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	//ASSERT(pVCellData->pObj != NULL);
	CValue* pValue = NULL;
	QCharEditGrid_Character_Eng *pEngGrid = (QCharEditGrid_Character_Eng *)pGrid;

	CCharacteristic *pData = (CCharacteristic *)pGrid->GetData(nRow,nCol);
	pData->m_nUse = pCell->dwValue;
	//20240912 luozibing 当前选择ALL类型使用,取消所有相同区段的选择状态
	if (pData->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL)
	{
		for (int i = 0; i < pGrid->rowCount(); i++)
		{
			if (i == nRow)
			{
				continue;
			}
			CCharacteristic* pOtherChar = (CCharacteristic*)pGrid->GetData(i, nCol);
			if (pOtherChar->m_strIndex == pData->m_strIndex)
			{
				pOtherChar->m_nUse = 0;
				QGV_ITEM* pOtherCell = pGrid->GetCell(i, nCol);
				pOtherCell->setCheckState(Qt::Unchecked);
			}
			
		}
	}
	else
	{
	//20240723 luozibing 根据OMICRON增强距离,启动同一区段相同故障类型时,取消前一个启动项并选中当前项
		int nOtherRow = pEngGrid->FindTheSameZoomAndFault(nRow, pGrid);
	if (nOtherRow != -1)
	{
			CCharacteristic* pOtherChar = (CCharacteristic*)pGrid->GetData(nOtherRow, nCol);
			pOtherChar->m_nUse = 0;
			QGV_ITEM* pOtherCell = pGrid->GetCell(nOtherRow, nCol);
		pOtherCell->setCheckState(Qt::Unchecked);
	}
	}

}
int QCharEditGrid_Character_Eng::FindTheSameZoomAndFault(int nRow, QExBaseListGridBase *pGrid)
{
	int nCol = 3;
	CCharacteristic* pChar = NULL;
	CCharacteristic* pOtherChar = NULL;

	CExBaseObject *pData = pGrid->GetData(nRow, nCol);
	pChar = (CCharacteristic*)pData;
	if (pChar->m_nUse == 1)
	{
		for (int i = 0;i<pGrid->rowCount();i++)
		{
			if (i == nRow)
			{
				continue;
			}
			pOtherChar = (CCharacteristic*)pGrid->GetData(i,nCol);
			if (pOtherChar->m_nUse == 1)
			{
				//20240912 luozibing 当前选择为ALL类型时存在相同区段曲线则视为相同
				if (pChar->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL || pOtherChar->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL)
				{
					if (pOtherChar->m_strIndex == pChar->m_strIndex)
					{
						return i;
					}
				}
				else
				{
				if (pOtherChar->m_strIndex == pChar->m_strIndex&&
					pOtherChar->m_strID == pChar->m_strID)
				{
					return i;
				}
			}
				
			}
		}
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////
//曲线参数接口表
QCharEditGrid_Param_Eng::QCharEditGrid_Param_Eng(QWidget* pParent) : 
	QCharEditGrid_Param(pParent)
{
}

QCharEditGrid_Param_Eng::~QCharEditGrid_Param_Eng()
{

}

void QCharEditGrid_Param_Eng::InitGridTitle()
{
	CString strName, strID, strNum, strAttach;
	xlang_GetLangStrByFile(strName, "sName");
	xlang_GetLangStrByFile(strNum, "sValue");
	//	xlang_GetLangStrByFile(strAttach, "CharLib_AttachSetting");

	CString astrGridTitle[2] = {strName,strNum/*, strAttach*/};
	int iGridWidth[2]={100,100/*, 200*/};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 2);

	QExBaseListComBoxDelegBase* pZoomIndexDelegate = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(1, pZoomIndexDelegate);
}
void QCharEditGrid_Param_Eng::InitDataTypes()
{
	CDataType*pListTemp = (CDataType  *)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_PARAS_DATATYPE_ID_RltErrorLogic_Time);
	m_oTestDataTypes.AddNewChild((CDataType *)pListTemp->Clone());
	//InitDistance_ErrorDataType(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC);
	//InitDistance_ErrorDataType(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC);
}
void QCharEditGrid_Param_Eng::InitDistance_ErrorDataType(const CString &strErrorZone)
{
	/*CDataType* pDataType = m_oTestDataTypes.AddNew2(strErrorZone,strErrorZone);
	pDataType->AddNewValue(g_sLangTxt_StateEstimate_AbsError, _T("0"), _T("0"));
	pDataType->AddNewValue(g_sLangTxt_StateEstimate_RelError, _T("1"), _T("1"));
	pDataType->AddNewValue(g_sLangTxt_Distance_ErrorRelorAbs, _T("2"), _T("2"));
	pDataType->AddNewValue(g_sLangTxt_Distance_ErrorRelAndAbs, _T("3"), _T("3"));
	pDataType->AddNewValue(g_sLangTxt_StateEstimate_CombinationError, _T("4"), _T("4"));
	pDataType->AddNewValue(g_sLangTxt_Distance_ErrorNot, _T("5"), _T("5"));*/
}
void QCharEditGrid_Param_Eng::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCharInterfaceVariable* pCurObj = (CCharInterfaceVariable*)pData;

	Show_StaticString(pData, nRow, 0, &pCurObj->m_strName);
	//20241011 luozibing 距离模块曲线编辑页面移出误差类型
	if (/*pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC || */pCurObj->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC)
	{
		//Show_DataType_Index(pData, nRow, 1, pData->m_strID, &pCurObj->m_strValue, EndEditCell_DataType_Val);
		Show_DataType_Index(pData, nRow, 1, STT_MULTI_MACRO_PARAS_DATATYPE_ID_RltErrorLogic_Time, &pCurObj->m_strValue);
	}
	/*else if (pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5)*/
	else if (pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING ||
             pCurObj->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING)
	{
		//Show_String(pData, nRow, 1, &pCurObj->m_strValue, EndEditCell_CheckBit);	//20241017 huangliang 改变对象的值
		Show_String_Object(pData, nRow, 1, &pCurObj->m_strValue, EndEditCell_CheckBit);
	}
	else if (pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS ||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS||
		pCurObj->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR)
	{
		//Show_String(pData, nRow, 1, &pCurObj->m_strValue, EndEditCell_CheckBit_AbsError);	//20241017 huangliang 改变对象的值
		Show_String_Object(pData, nRow, 1, &pCurObj->m_strValue, EndEditCell_CheckBit_AbsError);
	}
	else if (pCurObj->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR||
             pCurObj->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR)
	{
		//Show_String(pData, nRow, 1, &pCurObj->m_strValue, EndEditCell_CheckBit_RelError);	//20241017 huangliang 改变对象的值
		Show_String_Object(pData, nRow, 1, &pCurObj->m_strValue, EndEditCell_CheckBit_RelError);
	}
	else
	{
		//Show_String(pData, nRow, 1, &pCurObj->m_strValue, EndEditCell_String);	//20241017 huangliang 改变对象的值
		Show_String_Object(pData, nRow, 1, &pCurObj->m_strValue, EndEditCell_String);
	}
	nRow++;
}
void QCharEditGrid_Param_Eng::EndEditCell_CheckBit_AbsError(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{//20240929 luozibing 绝对正/负误差设置取值范围
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CString strValue = pCell->text();
	double dTmp = strValue.toDouble();
	if (dTmp < STT_MULTI_MACRO_PARAS_AbsErrorMinValue)
	{
		dTmp = STT_MULTI_MACRO_PARAS_AbsErrorMinValue;
	}
	else if (dTmp > STT_MULTI_MACRO_PARAS_AbsErrorMaxValue)
	{
		dTmp = STT_MULTI_MACRO_PARAS_AbsErrorMaxValue;
	}
	strValue.Format("%.3f", dTmp);
	pCell->setText(strValue);
	*(pVCellData->pString) = pCell->text();
	((QCharEditGridBase*)pGrid)->EmitCharChanged();
}
void QCharEditGrid_Param_Eng::EndEditCell_CheckBit_RelError(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{//20240929 luozibing 相对误差设置取值范围
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CString strValue = pCell->text();
	double dTmp = strValue.toDouble();
	if (dTmp<STT_MULTI_MACRO_PARAS_RelErrorMinValue)
	{
		dTmp = STT_MULTI_MACRO_PARAS_RelErrorMinValue;
	}
	else if (dTmp > STT_MULTI_MACRO_PARAS_RelErrorMaxValue)
	{
		dTmp = STT_MULTI_MACRO_PARAS_RelErrorMaxValue;
	}
	strValue.Format("%.3f", dTmp);
	pCell->setText(strValue);
	*(pVCellData->pString) = pCell->text();
	((QCharEditGridBase*)pGrid)->EmitCharChanged();
}
void QCharEditGrid_Param_Eng::EndEditCell_CheckBit(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CString strValue = pCell->text();
	double dTmp = strValue.toDouble();
	strValue.Format("%.3f",dTmp);
	pCell->setText(strValue);
	*(pVCellData->pString) = pCell->text();
	((QCharEditGridBase*)pGrid)->EmitCharChanged();

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//距离widget
QCharEditWidget_DistanceSearch_Eng::QCharEditWidget_DistanceSearch_Eng(QWidget* pParent /* = NULL */) : QWidget(pParent)
{
	m_pMain_VLayout = NULL;
	m_pCharAddHLayout = NULL;
	m_pAddCharPushButton = NULL;
	m_pDeleteCharPushButton = NULL;
	m_pEditCharPushButton = NULL;

	m_pCharEditWidget = this;
//	ui.setupUi(this);

	m_pGridCharacter = 0;
	m_pGridParam = 0;
	m_pCharacteristics_Inner = NULL;

	InitChar();//20240809 luozibing 获取克隆的唯一变量
	InitUI();
	InitConnect();
	UpdateCharacters(FALSE);

#ifdef _PSX_QT_LINUX_
	m_pEditCharPushButton->hide();
#endif
	SetDistanceFont();
	UpdateBtnEnable();

	QCharEditMainDialog* pMainWidget = (QCharEditMainDialog*)parentWidget();
	pMainWidget->m_pImpCharactWidget->SetShowCurrCharactColor(TRUE);	//20241025 wanmj 选中特性曲线变色
}

QCharEditWidget_DistanceSearch_Eng::~QCharEditWidget_DistanceSearch_Eng()
{
	m_oLineCache.DeleteAll();
// 	if (m_pCharacteristics_Inner != NULL)
// 	{
// 		m_pCharacteristics_Inner->DeleteAll();
// 		delete m_pCharacteristics_Inner;
// 		m_pCharacteristics_Inner = NULL;
// 	}
}

void QCharEditWidget_DistanceSearch_Eng::InitUI()
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

	m_pMain_VLayout->addLayout(m_pCharAddHLayout);

	m_pGridCharacter = new QCharEditGrid_Character_Eng(this);
	m_pGridCharacter->InitGrid();
	m_pGridCharacter->AttachDataViewOptrInterface(this);
	m_pMain_VLayout->insertWidget(1, m_pGridCharacter);

	m_pGridParam = new QCharEditGrid_Param_Eng(this);
	m_pGridParam->InitGrid();
	m_pMain_VLayout->insertWidget(2, m_pGridParam);

}

void QCharEditWidget_DistanceSearch_Eng::InitConnect()
{
	QCharEditMainDialog* pMainWidget = (QCharEditMainDialog*)parentWidget();
	connect(m_pAddCharPushButton, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnAddClicked()));
	connect(m_pEditCharPushButton, SIGNAL(clicked ()), this, SLOT(slot_btnEditCharClicked()));
	connect(m_pDeleteCharPushButton, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnDelClicked()));
	connect(this, SIGNAL(sig_CharChanged(CExBaseObject *,int)), pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *,int)));
	connect(m_pGridParam, SIGNAL(sig_CharChanged(CExBaseObject *)), pMainWidget,SLOT(slot_UpdateDrawCharacters(CExBaseObject *)));
}

void QCharEditWidget_DistanceSearch_Eng::InitChar()
{
	QCharEditMainDialog* pMainWidget = (QCharEditMainDialog*)parentWidget();
	pMainWidget->UpdateCharAxisType(AXIS_TYPE_ID_CARTES,TRUE);
	pMainWidget->m_pImpCharactWidget->SetChangePlot(TRUE);
	pMainWidget->m_pImpCharactWidget->EnableSetting(TRUE);
	pMainWidget->m_pImpCharactWidget->setObjectName(QString::fromUtf8("QCharactEditWidget_Eng"));
    pMainWidget->m_pImpCharactWidget->SetAxisName(_T("R/Ω   "),_T("X/Ω   "),g_sLangTxt_Distance_ImpActBorder/*("阻抗动作边界")*/);
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowAng(true);
	pMainWidget->m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
	if (m_pCharacteristics_Inner == NULL)
	{//20240809 luozibing 坐标轴显示数据为唯一变量则克隆唯一变量，指针指向不为唯一变量数据则获取复制变量
	/*	if (pMainWidget->m_pImpCharactWidget->m_pCharacteristics == stt_Frame_Characteristics())
		{
			m_pCharacteristics_Inner = (CCharacteristics *)stt_Frame_Characteristics()->Clone();
			pMainWidget->m_pImpCharactWidget->m_pCharacteristics = m_pCharacteristics_Inner;
		}
		else
		{
			m_pCharacteristics_Inner = pMainWidget->m_pImpCharactWidget->m_pCharacteristics;
		}*/
		//20240815 luozibing 为空时获取父窗口内部对象
		m_pCharacteristics_Inner = pMainWidget->GetCharacteristics_Inner();
	}
	pMainWidget->resize(800, 660);
	//m_oCharacteristics__Inner.AppendClone(stt_Frame_Characteristics());
}


void QCharEditWidget_DistanceSearch_Eng::slot_ZkAddChar(CCharacteristic *pObj)
{
	CCharacteristic *pNew = (CCharacteristic*)pObj->Clone();
	CCharacterArea *pCharArea = (CCharacterArea *)pNew->GetCharacterArea();
	CCharElement *pElement = (CCharElement*)pCharArea->GetAtIndex(0);
	if (pElement != NULL)
	{
		if (pElement->GetClassID()>=CHARCLASSID_CCHARELEMENTI2T && pElement->GetClassID()<=CHARCLASSID_CCHARELEMENTIEEE)
		{
             /*stt_Frame_Characteristics()->RemoveAll();
             stt_Frame_Characteristics()->AddNewChild(pNew);*/
            m_pCharacteristics_Inner->DeleteAll();
            m_pCharacteristics_Inner->AddNewChild(pNew);

			UpdateCharacters(TRUE);
		}
		else
		{
			//stt_Frame_Characteristics()->AddNewChild(pNew);
            m_pCharacteristics_Inner->AddNewChild(pNew);
			AddCharacter();
		}
	}
	UpdateZKFeature(/*pNew,*/ TRUE);
	emit sig_CharChanged(NULL, TRUE);
}

void QCharEditWidget_DistanceSearch_Eng::slot_ZkPbnAddClicked()
{
 	m_pDeleteCharPushButton->setDisabled(false);

	QCharEditMainDialog* pMainWidget = (QCharEditMainDialog*)parentWidget();
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

void QCharEditWidget_DistanceSearch_Eng::slot_btnEditCharClicked()
{
    //20241016 wanmj 曲线编辑窗口用QSingleCharCurveEditDlg类封装
	CCharacteristic *pCurrCharaObj =  (CCharacteristic*)m_pGridCharacter->GetCurrSelData();
    if(pCurrCharaObj == NULL)
        return;

    QSingleCharCurveEditDlg oEditDlg(pCurrCharaObj);
    if(oEditDlg.exec() == QDialog::Accepted)
    {
        emit sig_CharChanged(NULL,TRUE);
    }
}

void QCharEditWidget_DistanceSearch_Eng::slot_ZkPbnDelClicked()
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

void QCharEditWidget_DistanceSearch_Eng::UpdateZKFeature(BOOL bSetting)
{
	if (m_pGridCharacter == NULL)
	{
		return;
	}

	QCharEditMainDialog* pMainWidget = (QCharEditMainDialog*)parentWidget();

	pMainWidget->m_bSetting = bSetting;
	ShowGridDatas_CharVariables();

    //20241025 wanmj 更新选中特性曲线颜色
    CCharacteristic *pCurCharaObj = (CCharacteristic*)m_pGridCharacter->GetCurrSelData();
    if(pCurCharaObj != NULL)
    {
        pMainWidget->m_pImpCharactWidget->SetCurCharact(pCurCharaObj);
    }

}

void QCharEditWidget_DistanceSearch_Eng::UpdateCharacters(BOOL bCharChaged)
{
	CCharacteristic *pChar = NULL;
	m_pGridCharacter->setRowCount(0);
	m_pGridCharacter->ShowDatas(m_pCharacteristics_Inner);
	int rowCount = m_pGridCharacter->rowCount();
	m_pGridCharacter->setFocus();
	m_pGridCharacter->SelectRow(1);

	UpdateZKFeature(TRUE);
	emit sig_CharChanged(NULL,bCharChaged);
}

void QCharEditWidget_DistanceSearch_Eng::AddCharacter()
{
	int rowCount = m_pGridCharacter->rowCount();
	m_pGridCharacter->ShowDatas(m_pCharacteristics_Inner);
	m_pGridCharacter->setFocus();
	m_pGridCharacter->setCurrentCell(rowCount,2);
}

void QCharEditWidget_DistanceSearch_Eng::ShowGridDatas_CharVariables()
{
	CCharacteristic *pCurrCharaOb =  (CCharacteristic*)m_pGridCharacter->GetCurrSelData();

	if (pCurrCharaOb)
	{
		CExBaseList *pParas = pCurrCharaOb->GetCharInterface();
		CheckZoneParas(pParas);
        m_pGridParam->ShowDatas(pParas);
	}
	else
	{
		m_pGridParam->ShowDatas(NULL);
	}
}
void QCharEditWidget_DistanceSearch_Eng::CheckZoneParas(CExBaseList *pParas)
{
		CCharInterfaceVariable* pNewData = NULL;
    if(m_strUI_ID == STT_ORG_MACRO_DistanceTest_I)
    {
	if(FindTSeting(pParas) == NULL)
		{
			pNewData = new CCharInterfaceVariable();
			pNewData->m_strName = g_sLangTxt_DistanceSearch_ActionTime;//动作时间
			//pNewData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1;
			pNewData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING;
			pNewData->m_strValue = "0.00";
			pParas->AddTail(pNewData);
		}
	if(FindErrorLogic(pParas) == NULL)
		{
	//20241011 luozibing 距离模块曲线编辑页面移出误差类型
		//pNewData = new CCharInterfaceVariable();
		//pNewData->m_strName = g_sLangTxt_StateEstimate_ErrorType;//误差类型
		////pNewData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1;
		//pNewData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC;
		//pNewData->m_strValue = "0";
		//pParas->AddTail(pNewData);
		}
	if(FindRelErr(pParas) == NULL)
		{
			pNewData = new CCharInterfaceVariable();
			pNewData->m_strName = g_sLangTxt_StateEstimate_RelError;//相对误差
			//pNewData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1;
			pNewData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR;
			pNewData->m_strValue = "0.010";
			pParas->AddTail(pNewData);
		}
	if(FindAbsErr_Plus(pParas) == NULL)
		{
			pNewData = new CCharInterfaceVariable();
			pNewData->m_strName = g_sLangTxt_Distance_AbsErrPlus;//绝对误差(+)
			//pNewData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1;
			pNewData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS;
			pNewData->m_strValue = "1.000";
			pParas->AddTail(pNewData);
		}
	if(FindAbsErr_Minus(pParas) == NULL)
		{
			pNewData = new CCharInterfaceVariable();
			pNewData->m_strName = g_sLangTxt_Distance_AbsErrMinus;//绝对误差(-)
			//pNewData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1;
			pNewData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS;
			pNewData->m_strValue = "1.000";
			pParas->AddTail(pNewData);
		}
    }
    else if(m_strUI_ID == STT_ORG_MACRO_DistanceSearchTest_I)
    {
        if(FindTSeting(pParas) == NULL)
        {
            pNewData = new CCharInterfaceVariable();
            pNewData->m_strName = g_sLangTxt_DistanceSearch_ActionTime;//动作时间
            pNewData->m_strID = STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING;
            pNewData->m_strValue = "0.00";
            pParas->AddTail(pNewData);
        }
        if(FindErrorLogic(pParas) == NULL)
        {
            pNewData = new CCharInterfaceVariable();
            pNewData->m_strName = g_sLangTxt_StateEstimate_ErrorType;//误差类型
            pNewData->m_strID = STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC;
            pNewData->m_strValue = "0";
            pParas->AddTail(pNewData);
        }
        if(FindRelErr(pParas) == NULL)
        {
            pNewData = new CCharInterfaceVariable();
            pNewData->m_strName = g_sLangTxt_StateEstimate_RelError_Percent;//相对误差(％)
            pNewData->m_strID = STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR;
            pNewData->m_strValue = "0.000";
            pParas->AddTail(pNewData);
        }
        if(FindAbsErr_Plus(pParas) == NULL)
        {
            pNewData = new CCharInterfaceVariable();
            pNewData->m_strName = g_sLangTxt_StateEstimate_AbsError;//绝对误差
            pNewData->m_strID = STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR;
            pNewData->m_strValue = "0.000";
            pParas->AddTail(pNewData);
        }
    }

}
void QCharEditWidget_DistanceSearch_Eng::SetZoneParas(CCharacteristic *pCurrCharaObj)
{	//20240819 luozibing 特性曲线编辑参数id不根据区段进行区分时该函数不适用
	//CString strZone = pCurrCharaObj->m_strIndex;
	//CString strFault = pCurrCharaObj->m_strID; 
	//CExBaseObject *pData;
	//CExBaseList *pParas = pCurrCharaObj->GetCharInterface();
	//switch(CString_To_long(pCurrCharaObj->m_strIndex))
	//{
	//case 0:
	//	pData = FindTSeting(pParas);
	//	if (pCurrCharaObj->m_strID == "LL")
	//	{
	//		pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1;
	//	}
	//	else if (pCurrCharaObj->m_strID == "LN")
	//	{
	//		pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1;
	//	}
	//	
	//	pData = FindErrorLogic(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1;
	//	pData = FindRelErr(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1;
	//	pData = FindAbsErr_Plus(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1;
	//	pData = FindAbsErr_Minus(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1;
	//	break;
	//case 1:
	//	pData = FindTSeting(pParas);
	//	if (pCurrCharaObj->m_strID == "LL")
	//	{
	//		pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2;
	//	}
	//	else if (pCurrCharaObj->m_strID == "LN")
	//	{
	//		pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2;
	//	}
	//	pData = FindErrorLogic(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2;
	//	pData = FindRelErr(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2;
	//	pData = FindAbsErr_Plus(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2;
	//	pData = FindAbsErr_Minus(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2;
	//	break;
	//case 2:
	//	pData = FindTSeting(pParas);
	//	if (pCurrCharaObj->m_strID == "LL")
	//	{
	//		pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3;
	//	}
	//	else if (pCurrCharaObj->m_strID == "LN")
	//	{
	//		pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3;
	//	}
	//	pData = FindErrorLogic(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3;
	//	pData = FindRelErr(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3;
	//	pData = FindAbsErr_Plus(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3;
	//	pData = FindAbsErr_Minus(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3;
	//	break;
	//case 3:
	//	pData = FindTSeting(pParas);
	//	if (pCurrCharaObj->m_strID == "LL")
	//	{
	//		pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4;
	//	}
	//	else if (pCurrCharaObj->m_strID == "LN")
	//	{
	//		pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4;
	//	}
	//	pData = FindErrorLogic(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4;
	//	pData = FindRelErr(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4;
	//	pData = FindAbsErr_Plus(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4;
	//	pData = FindAbsErr_Minus(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4;
	//	break;
	//case 4:
	//	pData = FindTSeting(pParas);
	//	if (pCurrCharaObj->m_strID == "LL")
	//	{
	//		pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5;
	//	}
	//	else if (pCurrCharaObj->m_strID == "LN")
	//	{
	//		pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5;
	//	}
	//	pData = FindErrorLogic(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5;
	//	pData = FindRelErr(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5;
	//	pData = FindAbsErr_Plus(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5;
	//	pData = FindAbsErr_Minus(pParas);
	//	pData->m_strID = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5;
	//	break;
	//}
}
CExBaseObject* QCharEditWidget_DistanceSearch_Eng::FindTSeting(CExBaseList *pParas)
{
	CExBaseObject *pDataLN1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);
	if (pDataLN1 != NULL)
	{
		return pDataLN1;
		}
	/*CExBaseObject *pDataLN1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1);
	if (pDataLN1 != NULL)
	{
		return pDataLN1;
	}
	CExBaseObject *pDataLN2 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2);
	if (pDataLN2 != NULL)
	{
		return pDataLN2;
	}
	CExBaseObject *pDataLN3 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3);
	if (pDataLN3 != NULL)
	{
		return pDataLN3;
	}
	CExBaseObject *pDataLN4 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4);
	if (pDataLN4 != NULL)
	{
		return pDataLN4;
	}
	CExBaseObject *pDataLN5 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5);
	if (pDataLN5 != NULL)
	{
		return pDataLN5;
	}
	CExBaseObject *pDataLL1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1);
	if (pDataLL1 != NULL)
	{
		return pDataLL1;
	}
	CExBaseObject *pDataLL2 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2);
	if (pDataLL2 != NULL)
	{
		return pDataLL2;
	}
	CExBaseObject *pDataLL3 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3);
	if (pDataLL3 != NULL)
	{
		return pDataLL3;
	}
	CExBaseObject *pDataLL4 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4);
	if (pDataLL4 != NULL)
	{
		return pDataLL4;
	}
	CExBaseObject *pDataLL5 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5);
	if (pDataLL5 != NULL)
	{
		return pDataLL5;
	}*/
	return NULL;
}
CExBaseObject* QCharEditWidget_DistanceSearch_Eng::FindAbsErr_Plus(CExBaseList *pParas)
{
    if(m_strUI_ID == STT_ORG_MACRO_DistanceTest_I)
    {
	CExBaseObject *pData1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS);
	if (pData1 != NULL)
	{
		return pData1;
	}
    }
    else if(m_strUI_ID == STT_ORG_MACRO_DistanceSearchTest_I)
    {
        CExBaseObject *pData1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR);
        if (pData1 != NULL)
        {
            return pData1;
        }
    }
	/*CExBaseObject *pData1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1);
	if (pData1 != NULL)
	{
		return pData1;
	}
	CExBaseObject *pData2 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2);
	if (pData2 != NULL)
	{
		return pData2;
	}
	CExBaseObject *pData3 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3);
	if (pData3 != NULL)
	{
		return pData3;
	}
	CExBaseObject *pData4 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4);
	if (pData4 != NULL)
	{
		return pData4;
	}
	CExBaseObject *pData5 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5);
	if (pData5 != NULL)
	{
		return pData5;
	}*/
	return NULL;
}
CExBaseObject* QCharEditWidget_DistanceSearch_Eng::FindAbsErr_Minus(CExBaseList *pParas)
{
	CExBaseObject *pData1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS);
	if (pData1 != NULL)
	{
		return pData1;
	}
	/*CExBaseObject *pData1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1);
	if (pData1 != NULL)
	{
		return pData1;
	}
	CExBaseObject *pData2 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2);
	if (pData2 != NULL)
	{
		return pData2;
	}
	CExBaseObject *pData3 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3);
	if (pData3 != NULL)
	{
		return pData3;
	}
	CExBaseObject *pData4 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4);
	if (pData4 != NULL)
	{
		return pData4;
	}
	CExBaseObject *pData5 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5);
	if (pData5 != NULL)
	{
		return pData5;
	}*/
	return NULL;
}
CExBaseObject* QCharEditWidget_DistanceSearch_Eng::FindRelErr(CExBaseList *pParas)
{
    if(m_strUI_ID == STT_ORG_MACRO_DistanceTest_I)
    {
	CExBaseObject *pData1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR);
	if (pData1 != NULL)
	{
		return pData1;
	}
    }
    else if(m_strUI_ID == STT_ORG_MACRO_DistanceSearchTest_I)
    {
        CExBaseObject *pData1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR);
        if (pData1 != NULL)
        {
            return pData1;
        }
    }
	/*CExBaseObject *pData1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1);
	if (pData1 != NULL)
	{
		return pData1;
	}
	CExBaseObject *pData2 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2);
	if (pData2 != NULL)
	{
		return pData2;
	}
	CExBaseObject *pData3 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3);
	if (pData3 != NULL)
	{
		return pData3;
	}
	CExBaseObject *pData4 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4);
	if (pData4 != NULL)
	{
		return pData4;
	}
	CExBaseObject *pData5 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5);
	if (pData5 != NULL)
	{
		return pData5;
	}*/
	return NULL;
}
CExBaseObject* QCharEditWidget_DistanceSearch_Eng::FindErrorLogic(CExBaseList *pParas)
{
    if(m_strUI_ID == STT_ORG_MACRO_DistanceTest_I)
    {
		//20241011 luozibing 距离模块曲线编辑页面移出误差类型 存在误差类型节点则删除
	CExBaseObject *pData1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC);
	if (pData1 != NULL)
	{
			pParas->Delete(pData1);
	}
		return NULL;
    }
    else if(m_strUI_ID == STT_ORG_MACRO_DistanceSearchTest_I)
    {
        CExBaseObject *pData1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC);
        if (pData1 != NULL)
        {
            return pData1;
        }
    }

	/*CExBaseObject *pData1 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1);
	if (pData1 != NULL)
	{
		return pData1;
	}
	CExBaseObject *pData2 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2);
	if (pData2 != NULL)
	{
		return pData2;
	}
	CExBaseObject *pData3 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3);
	if (pData3 != NULL)
	{
		return pData3;
	}
	CExBaseObject *pData4 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4);
	if (pData4 != NULL)
	{
		return pData4;
	}
	CExBaseObject *pData5 = (CExBaseObject *)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5);
	if (pData5 != NULL)
	{
		return pData5;
	}*/
	return NULL;
}
void QCharEditWidget_DistanceSearch_Eng::SetDistanceFont()
{
	m_pGridCharacter->setFont(*g_pSttGlobalFont);
	m_pGridCharacter->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pGridParam->setFont(*g_pSttGlobalFont);
	m_pGridParam->horizontalHeader()->setFont(*g_pSttGlobalFont);

	m_pAddCharPushButton->setFont(*g_pSttGlobalFont);
	m_pDeleteCharPushButton->setFont(*g_pSttGlobalFont);
	m_pEditCharPushButton->setFont(*g_pSttGlobalFont);
}

void QCharEditWidget_DistanceSearch_Eng::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	UpdateBtnEnable();

	if (m_pGridCharacter == NULL)
	{
		return;
	}

	if (pGridCtrl == m_pGridCharacter)
	{
		UpdateZKFeature(TRUE);
        UpdateCharacterErrBand();
	}
}

void QCharEditWidget_DistanceSearch_Eng::UpdateBtnEnable()
{
	if (m_pGridCharacter != NULL)
	{
		if (m_pGridCharacter->GetCurrSelData() != NULL)
		{
			m_pEditCharPushButton->setEnabled(true);
			m_pDeleteCharPushButton->setEnabled(true);
		} 
		else
		{
			m_pEditCharPushButton->setEnabled(false);
			m_pDeleteCharPushButton->setEnabled(false);
		}
	}
	else
	{
		m_pEditCharPushButton->setEnabled(false);
		m_pDeleteCharPushButton->setEnabled(false);
	}
	
}
void QCharEditWidget_DistanceSearch_Eng::CheckZoneParas()
{
	//CExBaseList *pCharacterDatas = m_pGridCharacter->GetDatas();
	//POS pos = pCharacterDatas->GetHeadPosition();
	//while(pos != NULL)
	//{
	//	CCharacteristic *pZone = (CCharacteristic *)pCharacterDatas->GetNext(pos);
	//	//SetZoneParas(pZone);
	//}
}

void QCharEditWidget_DistanceSearch_Eng::CharToGroupDatas(CDataGroup *pDatas)
{

}

void QCharEditWidget_DistanceSearch_Eng::UpdateCharacterErrBand()
{
    m_pCharacteristics_Inner->SetIsShowErrorBand(FALSE);

    CCharacteristic *pCurCharaObj = (CCharacteristic*)m_pGridCharacter->GetCurrSelData();
    if(pCurCharaObj != NULL)
    {
    pCurCharaObj->SetIsShowErrorBand(TRUE);
        emit sig_CharChanged(m_pCharacteristics_Inner, TRUE);
    }
}

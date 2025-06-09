#include "SttMultiMacroParaEditViewDistanceSearch.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../../../Module/TestMacro/TestMacro.h"
#include "../../../../Module/TestMacro/TestMacros.h"
#include "DistanceSearchCommonParasDlg.h"
#include "DistanceSearchBinarySignalDlg.h"
#include "DistanceSearchBatchAddMultDlg.h"
#include "DistanceSearchQuickAddMultDlg.h"
#include "../../Module/UI/SttTestCntrFrameBase.h"
#include "DistanceSearchCommon.h"
#include "../../Module/UI/SttTestCntrFrameApi.h"
#include <qmath.h>

QSttMultiMacroParaEditViewDistanceSearch::QSttMultiMacroParaEditViewDistanceSearch(const CString &strGridFile,QWidget *parent) :
    QSttMultiMacroParaEditViewBase(strGridFile,parent)
{
    m_pSingleMacroRef = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_DistanceSearch_I);
	m_pGridInst = NULL;
//	m_pAddMultiItemSelectDlg = NULL;//放入基类  zhouhj 2024.9.15
    m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
    m_pZTViewInterface = g_theTestCntrFrame->GetInternationalZTViewInterface();
    m_nQuickAddFaultTypeArr.resize(7);
    m_pDistanceSearchMultDlg = new QDistanceSearchAddMultDlg(this);
}

QSttMultiMacroParaEditViewDistanceSearch::~QSttMultiMacroParaEditViewDistanceSearch()
{
}

void QSttMultiMacroParaEditViewDistanceSearch::InitUI_OneMacro()
{
	QSttMultiMacroParaEditViewBase::InitUI_OneMacro();
	m_pSingleItemParaEditWidget = new QDistanceSearchItemParaEditWidget(this);
	m_pSingleItemParaEditWidget->InitDatas(m_pSingleMacroRef);

    m_pSingleItemEditTab->insertTab(0,m_pSingleItemParaEditWidget,g_sLangTxt_Impedance_FunParas);

// 	m_pGoosePubsWidget = new QGooseParaWidget(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr());
//     strText = "GOOSE数据发送";
// 	m_pSingleItemEditTab->insertTab(1,m_pGoosePubsWidget,strText);
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();

    m_pAddOneItemBtn = new QPushButton(g_sLangTxt_Button_AddOneItem);
    m_pAddMultiItemBtn = new QPushButton(g_sLangTxt_Button_AddMultiItem);
	
	m_pBottomHboxLayout->insertWidget(0,m_pAddOneItemBtn);
	m_pBottomHboxLayout->insertWidget(1,m_pAddMultiItemBtn);

}

void QSttMultiMacroParaEditViewDistanceSearch::InitDatas(CSttItems *pCurrRootItems)
{
    DisConnectAll_SigSlot();
    UpdateZoneSelDataTypes();   //20240913 wanmj 初始化区段下拉框显示

    m_pGridInst = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_DistanceSearch_I,STT_MACRO_ID_DistanceSearch_I);
    InitGridTitleLanguage();    //20241025 wanmj 表格表头多语言处理
	m_pCurrMacroParaEditGrid->InitColDef(m_pGridInst, m_pSingleMacroRef, g_theHtmlRptGenFactory->m_pDataTypes);
	QSttMultiMacroParaEditViewBase::InitDatas(pCurrRootItems);
    CheckMacroTestAllPresence(&m_oSingleMacroItemsRef);
	m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);

    //打开测试界面，下发增加提示信息
    if (m_oSingleMacroItemsRef.FindByClassID(STTGBXMLCLASSID_CSTTMACROTEST) == NULL)
    {
        CLogPrint::LogString(XLOGLEVEL_INFOR, _T("请添加测试项目！"));
    }

    UpdateParas_To_ZTView();

    SetCharactMaxSensAng();

    //初始化时获取特性曲线参数
    UpdateCharacteristicParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
    m_pSingleItemParaEditWidget->UpdateParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
    ConnectAll_SigSlot();

    return;
}

//20241025 wanmj 表格表头多语言处理
void QSttMultiMacroParaEditViewDistanceSearch::InitGridTitleLanguage()
{
    if(m_pGridInst == NULL)
        return;

    CSttGdInst_Cols *pSttGdInst_Cols = m_pGridInst->GetInst_Cols();
    CSttGdInst_Col *pSttGdInst_Col = NULL;
    POS pos = pSttGdInst_Cols->GetHeadPosition();
    while(pos != NULL)
    {
        pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos);
        SetValueToInstColName(pSttGdInst_Col);
    }

}

void QSttMultiMacroParaEditViewDistanceSearch::SetValueToInstColName(CSttGdInst_Col *pSttGdInst_Col)
{
    if(pSttGdInst_Col == NULL)
        return;
    if(pSttGdInst_Col->m_pSttGdColDef_Ref == NULL)
        return;

    if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_GRID_PARAS_ID_SELECT)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_ActionTime_Select;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_GRID_PARAS_ID_STATE)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_Syn_State;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_GRID_PARAS_ID_TripZ)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_DistanceSearch_TripZ;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_GRID_PARAS_ID_TripZAngle)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_DistanceSearch_TripZAngle;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_Gradient_FailType;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_DistanceSearch_Header_ZoneType;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_GRID_PARAS_ID_TTRIP_ERRORLOGIC)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_StateEstimate_ErrorType;
    }
}

void QSttMultiMacroParaEditViewDistanceSearch::CheckMacroTestAllPresence(CExBaseList *pListItems)
{
    POS pos = pListItems->GetHeadPosition();
    while(pos != NULL)
    {
        CExBaseObject *pData = (CExBaseObject *)pListItems->GetNext(pos);
        if(pData->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
        {
            continue;
        }
        CSttMacroTest *pMacroTest = (CSttMacroTest *)pData;
        CSttMacroTestParaDatas *pParaDatas = pMacroTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
        DistanceSearchCheckParaExist(pParaDatas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE);
        DistanceSearchCheckParaExist(pParaDatas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE);
        DistanceSearchCheckParaExist(pParaDatas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING);
    }
}

void QSttMultiMacroParaEditViewDistanceSearch::SetCharactMaxSensAng()
{
    //设置特性曲线最大灵敏角 用于计算误差带
    CExBaseList* pInnerMacroTest = ((QDistanceSearchItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas();
    CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pInnerMacroTest->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_MAXANGLE);

    if(pData == NULL)
        return;

    CCharacteristics* pCharacteristics = stt_Frame_Characteristics();
    if(pCharacteristics != NULL)
    {
        if(fabs(pCharacteristics->m_dMaxSensAng - pData->m_strValue.toDouble()) > 0.01)
        {
            pCharacteristics->m_dMaxSensAng = pData->m_strValue.toDouble();
            if (m_pCharactInterface == NULL)
            {
                m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
            }
            m_pCharactInterface->slot_UpdateDrawCharacters();
        }
    }
}

void QSttMultiMacroParaEditViewDistanceSearch::ConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::ConnectAll_SigSlot();
	connect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	connect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	connect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
    connect(m_pDistanceSearchMultDlg, SIGNAL(sig_AddDistanceSearchItem(int, double, int, double, double, double, double, double, double, double, double, int)), this,
            SLOT(slot_AddDistanceSearchItem(int, double, int, double, double, double, double, double, double, double, double, int)));
}

void QSttMultiMacroParaEditViewDistanceSearch::DisConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::DisConnectAll_SigSlot();
	disconnect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	disconnect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	disconnect(m_pCommonParasBtn,SIGNAL(clicked()),this,SLOT(slot_CommonParasBtnClick()));
	disconnect(m_pBinarysBtn,SIGNAL(clicked()),this,SLOT(slot_BinarysBtnClick()));
	disconnect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
    disconnect(m_pDistanceSearchMultDlg, SIGNAL(sig_AddDistanceSearchItem(int, double, int, double, double, double, double, double, double)), this,
            SLOT(slot_AddDistanceSearchItem(int, double, int, double, double, double, double, double, double)));
}

void QSttMultiMacroParaEditViewDistanceSearch::UpdateParas_To_ZTView()
{
    //20240812 wanmj 显示默认ZT视图
    if (m_pZTViewInterface == NULL)
    {
        m_pZTViewInterface = g_theTestCntrFrame->GetInternationalZTViewInterface();
    }

    CString arrName[10] = {"LNZone1_Check", "LNZone2_Check", "LNZone3_Check", "LNZone4_Check", "LNZone5_Check",
                           "LLZone1_Check", "LLZone2_Check", "LLZone3_Check", "LLZone4_Check", "LLZone5_Check"};
    double arrZSet[10] = { 7, 14, 21, 28, 35, 5, 10, 15, 20, 25 };
    double arrTSet[10] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
    double arrPlus[10] = { 0 };
    double arrMinus[10] = { 0 };

    m_pZTViewInterface->UpdateZTViewDraw(arrName, arrZSet, arrTSet, arrPlus, arrMinus);
}

//获取最新特性曲线参数并更新到界面
void QSttMultiMacroParaEditViewDistanceSearch::UpdateParasByCharEdit()
{
    //进入特性曲线编辑前已经选中测试项 编辑完成后仍选择进入特性曲线编辑前的测试项
    CExBaseObject *pCurrObj = m_pCurrMacroParaEditGrid->GetCurrSelData();
    //更新特性曲线时间定值等参数到表格数据
    POS pos = m_pCurrMacroItemsRef->GetHeadPosition();
    while (pos != NULL)
    {
        CSttMacroTest *pMacroTest = (CSttMacroTest *)m_pCurrMacroItemsRef->GetNext(pos);
        UpdateCharacteristicParas(pMacroTest);
    }
    m_pCurrMacroParaEditGrid->ShowDatas(m_pCurrMacroItemsRef);
    if (pCurrObj != NULL)
    {
        m_pCurrMacroParaEditGrid->SelectRow((CSttMacroTest*)pCurrObj->GetAncestor(STTGBXMLCLASSID_CSTTMACROTEST));
    }

    UpdateZoneSelDataTypes();//初始化区段下拉框显示

    //更新特性曲线时间定值到编辑界面
    UpdateCharacteristicParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
    m_pSingleItemParaEditWidget->UpdateParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
}

void QSttMultiMacroParaEditViewDistanceSearch::UpdateCharacteristicParas(CSttMacroTest *pCurrMacroTest)
{
    if (pCurrMacroTest == NULL)
    {
        return;
    }

    CSttMacroTestParaDatas *pDstDatas = pCurrMacroTest->GetSttMacroTestParaDatas(FALSE,"");
    if (pDstDatas == NULL)
    {
        return;
    }

    CSttMacroTestParaData *pDataZonePara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE);
    if (pDataZonePara == NULL)
    {
        DistanceSearchCheckParaExist(pDstDatas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE);
        pDataZonePara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE);
    }
    //没有对应的特性曲线参数显示为0
    CSttMacroTestParaData *pDataTSetPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING);
    if (pDataTSetPara == NULL)
    {
        DistanceSearchCheckParaExist(pDstDatas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING);
        pDataTSetPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING);
    }
    CSttMacroTestParaData *pDataPlusPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR);
    if (pDataPlusPara == NULL)
    {
        DistanceSearchCheckParaExist(pDstDatas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR);
        pDataPlusPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR);
    }
    CSttMacroTestParaData *pDataRelPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR);
    if (pDataRelPara == NULL)
    {
        DistanceSearchCheckParaExist(pDstDatas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR);
        pDataRelPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR);
    }

    CSttMacroTestParaData *pDataLogicPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC);
    if (pDataLogicPara == NULL)
    {
        DistanceSearchCheckParaExist(pDstDatas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC);
        pDataLogicPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC);
    }
    CSttMacroTestParaData *pDataFaultPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE);
    if (pDataFaultPara == NULL)
    {
        DistanceSearchCheckParaExist(pDstDatas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE);
        pDataFaultPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE);
    }
    if (CString_To_long(pDataZonePara->m_strValue) == 0)
    {//当前区段为线路长度时 设置线路阻抗为测试项阻抗值
        return;
    }

    //根据故障类型和区段值查找对应曲线 并将曲线参数设置到MacroTest
    CCharacteristic *pChar = NULL;
    CCharacteristics* pCharacteristics = stt_Frame_Characteristics();
    POS pos = pCharacteristics->GetHeadPosition();
    while (pos != NULL)
    {
        CExBaseObject *pObj = pCharacteristics->GetNext(pos);
        if (pObj->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
            continue;

        CCharacteristic *pCharTemp = (CCharacteristic *)pObj;
        //获取勾选使用的曲线
        if (pCharTemp->m_nUse != 1)
        {
            continue;
        }
        if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL)
        {
            if (pCharTemp->m_strIndex != pDataZonePara->m_strValue)
            {
                continue;
            }
        }
        else
        {
            CString strCharID = Global_GetCharFaultTypeStringByFaultType(CString_To_long(pDataFaultPara->m_strValue));
            if (pCharTemp->m_strID != strCharID || pCharTemp->m_strIndex != pDataZonePara->m_strValue)
            {
                continue;
            }
        }

        pChar = pCharTemp;

        CExBaseList* pParas = (CExBaseList*)pChar->GetCharInterface();
        CCharInterfaceVariable *pPara = (CCharInterfaceVariable*)pParas->FindByID(pDataTSetPara->m_strID);
        if (pPara != NULL)
        {
            pCurrMacroTest->m_nModified = 1;
            pDataTSetPara->m_strValue = DistanceSearchValueCheck(pPara->m_strValue, FAULTTIME_MAX, FAULTTIME_MIN, 3);
        }

        pPara = (CCharInterfaceVariable*)pParas->FindByID(pDataPlusPara->m_strID);
        if (pPara != NULL)
        {
            pCurrMacroTest->m_nModified = 1;
            pDataPlusPara->m_strValue = DistanceSearchValueCheck(pPara->m_strValue, TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3);
        }


        pPara = (CCharInterfaceVariable*)pParas->FindByID(pDataRelPara->m_strID);
        if (pPara != NULL)
        {
            pCurrMacroTest->m_nModified = 1;
            pDataRelPara->m_strValue = DistanceSearchValueCheck(pPara->m_strValue, TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3);
        }

        pPara = (CCharInterfaceVariable*)pParas->FindByID(pDataLogicPara->m_strID);
        if (pPara != NULL)
        {
            pCurrMacroTest->m_nModified = 1;
            pDataLogicPara->m_strValue = pPara->m_strValue;
        }
    }

}

BOOL QSttMultiMacroParaEditViewDistanceSearch::DeleteTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest)
{
    if (m_pCharactInterface == NULL)
    {
        m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
    }
    if (m_pCharactInterface == NULL)
    {
        return FALSE;
    }
    if(pCurrMacroTest == NULL)
    {
        return FALSE;
    }
    m_pCharactInterface->DeleteTestData(pCurrMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE));
	m_bCharTestObjectHasChanged = TRUE;
    return TRUE;
}

BOOL QSttMultiMacroParaEditViewDistanceSearch::AddUpdateTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest, int nState)
{
    if (m_pCharactInterface == NULL)
    {
        m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
    }

    //判断测试项是否已添加
    BOOL bCurrMacroTestExist = FALSE;
    POS pos = m_pCurrMacroItemsRef->GetHeadPosition();
    while(pos != NULL)
    {
        CSttMacroTest* pMacroTestTemp = (CSttMacroTest*)m_pCurrMacroItemsRef->GetNext(pos);
        if(pMacroTestTemp == pCurrMacroTest)
        {
            bCurrMacroTestExist = TRUE;
            break;
        }
    }
    if(!bCurrMacroTestExist)
        return FALSE;

    CSttMacroTestParaDatas *pDataParas = pCurrMacroTest->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
    if(pDataParas == NULL)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("[UpdateTestLine_To_Charact]参数为空"));
        return FALSE;
    }
    CSttMacroTestParaData *pData_ZBegVal = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVAL);//首端阻抗
    if (pData_ZBegVal == NULL)
    {
        DistanceSearchCheckParaExist(pDataParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVAL);
        pData_ZBegVal = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVAL);
    }
    CSttMacroTestParaData *pData_ZBegAng = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVALANG);//首端阻抗
    if (pData_ZBegAng == NULL)
    {
        DistanceSearchCheckParaExist(pDataParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVALANG);
        pData_ZBegAng = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVALANG);
    }
    CSttMacroTestParaData *pData_ZEndVal = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVAL);//首端阻抗
    if (pData_ZEndVal == NULL)
    {
        DistanceSearchCheckParaExist(pDataParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVAL);
        pData_ZEndVal = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVAL);
    }
    CSttMacroTestParaData *pData_ZEndAng = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVALANG);//首端阻抗
    if (pData_ZEndAng == NULL)
    {
        DistanceSearchCheckParaExist(pDataParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVALANG);
        pData_ZEndAng = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVALANG);
    }
    CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE);//故障类型
    if (pData_Fault == NULL)
    {
        DistanceSearchCheckParaExist(pDataParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE);
        pData_Fault = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE);
    }
    CSttMacroTestParaData *pData_Zone = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE);//区段
    if (pData_Zone == NULL)
    {
        DistanceSearchCheckParaExist(pDataParas,STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE);
        pData_Zone = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE);
    }

    float fZBeg = pData_ZBegVal->m_strValue.toFloat();
    float fZBegPhi = pData_ZBegAng->m_strValue.toFloat();
    float fZEnd = pData_ZEndVal->m_strValue.toFloat();
    float fZEndPhi = pData_ZEndAng->m_strValue.toFloat();
    double dRBeg = fZBeg*cos(fZBegPhi * M_PI / 180.0);
    double dXBeg = fZBeg*sin(fZBegPhi * M_PI / 180.0);
    double dREnd = fZEnd*cos(fZEndPhi * M_PI / 180.0);
    double dXEnd = fZEnd*sin(fZEndPhi * M_PI / 180.0);
    m_pCharactInterface->AddUpdateTestLine_Imp(pCurrMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), dRBeg, dXBeg, dREnd, dXEnd, CString_To_long(pData_Fault->m_strValue), CString_To_long(pData_Zone->m_strValue), nState);
	m_bCharTestObjectHasChanged = TRUE;
    return TRUE;
}

BOOL QSttMultiMacroParaEditViewDistanceSearch::AddItem_From_Charact(double dBegX, double dBegY, double dEndX, double dEndY)
{
    if (m_pMulitMacroRootItems == NULL)
    {
        return FALSE;
    }

    CSttItems *pParentItems = GetRootItems_CurrTestMacro(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
    if (pParentItems == NULL)
    {
        return FALSE;
    }

    if (m_pCharactInterface == NULL)
    {
        m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
    }

    CExBaseList* pInnerMacroTest = ((QDistanceSearchItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas();
    CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pInnerMacroTest->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTYPE);
    CString strFaultType;
    int nFaultType = 0;

    if(pData != NULL)
        nFaultType = CString_To_long(pData->m_strValue);

    if(nFaultType < 3)
        strFaultType = "LN";
    else if(nFaultType < 6)
        strFaultType = "LL";
    else if(nFaultType < 9)
        strFaultType = "LLN";
    else if(nFaultType < 10)
        strFaultType = "LLL";
    else
        strFaultType = "LN";

    QVector<double> dBegZArr, dBegAngArr, dEndZArr, dEndAngArr,
            dTSettingArr, dRelErrArr, dAbsErrArr;
    QVector<int> nErrTypeArr, nZoneTypeArr;
    BOOL bAdd = CalDistanceSearchItemParas(strFaultType, dBegX, dBegY, dEndX, dEndY,
                                           dBegZArr, dBegAngArr, dEndZArr, dEndAngArr,
                                           nZoneTypeArr, dTSettingArr, dRelErrArr, dAbsErrArr,
                                           nErrTypeArr);
    if(!bAdd)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("绘制线段【BegX = %.2f, BegY = %.2f, EndX = %.2f, EndY = %.2f】与特性曲线没有交点，不生成测试项。"),
                                   dBegX, dBegY, dEndX, dEndY);
        return FALSE;
    }

    for(int i = 0; i < dBegZArr.size(); i++)
    {
        CDataGroup *pMacroParas = GetAddOneItem_DataGroup(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
        CDvmData *pDvmData = NULL;
        CString strItemPath, strMacroUI_ID, strItemName, strItemID, strValue;
        CString strBegZ, strBegAng, strEndZ, strEndAng, strTSetting, strFaultCur, strFaultVol, strAbsErr, strRelErr;

        strItemPath = pParentItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
        strItemName = m_pSingleMacroRef->m_strName;
        strItemID = m_pSingleMacroRef->m_strID;
        strMacroUI_ID = GetMacroID();
        pParentItems->InitNameAndIDForPaste(strItemName, strItemID);

        //首端阻抗
        pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVAL);
        strBegZ.setNum(dBegZArr[i]);
        strValue = DistanceSearchValueCheck(strBegZ, BEGINVAL_MAX, BEGINVAL_MIN, 3);
        if(pDvmData != NULL)
        {
            if(pDvmData->m_strValue != strValue)
            {
                pDvmData->m_strValue = strValue;
            }
        }
        else
        {
            pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
        }

        //首端阻抗角
        pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVALANG);
        strBegAng.setNum(dBegAngArr[i]);
        strValue = DistanceSearchValueCheck(strBegAng, BEGINVALANG_MAX, BEGINVALANG_MIN, 3);
        if(pDvmData != NULL)
        {
            if(pDvmData->m_strValue != strValue)
            {
                pDvmData->m_strValue = strValue;
            }
        }
        else
        {
            pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
        }

        //末端阻抗
        pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVAL);
        strEndZ.setNum(dEndZArr[i]);
        strValue = DistanceSearchValueCheck(strEndZ, ENDVAL_MAX, ENDVAL_MIN, 3);
        if(pDvmData != NULL)
        {
            if(pDvmData->m_strValue != strValue)
            {
                pDvmData->m_strValue = strValue;
            }
        }
        else
        {
            pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
        }

        //末端阻抗角
        pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVALANG);
        strEndAng.setNum(dEndAngArr[i]);
        strValue = DistanceSearchValueCheck(strEndAng, ENDVALANG_MAX, ENDVALANG_MIN, 3);
        if(pDvmData != NULL)
        {
            if(pDvmData->m_strValue != strValue)
            {
                pDvmData->m_strValue = strValue;
            }
        }
        else
        {
            pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
        }

        //区段
        CDvmData* pZoneTypeDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
        strValue.setNum(nZoneTypeArr[i]);
        if(pZoneTypeDvmData != NULL)
        {
            if(pZoneTypeDvmData->m_strValue != strValue)
            {
                pZoneTypeDvmData->m_strValue = strValue;
            }
        }
        else
        {
            pMacroParas->AddNewData(pZoneTypeDvmData->m_strName, pZoneTypeDvmData->m_strID, pZoneTypeDvmData->m_strDataType, strValue);
        }

        //时间定值
        CDvmData* pTSettingDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING);
        strTSetting.setNum(dTSettingArr[i]);
        strValue = DistanceSearchValueCheck(strTSetting, FAULTTIME_MAX, FAULTTIME_MIN, 3);
        if(pTSettingDvmData != NULL)
        {
            if(pTSettingDvmData->m_strValue != strValue)
            {
                pTSettingDvmData->m_strValue = strValue;
            }
        }
        else
        {
            pMacroParas->AddNewData(pTSettingDvmData->m_strName, pTSettingDvmData->m_strID, pTSettingDvmData->m_strDataType, strValue);
        }

        //绝对误差
        CDvmData* pAbsErrDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR);
        strAbsErr.setNum(dAbsErrArr[i]);
        strValue = DistanceSearchValueCheck(strAbsErr, TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3);
        if(pAbsErrDvmData != NULL)
        {
            if(pAbsErrDvmData->m_strValue != strValue)
            {
                pAbsErrDvmData->m_strValue = strValue;
            }
        }
        else
        {
            pMacroParas->AddNewData(pAbsErrDvmData->m_strName, pAbsErrDvmData->m_strID, pAbsErrDvmData->m_strDataType, strValue);
        }

        //相对误差
        CDvmData* pRelErrDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR);
        strRelErr.setNum(dRelErrArr[i]);
        strValue = DistanceSearchValueCheck(strRelErr, TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3);
        if(pRelErrDvmData != NULL)
        {
            if(pRelErrDvmData->m_strValue != strValue)
            {
                pRelErrDvmData->m_strValue = strValue;
            }
        }
        else
        {
            pMacroParas->AddNewData(pRelErrDvmData->m_strName, pRelErrDvmData->m_strID, pRelErrDvmData->m_strDataType, strValue);
        }

        //误差逻辑
        CDvmData* pErrTypeDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC);
        strValue.setNum(nErrTypeArr[i]);
        if(pErrTypeDvmData != NULL)
        {
            if(pErrTypeDvmData->m_strValue != strValue)
            {
                pErrTypeDvmData->m_strValue = strValue;
            }
        }
        else
        {
            pMacroParas->AddNewData(pErrTypeDvmData->m_strName, pErrTypeDvmData->m_strID, pErrTypeDvmData->m_strDataType, strValue);
        }

        g_nUpdateMultiMacroParaEditView = 0;
        long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AddOneMacroItem(pMacroParas, strItemName, strItemID, strItemPath,
                                                                           0, m_pSingleMacroRef->m_strID, STT_ORG_MACRO_DistanceSearchTest_I);
        g_nUpdateMultiMacroParaEditView = 1;

        if (nRet!= STT_CMD_ExecStatus_SUCCESS)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("添加单个电气量测试功能执行命令失败(%ld)."),nRet);
            return FALSE;
        }

        CSttMacroTest *pNewTest = (CSttMacroTest*)pParentItems->FindByID(strItemID);
        if (pNewTest == NULL)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("添加单个电气量测试功能失败."));
            return FALSE;
        }

        m_pCurrMacroItemsRef->AddTail(pNewTest);
        m_pCurrMacroParaEditGrid->InsertData(pNewTest);

        //添加测试线
        double dBegXTemp = dBegZArr[i]*cos(dBegAngArr[i] * M_PI / 180.0);
        double dBegYTemp = dBegZArr[i]*sin(dBegAngArr[i] * M_PI / 180.0);
        double dEndXTemp = dEndZArr[i]*cos(dEndAngArr[i] * M_PI / 180.0);
        double dEndYTemp = dEndZArr[i]*sin(dEndAngArr[i] * M_PI / 180.0);
        m_pCharactInterface->AddUpdateTestLine_Imp(pNewTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), dBegXTemp, dBegYTemp, dEndXTemp, dEndYTemp, nFaultType, nZoneTypeArr[i]);
        m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());
    }

    UpdateBottomBtnsEnable();
    return TRUE;
}

void QSttMultiMacroParaEditViewDistanceSearch::AddDistanceSearchItemQuick()
{
    if(m_nQuickAddFaultTypeArr.size() < 7)
        return;

    if (m_pMulitMacroRootItems == NULL)
        return;

    CSttItems *pParentItems = GetRootItems_CurrTestMacro(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
    if (pParentItems == NULL)
        return;

    if (m_pCharactInterface == NULL)
    {
        m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
    }

    for(int i = 0; i < 7; i++)
    {
        if(m_nQuickAddFaultTypeArr[i] == 0)
            continue;

        CString strFaultType;
        if(i < 3)
            strFaultType = "LN";
        else if(i < 6)
            strFaultType = "LL";
        else
            strFaultType = "LLL";

        for(int j = 0; j < 3; j++)
        {
            QVector<double> dBegZArr, dBegAngArr, dEndZArr, dEndAngArr,
                    dTSettingArr, dRelErrArr, dAbsErrArr;
            QVector<int> nErrTypeArr, nZoneTypeArr;
            BOOL bAdd = FALSE;
            if(j == 0)
            {
               //0度
                bAdd = CalDistanceSearchItemParas(strFaultType, 0, 0, 0, dBegZArr, dBegAngArr, dEndZArr, dEndAngArr, nZoneTypeArr,
                                                  dTSettingArr, dRelErrArr, dAbsErrArr, nErrTypeArr);
                if(!bAdd)
                {
                    CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("绘制射线【BegX = 0, BegY = 0, Angle = 0】与特性曲线没有交点，不生成测试项。"));
                    continue;
                }
            }
            else if(j == 1)
            {
                //90度
                bAdd = CalDistanceSearchItemParas(strFaultType, 0, 0, 90, dBegZArr, dBegAngArr, dEndZArr, dEndAngArr, nZoneTypeArr,
                                                  dTSettingArr, dRelErrArr, dAbsErrArr, nErrTypeArr);
                if(!bAdd)
                {
                    CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("绘制射线【BegX = 0, BegY = 0, Angle = 90】与特性曲线没有交点，不生成测试项。"));
                    continue;
                }
            }
            else
            {
                //最大灵敏角
                CExBaseList* pInnerMacroTest = ((QDistanceSearchItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas();
                CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pInnerMacroTest->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_MAXANGLE);
                if(NULL != pData)
                {
                    bAdd = CalDistanceSearchItemParas(strFaultType, 0, 0, pData->m_strValue.toDouble(), dBegZArr, dBegAngArr, dEndZArr, dEndAngArr,
                                                      nZoneTypeArr, dTSettingArr, dRelErrArr, dAbsErrArr, nErrTypeArr);
                    if(!bAdd)
                    {
                        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("绘制射线【BegX = 0, BegY = 0, Angle = %.2f】与特性曲线没有交点，不生成测试项。"), pData->m_strValue.toDouble());
                        continue;
                    }
                }
            }

            for(int k = 0; k < dBegZArr.size(); k++)
            {
                CDataGroup *pMacroParas = GetAddOneItem_DataGroup(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
                CDvmData *pDvmData = NULL;
                CString strItemPath, strMacroUI_ID, strItemName, strItemID, strValue;
                CString strBegZ, strBegAng, strEndZ, strEndAng, strTSetting, strRelErr, strAbsErr;

                strItemPath = pParentItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
                strItemName = m_pSingleMacroRef->m_strName;
                strItemID = m_pSingleMacroRef->m_strID;
                strMacroUI_ID = GetMacroID();
                pParentItems->InitNameAndIDForPaste(strItemName, strItemID);

                //首端阻抗
                pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVAL);
                strBegZ.setNum(dBegZArr[k]);
                strValue = DistanceSearchValueCheck(strBegZ, BEGINVAL_MAX, BEGINVAL_MIN, 3);
                if(pDvmData != NULL)
                {
                    if(pDvmData->m_strValue != strValue)
                    {
                        pDvmData->m_strValue = strValue;
                    }
                }
                else
                {
                    pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
                }

                //首端阻抗角
                pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVALANG);
                strBegAng.setNum(dBegAngArr[k]);
                strValue = DistanceSearchValueCheck(strBegAng, BEGINVALANG_MAX, BEGINVALANG_MIN, 3);
                if(pDvmData != NULL)
                {
                    if(pDvmData->m_strValue != strValue)
                    {
                        pDvmData->m_strValue = strValue;
                    }
                }
                else
                {
                    pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
                }

                //末端阻抗
                pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVAL);
                strEndZ.setNum(dEndZArr[k]);
                strValue = DistanceSearchValueCheck(strEndZ, ENDVAL_MAX, ENDVAL_MIN, 3);
                if(pDvmData != NULL)
                {
                    if(pDvmData->m_strValue != strValue)
                    {
                        pDvmData->m_strValue = strValue;
                    }
                }
                else
                {
                    pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
                }

                //末端阻抗角
                pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVALANG);
                strEndAng.setNum(dEndAngArr[k]);
                strValue = DistanceSearchValueCheck(strEndAng, ENDVALANG_MAX, ENDVALANG_MIN, 3);
                if(pDvmData != NULL)
                {
                    if(pDvmData->m_strValue != strValue)
                    {
                        pDvmData->m_strValue = strValue;
                    }
                }
                else
                {
                    pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
                }

                //故障类型
                pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
                int nFaultType;
                if(i == 6)
                    nFaultType = 9;
                else
                    nFaultType = i;

                strValue.setNum(nFaultType);
                if(pDvmData != NULL)
                {
                    if(pDvmData->m_strValue != strValue)
                    {
                        pDvmData->m_strValue = strValue;
                    }
                }
                else
                {
                    pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
                }

                //区段
                pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
                strValue.setNum(nZoneTypeArr[k]);
                if(pDvmData != NULL)
                {
                    if(pDvmData->m_strValue != strValue)
                    {
                        pDvmData->m_strValue = strValue;
                    }
                }
                else
                {
                    pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
                }

                //时间定值
                pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING);
                strTSetting.setNum(dTSettingArr[k]);
                strValue = DistanceSearchValueCheck(strTSetting, FAULTTIME_MAX, FAULTTIME_MIN, 3);
                if(pDvmData != NULL)
                {
                    if(pDvmData->m_strValue != strValue)
                    {
                        pDvmData->m_strValue = strValue;
                    }
                }
                else
                {
                    pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
                }

                //绝对误差
                pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR);
                strAbsErr.setNum(dAbsErrArr[k]);
                strValue = DistanceSearchValueCheck(strAbsErr, TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3);
                if(pDvmData != NULL)
                {
                    if(pDvmData->m_strValue != strValue)
                    {
                        pDvmData->m_strValue = strValue;
                    }
                }
                else
                {
                    pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
                }

                //相对误差
                pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR);
                strRelErr.setNum(dRelErrArr[k]);
                strValue = DistanceSearchValueCheck(strRelErr, TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3);
                if(pDvmData != NULL)
                {
                    if(pDvmData->m_strValue != strValue)
                    {
                        pDvmData->m_strValue = strValue;
                    }
                }
                else
                {
                    pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
                }

                //误差逻辑
                pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC);
                strValue.setNum(nErrTypeArr[k]);
                if(pDvmData != NULL)
                {
                    if(pDvmData->m_strValue != strValue)
                    {
                        pDvmData->m_strValue = strValue;
                    }
                }
                else
                {
                    pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
                }

                g_nUpdateMultiMacroParaEditView = 0;
                long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AddOneMacroItem(pMacroParas, strItemName, strItemID, strItemPath,
                                                                                   0, m_pSingleMacroRef->m_strID, STT_ORG_MACRO_DistanceSearchTest_I);
                g_nUpdateMultiMacroParaEditView = 1;

                if (nRet!= STT_CMD_ExecStatus_SUCCESS)
                {
                    CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("添加单个电气量测试功能执行命令失败(%ld)."),nRet);
                    return;
                }

                CSttMacroTest *pNewTest = (CSttMacroTest*)pParentItems->FindByID(strItemID);
                if (pNewTest == NULL)
                {
                    CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("添加单个电气量测试功能失败."));
                    return;
                }

                m_pCurrMacroItemsRef->AddTail(pNewTest);
                m_pCurrMacroParaEditGrid->InsertData(pNewTest);

                //添加测试线
                double dBegX = dBegZArr[k]*cos(dBegAngArr[k] * M_PI / 180.0);
                double dBegY = dBegZArr[k]*sin(dBegAngArr[k] * M_PI / 180.0);
                double dEndX = dEndZArr[k]*cos(dEndAngArr[k] * M_PI / 180.0);
                double dEndY = dEndZArr[k]*sin(dEndAngArr[k] * M_PI / 180.0);
                m_pCharactInterface->AddUpdateTestLine_Imp(pNewTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), dBegX, dBegY, dEndX, dEndY, nFaultType, nZoneTypeArr[k]);
                m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());

                UpdateBottomBtnsEnable();
            }
        }
    }
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_AddDistanceSearchItem(int nFaultType, double dSettingTime, int nZoneType, double dBegZ, double dBegAng, double dEndZ, double dEndAng,
                                                                          double dFaultCur, double dFaultVolt, double dRelErr, double dAbsErr, int nErrType)
{
    if (m_pMulitMacroRootItems == NULL)
    {
        return;
    }

    CSttItems *pParentItems = GetRootItems_CurrTestMacro(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
    if (pParentItems == NULL)
    {
        return;
    }

    if (m_pCharactInterface == NULL)
    {
        m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
    }

    CDataGroup *pMacroParas = GetAddOneItem_DataGroup(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
    CDvmData *pDvmData = NULL;
    CString strItemPath, strMacroUI_ID, strItemName, strItemID, strValue;
    CString strBegZ, strBegAng, strEndZ, strEndAng, strTSetting, strFaultCur, strFaultVol, strAbsErr, strRelErr;

    strItemPath = pParentItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
    strItemName = m_pSingleMacroRef->m_strName;
    strItemID = m_pSingleMacroRef->m_strID;
    strMacroUI_ID = GetMacroID();
    pParentItems->InitNameAndIDForPaste(strItemName, strItemID);

    //首端阻抗
    pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVAL);
    strBegZ.setNum(dBegZ);
    strValue = DistanceSearchValueCheck(strBegZ, BEGINVAL_MAX, BEGINVAL_MIN, 3);
    if(pDvmData != NULL)
    {
        if(pDvmData->m_strValue != strValue)
        {
            pDvmData->m_strValue = strValue;
        }
    }
    else
    {
        pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
    }

    //首端阻抗角
    pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BEGINVALANG);
    strBegAng.setNum(dBegAng);
    strValue = DistanceSearchValueCheck(strBegAng, BEGINVALANG_MAX, BEGINVALANG_MIN, 3);
    if(pDvmData != NULL)
    {
        if(pDvmData->m_strValue != strValue)
        {
            pDvmData->m_strValue = strValue;
        }
    }
    else
    {
        pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
    }

    //末端阻抗
    pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVAL);
    strEndZ.setNum(dEndZ);
    strValue = DistanceSearchValueCheck(strEndZ, ENDVAL_MAX, ENDVAL_MIN, 3);
    if(pDvmData != NULL)
    {
        if(pDvmData->m_strValue != strValue)
        {
            pDvmData->m_strValue = strValue;
        }
    }
    else
    {
        pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
    }

    //末端阻抗角
    pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ENDVALANG);
    strEndAng.setNum(dEndAng);
    strValue = DistanceSearchValueCheck(strEndAng, ENDVALANG_MAX, ENDVALANG_MIN, 3);
    if(pDvmData != NULL)
    {
        if(pDvmData->m_strValue != strValue)
        {
            pDvmData->m_strValue = strValue;
        }
    }
    else
    {
        pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
    }

    //故障类型
    pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
    strValue.setNum(nFaultType);
    if(pDvmData != NULL)
    {
        if(pDvmData->m_strValue != strValue)
        {
            pDvmData->m_strValue = strValue;
        }
    }
    else
    {
        pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
    }

    //区段
    CDvmData* pZoneTypeDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
    strValue.setNum(nZoneType);
    if(pZoneTypeDvmData != NULL)
    {
        if(pZoneTypeDvmData->m_strValue != strValue)
        {
            pZoneTypeDvmData->m_strValue = strValue;
        }
    }
    else
    {
        pMacroParas->AddNewData(pZoneTypeDvmData->m_strName, pZoneTypeDvmData->m_strID, pZoneTypeDvmData->m_strDataType, strValue);
    }

    //时间定值
    CDvmData* pTSettingDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING);
    strTSetting.setNum(dSettingTime);
    strValue = DistanceSearchValueCheck(strTSetting, FAULTTIME_MAX, FAULTTIME_MIN, 3);
    if(pTSettingDvmData != NULL)
    {
        if(pTSettingDvmData->m_strValue != strValue)
        {
            pTSettingDvmData->m_strValue = strValue;
        }
    }
    else
    {
        pMacroParas->AddNewData(pTSettingDvmData->m_strName, pTSettingDvmData->m_strID, pTSettingDvmData->m_strDataType, strValue);
    }

    //短路电流
    pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTIF);
    strFaultCur.setNum(dFaultCur);
    strValue = DistanceSearchValueCheck(strFaultCur, FAULTIF_MAX, FAULTIF_MIN, 3);
    if(pDvmData != NULL)
    {
        if(pDvmData->m_strValue != strValue)
        {
            pDvmData->m_strValue = strValue;
        }
    }
    else
    {
        pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
    }

    //短路电压
    pDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTVF);
    strFaultVol.setNum(dFaultVolt);
    strValue = DistanceSearchValueCheck(strFaultVol, FAULTVF_MAX, FAULTVF_MIN, 3);
    if(pDvmData != NULL)
    {
        if(pDvmData->m_strValue != strValue)
        {
            pDvmData->m_strValue = strValue;
        }
    }
    else
    {
        pMacroParas->AddNewData(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strDataType, strValue);
    }

    //绝对误差
    CDvmData* pAbsErrDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR);
    strAbsErr.setNum(dAbsErr);
    strValue = DistanceSearchValueCheck(strAbsErr, TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3);
    if(pAbsErrDvmData != NULL)
    {
        if(pAbsErrDvmData->m_strValue != strValue)
        {
            pAbsErrDvmData->m_strValue = strValue;
        }
    }
    else
    {
        pMacroParas->AddNewData(pAbsErrDvmData->m_strName, pAbsErrDvmData->m_strID, pAbsErrDvmData->m_strDataType, strValue);
    }

    //相对误差
    CDvmData* pRelErrDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR);
    strRelErr.setNum(dRelErr);
    strValue = DistanceSearchValueCheck(strRelErr, TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3);
    if(pRelErrDvmData != NULL)
    {
        if(pRelErrDvmData->m_strValue != strValue)
        {
            pRelErrDvmData->m_strValue = strValue;
        }
    }
    else
    {
        pMacroParas->AddNewData(pRelErrDvmData->m_strName, pRelErrDvmData->m_strID, pRelErrDvmData->m_strDataType, strValue);
    }

    //误差逻辑
    CDvmData* pErrTypeDvmData = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC);
    strValue.setNum(nErrType);
    if(pErrTypeDvmData != NULL)
    {
        if(pErrTypeDvmData->m_strValue != strValue)
        {
            pErrTypeDvmData->m_strValue = strValue;
        }
    }
    else
    {
        pMacroParas->AddNewData(pErrTypeDvmData->m_strName, pErrTypeDvmData->m_strID, pErrTypeDvmData->m_strDataType, strValue);
    }

    g_nUpdateMultiMacroParaEditView = 0;
    long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AddOneMacroItem(pMacroParas, strItemName, strItemID, strItemPath,
                                                                       0, m_pSingleMacroRef->m_strID, STT_ORG_MACRO_DistanceSearchTest_I);
    g_nUpdateMultiMacroParaEditView = 1;

    if (nRet!= STT_CMD_ExecStatus_SUCCESS)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("添加单个电气量测试功能执行命令失败(%ld)."),nRet);
        return;
    }

    CSttMacroTest *pNewTest = (CSttMacroTest*)pParentItems->FindByID(strItemID);
    if (pNewTest == NULL)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("添加单个电气量测试功能失败."));
        return;
    }

    m_pCurrMacroItemsRef->AddTail(pNewTest);
    m_pCurrMacroParaEditGrid->InsertData(pNewTest);

    //添加测试线
    double dBegX = dBegZ*cos(dBegAng * M_PI / 180.0);
    double dBegY = dBegZ*sin(dBegAng * M_PI / 180.0);
    double dEndX = dEndZ*cos(dEndAng * M_PI / 180.0);
    double dEndY = dEndZ*sin(dEndAng * M_PI / 180.0);
    m_pCharactInterface->AddUpdateTestLine_Imp(pNewTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), dBegX, dBegY, dEndX, dEndY, nFaultType, nZoneType);
    m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());

    UpdateBottomBtnsEnable();
    return;
}

CSttItems* QSttMultiMacroParaEditViewDistanceSearch::GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest)
{
	return QSttMultiMacroParaEditViewBase::GetRootItems_CurrTestMacro(pSttMacroTest);
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_AddOneItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_AddOneItemBtnClick();
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_AddMultiItemBtnClick()
{	
	InitAddMultiItemSelectDlg(m_pAddMultiItemBtn->pos(),ADDMULTIITEM_DLG);
}

void QSttMultiMacroParaEditViewDistanceSearch::InitAddMultiItemSelectDlg(QPoint pos,int nDlgState)
{
	//20240701 初次初始化创建选择界面时，创建所有按键，根据按键名称与传入状态显示不同按键
	if (m_pAddMultiItemSelectDlg == NULL)
	{
		m_pAddMultiItemSelectDlg = new QDialog(this);
		m_pAddMultiItemSelectDlg->setWindowFlags(Qt::Popup);
		m_pAddMultiItemSelectDlg->setFont(*g_pSttGlobalFont);

		QGridLayout *pLayout = new QGridLayout(m_pAddMultiItemSelectDlg);

        QPushButton *pBtnAddMultQuick= new QPushButton(g_sLangTxt_Button_AddMultQuick);
        QPushButton *pBtnAddMultDlg= new QPushButton(g_sLangTxt_Button_AddMultDlg);
        QPushButton *pBtnAddMultBatch= new QPushButton(g_sLangTxt_Button_AddMultBatch);

        QPushButton *pBtnDeleteSelItem= new QPushButton(g_sLangTxt_Button_DeleteSelItem);
        QPushButton *pBtnDeleteAllItem= new QPushButton(g_sLangTxt_Button_DeleteAllItem);

        QPushButton *pBtnClearSelResult= new QPushButton(g_sLangTxt_Button_ClearSelResult);
        QPushButton *pBtnClearAllResult= new QPushButton(g_sLangTxt_Button_ClearAllResult);

		pBtnAddMultQuick->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnAddMultDlg->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnAddMultBatch->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnDeleteSelItem->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnDeleteAllItem->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnClearSelResult->setMinimumSize(m_pClearResultBtn->size());
		pBtnClearAllResult->setMinimumSize(m_pClearResultBtn->size());

		pLayout->addWidget(pBtnAddMultQuick,0,0);
		pLayout->addWidget(pBtnAddMultDlg,1,0);
		pLayout->addWidget(pBtnAddMultBatch,2,0);

		pLayout->addWidget(pBtnDeleteSelItem,3,0);
		pLayout->addWidget(pBtnDeleteAllItem,4,0);

		pLayout->addWidget(pBtnClearSelResult,5,0);
		pLayout->addWidget(pBtnClearAllResult,6,0);

		connect(pBtnAddMultQuick,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemQuickBtnClick()));
		connect(pBtnAddMultDlg,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemDlgBtnClick()));
		connect(pBtnAddMultBatch,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBatchDlgBtnClick()));

		connect(pBtnDeleteSelItem,SIGNAL(clicked()),this,SLOT(slot_DeleteSelItemBtnClick()));
		connect(pBtnDeleteAllItem,SIGNAL(clicked()),this,SLOT(slot_DeleteAllItemBtnClick()));

		connect(pBtnClearSelResult,SIGNAL(clicked()),this,SLOT(slot_ClearSelResultBtnClick()));
		connect(pBtnClearAllResult,SIGNAL(clicked()),this,SLOT(slot_ClearAllResultBtnClick()));
	}

	QStringList listTmp;
	switch(nDlgState)
	{
	case ADDMULTIITEM_DLG:
		{
            listTmp.append(g_sLangTxt_Button_AddMultQuick);
            listTmp.append(g_sLangTxt_Button_AddMultDlg);
            listTmp.append(g_sLangTxt_Button_AddMultBatch);
			break;
		}
	case DELETEITEM_DLG:
		{
            listTmp.append(g_sLangTxt_Button_DeleteSelItem);
            listTmp.append(g_sLangTxt_Button_DeleteAllItem);
			break;
		}

	case CLEARSELRESULT:
		{
            listTmp.append(g_sLangTxt_Button_ClearSelResult);
            listTmp.append(g_sLangTxt_Button_ClearAllResult);
			break;
		}
	default:
		break;
	}

	foreach(QPushButton* button, m_pAddMultiItemSelectDlg->findChildren<QPushButton*>()) 
	{
		CString strBtnText = button->text();
		if (listTmp.indexOf(strBtnText)!= -1)
		{
			button->setVisible(true);
		}
		else
		{
			button->setVisible(false);
		}
	}

	QPoint ParentPos = this->mapToGlobal(QPoint(0, 0));
	QSize DlgSize = m_pAddMultiItemSelectDlg->sizeHint();
	m_pAddMultiItemSelectDlg->move(ParentPos.x()+pos.x()-10,ParentPos.y()+pos.y()-DlgSize.height());
	m_pAddMultiItemSelectDlg->show();

	return;
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_DeleteItemBtnClick()
{
	InitAddMultiItemSelectDlg(m_pDeleteItemBtn->pos(),DELETEITEM_DLG);
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_DeleteSelItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteSelItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
//         m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_DeleteAllItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteAllItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
//         m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_ClearResultBtnClick()
{
	InitAddMultiItemSelectDlg(m_pClearResultBtn->pos(),CLEARSELRESULT);
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_ClearSelResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearSelResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
//         m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_ClearAllResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearAllResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
//         m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_CommonParasBtnClick()
{
    QDistanceSearchCommonParasDlg oDistanceSearchCommonParasDlg;
    oDistanceSearchCommonParasDlg.SetDatas(((QDistanceSearchItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());

    if(oDistanceSearchCommonParasDlg.exec() == QDialog::Accepted)
    {
        CExBaseList *pItem = ((QDistanceSearchItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
        if (pItem == NULL)
        {
            pItem = ((QDistanceSearchItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas();
        }
        if (oDistanceSearchCommonParasDlg.CheckItemsModify(pItem))
        {
            oDistanceSearchCommonParasDlg.GetDatas(((QDistanceSearchItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());
            //通用参数修改后，修改表格中所有项数据通用参数
            oDistanceSearchCommonParasDlg.UpdateAllCommonParas(&m_oSingleMacroItemsRef);
            SetCharactMaxSensAng();
            Ats_UpdateMacroTestItems();
        }
    }

	return;
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_BinarysBtnClick()
{   
    QDistanceSearchBinarySignalDlg oDistanceSearchBinarySignalDlg;
    oDistanceSearchBinarySignalDlg.SetDatas(((QDistanceSearchItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());

    if(oDistanceSearchBinarySignalDlg.exec() == QDialog::Accepted)
    {
        CExBaseList *pItem = ((QDistanceSearchItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
        if (pItem == NULL)
        {
            pItem = ((QDistanceSearchItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas();
        }
        if (oDistanceSearchBinarySignalDlg.CheckItemsModify(pItem))
        {
            oDistanceSearchBinarySignalDlg.GetDatas(((QDistanceSearchItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());
            //通用参数修改后，修改表格中所有项数据通用参数
            oDistanceSearchBinarySignalDlg.UpdateAllBinarys(&m_oSingleMacroItemsRef);
            Ats_UpdateMacroTestItems();
        }
    }

	return;
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_AddMultiItemQuickBtnClick()
{
    QDistanceSearchQuickAddMultDlg oDistanceSearchQuickAddMultDlg;
    oDistanceSearchQuickAddMultDlg.SetDatas(m_nQuickAddFaultTypeArr);
    if(oDistanceSearchQuickAddMultDlg.exec() == QDialog::Accepted)
    {
        oDistanceSearchQuickAddMultDlg.GetDatas(m_nQuickAddFaultTypeArr);
        AddDistanceSearchItemQuick();
    }
    return;
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_AddMultiItemBatchDlgBtnClick()
{
    QDistanceSearchBatchAddMultDlg oDistanceSearchBatchAddMultDlg;
    GetMacroTestDataToParas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, ((QDistanceSearchItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());
    oDistanceSearchBatchAddMultDlg.SetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);

    if(oDistanceSearchBatchAddMultDlg.exec() == QDialog::Accepted)
    {
        CString strItemsName,strItemsID;
        long nRepeatTimes = 1,nRptTitle = 2,nTitleLevel = 3;
#ifndef SttTestCntrThread_H
        bool bGenSucc = g_theTestCntrFrame->GenerateTemplate(m_pMulitMacroRootItems, strItemsName, strItemsID, nRepeatTimes, nRptTitle, nTitleLevel);
#else
        g_theSttTestCntrThread->m_pParentItems = m_pMulitMacroRootItems;
        g_theSttTestCntrThread->m_strItemsName = strItemsName;
        g_theSttTestCntrThread->m_strItemsID = strItemsID;
        g_theSttTestCntrThread->PostThreadMessage(10, 0, 0);
#endif
        UpdateBottomBtnsEnable();
    }

    return;
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_AddMultiItemDlgBtnClick()
{
    m_pDistanceSearchMultDlg->SetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
    m_pDistanceSearchMultDlg->exec();

	return;
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest)
{
	QSttMultiMacroParaEditViewBase::slot_ParaEditWidget_To_Grid(pMacroTest);
}

void QSttMultiMacroParaEditViewDistanceSearch::slot_Grid_To_ParaEditWidget(CSttMacroTest* pMacroTest)
{
    if (m_pSingleItemParaEditWidget == NULL)
    {
        return;
    }

    pMacroTest->m_nModified = 1;
    if (m_pSingleItemParaEditWidget->m_pCurrMacroTest_External != pMacroTest)
    {
        return;
    }

    UpdateCharacteristicParas(pMacroTest);
    m_pSingleItemParaEditWidget->UpdateParas(pMacroTest);
    m_pCurrMacroParaEditGrid->UpdateData(pMacroTest);

    AddUpdateTestPoint_To_Charact(pMacroTest);
    UpdateTestPoint_To_ZTView(pMacroTest, true);
}

void QSttMultiMacroParaEditViewDistanceSearch::SetValueToParas(CDataGroup *pParas, CSttMacroTestParaData *pData)
{
    if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_STEP)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_STEP, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTIF)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_FAULTIF, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTVF)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_FAULTVF, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_CURVEERR_ABSERR, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_CURVEERR_RELERR, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_PREFAULTTIME)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_PREFAULTTIME, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TIMEAFTERTRIGGER)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TIMEAFTERTRIGGER, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ILOAD)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ILOAD, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ILOADPH)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ILOADPH, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_K0MODE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_K0MODE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_KLKR)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_KLKR, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ANGKX)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ANGKX, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTTIME)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_FAULTTIME, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ACTIONTIME)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ACTIONTIME, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_SEARCHMODE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_SEARCHMODE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CALCUMODE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_CALCUMODE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZSMAG)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ZSMAG, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZSANG)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ZSANG, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZL)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ZL, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_MAXANGLE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_MAXANGLE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_PTPOS)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_PTPOS, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CTPOS)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_CTPOS, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_SIMULATEBREAKERDELAY)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_SIMULATEBREAKERDELAY, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BRKBREAKTIME)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_BRKBREAKTIME, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_BRKCLOSETIME)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_BRKCLOSETIME, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTID)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_FAULTID, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTANGMODE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_FAULTANGMODE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_FAULTANG)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_FAULTANG, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_A)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_A, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_C)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_C, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_D)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_D, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_E)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_E, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_F)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_F, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_G)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_G, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_H)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_H, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ANDOR)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ANDOR, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B01)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B01, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B02)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B02, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B03)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B03, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B04)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B04, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B05)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B05, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B06)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B06, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B07)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B07, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_B08)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B08, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTSWITCHMODE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_OUTPUTSWITCHMODE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTKEEPTIME)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_OUTPUTKEEPTIME, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_OUTPUTDELAYTIME)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_OUTPUTDELAYTIME, pData->m_strValue, true);
    }

    return;
}

void QSttMultiMacroParaEditViewDistanceSearch::CheckAllPresence(CExBaseList *pParas)
{
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_STEP);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_FAULTIF);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_FAULTVF);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_CURVEERR_ABSERR);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_CURVEERR_RELERR);

    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_PREFAULTTIME);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TIMEAFTERTRIGGER);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ILOAD);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ILOADPH);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_K0MODE);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_KLKR);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ANGKX);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_FAULTTIME);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ACTIONTIME);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_SEARCHMODE);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_CALCUMODE);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ZSMAG);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ZSANG);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ZL);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_MAXANGLE);

    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_PTPOS);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_CTPOS);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_SIMULATEBREAKERDELAY);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_BRKBREAKTIME);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_BRKCLOSETIME);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_FAULTID);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_FAULTANGMODE);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_FAULTANG);

    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_A);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_C);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_D);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_E);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_F);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_G);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_H);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_ANDOR);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B01);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B02);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B03);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B04);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B05);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B06);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B07);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_B08);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_OUTPUTSWITCHMODE);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_OUTPUTKEEPTIME);
    DistanceSearchCheckParaExist(pParas, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_OUTPUTDELAYTIME);

    return;
}

//20240821 wanmj 从测试项获取公共参数给m_oTestMacroUI_Paras
void QSttMultiMacroParaEditViewDistanceSearch::GetMacroTestDataToParas(CDataGroup *pParas, CExBaseList* pInnerTestmacro)
{
    if(pParas == NULL || pInnerTestmacro == NULL)
        return;

    CheckAllPresence(pInnerTestmacro);

    POS pos = pInnerTestmacro->GetHeadPosition();
    while(pos != NULL)
    {
        CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pInnerTestmacro->GetNext(pos);
        SetValueToParas(pParas, pData);
    }

    return;
}

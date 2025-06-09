#include "SttMultiMacroParaEditViewActionTime.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../../../Module/TestMacro/TestMacro.h"
#include "../../../../Module/TestMacro/TestMacros.h"
#include "../../Module/UI/SttTestCntrFrameBase.h"
#include "../../Module/SttTestCtrl/SttTestAppBase.h"
#include "ActionTimeCommon.h"

extern STT_SystemParas g_oSystemParas;

QSttMultiMacroParaEditViewActionTime::QSttMultiMacroParaEditViewActionTime(const CString &strGridFile,QWidget *parent) :
    QSttMultiMacroParaEditViewBase(strGridFile,parent)
{
	m_pSingleMacroRef = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_ActionTime);
	m_pGridInst = NULL;
//	m_pAddMultiItemSelectDlg = NULL;//放入基类  zhouhj 2024.9.15

//	return;
}

QSttMultiMacroParaEditViewActionTime::~QSttMultiMacroParaEditViewActionTime()
{
}

void QSttMultiMacroParaEditViewActionTime::InitDefaultDatas(CTestMacro *pMacroRef)
{
    if(m_pSingleItemParaEditWidget == NULL || pMacroRef == NULL)
        return;

    CSttMacroTestParaDatas *pSttMacroTestParaDatas = m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE,pMacroRef->m_strID);
    ActTimeCheckParaExist(pSttMacroTestParaDatas, STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_UPRE);
    ActTimeCheckParaExist(pSttMacroTestParaDatas, STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFRE);

    CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pSttMacroTestParaDatas->FindByID(STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_UPRE);
    if(pData != NULL)
    {
        CString str_UPre;
        pData->m_strValue = str_UPre.setNum(g_oSystemParas.m_fVNom/sqrt((float)3));
    }

    pData = (CSttMacroTestParaData*)pSttMacroTestParaDatas->FindByID(STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFRE);
    if(pData != NULL)
    {
        CString str_FrePre;
        pData->m_strValue = str_FrePre.setNum(g_oSystemParas.m_fFNom);
    }

    return;
}

void QSttMultiMacroParaEditViewActionTime::InitUI_OneMacro()
{
	QSttMultiMacroParaEditViewBase::InitUI_OneMacro();
	m_pSingleItemParaEditWidget = new QActionTimeItemParaEditWidget(this);
    InitDefaultDatas(m_pSingleMacroRef);
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

void QSttMultiMacroParaEditViewActionTime::InitDatas(CSttItems *pCurrRootItems)
{
	DisConnectAll_SigSlot();

	m_pGridInst = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_ActionTime,STT_MACRO_ID_ActionTime);
    InitGridTitleLanguage();    //20241025 wanmj 表格表头多语言处理
	m_pCurrMacroParaEditGrid->InitColDef(m_pGridInst, m_pSingleMacroRef, g_theHtmlRptGenFactory->m_pDataTypes);
	QSttMultiMacroParaEditViewBase::InitDatas(pCurrRootItems);
	m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);

	ConnectAll_SigSlot();

	return;
}

//20241025 wanmj 表格表头多语言处理
void QSttMultiMacroParaEditViewActionTime::InitGridTitleLanguage()
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

void QSttMultiMacroParaEditViewActionTime::SetValueToInstColName(CSttGdInst_Col *pSttGdInst_Col)
{
    if(pSttGdInst_Col == NULL)
        return;
    if(pSttGdInst_Col->m_pSttGdColDef_Ref == NULL)
        return;

    if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_ACTIONTIME_GRID_PARAS_ID_SELECT)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_ActionTime_Select;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_ACTIONTIME_GRID_PARAS_ID_STATE)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_Syn_State;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_ACTIONTIME_GRID_PARAS_ID_TESTRSLT)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_ActionTime_TestResult;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTTYPE)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_Gradient_FailType;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_SETTINGTIME)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_ActionTime_Title_SettingTime;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_ACTIONTIME_GRID_PARAS_ID_TTRIP_ERRORLOGIC)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_StateEstimate_ErrorType;
    }
}

void QSttMultiMacroParaEditViewActionTime::ConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::ConnectAll_SigSlot();
	connect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	connect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	connect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
}

void QSttMultiMacroParaEditViewActionTime::DisConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::DisConnectAll_SigSlot();
	disconnect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	disconnect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	disconnect(m_pCommonParasBtn,SIGNAL(clicked()),this,SLOT(slot_CommonParasBtnClick()));
	disconnect(m_pBinarysBtn,SIGNAL(clicked()),this,SLOT(slot_BinarysBtnClick()));
	disconnect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
}

CSttItems* QSttMultiMacroParaEditViewActionTime::GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest)
{
	return QSttMultiMacroParaEditViewBase::GetRootItems_CurrTestMacro(pSttMacroTest);
}

void QSttMultiMacroParaEditViewActionTime::slot_AddOneItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_AddOneItemBtnClick();
}

void QSttMultiMacroParaEditViewActionTime::slot_AddMultiItemBtnClick()
{	
    QActionTimeAddMultDlg oActionTimeAddMultDlg;
    GetMacroTestDataToParas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, ((QActionTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());
    oActionTimeAddMultDlg.SetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);

	if(oActionTimeAddMultDlg.exec() == QDialog::Accepted)
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

void QSttMultiMacroParaEditViewActionTime::InitAddMultiItemSelectDlg(QPoint pos,int nDlgState)
{
	//20240701 初次初始化创建选择界面时，创建所有按键，根据按键名称与传入状态显示不同按键
	if (m_pAddMultiItemSelectDlg == NULL)
	{
		m_pAddMultiItemSelectDlg = new QDialog(this);
		m_pAddMultiItemSelectDlg->setWindowFlags(Qt::Popup);
		m_pAddMultiItemSelectDlg->setFont(*g_pSttGlobalFont);

		QGridLayout *pLayout = new QGridLayout(m_pAddMultiItemSelectDlg);

        QPushButton *pBtnDeleteSelItem= new QPushButton(g_sLangTxt_Button_DeleteSelItem);
        QPushButton *pBtnDeleteAllItem= new QPushButton(g_sLangTxt_Button_DeleteAllItem);

        QPushButton *pBtnClearSelResult= new QPushButton(g_sLangTxt_Button_ClearSelResult);
        QPushButton *pBtnClearAllResult= new QPushButton(g_sLangTxt_Button_ClearAllResult);

		pBtnDeleteSelItem->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnDeleteAllItem->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnClearSelResult->setMinimumSize(m_pClearResultBtn->size());
		pBtnClearAllResult->setMinimumSize(m_pClearResultBtn->size());

		pLayout->addWidget(pBtnDeleteSelItem,0,0);
		pLayout->addWidget(pBtnDeleteAllItem,1,0);

		pLayout->addWidget(pBtnClearSelResult,2,0);
		pLayout->addWidget(pBtnClearAllResult,3,0);

		connect(pBtnDeleteSelItem,SIGNAL(clicked()),this,SLOT(slot_DeleteSelItemBtnClick()));
		connect(pBtnDeleteAllItem,SIGNAL(clicked()),this,SLOT(slot_DeleteAllItemBtnClick()));

		connect(pBtnClearSelResult,SIGNAL(clicked()),this,SLOT(slot_ClearSelResultBtnClick()));
		connect(pBtnClearAllResult,SIGNAL(clicked()),this,SLOT(slot_ClearAllResultBtnClick()));
	}

	QStringList listTmp;
	switch(nDlgState)
	{
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

void QSttMultiMacroParaEditViewActionTime::slot_DeleteItemBtnClick()
{
	InitAddMultiItemSelectDlg(m_pDeleteItemBtn->pos(),DELETEITEM_DLG);
}

void QSttMultiMacroParaEditViewActionTime::slot_DeleteSelItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteSelItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
//         m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewActionTime::slot_DeleteAllItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteAllItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
//         m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewActionTime::slot_ClearResultBtnClick()
{
	InitAddMultiItemSelectDlg(m_pClearResultBtn->pos(),CLEARSELRESULT);
}

void QSttMultiMacroParaEditViewActionTime::slot_ClearSelResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearSelResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式清除结果时m_pAddMultiItemSelectDlg为空指针
//     {
// 		m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewActionTime::slot_ClearAllResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearAllResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式清除结果时m_pAddMultiItemSelectDlg为空指针
//     {
// 		m_pAddMultiItemSelectDlg->hide();
//     }//放入基类  zhouhj 2024.9.15
}

void QSttMultiMacroParaEditViewActionTime::slot_CommonParasBtnClick()
{	
    QActionTimeCommonParasDlg oActionTimeCommonParasDlg;
    oActionTimeCommonParasDlg.SetDatas(((QActionTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());

    if(oActionTimeCommonParasDlg.exec() == QDialog::Accepted)
    {
        CExBaseList *pItem = ((QActionTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
        if (pItem == NULL)
        {
            pItem = ((QActionTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas();
        }
        if (oActionTimeCommonParasDlg.CheckItemsModify(pItem))
        {
            oActionTimeCommonParasDlg.GetDatas(((QActionTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());
            //通用参数修改后，修改表格中所有项数据通用参数
            oActionTimeCommonParasDlg.UpdateAllCommonParas(&m_oSingleMacroItemsRef);
            Ats_UpdateMacroTestItems();
        }
    }

	return;
}

void QSttMultiMacroParaEditViewActionTime::slot_BinarysBtnClick()
{
    QActionTimeBinarySignalDlg oActionTimeBinarySignalDlg;
    oActionTimeBinarySignalDlg.SetDatas(((QActionTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());

    if(oActionTimeBinarySignalDlg.exec() == QDialog::Accepted)
    {
        CExBaseList *pItem = ((QActionTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
        if (pItem == NULL)
        {
            pItem = ((QActionTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas();
        }
        if (oActionTimeBinarySignalDlg.CheckItemsModify(pItem))
        {
            oActionTimeBinarySignalDlg.GetDatas(((QActionTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());
            //通用参数修改后，修改表格中所有项数据通用参数
            oActionTimeBinarySignalDlg.UpdateAllBinarys(&m_oSingleMacroItemsRef);
            Ats_UpdateMacroTestItems();
        }
    }
		
	return;
}

void QSttMultiMacroParaEditViewActionTime::slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest)
{
	QSttMultiMacroParaEditViewBase::slot_ParaEditWidget_To_Grid(pMacroTest);
}

void QSttMultiMacroParaEditViewActionTime::SetValueToParas(CDataGroup *pParas, CSttMacroTestParaData *pData)
{
    if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTFRE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_FAULTFRE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFAULTTIME)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_PREFAULTTIME, pData->m_strValue, true);
    }
    else if (pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_UPRE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_UPRE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_IPRE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_IPRE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREANGLE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_PREANGLE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFRE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_PREFRE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTTIME)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_FAULTTIME, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_A)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_A, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_C)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_C, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_D)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_D, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_E)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_E, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_F)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_F, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_G)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_G, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_H)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_H, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B01)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B01, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B02)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B02, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B03)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B03, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B04)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B04, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B05)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B05, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B06)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B06, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B07)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B07, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B08)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B08, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B1)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B1, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B2)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B2, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B3)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B3, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B4)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B4, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B5)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B5, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B6)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B6, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B7)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B7, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B8)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_B8, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_ANDOR)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_ACTIONTIME_PARAS_ADDMULT_ID_ANDOR, pData->m_strValue, true);
    }

    return;
}

void QSttMultiMacroParaEditViewActionTime::CheckAllPresence(CExBaseList *pParas)
{
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTFRE);

    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFAULTTIME);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_UPRE);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_IPRE);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREANGLE);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_PREFRE);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_FAULTTIME);

    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_A);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_C);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_D);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_E);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_F);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_G);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_H);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_ANDOR);

    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B01);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B02);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B03);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B04);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B05);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B06);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B07);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B08);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B1);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B2);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B3);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B4);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B5);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B6);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B7);
    ActTimeCheckParaExist(pParas,STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_B8);

    return;
}
//20240805 wanmj 从测试项获取公共参数给m_oTestMacroUI_Paras
void QSttMultiMacroParaEditViewActionTime::GetMacroTestDataToParas(CDataGroup *pParas, CExBaseList* pInnerTestmacro)
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

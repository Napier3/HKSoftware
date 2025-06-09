#include "SttMultiMacroParaEditViewRecloseAcc.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../../../Module/TestMacro/TestMacro.h"
#include "../../../../Module/TestMacro/TestMacros.h"
#include "RecloseAccItemParaEditWidget.h"
#include "RecloseAccBinarySignalDlg.h"
#include "RecloseAccCommonParasDlg.h"
#include "QRecloseAddMultDlg.h"
#include "../../Module/SttTestCtrl/SttTestAppBase.h"
#include "../../Module/UI/SttTestCntrFrameBase.h"
#include "RecloseAccCommon.h"
#include "../../UI/SttTestCntrFrameApi.h"

QSttMultiMacroParaEditViewRecloseAcc::QSttMultiMacroParaEditViewRecloseAcc(const CString &strGridFile,QWidget *parent) :
    QSttMultiMacroParaEditViewBase(strGridFile,parent)
{
	m_pSingleMacroRef = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_RecloseAcc);
	m_pGridInst = NULL;
//	m_pAddMultiItemSelectDlg = NULL;//放入基类  zhouhj 2024.9.15

//	return;
}

QSttMultiMacroParaEditViewRecloseAcc::~QSttMultiMacroParaEditViewRecloseAcc()
{
}

void QSttMultiMacroParaEditViewRecloseAcc::InitUI_OneMacro()
{
	QSttMultiMacroParaEditViewBase::InitUI_OneMacro();
	m_pSingleItemParaEditWidget = new QRecloseAccItemParaEditWidget(this);
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

void QSttMultiMacroParaEditViewRecloseAcc::InitDatas(CSttItems *pCurrRootItems)
{
	DisConnectAll_SigSlot();
	m_pGridInst = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_RecloseAcc,STT_MACRO_ID_RecloseAcc);
    InitGridTitleLanguage();    //20241025 wanmj 表格表头多语言处理
	m_pCurrMacroParaEditGrid->InitColDef(m_pGridInst, m_pSingleMacroRef, g_theHtmlRptGenFactory->m_pDataTypes);
	QSttMultiMacroParaEditViewBase::InitDatas(pCurrRootItems);
	m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);

	ConnectAll_SigSlot();

	return;
}

//20241025 wanmj 表格表头多语言处理
void QSttMultiMacroParaEditViewRecloseAcc::InitGridTitleLanguage()
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

void QSttMultiMacroParaEditViewRecloseAcc::SetValueToInstColName(CSttGdInst_Col *pSttGdInst_Col)
{
    if(pSttGdInst_Col == NULL)
        return;
    if(pSttGdInst_Col->m_pSttGdColDef_Ref == NULL)
        return;

    if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_RECLOSEACC_GRID_PARAS_ID_SELECT)
    {
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_ActionTime_Select;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_RECLOSEACC_GRID_PARAS_ID_STATE)
    {
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_Syn_State;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_RECLOSEACC_GRID_PARAS_ID_TRIPTIME)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_RecloseAcc_TripTime;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_RECLOSEACC_GRID_PARAS_ID_TTRIPD)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_RecloseAcc_TtripD;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_RECLOSEACC_GRID_PARAS_ID_TTRIPACC)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_RecloseAcc_TtripAcc;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTYPE1)
    {
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_Gradient_FailType;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTMAG)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_RecloseAcc_Title_UxInputMag;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTANG)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_RecloseAcc_Title_UxInputAng;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_UXINPUTFRE)
    {
        pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_RecloseAcc_Title_VZFreq;
    }
    else if(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_TRIPD_ERRTYPE)
    {
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_StateEstimate_ResultEstimate;
    }
}

void QSttMultiMacroParaEditViewRecloseAcc::ConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::ConnectAll_SigSlot();
	connect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	connect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	connect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
}

void QSttMultiMacroParaEditViewRecloseAcc::DisConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::DisConnectAll_SigSlot();
	disconnect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	disconnect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	disconnect(m_pCommonParasBtn,SIGNAL(clicked()),this,SLOT(slot_CommonParasBtnClick()));
	disconnect(m_pBinarysBtn,SIGNAL(clicked()),this,SLOT(slot_BinarysBtnClick()));
	disconnect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
}

CSttItems* QSttMultiMacroParaEditViewRecloseAcc::GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest)
{
	return QSttMultiMacroParaEditViewBase::GetRootItems_CurrTestMacro(pSttMacroTest);
}

BOOL QSttMultiMacroParaEditViewRecloseAcc::IsManualTriggerMode_MacroTestItem(CSttMacroTest* pMacroTest)
{
	if (pMacroTest == NULL)
	{
		return FALSE;
	}

	//20240820 wanmj 手动触发模式
	CSttMacroTestParaDatas *pItem = pMacroTest->GetSttMacroTestParaDatas(FALSE, "");
	CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pItem->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTRIGMODE/*"FaultTrigMode"*/);

	if (pData == NULL)
	{
		return FALSE;
	}

	long nValue = CString_To_long(pData->m_strValue);
	return (nValue == 1);
}

void QSttMultiMacroParaEditViewRecloseAcc::slot_AddOneItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_AddOneItemBtnClick();
}

void QSttMultiMacroParaEditViewRecloseAcc::slot_AddMultiItemBtnClick()
{
	QRecloseAddMultDlg oRecloseAddMultDlg;
    GetMacroTestDataToParas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, ((QRecloseAccItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());
    oRecloseAddMultDlg.SetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
	if(oRecloseAddMultDlg.exec() == QDialog::Accepted)
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

void QSttMultiMacroParaEditViewRecloseAcc::InitAddMultiItemSelectDlg(QPoint pos,int nDlgState)
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

void QSttMultiMacroParaEditViewRecloseAcc::slot_DeleteItemBtnClick()
{
	InitAddMultiItemSelectDlg(m_pDeleteItemBtn->pos(),DELETEITEM_DLG);
}

void QSttMultiMacroParaEditViewRecloseAcc::slot_DeleteSelItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteSelItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
//         m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewRecloseAcc::slot_DeleteAllItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteAllItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
//         m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewRecloseAcc::slot_ClearResultBtnClick()
{
	InitAddMultiItemSelectDlg(m_pClearResultBtn->pos(),CLEARSELRESULT);
}

void QSttMultiMacroParaEditViewRecloseAcc::slot_ClearSelResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearSelResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式清除结果时m_pAddMultiItemSelectDlg为空指针
//     {
//     m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewRecloseAcc::slot_ClearAllResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearAllResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式清除结果时m_pAddMultiItemSelectDlg为空指针
//     {
//     m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewRecloseAcc::slot_CommonParasBtnClick()
{
    QRecloseAccCommonParasDlg oRecloseAccCommonParasDlg;
    GetMacroTestDataToParas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, ((QRecloseAccItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());
    oRecloseAccCommonParasDlg.SetDatas(((QRecloseAccItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());

    if(oRecloseAccCommonParasDlg.exec() == QDialog::Accepted)
    {
        CExBaseList *pItem = ((QRecloseAccItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
        if (pItem == NULL)
        {
            pItem = ((QRecloseAccItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas();
        }
        if (oRecloseAccCommonParasDlg.CheckItemsModify(pItem))
        {
            oRecloseAccCommonParasDlg.GetDatas(((QRecloseAccItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());

            //通用参数修改后，修改表格中所有项数据通用参数
            oRecloseAccCommonParasDlg.UpdateAllCommonParas(&m_oSingleMacroItemsRef);
            Ats_UpdateMacroTestItems();
        }
    }

	return;
}
void QSttMultiMacroParaEditViewRecloseAcc::slot_BinarysBtnClick()
{
    QRecloseAccBinarySignalDlg oRecloseAccBinarySignalDlg;
    oRecloseAccBinarySignalDlg.SetDatas(((QRecloseAccItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());

    if(oRecloseAccBinarySignalDlg.exec() == QDialog::Accepted)
    {
        CExBaseList *pItem = ((QRecloseAccItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
        if (pItem == NULL)
        {
            pItem = ((QRecloseAccItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas();
        }
        if (oRecloseAccBinarySignalDlg.CheckItemsModify(pItem))
        {
            oRecloseAccBinarySignalDlg.GetDatas(((QRecloseAccItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetInnerMacroTestParaDatas());
            //通用参数修改后，修改表格中所有项数据通用参数
            oRecloseAccBinarySignalDlg.UpdateAllBinarys(&m_oSingleMacroItemsRef);
            Ats_UpdateMacroTestItems();
        }
    }

	return;
}

void QSttMultiMacroParaEditViewRecloseAcc::slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest)
{
	QSttMultiMacroParaEditViewBase::slot_ParaEditWidget_To_Grid(pMacroTest);
}


void QSttMultiMacroParaEditViewRecloseAcc::SetValueToParas(CDataGroup *pParas, CSttMacroTestParaData *pData)
{
    //重合闸模块添加系列界面未配置参数para.xml的id与testmacro.xml的id都相同
    if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FRE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FRE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PREFAULTTIME)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PREFAULTTIME, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTIME)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTIME, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ACTIONTIME)
    {
       pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ACTIONTIME, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTRIGMODE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTRIGMODE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PTPOS)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PTPOS, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_CTPOS)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_CTPOS, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOAD)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOAD, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOADPH)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOADPH, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_SIMULATEBREAKERDELAY)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_SIMULATEBREAKERDELAY, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKBREAKTIME)
    {
        //20240820 wanmj testmacro里面单位是s，paras里面单位是ms
        float fBreakTime = pData->m_strValue.toFloat();
        CString strBreakTime;
        strBreakTime.setNum(fBreakTime*1000);
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKBREAKTIME, strBreakTime, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKCLOSETIME)
    {
        //20240820 wanmj testmacro里面单位是s，paras里面单位是ms
        float fCloseTime = pData->m_strValue.toFloat();
        CString strCloseTime;
        strCloseTime.setNum(fCloseTime*1000);
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKCLOSETIME, strCloseTime, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BINSELECT)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BINSELECT, pData->m_strValue, true);
    }
    if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_A)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_A, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_C)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_C, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_D)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_D, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_E)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_E, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_F)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_F, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_G)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_G, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_H)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_H, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B01)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B01, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B02)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B02, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B03)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B03, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B04)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B04, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B05)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B05, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B06)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B06, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B07)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B07, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B08)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B08, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTSWITCHMODE)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTSWITCHMODE, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTKEEPTIME)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTKEEPTIME, pData->m_strValue, true);
    }
    else if(pData->m_strID == STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTDELAYTIME)
    {
        pParas->SetDataValue(STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTDELAYTIME, pData->m_strValue, true);
    }

    return;
}

void QSttMultiMacroParaEditViewRecloseAcc::CheckAllPresence(CExBaseList *pParas)
{
    RecloseAccCheckParaExist(pParas, STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FRE);

    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PREFAULTTIME);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTIME);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_FAULTTRIGMODE);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PTPOS);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_CTPOS);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_PREFAULTTIME);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOAD);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_ILOADPH);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_SIMULATEBREAKERDELAY);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKBREAKTIME);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BRKCLOSETIME);

    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_BINSELECT);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_A);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_C);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_D);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_E);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_F);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_G);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_H);


    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B01);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B02);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B03);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B04);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B05);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B06);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B07);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_B08);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTSWITCHMODE);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTKEEPTIME);
    RecloseAccCheckParaExist(pParas,STT_MULTI_MACRO_RECLOSEACC_PARAS_ID_OUTPUTDELAYTIME);

    return;
}
//20240805 wanmj 从测试项获取公共参数给m_oTestMacroUI_Paras
void QSttMultiMacroParaEditViewRecloseAcc::GetMacroTestDataToParas(CDataGroup *pParas, CExBaseList* pInnerTestmacro)
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

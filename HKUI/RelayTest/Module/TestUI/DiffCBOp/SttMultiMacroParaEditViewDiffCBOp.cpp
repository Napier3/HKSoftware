#include "SttMultiMacroParaEditViewDiffCBOp.h"
//#include "ui_SttMultiMacroParaEditViewDistance.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "DiffCBOpItemParaEditWidget.h"
#include "../../SttTest/Common/tmt_common_def.h"
//#ifdef _PSX_QT_WINDOWS_
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "SttMultiMacroDiffCBOpParasDefine.h"
#include "DiffCBOpCommonParasDlg.h"
#include "DiffCBOpBinarysDlg.h"
#include "DiffCBOpResultEstimateDlg.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include <QDesktopWidget>

extern CGbSmartGenWzd *g_theGbSmartGenWzd;
//#endif
//#include "SttTestCntrFrameWin.h"

QSttMultiMacroParaEditViewDiffCBOp::QSttMultiMacroParaEditViewDiffCBOp(const CString &strGridFile,QWidget *parent) :
QSttMultiMacroParaEditViewBase(strGridFile,parent)
{
//    m_pAddMultiItemSelectDlg = NULL;//放入基类  zhouhj 2024.9.15
    m_pLabel = new QLabel(this);
    m_pLabel->setAlignment(Qt::AlignCenter);
 //	CString strGbXmlPath;
 //	strGbXmlPath = _P_GetLibraryPath();
 //	strGbXmlPath += "Distance.gbxml";
 //	CSttGuideBook *pSttGuideBook = (CSttGuideBook*)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
 //	CExBaseList oTempList;
 //	oTempList.Append(pSttGuideBook);
 //	pSttGuideBook->RemoveAll();
 //
 //	pSttGuideBook->OpenXmlFile(strGbXmlPath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
 //	pSttGuideBook->AppendEx(oTempList);
 //	oTempList.RemoveAll();
 //	m_pMulitMacroRootItems = pSttGuideBook->FindFirstItems(STTITEMS_NODETYPE_ROOTNODE, TRUE);
 //	stt_gb_get_all_macro_items(STT_MACRO_ID_Distance,&m_oSingleMacroItemsRef,m_pMulitMacroRootItems);
    m_pSingleMacroRef = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_DiffCBOp);

    //m_pZPhiGridInst = NULL;
    //m_pRXGridInst = NULL;
	m_pDiffCBOpWiringWidget = NULL;
	m_pDiffCBOpWiringWidget = new QDiffCBOpWiringWidget(this);
}

QSttMultiMacroParaEditViewDiffCBOp::~QSttMultiMacroParaEditViewDiffCBOp()
{
}

void QSttMultiMacroParaEditViewDiffCBOp::InitUI_OneMacro()
{
    QSttMultiMacroParaEditViewBase::InitUI_OneMacro();
    m_pSingleItemParaEditWidget = new QDiffCBOpItemParaEditWidget();
    m_pSingleItemParaEditWidget->InitDatas(m_pSingleMacroRef);

    CString strText;
	strText = /*"功能参数"*/g_sLangTxt_Impedance_FunParas;
    m_pSingleItemEditTab->insertTab(0,m_pSingleItemParaEditWidget,strText);

//     m_pGoosePubsWidget = new QGooseParaWidget(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr());
//     strText = "GOOSE发布";
//     m_pSingleItemEditTab->insertTab(1,m_pGoosePubsWidget,strText);
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();


    QString strImagePath;
#ifdef _PSX_QT_WINDOWS_
        strImagePath = _P_GetResourcePath();
        strImagePath = strImagePath + _T("DiffCBOpHIn.png");
#else
        strImagePath = ":/ctrls/images/DiffCBOpHIn.png";
#endif
		//strText = "示意图";
    m_pDiagramTab = new QStackedWidget();
		//m_pDiagramTab->resize(700, 400);
		//m_pSingleItemEditTab->insertTab(2, m_pDiagramTab, strText);
    slot_strImagePath(strImagePath);

	strText = /*"添加单项"*/g_sLangTxt_DiffCBOp_AddOneItme;
    m_pAddOneItemBtn = new QPushButton(strText);
	strText = /*"结果评估"*/g_sLangTxt_StateEstimate_ResultEstimate;
    m_pResultAssessBtn = new QPushButton(strText);

	m_pBottomHboxLayout->insertWidget(0, m_pAddOneItemBtn);
    m_pBottomHboxLayout->insertWidget(5,m_pResultAssessBtn);

}

void QSttMultiMacroParaEditViewDiffCBOp::UpdateGoutTab(BOOL bUpdateList)
{
	//m_pGoosePubsWidget->initGoosePubTable(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr());
	if (g_oSystemParas.m_nHasDigital)
	{
		InitGoosePubDataGroups();
		UpdateGoutTab_UI(m_listGoosePub.at(0));
	}
	else
	{
		RemoveGooseParaWidget();
	}
}

void QSttMultiMacroParaEditViewDiffCBOp::InitGridTitleLanguage()
{
	if (m_pDiffProtectionGrid == NULL)
		return;

	CSttGdInst_Cols *pSttGdInst_Cols = m_pDiffProtectionGrid->GetInst_Cols();
	CSttGdInst_Col *pSttGdInst_Col = NULL;
	POS pos = pSttGdInst_Cols->GetHeadPosition();
	while (pos != NULL)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos);
		SetValueToInstColName(pSttGdInst_Col);
	}
}

void QSttMultiMacroParaEditViewDiffCBOp::SetValueToInstColName(CSttGdInst_Col *pSttGdInst_Col)
{
	if (pSttGdInst_Col == NULL)
		return;
	if (pSttGdInst_Col->m_pSttGdColDef_Ref == NULL)
		return;

	if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_SELECT)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_Select;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_STATE)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_Syn_State;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_TESTRSLT)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_Gradient_TestResult;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTTYPE)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_Gradient_FailType;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_FAULTLOCATION)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_DiffCBOp_FaultLocation;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_ERRORTYPE)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = g_sLangTxt_StateEstimate_ErrorType;
	}
	
}

void QSttMultiMacroParaEditViewDiffCBOp::InitDatas(CSttItems *pCurrRootItems)
{
    DisConnectAll_SigSlot();
    m_pDiffProtectionGrid = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_DiffCBOp,STT_MULTI_MACRO_DIFFCBOP_PARAS_GRID_ID);
	InitGridTitleLanguage();
    m_pCurrMacroParaEditGrid->InitColDef(m_pDiffProtectionGrid,m_pSingleMacroRef,g_theHtmlRptGenFactory->m_pDataTypes/*((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->GetDataTypes()*/);
    QSttMultiMacroParaEditViewBase::InitDatas(pCurrRootItems);
    CheckAllPresence(&m_oSingleMacroItemsRef);
    m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);
    ConnectAll_SigSlot();
	slot_UpdateDiffCBOpWiringWidget();
}

void QSttMultiMacroParaEditViewDiffCBOp::CheckAllPresence(CExBaseList *pListItems)
{
    POS pos = m_oSingleMacroItemsRef.GetHeadPosition();
    while(pos != NULL)
    {
        CExBaseObject *pData = (CExBaseObject *)m_oSingleMacroItemsRef.GetNext(pos);
        if(pData->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
        {
            continue;
        }
        CSttMacroTest *pMacroTest = (CSttMacroTest *)pData;
        CSttMacroTestParaDatas *pParaDatas = pMacroTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
       // CheckForPresence(pParaDatas,STT_MULTI_MACRO_DIFFCBOP_PARAS_ID_KCAL);
    }
}

void QSttMultiMacroParaEditViewDiffCBOp::ConnectAll_SigSlot()
{
    QSttMultiMacroParaEditViewBase::ConnectAll_SigSlot();
    connect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
    connect(m_pSingleItemParaEditWidget,SIGNAL(sig_strImagePath(const QString&)),this,SLOT(slot_strImagePath(const QString&)));
    connect(m_pResultAssessBtn,SIGNAL(clicked()),this,SLOT(slot_ResultEstimateBtnClick()));
    connect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));

	connect(m_pSingleItemParaEditWidget, SIGNAL(sig_UpdateDiffWiringWidget()), this, SLOT(slot_UpdateDiffCBOpWiringWidget()));
}

void QSttMultiMacroParaEditViewDiffCBOp::DisConnectAll_SigSlot()
{
    QSttMultiMacroParaEditViewBase::DisConnectAll_SigSlot();
    disconnect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
    disconnect(m_pSingleItemParaEditWidget,SIGNAL(sig_strImagePath(const QString&)),this,SLOT(slot_strImagePath(const QString&)));
    disconnect(m_pResultAssessBtn,SIGNAL(clicked()),this,SLOT(slot_ResultEstimateBtnClick()));
    disconnect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
}

//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
CSttItems* QSttMultiMacroParaEditViewDiffCBOp::GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest)
{
    return QSttMultiMacroParaEditViewBase::GetRootItems_CurrTestMacro(pSttMacroTest);
}

void QSttMultiMacroParaEditViewDiffCBOp::slot_AddOneItemBtnClick()
{
    QSttMultiMacroParaEditViewBase::slot_AddOneItemBtnClick();

}

void QSttMultiMacroParaEditViewDiffCBOp::InitAddMultiItemSelectDlg(QPoint pos,int nDlgState)
{
    if (m_pAddMultiItemSelectDlg == NULL)
    {
        m_pAddMultiItemSelectDlg = new QDialog(this);
        //m_pAddMultiItemSelectDlg->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
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


         pLayout->addWidget(pBtnDeleteSelItem,3,0);
         pLayout->addWidget(pBtnDeleteAllItem,4,0);

         pLayout->addWidget(pBtnClearSelResult,5,0);
         pLayout->addWidget(pBtnClearAllResult,6,0);

         connect(pBtnDeleteSelItem,SIGNAL(clicked()),this,SLOT(slot_DeleteSelItemBtnClick()));
         connect(pBtnDeleteAllItem,SIGNAL(clicked()),this,SLOT(slot_DeleteAllItemBtnClick()));

         connect(pBtnClearSelResult,SIGNAL(clicked()),this,SLOT(slot_ClearSelResultBtnClick()));
         connect(pBtnClearAllResult,SIGNAL(clicked()),this,SLOT(slot_ClearAllResultBtnClick()));
     }
     QStringList listTmp;
     switch(nDlgState)
     {
     case DELETEITEM_DLG:
         listTmp.append(g_sLangTxt_Button_DeleteSelItem);
         listTmp.append(g_sLangTxt_Button_DeleteAllItem);
         break;
     case CLEARSELRESULT:
         listTmp.append(g_sLangTxt_Button_ClearSelResult);
         listTmp.append(g_sLangTxt_Button_ClearAllResult);
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

void QSttMultiMacroParaEditViewDiffCBOp::slot_CommonParasBtnClick()
{
    //通用参数页面
    QDiffCBOpCommonParasDlg oDiffCBOpCommonParasDlg;
    oDiffCBOpCommonParasDlg.SetDatas(((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());

    if(oDiffCBOpCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oDiffCBOpCommonParasDlg.CheckItemsModify(pItem))
            {
                oDiffCBOpCommonParasDlg.GetDatas(((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
                oDiffCBOpCommonParasDlg.UpdataAllCommonParas(&m_oSingleMacroItemsRef);
				CString strText1 = /*"高压侧(区内)"*/g_sLangTxt_DiffCBOp_FauleInH;
				CString strText2 = /*"高压侧(区外)"*/g_sLangTxt_DiffCBOp_FauleOutH;
				CString strText3 = /*"低压侧(区内)"*/g_sLangTxt_DiffCBOp_FauleInL;
				CString strText4 =/* "低压侧(区外)"*/g_sLangTxt_DiffCBOp_FauleOutL;
				CString strText5 = /*"中压侧(区内)"*/g_sLangTxt_DiffCBOp_FauleInM;
				CString strText6 = /*"中压侧(区外)"*/g_sLangTxt_DiffCBOp_FauleOutM;
				long nValue = oDiffCBOpCommonParasDlg.m_nCoordinate;
				if (nValue == 0)
				{
					((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurLabel->setText(g_sLangTxt_Current + "(A)");
				}
				else if (nValue == 1)
				{
					((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurLabel->setText(g_sLangTxt_Current + "(In)");
				}
				long nAdoptWind = oDiffCBOpCommonParasDlg.m_nAdoptWind;
				int itemCount = ((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurCmbAdoptWind->count();
				if (nAdoptWind == 0)
				{
					if (itemCount >= 4)
					{
						((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurCmbAdoptWind->setItemText(0, strText1);
						((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurCmbAdoptWind->setItemText(1, strText2);
						((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurCmbAdoptWind->setItemText(2, strText3);
						((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurCmbAdoptWind->setItemText(3, strText4);
					}
				}
				else if (nAdoptWind == 1)
				{
					if (itemCount >= 4)
					{
						((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurCmbAdoptWind->setItemText(0, strText1);
						((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurCmbAdoptWind->setItemText(1, strText2);
						((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurCmbAdoptWind->setItemText(2, strText5);
						((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurCmbAdoptWind->setItemText(3, strText6);
					}
				}
				else if (nAdoptWind == 2)
				{
					if (itemCount >= 4)
					{
						((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurCmbAdoptWind->setItemText(0, strText5);
						((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurCmbAdoptWind->setItemText(1, strText6);
						((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurCmbAdoptWind->setItemText(2, strText3);
						((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->m_pCurCmbAdoptWind->setItemText(3, strText4);
					}
				}
                Ats_UpdateMacroTestItems();
                //m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);
				slot_UpdateDiffCBOpWiringWidget();
            }
        }
}

void QSttMultiMacroParaEditViewDiffCBOp::slot_ResultEstimateBtnClick()
{
    QDiffCBOpResultEstimateDlg oDiffCBOpResultEstimateDlg;
    oDiffCBOpResultEstimateDlg.SetDatas(((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());

//    if(oDiffCBOpResultEstimateDlg.exec() == QDialog::Accepted)
//    {
//        oDiffCBOpResultEstimateDlg.UpdataAllResult(&m_oSingleMacroItemsRef);
//        Ats_UpdateMacroTestItems();
//        m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);
//    }
    if(oDiffCBOpResultEstimateDlg.exec() == QDialog::Accepted)
    {
        CExBaseList *pItem = ((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
        if (pItem == NULL)
        {
            pItem = ((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
        }
        if (oDiffCBOpResultEstimateDlg.CheckItemsModify(pItem))
        {
            oDiffCBOpResultEstimateDlg.GetDatas(((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
            oDiffCBOpResultEstimateDlg.UpdataAllResults(&m_oSingleMacroItemsRef);
            Ats_UpdateMacroTestItems();
        }
    }
}


void QSttMultiMacroParaEditViewDiffCBOp::slot_BinarysBtnClick()
{
    //开入量、开出量页面
    QDiffCBOpBinarysDlg oDiffCBOpBinarysDlg;
    oDiffCBOpBinarysDlg.SetDatas(((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());

//    if(oDiffCBOpBinarysDlg.exec() == QDialog::Accepted)
//    {
//        oDiffCBOpBinarysDlg.UpdataAllBinarys(&m_oSingleMacroItemsRef);
//        Ats_UpdateMacroTestItems();
//    }
    if(oDiffCBOpBinarysDlg.exec() == QDialog::Accepted)
    {
        CExBaseList *pItem = ((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
        if (pItem == NULL)
        {
            pItem = ((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
        }
        if (oDiffCBOpBinarysDlg.CheckItemsModify(pItem))
        {
            oDiffCBOpBinarysDlg.GetDatas(((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
            oDiffCBOpBinarysDlg.UpdataAllBinarys(&m_oSingleMacroItemsRef);
            Ats_UpdateMacroTestItems();
        }
    }
}

void QSttMultiMacroParaEditViewDiffCBOp::slot_DeleteItemBtnClick()
{
    InitAddMultiItemSelectDlg(m_pDeleteItemBtn->pos(),DELETEITEM_DLG);
}

void QSttMultiMacroParaEditViewDiffCBOp::slot_DeleteSelItemBtnClick()
{
    QSttMultiMacroParaEditViewBase::slot_DeleteSelItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
//     m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewDiffCBOp::slot_DeleteAllItemBtnClick()
{
    QSttMultiMacroParaEditViewBase::slot_DeleteAllItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
//     m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewDiffCBOp::slot_ClearResultBtnClick()
{
    InitAddMultiItemSelectDlg(m_pClearResultBtn->pos(),CLEARSELRESULT);
}

void QSttMultiMacroParaEditViewDiffCBOp::slot_ClearSelResultBtnClick()
{
    QSttMultiMacroParaEditViewBase::slot_ClearSelResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
//     m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewDiffCBOp::slot_ClearAllResultBtnClick()
{
    QSttMultiMacroParaEditViewBase::slot_ClearAllResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
//     m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewDiffCBOp::slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest)
{
    QSttMultiMacroParaEditViewBase::slot_ParaEditWidget_To_Grid(pMacroTest);
}

void QSttMultiMacroParaEditViewDiffCBOp::slot_strImagePath(const QString &strImagePath)
{
    m_pLabel->clear();
    QPixmap pixmap(strImagePath);
    if (!pixmap.isNull())
    {
			QDesktopWidget* desktopWidget = QApplication::desktop();
			QRect rect = desktopWidget->screenGeometry();
			if (rect.height() <= 1080)
			{
				pixmap = pixmap.scaled(QSize(950, 600));

			}
			else
			{
				pixmap = pixmap.scaled(QSize(1100, 700));
			}

        m_pLabel->setPixmap(pixmap);
        m_pLabel->update();
			m_pLabel->setScaledContents(true);
		m_pDiagramTab->addWidget(m_pLabel);
    }
}

void QSttMultiMacroParaEditViewDiffCBOp::slot_UpdateDiffCBOpWiringWidget()
{
	m_pDiffCBOpWiringWidget->setCommonData(((QDiffCBOpItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
	m_pDiffCBOpWiringWidget->updateTable(STT_MULTI_MACRO_DIFFCBOP_PARAS_GRID_ID);
}
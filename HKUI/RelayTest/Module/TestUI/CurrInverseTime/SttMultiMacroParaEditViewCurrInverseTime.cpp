#include "SttMultiMacroParaEditViewCurrInverseTime.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../UI/SttTestCntrFrameApi.h"

//#ifdef _USE_SoftKeyBoard_	
//#include "../../UI/SoftKeyboard/SoftKeyBoard.h"
//#endif

#ifdef _PSX_QT_WINDOWS_
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;
#endif

QSttMultiMacroParaEditViewCurrInverseTime::QSttMultiMacroParaEditViewCurrInverseTime(const CString &strGridFile,QWidget *parent) :
    QSttMultiMacroParaEditViewBase(strGridFile,parent)
{
//	m_pAddMultiItemSelectDlg = NULL;//放入基类  zhouhj 2024.9.15

	//CString strGbXmlPath;
	//strGbXmlPath = _P_GetLibraryPath();
	//strGbXmlPath += "CurrInverseTime.gbxml";
	//CSttGuideBook *pSttGuideBook = (CSttGuideBook*)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	//CExBaseList oTempList;
	//oTempList.Append(pSttGuideBook);
	//pSttGuideBook->RemoveAll();
	//
	//pSttGuideBook->OpenXmlFile(strGbXmlPath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	//pSttGuideBook->AppendEx(oTempList);
	//oTempList.RemoveAll();

	//m_pCurrRootItems = pSttGuideBook->FindFirstItems(STTITEMS_NODETYPE_ROOTNODE, TRUE);
	//stt_gb_get_macro_items(STT_MACRO_ID_CurrInverseTime,&m_oSingleMacroItemsRef,m_pCurrRootItems);
	m_pSingleMacroRef = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_ActionTime);
	m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();

	//pCharLibWidget = (QCharEditMainWidget*)g_theTestCntrFrame->GetCharEditMainWidget();
}

QSttMultiMacroParaEditViewCurrInverseTime::~QSttMultiMacroParaEditViewCurrInverseTime()
{
}

void QSttMultiMacroParaEditViewCurrInverseTime::InitUI_OneMacro()
{
	QSttMultiMacroParaEditViewBase::InitUI_OneMacro();
	m_pSingleItemParaEditWidget = new QCurrInverTimeItemParaEditWidget();
	//m_pSingleItemParaEditWidget->m_pSingleMacroRef = m_pSingleMacroRef;
	m_pSingleItemParaEditWidget->InitDatas(m_pSingleMacroRef);

	CString strText;
	strText = g_sLangTxt_Impedance_FunParas/*"功能参数"*/;
	m_pSingleItemEditTab->insertTab(0,m_pSingleItemParaEditWidget,strText);

// 	m_pGoosePubsWidget = new QGooseParaWidget(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr());
// 	strText = "GOOSE发布";
// 	m_pSingleItemEditTab->insertTab(1,m_pGoosePubsWidget,strText);
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();

	//strText = "添加单项";
	m_pAddOneItemBtn = new QPushButton(/*strText*/g_sLangTxt_Button_AddOneItem);
	//strText = "添加系列";
	m_pAddMultiItemBtn = new QPushButton(/*strText*/g_sLangTxt_Button_AddMultiItem);
	
	m_pBottomHboxLayout->insertWidget(0,m_pAddOneItemBtn);
	m_pBottomHboxLayout->insertWidget(1,m_pAddMultiItemBtn);
	//InitDatas();
}

void QSttMultiMacroParaEditViewCurrInverseTime::InitDatas(CSttItems *pCurrRootItems)
{
	DisConnectAll_SigSlot();

	m_pCurrInst = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_ActionTime,STT_MACRO_ID_CurrentInverseTime);
	m_pCurrMacroParaEditGrid->InitColDef(m_pCurrInst,m_pSingleMacroRef,g_theHtmlRptGenFactory->m_pDataTypes);
	QSttMultiMacroParaEditViewBase::InitDatas(pCurrRootItems);
	CheckAllPresence();
	m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);
	//20240926 gongyiping 初始化数据时 CSttMacroTest为空显示提示信息
	if (m_oSingleMacroItemsRef.FindByClassID(STTGBXMLCLASSID_CSTTMACROTEST) == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, g_sLangID_Distance_AddTestItemTips /*_T("请添加测试项！")*/);//在初始化没有测试项时提示；
	}
	ConnectAll_SigSlot();
}

void QSttMultiMacroParaEditViewCurrInverseTime::CheckAllPresence()
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
		CheckForPresence(pParaDatas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT);
		CheckForPresence(pParaDatas,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_TSETTING);
	}
}

void QSttMultiMacroParaEditViewCurrInverseTime::ConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::ConnectAll_SigSlot();
	connect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	connect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	connect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
	//connect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrPoint(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Draw(CSttMacroTest*)));
}

void QSttMultiMacroParaEditViewCurrInverseTime::DisConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::DisConnectAll_SigSlot();
	disconnect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	disconnect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	disconnect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
	//disconnect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrPoint(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Draw(CSttMacroTest*)));
}

//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
CSttItems* QSttMultiMacroParaEditViewCurrInverseTime::GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest)
{
	return QSttMultiMacroParaEditViewBase::GetRootItems_CurrTestMacro(pSttMacroTest);

	if (pSttMacroTest == NULL)
	{
		return NULL;
	}

	if (m_pMulitMacroRootItems == NULL)
	{
		return NULL;
	}

	CSttMacroTestParaData *pSttMacroTestParaData = Global_FindAddMacroTestParaData(pSttMacroTest,m_pSingleMacroRef,STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE);

	if (pSttMacroTestParaData == NULL)
	{
		return NULL;
	}

	CString strItemID,strItemName;
	long nFaultType = CString_To_long(pSttMacroTestParaData->m_strValue);

	switch(nFaultType)
	{
	case CURRINVERSE_FAULT_TYPE_AE:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_AE;
		strItemName = "A相接地";
		break;
	case CURRINVERSE_FAULT_TYPE_BE:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_BE;
		strItemName = "B相接地";
		break;
	case CURRINVERSE_FAULT_TYPE_CE:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_CE;
		strItemName = "C相接地";
		break;
	case CURRINVERSE_FAULT_TYPE_AB:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_AB;
		strItemName = "AB相间";
		break;
	case CURRINVERSE_FAULT_TYPE_BC:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_BC;
		strItemName = "BC相间";
		break;
	case CURRINVERSE_FAULT_TYPE_CA:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_CA;
		strItemName = "CA相间";
		break;
	case CURRINVERSE_FAULT_TYPE_ABC:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_ABC;
		strItemName = "三相短路";
		break;
	case CURRINVERSE_FAULT_TYPE_3I0:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_3I0;
		strItemName = "3I0";
		break;
	case CURRINVERSE_FAULT_TYPE_IAIBIC:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_IAIBIC;
		strItemName = "Ia+Ib+Ic";
		break;
	case CURRINVERSE_FAULT_TYPE_UAIA:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_UAIA;
		strItemName = "Ua,Ia";
		break;
	case CURRINVERSE_FAULT_TYPE_UAUB:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_UAUB;
		strItemName = "Va,Vb";
		break;
	case CURRINVERSE_FAULT_TYPE_A:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_A;
		strItemName = "A";
		break;
	case CURRINVERSE_FAULT_TYPE_B:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_B;
		strItemName = "B";
		break;
	case CURRINVERSE_FAULT_TYPE_C:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_C;
		strItemName = "C";
		break;

	default:
		strItemID = STT_MULTI_MACRO_CURRINVERSE_Items_ID_AE;
		strItemName = "A相接地";
		break;
	}

	CSttItems *pCSttItems = (CSttItems*)m_pMulitMacroRootItems->FindByID(strItemID);

	if (pCSttItems != NULL)
	{
		return pCSttItems;
	}

	CSttItems *pNewItems = new CSttItems;
	pNewItems->m_strID = strItemID;
	pNewItems->m_strName = strItemName;
	m_pMulitMacroRootItems->AddNewChild(pNewItems);
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_NewItems(m_pMulitMacroRootItems, pNewItems);

	g_theTestCntrFrame->m_pSttGbTreeView->m_pTreeCtrl->AddObj(pNewItems, TRUE);

	CString strParentItemPath = m_pMulitMacroRootItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
// #ifdef _PSX_QT_WINDOWS_//zhouhj 2024.10.10 删除防止自动添加测试项
// 	g_theGbSmartGenWzd->NewItems(strParentItemPath, pNewItems);
// 	g_theGbSmartGenWzd->ItemsAdd(strParentItemPath, pNewItems->m_strID, pNewItems->m_strName
// 		, pNewItems->m_nTestTimes, pNewItems->m_nRptTitle, pNewItems->m_nTitleLevel);
// #endif
	return pNewItems;
}

void QSttMultiMacroParaEditViewCurrInverseTime::slot_AddOneItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_AddOneItemBtnClick();
}

void QSttMultiMacroParaEditViewCurrInverseTime::slot_AddMultiItemBtnClick()
{
	QCurrInverAddMultDlg oCurrInverAddMultDlg;
	////oCurrInverAddMultDlg.setFont(*g_pSttGlobalFont);
	//CDataGroup *pTestMacroUI_Paras = GetAddMultItems_Paras();
	//CDataGroup *pCurrTestMacroUI_Paras  = (CDataGroup*)pTestMacroUI_Paras->Clone();
	///*	CDataGroup *pPara = oDistanceAddMultDlg.GetDisTanceParas();*/
	//oCurrInverAddMultDlg.SetDatas(pCurrTestMacroUI_Paras);

	GetMacroTestDataToParas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, ((QCurrInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
	oCurrInverAddMultDlg.SetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);

	if(oCurrInverAddMultDlg.exec() == QDialog::Accepted)
	{
		//??????zhouhj备注,此处逻辑是有问题的,在点击确认时，就应该把对应的数据存入链表，此处不需要再调用GetDatas
		//oCurrInverAddMultDlg.GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
		CDvmData *pData_Select = (CDvmData *)oCurrInverAddMultDlg.m_pDataGroup->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Select);//I*
		if (pData_Select->m_strValue.toInt())//相位
		{
			oCurrInverAddMultDlg.CheckAllPresence();	
			AddMultiItems(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, ((QCurrInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                        UpdateBottomBtnsEnable();
			return;
			
		}
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
	}
	//UpdateBottomBtnsEnable();
	return;
	//pCurrTestMacroUI_Paras->DeleteAll();
	//delete pCurrTestMacroUI_Paras;
	//pCurrTestMacroUI_Paras = NULL;
}

void QSttMultiMacroParaEditViewCurrInverseTime::GetMacroTestDataToParas(CDataGroup *pParas, CExBaseList* pInnerTestmacro)
{
	if (pParas == NULL || pInnerTestmacro == NULL)
		return;

	CheckAllPresence(pInnerTestmacro);

	POS pos = pInnerTestmacro->GetHeadPosition();
	while (pos != NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pInnerTestmacro->GetNext(pos);
		SetValueToParas(pParas, pData);
	}

	return;
}

void QSttMultiMacroParaEditViewCurrInverseTime::CheckAllPresence(CExBaseList *pParas)
{
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreFaultTime);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_UPre);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_IPre);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreAngle);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreFre);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RefValueType);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_In);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CTPos);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Ipu);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultTime);

	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_AndOr);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_A);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_B);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_C);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_D);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_E);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_F);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_G);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID_H);

	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B01);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B02);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B03);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B04);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B05);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B06);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B07);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B08);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B1);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B2);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B3);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B4);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B5);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B6);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B7);
	CurrInverseCheckExist(pParas, STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B8);

	return;
}

void QSttMultiMacroParaEditViewCurrInverseTime::CurrInverseCheckExist(CExBaseList *pParas, CString strID)
{
	if (pParas == NULL)
		return;

	CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pParas->FindByID(strID);
	if (pData == NULL)
	{
		CSttMacroTestParaData *pNew = new CSttMacroTestParaData();
		pNew->m_strName = STT_MULTI_MACRO_CurrInverTime_PARAS_ID_DEFAULT;
		pNew->m_strID = strID;
		pNew->m_strValue = STT_MULTI_MACRO_CurrInverTime_PARAS_ID_DEFAULT;
		pParas->AddNewChild(pNew);
	}
}

void QSttMultiMacroParaEditViewCurrInverseTime::SetValueToParas(CDataGroup *pParas, CSttMacroTestParaData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreFaultTime)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_PreFaultTime, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_UPre)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_UPre, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_IPre)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_IPre, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreAngle)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_PreAngle, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_PreFre)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_PreFre, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RefValueType)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_RefValueType, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_In)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_In, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CTPos)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_CTPos, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Ipu)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_Ipu, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultTime)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_FaultTime, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_A)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_A, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_B)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_C)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_C, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_D)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_D, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_E)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_E, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_F)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_F, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_G)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_G, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_H)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_H, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B01)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B01, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B02)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B02, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B03)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B03, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B04)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B04, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B05)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B05, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B06)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B06, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B07)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B07, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B08)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B08, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B1)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B1, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B2)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B2, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B3)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B3, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B4)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B4, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B5)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B5, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B6)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B6, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B7)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B7, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID__B8)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_B8, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_AndOr)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_CurrInverTime_PARAS_ADDMULT_ID_ANDOR, pData->m_strValue, true);
	}

	return;
}

//故障类型的测试点循环
void QSttMultiMacroParaEditViewCurrInverseTime::AddMultiItems(CDataGroup *pParas, CExBaseList* pInnerTestmacro)
{
	CDvmData *pFaultTypeA = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_AN_CHECK);//故障类型-A
	CDvmData *pFaultTypeB = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_BN_CHECK);//故障类型-B
	CDvmData *pFaultTypeC = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CN_CHECK);//故障类型-C
	CDvmData *pFaultTypeAB = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_AB_CHECK);//故障类型-AB
	CDvmData *pFaultTypeBC = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_BC_CHECK);//故障类型-BC
	CDvmData *pFaultTypeCA = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CA_CHECK);//故障类型-CA
	CDvmData *pFaultTypeABC = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABC_CHECK);//故障类型-ABC
	CDvmData *pFaultTypeIaIbIc = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_IaIbIc_CHECK);//故障类型-IaIbIc
	CSttMacroTestParaData *pData = NULL;


	if (pFaultTypeA->m_strValue.toInt() == 1)
	{
		pData = (CSttMacroTestParaData *)pInnerTestmacro->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE);//故障类型
		pData->m_strValue.setNum(CURRINVERSE_FAULT_TYPE_AE);
		GetMacroTestParasToData(pParas, pInnerTestmacro);
	}
	if (pFaultTypeB->m_strValue.toInt() == 1)
	{
		pData = (CSttMacroTestParaData *)pInnerTestmacro->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE);//故障类型
		pData->m_strValue.setNum(CURRINVERSE_FAULT_TYPE_BE);
		GetMacroTestParasToData(pParas, pInnerTestmacro);
	}
	if (pFaultTypeC->m_strValue.toInt() == 1)
	{
		pData = (CSttMacroTestParaData *)pInnerTestmacro->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE);//故障类型
		pData->m_strValue.setNum(CURRINVERSE_FAULT_TYPE_CE);
		GetMacroTestParasToData(pParas, pInnerTestmacro);
	}
	if (pFaultTypeAB->m_strValue.toInt() == 1)
	{
		pData = (CSttMacroTestParaData *)pInnerTestmacro->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE);//故障类型
		pData->m_strValue.setNum(CURRINVERSE_FAULT_TYPE_AB);
		GetMacroTestParasToData(pParas, pInnerTestmacro);
	}
	if (pFaultTypeBC->m_strValue.toInt() == 1)
	{
		pData = (CSttMacroTestParaData *)pInnerTestmacro->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE);//故障类型
		pData->m_strValue.setNum(CURRINVERSE_FAULT_TYPE_BC);
		GetMacroTestParasToData(pParas, pInnerTestmacro);
	}
	if (pFaultTypeCA->m_strValue.toInt() == 1)
	{
		pData = (CSttMacroTestParaData *)pInnerTestmacro->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE);//故障类型
		pData->m_strValue.setNum(CURRINVERSE_FAULT_TYPE_CA);
		GetMacroTestParasToData(pParas, pInnerTestmacro);
	}
	if (pFaultTypeABC->m_strValue.toInt() == 1)
	{
		pData = (CSttMacroTestParaData *)pInnerTestmacro->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE);//故障类型
		pData->m_strValue.setNum(CURRINVERSE_FAULT_TYPE_ABC);
		GetMacroTestParasToData(pParas, pInnerTestmacro);
	}
	if (pFaultTypeIaIbIc->m_strValue.toInt() == 1)
	{
		pData = (CSttMacroTestParaData *)pInnerTestmacro->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE);//故障类型
		pData->m_strValue.setNum(9);
		GetMacroTestParasToData(pParas, pInnerTestmacro);
	}
	return;
}

void QSttMultiMacroParaEditViewCurrInverseTime::GetValueToData(CDataGroup *pParas, CSttMacroTestParaData *pData)
{
	CDvmData *pDataParas = NULL;
	if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Select)
	{
		pDataParas = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_Select);
		pData->m_strValue = pDataParas->m_strValue;
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTVolt)
	{
		pDataParas = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTVolt);
		pData->m_strValue = pDataParas->m_strValue;;
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG)
	{
		pDataParas = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeStart);
		pData->m_strValue = pDataParas->m_strValue;
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT)
	{
		pDataParas = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT);
		pData->m_strValue = pDataParas->m_strValue;
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultFre)
	{
		pDataParas = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FaultFre);
		pData->m_strValue = pDataParas->m_strValue;
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ErrorLogic)
	{
		pDataParas = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ErrorLogic);
		pData->m_strValue = pDataParas->m_strValue;
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RelErr)
	{
		pDataParas = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_RelErr);
		pData->m_strValue = pDataParas->m_strValue;
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_PLUS)
	{
		pDataParas = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_PLUS);
		pData->m_strValue = pDataParas->m_strValue;
	}
	else if (pData->m_strID == STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_MINUS)
	{
		pDataParas = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ABSERR_MINUS);
		pData->m_strValue = pDataParas->m_strValue;
	}

	return;
}

//20241017 gongyiping 克隆当前页面
void QSttMultiMacroParaEditViewCurrInverseTime::CloneMacroTestPage(CString str)
{
	CSttMacroTest *pNewTest = (CSttMacroTest *)m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.CloneEx(TRUE, TRUE);

	CSttMacroTestParaDatas *pDataParas = pNewTest->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG);
	pData->m_strValue = str;



	CSttItems *pParent = GetRootItems_CurrTestMacro(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);

	if (pNewTest->GetSttMacroTestPara() == NULL)
	{
		CSttMacroTestPara *pTestPara = m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.GetSttMacroTestPara();
		CSttMacroTestPara *pNewTestPara = (CSttMacroTestPara *)pNewTest->CreateNewChild(STTGBXMLCLASSID_CSTTMACROPARA);
		pNewTestPara->SetParent(pNewTest);
		CSttMacroTestParaDatas *pNewParas = (CSttMacroTestParaDatas *)pNewTestPara->CreateNewChild(STTGBXMLCLASSID_CSTTMACROPARADATAS);

		pNewTestPara->AddNewChild(pNewParas);
		pNewParas->AppendCloneEx((CExBaseList &)*pTestPara->GetHead());
	}

	pParent->AddNewChild(pNewTest);
	m_oSingleMacroItemsRef.AddTail(pNewTest);

	m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);
	m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroParaEditGrid->rowCount());
}

//20241017 gongyiping 更新下发参数
void QSttMultiMacroParaEditViewCurrInverseTime::UpDataMacroTestPage()
{
	if (m_pCurrMacroParaEditGrid == NULL)
	{
		return;
	}

	CSttItems *pRootItems = GetRootItems_CurrTestMacro(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	CExBaseObject *pCurrObj = NULL;
	CSttMacroTest *pCurrMacroTest = NULL;
	POS pos1 = pRootItems->GetHeadPosition();

	while (pos1)
	{
		pCurrObj = pRootItems->GetNext(pos1);

		if (pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROCHARITEMS)
		{
			CExBaseList *pCurrObjList = NULL;
			pCurrObjList = (CExBaseList*)pCurrObj;
			POS pos_child = pCurrObjList->GetHeadPosition();

			while (pos_child)
			{
				pCurrObj = pCurrObjList->GetNext(pos_child);
				if (pCurrObj->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
				{
					continue;
				}
				pCurrMacroTest = (CSttMacroTest *)pCurrObj;
				g_pTheSttTestApp->m_pTestCtrlCntr->Ats_UpdateOneMacroItem(pCurrMacroTest);
			}
		}
		else
		{
			if (pCurrObj->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
			{
				continue;
			}

			pCurrMacroTest = (CSttMacroTest *)pCurrObj;
			g_pTheSttTestApp->m_pTestCtrlCntr->Ats_UpdateOneMacroItem(pCurrMacroTest);
		}
	}
}

//20241016 gongyiping 添加系列电流相位
void QSttMultiMacroParaEditViewCurrInverseTime::GetMacroTestParasToData(CDataGroup *pParas, CExBaseList* pInnerTestmacro)
{
	CDvmData *pCurrentChangeStart = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeStart);//始值
	CDvmData *pCurrentChangeFinal = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeFinal);//终值
	CDvmData *pCurrentChangeStep = (CDvmData *)pParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CurrentChangeStep);//步长

	CString str, strStart = "";
	double dCurr = 0;
	bool bStartFinal = true;
	CSttMacroTestParaData *pData = NULL;
	POS pos = pInnerTestmacro->GetHeadPosition();
	while (pos != NULL)
	{
		pData = (CSttMacroTestParaData*)pInnerTestmacro->GetNext(pos);
		GetValueToData(pParas, pData);
	}
	//slot_AddOneItemBtnClick();
	CloneMacroTestPage(pCurrentChangeStart->m_strValue);

	strStart = pCurrentChangeStart->m_strValue;
	while (bStartFinal)
	{
		if (strStart > pCurrentChangeFinal->m_strValue)
		{
			dCurr = CString_To_double(strStart) - CString_To_double(pCurrentChangeStep->m_strValue);//实际的电流值
			str.Format(_T("%.3f"), dCurr);
			strStart = str;
			if (str == pCurrentChangeFinal->m_strValue)//始值是否等于终值
			{
				bStartFinal = false;
			}
		}
		else
		{
			dCurr = CString_To_double(strStart) + CString_To_double(pCurrentChangeStep->m_strValue);//实际的电流值
			str.Format(_T("%.3f"), dCurr);
			strStart = str;
			if (str == pCurrentChangeFinal->m_strValue)//始值是否等于终值
			{
				bStartFinal = false;
			}
		}
		pData = (CSttMacroTestParaData *)pInnerTestmacro->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_ANG);//相位差
		pData->m_strValue = str;

		//slot_AddOneItemBtnClick();
		//20241017 gongyiping 克隆当前编辑页面显示节点 
		CloneMacroTestPage(str);

	}
	UpDataMacroTestPage();
	
	return;
}

void QSttMultiMacroParaEditViewCurrInverseTime::slot_CommonParasBtnClick()
{
	QCurrInverseCommonParasDlg oCurrInverseCommonParasDlg;
    //取功能参数编辑界面的参数数据
    oCurrInverseCommonParasDlg.SetDatas(((QCurrInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());

    if(oCurrInverseCommonParasDlg.exec() == QDialog::Accepted)
	{
        CExBaseList *pItem = ((QCurrInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
        if (pItem == NULL)
		{
            pItem = ((QCurrInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
		}
        if (oCurrInverseCommonParasDlg.CheckItemsModify(pItem))
	{
            oCurrInverseCommonParasDlg.GetDatas(((QCurrInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
            //通用参数修改后，修改表格中所有项数据通用参数
		oCurrInverseCommonParasDlg.UpdataAllCommonParas(&m_oSingleMacroItemsRef);
		Ats_UpdateMacroTestItems();
	}
	}
}

void QSttMultiMacroParaEditViewCurrInverseTime::slot_BinarysBtnClick()
{
	QCurrInverBinarysDlg oCurrInverBinarysDlg;
    oCurrInverBinarysDlg.SetDatas(((QCurrInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());

    if(oCurrInverBinarysDlg.exec() == QDialog::Accepted)
	{
        CExBaseList *pItem = ((QCurrInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
        if (pItem == NULL)
		{
            pItem = ((QCurrInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
	}
        if (oCurrInverBinarysDlg.CheckItemsModify(pItem))
	{
            oCurrInverBinarysDlg.GetDatas(((QCurrInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
		oCurrInverBinarysDlg.UpdataAllBinarys(&m_oSingleMacroItemsRef);
		Ats_UpdateMacroTestItems();
	}
	}
}

void QSttMultiMacroParaEditViewCurrInverseTime::InitAddMultiItemSelectDlg(QPoint pos,int nDlgState)
{
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
}

void QSttMultiMacroParaEditViewCurrInverseTime::slot_DeleteItemBtnClick()
{
	InitAddMultiItemSelectDlg(m_pDeleteItemBtn->pos(),DELETEITEM_DLG);
}

void QSttMultiMacroParaEditViewCurrInverseTime::slot_DeleteSelItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteSelItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewCurrInverseTime::slot_DeleteAllItemBtnClick()
{
	//QSttMultiMacroParaEditViewBase::slot_DeleteAllItemBtnClick();
	//电流反时限的节点macro-char-items
	if (m_pCurrMacroParaEditGrid == NULL)
	{
		return;
	}

	CSttItems *pRootItems = GetRootItems_CurrTestMacro(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	CExBaseObject *pCurrObj = NULL;
	CSttMacroTest *pCurrMacroTest = NULL;
	POS pos = pRootItems->GetHeadPosition();

	while (pos)
	{
		pCurrObj = pRootItems->GetNext(pos);

		if (pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROCHARITEMS)
		{
			CExBaseList *pCurrObjList = NULL;
			pCurrObjList = (CExBaseList*)pCurrObj;
			POS pos_child = pCurrObjList->GetHeadPosition();

			while (pos_child)
			{
				pCurrObj = pCurrObjList->GetNext(pos_child);
				if (pCurrObj->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
				{
					continue;
				}
				pCurrMacroTest = (CSttMacroTest *)pCurrObj;
				MultiMacroParaEdit_DeleteOneMacroItem(pCurrMacroTest, m_pCurrMacroItemsRef);
			}
		}
		else
		{
			if (pCurrObj->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
			{
				continue;
			}

			pCurrMacroTest = (CSttMacroTest *)pCurrObj;
			MultiMacroParaEdit_DeleteOneMacroItem(pCurrMacroTest, m_pCurrMacroItemsRef);
		}
	}

    //stt_Frame_AddUpdateReport_QT(m_pMulitMacroRootItems);//zhouhj 2024.10.16 更新报告视图
    //ftt 2024.10.16 使用项目路径更新报告
    QString strItemsPath = m_pMulitMacroRootItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
    stt_Frame_AddUpdateReport_QT(strItemsPath);

    if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
    {
		m_pAddMultiItemSelectDlg->hide();
    }
}

void QSttMultiMacroParaEditViewCurrInverseTime::slot_ClearResultBtnClick()
{
	InitAddMultiItemSelectDlg(m_pClearResultBtn->pos(),CLEARSELRESULT);
}

void QSttMultiMacroParaEditViewCurrInverseTime::slot_ClearSelResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearSelResultBtnClick();
	CSttMacroTest *pCurrSelectData = m_pCurrMacroParaEditGrid->GetCurrSelSttMacroTest();
	if (pCurrSelectData != NULL)
	{
		if (pCurrSelectData->m_nState == TEST_STATE_NORMAL)
		{
			//20241028 luozibing 清除测试结果后 更新测试点状态
			AddUpdateTestPoint_To_Charact(pCurrSelectData, CHAR_TEST_OBJECT_STATE_NORMAL);
		}
	}
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();
//     }//放入基类  zhouhj 2024.9.15
}

void QSttMultiMacroParaEditViewCurrInverseTime::slot_ClearAllResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearAllResultBtnClick();
	POS pos = m_oSingleMacroItemsRef.GetHeadPosition();
	while (pos != NULL)
	{
		CSttMacroTest *pData = (CSttMacroTest *)m_oSingleMacroItemsRef.GetNext(pos);
		if (pData->m_nState == TEST_STATE_NORMAL)
		{
			//20241028 luozibing 清除测试结果后 更新测试点状态 清除时当前选择测试项改变
			AddUpdateTestPoint_To_Charact(pData, CHAR_TEST_OBJECT_STATE_NORMAL);
		}
	}
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewCurrInverseTime::slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest)
{
	QSttMultiMacroParaEditViewBase::slot_ParaEditWidget_To_Grid(pMacroTest);
}

//添加测试项时,在特性曲线界面添加对应测试点
//BOOL QSttMultiMacroParaEditViewCurrInverseTime::AddTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest)
//{
//	if (m_pCharactInterface == NULL)
//	{
//		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
//	}
//	//添加测试点
//	CSttMacroTest *pNewTest = (CSttMacroTest *)m_pCurrMacroItemsRef->GetTail();
//	CSttMacroTestParaDatas *pNewDataParas = pNewTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
//	CSttMacroTestParaData *pData_X = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT);//I*
//	CSttMacroTestParaData *pData_Y = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_TSETTING);//t
//	CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE);//故障类型
//	m_pCharactInterface->AddUpdateTestPoint_Imp(pNewTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), pData_X->m_strValue.toDouble(), pData_Y->m_strValue.toDouble(), pData_Fault->m_strValue.toInt(), NULL);
//	return TRUE;
//}

BOOL QSttMultiMacroParaEditViewCurrInverseTime::DeleteTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest)
{
	if (pCurrMacroTest == NULL)
	{
		return FALSE;
	}

	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}
	m_pCharactInterface->DeleteTestData(pCurrMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE));
	m_bCharTestObjectHasChanged = TRUE;
	return TRUE;
}

BOOL QSttMultiMacroParaEditViewCurrInverseTime::AddUpdateTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest,int nState)
{
	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}
	CSttMacroTestParaDatas *pDataParas = pCurrMacroTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	CSttMacroTestParaData *pData_X = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT);//I*
	CSttMacroTestParaData *pData_Y = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_TSETTING);//t
	CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);//故障类型
	
	double dTime = pData_Y->m_strValue.toDouble();
	if (dTime < 0)
	{
		pData_Y->m_strValue = "-1";
	}

	m_pCharactInterface->AddUpdateTestPoint_Imp(pCurrMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), pData_X->m_strValue.toDouble(), pData_Y->m_strValue.toDouble(), pData_Fault->m_strValue.toInt(), NULL, nState);
	m_bCharTestObjectHasChanged = TRUE;
	return TRUE;
}

BOOL QSttMultiMacroParaEditViewCurrInverseTime::AddItem_From_Charact(double dX, double dY)
{
	//if (m_pMulitMacroRootItems == NULL)
	//{
	//	return FALSE;
	//}

	//CSttItems *pParentItems = GetRootItems_CurrTestMacro(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);

	//if (pParentItems == NULL)
	//{
	//	return FALSE;
	//}

	//if (m_pCharactInterface == NULL)
	//{
	//	m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	//}

	//CDataGroup *pMacroParas = GetAddOneItem_DataGroup(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	//CString strItemPath;
	//strItemPath = pParentItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	//根据坐标生成新建测试项阻抗定值、时间定值、R、X
	//CSttMacroTest *pNewTest = (CSttMacroTest *)m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.Clone();
	//CSttMacroTestParaDatas *pNewDataParas = pNewTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	//CSttMacroTestParaData *pData_X = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT);//I*
	//CSttMacroTestParaData *pData_Y = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_TSETTING);//t

	//double dTime = pData_Y->m_strValue.toDouble();
	//if (dTime < 0)
	//{
	//	pData_Y->m_strValue = "-1";
	//}

	//pData_X->m_strValue.setNum(dX);
	//pData_Y->m_strValue.setNum(dY);
	//CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_FAULTTYPE);//故障类型

	//CSttMacroTestParaDatas *pParaDatas = pNewTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	//pParentItems->AddNewChild(pNewTest,TRUE);

	//long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AddOneMacroItem(pMacroParas,pNewTest->m_strName,pNewTest->m_strID,strItemPath,
	//	0, m_pSingleMacroRef->m_strID, STT_ORG_MACRO_CurrInverseTimeTest_I);

	//if (nRet!= STT_CMD_ExecStatus_SUCCESS)
	//{
	//	pParentItems->Delete(pNewTest);
	//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("添加单个电气量测试功能执行命令失败(%ld)."),nRet);
	//	return FALSE;
	//}

	//m_pCurrMacroItemsRef->AddTail(pNewTest);
	//m_pCurrMacroParaEditGrid->InsertData(pNewTest);
	////添加测试点
	//m_pCharactInterface->AddUpdateTestPoint_Imp(pNewTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), pData_X->m_strValue.toDouble(), pData_Y->m_strValue.toDouble(), pData_Fault->m_strValue.toInt(), NULL);
	//m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());

	CSttMacroTest *pNewTest = &m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner;
	CSttMacroTestParaDatas *pNewDataParas = pNewTest->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);

	//根据坐标设置
	CString strCurr, strTSetting;
	strCurr.setNum(dX);
	strTSetting.setNum(dY);

	CSttMacroTestParaData *pData_X = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_CURRENT);//I*
	CSttMacroTestParaData *pData_Y = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_CurrInverTime_PARAS_ID_TSETTING);//t
	pData_X->m_strValue = CheckDataMinMax(strCurr, 20, 0, 3);
	pData_Y->m_strValue = CheckDataMinMax(strTSetting, 999.999, -1, 3);

	//根据编辑页面添加测试项
	slot_AddOneItemBtnClick();
	m_bCharTestObjectHasChanged = TRUE;

	return TRUE;
}

BOOL QSttMultiMacroParaEditViewCurrInverseTime::UpdateCurrItem_From_Charact(double dX, double dY)
{
	return FALSE;
}

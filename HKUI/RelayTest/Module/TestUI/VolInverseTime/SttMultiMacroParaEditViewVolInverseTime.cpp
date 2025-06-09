#include "SttMultiMacroParaEditViewVolInverseTime.h"
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

QSttMultiMacroParaEditViewVolInverseTime::QSttMultiMacroParaEditViewVolInverseTime(const CString &strGridFile,QWidget *parent) :
    QSttMultiMacroParaEditViewBase(strGridFile,parent)
{
//	m_pAddMultiItemSelectDlg = NULL;//放入基类  zhouhj 2024.9.15

	//CString strGbXmlPath;
	//strGbXmlPath = _P_GetLibraryPath();
	//strGbXmlPath += "VolInverseTime.gbxml";
	//CSttGuideBook *pSttGuideBook = (CSttGuideBook*)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	//CExBaseList oTempList;
	//oTempList.Append(pSttGuideBook);
	//pSttGuideBook->RemoveAll();
	//
	//pSttGuideBook->OpenXmlFile(strGbXmlPath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	//pSttGuideBook->AppendEx(oTempList);
	//oTempList.RemoveAll();

	//m_pCurrRootItems = pSttGuideBook->FindFirstItems(STTITEMS_NODETYPE_ROOTNODE, TRUE);
	//stt_gb_get_macro_items(STT_MACRO_ID_VolInverseTime,&m_oSingleMacroItemsRef,m_pCurrRootItems);
	m_pSingleMacroRef = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_VoltageInverseTime);
	m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
}

QSttMultiMacroParaEditViewVolInverseTime::~QSttMultiMacroParaEditViewVolInverseTime()
{
}

void QSttMultiMacroParaEditViewVolInverseTime::InitUI_OneMacro()
{
	QSttMultiMacroParaEditViewBase::InitUI_OneMacro();
	m_pSingleItemParaEditWidget = new QVolInverTimeItemParaEditWidget();
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

	strText = g_sLangTxt_Button_AddOneItem/*添加测试项*/;
	m_pAddOneItemBtn = new QPushButton(strText);
	strText = g_sLangTxt_Button_AddMultiItem/*"添加系列"*/;
	m_pAddMultiItemBtn = new QPushButton(strText);
	
	m_pBottomHboxLayout->insertWidget(0,m_pAddOneItemBtn);
	m_pBottomHboxLayout->insertWidget(1,m_pAddMultiItemBtn);
	//InitDatas();
}

void QSttMultiMacroParaEditViewVolInverseTime::InitDatas(CSttItems *pCurrRootItems)
{
	DisConnectAll_SigSlot();
	m_pVolInst = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_VoltageInverseTime, STT_MACRO_ID_VoltageInverseTime);
	m_pCurrMacroParaEditGrid->InitColDef(m_pVolInst,m_pSingleMacroRef,g_theHtmlRptGenFactory->m_pDataTypes);
	QSttMultiMacroParaEditViewBase::InitDatas(pCurrRootItems);
	CheckAllPresence();
	m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);
	//20240926 gongyiping 初始化数据时 CSttMacroTest为空显示提示信息
	if (m_oSingleMacroItemsRef.FindByClassID(STTGBXMLCLASSID_CSTTMACROTEST) == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("请添加测试项！"));//在初始化没有测试项时提示；
	}
	ConnectAll_SigSlot();
}

void QSttMultiMacroParaEditViewVolInverseTime::CheckAllPresence()
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
		CheckForPresence(pParaDatas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_VOLTAGE);
		CheckForPresence(pParaDatas,STT_MULTI_MACRO_VolInverTime_PARAS_ID_TSETTING);
	}
}

void QSttMultiMacroParaEditViewVolInverseTime::ConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::ConnectAll_SigSlot();
	connect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	connect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	connect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
	//connect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
}

void QSttMultiMacroParaEditViewVolInverseTime::DisConnectAll_SigSlot()
{ 
	QSttMultiMacroParaEditViewBase::DisConnectAll_SigSlot();
	disconnect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	disconnect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	disconnect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
	//disconnect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
}

//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
CSttItems* QSttMultiMacroParaEditViewVolInverseTime::GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest)
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

	CSttMacroTestParaData *pSttMacroTestParaData = Global_FindAddMacroTestParaData(pSttMacroTest,m_pSingleMacroRef,STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTTYPE);

	if (pSttMacroTestParaData == NULL)
	{
		return NULL;
	}

	CString strItemID,strItemName;
	long nFaultType = CString_To_long(pSttMacroTestParaData->m_strValue);

	switch(nFaultType)
	{
	case VOLINVERSE_FAULT_TYPE_AE:
		strItemID = STT_MULTI_MACRO_VOLINVERSE_Items_ID_AE;
		strItemName = "A相接地";
		break;
	case VOLINVERSE_FAULT_TYPE_BE:
		strItemID = STT_MULTI_MACRO_VOLINVERSE_Items_ID_BE;
		strItemName = "B相接地";
		break;
	case VOLINVERSE_FAULT_TYPE_CE:
		strItemID = STT_MULTI_MACRO_VOLINVERSE_Items_ID_CE;
		strItemName = "C相接地";
		break;
	case VOLINVERSE_FAULT_TYPE_AB:
		strItemID = STT_MULTI_MACRO_VOLINVERSE_Items_ID_AB;
		strItemName = "AB相间";
		break;
	case VOLINVERSE_FAULT_TYPE_BC:
		strItemID = STT_MULTI_MACRO_VOLINVERSE_Items_ID_BC;
		strItemName = "BC相间";
		break;
	case VOLINVERSE_FAULT_TYPE_CA:
		strItemID = STT_MULTI_MACRO_VOLINVERSE_Items_ID_CA;
		strItemName = "CA相间";
		break;
	case VOLINVERSE_FAULT_TYPE_ABC:
		strItemID = STT_MULTI_MACRO_VOLINVERSE_Items_ID_ABC;
		strItemName = "三相短路";
		break;
	case VOLINVERSE_FAULT_TYPE_3U0:
		strItemID = STT_MULTI_MACRO_VOLINVERSE_Items_ID_3U0;
		strItemName = "3U0";
		break;
	case VOLINVERSE_FAULT_TYPE_U2:
		strItemID = STT_MULTI_MACRO_VOLINVERSE_Items_ID_U2;
		strItemName = "U2";
		break;
	
	default:
		strItemID = STT_MULTI_MACRO_VOLINVERSE_Items_ID_AE;
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

void QSttMultiMacroParaEditViewVolInverseTime::slot_AddOneItemBtnClick()
{
	GetMacroTestDatasToeCharacters(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, ((QVolInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
	QSttMultiMacroParaEditViewBase::slot_AddOneItemBtnClick();
}

void QSttMultiMacroParaEditViewVolInverseTime::slot_AddMultiItemBtnClick()
{
	QVolInverAddMultDlg oVolInverAddMultDlg;
	//oVolInverAddMultDlg.setFont(*g_pSttGlobalFont);
	//CDataGroup *pTestMacroUI_Paras = GetAddMultItems_Paras();
	//CDataGroup *pCurrTestMacroUI_Paras  = (CDataGroup*)pTestMacroUI_Paras->Clone();
	///*	CDataGroup *pPara = oDistanceAddMultDlg.GetDisTanceParas();*/
	//oVolInverAddMultDlg.SetDatas(pCurrTestMacroUI_Paras);

	GetMacroTestDataToParas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, ((QVolInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
	oVolInverAddMultDlg.SetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);

	if(oVolInverAddMultDlg.exec() == QDialog::Accepted)
	{
        //zhouhj备注,此处逻辑是有问题的,在点击确认时，就应该把对应的数据存入链表，此处不需要再调用GetDatas
		oVolInverAddMultDlg.GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
		GetMacroTestDatasToeCharacters(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, ((QVolInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
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
	return;
	//delete pCurrTestMacroUI_Paras;
}

void QSttMultiMacroParaEditViewVolInverseTime::GetMacroTestDataToParas(CDataGroup *pParas, CExBaseList* pInnerTestmacro)
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

void QSttMultiMacroParaEditViewVolInverseTime::CheckAllPresence(CExBaseList *pParas)
{
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_PreFaultTime);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_UPre);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_IPre);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_PreAngle);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_NORMHZ);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_CTPos);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultTime);
	
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_AndOr);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_A);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_B);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_C);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_D);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_E);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_F);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_G);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID_H);

	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B01);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B02);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B03);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B04);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B05);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B06);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B07);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B08);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B1);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B2);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B3);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B4);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B5);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B6);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B7);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_PARAS_ID__B8);

	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_VP);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_D);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_K);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_A);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_B);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_C);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_E);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_P);
	//VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_M);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_DownU);
	VoltInverseCheckExist(pParas, STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_OverU);

	return;
}

void QSttMultiMacroParaEditViewVolInverseTime::VoltInverseCheckExist(CExBaseList *pParas, CString strID)
{
	if (pParas == NULL)
		return;

	CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pParas->FindByID(strID);
	if (pData == NULL)
	{
		CSttMacroTestParaData *pNew = new CSttMacroTestParaData();
		pNew->m_strName = STT_MULTI_MACRO_VolInverTime_PARAS_ID_DEFAULT;
		pNew->m_strID = strID;
		pNew->m_strValue = STT_MULTI_MACRO_VolInverTime_PARAS_ID_DEFAULT;
		pParas->AddNewChild(pNew);
	}
}

void QSttMultiMacroParaEditViewVolInverseTime::SetValueToParas(CDataGroup *pParas, CSttMacroTestParaData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_PreFaultTime)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_PreFaultTime, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_UPre)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_UPre, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_IPre)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_IPre, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_PreAngle)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_PreAngle, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_NORMHZ)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_NORMHZ, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CTPos)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_CTPos, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultTime)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_FaultTime, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_CTPos)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_CTPos, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_FaultTime)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_FaultTime, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_A)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_A, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_B)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_C)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_C, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_D)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_D, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_E)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_E, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_F)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_F, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_G)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_G, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_H)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_H, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B01)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B01, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B02)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B02, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B03)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B03, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B04)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B04, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B05)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B05, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B06)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B06, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B07)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B07, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B08)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B08, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B1)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B1, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B2)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B2, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B3)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B3, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B4)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B4, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B5)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B5, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B6)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B6, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B7)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B7, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID__B8)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_B8, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_PARAS_ID_AndOr)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_PARAS_ADDMULT_ID_ANDOR, pData->m_strValue, true);
	}

	return;
}

void QSttMultiMacroParaEditViewVolInverseTime::slot_CommonParasBtnClick()
{
	QVolInverseCommonParasDlg oVolInverseCommonParasDlg;
	oVolInverseCommonParasDlg.SetDatas(((QVolInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());

	if(oVolInverseCommonParasDlg.exec() == QDialog::Accepted)
	{
		CExBaseList *pItem = ((QVolInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
		if (pItem == NULL)
		{
			pItem = ((QVolInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
		}
		if (oVolInverseCommonParasDlg.CheckItemsModify(pItem))
	{
			oVolInverseCommonParasDlg.GetDatas(((QVolInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
		//通用参数修改后，修改表格中所有项数据通用参数
		oVolInverseCommonParasDlg.UpdataAllCommonParas(&m_oSingleMacroItemsRef);
		Ats_UpdateMacroTestItems();
	}
	}
}

void QSttMultiMacroParaEditViewVolInverseTime::slot_BinarysBtnClick()
{
	QVolInverBinarysDlg oVolInverBinarysDlg;
	oVolInverBinarysDlg.SetDatas(((QVolInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());

	if(oVolInverBinarysDlg.exec()  == QDialog::Accepted)
	{
		CExBaseList *pItem = ((QVolInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
		if (pItem == NULL)
		{
			pItem = ((QVolInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
	}
		if (oVolInverBinarysDlg.CheckItemsModify(pItem))
	{
			oVolInverBinarysDlg.GetDatas(((QVolInverTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
		oVolInverBinarysDlg.UpdataAllBinarys(&m_oSingleMacroItemsRef);
		Ats_UpdateMacroTestItems();
	}
	}
}

void QSttMultiMacroParaEditViewVolInverseTime::InitAddMultiItemSelectDlg(QPoint pos,int nDlgState)
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

void QSttMultiMacroParaEditViewVolInverseTime::slot_DeleteItemBtnClick()
{
	InitAddMultiItemSelectDlg(m_pDeleteItemBtn->pos(),DELETEITEM_DLG);
}

void QSttMultiMacroParaEditViewVolInverseTime::slot_DeleteSelItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteSelItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewVolInverseTime::slot_DeleteAllItemBtnClick()
{
	//QSttMultiMacroParaEditViewBase::slot_DeleteAllItemBtnClick();
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

void QSttMultiMacroParaEditViewVolInverseTime::slot_ClearResultBtnClick()
{
	InitAddMultiItemSelectDlg(m_pClearResultBtn->pos(),CLEARSELRESULT);
}

void QSttMultiMacroParaEditViewVolInverseTime::slot_ClearSelResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearSelResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewVolInverseTime::slot_ClearAllResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearAllResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewVolInverseTime::slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest)
{
	QSttMultiMacroParaEditViewBase::slot_ParaEditWidget_To_Grid(pMacroTest);
}

//添加测试项时,在特性曲线界面添加对应测试点
//BOOL QSttMultiMacroParaEditViewVolInverseTime::AddTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest)
//{
//	if (m_pCharactInterface == NULL)
//	{
//		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
//	}
//	//添加测试点
//	CSttMacroTest *pNewTest = (CSttMacroTest *)m_pCurrMacroItemsRef->GetTail();
//	CSttMacroTestParaDatas *pNewDataParas = pNewTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
//	CSttMacroTestParaData *pData_X = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_VOLTAGE);//I*
//	CSttMacroTestParaData *pData_Y = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_TSETTING);//t
//	CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTTYPE);//故障类型
//	m_pCharactInterface->AddUpdateTestPoint_Imp(pNewTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), pData_X->m_strValue.toDouble(), pData_Y->m_strValue.toDouble(), pData_Fault->m_strValue.toInt(), NULL);
//	return TRUE;
//}

BOOL QSttMultiMacroParaEditViewVolInverseTime::DeleteTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest)
{
	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}
	m_pCharactInterface->DeleteTestData(pCurrMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE));
	m_bCharTestObjectHasChanged = TRUE;
	return TRUE;
}

BOOL QSttMultiMacroParaEditViewVolInverseTime::AddUpdateTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest, int nState)
{
	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}

	CSttMacroTestParaDatas *pDataParas = pCurrMacroTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	CSttMacroTestParaData *pData_X = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_VOLTAGE);//I*
	CSttMacroTestParaData *pData_Y = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_TSETTING);//t
	CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTTYPE);//故障类型
	m_pCharactInterface->AddUpdateTestPoint_Imp(pCurrMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), pData_X->m_strValue.toDouble(), pData_Y->m_strValue.toDouble(), pData_Fault->m_strValue.toInt(), NULL, nState);
	m_bCharTestObjectHasChanged = TRUE;
	return TRUE;
}

BOOL QSttMultiMacroParaEditViewVolInverseTime::AddItem_From_Charact(double dX, double dY)
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

	////根据坐标生成新建测试项阻抗定值、时间定值、R、X
	//CSttMacroTest *pNewTest = (CSttMacroTest *)m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.Clone();
	//CSttMacroTestParaDatas *pNewDataParas = pNewTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	//CSttMacroTestParaData *pData_X = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_VOLTAGE);//I*
	//CSttMacroTestParaData *pData_Y = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_TSETTING);//t
	//pData_X->m_strValue.setNum(dX);
	//pData_Y->m_strValue.setNum(dY);
	//CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTTYPE);//故障类型

	//CSttMacroTestParaDatas *pParaDatas = pNewTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	//pParentItems->AddNewChild(pNewTest,TRUE);

	//long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AddOneMacroItem(pMacroParas,pNewTest->m_strName,pNewTest->m_strID,strItemPath,0,
	//	m_pSingleMacroRef->m_strID, STT_ORG_MACRO_VolInverseTimeTest_I);

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

	CSttMacroTestParaData *pData_X = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_VOLTAGE);//I*
	CSttMacroTestParaData *pData_Y = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_TSETTING);//t
	pData_X->m_strValue = CheckDataMinMax(strCurr, 120, 0, 3);
	pData_Y->m_strValue = CheckDataMinMax(strTSetting, 999.999, -1, 3);

	//根据编辑页面添加测试项
	slot_AddOneItemBtnClick();
	m_bCharTestObjectHasChanged = TRUE;
	return TRUE;
}

BOOL QSttMultiMacroParaEditViewVolInverseTime::UpdateCurrItem_From_Charact(double dX, double dY)
{
	return FALSE;
}

//获取最新特性曲线参数并更新到界面 20240905 gongyiping
//void QSttMultiMacroParaEditViewVolInverseTime::UpdateParasByCharEdit()
//{
//	CString strTime;
//
//	//更新特性曲线时间定值等参数到表格数据
//	POS pos = m_pCurrMacroItemsRef->GetHeadPosition();
//	while (pos != NULL)
//	{
//		CSttMacroTest *pMacroTest = (CSttMacroTest *)m_pCurrMacroItemsRef->GetNext(pos);
//		CSttMacroTestParaDatas *pDataParas = pMacroTest->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
//		CSttMacroTestParaData *pData_X = (CSttMacroTestParaData*)pDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_VOLTAGE);
//		CSttMacroTestParaData *pData_Y = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_TSETTING);
//		CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTTYPE);//故障类型
//		CCharacteristic* pCurrCharacteristic = (CCharacteristic*)stt_Frame_Characteristics()->GetAtIndex(0);
//
//		if (pCurrCharacteristic == NULL)
//		{
//			return;
//		}
//
//		CCharacterArea *pCharArea = pCurrCharacteristic->GetCharacterArea();
//
//		if (pCharArea == NULL)
//		{
//			return;
//		}
//
//		POS pos = pCharArea->GetHeadPosition();
//		
//		while (pos)
//		{
//			CCharElementUIVP *m_pCurrElementLined = (CCharElementUIVP*)pCharArea->GetNext(pos);
//			double nTime = m_pCurrElementLined->CalInverse(pData_X->m_strValue.toDouble());
//			strTime.Format(_T("%.3f"), nTime);
//			pData_Y->m_strValue = strTime;
//			m_pCharactInterface->AddUpdateTestPoint_Imp(pMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), pData_X->m_strValue.toDouble(), pData_Y->m_strValue.toDouble(), pData_Fault->m_strValue.toInt(), NULL, 0);
//		}
//	}
//	QSttMultiMacroParaEditViewBase::UpdateParasByCharEdit();
//}

//获取最新特性曲线参数并更新到界面 20241010 gongyiping
void QSttMultiMacroParaEditViewVolInverseTime::UpdateCharacteristicParas(CSttMacroTest *pMacroTest)
{//更新界面显示对应特性曲线参数
	CString strTime;

	//更新特性曲线时间定值等参数到表格数据
	POS pos = m_pCurrMacroItemsRef->GetHeadPosition();
	while (pos != NULL)
	{
		CSttMacroTest *pMacroTest = (CSttMacroTest *)m_pCurrMacroItemsRef->GetNext(pos);
		CSttMacroTestParaDatas *pDataParas = pMacroTest->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
		CSttMacroTestParaData *pData_X = (CSttMacroTestParaData*)pDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_VOLTAGE);
		CSttMacroTestParaData *pData_Y = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_TSETTING);
		CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_VolInverTime_PARAS_ID_FAULTTYPE);//故障类型
		CCharacteristic* pCurrCharacteristic = (CCharacteristic*)stt_Frame_Characteristics()->GetAtIndex(0);

		if (pCurrCharacteristic == NULL)
		{
			return;
		}

		CCharacterArea *pCharArea = pCurrCharacteristic->GetCharacterArea();

		if (pCharArea == NULL)
		{
			return;
		}

		POS pos = pCharArea->GetHeadPosition();
		if (m_pCharactInterface == NULL)
		{
			return;
		}
		while (pos)
		{
			CCharElementUIVP *m_pCurrElementLined = (CCharElementUIVP*)pCharArea->GetNext(pos);
			double nTime = m_pCurrElementLined->CalInverse(pData_X->m_strValue.toDouble());
			strTime.Format(_T("%.3f"), nTime);
			pData_Y->m_strValue = strTime;
			m_pCharactInterface->AddUpdateTestPoint_Imp(pMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), pData_X->m_strValue.toDouble(), pData_Y->m_strValue.toDouble(), pData_Fault->m_strValue.toInt(), NULL, 0);
		}
	}
}

void QSttMultiMacroParaEditViewVolInverseTime::GetMacroTestDatasToeCharacters(CDataGroup *pParas, CExBaseList* pInnerTestmacro)
{
	if (pParas == NULL || pInnerTestmacro == NULL)
		return;

	CheckAllPresence(pInnerTestmacro);

	POS pos = pInnerTestmacro->GetHeadPosition();
	while (pos != NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pInnerTestmacro->GetNext(pos);
		SetValueToParas(pParas, pData);
		GetMacroTestDataToeCharacter(pParas,pData);
	}

	return;
}
void QSttMultiMacroParaEditViewVolInverseTime::GetMacroTestDataToeCharacter(CDataGroup *pParas, CSttMacroTestParaData* pData)
{
	CCharacteristic* pCurrCharacteristic = (CCharacteristic*)stt_Frame_Characteristics()->GetAtIndex(0);

	if (pCurrCharacteristic == NULL)
	{
		return;
	}

	CCharacterArea *pCharArea = pCurrCharacteristic->GetCharacterArea();

	if (pCharArea == NULL)
	{
		return;
	}

	POS pos = pCharArea->GetHeadPosition();

	while (pos)
	{

		CCharElementUIVP *m_pElementLined = (CCharElementUIVP*)pCharArea->GetNext(pos);

		if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_VP)
		{
			pData->m_strValue = m_pElementLined->m_strVp;
			pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_VP, pData->m_strValue, true);
		}
		else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_D)
		{
			pData->m_strValue = m_pElementLined->m_strD;
			pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_D, pData->m_strValue, true);
		}
		else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_K)
		{
			pData->m_strValue = m_pElementLined->m_strK;
			pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_K, pData->m_strValue, true);
		}
		else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_A)
		{
			pData->m_strValue = m_pElementLined->m_strA;
			pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_A, pData->m_strValue, true);
		}
		else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_B)
		{
			pData->m_strValue = m_pElementLined->m_strB;
			pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_B, pData->m_strValue, true);
		}
		else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_C)
		{
			pData->m_strValue = m_pElementLined->m_strC;
			pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_C, pData->m_strValue, true);
		}
		else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_E)
		{
			pData->m_strValue = m_pElementLined->m_strE;
			pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_E, pData->m_strValue, true);
		}
		else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_P)
		{
			pData->m_strValue = m_pElementLined->m_strP;
			pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_P, pData->m_strValue, true);
		}
		else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_DownU)
		{
			if (m_pElementLined->m_nUType == 0)
			{
				pData->m_strValue.setNum(1);
			}
			else
			{
				pData->m_strValue.setNum(0);
			}
			pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_DownU, pData->m_strValue, true);
		}
		else if (pData->m_strID == STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_OverU)
		{
			if (m_pElementLined->m_nUType == 0)
			{
				pData->m_strValue.setNum(0);
			}
			else
			{
				pData->m_strValue.setNum(1);
			}
			pParas->SetDataValue(STT_MULTI_MACRO_VolInverTime_CHARACTER_ID_OverU, pData->m_strValue, true);
		}
	}
	return;
}


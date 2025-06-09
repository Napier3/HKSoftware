#include "CharEditMainWidget.h"
#include <QComboBox>
#include "../../../../../Module/DataMngr/DvmDataset.h"
#include "../../../../../Module/DataMngr/DataGroup.h"
//#include "../../../SttTest/Common/tmt_test_mngr.h"
#include "../../../../../AutoTest/Module/Characteristic/CharElementMho.h"
#include "../ZKCharaCurve/QZKFeatureAddDig.h"
#include "../../SttTestCntrFrameAPI.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../SttTestCtrl/SttTestAppBase.h"
#include "QCharInverseSet.h"
#include "../ZKCharaCurve/QCharElementDlg.h"
#include "../../../XLangResource_Native.h"
#include "CharEditWidget_None.h"
#include "CharEditWidget_Distance.h"
#include "CharEditWidget_Inverse.h"
#include "CharEditWidget_Diff.h"
//#include "CharEditWidget_Syn.h"

//2022-12-02 修改功能ID，导致所有的都要编译，效率低下，所以从头文件中去掉，在任何需要包含的地方进行包含
#include "../../SttTestCntrCmdDefine.h" 

QCharEditMainWidget::QCharEditMainWidget(QWidget* pParent) : QWidget(pParent)
{
	ui.setupUi(this);

//	m_pCurrCharaObj = NULL;
//	m_pInterface = 0;
//	m_pCharArea = 0;
//	m_pInterfacebak = 0;
//	m_pCharAreabak = 0;
	m_bSetting = TRUE;
//	m_nZKCurrentRow = 0;
	m_pImpCharactWidget = NULL;
	m_pCharacteristicsLib = NULL;
	m_pCharEditWidget = NULL;
	m_bCharChanged = FALSE;

	InitUI();
	InitConnect();
}

QCharEditMainWidget::~QCharEditMainWidget()
{
// 	if(m_pInterfacebak)
// 	{
// 		delete m_pInterfacebak;
// 		m_pInterfacebak = NULL;
// 	}

// 	if(m_pCharAreabak)
// 	{
// 		delete m_pCharAreabak;
// 		m_pCharAreabak = NULL;
// 	}
}

void QCharEditMainWidget::InitConnect()
{
	connect(m_pImpCharactWidget, SIGNAL(sig_UpdatePointLocation(float ,float)), this, SLOT(slot_ParaPointChange(float ,float)));
	connect(m_pImpCharactWidget, SIGNAL(sig_AddPointLocation(float ,float)), this, SLOT(slot_ParaAddPoint(float ,float)));
	connect(m_pImpCharactWidget, SIGNAL(sig_LeftButtonDown()), this, SLOT(slot_LeftButtonDown()));
}

void QCharEditMainWidget::InitUI()
{
	CXDrawElement:: m_crPickColor = RGB(127, 255, 0);//2023.6.1 zhouhj 设置当前选择线条的颜色
	CreateCharEditWidgetUI_ID("");
	InitCharactWidget();
}

// void QCharEditMainWidget::slot_CharChanged()
// {
// 	m_bCharChanged = TRUE;
// }

void QCharEditMainWidget::slot_UpdateDrawCharacters(CExBaseObject *pCharacteristic,int bCharChanged)
{
	if (m_pImpCharactWidget != NULL)
	{
		m_bCharChanged = bCharChanged;
		m_pImpCharactWidget->SetViewTestLines(IsViewTestLines());
		m_pImpCharactWidget->slot_UpdateDrawCharacters(pCharacteristic);
	}
}


void QCharEditMainWidget::slot_UpdateDrawCharacters(CExBaseObject *pCharacteristic)
{
	if (m_pImpCharactWidget != NULL)
	{
		m_bCharChanged = TRUE;
		m_pImpCharactWidget->SetViewTestLines(IsViewTestLines());
		m_pImpCharactWidget->slot_UpdateDrawCharacters(pCharacteristic);
	}
}


void QCharEditMainWidget::slot_LeftButtonDown()
{
    if(m_pCharEditWidget)
    {
	m_pCharEditWidget->OnLeftButtonDown();
    }
}

void QCharEditMainWidget::InitCharactWidget()
{
	if (m_strUI_ID == STT_ORG_MACRO_CurrInverseTimeTest||(m_strUI_ID == STT_ORG_MACRO_CurrInverseTimeTest_I))
	{
		m_pImpCharactWidget = new QImpCharactWidget(NULL,this,true,true);
		m_pImpCharactWidget->setObjectName(QString::fromUtf8("QInverseCharactWidget"));
		m_pImpCharactWidget->SetAxisName(_T("I/In"),_T("t(s)"),_T("I* - t"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
		m_pImpCharactWidget->EnableSetting(false);
		m_pImpCharactWidget->IsHaveAddAct();
	}
	else if (m_strUI_ID == STT_ORG_MACRO_VolInverseTimeTest||(m_strUI_ID == STT_ORG_MACRO_VolInverseTimeTest_I))
	{
		m_pImpCharactWidget = new QImpCharactWidget(NULL, this, true, true);
		m_pImpCharactWidget->setObjectName(QString::fromUtf8("QInverseCharactWidget"));
		m_pImpCharactWidget->SetAxisName(_T("U(V)"),_T("t(s)"),_T("U - t"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
		m_pImpCharactWidget->EnableSetting(false);
		m_pImpCharactWidget->IsHaveAddAct();
	}
	else if (m_strUI_ID == STT_ORG_MACRO_UFInverseTimeTest)
	{
		m_pImpCharactWidget = new QImpCharactWidget(NULL, this, true, true);
		m_pImpCharactWidget->setObjectName(QString::fromUtf8("QInverseCharactWidget"));
		m_pImpCharactWidget->SetAxisName(_T("U*/F*"),_T("t(s)"),_T("U*/F* - t"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
		m_pImpCharactWidget->EnableSetting(false);
		m_pImpCharactWidget->IsHaveAddAct();
	}
	else if ((m_strUI_ID == STT_ORG_MACRO_DiffCurr6ITest)||(m_strUI_ID == STT_ORG_MACRO_LineDiffCurr6ITest)
		||(m_strUI_ID == STT_ORG_MACRO_BusDiffCurr6ITest)||(m_strUI_ID == STT_ORG_MACRO_ElecRailwayDiffTest)
		|| (m_strUI_ID == STT_ORG_MACRO_DiffTest_I))
	{
		m_pImpCharactWidget = new QImpCharactWidget(NULL, this, false, true);
		m_pImpCharactWidget->setObjectName(QString::fromUtf8("QDiffCurr6ICharactWidget"));
		m_pImpCharactWidget->SetAxisName(_T("Ir(A)"),_T("Id(A)"),_T(" "));
		m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T("A"),_T("A"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
		m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowAng(false);
		m_pImpCharactWidget->EnableSetting(false);
	}
	else
	{
		m_pImpCharactWidget = new QImpCharactWidget(NULL, this, true, true);
		m_pImpCharactWidget->setObjectName(QString::fromUtf8("QImpCharactWidget"));
		m_pImpCharactWidget->SetAxisName(_T("R"),_T("X"),_T("R-X(omg)"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowAng(true);
		m_pImpCharactWidget->EnableSetting(true);
	}

	ui.m_wgtCharLib->insertTab(-1, m_pImpCharactWidget, "ImpCharactWidget");
	ui.m_wgtCharLib->findChildren<QTabBar*>().at(0)->hide();
}

void QCharEditMainWidget::UpdateAxisDesc(const CString &strXAxisName, const CString &strYAxisName, 
					const CString &strAxisTitle,CString strUniuX,CString strUnitY)
{
	if (m_pImpCharactWidget != NULL)
	{
		m_pImpCharactWidget->SetAxisName(strXAxisName,strYAxisName,strAxisTitle);
		m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(strUniuX,strUnitY);
	}
}

CXDrawList* QCharEditMainWidget::GetDrawListByID(const CString& strID)
{
	CExBaseObject *pCurrObj = stt_Frame_Characteristics()->FindByID(strID);

	if (pCurrObj == NULL)
	{
		return NULL;
	}

	if (pCurrObj->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
	{
		return NULL;
	}

	CCharacteristic* pCChar = (CCharacteristic*)pCurrObj;

 //   CCharacteristic* pCChar = (CCharacteristic*)stt_Frame_Characteristics()->FindByID(strID);
	CCharacterArea* pArea = pCChar->GetCharacterArea();
	CXDrawList* pList = (CXDrawList*)pArea->GetDrawListRef();
	return pList;
}

// void QCharEditMainWidget::DrawSearchPointLine(CPoint ptBegin, CPoint ptEnd, const CString& strCharLib)
// {
// 	if(m_strLastCharaID.GetLength() && m_strLastCharaID != strCharLib)
// 	{
// 		//如果正在测试的特性曲线进行了切换
// 		CXDrawList* pList = GetDrawListByID(m_strLastCharaID);
// 		POS pos = pList->GetHeadPosition();
// 		CXDrawLine* pCurLine = NULL;
// 		while (pos)
// 		{
// 			CXDrawBase* pBase = (CXDrawBase*)pList->GetNext(pos);
// 			if(pBase->GetClassID() != DWCLASSID_CXDRAWLINE)
// 			{
// 				continue;
// 			}
// 			CXDrawLine* pLine = (CXDrawLine*)pBase;
// 			pLine->m_crForeColor = RGB(0, 255, 0);
// 		}
// 	}
// 
// 	CXDrawList* pList = GetDrawListByID(strCharLib);
// 	POS pos = pList->GetHeadPosition();
// 	CXDrawLine* pCurLine = NULL;
// 	while (pos)
// 	{
// 		CXDrawBase* pBase = (CXDrawBase*)pList->GetNext(pos);
// 
// 		if(pBase->GetClassID() != DWCLASSID_CXDRAWLINE)
// 		{
// 			continue;
// 		}
// 
// 		CXDrawLine* pLine = (CXDrawLine*)pBase;
// 		//查找报文对应的线段
// 		if(pLine->m_fXb == ptBegin.x
// 			&& pLine->m_fYb == ptBegin.y
// 			&& pLine->m_fXe == ptEnd.x
// 			&& pLine->m_fYe == ptEnd.y)
// 		{
// 			pCurLine = pLine;
// 		}
// 		pLine->m_crForeColor = RGB(0, 255, 0);
// 	}
// 	pCurLine->m_crForeColor = RGB(255,255,0);
// }
// 
// void QCharEditMainWidget::DrawSearchPointPoint(CPoint ptCur, const CString& strCharLib)
// {
// 	if(m_strLastCharaID.GetLength() && m_strLastCharaID != strCharLib)
// 	{
// 		//如果正在测试的特性曲线进行了切换
// 		CXDrawList* pList = GetDrawListByID(m_strLastCharaID);
// 		CXDrawPoint* pt = (CXDrawPoint*)pList->FindByID("CurSearchPoint");
// 		pt->m_dwDrawStyle = 8;
// 		pt->m_strID = "";//将临时点转换为固定点
// 	}
// 
// 	CXDrawList* pList = GetDrawListByID(strCharLib);
// 	CXDrawPoint* pBase = (CXDrawPoint*)pList->FindByID("CurSearchPoint");
// 	if(pBase)
// 	{
// 		pList->DeleteByID("CurSearchPoint");
// 	}
// 
// 	CXDrawPoint* pt = pList->AddPoint(ptCur.x, ptCur.y);
// 	pt->m_strID = "CurSearchPoint";
// 	pt->m_crForeColor = RGB(255, 0, 0);
// 	pt->m_dwDrawStyle = 12;
// }

void QCharEditMainWidget::InitCharacteristicsLib(const CString &strUI_ID,const CString &strCharLibFile)
{
	if (strCharLibFile.GetLength() == 0)
	{
		if (m_pCharacteristicsLib != NULL)
		{
			delete m_pCharacteristicsLib;
			m_pCharacteristicsLib = NULL;
		}
	}
	else
	{
		CString strFile;
		strFile = _P_GetConfigPath();
		strFile += strCharLibFile;

		if (m_pCharacteristicsLib == NULL)
		{
			m_pCharacteristicsLib = new CCharacteristicLib();
		}
		else
		{
			m_pCharacteristicsLib->DeleteAll();
		}

		m_pCharacteristicsLib->OpenXmlFile(strFile, CCharacteristicXmlRWKeys::CCharacteristicLibKey(),CCharacteristicXmlRWKeys::g_pXmlKeys);
	}

	CreateCharEditWidgetUI_ID(strUI_ID);
}

void QCharEditMainWidget::RemoveCurrWidget()
{
	if (m_pCharEditWidget != NULL)
	{
		ui.m_layoutLeft->removeWidget(m_pCharEditWidget->m_pCharEditWidget);
		//delete widget的时候已经同时析构base和qwidget
		//如果调用DeleteCharEditWidget则会先析构widget
		//然后又在delete this的时候重复析构widget
		delete m_pCharEditWidget;
		m_pCharEditWidget = NULL;
	}
}

void QCharEditMainWidget::CreateCharEditWidgetUI_ID(const CString &strUI_ID)
{
	if (strUI_ID.IsEmpty())
	{
		RemoveCurrWidget();
		m_strUI_ID = strUI_ID;
		m_pCharEditWidget = new QCharEditWidget_None(this);
		ui.m_layoutLeft->addWidget(m_pCharEditWidget->m_pCharEditWidget);
		return;
	}

	if (strUI_ID == m_strUI_ID)
	{
		return;
	}

	m_strUI_ID = strUI_ID;
	RemoveCurrWidget();


    if (m_strUI_ID == STT_ORG_MACRO_DistanceSearchTest || m_strUI_ID == STT_ORG_MACRO_DistanceSearchTest_I)
	{
		m_pCharEditWidget = new QCharEditWidget_DistanceSearch(this);
	}
	else if ((m_strUI_ID == STT_ORG_MACRO_DistanceTest) || (m_strUI_ID == STT_ORG_MACRO_CBOperateTest) || (m_strUI_ID == STT_ORG_MACRO_DistanceTest_I))
	{
		m_pCharEditWidget = new QCharEditWidget_DistanceSearch(this);
	}
	else if (m_strUI_ID == STT_ORG_MACRO_DistSearchOneTest)
	{
		m_pCharEditWidget = new QCharEditWidget_DistSearchOne(this);
	}
	else if ((m_strUI_ID == STT_ORG_MACRO_CurrInverseTimeTest)
		||(m_strUI_ID == STT_ORG_MACRO_VolInverseTimeTest)
		||(m_strUI_ID == STT_ORG_MACRO_UFInverseTimeTest)
		|| (m_strUI_ID == STT_ORG_MACRO_CurrInverseTimeTest_I)
		||(m_strUI_ID == STT_ORG_MACRO_VolInverseTimeTest_I))
	{
		m_pCharEditWidget = new QCharEditWidget_Inverse(this);
	}
	else if ((m_strUI_ID == STT_ORG_MACRO_DiffCurr6ITest) /*|| (m_strUI_ID == STT_ORG_MACRO_DiffTest_I)*/)
	{
		m_pCharEditWidget = new QCharEditWidget_Diff(this);
	}
	else if (m_strUI_ID == STT_ORG_MACRO_ElecRailwayDiffTest)
	{
		m_pCharEditWidget = new QCharEditWidget_ElecRailwayDiff(this);//20230718-wxy-牵引变差动
	}
	else if (m_strUI_ID == STT_ORG_MACRO_LineDiffCurr6ITest)
	{
		m_pCharEditWidget = new QCharEditWidget_LineDiff(TRUE,this);
	}
	else if (m_strUI_ID == STT_ORG_MACRO_BusDiffCurr6ITest)
	{
		m_pCharEditWidget = new QCharEditWidget_LineDiff(FALSE,this);
	}
// 	else if (m_strUI_ID == "syn")
// 	{
// 		m_pCharEditWidget = new QCharEditWidget_Syn(this);
// 	}
	
	if (m_pCharEditWidget != NULL)
	{
		ui.m_layoutLeft->addWidget(m_pCharEditWidget->m_pCharEditWidget);
	}
}

BOOL QCharEditMainWidget::IsViewTestLines()
{
	if (m_strUI_ID == STT_ORG_MACRO_DistanceTest)
	{
		return FALSE;
	}

	if (m_strUI_ID == STT_ORG_MACRO_DistanceTest_I)
	{
		return FALSE;
	}

    if (m_strUI_ID == STT_ORG_MACRO_DistanceSearchTest_I)
    {
        return FALSE;
    }

	return TRUE;
}

void QCharEditMainWidget::UI_SetActiveElement(CXDrawElement *pElement)
{
	if (m_pImpCharactWidget == NULL)
	{
		return;
	}

	m_pImpCharactWidget->UI_SetActiveElement(pElement);
}

void QCharEditMainWidget::ShowCharacteristics(CCharacteristics *pCharacteristics)
{
//	m_pCurrCharaObj = NULL;

	if (m_pCharEditWidget)
	{
		m_pCharEditWidget->UpdateCharacters(FALSE);
	}
}

CString QCharEditMainWidget::GetCharLibID()
{
	if (m_pCharacteristicsLib == NULL)
	{
		return _T("none");
	}

	return m_pCharacteristicsLib->m_strID;
}

void QCharEditMainWidget::UpdateCharAxisType(const CString& strAxis,BOOL bLockXY)
{
	m_pImpCharactWidget->m_pCharacterDrawView->UpdateAxisType(strAxis,bLockXY);
}

void QCharEditMainWidget::UpdateCharScriptByUIParas(CDataGroup *pCurrentUIParas)
{
	if (m_pCharEditWidget == NULL)
	{
		return;
	}

	m_pCharEditWidget->UpdateCharScriptByUIParas(pCurrentUIParas);
}

void QCharEditMainWidget::AddTestResultPoint(CExBaseList* pValue)
{
	CDvmValues* pValues = (CDvmValues*)pValue;
	CDvmValue* pX = NULL;
	CDvmValue* pY = NULL;
	BOOL bHasAct = FALSE;

	CString strCharID;

	if (m_pImpCharactWidget->m_pCharacteristic != NULL)
	{
		strCharID = m_pImpCharactWidget->m_pCharacteristic->m_strID;
	}

	if ((m_strUI_ID == STT_ORG_MACRO_DiffCurr6ITest)||(m_strUI_ID == STT_ORG_MACRO_LineDiffCurr6ITest)
		||(m_strUI_ID == STT_ORG_MACRO_BusDiffCurr6ITest)||(m_strUI_ID == STT_ORG_MACRO_ElecRailwayDiffTest))
	{
		if ((strCharID != _T("PsuDiffHarmTest"))&&(strCharID != _T("ElecRailwayDiffHarmTest")))
		{
		pX = (CDvmValue*)pValues->FindByID("TripIr");
		pY = (CDvmValue*)pValues->FindByID("TripId");


			if ((pY != NULL)&&(pY->m_strValue != /*_T("未动作")*/g_sLangTxt_State_NoActioned))//lcq
		{
			bHasAct = TRUE;
		}
		else
		{
			pY = (CDvmValue*)pValues->FindByID("IdSetting");
		}
		} 
		else
		{
			pX = (CDvmValue*)pValues->FindByID("TripRHarm");
			pY = (CDvmValue*)pValues->FindByID("Id");

			if ((pX != NULL)&&(pX->m_strValue != /*_T("未动作")*/g_sLangTxt_State_NoActioned))//lcq
			{
				bHasAct = TRUE;
			}
			else
			{
				pX = (CDvmValue*)pValues->FindByID("RateHarmSet");
			}
		}
 		

	}
	else if ((m_strUI_ID == STT_ORG_MACRO_DistanceSearchTest)||
		(m_strUI_ID == STT_ORG_MACRO_DistSearchOneTest))
	{
		pX = (CDvmValue*)pValues->FindByID("TripZ");
		pY = (CDvmValue*)pValues->FindByID("TripZAngle");

		if ((pX != NULL)&&(pX->m_strValue != _T("未动作")))
		{
			bHasAct = TRUE;
		}
		else
		{
			pX = (CDvmValue*)pValues->FindByID("ValSetting");
			pY = (CDvmValue*)pValues->FindByID("ValSettingAngle");
		}
	}
	else if (m_strUI_ID == STT_ORG_MACRO_CurrInverseTimeTest||
		(m_strUI_ID == STT_ORG_MACRO_CurrInverseTimeTest_I))
	{
		pX = (CDvmValue*)pValues->FindByID("FaultCurrent");
		pY = (CDvmValue*)pValues->FindByID("TripTime");

		if ((pY != NULL)&&(pY->m_strValue != _T("未动作")))
		{
			bHasAct = TRUE;
		}
		else
		{
			pY = (CDvmValue*)pValues->FindByID("SettingTime");
		}
	}
	else if (m_strUI_ID == STT_ORG_MACRO_UFInverseTimeTest)
	{
		pX = (CDvmValue*)pValues->FindByID("VolFreqRate");
		pY = (CDvmValue*)pValues->FindByID("TripTime");

		if ((pY != NULL)&&(pY->m_strValue != _T("未动作")))
		{
			bHasAct = TRUE;
		}
		else
		{
			pY = (CDvmValue*)pValues->FindByID("SettingTime");
		}
	}
	else if (m_strUI_ID == STT_ORG_MACRO_VolInverseTimeTest||m_strUI_ID == STT_ORG_MACRO_VolInverseTimeTest_I)
	{
		pX = (CDvmValue*)pValues->FindByID("FaultVolt");
		pY = (CDvmValue*)pValues->FindByID("TripTime");

		if ((pY != NULL)&&(pY->m_strValue != _T("未动作")))
		{
			bHasAct = TRUE;
		}
		else
		{
			pY = (CDvmValue*)pValues->FindByID("MaxFaultTime");
		}
	}
	

	if(pX && pY)
	{
		double dX = CString_To_double(pX->m_strValue);
		double dY = CString_To_double(pY->m_strValue);

// 		if (m_strLastCharLibID == "distance")
// 		{
// 			double dX_New = dX*cos(dY*3.1415926/180.0);
// 			double dY_New = dX*sin(dY*3.1415926/180.0);
// 			dX = dX_New;
// 			dY = dY_New;
// 		}

		if ((m_strUI_ID == STT_ORG_MACRO_DistanceSearchTest)||
			(m_strUI_ID == STT_ORG_MACRO_DistSearchOneTest))
		{
			double dX_New = dX*cos(dY*3.1415926/180.0);
			double dY_New = dX*sin(dY*3.1415926/180.0);
			dX = dX_New;
			dY = dY_New;
		}
		else if ((strCharID == _T("PsuDiffHarmTest"))||(strCharID == _T("ElecRailwayDiffHarmTest")))
		{
			dX *= 100;
			//dX_set *= 100;
		}


		m_pImpCharactWidget->m_pCharacterDrawView->AddTestResultPoint(dX, dY,bHasAct);
        stt_Frame_AddTestPoints(dX, dY,bHasAct);
	}
}

void QCharEditMainWidget::GroupDatasToChar(CDataGroup *pDatas)
{
	if (m_pCharEditWidget == NULL)
	{
		return;
	}

	m_pCharEditWidget->GroupDatasToChar(pDatas);
}

void QCharEditMainWidget::CharToGroupDatas(CDataGroup *pDatas)
{
	if (m_pCharEditWidget == NULL)
	{
		return;
	}

	m_pCharEditWidget->CharToGroupDatas(pDatas);
}

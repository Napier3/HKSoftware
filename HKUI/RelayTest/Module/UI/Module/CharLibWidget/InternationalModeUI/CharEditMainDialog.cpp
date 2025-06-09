#include "CharEditMainDialog.h"
#include <QComboBox>
#include "../../../../../../Module/DataMngr/DvmDataset.h"
#include "../../../../../../Module/DataMngr/DataGroup.h"
#include "../../../../../../AutoTest/Module/Characteristic/CharElementMho.h"
#include "../../ZKCharaCurve/QZKFeatureAddDig.h"
#include "../../../SttTestCntrFrameAPI.h"
#include "../../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../SttTestCtrl/SttTestAppBase.h"
#include "../QCharInverseSet.h"
#include "../../ZKCharaCurve/QCharElementDlg.h"
#include "../../../../XLangResource_Native.h"
#include "../CharEditWidget_None.h"
#include "CharEditWidget_Distance_Eng.h"
#include "CharEditWidget_Inverse_Eng.h"
#include "CharEditWidget_Diff_Eng.h"
#include "../CharEditWidget_Inverse.h"
#include "../CharEditWidget_Diff.h"
//#include "../CharEditWidget_Syn.h"

//2022-12-02 修改功能ID，导致所有的都要编译，效率低下，所以从头文件中去掉，在任何需要包含的地方进行包含
#include "../../../SttTestCntrCmdDefine.h"

QCharEditMainDialog::QCharEditMainDialog(QWidget* pParent) : QDialog(pParent)
{
	m_bSetting = TRUE;
	m_pImpCharactWidget = NULL;
//	m_pCharacteristicsLib = NULL;
	m_pCharEditWidget = NULL;
	m_bCharChanged = FALSE;
	m_pCharEditMain_VBoxLayout = NULL;
	m_pCharEdit_GridLayout = NULL;
	m_pCharEditBottom_HLayout = NULL;
	m_pCharacteristics_Exter = NULL;
	m_pCharacteristics_Inner = NULL;

	m_pCharEditMain_VBoxLayout = new QVBoxLayout(this);
	m_pCharEdit_GridLayout = new QGridLayout(this);
	m_pCharEditBottom_HLayout = new QHBoxLayout(this);
	m_pCharEditMain_VBoxLayout->addLayout(m_pCharEdit_GridLayout);
	m_pCharEditMain_VBoxLayout->addLayout(m_pCharEditBottom_HLayout);
	m_pOk_Button = new QPushButton(g_sLangTxt_OK, this);
	m_pCancel_Button = new QPushButton(g_sLangTxt_Cancel,this);
	m_pCharEditBottom_HLayout->addStretch();
	m_pCharEditBottom_HLayout->addWidget(m_pOk_Button);
	m_pCharEditBottom_HLayout->addWidget(m_pCancel_Button);
	m_pCharEditBottom_HLayout->addStretch();
	setLayout(m_pCharEditMain_VBoxLayout);
	setWindowTitle(g_sLangTxt_Win_CharEditTabTitle);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

// 	InitUI();
// 	InitConnect();
	resize(1024, 900);
}

QCharEditMainDialog::~QCharEditMainDialog()
{
	if (m_pCharacteristics_Inner != NULL)
	{
		delete m_pCharacteristics_Inner;
		m_pCharacteristics_Inner = NULL;
	}
}

void QCharEditMainDialog::InitConnect()
{
	connect(m_pImpCharactWidget, SIGNAL(sig_UpdatePointLocation(float ,float)), this, SLOT(slot_ParaPointChange(float ,float)));
	connect(m_pImpCharactWidget, SIGNAL(sig_AddPointLocation(float ,float)), this, SLOT(slot_ParaAddPoint(float ,float)));
	connect(m_pImpCharactWidget, SIGNAL(sig_LeftButtonDown()), this, SLOT(slot_LeftButtonDown()));
	connect(m_pOk_Button, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_Button, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

// void QCharEditMainDialog::InitUI()
// {
// 	CXDrawElement:: m_crPickColor = RGB(127, 255, 0);//2023.6.1 zhouhj 设置当前选择线条的颜色
// 	CreateCharEditWidgetUI_ID("");
// 	InitCharactWidget();
// }

void QCharEditMainDialog::slot_UpdateDrawCharacters(CExBaseObject *pCharacteristic, int bCharChanged)
{
	if (m_pImpCharactWidget != NULL)
	{
		m_bCharChanged = bCharChanged;
		m_pImpCharactWidget->SetViewTestLines(IsViewTestLines());
        //20241017 wanmj 先创建计算和创建绘图元素才可以获取和曲线的交点，计算相对误差
		m_pCharacteristics_Inner->CalCharElement(NULL);
        m_pImpCharactWidget->m_pCharacterDrawView->XCreateElement(m_pCharacteristics_Inner, NULL, FALSE, FALSE);
		m_pImpCharactWidget->slot_UpdateDrawCharacters(pCharacteristic);
	}
}


void QCharEditMainDialog::slot_UpdateDrawCharacters(CExBaseObject *pCharacteristic)
{
	if (m_pImpCharactWidget != NULL)
	{
		m_bCharChanged = TRUE;
		m_pImpCharactWidget->SetViewTestLines(IsViewTestLines());
        //20241017 wanmj 先创建m_listCharElement链表里的元素才可以获取和曲线的交点，计算相对误差
		m_pCharacteristics_Inner->CalCharElement(NULL);
        m_pImpCharactWidget->m_pCharacterDrawView->XCreateElement(m_pCharacteristics_Inner, NULL, FALSE, FALSE);
		m_pImpCharactWidget->slot_UpdateDrawCharacters(pCharacteristic);
	}
}

void QCharEditMainDialog::slot_LeftButtonDown()
{
    //2024-26 wuxinyi 添加判断条件
    if(m_pCharEditWidget)
    {
		m_pCharEditWidget->OnLeftButtonDown();
    }
}

void QCharEditMainDialog::slot_OKClicked()
{
	//20240819 luozibing 特性曲线编辑中的参数id改为TestMacro.xml文件id,不区分区段，因此不需要对检查id对应区段
 //   if(m_strUI_ID == STT_ORG_MACRO_DistanceTest_I || m_strUI_ID == STT_ORG_MACRO_DistanceSearchTest_I)
//	{
//		//将页面设置数据更新到内部特性曲线数据
//		((QCharEditWidget_DistanceSearch_Eng *)m_pCharEditWidget)->CheckZoneParas();
//	}
	if (m_strUI_ID == STT_ORG_MACRO_CurrInverseTimeTest_I || m_strUI_ID == STT_ORG_MACRO_VolInverseTimeTest_I)
	{
		((QCharEditWidget_Inverse_Eng *)m_pCharEditWidget)->UpDataParas();
	}
	else if (m_strUI_ID == STT_ORG_MACRO_DiffTest_I)
	{
		((QCharEditWidget_Diff_Eng *)m_pCharEditWidget)->UpDataParas();
	}

	//20240815 luozibing 点击确定时将内部特性曲线数据更新到外部
	m_pCharacteristics_Exter->DeleteAll();
	m_pCharacteristics_Exter->AppendClone(m_pCharacteristics_Inner);

    //20240830 wanmj CCharacteristics克隆后需要初始化
    m_pCharacteristics_Exter->InitAfterRead();
    m_pCharacteristics_Exter->SetIsShowErrorBand(TRUE);
	
	accept();
}
void QCharEditMainDialog::slot_CancelClicked()
{
	close();
}

void QCharEditMainDialog::InitCharactWidget()
{
	if ((m_strUI_ID == STT_ORG_MACRO_CurrInverseTimeTest_I))
	{
		m_pImpCharactWidget = new QCharactEditWidget_Eng(m_pCharacteristics_Inner, this, true, true);
		m_pImpCharactWidget->setObjectName(QString::fromUtf8("QInverseCharactWidget"));
		m_pImpCharactWidget->SetAxisName(_T("I/In"),_T("t(s)"),_T("I* - t"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
		m_pImpCharactWidget->EnableSetting(false);
		m_pImpCharactWidget->IsHaveAddAct();
	}
	else if ((m_strUI_ID == STT_ORG_MACRO_VolInverseTimeTest_I))
	{
		m_pImpCharactWidget = new QCharactEditWidget_Eng(m_pCharacteristics_Inner, this, true, true);
		m_pImpCharactWidget->setObjectName(QString::fromUtf8("QInverseCharactWidget"));
		m_pImpCharactWidget->SetAxisName(_T("U(V)"),_T("t(s)"),_T("U - t"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
		m_pImpCharactWidget->EnableSetting(false);
		m_pImpCharactWidget->IsHaveAddAct();
	}
	else if ((m_strUI_ID == STT_ORG_MACRO_DiffTest_I))
	{
		m_pImpCharactWidget = new QCharactEditWidget_Eng(m_pCharacteristics_Inner, this, false, true);
		m_pImpCharactWidget->setObjectName(QString::fromUtf8("QDiffICharactWidget"));
		m_pImpCharactWidget->SetAxisName(_T("Ir(A)"), _T("Id(A)"), /*比例制动边界搜索*/g_sLangTxt_Diff_BorderSearch);
		m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T("A"),_T("A"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
		m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowAng(false);
		m_pImpCharactWidget->EnableSetting(false);
	}
    else if (m_strUI_ID == STT_ORG_MACRO_DistanceTest_I || m_strUI_ID == STT_ORG_MACRO_DistanceSearchTest_I)
    {//20240809 luozibing 克隆唯一变量并传入坐标轴
//		CCharacteristics *pCharacteristics_Inner = (CCharacteristics *)stt_Frame_Characteristics()->Clone();
		m_pImpCharactWidget = new QCharactEditWidget_Eng(m_pCharacteristics_Inner, this, true, true);
        m_pImpCharactWidget->setObjectName(QString::fromUtf8("QInternationalCharactWidget"));
        m_pImpCharactWidget->SetAxisName(_T("R/Ω"),_T("X/Ω"),g_sLangTxt_Distance_ImpActBorder/*("阻抗动作边界")*/);
        m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowAng(true);
		 m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
        m_pImpCharactWidget->EnableSetting(true);
    }
	else
	{
        m_pImpCharactWidget = new QCharactEditWidget_Eng(NULL,this,true,true);
		m_pImpCharactWidget->setObjectName(QString::fromUtf8("QImpCharactWidget"));
		m_pImpCharactWidget->SetAxisName(_T("R"),_T("X"),_T("R-X(omg)"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowAng(true);
		m_pImpCharactWidget->EnableSetting(true);
	}
	
	QTabWidget *pTabWidget = new QTabWidget(this);
	m_pCharEdit_GridLayout->addWidget(pTabWidget, 0, 1);
	pTabWidget->insertTab(-1, m_pImpCharactWidget, "ImpCharactWidget");
	pTabWidget->findChildren<QTabBar*>().at(0)->hide();
}

void QCharEditMainDialog::UpdateAxisDesc(const CString &strXAxisName, const CString &strYAxisName,
					const CString &strAxisTitle,CString strUniuX,CString strUnitY)
{
	if (m_pImpCharactWidget != NULL)
	{
		m_pImpCharactWidget->SetAxisName(strXAxisName,strYAxisName,strAxisTitle);
		m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(strUniuX,strUnitY);
	}
}

CXDrawList* QCharEditMainDialog::GetDrawListByID(const CString& strID)
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
	CCharacterArea* pArea = pCChar->GetCharacterArea();
	CXDrawList* pList = (CXDrawList*)pArea->GetDrawListRef();
	return pList;
}

void QCharEditMainDialog::InitCharacteristics(CCharacteristics *pCharacteristics, CDataGroup *pParaDatas, const CString &strUI_ID)
{
	CXDrawElement::m_crPickColor = RGB(127, 255, 0);//2023.6.1 zhouhj 设置当前选择线条的颜色
//	m_oCharEditCharacteristicsLib.DeleteAll();

// 	if (strCharLibFile.GetLength() > 0)
// 	{
// 		CString strFile;
// 		strFile = _P_GetConfigPath();
// 		strFile += strCharLibFile;
// 		m_oCharEditCharacteristicsLib.OpenXmlFile(strFile, CCharacteristicXmlRWKeys::CCharacteristicLibKey(), CCharacteristicXmlRWKeys::g_pXmlKeys);
// 	}
	m_pCharacteristics_Exter = pCharacteristics;

	if (m_pCharacteristics_Inner != NULL)
	{
		delete m_pCharacteristics_Inner;
		m_pCharacteristics_Inner = NULL;
	}

	m_pCharacteristics_Inner = (CCharacteristics*)m_pCharacteristics_Exter->Clone();
    m_pCharacteristics_Inner->InitAfterRead();  //20240830 wanmj
	m_strUI_ID = strUI_ID;
	InitCharactWidget();
	CreateCharEditWidgetUI_ID();

	GroupDatasToChar(pParaDatas);
	ShowCharacteristics(pCharacteristics);
	InitConnect();

// 	if (strUI_ID == STT_ORG_MACRO_DistanceTest_I)
// 	{
// 		 InitCharactWidget();
// 	}
}

void QCharEditMainDialog::RemoveCurrWidget()
{
	if (m_pCharEditWidget != NULL)
	{
		m_pCharEdit_GridLayout->removeWidget(m_pCharEditWidget->m_pCharEditWidget);
		//delete widget的时候已经同时析构base和qwidget
		//如果调用DeleteCharEditWidget则会先析构widget
		//然后又在delete this的时候重复析构widget
		delete m_pCharEditWidget;
		m_pCharEditWidget = NULL;
	}
}

void QCharEditMainDialog::CreateCharEditWidgetUI_ID()
{
	if (m_strUI_ID.IsEmpty())
	{
		m_pCharEditWidget = new QCharEditWidget_None(this);
		m_pCharEdit_GridLayout->addWidget(m_pCharEditWidget->m_pCharEditWidget, 0, 0);
		return;
	}

	if (m_strUI_ID == STT_ORG_MACRO_DistanceSearchTest_I)
	{
		m_pCharEditWidget = new QCharEditWidget_DistanceSearch_Eng(this);
        ((QCharEditWidget_DistanceSearch_Eng*)m_pCharEditWidget)->m_strUI_ID = STT_ORG_MACRO_DistanceSearchTest_I;
	}
	else if (m_strUI_ID == STT_ORG_MACRO_DistanceTest_I)
	{
		m_pCharEditWidget = new QCharEditWidget_DistanceSearch_Eng(this);
        ((QCharEditWidget_DistanceSearch_Eng*)m_pCharEditWidget)->m_strUI_ID = STT_ORG_MACRO_DistanceTest_I;
    }
	else if ((m_strUI_ID == STT_ORG_MACRO_VolInverseTimeTest_I)
		|| (m_strUI_ID == STT_ORG_MACRO_CurrInverseTimeTest_I))
	{
		m_pCharEditWidget = new QCharEditWidget_Inverse_Eng(this);
	}
	else if (m_strUI_ID == STT_ORG_MACRO_DiffTest_I)
	{
		m_pCharEditWidget = new QCharEditWidget_Diff_Eng(this);
		m_pImportChar_Button = new QPushButton(CString("导入特性曲线"), this);
		m_pCharEditBottom_HLayout->insertWidget(0,m_pImportChar_Button);
		connect(m_pImportChar_Button, SIGNAL(clicked()), this, SLOT(slot_ImportCharClicked()));
	}
	
// 	else if (m_strUI_ID == STT_ORG_MACRO_DiffCurr6ITest)
// 	{
// 		m_pCharEditWidget = new QCharEditWidget_Diff(this);
// 	}
	
	if (m_pCharEditWidget != NULL)
	{
		m_pCharEdit_GridLayout->addWidget(m_pCharEditWidget->m_pCharEditWidget, 0, 0);
	}
}

BOOL QCharEditMainDialog::IsViewTestLines()
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

	//20240813 zhangyq 曲线编辑不显示测试点
	if (m_strUI_ID == STT_ORG_MACRO_CurrInverseTimeTest_I || m_strUI_ID == STT_ORG_MACRO_VolInverseTimeTest_I)
	{
		return FALSE;
	}
	//add wangtao 20240929 差动曲线编辑不显示测试线
	if (m_strUI_ID == STT_ORG_MACRO_DiffTest_I)
	{
		return FALSE;
	}


	return TRUE;
}

void QCharEditMainDialog::UI_SetActiveElement(CXDrawElement *pElement)
{
	if (m_pImpCharactWidget == NULL)
	{
		return;
	}

	m_pImpCharactWidget->UI_SetActiveElement(pElement);
}

void QCharEditMainDialog::ShowCharacteristics(CCharacteristics *pCharacteristics)
{
	if (m_pCharEditWidget)
	{
		m_pCharEditWidget->UpdateCharacters(FALSE);
	}
}

// CString QCharEditMainDialog::GetCharLibID()
// {
// // 	if (m_pCharEditCharacteristicsLib == NULL)
// // 	{
// // 		return _T("none");
// // 	}
// 
// 	return m_oCharEditCharacteristicsLib.m_strID;
// }

void QCharEditMainDialog::UpdateCharAxisType(const CString& strAxis, BOOL bLockXY)
{
	if (m_pImpCharactWidget != NULL)
	{
		m_pImpCharactWidget->m_pCharacterDrawView->UpdateAxisType(strAxis,bLockXY);
	}
}

void QCharEditMainDialog::UpdateCharScriptByUIParas(CDataGroup *pCurrentUIParas)
{
	if (m_pCharEditWidget == NULL)
	{
		return;
	}

	m_pCharEditWidget->UpdateCharScriptByUIParas(pCurrentUIParas);
}

void QCharEditMainDialog::GroupDatasToChar(CDataGroup *pDatas)//将模板视图数据赋值给特性曲线界面
{
	if (m_pCharEditWidget == NULL)
	{
		return;
	}

	m_pCharEditWidget->GroupDatasToChar(pDatas);
}

void QCharEditMainDialog::CharToGroupDatas(CDataGroup *pDatas)//将特性曲线界面参数数据赋值给模板视图数据
{
	if (m_pCharEditWidget == NULL)
	{
		return;
	}

	m_pCharEditWidget->CharToGroupDatas(pDatas);
}
CCharacteristics *QCharEditMainDialog::GetCharacteristics_Inner()
{//20240815 luozibing 获取内部对象指针
	return m_pCharacteristics_Inner;
}
void QCharEditMainDialog::slot_ImportCharClicked()
{
	if (m_pCharEditWidget == NULL)
	{
		return;
	}

	((QCharEditWidget_Diff_Eng*)m_pCharEditWidget)->ImportChar();
}
#include "SttIecSysCfgChildWidget.h"
#include <QHeaderView>
//#include "../SttTestCntrFrameBase.h"
#include "../../SttSystemConfig/SttSystemConfig.h"
#include "../../SttTestSysGlobalPara.h"


QSttIecSysCfgChildWidget::QSttIecSysCfgChildWidget(QFont oIecFont,long nSysParaType,QWidget *parent)
	: QWidget(parent)
{
	m_pMain_HBoxLayout = NULL;
	m_oIecFont = oIecFont;
	setFont(m_oIecFont);
	m_nSysParaType = nSysParaType;
	InitUI();
}

QSttIecSysCfgChildWidget::~QSttIecSysCfgChildWidget()
{
	m_oLeftList.RemoveAll();
	m_oRightList.RemoveAll();
}

void QSttIecSysCfgChildWidget::InitUI()
{
	m_pMain_HBoxLayout = new QHBoxLayout(this);
//	CString strModel;
//	strModel = g_oSttSystemConfig.GetDevModel();

	if ((m_nSysParaType == STT_IECSYS_WIDGET_TYPE_SmvOutRate)||
		(m_nSysParaType == STT_IECSYS_WIDGET_TYPE_SmvInRate))
	{
		m_pLeft_SysCfgChildGrid = new CIecCfgPrimRateGrid(IECCFG_PRIMRATE_GRIDTYPE_PT,this);
		m_pRight_SysCfgChildGrid = new CIecCfgPrimRateGrid(IECCFG_PRIMRATE_GRIDTYPE_CT,this);
		m_pLeft_SysCfgChildGrid->horizontalHeader()->setFont(*g_pSttGlobalFont/*m_oIecFont*/); // 2022-10-22 sy m_oIecFont修改为*g_pSttGlobalFont
		m_pLeft_SysCfgChildGrid->setFont(*g_pSttGlobalFont);
		m_pRight_SysCfgChildGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		m_pRight_SysCfgChildGrid->setFont(*g_pSttGlobalFont);
		
		
		m_pLeft_SysCfgChildGrid->InitGrid();
		m_pRight_SysCfgChildGrid->InitGrid();
		m_pMain_HBoxLayout->addWidget(m_pLeft_SysCfgChildGrid);
		m_pMain_HBoxLayout->addWidget(m_pRight_SysCfgChildGrid);
	} 

	if (m_nSysParaType == STT_IECSYS_WIDGET_TYPE_FiberSet)
	{
		m_pLeft_SysCfgChildGrid = new CIecCfgFiberSetGrid(this);
		m_pRight_SysCfgChildGrid = new CIecCfgFiberSetGrid(this);
		m_pLeft_SysCfgChildGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		m_pLeft_SysCfgChildGrid->setFont(*g_pSttGlobalFont);

		m_pRight_SysCfgChildGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		m_pRight_SysCfgChildGrid->setFont(*g_pSttGlobalFont);
		//zhouhj 2023.11.25 光口最大数量根据读取的硬件信息处理
		((CIecCfgFiberSetGrid*)m_pLeft_SysCfgChildGrid)->m_nMaxFiberNum = g_oLocalSysPara.m_nTotalSTSend_Num;
		((CIecCfgFiberSetGrid*)m_pRight_SysCfgChildGrid)->m_nMaxFiberNum = g_oLocalSysPara.m_nLC_GFiberNum;

// 		//20230829 suyang 不同型号设备的ST光口与LC光口不同
// #ifdef _PSX_QT_LINUX_
// 
// 		if (strModel =="L336D")
// 		{
// 			((CIecCfgFiberSetGrid*)m_pLeft_SysCfgChildGrid)->m_nMaxFiberNum = 6;
// 			((CIecCfgFiberSetGrid*)m_pRight_SysCfgChildGrid)->m_nMaxFiberNum = 2;
// 		}
// 		else
// 		{
// 			((CIecCfgFiberSetGrid*)m_pLeft_SysCfgChildGrid)->m_nMaxFiberNum = 2;
// 			((CIecCfgFiberSetGrid*)m_pRight_SysCfgChildGrid)->m_nMaxFiberNum = 1;
// 
// 		}	
// #endif
	m_pLeft_SysCfgChildGrid->InitGrid();
	m_pRight_SysCfgChildGrid->InitGrid();
	m_pMain_HBoxLayout->addWidget(m_pLeft_SysCfgChildGrid);
	m_pMain_HBoxLayout->addWidget(m_pRight_SysCfgChildGrid);
	}

	if (m_nSysParaType == STT_IECSYS_WIDGET_TYPE_FiberInSet)
	{
		m_pLeft_SysCfgChildGrid = new CIecCfgFiberSetGrid(this);
		m_pLeft_SysCfgChildGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		m_pLeft_SysCfgChildGrid->setFont(*g_pSttGlobalFont);
		((CIecCfgFiberSetGrid*)m_pLeft_SysCfgChildGrid)->m_nLeftWidth=400;//20240103 gongyiping 由于只有一个表格，设置表格的strFiberDesc宽度为400
	m_pLeft_SysCfgChildGrid->InitGrid();
	m_pMain_HBoxLayout->addWidget(m_pLeft_SysCfgChildGrid);
	((CIecCfgFiberSetGrid*)m_pLeft_SysCfgChildGrid)->m_nMaxFiberNum = g_oLocalSysPara.m_nTotalSTRecv_Num;

//  #ifdef _PSX_QT_LINUX_
// 
// 		if (strModel =="L336D")
// 		{
// 			((CIecCfgFiberSetGrid*)m_pLeft_SysCfgChildGrid)->m_nMaxFiberNum = 6;
// 			
// 		}
// 		else
// 		{
// 			((CIecCfgFiberSetGrid*)m_pLeft_SysCfgChildGrid)->m_nMaxFiberNum = 2;
// 
// 		}
// 
//  #endif
		
	}

	setLayout(m_pMain_HBoxLayout);
}

void QSttIecSysCfgChildWidget::InitData(CIecCfgSysParas* pIecCfgSysParas)
{
	if (m_nSysParaType == STT_IECSYS_WIDGET_TYPE_SmvOutRate)
	{
		GetSmvOutRateList(pIecCfgSysParas->GetPrimRates());
	} 
	else if (m_nSysParaType == STT_IECSYS_WIDGET_TYPE_SmvInRate)
	{
		GetSmvInRateList(pIecCfgSysParas->GetPrimRatesIn());
	} 
	else if (m_nSysParaType == STT_IECSYS_WIDGET_TYPE_FiberSet)
	{
		GetFiberSetList(pIecCfgSysParas->GetFiberParas());
	} 
	else if (m_nSysParaType == STT_IECSYS_WIDGET_TYPE_FiberInSet)
	{
		GetFiberInSetList(pIecCfgSysParas->GetFiberParasIn());
		//2024/1/2 wangjunsheng 在显示表格前，先释放链表
		CIecCfgFiberSetGrid* pIecCfgFiberSetGrid =(CIecCfgFiberSetGrid*)m_pLeft_SysCfgChildGrid;
		pIecCfgFiberSetGrid->m_oFiberSetList.RemoveAll();

		/*m_pLeft_SysCfgChildGrid*/pIecCfgFiberSetGrid->ShowDatas(&m_oLeftList);
		return;
	} 

	m_pLeft_SysCfgChildGrid->ShowDatas(&m_oLeftList);
	m_pRight_SysCfgChildGrid->ShowDatas(&m_oRightList);
}

void QSttIecSysCfgChildWidget::GetSmvOutRateList(CIecCfgPrimRates* pPrimRates)
{
	m_oLeftList.RemoveAll();
	m_oRightList.RemoveAll();

	POS pos = pPrimRates->GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;

	while(pos)
	{
		pCurrObj = pPrimRates->GetNext(pos);

		if (pCurrObj->m_strID.Find("U") != -1)
		{
			m_oLeftList.AddTail(pCurrObj);
		} 
		else
		{
			m_oRightList.AddTail(pCurrObj);

		}
	}
}

void QSttIecSysCfgChildWidget::GetSmvInRateList(CIecCfgPrimRatesIn *pPrimRates)
{
	GetSmvOutRateList(pPrimRates);
}

void QSttIecSysCfgChildWidget::GetFiberSetList(CIecCfgFiberParas *pIecCfgFiberParas)
{
	m_oLeftList.RemoveAll();
	m_oRightList.RemoveAll();

	POS pos = pIecCfgFiberParas->GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;

	while(pos)
	{
		pCurrObj = pIecCfgFiberParas->GetNext(pos);

		if (pCurrObj->m_strID.Find("ST") != -1)
		{
			m_oLeftList.AddTail(pCurrObj);
		} 
		else
		{
			m_oRightList.AddTail(pCurrObj);

		}
	}
}
void QSttIecSysCfgChildWidget::GetFiberInSetList(CIecCfgFiberParasIn *pIecCfgFiberParasIn)
{
	m_oLeftList.RemoveAll();
	
	POS pos = pIecCfgFiberParasIn->GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;

	while(pos)
	{
		pCurrObj = pIecCfgFiberParasIn->GetNext(pos);
		m_oLeftList.AddTail(pCurrObj);
	}
}


void QSttIecSysCfgChildWidget::SaveData()
{

}


void QSttIecSysCfgChildWidget::SetEnableState(bool bEnable)
{
	if (m_pLeft_SysCfgChildGrid != NULL)
	{
		m_pLeft_SysCfgChildGrid->setEnabled(bEnable);
	}

	if (m_pRight_SysCfgChildGrid != NULL)
	{
		m_pRight_SysCfgChildGrid->setEnabled(bEnable);
	}

	setEnabled(bEnable);
}
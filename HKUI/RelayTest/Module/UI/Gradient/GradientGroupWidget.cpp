#include "GradientGroupWidget.h"
#include <QGridLayout>
#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../Module/SttUIDefine.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/XLangResource_Native.h"
#include <QHeaderView>

QGradientGroupWidget::QGradientGroupWidget(QWidget* pParent)
{
	setParent(pParent);
	m_pCurGrid = NULL;
	m_pVoltGrid = NULL;
}

QGradientGroupWidget::~QGradientGroupWidget()
{

}

void QGradientGroupWidget::SetEnabledUI(BOOL bEnable)
{
	m_pVoltGrid->setEnabled(bEnable);
	m_pCurGrid->setEnabled(bEnable);
	m_pFaultVoltGrid->setEnabled(bEnable);
	m_pFaultCurGrid->setEnabled(bEnable);
}

void QGradientGroupWidget::Init(tmt_GradientParasEx* pGradientParas)
{
	InitUI();
	InitData(pGradientParas);
}

void QGradientGroupWidget::InitData( tmt_GradientParasEx* pGradientParas )
{
	POS pos = g_oSttTestResourceMngr.m_oChMaps.GetHeadPosition();
	long nVoltIndex = 0;
	long nCurIndex = 0;

	//wangtao 20240625 清理之前的通道，防止通道重复增加
	if (m_oNormalVoltList.GetCount() != 0)
	{
		m_oNormalVoltList.DeleteAll();
	}

	if (m_oNormalCurList.GetCount() != 0)
	{
		m_oNormalCurList.DeleteAll();
	}

	if (m_oFaultVoltList.GetCount() != 0)
	{
		m_oFaultVoltList.DeleteAll();
	}

	if (m_oFaultCurList.GetCount() != 0)
	{
		m_oFaultCurList.DeleteAll();
	}
    //end
	while (pos)
	{
		CSttChMap* pCh = (CSttChMap*)g_oSttTestResourceMngr.m_oChMaps.GetNext(pos);
		if(pCh->m_strName.indexOf("U") != -1)
		{
			QGradientGroupData* pData = new QGradientGroupData;
			pData->m_pfAmp = &pGradientParas->m_uiVOL[0][nVoltIndex].Harm[1].fAmp;
			pData->m_pfAngle = &pGradientParas->m_uiVOL[0][nVoltIndex].Harm[1].fAngle;
			pData->m_pfFreq = &pGradientParas->m_uiVOL[0][nVoltIndex].Harm[1].fFreq;
			pData->m_strName = pCh->m_strName;
			m_oNormalVoltList.AddNewChild(pData);

			pData = new QGradientGroupData;
			pData->m_pfAmp = &pGradientParas->m_uiVOL[2][nVoltIndex].Harm[1].fAmp;
			pData->m_pfAngle = &pGradientParas->m_uiVOL[2][nVoltIndex].Harm[1].fAngle;
			pData->m_pfFreq = &pGradientParas->m_uiVOL[2][nVoltIndex].Harm[1].fFreq;
			pData->m_fDefaultAmp = pGradientParas->m_uiVOL[2][nVoltIndex].Harm[1].fAmp;
			pData->m_fDefaultAngle = pGradientParas->m_uiVOL[2][nVoltIndex].Harm[1].fAngle;
			pData->m_fDefaultFreq = pGradientParas->m_uiVOL[2][nVoltIndex].Harm[1].fFreq;
			pData->m_strName = pCh->m_strName;
			m_oFaultVoltList.AddNewChild(pData);

			nVoltIndex++;
		}
		else
		{
			QGradientGroupData* pData = new QGradientGroupData;
			pData->m_pfAmp = &pGradientParas->m_uiCUR[0][nCurIndex].Harm[1].fAmp;
			pData->m_pfAngle = &pGradientParas->m_uiCUR[0][nCurIndex].Harm[1].fAngle;
			pData->m_pfFreq = &pGradientParas->m_uiCUR[0][nCurIndex].Harm[1].fFreq;
			pData->m_strName = pCh->m_strName;
			m_oNormalCurList.AddNewChild(pData);

			pData = new QGradientGroupData;
			pData->m_pfAmp = &pGradientParas->m_uiCUR[2][nCurIndex].Harm[1].fAmp;
			pData->m_pfAngle = &pGradientParas->m_uiCUR[2][nCurIndex].Harm[1].fAngle;
			pData->m_pfFreq = &pGradientParas->m_uiCUR[2][nCurIndex].Harm[1].fFreq;
			pData->m_fDefaultAmp = pGradientParas->m_uiCUR[2][nVoltIndex].Harm[1].fAmp;
			pData->m_fDefaultAngle = pGradientParas->m_uiCUR[2][nVoltIndex].Harm[1].fAngle;
			pData->m_fDefaultFreq = pGradientParas->m_uiCUR[2][nVoltIndex].Harm[1].fFreq;
			pData->m_strName = pCh->m_strName;
			m_oFaultCurList.AddNewChild(pData);		

			nCurIndex++;
		}

	}

	if (g_oSttTestResourceMngr.m_oChMaps.GetCount() == 0)
	{
		//20240605 suyang 通道为空，链表需要清除
		if (m_oNormalVoltList.GetCount() != 0)
		{
			m_oNormalVoltList.DeleteAll();
		}

		if (m_oNormalCurList.GetCount() != 0)
		{
			m_oNormalCurList.DeleteAll();
		}

		if (m_oFaultVoltList.GetCount() != 0)
		{
			m_oFaultVoltList.DeleteAll();
		}

		if (m_oFaultCurList.GetCount() != 0)
		{
			m_oFaultCurList.DeleteAll();
		}
	}

	
	Update();
// 	m_pVoltGrid->ShowDatas(&m_oNormalVoltList);
// 	m_pCurGrid->ShowDatas(&m_oNormalCurList);
// 	m_pFaultVoltGrid->ShowDatas(&m_oFaultVoltList);
// 	m_pFaultCurGrid->ShowDatas(&m_oFaultCurList);

	m_pVoltGrid->SetDatas(&m_oNormalVoltList);
	m_pCurGrid->SetDatas(&m_oNormalCurList);
	m_pFaultVoltGrid->SetDatas(&m_oFaultVoltList);
	m_pFaultCurGrid->SetDatas(&m_oFaultCurList);

	m_pParas = pGradientParas;
}

void QGradientGroupWidget::Update()
{
	m_pVoltGrid->ShowDatas(&m_oNormalVoltList);
	m_pCurGrid->ShowDatas(&m_oNormalCurList);
	m_pFaultVoltGrid->ShowDatas(&m_oFaultVoltList);
	m_pFaultCurGrid->ShowDatas(&m_oFaultCurList);
}

void QGradientGroupWidget::InitUI()
{
	//绑定了父窗口后的控件不需要主动析构
	QGridLayout* pLayout = new QGridLayout(this);
	setLayout(pLayout);
	QTabWidget* pTabWidget = new QTabWidget(this);
	pTabWidget->setFont(*g_pSttGlobalFont);
	pLayout->addWidget(pTabWidget);

	//添加常态tab
	//CString strTemp = "常态";
    //xlang_GetLangStrByFile(g_sLangTxt_Gradient_Normal,"Gradient_Normal");  //常态 lcq 3.20
	QWidget* pWidget = new QWidget(pTabWidget);
	//pTabWidget->addTab(pWidget, strTemp);
	pTabWidget->addTab(pWidget, g_sLangTxt_Gradient_Norm);//lcq 3.20
	m_pCurGrid = new QGradientGroupGrid(pWidget);
	m_pCurGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pCurGrid->setFont(*g_pSttGlobalFont);
	m_pCurGrid->InitGrid(Moudle_I);

	m_pVoltGrid = new QGradientGroupGrid(pWidget);
	m_pVoltGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pVoltGrid->setFont(*g_pSttGlobalFont);
	m_pVoltGrid->InitGrid(Moudle_U);
	pLayout = new QGridLayout(pWidget);
	pLayout->addWidget(m_pVoltGrid, 0, 0);
	pLayout->addWidget(m_pCurGrid, 0, 1);
	pWidget->setLayout(pLayout);

	//添加故障态tab
	//strTemp = "故障态";
	pWidget = new QWidget(pTabWidget);
	pTabWidget->addTab(pWidget, g_sLangTxt_Gradient_Failure);//lcq 3.20 //故障态
	m_pFaultVoltGrid = new QGradientGroupGrid(pWidget);
	m_pFaultVoltGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pFaultVoltGrid->setFont(*g_pSttGlobalFont);
	m_pFaultVoltGrid->InitGrid(Moudle_U);

	m_pFaultCurGrid = new QGradientGroupGrid(pWidget);
	m_pFaultCurGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pFaultCurGrid->setFont(*g_pSttGlobalFont);
	m_pFaultCurGrid->InitGrid(Moudle_I);
	pLayout = new QGridLayout(pWidget);
	pLayout->addWidget(m_pFaultVoltGrid, 0, 0);
	pLayout->addWidget(m_pFaultCurGrid, 0, 1);
	pWidget->setLayout(pLayout);
}

void QGradientGroupWidget::ClearFaultEditState(QGradientGroupGrid* pGrid)
{
	long nRows = pGrid->rowCount();
	long nCols = pGrid->columnCount();
	for (int i = 0; i < nRows; i++)
	{
		for (int n = 1; n < nCols; n++)
		{
			QTableWidgetItem* pItem = pGrid->item(i, n);
			pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
			pGrid->SetItemBkColour(i, n, qRgb(255, 255, 255));
		}
	}
}

void QGradientGroupWidget::ClearFaultEditState()
{
	ClearFaultEditState(m_pFaultVoltGrid);
	ClearFaultEditState(m_pFaultCurGrid);
}

void QGradientGroupWidget::UpdateFaultEditState(CString strName,int GradientcbbVar)
{
	CString strAllFreq;
	xlang_GetLangStrByFile(strAllFreq, "Gradient_AllFreq");
	if(strAllFreq == strName)
	{
		long nRows = m_pFaultVoltGrid->rowCount();
		for (int i = 0; i < nRows; i++)
		{
			QTableWidgetItem* pItem = m_pFaultVoltGrid->item(i, 3);
			pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable &~Qt::ItemIsEnabled &~Qt::ItemIsSelectable);
			if( GradientcbbVar == 1)
			{
			pItem->setText(QString::number(m_pParas->m_fStart,'f',3));
			}
			else
			{
				pItem->setText(QString::number(m_pParas->m_fStart2,'f',3));
			}
#ifndef _PSX_QT_LINUX_//mod wangtao 20240827 国际版要求设置为灰色的，Linux下不调用
				m_pFaultVoltGrid->SetItemBkColour(i, 3, qRgb(128, 128, 128));//dingxy 20240529 按测试要求取消灰色背景
#endif		
		}
		nRows = m_pFaultCurGrid->rowCount();
		for (int i = 0; i < nRows; i++)
		{
			QTableWidgetItem* pItem = m_pFaultCurGrid->item(i, 3);
			pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable &~Qt::ItemIsEnabled &~Qt::ItemIsSelectable);
			if( GradientcbbVar == 1)
			{
			pItem->setText(QString::number(m_pParas->m_fStart,'f',3));
			}
			else
			{
				pItem->setText(QString::number(m_pParas->m_fStart2,'f',3));
			}
#ifndef _PSX_QT_LINUX_
			m_pFaultCurGrid->SetItemBkColour(i, 3, qRgb(128, 128, 128));
#endif	
		}
	}
	else
	{
		if(GradientcbbVar == 1)
		{
		long nRow = m_pFaultVoltGrid->GetRow(0, strName);
		long nCol = m_pParas->m_nType + 1; //第一列是名称
		if(nRow == -1)
		{
			nRow = m_pFaultCurGrid->GetRow(0, strName);
				QTableWidgetItem* pItem = m_pFaultCurGrid->item(nRow, nCol);
				pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable &~Qt::ItemIsEnabled &~Qt::ItemIsSelectable);
				pItem->setText(QString::number(m_pParas->m_fStart,'f',3));
#ifndef _PSX_QT_LINUX_
				m_pFaultCurGrid->SetItemBkColour(nRow, nCol, qRgb(128, 128, 128));
#endif		
			}
			else
			{
				QTableWidgetItem* pItem = m_pFaultVoltGrid->item(nRow, nCol);
				pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable &~Qt::ItemIsEnabled &~Qt::ItemIsSelectable);
				pItem->setText(QString::number(m_pParas->m_fStart,'f',3));
#ifndef _PSX_QT_LINUX_
				m_pFaultVoltGrid->SetItemBkColour(nRow, nCol, qRgb(128, 128, 128));
#endif		
			}
			}
		else
		{
			long nRow = m_pFaultVoltGrid->GetRow(0, strName);
			long nCol = m_pParas->m_nType2 + 1; //第一列是名称
			if(nRow == -1)
			{
				nRow = m_pFaultCurGrid->GetRow(0, strName);
			QTableWidgetItem* pItem = m_pFaultCurGrid->item(nRow, nCol);
			pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable &~Qt::ItemIsEnabled &~Qt::ItemIsSelectable);
				pItem->setText(QString::number(m_pParas->m_fStart2,'f',3));
#ifndef _PSX_QT_LINUX_
				m_pFaultCurGrid->SetItemBkColour(nRow, nCol, qRgb(128, 128, 128));
#endif		
		}
		else
		{
			QTableWidgetItem* pItem = m_pFaultVoltGrid->item(nRow, nCol);
			pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable &~Qt::ItemIsEnabled &~Qt::ItemIsSelectable);
				pItem->setText(QString::number(m_pParas->m_fStart2,'f',3));
#ifndef _PSX_QT_LINUX_
				m_pFaultVoltGrid->SetItemBkColour(nRow, nCol, qRgb(128, 128, 128));
#endif		
		}
	}
	}
}

long QGradientGroupWidget::GetFaultSymIndex(CString strName)
{
	long nSym = strName.Find(",");
	if(nSym == -1)
	{
		nSym = strName.Find("+");
	}
	return nSym;
}

void QGradientGroupWidget::UpdateFaultEditState(CDataTypeValue *pCurDataTypeValue,CDataTypeValue *pCurDataTypeValue2)
{
	ClearFaultEditState();

	CString strID;
	long nSym;
	if (pCurDataTypeValue)
	{
		strID = pCurDataTypeValue->m_strID;
		nSym = GetFaultSymIndex(strID);
	while (nSym != -1)
	{
		UpdateFaultEditState(strID.Left(nSym));
		strID = strID.Mid(nSym + 1);
		nSym = GetFaultSymIndex(strID);
	}
	UpdateFaultEditState(strID);
	}
	if (pCurDataTypeValue2)
	{
		strID = pCurDataTypeValue2->m_strID;
		nSym = GetFaultSymIndex(strID);
		while (nSym != -1)
		{
			UpdateFaultEditState(strID.Left(nSym),2);
			strID = strID.Mid(nSym + 1);
			nSym = GetFaultSymIndex(strID);
		}
		UpdateFaultEditState(strID,2);
	}
}

void QGradientGroupWidget::SetDefaultFaultValue(long nIndex, bool bVolt)
{
	QGradientGroupData* pData = NULL;
	if(bVolt)
	{
		pData = (QGradientGroupData*)m_oFaultVoltList.GetAt(nIndex);
	}
	else
	{
		pData = (QGradientGroupData*)m_oFaultCurList.GetAt(nIndex);
	}
	
	if (pData == NULL)
	{
		return;
	}

	*pData->m_pfAmp = pData->m_fDefaultAmp;
	//*pData->m_pfAngle = pData->m_fDefaultAngle;
	//*pData->m_pfFreq = pData->m_fDefaultFreq;
}
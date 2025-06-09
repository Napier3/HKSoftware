#include "../Module/SttUIDefine.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../Module/XLangResource_Native.h"
#include "SequenceGradientWidget.h"
#include <QHeaderView>
#include <QGridLayout>

QSequenceGradientWidget::QSequenceGradientWidget(QWidget* pParent)
{
	setParent(pParent);
	m_pCurGrid = NULL;
	m_pVoltGrid = NULL;
}

QSequenceGradientWidget::~QSequenceGradientWidget()
{

}

void QSequenceGradientWidget::SetEnabledUI(BOOL bEnable)
{
	m_pVoltGrid->setEnabled(bEnable);
	m_pCurGrid->setEnabled(bEnable);
	m_pFaultVoltGrid->setEnabled(bEnable);
	m_pFaultCurGrid->setEnabled(bEnable);
}

void QSequenceGradientWidget::InitUI()
{
	//绑定了父窗口后的控件不需要主动析构
	QGridLayout* pLayout = new QGridLayout(this);
	setLayout(pLayout);
	QTabWidget* pTabWidget = new QTabWidget(this);
	pTabWidget->setFont(*g_pSttGlobalFont);
	pLayout->addWidget(pTabWidget);

	//添加常态tab
	QWidget* pWidget = new QWidget(pTabWidget);
	pTabWidget->addTab(pWidget, g_sLangTxt_Gradient_Normal);//lcq 3.20 正常态
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
	m_pFaultCurGrid = new QGradientGroupGrid(pWidget);
	m_pFaultCurGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pFaultCurGrid->setFont(*g_pSttGlobalFont);
	m_pFaultCurGrid->InitGrid(Moudle_I);

	m_pFaultVoltGrid = new QGradientGroupGrid(pWidget);
	m_pFaultVoltGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pFaultVoltGrid->setFont(*g_pSttGlobalFont);
	m_pFaultVoltGrid->InitGrid(Moudle_U);

	
	pLayout = new QGridLayout(pWidget);
	pLayout->addWidget(m_pFaultCurGrid, 0, 1);
	pLayout->addWidget(m_pFaultVoltGrid, 0, 0);
	pWidget->setLayout(pLayout);
	HideFreCol();
}

void QSequenceGradientWidget::Init(tmt_GradientParasEx* pGradientParas)
{
	InitUI();
	InitData(pGradientParas);
}

void QSequenceGradientWidget::InitData(tmt_GradientParasEx* pGradientParas)
{
	POS pos = g_oSttTestResourceMngr.m_oChMaps.GetHeadPosition();
	long nVoltIndex = 0;
	long nCurIndex = 0;
	CDataTypeValue *pCh = NULL;

	while (pos)
	{
		CSttChMap* pCh = (CSttChMap*)g_oSttTestResourceMngr.m_oChMaps.GetNext(pos);
		if((pCh->m_strName.indexOf("U") != -1) && (nVoltIndex < 3))
		{
			QGradientGroupData* pData = new QGradientGroupData;
			pData->m_pfAmp = &pGradientParas->m_uiVOL[0][nVoltIndex].Harm[1].fAmp;
			pData->m_pfAngle = &pGradientParas->m_uiVOL[0][nVoltIndex].Harm[1].fAngle;
			pData->m_pfFreq = &pGradientParas->m_uiVOL[0][nVoltIndex].Harm[1].fFreq;
			pData->m_strName = pCh->m_strName;
			if (nVoltIndex == 2)
			{
				pData->m_strName.Format(_T("U1-%1d"), nVoltIndex - 2);
			}
			else
			{
				pData->m_strName.Format(_T("U1-%1d"), nVoltIndex + 1);
			}
			
			m_oNormalVoltList.AddNewChild(pData);

			pData = new QGradientGroupData;
			pData->m_pfAmp = &pGradientParas->m_uiVOL[2][nVoltIndex].Harm[1].fAmp;
			pData->m_pfAngle = &pGradientParas->m_uiVOL[2][nVoltIndex].Harm[1].fAngle;
			pData->m_pfFreq = &pGradientParas->m_uiVOL[2][nVoltIndex].Harm[1].fFreq;
			pData->m_strName = pCh->m_strName;
			if (nVoltIndex == 2)
			{
				pData->m_strName.Format(_T("U1-%1d"), nVoltIndex - 2);
			}
			else
			{
				pData->m_strName.Format(_T("U1-%1d"), nVoltIndex + 1);
			}
			m_oFaultVoltList.AddNewChild(pData);

			nVoltIndex++;
			
		}
		else if ((pCh->m_strName.indexOf("I") != -1) && (nCurIndex < 3))
		{
 			QGradientGroupData* pData = new QGradientGroupData;
 			pData->m_pfAmp = &pGradientParas->m_uiCUR[0][nCurIndex].Harm[1].fAmp;
 			pData->m_pfAngle = &pGradientParas->m_uiCUR[0][nCurIndex].Harm[1].fAngle;
 			pData->m_pfFreq = &pGradientParas->m_uiCUR[0][nCurIndex].Harm[1].fFreq;
 			pData->m_strName = pCh->m_strName;
			if (nCurIndex == 2)
			{
				pData->m_strName.Format(_T("I1-%1d"), nCurIndex - 2);
			}
			else
			{
				pData->m_strName.Format(_T("I1-%1d"), nCurIndex + 1);
			}
 			m_oNormalCurList.AddNewChild(pData);

 			pData = new QGradientGroupData;
 			pData->m_pfAmp = &pGradientParas->m_uiCUR[2][nCurIndex].Harm[1].fAmp;
 			pData->m_pfAngle = &pGradientParas->m_uiCUR[2][nCurIndex].Harm[1].fAngle;
 			pData->m_pfFreq = &pGradientParas->m_uiCUR[2][nCurIndex].Harm[1].fFreq;
 			pData->m_strName = pCh->m_strName;
			if (nCurIndex == 2)
			{
				pData->m_strName.Format(_T("I1-%1d"), nCurIndex - 2);
			}
			else
			{
				pData->m_strName.Format(_T("I1-%1d"), nCurIndex + 1);
			}
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

	Update();//20240606 suyang 调用函数，不重复写

// 	m_pVoltGrid->ShowDatas(&m_oNormalVoltList);
// 	m_pFaultCurGrid->ShowDatas(&m_oFaultCurList);
// 	m_pCurGrid->ShowDatas(&m_oNormalCurList);
// 	m_pFaultVoltGrid->ShowDatas(&m_oFaultVoltList);

	m_pVoltGrid->SetDatas(&m_oNormalVoltList);
	m_pCurGrid->SetDatas(&m_oNormalCurList);
	m_pFaultVoltGrid->SetDatas(&m_oFaultVoltList);
	m_pFaultCurGrid->SetDatas(&m_oFaultCurList);

	m_pParas = pGradientParas;
}

void QSequenceGradientWidget::Update()
{
	m_pVoltGrid->ShowDatas(&m_oNormalVoltList);
	m_pCurGrid->ShowDatas(&m_oNormalCurList);
	m_pFaultVoltGrid->ShowDatas(&m_oFaultVoltList);
	m_pFaultCurGrid->ShowDatas(&m_oFaultCurList);
}

long QSequenceGradientWidget::GetFaultSymIndex(CString strName)
{
	long nSym = strName.Find(",");
	if(nSym == -1)
	{
		nSym = strName.Find("+");
	}
	return nSym;
}

void QSequenceGradientWidget::UpdateFaultEditState(CString strName)
{
	CString strAllFreq;
	xlang_GetLangStrByFile(strAllFreq, "Gradient_AllFreq");
	if(strAllFreq == strName)
	{//故障电压电流的频率
		long nRows = m_pFaultVoltGrid->rowCount();
		for (int i = 0; i < nRows; i++)
		{
			QTableWidgetItem* pItem = m_pFaultVoltGrid->item(i, 3);
			pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
			pItem->setText(QString::number(m_pParas->m_fStart,'f',3));
			//m_pFaultVoltGrid->SetItemBkColour(i, 3, qRgb(128, 128, 128));
		}
		nRows = m_pFaultCurGrid->rowCount();
		for (int i = 0; i < nRows; i++)
		{
			QTableWidgetItem* pItem = m_pFaultCurGrid->item(i, 3);
			pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
			pItem->setText(QString::number(m_pParas->m_fStart,'f',3));
			//m_pFaultCurGrid->SetItemBkColour(i, 3, qRgb(128, 128, 128));
		}
	}
	else
	{
		long nRow = m_pFaultVoltGrid->GetRow(0, strName);
		long nCol = m_pParas->m_nType + 1; //第一列是名称
		//long nCurRow = m_pFaultCurGrid->GetRow(0,strName);
		//QTableWidgetItem* pItem = m_pFaultVoltGrid->item(0, 3);
		//pItem->setText(QString::number(m_pParas->m_fStart,'f',3));
		//pItem->setText(strName);

 		if(nRow == -1)
 		{
 			nRow = m_pFaultCurGrid->GetRow(0, strName);
			if (nRow == -1) //20240606 suyang 当通道为空时防止崩溃
			{
				return;
			}
   			QTableWidgetItem* pItem = m_pFaultCurGrid->item(nRow, nCol);
   			pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
  			pItem->setText(QString::number(m_pParas->m_fStart,'f',3));
  			//m_pFaultCurGrid->SetItemBkColour(nRow, nCol, qRgb(128, 128, 128));
 		}
 		else
 		{
  			QTableWidgetItem* pItem = m_pFaultVoltGrid->item(nRow, nCol);
  			pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
  			pItem->setText(QString::number(m_pParas->m_fStart,'f',3));
  			//m_pFaultVoltGrid->SetItemBkColour(nRow, nCol, qRgb(128, 128, 128));
 		}
	}
}

void QSequenceGradientWidget::ClearFaultEditState()
{
	ClearFaultEditState(m_pFaultVoltGrid);
	ClearFaultEditState(m_pFaultCurGrid);
}

void QSequenceGradientWidget::ClearFaultEditState(QGradientGroupGrid* pGrid)
{
	long nRows = pGrid->rowCount();
	long nCols = pGrid->columnCount();
	for (int i = 0; i < nRows; i++)
	{
		for (int n = 1; n < nCols; n++)
		{
			QTableWidgetItem* pItem = pGrid->item(i, n);
			pItem->setFlags(pItem->flags() | Qt::ItemIsEditable);
			pGrid->SetItemBkColour(i, n, qRgb(255, 255, 255));
		}
	}
}

void QSequenceGradientWidget::UpdateFaultEditState(CDataTypeValue *pCurDataTypeValue)
{
	ClearFaultEditState();
	CString strID =pCurDataTypeValue->m_strID;
	long nSym = GetFaultSymIndex(strID);
	while (nSym != -1)
	{
		UpdateFaultEditState(strID.Left(nSym));
		strID = strID.Mid(nSym + 1);
		nSym = GetFaultSymIndex(strID);
	}
	UpdateFaultEditState(strID);
}

void QSequenceGradientWidget::HideFreCol()
{	
	m_pVoltGrid->setColumnHidden(3, true);
	m_pCurGrid->setColumnHidden(3, true);
	m_pFaultCurGrid->setColumnHidden(3, true);
	m_pFaultVoltGrid->setColumnHidden(3,true);
	//m_pVoltGrid->horizontalHeader()->setStretchLastSection(false);
}
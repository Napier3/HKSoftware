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
	m_bHasInitFinished = false;
	m_pCurDataTypeValue = NULL;
}

QGradientGroupWidget::~QGradientGroupWidget()
{

}

void QGradientGroupWidget::SetEnabledUI(BOOL bEnable)
{
	if (!m_bHasInitFinished)
	{
		return;
	}
	m_pVoltGrid->setEnabled(bEnable);
	m_pCurGrid->setEnabled(bEnable);
	m_pFaultVoltGrid->setEnabled(bEnable);
	m_pFaultCurGrid->setEnabled(bEnable);
}

void QGradientGroupWidget::Init(tmt_GradientParasEx* pGradientParas)
{
	//InitUI();
	InitData(pGradientParas);
}

void QGradientGroupWidget::showEvent(QShowEvent *event)
{
	if (!m_bHasInitFinished)
	{
		InitUI();
		m_bHasInitFinished = true;
		Update();
		setGridDatas();
		UpdateFaultEditState(m_pCurDataTypeValue);
	}

	QWidget::showEvent(event);
}

void QGradientGroupWidget::InitData( tmt_GradientParasEx* pGradientParas )
{
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
	POS pos = g_oSttTestResourceMngr.m_oChMaps.GetHeadPosition();
	long nVoltIndex = 0;
	long nCurIndex = 0;
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

	if(g_oSttTestResourceMngr.m_oChMaps.GetCount() == 0)
	{
		//20240605 suyang ͨ��Ϊ�գ�������Ҫ���
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
	setGridDatas();
	m_pParas = pGradientParas;
}

void QGradientGroupWidget::setGridDatas()
{
	if (m_bHasInitFinished)
	{
	m_pVoltGrid->SetDatas(&m_oNormalVoltList);
	m_pCurGrid->SetDatas(&m_oNormalCurList);
	m_pFaultVoltGrid->SetDatas(&m_oFaultVoltList);
	m_pFaultCurGrid->SetDatas(&m_oFaultCurList);
	}
}

void QGradientGroupWidget::Update()
{
	if (m_bHasInitFinished)
	{
	m_pVoltGrid->ShowDatas(&m_oNormalVoltList);
	m_pCurGrid->ShowDatas(&m_oNormalCurList);
	m_pFaultVoltGrid->ShowDatas(&m_oFaultVoltList);
	m_pFaultCurGrid->ShowDatas(&m_oFaultCurList);
	}
}

void QGradientGroupWidget::InitUI()
{
	//���˸����ں�Ŀؼ�����Ҫ��������
	QGridLayout* pLayout = new QGridLayout(this);
	setLayout(pLayout);
	QTabWidget* pTabWidget = new QTabWidget(this);
	pTabWidget->setFont(*g_pSttGlobalFont);
	pLayout->addWidget(pTabWidget);

	//��ӳ�̬tab
	//CString strTemp = "��̬";
    //xlang_GetLangStrByFile(g_sLangTxt_Gradient_Normal,"Gradient_Normal");  //��̬ lcq 3.20
	QWidget* pWidget = new QWidget(pTabWidget);
	//pTabWidget->addTab(pWidget, strTemp);
        pTabWidget->addTab(pWidget, g_sLangTxt_Gradient_Normal);//lcq 3.20
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

	//��ӹ���̬tab
	//strTemp = "����̬";
	pWidget = new QWidget(pTabWidget);
	pTabWidget->addTab(pWidget, g_sLangTxt_Gradient_Failure);//lcq 3.20 //����̬
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
			pItem->setFlags(pItem->flags() | Qt::ItemIsEditable);
			pGrid->SetItemBkColour(i, n, qRgb(255, 255, 255));
		}
	}
}

void QGradientGroupWidget::ClearFaultEditState()
{
	ClearFaultEditState(m_pFaultVoltGrid);
	ClearFaultEditState(m_pFaultCurGrid);
}

void QGradientGroupWidget::UpdateFaultEditState(CString strName)
{
	CString strAllFreq;
	xlang_GetLangStrByFile(strAllFreq, "Gradient_AllFreq");
	if(strAllFreq == strName)
	{
		long nRows = m_pFaultVoltGrid->rowCount();
		for (int i = 0; i < nRows; i++)
		{
			QTableWidgetItem* pItem = m_pFaultVoltGrid->item(i, 3);
			pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
			pItem->setText(QString::number(m_pParas->m_fStart,'f',3));
			//m_pFaultVoltGrid->SetItemBkColour(i, 3, qRgb(128, 128, 128));//dingxy 20240529 ������Ҫ��ȡ����ɫ����
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
		long nCol = m_pParas->m_nType + 1; //��һ��������
		if(nRow == -1)
		{
			nRow = m_pFaultCurGrid->GetRow(0, strName);
			if (nRow == -1) //20240605 suyang ��ͨ��Ϊ��ʱ��ֹ����
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

long QGradientGroupWidget::GetFaultSymIndex(CString strName)
{
	long nSym = strName.Find(",");
	if(nSym == -1)
	{
		nSym = strName.Find("+");
	}
	return nSym;
}

void QGradientGroupWidget::UpdateFaultEditState(CDataTypeValue *pCurDataTypeValue)
{
	if (!m_bHasInitFinished)
	{
		m_pCurDataTypeValue = new CDataTypeValue;
		pCurDataTypeValue->Copy(m_pCurDataTypeValue);
	}
	if (m_bHasInitFinished)
	{
	ClearFaultEditState();

	CString strID = pCurDataTypeValue->m_strID;
	long nSym = GetFaultSymIndex(strID);
	while (nSym != -1)
	{
		UpdateFaultEditState(strID.Left(nSym));
		strID = strID.Mid(nSym + 1);
		nSym = GetFaultSymIndex(strID);
	}
	UpdateFaultEditState(strID);
		delete m_pCurDataTypeValue;
		m_pCurDataTypeValue = NULL;
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
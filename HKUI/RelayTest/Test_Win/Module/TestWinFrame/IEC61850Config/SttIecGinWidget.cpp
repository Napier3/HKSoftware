#include <QMessageBox>
#include "SttIecGinWidget.h"
#include <QDebug>
#include <fstream>
#include <QEvent>
#include <QKeyEvent>
#include <QHeaderView>
#include "SttIecSMV92OtherSetDialog.h"
//#include "../SttTestCntrFrameBase.h"
extern QFont *g_pSttGlobalFont;

QSttIecGinWidget::QSttIecGinWidget(QFont oIecFont,QWidget *parent)
	: QSttIecConfigWidgetBase(parent)
{
	m_oIecFont = oIecFont;
	SetFont(m_oIecFont);
	InitUI();
//	m_blockTableView->installEventFilter(this);
	this->installEventFilter(this);
}

QSttIecGinWidget::~QSttIecGinWidget()
{
}

void QSttIecGinWidget::InitUI()
{
 	QSttIecConfigWidgetBase::InitUI();
 	CreateToolbar();

	m_pIecCfgDataGridBase = new CIecCfgGinDataGrid(this);

	if (g_pSttGlobalFont!= NULL)
	{
		m_pIecCfgDataGridBase->horizontalHeader()->setFont(*g_pSttGlobalFont);//2022-10-22 sy 修改为*g_pSttGlobalFont
		m_pIecCfgDataGridBase->setFont(*g_pSttGlobalFont);
	}

	m_pIecCfgDataGridBase->InitGrid();

 	m_pMainVLayout = new QVBoxLayout;
 	setLayout(m_pMainVLayout);
	m_pMainVLayout->addWidget(m_pIecCfgDataGridBase);
	m_pClear_PushButton = new QPushButton("清除绑定");
	m_pCtrlBlocksSetHLayout->addWidget(m_pClear_PushButton);
	m_pMainVLayout->addLayout(m_pCtrlBlocksSetHLayout);

	connect(m_pClear_PushButton,SIGNAL(clicked()),SLOT(slot_ClearClicked()));
}

void QSttIecGinWidget::CreateToolbar()
{
}

void QSttIecGinWidget::InitData(CIecCfgDatasBase* pIecCfgDatasBase)
{
	ASSERT(pIecCfgDatasBase);
	QSttIecConfigWidgetBase::InitData(pIecCfgDatasBase);
	CIecCfgGinDatas* pIecCfgGinDatas = (CIecCfgGinDatas*)pIecCfgDatasBase;
}

void QSttIecGinWidget::SaveData()
{
	CIecCfgGinDatas* pIecCfgGinDatas = (CIecCfgGinDatas*)m_pIecCfgDatasBase;
}

void QSttIecGinWidget::UpdateAppMaps()
 {
	 if(m_pIecCfgDatasBase == NULL)
		 return;

	 ((CIecCfgGinDatas*)m_pIecCfgDatasBase)->InitGinAppChMaps();
 }


bool QSttIecGinWidget::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress) 
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

		if (keyEvent->key() == Qt::Key_Down) 
		{	
		}
		else if (keyEvent->key() == Qt::Key_Up)
		{
		}
		else if (keyEvent->key() == Qt::Key_Escape)
		{
			//SaveBlockModel();
			return true;
		}

		return false;
	}else{
		return false;
	}
}

void QSttIecGinWidget::slot_ClearClicked()
{
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)m_pIecCfgDataGridBase->GetCurrSelData();

	if (pIecCfgData == NULL)
	{
		return;
	}

	if (pIecCfgData->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
	{
		if(!pIecCfgData->m_pCfgChs->GetCount())
		{
			return;
		}
		CIecCfgGinCh *pIecCfgGinCh = NULL;
		POS pos = pIecCfgData->m_pCfgChs->GetHeadPosition();

		while(pos)
		{
			pIecCfgGinCh = (CIecCfgGinCh *)pIecCfgData->m_pCfgChs->GetNext(pos);

			CIecCfgGinDatas *pIecCfgGinDatas = (CIecCfgGinDatas*)pIecCfgGinCh->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);
			CIecCfgGinAppChMaps* pIecCfgGinAppChMaps = pIecCfgGinDatas->GetIecCfgGinAppChMaps();
			CIecCfgGinAppChMap* pIecCfgGinAppChMap = NULL;

			long nIndex = pIecCfgGinCh->m_strAppChID.Find(_T(";"));
			CString strID = _T("");
			if (nIndex >0 )
			{
				strID = pIecCfgGinCh->m_strAppChID.left(nIndex);
			}

			pIecCfgGinAppChMap = (CIecCfgGinAppChMap*)pIecCfgGinAppChMaps->FindByID(strID);

			if (pIecCfgGinAppChMap !=NULL)
			{
				pIecCfgGinAppChMap->m_pIecCfgGinCh =NULL;
		}

			pIecCfgGinCh->m_strAppChID = "none";
		}

			
		
		emit sig_UpdateCB_ChDatas(pIecCfgData);//更新控制块通道数据	
	}

}

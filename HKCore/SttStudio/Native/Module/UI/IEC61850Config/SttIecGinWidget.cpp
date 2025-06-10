#include <QMessageBox>
#include "SttIecGinWidget.h"
#include <QDebug>
#include <fstream>
#include <QEvent>
#include <QKeyEvent>
#include <QHeaderView>
#include "SttIecSMV92OtherSetDialog.h"
//#include "../SttTestCntrFrameBase.h"

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
	m_pIecCfgDataGridBase->horizontalHeader()->setFont(*g_pSttGlobalFont);//2022-10-22 sy ÐÞ¸ÄÎª*g_pSttGlobalFont
	m_pIecCfgDataGridBase->setFont(*g_pSttGlobalFont);

	m_pIecCfgDataGridBase->InitGrid();

 	m_pMainVLayout = new QVBoxLayout;
 	setLayout(m_pMainVLayout);
	m_pMainVLayout->addWidget(m_pIecCfgDataGridBase);
	m_pMainVLayout->addLayout(m_pCtrlBlocksSetHLayout);
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

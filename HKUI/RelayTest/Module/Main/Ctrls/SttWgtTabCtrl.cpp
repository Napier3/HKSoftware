#include "SttWgtTabCtrl.h"
#include "../SttXuiData/SttXuiDataTabs.h"
#include "../Module/SttWgtFactory.h"
#include "SttWgtButtonGroup.h"
#include "SttWgtText.h"
#include "../SttXuiData/SttXuiDataFileMngrGrid.h"
#include "SttWgtFileMngrGrid.h"
#include "../../UI/SCL/QSttSelSclFileWidget.h"

QSttWgtTabCtrl::QSttWgtTabCtrl(QWidget* pParent)
{
	m_pParent = pParent;
	setParent(pParent);
}

QSttWgtTabCtrl::~QSttWgtTabCtrl()
{

}

void QSttWgtTabCtrl::InitUIOwn(CExBaseObject *pSttXuiData)
{
	if(pSttXuiData)
	{
		CSttXuiDataTabs* pData = (CSttXuiDataTabs*)pSttXuiData;
		setGeometry(pData->m_nX*g_dUIShowCoef, pData->m_nY*g_dUIShowCoef, pData->m_nCx*g_dUIShowCoef, pData->m_nCy*g_dUIShowCoef);
		setObjectName(pData->m_strID);
		QSttWgtStyle* pStyle = GetWgtStyle(WGT_TYPE_FONT, pData->m_strFont);
		SetWgtStyle(this, pStyle);
	}
}

void QSttWgtTabCtrl::InitUIChildren(CExBaseObject *pSttXuiData)
{
	if(pSttXuiData)
	{
		CSttXuiDataBase* pData = (CSttXuiDataBase*)pSttXuiData;
		POS pos = pData->GetHeadPosition();

		while(pos)
		{
			CSttXuiDataBase* pNode = (CSttXuiDataBase*)pData->GetNext(pos);
			QSttWgtFactory::CreateSttWgt(pNode, this);
		}
	}
}

QSttWgtTab::QSttWgtTab(QWidget* pParent)
{
	m_pParent = pParent;
}

QSttWgtTab::~QSttWgtTab()
{

}

void QSttWgtTab::InitUIOwn(CExBaseObject *pSttXuiData)
{
	if(pSttXuiData)
	{
		CSttXuiDataTab* pData = (CSttXuiDataTab*)pSttXuiData;
		long nCount = ((QSttWgtTabCtrl*)m_pParent)->count();
		((QSttWgtTabCtrl*)m_pParent)->insertTab(nCount, this, pData->m_strName);
		//设置样式
//#ifdef _PSX_QT_LINUX_
		QSttWgtStyle* pStyle = GetWgtStyle(WGT_TYPE_FONT, pData->m_strFont);
		SetWgtStyle(this, pStyle);
//#endif
	}
}

void QSttWgtTab::InitUIChildren(CExBaseObject *pSttXuiData)
{
	if(pSttXuiData)
	{
		if (pSttXuiData->m_strID == _T("SelSCLFile"))
		{
//#ifdef _PSX_QT_LINUX_
			*g_pSttGlobalFont = this->font();
//#endif
			QSttSelSclFileWidget *pQSttSelSclFileWidget = new QSttSelSclFileWidget(this);

			if (g_pSttGlobalFont != NULL)
			{
				pQSttSelSclFileWidget->setFont(*g_pSttGlobalFont);
			}

			pQSttSelSclFileWidget->InitUI();
			g_pSttSelSclFileWidget = pQSttSelSclFileWidget;
			AddWidgetChild(pQSttSelSclFileWidget);
		}
		else
		{
			CSttXuiDataBase* pData = (CSttXuiDataBase*)pSttXuiData;
			CSttXuiDataBase* pNode = NULL;
			POS pos = pData->GetHeadPosition();

			while(pos)
			{
				pNode = (CSttXuiDataBase*)pData->GetNext(pos);
				QSttWgtFactory::CreateSttWgt(pNode, this);
			}
		}
	}
}

void QSttWgtTab::AddWidgetChild(QWidget *pChildWidget)
{
	QVBoxLayout *pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(pChildWidget);
	setLayout(pVBoxLayout);
}
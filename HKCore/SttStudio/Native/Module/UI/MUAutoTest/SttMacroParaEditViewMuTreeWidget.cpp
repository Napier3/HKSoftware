#include "SttMacroParaEditViewMuTreeWidget.h"


QSttMacroParaEditViewMuTreeWidget::QSttMacroParaEditViewMuTreeWidget()
{	
	m_pAutomatedTestItem = NULL;
	m_pAccuracyTestItem = NULL;
	m_pFirWeekWaveTestItem = NULL;
	m_pZeroDrifTestItem = NULL;
	m_pTimeTestItem = NULL;
	m_pTreelayout = NULL;
	m_pTreeWidget = NULL;
	m_pPunAccuracyItem = NULL;
	m_pTimAccuracyItem = NULL;
	m_pPercentItem_2 = NULL;
	m_pPercentItem_100 = NULL;
	m_pPercentItem_5 = NULL;
	m_pPercentItem_10 = NULL;
	m_pPercentItem_50 = NULL;
	m_pPercentItem_80 = NULL;
	m_pPercentItem_120 = NULL;
	m_pPercentItem_150 = NULL;
	m_pCustomizationItem = NULL;
    m_clickedItem = NULL;
	m_nIsRelease = TRUE;

}

QSttMacroParaEditViewMuTreeWidget::~QSttMacroParaEditViewMuTreeWidget()
{

}

void QSttMacroParaEditViewMuTreeWidget::InitTreeUI()
{  
	CString strItem;
	CExBaseObject *pTempData = NULL;
	m_pTreelayout = new QHBoxLayout();
	m_pTreeWidget = new QScrollTreeWidget();

    m_pTreeWidget->setStyle(QStyleFactory::create("windows"));
	strItem = _T("Tree Header");
	m_pTreeWidget->setFrameStyle(QFrame::NoFrame);
	m_pTreeWidget->setHeaderLabel(strItem);
	m_pTreeWidget->setHeaderHidden(true);
	//m_pTreeWidget->header()->setSectionHidden(0, true);
	//m_pTreeWidget->header()->setVisible(false);
	m_pTreeWidget->setColumnCount(1);
	m_pTreeWidget->setStyleSheet("QTreeWidget::item{height: 30px;}");
 	
	
	m_pAutomatedTestItem = NewMUItem(NULL,pTempData);
	strItem = _T("合并单元自动测试");
	m_pAutomatedTestItem->setText(0,strItem);
	m_pAutomatedTestItem->setCheckState(0,Qt::Checked);  
    m_pTreeWidget->addTopLevelItem(m_pAutomatedTestItem); 
	
	m_pAccuracyTestItem = NewMUItem(m_pAutomatedTestItem,pTempData);
	strItem = _T("精度测试");
	m_pAccuracyTestItem->setText(0,strItem);
	m_pAccuracyTestItem->setCheckState(0,Qt::Checked);  
    m_pAutomatedTestItem->addChild(m_pAccuracyTestItem);
	
	m_pPercentItem_100 = NewMUItem(m_pAccuracyTestItem,pTempData);
	strItem = _T("100%");
	m_pPercentItem_100->setCheckState(0,Qt::Unchecked);  
    m_pPercentItem_100->setText(0,strItem);
	m_pAccuracyTestItem->addChild(m_pPercentItem_100);

	m_pPercentItem_2 = NewMUItem(m_pAccuracyTestItem,pTempData);
	strItem = _T("2%");
	m_pPercentItem_2->setCheckState(0,Qt::Unchecked); 
	m_pPercentItem_2->setText(0,strItem);
    m_pAccuracyTestItem->addChild(m_pPercentItem_2);

	m_pPercentItem_5 = NewMUItem(m_pAccuracyTestItem,pTempData);
	strItem = _T("5%");
	m_pPercentItem_5->setCheckState(0,Qt::Unchecked); 
	m_pPercentItem_5->setText(0,strItem);
    m_pAccuracyTestItem->addChild(m_pPercentItem_5);

	m_pPercentItem_10 = NewMUItem(m_pAccuracyTestItem,pTempData);
	strItem = _T("10%");
	m_pPercentItem_10->setCheckState(0,Qt::Unchecked); 
	m_pPercentItem_10->setText(0,strItem);
	m_pAccuracyTestItem->addChild(m_pPercentItem_10);

	m_pPercentItem_50 = NewMUItem(m_pAccuracyTestItem,pTempData);
	strItem = _T("50%");
	m_pPercentItem_50->setCheckState(0,Qt::Unchecked); 
	m_pPercentItem_50->setText(0,strItem);
	m_pAccuracyTestItem->addChild(m_pPercentItem_50);

	m_pPercentItem_80 = NewMUItem(m_pAccuracyTestItem,pTempData);
	strItem = _T("80%");
	m_pPercentItem_80->setCheckState(0,Qt::Unchecked); 
	m_pPercentItem_80->setText(0,strItem);
	m_pAccuracyTestItem->addChild(m_pPercentItem_80);

	m_pPercentItem_120 = NewMUItem(m_pAccuracyTestItem,pTempData);
	strItem = _T("120%");
	m_pPercentItem_120->setCheckState(0,Qt::Unchecked); 
	m_pPercentItem_120->setText(0,strItem);
	m_pAccuracyTestItem->addChild(m_pPercentItem_120);

	m_pPercentItem_150 = NewMUItem(m_pAccuracyTestItem,pTempData);
	strItem = _T("150%");
	m_pPercentItem_150->setCheckState(0,Qt::Unchecked); 
	m_pPercentItem_150->setText(0,strItem);
	m_pAccuracyTestItem->addChild(m_pPercentItem_150);

	m_pZeroDrifTestItem = NewMUItem(m_pAutomatedTestItem,pTempData);
	strItem = _T("零漂测试");
	m_pZeroDrifTestItem->setText(0,strItem);
	m_pZeroDrifTestItem->setCheckState(0,Qt::Unchecked);  
    m_pAutomatedTestItem->addChild(m_pZeroDrifTestItem);

	m_pFirWeekWaveTestItem = NewMUItem(m_pAutomatedTestItem,pTempData);
	strItem = _T("首周波测试");
	m_pFirWeekWaveTestItem->setText(0,strItem);
	m_pFirWeekWaveTestItem->setCheckState(0,Qt::Unchecked);  
    m_pAutomatedTestItem->addChild(m_pFirWeekWaveTestItem);

	m_pTimeTestItem = NewMUItem(m_pAutomatedTestItem,pTempData);
	strItem = _T("时间测试");
	m_pTimeTestItem->setText(0,strItem);
	m_pTimeTestItem->setCheckState(0,Qt::Checked);  
    m_pAutomatedTestItem->addChild(m_pTimeTestItem);

	m_pTimAccuracyItem = NewMUItem(m_pTimeTestItem,pTempData);
	strItem = _T("对时精度");
	m_pTimAccuracyItem->setText(0,strItem);
	m_pTimAccuracyItem->setCheckState(0,Qt::Unchecked);  
	m_pTimeTestItem->addChild(m_pTimAccuracyItem);

	m_pPunAccuracyItem = NewMUItem(m_pTimeTestItem,pTempData);
    strItem = _T("守时精度");
	m_pPunAccuracyItem->setText(0,strItem);
	m_pPunAccuracyItem->setCheckState(0,Qt::Unchecked);  
	m_pTimeTestItem->addChild(m_pPunAccuracyItem);

	

    //m_pTreeWidget->setItemsExpandable(false);
 	m_pTreeWidget->expandAll();
	m_pTreeWidget->setSelectionMode(QTreeWidget::ExtendedSelection);
    m_pTreelayout->addWidget(m_pTreeWidget);
	this->setLayout(m_pTreelayout);
	
 
}

void QSttMacroParaEditViewMuTreeWidget::StartInit()
{
    m_pTreeWidget->setDisabled(true);
}
void QSttMacroParaEditViewMuTreeWidget::StopInit()
{
    m_pTreeWidget->setDisabled(false);
}

QExBaseTreeWidgetItem* QSttMacroParaEditViewMuTreeWidget::NewMUItem(QExBaseTreeWidgetItem *parent, CExBaseObject *pData)
{
	return new QExBaseTreeWidgetItem(parent, pData);
}

void QSttMacroParaEditViewMuTreeWidget::mousePressEvent(QMouseEvent* event)  
{
// 	if (event->button() == Qt::LeftButton) 
// 	{
// 		QTreeWidgetItem* item = itemAt(event->pos());
// 
// 		if (item != NULL) 
// 		{
// 			m_clickedItem = item;
// 			m_pressPos = event->pos();
// 		}
// 	}
// 
// 	QTreeWidget::mousePressEvent(event);
}

void QSttMacroParaEditViewMuTreeWidget::mouseReleaseEvent(QMouseEvent* event)  
{
// 	if (event->button() == Qt::LeftButton) 
// 	{
// 		QTreeWidgetItem* item = itemAt(event->pos());
// 
// 		if (item != NULL && item == m_clickedItem && event->pos() == m_pressPos) // 鼠标有释放 
// 		{
// 			m_nIsRelease = TRUE;
// 			
// 		} 
// 		else // 鼠标没有释放
// 		{
// 			
// 			m_nIsRelease = FALSE;
// 		}
// 
// 		m_clickedItem = NULL;
// 	}
// 
// 	QTreeWidget::mouseReleaseEvent(event);
}


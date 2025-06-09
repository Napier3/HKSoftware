#ifndef STTMACROPARAEDITVIEWMUTREEWIDGET_H
#define STTMACROPARAEDITVIEWMUTREEWIDGET_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QTreeWidget>
#include <QCheckBox>
#include <QString>
#include <QScrollArea>
#include <QHeaderView>
#include <QStyleFactory>

#include "../../../../Module/OSInterface/QT/CString_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/BaseClass/QT/QExBaseListTreeCtrl.h"
#include "../Module/ScrollCtrl/ScrollTreeWidget.h"

class QSttMacroParaEditViewMuTreeWidget : public QWidget 
{
	Q_OBJECT

public:

	QSttMacroParaEditViewMuTreeWidget();
	virtual ~QSttMacroParaEditViewMuTreeWidget();

	void InitTreeUI();
	void StartInit();
	void StopInit();

	QExBaseTreeWidgetItem* NewMUItem(QExBaseTreeWidgetItem *parent, CExBaseObject *pData);

    QHBoxLayout* m_pTreelayout;
	QScrollTreeWidget* m_pTreeWidget;
    QExBaseTreeWidgetItem* m_pAutomatedTestItem;
	QExBaseTreeWidgetItem* m_pAccuracyTestItem;
    QExBaseTreeWidgetItem* m_pFirWeekWaveTestItem;
    QExBaseTreeWidgetItem* m_pZeroDrifTestItem;
	QExBaseTreeWidgetItem* m_pTimeTestItem;
	QExBaseTreeWidgetItem* m_pPunAccuracyItem;
	QExBaseTreeWidgetItem* m_pTimAccuracyItem;
    QExBaseTreeWidgetItem* m_pPercentItem_2;
	QExBaseTreeWidgetItem* m_pPercentItem_100;
	QExBaseTreeWidgetItem* m_pPercentItem_5;
	QExBaseTreeWidgetItem* m_pPercentItem_10;
	QExBaseTreeWidgetItem* m_pPercentItem_50;
	QExBaseTreeWidgetItem* m_pPercentItem_80;
	QExBaseTreeWidgetItem* m_pPercentItem_120;
	QExBaseTreeWidgetItem* m_pPercentItem_150;
	QExBaseTreeWidgetItem* m_pCustomizationItem;

	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event); 

	
public:
	QTreeWidgetItem* m_clickedItem ;
	QPoint m_pressPos;
	BOOL m_nIsRelease;

};

#endif

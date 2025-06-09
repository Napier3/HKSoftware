#ifndef QTERMINALTREEWIDGET_H
#define QTERMINALTREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QCheckBox>
#include <QPushButton>
#include "../../../../Module/OSInterface/QT/CString_QT.h"
#include "../../../../Module/BaseClass/QT/QExBaseListTreeCtrl.h"
#include "QTerminalSettingTabWidget.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgGoutDatas.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgGoutData.h"
#include "../Module/ScrollCtrl/ScrollTreeWidget.h"

class QTerminalTreeWidget : public QWidget
{

	Q_OBJECT
public:
	QTerminalTreeWidget(QWidget *parent = 0);
	~QTerminalTreeWidget();

	void InitUI();
	QExBaseTreeWidgetItem* NewMUItem(QExBaseTreeWidgetItem *parent, CExBaseObject *pObj);
	void InitConnection();
	void UpdateTreeItem();
	void StartInit();
	void StopInit();
	void CheckChildItems(QTreeWidgetItem* item, Qt::CheckState checked);
	void SetFont();
	void ClearChildItems(QTreeWidgetItem* parentItem, const QString& idFormat);
	void AddNewItems(QExBaseTreeWidgetItem* parentItem, int nItemCount, const QString& idFormat, QList<QExBaseTreeWidgetItem *>& itemList);

	void ResetDataItemValues();// 清空设置paras对应ID为0
	BOOL IsGoutCheckID(const CString& strID);
	BOOL IsGinCheckID(const CString& strID);

public:
	QScrollTreeWidget* m_pTreeWidget;
	QPushButton* m_pBtn_SelectAll;
	QPushButton* m_pBtn_Clear;
	QPushButton* m_pBtn_Setting;
	QTerminalSettingTabWidget *m_pMuSettingTabWidget;

	QExBaseTreeWidgetItem *m_pRootItem;
	QExBaseTreeWidgetItem *m_pGooseBinItem;
	QExBaseTreeWidgetItem *m_pGooseBinItem1;
	QExBaseTreeWidgetItem *m_pGooseBoutItem;
	QExBaseTreeWidgetItem *m_pGooseBoutItem1;
	QExBaseTreeWidgetItem *m_pSOEItem;
	QExBaseTreeWidgetItem *m_pSOEItem1;
	QExBaseTreeWidgetItem *m_pSOEItem2;
	QList<QExBaseTreeWidgetItem *> m_pGoutTestItems;
	QList<QExBaseTreeWidgetItem *> m_pGinTestItems;

signals:
	void sig_UpdateData(CIecCfgGoutChs *);

public slots:
	void slot_Setting();
	void slot_AllSelected();
	void slot_Clear();
	void handleItemChanged(QTreeWidgetItem* item, int column);
};
#endif

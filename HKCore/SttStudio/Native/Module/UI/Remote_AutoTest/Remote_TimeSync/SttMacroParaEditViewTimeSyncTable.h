#ifndef QSttMacroParaEditViewTimeSyncTable_H
#define QSttMacroParaEditViewTimeSyncTable_H


#include "../../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../Module/CommonCtrl_QT/CommonCtrlInterface.h"
#include "../../../Module/DataMngr/DvmData.h"


class QSttMacroParaEditViewTimeSyncTable :public QScrollTableWidget, public CCommonCtrlInterface
{
	Q_OBJECT

public:
	QSttMacroParaEditViewTimeSyncTable(QWidget *parent = 0);
	~QSttMacroParaEditViewTimeSyncTable();

	void InitUI();
	virtual void UpdateText(const QString &strText);
	void InitTable();
	void InitData(CDataGroup *pData);
	void GetTableWidgetItemValue(QTableWidgetItem * pItem );
public:	
	BOOL m_bRunning;
	int m_nRowHeight;
	int m_nHeaderViewHeight;
	QTableWidgetItem *m_pCurrKeyboardItem;
	CDataGroup *m_pTimeSyncDataGroup;


protected slots:

};

#endif

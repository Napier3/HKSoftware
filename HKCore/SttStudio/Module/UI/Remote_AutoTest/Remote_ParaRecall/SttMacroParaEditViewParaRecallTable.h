#ifndef QSttMacroParaEditViewParaRecallTable_H
#define QSttMacroParaEditViewParaRecallTable_H


#include "../../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../Module/CommonCtrl_QT/CommonCtrlInterface.h"
#include "../../../../../Module/DataMngr/DvmData.h"


class QSttMacroParaEditViewParaRecallTable :public QScrollTableWidget, public CCommonCtrlInterface
{
	Q_OBJECT

public:
	QSttMacroParaEditViewParaRecallTable(QWidget *parent = 0);
	~QSttMacroParaEditViewParaRecallTable();

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
	CDataGroup *m_pParaRecallDataGroup;


protected slots:

};

#endif
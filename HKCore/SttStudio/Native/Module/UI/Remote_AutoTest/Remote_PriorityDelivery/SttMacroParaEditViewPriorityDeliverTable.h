#ifndef QSttMacroParaEditViewPriorityDeliverTable_H
#define QSttMacroParaEditViewPriorityDeliverTable_H


#include "../../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../Module/CommonCtrl_QT/CommonCtrlInterface.h"
#include "../../../Module/DataMngr/DvmData.h"


class QSttMacroParaEditViewPriorityDeliverTable :public QScrollTableWidget, public CCommonCtrlInterface
{
	Q_OBJECT

public:
	QSttMacroParaEditViewPriorityDeliverTable(QWidget *parent = 0);
	~QSttMacroParaEditViewPriorityDeliverTable();

	void InitUI();
	virtual void UpdateText(const QString &strText);
	void InitTable();
	void UpdataData(CDvmData *pDvmData,long nIndex);
	void InitData(CDataGroup *pData,CDataGroup *pParas);
	void GetTableWidgetItemValue(CDataGroup *pParas,long nIndex,long nDecimal,QTableWidgetItem * pItem,const CString strID );
	void UpdateTable(CDataGroup *pParas);


public:	
	BOOL m_bRunning;
	int m_nRowHeight;
	int m_nHeaderViewHeight;
	QTableWidgetItem *m_pCurrKeyboardItem;
	CDataGroup *m_pDeliverDataGroup;

protected slots:
	void slot_OnCellChanged(int row,int col);
};

#endif

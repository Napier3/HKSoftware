#ifndef QSttMacroParaEditViewRemote_DualPositionTable_H
#define QSttMacroParaEditViewRemote_DualPositionTable_H


#include "../../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../Module/CommonCtrl_QT/CommonCtrlInterface.h"
#include "../../../Module/DataMngr/DvmData.h"


class QSttMacroParaEditViewDualPositionTable :public QScrollTableWidget, public CCommonCtrlInterface
{
	Q_OBJECT

public:
	QSttMacroParaEditViewDualPositionTable(QWidget *parent = 0);
	~QSttMacroParaEditViewDualPositionTable();

	void InitUI();
	virtual void UpdateText(const QString &strText);
	void InitTable();
	void InitData(CDataGroup *pData);
	void AddRow(const CString &col0Text, const CString &col1Text);
	void UpdataData(CString strID,CDvmData *pDvmData);
	void GetTableWidgetItemValue( CDataGroup *pParas ,long nIndex,QTableWidgetItem * pItem);
	void UpdateTable(CDataGroup *pParas);


public:	
	BOOL m_bRunning;
	int m_nRowHeight;
	int m_nHeaderViewHeight;
	QTableWidgetItem *m_pCurrKeyboardItem;
	CDataGroup *m_pDualPositionDataGroup;
	QStringList m_pIDList;

protected slots:
	void slot_OnCellChanged(int row,int col);
};

#endif

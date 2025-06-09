#ifndef QSttMacroParaEditViewRemote_AccuracyTable_H
#define QSttMacroParaEditViewRemote_AccuracyTable_H


#include "../../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../Module/CommonCtrl_QT/CommonCtrlInterface.h"
#include "../../../../../Module/DataMngr/DvmData.h"


class QSttMacroParaEditViewRemote_AccuracyTable :public QScrollTableWidget, public CCommonCtrlInterface
{
	Q_OBJECT

public:
	QSttMacroParaEditViewRemote_AccuracyTable(QWidget *parent = 0);
	~QSttMacroParaEditViewRemote_AccuracyTable();

	void InitUI();
	virtual void UpdateText(const QString &strText);
	void InitTable();
	void InitData(CDataGroup *pData,CDataGroup *pAccuracyDataGroup);
	void UpdataData(CDvmData *pDvmData,long nIndex);
	void GetTableWidgetItemValue(CDataGroup *pParas,long nIndex,QTableWidgetItem * pItem);
	void UpdateTable(CDataGroup *pParas);


public:	
	BOOL m_bRunning;
	int m_nRowHeight;
	int m_nHeaderViewHeight;
	QTableWidgetItem *m_pCurrKeyboardItem;
	CDataGroup *m_pAccuracyDataGroup;

protected slots:
	void slot_OnCellChanged(int row,int col);
};

#endif
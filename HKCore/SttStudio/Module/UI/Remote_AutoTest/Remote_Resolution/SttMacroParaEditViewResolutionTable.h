#ifndef QSttMacroParaEditViewResolutionTable_H
#define QSttMacroParaEditViewResolutionTable_H


#include "../../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../Module/CommonCtrl_QT/CommonCtrlInterface.h"
#include "../../../../../Module/DataMngr/DvmData.h"


class QSttMacroParaEditViewResolutionTable :public QScrollTableWidget, public CCommonCtrlInterface
{
	Q_OBJECT

public:
	QSttMacroParaEditViewResolutionTable(QWidget *parent = 0);
	~QSttMacroParaEditViewResolutionTable();

	void InitUI();
	virtual void UpdateText(const QString &strText);
	void InitTable();
	void InitData(CDataGroup *pData);
	void AddRow(const CString &colText);
	void GetTableWidgetItemValue(CDataGroup *pParas,QTableWidgetItem * pItem,CString strID);
	void UpdataData(CDvmData *pDvmData,long nIndex);
	void UpdateKeepTime();
	void UpdateTable(CDataGroup *pParas);


public:	
	BOOL m_bRunning;
	int m_nRowHeight;
	int m_nHeaderViewHeight;
	QTableWidgetItem *m_pCurrKeyboardItem;
	CDataGroup *m_pResolutionDataGroup;


protected slots:
	void slot_OnCellChanged(int row,int col);
};

#endif
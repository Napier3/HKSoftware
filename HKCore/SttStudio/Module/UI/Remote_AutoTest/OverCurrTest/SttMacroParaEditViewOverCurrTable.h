#ifndef QSttMacroParaEditViewOverCurrTable_H
#define QSttMacroParaEditViewOverCurrTable_H


#include "../../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"

class QSttMacroParaEditViewOverCurrTable :public QTableWidget
{
	Q_OBJECT

public:
	QSttMacroParaEditViewOverCurrTable(int rows, int columns,QWidget *parent);
	~QSttMacroParaEditViewOverCurrTable();

	void InitUI();
	void InitTable();
	void InitData(CDataGroup *pData);
	void GetTableWidgetItemValue( QTableWidgetItem * pItem,const CString strID ,bool bCheck);
	void UpdateTable();

public:	
	BOOL m_bRunning;
	int m_nRowHeight;
	int m_nHeaderViewHeight;
	CDataGroup *m_pData ;
	QTableWidgetItem *m_pCurrKeyboardItem;//弹键盘时使用的表格单元格
	QExBaseListCheckBoxDelegate *m_pCheckBoxDelegateBase;

protected slots:
	void slot_OnCellChanged(int row,int col);
};

#endif
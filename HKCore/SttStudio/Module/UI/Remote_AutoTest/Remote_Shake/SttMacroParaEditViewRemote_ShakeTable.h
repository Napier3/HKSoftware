#ifndef QSttMacroParaEditViewRemote_ShakeTable_H
#define QSttMacroParaEditViewRemote_ShakeTable_H


#include "../../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../Module/CommonCtrl_QT/CommonCtrlInterface.h"
#include "../../../../../Module/DataMngr/DvmData.h"
#include "../../../Module/UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"


class QSttMacroParaEditViewRemote_ShakeTable :public QScrollTableWidget, public CCommonCtrlInterface
{
	Q_OBJECT

public:
	QSttMacroParaEditViewRemote_ShakeTable(QWidget *parent = 0);
	~QSttMacroParaEditViewRemote_ShakeTable();

	void InitUI();
	virtual void UpdateText(const QString &strText);
	void InitTable();
	void InitData(CDataGroup *pData);
	void GetTableWidgetItemValue(CDataGroup *pParas,long nIndex,QTableWidgetItem * pItem,const CString strID ,bool bCheck);
	void UpdateTable( CDvmData *pDvmData,long nIndex );
	void UpdateTable(CDataGroup *pParas);


public:	
	BOOL m_bRunning;
	int m_nRowHeight;
	int m_nHeaderViewHeight;
	QTableWidgetItem *m_pCurrKeyboardItem;
	QExBaseListCheckBoxDelegate *m_pCheckBoxDelegateBase;
	CDataGroup *m_pShakeDataGroup;

protected slots:
	void slot_OnCellChanged(int row,int col);
};

#endif
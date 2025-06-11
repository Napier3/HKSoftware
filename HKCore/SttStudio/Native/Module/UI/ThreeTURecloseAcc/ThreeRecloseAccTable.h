#ifndef STTMACROPARAEDITVIEWTHREETURECLOSEACCTABLE_H
#define STTMACROPARAEDITVIEWTHREETURECLOSEACCTABLE_H
#include "../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../Module/CommonCtrl_QT/CommonCtrlInterface.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttLineEdit.h"
#include "../../DataMngr/DataGroup.h"

class QThreeRecloseAccTable :public QScrollTableWidget, public CCommonCtrlInterface
{
	Q_OBJECT

public:
	QThreeRecloseAccTable(CDataGroup* pParas,QWidget *parent = 0);
	 ~QThreeRecloseAccTable();

public:
	void InitUI();
	void InitTable();
	virtual void UpdateText(const QString &strText);
	void UpdateCheckbox(int row,bool bChecked );
	void GetCheckBoxValue( CDataGroup *pParas,QSttCheckBox * pCheckBox,const CString strID);
	void UpdateTableData(CDataGroup *pParas);
	void UpdateRecState(bool bUpdateRec1State=false, bool bCheck=false);//更新三次重合闸
	void UpdateTestItemState();//更新第一列测试项
	void UpdateRecSetValue();//更新一次重合闸时间定值使能状态

public:	
	BOOL m_bRunning;
	int m_nRowHeight;
	int m_nHeaderViewHeight;
	QTableWidgetItem *m_pCurrKeyboardItem;
	QList<QSttCheckBox*> m_pAllCheckBoxList;
	QList<QSttLineEdit*> m_pAllLineEditList;
	QList<QSttCheckBox*> m_pRecCheckBoxList;
	QList<QSttCheckBox*> m_pPreAccRecCheckBoxList;
	CDataGroup* m_pParas;

signals:
	void sig_AftAccCheckStateChanged(bool);

protected slots:
	void slot_CheckBoxStateChanged(int);
	void slot_EditingFinished();
};
#endif
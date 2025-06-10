#ifndef QREMOTECTRLTABLE_H
#define QREMOTECTRLTABLE_H

#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
#include "../../SttTest/Common/tmt_manu_test.h"

#include "../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"


#include "../Module/CommonCtrl_QT/CommonCtrlInterface.h"

#define STT_REMOTECTRL_TABLE_COL_Index                 0//第一列  编号
#define STT_REMOTECTRL_TABLE_COL_Internal                1 //间隔 
#define STT_REMOTECTRL_TABLE_COL_Chanal                2 //通道
#define STT_REMOTECTRL_TABLE_COL_Operation                  3 //操作
#define STT_REMOTECTRL_TABLE_COL_Act            4 //动作 
#define STT_REMOTECTRL_TABLE_COL_Record          5 //记录
#define STT_REMOTECTRL_TABLE_COL_Time           6 //时间

#define STT_REMOTECTRL_SecondTABLE_COL_Index                 0//第一列  编号
#define STT_REMOTECTRL_SecondTABLE_COL_Internal                1 //间隔 
#define STT_REMOTECTRL_SecondTABLE_COL_Chanal                2 //通道
#define STT_REMOTECTRL_SecondTABLE_COL_EventType                  3 //事件类型
#define STT_REMOTECTRL_SecondTABLE_COL_DeviceTime           4 //装置时间 
#define STT_REMOTECTRL_SecondTABLE_COL_PCTime          5 //PC时间

#define REMOTECTRL_TABLE_First 0
#define REMOTECTRL_TABLE_Second 1

typedef struct EventStruct
{
	long nIndex;//编号
	CString strInterSelectName;//间隔名
	CString strChannelSelectName;//通道名
	CString strOperationSelectName;//操作
	CString strActionName;//动作
	CString strRecord;//记录
	CString strRecordtime;//时间
}EventStruct;

class QRemoteCtrlTable :public QScrollTableWidget, public CCommonCtrlInterface
{
	Q_OBJECT

public:
	QRemoteCtrlTable(int nTableType,QWidget *parent = 0);
	~QRemoteCtrlTable();

	void InitUI();
	void InitTable();
	void SetData();
	//显示操作记录
	void UpdateTableData(EventStruct* pEventStruct ,long nIndex);
	void UpdateExcRlt(long nErrorInfor);
	//显示SOE报告
	void AddShowSoeReports(CExBaseList *pSoeRptList);
	CString GetSoeAttrValue(CDvmData *pCurrData,const CString &strSearchID);


	void UpdateTable(int row,int col);

	virtual void UpdateText(const QString &strText);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

	BOOL m_bRunning;

public:
	int m_nTableType;
	int m_nRowHeight;
	int m_nHeaderViewHeight;

	QTableWidgetItem *m_pCurrKeyboardItem;//弹键盘时使用的表格单元格

	int m_nTime;
	int  m_nCnt;
	QLineEdit *pLinedit ;

signals:

	void sig_updataParas();

protected slots:
		void slot_OnCellChanged(int row,int col);
		void slot_OnItemDoubleClicked(QTableWidgetItem *pItem);

};

#endif // QREMOTECTRLTABLE_H

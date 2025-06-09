#ifndef QREMOTECTRLTABLE_H
#define QREMOTECTRLTABLE_H

#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
#include "../../SttTest/Common/tmt_manu_test.h"

#include "../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"


#include "../Module/CommonCtrl_QT/CommonCtrlInterface.h"

#define STT_REMOTECTRL_TABLE_COL_Index                 0//��һ��  ���
#define STT_REMOTECTRL_TABLE_COL_Internal                1 //��� 
#define STT_REMOTECTRL_TABLE_COL_Chanal                2 //ͨ��
#define STT_REMOTECTRL_TABLE_COL_Operation                  3 //����
#define STT_REMOTECTRL_TABLE_COL_Act            4 //���� 
#define STT_REMOTECTRL_TABLE_COL_Record          5 //��¼
#define STT_REMOTECTRL_TABLE_COL_Time           6 //ʱ��

#define STT_REMOTECTRL_SecondTABLE_COL_Index                 0//��һ��  ���
#define STT_REMOTECTRL_SecondTABLE_COL_Internal                1 //��� 
#define STT_REMOTECTRL_SecondTABLE_COL_Chanal                2 //ͨ��
#define STT_REMOTECTRL_SecondTABLE_COL_EventType                  3 //�¼�����
#define STT_REMOTECTRL_SecondTABLE_COL_DeviceTime           4 //װ��ʱ�� 
#define STT_REMOTECTRL_SecondTABLE_COL_PCTime          5 //PCʱ��

#define REMOTECTRL_TABLE_First 0
#define REMOTECTRL_TABLE_Second 1

typedef struct EventStruct
{
	long nIndex;//���
	CString strInterSelectName;//�����
	CString strChannelSelectName;//ͨ����
	CString strOperationSelectName;//����
	CString strActionName;//����
	CString strRecord;//��¼
	CString strRecordtime;//ʱ��
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
	//��ʾ������¼
	void UpdateTableData(EventStruct* pEventStruct ,long nIndex);
	void UpdateExcRlt(long nErrorInfor);
	//��ʾSOE����
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

	QTableWidgetItem *m_pCurrKeyboardItem;//������ʱʹ�õı��Ԫ��

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

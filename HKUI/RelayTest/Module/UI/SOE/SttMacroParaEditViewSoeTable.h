#ifndef _QSttMacroParaEditViewSoe_table_H
#define _QSttMacroParaEditViewSoe_table_H

#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
#include "../../SttTest/Common/tmt_soe_test.h"

#include "../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"


#include "../Module/CommonCtrl_QT/CommonCtrlInterface.h"

#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"

#define STT_SOE_TABLE_COL_Index                 0//第一列  序号列
#define STT_SOE_TABLE_COL_Select                1 //选择 
#define STT_SOE_TABLE_COL_Chanal                2 //通道
#define STT_SOE_TABLE_COL_Stat                  3 //初始状态
#define STT_SOE_TABLE_COL_TimeBinAct            4 //变位前时长 
#define STT_SOE_TABLE_COL_TimeBinExAct          5 //闭合时长
#define STT_SOE_TABLE_COL_TimeBoutAct           6 //断开时长
#define STT_SOE_TABLE_COL_Count                 7 //变位次数
#define STT_SOE_TABLE_COL_HoldTime              8 //持续时间

class CComboBoxSoeDelegate :  public QItemDelegate 
{
	Q_OBJECT
public:
	CComboBoxSoeDelegate(QObject *parent=NULL);
	~CComboBoxSoeDelegate();


	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
		const QModelIndex &index ) const;

	virtual void setEditorData(QWidget * ditor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
		const QModelIndex &index) const;
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;

private slots:
	void commitAndCloseEditor();
};

///////////////////////////////////////////////////////////////////////////


class QSttMacroParaEditViewSoeTable :public QScrollTableWidget, public CCommonCtrlInterface
{
	Q_OBJECT

public:
	QSttMacroParaEditViewSoeTable(QWidget *parent = 0);
	~QSttMacroParaEditViewSoeTable();

	void InitUI();
	void InitTable();
	void SetData(tmt_soe_test *pChData);

	void UpdateTable(int row,int col);
	void GetMaxHoldTime(); //chenling20240325 获得最大持续时间

	virtual void UpdateText(const QString &strText);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

	BOOL m_bRunning;

public:
	tmt_soe_test   *m_pSoeTest;

	int m_nRowHeight;
	int m_nHeaderViewHeight;

	QTableWidgetItem *m_pCurrKeyboardItem;//弹键盘时使用的表格单元格
	QExBaseListCheckBoxDelegate *m_pCheckBoxDelegateBase;
	//QScrollComboBox *m_pComboBox;

	CComboBoxSoeDelegate *m_pComboBox;
	int m_nTime;
	int  m_nCnt;
	QLineEdit *pLinedit ;

	void SetSelState_SelectAll();
	void SetSelState_UnSelectAll();

	void SetSelState_InitialAll();
	void SetSelState_UnInitialAll();

	void setComboxSoeDelegate(int row,QTableWidgetItem *pItem,tmt_soe_test *pData);

// private:
// 	QScrollComboBox* NewStatType();

	void setHoldTimeData(int nRow);

signals:

	void sig_updataParas();

	protected slots:
		void slot_SetStateChanged(int);
		void slot_OnCellChanged(int row,int col);
		void slot_OnItemDoubleClicked(QTableWidgetItem *pItem);

		void slot_SoeCountChanged(QWidget* editor);

};

#endif // _QSttMacroParaEditViewSoe_table_H

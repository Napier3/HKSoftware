#ifndef _QSttMacroParaEditViewSoe_table_H
#define _QSttMacroParaEditViewSoe_table_H

#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QStringList>
#include <QVector>
#include "../../SttTest/Common/tmt_soe_test.h"
#include "../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../Module/CommonCtrl_QT/CommonCtrlInterface.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../Module/DataMngr/DvmDataset.h"

#define STT_SOE_FirstTABLE_COL_Index                 0//序号
#define STT_SOE_FirstTABLE_COL_Select                1 //选择 
#define STT_SOE_FirstTABLE_COL_BoutChanal            2 //开出通道
#define STT_SOE_FirstTABLE_COL_State                 3 //初始状态
#define STT_SOE_FirstTABLE_COL_Object                4 //测试对象
#define STT_SOE_FirstTABLE_COL_ClosedTime            5 //闭合时长


#define STT_SOE_SecondTABLE_COL_Index                 0//编号
#define STT_SOE_SecondTABLE_COL_Internal              1 //间隔 
#define STT_SOE_SecondTABLE_COL_Chanal                2 //通道
#define STT_SOE_SecondTABLE_COL_EventDescribe         3 //事件描述
#define STT_SOE_SecondTABLE_COL_EventTime             4 //事件时间 

#define SOE_TABLE_First    0
#define SOE_TABLE_Second   1


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

	void updateItems(const QVector<QStringList> ObjectIndexList);

private slots:
	void commitAndCloseEditor();	

private:
	QVector<QStringList> m_ObjectIndexList;


};

///////////////////////////////////////////////////////////////////////////

#ifdef _PSX_QT_LINUX_ 
class QSttMacroParaEditViewSoeTable :public QScrollTableWidget, public CCommonCtrlInterface
#else
class QSttMacroParaEditViewSoeTable :public QTableWidget, public CCommonCtrlInterface
#endif
{
	Q_OBJECT

public:
	QSttMacroParaEditViewSoeTable(int nTableType,QWidget *parent = 0);
	~QSttMacroParaEditViewSoeTable();

	void InitUI();
	void InitTable();
	void InitData(tmt_SoeParas *pSoeParas);
	virtual void UpdateText(const QString &strText);
#ifdef _PSX_QT_LINUX_
	//bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
#endif
	void setInitStateComboxSoeDelegate(int row,QTableWidgetItem *pItem,tmt_SoeParas *pSoeParas);
	void UpdateDeviceData(int row,int col,QTableWidgetItem *pItem);
	void AddShowSoeReports(CDvmDataset *pSoeRptDataset);
	CString GetSoeAttrValue(CDvmData *pCurrData,const CString &strSearchID);
	void UpdateTestObjet(CExBaseList *pList);
	void slot_InterChanged(int nIndex);
	void UpdateTable();
	void UpdateSelTestObject();


public:	
	BOOL m_bRunning;
	int m_nRowHeight;
	int m_nHeaderViewHeight;

	QTableWidgetItem *m_pCurrKeyboardItem;//弹键盘时使用的表格单元格
	QExBaseListCheckBoxDelegate *m_pCheckBoxDelegateBase;

	CComboBoxSoeDelegate *m_pInitStateComboBox;
	CComboBoxSoeDelegate *m_pTestObjetcComboBox;

	int m_nTableType;
	tmt_SoeParas *m_pSoeParas;

	QVector<QStringList> oObjectNameList;
	QVector<QStringList> oObjectIDList;


protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_OnItemDoubleClicked(QTableWidgetItem *pItem);
	void slot_SoeCountChanged(QWidget* editor);
	void slot_TestObjectChanged(QWidget* editor);
};

#endif // _QSttMacroParaEditViewSoe_table_H



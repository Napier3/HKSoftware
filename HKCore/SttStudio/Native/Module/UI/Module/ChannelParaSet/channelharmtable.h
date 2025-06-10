#ifndef CHANNELHARMTABLE_H
#define CHANNELHARMTABLE_H

#include "channeltable.h"

class CComboBoxHarmDelegate :  public QItemDelegate 
{
	Q_OBJECT
public:
	CComboBoxHarmDelegate(bool bDC = false,QObject *parent=NULL);
	~CComboBoxHarmDelegate();

	bool m_bDC;

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
		const QModelIndex &index ) const;

	virtual void setEditorData(QWidget * ditor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
		const QModelIndex &index) const;
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;
};


class QChannelHarmTable : public QChannelTable
{
	Q_OBJECT

public:
	QChannelHarmTable(MOUDLEType moudleType,CExBaseList *pChList,tmt_channel *pArrUI,QWidget *parent = 0);
	~QChannelHarmTable();
	
	virtual void setProperty(bool bDCTest);
	virtual void setItemValue(int row,int col,float fv);
	
	virtual void initTable();
	virtual void UpdateTable();
	virtual void UpdateValidTableDatas();

	void setComboxHarmDelegate();
	QString getHarmString(int nHarmCount);
	int getHarmCount(CString strHarmDesc);
	int getHarmSelectedCount(tmt_channel *pCh);
	void UpdateHarmCell(int row,bool bEnable);
	bool IsHarmBaseAddValid(int row,int col,int nHarmCount,float fv);

	virtual void setTableData(tmt_channel *pArrUI);

	Qt::ItemFlags m_Originalflags;
	CComboBoxHarmDelegate* m_pComboBoxHarmDelegate; 
public:
	virtual void UpdateText(const QString &strText);

protected slots:
	virtual void slot_OnCellChanged(int row,int col);
	virtual void slot_OnItemClicked(QTableWidgetItem *pItem);
	void slot_TableShowMent(QPoint pos);
	void slot_HarmCountChanged(QWidget* editor);

signals:
	void sig_ChannelValueChanged(MOUDLEType moudleType,int channelNum,int valueFlag,float harmvalue);//valueFlag=（1:幅值 2:相位 3:谐波次数）
};


#endif // CHANNELHARMTABLE_H

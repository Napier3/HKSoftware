#ifndef CHANNELHARMTABLE_H
#define CHANNELHARMTABLE_H

#include "channeltable.h"

class CHannelHarmTable : public CHannelTable
{
	Q_OBJECT

public:
	CHannelHarmTable(MOUDLEType moudleType,CExBaseList *pChList,tmt_channel *pArrUI,QWidget *parent = 0);
	~CHannelHarmTable();
	
	virtual void setProperty(bool bDCTest);
	virtual void setItemValue(int row,int col,float fv);
	virtual void setColumnNum(int num);
	virtual void initTable();
	virtual void UpdateTable();
	virtual void UpdateValidTableDatas();

	void setComboxHarmDelegate();
	QString getHarmString(int nHarmCount);
	int getHarmCount(QString strHarmDesc);
	int getHarmSelectedCount(tmt_channel *pCh);
	void UpdateHarmCell(int row,bool bEnable);
	bool IsHarmBaseAddValid(int row,int col,int nHarmCount,float fv);

	Qt::ItemFlags m_Originalflags;

protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_TableShowMent(QPoint pos);
	void slot_HarmCountChanged(QWidget* editor);

signals:
	void sig_ChannelValueChanged(MOUDLEType moudleType,int channelNum,int valueFlag,float harmvalue);//valueFlag=（1:幅值 2:相位 3:谐波次数）
};

class CComboBoxHarmDelegate : public QItemDelegate
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
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CHANNELHARMTABLE_H

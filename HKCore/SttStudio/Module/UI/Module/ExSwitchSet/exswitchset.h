#ifndef EXSWITCHSET_H
#define EXSWITCHSET_H

#include <QWidget>
#include <QTableWidget>
#include <QCheckBox>
#include <QHeaderView>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include "../../Module/SttTest/Common/tmt_common_def.h"

enum ExSwitchType{ExInput = 0,ExOutPut};

class ExSwitchSet : public QWidget
{
	Q_OBJECT

public:
	ExSwitchSet(ExSwitchType etype,QWidget *parent = 0);
	~ExSwitchSet();
	
	QTableWidget *m_pTable;
	QCheckBox *ck_SelectAll;
	QFrame *frame;

	void setData(tmt_BinaryIn *pArrInEx,tmt_BinaryOut *pArrOutEx);
	
	tmt_BinaryIn  *m_pArrInEx;	//系统扩展开入量
	tmt_BinaryOut *m_pArrOutEx;	//系统扩展开出量
	
	void initUI();
	void initTable();
	void initTableData();
	void updateData();

	void GetMaxRowColIndex(long &nMaxRowIndex,long &nMaxColIndex,long &nTotalCounts);

signals:
	void sig_ExSwitchChanged();

public slots:
	void slot_ck_SelectAllChanged(int);
	void slot_Table_cellClicked ( int row, int column);

private:
	ExSwitchType m_eType;
	
	bool m_bExVal[MAX_ExBINARY_COUNT];
};

#endif // EXSWITCHSET_H

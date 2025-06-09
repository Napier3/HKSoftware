#ifndef QINTERHARMONICSWIDGET_H
#define QINTERHARMONICSWIDGET_H

#include "../Module/ChannelParaSet/QBasicTestParaSet.h"
#include "../../SttTest/Common/tmt_harm_test.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../Controls/SettingCtrls/QSettingItem.h"
#include <QWidget>

class QInterharmonicsChannelTable : public QChannelTable
{
	Q_OBJECT
public:
	QInterharmonicsChannelTable(MOUDLEType moudleType, CExBaseList *pChList,
		tmt_channel *pArrUI, QWidget *parent = NULL);

	QCheckBoxDelegateBase *m_pCheckBoxDelegateBase;

	virtual ~QInterharmonicsChannelTable();

	virtual void initTable();
	virtual void UpdateTable();

	virtual void Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll=TRUE, long nCol = 1);
	virtual void Act_setPrasePValue(int nSwitch,int nOffset,float fv, long nCol = 2);
	virtual void Act_setPraseNValue(int nSwitch,int nOffset,float fv, long nCol = 2);
	virtual void Act_setPraseZValue(int nStart,int nEnd, long nCol = 2);
	virtual void Act_setHzEqualValue(int nStart,int nEnd,float fv, long nCol = 3);
	virtual void mousePressEvent(QMouseEvent *);

protected slots:
	virtual void slot_OnCellChanged(int row,int col);
	virtual void slot_TableShowMent(QPoint pos);
	virtual void slot_OnItemDoubleClicked(QTableWidgetItem *pItem);
};

class QInterharmonicsImp : public QBasicTestParaSetImp
{
	Q_OBJECT
public:
	QInterharmonicsImp(QWidget *parent = NULL);
	virtual ~QInterharmonicsImp();

	virtual void initUI(CSttTestResourceBase *pSttTestResource);
};

class QInterharmonicsWidget : public QBasicTestParaSet
{
	Q_OBJECT
public:
	tmt_harm_paras* m_pParas;

public:
	QInterharmonicsWidget(tmt_harm_paras* pParas, QWidget* pParent = NULL);
	virtual ~QInterharmonicsWidget();

public:
	virtual void showEvent(QShowEvent *);
};

#endif
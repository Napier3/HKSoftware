#ifndef QINTERHARMONICSWIDGET_H
#define QINTERHARMONICSWIDGET_H

#include "../Module/ChannelParaSet/QBasicTestParaSet.h"
#include "../../SttTest/Common/tmt_harm_test.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include <QWidget>

class QInterharmonicsChannelTable : public QChannelTable
{
	Q_OBJECT
public:
	QInterharmonicsChannelTable(MOUDLEType moudleType, CExBaseList *pChList,
		tmt_channel *pArrUI, QWidget *parent = NULL);

	QExBaseListCheckBoxDelegate *m_pCheckBoxDelegateBase;

	virtual ~QInterharmonicsChannelTable();

	virtual void initTable();
	virtual void UpdateTable();

	virtual void Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll=TRUE, long nCol = 1);
	virtual void Act_setPrasePValue(int nSwitch,int nOffset,float fv, long nCol = 2);
	virtual void Act_setPraseNValue(int nSwitch,int nOffset,float fv, long nCol = 2);
	virtual void Act_setPraseZValue(int nStart,int nEnd, long nCol = 2);
	virtual void Act_setHzEqualValue(int nStart,int nEnd,float fv, long nCol = 3);
	virtual void mousePressEvent(QMouseEvent *);

	void SetParaSetSecondValue(int nParaSetSecondValue);

signals:
	void sig_updataInterharmonicsChannelParas();//用于参数修改后发送信息更新


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

	QChannelTable *m_pVolChTable ;
	QChannelTable *m_pCurChTable ;
	virtual void initUI(CSttTestResourceBase *pSttTestResource);
	virtual void SetParaSetSecondValue(int nParaSetSecondValue);
};

class QInterharmonicsWidget : public QBasicTestParaSet
{
	Q_OBJECT
public:
	tmt_harm_paras* m_pParas;

	QInterharmonicsImp *m_pInterharmonicsImp;
	virtual void SetParaSetSecondValue(int nParaSetSecondValue);

public:
	QInterharmonicsWidget(tmt_harm_paras* pParas, QWidget* pParent = NULL);
	virtual ~QInterharmonicsWidget();
	void UpdataTableData();

signals:
	void sig_updataParas();

public slots:

	void slot_updataParas();

public:
	virtual void showEvent(QShowEvent *);
};

#endif
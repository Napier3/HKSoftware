#ifndef QASYNCWEEKTESTPARASET_H
#define QASYNCWEEKTESTPARASET_H

#include "QAsyncTestParaSetBase.h"
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>


class QAsyncWeekTestParaSet  : public QAsyncTestParaSetBase
{
	Q_OBJECT

public:
	QAsyncWeekTestParaSet(tmt_async_modules *pModules,QWidget *parent = 0);
	~QAsyncWeekTestParaSet(void);

	virtual void initUI();
	virtual void initData();
	virtual void setData(tmt_async_modules *pModules);
	virtual void UpdateModulesData(tmt_async_modules *pModules);
	virtual void UpdateTableData();

	virtual void startInit();
	virtual void stopInit();

	void IsTestInProgress( bool b );//是否为测试过程中


public:
	virtual void DCStateChanged(bool bDc);

public:

	QList<QAsyncChannelTable*> m_LeftChannelTableList;
	QList<QAsyncChannelTable*> m_RightChannelTableList;
	QList<QLabel*>m_ChTableLableList;//模块名称标签链表
	
	QScrollArea *m_pMainScrollArea;
	QWidget* m_pScrollWidget;
	QGridLayout *m_pGridLayout;//主布局
	QWidget *m_pMainWin;
	QVBoxLayout* m_pVScrollLayout;
	QHBoxLayout* m_pHLayout;

public slots:
	void slot_ChannelValueChanged();

signals:
	void sig_updataParas();

};

#endif
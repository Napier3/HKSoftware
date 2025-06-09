#pragma once

#include <QWidget>
#include "../../../../.././Module/SttTest/Common/tmt_common_def.h"
#include "QAsyncChannelTable.h"

class QAsyncTestParaSetBase : public QWidget
{
		Q_OBJECT

public:
	QAsyncTestParaSetBase(tmt_async_modules *pModules,QWidget *parent = 0);
	~QAsyncTestParaSetBase(void);

	virtual void initUI() = 0;
	virtual void initData() = 0;

	virtual void DCStateChanged(bool bDc);
	virtual void setData(tmt_async_modules *pModules);
	virtual void UpdateTableData() = 0;
	virtual void UpdateModulesData(tmt_async_modules *pModules);

	virtual void startInit() = 0;
	virtual void stopInit() = 0;

	virtual void setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC){}//valueFalg: 0:幅值 1：相位 2：频率
	
	//nMouleIndex:模块序号;		type：表格类型;	nChIndex:通道数量;		valueFalg: type 0:幅值 1：相位 2：频率
	virtual void setChannelTableItemValue(int nMouleIndex,MOUDLEType type,int nChIndex,float fstep,int valueFlag,int AddOrMinus,bool bDC){}

	virtual void setChannelTableItemValue(QAsyncChannelTable *pTable,CString strChName,float fstep,int valueFlag,int AddOrMinus,bool bDC);

	virtual void IsTestInProgress( bool b ){}//是否为测试过程中

public:
	tmt_async_modules *m_pAsyncModules;
	bool m_bDc;
};

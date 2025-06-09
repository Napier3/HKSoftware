#ifndef AnalogCirBreakerParaset_H
#define AnalogCirBreakerParaset_H

#include <QWidget>
#include "../Module/ChannelParaSet/channeltable.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../SttTest/Common/tmt_manu_test.h"
#include "../../SttTest/Common/tmt_common_def.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResourceBase.h"
#include "../Module/ChannelParaSet/QParaSetBase.h"

class AnalogCirBreakerParaset : public QParaSetBase
{
	Q_OBJECT

public:
	AnalogCirBreakerParaset(QWidget *parent = 0);
	~AnalogCirBreakerParaset();

	virtual void setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
		,tmt_channel *pArrUICUR,bool bDC = false);

	void setData(tmt_channel *pArrUICUR);
	virtual void setMaxMinAndEDVal(bool bCanUpdateTable=true);
	virtual void setIAmpMaxMinValue(bool bCanUpdateTable);
	virtual void setIAmpEDValue(float fIEDVal);
	virtual void startInit(bool bEnable=TRUE);
	virtual void stopInit(bool bEnable=TRUE);

public:
	void InitUI();
	virtual void initUI(CSttTestResourceBase *pSttTestResource);
	virtual void initData();
	virtual void Release();
	void setMacroType(int type){ m_MacroType = type;}
	tmt_channel *m_pArrUICUR;

	CSttTestResourceBase *m_pParaSetSttTestResource;
	plugin_type m_type;
	QList<QChannelTable *> m_ICHannelTableList;
	int m_MacroType;
	bool m_bDC;

	QGroupBox *m_pIGroupBox;
	QHBoxLayout *m_pMainHBoxLayout;
	QScrollArea *m_pIScrollArea;
	QWidget *m_pIWidget;
	QGridLayout *m_pIGridLayout;

public:
	void UpdateTables();
	void UpdateValidTableDatas();

signals:
	void sig_updataParas(int channelNum,int valueFlag,float datavalue);

protected slots:
	void slot_ChannelValueChanged(MOUDLEType moudleType,int channelNum,int valueFlag,float datavalue);//valueFlag=（1:幅值 2:相位 3:频率）

};
#endif 

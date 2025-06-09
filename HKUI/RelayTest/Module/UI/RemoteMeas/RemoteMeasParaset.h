#ifndef REMOTEMEASPARASET_H
#define REMOTEMEASPARASET_H

#include <QWidget>
#include <QStringList>
#include <QDate>
#include "../Module/ChannelParaSet/channeltable.h"
#include "QRemoteMeasTable.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../SttTest/Common/tmt_manu_test.h"
#include "../../SttTest/Common/tmt_common_def.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResourceBase.h"

#include <QGridLayout>
#include <QScrollArea>

class RemoteMeasParaSet : public QWidget
{
	Q_OBJECT

public:
	RemoteMeasParaSet(QWidget *parent = 0);
	~RemoteMeasParaSet();

	virtual void setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
		,tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR,bool bDC = false);

	void setData(tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR);
	void setMaxMinAndEDVal();
	void setUAmpMaxMinValue();
	void setIAmpMaxMinValue();
	virtual void setUAmpEDValue(float fUEDVal);
	virtual void setIAmpEDValue(float fIEDVal);

public:
	virtual void initUI(CSttTestResourceBase *pSttTestResource);
	void initData();
	void Release();
	void setMacroType(int type){ m_MacroType = type;}
	tmt_channel *m_pArrUIVOL;
	tmt_channel *m_pArrUICUR;

	CSttTestResourceBase *m_pParaSetSttTestResource;
	plugin_type m_type;
	QList<QChannelTable *> m_UCHannelTableList;
	QList<QChannelTable *> m_ICHannelTableList;
	QList<QRemoteMeasTable *> m_RemoteMeasTableList;
	int m_MacroType;
	bool m_bDC;


	QGridLayout* m_pMainGridLayout;
	QGridLayout *m_pUVGridLayout;
	QGridLayout *m_pIVGridLayout;
	QGridLayout *m_pRemoteMeasGridLayout;

	QWidget *m_pUWidget;
	QWidget *m_pIWidget;
	QWidget *m_pRemoteMeasWidget;
	QScrollArea *m_pUScrollArea;
	QScrollArea *m_pIScrollArea;
	QScrollArea *m_pRemoteMeasScrollArea;

public:
	void UpdateTables();
	void UpdateValidTableDatas();
	void Send_UpdataParas();
	virtual void startInit(bool bEnable=TRUE);
	virtual void stopInit(bool bEnable=TRUE);
	virtual void setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus);

signals:
	void sig_updataParas();
	void sig_ChannelAmpValueChanged(int nIndex,float fValue);

protected slots:
	void slot_ChannelValueChanged(MOUDLEType moudleType,int channelNum,int valueFlag,float datavalue);//valueFlag=（1:幅值 2:相位 3:频率）
	void slot_ChannelRemoteValueChanged(int channelNum,int valueFlag,float datavalue);//valueFlag=（1:幅值 2:相位 3:频率）

};
#endif // TELEMETERPARASET_H

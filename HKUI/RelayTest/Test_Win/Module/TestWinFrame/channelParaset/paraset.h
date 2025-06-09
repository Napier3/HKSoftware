#ifndef PARASETOFSTATUS_H
#define PARASETOFSTATUS_H

#include <QWidget>
#include <QStringList>
#include <QDate>
#include "channeltable.h"
#include "channellowstable.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../../../../SttStudio/Module/SttTest/Common/tmt_common_def.h"
#include "../../../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"

class ParaSet : public QWidget
{
	Q_OBJECT

public:
	ParaSet(QWidget *parent = 0);
	~ParaSet();

	virtual void setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
		,tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR);

	virtual void startInit(bool bEnable=TRUE);
	virtual void stopInit(bool bEnable=TRUE);

	void DCStateChanged(int type,bool bdc);
	void setDispMode(int dispmode);

	void setData(tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR);
	void setMaxMinAndEDVal();
	void setUAmpMaxMinValue();
	void setUAmpEDValue(float fUEDVal);
	void setIAmpMaxMinValue();
	void setIAmpEDValue(float fIEDVal);

	void setUAmpMaxMinValueZero(float fmax,float fmin);
	void setIAmpMaxMinValueZero(float fmax,float fmin);

	bool isDigital()	{  return m_type == P_Digit;  }
	bool isAnalog()		{  return m_type == P_Analog;	}
	bool isLowSignal()	{  return m_type == P_LowSignal;  }
	bool isCommon()		{  return m_type == P_Common;	}

	void setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC);//valueFalg: 0:幅值 1：相位 2：频率

signals:
	void sig_AddLog(LogLevel level, QString str);
	void sig_updataParas();

public:
	virtual void initUI(CSttTestResourceBase *pSttTestResource);
	void initData();
	void Release();
	tmt_channel *m_pArrUIVOL;
	tmt_channel *m_pArrUICUR;

	plugin_type m_type;	
// 	int *m_pUModuleNum;		
// 	int *m_pIModuleNum;		
// 	QList<int> *m_pUModultChannelNumList;
// 	QList<int> *m_pIModultChannelNumList;
	CSttTestResourceBase *m_pSttTestResource;
	QList<CHannelTable *> m_UCHannelTableList;
	QList<CHannelTable *> m_ICHannelTableList;
	int m_dispMode;	//V_Primary:显示一次值；V_Secondary:显示二次值

	QGridLayout* m_pMainGridLayout;
	QGridLayout *m_pUVGridLayout;
	QGridLayout *m_pIVGridLayout;

	QWidget *m_pUWidget;
	QWidget *m_pIWidget;
	QScrollArea *m_pUScrollArea;
	QScrollArea *m_pIScrollArea;

protected slots:
	void slot_ChannelValueChanged(MOUDLEType moudleType,/*int moudleID,*/int channelNum,int valueFlag,float datavalue);//valueFlag=（1:幅值 2:相位 3:频率）
};

#endif // PARASETOFSTATUS_H

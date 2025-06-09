#ifndef PARASETOFSTATUS_H
#define PARASETOFSTATUS_H

#include <QWidget>
#include <QStringList>
#include <QDate>
#include "channeltable.h"
#include "channellowstable.h"
#include "channelharmtable.h"
#include "../../CommonMethod/commonMethod.h"
#include "../../../../../SttStudio/Module/SttTest/Common/tmt_common_def.h"
#include "../../../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"

class QParaSetBase : public QWidget
{
	Q_OBJECT

public:
	QParaSetBase(QWidget *parent = 0);
	~QParaSetBase();

	virtual void setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
		,tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR,bool bDC = false);

	virtual void startInit(bool bEnable=TRUE);
	virtual void stopInit(bool bEnable=TRUE);

	
	void setData(tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR);
	void setMaxMinAndEDVal();
	void setMacroType(int type){ m_MacroType = type;}
	virtual void setUAmpMaxMinValue(){}
	virtual void setUAmpEDValue(float fUEDVal){}
	virtual void setIAmpMaxMinValue(){}
	virtual void setIAmpEDValue(float fIEDVal){}

	virtual void setUAmpMaxMinValueZero(float fmax,float fmin){}
	virtual void setIAmpMaxMinValueZero(float fmax,float fmin){}

	bool isDigital()	{  return m_type == P_Digit;  }
	bool isAnalog()		{  return m_type == P_Analog;	}
	bool isLowSignal()	{  return m_type == P_LowSignal;  }
	bool isCommon()		{  return m_type == P_Common;	}
	bool isHarm()		{  return m_type == P_Harm; }

	virtual void setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC){}//valueFalg: 0:幅值 1：相位 2：频率
	virtual void keyPressEvent(QKeyEvent *event){}

signals:
	void sig_AddLog(LogLevel level, QString str);
	void sig_updataParas();

public:
	virtual void initUI(CSttTestResourceBase *pSttTestResource);
	virtual void initData(){}
	virtual void UpdateVolChsTable(){}//zhouhj 2023.8.9 只更新电压通道表格
	virtual void Release(){}
	tmt_channel *m_pArrUIVOL;
	tmt_channel *m_pArrUICUR;

	int m_MacroType; //测试功能类型 0:通用  1:状态序列
	plugin_type m_type;	
	CSttTestResourceBase *m_pSttTestResource;
	int m_dispMode;	//V_Primary:显示一次值；V_Secondary:显示二次值
	bool m_bDC;

protected slots:
	void slot_ChannelValueChanged(MOUDLEType moudleType,/*int moudleID,*/int channelNum,int valueFlag,float datavalue);//valueFlag=（1:幅值 2:相位 3:频率）
};

#endif // PARASETOFSTATUS_H

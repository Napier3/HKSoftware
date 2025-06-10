#ifndef PARASETBASE_H
#define PARASETBASE_H

#include <QWidget>
#include <QStringList>
#include "channeltable.h"
#include "channelharmtable.h"

class QParaSetBase : public QWidget
{
	Q_OBJECT

public:
	QParaSetBase(QWidget *parent = 0);
	~QParaSetBase();

	virtual void setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
		,tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR,bool bDC = false);
	void setData(tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR);
	void setMacroType(int type){ m_MacroType = type;}

	virtual void startInit(bool bEnable=TRUE);
	virtual void stopInit(bool bEnable=TRUE);

	void setMaxMinAndEDVal();
	virtual void setUAmpMaxMinValue(){}
	virtual void setUAmpEDValue(float fUEDVal){}
	virtual void setIAmpMaxMinValue(){}
	virtual void setIAmpEDValue(float fIEDVal){}

	bool isCommon()		{  return m_type == P_Common; }
	bool isWeekSignal()		{  return m_type == P_LowSignal;  }
	bool isHarm()		{  return m_type == P_Harm; }

	virtual void setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC){}//valueFalg: 0:��ֵ 1����λ 2��Ƶ��

// signals:
// 	void sig_updataParas();

public:
	virtual void initUI(CSttTestResourceBase *pSttTestResource);
	virtual void initData(){}
	virtual void Release(){}
	tmt_channel *m_pArrUIVOL;
	tmt_channel *m_pArrUICUR;

	int m_MacroType; //���Թ������� 0:ͨ��  1:״̬����  2:ͨ��г������
	plugin_type m_type;	
	bool m_bDC;
	CSttTestResourceBase *m_pParaSetSttTestResource;

protected slots:
	void slot_ChannelValueChanged(MOUDLEType moudleType,int channelNum,int valueFlag,float datavalue);//valueFlag=��1:��ֵ 2:��λ 3:Ƶ�ʣ�
};

#endif // PARASETBASE_H

#ifndef CSTTPOWERCTRLBASE_H
#define CSTTPOWERCTRLBASE_H

class CSttPowerCtrlBase
{
public:
	CSttPowerCtrlBase();

	//��ѹģ��߱����440����λ������ѹģ�麬����ѹ��,Ŀǰ��PTU100 PTU100B���л�����ʱ��ֹͣ���
	//��ѹģʽ���ֶ�ʵ�飬ֻ�ܳ�����������ջ����ڣ�CSttDeviceBase::AutoControl_PTU()����
	BOOL m_bVolt_440V;

	//ģ��ķŴ���������ֵ�����ڵ�ѹģ�鼴����ѹ��ʱ�ı�����ֵ
	float m_fMaxVal;//��Ӧģ��У׼m_oModuleAttr.m_fChMax
	float m_fMaxVal_DC;//��Ӧģ��У׼m_oModuleAttr.m_fChDcMax

	//��ѹģ����ѹ��ı�����ֵ
	float m_fMaxVal2;//PTU100:440��PTU100B:380

	unsigned long m_nDA;//�˿ڵ�ѹ

	//Volt
    virtual void SetVoltDA(float fVout, BOOL bIsDc){}
    virtual void SetVoltDA_State(){}
	virtual void SetVoltDA_DC_300V(float fVout);

	//Current
	virtual void SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc=FALSE){}
	virtual void SetCurrentDA_State(int nModuleIndex){}
	void GetCurrentPowerMode(int nModuleIndex,int &nPowerMode,float &fVset);
	void GetCurrentPowerMode_UI(int nModuleIndex,int &nPowerMode,float &fVset);
	unsigned long GetModuleDA(){return m_nDA;}
};
#endif // CSTTPOWERCTRLBASE_H

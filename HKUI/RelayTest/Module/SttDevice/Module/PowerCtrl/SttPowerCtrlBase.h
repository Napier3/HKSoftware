#ifndef CSTTPOWERCTRLBASE_H
#define CSTTPOWERCTRLBASE_H

class CSttPowerCtrlBase
{
public:
	CSttPowerCtrlBase();

	//电压模块具备输出440伏档位，即电压模块含有升压器,目前仅PTU100 PTU100B。切换动作时需停止输出
	//升压模式限手动实验，只能出交流量。需闭环调节，CSttDeviceBase::AutoControl_PTU()重载
	BOOL m_bVolt_440V;

	//模块的放大器标称最大值，对于电压模块即无升压器时的标称最大值
	float m_fMaxVal;//对应模块校准m_oModuleAttr.m_fChMax
	float m_fMaxVal_DC;//对应模块校准m_oModuleAttr.m_fChDcMax

	//电压模块升压后的标称最大值
	float m_fMaxVal2;//PTU100:440或PTU100B:380

	unsigned long m_nDA;//端口电压

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

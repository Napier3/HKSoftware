#pragma once

#include "../../SttTestBase/SttTestBase.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/Module/Driver466/SttDeviceComm.h"
#endif

typedef struct
{
	unsigned int tirpType;	// 触发类型，0-手动，1-开入
	DrvBITrip biTrip;	// 开入触发参数
} Drv_BinMeas;

class CSttBinMeasure : public CSttTestBase
{
public:
	CSttBinMeasure(void);
	virtual ~CSttBinMeasure(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
		return new CSttBinMeasure;
	}
public:
	virtual void Init();
	virtual long SetParameter(DWORD dwState=0);
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void StartTest();
	virtual void Stop();
#ifdef _PSX_QT_LINUX_
	Drv_BinarySetting m_oBinSetting;
#endif
};

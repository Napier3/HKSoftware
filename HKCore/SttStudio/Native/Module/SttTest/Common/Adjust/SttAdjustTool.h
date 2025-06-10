#pragma once

#include"tmt_adjust_test.h"

#define SWITCH_U_0   243
#define SWITCH_U_1   247
#define SWITCH_U_2   251
#define SWITCH_U_3   242
#define SWITCH_U_4   246
#define SWITCH_U_5   250

#define SWITCH_I_0   241
#define SWITCH_I_1   245
#define SWITCH_I_2   249
#define SWITCH_I_3   240
#define SWITCH_I_4   244
#define SWITCH_I_5   248

#define SWITCH_GROUP_1   255
#define SWITCH_GROUP_2   254

class CSttAdjustTool
{
public:
    CSttAdjustTool();
    virtual ~CSttAdjustTool(void);

public:
	BOOL Adjust(const CString &strMacroID, CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport );
	int m_nSwitchCtrl;//开关量切换装置控制字
	CString Adjust_GetSwitch(int nSwitchCtrl);

	BYTE *m_pszAdjSysPara;
	long m_nDestLen;
protected:
	void Adjust_SetMeasGear(CSttXmlSerializeBase *pMacroParas);
	BOOL Adjust_One(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport );
	BOOL Adjust_Three(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport );
	BOOL Adjust_One2Points(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport );
	BOOL Adjust_OneAngle(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport );
	BOOL Adjust_OneFreq(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport );
	BOOL Adjust_OneDcZero(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport );
	void Adjust_Switch(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport );
	void Adjust_ReadModuleFlash(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport );
	void Adjust_WriteModuleFlash(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport );
	void Adjust_OneCopy(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport );
};

extern CSttAdjustTool g_theSttAdjustTool;

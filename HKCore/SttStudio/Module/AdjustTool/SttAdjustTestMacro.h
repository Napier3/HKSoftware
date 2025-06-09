//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttAdjustTestMacro.h  CSttAdjustTestMacro

#pragma once

#include "SttAdjBase.h"
#include "..\..\..\Module\TestMacro\TestMacros.h"

#define STT_ADJUST_MACRO_ID_ModuleOutput		_T("ModuleOutput")
#define STT_ADJUST_MACRO_ID_SetChannelMap	_T("SetChannelMap")
#define STT_ADJUST_MACRO_ID_AdjustThree		_T("AdjustThree")
#define STT_ADJUST_MACRO_ID_AdjustOne		_T("AdjustOne")
#define STT_ADJUST_MACRO_ID_AdjustSwitch		_T("AdjustSwitch")
#define STT_TEST_MACROID_BinaryOutput     _T("BinaryOutput")
#define STT_TEST_MACROID_BinaryExOutput      _T("BinaryExOutput")
#define STT_TEST_MACROID_SttSystemConfig     _T("SystemConfig")
#define STT_ADJUST_MACRO_ID_AdjustReboot		_T("AdjustReboot")
#define STT_ADJUST_MACRO_ID_FPGAUPDATE        _T("UpdateFPGA")//用于FPGA更新
#define STT_ADJUST_MACRO_ID_GetUTCTime        _T("GetUTCTime")
#define STT_ADJUST_MACRO_ID_SetUTCTime        _T("SetUTCTime")//2023-3-22 Zhouyy 增加用于修改UTC时间
#define STT_ADJUST_MACRO_ID_ReadModuleFlash	_T("ReadModuleFlash")//2023/10/7 wjs 添加读写系数
#define STT_ADJUST_MACRO_ID_WriteModuleFlash	_T("WriteModuleFlash")


//2021-9-22  lijunqing  增加的测试功能，此处没有使用测试功能的ID  tmt_adjust_test.h
#define STT_ADJUST_MACRO_ID_AdjustOne2Points   "AdjustOne2Points"
#define STT_ADJUST_MACRO_ID_AdjustOneAngle	   "AdjustOneAngle"
#define STT_ADJUST_MACRO_ID_AdjustOneFreq	   "AdjustOneFreq"
#define STT_ADJUST_MACRO_ID_AdjustOneDcZero	   "AdjustOneDcZero"
#define STT_ADJUST_MACRO_ID_SetMeasGear		   "SetMeasGear"   //zhouhj 20211210  增加用于设置采集档位


// #define STT_ADJ_ID_ModuleType			_T("ModuleType")
// #define STT_ADJ_ID_ModuleIndex			_T("ModuleIndex")
// #define STT_ADJ_ID_FreqIndex			_T("FreqIndex")
// #define STT_ADJ_ID_FreqSel			_T("FreqSel")
#define STT_ADJ_ID_TempretureID			_T("TempretureID")
#define STT_ADJ_ID_GearID			_T("GearID")
#define STT_ADJ_ID_Channel			_T("Channel")
#define STT_ADJ_ID_Mag			_T("Mag")
#define STT_ADJ_ID_Ang			_T("Ang")
#define STT_ADJ_ID_Freq			_T("Freq")
#define STT_ADJ_ID_Channel1		_T("Channel1")
#define STT_ADJ_ID_Mag1			_T("Mag1")
#define STT_ADJ_ID_Ang1			_T("Ang1")
#define STT_ADJ_ID_Freq1			_T("Freq1")
#define STT_ADJ_ID_Channel2			_T("Channel2")
#define STT_ADJ_ID_Mag2			_T("Mag2")
#define STT_ADJ_ID_Ang2			_T("Ang2")
#define STT_ADJ_ID_Freq2			_T("Freq2")
#define STT_ADJ_ID_Channel3		_T("Channel3")
#define STT_ADJ_ID_Mag3			_T("Mag3")
#define STT_ADJ_ID_Ang3			_T("Ang3")
#define STT_ADJ_ID_Freq3			_T("Freq3")

#define STT_ADJ_ID_Point1RefMag			_T("OutValue1")
#define STT_ADJ_ID_Point2RefMag			_T("OutValue2")
#define STT_ADJ_ID_Point1MeasMag			_T("MeasValue1")
#define STT_ADJ_ID_Point2MeasMag			_T("MeasValue2")
#define STT_ADJ_ID_Deviation			_T("Deviation")
#define STT_ADJ_ID_RefFreq			_T("OutValue")
#define STT_ADJ_ID_MeasValue			_T("MeasValue")
#define STT_ADJ_ID_MeasFreq			STT_ADJ_ID_MeasValue
#define STT_ADJ_ID_MeasDcZero		STT_ADJ_ID_MeasValue
#define STT_ADJ_ID_MeasAng			STT_ADJ_ID_MeasValue
#define STT_ADJ_ID_OutMag			_T("OutMag")


class CSttAdjTest_Base : public CSttAdjBase
{
public:
	CSttAdjTest_Base();
	virtual ~CSttAdjTest_Base();

public:
	CTestMacro *m_pTestMacro;

	CDataGroup *m_pFaultParas;
	CDataGroup *m_pResults;

public:
	virtual void SetTestMacro(CTestMacro *pTestMacro);
	virtual void WriteParasFile();
	virtual void ResetParas();
};

//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_MacroBase
class CSttAdjTest_MacroBase : public CSttAdjTest_Base
{
public:
	CSttAdjTest_MacroBase();
	virtual ~CSttAdjTest_MacroBase();

	virtual void SetTestMacro(CTestMacro *pTestMacro);

public:
	CDvmData *m_pModuleType;
	CDvmData *m_pModuleIndex;
	CDvmData *m_pTempretureID;
	CDvmData *m_pFreqSel;
	CDvmData *m_pGearID;
	CDvmData *m_pDeviation;
};

//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustOne
class CSttAdjTest_AdjustOne : public CSttAdjTest_MacroBase
{
public:
	CSttAdjTest_AdjustOne();
	virtual ~CSttAdjTest_AdjustOne();

	virtual void SetTestMacro(CTestMacro *pTestMacro);

public:
	CDvmData *m_pChannel;
	CDvmData *m_pMag;
	CDvmData *m_pAng;
	CDvmData *m_pFreq;
};

//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustThree
class CSttAdjTest_AdjustThree : public CSttAdjTest_MacroBase
{
public:
	CSttAdjTest_AdjustThree();
	virtual ~CSttAdjTest_AdjustThree();

	virtual void SetTestMacro(CTestMacro *pTestMacro);

public:
	CDvmData *m_pChannel1;
	CDvmData *m_pMag1;
	CDvmData *m_pAng1;
	CDvmData *m_pFreq1;
	CDvmData *m_pChannel2;
	CDvmData *m_pMag2;
	CDvmData *m_pAng2;
	CDvmData *m_pFreq2;
	CDvmData *m_pChannel3;
	CDvmData *m_pMag3;
	CDvmData *m_pAng3;
	CDvmData *m_pFreq3;
};


//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustOne2Points
class CSttAdjTest_AdjustOne2Points : public CSttAdjTest_MacroBase
{
public:
	CSttAdjTest_AdjustOne2Points();
	virtual ~CSttAdjTest_AdjustOne2Points();

	virtual void SetTestMacro(CTestMacro *pTestMacro);

public:
	CDvmData *m_pChannel;
	CDvmData *m_pPoint1RefMag;
	CDvmData *m_pPoint1MeasMag;
	CDvmData *m_pPoint2RefMag;
	CDvmData *m_pPoint2MeasMag;
};


//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustOneAngle
class CSttAdjTest_AdjustOneAngle : public CSttAdjTest_MacroBase
{
public:
	CSttAdjTest_AdjustOneAngle();
	virtual ~CSttAdjTest_AdjustOneAngle();

	virtual void SetTestMacro(CTestMacro *pTestMacro);

public:
	CDvmData *m_pChannel;
	CDvmData *m_pOutMag;
	CDvmData *m_pMeasAng;
};


//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustOneFreq
class CSttAdjTest_AdjustOneFreq : public CSttAdjTest_MacroBase
{
public:
	CSttAdjTest_AdjustOneFreq();
	virtual ~CSttAdjTest_AdjustOneFreq();

	virtual void SetTestMacro(CTestMacro *pTestMacro);

public:
	CDvmData *m_pRefFreq;
	CDvmData *m_pMeasFreq;
};


//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustOneDcZero
class CSttAdjTest_AdjustOneDcZero : public CSttAdjTest_MacroBase
{
public:
	CSttAdjTest_AdjustOneDcZero();
	virtual ~CSttAdjTest_AdjustOneDcZero();

	virtual void SetTestMacro(CTestMacro *pTestMacro);

public:
	CDvmData *m_pChannel;
	CDvmData *m_pMeasDcZero;
};

//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_ModuleOutput
class CSttAdjTest_ModuleOutput : public CSttAdjTest_Base
{
public:
	CSttAdjTest_ModuleOutput();
	virtual ~CSttAdjTest_ModuleOutput();

	virtual void SetTestMacro(CTestMacro *pTestMacro);

public:
	CDvmData *m_pModuleType;
	CDvmData *m_pModuleIndex;
	CDvmData *m_pTempretureID;
	CDvmData *m_pFreqIndex;
	CDvmData m_oFreqValue;

	//2021-9-24  lijunqing
	CExBaseList m_listGroupChannels;

public:
	//2021-9-26  lijunqing
	void FreqValueToIndex();
	void FreqIndexToValue();

	//2022-2-9  lijunqing  
	void SetChannelCount(long nChannelCount);

};

class CSttAdjTest_AdjustSwitch : public CSttAdjTest_Base
{
public:
	CSttAdjTest_AdjustSwitch();
	virtual ~CSttAdjTest_AdjustSwitch();

	virtual void SetTestMacro(CTestMacro *pTestMacro);

public:
	CDvmData *m_pModuleType;
	CDvmData *m_pModuleIndex;
	CDvmData *m_pSwitchMode;
};

void stt_test_set_data_value(CDvmData *pSrc, CDvmData *pDest);

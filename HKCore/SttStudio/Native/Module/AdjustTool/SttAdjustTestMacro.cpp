//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttAdjustTestMacro.cpp  CSttAdjustTestMacro


#include "stdafx.h"
#include "SttAdjustTestMacro.h"

#include "..\..\..\Module\API\FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void stt_test_set_data_value(CDvmData *pSrc, CDvmData *pDest)
{
	if (pSrc == NULL || pDest == NULL)
	{
		return;
	}

	pDest->m_strValue = pSrc->m_strValue;
}

CSttAdjTest_Base::CSttAdjTest_Base()
{
	m_pTestMacro = NULL;
	m_pFaultParas = new CDataGroup();
	m_pResults = new CDataGroup();
}

CSttAdjTest_Base::~CSttAdjTest_Base()
{
	delete m_pFaultParas;
	delete m_pResults;
}

void CSttAdjTest_Base::SetTestMacro(CTestMacro *pTestMacro)
{
	m_pTestMacro = pTestMacro;
	m_pTestMacro->GetTestMacroParas(m_pFaultParas, m_pResults);
}

void CSttAdjTest_Base::WriteParasFile()
{
	CString strFile;
	strFile = _P_GetBinPath();
	strFile += m_pTestMacro->m_strID;
	strFile += _T(".xml");
	m_pFaultParas->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CSttAdjTest_Base::ResetParas()
{
	m_pFaultParas->ResetDatas();
}

//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustOne
CSttAdjTest_MacroBase::CSttAdjTest_MacroBase()
{
	m_pModuleType = NULL;
	m_pModuleIndex = NULL;
	m_pTempretureID = NULL;
	m_pFreqSel = NULL;
	m_pGearID = NULL;
}

CSttAdjTest_MacroBase::~CSttAdjTest_MacroBase()
{

}

void CSttAdjTest_MacroBase::SetTestMacro(CTestMacro *pTestMacro)
{
	CSttAdjTest_Base::SetTestMacro(pTestMacro);

	m_pModuleType		= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_ModuleType);
	m_pModuleIndex		= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_ModuleIndex);
	m_pTempretureID	= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_TempretureID);
	m_pFreqSel				= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_FreqSel);
	m_pGearID				= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_GearID);
	m_pDeviation			= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Deviation);
}

//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustOne
CSttAdjTest_AdjustOne::CSttAdjTest_AdjustOne()
{
	m_pModuleType = NULL;
	m_pModuleIndex = NULL;
	m_pTempretureID = NULL;
	m_pChannel = NULL;
	m_pFreqSel = NULL;
	m_pGearID = NULL;
	m_pMag = NULL;
	m_pAng = NULL;
	m_pFreq = NULL;
}

CSttAdjTest_AdjustOne::~CSttAdjTest_AdjustOne()
{

}

void CSttAdjTest_AdjustOne::SetTestMacro(CTestMacro *pTestMacro)
{
	CSttAdjTest_MacroBase::SetTestMacro(pTestMacro);

// 	m_pModuleType		= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_ModuleType);
// 	m_pModuleIndex		= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_ModuleIndex);
// 	m_pTempretureID	= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_TempretureID);
// 	m_pFreqSel				= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_FreqSel);
// 	m_pGearID				= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_GearID);
	m_pChannel			= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Channel);
	m_pMag					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Mag);
	m_pAng					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Ang);
	m_pFreq					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Freq);
}

//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustThree
CSttAdjTest_AdjustThree::CSttAdjTest_AdjustThree()
{
// 	m_pModuleType = NULL;
// 	m_pModuleIndex = NULL;
// 	m_pTempretureID = NULL;
// 	m_pFreqSel = NULL;
// 	m_pGearID = NULL;
	m_pChannel1 = NULL;
	m_pMag1 = NULL;
	m_pAng1 = NULL;
	m_pFreq1 = NULL;
	m_pChannel2 = NULL;
	m_pMag2 = NULL;
	m_pAng2 = NULL;
	m_pFreq2 = NULL;
	m_pChannel3 = NULL;
	m_pMag3 = NULL;
	m_pAng3 = NULL;
	m_pFreq3 = NULL;
}

CSttAdjTest_AdjustThree::~CSttAdjTest_AdjustThree()
{

}

void CSttAdjTest_AdjustThree::SetTestMacro(CTestMacro *pTestMacro)
{
	CSttAdjTest_MacroBase::SetTestMacro(pTestMacro);

// 	m_pModuleType		= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_ModuleType);
// 	m_pModuleIndex		= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_ModuleIndex);
// 	m_pTempretureID	= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_TempretureID);
// 	m_pFreqSel				= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_FreqSel);
// 	m_pGearID				= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_GearID);
	m_pChannel1			= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Channel1);
	m_pMag1					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Mag1);
	m_pAng1					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Ang1);
	m_pFreq1				= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Freq1);
	m_pChannel2			= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Channel2);
	m_pMag2					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Mag2);
	m_pAng2					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Ang2);
	m_pFreq2				= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Freq2);
	m_pChannel3			= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Channel3);
	m_pMag3					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Mag3);
	m_pAng3					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Ang3);
	m_pFreq3				= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Freq3);
}

//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustOne2Points
CSttAdjTest_AdjustOne2Points::CSttAdjTest_AdjustOne2Points()
{
	m_pChannel = NULL;
	m_pPoint1RefMag = NULL;
	m_pPoint2RefMag = NULL;
	m_pPoint1MeasMag = NULL;
	m_pPoint2MeasMag = NULL;
}

CSttAdjTest_AdjustOne2Points::~CSttAdjTest_AdjustOne2Points()
{

}

void CSttAdjTest_AdjustOne2Points::SetTestMacro(CTestMacro *pTestMacro)
{
	CSttAdjTest_MacroBase::SetTestMacro(pTestMacro);

	m_pChannel			= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Channel);
	m_pPoint1RefMag					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Point1RefMag);
	m_pPoint2RefMag					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Point2RefMag);
	m_pPoint1MeasMag				= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Point1MeasMag);
	m_pPoint2MeasMag			= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Point2MeasMag);
}

//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustOneAngle
CSttAdjTest_AdjustOneAngle::CSttAdjTest_AdjustOneAngle()
{
	m_pChannel = NULL;
	m_pMeasAng = NULL;
}

CSttAdjTest_AdjustOneAngle::~CSttAdjTest_AdjustOneAngle()
{

}

void CSttAdjTest_AdjustOneAngle::SetTestMacro(CTestMacro *pTestMacro)
{
	CSttAdjTest_MacroBase::SetTestMacro(pTestMacro);

	m_pChannel			= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Channel);
	m_pOutMag					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_OutMag);
	m_pMeasAng					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_MeasAng);
}


//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustOneFreq
CSttAdjTest_AdjustOneFreq::CSttAdjTest_AdjustOneFreq()
{
	m_pRefFreq = NULL;
	m_pMeasFreq = NULL;
}

CSttAdjTest_AdjustOneFreq::~CSttAdjTest_AdjustOneFreq()
{

}

void CSttAdjTest_AdjustOneFreq::SetTestMacro(CTestMacro *pTestMacro)
{
	CSttAdjTest_MacroBase::SetTestMacro(pTestMacro);

	m_pRefFreq			= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_RefFreq);
	m_pMeasFreq					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_MeasFreq);
}


//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustOneDcZero
CSttAdjTest_AdjustOneDcZero::CSttAdjTest_AdjustOneDcZero()
{
	m_pChannel = NULL;
	m_pMeasDcZero = NULL;
}

CSttAdjTest_AdjustOneDcZero::~CSttAdjTest_AdjustOneDcZero()
{

}

void CSttAdjTest_AdjustOneDcZero::SetTestMacro(CTestMacro *pTestMacro)
{
	CSttAdjTest_MacroBase::SetTestMacro(pTestMacro);

	m_pChannel			= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_Channel);
	m_pMeasDcZero					= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_MeasDcZero);
}

//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_ModuleOutput
CSttAdjTest_ModuleOutput::CSttAdjTest_ModuleOutput()
{

}

CSttAdjTest_ModuleOutput::~CSttAdjTest_ModuleOutput()
{
	m_listGroupChannels.RemoveAll();
}

void CSttAdjTest_ModuleOutput::SetTestMacro(CTestMacro *pTestMacro)
{
	CSttAdjTest_Base::SetTestMacro(pTestMacro);

	m_pModuleType		= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_ModuleType);
	m_pModuleIndex		= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_ModuleIndex);
	m_pFreqIndex		= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_FreqIndex);

	//2021-9-24  lijunqing
	m_pFaultParas->FindByDataType(STT_ADJ_DATA_TYPE_Channel, m_listGroupChannels);

	ASSERT (m_pFreqIndex != NULL);

	if (m_pFreqIndex != NULL)
	{
		m_pFreqIndex->Copy(&m_oFreqValue);
		FreqIndexToValue();
	}
}

//2021-9-26  lijunqing
void CSttAdjTest_ModuleOutput::FreqValueToIndex()
{
	ASSERT (m_pFreqIndex != NULL);

	if (m_pFreqIndex == NULL)
	{
		return;
	}

	double fValue = CString_To_double(m_oFreqValue.m_strValue);
	fValue = fValue / 50;
	long nIndex = (long)fValue;

	if (fValue - nIndex * 50  > 0.4)
	{
		nIndex++;
	}

	m_pFreqIndex->m_strValue.Format(_T("%d"), nIndex);
}

void CSttAdjTest_ModuleOutput::FreqIndexToValue()
{
	ASSERT (m_pFreqIndex != NULL);

	if (m_pFreqIndex == NULL)
	{
		return;
	}

	long nValue = CString_To_long(m_pFreqIndex->m_strValue);
	m_oFreqValue.m_strValue.Format(_T("%d"), nValue*50);
}

void CSttAdjTest_ModuleOutput::SetChannelCount(long nChannelCount)
{
	if (nChannelCount <= 0)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("ChannelCount == 0"));
		return;
	}

	long nCount = m_listGroupChannels.GetCount();
	long nIndex = 0;
	CExBaseObject *p = NULL;

	if (nCount == nChannelCount)
	{
		return;
	}

	//删除多余的通道
	if (nCount > nChannelCount)
	{
		nCount = nCount - nChannelCount;

		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			p = m_listGroupChannels.GetAtIndex(nChannelCount);
			m_listGroupChannels.Delete(p);
			m_pFaultParas->Remove(p);
		}

		return;
	}

	//增加通道
	CDataGroup *pChannel = (CDataGroup*)m_listGroupChannels.GetHead();
	CDataGroup *pNew = NULL;

	if (pChannel == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Test Macro [ModuleOutput] Error"));
		return;
	}

	for (nIndex=nCount; nIndex<nChannelCount; nIndex++)
	{
		pNew = (CDataGroup*)pChannel->Clone();
		pNew->m_strName.Format(_T("通道%d"), nIndex+1);
		pNew->m_strID.Format(_T("Ch%d"), nIndex);
		m_listGroupChannels.AddTail(pNew);
		m_pFaultParas->AddNewChild(pNew);
	}
}

//////////////////////////////////////////////////////////////////////////
//CSttAdjTest_AdjustSwitch
CSttAdjTest_AdjustSwitch::CSttAdjTest_AdjustSwitch()
{
	
}

CSttAdjTest_AdjustSwitch::~CSttAdjTest_AdjustSwitch()
{

}

void CSttAdjTest_AdjustSwitch::SetTestMacro(CTestMacro *pTestMacro)
{
	CSttAdjTest_Base::SetTestMacro(pTestMacro);

	m_pModuleType		= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_ModuleType);
	m_pModuleIndex		= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_ModuleIndex);
	m_pSwitchMode		= (CDvmData*)m_pFaultParas->FindByID(STT_ADJ_ID_SwitchMode);
}

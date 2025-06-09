// CalFunctions.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CALFUNIONS_H_)
#define _CALFUNIONS_H_

#include "RecordDefine.h"
#include "DFT\DFT.h"
#include "CalFilterData.h"

//计算函数
//SingleVariable
	void RT_CalFrequency(PRTCALFUNCPARA pCalFuncPara);			//0
	void RT_CalEffecValue(PRTCALFUNCPARA pCalFuncPara);			//1
	void RT_CalFundValue(PRTCALFUNCPARA pCalFuncPara);			//2
	void RT_CalFundPhase(PRTCALFUNCPARA pCalFuncPara);			//3
	void RT_CalPeakValue(PRTCALFUNCPARA pCalFuncPara);			//4
	void RT_CalVellayValue(PRTCALFUNCPARA pCalFuncPara);		//5
	void RT_CalInstValue(PRTCALFUNCPARA pCalFuncPara);			//6
	void RT_CalAverageValue(PRTCALFUNCPARA pCalFuncPara);		//7
	void RT_CalHarm02Value(PRTCALFUNCPARA pCalFuncPara);		//8
	void RT_CalHarm03Value(PRTCALFUNCPARA pCalFuncPara);		//9
	void RT_CalHarm04Value(PRTCALFUNCPARA pCalFuncPara);		//10
	void RT_CalHarm05Value(PRTCALFUNCPARA pCalFuncPara);		//11
	void RT_CalHarm06Value(PRTCALFUNCPARA pCalFuncPara);		//12
	void RT_CalHarm07Value(PRTCALFUNCPARA pCalFuncPara);		//13
	void RT_CalHarm08Value(PRTCALFUNCPARA pCalFuncPara);		//14
	void RT_CalHarm09Value(PRTCALFUNCPARA pCalFuncPara);		//15
	void RT_CalHarm10Value(PRTCALFUNCPARA pCalFuncPara);		//16
	void RT_CalHarm11Value(PRTCALFUNCPARA pCalFuncPara);		//17
	void RT_CalHarm12Value(PRTCALFUNCPARA pCalFuncPara);		//18
	void RT_CalHarm13Value(PRTCALFUNCPARA pCalFuncPara);		//19
	void RT_CalHarm14Value(PRTCALFUNCPARA pCalFuncPara);		//20
	void RT_CalHarm15Value(PRTCALFUNCPARA pCalFuncPara);		//21
	void RT_CalHarm16Value(PRTCALFUNCPARA pCalFuncPara);		//22
	void RT_CalHarm17Value(PRTCALFUNCPARA pCalFuncPara);		//23
	void RT_CalHarm18Value(PRTCALFUNCPARA pCalFuncPara);		//24
	void RT_CalHarm19Value(PRTCALFUNCPARA pCalFuncPara);		//25
	void RT_CalHarm20Value(PRTCALFUNCPARA pCalFuncPara);		//26
	void RT_CalHarm21Value(PRTCALFUNCPARA pCalFuncPara);		//27
	void RT_CalHarm22Value(PRTCALFUNCPARA pCalFuncPara);		//28
	void RT_CalHarm23Value(PRTCALFUNCPARA pCalFuncPara);		//29
	void RT_CalHarm24Value(PRTCALFUNCPARA pCalFuncPara);		//30
	void RT_CalHarm25Value(PRTCALFUNCPARA pCalFuncPara);		//31
	void RT_CalHarm02Phase(PRTCALFUNCPARA pCalFuncPara);		//32
	void RT_CalHarm03Phase(PRTCALFUNCPARA pCalFuncPara);		//33
	void RT_CalHarm04Phase(PRTCALFUNCPARA pCalFuncPara);		//34
	void RT_CalHarm05Phase(PRTCALFUNCPARA pCalFuncPara);		//35
	void RT_CalHarm06Phase(PRTCALFUNCPARA pCalFuncPara);		//36
	void RT_CalHarm07Phase(PRTCALFUNCPARA pCalFuncPara);		//37
	void RT_CalHarm08Phase(PRTCALFUNCPARA pCalFuncPara);		//38
	void RT_CalHarm09Phase(PRTCALFUNCPARA pCalFuncPara);		//39
	void RT_CalHarm10Phase(PRTCALFUNCPARA pCalFuncPara);		//40
	void RT_CalHarm11Phase(PRTCALFUNCPARA pCalFuncPara);		//41
	void RT_CalHarm12Phase(PRTCALFUNCPARA pCalFuncPara);		//42
	void RT_CalHarm13Phase(PRTCALFUNCPARA pCalFuncPara);		//43
	void RT_CalHarm14Phase(PRTCALFUNCPARA pCalFuncPara);		//44
	void RT_CalHarm15Phase(PRTCALFUNCPARA pCalFuncPara);		//45
	void RT_CalHarm16Phase(PRTCALFUNCPARA pCalFuncPara);		//46
	void RT_CalHarm17Phase(PRTCALFUNCPARA pCalFuncPara);		//47
	void RT_CalHarm18Phase(PRTCALFUNCPARA pCalFuncPara);		//48
	void RT_CalHarm19Phase(PRTCALFUNCPARA pCalFuncPara);		//49
	void RT_CalHarm20Phase(PRTCALFUNCPARA pCalFuncPara);		//50
	void RT_CalHarm21Phase(PRTCALFUNCPARA pCalFuncPara);		//51
	void RT_CalHarm22Phase(PRTCALFUNCPARA pCalFuncPara);		//52
	void RT_CalHarm23Phase(PRTCALFUNCPARA pCalFuncPara);		//53
	void RT_CalHarm24Phase(PRTCALFUNCPARA pCalFuncPara);		//54
	void RT_CalHarm25Phase(PRTCALFUNCPARA pCalFuncPara);		//55

	//MultiVariable
	void RT_CalImpedance(PRTCALFUNCPARA pCalFuncPara);          //0
	void RT_CalPositiveSequence(PRTCALFUNCPARA pCalFuncPara);   //1
	void RT_CalNegativeSequence(PRTCALFUNCPARA pCalFuncPara);   //2
	void RT_CalZeroSequence(PRTCALFUNCPARA pCalFuncPara);       //3
	void RT_CalActivePower(PRTCALFUNCPARA pCalFuncPara);        //4
	void RT_CalReactivePower(PRTCALFUNCPARA pCalFuncPara);      //5
	void RT_CalApparentPower(PRTCALFUNCPARA pCalFuncPara);      //6
	void RT_CalReserve01Value(PRTCALFUNCPARA pCalFuncPara);     //7
	void RT_CalReserve02Value(PRTCALFUNCPARA pCalFuncPara);     //8
	void RT_CalReserve03Value(PRTCALFUNCPARA pCalFuncPara);     //9
	void RT_CalReserve04Value(PRTCALFUNCPARA pCalFuncPara);     //10
	void RT_CalReserve05Value(PRTCALFUNCPARA pCalFuncPara);     //11
	void RT_CalReserve06Value(PRTCALFUNCPARA pCalFuncPara);     //12
	void RT_CalReserve07Value(PRTCALFUNCPARA pCalFuncPara);     //13
	void RT_CalReserve08Value(PRTCALFUNCPARA pCalFuncPara);     //14
	void RT_CalReserve09Value(PRTCALFUNCPARA pCalFuncPara);     //15
	void RT_CalReserve10Value(PRTCALFUNCPARA pCalFuncPara);		//16
	void CalHar(long nHar,PRTCALFUNCPARA pCalFuncPara, double& dHarValue ,double& dHarPhasic);
	void GetRealandImValue(PRTCALFUNCPARA pCalFuncPara,double& dReal1,double& dReal2,double& dReal3,double& dIm1,double& dIm2,double& dIm3);

	inline void RT_CalPower(PRTCALFUNCPARA pCalFuncPara)
	{
		RT_CalActivePower(pCalFuncPara);
		RT_CalReactivePower(pCalFuncPara);
		RT_CalApparentPower(pCalFuncPara);
	}
	//调整过零点的位置，原因是由于噪声干扰，在零点附近可能会有波动，使得很多过零点不可用 fdp add 2010.4.15
	BOOL ModifyZeroPosition(DWORD dwBufferLen,DWORD* pZeroPos,DWORD& dwCount);
	BOOL ModifyZeroPosition(PRTCALFUNCPARA pCalFuncPara, DWORD* pZeroPos, DWORD& dwCount);
	
#endif//!defined(_CALFUNIONS_H_)
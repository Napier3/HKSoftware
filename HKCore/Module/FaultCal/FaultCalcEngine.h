// CalcEngine.h : CCalcEngine µÄÉùÃ÷

#pragma once

#include "FaultDef.h"
#include "FaultDef_Calc.h"

class CCalcEngine
{
public:
	CCalcEngine()
	{
	}

public:

private:
	long my_GetCalcID(VARIANT var);
	HRESULT my_Calculate(long nCalcID, IDispatch *ptrRootNode,BSTR *bstrChildName);

public:
	STDMETHOD(Calculate)(IDispatch* lpGenericData);
public:
	STDMETHOD(Calculate_LoadState)(BYTE* lpFaultCalc_LoadState, LONG nSize);
	STDMETHOD(Calculate_Fault)(BYTE* lpFaultCalc_Fault, LONG nSize);
	STDMETHOD(Calculate_GPFault)(BYTE* lpFaultCalc_GPFault, LONG nSize);
	STDMETHOD(Calculate_ABCtoPP)(BYTE* lpFaultCalc_ABCPP, LONG nSize);
	STDMETHOD(Calculate_PPtoABC)(BYTE* lpFaultCalc_ABCPP, LONG nSize);
	STDMETHOD(Calculate_ABCto120)(BYTE* lpFaultCalc_ABC120, LONG nSize);
	STDMETHOD(Calculate_120toABC)(BYTE* lpFaultCalc_ABC120, LONG nSize);
	STDMETHOD(Calculate_PQ)(BYTE* lpFaultCalc_PQ, LONG nSize);
public:
	STDMETHOD(Comp_Add)(FLOAT Mag1, FLOAT Ang1, FLOAT Mag2, FLOAT Ang2, FLOAT* theMag, FLOAT* theAng);
	STDMETHOD(Comp_Sub)(FLOAT Mag1, FLOAT Ang1, FLOAT Mag2, FLOAT Ang2, FLOAT* theMag, FLOAT* theAng);
	STDMETHOD(Comp_Mul)(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT* theX, FLOAT* theY);
	STDMETHOD(Comp_Div)(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT* theX, FLOAT* theY);
	STDMETHOD(Comp_POtoXY)(FLOAT Mag, FLOAT Ang, FLOAT* x, FLOAT* y);
	STDMETHOD(Comp_XYtoPO)(FLOAT x, FLOAT y, FLOAT* Mag, FLOAT* Ang);
public:
	STDMETHOD(Calculate_Shot)(BYTE* lpFaultCalc_Shot, LONG nSize);
	STDMETHOD(Calculate_Distance)(BYTE* lpFaultCalc_Distance, LONG nSize);
	STDMETHOD(Calculate_GPDistance)(BYTE* lpFaultCalc_GPDistance, LONG nSize);
	STDMETHOD(Calculate_OverCurr)(BYTE* lpFaultCalc_OverCurr, LONG nSize);
	STDMETHOD(Calculate_NegSeqCurr)(BYTE* lpFaultCalc_NegSeqCurr, LONG nSize);
	STDMETHOD(Calculate_ZeroSeqCurr)(BYTE* lpFaultCalc_ZeroSeqCurr, LONG nSize);
public:
	STDMETHOD(Calculate_Diff)(BYTE* lpFaultCalc_Diff, LONG nSize);
	STDMETHOD(Calculate_Diff_Shot)(BYTE* lpFaultCalc_Diff_Shot, LONG nSize);
	STDMETHOD(Calculate_Diff_IrId)(BYTE* lpFaultCalc_Diff_IrId, LONG nSize);
	STDMETHOD(Calculate_Diff_KP)(BYTE* lpFaultCalc_Diff_KP, LONG nSize);
public:
	STDMETHOD(Calculate_Diff5)(BYTE* lpFaultCalc_Diff5, LONG nSize);
public:
	STDMETHOD(Calculate_Osc)(BYTE* lpFaultCalc_Osc, LONG nSize);
	STDMETHOD(Calculate_Osc_Zk)(BYTE* lpFaultCalc_Osc_Zk, LONG nSize);
public:
	STDMETHOD(Calculate_Fault_Ex)(BYTE* lpFaultCalc_Fault_Ex, LONG nSize);
	STDMETHOD(Calculate_Shot_Ex)(BYTE* lpFaultCalc_Shot_Ex, LONG nSize);
	STDMETHOD(Calculate_GPFault_Ex)(BYTE* lpFaultCalc_GPFault_Ex, LONG nSize);
	STDMETHOD(Calculate_GPDistance_Ex)(BYTE* lpFaultCalc_GPDistance_Ex, LONG nSize);
}; 

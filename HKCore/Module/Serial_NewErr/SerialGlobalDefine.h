#pragma once

#define SERIAL_CHECKBYTE_NONE    0    //(_T("无校验"));
#define SERIAL_CHECKBYTE_ODD     1    //(_T("奇校验"));
#define SERIAL_CHECKBYTE_EVEN    2    //(_T("偶校验"));

#define SERIAL_CHECKBYTE_STRING_NONE    _T("none")    //(_T("无校验"));
#define SERIAL_CHECKBYTE_STRING_ODD     _T("odd")    //(_T("奇校验"));
#define SERIAL_CHECKBYTE_STRING_EVEN    _T("even")    //(_T("偶校验"));

#define SERIAL_STOPBYTE_STRING_1    _T("1")
#define SERIAL_STOPBYTE_STRING_15     _T("1.5") 
#define SERIAL_STOPBYTE_STRING_2    _T("2")



inline BYTE Serial_GetStopBits(float fStopBit)
{ /* 0,1,2 = 1, 1.5, 2               */
	if ( fabs(fStopBit - 1) <=0.001 )
	{
		return 0;
	}

	if ( fabs(fStopBit - 1.5) <=0.001 )
	{
		return 1;
	}

	if ( fabs(fStopBit - 2) <=0.001 )
	{
		return 2;
	}

	return 0;
}


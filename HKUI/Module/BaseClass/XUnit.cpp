#include "stdafx.h"
#include "XUnit.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CXUnit
CString CXUnit::g_strXUnit[_XUNITS_MAX_COUNT_];

CXUnit::CXUnit()
{
	if (g_strXUnit[0].GetLength() > 0)
	{
		return;
	}

	g_strXUnit[0]="MVA";
	g_strXUnit[1]="kA";
	g_strXUnit[2]="kV";
	g_strXUnit[3]="A";
	g_strXUnit[4]="V";
	g_strXUnit[5]="Hz";
	g_strXUnit[6]="K";
	g_strXUnit[7]="s";
	g_strXUnit[8]="S";
	g_strXUnit[9]="Ω";
	g_strXUnit[10]="VA";
	g_strXUnit[11]="W";
	g_strXUnit[12]="km";
	g_strXUnit[13]="kg";
	g_strXUnit[14]="mol";
	g_strXUnit[15]="cd";
	g_strXUnit[16]="m";
	g_strXUnit[17]="度";
	g_strXUnit[20]="deg";
	g_strXUnit[21]="rad";
	g_strXUnit[22]="sr";
	g_strXUnit[23]="Ie";
	g_strXUnit[24]="Gy";
	g_strXUnit[25]="q";
	g_strXUnit[26]="°C";
	g_strXUnit[27]="Sv";
	g_strXUnit[28]="F";
	g_strXUnit[29]="C";
	g_strXUnit[30]="S";
	g_strXUnit[31]="H";
	g_strXUnit[32]="ohm";
	g_strXUnit[33]="J";
	g_strXUnit[34]="N";
	g_strXUnit[35]="lx";
	g_strXUnit[36]="Lm";
	g_strXUnit[37]="Wb";
	g_strXUnit[38]="T";
	g_strXUnit[39]="Pa";
	g_strXUnit[41]="m2";
	g_strXUnit[42]="m3";
	g_strXUnit[43]="m/s";
	g_strXUnit[44]="m/s2";
	g_strXUnit[45]="m3/s";
	g_strXUnit[46]="m/m3";
	g_strXUnit[47]="M";
	g_strXUnit[48]="kg/m3";
	g_strXUnit[49]="m2/s";
	g_strXUnit[50]="W/mK";
	g_strXUnit[51]="J/K";
	g_strXUnit[52]="ppm";
	g_strXUnit[53]="1/s";
	g_strXUnit[60]="rad/s";
	g_strXUnit[61]="Watts";
	g_strXUnit[62]="VAr";
	g_strXUnit[63]="phi";
	g_strXUnit[64]="cos(phi)";
	g_strXUnit[65]="Vs";
	g_strXUnit[66]="V2";
	g_strXUnit[67]="As";
	g_strXUnit[68]="A2";
	g_strXUnit[69]="A2t";
	g_strXUnit[70]="VAh";
	g_strXUnit[71]="Wh";
	g_strXUnit[72]="VArh";
	g_strXUnit[73]="V/Hz";
	g_strXUnit[74]="Hz/s";
	g_strXUnit[75]="dBm";
	g_strXUnit[76]="dBm/s";
	g_strXUnit[77]="kgm2";
	g_strXUnit[78]="dB";
}


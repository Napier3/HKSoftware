#include "stdafx.h"
#include "EnumType.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CMultiplier
CString CMultiplier::g_strMultiplier[21];

CMultiplier::CMultiplier()
{
	if (g_strMultiplier[0].GetLength() > 0)
	{
		return;
	}

	g_strMultiplier[0] = "y";
	g_strMultiplier[1] = "z";
	g_strMultiplier[2] = "a";
	g_strMultiplier[3] = "f";
	g_strMultiplier[4] = "p";
	g_strMultiplier[5] = "n";
	g_strMultiplier[6] = "¶Ã";
	g_strMultiplier[7] = "m";
	g_strMultiplier[8] = "c";
	g_strMultiplier[9] = "d";
	g_strMultiplier[10] = "";
	g_strMultiplier[11] = "da";
	g_strMultiplier[12] = "h";
	g_strMultiplier[13] = "k";
	g_strMultiplier[14] = "M";
	g_strMultiplier[15] = "G";
	g_strMultiplier[16] = "T";
	g_strMultiplier[17] = "P";
	g_strMultiplier[18] = "E";
	g_strMultiplier[19] = "Z";
	g_strMultiplier[20] = "Y";
}

CString CMultiplier::GetMultiplierUnite(int nEnumType)
{
	if (nEnumType==-24)
		return g_strMultiplier[0];
	if (nEnumType==-21)
		return g_strMultiplier[1];
	if (nEnumType==-18)
		return g_strMultiplier[2];
	if (nEnumType==-15)
		return g_strMultiplier[3];
	if (nEnumType==-12)
		return g_strMultiplier[4];
	if (nEnumType==-9)
		return g_strMultiplier[5];
	if (nEnumType==-6)
		return g_strMultiplier[6];
	if (nEnumType==-3)
		return g_strMultiplier[7];
	if (nEnumType==-2)
		return g_strMultiplier[8];
	if (nEnumType==-1)
		return g_strMultiplier[9];
	if (nEnumType==0)
		return g_strMultiplier[10];
	if (nEnumType==1)
		return g_strMultiplier[11];
	if (nEnumType==2)
		return g_strMultiplier[12];
	if (nEnumType==3)
		return g_strMultiplier[13];
	if (nEnumType==6)
		return g_strMultiplier[14];
	if (nEnumType==9)
		return g_strMultiplier[15];
	if (nEnumType==12)
		return g_strMultiplier[16];
	if (nEnumType==15)
		return g_strMultiplier[17];
	if (nEnumType==18)
		return g_strMultiplier[18];
	if (nEnumType==21)
		return g_strMultiplier[19];
	if (nEnumType==24)
		return g_strMultiplier[20];

	return "";
}

int CMultiplier::GetMultiplierUniteIndex(CString strUnite)
{
	if (strUnite == g_strMultiplier[0])
		return -24;
	if (strUnite == g_strMultiplier[1])
		return -21;
	if (strUnite == g_strMultiplier[2])
		return -18;
	if (strUnite == g_strMultiplier[3])
		return -15;
	if (strUnite == g_strMultiplier[4])
		return -12;
	if (strUnite == g_strMultiplier[5])
		return -9;
	if (strUnite == g_strMultiplier[6])
		return -6;
	if (strUnite == g_strMultiplier[7])
		return -3;
	if (strUnite == g_strMultiplier[8])
		return -2;
	if (strUnite == g_strMultiplier[9])
		return -1;
	if (strUnite == g_strMultiplier[10])
		return 0;
	if (strUnite == g_strMultiplier[11])
		return 1;
	if (strUnite == g_strMultiplier[12])
		return 2;
	if (strUnite == g_strMultiplier[13])
		return 3;
	if (strUnite == g_strMultiplier[14])
		return 6;
	if (strUnite == g_strMultiplier[15])
		return 9;
	if (strUnite == g_strMultiplier[16])
		return 12;
	if (strUnite == g_strMultiplier[17])
		return 15;
	if (strUnite == g_strMultiplier[18])
		return 18;
	if (strUnite == g_strMultiplier[19])
		return 21;
	if (strUnite == g_strMultiplier[20])
		return 24;

	return 65535;
}

//////////////////////////////////////////////////////////////////////////
//CSIUnit
CString CSIUnit::g_strSIUnit[79];

CSIUnit::CSIUnit()
{
	if (g_strSIUnit[0].GetLength() > 0)
	{
		return;
	}

	g_strSIUnit[1] = "m";
	g_strSIUnit[2] = "kg";
	g_strSIUnit[3] = "s";
	g_strSIUnit[4] = "A";
	g_strSIUnit[5] = "K";
	g_strSIUnit[6] = "mol";
	g_strSIUnit[7] = "cd";
	g_strSIUnit[8] = "deg";
	g_strSIUnit[9] = "rad";
	g_strSIUnit[10] = "sr";
	g_strSIUnit[20] = "Gy";
	g_strSIUnit[21] = "q";
	g_strSIUnit[22] = "°„C";
	g_strSIUnit[23] = "Sv";
	g_strSIUnit[24] = "F";
	g_strSIUnit[25] = "C";
	g_strSIUnit[26] = "S";
	g_strSIUnit[27] = "H";
	g_strSIUnit[28] = "V";
	g_strSIUnit[29] = "ohm";
	g_strSIUnit[30] = "J";
	g_strSIUnit[31] = "N";
	g_strSIUnit[32] = "Hz";
	g_strSIUnit[33] = "lx";
	g_strSIUnit[34] = "Lm";
	g_strSIUnit[35] = "Wb";
	g_strSIUnit[36] = "T";
	g_strSIUnit[37] = "W";
	g_strSIUnit[38] = "Pa";
	g_strSIUnit[39] = "m2";
	g_strSIUnit[41] = "m3";
	g_strSIUnit[42] = "m/s";
	g_strSIUnit[43] = "m/s2";
	g_strSIUnit[44] = "m3/s";
	g_strSIUnit[45] = "m/m3";
	g_strSIUnit[46] = "M";
	g_strSIUnit[47] = "kg/m3";
	g_strSIUnit[48] = "m2/s";
	g_strSIUnit[49] = "W/m K";
	g_strSIUnit[50] = "J/K";
	g_strSIUnit[51] = "ppm";
	g_strSIUnit[52] = "1/s";
	g_strSIUnit[53] = "rad/s";
	g_strSIUnit[60] = "VA";
	g_strSIUnit[61] = "Watts";
	g_strSIUnit[62] = "VAr";
	g_strSIUnit[63] = "phi";
	g_strSIUnit[64] = "cos(phi)";
	g_strSIUnit[65] = "Vs";
	g_strSIUnit[66] = "V2";
	g_strSIUnit[67] = "As";
	g_strSIUnit[68] = "A2";
	g_strSIUnit[69] = "A2t";
	g_strSIUnit[70] = "VAh";
	g_strSIUnit[71] = "Wh";
	g_strSIUnit[72] = "VArh";
	g_strSIUnit[73] = "V/Hz";
	g_strSIUnit[74] = "Hz/s";
	g_strSIUnit[75] = "dBm";
	g_strSIUnit[76] = "dBm/s";
	g_strSIUnit[77] = "kgm2";
	g_strSIUnit[78] = "dB";
}


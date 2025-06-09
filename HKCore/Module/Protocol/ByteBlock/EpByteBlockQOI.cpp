#include "StdAfx.h"
#include "EpByteBlockQOI.h"

CEpByteBlockQOI::CEpByteBlockQOI(BYTE byteQOI, BOOL bAddDetail)
{
	m_byteQOI = byteQOI;

	if (bAddDetail)
	{
		AddBbInfor(g_strEpQOI, m_byteQOI, 0, 7);
	}
}


CEpByteBlockQOI::~CEpByteBlockQOI()
{
	
}

void CEpByteBlockQOI::GetBbInfor(CString &strInfor)
{
	if (m_byteQOI > 0x3F)
	{
		strInfor = _T("QOI:错误的命令");
		return;
	}

	switch (m_byteQOI)
	{
	case 0x14:
		strInfor = _T("QOI:站召唤全局");
		break;
	case 0x15:
		strInfor = _T("QOI:第1组召唤");
		break;
	case 0x16:
		strInfor = _T("QOI:第2组召唤");
		break;
	case 0x17:
		strInfor = _T("QOI:第3组召唤");
		break;
	case 0x18:
		strInfor = _T("QOI:第4组召唤");
		break;
	case 0x19:
		strInfor = _T("QOI:第5组召唤");
		break;
	case 0x1A:
		strInfor = _T("QOI:第6组召唤");
		break;
	case 0x1B:
		strInfor = _T("QOI:第7组召唤");
		break;
	case 0x1C:
		strInfor = _T("QOI:第8组召唤");
		break;
	case 0x1D:
		strInfor = _T("QOI:第9组召唤");
		break;
	case 0x1E:
		strInfor = _T("QOI:第10组召唤");
		break;
	case 0x1F:
		strInfor = _T("QOI:第11组召唤");
		break;
	case 0x20:
		strInfor = _T("QOI:第12组召唤");
		break;
	case 0x21:
		strInfor = _T("QOI:第13组召唤");
		break;
	case 0x22:
		strInfor = _T("QOI:第14组召唤");
		break;
	case 0x23:
		strInfor = _T("QOI:第15组召唤");
		break;
	case 0x24:
		strInfor = _T("QOI:第16组召唤");
		break;
	default:
		strInfor = _T("QOI:保留或未用");
		break;
	}
}


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
		strInfor = _T("QOI:���������");
		return;
	}

	switch (m_byteQOI)
	{
	case 0x14:
		strInfor = _T("QOI:վ�ٻ�ȫ��");
		break;
	case 0x15:
		strInfor = _T("QOI:��1���ٻ�");
		break;
	case 0x16:
		strInfor = _T("QOI:��2���ٻ�");
		break;
	case 0x17:
		strInfor = _T("QOI:��3���ٻ�");
		break;
	case 0x18:
		strInfor = _T("QOI:��4���ٻ�");
		break;
	case 0x19:
		strInfor = _T("QOI:��5���ٻ�");
		break;
	case 0x1A:
		strInfor = _T("QOI:��6���ٻ�");
		break;
	case 0x1B:
		strInfor = _T("QOI:��7���ٻ�");
		break;
	case 0x1C:
		strInfor = _T("QOI:��8���ٻ�");
		break;
	case 0x1D:
		strInfor = _T("QOI:��9���ٻ�");
		break;
	case 0x1E:
		strInfor = _T("QOI:��10���ٻ�");
		break;
	case 0x1F:
		strInfor = _T("QOI:��11���ٻ�");
		break;
	case 0x20:
		strInfor = _T("QOI:��12���ٻ�");
		break;
	case 0x21:
		strInfor = _T("QOI:��13���ٻ�");
		break;
	case 0x22:
		strInfor = _T("QOI:��14���ٻ�");
		break;
	case 0x23:
		strInfor = _T("QOI:��15���ٻ�");
		break;
	case 0x24:
		strInfor = _T("QOI:��16���ٻ�");
		break;
	default:
		strInfor = _T("QOI:������δ��");
		break;
	}
}


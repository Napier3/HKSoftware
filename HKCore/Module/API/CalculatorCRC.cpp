#include "StdAfx.h"
#include "CalculatorCRC.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCalculatorCCR::CCalculatorCCR()
{
	ResetData();
}
void CCalculatorCCR::ResetData()
{
	for (int i =0;i<16;i++)
	{
		cbit[i]=0;
	}
	bit[0]=D0;bit[1]=D1;bit[2]=D2;bit[3]=D3;bit[4]=D4;bit[5]=D5;bit[6]=D6;bit[7]=D7;
	bit[8]=D8;bit[9]=D9;bit[10]=D10;bit[11]=D11;bit[12]=D12;bit[13]=D13;bit[14]=D14;bit[15]=D15;
}
void CCalculatorCCR::crc(unsigned short input)
{
	unsigned short dbit[16];
	unsigned char i;
	
	for(i=0;i<16;i++)
	{
		if(input&bit[i]) dbit[i]=1;
		else dbit[i]=0;
	}
	
	cnbit[0]=dbit[15] ^ dbit[11] ^ dbit[10] ^ dbit[9] ^ dbit[5] ^ dbit[4] ^ dbit[3] ^ dbit[0] \
		^cbit[0] ^ cbit[3] ^ cbit[4] ^ cbit[5] ^ cbit[9] ^ cbit[10] ^ cbit[11] ^ cbit[15];
	cnbit[1] = dbit[12] ^ dbit[11] ^ dbit[10] ^ dbit[6] ^ dbit[5] ^ dbit[4] ^ dbit[1] ^ \
		cbit[1] ^ cbit[4] ^ cbit[5] ^ cbit[6] ^ cbit[10] ^ cbit[11] ^ cbit[12];
	cnbit[2] = dbit[15] ^ dbit[13] ^ dbit[12] ^ dbit[10] ^ dbit[9] ^ dbit[7] ^ dbit[6] ^ \
		dbit[4] ^ dbit[3] ^ dbit[2] ^ dbit[0] ^ cbit[0] ^ cbit[2] ^ cbit[3] ^ cbit[4] ^  \
		cbit[6] ^ cbit[7] ^ cbit[9] ^ cbit[10] ^ cbit[12] ^ cbit[13] ^ cbit[15];
	cnbit[3] = dbit[14] ^ dbit[13] ^ dbit[11] ^ dbit[10] ^ dbit[8] ^ dbit[7] ^ dbit[5] ^ \
		dbit[4] ^ dbit[3] ^ dbit[1] ^ cbit[1] ^ cbit[3] ^ cbit[4] ^ cbit[5] ^ cbit[7] ^  \
		cbit[8] ^ cbit[10] ^ cbit[11] ^ cbit[13] ^ cbit[14];
	cnbit[4] = dbit[15] ^ dbit[14] ^ dbit[12] ^ dbit[11] ^ dbit[9] ^ dbit[8] ^ dbit[6] ^ \
		dbit[5] ^ dbit[4] ^ dbit[2] ^ cbit[2] ^ cbit[4] ^ cbit[5] ^ cbit[6] ^ cbit[8] ^  \
		cbit[9] ^ cbit[11] ^ cbit[12] ^ cbit[14] ^ cbit[15];
	cnbit[5] = dbit[13] ^ dbit[12] ^ dbit[11] ^ dbit[7] ^ dbit[6] ^ dbit[4] ^ dbit[0] ^  \
		cbit[0] ^ cbit[4] ^ cbit[6] ^ cbit[7] ^ cbit[11] ^ cbit[12] ^ cbit[13];
	cnbit[6]= dbit[15]^dbit[14]^dbit[13]^dbit[12]^dbit[11]^dbit[10]^dbit[9]^dbit[8]^dbit[7]^dbit[4] \
		^dbit[3]^dbit[1]^dbit[0]^cbit[0]^cbit[1]^cbit[3]^cbit[4]^cbit[7]^cbit[8]^cbit[9]^cbit[10] \
		^cbit[11]^cbit[12]^cbit[13]^cbit[14]^cbit[15];
	cnbit[7] = dbit[15] ^ dbit[14] ^ dbit[13] ^ dbit[12] ^ dbit[11] ^ dbit[10] ^ dbit[9] ^  \
		dbit[8] ^ dbit[5] ^ dbit[4] ^ dbit[2] ^ dbit[1] ^ cbit[1] ^ cbit[2] ^ cbit[4] ^     \
		cbit[5] ^ cbit[8] ^ cbit[9] ^ cbit[10] ^ cbit[11] ^ cbit[12] ^ cbit[13] ^           \
		cbit[14] ^ cbit[15];
	cnbit[8] = dbit[14] ^ dbit[13] ^ dbit[12] ^ dbit[6] ^ dbit[4] ^ dbit[2] ^ dbit[0] ^     \
		cbit[0] ^ cbit[2] ^ cbit[4] ^ cbit[6] ^ cbit[12] ^ cbit[13] ^ cbit[14];
	cnbit[9] = dbit[15] ^ dbit[14] ^ dbit[13] ^ dbit[7] ^ dbit[5] ^ dbit[3] ^ dbit[1] ^     \
		cbit[1] ^ cbit[3] ^ cbit[5] ^ cbit[7] ^ cbit[13] ^ cbit[14] ^ cbit[15];
	cnbit[10] = dbit[14] ^ dbit[11] ^ dbit[10] ^ dbit[9] ^ dbit[8] ^ dbit[6] ^ dbit[5] ^    \
		dbit[3] ^ dbit[2] ^ dbit[0] ^ cbit[0] ^ cbit[2] ^ cbit[3] ^ cbit[5] ^ cbit[6] ^     \
		cbit[8] ^ cbit[9] ^ cbit[10] ^ cbit[11] ^ cbit[14];
	cnbit[11] = dbit[12] ^ dbit[7] ^ dbit[6] ^ dbit[5] ^ dbit[1] ^ dbit[0] ^ cbit[0] ^ cbit[1] ^  \
		cbit[5] ^ cbit[6] ^ cbit[7] ^ cbit[12];
	cnbit[12] = dbit[15] ^ dbit[13] ^ dbit[11] ^ dbit[10] ^ dbit[9] ^ dbit[8] ^ dbit[7] ^   \
		dbit[6] ^ dbit[5] ^ dbit[4] ^ dbit[3] ^ dbit[2] ^ dbit[1] ^ dbit[0] ^ cbit[0] ^     \
		cbit[1] ^ cbit[2] ^ cbit[3] ^ cbit[4] ^ cbit[5] ^ cbit[6] ^ cbit[7] ^ cbit[8] ^     \
		cbit[9] ^ cbit[10] ^ cbit[11] ^ cbit[13] ^ cbit[15];
	cnbit[13] = dbit[15] ^ dbit[14] ^ dbit[12] ^ dbit[8] ^ dbit[7] ^ dbit[6] ^ dbit[2] ^    \
		dbit[1] ^ dbit[0] ^ cbit[0] ^ cbit[1] ^ cbit[2] ^ cbit[6] ^ cbit[7] ^ cbit[8] ^     \
		cbit[12] ^ cbit[14] ^ cbit[15];
	cnbit[14]=dbit[15]^dbit[13]^dbit[9]^dbit[8]^dbit[7]^dbit[3]^dbit[2]^dbit[1]^ \
		cbit[1]^cbit[2]^cbit[3]^cbit[7]^cbit[8]^cbit[9]^cbit[13]^cbit[15];
	cnbit[15] = dbit[14] ^ dbit[10] ^ dbit[9] ^ dbit[8] ^ dbit[4] ^ dbit[3] ^ dbit[2] ^     \
		cbit[2] ^ cbit[3] ^ cbit[4] ^ cbit[8] ^ cbit[9] ^ cbit[10] ^ cbit[14];
	
	for(i=0;i<16;i++)
		cbit[i]=cnbit[i];
	return;
}
unsigned short CCalculatorCCR::GetCrcValue(unsigned short * pArray,unsigned short length)
{

	return 0;
}
CString CCalculatorCCR::GetCrcValue(CString m_strDeal, int nMode)
{
	ResetData();
	int length = m_strDeal.GetLength();
	if (length%2!=0)
	{
		m_strDeal = m_strDeal.Mid(0,length-1);
	}
	int t_StartPos = 0;
	if (nMode == 0)
	{
		char *chTemp;
		for (int j =0;j<length/4;j++)		//原来的代码，耗时太多
		{
			CString temp = m_strDeal.Mid(t_StartPos,4);
			CString_to_char(temp, &chTemp);
			int	nCrc = GetIntegerFromString(chTemp);
			crc(nCrc);
			delete []chTemp;
			t_StartPos+=4;
		}
	}
	else
	{
		for (int j =0;j<length/4;j++)		//尝试修改，未必正确
		{
			CString temp = m_strDeal.Mid(t_StartPos,4);
#ifdef UNICODE
			DWORD nCrc = wcstoul(temp, NULL,16);
#else
			DWORD nCrc = strtoul(temp, NULL,16);
#endif
			crc(nCrc);
			t_StartPos+=4;
		}
	}
	unsigned short output_data = 0;
	for(int i=0;i<16;i++)
	{
		if(cbit[i])
			output_data |= bit[i];
	}
	CString temp1;
	temp1.Format(_T("%d"),output_data);
	return temp1;
}
unsigned short CCalculatorCCR::GetIntegerFromString(const char* pStr)
{
    unsigned short nValue = 0;
    for (int i = 0; i<strlen(pStr); i++)
    {
        int nLetterValue ;
		
        switch (*(pStr+i))
        {
		case 'a':case 'A':
			nLetterValue = 10;break;
		case 'b':case 'B':
			nLetterValue = 11;break;
		case 'c': case 'C':
			nLetterValue = 12;break;
		case 'd':case 'D':
			nLetterValue = 13;break;
		case 'e': case 'E':
			nLetterValue = 14;break;
		case 'f': case 'F':
			nLetterValue = 15;break;
		default:nLetterValue = *(pStr+i) - '0';
			
        }
        nValue = nValue * 16 + nLetterValue; //16进制
    }
    return nValue;
}
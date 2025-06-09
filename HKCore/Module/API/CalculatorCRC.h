#ifndef CCRComputer_h
#define CCRComputer_h

#define D15	(1<<15)
#define D14 (1<<14)
#define D13 (1<<13)
#define D12 (1<<12)
#define D11 (1<<11)
#define D10 (1<<10)
#define D9  (1<<9)
#define D8  (1<<8)
#define D7  (1<<7)
#define D6  (1<<6)
#define D5  (1<<5)
#define D4  (1<<4)
#define D3  (1<<3)
#define D2  (1<<2)
#define D1  (1<<1)
#define D0  1
class CCalculatorCCR
{
public:
	CCalculatorCCR();
	unsigned short cbit[16];
	unsigned short cnbit[16];
	unsigned short bit[16];
	unsigned short data[3];
	void crc(unsigned short input);
	CString GetCrcValue(CString m_strDeal, int nMode=0);
	unsigned short GetIntegerFromString(const char* pStr);//16进制样式的字符串转16进制数
	unsigned short GetCrcValue(unsigned short * pArray,unsigned short length);
	void ResetData();
};

#endif

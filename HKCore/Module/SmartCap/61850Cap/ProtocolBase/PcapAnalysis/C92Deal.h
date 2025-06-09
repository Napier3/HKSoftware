#pragma once

union ConverStruct {
	unsigned char b[4];
	unsigned long l;
	float f;
};//4个字节，利用共用体，进行转换
class C92Deal//92和Goose信息解析方法类
{
public:
	C92Deal(void);

	static CString Get92FlagValue(CByteArray &DataArray,   BYTE bFlag,   int  nStartPos,   int &nAfterLength,  int nFormate  = 0);
	static CString GetValueFromByteArray(CByteArray &byArray,  int nStartPos,  int nLength);
	static int Get60AfterLength(CByteArray &m_DataArray,  int nOffset);
	static unsigned int GetIntegerFromString(CString pStr);
	static CString BinToDec(CString strBin);//2-10
	static CString DecToBin(CString strDec);//10-2
	static CString BinToHex(CString strBin);//2-16
	static CString HexToBin(CString strHex);//16-2
	static CString HexToDec(CString strHex);//16-10
	static CString DecToHex(CString strDec);
	static int ConverStrToNum(CString strDealStr);

public:
	~C92Deal(void);
};

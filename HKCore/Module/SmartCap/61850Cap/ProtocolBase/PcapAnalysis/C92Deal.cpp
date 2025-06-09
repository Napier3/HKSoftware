#include "StdAfx.h"
#include "C92Deal.h"
#include <math.h>
C92Deal::C92Deal(void)
{

}

C92Deal::~C92Deal(void)
{
}

CString C92Deal::BinToDec(CString strBin)//2进制转换10进制
{
	CString strDec;
	long nDec = 0, nLen;
	int i, j, k;
	nLen = strBin.GetLength();
	for (i=0; i<nLen;i++)
	{
		if (strBin.GetAt(nLen-i-1)=='0')continue;
		else
		{
			k = 1;
			for(j=0;j<i;j++)k= k*2;
			nDec+=k;
		}
	}
	strDec.Format(_T("%ld"), nDec);
	return strDec;
}

int C92Deal::ConverStrToNum(CString strDealStr)
{
	LPTSTR lpsz = new TCHAR[strDealStr.GetLength()+1];
	_tcscpy(lpsz,  strDealStr);
	int ReturnValue;
#ifdef UNICODE_STRING
	ReturnValue = _wtoi(lpsz);
#else
	ReturnValue = atoi(lpsz);
#endif
	return ReturnValue;
}

CString C92Deal::DecToBin(CString strDec)//10进制到2进制
{
	int nDec  =  ConverStrToNum(strDec);
	int nYushu,   nShang;
	CString strBin  = _T(""), strTemp;
	TCHAR buf[2];
	buf[0] = ' ';
	buf[1] = ' ';
	BOOL bContinue = TRUE;
	while ( bContinue )
	{
		nYushu  = nDec%2;
		nShang = nDec/2;
		wsprintf(buf,_T("%d"),  nYushu);
		strTemp   =  strBin;
		strBin.Format(_T("%s%s"),   buf, strTemp);
		nDec = nShang;
		if (nShang==0)bContinue=FALSE;
	}
	int nTemp = strBin.GetLength()%4;
	switch(nTemp)
	{
	case 1:
		strTemp.Format(_T("000%s"),strBin);
		strBin = strTemp;
		break;
	case 2:
		strTemp.Format(_T("00%s"),strBin);
		strBin = strTemp;
		break;
	case 3:
		strTemp.Format(_T("0%s"), strBin);
		strBin = strTemp;
		break;
	default:
		break;
	}
	return strBin;
}

CString C92Deal::BinToHex(CString strBin)//2-16
{
	CString strDec, strBinTemp, strHex;
	strBinTemp = strBin;
	strDec = BinToDec(strBinTemp);
	int nDec;
	nDec = ConverStrToNum(strDec);
	strHex.Format(_T("%x"), nDec);
	return strHex;
}

CString C92Deal::HexToBin(CString strHex)//16-2
{
	CString strDec,  strBin, strHexTemp;
	strHexTemp  =  strHex;
	DWORD dwHex = strtoul(strHexTemp,   NULL, 16);
	strDec.Format(_T("%uld"),  dwHex);
	strBin = DecToBin(strDec);
	return strBin;
}

CString C92Deal::DecToHex(CString strDec)//10-16
{
	int nDec = ConverStrToNum(strDec);
	CString str;
	str.Format(_T("%x"), nDec);
	return str;
}

CString C92Deal::HexToDec(CString strHex)//16-10
{
	CString strDec, strHexTemp;
	strHexTemp = strHex;
	DWORD dwHex = strtoul(strHexTemp, NULL,16);
	strDec.Format(_T("%ld"), dwHex);
	return strDec;
}

CString C92Deal::Get92FlagValue(CByteArray &byDataArray,  BYTE byFlag,  int nStartPos,  int & nAfterLength,  int nFormate)
{
	CString strResult = _T("");
	int nValueLength = 0;
	if (nStartPos+1>=byDataArray.GetSize())
	{
		return _T("error");
	}
	BYTE t1 = byDataArray.GetAt(nStartPos);
	int t_LNum =0;//设置位置的个数，0或者1
	if (t1!=byFlag)
	{
		return _T("error!");
	}
	BOOL bSpecial = FALSE;
	int t_Pos6 =(byFlag>>5)&0x01;//取第6位，用来判断1还是81.
	BYTE t2 = byDataArray.GetAt(nStartPos+1);
	if (t_Pos6==0&&nFormate!=0x811&&byFlag!=0x87)//82,85,80,83,87后面固定节01的,81, Security 特殊情况
	{
		t_LNum =1;
		if (t2>=0x80)//这对87后面有81的情况
		{
			 nValueLength=t2-0x80;
		}
		else nValueLength=t2;

	}
	else//60,A2,30,后面动态是0x81的
	{
		if(t2>=0x80)
		{
			t_LNum =1;
			nValueLength=t2-0x80;
		}
		else
		{
			if (byFlag==0x87&&nFormate==0)//goose 中的0x87
			{
				bSpecial = TRUE;
				t_LNum =1;
			}
			else
			{
				if (byFlag==0x87&&(nFormate==0x877||nFormate==0x878))// float 数据集
				{
					t_LNum =1;
					nValueLength=t2;		
				}
				else
				{
					t_LNum =0;
					nValueLength=1;	
				}

			}

		}
	}

	CString t_temp = _T("");
	switch(nFormate)
	{
	case 0:case 0x811:case 3:case 4:case 0x878:	//十进制数
		{
			BYTE t_H;
			CByteArray t_Array;
			if (nStartPos+1+t_LNum+nValueLength>byDataArray.GetSize())
			{
				return _T("error");
			}
			for (int j =0;j<nValueLength;j++)
			{
				CString t_str;
				t1 = byDataArray.GetAt(nStartPos+1+t_LNum+j);
				t_Array.Add(t1);
				if (j==0)
				{
					t_H = t1;
				}
				t_str.Format(_T("%.2X"),t1);
				t_temp+=t_str;	

			}
			if (nFormate==4)
			{
				if ((t_H>>7)&0x01==1)//负数情况
				{
					switch(nValueLength)
					{
					case 1:
						{
							int t_V =0xFF-(t_Array[0]);
							int t = -(t_V+1);
							strResult.Format(_T("%d"),t);
						}
						break;
					case 2:
						{
							int t_V =0xFFFF-(t_Array[1]+t_Array[0]*pow(2.0,8));
							int t = -(t_V+1);
							strResult.Format(_T("%d"),t);
						}
						break;
					case 3:
						{
							int t_V =0xFFFFFF-(t_Array[2]+t_Array[1]*pow(2.0,8)+t_Array[0]*pow(2.0,16));
							int t = -(t_V+1);
							strResult.Format(_T("%d"),t);
						}
						break;
					case 4:
						{
							int t_V =0xFFFFFFFF-(t_Array[3]+t_Array[2]*pow(2.0,8)+t_Array[1]*pow(2.0,16)+t_Array[0]*pow(2.0,24));
							int t = -(t_V+1);
							strResult.Format(_T("%d"),t);
						}
						break;
					case 5:
						{
							int t_V =0xFFFFFFFFFF-(t_Array[4]+t_Array[3]*pow(2.0,8)+t_Array[2]*pow(2.0,16)+t_Array[1]*pow(2.0,24)+t_Array[0]*pow(2.0,32));
							int t = -(t_V+1);
							strResult.Format(_T("%d"),t);
						}
						break;
					}
				}	
				else 
				{
					if(t_temp.GetLength()>8)
					{
						strResult.Format(_T("%u"),GetIntegerFromString(t_temp));
					}
					else strResult.Format(_T("%d"),GetIntegerFromString(t_temp));
				}
			}
			else
			{
				if (nFormate==3)
				{
					strResult.Format(_T("%u"),GetIntegerFromString(t_temp));	
				}
				else strResult.Format(_T("%d"),GetIntegerFromString(t_temp));
			}
	
		}
		break;
	case 1://字符串
		if (nStartPos+1+t_LNum+nValueLength>byDataArray.GetSize())
		{
			strResult = _T("");
		}
		else
		{
			for (int j =0;j<nValueLength;j++)
			{
				CString t_str;
				t1 = byDataArray.GetAt(nStartPos+1+t_LNum+j);
				t_str.Format(_T("%C"),t1);
				t_temp+=t_str;
			}
			strResult = t_temp;

		}

		break;
	case 0x8C1://6位时间
		{
			if (nStartPos+6>=byDataArray.GetSize())
			{
				return _T("0");
			}
			BYTE t6 =  byDataArray.GetAt(nStartPos+1+t_LNum);	
			BYTE t5 =  byDataArray.GetAt(nStartPos+1+t_LNum+1);


			BYTE t4 =  byDataArray.GetAt(nStartPos+1+t_LNum+2);	
			BYTE t3 =  byDataArray.GetAt(nStartPos+1+t_LNum+3);
			BYTE t2 =  byDataArray.GetAt(nStartPos+1+t_LNum+4);	
			BYTE t1 =  byDataArray.GetAt(nStartPos+1+t_LNum+5);
					
			double t_time = t1+t2*pow(2.0,8);

			double t_mstime =  t3+t4*pow(2.0,8)+t5*pow(2.0,16)+t6*pow(2.0,24);
			
			int t_H = t_mstime/(1000*60*60);

			int t_M =  (t_mstime-t_H*(1000*60*60))/(1000*60);

			int t_S = (t_mstime-t_H*(1000*60*60)-t_M*(1000*60))/1000;

			CTime t_1984Time(1984,1,1,0,0,0);
			t_1984Time += CTimeSpan(t_time,t_H,t_M,t_S); 
 			CString str = t_1984Time.Format("%Y-%m-%d %H:%M:%S");
 			strResult=str;
		}
		break;
	case 2://格林尼治时间
		{
			if (nStartPos+8>=byDataArray.GetSize())
			{
				return _T("0");
			}
			BYTE t4 =  byDataArray.GetAt(nStartPos+1+t_LNum);	
			BYTE t3 =  byDataArray.GetAt(nStartPos+1+t_LNum+1);
			BYTE t2 =  byDataArray.GetAt(nStartPos+1+t_LNum+2);
			BYTE t1 =  byDataArray.GetAt(nStartPos+1+t_LNum+3);
			double t_time = t1+t2*pow(2.0,8)+t3*pow(2.0,16)+t4*pow(2.0,24);
			CTime time = (CTime)(int)t_time;
			CString str = time.Format("%Y-%m-%d %H:%M:%S");

			t4 =  byDataArray.GetAt(nStartPos+1+t_LNum+4);	
			t3 =  byDataArray.GetAt(nStartPos+1+t_LNum+5);
			t2 =  byDataArray.GetAt(nStartPos+1+t_LNum+6);
			t1 =  byDataArray.GetAt(nStartPos+1+t_LNum+7);
    		double t_usTime = (/*t1+*/t2/**pow(2.0,8)*/+t3*pow(2.0,8)+t4*pow(2.0,16))/pow(2.0,/*t1*/24);
			CString str1;
			str1.Format(_T("%.9f"),/*(int)*/t_usTime);
			str1 = str1.Mid(2,10);
			str+=_T(".");
			str+=str1;
			str+=_T(" ");
			str+=_T("Tq:");
			CString t_QV;
			t_QV.Format(_T("%.2X"),t1);
			str+=t_QV;
			strResult=str;
		}
		break;
	case 0x84://goose BitString
		{	
			if (nStartPos+1+t_LNum+nValueLength>byDataArray.GetSize())
			{
				strResult=_T("0");
				break;
			}
			int t_SubLen =byDataArray.GetAt(nStartPos+1+t_LNum);

			for (int j =1;j<nValueLength;j++)
			{
				CString t_str;
				t1 = byDataArray.GetAt(nStartPos+1+t_LNum+j);
				t_str.Format(_T("%.2X"),t1);
				t_temp+=t_str;	
			}

			CString t_Bin = HexToBin(t_temp);
			int t_RL = t_Bin.GetLength();
			for (int i=t_RL;i<(nValueLength-1)*8;i++)
			{
				t_Bin.Insert(0,_T('0'));
			}
			strResult =t_Bin.Mid(0,t_Bin.GetLength()-t_SubLen);
		}
		break;
	case 0x87:
		for (int j =0;j<nValueLength;j++)
		{
			CString t_str;
			t1 = byDataArray.GetAt(nStartPos+1+t_LNum+j);
			t_str.Format(_T("%.2X"),t1);
			t_temp+=t_str;	

		}
		strResult.Format(_T("%d"),GetIntegerFromString(t_temp));
		break;
	case 0x877://Float 解码
		{
			if (nStartPos+2+t_LNum+3>=byDataArray.GetSize())
			{
				return _T("error");
			}
			ConverStruct t_s;
			int m =0;
			for (int j =3;j>=0;j--)
			{
				CString t_str;
				t1 = byDataArray.GetAt(nStartPos+2+t_LNum+j);
				t_s.b[m] =t1;
				m++;
			}
			strResult.Format(_T("%f"),t_s.f);		
			break;
		}
		break;
	case 0x872:
		CString temp1 = _T("");
		for (int j = 0 ; j < nValueLength; j++)
		{
			CString t_str;
			t1 = byDataArray.GetAt(nStartPos + 1 + t_LNum + j);
			t_str.Format(_T("%.2X"),t1);
			temp1+=t_str;	

		}
		int t_SeqLength = GetIntegerFromString(temp1);
		for (int j =0;j<t_SeqLength;j++)
		{
			CString t_str;
			int t_PosV = nStartPos+nValueLength+1+t_LNum+j;
			if (t_PosV>=byDataArray.GetSize())
			{
				break;
			}
			t1 = byDataArray.GetAt(t_PosV);
			t_str.Format(_T("%.2X"),t1);
			t_temp+=t_str;	

		}
		strResult=t_temp;
		break;
	}
	if (!bSpecial)
	{
		nAfterLength  = nValueLength+t_LNum+1;
	}
	else nAfterLength  = nValueLength+t_LNum+1+1;

	return strResult;
}

unsigned int C92Deal::GetIntegerFromString(CString pStr)
{
	unsigned int nValue  = 0;
	for (int i = 0; i <  pStr.GetLength(); i++)
	{
		int nLetterValue ;

		switch (pStr.GetAt(i))
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
		default:nLetterValue = pStr.GetAt(i) - '0';

		}
		nValue = nValue * 16 + nLetterValue; //16进制
	}
	return nValue;
}

int C92Deal::Get60AfterLength(CByteArray &byDataArray,int m_nOffset)
{
	BYTE t_60Value = byDataArray.GetAt(26+m_nOffset);
	if (t_60Value ==0x60)
	{
		BYTE t1=  byDataArray.GetAt(26+m_nOffset+1);
		if(t1>0x80)
		{
			return 3;
		}
		else
		{
			if (t1>=0x01&&t1<=0x3C)
			{	
				return 3;

			}
			else 
			{
				return 2;

			}
		}
	}

	return 0;
}

CString C92Deal::GetValueFromByteArray(CByteArray &m_Array,int nStartPos,int m_Length)
{
	CString strResult = _T("");
	for (int i =0;i<m_Length;i++)
	{
		CString temp;
		BYTE t_Byte = m_Array.GetAt(nStartPos+i);
		temp.Format(_T("%.2X"),t_Byte);
		strResult+=temp;

	}
	return strResult;
}
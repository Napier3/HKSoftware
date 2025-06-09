#include "StdAfx.h"
#include "GetInforFormVector.h"

#include "C92Deal.h"

CGetInforFormVector::CGetInforFormVector(void)
{

}

CGetInforFormVector::~CGetInforFormVector(void)
{
}

/*
函数理解说明：通过Pro里边给定的信息从DataArray里提取出来信息，获取该报文信息是GOOSE，SMV 9-1 还是 9-2。
*/
CString CGetInforFormVector::GetProtocolType(CDoMessage * pDo, CPacket &Pro, int &nTypeValue, int &nSmvOrGoose, int &n91Or92, int &nOffset)
{
	BYTE t1,  t2, t3, t4;
	int  nStartPos  = Pro.m_nHeadStartPos  + 16;
	t4 = pDo->DataArray.GetAt(nStartPos + 12);
	//t4 = Pro.m_pBuffer[nStartPos + 12];

	t3 = pDo->DataArray.GetAt(nStartPos + 13);

	t4 = pDo->DataArray.GetAt(nStartPos + 12);
	t3 = pDo->DataArray.GetAt(nStartPos + 13);

	int nType  =  (int)t4 * pow(2.0,  8)  +  t3;
	switch(nType)
	{
		case 33024://0x8100 goose or smv
			{
				t2 = pDo->DataArray.GetAt(nStartPos + 16);
				t1 = pDo->DataArray.GetAt(nStartPos + 17);
				nSmvOrGoose = (int)t2 * pow(2.0, 8)  +  t1;
				if(nSmvOrGoose ==35002)
				{
					n91Or92 = pDo->DataArray.GetAt(nStartPos + 26);//0x60
					switch(n91Or92)
					{
					case 0x60:
						{
							nTypeValue = IEC_SMV92;
							return _T("IEC_SMV92");
						}
						break;
					case 0x80:
						{
							BYTE t_80NextPos = pDo->DataArray.GetAt(nStartPos + 27);
							if (t_80NextPos>=0x80)
							{
								nOffset += 1;
							}
							nTypeValue = IEC_SMV91;
							return _T("IEC_SMV91");
						}
						break;
					default:
						{
							nTypeValue = PRO_OTHER;
							CString t_TypeString = _T("");
							t_TypeString.Format(_T("0x%.2X%.2X"),t4,t3);
							return t_TypeString;
						}
					}
				}	
				else
				{	if(nSmvOrGoose ==35000)
					{
						nTypeValue = IEC_GOOSE;
						return _T("IEC_GOOSE");
					}
					else
					{
						if (nSmvOrGoose ==0x88F7)
						{
							nTypeValue = PRO_1588;
							return _T("IEEE_1588");
						}
					}
				}				
			}
			break;
		case 35000://0x88B8 GOOSE	
			{
				if (nOffset==0)
				{
					nOffset  = -4;
				}
				nSmvOrGoose = 35000;
				nTypeValue = IEC_GOOSE;
				return _T("IEC_GOOSE");
			}
			break;
		case 35002://0x88BA SMV
			{
				if (nOffset==0)
				{
					nOffset  = -4;
				}
				n91Or92 = pDo->DataArray.GetAt(nStartPos + nOffset + 26);//0x60
				switch(n91Or92)
				{
				case 0x60:
					{
						nTypeValue  =  IEC_SMV92;
						return _T("IEC_SMV92");
					}
					break;
				case 0x80:
					{
						BYTE t_80NextPos = pDo->DataArray.GetAt(nStartPos + nOffset + 27);
						if (t_80NextPos>=0x80)
						{
							nOffset += 1;
						}
						nTypeValue = IEC_SMV91;
						return _T("IEC_SMV91");
					}
				default:
					{
						nTypeValue = PRO_OTHER;
						CString t_TypeString = _T("");
						t_TypeString.Format(_T("0x%.2X%.2X"), t4, t3);
						return t_TypeString;
					}
					break;

				}
			}
		case 0x88F7://1588
			{
				if (nOffset==0)
				{
					nOffset  = -4;
				}
				nTypeValue  = PRO_1588;
				return _T("IEEE_1588");
			}
			break;
		case 2048://0x0800 IP 
			{
				if (nOffset==0)
				{
					nOffset =-4;//TCP 报文无多余
				}
				BYTE t_TcpOrUdp;
				t_TcpOrUdp = pDo->DataArray.GetAt(nStartPos/*+nOffset*/+23);
				switch(t_TcpOrUdp)
				{
				case 0x06://tcp
					nTypeValue = PRO_TCP;
					return _T("TCP/MMS");
					break;
				case 0x11://udp
					nTypeValue = PRO_UDP;
					return _T("UDP");
					break;
				default:
					{
						nTypeValue  = PRO_OTHER;
						CString t_TypeString = _T("");
						t_TypeString.Format(_T("0x%.2X%.2X"),  t4,  t3);
						return t_TypeString;
					}
				}
			}
			break;
		case 0x0806:
			nTypeValue = PRO_ARP;
			return _T("ARP");
			break;
		default:
			{
				nTypeValue = PRO_OTHER;
				CString t_TypeString = _T("");
				t_TypeString.Format(_T("0x%.2X%.2X"),  t4,  t3);
				return t_TypeString;
			}
	}	
	return _T("");
}

double CGetInforFormVector::GetDifTimeDouble(CDoMessage * pDo,  CPacket & ProCur, CPacket & ProUp, int nSecondMode)
{
	int nDataTimePos  = ProCur.m_nHeadStartPos;
	int nSecimePos = ProCur.m_nHeadStartPos + 4;
	
	BYTE t4 =  pDo->DataArray.GetAt(nDataTimePos);	
	BYTE t3 =  pDo->DataArray.GetAt(nDataTimePos + 1);
	BYTE t2 =  pDo->DataArray.GetAt(nDataTimePos + 2);
	BYTE t1 =  pDo->DataArray.GetAt(nDataTimePos + 3);
	double t_time1 = t4 + t3 * pow(2.0,8) + t2 * pow(2.0, 16) + t1 * pow(2.0,  24);

	t4 =  pDo->DataArray.GetAt(nSecimePos);	
	t3 =  pDo->DataArray.GetAt(nSecimePos + 1);
	t2 =  pDo->DataArray.GetAt(nSecimePos + 2);
	t1 =  pDo->DataArray.GetAt(nSecimePos + 3);
	double t_usTime1 = t4 + t3 * pow(2.0, 8) + t2  * pow(2.0, 16)  + t1 * pow(2.0,  24);

	nDataTimePos = ProUp.m_nHeadStartPos;
	nSecimePos = ProUp.m_nHeadStartPos + 4;
	t4 =  pDo->DataArray.GetAt(nDataTimePos);	
	t3 =  pDo->DataArray.GetAt(nDataTimePos + 1);
	t2 =  pDo->DataArray.GetAt(nDataTimePos + 2);
	t1 =  pDo->DataArray.GetAt(nDataTimePos + 3);
	double t_time2 = t4 + t3 * pow(2.0, 8) + t2 * pow(2.0, 16) + t1 * pow(2.0, 24);

	t4 =  pDo->DataArray.GetAt(nSecimePos);	
	t3 =  pDo->DataArray.GetAt(nSecimePos + 1);
	t2 =  pDo->DataArray.GetAt(nSecimePos + 2);
	t1 =  pDo->DataArray.GetAt(nSecimePos + 3);
	double t_usTime2 = t4 + t3 * pow(2.0, 8 ) + t2 * pow(2.0, 16) + t1 * pow(2.0, 24);

	int t_SecDif = t_time1 - t_time2;
	double strResult;
	if (nSecondMode==1)
	{
		double t_d = t_usTime1 - t_usTime2;
		double t1 = t_d/double(1000000.0);
		double t2 = t1/double(pDo->m_usOrns);
		strResult  = t_SecDif + t_d/(double)(1000000.0 * pDo->m_usOrns);
	}
	else 
		strResult = t_SecDif  * 1000000 * pDo->m_usOrns + t_usTime1  -  t_usTime2;
	
	return strResult;
}

CString CGetInforFormVector::GetDifTimeDoubleSecondMode(CDoMessage * pDo,  CPacket & ProCur,   CPacket & ProUp)
{
	int nDataTimePos = ProCur.m_nHeadStartPos;
	int nSecimePos  = ProCur.m_nHeadStartPos+4;
	BYTE t4 =  pDo->DataArray.GetAt(nDataTimePos);	
	BYTE t3 =  pDo->DataArray.GetAt(nDataTimePos + 1);
	BYTE t2 =  pDo->DataArray.GetAt(nDataTimePos + 2);
	BYTE t1 =  pDo->DataArray.GetAt(nDataTimePos + 3);
	double t_time1 = t4 + t3 * pow(2.0, 8) + t2  * pow(2.0,16) + t1 * pow(2.0, 24);

	t4 =  pDo->DataArray.GetAt(nSecimePos);	
	t3 =  pDo->DataArray.GetAt(nSecimePos + 1);
	t2 =  pDo->DataArray.GetAt(nSecimePos + 2);
	t1 =  pDo->DataArray.GetAt(nSecimePos + 3);
	double t_usTime1 = t4 + t3 * pow(2.0, 8) + t2 * pow(2.0, 16) + t1 * pow(2.0, 24);

	nDataTimePos = ProUp.m_nHeadStartPos;
	nSecimePos = ProUp.m_nHeadStartPos  +  4;
	t4 =  pDo->DataArray.GetAt(nDataTimePos);	
	t3 =  pDo->DataArray.GetAt(nDataTimePos + 1);
	t2 =  pDo->DataArray.GetAt(nDataTimePos + 2);
	t1 =  pDo->DataArray.GetAt(nDataTimePos + 3);
	double t_time2 = t4 + t3 * pow(2.0, 8) + t2 * pow(2.0, 16) + t1 * pow(2.0, 24);

	t4 =  pDo->DataArray.GetAt(nSecimePos);	
	t3 =  pDo->DataArray.GetAt(nSecimePos + 1);
	t2 =  pDo->DataArray.GetAt(nSecimePos + 2);
	t1 =  pDo->DataArray.GetAt(nSecimePos + 3);
	unsigned long t_usTime2 = t4 + t3 * pow(2.0, 8) + t2 * pow(2.0, 16) + t1 * pow(2.0, 24);
	unsigned long  t_Result1;
	double t_Result2;
	int t_SecDif = t_time1 - t_time2;
	double t_usDif = (t_usTime1 - t_usTime2);
	//if(t_SecDif==1000)
	if(t_SecDif  > 1 && pDo->m_usOrns==1000)
	{
		t_Result2  = t_SecDif + t_usDif/1000000000;
	}
	else 
		t_Result1 = t_SecDif * 1000000 * pDo->m_usOrns + (t_usTime1  -  t_usTime2);
	CString temp;
	int nType = 0;
	if (nType==1)
	{
		temp.Format(_T("%d"),  t_SecDif);
	}
	else
	{
		if(t_SecDif>1&&pDo->m_usOrns==1000)
		{
			temp.Format(_T("%.9f s"),  t_Result2);
		}
		else
		{
			if(pDo->m_usOrns==1000)
				temp.Format(_T("%d ns"),  t_Result1);
			else
				temp.Format(_T("%d μs"),  t_Result1);
		}
	}
	temp.Replace(_T("-"),  _T(""));
	return temp;
}

unsigned long CGetInforFormVector::GetDifTimeINT(CDoMessage * pDo, CPacket &ProCur, CPacket &ProUp,int nSecondMode)//0:正常模式，1:微妙陌生
{
	int nDataTimePos = ProCur.m_nHeadStartPos;
	int nSecimePos = ProCur.m_nHeadStartPos+4;
	BYTE t4 =  pDo->DataArray.GetAt(nDataTimePos);	
	BYTE t3 =  pDo->DataArray.GetAt(nDataTimePos+1);
	BYTE t2 =  pDo->DataArray.GetAt(nDataTimePos+2);
	BYTE t1 =  pDo->DataArray.GetAt(nDataTimePos+3);
	double t_time1 = t4+t3*pow(2.0,8)+t2*pow(2.0,16)+t1*pow(2.0,24);

	t4 =  pDo->DataArray.GetAt(nSecimePos);	
	t3 =  pDo->DataArray.GetAt(nSecimePos+1);
	t2 =  pDo->DataArray.GetAt(nSecimePos+2);
	t1 =  pDo->DataArray.GetAt(nSecimePos+3);
	double t_usTime1 = t4+t3*pow(2.0,8)+t2*pow(2.0,16)+t1*pow(2.0,24);

	nDataTimePos = ProUp.m_nHeadStartPos;
	nSecimePos = ProUp.m_nHeadStartPos+4;
	t4 =  pDo->DataArray.GetAt(nDataTimePos);	
	t3 =  pDo->DataArray.GetAt(nDataTimePos+1);
	t2 =  pDo->DataArray.GetAt(nDataTimePos+2);
	t1 =  pDo->DataArray.GetAt(nDataTimePos+3);
	double t_time2 = t4+t3*pow(2.0,8)+t2*pow(2.0,16)+t1*pow(2.0,24);

	t4 =  pDo->DataArray.GetAt(nSecimePos);	
	t3 =  pDo->DataArray.GetAt(nSecimePos+1);
	t2 =  pDo->DataArray.GetAt(nSecimePos+2);
	t1 =  pDo->DataArray.GetAt(nSecimePos+3);
	double t_usTime2 = t4+t3*pow(2.0,8)+t2*pow(2.0,16)+t1*pow(2.0,24);

	int t_SecDif = t_time1-t_time2;
	unsigned long strResult;
	if(nSecondMode==0)//正常模式，取决于pDo->m_usOrns的值
	{
		 strResult = t_SecDif*1000000*pDo->m_usOrns+t_usTime1-t_usTime2;
	}
	else 
	{
		 strResult = t_SecDif*1000+(t_usTime1-t_usTime2)/(pDo->m_usOrns*1000);
	}
	return strResult;
}

CString CGetInforFormVector::GetDifTimeString(CDoMessage * pDo,CPacket &ProCur,CPacket &ProUp,int nType)
{
	int nDataTimePos = ProCur.m_nHeadStartPos;
	int nSecimePos = ProCur.m_nHeadStartPos+4;
	BYTE t4 =  pDo->DataArray.GetAt(nDataTimePos);	
	BYTE t3 =  pDo->DataArray.GetAt(nDataTimePos+1);
	BYTE t2 =  pDo->DataArray.GetAt(nDataTimePos+2);
	BYTE t1 =  pDo->DataArray.GetAt(nDataTimePos+3);
	double t_time1 = t4+t3*pow(2.0,8)+t2*pow(2.0,16)+t1*pow(2.0,24);

	t4 =  pDo->DataArray.GetAt(nSecimePos);	
	t3 =  pDo->DataArray.GetAt(nSecimePos+1);
	t2 =  pDo->DataArray.GetAt(nSecimePos+2);
	t1 =  pDo->DataArray.GetAt(nSecimePos+3);
	double t_usTime1 = t4+t3*pow(2.0,8)+t2*pow(2.0,16)+t1*pow(2.0,24);

	nDataTimePos = ProUp.m_nHeadStartPos;
	nSecimePos = ProUp.m_nHeadStartPos+4;
	t4 =  pDo->DataArray.GetAt(nDataTimePos);	
	t3 =  pDo->DataArray.GetAt(nDataTimePos+1);
	t2 =  pDo->DataArray.GetAt(nDataTimePos+2);
	t1 =  pDo->DataArray.GetAt(nDataTimePos+3);
	double t_time2 = t4+t3*pow(2.0,8)+t2*pow(2.0,16)+t1*pow(2.0,24);

	t4 =  pDo->DataArray.GetAt(nSecimePos);	
	t3 =  pDo->DataArray.GetAt(nSecimePos+1);
	t2 =  pDo->DataArray.GetAt(nSecimePos+2);
	t1 =  pDo->DataArray.GetAt(nSecimePos+3);

	unsigned long t_usTime2   =   t4+t3*pow(2.0,8)+t2*pow(2.0,16)+t1*pow(2.0,24);
	long  t_Result1;
	double t_Result2;
	int t_SecDif   =  t_time1  -  t_time2;
	double t_usDif  = (t_usTime1  -  t_usTime2);

	if(t_SecDif  >  1  &&  pDo->m_usOrns==1000)
	{
		t_Result2 = t_SecDif  +  t_usDif / 1000000000;
	}
	else
		t_Result1 = t_SecDif  *  1000000  *  pDo->m_usOrns  +  (t_usTime1  -  t_usTime2);

	CString temp;
	if (nType==1)
	{
		temp.Format(_T("%d"),t_SecDif);
	}
	else if (nType==2)
	{
		if(t_SecDif  >  1  &&  pDo->m_usOrns==1000)
		{
			temp.Format(_T("%.9f s"),  t_Result2);		
		}
		else
		{
			temp.Format(_T("%d"),t_Result1);	
			CString byTemp = temp;
			int t_FH = byTemp.Replace(_T("-"),_T(""));
			int t_PNum = byTemp.GetLength()/3;
			int t_YNum = byTemp.GetLength()%3;
			
			int t_C   =   0;
			for (int j =  0;  j  <  t_PNum;  j++)
			{
				if (t_YNum==0&&j==0)
				{
					continue;
				}
				
				byTemp.Insert(t_YNum  +  j  *  3  +  t_C,  ' ');
				t_C++;
			}

			CString temp1 = _T("");
			if (t_FH==1)
			{
				temp1+=_T("-");
			}

			if(pDo->m_usOrns==1000)
				temp.Format(_T("%s ns"),  byTemp);
			else 
				temp.Format(_T("%s μs"),  byTemp);

			temp1+=  temp;

			temp   =  temp1;			
		}
	}
	else
	{
		if(t_SecDif>1&&pDo->m_usOrns==1000)
		{
			temp.Format(_T("%.9f s"),   t_Result2);
		}
		else
		{
			if(pDo->m_usOrns==1000)
				temp.Format(_T("%d ns"),   t_Result1);
			else
				temp.Format(_T("%d μs"),   t_Result1);
		}
	}

	return temp;
}

CString CGetInforFormVector::GetTimeString(CDoMessage * pDo, CPacket &Pro)
{
	int nDataTimePos = Pro.m_nHeadStartPos;
	int nSecimePos = Pro.m_nHeadStartPos+4;
	BYTE t4 =  pDo->DataArray.GetAt(nDataTimePos);	
	BYTE t3 =  pDo->DataArray.GetAt(nDataTimePos+1);
	BYTE t2 =  pDo->DataArray.GetAt(nDataTimePos+2);
	BYTE t1 =  pDo->DataArray.GetAt(nDataTimePos+3);
	double t_time = t4+t3*pow(2.0,8)+t2*pow(2.0,16)+t1*pow(2.0,24);
	CTime time = (CTime)(int)t_time;
	CString str = time.Format("%Y-%m-%d %H:%M:%S");

	t4 =  pDo->DataArray.GetAt(nSecimePos);	
	t3 =  pDo->DataArray.GetAt(nSecimePos+1);
	t2 =  pDo->DataArray.GetAt(nSecimePos+2);
	t1 =  pDo->DataArray.GetAt(nSecimePos+3);
	double t_usTime = t4+t3*pow(2.0,8)+t2*pow(2.0,16)+t1*pow(2.0,24);

	CString str1;
	if(pDo->m_usOrns==1000)
	{
		str1.Format(_T("%.9f"),(t_usTime/1000000000.0));
		str1.Delete(0,1);
		str+=str1;
		if (t_usTime>1000000000.0)
		{
			str+=_T(" Abnormal:ns 差大于1秒");
		}
	}
	else 
	{
		str1.Format(_T("%.6f"),(t_usTime/1000000.0));
		str1.Delete(0,1);
		str+=str1;
	}
	return str;

}
void CGetInforFormVector::GetAppID(CDoMessage * pDo,CPacket &Pro,CByteArray &byDataArray,int nOffset)
{
	byDataArray.RemoveAll();
	BYTE t1,t2;
	t1 = pDo->DataArray.GetAt(Pro.m_nHeadStartPos+16+18+nOffset);
	t2 = pDo->DataArray.GetAt(Pro.m_nHeadStartPos+16+19+nOffset);
	byDataArray.Add(t1);
	byDataArray.Add(t2);
}

void CGetInforFormVector::Get1588AppID(CDoMessage * pDo,CPacket &Pro,CByteArray &byDataArray,int nOffset)
{
	byDataArray.RemoveAll();
	BYTE t1,t2;
	t1 = pDo->DataArray.GetAt(Pro.m_nHeadStartPos+16+44+nOffset);
	t2 = pDo->DataArray.GetAt(Pro.m_nHeadStartPos+16+45+nOffset);
	byDataArray.Add(t1);
	byDataArray.Add(t2);
}

CString CGetInforFormVector::Get1588SqID(CDoMessage * pDo,CPacket &Pro,CByteArray &byDataArray,int nOffset)
{
	byDataArray.RemoveAll();
	BYTE t1,t2;
	t1 = pDo->DataArray.GetAt(Pro.m_nHeadStartPos+16+48+nOffset);
	t2 = pDo->DataArray.GetAt(Pro.m_nHeadStartPos+16+49+nOffset);
	int t_Sqid = t2+t1*pow(2.0,8);
	CString t_strSqID;
	t_strSqID.Format(_T("%d"),t_Sqid);
	return t_strSqID;
}

void CGetInforFormVector::Get92Classification(CDoMessage * pDo)
{
	int nType ;
	int nOffset = 0;

	CPacket & pPro = pDo->m_NewPacketVector[pDo->m_92Vector[0]];

	CGetInforFormVector::GetProtocolType(pDo,  pPro, nType,  nType,  nType,  nOffset);

	int t_92Size = pDo->m_92Vector.size();	

	int n92FirstSmpCnt =0;
	int n92CurSmpCnt = 0;
	int n92MaxSmpCnt = 0;	

	BOOL bFindMaxSmpCnt = TRUE;

	for (int i   =  0;  i  <  t_92Size;  i++)
	{	
		CByteArray t_Array;
		int q  = pDo->m_92Vector[i];
		CPacket & pPro  = pDo->m_NewPacketVector[pDo->m_92Vector[i]];
		if (i==0)
		{
			Content content;	
			nOffset  =  0;

			CGetInforFormVector::GetProtocolType(pDo,  pPro,  nType,  nType,  nType,  nOffset);
			content.m_nOffset  = nOffset;

			CGetInforFormVector::GetDesMacArray(pDo,   pPro,  t_Array);
			for (int m  =  0 ;  m  <  6;  m++)
			{
				content.m_DES[m] = t_Array.GetAt(m);
			}

			CGetInforFormVector::GetSRCMacArray(pDo,  pPro,  t_Array);
			for (int m  =  0;  m  <  6;  m++)
			{
				content.m_SRC[m]   =   t_Array.GetAt(m);
			}

			CGetInforFormVector::GetAppID(pDo,   pPro ,   t_Array,  nOffset);
			for (int m  =  0;  m  <  2;  m++)
			{
				content.m_APPID[m]   =  t_Array.GetAt(m);
			}

			content.m_Vector.push_back(pDo->m_92Vector[i]);
			content.m_bAbnoState  =  FALSE;
			content.m_nPrePacketSize  = pPro.m_nDataPackLength;
			content.m_nMaxSmpCnt   =  4000;
			pDo->m_92KindsVector.push_back(content);
		}
		else
		{
		
			//CGetInforFormVector::GetProtocolType(pDo,pPro,nType,nType,nType,nOffset);
			CGetInforFormVector::GetDesMacArray(pDo,   pPro,  t_Array);
			int j;

			for (j  =  0;  j  <  pDo->m_92KindsVector.size();  j++)
			{
				Content &content   =  pDo->m_92KindsVector[j];
				if (CGetInforFormVector::CompareByteArray(t_Array,   content.m_DES))//目的地址相同
				{
					content.m_Vector.push_back(pDo->m_92Vector[i]);
					break;
				}
			}

			if (j==pDo->m_92KindsVector.size())
			{
				Content content;	

				nOffset   =  0;

				CGetInforFormVector::GetProtocolType(pDo,   pPro,   nType,   nType,   nType,   nOffset);
				content.m_nOffset = nOffset;

				CGetInforFormVector::GetDesMacArray(pDo,pPro,t_Array);
				for (int m  =  0;  m  <  6;  m++)
				{
					content.m_DES[m]   = t_Array.GetAt(m);
				}

				CGetInforFormVector::GetSRCMacArray(pDo,pPro,t_Array);
				for (int m  =  0;  m  <  6;  m++)
				{
					content.m_SRC[m]    =  t_Array.GetAt(m);
				}

				CGetInforFormVector::GetAppID(pDo,pPro,t_Array,nOffset);
				for (int m  =  0;  m  <  2;  m++)
				{
					content.m_APPID[m]   = t_Array.GetAt(m);
				}
				content.m_Vector.push_back(pDo->m_92Vector[i]);
				content.m_bAbnoState  =   FALSE;
				content.m_nPrePacketSize  = pPro.m_nDataPackLength;
				content.m_nMaxSmpCnt   =   4000;
				pDo->m_92KindsVector.push_back(content);
			}

		}
	}


/*
对于程序的说明：
m_NewPacketVector里边存储的是PCAP报文中所有的一帧一帧的数据；
m_92KindsVector 里边存储得是PCAP中有多少个不同的MAC地址；比如有5个，或者10个；
Content &content   =  pDo->m_92KindsVector[m];
Content 中存储的是具体得每一个MAC相关的信息，比如MAC ，APPID，ASDU数量，最大m_nMaxSmpCnt个数，是否有异常信息等等；
最重要的是 Content.m_Vector 里头存储的是该APPID下的帧在大PACP中的序号，也就是在m_NewPacketVector中的序号；

*/

////////////////获取SmpCnt最大值和ASDU数目///////////
	for (int m  =  0;  m  <  pDo->m_92KindsVector.size();  m++)
	{
		n92FirstSmpCnt  = 0;

		Content &content   =  pDo->m_92KindsVector[m];

		int nSize   = content.m_Vector.size();
		if(nSize   >   20000)
			nSize  =  20000;	

		for (int n  =  0;  n  <  nSize;  n++)
		{
			CPacket   & pPro = pDo->m_NewPacketVector[content.m_Vector[n]];
			n92CurSmpCnt   =  CGetInforFormVector::GetSmpCntValue(pDo,   pPro,   0x60,   content.m_nOffset);
			if (n92CurSmpCnt  >=  n92FirstSmpCnt)
			{
				content.m_nASDUNum    = n92CurSmpCnt    -   n92FirstSmpCnt;					
				n92MaxSmpCnt  =  n92CurSmpCnt;
				n92FirstSmpCnt = n92CurSmpCnt;
			}
			else
			{
				content.m_nMaxSmpCnt   = n92MaxSmpCnt;
				break;

			}
		}
	}
}

void CGetInforFormVector::Get91Classification(CDoMessage * pDo)
{
	int nType ;
	int nOffset = 0;
	CPacket & pPro = pDo->m_NewPacketVector[pDo->m_91Vector[0]];
	CGetInforFormVector::GetProtocolType(pDo,pPro,nType,nType,nType,nOffset);
	int n91FirstSmpCnt =0;
	int n91CurSmpCnt = 0;
	int n91MaxSmpCnt = 0;	
	BOOL bFindMaxSmpCnt = TRUE;
	int t_91Size = pDo->m_91Vector.size();
	for (int i =0;i<t_91Size;i++)
	{	
		CByteArray t_Array;
		CPacket & pPro = pDo->m_NewPacketVector[pDo->m_91Vector[i]];
		if (i==0)
		{
			Content content;	
			CGetInforFormVector::GetDesMacArray(pDo,pPro,t_Array);
			for (int m=0;m<6;m++)
			{
				content.m_DES[m] = t_Array.GetAt(m);
			}
			CGetInforFormVector::GetSRCMacArray(pDo,pPro,t_Array);
			for (int m=0;m<6;m++)
			{
				content.m_SRC[m] = t_Array.GetAt(m);
			}

			CGetInforFormVector::GetAppID(pDo,pPro,t_Array,nOffset);
			for (int m=0;m<2;m++)
			{
				content.m_APPID[m] = t_Array.GetAt(m);
			}

			content.m_Vector.push_back(pDo->m_91Vector[i]);
			content.m_nMaxSmpCnt=4000;
			pDo->m_91KindsVector.push_back(content);

		}
		else
		{
			CGetInforFormVector::GetDesMacArray(pDo,pPro,t_Array);
			int j;
			for (j=0;j<pDo->m_91KindsVector.size();j++)
			{
				Content &content = pDo->m_91KindsVector[j];
				if (CGetInforFormVector::CompareByteArray(t_Array,content.m_DES))//目的地址相同
				{
					content.m_Vector.push_back(pDo->m_91Vector[i]);
					break;
				}
			}
			if (j==pDo->m_91KindsVector.size())
			{
				Content content;	
				CGetInforFormVector::GetDesMacArray(pDo,pPro,t_Array);
				for (int m=0;m<6;m++)
				{
					content.m_DES[m] = t_Array.GetAt(m);
				}
				CGetInforFormVector::GetSRCMacArray(pDo,pPro,t_Array);
				for (int m=0;m<6;m++)
				{
					content.m_SRC[m] = t_Array.GetAt(m);
				}
				CGetInforFormVector::GetAppID(pDo,pPro,t_Array,nOffset);
				for (int m=0;m<2;m++)
				{
					content.m_APPID[m] = t_Array.GetAt(m);
				}
				content.m_Vector.push_back(pDo->m_91Vector[i]);
				content.m_bAbnoState=FALSE;
							content.m_nMaxSmpCnt=4000;
				pDo->m_91KindsVector.push_back(content);
			}

		}
	}
	////////////////获取SmpCnt最大值和ASDU数目///////////
	for (int m=0;m<pDo->m_91KindsVector.size();m++)
	{
		n91FirstSmpCnt =0;
		Content &content = pDo->m_91KindsVector[m];
		int nSize = content.m_Vector.size();
		if(nSize  > 20000)
			nSize  =  20000;

		for (int n=0;n<nSize;n++)
		{
			CPacket & pPro = pDo->m_NewPacketVector[content.m_Vector[n]];
			n91CurSmpCnt =  CGetInforFormVector::GetSmpCntValue(pDo,pPro,0x80,nOffset);
			if (n91CurSmpCnt>=n91FirstSmpCnt)
			{
				content.m_nASDUNum = n91CurSmpCnt  -  n91FirstSmpCnt;					
				n91MaxSmpCnt = n91CurSmpCnt;
				n91FirstSmpCnt = n91CurSmpCnt;
			}
			else
			{
				content.m_nMaxSmpCnt = n91MaxSmpCnt;
				break;

			}
		}
	}
}

void CGetInforFormVector::GetOtherClassification(CDoMessage * pDo)
{
	int nType ;
	int nOffset = 0;
	CPacket & pPro = pDo->m_NewPacketVector[pDo->m_OtherVector[0]];
//	CString t_strType = CGetInforFormVector::GetProtocolType(pDo,pPro,nType,nType,nType,nOffset);

	int t_OtherSize = pDo->m_OtherVector.size();
	for (int i =0;i<t_OtherSize;i++)
	{	
		CByteArray t_Array;
		int q = pDo->m_OtherVector[i];
		CPacket & pPro = pDo->m_NewPacketVector[pDo->m_OtherVector[i]];
		if (i==0)
		{
			Content content;	
			CGetInforFormVector::GetDesMacArray(pDo,pPro,t_Array);
			for (int m=0;m<6;m++)
			{
				content.m_DES[m] = t_Array.GetAt(m);
			}
			CGetInforFormVector::GetSRCMacArray(pDo,pPro,t_Array);
			for (int m=0;m<6;m++)
			{
				content.m_SRC[m] = t_Array.GetAt(m);
			}
			for (int m=0;m<2;m++)
			{
				content.m_APPID[m] = 0x00;
			}
			CString t_strType = CGetInforFormVector::GetProtocolType(pDo,pPro,nType,nType,nType,nOffset);
			content.m_OtherType = t_strType;
			content.m_Vector.push_back(pDo->m_OtherVector[i]);
			pDo->m_OtherKindsVector.push_back(content);

		}
		else
		{
			CGetInforFormVector::GetDesMacArray(pDo,pPro,t_Array);
			int j;
			for (j=0;j<pDo->m_OtherKindsVector.size();j++)
			{
				Content &content = pDo->m_OtherKindsVector[j];
				if (CGetInforFormVector::CompareByteArray(t_Array,content.m_DES))//目的地址相同
				{
					content.m_Vector.push_back(pDo->m_OtherVector[i]);
					break;
				}
			}
			if (j==pDo->m_OtherKindsVector.size())
			{
				Content content;	
				CGetInforFormVector::GetDesMacArray(pDo,pPro,t_Array);
				for (int m=0;m<6;m++)
				{
					content.m_DES[m] = t_Array.GetAt(m);
				}
				CGetInforFormVector::GetSRCMacArray(pDo,pPro,t_Array);
				for (int m=0;m<6;m++)
				{
					content.m_SRC[m] = t_Array.GetAt(m);
				}
				for (int m=0;m<2;m++)
				{
					content.m_APPID[m] = 0x00;
				}
				CString t_strType = CGetInforFormVector::GetProtocolType(pDo,pPro,nType,nType,nType,nOffset);
				content.m_OtherType = t_strType;
				content.m_Vector.push_back(pDo->m_OtherVector[i]);
				pDo->m_OtherKindsVector.push_back(content);
			}

		}
	}
}

void CGetInforFormVector::Get1588Classification(CDoMessage * pDo)
{
	int nType ;
	int nOffset = 0;
	CPacket & pPro = pDo->m_NewPacketVector[pDo->m_1588Vector[0]];
	CGetInforFormVector::GetProtocolType(pDo,pPro,nType,nType,nType,nOffset);
	int n1588Size = pDo->m_1588Vector.size();
	for (int i =0;  i<  n1588Size; i++)
	{	
		CByteArray t_Array;
		int q = pDo->m_1588Vector[i];
		CPacket & pPro = pDo->m_NewPacketVector[pDo->m_1588Vector[i]];
		if (i==0)
		{
			Content content;	
			CGetInforFormVector::GetDesMacArray(pDo,pPro,t_Array);
			for (int m=0;m<6;m++)
			{
				content.m_DES[m] = t_Array.GetAt(m);
			}
			CGetInforFormVector::GetSRCMacArray(pDo,pPro,t_Array);
			for (int m=0;m<6;m++)
			{
				content.m_SRC[m] = t_Array.GetAt(m);
			}

			CGetInforFormVector::Get1588AppID(pDo,pPro,t_Array,nOffset);
			for (int m=0;m<2;m++)
			{
				content.m_APPID[m] = t_Array.GetAt(m);
			}

			content.m_Vector.push_back(pDo->m_1588Vector[i]);
			pDo->m_1588eKindsVector.push_back(content);

		}
		else
		{
			CGetInforFormVector::GetDesMacArray(pDo,pPro,t_Array);
			int j;
			for (j=0;j<pDo->m_1588eKindsVector.size();j++)
			{
				Content &content = pDo->m_1588eKindsVector[j];
				if (CGetInforFormVector::CompareByteArray(t_Array,content.m_DES))//目的地址相同
				{
					content.m_Vector.push_back(pDo->m_1588Vector[i]);
					break;
				}
			}
			if (j==pDo->m_1588eKindsVector.size())
			{
				Content content;	
				CGetInforFormVector::GetDesMacArray(pDo,pPro,t_Array);
				for (int m=0;m<6;m++)
				{
					content.m_DES[m] = t_Array.GetAt(m);
				}
				CGetInforFormVector::GetSRCMacArray(pDo,pPro,t_Array);
				for (int m=0;m<6;m++)
				{
					content.m_SRC[m] = t_Array.GetAt(m);
				}
				CGetInforFormVector::Get1588AppID(pDo,pPro,t_Array,nOffset);
				for (int m=0;m<2;m++)
				{
					content.m_APPID[m] = t_Array.GetAt(m);
				}
				content.m_Vector.push_back(pDo->m_1588Vector[i]);
				pDo->m_1588eKindsVector.push_back(content);
			}

		}
	}
}

void CGetInforFormVector::GetTcpClassification(CDoMessage * pDo)
{
	int nType ;
	int nOffset = 0;
	CPacket & pPro = pDo->m_NewPacketVector[pDo->m_TcpVector[0]];
	CGetInforFormVector::GetProtocolType(pDo,pPro,nType,nType,nType,nOffset);
	int t_TcpSize = pDo->m_TcpVector.size();		
	int nTcpAddPos;
	for (int i = 0;  i  <  t_TcpSize;  i++)
	{
		CByteArray t_Array;
		CPacket & pPro = pDo->m_NewPacketVector[pDo->m_TcpVector[i]];
		pPro.m_nInvokeID = -1;
		if (i==0)
		{
			TCPContent content;	
			CByteArray byDESArray,bySRCArray;

			BOOL bMMSMode = CGetInforFormVector::GetDESandSRCIP(pDo,pPro,byDESArray,bySRCArray,nTcpAddPos);
			for (int m=0;m<4;m++)
			{
				content.m_DES[m] = byDESArray.GetAt(m);
				content.m_SRC[m] = bySRCArray.GetAt(m);
			}
			if (bMMSMode)
			{	
				content.m_TcpAddPos = nTcpAddPos;
				content.m_MMSVector.push_back(pDo->m_TcpVector[i]);
			}
			else
			{
				pPro.SetAbronamlType(MMS_COMUNCATION);
				content.m_ComunicationVector.push_back(pDo->m_TcpVector[i]);
			}
		
			content.m_Vector.push_back(pDo->m_TcpVector[i]);
			pDo->m_TcpKindsVector.push_back(content);
		}
		else
		{
			CByteArray byDESArray,bySRCArray;
			BOOL bMMSMode = CGetInforFormVector::GetDESandSRCIP(pDo,pPro,byDESArray,bySRCArray,nTcpAddPos);
			int j;
			for (j=0;j<pDo->m_TcpKindsVector.size();j++)
			{
				TCPContent &content = pDo->m_TcpKindsVector[j];
				if (CGetInforFormVector::CompareByteArray(byDESArray,content.m_DES)&&CGetInforFormVector::CompareByteArray(bySRCArray,content.m_SRC))//目的地址相同
				{
					if (bMMSMode)
					{
						content.m_TcpAddPos = nTcpAddPos;
						content.m_MMSVector.push_back(pDo->m_TcpVector[i]);
					}
					else
					{
						pPro.SetAbronamlType(MMS_COMUNCATION);
						content.m_ComunicationVector.push_back(pDo->m_TcpVector[i]);
					}
					content.m_Vector.push_back(pDo->m_TcpVector[i]);
					break;
				}
				if (CGetInforFormVector::CompareByteArray(byDESArray,content.m_SRC)&&CGetInforFormVector::CompareByteArray(bySRCArray,content.m_DES))//目的地址相同
				{
					if (bMMSMode)
					{
						content.m_TcpAddPos = nTcpAddPos;
						content.m_MMSVector.push_back(pDo->m_TcpVector[i]);
					}
					else
					{
						content.m_ComunicationVector.push_back(pDo->m_TcpVector[i]);
					}
					content.m_Vector.push_back(pDo->m_TcpVector[i]);
					break;
				}
			}
			if (j==pDo->m_TcpKindsVector.size())
			{

				TCPContent content;	
				CByteArray byDESArray,bySRCArray;
				BOOL bMMSMode =CGetInforFormVector::GetDESandSRCIP(pDo,pPro,byDESArray,bySRCArray,nTcpAddPos);
				for (int m=0;m<4;m++)
				{
					content.m_DES[m] = byDESArray.GetAt(m);
					content.m_SRC[m] = bySRCArray.GetAt(m);
				}
				if (bMMSMode)
				{
					content.m_TcpAddPos = nTcpAddPos;
					content.m_MMSVector.push_back(pDo->m_TcpVector[i]);
				}
				else
				{
					pPro.SetAbronamlType(MMS_COMUNCATION);
					content.m_ComunicationVector.push_back(pDo->m_TcpVector[i]);
				}
				content.m_Vector.push_back(pDo->m_TcpVector[i]);
				pDo->m_TcpKindsVector.push_back(content);
			}
		}
	}
}

void CGetInforFormVector::GetGooseClassification(CDoMessage * pDo)
{
	int nType ;
	int nOffset  = 0;
	CPacket & pPro  = pDo->m_NewPacketVector[pDo->m_GooseVector[0]];
	CGetInforFormVector::GetProtocolType(pDo,pPro,nType,nType,nType,nOffset);
	int t_GooseSize = pDo->m_GooseVector.size();
	for (int i =  0;  i  <  t_GooseSize;  i++)
	{	
		CByteArray t_Array;
		CPacket & pPro = pDo->m_NewPacketVector[pDo->m_GooseVector[i]];
		if (i==0)
		{
			Content content;	
			nOffset=0;
			CGetInforFormVector::GetProtocolType(pDo,pPro,nType,nType,nType,nOffset);
			content.m_nOffset = nOffset;
			CGetInforFormVector::GetDesMacArray(pDo,pPro,t_Array);
			for (int m=0;m<6;m++)
			{
				content.m_DES[m] = t_Array.GetAt(m);
			}
			CGetInforFormVector::GetSRCMacArray(pDo,pPro,t_Array);
			for (int m=0;m<6;m++)
			{
				content.m_SRC[m] = t_Array.GetAt(m);
			}

			CGetInforFormVector::GetAppID(pDo,pPro,t_Array,nOffset);
			for (int m=0;m<2;m++)
			{
				content.m_APPID[m] = t_Array.GetAt(m);
			}

			content.m_Vector.push_back(pDo->m_GooseVector[i]);
			content.m_bAbnoState = FALSE;	
			content.m_nPrePacketSize = pPro.m_nDataPackLength;
			pDo->m_GooseKindsVector.push_back(content);
		}
		else
		{
	//		CGetInforFormVector::GetProtocolType(pDo,pPro,nType,nType,nType,nOffset);
			CGetInforFormVector::GetDesMacArray(pDo,pPro,t_Array);
			int j;
			for (j=0;j<pDo->m_GooseKindsVector.size();j++)
			{
				Content &content = pDo->m_GooseKindsVector[j];
				if (CGetInforFormVector::CompareByteArray(t_Array,content.m_DES))//目的地址相同
				{
					content.m_Vector.push_back(pDo->m_GooseVector[i]);
					break;
				}
			}
			if (j==pDo->m_GooseKindsVector.size())
			{
				Content content;	
				nOffset=0;
				CGetInforFormVector::GetProtocolType(pDo,pPro,nType,nType,nType,nOffset);
				content.m_nOffset = nOffset;
				CGetInforFormVector::GetDesMacArray(pDo,pPro,t_Array);
				for (int m=0;m<6;m++)
				{
					content.m_DES[m] = t_Array.GetAt(m);
				}
				CGetInforFormVector::GetSRCMacArray(pDo,pPro,t_Array);
				for (int m=0;m<6;m++)
				{
					content.m_SRC[m] = t_Array.GetAt(m);
				}
				CGetInforFormVector::GetAppID(pDo,pPro,t_Array,nOffset);
				for (int m=0;m<2;m++)
				{
					content.m_APPID[m] = t_Array.GetAt(m);
				}
				content.m_Vector.push_back(pDo->m_GooseVector[i]);
				content.m_bAbnoState = FALSE;		
				content.m_nPrePacketSize = pPro.m_nDataPackLength;
				pDo->m_GooseKindsVector.push_back(content);
			}
		}
	}
}

int CGetInforFormVector::CompareByteArray(CByteArray &byArray1,BYTE byArray2[])
{
	int nSize = byArray1.GetSize();
	for (int i =0;i<nSize;i++)
	{
		BYTE t1 = byArray2[i];
		BYTE t2 = byArray1.GetAt(i);
		if (t1!=t2)
		{
			return 0;
		}
	}
	return 1;
}

void CGetInforFormVector::GetDesMacArray(CDoMessage * pDo,CPacket &Pro,CByteArray &byDataArray)
{
	byDataArray.RemoveAll();
	for (int i=0;i<6;i++)
	{
		BYTE t = pDo->DataArray.GetAt(Pro.m_nHeadStartPos+16+i);
		byDataArray.Add(t);
	}
}

void CGetInforFormVector::GetSRCMacArray(CDoMessage * pDo,CPacket &Pro,CByteArray &byDataArray)
{
	byDataArray.RemoveAll();
	for (int i=6;i<12;i++)
	{
		BYTE t1 = pDo->DataArray.GetAt(Pro.m_nHeadStartPos+16+i);
		byDataArray.Add(t1);
	}
}

bool CGetInforFormVector::GetPackHexDataPart(CDoMessage * pDo,CPacket &Pro,CByteArray &byByteArray)
{
	
	for (int i =0;i<Pro.m_nDataPackLength;i++)
	{
		byByteArray.Add(pDo->DataArray.GetAt(Pro.m_nHeadStartPos+16+i));
	}
	return true;
}

BYTE CGetInforFormVector::GetNextDataArrayFlag(CByteArray &byDataArray,int &nFindPos,int nType)
{
	int nComPos = nFindPos;
	int nSize = byDataArray.GetSize();
	BYTE byFlag;
	if (nFindPos<nSize)
	{
		byFlag = byDataArray.GetAt(nFindPos);
	}
	else return 0x00;
	nFindPos++;
	BYTE byTemp;
	BYTE n87Length;
	if (nFindPos < nSize)
	{
		byTemp = byDataArray.GetAt(nFindPos);
	}
	else return 0x00;
		int t_Off =0;
		if(byTemp>0x80)
		{
			if (byFlag==0x87)
			{
				if (nFindPos+1>=byDataArray.GetSize())
				{
					return 0x00;
					
				}
				n87Length = byDataArray.GetAt(nFindPos+1);
				nFindPos+=(byTemp-0x80+1);
				nFindPos+=n87Length;
			}
			else
			{	
				nFindPos+=(byTemp-0x80+1);
				t_Off =byTemp-0x80+1;
			}

		}
		else
		{
			if (byFlag==0x30||byFlag==0xA0||byFlag==0xA1||byFlag==0x60||byFlag==0xA2)//携带信息可能为很大的长度值
			{
				nFindPos+=1;
				t_Off=2;
			}
			else 
			{
				nFindPos+=(byTemp+1);
				t_Off=2;
			}
		}
	if (nFindPos==nSize)
	{
		nFindPos = nComPos+t_Off;
		if(nFindPos>=byDataArray.GetSize())
		{
			return 0x00;
		}
		else byTemp =  byDataArray.GetAt(nFindPos);
	}
	else
	{
		if (nFindPos<nSize)
		{
			byTemp =  byDataArray.GetAt(nFindPos);
		}
		else return 0x00;
	}

	return byTemp;
}

int CGetInforFormVector::GetFlagPos(CByteArray &byDataArray,  int byFlag,  int nFindPos)
{
	int nSize = byDataArray.GetSize();
	int t_Restult =0;
	int m_RealLength =0;
	int nLength = 0;
	for (int i=nFindPos;i<nSize;i++)
	{
		if(byDataArray.GetAt(i)==byFlag)
		{
			int t_Num =1;
			if (i+t_Num>=nSize)
			{
				break;
			}
			nLength = byDataArray.GetAt(i+t_Num);
			if (nLength==0||nLength>nSize)
			{
				continue;
			}
			int nValueLength =0;
			if(nLength>0x80)			
			{
				nValueLength=nLength-0x80;
				if (nValueLength>10)
				{
					continue;
				}
				if (nValueLength>byDataArray.GetSize()-i)
				{
					continue;
				}
				t_Num+=nValueLength;
				CString byTemp  = _T("");
				for (int j =0;j<nValueLength;j++)
				{
					if (i+2+nValueLength>=byDataArray.GetSize())
					{
						break;
						break;
					}
					CString t_str;
					BYTE t1 = byDataArray.GetAt(i+1+1+j);
					t_str.Format(_T("%.2X"),t1);
					byTemp+=t_str;	

				}
				m_RealLength = GetIntegerFromString(byTemp);
				t_Restult = i;
				//////有过修改原版if (nSize-i==m_RealLength+t_Num+1)/////
				if (nSize-i<=m_RealLength+t_Num+1)
				{
					t_Restult = i;
					break;
				}
				continue;
			}
			else
			{
				if (nSize-i==nLength+2)
				{
					t_Restult = i;
					break;
				}
				else continue;
			}
		}

	}
	return t_Restult;
}

BYTE CGetInforFormVector::GetNext92Flag(CDoMessage * pDo,int &nFindPos)
{
	BYTE byFlag = pDo->DataArray.GetAt(nFindPos);
	int nPos6 =(byFlag>>5)&0x01;//取第6位，用来判断1还是81
	nFindPos++;
	BYTE byTemp;
	byTemp =  pDo->DataArray.GetAt(nFindPos);
	if (nPos6==1)//60,30,A2
	{
		if(byTemp>0x80)nFindPos+=(byTemp-0x80+1);
		else nFindPos+=1; 
	}
	else//80~87情况，后面直接接位数
	{
		if(byTemp>0x80)nFindPos+=(byTemp-0x80+1);
		else nFindPos+=(byTemp+1);
	}

// 	if(byTemp>0x80)nFindPos+=(byTemp-0x80+1);
// 	else nFindPos+=(byTemp+1);

	byTemp =  pDo->DataArray.GetAt(nFindPos);
	return byTemp;
/*	nFindPos++;
	BYTE byTemp;
	byTemp =  pDo->DataArray.GetAt(nFindPos);

	if(byTemp>0x80)
	{
		nFindPos+=(byTemp-0x80+1);
	}
	else
	{
		if (byTemp>=0x01&&byTemp<=0x3C)
		{	
			nFindPos+=(byTemp+1);
		}
		else 
		{
			nFindPos+=1;//针对60之后直接是数据长度，无L标志
		}

	}
	byTemp =  pDo->DataArray.GetAt(nFindPos);
	return byTemp;*/
}

int CGetInforFormVector::GetSmpCntValue(CDoMessage * pDo,  CPacket &Pro,  int n91or92,   int nOffset)
{
	int nSmpCnt =-1;
	CString strResult = _T("");
	int nStartPos  = Pro.m_nHeadStartPos+16+nOffset;
	switch(n91or92)
	{
	case 0x60://9-2
		{
			BYTE byTemp,byT2,byT3;
			BYTE byl1,byl2;
			int nCount =nStartPos+26+nOffset;//0x60位置
			int t_break = nCount;
			int c =0;
			for(c =0;c<10;c++)
			{
				byT2 = GetNext92Flag(pDo,nCount);
				if (byT2==0x82)
				{	

					break;
				}
			}
			if (c==10)
			{
				return -1;
			}
			nCount++;
			nCount++;

			byl1 = pDo->DataArray.GetAt(nCount++);//获取scpcnt的前一个字节
			byl2 = pDo->DataArray.GetAt(nCount++);//获取scpcnt的后一个字节
//  		nSmpCnt  =(int)byl1*pow(2.0,8)+byl2 ;
// 			return nSmpCnt;
			int t_V1 =0;
			t_V1 = t_V1|byl2;
			t_V1 = t_V1|byl1<<8;
			return t_V1;
				
		}
		break;
	case 0x80://9-1
		{
			BYTE byTemp,byT2,byT3;
			BYTE byl1,byl2;
			int nCount =Pro.m_nHeadStartPos+16+Pro.m_nDataPackLength-4;
			byl1 = pDo->DataArray.GetAt(nCount++);//获取scpcnt的前一个字节
			byl2 = pDo->DataArray.GetAt(nCount++);//获取scpcnt的后一个字节

			nSmpCnt  =(int)byl1*pow(2.0,8)+byl2 ;
			return nSmpCnt;	

		}
		break;
	}
	return -1;
}

CString CGetInforFormVector::GetSmpCntValue(CDoMessage * pDo,   CPacket &Pro)
{
	int nType = 0;
	int nSmvorgoose = 0;
	int n91or92 = 0;
	int nOffset = 0;
	int nSmpCnt;
	CString strResult = _T("");
	GetProtocolType(pDo,Pro,nType,nSmvorgoose,n91or92,nOffset);
	if (n91or92 ==0)
	{
		return _T("error");
	}
	int nStartPos  = Pro.m_nHeadStartPos+16+nOffset;
	switch(n91or92)
	{
		case 0x60://9-2
			{
				BYTE byTemp,byT2,byT3;
				BYTE byl1,byl2;
				int nCount =nStartPos+26+nOffset;//0x60位置
				int t_break = nCount;
				int c =0;
				for(c =0;c<10;c++)
				{
					byT2 = GetNext92Flag(pDo,nCount);
					if (byT2==0x82)
					{	

						break;
					}
				}
				if (c==10)
				{
					return _T("error!");
				}
				nCount++;
				nCount++;
				byl1 = pDo->DataArray.GetAt(nCount++);//获取scpcnt的前一个字节
				byl2 = pDo->DataArray.GetAt(nCount++);//获取scpcnt的后一个字节
				nSmpCnt  =(int)byl1*pow(2.0,8)+byl2 ;
				strResult.Format(_T("%d"),nSmpCnt);
				return strResult;			
			}
			break;
		case 0x80://9-1
			{
				BYTE byTemp,byT2,byT3;
				BYTE byl1,byl2;
				int nCount =Pro.m_nHeadStartPos+16+Pro.m_nDataPackLength-4;
				byl1 = pDo->DataArray.GetAt(nCount++);//获取scpcnt的前一个字节
				byl2 = pDo->DataArray.GetAt(nCount++);//获取scpcnt的后一个字节
				nSmpCnt  =(int)byl1*pow(2.0,8)+byl2 ;
				strResult.Format(_T("%d"),nSmpCnt);
				return strResult;	

			}
			break;
		}
	return _T("");
}

int CGetInforFormVector::Get92PrePacketChannelData(CByteArray &byDataArray,   int &nChanPos,   int &nChanLength,  int nOffset,   int nRepeat)
{
	int nStartPos  = 16+nOffset;
	int nCount  =  nStartPos+10+nOffset;//搜索起始位置
	int c=0;
	BYTE byT2,byT3;
	int nLength = 0;
	for(c =0;c<60;c++)
	{
		byT2 = GetNextDataArrayFlag(byDataArray,nCount);
		if (byT2==0x87)
		{	
			if (nRepeat==0)
			{	
				nCount++;
				byT3 = byDataArray.GetAt(nCount);

				if (byT3>0x80)
				{	
					if (byT3==0x82)
					{

						int t1 = byDataArray.GetAt(nCount+1);
						int t2 = byDataArray.GetAt(nCount+2);
						nLength = t1*pow(2.0,8)+t2;
						nCount+=2;
					}
					else
					{
						nCount++;
						nLength = byDataArray.GetAt(nCount);//-0x80 通道数目大于30个通道，会出现0x82的情况
					}
				}
				else nLength = byT3;
				nCount++;
				break;
			}
			else
			{

				nRepeat--;
				continue;
			}

		}

	}
	nChanPos = nCount;
	nChanLength = nLength;
	return 0;
}

int CGetInforFormVector::GetASN1FlagPos(CDoMessage * pDo,   CPacket &Pro,   BYTE byFlag,   int nKindResult,   int nRepeat/*多个ASDU的情况下*/)
{

	int nType = 0;
	int nSmvorgoose = 0;
	int n91or92 = 0;
	int nOffset = 0;
	int nValue = 0;
	BYTE byTemp,byT2,byT3;
	BYTE byl1,  byl2;
	int c =0;
	CString strResult = _T("");
	CByteArray byDataArray;
	GetProtocolType(pDo,Pro,nType,nSmvorgoose,n91or92,nOffset);
	CGetInforFormVector::GetPackHexDataPart(pDo,Pro,byDataArray);
	int nStartPos  = 16  + nOffset;
	int nCount = nStartPos + 10;//搜索起始位置
	for(c  = 0;  c  <  80;  c++)
	{
		byT2 = GetNextDataArrayFlag(byDataArray,  nCount);
		if (byT2==byFlag)
		{	
			if (nRepeat==0)
			{
				break;
			}
			else
			{
				nRepeat--;
				continue;
			}

		}
	}
	if (c==80)
	{
		return -1;
	}
	return nCount;			
}

CString CGetInforFormVector::GetASN1Flag(CByteArray &byDataArray,   BYTE byFlag,   int nFindPos,   int nKindResult,  int nRepeat/*多个ASDU的情况下*/)
{
	BOOL bSpecial = FALSE;
	if (nRepeat>0)
	{
		bSpecial = TRUE;
	}
	int nType = 0;
	int nSmvorgoose = 0;
	int n91or92 = 0;
	int nOffset = 0;
	int nValue = 0;
	BYTE byTemp,byT2,byT3;
	BYTE byl1,byl2;
	int c =0;
	CString strResult = _T("");
	int nStartPos  = 16;
	int nCount =nFindPos;
	for(c =0;c<80;c++)
	{
		int t_size = byDataArray.GetSize();
		if (nCount>=t_size||nCount<0)
		{
			c=80;
			break;
		}
		int t_tempByte =  byDataArray.GetAt(nCount);
 		if (byFlag == byDataArray.GetAt(nCount)&&nRepeat==0&&bSpecial==FALSE)
 		{
 			break;
 		}
 		else
 		{
			if (nCount>=byDataArray.GetSize())
			{
				break;
			}
			byT2 = GetNextDataArrayFlag(byDataArray,nCount);
			if (byT2==byFlag)
			{	
				if (nRepeat==0)
				{
					break;
				}
				else
				{
					nRepeat--;
					continue;
				}

			}
		}

	}
	if (c==80)
	{
		return _T("error!");
	}
	if (nCount>=byDataArray.GetSize())
	{
		return _T("error!");
	}
	return GetFlagValue(byDataArray,byFlag,nCount,nType,nKindResult);;			

}

CString CGetInforFormVector::GetASN1Flag(CDoMessage * pDo,    CPacket &Pro,   BYTE byFlag,   int nKindResult,   int nRepeat/*多个ASDU的情况下*/)
{
	BOOL bSpecial = FALSE;
	if (nRepeat>0)
	{
		bSpecial = TRUE;
	}
	int nType = 0;
	int nSmvorgoose = 0;
	int n91or92 = 0;
	int nOffset = 0;
	int nValue = 0;
	BYTE byTemp,byT2,byT3;
	BYTE byl1,byl2;
	int c = 0;
	CString strResult = _T("");
	CByteArray byDataArray;
	GetProtocolType(pDo,Pro,nType,nSmvorgoose,n91or92,nOffset);
	CGetInforFormVector::GetPackHexDataPart(pDo,Pro,byDataArray);
	int nStartPos  = 16+nOffset;
	int nCount =nStartPos+10;//搜索起始位置
// 	for(c =0;c<60;c++)
// 	{
// 		byT2 = GetNextDataArrayFlag(byDataArray,nCount);
// 		if (byT2==byFlag)
// 		{	
// 			if (nRepeat==0)
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				nRepeat--;
// 				continue;
// 			}
// 	
// 		}
// 	}
// 	if (c==60)
// 	{
// 		return _T("error!");
// 	}
// 	if (nCount>=byDataArray.GetSize())
// 	{
// 		return _T("error!");
// 	}
// 	return GetFlagValue(byDataArray,byFlag,nCount,nType,nKindResult);;			
	for(c =0;c<80;c++)
	{
		int nSize = byDataArray.GetSize();
		if (nCount>=nSize||nCount<0)
		{
			c=80;
			break;
		}
		int nTempByte =  byDataArray.GetAt(nCount);
		if (byFlag == byDataArray.GetAt(nCount)&&nRepeat==0&&bSpecial==FALSE)
		{
			break;
		}
		else
		{
			if (nCount>=byDataArray.GetSize())
			{
				break;
			}
			byT2 = GetNextDataArrayFlag(byDataArray,  nCount);
			if (byT2==byFlag)
			{	
				if (nRepeat==0)
				{
					break;
				}
				else
				{
					nRepeat--;
					continue;
				}

			}
		}

	}
	if (c==80)
	{
		return _T("error!");
	}
	if (nCount>=byDataArray.GetSize())
	{
		return _T("error!");
	}
	return GetFlagValue(byDataArray,byFlag,nCount,nType,nKindResult);;	
}

int CGetInforFormVector::GetMMSItemNameTypeA4(CByteArray &byDataArray,  int nStartPos)//Read
{
	CString strItemName = GetASN1Flag(byDataArray,0x1A,nStartPos,1,1);
	if (strItemName.Find(_T("SGCB"))!=-1)
	{
		return MMS_READREPORT_SGCB;
	} 
	else if (strItemName.Find(_T("SE"))!=-1||strItemName.Find(_T("Set"))!=-1)
	{
		return MMS_READREPORT_SG;
	}
	else if (strItemName.Find(_T("Proxy"))!=-1||strItemName.Find(_T("ST"))!=-1||strItemName.Find(_T("CF"))!=-1||strItemName.Find(_T("DC"))!=-1||strItemName.Find(_T("MX"))!=-1||strItemName.Find(_T("SV"))!=-1||strItemName.Find(_T("EX"))!=-1||strItemName.Find(_T("CO"))!=-1||strItemName.Find(_T("SG"))!=-1||strItemName.Find(_T("GO"))!=-1)
	{
		return MMS_READREPORT_GETDATA;
	}
	else if (strItemName.Find(_T("ds"))!=-1)
	{
		return MMS_READREPORT_GETDATASET;
	}
	else if (strItemName.Find(_T("urcb"))!=-1)
	{
		return MMS_READREPORT_RPURCB;
	}
	else if (strItemName.Find(_T("brcb"))!=-1)
	{
		return MMS_READREPORT_RPBRCB;
	}
	return -1;
}

int CGetInforFormVector::GetMMSItemNameTypeA5(CByteArray &byDataArray,int nStartPos)//Wirte
{
	CString strItemName = GetASN1Flag(byDataArray,0x1A,nStartPos,1,1);
	if (strItemName.Find(_T("ActSG"))!=-1)
	{
		return MMS_WRITEREPORT_ACTSG;
	}
	else if(strItemName.Find(_T("EditSG"))!=-1)
	{
		return MMS_WRITEREPORT_EDITSG;
	}
	else if(strItemName.Find(_T("set"))!=-1)
	{
		return MMS_WRITEREPORT_SETSGVALUES;
	}
	else if(strItemName.Find(_T("CnfEdit"))!=-1)
	{
		return MMS_WRITEREPORT_CONFIRMEDITSGVALUES;
	}
	else if(strItemName.Find(_T("Oper"))!=-1)
	{
		return MMS_WRITEREPORT_CONTRALOPER;
	}
	else if(strItemName.Find(_T("SBow"))!=-1||strItemName.Find(_T("SBOw"))!=-1)
	{
		return MMS_WRITEREPORT_SELVAL;
	}
	else if(strItemName.Find(_T("Can"))!=-1)
	{
		return MMS_WRITEREPORT_CANCEL;
	}
	else if(strItemName.Find(_T("Proxy"))!=-1||strItemName.Find(_T("SV"))!=-1||strItemName.Find(_T("CF"))!=-1)
	{
		return MMS_WRITEREPORT_SETDATA;
	}
	else if (strItemName.Find(_T("urcb"))!=-1)
	{
		return MMS_WRITEREPORT_RPURCB;
	}
	else if (strItemName.Find(_T("brcb"))!=-1)
	{
		return MMS_WRITEREPORT_RPBRCB;
	}
	return -1;
}

CString CGetInforFormVector::GetFlagValue(CByteArray &byDataArray,   BYTE byFlag,   int nStartPos,  int &nAfterLength,   int nFormate)
{
	CString strResult = _T("");
	int nValueLength = 0;
	BYTE t1 = byDataArray.GetAt(nStartPos);
	int t_LNum =0;//设置位置的个数，0或者1,2
	if (t1!=byFlag)
	{
		return _T("error!");
	}
	BOOL bSpecial = FALSE;
	int nPos6 =(byFlag>>5)&0x01;//取第6位，用来判断1还是81.
	BYTE t2 = byDataArray.GetAt(nStartPos+1);
	BYTE byS = t2;
	int t_DSPos = nStartPos+1;
	if (nPos6==0)//82,85,80,83,87后面固定节01的
	{
		t_LNum =1;
		if(t2>=0x80)//这对87后面有81的情况
		{
			if (nStartPos+1>=byDataArray.GetSize())
			{
				return _T("error");
			}
			nValueLength =t2-0x80;
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
			t_LNum =0;
			nValueLength=1;
		}
	}
	CString byTemp = _T("");
	switch(nFormate)
	{
	case 0:	//十进制数
		if (nStartPos+1+t_LNum+nValueLength>=byDataArray.GetSize())
		{
			return _T("error");
		}
		for (int j =0;j<nValueLength;j++)
		{
			CString t_str;
			t1 = byDataArray.GetAt(nStartPos+1+t_LNum+j);
			t_str.Format(_T("%.2X"),t1);
			byTemp+=t_str;	

		}
		strResult.Format(_T("%d"),C92Deal::GetIntegerFromString(byTemp));		
		break;
	case 1://字符串
		for (int j =0;j<nValueLength;j++)
		{
			CString t_str;
			t1 = byDataArray.GetAt(nStartPos+1+t_LNum+j);
			t_str.Format(_T("%C"),t1);
			byTemp+=t_str;
		}
		strResult = byTemp;

		break;
	case 3:	//无符号
		if (nStartPos+1+t_LNum+nValueLength>=byDataArray.GetSize())
		{
			return _T("error");
		}
		for (int j =0;j<nValueLength;j++)
		{
			CString t_str;
			t1 = byDataArray.GetAt(nStartPos+1+t_LNum+j);
			t_str.Format(_T("%.2X"),t1);
			byTemp+=t_str;	

		}
		strResult.Format(_T("%u"),C92Deal::GetIntegerFromString(byTemp));		
		break;
	case 0x844://格林尼治时间最后的那个品质
		{
			CString t_strFactor;
			BYTE t1 =  byDataArray.GetAt(nStartPos+1+t_LNum+7);
			t_strFactor.Format(_T("%d"),t1);
			strResult = t_strFactor;
		}
		break;
	case 2://格林尼治时间
		{
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
			double t_usTime = t1+t2*pow(2.0,8)+t3*pow(2.0,16)+t4*pow(2.0,24);
			CString str1;
			str1.Format(_T("%d"),(int)t_usTime);
			str+=_T(".");
			str+=str1;
			strResult=str;
		}
		break;
	case 0x87:
		strResult.Format(_T("%d"),nValueLength);
		break;
	case 0x872:
		for (int j =0;j<nValueLength;j++)
		{
			CString t_str;
			int t_PosV = nStartPos+1+t_LNum+j;
			if (t_PosV>=byDataArray.GetSize())
			{
				break;
			}
			t1 = byDataArray.GetAt(t_PosV);
			t_str.Format(_T("%.2X"),t1);
			byTemp+=t_str;	

		}
		strResult=byTemp;
		break;	
	case 0xAB:
		{

			if (nValueLength==1)
			{
				if (t2>0x80)//Goose数据集
				{
					t2 = byDataArray.GetAt(nStartPos+1+1);
				}
				for (int j =0;j<t2;j++)
				{
					CString t_str;
					int t_PosV = nStartPos+2+t_LNum+j;
					if (t_PosV>=byDataArray.GetSize())
					{
						break;
					}
					t1 = byDataArray.GetAt(t_PosV);
					t_str.Format(_T("%.2X"),t1);
					byTemp+=t_str;	

				}
				strResult=byTemp;
			}
			else//0x82
			{
				CString t_t = _T("");
				if (byDataArray.GetSize()<=nStartPos+nValueLength)
				{
					return _T("error");
				}
				for (int j =0;j<nValueLength;j++)
				{
					CString t_str;
					t1 = byDataArray.GetAt(nStartPos+nValueLength+j);
					t_str.Format(_T("%.2X"),t1);
					t_t+=t_str;	

				}
				int t_GoDataLength = C92Deal::GetIntegerFromString(t_t);	
				for (int j =0;j<t_GoDataLength;j++)
				{
					CString t_str;
					int t_PosV = nStartPos+2+nValueLength+j;
					if (t_PosV>=byDataArray.GetSize())
					{
						break;
					}
					t1 = byDataArray.GetAt(t_PosV);
					t_str.Format(_T("%.2X"),t1);
					byTemp+=t_str;	

				}
				strResult=byTemp;
			}
		}

		break;	
	case 0xC1:
		{
			if (byS>0x80)
			{
				int t_dif = byS-0x80;
				for (int m =0;m<t_dif;m++)
				{
					CString t_str;
					t1 = byDataArray.GetAt(t_DSPos+1+m);
					t_str.Format(_T("%.2X"),t1);
					byTemp+=t_str;	
				}
				strResult.Format(_T("%d"),C92Deal::GetIntegerFromString(byTemp));	
			}
			else strResult.Format(_T("%d"),byS);
		}
		break;
	case 0xC11://返回长度的值 比如：A0 82 15 F1 返回结果为82，如 A0 28 返回 28  如 02 02 1A CD 返回 02 
		{
			if (byS>0x80)
			{
				int t_dif = byS;
				strResult.Format(_T("%d"),t_dif);	
			}
			else strResult.Format(_T("%d"),byS);
		}
		break;
	case 0xC12://返回长度的个数 比如：A0 82 15 F1 返回结果为2，如 A0 28 返回0  
		{
			if (byS>0x80)
			{
				int t_dif = byS-0x80;
				strResult.Format(_T("%d"),t_dif);	
			}
			else strResult.Format(_T("%d"),0);
		}
		break;
	case 0xC13://返回长度的真实值 比如：A0 82 15 F1 返回结果为15F1，如 A0 28 返回28 
		{
			if (byS>0x80)
			{
				int t_dif = byS-0x80;
				if (nStartPos+1+t_LNum+t_dif<byDataArray.GetSize())
				{
					for (int j =0;j<t_dif;j++)
					{
						CString t_str;
						t1 = byDataArray.GetAt(nStartPos+1+t_LNum+j);
						t_str.Format(_T("%.2X"),t1);
						byTemp+=t_str;
					}
					strResult.Format(_T("%d"),C92Deal::GetIntegerFromString(byTemp));				
				}
			}
			else strResult.Format(_T("%d"),byS);
		}
		break;
	case 0xC14://返回长度的真实值 比如：A0 82 15 F1 返回结果为2，A0 81 15  返回结果为1,如 80 01 15,返回值 01, A0 28 返回28 
		{
			if (byS>0x80)
			{
				int t_dif = byS-0x80;
				strResult.Format(_T("%d"),t_dif);	
			}
			else strResult.Format(_T("%d"),byS);
		}
		break;
	case 0xC2:
		{
			strResult.Format(_T("%d"),byS);
			break;
		}
	}
	if (!bSpecial)
	{
		nAfterLength  = nValueLength+t_LNum+1;
	}
	else nAfterLength  = nValueLength+t_LNum+1+1;
	return strResult;
}

int CGetInforFormVector::GetTimeAllowToLive(CDoMessage * pDo,  CPacket &Pro)
{
	int strResult = 0;
	strResult = atoi(GetASN1Flag(pDo,Pro,0x81));
	return strResult;
}

int CGetInforFormVector::GetEventTimeStampFactor(CDoMessage * pDo,  CPacket &Pro)
{
	CString strResult = 0;
	strResult = GetASN1Flag(pDo,Pro,0x84,0x844);
	return atoi(strResult);
}

CString CGetInforFormVector::GetSqNum(CDoMessage * pDo,  CPacket &Pro)
{
	CString strResult = _T("");
	strResult = GetASN1Flag(pDo,Pro,0x86,3);
	return strResult;
}

CString CGetInforFormVector::GetStNum(CDoMessage * pDo,  CPacket &Pro)
{
	CString strResult = _T("");
	strResult = GetASN1Flag(pDo,Pro,0x85,3);
	return strResult;
}

BOOL CGetInforFormVector::GetMMSMode(CDoMessage * pDo,  CPacket &Pro)
{
	CByteArray byDataArray;
	CGetInforFormVector::GetPackHexDataPart(pDo,Pro,byDataArray);
	if (byDataArray.GetSize()<59)
	{
		return FALSE;
	}
	int m_L = 54;
	BYTE t_F = byDataArray.GetAt(m_L);
	int nTcpAddPos = 0;
	if (t_F!=0x03)
	{
		m_L+=12;
		if (m_L>=byDataArray.GetSize())
		{
			return FALSE;
		}
		t_F = byDataArray.GetAt(m_L);
		nTcpAddPos = 12;
	}
	if (m_L+5>=byDataArray.GetSize())
	{
		return FALSE;
	}
	BYTE t_F1 = byDataArray.GetAt(m_L+5);
	if (t_F==0x03&&(t_F1==0xF0||t_F1==0xD0||t_F1==0xE0))//54:03为MMS标准1、59:0xE0,0xD0,0xF0 为MMS报文
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CGetInforFormVector::GetMMSMode(CByteArray &byDataArray)
{
	if (byDataArray.GetSize()<59)
	{
		return FALSE;
	}
	int m_L = 54;
	BYTE t_F = byDataArray.GetAt(m_L);
	int nTcpAddPos = 0;
	if (t_F!=0x03)
	{
		m_L+=12;	
		nTcpAddPos = 12;
		if (m_L>=byDataArray.GetSize())
		{
			return FALSE;
		}
		t_F = byDataArray.GetAt(m_L);

	}
	if (m_L+5>=byDataArray.GetSize())
	{
		return FALSE;
	}
	BYTE t_F1 = byDataArray.GetAt(m_L+5);
	if (t_F==0x03&&(t_F1==0xF0||t_F1==0xD0||t_F1==0xE0))//54:03为MMS标准1、59:0xE0,0xD0,0xF0 为MMS报文
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CGetInforFormVector::GetDESandSRCIP(CDoMessage * pDo,CPacket &Pro,CByteArray & byDESArray,CByteArray & bySRCArray,int & nTcpAddPos)
{
	CByteArray byDataArray;
	CGetInforFormVector::GetPackHexDataPart(pDo,Pro,byDataArray);
	BYTE t_SrcIp1 = byDataArray.GetAt(26);
	BYTE t_SrcIp2 = byDataArray.GetAt(27);
	BYTE t_SrcIp3 = byDataArray.GetAt(28);
	BYTE t_SrcIp4 = byDataArray.GetAt(29);

	bySRCArray.Add(t_SrcIp1);
	bySRCArray.Add(t_SrcIp2);
	bySRCArray.Add(t_SrcIp3);
	bySRCArray.Add(t_SrcIp4);

	BYTE t_DesIp1 = byDataArray.GetAt(30);
	BYTE t_DesIp2 = byDataArray.GetAt(31);
	BYTE t_DesIp3 = byDataArray.GetAt(32);
	BYTE t_DesIp4 = byDataArray.GetAt(33);

	byDESArray.Add(t_DesIp1);
	byDESArray.Add(t_DesIp2);
	byDESArray.Add(t_DesIp3);
	byDESArray.Add(t_DesIp4);

	if(byDataArray.GetSize()>59)//判断MMS报文，还是TCP报名
	{
		int m_L = 54;
		BYTE t_F = byDataArray.GetAt(m_L);
		nTcpAddPos = 0;
		if (t_F!=0x03)
		{
			m_L+=12;	
			nTcpAddPos = 12;
			if (m_L>=byDataArray.GetSize())
			{
				return FALSE;
			}
			t_F = byDataArray.GetAt(m_L);

		}
		if (m_L+5>=byDataArray.GetSize())
		{
			return FALSE;
		}
		BYTE t_F1 = byDataArray.GetAt(m_L+5);
		if (t_F==0x03&&(t_F1==0xF0||t_F1==0xD0||t_F1==0xE0))//54:03为MMS标准1、59:0xE0,0xD0,0xF0 为MMS报文
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CGetInforFormVector::GetIPandPortString(CDoMessage * pDo,CPacket &Pro,CString &strSrcIP,CString &strSrcPort,CString &strDesIP,CString &strDesPort)
{
	CByteArray byDataArray;
	CGetInforFormVector::GetPackHexDataPart(pDo,Pro,byDataArray);
	BYTE t_SrcIp1 = byDataArray.GetAt(26);
	BYTE t_SrcIp2 = byDataArray.GetAt(27);
	BYTE t_SrcIp3 = byDataArray.GetAt(28);
	BYTE t_SrcIp4 = byDataArray.GetAt(29);
	strSrcIP.Format(_T("%d.%d.%d.%d"),t_SrcIp1,t_SrcIp2,t_SrcIp3,t_SrcIp4);

	BYTE t_DesIp1 = byDataArray.GetAt(30);
	BYTE t_DesIp2 = byDataArray.GetAt(31);
	BYTE t_DesIp3 = byDataArray.GetAt(32);
	BYTE t_DesIp4 = byDataArray.GetAt(33);
	strDesIP.Format(_T("%d.%d.%d.%d"),t_DesIp1,t_DesIp2,t_DesIp3,t_DesIp4);

	BYTE t_SrcPort1 = byDataArray.GetAt(34);
	BYTE t_SrcPort2 = byDataArray.GetAt(35);
	
	strSrcPort = _T("");
	CString temp;
	temp.Format(_T("%.2X"),t_SrcPort1);
	strSrcPort+=temp;
	temp.Format(_T("%.2X"),t_SrcPort2);
	strSrcPort+=temp;
		
	strSrcPort.Format(_T("%d"),C92Deal::GetIntegerFromString(strSrcPort));

	BYTE t_DesPort1 = byDataArray.GetAt(36);
	BYTE t_DesPort2 = byDataArray.GetAt(37);

	temp.Format(_T("%.2X"),t_DesPort1);
	strDesPort+=temp;
	temp.Format(_T("%.2X"),t_DesPort2);
	strDesPort+=temp;	
	strDesPort.Format(_T("%d"),C92Deal::GetIntegerFromString(strDesPort));
}

unsigned int CGetInforFormVector::GetIntegerFromString(CString pStr)
{
	unsigned int nValue = 0;
	for (int i = 0; i<pStr.GetLength(); i++)
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
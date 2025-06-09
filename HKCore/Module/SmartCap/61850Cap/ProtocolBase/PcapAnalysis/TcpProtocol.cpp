#include "StdAfx.h"
#include "TcpProtocol.h"
#include <math.h>

#include "DoMessage.h"

CTcpProtocol::CTcpProtocol(int siDataTime,int siSecTime,int siDifUpTime,int m_iPacksize,int m_iRealPacksize,int m_iStartPos,int m_iEndPos)
{
	m_sDataTimePos = siDataTime;
	m_sSecimePos = siSecTime;
	m_sDifUpTime = siDifUpTime;
	m_RealPackSize= m_iRealPacksize;
	m_PackSize = m_iPacksize;  
	m_StartPos = m_iStartPos;
	m_EndPos = m_iEndPos;
	m_smpCnt =-1;
	m_91Or92 = 0;
	b_LostPack = FALSE;
	m_Lock = 0;
	m_ProType = 0;
	offset =0;
	m_60AfterLength = 3;
}

CTcpProtocol::~CTcpProtocol(void)
{

}

CString CTcpProtocol::GetPackLegth()
{
	CString t_Length;
	t_Length.Format(_T("%d"),m_PackSize);
	return t_Length;
}

bool CTcpProtocol::GetPackHexDataPart(CDoMessage * pDo,CByteArray &m_ByteArray)
{
	for (int i =0;i<m_PackSize;i++)
	{
		m_ByteArray.Add(pDo->DataArray.GetAt(m_StartPos+i));
	}
	return true;
}

/////////////////////从0x60开始逐个访问标志位/////////////////////////////
BYTE CTcpProtocol::GetNext92Flag(CDoMessage * pDo,int &m_FindPos)
{
	m_FindPos++;
	BYTE t_temp;
	t_temp =  pDo->DataArray.GetAt(m_FindPos);
	if(t_temp>0x80)
	{
		m_60AfterLength = 3;
		m_FindPos+=(t_temp-0x80+1);
	}
	else
	{
		if (t_temp>=0x01&&t_temp<=0x3C)
		{	
			m_60AfterLength = 3;
			m_FindPos+=(t_temp+1);
		}
		else 
		{
			m_60AfterLength = 2;
			m_FindPos+=1;//针对60之后直接是数据长度，无L标志
		}

	}
	t_temp =  pDo->DataArray.GetAt(m_FindPos);
	return t_temp;
}

int CTcpProtocol::GetSmpCntValue(CDoMessage * pDo)
{

	if (m_smpCnt == -1)
	{
		switch(m_91Or92)
		{
		case 0x60://9-2
			{
				BYTE t_temp,t_t2,t_t3;
				BYTE t_l1,t_l2;
				int t_count =m_StartPos+26+offset;//0x60位置
				int c =0;
				for(c =0;c<100;c++)
				{
					t_t2 = GetNext92Flag(pDo,t_count);
					if (t_t2==0x82)
					{	
						break;
					}
				}
				if (c==100)
				{
					return -2;
				}
				t_count++;
				t_count++;
				t_l1 = pDo->DataArray.GetAt(t_count++);//获取scpcnt的前一个字节
				t_l2 = pDo->DataArray.GetAt(t_count++);//获取scpcnt的后一个字节
				m_smpCnt  =(int)t_l1*pow(2.0,8)+t_l2 ;
				return m_smpCnt;			
			}
			break;
		case 0x80://9-1
			{
				BYTE t_temp,t_t2,t_t3;
				BYTE t_l1,t_l2;
				int t_count =m_StartPos+29+43+offset;//0x80位置
				t_l1 = pDo->DataArray.GetAt(t_count++);//获取scpcnt的前一个字节
				t_l2 = pDo->DataArray.GetAt(t_count++);//获取scpcnt的后一个字节
				m_smpCnt  =(int)t_l1*pow(2.0,8)+t_l2 ;
				return m_smpCnt;

			}
			break;
		}
	}
	else
	{
		return m_smpCnt;
	}

	return -1;
}

void CTcpProtocol::GetProtocolTypeValue(CDoMessage * pDo)
{
	BYTE t1,t2,t3,t4;
	
	t4 = pDo->DataArray.GetAt(m_StartPos+12);
	t3 = pDo->DataArray.GetAt(m_StartPos+13);
	int t_type = (int)t4*pow(2.0,8)+t3;
	m_ProType = t_type;
	switch(t_type)
	{
	case 33024://0x8100 goose or smv
		{

			t2 = pDo->DataArray.GetAt(m_StartPos+16);
			t1 = pDo->DataArray.GetAt(m_StartPos+17);
			int t_SMVOrGoose = (int)t2*pow(2.0,8)+t1;
			m_SMVOrGoose = t_SMVOrGoose;
			switch(t_SMVOrGoose)
			{
			case 35000://0x88B8 GOOSE			
				break;
			case 35002://0x88BA SMV
				m_91Or92 = pDo->DataArray.GetAt(m_StartPos+26);//0x60
				break;
			}	
		}
		break;
	case 35000://0x88B8 GOOSE	
		if (offset==0)
		{
			offset =-4;
		}
		m_SMVOrGoose = 35000;
		break;
	case 35002://0x88BA SMV
		if (offset==0)
		{
			offset =-4;
		}
		m_SMVOrGoose = 35002;
		m_91Or92 = pDo->DataArray.GetAt(m_StartPos+26+offset);//0x60
		break;
	}	
}

CString CTcpProtocol::GetProtocolType(CDoMessage * pDo)
{
	CString t_strType=_T("未知类型");
	int t_type;
	if(m_ProType!=0)
	{
		switch(m_ProType)
		{
		case 2048://0x0800 IP 
			{
				m_TcpOrUdp = pDo->DataArray.GetAt(m_StartPos+23);
				switch(m_TcpOrUdp)
				{
				case 0x06://tcp
					t_strType = _T("TCP");
					break;
				case 0x11://udp
					t_strType = _T("UDP");
					break;
				}
			}
			break;
		case 2054://0x0806
			{
				t_strType = _T("ARP");
			}
			break;
		case 33024://0x8100 goose or smv
			{
				switch(m_SMVOrGoose)
				{
				case 35000://0x88B8 GOOSE
					t_strType = _T("IEC_Goose");				
					break;

				case 35002://0x88BA SMV
					{
						t_strType = _T("IEC_SMV");
	
					}
					break;
				}	
			}
			break;
		case 35000://0x88B8 GOOSE
			t_strType = _T("IEC_Goose");				
			break;

		case 35002://0x88BA SMV
			t_strType = _T("IEC_SMV");
			break;
		}
	}
	else
	{
		if (pDo ==NULL)
		{
			return _T("");
		}
		BYTE t1,t2,t3,t4;
		t4 = pDo->DataArray.GetAt(m_StartPos+12);
		t3 = pDo->DataArray.GetAt(m_StartPos+13);
		t_type = (int)t4*pow(2.0,8)+t3;
		m_ProType = t_type;
		switch(t_type)
		{
			case 2048://0x0800 IP 
				{
					BYTE t_TcpOrUdp;
					t_TcpOrUdp = pDo->DataArray.GetAt(m_StartPos+23);
					switch(t_TcpOrUdp)
					{
					case 0x06://tcp
						t_strType = _T("TCP");
						break;
					case 0x11://udp
						t_strType = _T("UDP");
						break;
					}
				}
				break;
			case 2054://0x0806
				{
					t_strType = _T("ARP");
				}
				break;
			case 33024://0x8100 goose or smv
				{

					t2 = pDo->DataArray.GetAt(m_StartPos+16);
					t1 = pDo->DataArray.GetAt(m_StartPos+17);
					int t_SMVOrGoose = (int)t2*pow(2.0,8)+t1;
					m_SMVOrGoose = t_SMVOrGoose;
					switch(t_SMVOrGoose)
					{
					case 35000://0x88B8 GOOSE
						t_strType = _T("IEC_Goose");				
						break;

					case 35002://0x88BA SMV
						{
							m_91Or92 = pDo->DataArray.GetAt(m_StartPos+26);//0x60
							t_strType = _T("IEC_SMV");

						}
						break;
					}	
				}
				break;
			case 35000://0x88B8 GOOSE
				t_strType = _T("IEC_Goose");				
				break;

			case 35002://0x88BA SMV
				{
					if (offset ==0)
					{
						offset =-4;
					}
					m_91Or92 = pDo->DataArray.GetAt(m_StartPos+26+offset);//0x60
					t_strType = _T("IEC_SMV");

				}
				break;
		}

	}
	return t_strType;
}

int CTcpProtocol::GetTimeDif(CDoMessage * pDo)
{
	BYTE t1,t2,t3,t4;
	t4 =  pDo->DataArray.GetAt(m_sSecimePos);	
	t3 =  pDo->DataArray.GetAt(m_sSecimePos+1);
	t2 =  pDo->DataArray.GetAt(m_sSecimePos+2);
	t1 =  pDo->DataArray.GetAt(m_sSecimePos+3);
	double t_usTime = t4+t3*pow(2.0,8)+t2*pow(2.0,16)+t1*pow(2.0,24);
	m_sDifUpTime = (int)t_usTime;
	return m_sDifUpTime;
}

CString CTcpProtocol::GetTimeString(CDoMessage * pDo)
{
	BYTE t4 =  pDo->DataArray.GetAt(m_sDataTimePos);	
	BYTE t3 =  pDo->DataArray.GetAt(m_sDataTimePos+1);
	BYTE t2 =  pDo->DataArray.GetAt(m_sDataTimePos+2);
	BYTE t1 =  pDo->DataArray.GetAt(m_sDataTimePos+3);
	double t_time = t4+t3*pow(2.0,8)+t2*pow(2.0,16)+t1*pow(2.0,24);
	CTime time = (CTime)(int)t_time;
	CString str = time.Format("%Y-%m-%d %H:%M:%S");

	t4 =  pDo->DataArray.GetAt(m_sSecimePos);	
	t3 =  pDo->DataArray.GetAt(m_sSecimePos+1);
	t2 =  pDo->DataArray.GetAt(m_sSecimePos+2);
	t1 =  pDo->DataArray.GetAt(m_sSecimePos+3);
	double t_usTime = t4+t3*pow(2.0,8)+t2*pow(2.0,16)+t1*pow(2.0,24);
//	m_sDifUpTime = (int)t_usTime;
	CString str1;
	str1.Format(_T("%d"),(int)t_usTime);
	str+=_T(".");
	str+=str1;
	return str;
}
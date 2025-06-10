#include "stdafx.h"
#include "CapGlobalDef.h"

#include "../../CriticalSection/SynCriticalSection.h"
#include "../../GpsPcTime/GpsPcTime.h"

#define _use_CaptureIDCriticSection
volatile __int64 g_nCaptureID = 0;

#ifdef _use_CaptureIDCriticSection
CAutoCriticSection g_pCaptureIDCriticSection;
CAutoCriticSection g_oCapWriteCriticSection;
#endif

DWORD g_nEpCapBufferWriteState = 0;
DWORD g_nEpCapWriteCounter = 0;

BYTE g_bytePcapHead_us[24] = {0xd4,0xc3,0xb2,0xa1,0x02,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x04,0x00,0x01,0x00,0x00,0x00};
BYTE g_bytePcapHead_ns[24] = {0x4d,0x3c,0xb2,0xa1,0x02,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x04,0x00,0x01,0x00,0x00,0x00};

volatile __int64 Ep_Cap_GenerateCaptureID()
{
#ifdef _use_CaptureIDCriticSection
	CAutoSimpleLock oLock(g_pCaptureIDCriticSection);
#endif

	g_nCaptureID++;
	return g_nCaptureID;	
}


void ep_cap_timeval_to_time(const struct timeval &ts, EP_ETHER_CAP_TIME &time)
{
	int i,year,month,day,hour,minute,second;
	long tmp;
	int dyr[12]={31,29,31,30,31,30,31,31,30,31,30,31}; //�����·�
	int dyp[12]={31,28,31,30,31,30,31,31,30,31,30,31}; //ƽ��
	bool flag=0;
	long t = ts.tv_sec;
	int *pdy = NULL;
	int days=0;

	for(year=1970; ;year++)
	{
		if((year%400==0)||(year%4==0 && year%100!=0)) //����
		{
			days = 366;
			pdy = dyr;
		}
		else
		{
			days = 365;
			pdy = dyp;
		}

		tmp=days*24*60*60;

		if(t >= tmp)
		{
			t = t - tmp;
		}
		else
		{

			for(i=0;i<12;i++)
			{
				tmp=pdy[i]*24*60*60;

				if(t>=tmp)
				{
					t=t-tmp;
				}
				else
				{
					month=i+1;
					day=t/(24*60*60)+1;
					t=t-(day-1)*24*60*60;
					hour=t/(60*60);
					t=t-hour*60*60;
					minute=t/60;
					second=t%60;
					flag=1;
					break;
				}
			}
		}

		if(flag) 
		{
			break;
		}
	}


	SYSTEMTIME tmSys;
	tmSys.wYear = year;
	tmSys.wMonth = month;
	tmSys.wDay = day;
	tmSys.wHour = hour;
	tmSys.wMinute = minute;
	tmSys.wSecond = second;

	CGpsPcTime ctime(tmSys);
	CGpsPcTimeSpan tmSpan(0, 8, 0, 0, 0, 0);
	ctime += tmSpan;
	ctime.GetSysTime(tmSys);

	time.year = tmSys.wYear;
	time.month = tmSys.wMonth;
	time.day = tmSys.wDay;
	time.hour = tmSys.wHour;
	time.minute = minute;
	time.second = second;
	time.usec = ts.tv_usec;
}

void ep_time_to_cap_timeval(const EP_ETHER_CAP_TIME &time, struct timeval &ts)
{
	ts.tv_usec = time.usec;
	ts.tv_sec = 0;

	int dyr[12]={31,29,31,30,31,30,31,31,30,31,30,31}; //�����·�
	int dyp[12]={31,28,31,30,31,30,31,31,30,31,30,31}; //ƽ��
	int *pdy = NULL;
	int year = 0;
	int i = 1;

	for(year=1970; year <time.year ;year++)
	{
		if((year%400==0)||(year%4==0 && year%100!=0)) //����
		{
			ts.tv_sec += 366*24*60*60;
		}
		else
		{
			ts.tv_sec += 365*24*60*60;
		}
	}

	if((time.year%400==0)||(time.year%4==0 && time.year%100!=0)) //����
	{
		pdy = dyr;
	}
	else
	{
		pdy = dyp;
	}

	for(i=1;i<time.month; i++)
	{
		ts.tv_sec += pdy[i]*24*60*60;
	}

	ts.tv_sec += (time.day-1)*24*60*60; //day
	ts.tv_sec += time.hour*60*60;
	ts.tv_sec += time.minute*60;
	ts.tv_sec += time.second;
}

void ep_curr_cap_timeval(struct timeval &ts)
{
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	EP_ETHER_CAP_TIME time;
	time.year = tm.wYear;
	time.month = tm.wMonth;
	time.day = tm.wDay;
	time.hour = tm.wHour;
	time.minute = tm.wMinute;
	time.second = tm.wSecond;
	time.usec = tm.wMilliseconds*1000;
	ep_time_to_cap_timeval(time, ts);
}

//2020-06-28 ����ģʽ
long g_nXSmartCapDebugMode = 0;
long g_n_write_SyncDelt_Rcd_file_Mode = 2;

CString g_strSttRcdFilePath;

void stt_GetVariablePhaseID(const CString &strName, CString &strPhaseID, CString &strUnit)
{
	if (strName.Find(_T("_Ia")))
	{
		strPhaseID = _T("A");
		strUnit = _T("A");
	}
	else if (strName.Find(_T("_Ib")))
	{
		strPhaseID = _T("B");
		strUnit = _T("A");
	}
	else if (strName.Find(_T("_Ic")))
	{
		strPhaseID = _T("C");
		strUnit = _T("A");
	}
	else if (strName.Find(_T("_Ua")))
	{
		strPhaseID = _T("A");
		strUnit = _T("V");
	}
	else if (strName.Find(_T("_Ub")))
	{
		strPhaseID = _T("B");
		strUnit = _T("V");
	}
	else if (strName.Find(_T("_Uc")))
	{
		strPhaseID = _T("C");
		strUnit = _T("V");
	}
	else
	{
		strPhaseID = _T("A");
		strUnit = _T("A");
	}
}

long GetTimeGap_EpcapBufferItem(EPCAPBUFFERITEM *pCurrItem,EPCAPBUFFERITEM *pPrevItem,BOOL bUSec)
{
	struct timeval tmCurr,tmPrev;
	tmCurr.tv_sec = pCurrItem->Time >> 32;
	tmCurr.tv_usec = pCurrItem->Time & 0xFFFFFFFF;
	tmPrev.tv_sec = pPrevItem->Time >> 32;
	tmPrev.tv_usec = pPrevItem->Time & 0xFFFFFFFF;

	long nSecondGap = tmCurr.tv_sec - tmPrev.tv_sec;
	long nUsec = tmCurr.tv_usec - tmPrev.tv_usec;

	if (bUSec)
	{
		nUsec += (nSecondGap*1000000);
	} 
	else
	{
		nUsec += (nSecondGap*1000000000);
	}

	return nUsec;
}

long GetTimeGap_EpcapBufferItem(__int64 u64_CurrTime,__int64 u64_PrevTime,BOOL bUSec)
{
	struct timeval tmCurr,tmPrev;
	tmCurr.tv_sec = u64_CurrTime >> 32;
	tmCurr.tv_usec = u64_CurrTime & 0xFFFFFFFF;
	tmPrev.tv_sec = u64_PrevTime >> 32;
	tmPrev.tv_usec = u64_PrevTime & 0xFFFFFFFF;

    long nSecondGap = tmCurr.tv_sec - tmPrev.tv_sec;
    long nUsec = tmCurr.tv_usec - tmPrev.tv_usec;

	if (bUSec)
	{
		nUsec += (nSecondGap*1000000);
	} 
	else
	{
		nUsec += (nSecondGap*1000000000);
	}

	return nUsec;
}

__int64 Global_BufferGetINT64(BYTE *pszBuffer)
{
	__int64 val = *(pszBuffer);
	val = val << 8;
	val += *(pszBuffer + 1);
	val = val << 8;
	val += *(pszBuffer + 2);
	val = val << 8;
	val += *(pszBuffer + 3);
	val = val << 8;
	val += *(pszBuffer + 4);
	val = val << 8;
	val += *(pszBuffer + 5);
	val = val << 8;
	val += *(pszBuffer + 6);
	val = val << 8;
	val += *(pszBuffer + 7);
	return val;
}

DWORD Global_BufferGetDWORD(BYTE *pszBuffer)
{
	DWORD val = *(pszBuffer);
	val = val << 8;
	val += *(pszBuffer + 1);
	val = val << 8;
	val += *(pszBuffer + 2);
	val = val << 8;
	val += *(pszBuffer + 3);
	return val;
}

WORD Global_BufferGetWord(BYTE *pszBuffer)
{
	WORD val = *(pszBuffer);
	val = val << 8;
	val += *(pszBuffer + 1);
	return val;
}

long Global_GetPcapReadLenth(BYTE *pszBuffer,long nMaxLenth)
{
	long nCurrDataIndex = 12;//����MACԭ��ַ��Ŀ���ַ
	WORD wValue = Global_BufferGetWord(pszBuffer + nCurrDataIndex);

	if (wValue == 0x8100)//�ж��Ƿ����wlan
	{
		nCurrDataIndex += 4;
	}

	nCurrDataIndex += 4;//�����������ͺ�AppID
	long nActLenth = Global_BufferGetWord(pszBuffer + nCurrDataIndex);
	nActLenth += nCurrDataIndex;
	nActLenth -= 2;//��ȥ����ռ�õ�2���ֽ�

	if (nActLenth > nMaxLenth)
	{
		nMaxLenth = nActLenth;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡPcap�ļ��еĳ��ȳ���,Pcap����(%ld),AT02D����(%ld)."),nActLenth,nMaxLenth);
	}

	return nActLenth;
}

bool stt_save_pcap_file(const CString &strSrcAt02dFile,const char *pszSavePcapFile)
{
	CFile oAt02dFile;

	if (!oAt02dFile.Open(strSrcAt02dFile, CFile::modeRead))
	{
		return false;
	}
	// 	FILE *pAt02dFile = fopen(strSrcAt02dFile, "r+b");
	// 
	// 	if (pAt02dFile == NULL)
	// 	{
	// 		return false;
	// 	}

	FILE *pPcapFile = fopen(pszSavePcapFile, "w+b");

	if (pPcapFile == NULL)
	{
		oAt02dFile.Close();
		//fclose(pAt02dFile);
		return false;
	}

	fwrite(g_bytePcapHead_ns, sizeof(BYTE), 24, pPcapFile);
    BYTE pszReadDatas[CAP_RCD_BUFFER_MAX_LEN*2];
	size_t szRead = 0;
	DWORD dwHeadFrm = 0,dwAt02dPkgLenth = 0,dwPcapLenth = 0,dwTimeValue = 0;
	long nCurrParseLen = 0,nCurrParseLen_Head = 0,nValidLenth = 0;//�ϴν������һ֡����,�ӱ���ͷ���Ѷ�ȡ���ݵĳ���
	__int64 n64Time = 0;
	CString strTime;
    szRead = oAt02dFile.Read(pszReadDatas+ nCurrParseLen_Head,CAP_RCD_BUFFER_MAX_LEN*sizeof(BYTE));

	while (szRead>0/*!feof(pAt02dFile)*/)
	{
		//���Ķ�ȡʱ,����һ֡��δ������ȫ,�������һ֡���Ķ�ȡ������
        // 		szRead = fread(pszReadDatas+ nCurrParseLen_Head, sizeof(BYTE), CAP_RCD_BUFFER_MAX_LEN, pAt02dFile);
		// 
		// 		if (szRead <= 0)
		// 		{
		// 			break;
		// 		}

		nValidLenth = nCurrParseLen_Head + szRead;//��ǰ��ȡ����Ч����
		nCurrParseLen = 0;
		dwHeadFrm = Global_BufferGetDWORD(pszReadDatas);

		while((dwHeadFrm != STT_AT02_FIXED_HEAD)&&(nCurrParseLen < nValidLenth))
		{
			nCurrParseLen++;
			dwHeadFrm = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);
		}

		if (dwHeadFrm != STT_AT02_FIXED_HEAD)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ��ȡ���ĳ���(%u),δ�ҵ�����ͷ,Դ�ļ�(%s)��������."),szRead,strSrcAt02dFile.GetString());
			break;
		}

		nCurrParseLen_Head = nCurrParseLen;
		nCurrParseLen += 4;//��������ͷ
		dwAt02dPkgLenth = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);//��ȡ��ǰ֡���ĳ���
		dwAt02dPkgLenth *= 4;//��ǰ֡���ĳ��ȳ���4Ϊʵ��Pcap���ĵĳ���(ԭ���ȵ�λΪ4�ֽ�������)

		while (((nCurrParseLen_Head + dwAt02dPkgLenth + 4)<= nValidLenth)//��ǰ֡������ʼλ�ó���+�������ݳ���+����ͷ����,�ڶ�ȡ����Ч���ȷ�Χ��,����н���,���������ȡ
			&&(dwAt02dPkgLenth<nValidLenth))//��ֹdwAt02dPkgLenthΪ�ر��ֵ,��������ֵ�����
		{
			nCurrParseLen += 4;//�������Ȳ���,����Ϊʱ���
			dwAt02dPkgLenth -= 24;//�����Զ������ݽṹ����

			dwTimeValue = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);
			fwrite(&dwTimeValue, sizeof(BYTE), 4, pPcapFile);
			dwTimeValue = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen + 4);
			fwrite(&dwTimeValue, sizeof(BYTE), 4, pPcapFile);
			//n64Time = Global_BufferGetINT64(pszReadDatas + nCurrParseLen);
			//fwrite(&n64Time/*(pszReadDatas + nCurrParseLen)*/, sizeof(BYTE), 8, pPcapFile);
			//memcpy(&n64Time,(pszReadDatas + nCurrParseLen),8);
			//ep_cap_timeval_to_string_ns(n64Time,strTime);
			//fwrite((pszReadDatas + nCurrParseLen), sizeof(BYTE), 8, pPcapFile);
			nCurrParseLen += 20;//�����Զ������ݽṹ����
			dwPcapLenth = Global_GetPcapReadLenth(pszReadDatas + nCurrParseLen,dwAt02dPkgLenth);//����1Ϊ����ʵ�����ݲ��ֿ�ʼλ��,����2Ϊ���ݲ��ֳ���

			fwrite(&dwPcapLenth, sizeof(BYTE), 4, pPcapFile);
			fwrite(&dwPcapLenth, sizeof(BYTE), 4, pPcapFile);
			fwrite((pszReadDatas + nCurrParseLen), sizeof(BYTE), dwPcapLenth, pPcapFile);
			nCurrParseLen += dwPcapLenth;

			dwHeadFrm = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);

			while((dwHeadFrm != STT_AT02_FIXED_HEAD)&&(nCurrParseLen < nValidLenth))
			{
				nCurrParseLen++;
				dwHeadFrm = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);
			}

			if (dwHeadFrm == STT_AT02_FIXED_HEAD)
			{
				nCurrParseLen_Head = nCurrParseLen;
				nCurrParseLen += 4;//��������ͷ
				dwAt02dPkgLenth = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);//��ȡ��ǰ֡���ĳ���
				dwAt02dPkgLenth *= 4;//��ǰ֡���ĳ��ȳ���4Ϊʵ��Pcap���ĵĳ���(ԭ���ȵ�λΪ4�ֽ�������)
			}
		}

		if (nCurrParseLen_Head == 0)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ����Դ�ļ�(%s)��������,�䵱ǰ֡����(%ld)Խ��."),
				strSrcAt02dFile.GetString(),dwAt02dPkgLenth);
			break;
		}

		memcpy(pszReadDatas,pszReadDatas + nCurrParseLen_Head,(nValidLenth - nCurrParseLen_Head));
		nCurrParseLen_Head = nValidLenth - nCurrParseLen_Head;
        szRead = oAt02dFile.Read(pszReadDatas+ nCurrParseLen_Head,CAP_RCD_BUFFER_MAX_LEN*sizeof(BYTE));
	}

	oAt02dFile.close();
	//	fclose(pAt02dFile);
	fclose(pPcapFile);
	return true;
}

bool stt_save_pcap_file_ft3(const CString &strSrcAt02dFile,const char *pszSavePcapFile)
{
	CFile oAt02dFile;

	if (!oAt02dFile.Open(strSrcAt02dFile, CFile::modeRead))
	{
		return false;
	}

	FILE *pPcapFile = fopen(pszSavePcapFile, "w+b");

	if (pPcapFile == NULL)
	{
		oAt02dFile.Close();
		return false;
	}

	fwrite(g_bytePcapHead_ns, sizeof(BYTE), 24, pPcapFile);
	BYTE pszReadDatas[CAP_RCD_BUFFER_MAX_LEN*2];
	size_t szRead = 0;
	DWORD dwHeadFrm = 0,dwAt02dPkgLenth = 0,dwPcapLenth = 0,dwTimeValue = 0;
	long nCurrParseLen = 0,nCurrParseLen_Head = 0,nValidLenth = 0;//�ϴν������һ֡����,�ӱ���ͷ���Ѷ�ȡ���ݵĳ���
	__int64 n64Time = 0;
	CString strTime;
	szRead = oAt02dFile.Read(pszReadDatas+ nCurrParseLen_Head,CAP_RCD_BUFFER_MAX_LEN*sizeof(BYTE));

	while (szRead>0)
	{
		nValidLenth = nCurrParseLen_Head + szRead;//��ǰ��ȡ����Ч����
		nCurrParseLen = 0;
		dwHeadFrm = Global_BufferGetDWORD(pszReadDatas);

		while((dwHeadFrm != STT_AT02_FIXED_HEAD)&&(nCurrParseLen < nValidLenth))
		{
			nCurrParseLen++;
			dwHeadFrm = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);
		}

		if (dwHeadFrm != STT_AT02_FIXED_HEAD)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ��ȡ���ĳ���(%u),δ�ҵ�����ͷ,Դ�ļ�(%s)��������."),szRead,strSrcAt02dFile.GetString());
			break;
		}

		nCurrParseLen_Head = nCurrParseLen;
		nCurrParseLen += 4;//��������ͷ
		dwAt02dPkgLenth = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);//��ȡ��ǰ֡���ĳ���
		dwAt02dPkgLenth *= 4;//��ǰ֡���ĳ��ȳ���4Ϊʵ��Pcap���ĵĳ���(ԭ���ȵ�λΪ4�ֽ�������)

		while (((nCurrParseLen_Head + dwAt02dPkgLenth + 4)<= nValidLenth)//��ǰ֡������ʼλ�ó���+�������ݳ���+����ͷ����,�ڶ�ȡ����Ч���ȷ�Χ��,����н���,���������ȡ
			&&(dwAt02dPkgLenth<nValidLenth))//��ֹdwAt02dPkgLenthΪ�ر��ֵ,��������ֵ�����
		{
			nCurrParseLen += 4;//�������Ȳ���,����Ϊʱ���
			dwAt02dPkgLenth -= 24;//�����Զ������ݽṹ����

			dwTimeValue = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);
			fwrite(&dwTimeValue, sizeof(BYTE), 4, pPcapFile);
			dwTimeValue = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen + 4);
			fwrite(&dwTimeValue, sizeof(BYTE), 4, pPcapFile);
			nCurrParseLen += 20;//�����Զ������ݽṹ����

			dwPcapLenth = Global_BufferGetWord(pszReadDatas + nCurrParseLen - 8);//��֡���ĳ���
			fwrite(&dwPcapLenth, sizeof(BYTE), 4, pPcapFile);
			fwrite(&dwPcapLenth, sizeof(BYTE), 4, pPcapFile);
			fwrite((pszReadDatas + nCurrParseLen), sizeof(BYTE), dwPcapLenth, pPcapFile);
			nCurrParseLen += dwPcapLenth;

			dwHeadFrm = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);

			while((dwHeadFrm != STT_AT02_FIXED_HEAD)&&(nCurrParseLen < nValidLenth))
			{
				nCurrParseLen++;
				dwHeadFrm = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);
			}

			if (dwHeadFrm == STT_AT02_FIXED_HEAD)
			{
				nCurrParseLen_Head = nCurrParseLen;
				nCurrParseLen += 4;//��������ͷ
				dwAt02dPkgLenth = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);//��ȡ��ǰ֡���ĳ���
				dwAt02dPkgLenth *= 4;//��ǰ֡���ĳ��ȳ���4Ϊʵ��Pcap���ĵĳ���(ԭ���ȵ�λΪ4�ֽ�������)
			}
		}

		if (nCurrParseLen_Head == 0)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ����Դ�ļ�(%s)��������,�䵱ǰ֡����(%ld)Խ��."),
				strSrcAt02dFile.GetString(),dwAt02dPkgLenth);
			break;
		}

		memcpy(pszReadDatas,pszReadDatas + nCurrParseLen_Head,(nValidLenth - nCurrParseLen_Head));
		nCurrParseLen_Head = nValidLenth - nCurrParseLen_Head;
		szRead = oAt02dFile.Read(pszReadDatas+ nCurrParseLen_Head,CAP_RCD_BUFFER_MAX_LEN*sizeof(BYTE));
	}

	oAt02dFile.close();
	fclose(pPcapFile);
	return true;
}



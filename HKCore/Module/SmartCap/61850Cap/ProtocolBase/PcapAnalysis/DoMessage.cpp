#include "StdAfx.h"
#include "DoMessage.h"

CDoMessage* CDoMessage::g_pDoMessage = NULL;

long CDoMessage::g_nMngrRef = 0;

CDoMessage::CDoMessage(void)
{
	//1：9-1；
	//2：9-2；
	//3：Goose； 
	//4：TCP/IP；
	//5：Other；

	m_CurMsgType = 2; //如果是3则为GOOSE；
}

CDoMessage::~CDoMessage(void)
{

}

CDoMessage* CDoMessage::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pDoMessage = new CDoMessage();
	}

	return g_pDoMessage;
}

void CDoMessage::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pDoMessage;
		g_pDoMessage = NULL;
	}
}


bool CDoMessage::DealPcapFile(CString m_PcapFilePath)
{
	CFile t_DataFile;
	if (t_DataFile.Open(m_PcapFilePath.GetBuffer(0),CFile::modeRead|CFile::typeBinary|CFile::shareDenyNone))
	{
		int filelen = t_DataFile.GetLength();
		m_nArrayLength = filelen;
		int t_Count = m_nArrayLength/900;
		int t_LastCount  = m_nArrayLength%900;
		DataArray.ClearAll (0);
		if (DataArray.SetSize (filelen) == TRUE)
		{
			DataArray.SetUpperBound (filelen   -   1);	
			for (int i = 0 ;   i  <  900;  i++)
			{
				t_DataFile.Read(DataArray   +  t_Count  *  i,   t_Count);
			}
			t_DataFile.Read(DataArray  +  t_Count  *  900,   t_LastCount);
			t_DataFile.Close();
			return true;
		}
		else return FALSE;
	}
	return FALSE;
}

void  CDoMessage:: SetPacketFromXSmMemBuffe(BYTE *pBuffer,  int nBufferLen )
{
	if (pBuffer==NULL)
		return;

	//CPacket packet(pBuffer,  0  , nBufferLen);
	//m_NewPacketVector.push_back(packet);

	//unsigned char *pBuffer = DataArray.GetBuffer();
	////////////////开始/////////////////////	
	DWORD t_start = 0,   t_end;
	//t_start = 0;//timeGetTime(); mym 注销掉；

	int nPos =  24;	// 考虑PCAP文件的包头的问题；
	//if(DataArray.GetLength()  < 12)
	//	return;

	//	if(DataArray.GetAt(12)==0x01)
	//{
	//	m_usOrns = 1000;	
	//}
	//else
	//{
	m_usOrns  = 1;//1微秒，1000纳秒	
	//	}

	//CString t_strData;
	//int t_count = m_nArrayLength/1000;

	BYTE   t1 = 0,    t2 = 0,   t3 = 0,   t4 = 0;

	int   nStartPos  =  nPos;

	nPos  +=  8;

	t4 =   pBuffer[nPos++];	
	t3 =   pBuffer[nPos++];
	t2 =   pBuffer[nPos++];
	t1 =   pBuffer[nPos++];

	int t_reallength  = (int)(t4  +  t3  *  pow(2.0,  8)  +  t2  *  pow(2.0,  16)  +  t1  *  pow(2.0,   24));

	//nPos  +=   4;	
	//nPos  +=   t_reallength;

	//if (nPos  >  m_nArrayLength)
	//{
	//	break;
	//}

	//CPacket t_Protocol(pBuffer, t_StartPos,t_reallength);

	CPacket packet( nStartPos,   t_reallength);
	m_NewPacketVector.push_back(packet);
}

void CDoMessage::DealPackFromDataArray()
{
	//unsigned char *pBuffer = DataArray.GetBuffer();
	////////////////开始/////////////////////	
	DWORD t_start,t_end;
	t_start = 0;//timeGetTime(); mym 注销掉；

	int t_Pos =  24;	
	if(DataArray.GetLength()  < 12)
		return;
	
	if(DataArray.GetAt(12)==0x01)
	{
		m_usOrns = 1000;	
	}
	else
	{
		m_usOrns = 1;//1微秒，1000纳秒	
	}
	
	CString t_strData;
	int t_count = m_nArrayLength/1000;

	BYTE t1 = 0,    t2 = 0,   t3 = 0,   t4 = 0;
	int num = 1;
	int num1 = 0;
	try
	{	
		while (t_Pos   <   m_nArrayLength)
		{
			int t_StartPos  =  t_Pos;
			t_Pos  +=  8;

			t4 =  DataArray.GetAt(t_Pos++);	
			t3 =  DataArray.GetAt(t_Pos++);
			t2 =  DataArray.GetAt(t_Pos++);
			t1 =  DataArray.GetAt(t_Pos++);
			int t_reallength  = (int)(t4  +  t3  *  pow(2.0,  8)  +  t2  *  pow(2.0,  16)  +  t1  *  pow(2.0,  24));
			t_Pos  +=  4;	
			t_Pos  +=  t_reallength;
			if (t_Pos  >  m_nArrayLength)
			{
				break;
			}

			//CPacket t_Protocol(pBuffer, t_StartPos,t_reallength);
			CPacket t_Protocol( t_StartPos,   t_reallength);

			m_NewPacketVector.push_back(t_Protocol);
			if (t_Pos  >  t_count  * num)
			{
				//pFrame->m_pWndProgressCtrl->SetPos(1000+num);
				num++;
			}
			num1++;
		}
	}
	catch (CMemoryException* e)
	{
		return;
	}
	// 	///////////////////结束/////////////////
	// 	t_end = timeGetTime();
	// 	int t_Dif = t_end - t_start;
	// 	CString temp1;
	// 	temp1.Format(_T("%d"),t_Dif);		
	// 	AfxMessageBox(temp1);
	int af  =  0;
}

void CDoMessage::DoPacpFile()
{
	DealPcapFile(m_DealPacpFile);	
	DealPackFromDataArray();
}

/*
*各个参数说明：
*第二个参数(1:  所有报文,  2: 9 - 2总体,  3: 同一APPID)
*第三个参数(对应Mac的选择索引)
*/
CString CDoMessage::GetErrorInfor( int m_ID,    int m_Type,   int m_CurSelContentType, int  &nPacketNO)
{
	//if (m_92Vector.size() > 0)
		m_CurMsgType = 2;

	//if (m_GooseVector.size()  > 0)
	//	m_CurMsgType = 3;
    //m_Type;;//这里也是二；

	CString strResult = _T("");
	if (m_GooseAbnormalFinshedFlag !=  1)
	{
		return strResult;
	}
	switch(m_Type)
	{
	case 1:case PRO_Combine://全显所有报文,  包括GOOSE和SMV的；
		{
			CPacket & t_Pro =  m_NewPacketVector[m_ID];

			int t_Type  =   t_Pro.m_nAbnormalType;
			switch(t_Type)
			{
			case ABNORMAL_LOSTPOINT:
				strResult = _T("Frame loss");
				break;
			case ABNORMAL_ERRORNUM:
				strResult = _T("smpCnt jumoing");
				break;
			case ABNORMAL_LOSTSMSYNC:
				strResult = _T("Synchronization sigal loss");
				break;
			case ABNORMAL_SMVFACTORCHANGE:
				strResult = _T("Quality change");
				break;
			case ABNORMAL_SMVFLYPOINT:
				strResult = _T("Data abnormal");
				break;
			case GOOSE_BITCHANGE:
				strResult = _T("Status change");
				break;
			case GOOSE_CLOCKABNORMAL:
				strResult = _T("Clock abnormal");
				break;
			case GOOSE_CLOCKERROR:
				strResult = _T("Clock fault");
				break;
			case GOOSE_CLOCKUPSYNC:
				strResult = _T("Unsynchronization");
				break;
			case GOOSE_EQURESTART:
				strResult = _T("Restart");
				break;
			case GOOSE_SQNUMFIRSTVALUE:
				strResult = _T("Status change\\SqNum error");
				break;
			case GOOSE_VITRUALBITCHANGE:
				strResult = _T("Virtual status change");
				break;
			case GOOSE_STNUMLOST:
				strResult = _T("StNum loss");
				break;
			case GOOSE_BITCHANGESTNUMLOST:
				strResult = _T("Status change/StNum loss");
				break;
			case GOOSE_SQREPEAT:
				strResult = _T("SqNum repetition");
				break;
			case GOOSE_SQNUMLOST:
				strResult = _T("SqNum loss");
				break;
			case GOOSE_TIMELIVEEQUAL0:
				strResult = _T("Time allowed to live is 0");
				break;
			case GOOSE_TIMEDELAY:
				strResult = _T("GOOSE delay time");
				break;
			case GOOSE_BREAK:
				strResult = _T("GOOSE break");
				break;
			}
		}
		break;
	case 2://同类型全显
		{
			int t_Size =  m_GlobalAbnormalPointPos.size();
			if (t_Size  >  0)
			{
				int t_AbnormalPos =  0;
				if (m_CurMsgType == IEC_SMV92)
				{
					t_AbnormalPos = m_92Vector[m_ID];
				}
				else
				{
					if (m_CurMsgType==IEC_SMV91)
					{
						t_AbnormalPos =  m_91Vector[m_ID];
					}
					else
					{
						if (m_CurMsgType==IEC_GOOSE)
						{
							t_AbnormalPos  =  m_GooseVector[m_ID];
						}
					}
				}
				nPacketNO   = t_AbnormalPos;
				CPacket & t_Pro =  m_NewPacketVector[t_AbnormalPos];
				int t_Type  =  t_Pro.m_nAbnormalType;

		//		CGetInforFormVector::GetTimeString(t_Pro);

				switch(t_Type)
				{
				case ABNORMAL_LOSTPOINT:
					strResult = _T("丢帧"); //Frame loss
					break;
				case ABNORMAL_ERRORNUM:
					strResult = _T("错序");//strResult = _T("跳点 smpCnt jumping");
					break;
				case ABNORMAL_LOSTSMSYNC:
					strResult = _T(" 同步信号丢失"); //Synchronization sigal loss
					break;
				case ABNORMAL_MULTIMUNOSYNC:
					strResult = _T("MU unsynchorization");
					break;
				case ABNORMAL_SMVFACTORCHANGE:
					strResult = _T("品质改变");// Quality change
					break;
				case ABNORMAL_SMVFLYPOINT:
					strResult = _T("通道数据不正常"); //Data abnormal
					break;
				case GOOSE_CLOCKABNORMAL:
					strResult = _T("时钟异常"); //Clock abnormal
					break;
				case GOOSE_CLOCKERROR:
					strResult = _T("时钟失效"); //Clock fault
					break;
				case GOOSE_CLOCKUPSYNC:
					strResult = _T("Unsynchronization");
					break;
				case GOOSE_BITCHANGE:
					strResult = _T("状态改变 Status change");
					break;
				case GOOSE_EQURESTART:
					strResult = _T("装置重启");//_T("Restart");
					break;
				case GOOSE_SQNUMFIRSTVALUE:
					strResult = _T("变位\\SqNum 初值错误");//_T("Status change\\SqNum error");
					break;
				case GOOSE_VITRUALBITCHANGE:
					strResult = _T("虚变位");//Virtual status change
					break;
				case GOOSE_STNUMLOST:
					strResult = _T("StNum 丢失"); //loss
					break;
				case GOOSE_BITCHANGESTNUMLOST:
					strResult = _T("状态改变/StNum丢失");//_T("Status change/StNum loss");
					break;
				case GOOSE_SQREPEAT:
					strResult = _T("SqNum 重复"); // repetition
					break;
				case GOOSE_SQNUMLOST:
					strResult = _T("SqNum 丢失"); //loss
					break;
				case GOOSE_TIMELIVEEQUAL0:
					strResult = _T("Time allowed to live is 0");
					break;
				case GOOSE_TIMEDELAY:
					strResult = _T("GOOSE 延时"); //delay time
					break;
				case GOOSE_BREAK:
					strResult = _T("变位/GOOSE break");//_T("Status change/GOOSE break");
					break;
				}
			}
		}
		break;
	case 3://独立MAC显示
		{
			if (m_SMVAbnormalPosArray.size()  >  0  ||   m_GooseAbnormalPosArray.size()  >  0)
			{			
				if (m_CurMsgType == IEC_SMV92)
				{
					Content  & t_Con =  m_92KindsVector[m_CurSelContentType];
					CAbnormalPos  & t_Abnor =  m_SMVAbnormalPosArray[m_CurSelContentType];
					int t_Size =  t_Abnor.m_AbnormalCurContentPos.size();
					if (t_Size > 0)
					{
						CPacket & t_Pro =  m_NewPacketVector[t_Con.m_Vector[m_ID]];
						int t_Type =  t_Pro.m_nAbnormalType;
						switch(t_Type)
						{
						case ABNORMAL_LOSTPOINT:
							strResult = _T("Frame loss");
							break;
						case ABNORMAL_ERRORNUM:
							strResult = _T("smpCnt jumping");
							break;
						case ABNORMAL_LOSTSMSYNC:
							strResult = _T("Lost synchorization signal");
							break;
						case ABNORMAL_SMVFACTORCHANGE:
							strResult = _T("Quality change");
							break;
						case ABNORMAL_SMVFLYPOINT:
							strResult = _T("Data abnoemal");
							break;
						}
					}
				}
				else
				{
					if (m_CurMsgType == IEC_SMV91)
					{
						Content & t_Con =  m_91KindsVector[m_CurSelContentType];
						CAbnormalPos & t_Abnor =  m_SMVAbnormalPosArray[m_CurSelContentType];
						int t_Size =  t_Abnor.m_AbnormalCurContentPos.size();
						if (t_Size>0)
						{
							CPacket & t_Pro =  m_NewPacketVector[t_Con.m_Vector[m_ID]];
							int t_Type  =  t_Pro.m_nAbnormalType;
							switch(t_Type)
							{
							case ABNORMAL_LOSTPOINT:
								strResult =  _T("Frame loss");
								break;
							case ABNORMAL_ERRORNUM:
								strResult =  _T("smpCnt jumping");
								break;
							case ABNORMAL_LOSTSMSYNC:
								strResult =  _T("Lost synchorization signal");
								break;
							case ABNORMAL_SMVFACTORCHANGE:
								strResult =  _T("Quality change");
								break;
							case ABNORMAL_SMVFLYPOINT:
								strResult =  _T("Data abnoemal");
								break;
							}
						}
					}
					else
					{
						if (m_CurMsgType == IEC_GOOSE)
						{
							Content &  t_Con =  m_GooseKindsVector[m_CurSelContentType];
							CAbnormalPos & t_Abnor =  m_GooseAbnormalPosArray[m_CurSelContentType];
							int t_Size  =   t_Abnor.m_AbnormalCurContentPos.size();
							if (t_Size  >  0)
							{
								CPacket & t_Pro =  m_NewPacketVector[t_Con.m_Vector[m_ID]];
								int t_Type =  t_Pro.m_nAbnormalType;
								switch(t_Type)
								{
								case GOOSE_CLOCKABNORMAL:
									strResult =  _T("Clock abnormal");
									break;
								case GOOSE_CLOCKERROR:
									strResult =  _T("Clock fault");
									break;
								case GOOSE_CLOCKUPSYNC:
									strResult =  _T("Unsynchronization");
									break;
								case GOOSE_BITCHANGE:
									strResult =  _T("Status change");
									break;
								case GOOSE_STNUMLOST:
									strResult =  _T("StNum loss");
									break;
								case GOOSE_BITCHANGESTNUMLOST:
									strResult =  _T("Status change/StNum loss");
									break;
								case GOOSE_SQREPEAT:
									strResult =  _T("SqNum repetition");
									break;
								case GOOSE_SQNUMLOST:
									strResult =  _T("SqNum loss");
									break;
								case GOOSE_SQNUMFIRSTVALUE:
									strResult =  _T("Status change\\SqNum error");
									break;
								case GOOSE_VITRUALBITCHANGE:
									strResult =  _T("Virtual status change");
									break;
								case GOOSE_EQURESTART:
									strResult =  _T("Restart");
									break;
								case GOOSE_TIMELIVEEQUAL0:
									strResult =  _T("Time allowed to live is 0");
									break;
								case GOOSE_TIMEDELAY:
									strResult =  _T("GOOSE delay time");
									break;
								case GOOSE_BREAK:
									strResult =  _T("GOOSE break");
									break;
								}
							}
						}
					}
				}
			}
		}
		break;
	}

	return strResult;
}


void   CDoMessage:: ClearAllData()
{
	DataArray.ClearAll(0);

	m_NewPacketVector.clear();

	m_ProTypeArray.RemoveAll();//Goose, 9-1,9-2,其他

	m_91DesArray.RemoveAll();
	m_91SRCArray.RemoveAll();
	m_91AppIDArray.RemoveAll();
	m_92DesArray.RemoveAll();
	m_92SRCArray.RemoveAll();
	m_92AppIDArray.RemoveAll();	
	m_GooseDesArray.RemoveAll();
	m_GooseSRCArray.RemoveAll();
	m_GooseAppIDArray.RemoveAll();	

	m_91Vector.clear(); // 存储一个PCAP文件中9-1帧的数量； 

	m_92Vector.clear();  // 存储一个PCAP文件中9-2帧的数量； 
	m_GooseVector.clear(); // 存储一个PCAP文件中GOOSE帧的数量； 


	m_TcpVector.clear();
	m_UdpVector.clear();
	m_ArpVector.clear();
	m_1588Vector.clear();
	m_OtherVector.clear();

	m_91KindsVector.clear();

	m_92KindsVector.clear();         // 这里存储的是有几个不同的MAC地址，包括 MAC,APPID等,和同一个MAC的所有帧在整个报文
	//  列表中的序号，也就是在m_NewPacketVector的序号；

	m_GooseKindsVector.clear();  // 这里存储的是有几个不同的MAC地址，包括 MAC,APPID等,和同一个MAC的所有帧在整个报文
	//  列表中的序号，也就是在m_NewPacketVector的序号；

	m_CombineKindVector.clear();
	m_CombineAbnormalKindVector.clear();

	m_1588eKindsVector.clear();
	m_OtherKindsVector.clear();
	m_TcpKindsVector.clear();

	m_TimeStatisticDataArray.clear();

	m_MacWaveDataArray.clear();// 存储，为了波形数据;

	m_SMVAbnormalPosArray.clear();  // SMV异常  存储；这里存储一个PCAP文件所有的SMV异常;

	m_GooseAbnormalPosArray.clear();//GOOSE异常 ；存储；这里存储一个PCAP文件所有的GOOSE异常;

	m_GlobalAbnormalPointPos.clear();
}
#include "StdAfx.h"
#include "DoMessage.h"

CDoMessage* CDoMessage::g_pDoMessage = NULL;

long CDoMessage::g_nMngrRef = 0;

CDoMessage::CDoMessage(void)
{
	//1��9-1��
	//2��9-2��
	//3��Goose�� 
	//4��TCP/IP��
	//5��Other��

	m_CurMsgType = 2; //�����3��ΪGOOSE��
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
	////////////////��ʼ/////////////////////	
	DWORD t_start = 0,   t_end;
	//t_start = 0;//timeGetTime(); mym ע������

	int nPos =  24;	// ����PCAP�ļ��İ�ͷ�����⣻
	//if(DataArray.GetLength()  < 12)
	//	return;

	//	if(DataArray.GetAt(12)==0x01)
	//{
	//	m_usOrns = 1000;	
	//}
	//else
	//{
	m_usOrns  = 1;//1΢�룬1000����	
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
	////////////////��ʼ/////////////////////	
	DWORD t_start,t_end;
	t_start = 0;//timeGetTime(); mym ע������

	int t_Pos =  24;	
	if(DataArray.GetLength()  < 12)
		return;
	
	if(DataArray.GetAt(12)==0x01)
	{
		m_usOrns = 1000;	
	}
	else
	{
		m_usOrns = 1;//1΢�룬1000����	
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
	// 	///////////////////����/////////////////
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
*��������˵����
*�ڶ�������(1:  ���б���,  2: 9 - 2����,  3: ͬһAPPID)
*����������(��ӦMac��ѡ������)
*/
CString CDoMessage::GetErrorInfor( int m_ID,    int m_Type,   int m_CurSelContentType, int  &nPacketNO)
{
	//if (m_92Vector.size() > 0)
		m_CurMsgType = 2;

	//if (m_GooseVector.size()  > 0)
	//	m_CurMsgType = 3;
    //m_Type;;//����Ҳ�Ƕ���

	CString strResult = _T("");
	if (m_GooseAbnormalFinshedFlag !=  1)
	{
		return strResult;
	}
	switch(m_Type)
	{
	case 1:case PRO_Combine://ȫ�����б���,  ����GOOSE��SMV�ģ�
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
	case 2://ͬ����ȫ��
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
					strResult = _T("��֡"); //Frame loss
					break;
				case ABNORMAL_ERRORNUM:
					strResult = _T("����");//strResult = _T("���� smpCnt jumping");
					break;
				case ABNORMAL_LOSTSMSYNC:
					strResult = _T(" ͬ���źŶ�ʧ"); //Synchronization sigal loss
					break;
				case ABNORMAL_MULTIMUNOSYNC:
					strResult = _T("MU unsynchorization");
					break;
				case ABNORMAL_SMVFACTORCHANGE:
					strResult = _T("Ʒ�ʸı�");// Quality change
					break;
				case ABNORMAL_SMVFLYPOINT:
					strResult = _T("ͨ�����ݲ�����"); //Data abnormal
					break;
				case GOOSE_CLOCKABNORMAL:
					strResult = _T("ʱ���쳣"); //Clock abnormal
					break;
				case GOOSE_CLOCKERROR:
					strResult = _T("ʱ��ʧЧ"); //Clock fault
					break;
				case GOOSE_CLOCKUPSYNC:
					strResult = _T("Unsynchronization");
					break;
				case GOOSE_BITCHANGE:
					strResult = _T("״̬�ı� Status change");
					break;
				case GOOSE_EQURESTART:
					strResult = _T("װ������");//_T("Restart");
					break;
				case GOOSE_SQNUMFIRSTVALUE:
					strResult = _T("��λ\\SqNum ��ֵ����");//_T("Status change\\SqNum error");
					break;
				case GOOSE_VITRUALBITCHANGE:
					strResult = _T("���λ");//Virtual status change
					break;
				case GOOSE_STNUMLOST:
					strResult = _T("StNum ��ʧ"); //loss
					break;
				case GOOSE_BITCHANGESTNUMLOST:
					strResult = _T("״̬�ı�/StNum��ʧ");//_T("Status change/StNum loss");
					break;
				case GOOSE_SQREPEAT:
					strResult = _T("SqNum �ظ�"); // repetition
					break;
				case GOOSE_SQNUMLOST:
					strResult = _T("SqNum ��ʧ"); //loss
					break;
				case GOOSE_TIMELIVEEQUAL0:
					strResult = _T("Time allowed to live is 0");
					break;
				case GOOSE_TIMEDELAY:
					strResult = _T("GOOSE ��ʱ"); //delay time
					break;
				case GOOSE_BREAK:
					strResult = _T("��λ/GOOSE break");//_T("Status change/GOOSE break");
					break;
				}
			}
		}
		break;
	case 3://����MAC��ʾ
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

	m_ProTypeArray.RemoveAll();//Goose, 9-1,9-2,����

	m_91DesArray.RemoveAll();
	m_91SRCArray.RemoveAll();
	m_91AppIDArray.RemoveAll();
	m_92DesArray.RemoveAll();
	m_92SRCArray.RemoveAll();
	m_92AppIDArray.RemoveAll();	
	m_GooseDesArray.RemoveAll();
	m_GooseSRCArray.RemoveAll();
	m_GooseAppIDArray.RemoveAll();	

	m_91Vector.clear(); // �洢һ��PCAP�ļ���9-1֡�������� 

	m_92Vector.clear();  // �洢һ��PCAP�ļ���9-2֡�������� 
	m_GooseVector.clear(); // �洢һ��PCAP�ļ���GOOSE֡�������� 


	m_TcpVector.clear();
	m_UdpVector.clear();
	m_ArpVector.clear();
	m_1588Vector.clear();
	m_OtherVector.clear();

	m_91KindsVector.clear();

	m_92KindsVector.clear();         // ����洢�����м�����ͬ��MAC��ַ������ MAC,APPID��,��ͬһ��MAC������֡����������
	//  �б��е���ţ�Ҳ������m_NewPacketVector����ţ�

	m_GooseKindsVector.clear();  // ����洢�����м�����ͬ��MAC��ַ������ MAC,APPID��,��ͬһ��MAC������֡����������
	//  �б��е���ţ�Ҳ������m_NewPacketVector����ţ�

	m_CombineKindVector.clear();
	m_CombineAbnormalKindVector.clear();

	m_1588eKindsVector.clear();
	m_OtherKindsVector.clear();
	m_TcpKindsVector.clear();

	m_TimeStatisticDataArray.clear();

	m_MacWaveDataArray.clear();// �洢��Ϊ�˲�������;

	m_SMVAbnormalPosArray.clear();  // SMV�쳣  �洢������洢һ��PCAP�ļ����е�SMV�쳣;

	m_GooseAbnormalPosArray.clear();//GOOSE�쳣 ���洢������洢һ��PCAP�ļ����е�GOOSE�쳣;

	m_GlobalAbnormalPointPos.clear();
}
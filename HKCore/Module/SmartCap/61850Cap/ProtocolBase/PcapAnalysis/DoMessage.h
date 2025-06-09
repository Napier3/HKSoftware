#pragma once

#include "Simparr.h"
#include <vector>
//#include "TcpProtocol.h"
#include "Packet.h"
#include <math.h>
#include "MacDifWaveData.h"
#include "AbnormalPos.h"

#include "TimeDifData.h"

//#include "MMSystem.h"

#include "HeadFile.h"

class CGetInforFormVector;

struct Content 
{
	BYTE   m_SRC[6];
	BYTE    m_DES[6];
	BYTE    m_APPID[2];
	CString m_strSRC;
	CString m_strDes;
	CString m_strAppID;
	CString m_OtherType;
	int          m_nMaxSmpCnt;
	int		  m_nASDUNum;
	BOOL   m_bAbnoState;
	std::vector <int> m_Vector; // �洢���Ǹ�APPID�µ�һ֡һ֡�������ڵ�PCAP�ļ��е���ţ�
	int         m_nPrePacketSize;
	double  t_TotalTime;
	int         m_nOffset;
};

struct TCPContent 
{
	BYTE m_SRC[4];
	BYTE m_DES[4];
	std::vector<int> m_Vector;
	std::vector<int> m_ComunicationVector;
	std::vector<int> m_MMSVector;
	int m_TcpAddPos;
};

class CDoMessage
{
public:
	CDoMessage(void);
	~CDoMessage(void);
	static long g_nMngrRef;

public:
	static CDoMessage* g_pDoMessage;
	static CDoMessage* Create();
	static void Release();


public:
	void      DealPackFromDataArray();
	bool      DealPcapFile(CString m_PcapFilePath);
	void      DoPacpFile();
	void      SetPacketFromXSmMemBuffe(BYTE *pBuffer,  int nBufferLen = 0);
    void       ClearAllData();

	// ����
public:	

	CString m_strFileName;

	int     m_nArrayLength;
	bool  m_bGetTypeWork;


	SimpleArray<unsigned char> DataArray;

	std::vector<CPacket >m_NewPacketVector;

	CStringArray	m_ProTypeArray;//Goose, 9-1,9-2,����

	CStringArray	m_91DesArray,m_91SRCArray,m_91AppIDArray;
	CStringArray	m_92DesArray,m_92SRCArray,m_92AppIDArray;	
	CStringArray	m_GooseDesArray,m_GooseSRCArray,m_GooseAppIDArray;	

	std::vector<int> m_91Vector; // �洢һ��PCAP�ļ���9-1֡�������� 

	std::vector<int> m_92Vector;  // �洢һ��PCAP�ļ���9-2֡�������� 
	std::vector<int> m_GooseVector; // �洢һ��PCAP�ļ���GOOSE֡�������� 


	std::vector<int> m_TcpVector;
	std::vector<int> m_UdpVector;
	std::vector<int> m_ArpVector;
	std::vector<int> m_1588Vector;
	std::vector<int> m_OtherVector;

	std::vector<Content> m_91KindsVector;

	std::vector<Content> m_92KindsVector;         // ����洢�����м�����ͬ��MAC��ַ������ MAC,APPID��,��ͬһ��MAC������֡����������
	                                                                              //  �б��е���ţ�Ҳ������m_NewPacketVector����ţ�

	std::vector<Content> m_GooseKindsVector;  // ����洢�����м�����ͬ��MAC��ַ������ MAC,APPID��,��ͬһ��MAC������֡����������
	                                                                              //  �б��е���ţ�Ҳ������m_NewPacketVector����ţ�

	std::vector<std::vector<int>> m_CombineKindVector;
	std::vector<std::vector<int>> m_CombineAbnormalKindVector;

	std::vector<Content> m_1588eKindsVector;
	std::vector<Content> m_OtherKindsVector;;
	std::vector<TCPContent> m_TcpKindsVector;

	std::vector<CTimeDifData> m_TimeStatisticDataArray;

	std::vector<CMacDifWaveData> m_MacWaveDataArray;// �洢��Ϊ�˲�������;

	std::vector<CAbnormalPos> m_SMVAbnormalPosArray;  // SMV�쳣  �洢������洢һ��PCAP�ļ����е�SMV�쳣;

	std::vector<CAbnormalPos> m_GooseAbnormalPosArray;//GOOSE�쳣 ���洢������洢һ��PCAP�ļ����е�GOOSE�쳣;

	std::vector<int> m_GlobalAbnormalPointPos;

	int m_FinshedFlag;
	int m_SMVAbnormalFinshedFlag;
	int m_GooseAbnormalFinshedFlag;

	int m_usOrns;

	/////////////////////////////////////////////////////////////////
	// ����
public:
	//OCArray<CMultiDocTemplate *> m_pCapArray;
	//CPrePcapData pPcapData;
	//	SimpleArray<unsigned char> DataArray;

	int g_PcapFileNum;
	CString m_DealPacpFile;

	int g_CurAddDownPanType;

	int g_OpenComputerTimeDifFlag ;

	CMacDifWaveData * pWave0;


	// 2020-6-10 add mym;
	int m_CurMsgType;   //1 :�� 9-1�� 2��9-2��  3��Goose�� 4��TCP/IP��  5��Other��
	int m_CurSelContentType;
	int m_MMSEventOrCommunication;//1:�¼� 2:����
	CString GetErrorInfor(int m_ID,int m_Type,int m_CurSelContentType, int  &nPacketNO);

};

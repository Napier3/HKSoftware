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
	std::vector <int> m_Vector; // 存储的是该APPID下的一帧一帧数据所在的PCAP文件中得序号；
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

	// 属性
public:	

	CString m_strFileName;

	int     m_nArrayLength;
	bool  m_bGetTypeWork;


	SimpleArray<unsigned char> DataArray;

	std::vector<CPacket >m_NewPacketVector;

	CStringArray	m_ProTypeArray;//Goose, 9-1,9-2,其他

	CStringArray	m_91DesArray,m_91SRCArray,m_91AppIDArray;
	CStringArray	m_92DesArray,m_92SRCArray,m_92AppIDArray;	
	CStringArray	m_GooseDesArray,m_GooseSRCArray,m_GooseAppIDArray;	

	std::vector<int> m_91Vector; // 存储一个PCAP文件中9-1帧的数量； 

	std::vector<int> m_92Vector;  // 存储一个PCAP文件中9-2帧的数量； 
	std::vector<int> m_GooseVector; // 存储一个PCAP文件中GOOSE帧的数量； 


	std::vector<int> m_TcpVector;
	std::vector<int> m_UdpVector;
	std::vector<int> m_ArpVector;
	std::vector<int> m_1588Vector;
	std::vector<int> m_OtherVector;

	std::vector<Content> m_91KindsVector;

	std::vector<Content> m_92KindsVector;         // 这里存储的是有几个不同的MAC地址，包括 MAC,APPID等,和同一个MAC的所有帧在整个报文
	                                                                              //  列表中的序号，也就是在m_NewPacketVector的序号；

	std::vector<Content> m_GooseKindsVector;  // 这里存储的是有几个不同的MAC地址，包括 MAC,APPID等,和同一个MAC的所有帧在整个报文
	                                                                              //  列表中的序号，也就是在m_NewPacketVector的序号；

	std::vector<std::vector<int>> m_CombineKindVector;
	std::vector<std::vector<int>> m_CombineAbnormalKindVector;

	std::vector<Content> m_1588eKindsVector;
	std::vector<Content> m_OtherKindsVector;;
	std::vector<TCPContent> m_TcpKindsVector;

	std::vector<CTimeDifData> m_TimeStatisticDataArray;

	std::vector<CMacDifWaveData> m_MacWaveDataArray;// 存储，为了波形数据;

	std::vector<CAbnormalPos> m_SMVAbnormalPosArray;  // SMV异常  存储；这里存储一个PCAP文件所有的SMV异常;

	std::vector<CAbnormalPos> m_GooseAbnormalPosArray;//GOOSE异常 ；存储；这里存储一个PCAP文件所有的GOOSE异常;

	std::vector<int> m_GlobalAbnormalPointPos;

	int m_FinshedFlag;
	int m_SMVAbnormalFinshedFlag;
	int m_GooseAbnormalFinshedFlag;

	int m_usOrns;

	/////////////////////////////////////////////////////////////////
	// 操作
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
	int m_CurMsgType;   //1 :： 9-1； 2：9-2；  3：Goose； 4：TCP/IP；  5：Other；
	int m_CurSelContentType;
	int m_MMSEventOrCommunication;//1:事件 2:交互
	CString GetErrorInfor(int m_ID,int m_Type,int m_CurSelContentType, int  &nPacketNO);

};

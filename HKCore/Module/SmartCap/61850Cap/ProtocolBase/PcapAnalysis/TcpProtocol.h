#pragma once
#include "Packet.h"
class CDoMessage;

class CTcpProtocol 
{
public:
	int m_sDataTimePos;
	int m_sSecimePos;
	int m_sDifUpTime;
	CString m_DataTime;
	CString m_SecTime;
	CString m_DifUpTime;
	CString m_Infor;
	int m_ProType;
	int m_PackSize;
	int m_RealPackSize;
	int m_StartPos;
	int m_EndPos;
	int m_smpCnt;
	int m_91Or92;
	int m_SMVOrGoose;
	int smpCnt;
	int m_Lock;
	BOOL b_LostPack;
	int offset;
	int m_TcpOrUdp;
	int m_60AfterLength;
	CTcpProtocol(){};
	CTcpProtocol(int siDataTime,int siSecTime,int siDifUpTime,int m_iPacksize,int m_iRealPacksize,int m_iStartPos,int m_iEndPos);
public:
	CString GetTimeString(CDoMessage * pDo);
	int GetTimeDif(CDoMessage * pDo);
	CString GetProtocolType(CDoMessage * pDo);
	void GetProtocolTypeValue(CDoMessage * pDo);
	CString GetPackLegth();
	int GetSmpCntValue(CDoMessage * pDo);
	bool GetPackHexDataPart(CDoMessage * pDo,CByteArray &m_ByteArray);

public:	
	BYTE GetNext92Flag(CDoMessage * pDo,int &m_FindPos);
	inline CTcpProtocol& operator=(const CTcpProtocol& rhs)
	{	

		m_DataTime = rhs.m_DataTime;
		m_SecTime = rhs.m_SecTime ;
		m_DifUpTime = rhs.m_DifUpTime;
		m_RealPackSize = rhs.m_RealPackSize;
		m_PackSize = rhs.m_PackSize ;  
		m_StartPos = rhs.m_StartPos;
		m_EndPos = rhs.m_EndPos;
		return (*this);
	};
public:
	~CTcpProtocol(void);
};

#pragma once
#include "Packet.h"

#include "HeadFile.h"
#include "DoMessage.h"
#include "GetInforFormVector.h"

class CGetInforFormVector
{
public:

	CGetInforFormVector(void);

	~CGetInforFormVector(void);

public:
	static	CString GetTimeString(CDoMessage * pDo,CPacket &Pro);
	static	CString GetDifTimeString(CDoMessage * pDo,CPacket &ProCur,CPacket &ProUp,int nType =0);
	static	unsigned long GetDifTimeINT(CDoMessage * pDo,CPacket &ProCur,CPacket &ProUp,int nSecondMode=0);
	static	double GetDifTimeDouble(CDoMessage * pDo,CPacket &ProCur,CPacket &ProUp,int nSecondMode=0);
	static	CString GetDifTimeDoubleSecondMode(CDoMessage * pDo,CPacket &ProCur,CPacket &ProUp);
	static	CString GetSmpCntValue(CDoMessage * pDo,CPacket &Pro);
	static	int GetSmpCntValue(CDoMessage * pDo,CPacket &Pro,int n91or92,int noffset);
	static  CString GetProtocolType(CDoMessage * pDo,CPacket &m_Pro,int &nTypeValue,int &nSmvOrGoose,int &n91Or92,int &nOffset);

	static  int GetFlagPos(CByteArray &byDataArray,int nFlag,int nFindPos=0);
	static  BYTE GetNext92Flag(CDoMessage * pDo,int &m_FindPos);
	static  BYTE GetNextDataArrayFlag(CByteArray &byDataArray,int &nFindPos,int nType=0);//m_Type =0:正常，m_Type = 1为MMS中长度大于81的数据，例如C1 A2

	static bool GetPackHexDataPart(CDoMessage * pDo,CPacket &Pro,CByteArray &byDataArray);
	static void GetDesMacArray(CDoMessage * pDo,CPacket &Pro,CByteArray &byDataArray);
	static void GetSRCMacArray(CDoMessage * pDo,CPacket &Pro,CByteArray &byDataArray);
	static void GetAppID(CDoMessage * pDo,CPacket &m_Pro,CByteArray &byDataArray,int noffset);
	static void Get1588AppID(CDoMessage * pDo,CPacket &Pro,CByteArray &byDataArray,int noffset);
	static CString Get1588SqID(CDoMessage * pDo,CPacket &Pro,CByteArray &byDataArray,int noffset);
	static CString GetStNum(CDoMessage * pDo,CPacket &Pro);
	static CString GetSqNum(CDoMessage * pDo,CPacket &Pro);
	static int GetTimeAllowToLive(CDoMessage * pDo,CPacket &Pro);
	static int GetEventTimeStampFactor(CDoMessage * pDo,CPacket &Pro);
	static CString GetASN1Flag(CDoMessage * pDo,CPacket &Pro,BYTE byFlag,int nKindResult=0,int nRepeat =0);
	static CString GetASN1Flag(CByteArray &byDataArray,BYTE byFlag,int nFindPos,int nKindResult =0,int nRepeat =0/*多个ASDU的情况下*/);
	static int  GetASN1FlagPos(CDoMessage * pDo,CPacket &m_Pro,BYTE byFlag,int nKindResult=0,int nRepeat =0);
	static CString GetFlagValue(CByteArray &byDataArray, BYTE byFlag,int nStartPos, int &nAfterLength, int nFormate=0);

	static int GetMMSItemNameTypeA4(CByteArray &byDataArray,int nStartPos);
	static int GetMMSItemNameTypeA5(CByteArray &byDataArray,int nStartPos);

	static int CompareByteArray(CByteArray &m_Array1,BYTE[]);

	static void Get91Classification(CDoMessage * pDo);
	static void Get92Classification(CDoMessage * pDo);
	static void GetGooseClassification(CDoMessage * pDo);
	static void GetTcpClassification(CDoMessage * pDo);
	static void Get1588Classification(CDoMessage * pDo);
	static void GetOtherClassification(CDoMessage * pDo);
	static void GetIPandPortString(CDoMessage * pDo,  CPacket &Pro,  CString &strSrcIP,  CString &strSrcPort,  CString &strDesIP,  CString &strDesPort);
	static BOOL GetDESandSRCIP(CDoMessage * pDo,  CPacket &Pro,  CByteArray & byDESArray,  CByteArray & bySRCArray,  int & nTcpAddPos);
	static BOOL GetMMSMode(CDoMessage * pDo,  CPacket &Pro);
	static BOOL GetMMSMode(CByteArray &byDataArray);
	static unsigned int GetIntegerFromString(CString pStr);
	static int Get92PrePacketChannelData(CByteArray &byDataArray,int &nChanPos,int &nChanLength, int nOffset,int nRepeat=0);
};

//61850FrameBase.h  
#ifndef _61850FrameBase_H__
#define _61850FrameBase_H__

#include "FrameBase.h"

inline DWORD pkg_61850_read_length(PEPBUFFERPOS pBufferPos)
{
	DWORD Len = Ep_BufferReadByte(pBufferPos);

	if (0x80 & Len)
	{
		Len = 0x7F & Len;
		Len = Ep_BufferReadDWord2(pBufferPos, Len);//Bytes2UInt(pPacketStream+_pos, LL);
	}

	return Len;
}

class C61850FrameBase : public CFrameBase
{
public:
	C61850FrameBase();
	virtual ~C61850FrameBase();

public:

public:
	virtual DWORD ReadLength(PEPBUFFERPOS pBufferPos)
	{
		return pkg_61850_read_length(pBufferPos);
	}
	virtual DWORD ReadLength(const CString &strID, PEPBUFFERPOS pBufferPos, CByteBlocks *pDetailList)
	{
		DWORD Len = Ep_BufferReadByte(pBufferPos);

		if (0x80 & Len)
		{
			pDetailList->AddNewByteBlocks(strID);
			pDetailList->AddByteBlockByValueEx(strID+_T("_Flag"), (BYTE)Len, Ep_GetValuePos(pBufferPos));
			long n = 0x7F & Len;
			Len = Ep_BufferReadDWord2(pBufferPos, n);//Bytes2UInt(pPacketStream+_pos, LL);
			pDetailList->AddByteBlockByValueEx(strID, (BYTE)Len, n, Ep_GetValuePos(pBufferPos));
		}
		else
		{
			pDetailList->AddByteBlockByValue(strID, (BYTE)Len, Ep_GetValuePos(pBufferPos));
		}
		return Len;
	}

	virtual void ReadTagLength(BYTE &byteTag, long &nLen, PEPBUFFERPOS pBufferPos)
	{
		byteTag = Ep_BufferReadByte(pBufferPos);
		BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		if (0x80 & byteLen)
		{
			byteLen = 0x7F & byteLen;
			nLen = Ep_BufferReadDWord2(pBufferPos, byteLen);
		}
		else
		{
			nLen = byteLen;
		}
	}

	virtual void ReadTagLength(const CString &strID, BYTE &byteTag, long &nLen, PEPBUFFERPOS pBufferPos, CByteBlocks *pDetailList)
	{
		pDetailList->AddNewByteBlocks(strID);

		byteTag = Ep_BufferReadByte(pBufferPos);
		pDetailList->AddByteBlockByValueEx(strID+_T("_Tag"), byteTag, Ep_GetValuePos(pBufferPos));

		BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		if (0x80 & byteLen)
		{
			pDetailList->AddByteBlockByValueEx(strID+_T("_Len_Flag"), byteLen, Ep_GetValuePos(pBufferPos));
			byteLen = 0x7F & byteLen;
			nLen = Ep_BufferReadDWord2(pBufferPos, byteLen);
//			pDetailList->AddByteBlockByValueEx(strID+_T("_Len"), nLen, 2, Ep_GetValuePos(pBufferPos));
			pDetailList->AddByteBlockByValueEx(strID+_T("_Len"), nLen, byteLen, Ep_GetValuePos(pBufferPos));
		}
		else
		{
			nLen = byteLen;
			pDetailList->AddByteBlockByValueEx(strID+_T("_Len"), nLen, 1, Ep_GetValuePos(pBufferPos));
		}
	}

	// mym add 2020-7-13 
	virtual void ReadTagLen(BYTE &byteTag, long &nLen,/* long &nValue,*/ PEPBUFFERPOS pBufferPos)
	{
		byteTag = Ep_BufferReadByte(pBufferPos);
		BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		if (0x80 & byteLen)
		{
			byteLen = 0x7F & byteLen;
			nLen = Ep_BufferReadDWord2(pBufferPos, byteLen);
		}
		else
		{
			nLen = byteLen;
		}

		//nValue = Ep_BufferReadDWord2(pBufferPos, nLen);
	}

	// mym add 2020-7-13 
	virtual void ReadTagValue( long &nLen, long &nValue, PEPBUFFERPOS pBufferPos)
	{
		//byteTag = Ep_BufferReadByte(pBufferPos);
		//BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		//if (0x80 & byteLen)
		//{
		//byteLen = 0x7F & byteLen;
		//nLen = Ep_BufferReadDWord2(pBufferPos, byteLen);
		//}
		//else
		//{
		//	nLen = byteLen;
		//}
		//长度在外面已经确定好再传递进来的；
        /*
		int nValueLength = nLen;
		if(nLen>=0x80)	
			nValueLength = nLen - 0x80;		
		else 
			nValueLength = nLen ;
        */

		// mym 2020-7-15 modify 为了这里获取区间内的几个数，暂时规避之，采用的招数；
		nValue = Ep_BufferReadDWord2( pBufferPos, nLen);
	}

	virtual void ReadTagLenValue(BYTE &byteTag, long &nLen, long &nValue, PEPBUFFERPOS pBufferPos)
	{
		byteTag = Ep_BufferReadByte(pBufferPos);
		BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		if (0x80 & byteLen)
		{
			byteLen = 0x7F & byteLen;
			nLen = Ep_BufferReadDWord2(pBufferPos, byteLen);
		}
		else
		{
			nLen = byteLen;
		}

		nValue = Ep_BufferReadDWord2(pBufferPos, nLen);
	}

	// mym 2020-7-23 add 
	virtual void ReadTagLen(CString &strID, BYTE &byteTag, long &nLen,/* long &nValue, */PEPBUFFERPOS pBufferPos, CByteBlocks *pDetailList)
	{
		byteTag = Ep_BufferReadByte(pBufferPos);
		if (byteTag==0x81)
			strID = _T("Security");
		else if (byteTag==0x80)
			strID = _T("ASDU-NO");
		else if (byteTag==0xA2)
			strID = _T("Sequence of ASDU");
		else 
			return;

		pDetailList->AddNewByteBlocks(strID);
		pDetailList->AddByteBlockByValueEx(strID  +  _T("_Tag"),   byteTag,  Ep_GetValuePos(pBufferPos));
		BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		if (0x80 & byteLen)
		{
			pDetailList->AddByteBlockByValueEx(strID  +  _T("_Len_Flag"),  byteLen,   Ep_GetValuePos(pBufferPos));
			byteLen = 0x7F & byteLen;
			nLen = Ep_BufferReadDWord2(pBufferPos,   byteLen);
		}
		else
		{
			nLen = byteLen;
		}
		pDetailList->AddByteBlockByValueEx(strID  +  _T("_Len"),   nLen,   1,   Ep_GetValuePos(pBufferPos));

		//nValue = Ep_BufferReadDWord2(pBufferPos, nLen);
		//pDetailList->AddByteBlockByValueEx(strID+_T("_Value"), nValue, byteLen, Ep_GetValuePos(pBufferPos));
	}

	// mym 2020-7-23 add 
	virtual void ReadTagLenEx(CString &strID, BYTE &byteTag, long &nLen, PEPBUFFERPOS pBufferPos, CByteBlocks *pDetailList)
	{
		byteTag = Ep_BufferReadByte(pBufferPos);
		if (byteTag==0x81)
			strID = _T("Security");
		else if (byteTag==0x82)
			strID = _T("smpCnt");
		else if (byteTag==0x83)
			strID = _T("confRev");
		else if (byteTag==0x84)
			strID = _T("refreshTime");
		else if (byteTag==0x85)
			strID = _T("smpSynch");
		else if (byteTag==0x86)
			strID = _T("smpRate");
		else if (byteTag==0x87)
			strID = _T("通道数");
		else 
			return;

		pDetailList->AddNewByteBlocks(strID);
		pDetailList->AddByteBlockByValueEx(strID  +  _T("_Tag"),   byteTag,  Ep_GetValuePos(pBufferPos));
		BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		if (0x80 & byteLen)
		{
			pDetailList->AddByteBlockByValueEx(strID  +  _T("_Len_Flag"),  byteLen,   Ep_GetValuePos(pBufferPos));
			byteLen = 0x7F & byteLen;
			nLen = Ep_BufferReadDWord2(pBufferPos,   byteLen);
		}
		else
		{
			nLen = byteLen;
		}
		pDetailList->AddByteBlockByValueEx(strID  +  _T("_Len"),   nLen,   1,   Ep_GetValuePos(pBufferPos));

		//nValue = Ep_BufferReadDWord2(pBufferPos, nLen);
		//pDetailList->AddByteBlockByValueEx(strID+_T("_Value"), nValue, byteLen, Ep_GetValuePos(pBufferPos));
	}

	// mym 2020-7-23 add 
	virtual void ReadTagValue(const CString &strID, /*BYTE &byteTag, */long &nLen, long &nValue, PEPBUFFERPOS pBufferPos, CByteBlocks *pDetailList)
	{
		
		//pDetailList->AddNewByteBlocks(strID);

		//byteTag = Ep_BufferReadByte(pBufferPos);
		//pDetailList->AddByteBlockByValueEx(strID+_T("_Tag"), byteTag, Ep_GetValuePos(pBufferPos));

		//BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		//if (0x80 & byteLen)
		//{
		//	pDetailList->AddByteBlockByValueEx(strID+_T("_Len_Flag"), byteLen, Ep_GetValuePos(pBufferPos));
		//	byteLen = 0x7F & byteLen;
		//	nLen = Ep_BufferReadDWord2(pBufferPos, byteLen);
		//}
		//else
		//{
		//	nLen = byteLen;
		//}

		//pDetailList->AddByteBlockByValueEx(strID  +  _T("_Len"),   nLen,   1,   Ep_GetValuePos(pBufferPos));
		
		nValue = Ep_BufferReadDWord2(pBufferPos,  nLen);
		pDetailList->AddByteBlockByValueEx(strID  +  _T("_Value"),   nValue,   nLen,  Ep_GetValuePos(pBufferPos));

		//pDetailList->AddByteBlockByValueEx(strID  +  _T("_Value"),   nValue,   byteLen,  Ep_GetValuePos(pBufferPos));
	}

	virtual void ReadTagLenValue(const CString &strID,   BYTE &byteTag,   long &nLen,   long &nValue,   PEPBUFFERPOS pBufferPos,  CByteBlocks *pDetailList)
	{
		pDetailList->AddNewByteBlocks(strID);
	
		byteTag = Ep_BufferReadByte(pBufferPos);
		pDetailList->AddByteBlockByValueEx(strID  +  _T("_Tag"),  byteTag,  Ep_GetValuePos(pBufferPos));
	
		BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		if (0x80 & byteLen)
		{
			pDetailList->AddByteBlockByValueEx(strID  +  _T("_Len_Flag"),   byteLen,   Ep_GetValuePos(pBufferPos));
			byteLen    =   0x7F & byteLen;
			nLen = Ep_BufferReadDWord2(pBufferPos,  byteLen);
		}
		else
		{
			nLen  =  byteLen;
		}

		pDetailList->AddByteBlockByValueEx(strID  +  _T("_Len"),   nLen,   1,   Ep_GetValuePos(pBufferPos));
		nValue = Ep_BufferReadDWord2(pBufferPos,   nLen);
		pDetailList->AddByteBlockByValueEx(strID  +  _T("_Value"),   nValue,   byteLen,   Ep_GetValuePos(pBufferPos));
	}

	virtual void ReadTagLenValue(BYTE &byteTag, long &nLen, CString &strValue, PEPBUFFERPOS pBufferPos)
	{
		char pszString[MAX_PATH];
		byteTag = Ep_BufferReadByte(pBufferPos);
		BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		if (0x80 & byteLen)
		{
			byteLen = 0x7F & byteLen;
			nLen = Ep_BufferReadDWord2(pBufferPos, byteLen);
		}
		else
		{
			nLen = byteLen;
		}

		Ep_BufferReadString(pBufferPos, nLen, pszString);
		strValue = pszString;
	}

	//add mym 2020-7-13
	virtual void ReadTagValue(/*BYTE &byteTag, */long &nLen, CString &strValue, PEPBUFFERPOS pBufferPos)
	{
		char pszString[MAX_PATH];
		/*
		byteTag = Ep_BufferReadByte(pBufferPos);
		BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		if (0x80 & byteLen)
		{
			byteLen = 0x7F & byteLen;
			nLen = Ep_BufferReadDWord2(pBufferPos, byteLen);
		}
		else
		{
			nLen = byteLen;
		}
*/
		Ep_BufferReadString(pBufferPos, nLen, pszString);
		strValue = pszString;
	}

	virtual void ReadTagLenValue(BYTE &byteTag, long &nLen, char *strValue, PEPBUFFERPOS pBufferPos)
	{
		byteTag = Ep_BufferReadByte(pBufferPos);
		BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		if (0x80 & byteLen)
		{
			byteLen = 0x7F & byteLen;
			nLen = Ep_BufferReadDWord2(pBufferPos, byteLen);
		}
		else
		{
			nLen = byteLen;
		}

		Ep_BufferReadString(pBufferPos, nLen, strValue);
	}

	//add mym 2020-7-13
	virtual void ReadTagValue(/*BYTE &byteTag, */long &nLen, char *strValue, PEPBUFFERPOS pBufferPos)
	{
/*		byteTag = Ep_BufferReadByte(pBufferPos);
		BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		if (0x80 & byteLen)
		{
			byteLen = 0x7F & byteLen;
			nLen = Ep_BufferReadDWord2(pBufferPos, byteLen);
		}
		else
		{
			nLen = byteLen;
		}
*/
		Ep_BufferReadString(pBufferPos, nLen, strValue);
	}

	virtual void ReadTagLenValue(const CString &strID, BYTE &byteTag, long &nLen, CString &strValue, PEPBUFFERPOS pBufferPos, CByteBlocks *pDetailList)
	{
		char pszString[MAX_PATH];
		pDetailList->AddNewByteBlocks(strID);

		byteTag = Ep_BufferReadByte(pBufferPos);
		pDetailList->AddByteBlockByValueEx(strID+_T("_Tag"), byteTag, Ep_GetValuePos(pBufferPos));

		BYTE byteLen = Ep_BufferReadByte(pBufferPos);

		if (0x80 & byteLen)
		{
			pDetailList->AddByteBlockByValueEx(strID+_T("_Len_Flag"), byteLen, Ep_GetValuePos(pBufferPos));
			byteLen = 0x7F & byteLen;
			nLen = Ep_BufferReadDWord2(pBufferPos, byteLen);
		}
		else
		{
			nLen = byteLen;
		}

		pDetailList->AddByteBlockByValueEx(_T("Length"), nLen, 1, Ep_GetValuePos(pBufferPos));
		Ep_BufferReadString(pBufferPos, nLen, pszString);
		strValue = pszString;
		pDetailList->AddByteBlockByValueEx(_T("Value"), strValue, byteLen, Ep_GetValuePos(pBufferPos));
	}

	virtual void ReadTime(BYTE &byteTag, long &nLen, double &dTime, PEPBUFFERPOS pBufferPos)
	{
		byteTag = Ep_BufferReadByte(pBufferPos);
		nLen = Ep_BufferReadByte(pBufferPos);

		if (nLen == 8)
		{
            unsigned int nsec = Ep_BufferReadDWord2(pBufferPos, 4);
            unsigned int nusec = Ep_BufferReadDWord2(pBufferPos, 4);
			dTime = nsec + 1E-6*nusec;
		}
		else
		{
			DWORD dwSec = Ep_BufferReadDWord2(pBufferPos, nLen);
		}
	}

	virtual void ReadTime(const CString &strID, BYTE &byteTag, long &nLen, double &dTime, PEPBUFFERPOS pBufferPos, CByteBlocks *pDetailList)
	{
		pDetailList->AddNewByteBlocks(strID);

		byteTag = Ep_BufferReadByte(pBufferPos);
		pDetailList->AddByteBlockByValueEx(strID+_T("_Tag"), byteTag, Ep_GetValuePos(pBufferPos));

		BYTE byteLen = Ep_BufferReadByte(pBufferPos);
	
		if (byteLen == 8)
		{
            unsigned int nsec = Ep_BufferReadDWord2(pBufferPos, 4);;
            unsigned int nusec = Ep_BufferReadDWord2(pBufferPos, 4);
			dTime = nsec + 1E-6*nusec;
			pDetailList->AddByteBlockByValueEx(strID+_T("_Len"), byteLen, Ep_GetValuePos(pBufferPos));
			pDetailList->AddByteBlockByValueEx(strID+_T("_Time"), dTime, Ep_GetValuePos(pBufferPos));
		}
		else
		{
			DWORD dwSec = Ep_BufferReadDWord2(pBufferPos, byteLen);;
			pDetailList->AddByteBlockByValueEx(strID, dwSec, byteLen, Ep_GetValuePos(pBufferPos));
		}
	}

	virtual DWORD ParseInfor(PEPBUFFERPOS pBufferPos, CExBaseObject *pDevice);
};


#endif //_61850FrameBase_H__

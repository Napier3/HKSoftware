#pragma once

#include "../../../Module/BaseClass/TLinkList.h"
#include "../../../Module/BaseClass/XObjectRefBase.h"
#include "../../../Module/API/StringApi.h"
#ifdef _PSX_QT_LINUX_
#include <arpa/inet.h>
#include "../../../Module/API/GlobalApi.h"
#endif


//数据类型
#define STT_PP_DATATYPE_NONE					0x00
#define STT_PP_DATATYPE_BOOL					0x01
#define STT_PP_DATATYPE_CHAR					0x02
#define STT_PP_DATATYPE_UNSIGNEDCHAR	0x03
#define STT_PP_DATATYPE_SHORT				0x04
#define STT_PP_DATATYPE_UNSIGNEDSHORT	0x05
#define STT_PP_DATATYPE_INT					0x06
#define STT_PP_DATATYPE_UNSIGNEDINT		0x07
#define STT_PP_DATATYPE_LONG					0x08
#define STT_PP_DATATYPE_UNSIGNEDLONG	0x09
#define STT_PP_DATATYPE_FLOAT				0x0A
#define STT_PP_DATATYPE_DOUBLE				0x0B
#define STT_PP_DATATYPE_INT64					0x0C
#define STT_PP_DATATYPE_UNSIGNEDINT64	0x0D
#define STT_PP_DATATYPE_TIMEINT64			0x0E
#define STT_PP_DATATYPE_CPTIMEINT32		0x0F
#define STT_PP_DATATYPE_CPTIMEINT56		0x10
#define STT_PP_DATATYPE_STRING				0x11
#define STT_PP_DATATYPE_BUFFER				0x12
#define STT_PP_DATATYPE_IPV4					0x13
#define STT_PP_DATATYPE_IPV6					0x14
#define STT_PP_DATATYPE_STRUCT				0x70




//2020-12-24  lijunqing
typedef union _stt_pp_value_
{
	BOOL boolVal;
	char cVal;
	unsigned char bVal;  //BYTE
	short iVal;
	unsigned short uiVal;
	int intVal;
	unsigned int uintVal;
	float fltVal;
	double dblVal;
	long lVal;
	__int64 i64Val;
	__uint64 u64Val;
	unsigned long ulVal;
	double date;  //DATE=double
	char *pszString;
	unsigned char *pBuf;
} STT_PP_VALUE, *PSTT_PP_VALUE;

typedef struct _stt_pp_data_
{
	BYTE type;
	BYTE id;
	BYTE len;
	STT_PP_VALUE val;

	int nCount;
	struct _stt_pp_data_ *pPpDatas;
}STT_PP_DATA, *PSTT_PP_DATA;


//////////////////////////////////////////////////////////////////////////
////global functions
inline bool is_stt_pp_data_connection(PSTT_PP_DATA pData)
{
	return ((pData->type & 0x80) == 0x80);
}

inline bool is_stt_pp_data_connection(STT_PP_DATA &oData)
{
	return ((oData.type & 0x80) == 0x80);
}

void stt_pp_data_free(STT_PP_DATA &oData);
void stt_pp_data_free(PSTT_PP_DATA pData);
void stt_pp_data_get_ipVal(long len, STT_PP_VALUE &val, CString &strIP,CString &strMask);
void stt_pp_data_get_ipVal(STT_PP_DATA *pPpData,CString &strIP,CString &strMask);

void stt_pp_data_set_string(STT_PP_DATA *pPpData,BYTE nDataID, const CString &strData);
BOOL stt_pp_data_get_string(STT_PP_DATA *pPpData, CString &strData);

//////////////////////////////////////////////////////////////////////////
//数据打包、解包函数，为了提高效率，打包解包函数为inline函数
inline void stt_pp_pkt_pack_head(BYTE* &pPkg, BYTE nDataType, BYTE nID, BYTE nLen)
{
	*pPkg = nDataType;
	pPkg++;
	*pPkg = nID;
	pPkg++;
	*pPkg = nLen;
	pPkg++;
}

inline void stt_pp_pkt_pack_ipVal(BYTE* &pPkg, BYTE *pIPBuf,BYTE *pMaskBuf, BYTE nDataID, BOOL bIPV4=TRUE)
{
	if (bIPV4)
	{
		stt_pp_pkt_pack_head(pPkg, STT_PP_DATATYPE_IPV4, nDataID, 8);
		memcpy(pPkg,pIPBuf,4);
		pPkg += 4;
		memcpy(pPkg, pMaskBuf,4);
		pPkg += 4;
	}
	else
	{
		stt_pp_pkt_pack_head(pPkg, STT_PP_DATATYPE_IPV6, nDataID, 12);
		memcpy(pPkg,pIPBuf,6);
		pPkg += 6;
		memcpy(pPkg, pMaskBuf,6);
		pPkg += 6;
	}
}

inline void stt_pp_pkt_pack_ipV4Val(BYTE* &pPkg, BYTE nDataID, const CString &strIP,const CString &strMask)
{
	BYTE arrIPBuf[4] = {0};
	BYTE arrMaskBuf[4] = {0};

	DWORD dwIP;
	dwIP = inet_addr(strIP.GetString());
	memcpy(arrIPBuf,&dwIP,4);

	dwIP = inet_addr(strMask.GetString());
	memcpy(arrMaskBuf,&dwIP,4);

	stt_pp_pkt_pack_ipVal(pPkg, arrIPBuf, arrMaskBuf, nDataID, TRUE);
}

inline void stt_pp_pkt_pack_stringVal(BYTE* &pPkg,BYTE nDataID,const CString &strData)
{
	long nLen = String_Char_Count(strData);

	stt_pp_pkt_pack_head(pPkg, STT_PP_DATATYPE_STRING, nDataID, (BYTE)nLen);
	CString_to_char(strData, (char*)pPkg);
	pPkg += nLen; //不带结束表示符号“\0”
}

//地位在前，高位在后，例如：10000=0X2710  实际表示为（4字节）：10 27 00 00
inline  __uint64 stt_pp_pkt_parse_uint64(BYTE *pPkg, long nLen)
{
	if (nLen > 8 || nLen < 0)
	{
		nLen = 8;
	}

	BYTE *pCurr =pPkg + nLen - 1;
	BYTE *pEnd = pPkg;
	__uint64 val = 0;

	while (pCurr >= pEnd)
	{
		val = val << 8;
		val += *pCurr;
		pCurr--;
	}

	return val;
}
inline DWORD stt_pp_pkt_parse_long(BYTE *pPkg, long nLen)
{
	if (nLen > 4 || nLen < 0)
	{
		nLen = 4;
	}

	BYTE *pCurr =pPkg + nLen - 1;
	BYTE *pEnd = pPkg;
	DWORD val = 0;

	while (pCurr >= pEnd)
	{
		val = val << 8;
		val += *pCurr;
		pCurr--;
	}

	return val;
}
inline unsigned short stt_pp_pkt_parse_short(BYTE *pPkg, long nLen)
{
	if (nLen > 2 || nLen < 0)
	{
		nLen = 2;
	}

	BYTE *pCurr =pPkg + nLen - 1;
	BYTE *pEnd = pPkg;
	unsigned short val = 0;

	while (pCurr >= pEnd)
	{
		val = val << 8;
		val += *pCurr;
		pCurr--;
	}

	return val;
}

inline void stt_pp_pkt_pack_uint64(BYTE* &pPkg,  __uint64 val, long nLen)
{
	if (nLen > 8 || nLen < 0)
	{
		nLen = 8;
	}

	BYTE *pCurr =pPkg;
	BYTE *pEnd = pPkg + nLen - 1;

	while (pCurr <= pEnd)
	{
		*pCurr = (BYTE)(val & 0xFF);
		val = val >> 8;
		pCurr++;
	}
	pPkg += nLen;
}
inline void stt_pp_pkt_pack_long(BYTE* &pPkg, DWORD val, long nLen)
{
	if (nLen > 4 || nLen < 0)
	{
		nLen = 4;
	}

	BYTE *pCurr =pPkg;
	BYTE *pEnd = pPkg + nLen - 1;

	while (pCurr <= pEnd)
	{
		*pCurr = (BYTE)(val & 0xFF);
		val = val >> 8;
		pCurr++;
	}
	pPkg += nLen;
}
inline void stt_pp_pkt_pack_short(BYTE* &pPkg, unsigned short val, long nLen)
{
	if (nLen > 2 || nLen < 0)
	{
		nLen = 2;
	}

	BYTE *pCurr =pPkg;
	BYTE *pEnd = pPkg + nLen - 1;

	while (pCurr <= pEnd)
	{
		*pCurr = (BYTE)(val & 0xFF);
		val = val >> 8;
		pCurr++;
	}
	pPkg += nLen;
}


inline void stt_pp_pkt_pack_longVal(BYTE* &pPkg,BYTE nDataID, unsigned long nValue)
{
//	BYTE *pHead = pPkg ;
//	BYTE *p = pHead;
	stt_pp_pkt_pack_head(pPkg, STT_PP_DATATYPE_LONG, nDataID, 4);
	stt_pp_pkt_pack_long(pPkg, nValue, 4);
}


//从报文获取数据结构体
inline void stt_pp_pkt_parse_value(BYTE *pPkg, BYTE type, BYTE len, STT_PP_VALUE &val)
{
	switch (type)
	{
	case STT_PP_DATATYPE_CHAR:
		val.cVal = *pPkg;
		break;

	case STT_PP_DATATYPE_UNSIGNEDCHAR:
		val.bVal = *pPkg;
		break;

	case STT_PP_DATATYPE_SHORT:
		val.iVal = stt_pp_pkt_parse_short(pPkg, len);
		break;

	case STT_PP_DATATYPE_UNSIGNEDSHORT:
		val.uiVal = stt_pp_pkt_parse_short(pPkg, len);
		break;

	case STT_PP_DATATYPE_INT:
		val.intVal = stt_pp_pkt_parse_long(pPkg, len);
		break;

	case STT_PP_DATATYPE_UNSIGNEDINT:
		val.uintVal = stt_pp_pkt_parse_long(pPkg, len);
		break;

	case STT_PP_DATATYPE_LONG:
		val.lVal = stt_pp_pkt_parse_long(pPkg, len);
		break;

	case STT_PP_DATATYPE_UNSIGNEDLONG:
		val.ulVal = stt_pp_pkt_parse_long(pPkg, len);
		break;

	case STT_PP_DATATYPE_FLOAT:
		val.fltVal = *((float*)pPkg);
		break;

	case STT_PP_DATATYPE_DOUBLE:
		val.dblVal = *((double*)pPkg);
		break;

	case STT_PP_DATATYPE_INT64:
		val.i64Val = stt_pp_pkt_parse_uint64(pPkg, len);
		break;

	case STT_PP_DATATYPE_UNSIGNEDINT64:
		val.u64Val = stt_pp_pkt_parse_uint64(pPkg, len);
		break;

	case STT_PP_DATATYPE_TIMEINT64:
		val.date = *((double*)pPkg);
		break;

	case STT_PP_DATATYPE_CPTIMEINT32:
	case STT_PP_DATATYPE_CPTIMEINT56:
		break;

	case STT_PP_DATATYPE_STRING:
		val.pszString = new char[len+1];
		memcpy(val.pszString, pPkg, len);
		val.pszString[len] = 0;
		break;

	case STT_PP_DATATYPE_BUFFER:
	case STT_PP_DATATYPE_IPV4:
	case STT_PP_DATATYPE_IPV6:
		val.pBuf = new BYTE[len];
		memcpy(val.pBuf, pPkg, len);
		break;

		val.pBuf = new BYTE[len];
		memcpy(val.pBuf, pPkg, len);
		break;

	default:
		break;

	}
}

inline long stt_pp_pkt_parse_pp_data(BYTE* &pPkg, STT_PP_DATA *pPpData)
{
	BYTE *pHead = pPkg;
	pPpData->type = *pPkg;
	pPkg++;
	pPpData->id = *pPkg;
	pPkg++;
	pPpData->len = *pPkg;
	pPkg++;

	//集合对象数据
	if (is_stt_pp_data_connection(pPpData))
	{
		pPpData->nCount = stt_pp_pkt_parse_long(pPkg, pPpData->len);
		pPkg += pPpData->len;

		pPpData->pPpDatas = new STT_PP_DATA[pPpData->nCount];

		for (int i=0; i<pPpData->nCount; i++)
		{
			stt_pp_pkt_parse_pp_data(pPkg, &pPpData->pPpDatas[i]);
		}
	}
	else
	{
		pPpData->nCount = 0;
		pPpData->pPpDatas = NULL;
		stt_pp_pkt_parse_value(pPkg, pPpData->type, pPpData->len, pPpData->val);
		pPkg += pPpData->len;
	}

	return pPkg - pHead;
}


//数据结构体到报文中
inline void stt_pp_pkt_pack_value(BYTE* &pPkg, BYTE type, BYTE len, STT_PP_VALUE &val)
{
	switch (type)
	{
	case STT_PP_DATATYPE_CHAR:
		*pPkg = (BYTE)val.cVal;
		break;

	case STT_PP_DATATYPE_UNSIGNEDCHAR:
		*pPkg = val.bVal;
		break;

	case STT_PP_DATATYPE_SHORT:
		stt_pp_pkt_pack_short(pPkg, (unsigned short)val.iVal, len);
		break;

	case STT_PP_DATATYPE_UNSIGNEDSHORT:
		stt_pp_pkt_pack_short(pPkg, val.uiVal, len);
		break;

	case STT_PP_DATATYPE_INT:
		stt_pp_pkt_pack_long(pPkg, (unsigned long)val.intVal, len);
		break;

	case STT_PP_DATATYPE_UNSIGNEDINT:
		stt_pp_pkt_pack_long(pPkg, val.uintVal, len);
		break;

	case STT_PP_DATATYPE_LONG:
		stt_pp_pkt_pack_long(pPkg, (unsigned long)val.lVal, len);
		break;

	case STT_PP_DATATYPE_UNSIGNEDLONG:
		stt_pp_pkt_pack_long(pPkg, val.ulVal, len);
		break;

	case STT_PP_DATATYPE_FLOAT:
		*((float*)pPkg) = val.fltVal;
		break;

	case STT_PP_DATATYPE_DOUBLE:
		 *((double*)pPkg) = val.dblVal;
		break;

	case STT_PP_DATATYPE_INT64:
		stt_pp_pkt_pack_uint64(pPkg, (__uint64)val.i64Val, len);
		break;

	case STT_PP_DATATYPE_UNSIGNEDINT64:
		stt_pp_pkt_pack_uint64(pPkg, val.u64Val, len);
		break;

	case STT_PP_DATATYPE_TIMEINT64:
		*((double*)pPkg) = val.date;
		break;

	case STT_PP_DATATYPE_CPTIMEINT32:
	case STT_PP_DATATYPE_CPTIMEINT56:
		break;

	case STT_PP_DATATYPE_STRING:
		memcpy(pPkg, val.pszString, len);
		break;

	case STT_PP_DATATYPE_BUFFER:
	case STT_PP_DATATYPE_IPV4:
	case STT_PP_DATATYPE_IPV6:
		memcpy(pPkg, val.pBuf, len);
		break;

	default:
		break;

	}
}

inline long stt_pp_pkt_pack_data(BYTE* &pPkg, STT_PP_DATA *pPpData)
{
	BYTE *pHead = pPkg;
	*pPkg = pPpData->type;
	pPkg++;
	*pPkg = pPpData->id;
	pPkg++;
	*pPkg = pPpData->len;
	pPkg++;

	//集合对象数据
	if (is_stt_pp_data_connection(pPpData))
	{
		stt_pp_pkt_pack_long(pPkg, pPpData->nCount, pPpData->len);
		pPkg += pPpData->len;

		for (int i=0; i<pPpData->nCount; i++)
		{
			stt_pp_pkt_pack_data(pPkg, &pPpData->pPpDatas[i]);
		}
	}
	else
	{
		stt_pp_pkt_pack_value(pPkg, pPpData->type, pPpData->len, pPpData->val);
	}

	return pPkg - pHead;
}

class CSttPpDatas : public CTLinkList<STT_PP_DATA>, public CXObjectRefBase
{
public:
	CSttPpDatas();
	virtual ~CSttPpDatas();

public:
	//结构体STT_PP_DATA没有实现析构函数，要是用stt_pp_data_free来释放
	//CTLinkList::DeleteAll只释放对象本身，没有释放对象的子数据，所以实现DeleteAllDatas
	void DeleteAllDatas();
	PSTT_PP_DATA AddData(BYTE nDataID, const CString &strData);

	BOOL FindDataByID(BYTE id, CString &strValue);
	BOOL FindDataByID(BYTE id, long &nValue);
	BOOL FindDataByID(BYTE id, CString &strIP, CString &strMask);
};


inline void stt_pp_pkt_parse_pp_datas(BYTE* &pPkg, long nPkgLen, CSttPpDatas *pDestDatas)
{
	BYTE *p = pPkg;
	BYTE *pEnd = pPkg + nPkgLen;
	PSTT_PP_DATA pNew = NULL;

	while (p < pEnd)
	{
		pNew = new STT_PP_DATA();
		stt_pp_pkt_parse_pp_data(p, pNew);
		pDestDatas->AddTail(pNew);
	}
}


class CSttPpDatasDriver : public CXObjectRefDriver
{
public:
	CSttPpDatasDriver();
	CSttPpDatasDriver(CXObjectRefBase* lpXObject, BOOL bAutoRelease = TRUE);
	CSttPpDatasDriver(const CSttPpDatasDriver& oXobjRefSrc);

public:
	CSttPpDatas* CreateDatas();
	CSttPpDatas* GetDatas();

public:
	virtual ~CSttPpDatasDriver();
};

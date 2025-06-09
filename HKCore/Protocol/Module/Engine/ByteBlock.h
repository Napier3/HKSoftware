#pragma once

#include "PpGlobalDefine.h"
#include "BbDataRanges.h"
#include "ppscript.h"
#include "BbVariables.h"
#include "ProtocolXmlRWKeys.h"
#include "BbDataRange.h"

#include "../../../Module/MemBuffer/FormatTextBuffer.h"

BOOL Pp_IsDataTypeCheck(const CString &strDataType);

class CByteBlock :	public CExBaseList
{
public:
	CByteBlock(void);
	virtual ~CByteBlock(void);

public:
	long m_nIsKey;
	long m_nEnable;
	CString m_strLength;
	CString m_strDataType;			//数据类型
	long m_nPackOrder;       //制造的顺序

	BYTE *m_pBuffer;				//关联的数据
	CBbDataRanges*m_pRanges;	//数据的值域
	CPpScript *m_pMatchScript;			//匹配脚本
	CPpScript *m_pScript;			//脚本
	CBbVariables *m_pVariables;	//变量

	CByteBlock *m_pSrcByteBlock;
	long m_nBufferPos;

protected:
	long m_nLength;  //数据长度，缓冲区长度。
	long m_nDataLength;  //数据长度，针对“格式化数据txt”
	CFormatTextBuffer *m_pFormatTextBuffer;

	long m_nBufferLength;
public:
	virtual UINT GetClassID() {        return PPCLASSID_BYTEBLOCK;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlockKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual void InitAfterRead();

public:
	//字节块的解析		具体的解析在派生类中执行解析
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);

	//字节块的匹配		主要用于解析
	virtual DWORD Match(PACKAGEBUFFERPOS &oPkgBufPos);

	//字节块的制造
	virtual DWORD Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)	;

	// 获取该ByteBlock关联的数据
	DWORD GetByteBlockData(PACKAGEBUFFERPOS &oPkgBufPos, BYTE *byData, long nDataLength=-1);
	DWORD OffsetByteBlockData(PACKAGEBUFFERPOS &oPkgBufPos, BYTE *byData, long nDataLength=-1);
	unsigned long GetBufferSum();
	long GetByteBlockLength();
	long GetByteBlockLength2();//	{		return m_nLength;	};
	DWORD ProduceLastOrder();
	DWORD AddBufferData(long &nIndex, BYTE *pByte);
	void SetDataRanges(long nCount);
	CBbDataRanges* GetBbDataRanges();

	DWORD RunScript();

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
public:
	virtual void GetAllVariables(CExBaseList &oDestList);

	BOOL IsDataTypeConst();
	BOOL IsDataTypeCheck();
	BOOL IsDataTypeEncode();
	BOOL IsDataTypeText();

//////////////////////////////////////////////////////////////////////////
//缓冲区相关的管理
public:
	void AllocBuffer(long nLen);
	void AttachBuffer(BYTE *pBuffer);
	void SetBuffer(BYTE *pBuffer);
	BYTE* DetachBuffer();
	long SetBufferData(const CString &strData);
	void InitByHexString(const CString &strData);
	void InitByTextString(const CString &strData);

	void GetBufferPos(long &nBegin, long &nEnd);
	CFormatTextBuffer* GetFormatTextBuffer();
	void InitFormatTextBuffer();

protected:
	BOOL m_bAttchBuffer;
	void FreeBuffer();

	DWORD m_dwDataType;
	DWORD MatchConst();
	DWORD MatchConstLong(CBbDataRange *pRange);
	DWORD MatchConstHex(CBbDataRange *pRange);
	DWORD MatchConstText(CBbDataRange *pRange);
	DWORD MacthVariable();

	DWORD ParseNormal(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);
	DWORD ParseFormat(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);

};

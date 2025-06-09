// RtMemBufferMngr.h: interface for the CRtMemBufferMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTMEMBUFFERMNGR_H__D6FBC22B_B480_432F_9FF5_E2D0293C12F6__INCLUDED_)
#define AFX_RTMEMBUFFERMNGR_H__D6FBC22B_B480_432F_9FF5_E2D0293C12F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\Module\BASECLASS\ExBaseMngr.h"
#include "RtMemBufferChannel.h"
#include "..\MR1200GlobalDefine.h"

#include "MemBufferDef.h"
#include "MemBuffer.h"

class CRtMemBufferMngr : public CExBaseList
{
private:
	CRtMemBufferMngr();
	virtual ~CRtMemBufferMngr();

	virtual UINT GetClassID()    {    return MEMCLASSID_MNGR;     }

public:
	static CRtMemBufferMngr *g_pRtMemBufferMngr;
	static CRtMemBufferMngr* CreateRtMemBufferMngr();
	static long     g_nRtMemBufferRefCount;
	long  Release();	
	static CExBaseObject* FindBufferByBufferID(LPCTSTR pszBufferID);
	void Free();
	static long GetRecordDataLength()//得到录波缓存数据长度
	{
		return g_pRtMemBufferMngr->_GetRecordDataLength();
	}
	
public:
	//关键字属性
	static const char* g_pszKeyRtBuffer;
	static const char* g_pszKeyMaxBuffer;
	static const char* g_pszKeyFileFormat;
	static const char* g_pszKeyTimeGap;

	//自身属性	
	BOOL m_bHasGPS;
//	BOOL m_bRecordFomat ;
//	BOOL m_bTestFomat ;
	long m_nChannels;//通道的总的数量,包括模拟的(单通道和复合通道),开关的
	long m_nComplexChannels;
	long m_nMaxSpyBuffer;//以BYTE为单位
	long m_nMaxRecordBuffer;
	long m_nMaxAttrBuffer;
	long m_nMaxHdBuffer;
	long m_nCurrHdBufferCopyPos;

	__int64 m_n64RecordHeadIndex;//录波缓存头的绝对位置
	__int64 m_n64SpyHeadIndex;//监视缓存头的绝对位置
	__int64 m_n64CurrCalIndex;//参数计算时第一个数据的绝对位置
	
	CMemBuffer_UnsignedShort   *m_pHdMemBuffer;
	CRtMemBufferChannel *m_ppRtMemBufferMngr[MAX_MR1200_CHANNELS];//通道缓存管理对象数组
	CMemBuffer_Float    *m_ppVariableAttrBuffer[MAX_MR1200_VARIABLE_ATTR_BUFFERS];
	CMemBuffer_UnsignedShort   *m_pAttrTimeBuffer;//m_pAttrTimeBuffer记录了每一个属性数据的点数
	
public:
	/////////////////////派生的方法
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);

	long GetSpyBuffers();//使用SpyBuffer的Buffer的个数，Complex的SpyBuffer数为2
	long GetRecordBuffers();//类似GetSpyBuffers()
	long GetAttrBuffers();//类似GetSpyBuffers()
	/////////////////////自身的方法
	//初始化相关的方法
	void InitPara();//初始化缓存索引,并创建各个通道的缓存对象
	void InitDataPos();//初始化硬件缓存索引,并初始化各个通道的缓存索引
	void Init(long nMaxSpyBuffer, long nMaxRecordBuffer, long nMaxAttrBuffer, long nMaxHdBuffer);//设置各个缓存的大小
	void SetZeroValue(double* pdValue,double* pdCoef);

	//内存拷贝的方法
	void CopySpyBufferToRecordBuffer(long nGap = 1);
	void CopyHdBufferToSpyBuffer();//调用CopyHdBufferToSpyBuffer(long nHdBufferBegin, long nHdBufferEnd);
	void CopyHdBufferToSpyBuffer(long nHdBufferBegin, long nHdBufferEnd);

	//缓存的关联与获取
	long AppendHDBufferData(unsigned short *pHDData, long nLength);
	unsigned short* GetSpyBuffer(long nChannelIndex);//根据通道索引获取通道的监视缓存
	unsigned short* GetBuffer(long nChannelIndex);//根据通道索引获取通道的录波缓存
	CMemBuffer_UnsignedShort* GetSpyMemBuffer(long nChannelIndex);//根据通道索引获取通道的监视缓存的管理对象
	CMemBuffer_UnsignedShort* GetMemBuffer(long nChannelIndex);//根据通道索引获取通道的录波缓存的管理对象
	
	//缓冲区的查找
	CExBaseObject* FindByBufferID(LPCTSTR pszBufferID);//根据缓存ID,返回通道缓存的管理对象
	unsigned short* FindUShortByBufferID(LPCTSTR pszBufferID);//根据缓存ID,返回通道缓存
	long GetMemIndexByBufferID(LPCTSTR pszBufferID);//根据缓存ID获得缓存索引
	long GetAttrMemIndexByBufferID(LPCTSTR pszBufferID);//根据缓存ID获得属性缓存索引
	long* FindLongByBufferID(LPCTSTR pszBufferID);//根据缓存ID,返回复合通道的缓存
	float* FindFloatByBufferID(LPCTSTR pszBufferID);//同上
	double* FindDoubleByBufferID(LPCTSTR pszBufferID);//同上

	CRtMemBufferChannel* FindMemBufferChannel(const CString &strChID);//根据通道的ID获得通道对象

public:
	//与试验功能关联的接口函数
	static void FreeMR1200Buffer() 
	{
		ASSERT (g_pRtMemBufferMngr != NULL);
		g_pRtMemBufferMngr->FreeBuffer();
	}
	static CRtMemBufferChannel* AddMR1200Channel(const CString &strChannelID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID)
	{
		ASSERT (g_pRtMemBufferMngr != NULL);
		return g_pRtMemBufferMngr->_AddMR1200Channel(strChannelID, bUseRecordBuf, strRecordBufID, bUseSpyBuf, strSpyBufID);
	}
	static CRtMemBufferChannel* AddMR1200BinaryChannel(UINT nID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID)
	{
		ASSERT (g_pRtMemBufferMngr != NULL);
		return g_pRtMemBufferMngr->_AddMR1200BinaryChannel(nID, bUseRecordBuf, strRecordBufID, bUseSpyBuf, strSpyBufID);
	}
	static CRtMemBufferChannel* AddMR1200ComplexChannel(const CString &strChannelID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID, CRtScriptBase *pScript)
	{
		ASSERT (g_pRtMemBufferMngr != NULL);
		return g_pRtMemBufferMngr->_AddMR1200ComplexChannel(strChannelID, bUseRecordBuf, strRecordBufID, bUseSpyBuf, strSpyBufID, pScript);
	}
	static CRtMemBufferChannel* AddMR1200GPSChannel(const CString &strChannelID, const CString &strSpyBufID)
	{
		ASSERT (g_pRtMemBufferMngr != NULL);
		return g_pRtMemBufferMngr->_AddMR1200GPSChannel(strChannelID, strSpyBufID);
	}
	static CMemBuffer_Float* AddMR1200AttrBuffer(const CString &strBufID)
	{
		ASSERT (g_pRtMemBufferMngr != NULL);
		return g_pRtMemBufferMngr->_AddMR1200AttrBuffer(strBufID);
	}
	static CMemBuffer_Float* AddMR1200ComplexAttrBuffer(const CString &strBufID, CRtScriptBase *pScript)
	{
		ASSERT (g_pRtMemBufferMngr != NULL);
		return g_pRtMemBufferMngr->_AddMR1200ComplexAttrBuffer(strBufID, pScript);
	}

private:
	void InitBuffers();//创建各个通道缓存对象
	void AllocBuffers();//分配各个缓存大小
	CRtMemBufferChannel* _AddMR1200Channel(const CString &strChannelID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID);
	CRtMemBufferChannel* _AddMR1200BinaryChannel(UINT nID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID);
	CRtMemBufferChannel* _AddMR1200ComplexChannel(const CString &strChannelID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID, CRtScriptBase *pScript);
	CRtMemBufferChannel* _AddMR1200GPSChannel(const CString &strChannelID, const CString &strSpyBufID);
	CMemBuffer_Float* _AddMR1200AttrBuffer(const CString &strBufID);
	CComplexMemBuffer_Float* _AddMR1200ComplexAttrBuffer(const CString &strBufID, CRtScriptBase *pScript);
	long GetEmptyChannelIndex();

	CExBaseObject* ValidateBufferID(const CString &strBufferID);//根据ID查找通道缓存，在测试时用
	void BuildComplexChScript();
	long _GetRecordDataLength();
	
private:
	//释放内存空间的方法
	void FreeBuffer();

	void InitComplexChScript();

#ifdef _debug_complex_channel
	CRtMemBufferChannel *m_pComplexChannel;
#endif
};

#endif // !defined(AFX_RTMEMBUFFERMNGR_H__D6FBC22B_B480_432F_9FF5_E2D0293C12F6__INCLUDED_)

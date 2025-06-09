// RtMemBuffer.h: interface for the CRtMemBufferMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTMEMBUFFERMNGR_H__D6FBC22B_B480_432F_9FF5_E2D0293C12F6__INCLUDED_)
#define AFX_RTMEMBUFFERMNGR_H__D6FBC22B_B480_432F_9FF5_E2D0293C12F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RtMemBufferChannel.h"
#include "../RecordGlobalDefine.h"

#include "MemBufferDef.h"
#include "MemBuffer.h"
#include "../../BaseClass/ExBaseList.h"

class CRtMemBufferMngr : public CExBaseList
{
public:
	CRtMemBufferMngr();
	virtual ~CRtMemBufferMngr();

	virtual UINT GetClassID()    {    return MEMCLASSID_MNGR;     }

public:
	CExBaseObject* FindBufferByBufferID(const char *pszBufferID);
	void Free();
	long GetRecordDataLength()//�õ�¼���������ݳ���
	{
		return _GetRecordDataLength();
	}
	
public:
	//�ؼ�������
	static const char* g_pszKeyRtBuffer;
	static const char* g_pszKeyMaxBuffer;
	static const char* g_pszKeyFileFormat;
	static const char* g_pszKeyTimeGap;

	//��������	
	BOOL m_bHasGPS;
//	BOOL m_bRecordFomat ;
//	BOOL m_bTestFomat ;
	long m_nChannels;//ͨ�����ܵ�����,����ģ���(��ͨ���͸���ͨ��),���ص�
	long m_nComplexChannels;
	long m_nMaxSpyBuffer;//��BYTEΪ��λ
	long m_nMaxRecordBuffer;
	long m_nMaxAttrBuffer;
	long m_nMaxHdBuffer;
	long m_nCurrHdBufferCopyPos;
	long     m_nFIFOUnitSize;
	unsigned short *m_pChannelFIFOIndex;

	__int64 m_n64RecordHeadIndex;//¼������ͷ�ľ���λ��
	__int64 m_n64SpyHeadIndex;//���ӻ���ͷ�ľ���λ��
	__int64 m_n64CurrCalIndex;//��������ʱ��һ�����ݵľ���λ��
	
	CMemBuffer_UShort   *m_pHdMemBuffer;
	CRtMemBufferChannel *m_ppRtMemBufferMngr[MAX_MR1200_CHANNELS];//ͨ����������������
	CMemBuffer_Float    *m_ppVariableAttrBuffer[MAX_MR1200_VARIABLE_ATTR_BUFFERS];
	CMemBuffer_UShort   *m_pAttrTimeBuffer;//m_pAttrTimeBuffer��¼��ÿһ���������ݵĵ���
	
public:
	/////////////////////�����ķ���
	virtual long ReadOwnXml(CXmlRWNodeBase &oNode);

	long GetSpyBuffers();//ʹ��SpyBuffer��Buffer�ĸ�����Complex��SpyBuffer��Ϊ2
	long GetRecordBuffers();//����GetSpyBuffers()
	long GetAttrBuffers();//����GetSpyBuffers()
	/////////////////////����ķ���
	//��ʼ����صķ���
	void InitPara();//��ʼ����������,����������ͨ���Ļ������
	void InitDataPos();//��ʼ��Ӳ����������,����ʼ������ͨ���Ļ�������
	void Init(long nMaxSpyBuffer, long nMaxRecordBuffer, long nMaxAttrBuffer, long nMaxHdBuffer);//���ø�������Ĵ�С
	void SetZeroValue(double* pdValue,double* pdCoef);

	//�ڴ濽���ķ���
	void CopySpyBufferToRecordBuffer(long nGap = 1);
	void CopyHdBufferToSpyBuffer();//����CopyHdBufferToSpyBuffer(long nHdBufferBegin, long nHdBufferEnd);
	void CopyHdBufferToSpyBuffer(long nHdBufferBegin, long nHdBufferEnd);

	//����Ĺ������ȡ
	long AppendHDBufferData(unsigned short *pHDData, long nLength, DWORD nSampleGap);
	unsigned short* GetSpyBuffer(long nChannelIndex);//����ͨ��������ȡͨ���ļ��ӻ���
	unsigned short* GetBuffer(long nChannelIndex);//����ͨ��������ȡͨ����¼������
	CMemBufferInterface* GetSpyMemBuffer(long nChannelIndex);//����ͨ��������ȡͨ���ļ��ӻ���Ĺ������
	CMemBufferInterface* GetMemBuffer(long nChannelIndex);//����ͨ��������ȡͨ����¼������Ĺ������
	
	//�������Ĳ���
	CExBaseObject* FindByBufferID(const CString &pszBufferID);//���ݻ���ID,����ͨ������Ĺ������
	unsigned short* FindUShortByBufferID(const CString & pszBufferID);//���ݻ���ID,����ͨ������
	long GetMemIndexByBufferID(const CString & pszBufferID);//���ݻ���ID��û�������
	long GetAttrMemIndexByBufferID(const CString & pszBufferID);//���ݻ���ID������Ի�������
	long* FindLongByBufferID(const CString & pszBufferID);//���ݻ���ID,���ظ���ͨ���Ļ���
	float* FindFloatByBufferID(const CString & pszBufferID);//ͬ��
	double* FindDoubleByBufferID(const CString & pszBufferID);//ͬ��

	CRtMemBufferChannel* FindMemBufferChannel(const CString &strChID);//����ͨ����ID���ͨ������

public:
	//�����鹦�ܹ����Ľӿں���
	void FreeMR1200Buffer() 
	{
		FreeBuffer();
	}
	CRtMemBufferChannel* AddMR1200Channel(const CString &strChannelID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID)
	{
		return _AddMR1200Channel(strChannelID, bUseRecordBuf, strRecordBufID, bUseSpyBuf, strSpyBufID);
	}
	CRtMemBufferChannel* AddMR1200BinaryChannel(UINT nID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID)
	{
		return _AddMR1200BinaryChannel(nID, bUseRecordBuf, strRecordBufID, bUseSpyBuf, strSpyBufID);
	}
	CRtMemBufferChannel* AddMR1200ComplexChannel(const CString &strChannelID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID, CRtScriptBase *pScript)
	{
		return _AddMR1200ComplexChannel(strChannelID, bUseRecordBuf, strRecordBufID, bUseSpyBuf, strSpyBufID, pScript);
	}
	CRtMemBufferChannel* AddMR1200GPSChannel(const CString &strChannelID, const CString &strSpyBufID)
	{
		return _AddMR1200GPSChannel(strChannelID, strSpyBufID);
	}
	CMemBuffer_Float* AddMR1200AttrBuffer(const CString &strBufID)
	{
		return _AddMR1200AttrBuffer(strBufID);
	}
	CMemBuffer_Float* AddMR1200ComplexAttrBuffer(const CString &strBufID, CRtScriptBase *pScript)
	{
		return _AddMR1200ComplexAttrBuffer(strBufID, pScript);
	}

private:
	void InitBuffers();//��������ͨ���������
	void AllocBuffers();//������������С
	CRtMemBufferChannel* _AddMR1200Channel(const CString &strChannelID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID);
	CRtMemBufferChannel* _AddMR1200BinaryChannel(UINT nID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID);
	CRtMemBufferChannel* _AddMR1200ComplexChannel(const CString &strChannelID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID, CRtScriptBase *pScript);
	CRtMemBufferChannel* _AddMR1200GPSChannel(const CString &strChannelID, const CString &strSpyBufID);
	CMemBuffer_Float* _AddMR1200AttrBuffer(const CString &strBufID);
	CComplexMemBuffer_Float* _AddMR1200ComplexAttrBuffer(const CString &strBufID, CRtScriptBase *pScript);
	long GetEmptyChannelIndex();

	CExBaseObject* ValidateBufferID(const CString &strBufferID);//����ID����ͨ�����棬�ڲ���ʱ��
	void BuildComplexChScript();
	long _GetRecordDataLength();
	
private:
	//�ͷ��ڴ�ռ�ķ���
	void FreeBuffer();

	void InitComplexChScript();

#ifdef _debug_complex_channel
	CRtMemBufferChannel *m_pComplexChannel;
#endif
};

#endif // !defined(AFX_RTMEMBUFFERMNGR_H__D6FBC22B_B480_432F_9FF5_E2D0293C12F6__INCLUDED_)

#pragma once
#include "PpPackage.h"

class CPpPackageDetail :	public CPpPackage
{
protected:
	CPpPackageDetail(void){};

public:
	CPpPackageDetail(CExBaseObject *pChannel);
	virtual ~CPpPackageDetail(void);

	BOOL CanDelete();

public:
	BOOL m_bDelete;
	BOOL m_bUsed;
	BOOL m_bRecord;
	DWORD m_nBeginTime;
	long m_nTimeout;
	CExBaseObject *m_pChannel;  //关联的发送或者接受的通道
	CExBaseList   m_oDvmValues;		//携带的数据记录
	PPACKAGEBUFFERPOS m_pPkgBufPos;

	void SetBeginTime(){m_nBeginTime = GetTickCount();}
	BOOL IsTimeout(){return (long(GetTickCount()-m_nBeginTime)>m_nTimeout);}
	void GetPpDataBufferPos(CExBaseObject *pPpData, long &nBeginPos, long &nEndPos);
	void GetAllByteBlocks(CExBaseList *pDestList);
	long GetTotalLen();
	long GetPkgCurrBufVal(long nOffset);

public:
	void GetVariablesString(CString &strVariables);
	void AddDvmValue(const CString &strName, const CString &strID, const CString &strValue);

private:
	void GetByteBlockBufferPos(CByteBlock *pByteBlock, long &nBeginPos, long &nEndPos);
	void GetByteBlockBufferPos(CByteBlock *pFirst, CByteBlock *pLast, long &nBeginPos, long &nEndPos);
	BOOL GetByteBlockBufferPos(CExBaseList *pList, CByteBlock *pByteBlock, long &nBeginPos, long &nEndPos);

	void GetAllByteBlocks(CExBaseList *pSrcList, CExBaseList *pDestList);
};

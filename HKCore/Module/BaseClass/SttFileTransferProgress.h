#pragma once


class CSttSocketFileTransferProgress
{
public:
	CSttSocketFileTransferProgress()	{	m_nSTT_PKG_SEND_FILEDATA_MAXLEN = 2048;	}
	virtual ~CSttSocketFileTransferProgress()	{}

public:
	long CalStep(long nSize)
	{
		long nStep = nSize / m_nSTT_PKG_SEND_FILEDATA_MAXLEN;

		if (nSize > nStep * m_nSTT_PKG_SEND_FILEDATA_MAXLEN)
		{
			nStep++;
		}

		return nStep;
	}

	long m_nSTT_PKG_SEND_FILEDATA_MAXLEN;


public:
	virtual void TransferStart(const CString &strFile, long nTotalSize){};
	virtual void TransferStep(long nCurrSendSize) = 0;
	virtual void TransferFinish(const CString &strFile) = 0;
	virtual void TransferError(const CString &strFile,long nErrNo) = 0;
	virtual void Init(CStringArray &strArray){};
};
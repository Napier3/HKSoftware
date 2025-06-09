#pragma once

#include "ProtoPkgProcessInterface.h"


class CProtoPkgProcess_DNP : public CProtoPkgProcessInterface
{
public:
	CProtoPkgProcess_DNP(){};
	virtual ~CProtoPkgProcess_DNP(){};
	
	virtual bool PrcssAfterRcv(unsigned char *pBuffer, long &nBufLen);
	virtual bool PrcssAfterProduce(unsigned char *pBuffer, long &nBufLen);

protected:
	bool IsWholePkg(unsigned char *pBuffer, long &nBufLen);
	bool GetPkgLen(unsigned char *pBuffer, long &nBufLen, long &nPkgLen);
};

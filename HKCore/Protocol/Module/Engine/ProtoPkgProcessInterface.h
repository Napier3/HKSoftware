#pragma once


class CProtoPkgProcessInterface
{
public:
	CProtoPkgProcessInterface(){};
	virtual ~CProtoPkgProcessInterface(){};
	
	virtual bool PrcssAfterRcv(unsigned char *pBuffer, long &nBufLen) = 0;
	virtual bool PrcssAfterProduce(unsigned char *pBuffer, long &nBufLen) = 0;
};


CProtoPkgProcessInterface* pp_CreateProtoPkgProcess(char *pszProtoPkgPrcssID);

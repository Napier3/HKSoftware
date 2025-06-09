#pragma once

#include "../../../Module/DataMngr/DvmDataset.h"
#include "../../../Module/DataMngr/DataGroup.h"

class CPxProtocolImpInterface
{
public:
	CPxProtocolImpInterface(){}
	virtual ~CPxProtocolImpInterface(){}

public:
	//协议被调用执行接口
	virtual long RunProcedure(const CString &strProcedureID,CExBaseList *pListDatas
		,CDvmDataset *pDataset,const CString &strRecordMode) = 0;
	virtual long PkgPrase(char *pBuf,long nLen,CDvmDataset &oRetDataset) = 0;
	virtual long PkgProduce(const CString &strProduceID,CDvmDataset &oDataset,char **ppBuf,long &nLen) = 0;
	virtual long GetDataset(const CString &strDatasetPath,CDvmDataset &oRetDataset) = 0;
	virtual long ConfigDevice(const CString &strConfig) = 0;
	virtual long CloseDevice() = 0;
	virtual void InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
		,const CString &strCmmCfgFile,CDataGroup *pCfgGroup) = 0;

	virtual BOOL Init(const char *pszIP,long nPort){return FALSE;}
};

inline CString GetIDFromPath(const CString &strPath,char chSeperator='$')
{
	CString strID;
	long nPos = strPath.ReverseFind(chSeperator);

	if (nPos >= 0)
	{
		strID = strPath.Mid(nPos + 1);
	}
	else
	{
		strID = strPath;
	}

	return strID;
}
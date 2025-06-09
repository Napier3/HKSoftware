//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RemoteDev.h  CRemoteDev

#pragma once

#include "61850ClientCfgMngrGlobal.h"

#ifdef USE_61850CLient_STRCUT
#include "dlt860_client.h"
#include "glbtypes.h"
#include "sharemem.h"

#endif  //USE_61850CLient_STRCUT

#define DLT860_SERVER_PORT                                 8102

typedef void (FIRE_CMD_MSG_FUNC) (DWORD dwFuncParaEx, UINT nCmdIndex);


class CRemoteDev : public CExBaseObject
{
public:
	CRemoteDev();
	virtual ~CRemoteDev();


	CString  m_strIP;
	CString  m_strLocalIP;
	long  m_nUseLocalIP;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CREMOTEDEV;   }
	virtual BSTR GetXmlElementKey()  {      return C61850ClientCfgMngrXmlRWKeys::CRemoteDevKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//私有成员变量
private:

#ifdef USE_61850CLient_STRCUT
//私有成员变量访问方法
public:
	BOOL IsConnecting();

//属性变量访问方法
public://通讯命令相关
	BOOL LinkDev();//联机
	BOOL UnLinkDev();
	BOOL GetServerDirectory();
	BOOL GetLogicDeviceDirectory();
	BOOL GetAllDatasets();
	BOOL GetDataSetDirectory(LD_NODE *pLD,const long &nDatasetIndex);
	BOOL GetActiveSG(const long &nLdIndex);
	BOOL SetEditSG(const long &nLdIndex,const long &nSE);
	BOOL SetActiveSG(const long &nLdIndex,const long &nSG);
	BOOL ReadValue(const char *pLdName,tagDA *pDA);
	BOOL ReadValue(tagDAValue *pDAValue,const CString &strDataRef,const CString &strFC);
	BOOL ReadDataType(const CString &strDataRef,const CString &strFC,CString &strDataType);
	BOOL ReadSEValue(const char *pLdName,tagDA *pDA);
	BOOL WriteSEValue(const char *pLdName,tagDA *pDA);
	BOOL WriteValue(const char *pLdName,tagDA *pDA);
	BOOL CtrlWriteDA_SWV_Oper(const char *pLdName,tagDA *pDA,tagDA *pDA2,ST_INT iValue,ST_INT iValue2,ST_INT nTDelayAfterSel,FIRE_CMD_MSG_FUNC pFunc,DWORD pFuncParaEx);//带值选择执行
	BOOL CtrlWriteDA_SWV_Oper(const char *pLdName,tagDA *pDA,FIRE_CMD_MSG_FUNC pFunc,DWORD pFuncParaEx);//带值选择执行
	BOOL CtrlWriteDA_SBO_Oper(const char *pLdName,tagDA *pDA,FIRE_CMD_MSG_FUNC pFunc,DWORD pFuncParaEx);//不带值选择执行
	BOOL CtrlWriteDA_Direct(const char *pLdName,tagDA *pDA);//直控模式
	BOOL CtrlWriteDA_Direct(const CString &strRef,GspMmsValue* ctlVal);
	BOOL ConfirmEditSGValues(const char *pLdName);
	BOOL GetRCBEnableState(const char *pLdName,const char *pRcbItem,BOOL &bRptEna);
	BOOL GetURCBValues(const char *pLdName,const char *pRcbItem,BOOL &bRptEna);
	BOOL GetBRCBValues(const char *pLdName,const char *pRcbItem,BOOL &bRptEna);
	BOOL SetBRCBValues(RCB_NODE *pReportCB,const char *pLdName,const char *pRcbItem,long nOptFlds,long nTrgOps,long nEnbleGI,long nEntryID_Continue);
	BOOL SetURCBValues(RCB_NODE *pReportCB,const char *pLdName,const char *pRcbItem,long nOptFlds,long nTrgOps,long nEnbleGI);
	BOOL SetRCBValueGI(const char *pLdName,const char *pRcbItem,BOOL bGI_Value);
	BOOL StopReport(const char *pLdName,const char *pRcbItem);
	BOOL GetAllDir(const CString &strDirPath,BOOL bOnlyReadCfg);
	void GetAllSubDir(XMMS_FILE_SYS_OBJ *pTagFileDir,BOOL bOnlyReadCfg);
	BOOL GetDir(XMMS_FILE_SYS_OBJ *pFileDir,const CString &strFullPath,BOOL bOnlyReadCfg);
	BOOL ReadFile(const CString &strRemoteFilePath,const CString &strLocalRootFolderPath);
	BOOL SetFile(const CString &strLocalFile,const CString &strDevPath);
	BOOL ResetDev();
	BOOL ReadJournal(long long int nStartEntry,char *pszItemID,long nldIndex);
	BOOL GetRpcInterfaceDirectory();
	BOOL RpcCall(const CString &strParaFunction,const CString &strParaCallName,const CString &strParaCallID,
		ST_INT nVersion, ST_INT nTimeout, ST_INT nRequestType, ST_INT nResponseType);

	BOOL GetRptLogCB_GetAllCBValues(LD_NODE *pLD,long nGSP_ACSIClass);//20220519 通过获取全部控制块的方式,获取全部报告控制块,日志控制块的值
	ST_RET node_get_DataDescInfo(LD_NODE *pLD, tagDA*pDA);
	ST_RET node_get_DataLimitValInfoAll(LD_NODE *pLD,tagDA*pDA);

public://数据处理相关
	ACSI_NODE* GetAcsiNode(){return &m_oAcsiDevice;}
	LD_NODE* GetLdNode(const long &nLdIndex);
	long GetDeviceIndex();

	BOOL HasReadSettingZone();
	void InitRptLogCB_Struct(LD_NODE *pLD);

protected:
	long GetReadDatasetNum(GspLinkedList allCBDataValue);
	BOOL GetLogicDeviceDirectory(LD_NODE*pLD);
	BOOL GetAllDataDefinition_LogicNode(MMS_DATA_NODE *pLN,const CString &strDataRef,const int &nFC_Type);
	BOOL GetAllDataDefinition_DO_DA(MMS_DATA_NODE *pDO_DA,const CString &strDataRef,const int &nFC_Type);
	BOOL GetAllDataDefinition_DO_DA(DataDefinition__structure__Member *pDataDefine,MMS_DATA_NODE *pDO_DA,const CString &strDataRef,const int &nFC_Type);
	BOOL GetDataDefinition_DO_DA(tagDA* pDatasetTagDA,const char *pzfRef,const char *pzfFC);
	BOOL GetDataRef(const char *pLdName,const char *pMmsDataRef,CString &strFC,CString &strDataRef);

	ST_RET Get_LNX_Attributte(ST_CHAR *pLDName,MMS_DATA_NODE* _FCNode, enum NODE_TYPE nTypeDepp_1);
	BOOL Get_Nodes_Detail();
	ST_RET node_get_DataLimitValInfo(LD_NODE *pLD,tagDA*pDA, ST_INT nLimitKind);
	GspLinkedList ReadValue(const CString &strDataRef,const CString &strFC);

private:
	void LogPrint_GspLinkedList(GspLinkedList list);
	void Release_AcsiNode();
	//此函数检查路径中是否包含按时间段查找的前缀或按最新文件数查找的后缀，含有返回1，不包含返回0，将去除前缀、后缀后的文件路径返回给参数2
	BOOL check_prefix_and_suffix(const CString &strMsgPath,CString &strDirPath);
	BOOL ResetDev(const CString &strLDName);

	GspIedConnection m_oConnectIED;
	GspIedClientError m_oErrorInfor;
	const char* m_pAssociateID;
	ACSI_NODE m_oAcsiDevice;
    CTLinkList<struct sBRCBControlBlk> m_vBrcbContrlBlk;
    CTLinkList<struct sURCBControlBlk> m_vUrcbContrlBlk;

	BRCBControlBlk m_oCurBrcbControlBlk;
	URCBControlBlk m_oCurUrcbControlBlk;
#endif
};


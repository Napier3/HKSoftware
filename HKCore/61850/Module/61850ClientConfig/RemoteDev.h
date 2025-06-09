//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
//���غ���
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

//˽�г�Ա����
private:

#ifdef USE_61850CLient_STRCUT
//˽�г�Ա�������ʷ���
public:
	BOOL IsConnecting();

//���Ա������ʷ���
public://ͨѶ�������
	BOOL LinkDev();//����
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
	BOOL CtrlWriteDA_SWV_Oper(const char *pLdName,tagDA *pDA,tagDA *pDA2,ST_INT iValue,ST_INT iValue2,ST_INT nTDelayAfterSel,FIRE_CMD_MSG_FUNC pFunc,DWORD pFuncParaEx);//��ֵѡ��ִ��
	BOOL CtrlWriteDA_SWV_Oper(const char *pLdName,tagDA *pDA,FIRE_CMD_MSG_FUNC pFunc,DWORD pFuncParaEx);//��ֵѡ��ִ��
	BOOL CtrlWriteDA_SBO_Oper(const char *pLdName,tagDA *pDA,FIRE_CMD_MSG_FUNC pFunc,DWORD pFuncParaEx);//����ֵѡ��ִ��
	BOOL CtrlWriteDA_Direct(const char *pLdName,tagDA *pDA);//ֱ��ģʽ
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

	BOOL GetRptLogCB_GetAllCBValues(LD_NODE *pLD,long nGSP_ACSIClass);//20220519 ͨ����ȡȫ�����ƿ�ķ�ʽ,��ȡȫ��������ƿ�,��־���ƿ��ֵ
	ST_RET node_get_DataDescInfo(LD_NODE *pLD, tagDA*pDA);
	ST_RET node_get_DataLimitValInfoAll(LD_NODE *pLD,tagDA*pDA);

public://���ݴ������
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
	//�˺������·�����Ƿ������ʱ��β��ҵ�ǰ׺�������ļ������ҵĺ�׺�����з���1������������0����ȥ��ǰ׺����׺����ļ�·�����ظ�����2
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


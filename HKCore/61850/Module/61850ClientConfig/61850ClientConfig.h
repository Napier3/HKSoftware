//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//61850ClientConfig.h  C61850ClientConfig

#pragma once

#include "61850ClientCfgMngrGlobal.h"
#include "../../../Module/DataMngr/DvmLogicDevice.h"
#include "RemoteDevs.h"

class C61850ClientConfig : public CExBaseList
{
public:
	C61850ClientConfig();
	virtual ~C61850ClientConfig();


	long  m_nDebugMode;
	long  m_nUseDvmMapFile;
	long  m_nEnaWriteWaitAfterSel;
	long  m_nEnaWriteWait;
	long  m_nReadAinUseReport;
	long  m_nAddRptBuffer;
	long  m_nCanWriteActiveSG;
	long  m_nProtocolVersion;
	long  m_nUseDsDout;
	long m_nEnaReadBeforeWrite;//在修改压板前，先读取压板状态
	long m_nWriteDataWaitMs;//在修改压板前，先读取压板状态
	long  m_nAutoGenModelDatas;
	long  m_nUseGspLog;
	long  m_nSpecifiedDataset;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_C61850CLIENTCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return C61850ClientCfgMngrXmlRWKeys::C61850ClientConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CString m_strConfigPath;
	CRemoteDevs *m_pRemoteDevs;

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL OpenClientConfg(const CString &strConfigPath);
	BOOL SaveClientConfg(const CString &strConfigPath = _T(""));

	long GetRemoteDevCount();
	long GetCtrlType();
	BOOL HasCtrlTest();
	BOOL HasCtrlSynCheck();
	BOOL HasCtrlInterlockCheck();
	BOOL HasTimeActived();
	void SetCtrlTest(BOOL bValue);
	void SetCtrlSynCheck(BOOL bValue);
	void SetCtrlInterlockCheck(BOOL bValue);
	void SetTimeActived(BOOL bValue);
	void SetCtrlType(long nCtrlType);
	long GetIntgPdTime();//获取周期上送时间
	CRemoteDevs* GetRemoteDevs();
	CRemoteDev* GetRemoteDev(long nDevIndex);

#ifdef USE_61850CLient_STRCUT
	ACSI_NODE* mms_Find_ACSI_NODE_ByID(const CString &strDeviceID);
	ACSI_NODE* mms_Find_ACSI_NODE_UnConnect();

	void UpdateProtocolVersion();
#endif
};

#ifdef USE_61850CLient_STRCUT
ACSI_NODE* Client61850_GetAcsiNode(const long &nDevIndex);
#endif

extern C61850ClientConfig g_o61850ClientConfig;
extern long g_nProtocolVersion;


#pragma once

#include "PpPackages.h"
#include "DvDataTypes.h"
#include "PpProcedures.h"
#include "PpProcedureRefs.h"
#include "PpTtPackage.h"
#include "PpPackageDetail.h"
#include "DeviceModel/DeviceCmmConfig.h"
// #include "DeviceModel/DeviceModelDefine.h"
#include "DeviceModel/DevcieModel.h"
#include "ByteBlockDataTypes.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"
#include "XPkgFullRcvJdgTool.h"

//2023-1-27  lijunqing
#include "ProtoPkgProcessInterface.h"

#include <vector>

#define PPSCRIPT_TYPE_LUA  _T("LUA")
#define PPSCRIPT_TYPE_XVM _T("XVM")

#define PPSCRIPT_XVM_TASM_EXE _T("pptse")

class CPpTemplate :	public CExBaseList
{
public:
	CPpTemplate(void);
	virtual ~CPpTemplate(void);
	void Init();
	BOOL IsTemplateValid();

	CString m_strTemplateFile;
public:
	std::vector<BYTE> m_vecCRC;

private:
	CPpDvmDevice *m_pDevice;      //设备数据管理对象
	BOOL m_bUseOwnDefDevice;

	void InitPpDeviceDefine();

public:
	void SetDevice(CPpDvmDevice *pDevice);
	CExBaseList* GetDevice();
	
public:
	long m_nLength;
	CString  m_strVersion;
	CString  m_strPackageMaxLength;
	CString  m_strPackageMinLength;
	CString  m_strDeviceModel;//设备数据模型定义文件名称
	CString  m_strDeviceFileForDebug;//设备数据模型定义文件名称
	CString  m_strDefaultChannel;//默认通道
	
	
	CString  m_strPackageEncoded;//帧的编码方式
	CString  m_strPkgEncodedLen;//帧编码长度
	DWORD m_dwPkgEncodedSend;
	DWORD m_dwPkgEncodedReceive;
	CString m_strCommMode;
	long    m_nDeviceModeType;
	long    m_nEngineVersion;
	long    m_nDatasetMode;

	CString m_strOnRecvProcedure;
	CString m_strSndOptr_GlobalVar;
	CString m_strSndOptr_Optr;
	long m_nSndOptr_Value;
	//2019-05-27   添加变量
	long m_nSndOptr_Optr;
	BOOL m_bHasOnRecvProcedure;

	 //脚本的格式：LUA、XVM
	CString m_strScriptType; 

	//字符串编码
	CString m_strEncoding;   //UNICODE、UTF-8、......
	long     m_nEncoding;

	//设备模型
	//CDeviceModelTemplate *m_pDvTemplate;    //设备数据模型定义模板
	//CPpDeviceDefine *m_pDeviceModel;           //设备数据模型定义
	CDeviceCmmConfig *m_pCmmConfig;           //设备通讯配置

	//规约定义
	CPpPackages *m_pPackages;
	CPpProcedures *m_pProcedures;

	//初始化定义
	CPpProcedureRefs *m_pInitProcedure;
	CPpProcedureRefs *m_pOnlineProcedure;
	CBbVariables *m_pDataInterface;

	long  m_nPackageMaxLength;
	long  m_nPackageMinLength;
	CString m_strPkgFullRcvJdgID;

	//2023-1-27  lijunqing协议报文处理 for DNP  
	//DNP3协议的CRC比较特殊，报文头一个CRC、每16个字节一个CRC
	//因此增加此变量，用于通用化的使用，做报文解析、打包之前的处理
	CString m_strProtoPkgProcess;   
	CProtoPkgProcessInterface *m_pProtoPkgPrcss;
	
	CByteBlockDataTypes *m_pByteBlockDataTypes;

#ifdef _PP_DEV_MODE_
	CPpPackageText *m_pPpPackageText; //模板用于测试的报文
	CPpPackageTexts *m_pPpPackageTexts; //模板用于测试的报文
#endif

// 	CExBaseList m_listSystemVariableDataType;
	BOOL InitSystemVariableDataType(/*CPpDeviceModelDefine* pDeviceModelDefine*/);
	BOOL InitTtPackageSystemVariables();

#ifdef _PP_DEV_MODE_
	CPpPackageText* GetPpPackageText()
	{
		if (m_pPpPackageText == NULL)
		{
			m_pPpPackageText = (CPpPackageText*)m_pPpPackageTexts->GetHead();
			m_pPpPackageText = new CPpPackageText();
			m_pPpPackageTexts->AddNewChild(m_pPpPackageText);
		}

		return m_pPpPackageText;
	}

	CPpPackageTexts* GetPpPackageTexts()
	{
		if (m_pPpPackageTexts == NULL)
		{
			m_pPpPackageTexts = new CPpPackageTexts();
			AddNewChild(m_pPpPackageTexts);
		}

		return m_pPpPackageTexts;
	}
#endif

	BOOL IsSingleDeviceMode()	{	return m_nDeviceModeType == PPTEMPLATE_DEVICEMODE_SINGLE;	}
	BOOL IsMultiDeviceMode()	{	return m_nDeviceModeType == PPTEMPLATE_DEVICEMODE_MULTI;	}

public:
	virtual UINT GetClassID(){ return PPCLASSID_PPTEMPLATE; };
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strTemplateKey;     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual void InitAfterRead();

	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	void InitPackageAllVariables(UINT nClassID);
	
	CDeviceCmmConfig* GetDeviceCmmConfig()
	{
		if (m_pCmmConfig == NULL)
		{
			m_pCmmConfig = new CDeviceCmmConfig();
			AddNewChild(m_pCmmConfig);
			BringToHead(m_pCmmConfig);
		}

		return m_pCmmConfig;
	}

	CPpProcedureRefs* GetInitProcedure()
	{
		if (m_pInitProcedure == NULL)
		{
			m_pInitProcedure = new CPpProcedureRefs();
			AddNewChild(m_pInitProcedure);
		}

		return m_pInitProcedure;
	}

	CPpProcedureRefs* GetOnlineProcedure()
	{
		if (m_pOnlineProcedure == NULL)
		{
			m_pOnlineProcedure = new CPpProcedureRefs();
			AddNewChild(m_pOnlineProcedure);
		}

		return m_pOnlineProcedure;
	}

	DWORD GetCommMode();
	void SetCommMode(DWORD dwCommMode);

public:
	DWORD RunProcedure(const CString &strProcedureID, CBbVariables *pDataInterface, BOOL bIsInit);

	DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CPpPackageDetail* &pDetail);
	
	DWORD Produce(const CString &strPackageID, PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);
	
	//规约模板执行		执行当前的过程
	DWORD Run();

	//编码
	DWORD PkgEncoded(const CString &strEncodeMode);

protected:
	//解析帧
	typedef CTLinkListEx<CPpPackage> CPACKAGELIST;
	CPACKAGELIST m_listRPackage;	//解析的报文帧临时链表
	CPACKAGELIST m_listTPackage;			//模板帧临时链表
	CPACKAGELIST m_listWPackage;			//制造帧临时链表
	CPpProcedures m_oCurrRunProcedures;

	//当前执行的过程		解析完成一个报文帧后，由此进行匹配
	CPpTtPackage* MatchHeadAndTail(PACKAGEBUFFERPOS &oPkgBufPos);

	// 当没有模板帧的情况下，直接匹配解析帧
	CPpParsePackage* MatchPackge(PACKAGEBUFFERPOS &oPkgBufPos);

//编辑相关的接口
public:
	//帧的添加、删除
	BOOL AddPackage(CPpPackage *pPackage);
	BOOL DeletePackage(CPpPackage *pPackage);

	//过程的添加、删除
	void AddProcedure(CPpProcedure *pProcedure);
	void DeleteProcedure(CPpProcedure *pProcedure);

	//查找桢
	CPpPackage* FindPackagebyID(const CString &strPackageID);

	//设置Package变量ID；
	BOOL SetPackageVariableByID(const CString &strPackageID,const CString& strVariableID,const CString& strValue);
//文件相关的接口
public:
	BOOL IsScriptType_LUA();
	BOOL IsScriptType_XVM();
	void SetScriptType_LUA();
	void SetScriptType_XVM();

	BOOL IsEncoding_UTF8();
	BOOL IsEncoding_ASCII();
	void SetEncoding_UTF8();
	void SetEncoding_ASCII();
	void SetEncoding(long nEncoding);

	BOOL Open(const CString &strFile);
	BOOL Save(const CString &strFile);

	CString GetXvmTasmExeFile();
	BOOL OpenXmlFile(const CString &strFile);
	BOOL SaveXmlFile(const CString &strFile);

	BOOL OpenBinaryFile(const CString &strFile);
	BOOL SaveBinarylFile(const CString &strFile);

	void InitByteBlockDataTypes();
	void InitPackageAllVariables();
	void InitCommConfig(CExBaseList *pCmmList);
	void InitCommConfig()
	{
		InitCommConfig(m_pCmmConfig);
	}

	CString GetDeviceFileForDebug();
	CString GetDeviceFilePathForDebug();

public:
	void RegisterReport(const CString &strDatasetPath);
	void UnRegisterReport(const CString &strDatasetPath);
	void RegisterReport(CDvmDataset *pDataset);
	void UnRegisterReport(CDvmDataset *pDataset);
	void ResetReport();
	BOOL IsDvmDataCanAddToReport(CDvmData *pData);
	CXPkgFullRcvJdgInterface* GetXPkgFullRcvJdgInterface();
	BOOL CanRunWPackageOnReceive();

	//2023-1-27  lijunqing
	void InitProtoPkgProcess(const CString &strPkgPrcssID);

private:
	CExBaseList m_oListReportDataset;
};

extern CAutoCriticSection g_oDeviceBindListCriticSection;
static const CString g_strReportLogicDeviceID = _T("report");
static const CString g_strReportPackageID =     _T("package");
static const CString g_strReportSOEID =         _T("soe");

CString Pp_MakeFirstCharUpper(const CString& strInput);
BOOL Pp_GetSystemVariableByNodeTypes(CString& retString,const CString& strAddToHead,const CString& strAddToTail,const CString& strInputString,const CString& strMatch,BOOL bNeedMatch);
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
	CPpDvmDevice *m_pDevice;      //�豸���ݹ������
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
	CString  m_strDeviceModel;//�豸����ģ�Ͷ����ļ�����
	CString  m_strDeviceFileForDebug;//�豸����ģ�Ͷ����ļ�����
	CString  m_strDefaultChannel;//Ĭ��ͨ��
	
	
	CString  m_strPackageEncoded;//֡�ı��뷽ʽ
	CString  m_strPkgEncodedLen;//֡���볤��
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
	//2019-05-27   ��ӱ���
	long m_nSndOptr_Optr;
	BOOL m_bHasOnRecvProcedure;

	 //�ű��ĸ�ʽ��LUA��XVM
	CString m_strScriptType; 

	//�ַ�������
	CString m_strEncoding;   //UNICODE��UTF-8��......
	long     m_nEncoding;

	//�豸ģ��
	//CDeviceModelTemplate *m_pDvTemplate;    //�豸����ģ�Ͷ���ģ��
	//CPpDeviceDefine *m_pDeviceModel;           //�豸����ģ�Ͷ���
	CDeviceCmmConfig *m_pCmmConfig;           //�豸ͨѶ����

	//��Լ����
	CPpPackages *m_pPackages;
	CPpProcedures *m_pProcedures;

	//��ʼ������
	CPpProcedureRefs *m_pInitProcedure;
	CPpProcedureRefs *m_pOnlineProcedure;
	CBbVariables *m_pDataInterface;

	long  m_nPackageMaxLength;
	long  m_nPackageMinLength;
	CString m_strPkgFullRcvJdgID;

	//2023-1-27  lijunqingЭ�鱨�Ĵ��� for DNP  
	//DNP3Э���CRC�Ƚ����⣬����ͷһ��CRC��ÿ16���ֽ�һ��CRC
	//������Ӵ˱���������ͨ�û���ʹ�ã������Ľ��������֮ǰ�Ĵ���
	CString m_strProtoPkgProcess;   
	CProtoPkgProcessInterface *m_pProtoPkgPrcss;
	
	CByteBlockDataTypes *m_pByteBlockDataTypes;

#ifdef _PP_DEV_MODE_
	CPpPackageText *m_pPpPackageText; //ģ�����ڲ��Եı���
	CPpPackageTexts *m_pPpPackageTexts; //ģ�����ڲ��Եı���
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
	
	//��Լģ��ִ��		ִ�е�ǰ�Ĺ���
	DWORD Run();

	//����
	DWORD PkgEncoded(const CString &strEncodeMode);

protected:
	//����֡
	typedef CTLinkListEx<CPpPackage> CPACKAGELIST;
	CPACKAGELIST m_listRPackage;	//�����ı���֡��ʱ����
	CPACKAGELIST m_listTPackage;			//ģ��֡��ʱ����
	CPACKAGELIST m_listWPackage;			//����֡��ʱ����
	CPpProcedures m_oCurrRunProcedures;

	//��ǰִ�еĹ���		�������һ������֡���ɴ˽���ƥ��
	CPpTtPackage* MatchHeadAndTail(PACKAGEBUFFERPOS &oPkgBufPos);

	// ��û��ģ��֡������£�ֱ��ƥ�����֡
	CPpParsePackage* MatchPackge(PACKAGEBUFFERPOS &oPkgBufPos);

//�༭��صĽӿ�
public:
	//֡����ӡ�ɾ��
	BOOL AddPackage(CPpPackage *pPackage);
	BOOL DeletePackage(CPpPackage *pPackage);

	//���̵���ӡ�ɾ��
	void AddProcedure(CPpProcedure *pProcedure);
	void DeleteProcedure(CPpProcedure *pProcedure);

	//������
	CPpPackage* FindPackagebyID(const CString &strPackageID);

	//����Package����ID��
	BOOL SetPackageVariableByID(const CString &strPackageID,const CString& strVariableID,const CString& strValue);
//�ļ���صĽӿ�
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
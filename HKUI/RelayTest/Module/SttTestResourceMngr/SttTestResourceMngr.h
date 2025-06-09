#pragma once
#include "TestResource/SttTestResourceBase.h"
#include "RtDataMngr/SttGlobalRtDataMngr.h"
#include "../SttCmd/SttChMaps.h"
#include "../AdjustTool/SttAdjDevice.h"
#include "../../../Module/XfileMngrBase/XFileMngr.h"
#include "../../../Module/FilterText/FilterTextMngr.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"

//2023.6.9 zhouhj  ��ԭTest_Win.ixmlͳһ��ΪSttIecConfig.ixml
#define IECCONFIG_FILE_NAME_TESTWIN        _T("SttIecConfig.ixml")                   

class CSttModuleTag
{
public:
	CSttModuleTag(void);
	virtual ~CSttModuleTag(void){}

	long GetTotalChCount();//{return m_nChCountU + m_nChCountI;}

	long m_nModulePos;//ģ��λ��
	long m_nModuleType;//ģ������
	long m_nChCountU;//��ѹͨ����(����ģ���������������)
	long m_nChCountI;//����ͨ����(����ģ���������������)

	long m_nChCountU_Week;//��ѹͨ����(�������źŲ��)
	long m_nChCountI_Week;//����ͨ����(�������źŲ��)

	long m_nModuleIndex;//ģ����,����ģ�����ʹ�1��ʼ���
};

class CSttModuleTags :public CTLinkList<CSttModuleTag> 
{
public:
	CSttModuleTags(void){}
	virtual ~CSttModuleTags(void){}
	CSttModuleTag* AddModuleTag(long nModulePos,long nModuleType,long nChCount);
};

class CSttTestResourceMngr : public CExBaseList
{
public:
	CSttTestResourceMngr(void);
	virtual ~CSttTestResourceMngr(void);

public:
	CSttAdjDevice m_oCurrDevice;  //��ǰʹ�õ�Ӳ����Դ
	CSttTestResourceBase *m_pTestResouce;
    //CSttTestResource_Async *m_pTestResouce_Async;

	CSttChMaps m_oChMaps;

	CSttGlobalRtDataMngr m_oRtDataMngr;
	CDataGroup m_oFiberMsgGroup;	//chenlig �⹦������

#ifndef NOT_USE_TEST_RESOURCE_IECFG//����Ƿ�ʹ��IEC����
	CIecCfgDatasMngr m_oIecDatasMngr;//�����ֲ�����Ӳ��ͨ����Ϣ��ȡʱ,��Ҫ�õ�����
#endif
	void SetIecConfigFileName(const CString &strIecConfigFileName)//zhouhj 20220316 ���ӵ����ӿ������ļ���
	{
		m_strIecConfigFileName = strIecConfigFileName;
	}

	BOOL IsSyncMode();//�ж��Ƿ�Ϊͬ��ģʽ
	BOOL IsAsyncMode();//�ж��Ƿ�Ϊ�첽ģʽ
	CString GetRsDirPath_Device(); //װ����Դ��Ŀ¼
	CString GetRsDirPath_Model(CString strModel = _T("")); //װ����Դ��Ӧ�ͺŵĸ�Ŀ¼,�������Ϊ�գ���ȡ��ǰѡ����ͺ�
	CString GetDevFilePath_Model(CString strModel = _T("")); //��ǰ�ͺŵ����в�����SN�ļ���·��,�������Ϊ�գ���ȡ��ǰѡ����ͺ�
	CString GetCurSelRsDeviceFilePath();//��ȡ��ǰѡ����ͺţ���һ��ȱʡѡ��ı�Ŷ�Ӧ��Device�ļ�·��
	CString GetCurSelRsDeviceSysParasPath();//��ȡ��ǰѡ�����õ�ϵͳ���������ļ�
	CString GetCurSelDirPath_SN();//��ȡ��ǰѡ���װ�ñ�ŵ��ļ���Ŀ¼·��
	CString GetRsDeviceFilePath(const CString &strModel,const CString &strSN);//�����ͺż���ţ���ȡ��ӦDevice�ļ�·��
	long SelectChMapsFiles(CXFileMngr *pXFileMngr); //���ݵ�ǰDevice��Resource��ȡȫ��ӳ���ϵ�ļ�
	long GetAllDeviceModel(CFilterTextMngr *pModels);  //��ȡ����ȫ���ͺţ�����CFilterTextMngr �Ƿ���ʹ��

	void SetCurSelDevice(const CString &strModel,const CString &strSN,BOOL bSaveCfg = TRUE);//���õ�ǰѡ����豸

	BOOL IsDeviceInLocalDB(const CString &strModel,const CString &strSN); //װ���ͺ��Ƿ��ڱ��ؿ�
	BOOL HasLoadDevice();
	BOOL HasLoadChMaps();

	BOOL CreateChMaps();  //���������Դ��Device����ͨ��ӳ����󡢻���Ҫ����ϵͳ��������
	BOOL ValidHardRsChMaps();//��֤ʵ��ӳ���Ӳ��ͨ����Դ�Ƿ���ڣ��粻���ڣ���ӳ���ϵɾ��
	void CreateSoftRsCh();//��֤�����Դͨ���Ƿ���Ч�������ݵ�ǰ���ģʽ������ȫ�������Դ����ǳ�����Ӳ����Դӳ���ͨ��
	void CreateRtDataMngr();  //���������Դ�Լ�Device����ȫ������
	void SetCHVINum();
	BOOL GetAnalogCurrentMergeCoef(long &nCoef);//�ж�ͨ��ӳ�����Ƿ���6I�ϲ�Ϊ3I�����,�������,��������������Ҫ��������

	BOOL SelectDeviceFromLocalDB();
	BOOL OpenChMapsFile(CSttChMaps *pChMaps,CSttTestResourceBase *pTestResouce);
	BOOL OpenChMapsFile(const CString &strChMapsFile);
	BOOL OpenSystemParasFile(const CString &strSysParasPath = _T(""));//����Ϊϵͳ���������ļ�·��,���Ϊ��,����ݵ�ǰѡ����ͺż�SN�򿪶�Ӧ���ļ�
	BOOL SaveSystemParasFile();//����ϵͳ�������õ���ǰSN�ļ�����

	BOOL LoadDefaultIec61850Config(/*const CString &strFileName = "Test_Win.ixml"*/);//zhouhj 20220316 ȥ���β�,��Ϊʹ�ó�Ա������ʽ,�������ļ���
	BOOL SaveDefaultIec61850Config(/*const CString &strFileName = "Test_Win.ixml"*/);
	void ClearHisDatas(){m_oRtDataMngr.ClearHisDatas();}//���ʵʱ����ͨ���е���ʷ���ݣ��ڿ�ʼ����ʱʹ��

	BOOL HasContrlBlockSelected_IecConfig();

	void SaveAntherMapsFile(long iSttTestResourceType, const CString &strHeadPath);	//20240912 huangliang ���濪�뿪���������ļ���
	BOOL SaveCurChMapsFile();//���浱ǰͨ��ӳ���ļ�
	BOOL SaveCurDeviceFile();//���浱ǰDevice�ļ�
	void GetAllModuleTags();
	BOOL CreateDefaultChMapsByDevice(CSttChMaps *pCurChMaps,long nIecFormat,BOOL bHasDigital,BOOL bHasWeek = TRUE);//����Ӳ����Դ����ȱʡӳ���ļ���ֻ����ӳ���ļ�Ϊ�յ�Device���سɹ�������µ���

	CString GetCurrSelSN();//{return m_oDevSN_List.m_strID;}//��ȡ��ǰѡ���ͺ�װ�õ�SN
	CString GetCurrModel();//{return m_oDevSN_List.m_strName;}

	void InitLocalSysPara();//ԭ����CSttXTestMngrBaseApp��,�����ƶ����˴�  zhouhj 20210924
	void ValidIecParasSetSel();
	void UpdateParasMaxValuesByWeekRates();
	void UpdateLC_ST_FibersNum();
	long GetUartCount();//2024.5.8 chenling ��ȡ��������


#ifdef _USE_SoftKeyBoard_
	void UpdateSoftKeyboardType();//���¼��̵�ǰ����
protected:
	//2023/8/4  wjs
	void InitKeyBoardFunc();//��ʼ����KeyBoardXML�е�·��
	void ShowKeyBoardNormalFunc();//��Normal���ͼ���Func��ֵ��ֵ
	void ShowKeyBoardWeakFunc();//��Weak���ͼ���Func��ֵ��ֵ
	CDataGroup m_oKeyBoardFuncGroup;//xml�еı��Group
#endif

//	void ValidOutputSel();

protected:
	void CreateDefaultChMapsByDevice_Analog(CSttChMaps *pCurChMaps);
	void CreateDefaultChMapsByDevice_Digital(CSttChMaps *pCurChMaps,long nIecFormat);
	void CreateDefaultChMapsByDevice_Digital_IEC92(CSttChMaps *pCurChMaps);
	void CreateDefaultChMapsByDevice_Digital_FT3(CSttChMaps *pCurChMaps);//��ͨFT3
	void CreateDefaultChMapsByDevice_Digital_FT3DC(CSttChMaps *pCurChMaps);//��ֱFT3
	void CreateDefaultChMapsByDevice_Weak(CSttChMaps *pCurChMaps);
	CString GetModuleDefaultName(const CString &strText,long nChIndex);
	BOOL ParseHdRsID(const CString &strHdRsID,long &nChType ,long &nModuleType,long &nModuleIndex,long &nChIndex);
	BOOL HasMapHdResource();//�ж�ͨ��ӳ���Ƿ�Ϊ��,���Ϊ��������ȱʡͨ��ӳ��
	void UpdateChNames_UzIz(CExBaseList *pCurChMaps, CSttTestResourceBase *pTestResouce);//����U0��I0ͨ��������(Ϊͳһ����ն˺ͼ̵籣����ʽ,ͳһ��ΪU0\I0)

	long GetDigitalModuleNum();
	CString m_strModuleTagsSN;

	CDvmDataset m_oDevSN_List;//��ȡ��ǰѡ���ͺ��£���Ӧ��xml
	CString m_strIecConfigFileName;//zhouhj 20220316 ���ӳ�Ա�����������ø��ļ���,ԭ����ͨ���̶��βη�ʽ����
public:
	long m_nTotalFiberNum_LC ,m_nTotalFiberNum_STSend ;//20240202 suyang �޸�Ϊȫ��
	CSttModuleTags m_oAnalogU_Tags;
	CSttModuleTags m_oAnalogI_Tags;
	CSttModuleTags m_oAnalogUI_Tags;//ģ������ѹ������ϲ��
	//	CSttModuleTags m_oDigital_Tags;
	CSttModuleTags m_oWeak_Tags;
};

extern CSttTestResourceMngr g_oSttTestResourceMngr;

BOOL Global_SetModuleMaxMinValue(CDataGroup *pModule,float *pfAC_MaxMax,float *pfAC_MaxMin,float *pfDC_MaxMax,float *pfDC_MaxMin,BOOL bVol);
long Global_GetModulePos(CDataGroup *pModuleAttrs);
long Global_GetModuleType(CDataGroup *pModuleAttrs);
BOOL Global_GetBinBoutExNum(CDataGroup *pModuleAttrs,int &nBinExNum,int &nBoutExNum);
void Global_GetMaxHarmCount(CDataGroup *pModuleAttrs);

/*
��һ�������ģ�����������������Դ����ģ�飬�����ϴ�ʹ�õĲ������ͺţ�����ȡӲ����Դ���������һ��ʹ��Ӳ����ԴȱʡΪ4U3Iģ�顣�γ�ͨ��ӳ�����
�ڶ���������ͨ��ӳ�����������Դ������ȫ����Դ����ģ�顣
����������������������ȡӲ��ģ�ͣ���Ӳ����Ϣ���浽�����ͺ���ʷ�б����������Դ��Ӳ����Ϣ����ͨ��ӳ�䣬�Ӷ�����ȫ����Դ����ģ�飬���½��棨����¼�롢ʸ��ͼ������ͼ�ȣ���
���Ĳ�����ͨ��ӳ���ļ��������Ҫ
���岽����ʼ���ԣ�����ͨ��ӳ���ϵ�ļ������ز�������ʼ����
*/

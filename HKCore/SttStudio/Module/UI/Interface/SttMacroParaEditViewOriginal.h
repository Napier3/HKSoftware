#pragma once
#include <QWidget>
#include "SttMacroParaEditInterface.h"

#include "../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../Module/SttTest/Common/tmt_test_paras_head.h"
#include "../../Module/UI/Module/CommonMethod/commonMethod.h"
#include "../../SttTestSysGlobalPara.h"
#include "../SttTestCntrCmdDefine.h"
#include "../../SttSystemConfig/SttSystemConfig.h"

#define FILENAME_STTIECCONCFIG	"SttIecConfig.ixml"
#define STT_SETTING_ORIGINAL_ClassID	"CSttMacroParaEditViewOriginal"	//20240802 huangliang 

class CSttMacroParaEditViewOriginal : public QWidget, public CSttMacroParaEditInterface
{
	Q_OBJECT
public:
	CSttMacroParaEditViewOriginal(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~CSttMacroParaEditViewOriginal();

	virtual void SysConfig(CDataGroup *pSysConfig){};
	virtual void SysConfig(CDvmDataset *pSysConfig){};
	virtual void SysConfig(const CString &strSysConfig){};
	virtual void SetDatas(CDvmDataset *pDataset){};
	virtual void SetDatas(CDataGroup *pParas){};
	virtual void SetDatas(const CString &strDataset){};
	virtual void GetDatas(CDvmDataset *pParas){};
	virtual void GetDatas(CDataGroup *pParas){};
	virtual void GetDatas(CString& strParas){};
	virtual long GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml);
	virtual void GetMacroItemsXml(CSttItems &oRootItems);
	virtual void GetMacroItemsXml_Chs(CSttItems *pParentItems);

	virtual BOOL SetValues_dsRcdStep6U6I(CDvmDataset *pDsRcdStep6U6I){return FALSE;}
	virtual bool PrepStartTest(){return true;}//zhouhj 20221027 ��ʼ����ǰ��׼������
	virtual UINT GetMacroEditViewType()	{	return MACRO_EDIT_VIEW_TYPE_ORIGINAL;	}
	virtual void UpdateEventMsg(CEventResult *pCurrEventResult){}
	virtual void UpdateDeviceModelRef(){}
	virtual BOOL IsInternationalMode(){return FALSE;}
    virtual CExBaseList* GetCurrentMacroDatas(){ return NULL;};  //20240716 wanmj �����ܶ��Ĳ��Թ��ܻ�ȡ��ǰ�����������

	virtual void InitBinaryInBinaryOutUI(){};	//20240913 huangliang �ڻ�������ӽ�������麯��������ˢ�·�ģ̬�Ի���Ŀ��뿪����
	void ReadModeDataSaveMaps(CSttDataGroupSerializeRead *pRead);//20240913 huangliang ��ֵ����Maps��¼
	virtual void UpdateSettingAttachUI(){}//���¶�ֵ������ؿؼ�,����ֵ������ģ��ʹ��,���Խ�ȫ�����涼ˢ��,Ҳ����ֻˢ�¶�ֵ�����ؼ�

	virtual void AddShowSoeReports(CDvmDataset *pSoeRptDataset){};//soe�¼�
	virtual void UpdateDinCount(CDvmValues *pValues,CDvmDataset *pSoeRptDataset,CString strItemID){};//ң�ű�λ����
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem){return TRUE;}//�����ȡ�����Ĳ�����ӵ�report��
	virtual void UpdateRemoteBoutData(CDataGroup *pParas){};//����331�Զ����Կ���������
	virtual void UpdateFAParasData(CDataGroup *pParas){};//����FA����

	virtual void UpdatePrimParaSetUI();
	virtual BOOL IsUseSecondParaSet();
	virtual void SetPlotAcDcMaxMinValue(){}
	//�����ܲ���
public:
	CString m_strParaFileTitle;		//��������ģ���ļ�
	CString m_strParaFilePostfix;	//project(*.octxml)
	CString m_strDefaultParaFile;	//Ĭ�ϲ����ļ�·��

	BOOL m_bIsOpenMacroFinished;

	BOOL m_bTmtParaChanged;			//�����༭�����־
	BOOL m_bChMapsChanged;			//ͨ��ӳ��仯��־
	BOOL m_bSystemParasChanged;		//ϵͳ�����仯��־
	BOOL m_bIECGoutMapChanged;		//IEC GOOSE����ͨ��ӳ��ı�

	CSttTestResourceBase *m_pOriginalSttTestResource;//zhouhj 20220313  ÿ��ԭ�����ܶ�Ӧһ���Լ��������Դ

	virtual CString GetDefaultParaFile() { return ""; }
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true){ return false; }
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	BOOL SaveTestMngrFile(const CString& strParasFile);

	void GetAtsCmdDataParas(CDataGroup* pDataGroup);

	virtual void initTestParas();
	virtual void InitUI_OpenParas(){};

	virtual PTMT_PARAS_HEAD GetTestParas() { return NULL;}
	virtual char* GetMacroID(){ return ""; }
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)	{	}
	virtual void UpdateSerializeSysParas();//zhouhj 2024.5.20 ͨ��ϵͳ�������µ�ǰ������ṹ���еĲ���
// 	void UpdateSerializeTestParaBySysPara(CDataGroup* pCurrDataGroup);//dingxy 20240519 ����ϵͳ�����ֵˢ�µ�ѹ����Ƶ������
// 	void UpdateUNFreNom(CDataGroup* pDataGroup);

	QList<CIecCfgGoutDatas*> m_listGoosePub;		//Goose���ݷ����б�
	virtual void InitGoosePubDataGroups();
	void SerializeGoosePubs(CSttXmlSerializeBase *pXmlGoosePubsParent,CIecCfgGoutDatas *pGoutDatas);
	CIecCfgGoutDatas *GetGoutDatas(long nIndex)
	{
		if (nIndex<0)
		{
			return NULL;
		}

		if (nIndex>=m_listGoosePub.size())
		{
			return NULL;
		}

		return m_listGoosePub.at(nIndex);
	}
	QList<CIecCfgGinDatas*> m_listGooseGinPub;		//Goose���ݶ����б�
	virtual void InitGooseGinPubDataGroups();
	void SerializeGooseGinPubs(CSttXmlSerializeBase *pXmlGoosePubsParent,CIecCfgGinDatas *pGinDatas);	
	CIecCfgGinDatas *GetGinDatas(long nIndex)
	{
		if (nIndex<0)
		{
			return NULL;
		}

		if (nIndex>=m_listGooseGinPub.size())
		{
			return NULL;
		}

		return m_listGooseGinPub.at(nIndex);
	}
	QList<CIecCfgDatasSMV*> m_listFT3Pub;		
	virtual void InitFT3PubDataGroups();
	void SerializeFT3Pubs(CSttXmlSerializeBase *pXmlFT3PubsParent,CIecCfgDatasSMV *pIecCfgDatasSMV);
	CIecCfgDatasSMV *GetFT3Datas(long nIndex)
	{
		if (nIndex<0)
		{
			return NULL;
		}

		if (nIndex>=m_listFT3Pub.size())
		{
			return NULL;
		}

		return m_listFT3Pub.at(nIndex);
	}
	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE){};	 
	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE){};	//����GOOSE���ݷ���ҳ��
	virtual void UpdateBinBoutExTab(){};					//���¿�������չ����
	virtual void UpdateTestResource(BOOL bCreateChMaps){}//zhouhj 20220317
//	virtual void UpdateRtSyncTime(CDataGroup *pRtSycTime){}//20220920 zhouhj ���¶�ʱ����ʱͬ��ʱ��

	virtual void OnViewTestLink(BOOL b){};
	virtual void OnViewTestStart(){};
	virtual void OnViewTestStop(){};

	virtual void SetParaChanged();

	virtual void UpdateAuxDCEdit(){};//20240613 suyang �������ڸ���L336D ״̬���� ͨ�� ����ֱ���༭�� 
	//���������ģ���ڲ�ʵ�֣��Ͳ�Ҫ�� 20220221 sf
	//virtual void OnSetSwitch(){};//���ÿ�����
protected slots:
	void slot_GoutMapChanged();
};

float GlobalSetResultValue(CDvmValue* pResultValue,int nDecimalNum);
void GlobalSetQcheckState_BinaryIn(QCheckBox *pBinaryInCheck,tmt_BinaryIn *pBinaryIn,int nBinIndex);
void GlobalSetQcheckState_BinaryOut(QCheckBox *pBinaryOutCheck,tmt_BinaryOut *pBinaryOut,int nBoutIndex);
void GlobalSetQcheckEnable_Binary(QCheckBox *pBinaryInCheck,int nBinaryIndex,int nBinaryCount,bool bEanble);

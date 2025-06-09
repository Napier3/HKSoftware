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
#include <QCheckBox>
#include "../Controls/SettingCtrls/QSettingLineEdit.h"
#include "../Controls/SettingCtrls/QSettingItem.h"
#include "../Controls/SettingCtrls/settingselectdlg.h"
#include "../Controls/SettingCtrls/QSettingItem.h"

#define FILENAME_STTIECCONCFIG	"SttIecConfig.ixml"
#define STT_SETTING_ORIGINAL_ClassID	"CSttMacroParaEditViewOriginal"	//20240802 huangliang 

class CSttMacroParaEditViewOriginal : public QWidget, public CSttMacroParaEditInterface
{
	Q_OBJECT
public:
        CSttMacroParaEditViewOriginal(QWidget *parent = 0);
	virtual ~CSttMacroParaEditViewOriginal();

        virtual void SysConfig(CDataGroup *pSysConfig);
        virtual void SysConfig(CDvmDataset *pSysConfig);
        virtual void SysConfig(const CString &strSysConfig);
        virtual void SetDatas(CDvmDataset *pDataset);
        virtual void SetDatas(CDataGroup *pParas);
        virtual void SetDatas(const CString &strDataset);
        virtual void GetDatas(CDvmDataset *pParas);
        virtual void GetDatas(CDataGroup *pParas);
        virtual void GetDatas(CString& strParas);
	virtual long GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml);
	virtual void GetMacroItemsXml(CSttItems &oRootItems);
	virtual void GetMacroItemsXml_Chs(CSttItems *pParentItems);

        virtual BOOL SetValues_dsRcdStep6U6I(CDvmDataset *pDsRcdStep6U6I);
	virtual bool PrepStartTest(){return true;}//zhouhj 20221027 开始测试前的准备工作
	virtual UINT GetMacroEditViewType()	{	return MACRO_EDIT_VIEW_TYPE_ORIGINAL;	}
        virtual void UpdateEventMsg(CEventResult *pCurrEventResult);
	virtual void UpdateDeviceModelRef(){}
	virtual BOOL IsInternationalMode(){return FALSE;}
    virtual CExBaseList* GetCurrentMacroDatas(){ return NULL;};  //20240716 wanmj 单功能多点的测试功能获取当前测试项的数据

	virtual void InitBinaryInBinaryOutUI(){};	//20240913 huangliang 在基类中添加界面更新虚函数，用以刷新非模态对话框的开入开出量
	void ReadModeDataSaveMaps(CSttDataGroupSerializeRead *pRead);//20240913 huangliang 定值关联Maps记录


	//单功能测试
public:
	CString m_strParaFileTitle;		//过流试验模板文件
	CString m_strParaFilePostfix;	//project(*.octxml)
	CString m_strDefaultParaFile;	//默认参数文件路径

	BOOL m_bIsOpenMacroFinished;

	BOOL m_bTmtParaChanged;			//参数编辑保存标志
	BOOL m_bChMapsChanged;			//通道映射变化标志
	BOOL m_bSystemParasChanged;		//系统参数变化标志
	BOOL m_bIECGoutMapChanged;		//IEC GOOSE发布通道映射改变

	CSttTestResourceBase *m_pOriginalSttTestResource;//zhouhj 20220313  每个原生功能对应一个自己的软件资源

	virtual CString GetDefaultParaFile() { return ""; }
        virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	BOOL SaveTestMngrFile(const CString& strParasFile);

	void GetAtsCmdDataParas(CDataGroup* pDataGroup);

	virtual void initTestParas();
	virtual void InitUI_OpenParas(){};

	virtual PTMT_PARAS_HEAD GetTestParas() { return NULL;}
	virtual char* GetMacroID(){ return ""; }
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
                long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	virtual void UpdateSerializeSysParas();//zhouhj 2024.5.20 通过系统参数更新当前测试项结构体中的参数
// 	void UpdateSerializeTestParaBySysPara(CDataGroup* pCurrDataGroup);//dingxy 20240519 根据系统参数额定值刷新电压电流频率数据
// 	void UpdateUNFreNom(CDataGroup* pDataGroup);

	QList<CIecCfgGoutDatas*> m_listGoosePub;		//Goose数据发布列表
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
	QList<CIecCfgGinDatas*> m_listGooseGinPub;		//Goose数据订阅列表
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
        virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE);
        virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);	//更新GOOSE数据发送页面
        virtual void UpdateBinBoutExTab();					//更新开关量扩展界面
        virtual void UpdateTestResource(BOOL bCreateChMaps);//zhouhj 20220317
//	virtual void UpdateRtSyncTime(CDataGroup *pRtSycTime){}//20220920 zhouhj 更新对时、守时同步时间

        virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart(){};
	virtual void OnViewTestStop(){};

	virtual void SetParaChanged();

	virtual void UpdateAuxDCEdit(){};//20240613 suyang 新增用于更新L336D 状态序列 通用 辅助直流编辑框 
	//介个功能在模块内部实现，就不要了 20220221 sf
	//virtual void OnSetSwitch(){};//设置开关量
protected slots:
	void slot_GoutMapChanged();

	//20240802 huangliang 统一在函数Stt_Global_SettingParent中执行，删除此处代码
//	//20240722 huangliang
//public slots:
//	void slot_ClearAllMap();
};

float GlobalSetResultValue(CDvmValue* pResultValue,int nDecimalNum);
void GlobalSetQcheckState_BinaryIn(QCheckBox *pBinaryInCheck,tmt_BinaryIn *pBinaryIn,int nBinIndex);
void GlobalSetQcheckState_BinaryOut(QCheckBox *pBinaryOutCheck,tmt_BinaryOut *pBinaryOut,int nBoutIndex);
void GlobalSetQcheckEnable_Binary(QCheckBox *pBinaryInCheck,int nBinaryIndex,int nBinaryCount,bool bEanble);

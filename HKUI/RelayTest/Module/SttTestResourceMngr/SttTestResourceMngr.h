#pragma once
#include "TestResource/SttTestResourceBase.h"
#include "RtDataMngr/SttGlobalRtDataMngr.h"
#include "../SttCmd/SttChMaps.h"
#include "../AdjustTool/SttAdjDevice.h"
#include "../../../Module/XfileMngrBase/XFileMngr.h"
#include "../../../Module/FilterText/FilterTextMngr.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"

//2023.6.9 zhouhj  将原Test_Win.ixml统一改为SttIecConfig.ixml
#define IECCONFIG_FILE_NAME_TESTWIN        _T("SttIecConfig.ixml")                   

class CSttModuleTag
{
public:
	CSttModuleTag(void);
	virtual ~CSttModuleTag(void){}

	long GetTotalChCount();//{return m_nChCountU + m_nChCountI;}

	long m_nModulePos;//模块位置
	long m_nModuleType;//模块类型
	long m_nChCountU;//电压通道数(用于模拟量和数字量插件)
	long m_nChCountI;//电流通道数(用于模拟量和数字量插件)

	long m_nChCountU_Week;//电压通道数(用于弱信号插件)
	long m_nChCountI_Week;//电流通道数(用于弱信号插件)

	long m_nModuleIndex;//模块编号,根据模块类型从1开始编号
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
	CSttAdjDevice m_oCurrDevice;  //当前使用的硬件资源
	CSttTestResourceBase *m_pTestResouce;
    //CSttTestResource_Async *m_pTestResouce_Async;

	CSttChMaps m_oChMaps;

	CSttGlobalRtDataMngr m_oRtDataMngr;
	CDataGroup m_oFiberMsgGroup;	//chenlig 光功率数据

#ifndef NOT_USE_TEST_RESOURCE_IECFG//标记是否使用IEC配置
	CIecCfgDatasMngr m_oIecDatasMngr;//在数字测试仪硬件通道信息获取时,需要用到该类
#endif
	void SetIecConfigFileName(const CString &strIecConfigFileName)//zhouhj 20220316 增加单独接口设置文件名
	{
		m_strIecConfigFileName = strIecConfigFileName;
	}

	BOOL IsSyncMode();//判断是否为同步模式
	BOOL IsAsyncMode();//判断是否为异步模式
	CString GetRsDirPath_Device(); //装置资源根目录
	CString GetRsDirPath_Model(CString strModel = _T("")); //装置资源对应型号的根目录,如果参数为空，则取当前选择的型号
	CString GetDevFilePath_Model(CString strModel = _T("")); //当前型号的所有测试仪SN文件的路径,如果参数为空，则取当前选择的型号
	CString GetCurSelRsDeviceFilePath();//获取当前选择的型号，上一次缺省选择的编号对应的Device文件路径
	CString GetCurSelRsDeviceSysParasPath();//获取当前选择设置的系统参数配置文件
	CString GetCurSelDirPath_SN();//获取当前选择的装置编号的文件夹目录路径
	CString GetRsDeviceFilePath(const CString &strModel,const CString &strSN);//根据型号及编号，获取对应Device文件路径
	long SelectChMapsFiles(CXFileMngr *pXFileMngr); //根据当前Device和Resource获取全部映射关系文件
	long GetAllDeviceModel(CFilterTextMngr *pModels);  //获取本地全部型号，采用CFilterTextMngr 是方便使用

	void SetCurSelDevice(const CString &strModel,const CString &strSN,BOOL bSaveCfg = TRUE);//设置当前选择的设备

	BOOL IsDeviceInLocalDB(const CString &strModel,const CString &strSN); //装置型号是否在本地库
	BOOL HasLoadDevice();
	BOOL HasLoadChMaps();

	BOOL CreateChMaps();  //根据软件资源、Device生成通道映射对象、还需要依赖系统参数配置
	BOOL ValidHardRsChMaps();//验证实际映射的硬件通道资源是否存在，如不存在，将映射关系删除
	void CreateSoftRsCh();//验证软件资源通道是否有效，即根据当前输出模式，遍历全部软件资源，标记出具有硬件资源映射的通道
	void CreateRtDataMngr();  //根据软件资源以及Device生成全局数据
	void SetCHVINum();
	BOOL GetAnalogCurrentMergeCoef(long &nCoef);//判断通道映射中是否含有6I合并为3I的情况,如果存在,则最大输出电流需要重新设置

	BOOL SelectDeviceFromLocalDB();
	BOOL OpenChMapsFile(CSttChMaps *pChMaps,CSttTestResourceBase *pTestResouce);
	BOOL OpenChMapsFile(const CString &strChMapsFile);
	BOOL OpenSystemParasFile(const CString &strSysParasPath = _T(""));//参数为系统参数配置文件路径,如果为空,则根据当前选择的型号及SN打开对应的文件
	BOOL SaveSystemParasFile();//保存系统参数配置到当前SN文件夹中

	BOOL LoadDefaultIec61850Config(/*const CString &strFileName = "Test_Win.ixml"*/);//zhouhj 20220316 去除形参,改为使用成员变量方式,可设置文件名
	BOOL SaveDefaultIec61850Config(/*const CString &strFileName = "Test_Win.ixml"*/);
	void ClearHisDatas(){m_oRtDataMngr.ClearHisDatas();}//清除实时数据通道中的历史数据，在开始测试时使用

	BOOL HasContrlBlockSelected_IecConfig();

	void SaveAntherMapsFile(long iSttTestResourceType, const CString &strHeadPath);	//20240912 huangliang 保存开入开出到其他文件中
	BOOL SaveCurChMapsFile();//保存当前通道映射文件
	BOOL SaveCurDeviceFile();//保存当前Device文件
	void GetAllModuleTags();
	BOOL CreateDefaultChMapsByDevice(CSttChMaps *pCurChMaps,long nIecFormat,BOOL bHasDigital,BOOL bHasWeek = TRUE);//根据硬件资源生成缺省映射文件，只有在映射文件为空但Device加载成功的情况下调用

	CString GetCurrSelSN();//{return m_oDevSN_List.m_strID;}//获取当前选择型号装置的SN
	CString GetCurrModel();//{return m_oDevSN_List.m_strName;}

	void InitLocalSysPara();//原来在CSttXTestMngrBaseApp中,将其移动到此处  zhouhj 20210924
	void ValidIecParasSetSel();
	void UpdateParasMaxValuesByWeekRates();
	void UpdateLC_ST_FibersNum();
	long GetUartCount();//2024.5.8 chenling 获取串口数量


#ifdef _USE_SoftKeyBoard_
	void UpdateSoftKeyboardType();//更新键盘当前类型
protected:
	//2023/8/4  wjs
	void InitKeyBoardFunc();//初始化在KeyBoardXML中的路径
	void ShowKeyBoardNormalFunc();//给Normal类型键盘Func的值赋值
	void ShowKeyBoardWeakFunc();//给Weak类型键盘Func的值赋值
	CDataGroup m_oKeyBoardFuncGroup;//xml中的表格Group
#endif

//	void ValidOutputSel();

protected:
	void CreateDefaultChMapsByDevice_Analog(CSttChMaps *pCurChMaps);
	void CreateDefaultChMapsByDevice_Digital(CSttChMaps *pCurChMaps,long nIecFormat);
	void CreateDefaultChMapsByDevice_Digital_IEC92(CSttChMaps *pCurChMaps);
	void CreateDefaultChMapsByDevice_Digital_FT3(CSttChMaps *pCurChMaps);//普通FT3
	void CreateDefaultChMapsByDevice_Digital_FT3DC(CSttChMaps *pCurChMaps);//柔直FT3
	void CreateDefaultChMapsByDevice_Weak(CSttChMaps *pCurChMaps);
	CString GetModuleDefaultName(const CString &strText,long nChIndex);
	BOOL ParseHdRsID(const CString &strHdRsID,long &nChType ,long &nModuleType,long &nModuleIndex,long &nChIndex);
	BOOL HasMapHdResource();//判断通道映射是否为空,如果为空则设置缺省通道映射
	void UpdateChNames_UzIz(CExBaseList *pCurChMaps, CSttTestResourceBase *pTestResouce);//更新U0、I0通道的名称(为统一配电终端和继电保护方式,统一改为U0\I0)

	long GetDigitalModuleNum();
	CString m_strModuleTagsSN;

	CDvmDataset m_oDevSN_List;//读取当前选择型号下，对应的xml
	CString m_strIecConfigFileName;//zhouhj 20220316 增加成员变量用于设置该文件名,原来是通过固定形参方式传递
public:
	long m_nTotalFiberNum_LC ,m_nTotalFiberNum_STSend ;//20240202 suyang 修改为全局
	CSttModuleTags m_oAnalogU_Tags;
	CSttModuleTags m_oAnalogI_Tags;
	CSttModuleTags m_oAnalogUI_Tags;//模拟量电压电流混合插件
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
第一步：软件模块启动：创建软件资源定义模块，加载上次使用的测试仪型号（即获取硬件资源），如果第一次使用硬件资源缺省为4U3I模块。形成通道映射对象。
第二步：根据通道映射对象和软件资源，生成全局资源管理模块。
第三步：测试仪联机：读取硬件模型，将硬件信息保存到本地型号历史列表；根据软件资源和硬件信息更新通道映射，从而更新全局资源管理模块，更新界面（参数录入、矢量图、过程图等）。
第四步：打开通道映射文件，如果需要
第五步：开始测试：下载通道映射关系文件、下载参数，开始测试
*/

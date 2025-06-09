//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLanguageResourceBase.h  CXLanguageResourceBase

#pragma once


#include "../../Module/XLanguage/XLanguageResource.h"



class CXLanguageResourceDvmBase : public CXLanguageResourceBase
{
public:
	CXLanguageResourceDvmBase();
	virtual ~CXLanguageResourceDvmBase();
	
	void InitLangFileForDebug(const CString &strModule);
private:
	CXLanguage m_oXLangRsDvmBase; 
	static const CString  g_strXLangRsDvmBaseFile; 

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	 

	virtual void InitLangRsByFile(); 
	virtual void RegisterLanguageResource();

public:

	static CString g_sLangID_CanotCreatWnd;//未能创建输出窗口\n
	static CString g_sLangTxt_CanotCreatWnd;
    static CString g_sLangID_ConnetDev;//连接设备成功
    static CString g_sLangTxt_ConnetDev;
    static CString g_sLangID_CommunError;//通讯过程中出现错误
    static CString g_sLangTxt_CommunError;
    static CString g_sLangID_CommunTestStop;//通讯引擎异常，测试终止
    static CString g_sLangTxt_CommunTestStop;
    static CString g_sLangID_NoPrtc;//没有注册规约引擎组件
    static CString g_sLangTxt_NoPrtc;
    static CString g_sLangID_CreatPrtcFail;//创建规约通讯设备失败
    static CString g_sLangTxt_CreatPrtcFail;
    static CString g_sLangID_FctnDevelop;//功能设计开发中
    static CString g_sLangTxt_FctnDevelop;
	static CString g_sLangID_Find;//查找
	static CString g_sLangTxt_Find;
	static CString g_sLangID_Ge;//个
	static CString g_sLangTxt_Ge;
	static CString g_sLangID_MatchingTurn;//从此往下依次匹配
	static CString g_sLangTxt_MatchingTurn;
	static CString g_sLangID_Correlation;//关联
	static CString g_sLangTxt_Correlation;
	static CString g_sLangID_DelCorrelation;//依次关联
	static CString g_sLangTxt_DelCorrelation;
	static CString g_sLangID_DataSel;//数据选择
	static CString g_sLangTxt_DataSel;

	static CString g_sLangID_DelRstNewTest;//要删除之前的结果，进行新的测试吗？
	static CString g_sLangTxt_DelRstNewTest;
	static CString g_sLangID_DevDataTemp;//装置设备数据模型
	static CString g_sLangTxt_DevDataTemp;
	static CString g_sLangID_DevDataModelTest;//设备数据模型测试
	static CString g_sLangTxt_DevDataModelTest;
	static CString g_sLangID_DevDataModelCompara;//设备数据模型比较
	static CString g_sLangTxt_DevDataModelCompara;
	static CString g_sLangID_OutputInf;//输出信息
	static CString g_sLangTxt_OutputInf;
	static CString g_sLangID_CopyOutput;//复制输出
	static CString g_sLangTxt_CopyOutput;
	static CString g_sLangID_ClearOutput;//清除输出
	static CString g_sLangTxt_ClearOutput;
};	
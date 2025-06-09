#ifndef STTXTESTMNGRHTMLRPTBASE_H
#define STTXTESTMNGRHTMLRPTBASE_H

#include <QWidget>
#include "../../../../Module/UI/Interface/SttHtmlReportVIewInterface.h"
#include "../../Module/SttTest/Common/tmt_test_mngr.h"
#include "../../Module/SttCmd/GuideBook/SttReports.h"
#include "../../../../../Module/MemBuffer/ExpandMemBuf.h"
#include "../Module/Define.h"

#include "../../../../Module/HtmlReport/SttModuleHtmlRptGenBase.h"

#define FILE_REPORTGENCFG_NAME		"ReportGenConfig.xml"
#define MAX_GROUP_NUMBER			10


class CSttXTestMngrHtmlRptBase : public CSttModuleHtmlRptGenBase
{
public:
    CSttXTestMngrHtmlRptBase();
    virtual ~CSttXTestMngrHtmlRptBase();

	//成员变量
	TMT_PARAS_MNGR_GROUP m_oTmtTestMngrGroup; 	//测试点分组管理结构体
	CDataGroup m_ReportGenCfg;					//解析ReportGenConfig.xml
	CDataGroup m_oParas;						//测试参数数据组
	CSttReports m_oSttReprts;					//分组自动测试报告对象
	CString m_strTrFormat[MAX_GROUP_NUMBER];	//每个测试点的html行代码格式
	CString m_strPointID[TMT_TEST_MNGR_MAX_COUNT];

	virtual void InitIndex(){};
	//虚函数
	virtual void InitTestMngrGroup(); 			//初始化所有测试点按功能分组（每个功能模块需要重载）	
	virtual void FillReportParent();
	virtual void FillReport();		 	 		//向测试报告HTML文本中填测试参数
	virtual void FillReport(int nIndex, int nState);  //向测试报告HTML文本中填单个测试点的测试参数
	virtual void UpdateItemState(int nIndex, int nState);	//更新测试报告中单个测试点的状态
	virtual void UpdateReportState(){};			//更新测试报告中所有测试点的状态
	virtual void FillReportData(const CString &strParentItemsPath, const CString &strItemID, const CString &strState, char *pszReport);
	virtual void GetAllParas(){};		//取得所有子功能的测试参数和结果参数

	virtual void GenRootDiv_H1();
	virtual void AppendTr();
	virtual char* GetGroupMacroID(char* pszSetting){ return ""; };
	virtual char* GetGroupDivID(char* pszMacroID){ return ""; };

	char* GetStateString(int nState);

public:
	void InitReportGenCfg();
	void InitStrTrFormat();

	int GetGroupIndexByDivID(const char* pszDivID);
	virtual void GenHtml();			 					//生成测试报告HTML文本
	void GenRootDiv();				
	void GenRootDiv_End();
	virtual void GenTestMngr();									   //生成整个子表节点
	virtual void GenTestMngr_RootDiv(PTMT_PARAS_MNGR pParasMngr);  //生成子表根节点
	virtual void GenTestMngr_h2(PTMT_PARAS_MNGR pParasMngr);	   //生成子表标题
	virtual void GenTestMngr_Table(PTMT_PARAS_MNGR pParasMngr);	   //生成子表的<table>部分
	virtual void GenTestMngr_Table_th(PTMT_PARAS_MNGR pParasMngr); //生成子表头
	void GenTestMngr_Table_te();						   //生成子表尾
	virtual void GenTestMngr_Point(PTMT_PARAS_MNGR pParasMngr);

	//void UpdateItemState(const CString &strState);

	virtual int GetTestState(const CString &strItemID);		//获取指定测试项的测试状态

	virtual void FormatValueString(CDataGroup* p, CString strID = ""){};	//格式化报告数据字符串
	virtual void FormatValueString(CDataGroup* p, int nState, CString strID = ""){};	//格式化报告数据字符串
	
	virtual void FormatDataTypeString(CDataGroup* p,CString strID);
	void FormatFaultTypeString(CDataGroup* p,CString strID);
	void FormatFaultTypeVolString(CDataGroup* p);
	virtual void FormatOneDecString(CDataGroup* p, const char* pszType);
	void FormatTwoDecString(CDataGroup* p, const char* pszType);
	void FormatThrDecString(CDataGroup* p, const char* pszType);
	void FormatForDecString(CDataGroup* p, const char* pszType);
	virtual void FormatTtripString(CDataGroup* p, const char* pszType, int nState);
	virtual void FormatErrorString(CDataGroup* p, const char* pszType);

	void FormatFaultTypeString(CDataGroup* p);
	virtual void FormatTimeString(CDataGroup* p, const char* pszType);
	void FormatDirString(CDataGroup* p, const char* pszType);
	void FormatRateString(CDataGroup* p, const char* pszType);
	void FormatVoltageString(CDataGroup* p, const char* pszType);
	void FormatAngleString(CDataGroup* p, const char* pszType);
	void FormatAngleString(CDataGroup* p, const char* pszType, int nState);
	void FormatFaultType1String(CDataGroup* p);
	void FormatFaultType2String(CDataGroup* p);
	void FormatFaultTypeUString(CDataGroup* p);
	void FormatPerString(CDataGroup* p, const char* pszType);
	void FormatTranString(CDataGroup* p,const char* pszType);
	void FormatModString(CDataGroup* p,const char* pszType);
	void FormatBInString(CDataGroup* p, const char* pszType);
	void FormatBOutString(CDataGroup* p, const char* pszType);
	void FormatFreqString(CDataGroup* p, const char* pszType);
	QString getErrorType1StringByEnum( ErrorType type );

	void FormatValueTypeString(CDataGroup* p);

	void FormatFaultTypeVDfString(CDataGroup* p);
	void FormatTAString(CDataGroup* p, const char* pszType);
	void FormatTVString(CDataGroup* p,const char* pszType);
	void FormatIdString(CDataGroup* p,const char* pszType);
	void FormatBrString(CDataGroup* p,const char* pszType);
	void FormatChString(CDataGroup* p,const char* pszType);
	void FormatSearchString(CDataGroup* p, const char* pszType);
	void FormatKModeString(CDataGroup* p, const char* pszType);
	void FormatVzDfString(CDataGroup* p, const char* pszType);
	void FormatDfString(CDataGroup* p, const char* pszType);
	void FormatZmodeString(CDataGroup* p, const char* pszType);

};

extern CSttXTestMngrHtmlRptBase *g_pSttXTestMngrHtmlRpt;

#endif // STTXTESTMNGRHTMLRPTBASE_H

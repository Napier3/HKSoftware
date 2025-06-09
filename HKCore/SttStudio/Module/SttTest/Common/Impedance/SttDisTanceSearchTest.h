#pragma once


#include "SttDisTanceTest.h"
#include "tmt_distance_search_test.h"

#define USE_COMPLEX_SEARCH_MODE           //zhouhj 20211119 阻抗搜索方式由原PowerTest中的模式改为使用公共模块的tmt_ComplexSearch类中的函数模式


class CSttDisTanceSearchTest : public CSttDisTanceTest
{
public:
    CSttDisTanceSearchTest();
    virtual ~CSttDisTanceSearchTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttDisTanceSearchTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent);
	virtual void ReturnTestStateEvent_SearchPoint(double dTime, double dRealTime, bool bWithEvent);
	virtual void SetStateParas_StopTest(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//状态8(停止态)

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);

public:
#ifndef USE_COMPLEX_SEARCH_MODE
	int		m_nRunSearchCount;//当前运行搜索的次数,初始值为1
	BOOL	m_bJudge1;
	BOOL	m_bJudge2;
	BOOL	m_bTempResultJudge;


	Complex m_fZStart;		//首端阻抗
	Complex m_fZEnd;		//末端阻抗
	Complex m_fZStep;		//阻抗步长
	Complex m_fZCurrent;	//当前测试阻抗
#endif

protected:
	virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数

#ifndef USE_COMPLEX_SEARCH_MODE
	BOOL ActProcess(float fTime);	//返回试验是否已结束的消息
	BOOL CalNext();
#endif

private:
	tmt_DistanceSearchParas m_oParas;
	tmt_DistanceSearchResults m_oDistanceSearchResults;
};

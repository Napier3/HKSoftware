#pragma once

/*
自动测试对象，管理CTestControl对象，包括如下功能：
1、根据测试模板新建测试：单装置测试、多装置测试等
2、执行测试过程
3、发送自动测试事件给外部对象
4、导出测试报告
*/
class CXSmartTest
{
public:
    static CXSmartTest* Create();
	static CXSmartTest* GetSmartTest()	{	return g_pXSmartTest;	}
	static void Release();

private:
    CXSmartTest();
    virtual ~CXSmartTest();

    static CXSmartTest * g_pXSmartTest;
    static long g_nXSmartTestRef;

};

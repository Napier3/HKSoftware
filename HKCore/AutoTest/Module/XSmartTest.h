#pragma once

/*
�Զ����Զ��󣬹���CTestControl���󣬰������¹��ܣ�
1�����ݲ���ģ���½����ԣ���װ�ò��ԡ���װ�ò��Ե�
2��ִ�в��Թ���
3�������Զ������¼����ⲿ����
4���������Ա���
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

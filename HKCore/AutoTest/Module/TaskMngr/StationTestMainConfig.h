#pragma  once

#include "TestTask.h"
#include "TestWzdDefine.h"

class CStationTestMainConfig : public CExBaseList
{
private:
	CStationTestMainConfig();
	virtual ~CStationTestMainConfig();

	static CStationTestMainConfig *g_pStationTestMainConfig;
	static long               g_nStationTestMainConfig;

	CTestWzdDefines* m_pTestWzdDefines;
public:
	static CStationTestMainConfig* Create();
	static void Release();
	static CTestWzdDefines* GetCTestWzdDefines();
	static void SaveConfigFile();

protected:
	//��������
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID()	{	return CLASSID_STATIONTESTMAINCONFIG;	}
	
	//���л�
	virtual BSTR GetXmlElementKey(){	return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strCStationTestMainConfigKey;}

	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	
	//������
	BOOL Save();
	BOOL Open();

	CString GetStationTestMainConfigFile();
};

//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestApps.cpp  CAtsSvrTestApps


#include "stdafx.h"
#include "AtsSvrTestApps.h"

CAtsSvrTestApps::CAtsSvrTestApps()
{
	//初始化属性

	//初始化成员变量
}

CAtsSvrTestApps::~CAtsSvrTestApps()
{
}

long CAtsSvrTestApps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrTestApps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrTestApps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CAtsSvrTestApps::InitAfterRead()
{
}

BOOL CAtsSvrTestApps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAtsSvrTestApps *p = (CAtsSvrTestApps*)pObj;

	return TRUE;
}

BOOL CAtsSvrTestApps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAtsSvrTestApps *p = (CAtsSvrTestApps*)pDest;

	return TRUE;
}

CBaseObject* CAtsSvrTestApps::Clone()
{
	CAtsSvrTestApps *p = new CAtsSvrTestApps();
	Copy(p);
	return p;
}

BOOL CAtsSvrTestApps::CanPaste(UINT nClassID)
{
	if (nClassID == ATSVRCLASSID_CATSSVRRSTESTAPP)
	{
		return TRUE;
	}

	if (nClassID == ATSVRCLASSID_CATSSVRTESTAPPEX)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAtsSvrTestApps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAtsSvrRsTestAppKey)
	{
		pNew = new CAtsSvrRsTestApp();
	}
	else if (strClassID == pXmlKeys->m_strCAtsSvrTestAppExKey)
	{
		pNew = new CAtsSvrTestAppEx();
	}

	return pNew;
}

CExBaseObject* CAtsSvrTestApps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSVRCLASSID_CATSSVRRSTESTAPP)
	{
		pNew = new CAtsSvrRsTestApp();
	}
	else if (nClassID == ATSVRCLASSID_CATSSVRTESTAPPEX)
	{
		pNew = new CAtsSvrTestAppEx();
	}

	return pNew;
}

/*
<group id="test-apps">
	<group id="test-app">
		<data id="SN" value="123456789"/>
		<data id="EngineProgID" value="IotVm"/>
		<data id="dvm-file" value="MacroTest.xml"/>
		<data id="remote-ip" value="127.0.0.1"/>
		<data id="remote-port" value="9988"/>
	</group>
	……
</group>
*/
//将形参传过来的测试仪信息，写到this指针，即添加到本地的配置文件中
void CAtsSvrTestApps::InitSttParas(CSttParas *pSttParas)
{
// 	POS pos = GetHeadPosition();
// 	CAtsSvrRsTestApp *pApp = NULL; 
// 	CDataGroup *pGroupApps = pSttParas->AddNewGroup(_T("test-apps"), _T("test-apps"), _T("test-apps"));
// 	CDataGroup *pGroupApp = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pApp = (CAtsSvrRsTestApp *)GetNext(pos);
// 		pGroupApp = pGroupApps->AddNewGroup(_T("test-app"), _T("test-app"), _T("test-app"));
// 		pGroupApp->AppendCloneEx(*pApp);
// 	}

	CDataGroup *pTestApps = (CDataGroup *)pSttParas->FindByID(XPARA_ID_test_apps);
	CDataGroup *pTestApp = NULL;
	POS pos = pTestApps->GetHeadPosition();

	while (pos != NULL)
	{
		//pSttParas中传递过来的测试仪信息（pTestApp），没有ID信息，因此此处直接添加一个新的
		pTestApp = (CDataGroup *)pTestApps->GetNext(pos);
		CAtsSvrRsTestApp *pSvrApp = new CAtsSvrRsTestApp();
		pSvrApp->AppendCloneEx(*pTestApp);
		AddNewChild(pSvrApp);
	}
}


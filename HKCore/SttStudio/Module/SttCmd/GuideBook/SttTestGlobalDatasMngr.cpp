#include "stdafx.h"
#include "SttTestGlobalDatasMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSttTestGlobalDatasMngr::CSttTestGlobalDatasMngr()
{
}

CSttTestGlobalDatasMngr::~CSttTestGlobalDatasMngr()
{

}

long CSttTestGlobalDatasMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
		
	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	return 0;
}

long CSttTestGlobalDatasMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);


	return 0;
}

long CSttTestGlobalDatasMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer,m_nIndex);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		//BinarySerializeRead(oBinaryBuffer,m_nIndex);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		//BinarySerializeWrite(oBinaryBuffer,m_nIndex);
	}

	return 0;
}

CExBaseObject* CSttTestGlobalDatasMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strCDataGroupKey)
	{
		return new CDataGroup;
	}

	return NULL;
}

CExBaseObject* CSttTestGlobalDatasMngr::CreateNewChild(long nClassID)
{
	if (nClassID ==  DTMCLASSID_CDATAGROUP)
	{
		return new CDataGroup;
	}

	return NULL;
}

CBaseObject* CSttTestGlobalDatasMngr::Clone()
{
	CSttTestGlobalDatasMngr* pNew = new CSttTestGlobalDatasMngr();
	Copy(pNew);

	return pNew;
}

void CSttTestGlobalDatasMngr::InitAfterRead()
{
}

#include "../../SttGlobalDef.h"
void CSttTestGlobalDatasMngr::SetCommConfig_DvmFile(const CString &strDvmFile)
{
	CDataGroup *p = GetCommConfig(TRUE);
	p->SetDataValue(STT_CMD_PARA_DvmFile, strDvmFile, TRUE);
}

void CSttTestGlobalDatasMngr::SetCommConfig(CDataGroup *pCommConfig)
{
	CDataGroup *p = GetCommConfig(TRUE);
	p->DeleteAll();
	p->AppendCloneEx(*pCommConfig);
}

void CSttTestGlobalDatasMngr::SetCommConfigs(CDataGroup *pCommConfigs)
{
	CDataGroup *p = GetCommConfigs(TRUE);
	p->DeleteAll();
	p->AppendCloneEx(*pCommConfigs);
}

CDataGroup* CSttTestGlobalDatasMngr::GetCommConfig(BOOL bCreateNew)
{
	CDataGroup *p = (CDataGroup*)FindByID(STT_CMD_PARA_CommConfig);
	
	if (p == NULL)
	{
		if (bCreateNew)
		{
			p = new CDataGroup();
			p->m_strID = STT_CMD_PARA_CommConfig;
			p->m_strName = STT_CMD_PARA_CommConfig;
			AddNewChild(p);
		}
	}

	return p;
}

CDataGroup* CSttTestGlobalDatasMngr::GetCommConfigs(BOOL bCreateNew)
{
	CDataGroup *p = (CDataGroup*)FindByID(STT_CMD_PARA_CommConfigs);

	if (p == NULL)
	{
		if (bCreateNew)
		{
			p = new CDataGroup();
			p->m_strID = STT_CMD_PARA_CommConfigs;
			p->m_strName = STT_CMD_PARA_CommConfigs;
			AddNewChild(p);
		}
	}

	return p;
}

//将老版本的配置转换为最新版本的格式
void CSttTestGlobalDatasMngr::SetTestApps(CDvmDataset *pTestApps)
{
	
}

void CSttTestGlobalDatasMngr::SetTestApps(CDataGroup *pTestApps)
{
	CDataGroup *p = GetTestApps(TRUE);
	p->DeleteAll();

	if (pTestApps != NULL)
	{
		p->AppendCloneEx(*pTestApps);
	}
}

CDataGroup* CSttTestGlobalDatasMngr::GetTestApps(BOOL bCreateNew)
{
	CDataGroup *p = (CDataGroup*)FindByID(_T("test-apps")/*AtsRpcTestDef_test_apps*/);

	if (p == NULL)
	{
		if (bCreateNew)
		{
			p = new CDataGroup();
			p->m_strName = /*AtsRpcTestDef_test_apps*/_T("test-apps");
			p->m_strID = /*AtsRpcTestDef_test_apps*/_T("test-apps");
			AddNewChild(p);
		}
	}

	return p;
}

/*
<group id="test-apps">
	<group id="test-app1" data-type="EVD">
		<data id="BenchSN" value="ATS"/>
		<data id="DeviceSN" value="EVD"/>
		<data id="EngineProgID" value="MQTT"/>
		<data id="dvm-file" value="MacroTest.xml"/>
	</group>
	<group id="test-app2" data-type="EVD">
		<data id="BenchSN" value="ATS"/>
		<data id="DeviceSN" value="EVD"/>
		<data id="EngineProgID" value="MQTT"/>
		<data id="dvm-file" value="MacroTest.xml"/>
	</group>
	<group id="hd_res" data-type="hd_res">
		<data id="BenchSN" value="ATS"/>
		<data id="DeviceSN" value="hd_res_req"/>
		<data id="EngineProgID" value="MQTT"/>
		<data id="dvm-file" value=""/>
	</group>
</group>
*/
/*
<results name="结果参数" id="ResultParas">
	<group name="测试仪" id="test-apps" data-type="EVD" value="test-apps">
		<group name="测试仪1" id="test-app1" data-type="EVD" value="test-app">
			<data name="测试仪SN" id="DeviceSN" unit="" data-type="string" default="1" value="EVD"/>
		</group>
		<group name="测试仪2" id="test-app2" data-type="EVD" value="test-app">
			<data name="测试仪SN" id="DeviceSN" unit="" data-type="string" default="1" value="EVD"/>
		</group>
	</group>
</results>
*/
void CSttTestGlobalDatasMngr::UpdateTestApps(CDataGroup *pTestApps)
{
	//从传入的测试仪资源定义中，查找test-apps节点，保证通用性，test-apps可以位于比较深的层次
	CDataGroup *pFind = FindTestApps(pTestApps);

	if (pFind == NULL)
	{
		return;
	}

	//测试模板中定义的测试仪管理对象
	CDataGroup *pGbTestApps = (CDataGroup*)FindByID(_T("test-apps")/*AtsRpcTestDef_test_apps*/);

	if (pGbTestApps == NULL)
	{//如果没有找到，则将传入的资源设置为当前的资源
		SetTestApps(pFind);
		return;
	}

	CDataGroup *pTestApp = NULL;
	CDataGroup *pTestAppFind = NULL;
	POS pos = pFind->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{//遍历传入的资源
		p = pFind->GetNext(pos);
		
		if (p->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pTestAppFind = (CDataGroup*)pGbTestApps->FindByID(p->m_strID);

		if (pTestAppFind == NULL)
		{//如果没有找到对应的测试仪，则提示
			CString strTemp = p->m_strID;
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("TestApp [%s] not exist "), strTemp.GetString());
			continue;
		}

		//根据传入的测试仪对象，设置相关的属性
		pTestAppFind->InitDataValues((CDataGroup*)p, FALSE);
	}
}

CDataGroup* CSttTestGlobalDatasMngr::FindTestApps(CDataGroup *pTestApps)
{
	CDataGroup *pFind = NULL;
	CExBaseObject *p = NULL;

	if (pTestApps->m_strID == _T("test-apps")/*AtsRpcTestDef_test_apps*/)
	{
		return pTestApps;
	}

	POS pos = pTestApps->GetHeadPosition();

	while (pos != NULL)
	{
		p = pTestApps->GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			if (p->m_strID == _T("test-apps")/*AtsRpcTestDef_test_apps*/)
			{
				return (CDataGroup*)p;
			}
			else
			{
				pFind = FindTestApps((CDataGroup*)p);

				if (pFind != NULL)
				{
					return pFind;
				}
			}
		}
	}

	return NULL;
}

void CSttTestGlobalDatasMngr::AddTestAppInfo(const CString &strID, const CString&strValue)
{
	CDataGroup *pTestApps = GetTestApps(TRUE);
	POS pos = pTestApps->GetHeadPosition();

	while (pos != NULL)
	{
		CDataGroup *pTestApp = (CDataGroup *)pTestApps->GetNext(pos);

		CDvmData *pFind = (CDvmData *)pTestApp->FindByID(strID);

		if (pFind == NULL)
		{
			pFind = pTestApp->AddNewData(strID, strValue);
		}
		else
		{
			pFind->m_strValue = strValue;
		}
	}
}
#include "stdafx.h"
#include "TestGlobalDatasMngr.h"
#include "../AutoTestXMLRWKeys.h"
#include "../SmartTestDefineInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTestGlobalDatasMngr::CTestGlobalDatasMngr()
{
	m_pTestApp = NULL;
	m_pDeviceAttr = NULL;
}

CTestGlobalDatasMngr::~CTestGlobalDatasMngr()
{

}

long CTestGlobalDatasMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
		
	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	return 0;
}

long CTestGlobalDatasMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);


	return 0;
}

long CTestGlobalDatasMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

CExBaseObject* CTestGlobalDatasMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey)
	{
		return new CDataSet;
	}

	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strDataSetGroupKey)
	{
		return new CDataSetGroup;
	}

	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCDataGroupKey)
	{
		return new CDataGroup;
	}

	return NULL;
}

CExBaseObject* CTestGlobalDatasMngr::CreateNewChild(long nClassID)
{
	if (nClassID ==  GBCLASSID_DATASET)
	{
		return new CDataSet;
	}

	if (nClassID ==  GBCLASSID_DATASETGROUP)
	{
		return new CDataSetGroup;
	}

	if (nClassID ==  DTMCLASSID_CDATAGROUP)
	{
		return new CDataGroup;
	}

	return NULL;
}

CBaseObject* CTestGlobalDatasMngr::Clone()
{
	CTestGlobalDatasMngr* pNew = new CTestGlobalDatasMngr();
	Copy(pNew);

	return pNew;
}

void CTestGlobalDatasMngr::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch(nClassID)
		{
		case GBCLASSID_DATASET:
		
			if (p->m_strID == DSID_TESTAPP_DEF)
			{
				m_pTestApp = (CDataSet *)p;
			}
			else if (p->m_strID == DSID_DEVICEATTR)
			{
				m_pDeviceAttr = (CDataSet *)p;
			}
			break;
	
			
		}
	}	


	if (m_pTestApp == NULL)
	{
		m_pTestApp = new CDataSet();
		m_pTestApp->m_strName = DSID_TESTAPP_DEF;
		m_pTestApp->m_strID = DSID_TESTAPP_DEF;
		AddNewChild(m_pTestApp);
	}

	if (m_pDeviceAttr == NULL)
	{
		m_pDeviceAttr = new CDataSet();
		m_pDeviceAttr->m_strName = DSID_DEVICEATTR;
		m_pDeviceAttr->m_strID = DSID_DEVICEATTR;
		AddNewChild(m_pDeviceAttr);
	}
}


void CTestGlobalDatasMngr::SetTestGlobaoDatasMngrs(CDataSet *pDataset)
{
	SetTestGlobaoDatas_DeviceAttr(pDataset);
	SetTestGlobaoDatas_TestApp(pDataset);
}

void CTestGlobalDatasMngr::SetTestGlobaoDatas_DeviceAttr(CDataSet *pDataset)
{
	if (pDataset->m_strID != DSID_DEVICEATTR)
	{
		return;
	}

	if (m_pDeviceAttr == NULL)
	{
		return;
	}

	m_pDeviceAttr->DeleteAll();
	m_pDeviceAttr->AppendCloneEx(*pDataset, TRUE);
}

void CTestGlobalDatasMngr::SetTestGlobaoDatas_TestApp(CDataSet *pDataset)
{
	if (pDataset->m_strID != DSID_TESTAPP_DEF)
	{
		return;
	}

	if (m_pTestApp == NULL)
	{
		return;
	}

	m_pTestApp->DeleteAll();
	m_pTestApp->AppendCloneEx(*pDataset, TRUE);
}

#include "../../../SttStudio/Module/SttGlobalDef.h"
void CTestGlobalDatasMngr::SetCommConfig_DvmFile(const CString &strDvmFile)
{
	CDataGroup *p = GetCommConfig(TRUE);
	p->SetDataValue(STT_CMD_PARA_DvmFile, strDvmFile, TRUE);
}

void CTestGlobalDatasMngr::SetCommConfig(CDataGroup *pCommConfig)
{
	CDataGroup *p = GetCommConfig(TRUE);
	p->DeleteAll();
	p->AppendCloneEx(*pCommConfig);
}

void CTestGlobalDatasMngr::SetCommConfigs(CDataGroup *pCommConfigs)
{
	CDataGroup *p = GetCommConfigs(TRUE);
	p->DeleteAll();
	p->AppendCloneEx(*pCommConfigs);
}

CDataGroup* CTestGlobalDatasMngr::GetCommConfig(BOOL bCreateNew)
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

CDataGroup* CTestGlobalDatasMngr::GetCommConfigs(BOOL bCreateNew)
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
void CTestGlobalDatasMngr::SetTestApps(CDvmDataset *pTestApps)
{
	
}

void CTestGlobalDatasMngr::SetTestApps(CDataGroup *pTestApps)
{
	CDataGroup *p = GetTestApps(TRUE);
	p->DeleteAll();

	if (pTestApps != NULL)
	{
		p->AppendCloneEx(*pTestApps);
	}
}

CDataGroup* CTestGlobalDatasMngr::GetTestApps(BOOL bCreateNew)
{
	CDataGroup *p = (CDataGroup*)FindByID(AtsRpcTestDef_test_apps);

	if (p == NULL)
	{
		if (bCreateNew)
		{
			p = new CDataGroup();
			p->m_strName = AtsRpcTestDef_test_apps;
			p->m_strID = AtsRpcTestDef_test_apps;
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
void CTestGlobalDatasMngr::UpdateTestApps(CDataGroup *pTestApps)
{
	//从传入的测试仪资源定义中，查找test-apps节点，保证通用性，test-apps可以位于比较深的层次
	CDataGroup *pFind = FindTestApps(pTestApps);

	if (pFind == NULL)
	{
		return;
	}

	//测试模板中定义的测试仪管理对象
	CDataGroup *pGbTestApps = (CDataGroup*)FindByID(AtsRpcTestDef_test_apps);

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

CDataGroup* CTestGlobalDatasMngr::FindTestApps(CDataGroup *pTestApps)
{
	CDataGroup *pFind = NULL;
	CExBaseObject *p = NULL;

	if (pTestApps->m_strID == AtsRpcTestDef_test_apps)
	{
		return pTestApps;
	}

	POS pos = pTestApps->GetHeadPosition();

	while (pos != NULL)
	{
		p = pTestApps->GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			if (p->m_strID == AtsRpcTestDef_test_apps)
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

void CTestGlobalDatasMngr::AddTestAppInfo(const CString &strID, const CString&strValue)
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
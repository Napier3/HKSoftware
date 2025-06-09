#include "StdAfx.h"
#include "GbSmartGenWzd.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../SttStudio/Module/SttGlobalDef.h"
#include "../../../../IotProtoServer/Module/SttPxCommCmdDef.h"
#include "GbWzdItemPaste.h"

#include "../../../61850/Module/MMS_STACK_CFG/MMS_STACK_CFG.h"
#include "../../../61850/Module/61850ClientConfig/61850ClientConfig.h"
#include "../../../IotProtoServer/Module/SttPxCommCmdDef.h"

/*  //智能生成中的数据格式
<smart-wzd>
	<group name="device" id="device" data-type="device" value="">  【创建的项目分类】
		<group name="Items1" id="items1" data-type="items" value="">
		</group>
		<group name="Items2" id="items2" data-type="items" value="">
		</group>
	</group>
	<macro-gen name="" id="" data-type="" value="" test-class="" items-name="" items-id="" test-macro-ui-id="" parent-items-id="">【向导】
		<group name="cmd-gen-paras" id="cmd-gen-paras" data-type="cmd-gen-paras" value="">【命令参数】
		</group>
		<group name="cmd-gen-cfg" id="cmd-gen-cfg" data-type="cmd-gen-cfg" value="">
		</group>  【选择的通信命令配置】
		<group name="macro-ui-paras" id="macro-ui-paras" data-type="macro-ui-paras" value="">【测试功能界面参数】
		</group>
		<group name="test-macro-ui" id="test-macro-ui" data-type="test-macro-ui" value="">
		</group>【测试功能属性】
		<group name="characteristic" id="characteristic" data-type="characteristic" value="">
		</group>【特性曲线】
	</macro-gen>
</smart-wzd>
*/

extern CGbSmartGenWzd *g_theGbSmartGenWzd;

CGbSmartGenWzd::CGbSmartGenWzd(void)
{
	m_nDevPort = 102;
	m_strDevIP = _T("172.21.0.104");
	m_strLocalIP = _T("172.21.0.199");
	m_strDvmFile = _T("PCS-943.xml");
	m_pCurrItemCopy = NULL;

	InitWzd();
	m_bModifyFlag = FALSE;

	//CreateNew();

	CGbSmartGenWzdXmlRWKeys::Create();
	CGbWzdItemsNameLib::Create();

	m_pProtocolEngineCfg = new CDvmDataset();
	m_pTestClass = new CDataGroup();
	m_pCommCmdCfg = new CDataGroup();
	m_pDvmDevice = new CDvmDevice();
	m_pCmdDelay = new CDataGroup();
	m_bOwnAttrOnly = FALSE;
	m_nIsTimeSetsUnit_ms = 1;
	m_nIsAddDevReset = 1;
}

CGbSmartGenWzd::~CGbSmartGenWzd(void)
{
	if (m_pTestApp != NULL)
	{
		delete m_pTestApp;
		m_pTestApp = NULL;
	}

	if (m_pDevice != NULL)
	{
		delete m_pDevice;
		m_pDevice = NULL;
	}

	CGbSmartGenWzdXmlRWKeys::Release();
	CGbWzdItemsNameLib::Release();

	if (m_pGbMacroGenWzdInit != NULL)
	{
		delete m_pGbMacroGenWzdInit;
		m_pGbMacroGenWzdInit = NULL;
	}

	delete m_pProtocolEngineCfg;
	delete m_pTestClass;
	delete m_pCommCmdCfg;
	delete m_pDvmDevice;
	delete m_pCmdDelay;

	if (m_pCurrItemCopy != NULL)
	{
		delete m_pCurrItemCopy;
	}
}

void CGbSmartGenWzd::InitWzd()
{
	m_pTestApp = NULL;
	m_pDevice = NULL;
	m_pGbItemsRootTree = NULL;
	m_pCurrGbMacroGenWzd = NULL;
	m_pGbMacroGenWzdInit = NULL;
}

CString CGbSmartGenWzd::GetEngineProgID()
{
	//shaolei 2023-8-23
	return m_strEngineProgID;

	if (m_strEngineProgID == STT_IOT_PP_TYPE_PpEngine)
	{
		return _T("PpEngine.PoEngine");
	}
	else if (m_strEngineProgID == STT_IOT_PP_TYPE_MmsEngine)
	{
		return _T("PpMmsEngine.PoEngine");
	}
	else if (m_strEngineProgID == STT_IOT_PP_TYPE_CmsEngine)
	{
		return _T("DltEngine.PoEngine");
	}
	else
	{
		return _T("PpMmsEngine.PoEngine");
	}
}

//通讯命令是否是通过向导添加？
//并返回 对应ID = _BeforeTest_ 或者  _AfterTest_的group节点
CDataGroup* CGbSmartGenWzd::IsCommCmdAddByWzd(const CString &strPath, CSttCommCmd *pSttCommCmd, BOOL &bWzd)
{
	CExBaseList* pParent = (CExBaseList*)pSttCommCmd->GetParent();
	CSttItems *pRootNode = Stt_GetFirstParentItems(pSttCommCmd, GBITEMS_NODETYPE_ROOTNODE, TRUE);

	if (pRootNode == NULL)
	{
		bWzd = FALSE;
		return NULL;
	}

	pParent = (CExBaseList*)pRootNode->GetParent();
	CString strRootNodePath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);  //找到父项目，并获取父项目的项目路径
	CGbMacroGenWzd *pMacroGenWzd = FindMacroGen(pRootNode->m_strID, pRootNode->m_strName, strRootNodePath);

	if (pMacroGenWzd == NULL)
	{
		bWzd = FALSE;
		return NULL;
	}

	pParent = (CExBaseList*)pSttCommCmd->GetParent();
	//对应ID = _BeforeTest_ 或者  _AfterTest_的group节点
	CDataGroup *pGrp = (CDataGroup *)pMacroGenWzd->m_pCmdGenParas->FindByID(pParent->m_strID);

	bWzd = TRUE;
	return pGrp;
}

//根据当前向导步，更新默认向导
void CGbSmartGenWzd::UpdateGbMacroGenWzdInit()
{
	m_pGbMacroGenWzdInit->InitGbMacroGenWzd(m_pCurrGbMacroGenWzd);
	m_pGbMacroGenWzdInit->SaveInitXmlFile();
}


long CGbSmartGenWzd::XmlRead(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	try
	{
		XmlReadOwn(oNode, pXmlRWKeys);
	}
	catch (...)
	{
	}

	try
	{
		if (!m_bOwnAttrOnly)
		{
			CXmlRWNodeListBase *pChildNodeList = oNode.GetChildNodes();
			XmlReadChildren(*pChildNodeList, pXmlRWKeys);
		}
	}
	catch (...)
	{
	}

	if (!m_bOwnAttrOnly)
	{
		InitAfterRead();
	}

	return 0;
}

long CGbSmartGenWzd::XmlWrite(CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent, BSTR pszElementKey, CXmlRWKeys *pXmlRWKeys)
{
	CXmlRWElementBase *pElement = oXMLDoc.CreateElement(pszElementKey,&oParent);

	XmlWriteOwn(oXMLDoc, *pElement, pXmlRWKeys);

	if (!m_bOwnAttrOnly)
	{
		XmlWriteChildren(oXMLDoc, *pElement, pXmlRWKeys);
	}

	return 0;
}

long CGbSmartGenWzd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strDvmFileKey, oNode, m_strDvmFile);
	xml_GetAttibuteValue(pXmlKeys->m_strEngineProgIDKey, oNode, m_strEngineProgID);
	xml_GetAttibuteValue(pXmlKeys->m_strPpFileKey, oNode, m_strPpFile);
	xml_GetAttibuteValue(pXmlKeys->m_strDevIPKey, oNode, m_strDevIP);
	xml_GetAttibuteValue(pXmlKeys->m_strDevPortKey, oNode, m_nDevPort);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strDeviceType);
	xml_GetAttibuteValue(pXmlKeys->m_strLocalIPKey, oNode, m_strLocalIP);
	xml_GetAttibuteValue(pXmlKeys->m_strIsTimeSetsUnit_ms_Key, oNode, m_nIsTimeSetsUnit_ms);
	xml_GetAttibuteValue(pXmlKeys->m_strIsAddDevResetKey, oNode, m_nIsAddDevReset);

	return 0;
}

long CGbSmartGenWzd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDvmFileKey, oElement, m_strDvmFile);
	xml_SetAttributeValue(pXmlKeys->m_strEngineProgIDKey, oElement, m_strEngineProgID);
	xml_SetAttributeValue(pXmlKeys->m_strPpFileKey, oElement, m_strPpFile);
	xml_SetAttributeValue(pXmlKeys->m_strDevIPKey, oElement, m_strDevIP);
	xml_SetAttributeValue(pXmlKeys->m_strDevPortKey, oElement, m_nDevPort);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strDeviceType);
	xml_SetAttributeValue(pXmlKeys->m_strLocalIPKey, oElement, m_strLocalIP);
	xml_SetAttributeValue(pXmlKeys->m_strIsTimeSetsUnit_ms_Key, oElement, m_nIsTimeSetsUnit_ms);
	xml_SetAttributeValue(pXmlKeys->m_strIsAddDevResetKey, oElement, m_nIsAddDevReset);

	return 0;
}

long CGbSmartGenWzd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDataGroup::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		//BinarySerializeRead(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		//BinarySerializeWrite(oBinaryBuffer, m_strDataType);
	}

	return 0;
}

void CGbSmartGenWzd::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		if (pObj->m_strID == STT_CMD_PARA_GBITEMSTREE)
		{
			m_pGbItemsRootTree = (CDataGroup *)pObj;
		}
	}

	if (m_strEngineProgID == _T("PpEngine.PoEngine"))
	{
		m_strEngineProgID = STT_IOT_PP_TYPE_PpEngine;
	}
	else if (m_strEngineProgID == _T("PpMmsEngine.PoEngine"))
	{
		m_strEngineProgID = STT_IOT_PP_TYPE_PpEngine;
	}
	else if (m_strEngineProgID == _T("DltEngine.PoEngine"))
	{
		m_strEngineProgID = STT_IOT_PP_TYPE_PpEngine;
	}
	else
	{
		m_strEngineProgID = STT_IOT_PP_TYPE_MmsEngine;
	}
}

BOOL CGbSmartGenWzd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDataGroup::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbMacroGenWzd *p = (CGbMacroGenWzd*)pObj;

	return TRUE;
}

BOOL CGbSmartGenWzd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataGroup::CopyOwn(pDest);

	CGbSmartGenWzd *p = (CGbSmartGenWzd*)pDest;
	p->m_strDvmFile = m_strDvmFile;
	p->m_strEngineProgID = m_strEngineProgID;
	p->m_strPpFile = m_strPpFile;
	p->m_strDevIP = m_strDevIP;
	p->m_nDevPort = m_nDevPort;
	p->m_strDeviceType = m_strDeviceType;
	p->m_strLocalIP = m_strLocalIP;

	return TRUE;
}

CBaseObject* CGbSmartGenWzd::Clone()
{
	CGbSmartGenWzd *p = new CGbSmartGenWzd();
	Copy(p);
	return p;
}

CBaseObject* CGbSmartGenWzd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbSmartGenWzd *p = new CGbSmartGenWzd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CGbSmartGenWzd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->CGbMacroGenWzdKey())
	{
		pNew = new CGbMacroGenWzd();
	}
	else if (strClassID == pXmlKeys->CGbWzdCommCmdAddKey())
	{
		pNew = new CGbWzdCommCmdAdd();
	}
	else if (strClassID == pXmlKeys->CGbWzdMacroTestAddKey())
	{
		pNew = new CGbWzdMacroTestAdd();
	}
	else if (strClassID == pXmlKeys->CGbWzdItemsAddKey())
	{
		pNew = new CGbWzdItemsAdd();
	}
	else if (strClassID == pXmlKeys->CGbWzdItemEditKey())
	{
		pNew = new CGbWzdItemEdit();
	}
	else if (strClassID == pXmlKeys->CGbWzdItemMoveKey())
	{
		pNew = new CGbWzdItemMove();
	}
	else if (strClassID == pXmlKeys->CGbWzdItemRsltExprEditKey())
	{
		pNew = new CGbWzdItemRsltExprEdit();
	}
	//可以不将项目复制的操作，记录到向导中
// 	else if (strClassID == pXmlKeys->CGbWzdItemCopyKey())
// 	{
// 		pNew = new CGbWzdItemCopy();
// 	}
	else if (strClassID == pXmlKeys->CGbWzdItemPasteKey())
	{
		pNew = new CGbWzdItemPaste();
	}
	else if (strClassID == pXmlKeys->CGbWzdItemSetStateKey())
	{
		pNew = new CGbWzdItemSetState();
	}
	else if (strClassID == pXmlKeys->CGbWzdSafetyAddKey())
	{
		pNew = new CGbWzdSafetyAdd();
	}
	else if (strClassID == pXmlKeys->CGbWzdCommCmdUpdateKey())
	{
		pNew = new CGbWzdCommCmdUpdate();
	}
	else if (strClassID == pXmlKeys->CGbWzdCommCmdAddGrpKey())
	{
		pNew = new CGbWzdCommCmdAddGrp();
	}
	else if (strClassID == pXmlKeys->CGbWzdItemsDeleteKey())
	{
		pNew = new CGbWzdItemsDelete();
	}
	else
	{
		pNew = CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
	}

	return pNew;
}

CExBaseObject* CGbSmartGenWzd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DVMCLASSID_GBMACROGENWZD)
	{
		pNew = new CGbMacroGenWzd();
	}
	else if (nClassID == DVMCLASSID_GBWZDCOMMCMDADD)
	{
		pNew = new CGbWzdCommCmdAdd();
	}
	else if (nClassID == DVMCLASSID_GBWZDMACROTESTADD)
	{
		pNew = new CGbWzdMacroTestAdd();
	}
	else if (nClassID == DVMCLASSID_GBWZDITEMSADD)
	{
		pNew = new CGbWzdItemsAdd();
	}
	else if (nClassID == DVMCLASSID_GBWZDITEMEDIT)
	{
		pNew = new CGbWzdItemEdit();
	}
	else if (nClassID == DVMCLASSID_GBWZDITEMMOVE)
	{
		pNew = new CGbWzdItemMove();
	}
	//可以不将项目复制的操作，记录到向导中
// 	else if (nClassID == DVMCLASSID_GBWZDITEMCOPY)
// 	{
// 		pNew = new CGbWzdItemCopy();
// 	}
	else if (nClassID == DVMCLASSID_GBWZDITEMPASTE)
	{
		pNew = new CGbWzdItemPaste();
	}
	else if (nClassID == DVMCLASSID_GBWZDITEMRSLTEXPREDIT)
	{
		pNew = new CGbWzdItemRsltExprEdit();
	}
	else if (nClassID == DVMCLASSID_GBWZDITEMSETSTATE)
	{
		pNew = new CGbWzdItemSetState();
	}
	else if (nClassID == DVMCLASSID_GBWZDSAFETYADD)
	{
		pNew = new CGbWzdSafetyAdd();
	}	
	else if (nClassID == DVMCLASSID_GBWZDCOMMCMDUPDATE)
	{
		pNew = new CGbWzdCommCmdUpdate();
	}	
	else if (nClassID == DVMCLASSID_GBWZDCOMMCMDADDGRP)
	{
		pNew = new CGbWzdCommCmdAddGrp();
	}
	else if (nClassID == DVMCLASSID_GBWZDITEMSDELETE)
	{
		pNew = new CGbWzdItemsDelete();
	}
	else
	{
		pNew = CDataGroup::CreateNewChild(nClassID);
	}

	return pNew;
}

//////////////////////////////////////////////////////////////////////////
long CGbSmartGenWzd::GetEngineProgIDIndex()
{
	if (m_pProtocolEngineCfg == NULL)
	{
		return 0;
	}

	CExBaseObject *pFind = m_pProtocolEngineCfg->FindByID(m_strEngineProgID);

	if (pFind == NULL)
	{
		return 0;
	}

	return m_pProtocolEngineCfg->FindIndex(pFind);
}

BOOL CGbSmartGenWzd::ValidateCreateParas()
{
	//后续增加IP地址的合法性检测
	if (m_strDevIP.IsEmpty()
		|| m_strEngineProgID.IsEmpty()
		|| m_strDvmFile.IsEmpty()
		|| m_nDevPort <= 0)
	{
		return FALSE;
	}

	if (m_strEngineProgID == STT_IOT_PP_TYPE_PpEngine && m_strPpFile.IsEmpty())  //原先为_T("PpEngine.PoEngine")
	{
		return FALSE;
	}

	return TRUE;
}


void CGbSmartGenWzd::InitProtocolEngine()
{
	if (m_pProtocolEngineCfg->GetCount() > 0)
	{
		return;
	}

	CString strFile;
	strFile = _P_GetInstallPath();
	strFile += _T("Common/Config/");
	//strFile += _T("ProtocolEngineConfig.xml");
	strFile += _T("PpSttIotEngineConfig.xml");  //2022-11-23  lijunqing  引擎ID，不再使用ProgID

	m_pProtocolEngineCfg->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}


/*
<group id="device">
	<data id="EngineProgID" value="PpEngine"/>
	<data id="ppxml-file" value="SZNR-TTU.ppxml"/>
	<data id="dvm-file" value="SZNR-TTU.xml"/>
	<data id="remote-ip" value="127.0.0.1"/>
	<data id="remote-port" value="9988"/>
</group>
<group id="test-app">
	<data id="DeviceSN" value="123456789"/>
	<data id="EngineProgID" value="IotVm"/>
	<data id="dvm-file" value="MacroTest.xml"/>
	<data id="remote-ip" value="127.0.0.1"/>
	<data id="remote-port" value="9988"/>
</group>
*/
void CGbSmartGenWzd::InitCreateParas_Device()
{
	if (m_pDevice == NULL)
	{
		m_pDevice = new CDataGroup;
		m_pDevice->m_strDataType = XPARA_ID_device;
		m_pDevice->m_strID = XPARA_ID_device;
	}
	else
	{
		m_pDevice->DeleteAll();
	}

	CString strDvmFilePath;
	strDvmFilePath = InitDvmDevice(m_strDvmFile);
	m_pDevice->AddNewData(STT_CMD_PARA_EngineProgID, GetEngineProgID());
	m_pDevice->AddNewData(XPARA_ID_PPXMLFILE, m_strPpFile);  //暂时绝对路径。当时说要相对路径？
	m_pDevice->AddNewData(XPARA_ID_DVMFILE, strDvmFilePath);
	m_pDevice->AddNewData(XPARA_ID_Remote_ip, m_strDevIP);
	m_pDevice->AddNewData(XPARA_ID_Remote_port, m_nDevPort);
	m_pDevice->AddNewData(XPARA_ID_Type, m_strDeviceType);
	m_pDevice->AddNewData(XPARA_ID_Time_unit_ms, m_nIsTimeSetsUnit_ms);
	m_pDevice->AddNewData(XPARA_ID_AddDevReset, m_nIsAddDevReset);
}

void CGbSmartGenWzd::CmdDelay_Init()
{
	m_pCmdDelay->AddNewData(_T("0"), _T("0"));
	m_pCmdDelay->AddNewData(_T("100"), _T("100"));
	m_pCmdDelay->AddNewData(_T("200"), _T("200"));
	m_pCmdDelay->AddNewData(_T("500"), _T("500"));
	m_pCmdDelay->AddNewData(_T("1000"), _T("1000"));
	m_pCmdDelay->AddNewData(_T("2000"), _T("2000"));
	m_pCmdDelay->AddNewData(_T("3000"), _T("3000"));
	m_pCmdDelay->AddNewData(_T("5000"), _T("5000"));
	m_pCmdDelay->AddNewData(_T("8000"), _T("8000"));
	m_pCmdDelay->AddNewData(_T("10000"), _T("10000"));
	m_pCmdDelay->AddNewData(_T("20000"), _T("20000"));
	m_pCmdDelay->AddNewData(_T("30000"), _T("30000"));
	m_pCmdDelay->AddNewData(_T("60000"), _T("60000"));
}

void CGbSmartGenWzd::UpdateDvmDataset(const CString &strDsPath, CDvmValues *pRptValues)
{
	if (pRptValues == NULL || m_pDvmDevice == NULL)
	{
		return;
	}

	CDvmDataset *pDsLocal = m_pDvmDevice->FindDatasetByPath(strDsPath);

	if (pDsLocal == NULL)
	{
		return;
	}

	//先更新模型中的值
	POS pos = pRptValues->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmValue *pRptValue = (CDvmValue *)pRptValues->GetNext(pos);
		CDvmData *pDstData = (CDvmData *)pDsLocal->FindByID(pRptValue->m_strID);

		if (pDstData != NULL)
		{
			pDstData->m_strValue = pRptValue->m_strValue;
		}
	}

	pDsLocal->SetDataChange();
}

void CGbSmartGenWzd::UpdateDvmDataset(CDvmDataset *pRptDataset)
{
	if (pRptDataset == NULL)
	{
		return;
	}

	if (pRptDataset->GetCount() == 0)
	{
		return;
	}

	if (m_pDvmDevice == NULL)
	{
		return;
	}

	CDvmDataset *pDsLocal = m_pDvmDevice->FindDatasetByPath(pRptDataset->m_strID);

	if (pDsLocal == NULL)
	{
		return;
	}

	//先更新模型中的值
	pDsLocal->UpdateDataValue(pRptDataset, FALSE);
	pDsLocal->SetDataChange();
}

CPpSttCommConfig* CGbSmartGenWzd::SaveDevInfoToCfg()
{
	CPpSttCommConfig* pCommCfg = &m_oCommConfig;

	if (m_strEngineProgID == STT_IOT_PP_TYPE_CmsEngine)  //原先为_T("DltEngine.PoEngine")
	{
		SaveDevInfoToCfg_CMS(pCommCfg);
	}
	else if (m_strEngineProgID == STT_IOT_PP_TYPE_MmsEngine) //原先为_T("PpMmsEngine.PoEngine")
	{
		SaveDevInfoToCfg_MMS(pCommCfg);
	}
	else if (m_strEngineProgID == STT_IOT_PP_TYPE_PpEngine) //原先为_T("PpEngine.PoEngine") zhouhj 2023.12.6
	{
		SaveDevInfoToCfg_PpEngine(pCommCfg);
	}

	return pCommCfg;
}

void CGbSmartGenWzd::SaveDevInfoToCfg_MMS(CPpSttCommConfig *pCommCfg)
{
	//以下是PpMmsEngine需要用到的配置文件
	CString strName = GetFileTitleFromFilePath(m_strDvmFile, '/');
	CMMS_STACK_CFG oMMS_STACK_CFG;
	oMMS_STACK_CFG.Open_MMS_STACK_CFG_Outer();
	CStkCfg_RemoteAddressList *pRemoteAddressList = oMMS_STACK_CFG.GetRemoteAddressList();
	long nIndex = 0;
	pRemoteAddressList->SetCount(1);
	CStkCfg_RemoteAddress *pAddress = (CStkCfg_RemoteAddress *)pRemoteAddressList->GetAtIndex(0);
	pAddress->SetIP(m_strDevIP);
	pAddress->m_strModel = strName;

	oMMS_STACK_CFG.Save_MMS_STACK_CFG_Outer();
	oMMS_STACK_CFG.WriteIpToVMDFile();

	//以下是规约后台用到的对象
	if (pCommCfg == NULL)
	{
		CPpSttCommConfig oCommCfg;
		pCommCfg = &oCommCfg;
	}

	pCommCfg->InitEngine(strName, STT_IOT_PP_TYPE_MmsEngine, m_strPpFile, m_strDvmFile);
	pCommCfg->MMS_Init(m_strLocalIP, m_strDevIP, m_nDevPort, "", "");
}


void CGbSmartGenWzd::SaveDevInfoToCfg_CMS(CPpSttCommConfig *pCommCfg)
{
	//以下是DltEngine需要用到的配置文件
	CString strName = GetFileTitleFromFilePath(m_strDvmFile, '/');
	CString strPath;
	strPath = _P_GetInstallPath();
	strPath += _T("e-Protocol\\Config\\");    //需要将DltEngine.exe的工作目录，与PpMmsEngine一致。这样，模型文件的路径好固定下来
	strPath += _T("860ClientConfig.xml");
	C61850ClientConfig o61850ClientConfig;

	if (o61850ClientConfig.OpenClientConfg(strPath))
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("配置文件(%s)打开成功."),strPath.GetString());
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("配置文件(%s)打开失败."),strPath.GetString());
		return;
	}

	CRemoteDev *pRemoteDev = o61850ClientConfig.GetRemoteDev(0);
	pRemoteDev->m_strIP = m_strDevIP;
	pRemoteDev->m_strName = strName;
	o61850ClientConfig.SaveClientConfg();

	if (pCommCfg == NULL)
	{
		CPpSttCommConfig oCommCfg;
		pCommCfg = &oCommCfg;
	}
	//以下是规约后台用到的对象
	pCommCfg->InitEngine(strName, STT_IOT_PP_TYPE_CmsEngine, m_strPpFile, m_strDvmFile);
	pCommCfg->CMS_Init(m_strLocalIP, m_strDevIP, m_nDevPort, "", "");
}

void CGbSmartGenWzd::SaveDevInfoToCfg_PpEngine(CPpSttCommConfig *pCommCfg)
{
	CString strName = GetFileTitleFromFilePath(m_strDvmFile, '/');
	pCommCfg->InitEngine(strName, STT_IOT_PP_TYPE_PpEngine, m_strPpFile, m_strDvmFile);
	pCommCfg->PpEngineNet_Init(m_strLocalIP, m_strDevIP, m_nDevPort);//目前界面不支持串口模式,后续增加后,扩展,暂时只支持网口
}

void CGbSmartGenWzd::CreateNew()
{
	if (m_pGbItemsRootTree != NULL)
	{
		Remove(m_pGbItemsRootTree);
		m_pGbItemsRootTree->DeleteAll();
		DeleteAll();
		AddNewChild(m_pGbItemsRootTree);
	}
	else
	{
		m_pGbItemsRootTree = AddNewGroup(STT_CMD_PARA_GBITEMSTREE, STT_CMD_PARA_GBITEMSTREE, STT_CMD_PARA_GBITEMSTREE);
	}

	m_strSmartGenWzdFile.Empty();
}

void CGbSmartGenWzd::InitGbSmartGenWzd()
{
	stt_OpenCommCmdCfg();
	InitTestClass();
	InitProtocolEngine();
	CmdDelay_Init();

	//shaolei 2022-11-25 注释此处。每次新建向导，不打开原来的向导记录，向导记录直接覆盖
	//OpenSmartGenWzdFile(); //2022-11-4   lijunqing open default wzd file

	//2023-1-28  lijunqing 读取属性，OpenSmartGenWzdFile与OpenSmartGenWzdFileForAttr二选一
	OpenSmartGenWzdFileForAttr();

	//2023-2-28  lijunqing
	SaveDevInfoToCfg();
}

void CGbSmartGenWzd::InitTestClass()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("commcmd-wzd-cfg.xml");

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_pTestClass->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void CGbSmartGenWzd::stt_OpenCommCmdCfg()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("SttCommCmdCfg.xml");

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_pCommCmdCfg->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}


CString CGbSmartGenWzd::InitDvmDevice(const CString &strFile)
{
	m_pDvmDevice->DeleteAll();
	CString strFolderPath;

	if (! IsFileExist(strFile))
	{
		if (strFile.Find(_T("/")) < 0)
		{
			strFolderPath = _P_GetInstallPath();
			strFolderPath += _T("e-Protocol/Library/");
			strFolderPath += strFile;
		}
		else
		{
			strFolderPath = strFile;
		}
	}
	else
	{
		strFolderPath = strFile;
	}

	if (m_pDvmDevice->OpenXmlFile(strFolderPath, CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		m_pDvmDevice->m_strID = strFolderPath;
		m_pDvmDevice->m_strName = GetPathFileNameFromFilePathName(strFolderPath);
	}

	if (m_strDevIP.GetLength() > 0)
	{
		m_pDvmDevice->m_strName.AppendFormat(_T(" - %s"), m_strDevIP.GetString());
	}

	return strFolderPath;
}


CDvmDataset* CGbSmartGenWzd::FindDatasetByPath(const CString &strPath)
{
	CExBaseList oList;
	CString strDatasetPath = strPath;

	long nCount = m_pDvmDevice->FindByPathChildren(strDatasetPath, oList, '$');

	if (nCount > 0)
	{
		CDvmDataset *pFind = (CDvmDataset *)oList.GetHead();
		oList.RemoveAll();

		return pFind;
	}

	return NULL;
}

//重新导入模型
CString CGbSmartGenWzd::ImportDvmFile(const CString &strFile)
{
	CString strDvmFile = InitDvmDevice(strFile);
	m_strDvmFile = strDvmFile;
	SaveDevInfoToCfg();   //导入模型后，重新保存相关参数

	return strDvmFile;
}

//导入模型后，清理跟commcmd相关的记录
//清理后，导入模型重新添加的通讯命令，都通过commcmd-update去处理
void CGbSmartGenWzd::AfterImportDvmFile()
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_GBMACROGENWZD)
		{
			CGbMacroGenWzd* pMacroGenWzd = (CGbMacroGenWzd*)pObj;
			pMacroGenWzd->ClearAllCmdGenParas();
		}
		else if (nClassID == DVMCLASSID_GBWZDCOMMCMDADD)
		{
			Delete(pObj);
		}	
		else if (nClassID == DVMCLASSID_GBWZDCOMMCMDUPDATE)
		{
			Delete(pObj);
		}	
		else if (nClassID == DVMCLASSID_GBWZDCOMMCMDADDGRP)
		{
			//导入模型后，若需要重新执行添加测试前、后组合。已经是在新模型上添加了。因此可以不用处理
			//CGbWzdCommCmdAddGrp *pCommCmdAddGrp = (CGbWzdCommCmdAddGrp *)pObj;
			//pCommCmdAddGrp->m_nAddCommCmd = 0;  //只保留分类项目，删除通讯命令
		}
	}
}

CGbMacroGenWzd* CGbSmartGenWzd::NewGbMacroGenWzd()
{
	if (m_pGbMacroGenWzdInit == NULL)
	{
		m_pGbMacroGenWzdInit = new CGbMacroGenWzd();
		m_pGbMacroGenWzdInit->DeleteAll();
		m_pGbMacroGenWzdInit->OpenInitXmlFile();
	}

	m_pCurrGbMacroGenWzd = new CGbMacroGenWzd();
	AddNewChild(m_pCurrGbMacroGenWzd);

	//2022-10-4  lijunqing 根据默认对象初始化当前向导步
	m_pCurrGbMacroGenWzd->InitGbMacroGenWzd(m_pGbMacroGenWzdInit);

	return m_pCurrGbMacroGenWzd;
}

void CGbSmartGenWzd::CancelMacroGenWzd()
{
	ASSERT (m_pCurrGbMacroGenWzd != NULL);
	Delete(m_pCurrGbMacroGenWzd);
	m_pCurrGbMacroGenWzd = NULL;
}

void CGbSmartGenWzd::OpenSmartGenWzdFile()
{
	CString strFile = GetDefaultSmartGenWzdFile();

	OpenSmartGenWzdFile(strFile);
}

void CGbSmartGenWzd::OpenSmartGenWzdFileForAttr()
{
	CString strFile = GetDefaultSmartGenWzdFile();
	m_bOwnAttrOnly = TRUE;

	//2023-1-28  李俊庆 不调用OpenSmartGenWzdFile，只读取属性数据
	CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_nIsGroupUseDvmData++;
	OpenXmlFile(strFile, CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys);
	CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_nIsGroupUseDvmData--;

	m_bOwnAttrOnly = FALSE;

	//默认打开模型文件
	InitDvmDevice(m_strDvmFile);
}

void CGbSmartGenWzd::OpenSmartGenWzdFile(const CString &strFile)
{
	if (! IsFileExist(strFile))
	{
		return;
	}

	DeleteAll();
	InitWzd();

	//CreateNew();
	CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_nIsGroupUseDvmData++;
	OpenXmlFile(strFile, CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys);
	CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_nIsGroupUseDvmData--;

	m_strSmartGenWzdFile = strFile;

	//打开向导文件后，加载模型文件
	InitDvmDevice(m_strDvmFile);

	//打开向导文件后，加载通讯参数到m_oCommConfig
	SaveDevInfoToCfg();
}

void CGbSmartGenWzd::SaveSmartGenWzdFile(const CString &strFile)
{
	CGbSmartGenWzdXmlRWKeys::IncXmlOnlyWrite_Id_Value(CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys);
	SaveXmlFile(strFile, CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys);
	CGbSmartGenWzdXmlRWKeys::DecXmlOnlyWrite_Id_Value(CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys);
}

void CGbSmartGenWzd::SaveSmartGenWzdFile()
{
	CString strFile = GetDefaultSmartGenWzdFile();

	if (m_strSmartGenWzdFile.IsEmpty())
	{
		SaveSmartGenWzdFile(strFile);
	}
	else
	{
		SaveSmartGenWzdFile(m_strSmartGenWzdFile);
	}
}

CString CGbSmartGenWzd::GetDefaultSmartGenWzdFile()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("SmartGenWzd.");
	strFile += GbSmartGenWzd_File_Postfix;

	return strFile;
}

//测试项目分类数据树  编辑
void CGbSmartGenWzd::NewItems(const CString &strParentPath, CExBaseObject *pItems)
{
	CDataGroup *pParent = GetParentItems(strParentPath);

	if (pParent == NULL)
	{
		return;
	}

	pParent->AddNewGroup(pItems->m_strName, pItems->m_strID, STT_CMD_PARA_generate_items_items);
}

void CGbSmartGenWzd::EditItems(const CString &strParentPath, const CString &strItemsID, const CString &strItemsName
							   , CExBaseObject *pItems, long nRepeatTimes, long nRptTitle, long nTitleLevel)
{
// 	UINT nClassID = pItems->GetClassID();
// 
// 	if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
// 	{
// 		CGbWzdCommCmdAdd *pCommCmdAdd = (CGbWzdCommCmdAdd*)FindXItemBase(pItems->m_strID, strPath);
// 	}

	CDataGroup *pParent = GetParentItems(strParentPath);

	if (pParent != NULL)
	{
		CDataGroup *pFind = (CDataGroup*)pParent->FindByID(strItemsID);

		if (pFind != NULL)
		{
			pFind->m_strName = pItems->m_strName;
			pFind->m_strID = pItems->m_strID;
		}
	}
	//以上是处理gb-item-tree的

	CGbWzdXItemBase* pBase = FindXItemBase(strItemsID, strParentPath);

	if (pBase != NULL)
	{
		if (pBase->GetClassID() == DVMCLASSID_GBWZDITEMSADD)
		{
			CGbWzdItemsAdd *pItemsAdd = (CGbWzdItemsAdd *)pBase;
			pItemsAdd->m_strItemsName = pItems->m_strName;
			pItemsAdd->m_strItemsID = pItems->m_strID;
			pItemsAdd->m_nRepeatTimes = nRepeatTimes;
			pItemsAdd->m_nRptTitle = nRptTitle;
			pItemsAdd->m_nTitleLevel = nTitleLevel;
		}
		else if (pBase->GetClassID() == DVMCLASSID_GBWZDITEMEDIT)
		{
			CGbWzdItemEdit *pItemEdit = (CGbWzdItemEdit *)pBase;

			pItemEdit->m_strItemsName = pItems->m_strName;
			pItemEdit->m_strItemsID = pItems->m_strID;
			pItemEdit->m_nRepeatTimes = nRepeatTimes;
			pItemEdit->m_nRptTitle = nRptTitle;
			pItemEdit->m_nTitleLevel = nTitleLevel;
		}
		else if (pBase->GetClassID() == DVMCLASSID_GBWZDCOMMCMDADD)
		{
			CGbWzdCommCmdAdd *pCommCmdAdd = (CGbWzdCommCmdAdd *)pBase;
			pCommCmdAdd->m_strItemsName = pItems->m_strName;
			pCommCmdAdd->m_strItemsID = pItems->m_strID;
		}
		else if(pBase->GetClassID() == DVMCLASSID_GBWZDMACROTESTADD)
		{
			CGbWzdMacroTestAdd *pMacroTestAdd = (CGbWzdMacroTestAdd *)pBase;
			pMacroTestAdd->m_strItemsName = pItems->m_strName;
			pMacroTestAdd->m_strItemsID = pItems->m_strID;
		}
	}
	else
	{
		CGbMacroGenWzd* pMacroGen = FindMacroGen(strItemsID, strItemsName, strParentPath);

		if (pMacroGen != NULL)
		{
			pMacroGen->m_strItemsName = pItems->m_strName;
			pMacroGen->m_strItemsID = pItems->m_strID;
			pMacroGen->m_nRepeatTimes = nRepeatTimes;
			pMacroGen->m_nRptTitle = nRptTitle;
			pMacroGen->m_nTitleLevel = nTitleLevel;
		}
		else
		{
			CGbWzdItemEdit *pItemEdit = new CGbWzdItemEdit();
			pItemEdit->m_strParentItemsID = strParentPath;
			pItemEdit->m_strItemsName = pItems->m_strName;
			pItemEdit->m_strItemsID = pItems->m_strID;
			pItemEdit->m_strItemsID_Old = strItemsID;
			pItemEdit->m_nRepeatTimes = nRepeatTimes;
			pItemEdit->m_nRptTitle = nRptTitle;
			pItemEdit->m_nTitleLevel = nTitleLevel;
			AddNewChild(pItemEdit);
		}
	}

	//当被编辑的项目，就是被复制的项目时，更新被复制的项目指针
	if (m_pCurrItemCopy != NULL)
	{
		if (strItemsID == m_pCurrItemCopy->m_strItemsID
			&& strParentPath == m_pCurrItemCopy->m_strParentItemsID)
		{
			m_pCurrItemCopy->m_strItemsID = pItems->m_strID;
			m_pCurrItemCopy->m_strItemsName = pItems->m_strName;
		}
	}

	//SaveSmartGenWzdFile();
}

void CGbSmartGenWzd::DeleteItems(const CString &strParentPath, CExBaseObject *pItems)
{
	//从m_pGbItemsRootTree中删除模板项目结构
	CDataGroup *pParent = GetParentItems(strParentPath);

	if (pParent != NULL)
	{
		CDataGroup *pFind = (CDataGroup*)pParent->FindByID(pItems->m_strID);

		if (pFind != NULL)
		{
			pParent->Delete(pFind);
		}
	}
		
	//当被删除的项目，就是被复制的项目时，清空被复制的项目
	if (m_pCurrItemCopy != NULL)
	{
		if (pItems->m_strID == m_pCurrItemCopy->m_strItemsID
			&& strParentPath == m_pCurrItemCopy->m_strParentItemsID)
		{
			delete m_pCurrItemCopy;
			m_pCurrItemCopy = NULL;
		}
	}

	//先删除同项目的SetItemState
	CGbWzdItemSetState *pItemSetState = FindItemSetState(pItems->m_strID, strParentPath);

	if (pItemSetState != NULL)
	{
		Delete(pItemSetState);
	}

	//删除此目录下的向导
	UINT nClassID = pItems->GetClassID();

	if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{
		CSttItems *pSttItems = (CSttItems *)pItems;
		DeleteItems_SttItems(strParentPath, pSttItems);
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		CSttCommCmd *pSttCommCmd = (CSttCommCmd *)pItems;
		DeleteItems_SttCommCmd(strParentPath, pSttCommCmd);
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		CSttMacroTest *pSttMacroTest = (CSttMacroTest *)pItems;
		DeleteItems_SttMacroTest(strParentPath, pSttMacroTest);
	}

	//SaveSmartGenWzdFile();

// 	POS pos = GetHeadPosition();
// 	POS posPrev = NULL;
// 	CGbMacroGenWzd *pMacroWzd = NULL;
// 	CString strPath = strParentPath + _T("$") + pItems->m_strID;
// 	CString strPath2 = strPath + _T("$") ;
// 	long nLen = strPath2.GetLength();
// 
// 	if (pos == NULL)
// 	{
// 		return;
// 	}
// 
// 	GetNext(pos);
// 
// 	while (pos != NULL)
// 	{
// 		posPrev = pos;
// 		pMacroWzd = (CGbMacroGenWzd *)GetNext(pos);
// 
// 		if (pMacroWzd->GetClassID() != DVMCLASSID_GBMACROGENWZD)
// 		{
// 			continue;
// 		}
// 
// 		if (pMacroWzd->m_strParentItemsID == strPath)
// 		{
// 			DeleteAt(posPrev);
// 			continue;
// 		}
// 
// 		if (pMacroWzd->m_strParentItemsID.Left(nLen) == strPath2)
// 		{
// 			DeleteAt(posPrev);
// 		}
// 	}
}

void CGbSmartGenWzd::DeleteItems_SttItems(const CString &strParentPath, CSttItems *pSttItems)
{
	CSttItems *pRootNode = NULL;
	CGbMacroGenWzd *pMacroGenWzd = NULL;
	CString strRootNodePath;

	if (pSttItems->IsTypeRootNode())
	{
		pMacroGenWzd = FindMacroGen(pSttItems->m_strID, pSttItems->m_strName, strParentPath);

		if (pMacroGenWzd != NULL)
		{
			Delete(pMacroGenWzd);
		}
	}
	else if (pSttItems->m_strID == STT_CMD_PARA_Before_Test || pSttItems->m_strID == STT_CMD_PARA_After_Test)
	{
		pRootNode = Stt_GetFirstParentItems(pSttItems, GBITEMS_NODETYPE_ROOTNODE, TRUE);

		if (pRootNode != NULL)
		{
			CExBaseList *pParent = (CExBaseList*)pRootNode->GetParent();
			strRootNodePath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);  //找到父项目，并获取父项目的项目路径
			pMacroGenWzd = FindMacroGen(pRootNode->m_strID, pRootNode->m_strName, strRootNodePath);

			if (pMacroGenWzd != NULL)
			{
				pMacroGenWzd->m_pCmdGenParas->DeleteByID(pSttItems->m_strID);
			}
		}
	}

	if(pSttItems->IsTypeItems())
	{
		//对于项目树中，由人工创建的分类
		CGbWzdItemsAdd* pItemsAdd = (CGbWzdItemsAdd*)FindXItemBase(pSttItems->m_strID, strParentPath);

		if (pItemsAdd != NULL)
		{
			Delete(pItemsAdd);
		}
	}

	//应当判断该项目下是否有commcmd-add、macrotest-add和item-setstate
	DeleteItems_SttItems(pSttItems);
}

void CGbSmartGenWzd::DeleteItems_SttItems(CSttItems *pSttItems)
{
	CString strParentPath = pSttItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	POS pos = g_theGbSmartGenWzd->GetHeadPosition();
	CExBaseObject *pChild = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pChild = g_theGbSmartGenWzd->GetNext(pos);
		nClassID = pChild->GetClassID();

		if (nClassID == DVMCLASSID_GBMACROGENWZD)
		{
			CGbMacroGenWzd* pMacroGenWzd = (CGbMacroGenWzd *)pChild;
			long nPos = pMacroGenWzd->m_strParentItemsID.Find(strParentPath);

			if (nPos == 0)
			{
				//如果是当前CSttItems下的子项目。则pMacroGenWzd的父项目路径的第一级，必然是当前CSttItems的路径
				g_theGbSmartGenWzd->Delete(pMacroGenWzd);
			}
		}
		else if (nClassID == DVMCLASSID_GBWZDCOMMCMDADD)
		{
			CGbWzdCommCmdAdd *pCommCmdAdd = (CGbWzdCommCmdAdd *)pChild;
			long nPos = pCommCmdAdd->m_strParentItemsID.Find(strParentPath);

			if (nPos == 0)
			{
				//如果是当前CSttItems下的子项目。则pMacroTestAdd的父项目路径的第一级，必然是当前CSttItems的路径
				g_theGbSmartGenWzd->Delete(pCommCmdAdd);
			}
		}
		else if (nClassID == DVMCLASSID_GBWZDMACROTESTADD)
		{
			CGbWzdMacroTestAdd *pMacroTestAdd = (CGbWzdMacroTestAdd *)pChild;
			long nPos = pMacroTestAdd->m_strParentItemsID.Find(strParentPath);

			if (nPos == 0)
			{
				//如果是当前CSttItems下的子项目。则pMacroTestAdd的父项目路径的第一级，必然是当前CSttItems的路径
				g_theGbSmartGenWzd->Delete(pMacroTestAdd);
			}
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMSETSTATE)
		{
			CGbWzdItemSetState *pItemSetState = (CGbWzdItemSetState *)pChild;
			long nPos = pItemSetState->m_strParentItemsID.Find(strParentPath);

			if (nPos == 0)
			{
				//如果是当前CSttItems下的子项目。则pItemSetState的父项目路径的第一级，必然是当前CSttItems的路径
				g_theGbSmartGenWzd->Delete(pItemSetState);
			}
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMSADD)
		{
			CGbWzdItemsAdd *pItemsAdd = (CGbWzdItemsAdd *)pChild;
			long nPos = pItemsAdd->m_strParentItemsID.Find(strParentPath);

			if (nPos == 0)
			{
				//如果是当前CSttItems下的子项目。则pItemsAdd的父项目路径的第一级，必然是当前CSttItems的路径
				g_theGbSmartGenWzd->Delete(pItemsAdd);
			}
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMEDIT)
		{
			CGbWzdItemEdit *pItemEdit = (CGbWzdItemEdit *)pChild;
			long nPos = pItemEdit->m_strParentItemsID.Find(strParentPath);

			if (nPos == 0)
			{
				//如果是当前CSttItems下的子项目。则pItemEdit的父项目路径的第一级，必然是当前CSttItems的路径
				g_theGbSmartGenWzd->Delete(pItemEdit);
			}
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMMOVE)
		{
			CGbWzdItemMove *pItemMove = (CGbWzdItemMove *)pChild;
			long nPos = pItemMove->m_strParentItemsID.Find(strParentPath);

			if (nPos == 0)
			{
				//如果是当前CSttItems下的子项目。则pItemMove的父项目路径的第一级，必然是当前CSttItems的路径
				g_theGbSmartGenWzd->Delete(pItemMove);
			}
		}
		else if (nClassID == DVMCLASSID_GBWZDSAFETYADD)
		{
			CGbWzdSafetyAdd *pSafetyAdd = (CGbWzdSafetyAdd *)pChild;
			long nPos = pSafetyAdd->m_strParentItemsID.Find(strParentPath);

			if (nPos == 0)
			{
				//如果是当前CSttItems下的子项目。则pItemMove的父项目路径的第一级，必然是当前CSttItems的路径
				g_theGbSmartGenWzd->Delete(pSafetyAdd);
			}
		}	
		else if (nClassID == DVMCLASSID_GBWZDCOMMCMDUPDATE)
		{
			CGbWzdCommCmdUpdate *pCommCmdUpdate = (CGbWzdCommCmdUpdate *)pChild;
			long nPos = pCommCmdUpdate->m_strParentItemsID.Find(strParentPath);

			if (nPos == 0)
			{
				//如果是当前CSttItems下的子项目。则pItemMove的父项目路径的第一级，必然是当前CSttItems的路径
				g_theGbSmartGenWzd->Delete(pCommCmdUpdate);
			}
		}
		else if (nClassID == DVMCLASSID_GBWZDCOMMCMDADDGRP)
		{
			CGbWzdCommCmdAddGrp *pCommCmdAddGrp = (CGbWzdCommCmdAddGrp *)pChild;
			long nPos = pCommCmdAddGrp->m_strParentItemsID.Find(strParentPath);

			if (nPos == 0)
			{
				//如果是当前CSttItems下的子项目。则pItemMove的父项目路径的第一级，必然是当前CSttItems的路径
				g_theGbSmartGenWzd->Delete(pCommCmdAddGrp);
			}
		}
	}
}

/*
<?xml version="1.0" encoding="UTF-8"?>
<?xml version="1.0" encoding="UTF-8"?>
<group id="cmd-gen-paras" data-type="cmd-gen-paras" value="">
	<group id="_BeforeTest_" data-type="" value="">
		<group id="ReadSetting" data-type="read" value="">
			<group id="PE1102PROT$LLN0$dsSetting1" data-type="" value="" />【读指令，多个数据集】
			<group id="PE1102PROT$LLN0$dsSetting2" data-type="" value="" />
			<data id="zone-index" data-type="long" value="0"/>
		</group>
		<group id="WriteEna" data-type="write" value="">【写指令，通讯命令对应的group】
			<group id="PE1102LD0$LLN0$dsRelayEna" data-type="" value="">
				<data id="GGIO1$ST$SPCSO1" data-type="STRUCT" value="1"/>
			</group>
			<data id="delaybeforecmd" data-type="string" value="0"/>
			<data id="delayaftercmd" data-type="string" value="0"/>
		</group>
		<group id="WriteEna" data-type="write" value="">   【多个数据集，就有多个同ID的group】
			<group id="PE1102PROT$LLN0$dsRelayEna3" data-type="" value="">
				<data id="GGIO8$ST$SPCSO1" data-type="STRUCT" value="0"/>
			</group>
			<data id="delaybeforecmd" data-type="string" value="0"/>
			<data id="delayaftercmd" data-type="string" value="0"/>
		</group>
		<group id="ReadParameter" data-type="read" value="">
			<group id="PE1102PROT$LLN0$dsParameter" data-type="" value=""/>
			<group id="PE1102MEAS$LLN0$dsParameter" data-type="" value=""/>
		</group>
	</group>
	<group id="_AfterTest_" data-type="" value="">
		<group id="WriteSetting" data-type="write" value="">
			<group id="PE1102PROT$LLN0$dsSetting" data-type="" value="">
				<data id="LLN0$SG$DPFCStr" data-type="STRUCT" value="0.500000"/>
			</group>
			<data id="zone-index" data-type="long" value="0"/>
			<data id="delaybeforecmd" data-type="string" value="0"/>
			<data id="delayaftercmd" data-type="string" value="0"/>
		</group>
	</group>
</group>
*/
/*//添加通讯命令的方式有很多中：
1、单独添加的：CGbWzdCommCmdAdd
2、通过向导添加的：CGbMacroGenWzd
3、通过“测试前、后通讯组合”添加的：CGbWzdCommCmdAddGrp
4、通过“导入模型（模型替换）”添加的：CGbWzdCommCmdUpdate【导入模型后，原来添加的通讯命令会被删除，底层新增通讯命令，采用commcmd-update更新的】
*/
void CGbSmartGenWzd::DeleteItems_SttCommCmd(const CString &strParentPath, CSttCommCmd *pSttCommCmd)
{
	CExBaseList* pParent = (CExBaseList*)pSttCommCmd->GetParent();
	CString strPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	CGbWzdXItemBase* pBase = FindXItemBase(pSttCommCmd->m_strID, strPath);

	if (pBase != NULL)
	{
		if (pBase->GetClassID() == DVMCLASSID_GBWZDCOMMCMDADD)
		{
			CGbWzdCommCmdAdd *pCommCmdAdd = (CGbWzdCommCmdAdd *)pBase;
			//通信命令是单独添加的通信命令，不是通过向导添加的
			Delete(pCommCmdAdd);
			return;
		}
	}

	CGbWzdCommCmdUpdate* pCommCmdUpdate = FindCommCmdUpdate(pSttCommCmd->m_strID, strPath);

	if (pCommCmdUpdate != NULL)
	{
		Delete(pCommCmdUpdate);
		return;
	}

	//通讯命令是通过向导添加的
	BOOL bWzd = FALSE;
	CDataGroup *pGrp = IsCommCmdAddByWzd(strParentPath, pSttCommCmd, bWzd);
	
	if (bWzd && pGrp != NULL)
	{
		DeleteItems_SttCommCmd_Wzd(pSttCommCmd, pGrp);
		return;
	}

	//通过“测试前、后通讯组合”添加的：CGbWzdCommCmdAddGrp
	ItemsDelete(strParentPath, pSttCommCmd->m_strID, pSttCommCmd->m_strName);
}

void CGbSmartGenWzd::DeleteItems_SttCommCmd_Wzd(CSttCommCmd *pSttCommCmd, CDataGroup *pGrp)
{
	CDataGroup *pCmdGrp = NULL;   //通讯命令对应的group
	CExBaseList oList;
	long nCount = pGrp->QueryByID(pSttCommCmd->m_strCommCmdID, oList);

	if (nCount == 1)
	{
		pCmdGrp = (CDataGroup *)oList.GetHead();

		if (pCmdGrp->m_strDataType == COMMCMD_RWOPTR_WRITE)
		{
			//对于写指令，删除整个通讯命令对应的group
			pGrp->Delete(pCmdGrp);
		}
		else
		{
			//对于读指令，删除通讯命令下对应数据集的group
			CSttCommCmdData *pCmdData = pSttCommCmd->GetCommCmdData(FALSE);

			if (pCmdData != NULL)
			{
				pCmdGrp->DeleteByID(pCmdData->m_strDatasetPath);
			}

			if (pCmdGrp->GetCount() == 0)
			{
				pGrp->Delete(pCmdGrp);
			}
		}
	}
	else
	{
		//对于多个数据集，需要根据数据集路径去判断。例如WriteEna
		POS pos = oList.GetHeadPosition();

		while (pos != NULL)
		{
			pCmdGrp = (CDataGroup *)oList.GetNext(pos);
			CSttCommCmdData *pCmdData = pSttCommCmd->GetCommCmdData(FALSE);

			if (pCmdData != NULL)
			{
				CExBaseObject *pDsGrp = pCmdGrp->FindByID(pCmdData->m_strDatasetPath);

				if (pDsGrp != NULL)
				{
					if (pDsGrp->GetClassID() == DTMCLASSID_CDATAGROUP)
					{
						pGrp->Delete(pCmdGrp);
						break;
					}
				}
			}
		}
	}

	oList.RemoveAll();
}

void CGbSmartGenWzd::DeleteItems_SttMacroTest(const CString &strParentPath, CSttMacroTest *pSttMacroTest)
{
	CExBaseList* pParent = (CExBaseList*)pSttMacroTest->GetParent();
	CString strPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	CGbWzdMacroTestAdd* pMacroTestAdd = (CGbWzdMacroTestAdd*)FindXItemBase(pSttMacroTest->m_strID, strPath);

	if (pMacroTestAdd != NULL)
	{
		//电气量项目是单独添加
		Delete(pMacroTestAdd);
		return;
	}
}

//项目移动，上移和下移可以相互抵消，所以向导中最多存在一个项目的移动记录，记录了该项目移动的方向和次数
void CGbSmartGenWzd::MoveItem(const CString &strParentPath, CExBaseObject *pItem, const CString &strMoveType)
{
	CGbWzdItemMove *pMove = FindItemMove(pItem->m_strID, strParentPath);

	if (pMove == NULL)
	{
		pMove = new CGbWzdItemMove();
		pMove->m_strItemsID = pItem->m_strID;
		pMove->m_strItemsName = pItem->m_strName;
		pMove->m_strMoveType = strMoveType;
		pMove->m_nMoveTimes = 1;
		pMove->m_strParentItemsID = strParentPath;
		AddNewChild(pMove);
		return;
	}

	if (pMove->m_strMoveType == strMoveType)
	{
		//已经存在的移动记录和本次移动方向一致的，直接将移动次数 +1
		pMove->m_nMoveTimes += 1;
		return;
	}

	//已经存在的移动记录和本次移动方向不一致的，移动次数 -1
	pMove->m_nMoveTimes -= 1;

	if (pMove->m_nMoveTimes <= 0)
	{
		//当移动次数小于等于0时，说明两次移动相互抵消。此时删除移动记录
		Delete(pMove);
	}
}

void CGbSmartGenWzd::ItemPaste(const CString &strDestParentPath, CExBaseObject *pDestItem)
{
	if (m_pCurrItemCopy == NULL)
	{
		return;
	}

	CGbWzdItemPaste *pPaste = new CGbWzdItemPaste();
	AddNewChild(pPaste);
	
	pPaste->m_strSrcParentItemsID = m_pCurrItemCopy->m_strParentItemsID;
	pPaste->m_strSrcItemsName = m_pCurrItemCopy->m_strItemsName;
	pPaste->m_strSrcItemsID = m_pCurrItemCopy->m_strItemsID;
	pPaste->m_strItemType = m_pCurrItemCopy->m_strItemType;
	pPaste->m_strDestParentItemsID = strDestParentPath;
	pPaste->m_strDestItemsID = pDestItem->m_strID;
	pPaste->m_strDestItemsName = pDestItem->m_strName;

	//处理粘贴后，对于源项目的其它操作。需要一并复制。例如：项目名称编辑、新增通讯命令等
	AfterItemPaste(m_pCurrItemCopy, pPaste);
}

//项目复制：目前只针对rootnode
//项目粘贴：目前只在CDevice节点和人工创建的CItems可以粘贴
void CGbSmartGenWzd::AfterItemPaste(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CExBaseList oNewList;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_GBMACROGENWZD)
		{
			CGbMacroGenWzd* pMacroGenWzd = (CGbMacroGenWzd *)pObj;
			AfterItemPaste_MacroGenWzd(pCopy, pPaste, pMacroGenWzd, &oNewList);
		}
		else if (nClassID == DVMCLASSID_GBWZDCOMMCMDADD)
		{
			CGbWzdCommCmdAdd *pCommCmdAdd = (CGbWzdCommCmdAdd *)pObj;
			AfterItemPaste_CommCmdAdd(pCopy, pPaste, pCommCmdAdd, &oNewList);
		}
		else if (nClassID == DVMCLASSID_GBWZDMACROTESTADD)
		{
			CGbWzdMacroTestAdd *pMacroTestAdd = (CGbWzdMacroTestAdd *)pObj;
			AfterItemPaste_MacroTestAdd(pCopy, pPaste, pMacroTestAdd, &oNewList);
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMSADD)
		{
			CGbWzdItemsAdd *pItemsAdd = (CGbWzdItemsAdd *)pObj;
			AfterItemPaste_ItemsAdd(pCopy, pPaste, pItemsAdd, &oNewList);
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMEDIT)
		{
			CGbWzdItemEdit *pItemEdit = (CGbWzdItemEdit *)pObj;
			AfterItemPaste_ItemEdit(pCopy, pPaste, pItemEdit, &oNewList);
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMMOVE)
		{
			CGbWzdItemMove *pItemMove = (CGbWzdItemMove *)pObj;
			AfterItemPaste_ItemMove(pCopy, pPaste, pItemMove, &oNewList);
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMPASTE)
		{
			continue;
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMRSLTEXPREDIT)
		{
			continue;
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMSETSTATE)
		{
			CGbWzdItemSetState *pItemSetState = (CGbWzdItemSetState *)pObj;
			AfterItemPaste_ItemSetState(pCopy, pPaste, pItemSetState, &oNewList);
		}
		else if (nClassID == DVMCLASSID_GBWZDSAFETYADD)
		{
			CGbWzdSafetyAdd *pSafetyAdd = (CGbWzdSafetyAdd *)pObj;
			AfterItemPaste_SafetyAdd(pCopy, pPaste, pSafetyAdd, &oNewList);
		}	
		else if (nClassID == DVMCLASSID_GBWZDCOMMCMDUPDATE)
		{
			CGbWzdCommCmdUpdate *pCommCmdUpdate = (CGbWzdCommCmdUpdate *)pObj;
			AfterItemPaste_CommCmdUpdate(pCopy, pPaste, pCommCmdUpdate, &oNewList);
		}
		else if (nClassID == DVMCLASSID_GBWZDCOMMCMDADDGRP)
		{
			CGbWzdCommCmdAddGrp *pCommCmdAddGrp = (CGbWzdCommCmdAddGrp *)pObj;
			AfterItemPaste_CommCmdAddGrp(pCopy, pPaste, pCommCmdAddGrp, &oNewList);
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMSDELETE)
		{
			CGbWzdItemsDelete *pItemsDelete = (CGbWzdItemsDelete *)pObj;
			AfterItemPaste_ItemsDelete(pCopy, pPaste, pItemsDelete, &oNewList);
		}
	}

	AppendEx(oNewList, TRUE);
	oNewList.RemoveAll();
}

void CGbSmartGenWzd::AfterItemPaste_MacroGenWzd(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbMacroGenWzd* pMacroGenWzd, CExBaseList *pList)
{
	if (pMacroGenWzd->m_strParentItemsID == pCopy->m_strParentItemsID
		&& pMacroGenWzd->m_strItemsID == pCopy->m_strItemsID)
	{
		CGbMacroGenWzd *pNew = (CGbMacroGenWzd *)pMacroGenWzd->CloneEx(TRUE, TRUE);
		pNew->InitAfterRead();

		pNew->m_strParentItemsID = pPaste->m_strDestParentItemsID;
		pNew->m_strItemsName = pPaste->m_strDestItemsName;
		pNew->m_strItemsID = pPaste->m_strDestItemsID;
		pList->AddTail(pNew);
	}
}

void CGbSmartGenWzd::AfterItemPaste_CommCmdAdd(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdCommCmdAdd *pCommCmdAdd, CExBaseList *pList)
{
	CString strSrcItemPath;
	pCopy->GetItemCopyPath(strSrcItemPath); //获取源项目的项目路径

	long nPos = pCommCmdAdd->m_strParentItemsID.Find(strSrcItemPath);

	if (nPos != 0)
	{
		//如果是源项目（被复制项目）下的子项目。则pCommCmdAdd的父项目路径的第一级，必然是源项目的ItemPath
		return;
	}

	CString strTemp = pCommCmdAdd->m_strParentItemsID.Mid(strSrcItemPath.GetLength());

	if (strTemp.GetLength() > 0)
	{
		//对于同一个路径下，多次粘贴。项目的ID是自动编号。过滤掉这种自动编号的项目
		if (strTemp.Left(1) != "$")
		{
			return;
		}
	}

	CString strSrc, strDestItemPath;
	//pCommCmdAdd->GetItemPath(strSrc);  //待处理的源路径
	strSrc = pCommCmdAdd->m_strParentItemsID;
	pPaste->GetDestItemPath(strDestItemPath);  //目标项目的路径
	long nXpos = strSrc.Find(strSrcItemPath);

	ASSERT(nXpos == 0);

	if (nXpos != 0)
	{
		return;
	}

	CString strRight = strSrc.Mid(strSrcItemPath.GetLength());
	CGbWzdCommCmdAdd *pNew = (CGbWzdCommCmdAdd *)pCommCmdAdd->CloneEx(TRUE, TRUE);
	pNew->InitAfterRead();
	pList->AddTail(pNew);
	pNew->m_strParentItemsID = strDestItemPath + strRight;	
}

void CGbSmartGenWzd::AfterItemPaste_MacroTestAdd(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdMacroTestAdd *pMacroTestAdd, CExBaseList *pList)
{
	CString strSrcItemPath;
	pCopy->GetItemCopyPath(strSrcItemPath); //获取源项目的项目路径

	long nPos = pMacroTestAdd->m_strParentItemsID.Find(strSrcItemPath);

	if (nPos != 0)
	{
		//如果是源项目（被复制项目）下的子项目。则pMacroTestAdd的父项目路径的第一级，必然是源项目的ItemPath
		return;
	}

	CString strTemp = pMacroTestAdd->m_strParentItemsID.Mid(strSrcItemPath.GetLength());

	if (strTemp.GetLength() > 0)
	{
		//对于同一个路径下，多次粘贴。项目的ID是自动编号。过滤掉这种自动编号的项目
		if (strTemp.Left(1) != "$")
		{
			return;
		}
	}

	CString strSrc, strDestItemPath;
	strSrc = pMacroTestAdd->m_strParentItemsID;
	pPaste->GetDestItemPath(strDestItemPath);  //目标项目的路径
	long nXpos = strSrc.Find(strSrcItemPath);

	ASSERT(nXpos == 0);

	if (nXpos != 0)
	{
		return;
	}

	CString strRight = strSrc.Mid(strSrcItemPath.GetLength());
	CGbWzdMacroTestAdd *pNew = (CGbWzdMacroTestAdd *)pMacroTestAdd->CloneEx(TRUE, TRUE);
	pNew->InitAfterRead();
	pList->AddTail(pNew);
	pNew->m_strParentItemsID = strDestItemPath + strRight;
}

void CGbSmartGenWzd::AfterItemPaste_ItemsAdd(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdItemsAdd *pItemsAdd, CExBaseList *pList)
{
	CString strSrcItemPath;
	pCopy->GetItemCopyPath(strSrcItemPath); //获取源项目的项目路径

	long nPos = pItemsAdd->m_strParentItemsID.Find(strSrcItemPath);

	if (nPos != 0)
	{
		//如果是源项目（被复制项目）下的子项目。则pItemsAdd的父项目路径的第一级，必然是源项目的ItemPath
		return;
	}

	CString strTemp = pItemsAdd->m_strParentItemsID.Mid(strSrcItemPath.GetLength());

	if (strTemp.GetLength() > 0)
	{
		//对于同一个路径下，多次粘贴。项目的ID是自动编号。过滤掉这种自动编号的项目
		if (strTemp.Left(1) != "$")
		{
			return;
		}
	}

	CString strSrc, strDestItemPath;
	strSrc = pItemsAdd->m_strParentItemsID;
	pPaste->GetDestItemPath(strDestItemPath);  //目标项目的路径
	long nXpos = strSrc.Find(strSrcItemPath);

	ASSERT(nXpos == 0);

	if (nXpos != 0)
	{
		return;
	}

	CString strRight = strSrc.Mid(strSrcItemPath.GetLength());
	CGbWzdItemsAdd *pNew = (CGbWzdItemsAdd *)pItemsAdd->CloneEx(TRUE, TRUE);
	pNew->InitAfterRead();
	pList->AddTail(pNew);
	pNew->m_strParentItemsID = strDestItemPath + strRight;
}

void CGbSmartGenWzd::AfterItemPaste_ItemEdit(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdItemEdit *pItemEdit, CExBaseList *pList)
{
	CString strSrcItemPath;
	pCopy->GetItemCopyPath(strSrcItemPath); //获取源项目的项目路径

	long nPos = pItemEdit->m_strParentItemsID.Find(strSrcItemPath);

	if (nPos != 0)
	{
		//如果是源项目（被复制项目）下的子项目。则pItemEdit的父项目路径的第一级，必然是源项目的ItemPath
		return;
	}

	CString strTemp = pItemEdit->m_strParentItemsID.Mid(strSrcItemPath.GetLength());

	if (strTemp.GetLength() > 0)
	{
		//对于同一个路径下，多次粘贴。项目的ID是自动编号。过滤掉这种自动编号的项目
		if (strTemp.Left(1) != "$")
		{
			return;
		}
	}

	CString strSrc, strDestItemPath;
	strSrc = pItemEdit->m_strParentItemsID;
	pPaste->GetDestItemPath(strDestItemPath);  //目标项目的路径
	long nXpos = strSrc.Find(strSrcItemPath);

	ASSERT(nXpos == 0);

	if (nXpos != 0)
	{
		return;
	}

	CString strRight = strSrc.Mid(strSrcItemPath.GetLength());
	CGbWzdItemEdit *pNew = (CGbWzdItemEdit *)pItemEdit->CloneEx(TRUE, TRUE);
	pNew->InitAfterRead();
	pList->AddTail(pNew);
	pNew->m_strParentItemsID = strDestItemPath + strRight;
}

void CGbSmartGenWzd::AfterItemPaste_ItemMove(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdItemMove *pItemMove, CExBaseList *pList)
{
	if (pItemMove->m_strParentItemsID == pCopy->m_strParentItemsID
		&& pItemMove->m_strItemsID == pCopy->m_strItemsID)
	{
		//被复制项目的移动，则不需要处理
		return;
	}

	CString strSrcItemPath;
	pCopy->GetItemCopyPath(strSrcItemPath); //获取源项目的项目路径

	long nPos = pItemMove->m_strParentItemsID.Find(strSrcItemPath);

	if (nPos != 0)
	{
		//如果是源项目（被复制项目）下的子项目。则pItemsAdd的父项目路径的第一级，必然是源项目的ItemPath
		return;
	}

	CString strTemp = pItemMove->m_strParentItemsID.Mid(strSrcItemPath.GetLength());

	if (strTemp.GetLength() > 0)
	{
		//对于同一个路径下，多次粘贴。项目的ID是自动编号。过滤掉这种自动编号的项目
		if (strTemp.Left(1) != "$")
		{
			return;
		}
	}

	CString strSrc, strDestItemPath;
	strSrc = pItemMove->m_strParentItemsID;
	pPaste->GetDestItemPath(strDestItemPath);  //目标项目的路径
	long nXpos = strSrc.Find(strSrcItemPath);

	ASSERT(nXpos == 0);

	if (nXpos != 0)
	{
		return;
	}

	CString strRight = strSrc.Mid(strSrcItemPath.GetLength());
	CGbWzdItemMove *pNew = (CGbWzdItemMove *)pItemMove->CloneEx(TRUE, TRUE);
	pNew->InitAfterRead();
	pList->AddTail(pNew);
	pNew->m_strParentItemsID = strDestItemPath + strRight;
}

void CGbSmartGenWzd::AfterItemPaste_ItemSetState(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdItemSetState *pItemSetState, CExBaseList *pList)
{
	CString strSrcItemPath;
	pCopy->GetItemCopyPath(strSrcItemPath); //获取源项目的项目路径

	long nPos = pItemSetState->m_strParentItemsID.Find(strSrcItemPath);

	if (nPos != 0)
	{
		//如果是源项目（被复制项目）下的子项目。则pItemEdit的父项目路径的第一级，必然是源项目的ItemPath
		return;
	}

	CString strTemp = pItemSetState->m_strParentItemsID.Mid(strSrcItemPath.GetLength());

	if (strTemp.GetLength() > 0)
	{
		//对于同一个路径下，多次粘贴。项目的ID是自动编号。过滤掉这种自动编号的项目
		if (strTemp.Left(1) != "$")
		{
			return;
		}
	}

	CString strSrc, strDestItemPath;
	strSrc = pItemSetState->m_strParentItemsID;
	pPaste->GetDestItemPath(strDestItemPath);  //目标项目的路径
	long nXpos = strSrc.Find(strSrcItemPath);

	ASSERT(nXpos == 0);

	if (nXpos != 0)
	{
		return;
	}

	CString strRight = strSrc.Mid(strSrcItemPath.GetLength());
	CGbWzdItemSetState *pNew = (CGbWzdItemSetState *)pItemSetState->CloneEx(TRUE, TRUE);
	pNew->InitAfterRead();
	pList->AddTail(pNew);
	pNew->m_strParentItemsID = strDestItemPath + strRight;
}

void CGbSmartGenWzd::AfterItemPaste_SafetyAdd(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdSafetyAdd *pSafetyAdd, CExBaseList *pList)
{
	CString strSrcItemPath;
	pCopy->GetItemCopyPath(strSrcItemPath); //获取源项目的项目路径

	long nPos = pSafetyAdd->m_strParentItemsID.Find(strSrcItemPath);

	if (nPos != 0)
	{
		//如果是源项目（被复制项目）下的子项目。则pItemsAdd的父项目路径的第一级，必然是源项目的ItemPath
		return;
	}

	CString strTemp = pSafetyAdd->m_strParentItemsID.Mid(strSrcItemPath.GetLength());

	if (strTemp.GetLength() > 0)
	{
		//对于同一个路径下，多次粘贴。项目的ID是自动编号。过滤掉这种自动编号的项目
		if (strTemp.Left(1) != "$")
		{
			return;
		}
	}

	CString strSrc, strDestItemPath;
	strSrc = pSafetyAdd->m_strParentItemsID;
	pPaste->GetDestItemPath(strDestItemPath);  //目标项目的路径
	long nXpos = strSrc.Find(strSrcItemPath);

	ASSERT(nXpos == 0);

	if (nXpos != 0)
	{
		return;
	}

	CString strRight = strSrc.Mid(strSrcItemPath.GetLength());
	CGbWzdSafetyAdd *pNew = (CGbWzdSafetyAdd *)pSafetyAdd->CloneEx(TRUE, TRUE);
	pNew->InitAfterRead();
	pList->AddTail(pNew);
	pNew->m_strParentItemsID = strDestItemPath + strRight;
}

void CGbSmartGenWzd::AfterItemPaste_CommCmdUpdate(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdCommCmdUpdate *pCommCmdUpdate, CExBaseList *pList)
{
	CString strSrcItemPath;
	pCopy->GetItemCopyPath(strSrcItemPath); //获取源项目的项目路径

	long nPos = pCommCmdUpdate->m_strParentItemsID.Find(strSrcItemPath);

	if (nPos != 0)
	{
		//如果是源项目（被复制项目）下的子项目。则pItemsAdd的父项目路径的第一级，必然是源项目的ItemPath
		return;
	}

	CString strTemp = pCommCmdUpdate->m_strParentItemsID.Mid(strSrcItemPath.GetLength());

	if (strTemp.GetLength() > 0)
	{
		//对于同一个路径下，多次粘贴。项目的ID是自动编号。过滤掉这种自动编号的项目
		if (strTemp.Left(1) != "$")
		{
			return;
		}
	}

	CString strSrc, strDestItemPath;
	strSrc = pCommCmdUpdate->m_strParentItemsID;
	pPaste->GetDestItemPath(strDestItemPath);  //目标项目的路径
	long nXpos = strSrc.Find(strSrcItemPath);

	ASSERT(nXpos == 0);

	if (nXpos != 0)
	{
		return;
	}

	CString strRight = strSrc.Mid(strSrcItemPath.GetLength());
	CGbWzdCommCmdUpdate *pNew = (CGbWzdCommCmdUpdate *)pCommCmdUpdate->CloneEx(TRUE, TRUE);
	pNew->InitAfterRead();
	pList->AddTail(pNew);
	pNew->m_strParentItemsID = strDestItemPath + strRight;
}	

void CGbSmartGenWzd::AfterItemPaste_CommCmdAddGrp(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdCommCmdAddGrp *pCommCmdAddGrp, CExBaseList *pList)
{
	CString strSrcItemPath;
	pCopy->GetItemCopyPath(strSrcItemPath); //获取源项目的项目路径

	long nPos = pCommCmdAddGrp->m_strParentItemsID.Find(strSrcItemPath);

	if (nPos != 0)
	{
		//如果是源项目（被复制项目）下的子项目。则pItemsAdd的父项目路径的第一级，必然是源项目的ItemPath
		return;
	}

	CString strTemp = pCommCmdAddGrp->m_strParentItemsID.Mid(strSrcItemPath.GetLength());

	if (strTemp.GetLength() > 0)
	{
		//对于同一个路径下，多次粘贴。项目的ID是自动编号。过滤掉这种自动编号的项目
		if (strTemp.Left(1) != "$")
		{
			return;
		}
	}

	CString strSrc, strDestItemPath;
	strSrc = pCommCmdAddGrp->m_strParentItemsID;
	pPaste->GetDestItemPath(strDestItemPath);  //目标项目的路径
	long nXpos = strSrc.Find(strSrcItemPath);

	ASSERT(nXpos == 0);

	if (nXpos != 0)
	{
		return;
	}

	CString strRight = strSrc.Mid(strSrcItemPath.GetLength());
	CGbWzdCommCmdAddGrp *pNew = (CGbWzdCommCmdAddGrp *)pCommCmdAddGrp->CloneEx(TRUE, TRUE);
	pNew->InitAfterRead();
	pList->AddTail(pNew);
	pNew->m_strParentItemsID = strDestItemPath + strRight;
}

void CGbSmartGenWzd::AfterItemPaste_ItemsDelete(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdItemsDelete *pItemsDelete, CExBaseList *pList)
{
	CString strSrcItemPath;
	pCopy->GetItemCopyPath(strSrcItemPath); //获取源项目的项目路径

	long nPos = pItemsDelete->m_strParentItemsID.Find(strSrcItemPath);

	if (nPos != 0)
	{
		//如果是源项目（被复制项目）下的子项目。则pItemsAdd的父项目路径的第一级，必然是源项目的ItemPath
		return;
	}

	CString strTemp = pItemsDelete->m_strParentItemsID.Mid(strSrcItemPath.GetLength());

	if (strTemp.GetLength() > 0)
	{
		//对于同一个路径下，多次粘贴。项目的ID是自动编号。过滤掉这种自动编号的项目
		if (strTemp.Left(1) != "$")
		{
			return;
		}
	}

	CString strSrc, strDestItemPath;
	strSrc = pItemsDelete->m_strParentItemsID;
	pPaste->GetDestItemPath(strDestItemPath);  //目标项目的路径
	long nXpos = strSrc.Find(strSrcItemPath);

	ASSERT(nXpos == 0);

	if (nXpos != 0)
	{
		return;
	}

	CString strRight = strSrc.Mid(strSrcItemPath.GetLength());
	CGbWzdItemsDelete *pNew = (CGbWzdItemsDelete *)pItemsDelete->CloneEx(TRUE, TRUE);
	pNew->InitAfterRead();
	pList->AddTail(pNew);
	pNew->m_strParentItemsID = strDestItemPath + strRight;
}

CGbMacroGenWzd* CGbSmartGenWzd::FindMacroGen(const CString &strItemsID, const CString &strItemsName, const CString &strParentItemPath)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != DVMCLASSID_GBMACROGENWZD)
		{
			continue;
		}

		CGbMacroGenWzd *pMacroGenWzd = (CGbMacroGenWzd *)pObj;

		if (pMacroGenWzd->m_strItemsID == strItemsID
			&& pMacroGenWzd->m_strItemsName == strItemsName
			&& pMacroGenWzd->m_strParentItemsID == strParentItemPath)
		{
			return pMacroGenWzd;
		}
	}

	return NULL;
}

CGbWzdXItemBase* CGbSmartGenWzd::FindXItemBase(const CString &strItemsID, const CString &strParentItemPath)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if ((nClassID != DVMCLASSID_GBWZDCOMMCMDADD)
			&& (nClassID != DVMCLASSID_GBWZDMACROTESTADD)
			&& (nClassID != DVMCLASSID_GBWZDITEMSADD)
			&& (nClassID != DVMCLASSID_GBWZDITEMEDIT))
		{
			continue;
		}

		CGbWzdXItemBase *pXItemBase = (CGbWzdXItemBase *)pObj;

		if (pXItemBase->m_strItemsID == strItemsID
			&& pXItemBase->m_strParentItemsID == strParentItemPath)
		{
			return pXItemBase;
		}
	}

	return NULL;
}

//ItemMove时，可以上移和下移可以相互抵消。因此可以不通过移动次数来查找
CGbWzdItemMove* CGbSmartGenWzd::FindItemMove(const CString &strItemsID, const CString &strParentItemPath)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if ( nClassID != DVMCLASSID_GBWZDITEMMOVE )
		{
			continue;
		}

		CGbWzdItemMove *pItemMove = (CGbWzdItemMove *)pObj;

		if (pItemMove->m_strItemsID == strItemsID
			&& pItemMove->m_strParentItemsID == strParentItemPath)
		{
			return pItemMove;
		}
	}

	return NULL;
}

CGbWzdItemRsltExprEdit* CGbSmartGenWzd::FindItemRsltExprEdit(const CString &strItemsID, const CString &strParentItemPath)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if ( nClassID != DVMCLASSID_GBWZDITEMRSLTEXPREDIT )
		{
			continue;
		}

		CGbWzdItemRsltExprEdit *pItemRsltExprEdit = (CGbWzdItemRsltExprEdit *)pObj;

		if (pItemRsltExprEdit->m_strItemsID == strItemsID
			&& pItemRsltExprEdit->m_strParentItemsID == strParentItemPath)
		{
			return pItemRsltExprEdit;
		}
	}

	return NULL;
}

CGbWzdItemSetState* CGbSmartGenWzd::FindItemSetState(const CString &strItemsID, const CString &strParentItemPath)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if ( nClassID != DVMCLASSID_GBWZDITEMSETSTATE )
		{
			continue;
		}

		CGbWzdItemSetState *pGbWzdItemSetState = (CGbWzdItemSetState *)pObj;

		if (pGbWzdItemSetState->m_strItemsID == strItemsID
			&& pGbWzdItemSetState->m_strParentItemsID == strParentItemPath)
		{
			return pGbWzdItemSetState;
		}
	}

	return NULL;
}

CGbWzdSafetyAdd* CGbSmartGenWzd::FindSafetyAdd(const CString &strItemsID, const CString &strParentItemPath)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if ( nClassID != DVMCLASSID_GBWZDSAFETYADD )
		{
			continue;
		}

		CGbWzdSafetyAdd *pGbWzdSafetyAdd = (CGbWzdSafetyAdd *)pObj;

		if (pGbWzdSafetyAdd->m_strItemsID == strItemsID
			&& pGbWzdSafetyAdd->m_strParentItemsID == strParentItemPath)
		{
			return pGbWzdSafetyAdd;
		}
	}

	return NULL;
}

CGbWzdCommCmdUpdate* CGbSmartGenWzd::FindCommCmdUpdate(const CString &strItemsID, const CString &strParentItemPath)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if ( nClassID != DVMCLASSID_GBWZDCOMMCMDUPDATE )
		{
			continue;
		}

		CGbWzdCommCmdUpdate *pGbWzdCommCmdUpdate = (CGbWzdCommCmdUpdate *)pObj;

		if (pGbWzdCommCmdUpdate->m_strItemsID == strItemsID
			&& pGbWzdCommCmdUpdate->m_strParentItemsID == strParentItemPath)
		{
			return pGbWzdCommCmdUpdate;
		}
	}

	return NULL;
}

CGbWzdCommCmdAddGrp* CGbSmartGenWzd::FindCommCmdAddGrp(const CString &strParentItemPath)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if ( nClassID != DVMCLASSID_GBWZDCOMMCMDADDGRP )
		{
			continue;
		}

		CGbWzdCommCmdAddGrp *pGbWzdCommCmdAddGrp = (CGbWzdCommCmdAddGrp *)pObj;

		if (pGbWzdCommCmdAddGrp->m_strParentItemsID == strParentItemPath)
		{
			return pGbWzdCommCmdAddGrp;
		}
	}

	return NULL;
}

CGbWzdItemsDelete* CGbSmartGenWzd::FindItemsDelete(const CString &strItemsID, const CString &strParentItemPath)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if ( nClassID != DVMCLASSID_GBWZDITEMSDELETE )
		{
			continue;
		}

		CGbWzdItemsDelete *pGbWzdItemsDelete = (CGbWzdItemsDelete *)pObj;

		if (pGbWzdItemsDelete->m_strItemsID == strItemsID
			&& pGbWzdItemsDelete->m_strParentItemsID == strParentItemPath)
		{
			return pGbWzdItemsDelete;
		}
	}

	return NULL;
}

CDataGroup* CGbSmartGenWzd::GetParentItems(const CString &strParentPath)
{
	if (strParentPath.GetLength() == 0)
	{
		return m_pGbItemsRootTree;
	}

	if (m_pGbItemsRootTree == NULL)
	{
		return NULL;
	}

	CExBaseList listFind;
	CDataGroup *pParent = NULL;
	CString strTemp;
	strTemp = strParentPath;
	m_pGbItemsRootTree->Select(strTemp, listFind, '$');

	if (listFind.GetCount() > 0)
	{
		pParent = (CDataGroup *)listFind.GetHead();
	}
	else
	{
		pParent = m_pGbItemsRootTree;
	}

	listFind.RemoveAll();

	return pParent;
}

CGbWzdMacroTestAdd* CGbSmartGenWzd::MacroTestAdd(const CString &strParentItemPath, const CString &strItemID, const CString &strItemName, const CString &strMacroID)
{
	CGbWzdMacroTestAdd *pNew = new CGbWzdMacroTestAdd();
	
	pNew->m_strItemsName = strItemName;
	pNew->m_strItemsID = strItemID;
	pNew->m_strTestMacroUI = strMacroID;
	pNew->m_strParentItemsID = strParentItemPath;
	AddNewChild(pNew);

	return pNew;
}

CGbWzdCommCmdAdd* CGbSmartGenWzd::CommCmdAdd(const CString &strParentItemPath, const CString &strItemID, const CString &strItemName, const CString &strCommCmdID)
{
	CGbWzdCommCmdAdd *pNew = new CGbWzdCommCmdAdd();

	pNew->m_strItemsName = strItemName;
	pNew->m_strItemsID = strItemID;
	pNew->m_strCommCmdID = strCommCmdID;
	pNew->m_strParentItemsID = strParentItemPath;
	AddNewChild(pNew);

	return pNew;
}

CGbWzdItemsAdd* CGbSmartGenWzd::ItemsAdd(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName
										 , long nRepeatTimes, long nRptTitle, long nTitleLevel)
{
	CGbWzdItemsAdd *pNew = new CGbWzdItemsAdd();

	pNew->m_strItemsName = strItemsName;
	pNew->m_strItemsID = strItemsID;
	pNew->m_strParentItemsID = strParentItemPath;
	pNew->m_nRepeatTimes = nRepeatTimes;
	pNew->m_nRptTitle = nRptTitle;
	pNew->m_nTitleLevel = nTitleLevel;
	AddNewChild(pNew);

	return pNew;
}

CGbWzdItemRsltExprEdit* CGbSmartGenWzd::ItemsRsltExprEdit(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName)
{
	CGbWzdItemRsltExprEdit* pNew = FindItemRsltExprEdit(strItemsID, strParentItemPath);

	if (pNew != NULL)
	{
		pNew->m_strItemsName = strItemsName;
		return pNew;
	}

	pNew = new CGbWzdItemRsltExprEdit();

	pNew->m_strItemsName = strItemsName;
	pNew->m_strItemsID = strItemsID;
	pNew->m_strParentItemsID = strParentItemPath;
	AddNewChild(pNew);

	return pNew;
}

CGbWzdItemSetState* CGbSmartGenWzd::ItemsSetState(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName
								  , long nSelect, long nEnable, long nShow)
{
	CGbWzdItemSetState* pNew = FindItemSetState(strItemsID, strParentItemPath);

	if (pNew != NULL)
	{
		pNew->m_nSelect = nSelect;
		pNew->m_nEnable = nEnable;
		pNew->m_nShow = nShow;
		BringToTail(pNew);
		return pNew;
	}

	pNew = new CGbWzdItemSetState();

	pNew->m_strItemsName = strItemsName;
	pNew->m_strItemsID = strItemsID;
	pNew->m_strParentItemsID = strParentItemPath;
	pNew->m_nSelect = nSelect;
	pNew->m_nEnable = nEnable;
	pNew->m_nShow = nShow;
	AddNewChild(pNew);

	return pNew;
}

CGbWzdSafetyAdd* CGbSmartGenWzd::SafetyAdd_Add(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName
							   , const CString &strMsgs, CDataGroup *pListDatas)
{
	CGbWzdSafetyAdd* pNew = new CGbWzdSafetyAdd();

	pNew->m_strItemsID = strItemsID;
	pNew->m_strItemsName = strItemsName;
	pNew->m_strParentItemsID = strParentItemPath;
	pNew->m_strMsg = strMsgs;

	if (pListDatas != NULL)
	{
		pNew->AppendCloneEx(*pListDatas, TRUE);
	}

	AddNewChild(pNew);

	return pNew;
}

//编辑时，不会编辑ItemsID
CGbWzdSafetyAdd* CGbSmartGenWzd::SafetyAdd_Edit(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName
								, const CString &strMsgs, CDataGroup *pListDatas)
{
	CGbWzdSafetyAdd* pNew = FindSafetyAdd(strItemsID, strParentItemPath);

	if (pNew == NULL)
	{
		return SafetyAdd_Add(strParentItemPath, strItemsID, strItemsName, strMsgs, pListDatas);
	}

	//编辑时，直接修改创建的对象即可。
	pNew->m_strItemsName = strItemsName;
	pNew->m_strMsg = strMsgs;
	pNew->DeleteAll();

	if (pListDatas != NULL)
	{
		pNew->AppendCloneEx(*pListDatas, TRUE);
	}

	return pNew;
}

void CGbSmartGenWzd::SafetyAdd_Delete(const CString &strParentItemPath, const CString &strItemsID)
{
	CGbWzdSafetyAdd* pFind = FindSafetyAdd(strItemsID, strParentItemPath);

	if (pFind != NULL)
	{
		Delete(pFind);
	}
}

CGbWzdCommCmdUpdate* CGbSmartGenWzd::CommCmdUpdate(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName, const CString &strContents)
{
	CGbWzdCommCmdUpdate* pFind = FindCommCmdUpdate(strItemsID, strParentItemPath);

	if (pFind == NULL)
	{
		pFind = new CGbWzdCommCmdUpdate();
		pFind->m_strParentItemsID = strParentItemPath;
		pFind->m_strItemsName = strItemsName;
		pFind->m_strItemsID = strItemsID;
		AddNewChild(pFind);
	}

	CDvmContents *pContents = pFind->GetCommCmd();
	pContents->m_strText = strContents;

	return pFind;
}

CGbWzdCommCmdAddGrp* CGbSmartGenWzd::CommCmdAddGrp(const CString &strParentItemPath, long nAftUseReset, long nAddCommCmd)
{
	CGbWzdCommCmdAddGrp* pFind = FindCommCmdAddGrp(strParentItemPath);

	if (pFind == NULL)
	{
		pFind = new CGbWzdCommCmdAddGrp();
		pFind->m_strParentItemsID = strParentItemPath;
		AddNewChild(pFind);
	}

	pFind->m_nAftUseReset = nAftUseReset;
	pFind->m_nAddCommCmd = nAddCommCmd;
	return pFind;
}

CGbWzdItemsDelete* CGbSmartGenWzd::ItemsDelete(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName)
{
	CGbWzdItemsDelete* pFind = FindItemsDelete(strItemsID, strParentItemPath);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = new CGbWzdItemsDelete();
	pFind->m_strParentItemsID = strParentItemPath;
	pFind->m_strItemsID = strItemsID;
	pFind->m_strItemsName = strItemsName;
	AddNewChild(pFind);
	return pFind;
}

CDvmData* CGbSmartGenWzd::GetCmdCfgData(const CString &strCmdID, const CString &strCfgID)
{
	CDataGroup *pGroup = (CDataGroup*)m_pCommCmdCfg->FindByID(strCfgID/*STT_CMD_PARA_CMDBFT*/);

	if (pGroup == NULL)
	{
		return NULL;
	}

	CDvmData *pFind = (CDvmData*)pGroup->FindByID(strCmdID);

	return pFind;
}

//返回当前被复制的项目的项目类型
CString CGbSmartGenWzd::GetItemCopyType()
{
	if (m_pCurrItemCopy == NULL)
	{
		return _T("null");
	}

	return m_pCurrItemCopy->m_strItemType;   //macrotest, commcmd, items
}

void CGbSmartGenWzd::SetItemCopy(const CString &strParentItemPath, CExBaseObject *pCurrSelItem, const CString &strItemPath)
{
	if (m_pCurrItemCopy != NULL)
	{
		delete m_pCurrItemCopy;
	}

	m_pCurrItemCopy = new CGbWzdItemCopy();
	m_pCurrItemCopy->m_strParentItemsID = strParentItemPath;
	m_pCurrItemCopy->m_strItemsName = pCurrSelItem->m_strName;
	m_pCurrItemCopy->m_strItemsID = pCurrSelItem->m_strID;
	m_pCurrItemCopy->m_strItemPath = strItemPath;

	if (strParentItemPath.IsEmpty())
	{
		m_pCurrItemCopy->m_strItemPath = pCurrSelItem->m_strID;
	}

	UINT nClassID = pCurrSelItem->GetClassID();

	switch (nClassID)
	{
	case STTGBXMLCLASSID_CSTTITEMS:
		m_pCurrItemCopy->m_strItemType = _T("items");
		break;

	case STTGBXMLCLASSID_CSTTMACROTEST:
		m_pCurrItemCopy->m_strItemType = _T("macrotest");
		break;

	case STTGBXMLCLASSID_CSTTCOMMCMD:
		m_pCurrItemCopy->m_strItemType = _T("commcmd");
		break;
	default:
		m_pCurrItemCopy->m_strItemType = _T("null");
	}
}
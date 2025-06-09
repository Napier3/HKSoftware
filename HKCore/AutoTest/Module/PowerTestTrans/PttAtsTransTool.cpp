//PttAtsTransTool.cpp  CPttAtsTransTool

#include "stdafx.h"
#include "PttAtsTransTool.h"

#include "PttGlobalDefine.h"
#include "..\..\..\Module\Expression\EpExpression.h"
#include "..\..\..\Module\System\StringVariableReplace.h"

#define PTT_ATS_TRANS_ID_PROT_CPU  _T("Prot")
#define PTT_ATS_TRANS_ID_DSSETTING  _T("dsSetting")

CPttAtsTransTool::CPttAtsTransTool()
{
	CMacroMapMngrXmlRWKeys::Create();
	m_oMacroMaps.OpenMacroMaps();
	m_pGuideBook = new CGuideBook();
	m_pGuideBook->InitAfterRead();
	m_pDevice = NULL;
	m_bUseGlobalSetting = FALSE;
	m_bHasTransTestObject = FALSE;
	m_pElementBinary = NULL;
	m_pElementSetting = NULL;
	m_pElementCommonPara = NULL;
	m_pElementTestItem = NULL;
	m_pCurMacroMap = NULL;
	m_pDsSettings = NULL;
	m_pSystemParas = NULL;
	m_pCurMacroTestPara = NULL;
}

CPttAtsTransTool::~CPttAtsTransTool()
{
	delete m_pGuideBook;
	CMacroMapMngrXmlRWKeys::Release();
}

CString CPttAtsTransTool::TransPttFile (const CString& strFile)
{
	CString strGuideBookFile;

	m_strPttFile = strFile;
	m_oFileParse.ReadFromTemplate(strFile);
	TransRoot(m_oFileParse.GetRoot());
	CString strFileName;
	strFileName = ParseFileName(m_strPttFile);

	strGuideBookFile = _P_GetTemplatePath();
	strGuideBookFile += _T("PowerTest\\");
	CreateAllDirectories(strGuideBookFile);
	strGuideBookFile +=strFileName;
	strGuideBookFile = ChangeFilePostfix(strGuideBookFile, g_strGbFileFilter);
	m_pGuideBook->SaveXMLFile(strGuideBookFile);

	return strGuideBookFile;
}

void CPttAtsTransTool::TransRoot(CPNTplRoot* pRoot)
{
	ASSERT(pRoot != NULL);
 
	InitTestObject();

	POS pos = pRoot->GetHeadPosition();
	CExBaseObject *p = NULL;

	while(pos != NULL)
	{
		p = pRoot->GetNext(pos);
		
		if (p->m_strName == PTT_KEY_TestObject)
		{
			TransElement_TestObject((CPNTplElement*)p);
		}
		else if (p->m_strName == PTT_KEY_GlobalSetting)
		{
			TransElement_GlobalSetting((CPNTplElement*)p);
		}
		else if (p->m_strName == PTT_KEY_ProtectionRelay)
		{
			TransElement_ProtectionRelay((CPNTplElement*)p);
		}
	}
}

void CPttAtsTransTool::TransElement(CPNTplElement *pElement)
{
	if (pElement->GetClassID() != MNGRCLASSID_CPNTPLELEMENT)
	{
		return;
	}

	if (pElement->m_strName == PTT_KEY_CommonParameter)
	{
		return TransElement_CommonParameter(pElement);
	}

	if (pElement->m_strName == PTT_KEY_Setting)
	{
		return TransElement_Setting(pElement);
	}

	if (pElement->m_strName == PTT_KEY_CFG)
	{
		return TransElement_CFG(pElement);
	}

	if (pElement->m_strName == PTT_KEY_IECParameter)
	{
		return TransElement_CFG(pElement);
	}

	if (pElement->m_strName == PTT_KEY_Binary)
	{
		return TransElement_Binary(pElement);
	}

	if (pElement->m_strName == PTT_KEY_TextInput)
	{
		return TransElement_TextInput(pElement);
	}

	if (pElement->m_strName == PTT_KEY_Character)
	{
		return TransElement_Character(pElement);
	}

	if (pElement->m_strName == PTT_KEY_Report)
	{
		return TransElement_Report(pElement);
	}

	if (pElement->m_strName == PTT_KEY_TestPoint)
	{
		return TransElement_TestPoint(pElement);
	}

	if (pElement->m_strName == PTT_KEY_TestItem)
	{
		return TransElement_TestItem(pElement);
	}

	if (pElement->m_strName == PTT_KEY_CalculatorExp)
	{
		return TransElement_CalculatorExp(pElement);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("..............Element [%s] error......"), pElement->m_strName);
}

/*
<TestObjectBegin>
DeviceName=BCH-2差动继电器;
DeviceType=变压器保护;
Manufacturer=;
<TestObjectEnd>
*/

void CPttAtsTransTool::InitTestObject()
{
	if (m_pDevice == NULL)
	{
		m_pDevice = new CDevice();
		m_pDevice->m_strName = _T("PowerTest Test Template");
		m_pDevice->m_strID = m_pDevice->m_strName;
		m_pGuideBook->AddNewChild(m_pDevice);
		m_pDevice->InitAfterRead();

		m_pGuideBook->m_strTestTypeFile = _T("TestType.xml");
		m_pGuideBook->m_strTestMacroFileID = _T("RelayTest");
		m_pGuideBook->m_strCommCmdConfigFile = _T("MmsCommCmdConfig.xml");
		m_pGuideBook->m_strExpandConfigFile = _T("RelayExpandData.xml");
		m_pGuideBook->m_strScriptMngrFile = _T("GbScriptLibrary.xml");
	}
}

void CPttAtsTransTool::TransElement_TestObject(CPNTplElement *pElement)
{
	if (m_bHasTransTestObject)
	{
		return;
	}

	m_bHasTransTestObject = TRUE;

	if (m_pDevice == NULL)
	{
		m_pDevice = new CDevice();
		m_pDevice->m_strName = _T("PowerTest Test Template");
		m_pDevice->m_strID = m_pDevice->m_strName;
		m_pGuideBook->AddNewChild(m_pDevice);
		m_pDevice->InitAfterRead();
	
		m_pGuideBook->m_strTestTypeFile = _T("TestType.xml");
		m_pGuideBook->m_strTestMacroFileID = _T("RelayTest");
		m_pGuideBook->m_strCommCmdConfigFile = _T("MmsCommCmdConfig.xml");
		m_pGuideBook->m_strExpandConfigFile = _T("RelayExpandData.xml");
		m_pGuideBook->m_strScriptMngrFile = _T("GbScriptLibrary.xml");
	}

	if (pElement == NULL)
	{
		return;
	}

	GetKeyValue(pElement, PTT_KEY_DeviceName, m_pGuideBook->m_strID);
	GetKeyValue(pElement, PTT_KEY_Manufacturer, m_pDevice->m_strFactory);
	GetKeyValue(pElement, PTT_KEY_DeviceType, m_pDevice->m_strDeviceType);

	if (!m_pGuideBook->m_strID.IsEmpty())
	{
		m_pDevice->m_strName = m_pGuideBook->m_strID;
		m_pDevice->m_strID = m_pGuideBook->m_strID;
	}
}

void CPttAtsTransTool::TransElement_GlobalSetting(CPNTplElement *pElement)
{
	m_pElementSetting = pElement;
	m_bUseGlobalSetting = TRUE;

	CDataSet *pSetting = (CDataSet*)GetDvmDataset_Setting();
	TransElement_Dataset(pSetting, pElement);
}

/*
<ProtectionRelayBegin>
	ProtectiveRelayName=直流助磁继电器;
	Property=直流助磁继电器;
	WordReportName= ;
	Update=0;
*/
void CPttAtsTransTool::TransElement_ProtectionRelay(CPNTplElement *pElement)
{
	m_pElementBinary = NULL;
	m_oBinaryDataset.DeleteAll();
	m_pItems_ProtectionRelay = new CItems();
	m_pItems_ProtectionRelay->InitAfterRead();
	m_pDevice->AddNewChild(m_pItems_ProtectionRelay);

	GetKeyValue(pElement, PTT_KEY_ProtectiveRelayName, m_pItems_ProtectionRelay->m_strName);
	m_pItems_ProtectionRelay->m_strID = m_pItems_ProtectionRelay->m_strName;
	GetKeyValue(pElement, PTT_KEY_Property, m_pItems_ProtectionRelay->m_strType);

	POS pos = pElement->GetHeadPosition();
	CExBaseObject *p = NULL;

	while(pos != NULL)
	{
		p = pElement->GetNext(pos);

		if (p->GetClassID() == MNGRCLASSID_CPNTPLELEMENT)
		{
			TransElement((CPNTplElement*)p);
		}
	}
}

void CPttAtsTransTool::TransElement_CommonParameter(CPNTplElement *pElement)
{
	m_pElementCommonPara = pElement;
	CSysParas *pSysParas = m_pDevice->GetSysParas();
	m_pSystemParas = pSysParas;

	TransElement_Dataset(pSysParas, pElement);
}

void CPttAtsTransTool::TransElement_Setting(CPNTplElement *pElement)
{
// 	if (m_bUseGlobalSetting)
// 	{
// 		return;
// 	}

	m_pElementSetting = pElement;
	CDataSet *pSetting = (CDataSet*)GetDvmDataset_Setting();
	m_pDsSettings = pSetting;

	TransElement_Dataset(pSetting, pElement);
}

/*
4.3.2	CFG转换
第一步：将CFG的内容存为一个临时文件，临时文件名规则为：“[模板名称]_ [ProtectionRelay 的名称][_数字].pcfg”，如果ProtectionRelay名称有重复，就到后面补充数字编号；
第二步：添加电气量测试项目，测试功能为“IEC61850配置”，功能参数的值为CFG临时文件，测试项目名称为“IEC61850配置”；
*/
void CPttAtsTransTool::TransElement_CFG(CPNTplElement *pElement)
{
	//文件名：和模板名称相同【不按照设计来实现，因为一个模板只能有一个配置】
	CString strFileName, strParaValue;
	strFileName = ParseFileName(m_strPttFile);
	strFileName = ChangeFilePostfix(strFileName, _T("pcfg"));
	//strParaValue.Format(_T("\"%s\""), strFileName);

	CFile oFile;
	strFileName = mtdt_GetIecConfigFilePath() + strFileName;

	if (!oFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Translate "));
		return;
	}

	strParaValue = strFileName;

	CMacroTest *pNew = new CMacroTest();
	pNew->m_strName = _T("IEC61850_Config");
	pNew->m_strID = pNew->m_strName;
	m_pDevice->AddNewChild(pNew);
	CMacroTestPara *pPara = pNew->GetMacroTestPara();
	pNew->SetTestMacroID(_T("IECConfig"));
	pPara->UpdateMacroTestParaData(_T("_IecCfgFile"), strParaValue, FALSE);

}

void CPttAtsTransTool::TransElement_Binary(CPNTplElement *pElement)
{
	m_pElementBinary = pElement;
	TransElement_Dataset(&m_oBinaryDataset, pElement);
}

void CPttAtsTransTool::TransElement_TextInput(CPNTplElement *pElement)
{

}

void CPttAtsTransTool::TransElement_Character(CPNTplElement *pElement)
{

}

void CPttAtsTransTool::TransElement_Report(CPNTplElement *pElement)
{

}

void CPttAtsTransTool::TransElement_CalculatorExp(CPNTplElement *pElement)
{

}

void CPttAtsTransTool::TransElement_TestPoint(CPNTplElement *pElement)
{
	POS pos = pElement->GetHeadPosition();
	CExBaseObject *p = NULL;

	while(pos != NULL)
	{
		p = pElement->GetNext(pos);
		
		if (p->m_strName == PTT_KEY_TestItem)
		{
			TransElement_TestItem((CPNTplElement*)p);
		}
	}
}

void CPttAtsTransTool::TransElement_TestItem(CPNTplElement *pElement)
{
	m_pElementTestItem = pElement;  //邵雷
	long nHintSel = 0;
	CString strHint, strName, strMacroID;
//	m_pCurMacroMap = NULL;

	GetKeyValue(pElement, PTT_KEY_HINT, strHint);
	GetKeyValue(pElement, PTT_KEY_HINTSELECT, nHintSel);
	GetKeyValue(pElement, PTT_KEY_TestComName2, strMacroID);
	GetKeyValue(pElement, PTT_KEY_TESTNAME, strName);
	strName.Replace(_T("$"),_T("_USD_"));//zhouhj 20190814 对电气量名称汇总的$字符特殊处理为"_USD_"
	m_pCurMacroMap = FindMacroMapObj(&m_oMacroMaps,strMacroID,pElement);
//	pMacroMap = (CMacroMap*)m_oMacroMaps.FindByID(strMacroID);

	if (m_pCurMacroMap == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("PowerTest Macro ID [%s] has no map"), strMacroID);
		return;
	}

	//提示信息处理
	if (nHintSel == 0 &&strHint.GetLength() > 0)
	{
		TransElement_TestItem_Safety(strHint, strName);
	}

	//电气量项目处理
	CMacroTest *pMacroTest = NULL;

	if (strMacroID == _T("UIState.UIStateCom"))//对于状态序列查找该Item在ProtectionRelay中是否出现过
	{
		POS pos_MacroTest = m_pItems_ProtectionRelay->GetHeadPosition();
		CExBaseObject *pCurObj = NULL;
		CMacroTest *pTmpMacroTest = NULL;

		while(pos_MacroTest)
		{
			pCurObj = m_pItems_ProtectionRelay->GetNext(pos_MacroTest);

			if (pCurObj->GetClassID() == GBCLASSID_MACROTEST)
			{
				pTmpMacroTest = (CMacroTest*)pCurObj;

				if (pTmpMacroTest->GetTestMacroID() == _T("State4U3I"))
				{
					pMacroTest = pTmpMacroTest;
					m_pCurMacroTestPara = new CMacroTestPara;
					m_pCurMacroTestPara->InitAfterRead();
					break;
				}
			}
		}

		strName = m_pItems_ProtectionRelay->m_strName;
	} 

	if (pMacroTest == NULL)
	{
		pMacroTest = new CMacroTest();
		m_pItems_ProtectionRelay->AddNewChild(pMacroTest);
		pMacroTest->m_strName = strName;
		pMacroTest->m_strID = strName;
		pMacroTest->InitAfterRead();   //邵雷 初始化m_pPara
		m_pCurMacroTestPara = pMacroTest->GetMacroTestPara();
	}
	
	m_pCurMacroTestPara->SetMacroID(m_pCurMacroMap->m_strMapID);

	//对于只在Item存在的固定定值，进行提取，优先特殊处理
	InitBefore_TransTestItem(pElement,strMacroID,m_pCurMacroTestPara);

	Trans_ComboBox_SysParas_Settings(pElement);

	TransElement_MacroTest_Paras(pElement, m_pCurMacroMap);

	if (m_pElementBinary != NULL)
	{
		TransElement_MacroTest_ParasEx(m_pElementBinary, m_pCurMacroMap);
	}

	//处理电气量的结果脚本
	TransElement_MacroTest_RsltScript(pElement, pMacroTest, m_pCurMacroMap);

	//提示信息处理
	if (nHintSel == 1 &&strHint.GetLength() > 0)
	{
		TransElement_TestItem_Safety(strHint, strName);
	}

	//参数映射表达式处理
	Trans_MacroMap_Exprs(pElement, m_pCurMacroMap);

 	if (pMacroTest->GetMacroTestPara() != m_pCurMacroTestPara)
 	{
		CMacroTestPara *pTmpParaObj = m_pCurMacroTestPara;
		m_pCurMacroTestPara = pMacroTest->GetMacroTestPara();
		CMacroTestParaDatas *pTmpParaDatas = pTmpParaObj->GetFaultParaDatas();
		CMacroTestParaDatas *pCurParaDatas = m_pCurMacroTestPara->GetFaultParaDatas();
		CMacroTestParaData *pCurParaData = NULL;
		CMacroTestParaData *pParaDataStateCount = (CMacroTestParaData*)pCurParaDatas->FindByID(_T("StateCount"));

		if (pParaDataStateCount == NULL)
		{
			pParaDataStateCount = new CMacroTestParaData;
			pCurParaDatas->AddNewChild(pParaDataStateCount);
			pParaDataStateCount->m_strID = _T("StateCount");
			pParaDataStateCount->m_strName = _T("StateCount");
			pParaDataStateCount->m_strExpression = _T("1");
		}

		long nStateCount = CString_To_long(pParaDataStateCount->m_strExpression);
		nStateCount++;
		pParaDataStateCount->m_strExpression.Format(_T("%ld"),nStateCount);
 		POS pos_para = pTmpParaDatas->GetHeadPosition();
		CString strTmp;
		strTmp.Format(_T("state%ld$"),nStateCount);
 		
  		while(pos_para)
  		{
  			pCurParaData = (CMacroTestParaData*)pTmpParaDatas->GetNext(pos_para);

			if (pCurParaData->m_strID.Find(_T("state1$")) != -1)
			{
				pCurParaData->m_strID.Replace(_T("state1$"),strTmp);
				pCurParaData->m_strName.Replace(_T("state1$"),strTmp);
				pTmpParaDatas->Remove(pCurParaData);
				pCurParaDatas->AddNewChild(pCurParaData);
			}
  		}

		delete pTmpParaObj;
 	}

	m_pCurMacroMap = NULL;
}

CMacroMap *CPttAtsTransTool::FindMacroMapObj(CMacroMaps *pMacroMaps,const CString &strMacroID,CPNTplElement *pElement)
{
	CMacroMap *pMacroMap = NULL;

	if (strMacroID == _T("OverITime.OverITimeCom"))
	{
		if (m_pElementCommonPara != NULL)
		{
			CPNTplEquation *pEquation = (CPNTplEquation*)pElement->FindByID(_T("INVERSECURVE"));

			if (pEquation != NULL)
			{
				long nValue = CString_To_long(pEquation->m_strValue);

				if (nValue == 1)
				{
					pMacroMap = pMacroMaps->FindMacroMapByMapID(_T("InverseTimeIf"));
					return pMacroMap;
				}
			}

			pMacroMap = pMacroMaps->FindMacroMapByMapID(_T("OverITime"));
// 			CPNTplGroup *pGroup = m_pElementCommonPara->FindGroupByValueID(_T("FaultType"));
// 
// 			if (pGroup != NULL)
// 			{
// 				CString strFaultType;
// 				GetKeyValue(pGroup, PTT_KEY_DATA_ATTR_NUM, strFaultType);
// 
// 				if (strFaultType == _T("7"))
// 				{
// 					pMacroMap = pMacroMaps->FindMacroMapByMapID(_T("InverseTimeIf"));
// 				} 
// 				else
// 				{
// 					pMacroMap = pMacroMaps->FindMacroMapByMapID(_T("InverseTimeIf"));
// 				}
// 			}
		}
	}
	else
	{
		pMacroMap = (CMacroMap*)m_oMacroMaps.FindByID(strMacroID);
	}

	return pMacroMap;
}

void CPttAtsTransTool::InitBefore_TransTestItem(CPNTplElement *pElement,const CString &strMacroID,CMacroTestPara *pMacroTestPara)
{
	CString strTmp;
	CSysParas *pSysParas = m_pDevice->GetSysParas();

 	if (strMacroID == _T("OverITime.OverITimeCom"))
 	{
		CDataSet *pSetting = (CDataSet*)GetDvmDataset_Setting();
		AddSetting_TestItem(pSetting,_T("1段定时限"),_T("Iset1"),pElement,_T("ID1"));
		AddSetting_TestItem(pSetting,_T("2段定时限"),_T("Iset2"),pElement,_T("ID2"));
		AddSetting_TestItem(pSetting,_T("3段定时限"),_T("Iset3"),pElement,_T("ID3"));
		CPNTplEquation *pPNTplEquation = (CPNTplEquation*)pElement->FindByName(_T("IF"));

		if (pPNTplEquation != NULL)
		{
			pPNTplEquation->m_strValue.Replace(_T("In"),_T("Inom"));
			pPNTplEquation->m_strValue.Replace(_T("Ip"),_T("Ipu"));
		}
 	}
	else if (strMacroID == _T("Diff6I.Diff6ICom"))
	{
		CPNTplEquation *pASSESS_Equation = new CPNTplEquation;
		pElement->AddNewChild(pASSESS_Equation);
		pASSESS_Equation->m_strName = _T("ASSESSACTVALUE");
		pASSESS_Equation->m_strID = _T("ASSESSACTVALUE");
		CPNTplEquation *pErrorRange_Equation = (CPNTplEquation*)pElement->FindByID(_T("ERRORRANGE"));

		if (pErrorRange_Equation != NULL)
		{
			pASSESS_Equation->m_strValue.Format(_T("ABS(IdSet-TripId)<(%s/100)"),pErrorRange_Equation->m_strValue);
		} 
		else
		{
			pASSESS_Equation->m_strValue.Format(_T("ABS(IdSet-TripId)<(5/100)"));
		}
		
		ASSERT(m_pCurMacroMap);
		CParaMap *pParaMap = (CParaMap*)m_pCurMacroMap->FindByID(_T("ASSESSACTVALUE"));

		if (pParaMap == NULL)
		{
			pParaMap = new CParaMap;
			m_pCurMacroMap->AddNewChild(pParaMap);
			pParaMap->m_strName = "ASSESSACTVALUE";
			pParaMap->m_strID = "ASSESSACTVALUE";
			pParaMap->m_strMapName = "RsltJdg";
			pParaMap->m_strMapID = "RsltJdg";
		}
	}
	else if (strMacroID == _T("FreqAct.FreqActCom"))
	{
		CDataObj *pData = (CDataObj*)pSysParas->FindByID(_T("Fn"));

		if (pData == NULL)
		{
			pData = new CDataObj;
			pSysParas->AddNewChild(pData);
			pData->m_strID = _T("Fn");
			pData->m_strName = pData->m_strID;
			pData->m_strValue = _T("60");
			pData->m_strDefaultValue = pData->m_strValue;
		}
	}

	CheckInputValues(pElement);
}

void CPttAtsTransTool::CheckInputValues(CPNTplElement *pElement)
{
	ASSERT(pElement);
	CPNTplEquation *pInputA = (CPNTplEquation*)pElement->FindByName(_T("INPUTA"));

	if (pInputA == NULL)
	{
		return;
	}

	if (CheckInput_Valid(pInputA))
	{
		return;
	}

	if (CheckInput_Valid((CPNTplEquation*)pElement->FindByName(_T("INPUTB"))))
	{
		return;
	}

	if (CheckInput_Valid((CPNTplEquation*)pElement->FindByName(_T("INPUTC"))))
	{
		return;
	}

	if (CheckInput_Valid((CPNTplEquation*)pElement->FindByName(_T("INPUTD"))))
	{
		return;
	}

	if (CheckInput_Valid((CPNTplEquation*)pElement->FindByName(_T("INPUTE"))))
	{
		return;
	}

	if (CheckInput_Valid((CPNTplEquation*)pElement->FindByName(_T("INPUTF"))))
	{
		return;
	}

	if (CheckInput_Valid((CPNTplEquation*)pElement->FindByName(_T("INPUTG"))))
	{
		return;
	}

	if (CheckInput_Valid((CPNTplEquation*)pElement->FindByName(_T("INPUTH"))))
	{
		return;
	}

	pInputA->m_strValue = _T("2");
}

BOOL CPttAtsTransTool::CheckInput_Valid(CPNTplEquation *pInput)
{
	if (pInput == NULL)
	{
		return FALSE;
	}

	long nValue = CString_To_long(pInput->m_strValue);

	if (nValue<=1)
	{
		return FALSE;
	}

	return TRUE;
}

void CPttAtsTransTool::Replcae_ElementEquationValue(CPNTplElement *pElement,const CString &strName,const CString &strValue)
{
	CPNTplEquation *pPNTplEquation = (CPNTplEquation*)pElement->FindByName(strName);

	if (pPNTplEquation == NULL)
	{
		pPNTplEquation = new CPNTplEquation;
		pPNTplEquation->m_strName = strName;
		pElement->AddNewChild(pPNTplEquation);
	}

	pPNTplEquation->m_strValue = strValue;
}

BOOL CPttAtsTransTool::AddSetting_TestItem(CDataSet *pSetting,const CString &strSettingName,const CString &strSettingID,CPNTplElement *pElement,const CString &strEquationID)
{
	CPNTplEquation *pPNTplEquation = (CPNTplEquation*)pElement->FindByName(strEquationID);

	if (pPNTplEquation == NULL)
	{
		return FALSE;
	}

	CDataObj *pData = (CDataObj*)pSetting->FindByID(strSettingID);

	if (pData == NULL)
	{
		pData = new CDataObj;
		pSetting->AddNewChild(pData);
		pData->m_strID = strSettingID;
	}

	pData->m_strName = strSettingName;
	pData->m_strValue.Format(_T("%s*Inom"),pPNTplEquation->m_strValue);
	pData->m_strDefaultValue = pData->m_strValue;
	return TRUE;
}

void CPttAtsTransTool::TransElement_MacroTest_Paras(CPNTplElement *pElement, CMacroMap *pMacroMap)
{
	POS pos = pElement->GetHeadPosition();
	CPNTplEquation *pEquation = NULL;
	CMacroTestPara *pMacroTestPara = m_pCurMacroTestPara;
	CString strAtsParaID, strAtsParaValue;

	while (pos != NULL)
	{
		pEquation = (CPNTplEquation *)pElement->GetNext(pos);

		if (pEquation->m_strName == PTT_KEY_TESTNAME || pEquation->m_strName == PTT_KEY_HINT)   //邵雷 测试名称和提示信息不需要转换
		{
			continue;
		}
		
		if (!pMacroMap->MapPara(pEquation->m_strName, pEquation->m_strValue, strAtsParaID, strAtsParaValue))
		{
			continue;
		}

		if (!IsStringNumber(strAtsParaValue))
		{
			//如果是表达式，则进行表达式处理
			TransElement_MacroTest_Paras_Expr(strAtsParaValue, pMacroMap);
		}

		pMacroTestPara->UpdateMacroTestParaData(strAtsParaID, strAtsParaValue, TRUE);
	}
}

//void CPttAtsTransTool::UpdateMacroTestParaData(CMacroTestPara *pMacroTestPara,const CString &strAtsParaID, const CString &strAtsParaValue, BOOL bShowLog)
//{
//	CString strCurPath;
//	long nIndex = strCurPath.Find("$");
//
//	if (nIndex == -1)
//	{
//		pMacroTestPara->UpdateMacroTestParaData(strAtsParaID, strAtsParaValue, TRUE);
//		return;
//	}
//
//	CString strCurName,strRightPath;
//	CMacroTestParaDatas* pMacroTestParaDatas =  pMacroTestPara->GetFaultParaDatas();
//	strCurName = strCurPath.Left(nIndex);
//	strRightPath = strCurPath.Mid(nIndex+1);
//	CShortData
//
//	while(nIndex != -1)
//	{
//		strCurName = strCurPath.Left(nIndex);
//		strRightPath = strCurPath.Mid(nIndex+1);
//	}
//	
//}

void CPttAtsTransTool::TransElement_MacroTest_ParasEx(CPNTplElement *pElement, CMacroMap *pMacroMap)
{
	POS pos = pElement->GetHeadPosition();
	CPNTplEquation *pEquationValue = NULL;
	CPNTplEquation *pEquationID = NULL;
	CPNTplGroup *pGroup = NULL;
	CMacroTestPara *pMacroTestPara = m_pCurMacroTestPara;
	CString strAtsParaID, strAtsParaValue;

	while (pos != NULL)
	{
		pGroup = (CPNTplGroup *)pElement->GetNext(pos);
		pEquationID = (CPNTplEquation *)pGroup->FindByID(PTT_KEY_DATA_ATTR_ID);
		pEquationValue = (CPNTplEquation *)pGroup->FindByID(PTT_KEY_DATA_ATTR_V);

		if (pEquationID == NULL || pEquationValue == NULL)
		{
			continue;
		}

		if (!pMacroMap->MapPara(pEquationID->m_strValue, pEquationValue->m_strValue, strAtsParaID, strAtsParaValue))
		{
			continue;
		}

		if (!IsStringNumber(strAtsParaValue))
		{
			//如果是表达式，则进行表达式处理
			TransElement_MacroTest_Paras_Expr(strAtsParaValue, pMacroMap);
		}

		pMacroTestPara->UpdateMacroTestParaData(strAtsParaID, strAtsParaValue, TRUE);
	}
}

void CPttAtsTransTool::TransElement_MacroTest_Paras_Expr(CString &strAtsParaValue, CMacroMap *pMacroMap)
{
	CStringVariableReplace oReplace;
	CEpExpression oExpression;
	CEpExpVariable *pVar = NULL;
	CString strScript = strAtsParaValue;
	oExpression.ChangeEpExpression(strAtsParaValue);
	POS pos = oExpression.GetHeadPosition();
	CString strExprVar_Ats, strTemp;
	CDataSet *pSetting = (CDataSet*)GetDvmDataset_Setting();

	while (pos != NULL)
	{
		pVar = oExpression.GetNext(pos);
		CSysParas *pSysParas = m_pDevice->GetSysParas();

		if (pSysParas != NULL)
		{
			if (pSysParas->FindByID(pVar->m_strVarID) != NULL)
			{
				//如果是测试参数，则不需要处理
				continue;
			}
		}

		if (pSetting != NULL)
		{
			if (pSetting->FindByID(pVar->m_strVarID) != NULL)
			{//定值，需要带上绝对的路径
				strTemp.Format(_T("Prot$dsSetting$%s"), pVar->m_strVarID);
				oReplace.Replace(strScript, pVar->m_strVarID, strTemp);
				continue;
			}
		}

		//如果是功能参数，则进行映射和转换
		if (pMacroMap->MapPara(pVar->m_strVarID, strExprVar_Ats))
		{
			oReplace.Replace(strScript, pVar->m_strVarID, strExprVar_Ats);
		}
	}

	strAtsParaValue = strScript;
}


/*
ASSESSTRIPATIMEF=(TRIPATIMEF>0.001)&(TRIPATIMEF<T02);
ASSESSTRIPBTIMEF=(TRIPBTIMEF>0.001)&(TRIPBTIMEF<T02);
ASSESSTRIPCTIMEF=(TRIPCTIMEF>0.001)&(TRIPCTIMEF<T02);
ASSESSRECLOSETIME=RECLOSETIME<0.001;
ASSESSTRIPTIMES=TRIPTIMES<0.001;
UAC=AC5A-9;
UBC=AC5A-10;
UCC=AC5A-11;
*/
void CPttAtsTransTool::TransElement_MacroTest_RsltScript(CPNTplElement *pElement, CMacroTest *pMacroTest, CMacroMap *pMacroMap)
{
	POS pos = pElement->GetHeadPosition();
	CPNTplEquation *pEquation = NULL;
//	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	CString strAtsParaID, strAtsParaValue;
	CString strVariables, strExpr, strRslt;
	CExBaseList listVars;

	while (pos != NULL)
	{
		pEquation = (CPNTplEquation *)pElement->GetNext(pos);

		if (pEquation->m_strName.GetLength() <= 6 || pEquation->m_strValue.GetLength() == 0)
		{//变量ID太短（ASSCESS前缀）或者变量值为空，则不处理
			continue;
		}

		if (pEquation->m_strName.Left(6) != PTT_KEY_ASSESS)
		{//变量ID不包含ASSCESS，则不处理
			continue;
		}

		TransElement_MacroTest_RsltScript_Var(listVars, pEquation, strExpr, pMacroMap);
	}

	CScriptText *pScript = pMacroTest->GetResultScriptText();

	//变量定义
	TransElement_MacroTest_RsltScript_VarDef(listVars, pScript->m_strScriptText);

	//脚本
	pScript->m_strScriptText += strExpr;

	//结果设置部分
	TransElement_MacroTest_RsltScript_VarSet(listVars, pScript->m_strScriptText);
}

void CPttAtsTransTool::TransElement_MacroTest_RsltScript_Var(CExBaseList &listVars, CPNTplEquation *pEquation, CString &strExpr, CMacroMap *pMacroMap)
{
	CDataSet *pSetting = (CDataSet*)GetDvmDataset_Setting();
	CSysParas *pSysParas = m_pDevice->GetSysParas();
	ASSERT(pSetting != NULL && pSysParas != NULL);
	CString strAtsRsltParaID, strTemp, strExprVar_Ats;

	if (!pMacroMap->MapPara(pEquation->m_strName, strAtsRsltParaID))
	{//变量没有映射，则不处理
		return;
	}

	CStringVariableReplace oReplace;
	CEpExpression oExpression;
	CEpExpVariable *pVar = NULL;
	CString strScript = pEquation->m_strValue;

	if (strScript.Find(_T("ABS(")>0))//zhouhj20190724
	{
		strScript.Replace(_T("ABS("),_T("math.abs("));
//		strScript = pEquation->m_strValue;
	}

	oExpression.ChangeEpExpression(pEquation->m_strValue);
	POS pos = oExpression.GetHeadPosition();

	//结果变量
	NewRsltExprVar(&listVars, strAtsRsltParaID, RsltExprVar_type_MacroRslt);

	while (pos != NULL)
	{
		pVar = oExpression.GetNext(pos);
		
		if (IsSettingSysPara(pVar->m_strVarID)||IsVarMacroPara(pVar->m_strVarID))
		{
			//测试参数或者定值或TestMicro中data：转换为LUA脚本临时变量
			strTemp.Format(_T("v%s"), pVar->m_strVarID);
			NewRsltExprVar(&listVars, pVar->m_strVarID);
			oReplace.Replace(strScript, pVar->m_strVarID, strTemp);
		}
		else if (pMacroMap->MapPara(pVar->m_strVarID, strExprVar_Ats))
		{
			//PowerTest变量，转换为LUA脚本临时变量
			strTemp.Format(_T("v%s"), strExprVar_Ats);
			NewRsltExprVar(&listVars, strExprVar_Ats, RsltExprVar_type_MacroPara);
			oReplace.Replace(strScript, pVar->m_strVarID, strTemp);
		}
	}

	strScript.Replace(_T("&"), _T("and"));
	strScript.Replace(_T("|"), _T("or"));
	strExpr.AppendFormat(_T("v%s=%s;\r\n"), strAtsRsltParaID, strScript);
}

void CPttAtsTransTool::TransElement_MacroTest_RsltScript_VarDef(CExBaseList &listVars, CString &strScript)
{
	POS pos = listVars.GetHeadPosition();
	CRsltExprVar *pExprVar = NULL;

	while (pos != NULL)
	{
		pExprVar = (CRsltExprVar *)listVars.GetNext(pos);
		pExprVar->AppendVarDefScript(strScript);
	}
}

void CPttAtsTransTool::TransElement_MacroTest_RsltScript_VarSet(CExBaseList &listVars, CString &strScript)
{
	POS pos = listVars.GetHeadPosition();
	CRsltExprVar *pExprVar = NULL;
	CString strScriptAnd;
	BOOL bFirst = TRUE;
	//strScript.AppendFormat(_T("local vString;\r\n"));
	CString strDef;
	CGbScriptGenerateTool::GetVariableDefine_vString(strDef, m_pGuideBook);
	strScript += strDef;

	while (pos != NULL)
	{
		pExprVar = (CRsltExprVar *)listVars.GetNext(pos);
		pExprVar->AppendVarSetScript(strScript);
		pExprVar->AppendVarAndExpr(strScriptAnd, bFirst);
		bFirst = FALSE;
	}

	//strScript.AppendFormat(_T("If (v%s) then\r\n%s%s%s%s"), strScriptAnd, _T("SetRsltJdg(\"\", 1);\r\n"), _T("Else\r\n"), _T("SetRsltJdg(\"\", 0);\r\n") , _T("End\r\n"));
	if (strScriptAnd.GetLength() > 0)
	{
		strScript.AppendFormat(_T("if (%s) then\r\n"), strScriptAnd);
		strScript += _T("    SetRsltJdg(\"\", 1);\r\n");
		strScript += _T("else\r\n");
		strScript += _T("    SetRsltJdg(\"\", 0);\r\n");
		strScript += _T("end\r\n");
	}
}

void CPttAtsTransTool::TransElement_TestItem_Safety(const CString &strHint, const CString &strItemName)
{
	CSafety *pSafety = new CSafety();
	pSafety->m_strName.Format(_T("HINT: %s"), strItemName);
	pSafety->m_strID = pSafety->m_strName;
	CExBaseList *pMsgs = pSafety->GetMsgs();
	CMsg *pMsg = new CMsg();
	pMsg->m_strMsg = strHint;
	pMsgs->AddNewChild(pMsg);

	m_pItems_ProtectionRelay->AddNewChild(pSafety);
}

void CPttAtsTransTool::Trans_ComboBox_SysParas_Settings(CPNTplElement *pElement)
{
	Trans_ComboBox_Dataset(pElement ,m_pDevice->GetSysParas());
	Trans_ComboBox_Dataset(pElement ,(CDataSet*)GetDvmDataset_Setting());
	Trans_ComboBox_Dataset(pElement ,&m_oBinaryDataset);
}

//将ComboBox类型的系统参数或定值，直接替换为实际值
void CPttAtsTransTool::Trans_ComboBox_Dataset(CPNTplElement *pElement ,CDataSet *pDataset)
{
	CDataObj *pDataObj = NULL;
	CPNTplEquation *pPNTplEquation = NULL;
	POS pos_data = pDataset->GetHeadPosition();

	while(pos_data)
	{
		pDataObj = (CDataObj *)pDataset->GetNext(pos_data);

		if (pDataObj->m_strDataType != PTT_KEY_DATA_TYPE_COMBOBOX)
		{
			continue;
		}

		pPNTplEquation = pElement->FindEquationByValue(pDataObj->m_strID);

		if (pPNTplEquation != NULL)
		{
			pPNTplEquation->m_strValue = pDataObj->m_strValue;
		}
	}
}


void CPttAtsTransTool::Trans_MacroMap_Exprs(CPNTplElement *pElement, CMacroMap *pMacroMap)
{
	POS pos = pMacroMap->GetHeadPosition();
	CExBaseObject *p = NULL;

	//遍历各表达式对象，处理表达式对象
	while (pos != NULL)
	{
		p = pMacroMap->GetNext(pos);

		if (p->GetClassID() != MPCLASSID_CPARAMAPEXPR)
		{
			continue;
		}

		Trans_MacroMap_Expr(pElement, (CParaMapExpr*)p);
	}
}


void CPttAtsTransTool::Trans_MacroMap_Expr(CPNTplElement *pElement, CParaMapExpr *pParaMapExpr)
{
	//计算表达式的值
	BOOL bTrue = FALSE;

	//缺省模式，如果不定义表达式条件，则认为是正确的
	if (pParaMapExpr->m_strExpr.GetLength() == 0)
	{
		bTrue = TRUE;
	}
	else
	{
		double dVal = Trans_MacroMap_CalExpr(pParaMapExpr->m_strExpr);//计算para-map-expr中m_strExpr的值
		bTrue = dVal > 0.1;
	}

	if (!bTrue)
	{
		return;
	}

	//遍历表达式下面的各个计算公式，进行处理
	POS pos = pParaMapExpr->GetHeadPosition();
	CParaMapCal *p = NULL;

	while (pos != NULL)
	{
		p = (CParaMapCal*)pParaMapExpr->GetNext(pos);

		if (p->GetClassID() != MPCLASSID_CPARAMAPCAL)
		{
			continue;
		}

		Trans_MacroMap_Expr_Cal(pElement,  p);
	}
}

//计算公式para-map-cal处理，计算公式的值，然后添加到测试功能参数中。
void CPttAtsTransTool::Trans_MacroMap_Expr_Cal(CPNTplElement *pElement, CParaMapCal *pParaMapCal)
{
	//计算脚本执行
	CEpExpression oExpression;
	CEpExpVariable *pVar = NULL;
	oExpression.ChangeEpExpression(pParaMapCal->m_strScript);
	POS pos = oExpression.GetHeadPosition();

	while (pos != NULL)
	{
		pVar = oExpression.GetNext(pos);
		pVar->m_dValue = Trans_MacroMap_GetValueByVarID(pVar->m_strVarID);//获取变量的值
	}

	double dValCal = 0;
	int nError = oExpression.Value(dValCal);

	//更新测试功能的参数
	CMacroTestPara *pMacroTestPara = m_pCurMacroTestPara;
	CString strAtsParaValue;
	strAtsParaValue.Format(_T("%f"), dValCal);
	pMacroTestPara->UpdateMacroTestParaData(pParaMapCal->m_strMapID, strAtsParaValue, TRUE);
}

//计算表达式的值：strExpr中所有的变量，都是PowerTest中定义的变量
double CPttAtsTransTool::Trans_MacroMap_CalExpr(const CString &strExpr)
{
	double dValCal = 0;

	if (IsStringNumber(strExpr))
	{
		dValCal = CString_To_double(strExpr);
		return dValCal;
	}

	//计算表达式的值
	CEpExpression oExpression;
	CEpExpVariable *pVar = NULL;
	oExpression.ChangeEpExpression(strExpr);
	POS pos = oExpression.GetHeadPosition();

	while (pos != NULL)
	{
		pVar = oExpression.GetNext(pos);
		pVar->m_dValue = Trans_MacroMap_GetValueByVarID(pVar->m_strVarID);
	}

	int nError = oExpression.Value(dValCal);

	if (nError != 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("[%s] error!"), strExpr);
	}

	return dValCal;
}

double CPttAtsTransTool::Trans_MacroMap_GetEquationVal(CPNTplEquation *pEquation)
{
	//如果已经计算，则返回
	if (pEquation->HasCal())
	{
		return pEquation->GetValue();
	}

	//计算等值的值，并设置等式的值
	CString strValue;
	GetEquationMapValue(pEquation,strValue);

	double dValCal = Trans_MacroMap_CalExpr(strValue);   //递归调用
	pEquation->SetValueCal(dValCal);

	return dValCal;

#if 0
	if (IsStringNumber(pEquation->m_strValue))
	{
		dValCal = CString_To_double(pEquation->m_strValue);
		pEquation->SetValueCal(dValCal);
		return;
	}
	
	//计算表达式的值
	CEpExpression oExpression;
	CEpExpVariable *pVar = NULL;
	oExpression.ChangeEpExpression(pEquation->m_strValue);
	POS pos = oExpression.GetHeadPosition();

	while (pos != NULL)
	{
		pVar = oExpression.GetNext(pos);
		pVar->m_dValue = Trans_MacroMap_GetValueByVarID(pVar->m_strVarID);
	}

	int nError = oExpression.Value(dValCal);

	//设置等式的计算值
	pEquation->SetValueCal(dValCal);

	if (nError != 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, )
	}

	return dValCal;
#endif
}

BOOL CPttAtsTransTool::GetEquationMapValue(CPNTplEquation *pEquation,CString &strValue)
{
	strValue = pEquation->m_strValue;

	if (m_pCurMacroMap == NULL)
	{
		return FALSE;
	}

	CParaMap *pParaMap = (CParaMap*)m_pCurMacroMap->FindByID(pEquation->m_strName);

	if (pParaMap == NULL)
	{
		return FALSE;
	}

	return pParaMap->GetMapValue(strValue);
}

//获取变量的值
double CPttAtsTransTool::Trans_MacroMap_GetValueByVarID(const CString &strVarID)
{
	//查找PowerTest变量
	CPNTplEquation *pFind = Trans_MacroMap_FindValueByVarID(strVarID);

	if (pFind == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Powertest Tpl Variable [%s] not exist!"), strVarID);
		return 1.0;
	}

	//计算PowerTest变量的值
	return Trans_MacroMap_GetEquationVal(pFind);
}

//查找PowerTest的变量
CPNTplEquation* CPttAtsTransTool::Trans_MacroMap_FindValueByVarID(const CString &strVarID)
{
	CPNTplEquation *pFind = NULL;

	//是否为定值
	if (m_pElementSetting != NULL)
	{
		pFind = m_pElementSetting->FindEquationEx(strVarID);

		if (pFind != NULL)
		{
			return pFind;
		}
	}

	//是否为通用参数
	if (m_pElementCommonPara != NULL)
	{
		pFind = m_pElementCommonPara->FindEquationEx(strVarID);

		if (pFind != NULL)
		{
			return pFind;
		}
	}

	//测试项目参数
	if (m_pElementTestItem != NULL)
	{
		pFind = m_pElementTestItem->FindEquation(strVarID);

		if (pFind != NULL)
		{
			return pFind;
		}
	}

	//开关量参数
	if (m_pElementBinary != NULL)
	{
		pFind = m_pElementBinary->FindEquationEx(strVarID);

		if (pFind != NULL)
		{
			return pFind;
		}
	}

	return NULL;
}

BOOL CPttAtsTransTool::GetKeyValue(CExBaseList *pList, const CString &strKey, CString &strValue)
{
	CExBaseObject *pFind = pList->FindByName(strKey);

	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pFind->GetClassID() == MNGRCLASSID_CPNTPLEQUATION)
	{
		strValue = ((CPNTplEquation*)pFind)->m_strValue;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CPttAtsTransTool::GetKeyValue(CExBaseList *pList, const CString &strKey, float &fValue)
{
	CExBaseObject *pFind = pList->FindByName(strKey);

	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pFind->GetClassID() == MNGRCLASSID_CPNTPLEQUATION)
	{
		fValue = CString_To_double(((CPNTplEquation*)pFind)->m_strValue);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CPttAtsTransTool::GetKeyValue(CExBaseList *pList, const CString &strKey, long &nValue)
{
	CExBaseObject *pFind = pList->FindByName(strKey);

	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pFind->GetClassID() == MNGRCLASSID_CPNTPLEQUATION)
	{
		nValue = CString_To_long(((CPNTplEquation*)pFind)->m_strValue);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CPttAtsTransTool::TransElement_Dataset(CExBaseList *pDataset, CPNTplElement *pElement)
{
	POS pos = pElement->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pElement->GetNext(pos);

		if (p->GetClassID() == MNGRCLASSID_CPNTPLGROUP)
		{
			TransGroup(pDataset, (CPNTplGroup*)p);
		}
	}
}

/*
N1=故障前时间;L1=3;U1=秒;T1=Edit;V1=0.500;ID1=PreFaultTime;RE1=0;RT1=0;RN1=0;
N2=故障时间;L2=3;U2=秒;T2=Edit;V2=0.500;ID2=FaultTime;RE2=0;RT2=0;RN2=0;
N3=断路器模拟;T3=ComboBox;Num3=2;V3=0;S31=不模拟;S32=模拟;ID3=BCSIMULATION;RE3=0;RT3=0;RN3=0;
*/
void CPttAtsTransTool::TransGroup(CExBaseList *pDataset, CPNTplGroup *pGroup)
{
	CString strName ,strID, strValue,strType;
	GetKeyValue(pGroup, PTT_KEY_DATA_ATTR_N, strName);
	GetKeyValue(pGroup, PTT_KEY_DATA_ATTR_ID, strID);
	GetKeyValue(pGroup, PTT_KEY_DATA_ATTR_V, strValue);
	GetKeyValue(pGroup, PTT_KEY_DATA_ATTR_T, strType);

//	TransSpecialCharacters(strName);

//	CDataObj *pData = (CDataObj*)pDataset->FindByName(strName);
	CDataObj *pData = (CDataObj*)pDataset->FindByID(strID);
	
	if (pData == NULL)
	{
		pData = new CDataObj();
		pDataset->AddNewChild(pData);
	}
	else
	{
		if (strValue != pData->m_strValue)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("[%s] [%s] != [%s]"), strName, strValue, pData->m_strValue);
		}
	}

	pData->m_strName = strName;
	pData->m_strID = strID;
	pData->m_strValue = strValue;
	pData->m_strDefaultValue = strValue;
	pData->m_strDataType = strType;

//	GetKeyValue(pGroup, PTT_KEY_DATA_ATTR_ID, pData->m_strID);
	GetKeyValue(pGroup, PTT_KEY_DATA_ATTR_U, pData->m_strUnit);
}

void CPttAtsTransTool::TransSpecialCharacters(CString &strName)
{
	strName.Replace(_T("<"),_T("_LessThan_"));
	strName.Replace(_T("$"),_T("_USD_"));
}

CExBaseList* CPttAtsTransTool::GetDvmDataset_Setting()
{
	CCpus *pCpus = m_pDevice->GetCpus();
	CCpu *pProt = (CCpu*)pCpus->FindByID(PTT_ATS_TRANS_ID_PROT_CPU);

	if (pProt == NULL)
	{
		pProt = new CCpu();
		pProt->m_strName = PTT_ATS_TRANS_ID_PROT_CPU;
		pProt->m_strID = PTT_ATS_TRANS_ID_PROT_CPU;
		pCpus->AddNewChild(pProt);
		pProt->InitAfterRead();
	}

	CDataSet *pSetting = (CDataSet*)pProt->FindByID(PTT_ATS_TRANS_ID_DSSETTING);

	if (pSetting == NULL)
	{
		pSetting = new CDataSet();
		pProt->AddNewChild(pSetting);
		pSetting->m_strName = PTT_ATS_TRANS_ID_DSSETTING;
		pSetting->m_strID = PTT_ATS_TRANS_ID_DSSETTING;
	}

	return pSetting;
}

BOOL CPttAtsTransTool::IsSettingSysPara(const CString &strVar)
{
	CSysParas *pSysParas = m_pDevice->GetSysParas();

	if (pSysParas != NULL)
	{
		if (pSysParas->FindByID(strVar) != NULL)
		{
			return TRUE;
		}
	}

	CDataSet *pSetting = (CDataSet*)GetDvmDataset_Setting();

	if (pSetting != NULL)
	{
		if (pSetting->FindByID(strVar) != NULL)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CPttAtsTransTool::IsVarMacroPara(const CString &strVar)
{
	if (m_pCurMacroTestPara->IsOwnMacroTestData(strVar))
	{
		return TRUE;
	}

	return FALSE;
}

void CPttAtsTransTool::NewRsltExprVar(CExBaseList *pList, const CString &strVar)
{
	CSysParas *pSysParas = m_pDevice->GetSysParas();

	if (pSysParas != NULL)
	{
		if (pSysParas->FindByID(strVar) != NULL)
		{
			NewRsltExprVar(pList, strVar, RsltExprVar_type_SysPara);
			return;
		}
	}

	CDataSet *pSetting = (CDataSet*)GetDvmDataset_Setting();

	if (pSetting != NULL)
	{
		if (pSetting->FindByID(strVar) != NULL)
		{
			NewRsltExprVar(pList, strVar, RsltExprVar_type_Setting);
			return;
		}
	}

	NewRsltExprVar(pList, strVar, RsltExprVar_type_MacroRslt);
}


void CPttAtsTransTool::NewRsltExprVar(CExBaseList *pList, const CString &strVar, UINT nVarType)
{
	CRsltExprVar *pVar = (CRsltExprVar*)pList->FindByID(strVar);

	if (pVar != NULL)
	{
		return;
	}

	pVar = new CRsltExprVar();
	pVar->m_strID = strVar;
	pVar->m_nVarType = nVarType;
	pVar->m_pGuideBook = m_pGuideBook;
	pList->AddTail(pVar);
}


#include "StdAfx.h"
#include "SttGuideBookGenServer.h"
#ifndef _not_use_autotest_
#include "../../../AutoTest/Module/TCtrlCntrWorkSpace.h"
#endif

CSttGuideBookGenServer::CSttGuideBookGenServer(void)
{
}

CSttGuideBookGenServer::~CSttGuideBookGenServer(void)
{
}

void CSttGuideBookGenServer::InitGbGenSysPath(const CString &strSysPath)
{
	m_oTool.InitGbGenSysPath(strSysPath);
}

/*
<ats-cmd name="" id="GenerateTemplate" testor="ATS">
	<paras name="" id="">
		<data name="����ģ�巵��ģʽ" id="TtRetMode" data-type="" value=""/>
		<data name="���������" id="HasDigital" data-type="" value="1" />
		<group name="test-macro-ui" id="test-macro-ui" data-type="" value="">
			<data name="TestMacroUI" id="TestMacroUI" data-type="" value="ZeroTest"/>
			<data name="gen-file" id="gen-file" data-type="" value="Zero_GbGen.xml"/>
			<data name="ui-file" id="ui-file" data-type="" value="Zero_UI.html"/>
			<data name="ui-para-file" id="ui-para-file" data-type="" value="Zero_Paras.xml"/>
			<data name="report-file" id="report-file" data-type="" value="Zero_Report.html"/>
			<data name="hd-rs-file" id="hd-rs-file" data-type="" value="ChMapConfig.4u3i"/>
		</group>
		<group id="macro-ui-paras" name="macro-ui-paras">
			<data name="" id="" data-type="" value=""/>
			...............................
		</group>
		<contents id="characteristic" data-type="characteristic">
			<![CDATA[�˴�Ϊcharacteristics�����xml�ı�]]>
		</contents>
	</paras>
</ats-cmd>
*/
long CSttGuideBookGenServer::Process_Cmd_Ats_GenerateTemplate( CDataGroup *pSttParas )
{
	m_oTool.Reset();
	CDataGroup *pTestMacroUI = (CDataGroup *)pSttParas->FindByID(STT_CMD_PARA_TestMacroUI);

	if (pTestMacroUI == NULL)
	{
		
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("ȱ��[%s]�����ɿղ���ģ�壡"), STT_CMD_PARA_TestMacroUI);
		return 0;
	}

	BOOL bRet = m_oTool.Init(pTestMacroUI);

	if (!bRet)
	{
		return -1;
	}

	CString strMacroID;
	pTestMacroUI->GetDataValue(STT_CMD_PARA_TestMacroUI_ID, strMacroID);
	CDataGroup *pUIParas = (CDataGroup *)pSttParas->FindByID(STT_CMD_PARA_MacroUIParas);
	CDataGroup *pCommCmd = (CDataGroup *)pSttParas->FindByID(STT_CMD_PARA_CommCmd);
	CSttContents *pContents = (CSttContents *)pSttParas->FindByID(STT_CMD_PARA_Characteristic);

    if (pUIParas != NULL)
	{
		//���½���������ڴ�
		m_oTool.UpdateUIParas(pUIParas);
	}

	//����ͨѶ��������
	m_oTool.UpdateCommCmd(pCommCmd);

	if (pContents != NULL)
	{
		//������������
		m_oTool.SetCharacteristics(pContents);
	}

	CString strTestClass, strDvmFile;
    pSttParas->GetDataValue(STT_CMD_PARA_HasDigital, m_oTool.m_bHasDigital);
    pSttParas->GetDataValue(STT_CMD_PARA_GenForDebug, m_oTool.m_nGenWithDebug);
	pSttParas->GetDataValue(STT_CMD_PARA_DvmFile, strDvmFile);
	pSttParas->GetDataValue(STT_CMD_PARA_TestClass, strTestClass);

	if (strTestClass.GetLength() > 0)
	{
		m_oTool.m_strTestClass = strTestClass;
	}

	if (strDvmFile != m_oTool.m_strDvmFile)
	{
		m_oTool.m_strDvmFile = strDvmFile;
		m_oTool.Init_DvmDevice();
#ifndef _not_use_autotest_
		CTCtrlCntrWorkSpace::s_SetPpDeviceFile(strDvmFile);
#endif
		CGuideBook *pGuideBook = m_oTool.GetGuideBook();
		pGuideBook->m_strDeviceModelFile = strDvmFile;
	}

    m_oTool.GenGuideBook(strMacroID,  strMacroID);
	//shaolei 20220211  ��Ϊ���ӻ���ģ���ȡ�����Ƕ�̬����
    //m_oTool.GenGuideBook_BeforeTest_FromFile(strMacroID);
    //m_oTool.SaveGbXmlFile(pTestMacroUI->m_strID);
	//m_oTool.GenGuideBook_BeforeTest(strMacroID);   ������λ����û��Ӳ��ͨ�����ã�IEC���õȹ��ܣ���ʱ�����ɸ�������Ŀ

	return 0;
}

long CSttGuideBookGenServer::Process_Cmd_Ats_GenerateItems( CDataGroup *pSttParas )
{
	CString strTestClass, strDvmFile;
	pSttParas->GetDataValue(STT_CMD_PARA_DvmFile, strDvmFile);
	pSttParas->GetDataValue(STT_CMD_PARA_TestClass, strTestClass);

	if (strTestClass.GetLength() > 0)
	{
		m_oTool.m_strTestClass = strTestClass;
	}

	if (strDvmFile != m_oTool.m_strDvmFile && !strDvmFile.IsEmpty())
	{
		m_oTool.m_strDvmFile = strDvmFile;
		m_oTool.Init_DvmDevice();
#ifndef _not_use_autotest_
		CTCtrlCntrWorkSpace::s_SetPpDeviceFile(strDvmFile);
#endif
		CGuideBook *pGuideBook = m_oTool.GetGuideBook();
		pGuideBook->m_strDeviceModelFile = strDvmFile;
	}

	m_oTool.OpenCommCmdWzdCfgFile();
	CDataGroup *pGenerateItems = (CDataGroup *)pSttParas->FindByID(STT_CMD_PARA_generate_items);

	if (pGenerateItems != NULL)
	{
		return m_oTool.GenerateItemsOnly(pSttParas);
	}

	//m_oTool.Reset();
	CDataGroup *pTestMacroUI = (CDataGroup *)pSttParas->FindByID(STT_CMD_PARA_TestMacroUI);

	if (pTestMacroUI == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("��������ȱ�١�%s��������ģ������ʧ�ܣ�"), STT_CMD_PARA_TestMacroUI);
		return -1;
	}

	BOOL bRet = m_oTool.Init(pTestMacroUI);

	if (!bRet)
	{
		return -1;
	}

	CString strMacroID, strParentItemPath, strItemsName, strItemsID;
	pTestMacroUI->GetDataValue(STT_CMD_PARA_TestMacroUI_ID, strMacroID); //���Թ���ID   GradientTest��Ҫ���⴦���������������
	pSttParas->GetDataValue(STT_CMD_PARA_ParentItemsPath, strParentItemPath);
	pSttParas->GetDataValue(STT_CMD_PARA_generate_items_ItemsName, strItemsName);
	pSttParas->GetDataValue(STT_CMD_PARA_generate_items_ItemsID, strItemsID);
	CDataGroup *pUIParas = (CDataGroup *)pSttParas->FindByID(STT_CMD_PARA_MacroUIParas);

	if (pUIParas != NULL)
	{
		//���½���������ڴ�
		m_oTool.UpdateUIParas(pUIParas);
	}

	if (strMacroID == STT_CMD_ATS_MACRO_ID_GradientTest)
	{
		//���ظ���λ����ģ���У�����Ҫ���в��Թ���ID���滻�����Ǹ����Եײ�����͵�ָ������Ҫ����ID�滻
		//���ע�ʹ˴�  saholei 20220416
		//m_oTool.GenGbItem_MacroID_Revise(strMacroID, pUIParas);
	}

	CDataGroup *pCommCmd = (CDataGroup *)pSttParas->FindByID(STT_CMD_PARA_CommCmd);
	CSttContents *pContents = (CSttContents *)pSttParas->FindByID(STT_CMD_PARA_Characteristic);

	if (pUIParas != NULL)
	{
		//���½���������ڴ�
		m_oTool.UpdateUIParas(pUIParas);
	}

	//����ͨѶ��������
	m_oTool.UpdateCommCmd(pCommCmd);

	if (pContents != NULL)
	{
		//������������
		m_oTool.SetCharacteristics(pContents);
	}

	m_oTool.GenGuideBook_Items(strMacroID, strMacroID, strParentItemPath, strItemsName, strItemsID);


	//for debug begin
 	 	CString strPath = _P_GetTemplatePath();
 	 	strPath += _T("0x0x01.gbxml");
		CGuideBook *pGuideBook = GetGuideBook();
 	 	pGuideBook->SaveXMLFile(strPath);
	//for debug end

	return 0;
}

long CSttGuideBookGenServer::Process_Cmd_Ats_SetItemPara( CDataGroup *pSttParas )
{
    CString strItemPath, strMacroID;
	pSttParas->GetDataValue(STT_CMD_PARA_ItemPath, strItemPath);
    pSttParas->GetDataValue(STT_CMD_PARA_MacroID, strMacroID);

	CDataGroup *pItemsParas = (CDataGroup *)pSttParas->FindByID(STT_CMD_PARA_ItemParas);
    CSttContents *pContents = (CSttContents *)pSttParas->FindByID(STT_CMD_PARA_ContentsParas);

	if (pItemsParas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("��������ȱ�١�%s����������Ŀ��������ʧ�ܣ�"), STT_CMD_PARA_ItemParas);
		return -1;
	}

    BOOL bRet = m_oTool.SetItemPara(strMacroID, strItemPath, pItemsParas, pContents);

	if (!bRet)
	{
		return -1;
	}

	return 0;
}

long CSttGuideBookGenServer::Process_Cmd_Ats_SetItemPara_SystemConfig(CDataGroup *pSttParas)
{
    long nHasDigital = 0;
    CSttContents *pContents = (CSttContents *)pSttParas->FindByID(STT_CMD_PARA_ContentsParas);

    if(pContents == NULL)
    {
        return 0;
    }

    CSttMacro *pSttMacro = new CSttMacro;
    pSttMacro->SetCreateMacroChild(TRUE);
    BSTR bstrText = pContents->m_strText.AllocSysString();
    CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
    pSttMacro->SetXml(bstrText, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
    CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
#ifdef _PSX_IDE_QT_
    delete bstrText;
#else
    SysFreeString(bstrText);// �����ͷ�
#endif

    CSttParas *pItemParas = pSttMacro->GetParas();
    pItemParas->GetDataValue(STT_CMD_PARA_HasDigital, nHasDigital);
    m_oTool.SetItemPara_SystemConfig(nHasDigital);
	m_oTool.SetSysParameter(pSttMacro);

    return 0;
}

UINT CSttGuideBookGenServer::GetTemplateGenMode()
{
	return m_oTool.GetTemplateGenMode();
}

void CSttGuideBookGenServer::SetTemplateGenMode(UINT nMode)
{
	m_oTool.SetTemplateGenMode(nMode);
}

BOOL CSttGuideBookGenServer::Is_GenerateItems_CmdWzd()
{
	return m_oTool.m_bGenerateItemsOnly_CmdWzd;
}

CDataGroup* CSttGuideBookGenServer::GetGenrateItems_CmdWzd_Reply()
{
	return &m_oTool.m_oGroupCmdWzdReply;
}
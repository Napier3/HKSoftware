#include "stdafx.h"
#include "SttMacroParaEditViewOriginal.h"
#include "../Module/SttTest/Common/tmt_system_config.h"
#include "../Module/SttCmd/SttParas.h"
#include "../Module/SttCmd/SttMacro.h"
#include "../Module/UI/Interface/SttHtmlViewApi.h"
#include "../SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"
#include "../../XLangResource_Native.h"

void GlobalSetQcheckState_BinaryIn(QCheckBox *pBinaryInCheck,tmt_BinaryIn *pBinaryIn,int nBinIndex)
{

	if (nBinIndex<g_nBinCount)
	{
		pBinaryInCheck->setChecked(pBinaryIn[nBinIndex].nSelect);
	} 
	else
	{
		pBinaryIn[nBinIndex].nSelect = 0;
		pBinaryInCheck->setChecked(false);
		pBinaryInCheck->setEnabled(false);
	}
}

void GlobalSetQcheckState_BinaryOut(QCheckBox *pBinaryOutCheck,tmt_BinaryOut *pBinaryOut,int nBoutIndex)
{
	if (nBoutIndex<g_nBoutCount)
	{
		pBinaryOutCheck->setChecked(pBinaryOut[nBoutIndex].nState);
	} 
	else
	{
		pBinaryOut[nBoutIndex].nState = 0;
		pBinaryOutCheck->setChecked(false);
		pBinaryOutCheck->setEnabled(false);
	}
}

void GlobalSetQcheckEnable_Binary(QCheckBox *pBinaryInCheck,int nBinaryIndex,int nBinaryCount,bool bEanble)
{
	if (nBinaryIndex<nBinaryCount)
	{
		pBinaryInCheck->setEnabled(bEanble);
	} 
	else
	{
		pBinaryInCheck->setEnabled(false);
	}
}

CSttMacroParaEditViewOriginal::CSttMacroParaEditViewOriginal(QWidget *parent, Qt::WindowFlags flags)
{
	QWidget *pWidget = this;
	m_pMacroParaEditWnd = pWidget;

	m_bTmtParaChanged = FALSE;
	m_bChMapsChanged = TRUE;			
	m_bSystemParasChanged = FALSE;		
	m_bIECGoutMapChanged = FALSE;	
	m_bIsOpenMacroFinished = FALSE;
	m_pOriginalSttTestResource = NULL;
}

CSttMacroParaEditViewOriginal::~CSttMacroParaEditViewOriginal()
{
// 	if (m_pOriginalSttTestResource != NULL)
// 	{
// 		delete m_pOriginalSttTestResource;
// 		m_pOriginalSttTestResource = NULL;
// 	}
}

void CSttMacroParaEditViewOriginal::initTestParas()
{
	if (!OpenTestTestMngrFile(_T("")))
	{
		InitGoosePubDataGroups();
		InitFT3PubDataGroups();
	}

	InitUI_OpenParas();
}

BOOL CSttMacroParaEditViewOriginal::OpenTestTestMngrFile(const CString& strParasFile)
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}

	CDataGroup*  pDataGroup = g_theTestCntrFrame->GetTestMacroUI_Paras();

	if ((pDataGroup->GetCount()<=0)&&(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile.GetLength()>0))
	{
		stt_ui_OpenParasFile(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile,pDataGroup);
	}

	if (pDataGroup->GetCount()>0)
	{
		CSttDataGroupSerializeRead oRead(pDataGroup);

		if (g_oSttSystemConfig.GetSelSysPata())
		{
			oRead.AddSysPara(STT_XML_SERIALIZE_SYS_PARA_ID_VNom,STT_XML_SERIALIZE_SYS_PARA_ID_OldVNom,g_oSystemParas.m_fVNom/SQRT3);
			oRead.AddSysPara(STT_XML_SERIALIZE_SYS_PARA_ID_INom,STT_XML_SERIALIZE_SYS_PARA_ID_OldINom,g_oSystemParas.m_fINom);
			oRead.AddSysPara(STT_XML_SERIALIZE_SYS_PARA_ID_FNom,STT_XML_SERIALIZE_SYS_PARA_ID_OldFNom,g_oSystemParas.m_fFNom);
		}

		PTMT_PARAS_HEAD pCurrTmtPara = GetTestParas();
		SerializeTestParas(&oRead, pCurrTmtPara,g_oSttTestResourceMngr.m_pTestResouce->GetVolRsNum(),g_oSttTestResourceMngr.m_pTestResouce->GetVCurRsNum(),
			g_oLocalSysPara.m_nCHBinInExNum,g_oLocalSysPara.m_nCHBinOutExNum,g_oSystemParas.m_nHasDigital);
		//		stt_xml_serialize(pCurrTmtPara, &oRead);
		return TRUE;
	}
	

	//zhouhj 2023.8.31 后面代码废弃,统一采用参数配置文件方式
	CString strFile;

	if (!IsValidTestParasFile(strParasFile))
	{
		strFile = GetDefaultParaFile();
	}
	else
	{
		strFile = strParasFile;
	}

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("功能测试参数文件【%s】不存在")*/g_sLangTxt_Gradient_Functionalfiledtexist.GetString(),strFile.GetString()); //lcq
		return FALSE;
	}

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttXmlSerializeBase *pRootParas = NULL, *pMacroParas = NULL;
	pRootParas = oSttXmlSerializeTool.CreateXmlSerializeRead(stt_TestMacrosKey(), strFile);

	if (pRootParas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("解析功能测试参数文件【%s】失败")*/g_sLangTxt_Gradient_FailedTestParameterfile.GetString(),strFile.GetString());//lcq
		return FALSE;
	}

	long nIndex = 0;
	PTMT_PARAS_HEAD p = NULL;

	char szMacroID[TMT_PARAS_HEAD_MACROID_LEN];  
	
	const char* pCharMacroID = GetMacroID();
	pMacroParas = pRootParas->xml_serialize(pCharMacroID,pCharMacroID, "macro", stt_TestMacroKey());

	if (pMacroParas == NULL)
	{
		return FALSE;
	}

	stt_xml_serialize_ReadMacroID(pMacroParas,szMacroID);
	p = GetTestParas();

	CSttXmlSerializeBase *pXmlParas = pMacroParas->xml_serialize("paras", "paras", "paras", stt_ParasKey());
	SerializeTestParas(pXmlParas, p,g_oSttTestResourceMngr.m_pTestResouce->GetVolRsNum(),g_oSttTestResourceMngr.m_pTestResouce->GetVCurRsNum(),
		g_oLocalSysPara.m_nCHBinInExNum,g_oLocalSysPara.m_nCHBinOutExNum,g_oSystemParas.m_nHasDigital);

	return TRUE;
}

BOOL CSttMacroParaEditViewOriginal::SaveTestMngrFile(const CString& strParasFile)
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}

	if (!g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile.IsEmpty())
	{
		CDataGroup  oDataGroup;
		CSttDataGroupSerializeRegister oRegister(&oDataGroup);
		PTMT_PARAS_HEAD pCurrTmtPara = GetTestParas();
		SerializeTestParas(&oRegister, pCurrTmtPara,g_oSttTestResourceMngr.m_pTestResouce->GetVolRsNum(),g_oSttTestResourceMngr.m_pTestResouce->GetVCurRsNum(),
			g_oLocalSysPara.m_nCHBinInExNum,g_oLocalSysPara.m_nCHBinOutExNum,g_oSystemParas.m_nHasDigital);

		CString strPath;
		strPath = _P_GetDBPath();
		strPath += "atsgen/";
		strPath += g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile;
		oDataGroup.SaveXmlFile(strPath,CDataMngrXmlRWKeys::g_pXmlKeys);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
// 	CString strFile;
// 	
// 	if (!IsValidTestParasFile(strParasFile,false))
// 	{
// 		strFile = GetDefaultParaFile();
// 	}
// 	else
// 	{
// 		strFile = strParasFile;
// 	}
// 
// 	CSttXmlSerializeTool oSttXmlSerializeTool;
// 	CSttXmlSerializeBase *pRootParas = NULL, *pMacroParas = NULL;
// 	pRootParas = oSttXmlSerializeTool.CreateXmlSerializeRegister(stt_TestMacrosKey());
// 
// 	if (pRootParas == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("解析功能测试参数文件【%s】失败"),strFile.GetString());
// 		return FALSE;
// 	}
// 
// 	PTMT_PARAS_HEAD p = GetTestParas();
// 	if (p == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	pMacroParas = pRootParas->xml_serialize(p->m_pszMacroID,p->m_pszMacroID, "macro", stt_TestMacroKey());
// 
// 	if (pMacroParas == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	stt_xml_serialize(p, pMacroParas);
// 	CSttXmlSerializeBase *pXmlParas = pMacroParas->xml_serialize("paras", "paras", "paras", stt_ParasKey());
// 	SerializeTestParas(pXmlParas, p, g_oSttTestResourceMngr.m_pTestResouce->GetVolRsNum(),g_oSttTestResourceMngr.m_pTestResouce->GetVCurRsNum(),
// 		g_oLocalSysPara.m_nCHBinInExNum,g_oLocalSysPara.m_nCHBinOutExNum,g_oSystemParas.m_nHasDigital);
// 
// 	m_bTmtParaChanged = FALSE;  
// 	return oSttXmlSerializeTool.Stt_WriteFile(strFile);
}

void CSttMacroParaEditViewOriginal::UpdateSerializeSysParas()
{
	if (g_theTestCntrFrame->m_oOldSysParasList.GetCount()<=0)
	{
		return;
	}

	double dVNom = g_oSystemParas.m_fVNom/SQRT3;
	double dINom = g_oSystemParas.m_fINom;
	double dFNom = g_oSystemParas.m_fFNom;
	g_theTestCntrFrame->m_oOldSysParasList.GetDataValue(STT_XML_SERIALIZE_SYS_PARA_ID_OldVNom,dVNom);
	g_theTestCntrFrame->m_oOldSysParasList.GetDataValue(STT_XML_SERIALIZE_SYS_PARA_ID_OldINom,dINom);
	g_theTestCntrFrame->m_oOldSysParasList.GetDataValue(STT_XML_SERIALIZE_SYS_PARA_ID_OldFNom,dFNom);
	CSttSerializeUpdateSysParas oUpdateSysParas;
	oUpdateSysParas.AddSysPara(STT_XML_SERIALIZE_SYS_PARA_ID_VNom,STT_XML_SERIALIZE_SYS_PARA_ID_OldVNom
		,g_oSystemParas.m_fVNom/SQRT3, dVNom);
	oUpdateSysParas.AddSysPara(STT_XML_SERIALIZE_SYS_PARA_ID_INom,STT_XML_SERIALIZE_SYS_PARA_ID_OldINom
		,g_oSystemParas.m_fINom, dINom);
	oUpdateSysParas.AddSysPara(STT_XML_SERIALIZE_SYS_PARA_ID_FNom,STT_XML_SERIALIZE_SYS_PARA_ID_OldFNom
		,g_oSystemParas.m_fFNom, dFNom);

	if (oUpdateSysParas.m_oSysParasList.GetCount()<=0)
	{
		return;
	}

	PTMT_PARAS_HEAD pCurrTmtPara = GetTestParas();
	SerializeTestParas(&oUpdateSysParas, pCurrTmtPara,g_oSttTestResourceMngr.m_pTestResouce->GetVolRsNum(),g_oSttTestResourceMngr.m_pTestResouce->GetVCurRsNum(),
		g_oLocalSysPara.m_nCHBinInExNum,g_oLocalSysPara.m_nCHBinOutExNum,FALSE);
}

// void CSttMacroParaEditViewOriginal::UpdateSerializeTestParaBySysPara( CDataGroup* pCurrDataGroup )
// {
// 	CString strVNom, strINom, strFNom;
// 	bool bVNom = pCurrDataGroup->GetDataValue("VNom", strVNom);
// 	bool bINom = pCurrDataGroup->GetDataValue("INom", strINom);
// 	bool bFNom = pCurrDataGroup->GetDataValue("FreNom", strFNom);
// 	if (bVNom || bINom || bFNom)
// 	{
// 		UpdateUNFreNom(pCurrDataGroup);
// 	}
// }
// 
// void CSttMacroParaEditViewOriginal::UpdateUNFreNom( CDataGroup* pDataGroup )
// {
// 	if (!pDataGroup)
// 	{
// 		return;
// 	}
// 	CLogPrint::LogString(XLOGLEVEL_TRACE, ">> xiaoding test 111通用试验打开模板 >>");
// 	CString strFormat, strNom;
// 	POS pos = pDataGroup->GetHeadPosition();
// 	CExBaseObject* pExBaseObject = NULL;
// 	CDvmData* pDvmData = NULL;
// 	while (pos)
// 	{
// 		pExBaseObject = (CExBaseObject*)pDataGroup->GetNext(pos);
// 		if (pExBaseObject->GetClassID() == DVMCLASSID_CDVMDATA)
// 		{
// 			//获取pDvmData的Format
// 			pDvmData = (CDvmData*)pExBaseObject;
// 			strFormat = pDvmData->m_strFormat;
// 			if (!strFormat.IsEmpty())
// 			{
// 				bool ret = pDataGroup->GetDataValue(strFormat, strNom);
// 				double dNom = CString_To_double(strNom);
// 				double dValue = CString_To_double(pDvmData->m_strValue);
// 				//当前数据pDvmData的Value与当前数据Format对应的数据比较
// 				if (ret)
// 				{
// 					if (abs(dValue - dNom) > 0.001)
// 					{
// 						pDvmData->m_strValue = strNom;
//                         CLogPrint::LogFormatString(XLOGLEVEL_INFOR, "数据id数据类型分别为%s%s", pDvmData->m_strID.GetString(), pDvmData->m_strValue.GetString());
// 					}	
// 				}
// 			}
// 			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, "数据类型不对%d", pDvmData->GetClassID());
// 			//return;
// 		}
// 		else if (pExBaseObject->GetClassID() == DTMCLASSID_CDATAGROUP)
// 		{
// 			CDataGroup *pDataGroup = (CDataGroup*)pExBaseObject;
// 			if (pDataGroup)
// 			{
// 				UpdateUNFreNom(pDataGroup);
// 			}
// 		}
// 	}
// }

void CSttMacroParaEditViewOriginal::InitGoosePubDataGroups()
{
	m_listGoosePub.clear();
	CIecCfgGoutDatas *pSourceGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr();
	CIecCfgGoutDatas *pIecCfgGoutDatas = NULL;

	pIecCfgGoutDatas = (CIecCfgGoutDatas*)pSourceGoutDatas->Clone();
	m_listGoosePub.append(pIecCfgGoutDatas);
}
void CSttMacroParaEditViewOriginal::InitGooseGinPubDataGroups()
{
	m_listGooseGinPub.clear();
	CIecCfgGinDatas *pSourceGinDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGinMngr();
	CIecCfgGinDatas *pIecCfgGinDatas = NULL;

	pIecCfgGinDatas = (CIecCfgGinDatas*)pSourceGinDatas->Clone();
	m_listGooseGinPub.append(pIecCfgGinDatas);
}
void CSttMacroParaEditViewOriginal::InitFT3PubDataGroups()
{
	m_listFT3Pub.clear();
	CIecCfgDatasSMV *pSourceDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
	CIecCfgDatasSMV *pIecCfgDatasSMV = NULL;

	pIecCfgDatasSMV = (CIecCfgDatasSMV*)pSourceDatasSMV->Clone();
	m_listFT3Pub.append(pIecCfgDatasSMV);
} 

void CSttMacroParaEditViewOriginal::SerializeGoosePubs(CSttXmlSerializeBase *pXmlGoosePubsParent,CIecCfgGoutDatas *pGoutDatas)
{
	if (pXmlGoosePubsParent == NULL)
	{
		return;
	}

	CSttXmlSerializeBase *pXmlGouts = pXmlGoosePubsParent->xml_serialize("GOOSEPubs", "GOOSEPubs", "GOOSEPubs", stt_ParaGroupKey());

	if ((pXmlGouts != NULL)&&g_oSystemParas.m_nHasDigital)
	{
		long nRet = 0;
		CXmlRWElementBase *pElementNode = pXmlGouts->GetElement();
		CDataGroup oGoutGroup;

		if (stt_xml_serialize_is_read(pXmlGouts)&&(pXmlGouts->IsSttGroupXmlSerialize()))
		{
			pGoutDatas->ReadGouts_GroupDatas(pXmlGouts->GetDataGroup()/*&oGoutGroup*/);
		}
		else if ((stt_xml_serialize_is_write(pXmlGouts)||stt_xml_serialize_is_register(pXmlGouts))&&((pXmlGouts->IsSttGroupXmlSerialize())))
		{
			pGoutDatas->GenerateGouts_GroupDatas(pXmlGouts->GetDataGroup()/*&oGoutGroup*/);
		}
		else if (stt_xml_serialize_is_read(pXmlGouts))
		{
			CXmlRWNodeListBase *pChildNodeList = pElementNode->GetChildNodes();
 			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
 			oGoutGroup.XmlReadChildren(*pChildNodeList, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
 			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
			pGoutDatas->ReadGouts_GroupDatas(&oGoutGroup);
		}
		else if (stt_xml_serialize_is_write(pXmlGouts)||stt_xml_serialize_is_register(pXmlGouts))
		{
			CXmlRWDocBase *pRootNode = pXmlGouts->GetRWDoc();
			pGoutDatas->GenerateGouts_GroupDatas(&oGoutGroup);
 			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
 			oGoutGroup.XmlWriteChildren(*pRootNode,*pElementNode, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
 			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
		}
	}
}

void CSttMacroParaEditViewOriginal::SerializeGooseGinPubs(CSttXmlSerializeBase *pXmlGoosePubsParent,CIecCfgGinDatas *pGinDatas)
{
	if (pXmlGoosePubsParent == NULL)
	{
		return;
	}
	
	CSttXmlSerializeBase *pXmlGins = pXmlGoosePubsParent->xml_serialize("GOOSEGinPubs", "GOOSEGinPubs", "GOOSEGinPubs", stt_ParaGroupKey());
	if ((pXmlGins != NULL)&&g_oSystemParas.m_nHasDigital)
	{
		long nRet = 0;
		CXmlRWElementBase *pElementNode = pXmlGins->GetElement();
		CDataGroup oGoutGroup;

		if (stt_xml_serialize_is_read(pXmlGins)&&(pXmlGins->IsSttGroupXmlSerialize()))
		{
			pGinDatas->ReadGins_GroupDatas(pXmlGins->GetDataGroup()/*&oGoutGroup*/);
		}
		else if ((stt_xml_serialize_is_write(pXmlGins)||stt_xml_serialize_is_register(pXmlGins))&&((pXmlGins->IsSttGroupXmlSerialize())))
		{
			pGinDatas->GenerateGins_GroupDatas(pXmlGins->GetDataGroup()/*&oGoutGroup*/);
		}
		else if (stt_xml_serialize_is_read(pXmlGins))
		{
			CXmlRWNodeListBase *pChildNodeList = pElementNode->GetChildNodes();
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			oGoutGroup.XmlReadChildren(*pChildNodeList, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
			pGinDatas->ReadGins_GroupDatas(&oGoutGroup);
		}
		else if (stt_xml_serialize_is_write(pXmlGins)||stt_xml_serialize_is_register(pXmlGins))
		{
			CXmlRWDocBase *pRootNode = pXmlGins->GetRWDoc();
			pGinDatas->GenerateGins_GroupDatas(&oGoutGroup);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			oGoutGroup.XmlWriteChildren(*pRootNode,*pElementNode, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
		}			
	}
}
void CSttMacroParaEditViewOriginal::SerializeFT3Pubs(CSttXmlSerializeBase *pXmlFT3PubsParent,CIecCfgDatasSMV *pIecCfgDatasSMV)
{
	if (pXmlFT3PubsParent == NULL)
	{
		return;
	}

	CSttXmlSerializeBase *pXmlFT3=pXmlFT3PubsParent->xml_serialize("FT3Pubs", "FT3Pubs", "FT3Pubs", stt_ParaGroupKey());

	if ((pXmlFT3 != NULL)&&g_oSystemParas.m_nHasDigital)
	{
		long nRet = 0;
		CXmlRWElementBase *pElementNode = pXmlFT3->GetElement();
		CDataGroup oGoutGroup;

		if(stt_xml_serialize_is_read(pXmlFT3)&&(pXmlFT3->IsSttGroupXmlSerialize()))
		{
			pIecCfgDatasSMV->ReadSmv_GroupDatas(pXmlFT3->GetDataGroup());
		}
		else if ((stt_xml_serialize_is_write(pXmlFT3)||stt_xml_serialize_is_register(pXmlFT3))&&((pXmlFT3->IsSttGroupXmlSerialize())))
		{
			pIecCfgDatasSMV->GenerateSmv_GroupDatas(pXmlFT3->GetDataGroup());
		}
		else if (stt_xml_serialize_is_read(pXmlFT3))
		{
			CXmlRWNodeListBase *pChildNodeList = pElementNode->GetChildNodes();
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			oGoutGroup.XmlReadChildren(*pChildNodeList, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
			pIecCfgDatasSMV->ReadSmv_GroupDatas(&oGoutGroup);
		}
		else if (stt_xml_serialize_is_write(pXmlFT3)||stt_xml_serialize_is_register(pXmlFT3))
		{
			CXmlRWDocBase *pRootNode = pXmlFT3->GetRWDoc();
			pIecCfgDatasSMV->GenerateSmv_GroupDatas(&oGoutGroup);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			oGoutGroup.XmlWriteChildren(*pRootNode,*pElementNode, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
		}			
	}
}
void CSttMacroParaEditViewOriginal::SetParaChanged()
{
	if(m_bIsOpenMacroFinished)
	{
		m_bTmtParaChanged = TRUE;
	}
}

void CSttMacroParaEditViewOriginal::GetAtsCmdDataParas(CDataGroup* pDataGroup)
{
	ASSERT(pDataGroup != NULL);
	pDataGroup->DeleteAll();
/*	
	bool bRet = SaveTestMngrFile(m_strDefaultParaFile);
	if(bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("参数模板：%s保存成功."),m_strDefaultParaFile.GetString());
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("参数模板：%s保存失败."),m_strDefaultParaFile.GetString());
	}
*/
//	CSttTestCmd oSttCmd;
//	CSttMacro *pMacro = oSttCmd.GetSttMacro(TRUE,FALSE,FALSE);

	CSttMacro *pMacro = new CSttMacro();

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttXmlSerializeBase* pMacroSerializeBase = oSttXmlSerializeTool.CreateXmlSerializeWrite(pMacro);

	ASSERT(m_pSttTestResource);
	PTMT_PARAS_HEAD p = GetTestParas();

	CSttXmlSerializeBase *pXmlParas = pMacroSerializeBase->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (g_oSttSystemConfig.GetSelSysPata())//zhouhj 2024.5.19 在保存模板时固定增加该参数
	{
		double dVNom = g_oSystemParas.m_fVNom/SQRT3;
		pXmlParas->xml_serialize("额定电压", STT_XML_SERIALIZE_SYS_PARA_ID_VNom, "", "number", dVNom);
		pXmlParas->xml_serialize("额定电流", STT_XML_SERIALIZE_SYS_PARA_ID_INom, "", "number", g_oSystemParas.m_fINom);
		pXmlParas->xml_serialize("额定频率", STT_XML_SERIALIZE_SYS_PARA_ID_FNom, "", "number", g_oSystemParas.m_fFNom);
	}

	SerializeTestParas(pXmlParas, p, g_oSttTestResourceMngr.m_pTestResouce->GetVolRsNum(), 
		g_oSttTestResourceMngr.m_pTestResouce->GetVCurRsNum(),
		0,0,g_oSystemParas.m_nHasDigital);

	pMacro->SetCreateMacroChild(true);
	//只串行化ID、Value。方便判断参数是否改变
//	++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value;
	oSttXmlSerializeTool.SttXmlSerializeRead(pMacro);
//	--CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value;

	CSttParas* pParas = pMacro->GetParas();

	pParas->CopyChildren(pDataGroup);
	pDataGroup->m_strName = "macro-ui-paras";
	pDataGroup->m_strID = pDataGroup->m_strName;

	delete pMacro;
}

long CSttMacroParaEditViewOriginal::GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml)
{
	CSttItemsEmpty oItems;

	CSttCmdDefineXmlRWKeys::SetOnlyGetItem(TRUE);
	GetMacroItemsXml(oItems);
	oItems.GetHead()->m_strID = strMacroItemsID;
	long nLen = oItems.GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, ppszItemsXml, 0, _JSON_TYPE_);
	CSttCmdDefineXmlRWKeys::SetOnlyGetItem(FALSE);

	return nLen;
}

void CSttMacroParaEditViewOriginal::GetMacroItemsXml(CSttItems &oRootItems)
{
	CSttItems* pRoot = new CSttItems;
	pRoot->m_strID = GetMacroID();
	pRoot->m_nTkID = 65535;
	oRootItems.AddNewChild(pRoot);

	CSttItems* pItems = new CSttItems;
	pItems->m_strID = GetMacroID();
	pItems->m_nTkID = 65535;
	pRoot->AddNewChild(pItems);

	GetMacroItemsXml_Chs(pItems);
}

void CSttMacroParaEditViewOriginal::GetMacroItemsXml_Chs(CSttItems *pParentItems)
{
	if (g_oSttTestResourceMngr.m_pTestResouce == NULL)
	{
		return;
	}

	//更新当前电压电流通道
	POS pos = g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef.GetHeadPosition();

	while (pos)
	{
		CExBaseList* pChild = (CExBaseList*)g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef.GetNext(pos);
		CSttItemBase* pMacroTest = new CSttItemBase;
		pMacroTest->m_strID = pChild->m_strID;
		pMacroTest->m_nTkID = 65535;
		pParentItems->AddNewChild(pMacroTest);
	}

	pos = g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef.GetHeadPosition();
	while (pos)
	{
		CExBaseList* pChild = (CExBaseList*)g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef.GetNext(pos);
		CSttItemBase* pMacroTest = new CSttItemBase;
		pMacroTest->m_strID = pChild->m_strID;
		pMacroTest->m_nTkID = 65535;
		pParentItems->AddNewChild(pMacroTest);
	}
}

void CSttMacroParaEditViewOriginal::slot_GoutMapChanged()
{
	m_bIECGoutMapChanged = TRUE;
}

float GlobalSetResultValue(CDvmValue* pResultValue,int nDecimalNum)
{
	if (pResultValue->m_strValue == /*"未动作"*/g_sLangTxt_State_NoActioned)
	{
		return 0.0f;
	}

	float fTripValue = CString_To_double(pResultValue->m_strValue);
	pResultValue->m_strValue = QString::number(fTripValue,'f',3);
	return fTripValue;
}


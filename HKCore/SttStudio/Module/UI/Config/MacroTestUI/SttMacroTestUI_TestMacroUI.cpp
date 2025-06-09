//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTestUI_TestMacroUI.cpp  CSttMacroTestUI_TestMacroUI


#include "stdafx.h"
#include "SttMacroTestUI_TestMacroUI.h"
#include "../../../SttGlobalDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttMacroTestUI_TestMacroUI::CSttMacroTestUI_TestMacroUI()
{
	//初始化属性
	m_nDefaultRepeatTimes = 1;
	//初始化成员变量
}

CSttMacroTestUI_TestMacroUI::~CSttMacroTestUI_TestMacroUI()
{
}

long CSttMacroTestUI_TestMacroUI::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strGen_FileKey, oNode, m_strGenFile);
	xml_GetAttibuteValue(pXmlKeys->m_strUi_FileKey, oNode, m_strUI_File);
	xml_GetAttibuteValue(pXmlKeys->m_strUi_Para_FileKey, oNode, m_strUI_ParaFile);
	xml_GetAttibuteValue(pXmlKeys->m_strReport_FileKey, oNode, m_strReportFile);
	xml_GetAttibuteValue(pXmlKeys->m_strHd_Rs_FileKey, oNode, m_strHdRsFile);
	xml_GetAttibuteValue(pXmlKeys->m_strCharLib_FileKey, oNode, m_strCharlibFile);
	xml_GetAttibuteValue(pXmlKeys->m_strUi_IdKey, oNode, m_strUI_ID);
	xml_GetAttibuteValue(pXmlKeys->m_strRptDataCfgFileKey, oNode, m_strrpt_Data_CfgFile);
	xml_GetAttibuteValue(pXmlKeys->m_strRepeatTimesKey, oNode, m_nDefaultRepeatTimes);
	xml_GetAttibuteValue(pXmlKeys->m_strGirdFileKey, oNode, m_strGirdFile);
	return 0;
}

long CSttMacroTestUI_TestMacroUI::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strGen_FileKey, oElement, m_strGenFile);
	xml_SetAttributeValue(pXmlKeys->m_strUi_FileKey, oElement, m_strUI_File);
	xml_SetAttributeValue(pXmlKeys->m_strUi_Para_FileKey, oElement, m_strUI_ParaFile);
	xml_SetAttributeValue(pXmlKeys->m_strReport_FileKey, oElement, m_strReportFile);
	xml_SetAttributeValue(pXmlKeys->m_strHd_Rs_FileKey, oElement, m_strHdRsFile);
	xml_SetAttributeValue(pXmlKeys->m_strCharLib_FileKey, oElement, m_strCharlibFile);
	xml_SetAttributeValue(pXmlKeys->m_strUi_IdKey, oElement, m_strUI_ID);
	xml_SetAttributeValue(pXmlKeys->m_strRptDataCfgFileKey, oElement, m_strrpt_Data_CfgFile);
	xml_SetAttributeValue(pXmlKeys->m_strRepeatTimesKey, oElement, m_nDefaultRepeatTimes);
	xml_SetAttributeValue(pXmlKeys->m_strGirdFileKey, oElement, m_strGirdFile);
	return 0;
}

long CSttMacroTestUI_TestMacroUI::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strGenFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strUI_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strUI_ParaFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strReportFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strHdRsFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strCharlibFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strUI_ID);
		BinarySerializeCalLen(oBinaryBuffer, m_strrpt_Data_CfgFile);
		BinarySerializeCalLen(oBinaryBuffer, m_nDefaultRepeatTimes);
		BinarySerializeCalLen(oBinaryBuffer, m_strGirdFile);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strGenFile);
		BinarySerializeRead(oBinaryBuffer, m_strUI_File);
		BinarySerializeRead(oBinaryBuffer, m_strUI_ParaFile);
		BinarySerializeRead(oBinaryBuffer, m_strReportFile);
		BinarySerializeRead(oBinaryBuffer, m_strHdRsFile);
		BinarySerializeRead(oBinaryBuffer, m_strCharlibFile);
		BinarySerializeRead(oBinaryBuffer, m_strUI_ID);
		BinarySerializeRead(oBinaryBuffer, m_strrpt_Data_CfgFile);
		BinarySerializeRead(oBinaryBuffer, m_nDefaultRepeatTimes);
		BinarySerializeRead(oBinaryBuffer, m_strGirdFile);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strGenFile);
		BinarySerializeWrite(oBinaryBuffer, m_strUI_File);
		BinarySerializeWrite(oBinaryBuffer, m_strUI_ParaFile);
		BinarySerializeWrite(oBinaryBuffer, m_strReportFile);
		BinarySerializeWrite(oBinaryBuffer, m_strHdRsFile);
		BinarySerializeWrite(oBinaryBuffer, m_strCharlibFile);
		BinarySerializeWrite(oBinaryBuffer, m_strUI_ID);
		BinarySerializeWrite(oBinaryBuffer, m_strrpt_Data_CfgFile);
		BinarySerializeWrite(oBinaryBuffer, m_nDefaultRepeatTimes);
		BinarySerializeWrite(oBinaryBuffer, m_strGirdFile);
	}
	return 0;
}

void CSttMacroTestUI_TestMacroUI::InitAfterRead()
{
}

BOOL CSttMacroTestUI_TestMacroUI::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttMacroTestUI_TestMacroUI *p = (CSttMacroTestUI_TestMacroUI*)pObj;

	if(m_strGenFile != p->m_strGenFile)
	{
		return FALSE;
	}

	if(m_strGirdFile != p->m_strGirdFile)
	{
		return FALSE;
	}

	if(m_strUI_File != p->m_strUI_File)
	{
		return FALSE;
	}

	if(m_strUI_ParaFile != p->m_strUI_ParaFile)
	{
		return FALSE;
	}

	if(m_strReportFile != p->m_strReportFile)
	{
		return FALSE;
	}

	if(m_strHdRsFile != p->m_strHdRsFile)
	{
		return FALSE;
	}

	if(m_strCharlibFile != p->m_strCharlibFile)
	{
		return FALSE;
	}

	if(m_strUI_ID != p->m_strUI_ID)
	{
		return FALSE;
	}

	if(m_strrpt_Data_CfgFile != p->m_strrpt_Data_CfgFile)
	{
		return FALSE;
	}

	if(m_nDefaultRepeatTimes != p->m_nDefaultRepeatTimes)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttMacroTestUI_TestMacroUI::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttMacroTestUI_TestMacroUI *p = (CSttMacroTestUI_TestMacroUI*)pDest;

	p->m_strGenFile = m_strGenFile;
	p->m_strGirdFile = m_strGirdFile;
	p->m_strUI_File = m_strUI_File;
	p->m_strUI_ParaFile = m_strUI_ParaFile;
	p->m_strReportFile = m_strReportFile;
	p->m_strHdRsFile = m_strHdRsFile;
	p->m_strUI_ID = m_strUI_ID;
	p->m_strCharlibFile = m_strCharlibFile;
	p->m_strrpt_Data_CfgFile = m_strrpt_Data_CfgFile;
	p->m_nDefaultRepeatTimes = m_nDefaultRepeatTimes;
	return TRUE;
}

CBaseObject* CSttMacroTestUI_TestMacroUI::Clone()
{
	CSttMacroTestUI_TestMacroUI *p = new CSttMacroTestUI_TestMacroUI();
	Copy(p);
	return p;
}

CBaseObject* CSttMacroTestUI_TestMacroUI::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttMacroTestUI_TestMacroUI *p = new CSttMacroTestUI_TestMacroUI();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CDataGroup * CSttMacroTestUI_TestMacroUI::GetTestMacroUIDataGroup()
{
	CDataGroup *pDataGroup = new CDataGroup();

	GetTestMacroUIDataGroup(pDataGroup);

	return pDataGroup;
}

void CSttMacroTestUI_TestMacroUI::GetTestMacroUIDataGroup( CDataGroup *pDataParas )
{
	if (pDataParas == NULL)
	{
		pDataParas = new CDataGroup();
	}

	pDataParas->m_strName = STT_CMD_PARA_TestMacroUI;
	pDataParas->m_strID = STT_CMD_PARA_TestMacroUI;

	pDataParas->AddNewData(STT_CMD_PARA_TestMacroUI_ID, m_strID);
	pDataParas->AddNewData(STT_CMD_PARA_GenFile, m_strGenFile);
	pDataParas->AddNewData(STT_CMD_PARA_GridFile, m_strGirdFile);
	pDataParas->AddNewData(STT_CMD_PARA_UIFile, m_strUI_File);
	pDataParas->AddNewData(STT_CMD_PARA_UIParaFile, m_strUI_ParaFile);
	pDataParas->AddNewData(STT_CMD_PARA_ReportFile, m_strReportFile);
	pDataParas->AddNewData(STT_CMD_PARA_HdRsFile, m_strHdRsFile);//20220315  sf  sl说少个参数没发，在这里加上
	pDataParas->AddNewData(STT_CMD_PARA_CharLibFile, m_strCharlibFile);
	pDataParas->AddNewData(STT_CMD_PARA_UI_ID, m_strUI_ID);//20220802 zhouhj 界面ID  
}


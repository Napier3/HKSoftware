//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttDevConfig.cpp  CSttDevConfig


#include "stdafx.h"
#include "SttDevConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttDevConfig::CSttDevConfig()
{
	//初始化属性
	m_nSelOffLine = 0;
	m_nSelSOE_Test = 0;
	m_nSelSteadyOutput = 0;
	m_nSetPassword = 1;
	m_nOverloadDelay = 0;
	m_nDoubleClickEdit = 1;
	m_strAuxIP = _T("192.168.1.123");
	m_strLastFolderPath = _T("");
	m_nMultiExpList = 1;
	m_nUseSclView = 0;
	m_nLogPrint = 0;
	m_nFt3_Prim_Code_Value = 0;
	m_nLockMaps = 1;//缺省需要锁定通道映射，在登录后，不自动更新通道映射
    
	//初始化成员变量
}

CSttDevConfig::~CSttDevConfig()
{
}

long CSttDevConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttSystemConfigXmlRWKeys *pXmlKeys = (CSttSystemConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strCur_Sel_ModelKey, oNode, m_strCurSelModel);
	xml_GetElementText(pXmlKeys->m_strSel_OfflineKey, oNode, m_nSelOffLine);
	xml_GetElementText(pXmlKeys->m_strSel_SOE_TestKey, oNode, m_nSelSOE_Test);
	xml_GetElementText(pXmlKeys->m_strSel_Steady_OutputKey, oNode, m_nSelSteadyOutput);
	xml_GetElementText(pXmlKeys->m_strSet_PasswordKey, oNode, m_nSetPassword);
	xml_GetElementText(pXmlKeys->m_strOverload_DelayKey, oNode, m_nOverloadDelay);
	xml_GetElementText(pXmlKeys->m_strDouble_Click_EditKey, oNode, m_nDoubleClickEdit);
	xml_GetElementText(pXmlKeys->m_strAux_IpKey, oNode, m_strAuxIP);
	xml_GetElementText(pXmlKeys->m_strLast_Folder_PathKey, oNode, m_strLastFolderPath);
	xml_GetElementText(pXmlKeys->m_strMulti_Exp_ListKey, oNode, m_nMultiExpList);
	xml_GetElementText(pXmlKeys->m_strUse_Scl_ViewKey, oNode, m_nUseSclView);
	xml_GetElementText(pXmlKeys->m_strLog_PrintKey, oNode, m_nLogPrint);
	xml_GetElementText(pXmlKeys->m_strFt3_Prim_Code_ValueKey,oNode, m_nFt3_Prim_Code_Value); 
    xml_GetElementText(pXmlKeys->m_strLock_MapsKey,oNode, m_nLockMaps); 
	xml_GetElementText(pXmlKeys->m_strSel_Sys_Pata, oNode, m_nSel_Sys_Pata);

	return 0;
}

long CSttDevConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttSystemConfigXmlRWKeys *pXmlKeys = (CSttSystemConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strCur_Sel_ModelKey,oXMLDoc, oElement, m_strCurSelModel);
	xml_SetElementText(pXmlKeys->m_strSel_OfflineKey,oXMLDoc, oElement, m_nSelOffLine);
	xml_SetElementText(pXmlKeys->m_strSel_SOE_TestKey,oXMLDoc, oElement, m_nSelSOE_Test);
	xml_SetElementText(pXmlKeys->m_strSel_Steady_OutputKey,oXMLDoc, oElement, m_nSelSteadyOutput);
	xml_SetElementText(pXmlKeys->m_strSet_PasswordKey, oXMLDoc,oElement, m_nSetPassword);
	xml_SetElementText(pXmlKeys->m_strOverload_DelayKey,oXMLDoc, oElement, m_nOverloadDelay);
	xml_SetElementText(pXmlKeys->m_strDouble_Click_EditKey,oXMLDoc, oElement, m_nDoubleClickEdit);
	xml_SetElementText(pXmlKeys->m_strAux_IpKey,oXMLDoc, oElement, m_strAuxIP);
	xml_SetElementText(pXmlKeys->m_strLast_Folder_PathKey,oXMLDoc, oElement, m_strLastFolderPath);
	xml_SetElementText(pXmlKeys->m_strMulti_Exp_ListKey,oXMLDoc,  oElement, m_nMultiExpList);
	xml_SetElementText(pXmlKeys->m_strUse_Scl_ViewKey,oXMLDoc, oElement, m_nUseSclView);
	xml_SetElementText(pXmlKeys->m_strLog_PrintKey,oXMLDoc, oElement, m_nLogPrint);
	xml_SetElementText(pXmlKeys->m_strFt3_Prim_Code_ValueKey,oXMLDoc, oElement, m_nFt3_Prim_Code_Value);
	xml_SetElementText(pXmlKeys->m_strLock_MapsKey,oXMLDoc,oElement, m_nLockMaps); 
	xml_SetElementText(pXmlKeys->m_strSel_Sys_Pata, oXMLDoc, oElement, m_nSel_Sys_Pata);

	return 0;
}

long CSttDevConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCurSelModel);
		BinarySerializeCalLen(oBinaryBuffer, m_nSelOffLine);
		BinarySerializeCalLen(oBinaryBuffer, m_nSelSOE_Test);
		BinarySerializeCalLen(oBinaryBuffer, m_nSelSteadyOutput);
		BinarySerializeCalLen(oBinaryBuffer, m_nSetPassword);
		BinarySerializeCalLen(oBinaryBuffer, m_nOverloadDelay);
		BinarySerializeCalLen(oBinaryBuffer, m_nDoubleClickEdit);
		BinarySerializeCalLen(oBinaryBuffer, m_strAuxIP);
		BinarySerializeCalLen(oBinaryBuffer, m_strLastFolderPath);
		BinarySerializeCalLen(oBinaryBuffer, m_nMultiExpList);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseSclView);
		BinarySerializeCalLen(oBinaryBuffer, m_nLogPrint);
		BinarySerializeCalLen(oBinaryBuffer, m_nFt3_Prim_Code_Value);
		BinarySerializeCalLen(oBinaryBuffer, m_nLockMaps); 
		BinarySerializeCalLen(oBinaryBuffer, m_nSel_Sys_Pata);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCurSelModel);
		BinarySerializeRead(oBinaryBuffer, m_nSelOffLine);
		BinarySerializeRead(oBinaryBuffer, m_nSelSOE_Test);
		BinarySerializeRead(oBinaryBuffer, m_nSelSteadyOutput);
		BinarySerializeRead(oBinaryBuffer, m_nSetPassword);
		BinarySerializeRead(oBinaryBuffer, m_nOverloadDelay);
		BinarySerializeRead(oBinaryBuffer, m_nDoubleClickEdit);
		BinarySerializeRead(oBinaryBuffer, m_strAuxIP);
		BinarySerializeRead(oBinaryBuffer, m_strLastFolderPath);
		BinarySerializeRead(oBinaryBuffer, m_nMultiExpList);
		BinarySerializeRead(oBinaryBuffer, m_nUseSclView);
		BinarySerializeRead(oBinaryBuffer, m_nLogPrint);
		BinarySerializeRead(oBinaryBuffer, m_nFt3_Prim_Code_Value);
		BinarySerializeRead(oBinaryBuffer, m_nLockMaps);
		BinarySerializeRead(oBinaryBuffer, m_nSel_Sys_Pata);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCurSelModel);
		BinarySerializeWrite(oBinaryBuffer, m_nSelOffLine);
		BinarySerializeWrite(oBinaryBuffer, m_nSelSOE_Test);
		BinarySerializeWrite(oBinaryBuffer, m_nSelSteadyOutput);
		BinarySerializeWrite(oBinaryBuffer, m_nSetPassword);
		BinarySerializeWrite(oBinaryBuffer, m_nOverloadDelay);
		BinarySerializeWrite(oBinaryBuffer, m_nDoubleClickEdit);
		BinarySerializeWrite(oBinaryBuffer, m_strAuxIP);
		BinarySerializeWrite(oBinaryBuffer, m_strLastFolderPath);
		BinarySerializeWrite(oBinaryBuffer, m_nMultiExpList);
		BinarySerializeWrite(oBinaryBuffer, m_nUseSclView);
		BinarySerializeWrite(oBinaryBuffer, m_nLogPrint);
		BinarySerializeWrite(oBinaryBuffer, m_nFt3_Prim_Code_Value);
		BinarySerializeWrite(oBinaryBuffer, m_nLockMaps);
		BinarySerializeWrite(oBinaryBuffer, m_nSel_Sys_Pata);
	}
	return 0;
}

void CSttDevConfig::InitAfterRead()
{
}

BOOL CSttDevConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttDevConfig *p = (CSttDevConfig*)pObj;

	if(m_strCurSelModel != p->m_strCurSelModel)
	{
		return FALSE;
	}

	if(m_nSelOffLine != p->m_nSelOffLine)
	{
		return FALSE;
	}

	if(m_nSelSOE_Test != p->m_nSelSOE_Test)
	{
		return FALSE;
	}

	if(m_nSelSteadyOutput != p->m_nSelSteadyOutput)
	{
		return FALSE;
	}

	if(m_nSetPassword != p->m_nSetPassword)
	{
		return FALSE;
	}

	if(m_nOverloadDelay != p->m_nOverloadDelay)
	{
		return FALSE;
	}

	if(m_nDoubleClickEdit != p->m_nDoubleClickEdit)
	{
		return FALSE;
	}

	if(m_strAuxIP != p->m_strAuxIP)
	{
		return FALSE;
	}

	if(m_strLastFolderPath != p->m_strLastFolderPath)
	{
		return FALSE;
	}

	if(m_nMultiExpList != p->m_nMultiExpList)
	{
		return FALSE;
	}

	if(m_nUseSclView != p->m_nUseSclView)
	{
		return FALSE;
	}
	if(m_nLogPrint != p->m_nLogPrint)
	{
		return FALSE;
	}
	if(m_nFt3_Prim_Code_Value != p->m_nFt3_Prim_Code_Value)
	{
		return FALSE;
	}
	if(m_nLockMaps != p->m_nLockMaps)
	{
		return FALSE;
	}

	if(m_nSel_Sys_Pata != p->m_nSel_Sys_Pata)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttDevConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttDevConfig *p = (CSttDevConfig*)pDest;

	p->m_strCurSelModel = m_strCurSelModel;
	p->m_nSelOffLine = m_nSelOffLine;
	p->m_nSelSOE_Test = m_nSelSOE_Test;
	p->m_nSelSteadyOutput = m_nSelSteadyOutput;
	p->m_nSetPassword = m_nSetPassword;
	p->m_nOverloadDelay = m_nOverloadDelay;
	p->m_nDoubleClickEdit = m_nDoubleClickEdit;
	p->m_strAuxIP = m_strAuxIP;
	p->m_strLastFolderPath = m_strLastFolderPath;
	p->m_nMultiExpList = m_nMultiExpList;
	p->m_nUseSclView = m_nUseSclView;
	p->m_nLogPrint = m_nLogPrint;
	p->m_nFt3_Prim_Code_Value = m_nFt3_Prim_Code_Value;
	p->m_nLockMaps = m_nLockMaps;
	p->m_nSel_Sys_Pata = m_nSel_Sys_Pata;
	return TRUE;
}

CBaseObject* CSttDevConfig::Clone()
{
	CSttDevConfig *p = new CSttDevConfig();
	Copy(p);
	return p;
}

CBaseObject* CSttDevConfig::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttDevConfig *p = new CSttDevConfig();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}


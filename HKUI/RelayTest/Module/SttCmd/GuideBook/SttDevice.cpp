//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttDevice.cpp  CSttDevice


#include "stdafx.h"
#include "SttDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttDevice::CSttDevice()
{
	//初始化属性
	m_nIsTimeSetsUnit_ms = 0;
	m_nDsvTextWithValue = 0;
	m_nDsvTextWithUtcTime = 0;

	//初始化成员变量
	m_strName= _T("新测试模板");
	m_strID = _T("Device");

	m_pSysPara = NULL;
}

CSttDevice::~CSttDevice()
{
}

long CSttDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFactoryKey, oNode, m_strFactory);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceTypeKey, oNode, m_strDeviceType);
	xml_GetAttibuteValue(pXmlKeys->m_strIsTimeSetsUnit_ms_Key, oNode, m_nIsTimeSetsUnit_ms);
	xml_GetAttibuteValue(pXmlKeys->m_strDsvTextWithValueKey, oNode, m_nDsvTextWithValue);
	xml_GetAttibuteValue(pXmlKeys->m_strDsvTextWithUtcTimeKey, oNode, m_nDsvTextWithUtcTime);
	xml_GetAttibuteValue(pXmlKeys->m_strSrcDeviceModelFileKey, oNode, m_strSrcDeviceModelFile);
	return 0;
}

long CSttDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFactoryKey, oElement, m_strFactory);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceTypeKey, oElement, m_strDeviceType);
	xml_SetAttributeValue(pXmlKeys->m_strIsTimeSetsUnit_ms_Key, oElement, m_nIsTimeSetsUnit_ms);
	xml_SetAttributeValue(pXmlKeys->m_strDsvTextWithValueKey, oElement, m_nDsvTextWithValue);
	xml_SetAttributeValue(pXmlKeys->m_strDsvTextWithUtcTimeKey, oElement, m_nDsvTextWithUtcTime);
	xml_SetAttributeValue(pXmlKeys->m_strSrcDeviceModelFileKey, oElement, m_strSrcDeviceModelFile);
	return 0;
}

long CSttDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttItemBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strFactory);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceType);
		BinarySerializeCalLen(oBinaryBuffer, m_nIsTimeSetsUnit_ms);
		BinarySerializeCalLen(oBinaryBuffer, m_nDsvTextWithValue);
		BinarySerializeCalLen(oBinaryBuffer, m_nDsvTextWithUtcTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strSrcDeviceModelFile);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strFactory);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceType);
		BinarySerializeRead(oBinaryBuffer, m_nIsTimeSetsUnit_ms);
		BinarySerializeRead(oBinaryBuffer, m_nDsvTextWithValue);
		BinarySerializeRead(oBinaryBuffer, m_nDsvTextWithUtcTime);
		BinarySerializeRead(oBinaryBuffer, m_strSrcDeviceModelFile);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strFactory);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceType);
		BinarySerializeWrite(oBinaryBuffer, m_nIsTimeSetsUnit_ms);
		BinarySerializeWrite(oBinaryBuffer, m_nDsvTextWithValue);
		BinarySerializeWrite(oBinaryBuffer, m_nDsvTextWithUtcTime);
		BinarySerializeWrite(oBinaryBuffer, m_strSrcDeviceModelFile);
	}
	return 0;
}

void CSttDevice::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == STTGBXMLCLASSID_CSTTSYSPARAS)
		{
			m_pSysPara = (CSttSysParas *)pObj;
		}
	}
}

BOOL CSttDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttDevice *p = (CSttDevice*)pObj;

	if(m_strFactory != p->m_strFactory)
	{
		return FALSE;
	}

	if(m_strDeviceType != p->m_strDeviceType)
	{
		return FALSE;
	}

	if(m_nIsTimeSetsUnit_ms != p->m_nIsTimeSetsUnit_ms)
	{
		return FALSE;
	}

	if(m_nDsvTextWithValue != p->m_nDsvTextWithValue)
	{
		return FALSE;
	}

	if(m_nDsvTextWithUtcTime != p->m_nDsvTextWithUtcTime)
	{
		return FALSE;
	}

	if(m_strSrcDeviceModelFile != p->m_strSrcDeviceModelFile)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttItemBase::CopyOwn(pDest);

	CSttDevice *p = (CSttDevice*)pDest;

	p->m_strFactory = m_strFactory;
	p->m_strDeviceType = m_strDeviceType;
	p->m_nIsTimeSetsUnit_ms = m_nIsTimeSetsUnit_ms;
	p->m_nDsvTextWithValue = m_nDsvTextWithValue;
	p->m_nDsvTextWithUtcTime = m_nDsvTextWithUtcTime;
	p->m_strSrcDeviceModelFile = m_strSrcDeviceModelFile;
	return TRUE;
}

CBaseObject* CSttDevice::Clone()
{
	CSttDevice *p = new CSttDevice();
	Copy(p);
	return p;
}

CBaseObject* CSttDevice::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttDevice *p = new CSttDevice();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttDevice::CanPaste(UINT nClassID)
{
	if (nClassID == STTGBXMLCLASSID_CSTTSYSPARAS)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTSAFETY)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTSYSPARAEDIT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttSysParasKey)
	{
		pNew = new CSttSysParas();
		m_pSysPara = (CSttSysParas *)pNew;
		return pNew;
	}
	else if (strClassID == pXmlKeys->m_strCSttItemsKey)
	{
		pNew = new CSttItems();
		return pNew;
	}
	else if (strClassID == pXmlKeys->m_strCSttCommCmdKey)
	{
		pNew = new CSttCommCmd();
		return pNew;
	}
	else if (strClassID == pXmlKeys->m_strCSttMacroTestKey)
	{
		pNew = new CSttMacroTest();
		return pNew;
	}
	else if (strClassID == pXmlKeys->m_strCSttSafetyKey)
	{
		pNew = new CSttSafety();
		return pNew;
	}
	else if (strClassID == pXmlKeys->m_strCSttSysParaEditKey)
	{
		pNew = new CSttSysParaEdit();
		return pNew;
	}

	return CSttItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CSttDevice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTGBXMLCLASSID_CSTTSYSPARAS)
	{
		pNew = new CSttSysParas();
		m_pSysPara = (CSttSysParas *)pNew;
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{
		pNew = new CSttItems();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		pNew = new CSttCommCmd();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		pNew = new CSttMacroTest();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTSAFETY)
	{
		pNew = new CSttSafety();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTSYSPARAEDIT)
	{
		pNew = new CSttSysParaEdit();
	}
	else
	{
		return CSttItemBase::CreateNewChild(nClassID);
	}

	return pNew;
}

CSttSysParas* CSttDevice::GetSysPara(BOOL bCreate)
{
	if (m_pSysPara != NULL)
	{
		return m_pSysPara;
	}

	if (bCreate)
	{
		m_pSysPara = new CSttSysParas();
		AddNewChild(m_pSysPara);
	}

	return m_pSysPara;
}

void CSttDevice::UpdateSysPara(CExBaseList *pSrcList, BOOL bCreateNew)
{
	if (m_pSysPara == NULL)
	{
		return;
	}

	m_pSysPara->UpdateDataValue((CDvmDataset*)pSrcList, bCreateNew);
}

long CSttDevice::SelectAllRootItem(CExBaseList &oList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == STTGBXMLCLASSID_CSTTSAFETY || nClassID == STTGBXMLCLASSID_CSTTMACROTEST
			|| nClassID == STTGBXMLCLASSID_CSTTCOMMCMD || nClassID == STTGBXMLCLASSID_CSTTSYSPARAEDIT
			|| nClassID == STTGBXMLCLASSID_CSTTITEMS)
		{
			oList.AddTail(p);
		}
	}

	return oList.GetCount();
}

long CSttDevice::GetGbItemCount()
{
	return CSttItemBase::GetGbItemCount();
}

void CSttDevice::GetItemsCountByItemsType(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount)
{
	CSttItemBase::GetItemsCountByItemsType(nTotalCount, nEligibleCount, nInlegibleCount);
}

BOOL CSttDevice::ExprRsltBind(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strDataName, const CString &strParentPath, const CString &strValue)
{
	if (strType == _T("dataset"))
	{
		return ExprRsltBind_dataset(pExprParent, strType, strExpression, strParentPath, strValue);
	}
	else if (strType == _T("sys-para"))
	{
		return ExprRsltBind_sys_para(pExprParent, strType, strExpression, strValue);
	}
	else if (strType == _T("global-para"))
	{
		return ExprRsltBind_global_para(pExprParent, strType, strExpression, strValue);
	}
	else if (strType == _T("report"))
	{
		return ExprRsltBind_report(pExprParent, strType, strExpression, strDataName, strParentPath, strValue);
	}
	else if (strType == _T("number"))
	{
		return TRUE;
	}
	else if (strType == _T("script"))
	{
		return ExprRsltBind_script(pExprParent, strType, strExpression, strValue);
	}
	else
	{
		return ExprRsltBind_script(pExprParent, strType, strExpression, strValue);
	}
}

BOOL CSttDevice::ExprGetValueAttr(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, CString &strValueAttrRet, const CString &strAttr)
{
	if (strType == _T("dataset"))
	{
		return ExprGetValueAttr_dataset(pExprParent, strType, strExpression, strValueAttrRet, strAttr);
	}
	else if (strType == _T("sys-para"))
	{
		return ExprGetValueAttr_sys_para(pExprParent, strType, strExpression, strValueAttrRet, strAttr);
	}
	else if (strType == _T("global-para"))
	{
		return ExprGetValueAttr_global_para(pExprParent, strType, strExpression, strValueAttrRet, strAttr);
	}
	else if (strType == _T("report"))
	{
		return ExprGetValueAttr_report(pExprParent, strType, strExpression, strParentPath, strValueAttrRet, strAttr);
	}
	else if (strType == _T("number"))
	{
		return TRUE;
	}
	else if (strType == _T("script"))
	{
		return ExprGetValueAttr_script(pExprParent, strType, strExpression, strValueAttrRet, strAttr);
	}
	else
	{
		return ExprGetValueAttr_script(pExprParent, strType, strExpression, strValueAttrRet, strAttr);
	}
}

BOOL CSttDevice::ExprRsltBind_dataset(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, const CString &strValue)
{
	//数据集，存放在g_theGbSmartGenWzd->m_pDvmDevice。
	//暂时不更新
	return TRUE;
}

BOOL CSttDevice::ExprRsltBind_sys_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strValue)
{
	CDvmData *pFind = (CDvmData*)m_pSysPara->FindByID(strExpression);

	if (pFind == NULL)
	{
		return FALSE;
	}

	pFind->m_strValue = strValue;
	return TRUE;
}

#include "SttGuideBook.h"

BOOL CSttDevice::ExprRsltBind_global_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strValue)
{
	CSttGuideBook *pGuideBook = (CSttGuideBook*)GetParent();
	CDvmData *pFind = (CDvmData*)pGuideBook->m_pGlobalDatas->FindByID(strExpression);

	if (pFind == NULL)
	{
		return FALSE;
	}

	pFind->m_strValue = strValue;
	return TRUE;
}

BOOL CSttDevice::ExprRsltBind_report(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strDataName, const CString &strParentPath, const CString &strValue)
{
	//对于报告而言，分为两种情况：
	//1、绑定的是表达式父对象自身的报告：在自动测试执行端，已经进行了更新。并将更新的报告，通过REPORT事件上传
	//2、绑定的是表达式父对象以外的项目的报告（自动测试执行端也进行了绑定，但是并没有指令将报告送上来）：即通过strParentPath找到相对对象，并进行报告绑定
	if (strParentPath.IsEmpty())
	{
		return TRUE;
	}

	CSttItemBase *pItem = (CSttItemBase*)pExprParent;  //表达式的父对象
	CSttReport *pReport = NULL;

	CExBaseList oDestList;
	//通过项目相对路径，查找项目
	pItem->SelectItems(strParentPath, oDestList);
	long nCount = oDestList.GetCount();

	if (nCount != 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("项目【%s】查找结果不唯一！找到【%d】个目标项目"), strParentPath.GetString(), nCount);
		oDestList.RemoveAll();
		return FALSE;
	}

	CSttItemBase *pDestItem = (CSttItemBase *)oDestList.GetHead();
	pReport = pDestItem->GetReport(-1);
	oDestList.RemoveAll();

	if (pReport == NULL)
	{
		return FALSE;
	}

	CDvmValue *pFind = (CDvmValue*)pReport->m_pValues->FindByID(strExpression);

	//找不到结果参数，可以新建一个CValue。需要把name传进来
	//对于ID中携带$符的参数，可以取$符最后一段，简单进行处理。例如：状态序列结果评估：rslt_evaluation$rslt_evaluation1$Ttrip_AbsErr
	if (pFind == NULL)
	{
		pFind = new CDvmValue();
		pReport->m_pValues->AddNewChild(pFind);
		pReport->m_pValues->BringToHead(pFind);

		CString strID = strExpression;
		long nPos = strID.Find(_T("$"));

		if (nPos >= 0)
		{
			strID = strID.Mid(nPos + 1);
		}

		pFind->m_strID = strID;
		pFind->m_strName = strDataName;
		/*return FALSE;*/
	}

	pFind->m_strValue = strValue;

	return TRUE;
}

BOOL CSttDevice::ExprRsltBind_script(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strValue)
{
	return FALSE;
}

//extern CGbSmartGenWzd *g_theGbSmartGenWzd;
BOOL CSttDevice::ExprGetValueAttr_dataset(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, CString &strValueAttrRet, const CString &strAttr)
{
	//有需要再改
	return FALSE;
	/*
	CDvmDevice *pDvmDevice = g_theGbSmartGenWzd->m_pDvmDevice;
	CDvmData *pFind = NULL;

	CExBaseList oListData;
	pDvmDevice->SelectDatas(strExpression, oListData, _T("$"));

	if (oListData.GetCount() == 1)
	{
		pFind = (CDvmData *)oListData.GetHead();
	}
	else if (oListData.GetCount() > 1)
	{
		pFind = (CDvmData *)oListData.GetHead();
	}

	if (pFind != NULL)
	{
		if(strAttr == _T("name"))
		{
			strValueAttrRet = pFind->m_strName;
		}
		else if(strAttr == _T("unit"))
		{
			strValueAttrRet = pFind->m_strUnit;
		}
	}

	return pFind != NULL;
	*/
}

BOOL CSttDevice::ExprGetValueAttr_sys_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, CString &strValueAttrRet, const CString &strAttr)
{
	CDvmData *pFind = (CDvmData*)m_pSysPara->FindByID(strExpression);

	if (pFind == NULL)
	{
		return FALSE;
	}

	if(strAttr == _T("name"))
	{
		strValueAttrRet = pFind->m_strName;
	}
	else if (strAttr == _T("unit"))
	{
		strValueAttrRet = pFind->m_strUnit;
	}
	
	return TRUE;
}

BOOL CSttDevice::ExprGetValueAttr_global_para(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, CString &strValueAttrRet, const CString &strAttr)
{
	CSttGuideBook *pGuideBook = (CSttGuideBook*)GetParent();
	CDvmData *pFind = (CDvmData*)pGuideBook->m_pGlobalDatas->FindByID(strExpression);

	if (pFind != NULL)
	{
		return FALSE;
	}

	if(strAttr == _T("name"))
	{
		strValueAttrRet = pFind->m_strName;
	}
	else if (strAttr == _T("unit"))
	{
		strValueAttrRet = pFind->m_strUnit;
	}

	return TRUE;
}

BOOL CSttDevice::ExprGetValueAttr_report(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, CString &strValueAttrRet, const CString &strAttr)
{
	//对于报告而言，分为两种情况：
	//1、绑定的是表达式父对象自身的报告：
	//2、绑定的是表达式父对象以外的项目的报告：即通过strParentPath找到相对对象，并进行报告绑定

	CSttItemBase *pItem = (CSttItemBase*)pExprParent;  //表达式的父对象
	CSttItemBase *pDestItem = NULL;  //目标项目。
	CSttReport *pReport = NULL;
	CExBaseList oDestList;

	if (strParentPath.IsEmpty())
	{
		pDestItem = pItem;  //项目路径为空时，表示目标项目就是本项目
	}
	else
	{
		//通过项目相对路径，查找项目
		pItem->SelectItems(strParentPath, oDestList);
		long nCount = oDestList.GetCount();

		if (nCount != 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("项目【%s】查找结果不唯一！找到【%d】个目标项目"), strParentPath.GetString(), nCount);
			oDestList.RemoveAll();
			return FALSE;
		}

		pDestItem = (CSttItemBase *)oDestList.GetHead();
	}

	pReport = pDestItem->GetReport(-1);
	oDestList.RemoveAll();

	if (pReport == NULL)
	{
		return FALSE;
	}

	CDvmValue *pFind = (CDvmValue*)pReport->m_pValues->FindByID(strExpression);

	if (pFind == NULL)
	{
		return FALSE;
	}

	if(strAttr == _T("name"))
	{
		strValueAttrRet = pFind->m_strName;
	}
// 	else if (strAttr == _T("unit"))
// 	{
// 		strValueAttrRet = pFind->m_strUnit;
// 	}

	return TRUE;
}

BOOL CSttDevice::ExprGetValueAttr_script(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, CString &strValueAttrRet, const CString &strAttr)
{
	return FALSE;
}
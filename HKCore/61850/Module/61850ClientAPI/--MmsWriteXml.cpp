// IVtag.cpp : 实现文件
//

#include "stdafx.h"
#include "MmsWriteXml.h"
#include "..\..\..\Module\API\FileApi.h"
#include "61850ClientGlobal.h"

#include "..\..\..\Module\System\TickCount32.h"

static BSTR G_BSTRKEY_NAME  = L"name";
static BSTR G_BSTRKEY_ID  = L"id";
static BSTR G_BSTRKEY_UNITPATH  = L"unit-path";
static BSTR G_BSTRKEY_UNITVALUE  = L"unit-value";
static BSTR G_BSTRKEY_DATATYPE  = L"data-type";
static BSTR G_BSTRKEY_NODETYPE  = L"node-type";
static BSTR G_BSTRKEY_VALUE  = L"value";
static BSTR G_BSTRKEY_DEFVALUE  = L"default-value";
static BSTR G_BSTRKEY_MAX  = L"max";
static BSTR G_BSTRKEY_MIN  = L"min";
static BSTR G_BSTRKEY_STEPSIZE  = L"step";
static BSTR G_BSTRKEY_PATH  = L"path";
static BSTR G_BSTRKEY_DATASET  = L"dataset";
static BSTR G_BSTRKEY_DATA  = L"data";
static BSTR G_BSTRKEY_BRCB  = L"brcb";
static BSTR G_BSTRKEY_LGCTRL  = L"log-ctrl";

static BSTR G_BSTRKEY_LOGREF = L"logRef";
static BSTR G_BSTRKEY_LOGENA  = L"logEna";

long mms_XmlWrite(const CString &strFile, ACSI_NODE *pDevice)
{
	CXmlRWDocBase* docPtr = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	CXmlRWElementBase *pElement = docPtr->GetDocElement();
//	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));

	mms_XmlWrite(pDevice, *docPtr,*pElement);

	ClearFileReadOnlyAttr(strFile);

	//BSTR strTemp = strFile.AllocSysString();
	docPtr->SaveXml(strFile);
	delete docPtr;
//	::SysFreeString(strTemp);

	return 0;
}

long mms_XmlWrite(ACSI_NODE *pDevice, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, BOOL bOblyGetLd)
{
	CXmlRWElementBase* oElement = NULL;

	oElement = oXMLDoc.CreateElement(L"device-model",&oParent);
	oXMLDoc.AppendChild(*oElement);

	long nIndex = 0;
	for (nIndex=0; nIndex<pDevice->numLD; nIndex++)
	{
		mms_XmlWrite(&pDevice->LD[nIndex], oXMLDoc, *oElement, bOblyGetLd);
	}

	return 0;
}

long mms_XmlWrite(LD_NODE *pLDevice, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, BOOL bOblyGetLd)
{
	CXmlRWElementBase* oElement = NULL;
	oElement = oXMLDoc.CreateElement(L"ldevice",&oParent);

	if (oParent.IsValid())
	{
		oParent.AppendChild(*oElement);
	}
	else
	{
		oXMLDoc.AppendChild(*oElement);
	}

	xml_SetAttributeValue(G_BSTRKEY_ID, *oElement, CString(pLDevice->LDName));
	xml_SetAttributeValue(G_BSTRKEY_NAME, *oElement, CString(""));

	if (bOblyGetLd)
	{
		return 0;
	}

	for (int i=0; i<pLDevice->numDaSet; i++)
	{
		LD_DATASET_INFO *pLD_INFO = &pLDevice->DataInfo[i];
		mms_XmlWrite(_T("dataset"),pLD_INFO, oXMLDoc, *oElement);
	}

	CString strElement;
	strElement = G_BSTRKEY_LGCTRL;
	mms_XmlWriteJournalCtrls(strElement, &pLDevice->JournalCtrls, oXMLDoc, *oElement);

	return 0;
}

void mms_XmlWrite(const CString &strElement,RCB_NODE *pRCB, int nNum, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent)
{
	CXmlRWElementBase* oElement = NULL;
	oElement = oXMLDoc.CreateElement(_bstr_t(strElement),&oParent);

	if (oParent.IsValid())
	{
		oParent.AppendChild(*oElement);
	}
	else
	{
		oXMLDoc.AppendChild(*oElement);
	}

	for (int i=0; i<nNum; i++)
	{
		CXmlRWElementBase* oSubElement = NULL;
		oSubElement = oXMLDoc.CreateElement(_bstr_t("data"),oElement);
		oElement->AppendChild(*oSubElement);
		xml_SetAttributeValue(G_BSTRKEY_NAME, *oSubElement, pRCB[i].rcbName);
		xml_SetAttributeValue(G_BSTRKEY_ID, *oSubElement, pRCB[i].RptID);
	}
}

void mms_XmlWriteJournalCtrls(const CString &strElement,LD_JOURNAL_CTRLS *pJournalCtrls, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent)
{
	CXmlRWElementBase* oElement = NULL;
	LD_LOG_INFO *pLogInfo = NULL;
	oElement = oXMLDoc.CreateElement(_bstr_t(strElement),&oParent);

	if (oParent.IsValid())
	{
		oParent.AppendChild(*oElement);
	}
	else
	{
		oXMLDoc.AppendChild(*oElement);
	}

	for (int i=0; i<pJournalCtrls->numData; i++)
	{
		pLogInfo = pJournalCtrls->LogInfo+i;
		CXmlRWElementBase* oSubElement = NULL;
		oSubElement = oXMLDoc.CreateElement(_bstr_t("data"),oElement);
		oElement->AppendChild(*oSubElement);
#ifdef _use_mms_string
		xml_SetAttributeValue(G_BSTRKEY_NAME, *oSubElement, mms_string(&pLogInfo->logRef));
		xml_SetAttributeValue(G_BSTRKEY_ID, *oSubElement, mms_string(&pLogInfo->Name)  );
		xml_SetAttributeValue(G_BSTRKEY_DATASET, *oSubElement, mms_string(&pLogInfo->Dataset) );
#else
		xml_SetAttributeValue(G_BSTRKEY_NAME, *oSubElement,pJournal->logRef.mmsName );
		xml_SetAttributeValue(G_BSTRKEY_ID, *oSubElement,pJournal->Name);
		xml_SetAttributeValue(G_BSTRKEY_DATASET, *oSubElement, pJournal->Dataset.mmsName);
#endif
	}
}

long mms_XmlWrite(const CString &strElement, LD_DATASET_INFO*pLD_INFO, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent)
{
// 	if (pLD_INFO->bHasEnum == 0)
// 	{
// 		return 0;
// 	}

	CXmlRWElementBase* oElement = NULL;
	oElement = oXMLDoc.CreateElement(_bstr_t(strElement),&oParent);
	
	if (oParent.IsValid())
	{
		oParent.AppendChild(*oElement);
	}
	else
	{
		oXMLDoc.AppendChild(*oElement);
	}

	xml_SetAttributeValue(G_BSTRKEY_ID, *oElement, pLD_INFO->DataSetID);
	xml_SetAttributeValue(G_BSTRKEY_NAME, *oElement, pLD_INFO->DaSetDesc);
	mms_XmlWrite(_T("brcb"),pLD_INFO->RCB, pLD_INFO->numRcb, oXMLDoc, *oElement);

	long nIndex = 0;
	for (nIndex=0; nIndex<pLD_INFO->numData; nIndex++)
	{
		mms_XmlWrite("data", &pLD_INFO->DataSet[nIndex], oXMLDoc, *oElement);
	}

	return 0;
}

long mms_XmlWrite(const CString &strElement,tagDA *pDA,CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase* oElement = NULL;
	oElement = oXMLDoc.CreateElement(_bstr_t(strElement),&oParent);
	
	if (oParent.IsValid())
	{
		oParent.AppendChild(*oElement);
	}
	else
	{
		oXMLDoc.AppendChild(*oElement);
	}

	CString strText;
	CString strName , str, strType;

	//strName = pDA->DADescri.Value.name;//mms_UTF8ToUnicode(pDA->DADescri.Value.name, strlen(pDA->DADescri.Value.name));
	strName = mms_GetDADesc(pDA);
	
	if (strName.GetLength() < 1)
	{
#ifdef _use_mms_string
		strName = mms_string(&pDA->DADescri.Value.string);
#else
		strName = pDA->DADescri.Value.string;
#endif
		strName.TrimRight();
	}
	
	//strName = mms_UTF8ToUnicode(str, str.GetLength());

#ifdef _use_mms_string
	str = mms_string(&pDA->DAValue.mmsName);
#else
	str = pDA->DAValue.mmsName;
#endif
	//str.Replace(_T("$"), _T("_"));

	if (strName.IsEmpty())
	{
		xml_SetAttributeValue(G_BSTRKEY_NAME, *oElement, str);
	}
	else
		xml_SetAttributeValue(G_BSTRKEY_NAME, *oElement, strName);

	xml_SetAttributeValue(G_BSTRKEY_ID, *oElement, str);

	//xml_SetAttributeValue(_bstr_t("name-utf8"), oElement, strName);
	strType = pDA->DataType;
	xml_SetAttributeValue(_bstr_t("data-type"), *oElement, strType);

	strText = mms_ParseUnit(pDA->DAUnite.Value.i);
	xml_SetAttributeValue(_bstr_t("unit"), *oElement, strText);
#ifdef _use_mms_string
	strText = mms_string(&pDA->DAUnite.mmsName);
#else
	strText = pDA->DAUnite.mmsName;
#endif
	xml_SetAttributeValue(_bstr_t("unit-path"), *oElement, strText);
	long i = pDA->DAUnite.Value.i;
	xml_SetAttributeValue(_bstr_t("unit-value"), *oElement, i);

	strText = mms_GetDAValue(pDA);
	xml_SetAttributeValue(_bstr_t("value"), *oElement, strText);
	xml_SetAttributeValue(_bstr_t("default-value"), *oElement, strText);
	
#ifdef _use_mms_string
	strText = mms_string(&pDA->DAValue.mmsName);
#else
	strText = pDA->DAValue.mmsName;
#endif
	xml_SetAttributeValue(_bstr_t("value-path"), *oElement, strText);

	//min,max
	strText.Empty();

#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	if (mms_str_length(&pDA->MaxVal.mmsName)>0)
	{
		CString strDataType = "";

		if (mms_GetValueDataType(pDA,strDataType))
		{
			strText = mms_GetValueByDataType(&pDA->MaxVal.Value ,strDataType);
		}
	} 
	else
		strText = mms_GetMaxValue(pDA);
#endif

	xml_SetAttributeValue(G_BSTRKEY_MAX, *oElement, strText);

	strText.Empty();

#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	if (mms_str_length(&pDA->MinVal.mmsName)>0)
	{
		CString strDataType = "";

		if (mms_GetValueDataType(pDA,strDataType))
		{
			strText = mms_GetValueByDataType(&pDA->MinVal.Value ,strDataType);
		}
	} 
	else
		strText = mms_GetMinValue(pDA);
#endif
	
	xml_SetAttributeValue(G_BSTRKEY_MIN, *oElement, strText);

	strText.Empty();

#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	if (mms_str_length(&pDA->StepSize.mmsName)>0)
	{
		CString strDataType = "";

		if (mms_GetValueDataType(pDA,strDataType))
		{
			strText = mms_GetValueByDataType(&pDA->StepSize.Value ,strDataType);
		}
	} 
	else
		mms_GetDAStepSizeValue(pDA, strText);
#endif

	xml_SetAttributeValue(G_BSTRKEY_STEPSIZE, *oElement, strText);

	// 2013-3-4  增加结构体信息的保存
	if (strcmp(pDA->DataType ,"STRUCT") == 0)
	{
		if (pDA->pSubDA && pDA->nSubDANum>0)
		{
// 			long lData = pDA->nSubDANum;
// 			xml_SetAttributeValue(_bstr_t("sub-value-num"), oElement, lData);
// 
// 			CString str;
			for (long nIndex=0; nIndex<pDA->nSubDANum; nIndex++)
			{
// 				strText = pDA->pSubDA[nIndex].DataType;
// 				str.Format(_T("sub-value-type-%d"),nIndex);
// 				xml_SetAttributeValue(_bstr_t(str), oElement, strText);
// 				strText = pDA->pSubDA[nIndex].DAValue.mmsName;
// 				str.Format(_T("sub-value-path-%d"),nIndex);
// 				xml_SetAttributeValue(_bstr_t(str), oElement, strText);
				mms_XmlWrite_SubDA(_T("value"), &pDA->pSubDA[nIndex], oXMLDoc, *oElement);
			}
		}
	}

	return 0;
}

long mms_XmlWrite_SubDA(const CString &strElement,tagDA *pDA,CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CString strText;
	CString strName , str, strType;

	CXmlRWElementBase* oElement = NULL;
	oElement = oXMLDoc.CreateElement(_bstr_t(strElement),&oParent);
	
	if (oParent.IsValid())
	{
		oParent.AppendChild(*oElement);
	}
	else
	{
		oXMLDoc.AppendChild(*oElement);
	}

	strText = pDA->DataType;
	xml_SetAttributeValue(_bstr_t(_T("data-type")), *oElement, strText);

#ifdef _use_mms_string
	strText = mms_string(&pDA->DAValue.mmsName);
#else
	strText = pDA->DAValue.mmsName;
#endif
	xml_SetAttributeValue(_bstr_t(_T("id")), *oElement, strText);

#ifdef _use_mms_string
	strText = mms_string(&pDA->DADescri.Value.string);
#else
	strText = pDA->DADescri.Value.string;
#endif
	xml_SetAttributeValue(_bstr_t(_T("name")), *oElement, strText);

	strText = mms_GetValue(&pDA->DAValue, pDA->DataType);
	xml_SetAttributeValue(_bstr_t(_T("value")), *oElement, strText);

#ifdef _use_mms_string
	strText = mms_string(&pDA->DAValue.mmsName);
#else
	strText = pDA->DAValue.mmsName;
#endif
	xml_SetAttributeValue(_bstr_t(_T("path")), *oElement, strText);

	if (pDA->pSubDA && pDA->nSubDANum>0)
	{
		for (long nIndex=0; nIndex<pDA->nSubDANum; nIndex++)
		{
			mms_XmlWrite_SubDA(_T("value"), &pDA->pSubDA[nIndex], oXMLDoc, *oElement);
		}
	}

	return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2013-2-18  实现文件的导入
///////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL mms_XmlRead(const CString &strFile, ACSI_NODE *pDevice)
{
	if (strFile == pDevice->DeviceFilePath)
	{
		return TRUE;
	}

	CXmlRWDocBase *docPtr = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);

	try
	{
		if ( !xml_OpenFile(docPtr, strFile) )//调用XML2Interface.h中的全局函数，加载资源，入口返回给oDoc；
		{
			delete docPtr;
			return FALSE;
		}
	}
	catch (...)
	{
		delete docPtr;
		return FALSE;
	}

	
// 	CXmlRWDocBase* docPtr = NULL;
// 	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));

	ClearFileReadOnlyAttr(strFile);

// 	BOOL bSucc = docPtr->load(_variant_t(strFile));
// 
// 	if (!bSucc)
// 	{
// 		return FALSE;
// 	}

	CXmlRWNodeBase* oDocRoot = docPtr->GetDocNode();
	CXmlRWNodeBase* oRoot = NULL;
	_bstr_t bstr = L"device-model";
	oRoot = oDocRoot->GetChildNode(bstr);

	if (oRoot != NULL)
	{
		//CTickCount32 oTick;

		mms_XmlRead(pDevice, *oRoot);
		CString_to_char(strFile, pDevice->DeviceFilePath);
		delete docPtr;
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("mms_XmlRead(%s) = %d ms"), strFile, oTick.GetTickCountLong());

		return TRUE;
	}
	else
	{
		delete docPtr;
		return FALSE;
	}
}

long mms_XmlRead(ACSI_NODE *pDevice, CXmlRWNodeBase &pElement)
{
	CXmlRWNodeBase* pNode = &pElement;
	CXmlRWNodeListBase* oNodes = pNode->GetChildNodes();

	if (oNodes == NULL)
	{
		return 0;
	}

	//CTickCount32 oTick;

	long nCount = oNodes->GetNodeNum();
	long nIndex = 0;
	CExBaseObject *pNew = NULL;
	CXmlRWNodeBase* oNode = NULL;
	long nLdCount = 0;
	long nLdIndex = 0;
	_bstr_t bstrNodeName;
	CString strNodeName;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oNode = oNodes->GetChild(nIndex);
		bstrNodeName = oNode->GetNodeName();
		strNodeName = bstrNodeName.GetBSTR();

		if (strNodeName == CDataMngrXmlRWKeys::CDvmLogicDeviceKey())
		{
			nLdCount++;
		}
	}

#ifdef _use_dynamic_mem
	ACSI_NODE *pBack = mms_New_ACSI_NODE_numLD(pDevice, nLdCount, TRUE);//!g_bMmsEnumLDAfterReadXml);
#endif

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("1 = %d ms"), oTick.GetTickCountLong());

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oNode = oNodes->GetChild(nIndex);

		bstrNodeName = oNode->GetNodeName();
		strNodeName = bstrNodeName.GetBSTR();

		if (strNodeName != CDataMngrXmlRWKeys::CDvmLogicDeviceKey())
		{
			continue;
		}

		mms_XmlRead(&pDevice->LD[nLdIndex], *oNode);
		nLdIndex++;
	}
	
#ifndef _use_dynamic_mem
	pDevice->numLD = nCount;
#else
	if (pBack != NULL)
	{
		mms_InitLdAndBrcb(pDevice, pBack);
		mms_Free_ACSI_NODE(pBack);
		free(pBack);
	}
#endif

	return 1;
}

long mms_XmlReadData(RCB_NODE *pRCB, int &nRcb, CXmlRWNodeBase &pNode)
{
// 	ASSERT(pNode.IsValid());
// 	ASSERT(pRCB!=NULL);

	nRcb = 0;
	CString strText;
	CXmlRWNodeListBase* oNodes = pNode.GetChildNodes();

	if (oNodes == NULL)
	{
		return 0;
	}

	nRcb = oNodes->GetNodeNum();
	long nIndex = 0;
	CExBaseObject *pNew = NULL;
	CXmlRWNodeBase* oNode = NULL;

	for (nIndex=0; nIndex<nRcb; nIndex++)
	{
		oNode = oNodes->GetChild(nIndex);
		xml_GetAttibuteValue(G_BSTRKEY_NAME/*_bstr_t("name")*/, *oNode, strText);
		strcpy(pRCB[nIndex].rcbName,strText);

		strText.Empty();
		xml_GetAttibuteValue(G_BSTRKEY_ID/*_bstr_t("name")*/, *oNode, strText);
		strcpy(pRCB[nIndex].RptID,strText);
	}

	return 1;
}

long mms_XmlReadJournalCtrls(LD_JOURNAL_CTRLS *pJournalCtrls, CXmlRWNodeBase &pNode)
{
// 	ASSERT(pNode!=NULL);
// 	ASSERT(pJournalCtrls!=NULL);

//	pJournalCtrls->bHasEnum = 1;
	pJournalCtrls->numData = 0;

	CString strText;
	CXmlRWNodeListBase* oNodes = pNode.GetChildNodes();

	if (oNodes == NULL)
	{
		return 0;
	}

	ST_INT numData = oNodes->GetNodeNum();
	long nIndex = 0;
	CExBaseObject *pNew = NULL;
	CXmlRWNodeBase* oNode = NULL;

	if (numData > 0)
	{
		mms_New_LD_JOURNAL_CTRLS_numData(pJournalCtrls, numData);
	}

	for (nIndex=0; nIndex<numData; nIndex++)
	{
		oNode = oNodes->GetChild(nIndex);
		mms_XmlReadJournal(pJournalCtrls->LogInfo+nIndex, *oNode);
	}

	return 1;
}

long mms_XmlReadJournal(LD_LOG_INFO *pJournal, CXmlRWNodeBase &pNode)
{
	CString strText, strName, strID, strType, strValue;
//	ASSERT (pNode!=NULL);

	xml_GetAttibuteValue(G_BSTRKEY_NAME, pNode, strName);
	strName.TrimRight();
#ifdef _use_mms_string
	mms_str_set2(&pJournal->logRef, strName, strName.GetLength());
#else
	memcpy(pJournal->logRef.mmsName, strID, strName, strName.GetLength());
#endif

	xml_GetAttibuteValue(G_BSTRKEY_ID, pNode, strID);
#ifdef _use_mms_string
//	mms_str_set2(&pJournal->Descri, strID, strID.GetLength());
	mms_str_set2(&pJournal->Name, strID, strID.GetLength());
#else
	memcpy(pJournal->Descri.Value.string, strID.GetLength());
	memcpy(pJournal->Name, strID.GetLength());
#endif

	xml_GetAttibuteValue(G_BSTRKEY_DATASET, pNode, strText);
#ifdef _use_mms_string
	mms_str_set2(&pJournal->Dataset, strText, strText.GetLength());
#else
	memcpy(pJournal->Dataset.mmsName, strText, strText.GetLength());
#endif

	return 0;
}

long mms_XmlRead(LD_NODE *pLDevice, CXmlRWNodeBase &pNode)
{
	CString strName;
	xml_GetAttibuteValue(G_BSTRKEY_ID, pNode, strName);
	strcpy(pLDevice->LDName, strName);

	xml_GetAttibuteValue(G_BSTRKEY_NAME/*_bstr_t("name")*/, pNode, strName);
	strcpy(pLDevice->LDDesc, strName);

	pLDevice->numDaSet = 0;
	CXmlRWNodeListBase* oNodes = pNode.GetChildNodes();

	if (oNodes == NULL)
	{
		return 1;
	}

	//CTickCount32 oTick;
	long nCount = oNodes->GetNodeNum();
	long nDataset = 0;
	long nIndex = 0;
	CExBaseObject *pNew = NULL;
	CXmlRWNodeBase* oNode = NULL;
	CString strNodeName;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oNode = oNodes->GetChild(nIndex);
		strNodeName = oNode->GetNodeName();

		if (strNodeName ==  G_BSTRKEY_DATASET)
		{
			nDataset++;
		}
	}

#ifdef _use_dynamic_mem
	mms_New_LD_NODE_numDataset(pLDevice, nDataset);
#endif

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("\t2 = %d ms"), oTick.GetTickCountLong());

	long nDatasetIndex=0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oNode = oNodes->GetChild(nIndex);
		strNodeName = oNode->GetNodeName();

		if (strNodeName ==  G_BSTRKEY_DATASET)
		{
			LD_DATASET_INFO *pLD_INFO = pLDevice->DataInfo + nDatasetIndex;
			mms_XmlReadData(pLD_INFO, *oNode);
			nDatasetIndex++;

			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("\t2-%d = %d ms"),nIndex, oTick.GetTickCountLong());

#ifndef _use_dynamic_mem
			pLDevice->numDaSet++;
#endif
		}
		else if (strNodeName == G_BSTRKEY_LGCTRL)
		{
			LD_JOURNAL_CTRLS *pJournalCtrls = &pLDevice->JournalCtrls;
			mms_XmlReadJournalCtrls(pJournalCtrls, *oNode);
		}
	}

// 	while (childList->raw_nextNode(&child)==S_OK)
// 	{
// 		LD_DATASET_INFO *pLD_INFO = &pLDevice->DataInfo[pLDevice->numDaSet];
// 		mms_XmlReadData(pLD_INFO, child);
// 		CString strText;
// 		xml_GetAttibuteValue(_bstr_t("id"),child, strText);
// 		strcpy(pLD_INFO->DataSetID,strText);
// 		//xml_GetAttibuteValue(_bstr_t("name"), pLD_INFO->DaSetName);
// 		pLDevice->numDaSet++;
// 	}

	return 1;
}

long mms_XmlReadData(LD_DATASET_INFO *pLD_INFO, CXmlRWNodeBase &pNode)
{
	//CTickCount32 oTick;
	CString strText;
	xml_GetAttibuteValue(G_BSTRKEY_ID,pNode, strText);
	strcpy(pLD_INFO->DataSetID, strText);

	xml_GetAttibuteValue(G_BSTRKEY_NAME/*_bstr_t("name")*/,pNode, strText);
	strcpy(pLD_INFO->DaSetDesc, strText);

	pLD_INFO->numData = 0;
	pLD_INFO->bHasEnum = SD_FALSE;//(pLD_INFO->numData) ? SD_TRUE : SD_FALSE;
	//mms_XmlReadData(pLD_INFO->DataSet, pLD_INFO->numData, pLD_INFO->RCB, pLD_INFO->numRcb, pNode);

	CXmlRWNodeListBase* oNodes = pNode.GetChildNodes();

	if (oNodes == NULL)
	{
		return 0;
	}

	long nCount = oNodes->GetNodeNum();
	long nIndex = 0;
	CExBaseObject *pNew = NULL;
	CXmlRWNodeBase* oNode = NULL;
	CString strNodeName;

#ifdef _use_dynamic_mem
	long nDataCount = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oNode = oNodes->GetChild(nIndex);
		strNodeName = oNode->GetNodeName();

		if (strNodeName ==  G_BSTRKEY_DATA/*_bstr_t("data")*/)
		{
			nDataCount++;
		}
	}

	mms_New_LD_DATASET_INFO_numData(pLD_INFO, nDataCount);
#endif

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("\t\t3 = %d ms"), oTick.GetTickCountLong());

	long nDataIndex = 0;
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oNode = oNodes->GetChild(nIndex);
		strNodeName = oNode->GetNodeName();

		if (strNodeName ==  G_BSTRKEY_DATA/*_bstr_t("data")*/)
		{
			tagDA *pDA = pLD_INFO->DataSet + nDataIndex;
			mms_XmlRead(pDA, *oNode);
			nDataIndex++;
#ifndef _use_dynamic_mem
			pLD_INFO->numData++;
#endif
		}
		else if (strNodeName == G_BSTRKEY_BRCB/*_bstr_t("brcb")*/)
		{
			mms_XmlReadData(pLD_INFO->RCB,pLD_INFO->numRcb, *oNode);
		}

		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("\t\t3-%d = %d ms"), nIndex, oTick.GetTickCountLong());
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("\t\t3-%d = %d ms"),nIndex, oTick.GetTickCountLong());

	pLD_INFO->bHasEnum = (pLD_INFO->numData > 0) ? SD_TRUE : SD_FALSE;
	return 1;

}
// 
// void mms_XmlReadData(tagDA *pDAs, int &nCount, RCB_NODE *pRCB, int &nRcb, CXmlRWNodeBase &pNode)
// {
// 	CXmlRWNodeListBase* childList;
// 	HRESULT hr = pNode->get_childNodes(&childList);
// 
// 	nCount=0;
// 	CXmlRWElementBase* pElement;
// 	MSXML2::IXMLDOMNodePtr child;
// 	while(childList->raw_nextNode(&child)==S_OK)
// 	{
// 		pElement = child;
// 		if (pElement == NULL)
// 			continue;
// 
// 		_bstr_t bstr = pElement->GettagName();
// 		CString strText(bstr.GetBSTR());
// 
// 		if (strText == "brcb")
// 			mms_XmlReadData(pRCB,nRcb, child);
// 		else if (strText == "data")
// 		{		
// 			mms_XmlRead(&pDAs[nCount], child);
// 			nCount++;
// 		}
// 	}
// }


long mms_XmlRead( tagDA *pDA, CXmlRWNodeBase &pNode)
{
	CString strText, strName, strID, strType, strValue;
//	ASSERT (pNode!=NULL);

	xml_GetAttibuteValue(G_BSTRKEY_NAME, pNode, strName);
	strName.TrimRight();
#ifdef _use_mms_string
	mms_str_set2(&pDA->DADescri.Value.string, strName, strName.GetLength());
#else
	memcpy(pDA->DADescri.Value.string, strName, strName.GetLength());
#endif

	xml_GetAttibuteValue(G_BSTRKEY_ID/*_bstr_t("id")*/, pNode, strID);
#ifdef _use_mms_string
	mms_str_set2(&pDA->DAValue.mmsName, strID, strID.GetLength());
#else
	memcpy(pDA->DAValue.mmsName, strID, strID.GetLength());
#endif

	if (strName.GetLength() > 0)
	{
#ifdef _use_mms_string
		mms_str_set2(&pDA->DADescri.mmsName, strID, strID.GetLength());
#else
		memcpy(pDA->DADescri.mmsName, strID, strID.GetLength());
#endif
	}

	xml_GetAttibuteValue(G_BSTRKEY_UNITPATH/*_bstr_t("unit-path")*/, pNode, strText);
#ifdef _use_mms_string
	mms_str_set2(&pDA->DAUnite.mmsName, strText, strText.GetLength());
#else
	memcpy(pDA->DAUnite.mmsName, strText, strText.GetLength());
#endif

	long lData = 0;
	xml_GetAttibuteValue(G_BSTRKEY_UNITVALUE/*_bstr_t("unit-value")*/, pNode, lData);
	pDA->DAUnite.Value.i = lData;

	xml_GetAttibuteValue(G_BSTRKEY_DATATYPE/*_bstr_t("data-type")*/, pNode, strType);
	
	if (strType.GetLength() == 0)
	{
		strType = _T("BIT_STR");
	}

	memcpy(pDA->DataType, strType, strType.GetLength());
	mms_InitDA_DataType(pDA);
	xml_GetAttibuteValue(G_BSTRKEY_VALUE/*_bstr_t("value")*/, pNode, strValue);
	xml_GetAttibuteValue(G_BSTRKEY_DEFVALUE/*_bstr_t("default-value")*/, pNode, strText);

	//min.max
	CString strMax, strMin, strStep;
	strText.Empty();
	strText.Empty();
	strStep.Empty();
	xml_GetAttibuteValue(G_BSTRKEY_MAX/*_bstr_t("max")*/, pNode, strMax);
	xml_GetAttibuteValue(G_BSTRKEY_MIN/*_bstr_t("min")*/, pNode, strMin);
	xml_GetAttibuteValue(G_BSTRKEY_STEPSIZE/*_bstr_t("min")*/, pNode, strStep);

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("read-data-6= %dms"), oTick.GetTickCountLong());

	CString str;
	
	// 2013-3-4  增加结构体信息的保存
	if (strcmp(pDA->DataType ,"STRUCT") == 0)
	{
		//mms_ReleaseData(pDA);

		CXmlRWNodeListBase* oNodes = pNode.GetChildNodes();

		if (oNodes == NULL)
		{
			return 1;
		}

		long nCount = oNodes->GetNodeNum();
		long nIndex = 0;
		CExBaseObject *pNew = NULL;
		CXmlRWNodeBase* oNode = NULL;
		CString strNodeName;
		pDA->nSubDANum = nCount;

		pDA->pSubDA = (tagDA*)malloc(nCount*sizeof(tagDA));
		ZeroMemory(pDA->pSubDA,nCount*sizeof(tagDA));
		mms_InitDatas(pDA->pSubDA, nCount);

		for (int i=0;i<nCount;i++)
		{
			oNode = oNodes->GetChild(i);
			mms_XmlRead_SubDA(&pDA->pSubDA[i], *oNode);
		}
	}
	else
	{
		mms_SetValue(&pDA->DAValue, strValue, strType);
	}

	mms_SetMaxValue(pDA, strMax);
	mms_SetMinValue(pDA, strMin);

	mms_SetStepSizeValue(pDA, strStep);

	return 1;
}

long mms_XmlRead_SubDA(tagDA *pDA, CXmlRWNodeBase &pNode)
{
	CString strTemp, strType;
	xml_GetAttibuteValue(G_BSTRKEY_DATATYPE/*_bstr_t("data-type")*/, pNode, strType);
	strcpy(pDA->DataType,strType);
	mms_InitDA_DataType(pDA);

	//path和ID是同样的值
	xml_GetAttibuteValue(G_BSTRKEY_ID/*_bstr_t(_T("path"))*/, pNode, strTemp);		
#ifdef _use_mms_string
	mms_str_set(&pDA->DAValue.mmsName, strTemp);
#else
	strcpy(pDA->DAValue.mmsName, strTemp);
#endif

	xml_GetAttibuteValue(G_BSTRKEY_NAME/*_bstr_t(_T("name"))*/, pNode, strTemp);		
#ifdef _use_mms_string
	mms_str_set(&pDA->DADescri.Value.string, strTemp);
#else
	strcpy(pDA->DADescri.Value.string, strTemp);
#endif

	xml_GetAttibuteValue(G_BSTRKEY_VALUE/*_bstr_t(_T("value"))*/, pNode, strTemp);		

	if (mms_Is_SubDA_Value(pDA))
	{
		mms_SetValue(&pDA->DAValue, strTemp, strType);
	}
	else
	{
		mms_SetValue(&pDA->DAValue, strTemp, strType);	
	}

	CXmlRWNodeListBase* oNodes = pNode.GetChildNodes();

	if (oNodes == NULL)
	{
		return 1;
	}

	long nCount = oNodes->GetNodeNum();

	if (nCount == 0)
	{
		return 1;
	}

	long nIndex = 0;
	CExBaseObject *pNew = NULL;
	CXmlRWNodeBase* oNode = NULL;
	CString strNodeName;
	pDA->nSubDANum = nCount;

	pDA->pSubDA = (tagDA*)malloc(nCount*sizeof(tagDA));
	ZeroMemory(pDA->pSubDA,nCount*sizeof(tagDA));
	mms_InitDatas(pDA->pSubDA, nCount);

	for (int i=0;i<nCount;i++)
	{
		oNode = oNodes->GetChild(i);
		mms_XmlRead_SubDA(&pDA->pSubDA[i], *oNode);
	}

	return 1;
}

//////////////////////////////////////////////////////////////////////////
// 2013-4-16  加载 scd/cid 文件
#define LDNODE_PATH _T("Server")
#define DATASET_PATH _T("LN0")

void xml_LoadscdFile(const CString &strFile, ACSI_NODE *pDevice)
{
//	CXmlRWDocBase* docPtr = NULL;

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);

	try
	{
		if ( !xml_OpenFile(pRWDoc, strFile) )//调用XML2Interface.h中的全局函数，加载资源，入口返回给oDoc；
		{
			delete pRWDoc;
			return;
		}
	}
	catch (...)
	{
		delete pRWDoc;
		return;
	}


	//docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));

	ClearFileReadOnlyAttr(strFile);

	//BOOL bSucc = docPtr->load(_variant_t(strFile));
	CXmlRWNodeBase* XmlRootptr = pRWDoc->GetDocNode();
	//HRESULT hr = docPtr->get_documentElement(&XmlRootptr);

	if (XmlRootptr != NULL)
	{
		CXmlRWNodeListBase* childList;
		childList = XmlRootptr->GetChildNodes();

		CString strName, strDesc;
		CXmlRWNodeBase* pElement;
		CXmlRWNodeBase* child;
		//CXmlRWNodeBase* nodeptr;
		long nNodesCount = childList->GetNodeNum();

		for (long nNodeIndex = 0;nNodeIndex<nNodesCount;nNodeIndex++)
		//while (childList->raw_nextNode(&child)==S_OK)
		{
			child = childList->GetChild(nNodeIndex);
			pElement = child;
			if (pElement==NULL)
				continue;

			//_bstr_t bstr = pElement->GettagName();
			CString strText;//(bstr.GetBSTR());
			strText = pElement->GetNodeName();

			if (strText==_T("IED"))
			{				
				xml_GetAttibuteValue(G_BSTRKEY_NAME, *child, strName);	
				if (strName.IsEmpty())
					xml_GetAttibuteValue(_bstr_t("inst"), *child, strName);
				xml_GetAttibuteValue(_bstr_t("desc"), *child, strDesc);	

				// 匹配出哪个IED	
				BOOL bMap = FALSE;
				for (int i=0;i<pDevice->numLD;i++)
				{
					LD_NODE *pLD = &pDevice->LD[i];
					if (strstr(pLD->LDName,strName))
					{	
						bMap = TRUE;
						break;
					}
				}
			
				if (bMap) 
				{	// 匹配逻辑设备描述
					xml_LoadAccessPoint(*child, pDevice);
					strcpy(pDevice->devName, strDesc);
					break;
				}
			}
		}	
	}

	delete pRWDoc;
}

// 2013-4-16  加载连接点
void xml_LoadAccessPoint(CXmlRWNodeBase &pNode, ACSI_NODE *pDevice)
{
	CXmlRWNodeListBase* childList;
	childList = pNode.GetChildNodes();

	CString strName, strDesc;
	CXmlRWNodeBase* pElement;
	CXmlRWNodeBase* child;

	long nNodesCount = childList->GetNodeNum();

	for (long nNodeIndex = 0;nNodeIndex<nNodesCount;nNodeIndex++)
	//while (childList->raw_nextNode(&child)==S_OK)
	{
		child = childList->GetChild(nNodeIndex);
		pElement = child;
		if (pElement==NULL)
			continue;

		CString strText = pElement->GetNodeName();
		//CString strText(bstr.GetBSTR());

		if (strText==_T("AccessPoint"))
		{
			xml_LoadLDDesc(*child, pDevice);
		}
	}	
}

// 2013-4-16  加载逻辑设备描述
void xml_LoadLDDesc(CXmlRWNodeBase &pNode, ACSI_NODE *pDevice)
{
	CXmlRWNodeBase* nodeptr;
	nodeptr = pNode.GetChildNode(_bstr_t(LDNODE_PATH));
	if (nodeptr == NULL) return;

	CXmlRWNodeListBase* childList;
	childList = nodeptr->GetChildNodes();

	CString strName, strDesc;
	CXmlRWNodeBase* pElement;
	CXmlRWNodeBase* child;
	long nNodesCount = childList->GetNodeNum();

	for (long nNodeIndex = 0;nNodeIndex<nNodesCount;nNodeIndex++)
	//while (childList->raw_nextNode(&child)==S_OK)
	{
		child = childList->GetChild(nNodeIndex);
		pElement = child;
		if (pElement==NULL)
			continue;

		CString strText = pElement->GetNodeName();
		//CString strText(bstr.GetBSTR());

		if (strText==_T("LDevice"))
		{
			strName = _T("");
			strDesc = _T("");

			xml_GetAttibuteValue(G_BSTRKEY_NAME, *child, strName);	
			if (strName.IsEmpty())
				xml_GetAttibuteValue(_bstr_t("inst"), *child, strName);
			xml_GetAttibuteValue(_bstr_t("desc"), *child, strDesc);	

			for (int i=0;i<pDevice->numLD;i++)
			{
				LD_NODE *pLD = &pDevice->LD[i];

				// 匹配逻辑设备类型
				if (strstr(pLD->LDName,strName))
				{
					strcpy(pLD->LDDesc,strDesc);
					nodeptr = child->GetChildNode(_bstr_t(DATASET_PATH));
					if (nodeptr)
					{
						xml_LoadDataSetDesc(*nodeptr, pLD);
						break;
					}
				}
			}
		}
	}
}

// 2013-4-16  加载数据集描述
void xml_LoadDataSetDesc(CXmlRWNodeBase &pNode, LD_NODE*pLD)
{
	CXmlRWNodeBase* pElement;
	CXmlRWNodeBase* child;
	//CXmlRWNodeBase* nodeptr;

	CXmlRWNodeListBase* childList;
	childList = pNode.GetChildNodes();

	CString strName, strDesc;

	long nNodesCount = childList->GetNodeNum();

	for (long nNodeIndex = 0;nNodeIndex<nNodesCount;nNodeIndex++)
	//while (childList->raw_nextNode(&child)==S_OK)
	{
		child = childList->GetChild(nNodeIndex);
		pElement = child;
		if (pElement==NULL)
			continue;

		CString strText = pElement->GetNodeName();
		//CString strText(bstr.GetBSTR());

		if (strText==_T("DataSet"))
		{
			xml_GetAttibuteValue(G_BSTRKEY_NAME, *child, strName);	
			xml_GetAttibuteValue(_bstr_t("desc"), *child, strDesc);	

			if (strName.IsEmpty())
			{
				xml_GetAttibuteValue(_bstr_t("inst"), *child, strName);	
			}

			for (int i=0;i<pLD->numDaSet;i++)
			{
				LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[i];

				if (strstr(pLD_INFO->DataSetID,strName))
				{
					strcpy(pLD_INFO->DaSetDesc,strDesc);
					xml_LoadDataInfor(*pElement, pLD_INFO);
					break;
				}
			}
		}
	}
}

void xml_LoadDataInfor(CXmlRWNodeBase &pNode, LD_DATASET_INFO*pDataset)
{

}

BOOL mms_GetXml(ACSI_NODE *pDevice, CString &bstrXml, BOOL bOblyGetLd)
{
	//CXmlRWDocBase* oDoc = NULL;
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	
	//HRESULT hr = oDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));

	if (pRWDoc != NULL)
	{
		CXmlRWElementBase *pRWElement = pRWDoc->GetDocElement();
		mms_XmlWrite(pDevice, *pRWDoc, *pRWElement, bOblyGetLd);
		//CXmlRWElementBase *pRWElement = pRWDoc->GetDocElement();
		//CXmlRWNodeBase* oDocRoot = pRWDoc->GetdocumentElement();
		pRWDoc->GetXml(bstrXml);
		delete pRWDoc;
	}

	return TRUE;
}

BOOL mms_GetXml(LD_NODE *pLDevice, CString &bstrXml)
{
	CXmlRWElementBase* oElement = NULL;
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	//HRESULT hr = oXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));
	

	if (pRWDoc != NULL)
	{
		CXmlRWElementBase* oRootElement = pRWDoc->GetDocElement();
		oElement = pRWDoc->CreateElement(_bstr_t("ldevice"),oRootElement);
		pRWDoc->AppendChild(*oElement);
		mms_XmlWrite(pLDevice, *pRWDoc, *oElement);
		
		CXmlRWNodeBase* oDocRoot = pRWDoc->GetDocElement();
		pRWDoc->GetXml(bstrXml);
		delete pRWDoc;
	}
	
	return TRUE;
}

BOOL mms_GetXml(LD_DATASET_INFO *pDataset, CString &bstrXml)
{
	CXmlRWElementBase* oElement = NULL;
	CXmlRWDocBase *oXMLDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	//HRESULT hr = oXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));


	if (oXMLDoc != NULL)
	{
		//oElement = oXMLDoc->createElement(_bstr_t("dataset"));
		//oXMLDoc->appendChild(oElement);
		oElement = oXMLDoc->GetDocElement();
		mms_XmlWrite(_T("dataset"), pDataset, *oXMLDoc, *oElement);
		//CXmlRWNodeBase* oDocRoot = oXMLDoc->GetdocumentElement();
		oXMLDoc->GetXml(bstrXml);
		delete oXMLDoc;
	}

	return TRUE;
}

BOOL mms_SetXml(ACSI_NODE *pDevice,const  CString &bstrXml)
{

	return TRUE;
}

BOOL mms_SetXml(LD_NODE *pLDevice,const  CString &bstrXml)
{

	return TRUE;
}

BOOL mms_SetXml(LD_DATASET_INFO *pDataset,const CString &bstrXml)
{
	
	return TRUE;
}



//////////////////////////////////////////////////////////////////////////
//
long mms_GetLdIndex(LD_NODE *pLdevice)
{
	long nPos = strlen(pLdevice->LDName) - 1;
	long nLastPos = nPos;

	if (nPos <= 0)
	{
		return -1;
	}

	long nIndex = -1;
	char ch = 0;
	BOOL bFind = FALSE;

	while (TRUE)
	{
		ch = pLdevice->LDName[nPos];

		if ('0' <= ch && ch <= '9')
		{
			nLastPos = nPos;
			bFind = TRUE;
			nPos--;
		}
		else
		{
			break;
		}
	}

	if (bFind)
	{
		nIndex = atol(&pLdevice->LDName[nLastPos]);
	}

	return nIndex;
}

LD_NODE* mms_FindLdByIndex(ACSI_NODE *pDevice, long nLdIndex)
{
	LD_NODE *pFind = 0;
	long nIndex = 0;
	
	for (nIndex=0; nIndex<pDevice->numLD; nIndex++)
	{
		if (nLdIndex == mms_GetLdIndex(&pDevice->LD[nIndex]))
		{
			pFind = &pDevice->LD[nIndex];
			break;
		}
	}

	return pFind;
}

void mms_InitLdAndBrcb(LD_DATASET_INFO *pDestDataset, LD_DATASET_INFO *pSrcDataset)
{
	long nIndex = 0;
	pDestDataset->numRcb = pSrcDataset->numRcb;

	for (nIndex=0; nIndex<pSrcDataset->numRcb; nIndex++)
	{
		strcpy(pDestDataset->RCB[nIndex].dsName, pSrcDataset->RCB[nIndex].dsName);
		strcpy(pDestDataset->RCB[nIndex].rcbName, pSrcDataset->RCB[nIndex].rcbName);
		strcpy(pDestDataset->RCB[nIndex].RptID, pSrcDataset->RCB[nIndex].RptID);
	}

}

void mms_InitLdAndBrcb(LD_NODE *pDestLdevice, LD_NODE *pSrcLdevice)
{
	long nIndex = 0;
	long nFind = 0;

	if (pSrcLdevice == NULL)
	{
		return;
	}

	strcpy(pDestLdevice->LDName, pSrcLdevice->LDName);
	strcpy(pDestLdevice->LDDesc, pSrcLdevice->LDDesc);
	
	for (nIndex=0; nIndex<pDestLdevice->numDaSet; nIndex++)
	{
		for (nFind=0; nFind<pSrcLdevice->numDaSet; nFind++)
		{
			if (strcmp(pDestLdevice->DataInfo[nIndex].DataSetID, pSrcLdevice->DataInfo[nFind].DataSetID) == 0)
			{
				mms_InitLdAndBrcb(&pDestLdevice->DataInfo[nIndex], &pSrcLdevice->DataInfo[nFind]);
				break;
			}
		}
	}
}

void mms_InitLdAndBrcb(ACSI_NODE *pDestDevice, ACSI_NODE *pSrcDevice)
{
	if (pSrcDevice->LD == NULL || pSrcDevice->numLD == 0)
	{
		return;
	}

	long nIndex = 0;
	long nLdIndex = 0;
	LD_NODE *pCurr = NULL;
	LD_NODE *pFind = NULL;

	for (nIndex=0; nIndex<pDestDevice->numLD; nIndex++)
	{
		pCurr = &pDestDevice->LD[nIndex];
		nLdIndex = mms_GetLdIndex(pCurr);

		if (nLdIndex == -1)
		{
			continue;
		}

		pFind = mms_FindLdByIndex(pSrcDevice, nLdIndex);

		if (pFind != NULL)
		{
			mms_InitLdAndBrcb(pCurr, pFind);
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//数据建模部分
void mms_XmlWriteNode(const CString &strFile,ACSI_NODE *pDevice, BOOL bChangeFile)
{
	CXmlRWDocBase* docPtr = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);

	if (docPtr == NULL)
	{
		return;
	}

	CXmlRWElementBase *pRWElement = docPtr->GetDocElement();
	//docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));

	mms_XmlWriteNode(pDevice, *docPtr,*pRWElement);

	CString strTemp;

	if (bChangeFile)
	{
		strTemp = strFile.Left(strFile.GetLength() - 4);
		strTemp += _T("_node.xml");
	}
	else
	{
		strTemp = strFile;
	}
	
	ClearFileReadOnlyAttr(strTemp);

	//BSTR bstrTemp = strTemp.AllocSysString();
	docPtr->SaveXml(strTemp);
	//::SysFreeString(bstrTemp);

	delete docPtr;
}

void mms_XmlWriteNode(ACSI_NODE *pDevice, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent)
{
	CXmlRWElementBase* oElement = NULL;

	oElement = oXMLDoc.CreateElement(_bstr_t("device-model"),&oParent);
	oXMLDoc.AppendChild(*oElement);

	long nIndex = 0;

	for (nIndex=0; nIndex<pDevice->numLD; nIndex++)
	{
		mms_XmlWriteNode(&pDevice->LD[nIndex], oXMLDoc, *oElement);
	}
}

void mms_XmlWriteNode(LD_NODE *pLDevice, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent)
{
	CXmlRWElementBase* oElement = NULL;
	oElement = oXMLDoc.CreateElement(_bstr_t("ldevice"),&oParent);

	if (oParent.IsValid())
	{
		oParent.AppendChild(*oElement);
	}
	else
	{
		oXMLDoc.AppendChild(*oElement);
	}

	xml_SetAttributeValue(G_BSTRKEY_ID, *oElement, CString(pLDevice->LDName));
	xml_SetAttributeValue(G_BSTRKEY_NAME, *oElement, CString(""));

	MMS_DATA_NODE *pHead = pLDevice->mms_data_node;
	MMS_DATA_NODE *pCurr = pHead;

	if (pCurr == NULL)
	{
		return;
	}

	do
	{
		mms_XmlWriteNode(pCurr, oXMLDoc, *oElement);
		pCurr = pCurr->pNext;
	}while (pCurr != pHead && pCurr != NULL);
}

void mms_XmlWriteNode(MMS_DATA_NODE *pNode, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent)
{
	CXmlRWElementBase* oElement = NULL;
	oElement = oXMLDoc.CreateElement(_bstr_t("node"),&oParent);

	if (oParent.IsValid())
	{
		oParent.AppendChild(*oElement);
	}
	else
	{
		oXMLDoc.AppendChild(*oElement);
	}

	mms_XmlWriteNodeAttr(pNode, *oElement);

	MMS_DATA_NODE *FC_node = pNode->pFirstChild;
	MMS_DATA_NODE *Head_FC_node = pNode->pFirstChild;

	if (Head_FC_node == NULL)
	{
		return;
	}

	do
	{
		mms_XmlWriteNode(FC_node, oXMLDoc, *oElement);
		FC_node = FC_node->pNext;
	} while (FC_node != Head_FC_node && FC_node != NULL);
}


void mms_XmlWriteNodeAttr(MMS_DATA_NODE *pNode, CXmlRWElementBase &oElement)
{
#ifdef _use_mms_string
	xml_SetAttributeValue(G_BSTRKEY_ID, oElement, mms_string(&pNode->name));
#else
	xml_SetAttributeValue(G_BSTRKEY_ID, oElement, CString(pNode->name));
#endif

	xml_SetAttributeValue(G_BSTRKEY_NAME, oElement, CString(""));
	xml_SetAttributeValue(G_BSTRKEY_DATATYPE, oElement, pNode->DataType);
	
	CString str_NODE_TYPE;
	switch (pNode->type)
	{
	case IED_TYPE:
		str_NODE_TYPE = _T("IED");
		break;
	case LD_TYPE:
		str_NODE_TYPE = _T("LD");
		break;
	case LN_TYPE:
		str_NODE_TYPE = _T("LN");
		break;
	case FC_TYPE:
		str_NODE_TYPE = _T("FC");
		break;
	case DO_TYPE:
		str_NODE_TYPE = _T("DO");
		break;
	case DA_TYPE:
		str_NODE_TYPE = _T("DA");
		break;
	case ERROR_TYPE:
		str_NODE_TYPE = _T("ERROR");
		break;
	}

	xml_SetAttributeValue(G_BSTRKEY_NODETYPE, oElement, str_NODE_TYPE);
}


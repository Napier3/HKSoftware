#include "stdafx.h"
#include "ModelWriteXml.h"
#include "..\..\..\Module\API\FileApi.h"
//#include "..\..\DllFile\Module\HistoryFileCheckAPI\HistoryFileCheckAPI.h"
#include "..\EnumType.h"

static BSTR G_BSTRKEY_NAME  = L"name";
static BSTR G_BSTRKEY_ID  = L"id";
static BSTR G_BSTRKEY_UNIT  = L"unit";
static BSTR G_BSTRKEY_UNITPATH  = L"unit-path";
static BSTR G_BSTRKEY_UNITVALUE  = L"unit-value";
static BSTR G_BSTRKEY_DATATYPE  = L"data-type";
static BSTR G_BSTRKEY_NODETYPE  = L"node-type";
static BSTR G_BSTRKEY_VALUE  = L"value";
static BSTR G_BSTRKEY_VALUEPATH  = L"value-path";
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
static BSTR G_BSTRKEY_DEVICEMODEL  = L"device-model";
static BSTR G_BSTRKEY_LDEVICE  = L"ldevice";

CStringArray g_strarrLNodeTypes;
CStringArray g_strarrDOTypes;

#define ModelWrite_DatasetID_dsMaxCount            25

const CString g_strModelWriteDataSetID[ModelWrite_DatasetID_dsMaxCount] = {_T("dsParameter"),_T("dsSetting"),_T("dsRelayEna"),_T("dsEna"),_T("dsRelayAin"),_T("dsAin")
,_T("dsRelayDin"), _T("dsDin"),_T("dsRelayRec"),_T("dsRec"),_T("dsTripInfo"),_T("dsAlarm"),_T("dsSetGrpNum"),_T("dsDeviceState"),_T("dsCommState"),_T("dsLog")
, _T("dsWarning"),_T("dsSoe"),_T("dsSV"),_T("dsGOOSE"), _T("dsDout"),_T("dsLog"),_T("dsRelayBlk"),_T("dsRelayFunEn"),_T("dsRelayState")};


const CString g_strModelWriteDataSetName[ModelWrite_DatasetID_dsMaxCount] = {_T("装置参数"),_T("定值"),_T("保护压板"),_T("压板"),_T("保护遥测"), _T("遥测")
,_T("保护遥信"), _T("遥信"),_T("保护录波"),_T("故障报告"),_T("保护事件"),_T("故障信号"),_T("定值区号"),_T("设备状态"),_T("通用状态"),_T("日志")
, _T("告警信号"),_T("SOE"),_T("采样值"),_T("GOOSE") , _T("遥控"),_T("日志"),_T("保护闭锁"),_T("保护功能压板"),_T("保护状态信息")};

#ifndef _PSX_IDE_QT_
bool UTF8ToMultiByte_Char(char *srcStr)
{
	ST_INT iTextLen = 0;
	unsigned short wszGBK[256] = {0};

	memset(wszGBK, 0, 256);

	iTextLen = MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, NULL,0); 
	memset(wszGBK, 0, iTextLen * 2 + 2); 
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, (LPWSTR)wszGBK, iTextLen); 

	iTextLen = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL); 
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, srcStr, iTextLen, NULL, NULL); 

	return true;
}

bool UTF8ToMultiByte_Char(CString &srcStr)
{
	ST_INT iTextLen = 0;
	unsigned short wszGBK[256] = {0};

	memset(wszGBK, 0, 256);

	iTextLen = MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, NULL,0); 
	memset(wszGBK, 0, iTextLen * 2 + 2); 
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, (LPWSTR)wszGBK, iTextLen); 

	iTextLen = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL); 
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, (LPSTR)(LPCSTR)srcStr, iTextLen, NULL, NULL); 

	return true;
}
#endif

#include "../../../Module/API/StringConvert/String_Utf8_To_Gbk.h"
void Utf8_to_gbk(char *pszUtf8, CString &strGbk)
{
	unsigned char* pTmpStringGBK = NULL;
	int nSrcLen = strlen(pszUtf8);
	int nLenth = 0;
	utf8_to_gbk_r((const unsigned char*)pszUtf8,nSrcLen,&pTmpStringGBK,&nLenth);

	if (nLenth>0)
	{
		strGbk = (char*)pTmpStringGBK;
	} 
	else
	{
		strGbk = pszUtf8;
	}

	if (pTmpStringGBK != NULL)
	{
		delete pTmpStringGBK;
	}
}

BSTR GetElementKey(const CString &strElement)
{
	if (strElement == _T("dataset"))
	{
		return G_BSTRKEY_DATASET;
	}

	if (strElement == _T("data"))
	{
		return G_BSTRKEY_DATA;
	}

	if (strElement == _T("value"))
	{
		return G_BSTRKEY_VALUE;
	}

	if (strElement == _T("log-ctrl"))
	{
		return G_BSTRKEY_LGCTRL;
	}

	if (strElement == _T("brcb"))
	{
		return G_BSTRKEY_BRCB;
	}
}

void scl_get_ln_name_model(SCL_LN  *scl_ln, ST_CHAR *lnName)
{
#ifdef SCL_USE_MMS_STRING_
	strncpy (lnName, mms_string(&scl_ln->prefix), MAX_IDENT_LEN + 1);
	strncat (lnName, mms_string(&scl_ln->lnClass), MAX_IDENT_LEN + 1 - strlen(lnName));
	strncat (lnName, mms_string(&scl_ln->inst),  MAX_IDENT_LEN + 1 - strlen(lnName));
#else
	strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
	strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
	strncat (lnName, scl_ln->inst,  MAX_IDENT_LEN + 1 - strlen(lnName));
#endif
}


BOOL check_decimal_format(const CString &strDecimal)
{
	long nIndex = strDecimal.GetLength();

	if (nIndex == 0)
	{
		return 0;
	}

	for (int nCount = 0;nCount<nIndex;nCount++)
	{
		if ((strDecimal.GetAt(nCount)<'0')||(strDecimal.GetAt(nCount)>'9'))
		{
			return 0;
		}
	}
	return 1;
}

CString Global_GetDatasetStdNameByID(const CString &strDataSetID)
{
	for (int nIndex = 0;nIndex<ModelWrite_DatasetID_dsMaxCount;nIndex++)
	{
		if (strDataSetID.Find(g_strModelWriteDataSetID[nIndex])>=0)
		{
			return g_strModelWriteDataSetName[nIndex];
		}
	}

	return _T("");
}

long model_XmlWrite(const CString &strFile,SCL_IED*  scl_ied,SCL_INFO *pSclInfo,BOOL bAnalCtrlData,BOOL bDLT860Model)
{
// 	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
// 	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	ASSERT(pRWDoc);
	CXmlRWElementBase *pElement = pRWDoc->GetDocElement();

	if (pElement == NULL)
	{
		delete pRWDoc;
		return 0;
	}

	if (bAnalCtrlData)
	{
		get_all_ctrltype_lnodetype(pSclInfo);
	}
	
	model_XmlWrite(scl_ied, *pRWDoc,*pElement,pSclInfo,bAnalCtrlData,bDLT860Model);

	CString strFolderPath;
	CreateAllDirectories(GetPathFromFilePathName(strFile));
	ClearFileReadOnlyAttr(strFile);

//	BSTR strTemp = strFile.AllocSysString();
	pRWDoc->SaveXml(strFile);
	delete pRWDoc;
//	::SysFreeString(strTemp);

	return 1;
}

void get_all_ctrltype_lnodetype(SCL_INFO *pSclInfo)
{
	if (pSclInfo == NULL)
		return;

	SCL_LNTYPE *pScl_lntype = NULL;
	SCL_DOTYPE *doType = NULL;
	SCL_DA *scl_da = NULL;
	SCL_DO *scl_do = NULL;
	bool bSymbol1,bSmbol2;
	g_strarrDOTypes.RemoveAll();
	g_strarrLNodeTypes.RemoveAll();

	for (doType = (SCL_DOTYPE *)list_find_last((DBL_LNK *)pSclInfo->doTypeHead);
		doType != NULL;
		doType = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)pSclInfo->doTypeHead, (DBL_LNK *)doType))
	{
#ifdef SCL_USE_MMS_STRING_
		if ((0 == stricmp(mms_string(&doType->cdc), "SPC"))||(0 == stricmp(mms_string(&doType->cdc), "DPC"))||
			(0 == stricmp(mms_string(&doType->cdc), "INC"))||(0 == stricmp(mms_string(&doType->cdc), "BSC")))
#else
		if ((0 == stricmp(doType->cdc, "SPC"))||(0 == stricmp(doType->cdc, "DPC"))||(0 == stricmp(doType->cdc, "INC"))||(0 == stricmp(doType->cdc, "BSC")))
#endif
		{
			bSymbol1 = false;
			bSmbol2 = false;

			for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)doType->daHead);//获取DOType中的DA及其对应的type
				scl_da != NULL;
				scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)doType->daHead, (DBL_LNK *)scl_da))
			{
				if (0 == stricmp(scl_da->fc, "CO"))
				{
					bSymbol1 = true;
					bSmbol2 = true;
					break;
				}
			}

			if ((bSymbol1 == true)&&(bSmbol2 == true))
			{
#ifdef SCL_USE_MMS_STRING_
				g_strarrDOTypes.Add(mms_string(&doType->id));
#else
				g_strarrDOTypes.Add(doType->id);
#endif
			}
		}
	}

	long nSize = g_strarrDOTypes.GetSize();

	for (pScl_lntype = (SCL_LNTYPE *)list_find_last((DBL_LNK *)pSclInfo->lnTypeHead);
		pScl_lntype != NULL;
		pScl_lntype = (SCL_LNTYPE *)list_find_prev((DBL_LNK *)pSclInfo->lnTypeHead, (DBL_LNK *)pScl_lntype))
	{
		bSymbol1 = false;

		for (scl_do = (SCL_DO *)list_find_last((DBL_LNK *)pScl_lntype->doHead);
			scl_do != NULL;
			scl_do = (SCL_DO *)list_find_prev((DBL_LNK *)pScl_lntype->doHead, (DBL_LNK *)scl_do))
		{
			for (int nCount = 0;nCount<nSize;nCount++)
			{
#ifdef SCL_USE_MMS_STRING_
				if (g_strarrDOTypes.GetAt(nCount) == mms_string(&scl_do->type))
				{
					g_strarrLNodeTypes.Add(mms_string(&pScl_lntype->id));
#else
				if (g_strarrDOTypes.GetAt(nCount) == scl_do->type)
				{
					g_strarrLNodeTypes.Add(pScl_lntype->id);
#endif
						bSymbol1 = true;
					break;
				}
			}

			if (bSymbol1 == true)
			{
				break;
			}
		}
	}
}

long model_XmlWrite(SCL_IED* scl_ied, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent,SCL_INFO *pSclInfo,BOOL bAnalCtrlData,BOOL bDLT860Model)
{
//	MSXML2::IXMLDOMElementPtr oElement = NULL;

	CXmlRWElementBase *pElement = oXMLDoc.CreateElement(G_BSTRKEY_DEVICEMODEL,&oParent);
	oXMLDoc.AppendChild(*pElement);

// 	oElement = oXMLDoc->createElement(_bstr_t("device-model"));
// 	oXMLDoc->appendChild(oElement);

	long nIndex = 0;

	SCL_AP		*scl_ap = NULL;
	SCL_LD		*scl_ld = NULL;

	for (scl_ap = (SCL_AP *)list_find_last((DBL_LNK *)scl_ied->apHead);
		scl_ap != NULL;
		scl_ap = (SCL_AP *)list_find_prev((DBL_LNK *)scl_ied->apHead, (DBL_LNK *)scl_ap))
	{
#ifdef SCL_USE_MMS_STRING_
		if ((0 == stricmp(mms_string(&scl_ap->name), "S1"))||(0 == stricmp(mms_string(&scl_ap->name), "P1"))||(0 == stricmp(mms_string(&scl_ap->name), "A1"))
			||(0 == stricmp(mms_string(&scl_ap->name), "accessPoint1")))
#else
		if ((0 == stricmp(scl_ap->name, "S1"))||(0 == stricmp(scl_ap->name, "P1"))||(0 == stricmp(scl_ap->name, "A1"))||(0 == stricmp(scl_ap->name, "accessPoint1")))
#endif
		{
			for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)scl_ap->ldHead);
				scl_ld != NULL;
				scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ap->ldHead, (DBL_LNK *)scl_ld))
			{
//				if (0 != stricmp(scl_ld->inst, "MGR"))
				{
#ifdef SCL_USE_MMS_STRING_
					model_XmlWrite(CString(mms_string(&scl_ied->name)),scl_ld, oXMLDoc, *pElement,pSclInfo,bAnalCtrlData,bDLT860Model);
#else
					model_XmlWrite(CString(scl_ied->name),scl_ld, oXMLDoc, *pElement,pSclInfo,bAnalCtrlData,bDLT860Model);
#endif
				}
			}
		}
	}

	return 0;
}

SCL_LN* Scl_FindSclLN_ByLnName(SCL_LD* scl_ld,const CString &strLnName) 
{
	SCL_LN		*scl_ln = NULL;

	for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
		scl_ln != NULL;
		scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
	{
		ST_CHAR lnName	[MAX_TYPE_LEN + 1] = {0};

		scl_get_ln_name_model(scl_ln, lnName);
		char *pszName = NULL;
		CString_to_char(strLnName, &pszName);

		if (0 == stricmp(lnName, pszName))
		{
			delete pszName;
			break;
		}

		delete pszName;
	}

	return scl_ln;
}

void model_XmlWrite_dsDevStdMsg(const CString &strLDName,SCL_LN	*scl_ln ,CXmlRWDocBase &oXMLDoc, CXmlRWElementBase *pParentElement,SCL_INFO *pSclInfo)
{
	BOOL bFindSerNum = FALSE,bFindSwRev = FALSE,bFindSwDate = FALSE,bFindRevCrc = FALSE,bFindAdRev = FALSE,bFindAdDate = FALSE,bFindAdRevCrc = FALSE;
	BOOL bFindSASPinCrc = FALSE,bFindIEDPinCrc = FALSE;
	SCL_DAI *scl_dai = NULL;
	CString strDAI;
	SCL_LNTYPE *pScl_lntype = NULL;
	SCL_DO *pScl_do = NULL;
	CString strPhyNamDO_Type = _T(""),strSASPinCrcDO_Type = _T(""),strIEDPinCrcDO_Type = _T("");

	for (pScl_lntype = (SCL_LNTYPE *)list_find_last((DBL_LNK *)pSclInfo->lnTypeHead);
		pScl_lntype != NULL;
		pScl_lntype = (SCL_LNTYPE *)list_find_prev((DBL_LNK *)pSclInfo->lnTypeHead, (DBL_LNK *)pScl_lntype))
	{
#ifdef SCL_USE_MMS_STRING_
		if(0 == strcmp(mms_string(&pScl_lntype->id), mms_string(&scl_ln->lnType)))
#else
		if(0 == strcmp(pScl_lntype->id, scl_ln->lnType))
#endif
		{
			for (pScl_do = (SCL_DO *)list_find_last((DBL_LNK *)pScl_lntype->doHead);
				pScl_do != NULL;
				pScl_do = (SCL_DO *)list_find_prev((DBL_LNK *)pScl_lntype->doHead, (DBL_LNK *)pScl_do))
			{
#ifdef SCL_USE_MMS_STRING_
				if(0 == strcmp(mms_string(&pScl_do->name),_T("PhyNam")))
#else
				if(0 == strcmp(pScl_do->name, _T("PhyNam")))
#endif
				{
					strPhyNamDO_Type = mms_string(&pScl_do->type);
				}
#ifdef SCL_USE_MMS_STRING_
				else if(0 == strcmp(mms_string(&pScl_do->name),_T("SASPinCrc")))
#else
				else if(0 == strcmp(pScl_do->name, _T("SASPinCrc")))
#endif
				{
					strSASPinCrcDO_Type = mms_string(&pScl_do->type);
				}			
#ifdef SCL_USE_MMS_STRING_
				else if(0 == strcmp(mms_string(&pScl_do->name),_T("IEDPinCrc")))
#else
				else if(0 == strcmp(pScl_do->name, _T("IEDPinCrc")))
#endif
				{
					strIEDPinCrcDO_Type = mms_string(&pScl_do->type);
				}			
			}

			break;
		}
	}

	if (strPhyNamDO_Type.IsEmpty())
	{
		return;
	}

	SCL_DOTYPE *pDO_Type = NULL;
	SCL_DA *pScl_da = NULL;

	char* pszPhyNamDO_Type = NULL;
	CString_to_char(strPhyNamDO_Type, &pszPhyNamDO_Type);
	char* pszSASPinCrcDO_Type = NULL;
	CString_to_char(strSASPinCrcDO_Type, &pszSASPinCrcDO_Type);
	char* pszIEDPinCrcDO_Type = NULL;
	CString_to_char(strIEDPinCrcDO_Type, &pszIEDPinCrcDO_Type);

	for (pDO_Type = (SCL_DOTYPE *)list_find_last((DBL_LNK *)pSclInfo->doTypeHead);
		pDO_Type != NULL;
		pDO_Type = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)pSclInfo->doTypeHead, (DBL_LNK *)pDO_Type))
	{
#ifdef SCL_USE_MMS_STRING_
		if(0 == strcmp(mms_string(&pDO_Type->id), pszPhyNamDO_Type))
#else
		if(0 == strcmp(pDO_Type->id, pszPhyNamDO_Type))
#endif
		{
			for (pScl_da = (SCL_DA *)list_find_last((DBL_LNK *)pDO_Type->daHead);//获取DOType中的DA及其对应的type
				pScl_da != NULL;
				pScl_da = (SCL_DA *)list_find_prev((DBL_LNK *)pDO_Type->daHead, (DBL_LNK *)pScl_da))
			{
#ifdef SCL_USE_MMS_STRING_
				if(0 == strcmp(mms_string(&pScl_da->name), _T("serNum")))
#else
				if(0 == strcmp(pScl_da->name, _T("serNum")))
#endif
				{
					bFindSerNum = TRUE;
				}

#ifdef SCL_USE_MMS_STRING_
				if(0 == strcmp(mms_string(&pScl_da->name), _T("swRev")))
#else
				if(0 == strcmp(pScl_da->name, _T("swRev")))
#endif
				{
					bFindSwRev = TRUE;
				}

#ifdef SCL_USE_MMS_STRING_
				if(0 == strcmp(mms_string(&pScl_da->name), _T("swDate")))
#else
				if(0 == strcmp(pScl_da->name, _T("swDate")))
#endif
				{
					bFindSwDate = TRUE;
				}

#ifdef SCL_USE_MMS_STRING_
				if(0 == strcmp(mms_string(&pScl_da->name), _T("swRevCrc")))
#else
				if(0 == strcmp(pScl_da->name, _T("swRevCrc")))
#endif
				{
					bFindRevCrc = TRUE;
				}

#ifdef SCL_USE_MMS_STRING_
				if(0 == strcmp(mms_string(&pScl_da->name), _T("adSwRev")))
#else
				if(0 == strcmp(pScl_da->name, _T("adSwRev")))
#endif
				{
					bFindAdRev = TRUE;
				}

#ifdef SCL_USE_MMS_STRING_
				if(0 == strcmp(mms_string(&pScl_da->name), _T("adSwDate")))
#else
				if(0 == strcmp(pScl_da->name, _T("adSwDate")))
#endif
				{
					bFindAdDate = TRUE;
				}

#ifdef SCL_USE_MMS_STRING_
				if(0 == strcmp(mms_string(&pScl_da->name), _T("adSwRevCrc")))
#else
				if(0 == strcmp(pScl_da->name, _T("adSwRevCrc")))
#endif
				{
					bFindAdRevCrc = TRUE;
				}
			}

//			break;
		}
#ifdef SCL_USE_MMS_STRING_
		 if((!strSASPinCrcDO_Type.IsEmpty())&&(0 == strcmp(mms_string(&pDO_Type->id), pszSASPinCrcDO_Type)))
#else
		if((!strSASPinCrcDO_Type.IsEmpty())&&(0 == strcmp(pDO_Type->id, pszSASPinCrcDO_Type)))
#endif
		{
			for (pScl_da = (SCL_DA *)list_find_last((DBL_LNK *)pDO_Type->daHead);//获取DOType中的DA及其对应的type
				pScl_da != NULL;
				pScl_da = (SCL_DA *)list_find_prev((DBL_LNK *)pDO_Type->daHead, (DBL_LNK *)pScl_da))
			{
#ifdef SCL_USE_MMS_STRING_
				if(0 == strcmp(mms_string(&pScl_da->name), _T("setVal")))
#else
				if(0 == strcmp(pScl_da->name, _T("setVal")))
#endif
				{
					bFindSASPinCrc = TRUE;
				}
			}
		} 
#ifdef SCL_USE_MMS_STRING_
		if((!strIEDPinCrcDO_Type.IsEmpty())&&(0 == strcmp(mms_string(&pDO_Type->id), pszIEDPinCrcDO_Type)))
#else
		if((!strIEDPinCrcDO_Type.IsEmpty())&&(0 == strcmp(pDO_Type->id, pszIEDPinCrcDO_Type)))
#endif
		{
			for (pScl_da = (SCL_DA *)list_find_last((DBL_LNK *)pDO_Type->daHead);//获取DOType中的DA及其对应的type
				pScl_da != NULL;
				pScl_da = (SCL_DA *)list_find_prev((DBL_LNK *)pDO_Type->daHead, (DBL_LNK *)pScl_da))
			{
#ifdef SCL_USE_MMS_STRING_
				if(0 == strcmp(mms_string(&pScl_da->name), _T("setVal")))
#else
				if(0 == strcmp(pScl_da->name, _T("setVal")))
#endif
				{
					bFindIEDPinCrc = TRUE;
				}
			}
		}
	}

	delete pszPhyNamDO_Type;
	delete pszSASPinCrcDO_Type;
	delete pszIEDPinCrcDO_Type;

	if ((!bFindSerNum)&&(!bFindSwRev))
	{
		return;
	}

	CXmlRWElementBase *pElementDsDevStdMsg = oXMLDoc.CreateElement(G_BSTRKEY_DATASET,pParentElement);
	pParentElement->AppendChild(*pElementDsDevStdMsg);
	CString strDataSetName = _T("LLN0$dsDevStdMsg");
	xml_SetAttributeValue(G_BSTRKEY_ID, *pElementDsDevStdMsg, strDataSetName);
	xml_SetAttributeValue(G_BSTRKEY_NAME, *pElementDsDevStdMsg, "版本及CRC信息");
	CXmlRWElementBase *pChildElement = NULL;

	if (bFindSerNum)
	{
		pChildElement = oXMLDoc.CreateElement(G_BSTRKEY_DATA,pElementDsDevStdMsg);
		oXMLDoc.AppendChild(*pChildElement);
		pElementDsDevStdMsg->AppendChild(*pChildElement);
		xml_SetAttributeValue(G_BSTRKEY_NAME, *pChildElement, _T("装置识别代码"));
		xml_SetAttributeValue(G_BSTRKEY_ID, *pChildElement, _T("LPHD1$DC$PhyNam$serNum"));
		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pChildElement, _T("V_STR"));
	}

	if (bFindSwRev)
	{
		pChildElement = oXMLDoc.CreateElement(L"data",pElementDsDevStdMsg);
		oXMLDoc.AppendChild(*pChildElement);
		pElementDsDevStdMsg->AppendChild(*pChildElement);
		xml_SetAttributeValue(G_BSTRKEY_NAME, *pChildElement, _T("程序版本"));
		xml_SetAttributeValue(G_BSTRKEY_ID, *pChildElement, _T("LPHD1$DC$PhyNam$swRev"));
		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pChildElement, _T("V_STR"));
	}

	if (bFindSwDate)
	{
		pChildElement = oXMLDoc.CreateElement(L"data",pElementDsDevStdMsg);
		oXMLDoc.AppendChild(*pChildElement);
		pElementDsDevStdMsg->AppendChild(*pChildElement);
		xml_SetAttributeValue(G_BSTRKEY_NAME, *pChildElement, _T("程序生成日期"));
		xml_SetAttributeValue(G_BSTRKEY_ID, *pChildElement, _T("LPHD1$DC$PhyNam$swDate"));
		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pChildElement, _T("V_STR"));
	}

	if (bFindRevCrc)
	{
		pChildElement = oXMLDoc.CreateElement(L"data",pElementDsDevStdMsg);
		oXMLDoc.AppendChild(*pChildElement);
		pElementDsDevStdMsg->AppendChild(*pChildElement);
		xml_SetAttributeValue(G_BSTRKEY_NAME, *pChildElement, _T("程序校验码"));
		xml_SetAttributeValue(G_BSTRKEY_ID, *pChildElement, _T("LPHD1$DC$PhyNam$swRevCrc"));
		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pChildElement, _T("V_STR"));
	}

	if (bFindAdRev)
	{
		pChildElement = oXMLDoc.CreateElement(L"data",pElementDsDevStdMsg);
		oXMLDoc.AppendChild(*pChildElement);
		pElementDsDevStdMsg->AppendChild(*pChildElement);
		xml_SetAttributeValue(G_BSTRKEY_NAME, *pChildElement, _T("管理程序版本"));
		xml_SetAttributeValue(G_BSTRKEY_ID, *pChildElement, _T("LPHD1$DC$PhyNam$adSwRev"));
		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pChildElement, _T("V_STR"));
	}

	if (bFindAdDate)
	{
		pChildElement = oXMLDoc.CreateElement(L"data",pElementDsDevStdMsg);
		oXMLDoc.AppendChild(*pChildElement);
		pElementDsDevStdMsg->AppendChild(*pChildElement);
		xml_SetAttributeValue(G_BSTRKEY_NAME, *pChildElement, _T("管理程序生成时间"));
		xml_SetAttributeValue(G_BSTRKEY_ID, *pChildElement, _T("LPHD1$DC$PhyNam$adSwDate"));
		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pChildElement, _T("V_STR"));
	}

	if (bFindAdRevCrc)
	{
		pChildElement = oXMLDoc.CreateElement(L"data",pElementDsDevStdMsg);
		oXMLDoc.AppendChild(*pChildElement);
		pElementDsDevStdMsg->AppendChild(*pChildElement);
		xml_SetAttributeValue(G_BSTRKEY_NAME, *pChildElement, _T("管理程序校验码"));
		xml_SetAttributeValue(G_BSTRKEY_ID, *pChildElement, _T("LPHD1$DC$PhyNam$adSwRevCrc"));
		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pChildElement, _T("V_STR"));
	}

	if (bFindSASPinCrc)
	{
		pChildElement = oXMLDoc.CreateElement(L"data",pElementDsDevStdMsg);
		oXMLDoc.AppendChild(*pChildElement);
		pElementDsDevStdMsg->AppendChild(*pChildElement);
		xml_SetAttributeValue(G_BSTRKEY_NAME, *pChildElement, _T("全站过程层虚端子配置CRC"));
		xml_SetAttributeValue(G_BSTRKEY_ID, *pChildElement, _T("LPHD1$DC$SASPinCrc$setVal"));
		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pChildElement, _T("V_STR"));
	}

	if (bFindIEDPinCrc)
	{
		pChildElement = oXMLDoc.CreateElement(L"data",pElementDsDevStdMsg);
		oXMLDoc.AppendChild(*pChildElement);
		pElementDsDevStdMsg->AppendChild(*pChildElement);
		xml_SetAttributeValue(G_BSTRKEY_NAME, *pChildElement, _T("IED过程层虚端子配置CRC"));
		xml_SetAttributeValue(G_BSTRKEY_ID, *pChildElement, _T("LPHD1$DC$IEDPinCrc$setVal"));
		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pChildElement, _T("V_STR"));
	}
}

long model_XmlWrite(const CString &strIedName,SCL_LD* scl_ld, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent,SCL_INFO *pSclInfo,BOOL bAnalCtrlData,BOOL bDLT860Model)
{
	CXmlRWElementBase *pElement = oXMLDoc.CreateElement(G_BSTRKEY_LDEVICE,&oParent);
	CXmlRWElementBase *pElementDout = NULL;
	oXMLDoc.AppendChild(*pElement);

// 	MSXML2::IXMLDOMElementPtr oElement = NULL ,oElementDout = NULL;
// 	oElement = oXMLDoc->createElement(_bstr_t("ldevice"));

	if (oParent.IsValid())
	{
		oParent.AppendChild(*pElement);
	}
	else
	{
		oXMLDoc.AppendChild(*pElement);
	}

	CString strLDName = strIedName;

	if (mms_str_is_null(&scl_ld->ldName))
	{
#ifdef SCL_USE_MMS_STRING_
		strLDName += CString(mms_string(&scl_ld->inst));
#else
		strLDName += CString(scl_ld->inst);
#endif
	} 
	else
	{
#ifdef SCL_USE_MMS_STRING_
		strLDName = CString(mms_string(&scl_ld->ldName));
#else
		strLDName = CString(scl_ld->ldName);
#endif
	}


	xml_SetAttributeValue(G_BSTRKEY_ID, *pElement, strLDName);
	xml_SetAttributeValue(G_BSTRKEY_NAME, *pElement, CString(""));

	SCL_LN		*scl_ln = NULL ,*pSclLN_LPHD1 = NULL;
	SCL_RCB     *scl_rcb = NULL;
	SCL_DATASET *scl_dataset = NULL;
	long nSize = g_strarrLNodeTypes.GetSize();

	for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
		scl_ln != NULL;
		scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
	{
		ST_CHAR lnName	[MAX_TYPE_LEN + 1] = {0};

		scl_get_ln_name_model(scl_ln, lnName);

		if (0 == stricmp(lnName, "LLN0"))
		{
			for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)scl_ln->datasetHead);
				scl_dataset != NULL;
				scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)scl_ln->datasetHead, (DBL_LNK *)scl_dataset))
			{
				model_XmlWrite(_T("dataset"),strLDName,scl_dataset,scl_ln , scl_ld,oXMLDoc, *pElement,pSclInfo,bDLT860Model);
			}

			CString strElement;
			strElement = G_BSTRKEY_LGCTRL;
			model_XmlWriteJournalCtrls(strElement,strLDName, scl_ln, oXMLDoc, *pElement);

			if ((strLDName.Find(_T("PROT"))>0)||(strLDName.Find(_T("LD0"))>0)||(strLDName.Find(_T("CTRL"))>0))
			{
				pSclLN_LPHD1 = Scl_FindSclLN_ByLnName(scl_ld,_T("LPHD1"));

				if (pSclLN_LPHD1 != NULL)
				{
					model_XmlWrite_dsDevStdMsg(strLDName,pSclLN_LPHD1 ,oXMLDoc, pElement,pSclInfo);
				}
			}

			if (!bAnalCtrlData)
			{
				break;
			}
		}

		if (bAnalCtrlData)
		{
			for (int nCount = 0;nCount<nSize;nCount++)//对本LD下所有控制类的命令，放入dsDout数据集
			{
#ifdef SCL_USE_MMS_STRING_
				if (g_strarrLNodeTypes.GetAt(nCount) == mms_string(&scl_ln->lnType))
#else
				if (g_strarrLNodeTypes.GetAt(nCount) == scl_ln->lnType)
#endif
				{
					if (pElementDout == NULL)
					{
						pElementDout = oXMLDoc.CreateElement(G_BSTRKEY_DATASET,pElement);
						pElement->AppendChild(*pElementDout);
						CString strDataSetName = _T("LLN0$dsDout");
						xml_SetAttributeValue(G_BSTRKEY_ID, *pElementDout, strDataSetName);
						xml_SetAttributeValue(G_BSTRKEY_NAME, *pElementDout, "");
					}

					model_XmlWrite_ctrltype(g_strarrLNodeTypes.GetAt(nCount),scl_ln , oXMLDoc, *pElementDout,pSclInfo);
					break;
				}
			}
		}
	}

	return 0;
}

long model_XmlWrite(const CString &strElement,const CString &strLDName, SCL_DATASET *scl_dataset,SCL_LN	*scl_ln0,SCL_LD *scl_ld , CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent,SCL_INFO *pSclInfo,BOOL bDLT860)
{
	CXmlRWElementBase *pElement = oXMLDoc.CreateElement(GetElementKey(strElement), &oParent);
	oXMLDoc.AppendChild(*pElement);

// 	MSXML2::IXMLDOMElementPtr oElement = NULL;
// 	oElement = oXMLDoc->createElement(_bstr_t(strElement));

	if (oParent.IsValid())
	{
		oParent.AppendChild(*pElement);
	}
	else
	{
		oXMLDoc.AppendChild(*pElement);
	}

	CString strDataSetID = _T("LLN0$");
#ifdef SCL_USE_MMS_STRING_
	strDataSetID += mms_string(&scl_dataset->name);
#else
	strDataSetID += scl_dataset->name;
#endif

	xml_SetAttributeValue(G_BSTRKEY_ID, *pElement, strDataSetID);

#ifdef _USE_SCL_MODEL_CHINESE_DESC_
	CString strDatasetName;

	if ((scl_dataset->desc == NULL)||(strlen(scl_dataset->desc) == 0))
	{
		strDatasetName = Global_GetDatasetStdNameByID(strDataSetID);
	} 
	else
	{
		strDatasetName = scl_dataset->desc;
	}

	xml_SetAttributeValue(G_BSTRKEY_NAME, *pElement, strDatasetName);
#else
	xml_SetAttributeValue(G_BSTRKEY_NAME, *pElement, strDataSetID);
#endif
#ifdef SCL_USE_MMS_STRING_
	model_XmlWrite_brcb(strLDName,mms_string(&scl_dataset->name), scl_ln0, oXMLDoc, *pElement,pSclInfo,bDLT860);
#else
	model_XmlWrite_brcb(strLDName,scl_dataset->name, scl_ln0, oXMLDoc, *pElement,pSclInfo,bDLT860);
#endif

	SCL_FCDA* scl_fcda = NULL;

	for (scl_fcda = (SCL_FCDA *)list_find_last((DBL_LNK *)scl_dataset->fcdaHead);
		scl_fcda != NULL;
		scl_fcda = (SCL_FCDA *)list_find_prev((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
	{
		model_XmlWrite("data", scl_fcda,scl_ld, oXMLDoc, *pElement,pSclInfo);
	}

// 	if (strDataSetID.Find(_T("LLN0$dsParameter")) == 0)
// 	{
// 		CXmlRWElementBase *pChildElement = oXMLDoc.CreateElement(L"data",pElement);
// 		oXMLDoc.AppendChild(*pChildElement);
// 		pElement->AppendChild(*pChildElement);
// 		xml_SetAttributeValue(G_BSTRKEY_NAME, *pChildElement, _T("装置识别代码"));
// 		xml_SetAttributeValue(G_BSTRKEY_ID, *pChildElement, _T("LPHD1$DC$PhyNam$serNum"));
// 		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pChildElement, _T("V_STR"));
// 
// 		pChildElement = oXMLDoc.CreateElement(L"data",pElement);
// 		oXMLDoc.AppendChild(*pChildElement);
// 		pElement->AppendChild(*pChildElement);
// 		xml_SetAttributeValue(G_BSTRKEY_NAME, *pChildElement, _T("装置程序版本"));
// 		xml_SetAttributeValue(G_BSTRKEY_ID, *pChildElement, _T("LPHD1$DC$PhyNam$swRev"));
// 		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pChildElement, _T("V_STR"));
// 	}

	return 0;
}

long model_XmlWrite_ctrltype(const CString &strLNodeTypeID,SCL_LN	*scl_ln, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oElement,SCL_INFO *pSclInfo)
{
	SCL_LNTYPE *pScl_lntype = NULL;

	for (pScl_lntype = (SCL_LNTYPE *)list_find_last((DBL_LNK *)pSclInfo->lnTypeHead);
		pScl_lntype != NULL;
		pScl_lntype = (SCL_LNTYPE *)list_find_prev((DBL_LNK *)pSclInfo->lnTypeHead, (DBL_LNK *)pScl_lntype))
	{
#ifdef SCL_USE_MMS_STRING_
		if (strLNodeTypeID == mms_string(&pScl_lntype->id))
#else
		if (strLNodeTypeID == pScl_lntype->id)
#endif
		{
			break;
		}
	}

	if (pScl_lntype == NULL)
	{
		return 0;
	}

	SCL_DO *scl_do = NULL;
	long nSize = g_strarrDOTypes.GetSize();

	for (scl_do = (SCL_DO *)list_find_last((DBL_LNK *)pScl_lntype->doHead);
		scl_do != NULL;
		scl_do = (SCL_DO *)list_find_prev((DBL_LNK *)pScl_lntype->doHead, (DBL_LNK *)scl_do))
	{
		for (int nCount = 0;nCount<nSize;nCount++)
		{
#ifdef SCL_USE_MMS_STRING_
			if (g_strarrDOTypes.GetAt(nCount) == mms_string(&scl_do->type))
#else
			if (g_strarrDOTypes.GetAt(nCount) == scl_do->type)
#endif
			{
				model_XmlWrite_ctrltype_data(scl_do, scl_ln, oXMLDoc, oElement,pSclInfo);
			}
		}
	}

	return 0;
}

void My_PareVarUnite(int nValue, CString &strText)
{
	ST_CHAR*pValue = (ST_CHAR*)&nValue;

	CString strUnit = "";
	CString strMuti = "";

	if (pValue)
	{
		CSIUnit SIUnit;
		int nIndex = *pValue;
		strUnit = SIUnit.GetSIUnite(nIndex);

		CMultiplier Multiplier;
		nIndex = *(++pValue);
		strMuti = Multiplier.GetMultiplierUnite(nIndex);
	}

	//strText.Format("%s%s",strMuti,strUnit);
	strText = strMuti + strUnit;
}

long model_XmlWrite_ctrltype_data(SCL_DO *scl_do,SCL_LN	*scl_ln, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent,SCL_INFO *pSclInfo)
{
	CXmlRWElementBase *pElement = oXMLDoc.CreateElement(G_BSTRKEY_DATA,&oParent);
	oXMLDoc.AppendChild(*pElement);

// 	MSXML2::IXMLDOMElementPtr oElement = NULL;
// 	oElement = oXMLDoc->createElement(G_BSTRKEY_DATA);

	if (oParent.IsValid())
	{
		oParent.AppendChild(*pElement);
	}
	else
	{
		oXMLDoc.AppendChild(*pElement);
	}

	SCL_DAI* scl_dai = NULL;

	SCL_DOTYPE *doType = NULL;
	SCL_DA *scl_da = NULL;
	SCL_DA_BDA scl_da_bda;

	CString strDoDaPath,strDoName,strDAI,strPathdU,strPathDesc,strPathUnit,strPathMultiplier,strPathValue,strPathMin,strPathMax,strPathStep,
#ifdef SCL_USE_MMS_STRING_
		strPathValue2,strPathMin2,strPathMax2,strPathStep2,strDoFcPath = mms_string(&scl_ln->prefix);
#else
		strPathValue2,strPathMin2,strPathMax2,strPathStep2,strDoFcPath = scl_ln->prefix;
#endif
	CString strModelName,strModelUnit,strModelUnitPath,strModelUnitValue,strModelValue,strModelValuePath,strModelMax,strModelMin,strModelStep;

#ifdef SCL_USE_MMS_STRING_
	strDoName = mms_string(&scl_do->name);

	strDoFcPath += mms_string(&scl_ln->lnClass);
	strDoFcPath += mms_string(&scl_ln->inst);
#else
	strDoName = scl_do->name;

	strDoFcPath += scl_ln->lnClass;
	strDoFcPath += scl_ln->inst;
#endif

#ifdef SCL_MODEL_CTRL_USE_ST
	strDoFcPath += "$ST$";
#else
	strDoFcPath += "$CO$";
#endif
	strDoFcPath += strDoName;
	strModelValuePath = strDoFcPath;//将记录到DO一级的路径赋值给这一级的路径

	strDoDaPath = strDoName;
	strDoDaPath += "$";

	strPathdU = strDoName + "$dU";
	strPathDesc = strDoName + "$desc";
	strPathUnit = strDoName + "$units$SIUnit";
	strPathMultiplier = strDoName + "$units$multiplier";
	strPathValue = strDoName + "$setVal$f";
	strPathMin = strDoName + "$minVal$f";
	strPathMax = strDoName + "$maxVal$f";
	strPathStep = strDoName + "$stepSize$f";
	strPathValue2 = strDoName + "$setVal";
	strPathMin2 = strDoName + "$minVal";
	strPathMax2 = strDoName + "$maxVal";
	strPathStep2 = strDoName + "$stepSize";

	CString strMultiplierVal = "",strUnitVal = "";

	for (scl_dai = (SCL_DAI *)list_find_last((DBL_LNK *)scl_ln->daiHead);
		scl_dai != NULL;
		scl_dai = (SCL_DAI *)list_find_prev((DBL_LNK *)scl_ln->daiHead, (DBL_LNK *)scl_dai))
	{
#ifdef SCL_USE_MMS_STRING_
		strDAI = mms_string(&scl_dai->flattened);
#else
		strDAI = scl_dai->flattened;
#endif

		if (scl_dai->Val != NULL)
		{
			if (strDAI == strPathdU)
			{
				CString strTmp = scl_dai->Val;
				//UTF8ToMultiByte_Char(strTmp);
				Utf8_to_gbk(scl_dai->Val, strTmp);
				strModelName = strTmp;
			}
			else if (strDAI == strPathUnit)
			{
				CString strTmp = scl_dai->Val;
				//UTF8ToMultiByte_Char(strTmp);
				Utf8_to_gbk(scl_dai->Val, strTmp);
				strUnitVal = strTmp;
				strModelUnitPath.Format("%s$units$SIUnit",strDoFcPath.GetString());
			}
			else if (strDAI == strPathMultiplier)
			{
				strMultiplierVal = scl_dai->Val;
			}
			else if ((strDAI == strPathValue)||(strDAI == strPathValue2))
			{
				strModelValue = scl_dai->Val;
			}
			else if ((strDAI == strPathMin)||(strDAI == strPathMin2))
			{
				strModelMin = scl_dai->Val;
			}
			else if ((strDAI == strPathMax)||(strDAI == strPathMax2))
			{
				strModelMax = scl_dai->Val;
			}
			else if((strDAI == strPathStep)||(strDAI == strPathStep2))
			{
				strModelStep = scl_dai->Val;
			}
			else if ((strDAI == strPathDesc)&&(strModelName.IsEmpty()))
			{
				CString strTmp = scl_dai->Val;
				//UTF8ToMultiByte_Char(strTmp);// DOI里面的描述是经过转换的
				strModelName = strTmp;
			}
		}
	}

	if (strModelName.IsEmpty())
		xml_SetAttributeValue(G_BSTRKEY_NAME, *pElement, strModelValuePath);
	else
		xml_SetAttributeValue(G_BSTRKEY_NAME, *pElement, strModelName);

	xml_SetAttributeValue(G_BSTRKEY_ID, *pElement, strModelValuePath);

	if (strModelValuePath.Right(2) == "$f")
	{
		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pElement, "FLOAT");
	} 
	else
	{
		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pElement, "STRUCT");
	}

	int nUnit = 0;
	if (!strMultiplierVal.IsEmpty())
	{
		if (check_decimal_format(strMultiplierVal))
		{
			char *pZF = NULL;
			char *pVal = NULL;
			CString_to_char(strMultiplierVal, &pVal);
			nUnit = strtol(pVal,&pZF,10);
			nUnit = nUnit*256;
			delete pVal;
		}
		else
		{
			CMultiplier Multiplier;
			nUnit = Multiplier.GetMultiplierUniteIndex(strMultiplierVal);
			nUnit = nUnit*256;
		}
	}

	if (!strUnitVal.IsEmpty())
	{
		if (check_decimal_format(strUnitVal))
		{
			char *pZF = NULL;
			char *pVal = NULL;
			CString_to_char(strUnitVal, &pVal);
			nUnit += strtol(pVal,&pZF,10);
			delete pVal;
		}
		else
		{
			CSIUnit SIUnit;
			nUnit += SIUnit.GetSIUniteIndex(strUnitVal);
		}
	}

	My_PareVarUnite(nUnit,strModelUnit);
	strModelUnitValue.Format("%d",nUnit);
	xml_SetAttributeValue(G_BSTRKEY_UNIT, *pElement, strModelUnit);
	xml_SetAttributeValue(G_BSTRKEY_UNITPATH, *pElement, strModelUnitPath);
	xml_SetAttributeValue(G_BSTRKEY_UNITVALUE, *pElement, strModelUnitValue);
	xml_SetAttributeValue(G_BSTRKEY_VALUE, *pElement, strModelValue);
	xml_SetAttributeValue(G_BSTRKEY_DEFVALUE, *pElement, "");
	xml_SetAttributeValue(G_BSTRKEY_VALUEPATH, *pElement, strModelValuePath);
	xml_SetAttributeValue(G_BSTRKEY_MAX, *pElement, strModelMax);
	xml_SetAttributeValue(G_BSTRKEY_MIN, *pElement, strModelMin);
	xml_SetAttributeValue(G_BSTRKEY_STEPSIZE, *pElement, strModelStep);

	for (doType = (SCL_DOTYPE *)list_find_last((DBL_LNK *)pSclInfo->doTypeHead);
		doType != NULL;
		doType = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)pSclInfo->doTypeHead, (DBL_LNK *)doType))
	{
#ifdef SCL_USE_MMS_STRING_
		if (0 == strcmp(mms_string(&doType->id), mms_string(&scl_do->type)))
#else
		if (0 == strcmp(doType->id, scl_do->type))
#endif
		{
			break;
		}
	}

	for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)doType->daHead);//获取DOType中的DA及其对应的type
		scl_da != NULL;
		scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)doType->daHead, (DBL_LNK *)scl_da))
	{
#ifdef SCL_MODEL_CTRL_USE_ST
		if (0 == strcmp(scl_da->fc, "ST"))
#else
		if (0 == strcmp(scl_da->fc, "CO"))
#endif
		{
#ifdef SCL_USE_MMS_STRING_
			scl_da_bda.da_name = mms_string(&scl_da->name);
			scl_da_bda.type = mms_string(&scl_da->type);
			scl_da_bda.btype = mms_string(&scl_da->bType);
#else
			scl_da_bda.da_name = scl_da->name;
			scl_da_bda.type = scl_da->type;
			scl_da_bda.btype = scl_da->bType;
#endif
			scl_da_bda.nCount = scl_da->count;
			model_XmlWrite_SubDA(strModelName,strDoFcPath, &scl_da_bda , oXMLDoc, *pElement,pSclInfo->daTypeHead);
		}
		else if (0 == strcmp(scl_da->fc ,""))
		{
			SCL_DOTYPE *doTypeNew = NULL;
			SCL_DA *scl_daNew = NULL;

			for (doTypeNew = (SCL_DOTYPE *)list_find_last((DBL_LNK *)pSclInfo->doTypeHead);
				doTypeNew != NULL;
				doTypeNew = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)pSclInfo->doTypeHead, (DBL_LNK *)doTypeNew))
			{
#ifdef SCL_USE_MMS_STRING_
				if (0 == strcmp(mms_string(&doTypeNew->id), mms_string(&scl_da->type)))
#else
				if (0 == strcmp(doTypeNew->id, scl_da->type))
#endif
				{
					for (scl_daNew = (SCL_DA *)list_find_last((DBL_LNK *)doTypeNew->daHead);
						scl_daNew != NULL;
						scl_daNew = (SCL_DA *)list_find_prev((DBL_LNK *)doTypeNew->daHead, (DBL_LNK *)scl_daNew))
					{
#ifdef SCL_MODEL_CTRL_USE_ST
						if (0 == strcmp(scl_daNew->fc, "ST"))
#else
						if (0 == strcmp(scl_daNew->fc, "CO"))
#endif
						{
							CString strTmp;
#ifdef SCL_USE_MMS_STRING_
							strTmp.Format("%s$%s",strDoFcPath.GetString(),mms_string(&scl_da->name));
							scl_da_bda.da_name = mms_string(&scl_daNew->name);
							scl_da_bda.type = mms_string(&scl_daNew->type);
							scl_da_bda.btype = mms_string(&scl_daNew->bType);
							scl_da_bda.nCount = scl_daNew->count;
#else
							strTmp.Format("%s$%s",strDoFcPath.GetString(),scl_da->name);
							scl_da_bda.da_name = scl_daNew->name;
							scl_da_bda.type = scl_daNew->type;
							scl_da_bda.btype = scl_daNew->bType;
							scl_da_bda.nCount = scl_daNew->count;
#endif
							model_XmlWrite_SubDA(strModelName,strTmp, &scl_da_bda , oXMLDoc, *pElement,pSclInfo->daTypeHead);
						}
					}

					break;
				}
			}
		}
	}

	return 0;
}

void model_XmlWrite_brcb(const CString &strLDName,const CString &strDataSetName, SCL_LN *scl_ln0, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent,SCL_INFO *pSclInfo,BOOL bDLT860)
{
	CXmlRWElementBase *pElement = oXMLDoc.CreateElement(G_BSTRKEY_BRCB,&oParent);
	oXMLDoc.AppendChild(*pElement);
	char* pszDataSetName;
	CString_to_char(strDataSetName, &pszDataSetName);

// 	MSXML2::IXMLDOMElementPtr oElement = NULL;
// 	oElement = oXMLDoc->createElement(G_BSTRKEY_BRCB);

	if (oParent.IsValid())
	{
		oParent.AppendChild(*pElement);
	}
	else
	{
		oXMLDoc.AppendChild(*pElement);
	}

	SCL_RCB *scl_ReportCtrl = NULL;
	CString strBrcbPath,strRptID;
	long nIndex = 0;

	for (scl_ReportCtrl = (SCL_RCB *)list_find_last((DBL_LNK *)scl_ln0->rcbHead);
		scl_ReportCtrl != NULL;
		scl_ReportCtrl = (SCL_RCB *)list_find_prev((DBL_LNK *)scl_ln0->rcbHead, (DBL_LNK *)scl_ReportCtrl))
	{
		CXmlRWElementBase *pSubElement = NULL;
		//MSXML2::IXMLDOMElementPtr oSubElement = NULL;
#ifdef SCL_USE_MMS_STRING_
		if (0 == strcmp(mms_string(&scl_ReportCtrl->datSet), pszDataSetName))
#else
		if (0 == strcmp(scl_ReportCtrl->datSet, pszDataSetName))
#endif
		{
			nIndex = scl_ReportCtrl->maxClient;

			if (bDLT860)
			{
				strBrcbPath = _T("LLN0.");
			} 
			else
			{
				strBrcbPath = _T("LLN0$");

				if (scl_ReportCtrl->buffered)
					strBrcbPath += _T("BR$");
				else
					strBrcbPath += _T("RP$");
			}

#ifdef SCL_USE_MMS_STRING_
			strBrcbPath += mms_string(&scl_ReportCtrl->name);
			strRptID = mms_string(&scl_ReportCtrl->rptID);
#else
			strBrcbPath += scl_ReportCtrl->name;
			strRptID = scl_ReportCtrl->rptID;
#endif

			if (strRptID.IsEmpty() || (strRptID == "NULL"))
			{
				strRptID = strLDName;
				strRptID += "/";
				strRptID += strBrcbPath;
			} 
			else
			{
				strRptID.Replace(_T("$BR$"),_T("."));
				strRptID.Replace(_T("$RP$"),_T("."));
				strRptID.Replace(_T("$"),_T("."));
			}

			if (nIndex>1)
			{
				CString strBrcbPathNew;

				for (int nLenth = 0;nLenth<nIndex;nLenth++)
				{
					pSubElement = oXMLDoc.CreateElement(G_BSTRKEY_DATA,pElement);
					pElement->AppendChild(*pSubElement);
					strBrcbPathNew.Format("%s%.2d",strBrcbPath.GetString(),(nLenth+1));
					xml_SetAttributeValue(G_BSTRKEY_NAME, *pSubElement, strBrcbPathNew);
					xml_SetAttributeValue(G_BSTRKEY_ID, *pSubElement, strRptID);
				}
			} 
			else
			{
				pSubElement = oXMLDoc.CreateElement(G_BSTRKEY_DATA,pElement);
				pElement->AppendChild(*pSubElement);
				xml_SetAttributeValue(G_BSTRKEY_NAME, *pSubElement, strBrcbPath);
				xml_SetAttributeValue(G_BSTRKEY_ID, *pSubElement, strRptID);
			}
		}
	}

	delete pszDataSetName;
}

void model_XmlWriteJournalCtrls(const CString &strElement,const CString &strLDName , SCL_LN *scl_ln0, CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent/*,SCL_INFO *pSclInfo*/)
{
	CXmlRWElementBase *pElement = oXMLDoc.CreateElement(GetElementKey(strElement),&oParent);
	oXMLDoc.AppendChild(*pElement);

// 	MSXML2::IXMLDOMElementPtr oElement = NULL;
// 	oElement = oXMLDoc->createElement(_bstr_t(strElement));
	SCL_DATASET *scl_dataset = NULL;
	SCL_LCB *scl_logcontrl = NULL;

	if (oParent.IsValid())
	{
		oParent.AppendChild(*pElement);
	}
	else
	{
		oXMLDoc.AppendChild(*pElement);
	}

	for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)scl_ln0->datasetHead);
		scl_dataset != NULL;
		scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)scl_ln0->datasetHead, (DBL_LNK *)scl_dataset))
	{
		CXmlRWElementBase *pSubElement = NULL;
		//MSXML2::IXMLDOMElementPtr oSubElement = NULL;
		pSubElement = oXMLDoc.CreateElement(G_BSTRKEY_DATA,pElement);
		pElement->AppendChild(*pSubElement);

		CString strLogName,strLogPath,strDatasetPath;
		strDatasetPath = "LLN0$";
#ifdef SCL_USE_MMS_STRING_
		strDatasetPath += mms_string(&scl_dataset->name);
#else
		strDatasetPath += scl_dataset->name;
#endif

		for (scl_logcontrl = (SCL_LCB *)list_find_last((DBL_LNK *)scl_ln0->lcbHead);
			scl_logcontrl != NULL;
			scl_logcontrl = (SCL_LCB *)list_find_prev((DBL_LNK *)scl_ln0->lcbHead, (DBL_LNK *)scl_logcontrl))
		{
#ifdef SCL_USE_MMS_STRING_
			if (0 == strcmp(mms_string(&scl_logcontrl->datSet), mms_string(&scl_dataset->name)))
			{
				strLogPath = "LLN0$LG$";
				strLogPath += mms_string(&scl_logcontrl->name);
				strLogName = strLDName;
				strLogName += "/";
				strLogName += mms_string(&scl_logcontrl->logName);
			}
#else
			if (0 == strcmp(scl_logcontrl->datSet, scl_dataset->name))
			{
				strLogPath = "LLN0$LG$";
				strLogPath += scl_logcontrl->name;
				strLogName = strLDName;
				strLogName += "/";
				strLogName += scl_logcontrl->logName;
			}
#endif
		}

		xml_SetAttributeValue(G_BSTRKEY_NAME, *pSubElement, strLogName);
		xml_SetAttributeValue(G_BSTRKEY_ID, *pSubElement, strLogPath );
		xml_SetAttributeValue(G_BSTRKEY_DATASET, *pSubElement, strDatasetPath);
	}
}

long model_XmlWrite(const CString &strElement,SCL_FCDA* scl_fcda,SCL_LD *scl_ld,CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent,SCL_INFO *pSclInfo)
{
	CXmlRWElementBase *pElement = oXMLDoc.CreateElement(GetElementKey(strElement),&oParent);
	oXMLDoc.AppendChild(*pElement);

//	MSXML2::IXMLDOMElementPtr oElement = NULL;
	SCL_LD *scl_ld_new = scl_ld;
//	oElement = oXMLDoc->createElement(_bstr_t(strElement));

	if (oParent.IsValid())
	{
		oParent.AppendChild(*pElement);
	}
	else
	{
		oXMLDoc.AppendChild(*pElement);
	}

	SCL_LN* scl_ln = NULL;
	SCL_DAI* scl_dai = NULL;

	SCL_LNTYPE *pScl_lntype = NULL;
	SCL_DO *scl_do = NULL;
	SCL_DOTYPE *doType = NULL;
	SCL_DA *scl_da = NULL;
	SCL_DA_BDA scl_da_bda;

	CString strDoDaPath,strDoName,strDoCompare,strDaName,strDAI,strPathdU,strPathDesc,strPathUnit,strPathMultiplier,strPathValue,strPathMin,strPathMax,strPathStep,
#ifdef SCL_USE_MMS_STRING_
		strPathValue2,strPathMin2,strPathMax2,strPathStep2,strDoFcPath = mms_string(&scl_fcda->prefix);
	CString strModelName,strModelUnit,strModelUnitPath,strModelUnitValue,strModelValue,strModelValuePath,strModelMax,strModelMin,strModelStep;
	strDoName = mms_string(&scl_fcda->doName);
	strDoCompare = strDoName;
	strDaName = mms_string(&scl_fcda->daName);
#else
		strPathValue2,strPathMin2,strPathMax2,strPathStep2,strDoFcPath = scl_fcda->prefix;
	CString strModelName,strModelUnit,strModelUnitPath,strModelUnitValue,strModelValue,strModelValuePath,strModelMax,strModelMin,strModelStep;
	strDoName = scl_fcda->doName;
	strDoCompare = strDoName;
	strDaName = scl_fcda->daName;
#endif

	int nTmp = strDoName.Find('.');
	if (nTmp != -1)
	{
		CString strOld, strNew;
		strOld = _T(".");
		strNew = _T("$");
		strDaName = strDoName.Mid(nTmp+1);
		strDoCompare = strDoName.Left(nTmp);
		strDoName.Replace(strOld,strNew);
	}

#ifdef SCL_USE_MMS_STRING_
	strDoFcPath += mms_string(&scl_fcda->lnClass);
	strDoFcPath += mms_string(&scl_fcda->lnInst);
	strDoFcPath += "$";
	strDoFcPath += mms_string(&scl_fcda->fc);
#else
	strDoFcPath += scl_fcda->lnClass;
	strDoFcPath += scl_fcda->lnInst;
	strDoFcPath += "$";
	strDoFcPath += scl_fcda->fc;
#endif

	strDoFcPath += "$";
	strDoFcPath += strDoName;
	strModelValuePath = strDoFcPath;//将记录到DO一级的路径赋值给这一级的路径

	char* pszDoCompare = NULL;
	CString_to_char(strDoCompare, &pszDoCompare);
	char* pszDaName = NULL;
	CString_to_char(strDaName, &pszDaName);

#ifdef SCL_USE_MMS_STRING_
	if (0 != strcmp(mms_string(&scl_fcda->ldInst),mms_string(&scl_ld_new->inst)))//首先在FCDA中查找确认逻辑设备的名称是否一致，如果不一致在本Server下查找，如果还是没查找到，就认为是本LD下的
#else
	if (0 != strcmp(scl_fcda->ldInst,scl_ld_new->inst))//首先在FCDA中查找确认逻辑设备的名称是否一致，如果不一致在本Server下查找，如果还是没查找到，就认为是本LD下的
#endif
	{
		for (scl_ld_new = (SCL_LD *)list_find_last((DBL_LNK *)scl_ld);
			scl_ld_new != NULL;
			scl_ld_new = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ld, (DBL_LNK *)scl_ld_new))
		{
#ifdef SCL_USE_MMS_STRING_
			if (0 == strcmp(mms_string(&scl_fcda->ldInst),mms_string(&scl_ld_new->inst)))
#else
			if (0 == strcmp(scl_fcda->ldInst,scl_ld_new->inst))
#endif
				break;
		}

		if (scl_ld_new == NULL)
			scl_ld_new = scl_ld;
//			return 0;
	}

	for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld_new->lnHead);
		scl_ln != NULL;
		scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld_new->lnHead, (DBL_LNK *)scl_ln))
	{
#ifdef SCL_USE_MMS_STRING_
		if ((0 == strcmp(mms_string(&scl_ln->lnClass), mms_string(&scl_fcda->lnClass))) && 
			(0 == strcmp(mms_string(&scl_ln->prefix), mms_string(&scl_fcda->prefix))) && (0 == strcmp(mms_string(&scl_ln->inst), mms_string(&scl_fcda->lnInst))))
#else
		if ((0 == strcmp(scl_ln->lnClass, scl_fcda->lnClass)) && (0 == strcmp(scl_ln->prefix, scl_fcda->prefix)) && (0 == strcmp(scl_ln->inst, scl_fcda->lnInst)))
#endif
		{
			for (pScl_lntype = (SCL_LNTYPE *)list_find_last((DBL_LNK *)pSclInfo->lnTypeHead);
				pScl_lntype != NULL;
				pScl_lntype = (SCL_LNTYPE *)list_find_prev((DBL_LNK *)pSclInfo->lnTypeHead, (DBL_LNK *)pScl_lntype))
			{
#ifdef SCL_USE_MMS_STRING_
				if (0 == strcmp(mms_string(&scl_ln->lnType), mms_string(&pScl_lntype->id)))
#else
				if (0 == strcmp(scl_ln->lnType, pScl_lntype->id))
#endif
				{
					for (scl_do = (SCL_DO *)list_find_last((DBL_LNK *)pScl_lntype->doHead);
						scl_do != NULL;
						scl_do = (SCL_DO *)list_find_prev((DBL_LNK *)pScl_lntype->doHead, (DBL_LNK *)scl_do))
					{
#ifdef SCL_USE_MMS_STRING_
						if (0 == strcmp(pszDoCompare, mms_string(&scl_do->name)))
#else
						if (0 == strcmp(pszDoCompare, scl_do->name))
#endif
						{
							for (doType = (SCL_DOTYPE *)list_find_last((DBL_LNK *)pSclInfo->doTypeHead);
								doType != NULL;
								doType = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)pSclInfo->doTypeHead, (DBL_LNK *)doType))
							{
#ifdef SCL_USE_MMS_STRING_
								if (0 == strcmp(mms_string(&doType->id), mms_string(&scl_do->type)))
#else
								if (0 == strcmp(doType->id, scl_do->type))
#endif
								{
									break;
								}
							}

							break;
						}	
					}
					break;
				}
			}

			if (doType == NULL)
			{
				delete pszDoCompare;
				delete pszDaName;
				return 0;
			}

			strDoDaPath = strDoName;
			strDoDaPath += "$";

#ifdef SCL_USE_MMS_STRING_
			if (0 != strcmp(mms_string(&scl_fcda->daName),""))//FCDA中定义到DA
			{
				strDoDaPath += mms_string(&scl_fcda->daName);
				strDoDaPath += "$";
				CString strOld, strNew;
				strOld = _T(".");
				strNew = _T("$");
				strDoDaPath.Replace(strOld,strNew);//防止部分厂家DA中定义多层，之间采用'.'分隔
				strModelValuePath += "$";
				strModelValuePath += mms_string(&scl_fcda->daName);
				strModelValuePath.Replace(strOld,strNew);//防止部分厂家DA中定义多层，之间采用'.'分隔
			}
#else
			if (0 != strcmp(scl_fcda->daName,""))//FCDA中定义到DA
			{
				strDoDaPath += scl_fcda->daName;
				strDoDaPath += "$";
				strDoDaPath.Replace('.','$');//防止部分厂家DA中定义多层，之间采用'.'分隔
				strModelValuePath += "$";
				strModelValuePath += scl_fcda->daName;
				strModelValuePath.Replace('.','$');//防止部分厂家DA中定义多层，之间采用'.'分隔
			}
#endif

			strPathdU = strDoName + "$dU";
			strPathDesc = strDoName + "$desc";
			strPathUnit = strDoName + "$units$SIUnit";
			strPathMultiplier = strDoName + "$units$multiplier";
			strPathValue = strDoName + "$setVal$f";
			strPathMin = strDoName + "$minVal$f";
			strPathMax = strDoName + "$maxVal$f";
			strPathStep = strDoName + "$stepSize$f";
			strPathValue2 = strDoName + "$setVal";
			strPathMin2 = strDoName + "$minVal";
			strPathMax2 = strDoName + "$maxVal";
			strPathStep2 = strDoName + "$stepSize";

			CString strMultiplierVal = "",strUnitVal = "";

			for (scl_dai = (SCL_DAI *)list_find_last((DBL_LNK *)scl_ln->daiHead);
				scl_dai != NULL;
				scl_dai = (SCL_DAI *)list_find_prev((DBL_LNK *)scl_ln->daiHead, (DBL_LNK *)scl_dai))
			{
#ifdef SCL_USE_MMS_STRING_
				strDAI = mms_string(&scl_dai->flattened);
#else
				strDAI = scl_dai->flattened;
#endif

				if (scl_dai->Val != NULL)
				{
					if (strDAI == strPathdU)
					{
						CString strTmp = scl_dai->Val;
						//UTF8ToMultiByte_Char(strTmp);
						Utf8_to_gbk(scl_dai->Val, strTmp);
						strModelName = strTmp;
					}
					else if (strDAI == strPathUnit)
					{
						CString strTmp = scl_dai->Val;
						//UTF8ToMultiByte_Char(strTmp);
						Utf8_to_gbk(scl_dai->Val, strTmp);
						strUnitVal/*strModelUnit*/ = strTmp;
						strModelUnitPath.Format("%s$units$SIUnit",strDoFcPath.GetString()/*,strDoName*/);
					}
					else if (strDAI == strPathMultiplier)
					{
						strMultiplierVal/*strModelUnitValue*/ = scl_dai->Val;
					}
					else if ((strDAI == strPathValue)||(strDAI == strPathValue2))
					{
						strModelValue = scl_dai->Val;
					}
					else if ((strDAI == strPathMin)||(strDAI == strPathMin2))
					{
						strModelMin = scl_dai->Val;
					}
					else if ((strDAI == strPathMax)||(strDAI == strPathMax2))
					{
						strModelMax = scl_dai->Val;
					}
					else if ((strDAI == strPathStep)||(strDAI == strPathStep2))
					{
						strModelStep = scl_dai->Val;
					}
					else if ((strDAI == strPathDesc)&&(strModelName.IsEmpty()))
					{
						CString strTmp = scl_dai->Val;
//						UTF8ToMultiByte_Char(strTmp);// DOI里面的描述是经过转换的
						strModelName = strTmp;
					}
				}
			}

			if (strModelName.IsEmpty())
				xml_SetAttributeValue(G_BSTRKEY_NAME, *pElement, strModelValuePath);
			else
				xml_SetAttributeValue(G_BSTRKEY_NAME, *pElement, strModelName);
			
			xml_SetAttributeValue(G_BSTRKEY_ID, *pElement, strModelValuePath);

			CString strDataType = "";
			BOOL bDataPathEnd = check_ModelValuePath_end(strModelValuePath,doType,pSclInfo,strDataType);

			if (strDataType.IsEmpty())
			{
				xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pElement, "STRUCT");				
			}
			else
			{
				model_format(strDataType);
				xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pElement, strDataType);
			}

			int nUnit = 0;
			if (!strMultiplierVal.IsEmpty())
			{
				if (check_decimal_format(strMultiplierVal))
				{
					char *pZF = NULL;
					char *pVal = NULL;
					CString_to_char(strMultiplierVal, &pVal);
					nUnit = strtol(pVal,&pZF,10);
					nUnit = nUnit*256;
					delete pVal;
				}
				else
				{
					CMultiplier Multiplier;
					nUnit = Multiplier.GetMultiplierUniteIndex(strMultiplierVal);
					nUnit = nUnit*256;
				}
			}

			if (!strUnitVal.IsEmpty())
			{
				if (check_decimal_format(strUnitVal))
				{
					char *pZF = NULL;
					char *pVal = NULL;
					CString_to_char(strUnitVal, &pVal);
					nUnit += strtol(pVal,&pZF,10);
					delete pVal;
				}
				else
				{
					CSIUnit SIUnit;
					nUnit += SIUnit.GetSIUniteIndex(strUnitVal);
				}
			}

			My_PareVarUnite(nUnit,strModelUnit);
			strModelUnitValue.Format("%d",nUnit);

			xml_SetAttributeValue(G_BSTRKEY_UNIT, *pElement, strModelUnit);
			xml_SetAttributeValue(G_BSTRKEY_UNITPATH, *pElement, strModelUnitPath);
			xml_SetAttributeValue(G_BSTRKEY_UNITVALUE, *pElement, strModelUnitValue);
			xml_SetAttributeValue(G_BSTRKEY_VALUE, *pElement, strModelValue);
			xml_SetAttributeValue(G_BSTRKEY_DEFVALUE, *pElement, "");
			xml_SetAttributeValue(G_BSTRKEY_VALUEPATH, *pElement, strModelValuePath);
			xml_SetAttributeValue(G_BSTRKEY_MAX, *pElement, strModelMax);
			xml_SetAttributeValue(G_BSTRKEY_MIN, *pElement, strModelMin);
			xml_SetAttributeValue(G_BSTRKEY_STEPSIZE, *pElement, strModelStep);

			if (bDataPathEnd)
//			if ((strModelValuePath.Right(2) == "$f")||(strModelValuePath.Right(2) == "$q")||(strModelValuePath.Right(2) == "$i"))//排除两种在数据集中已经详细定义路径的情况
			{
				continue;
			}
			
			for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)doType->daHead);//获取DOType中的DA及其对应的type
				scl_da != NULL;
				scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)doType->daHead, (DBL_LNK *)scl_da))
			{
#ifdef SCL_USE_MMS_STRING_
				if (strcmp_fc(mms_string(&scl_fcda->fc),scl_da->fc))//(0 == strcmp(scl_da->fc, scl_fcda->fc))
				{
					scl_da_bda.da_name = mms_string(&scl_da->name);
					scl_da_bda.type = mms_string(&scl_da->type);
					scl_da_bda.btype = mms_string(&scl_da->bType);
					scl_da_bda.nCount = scl_da->count;
					model_XmlWrite_SubDA(strModelName,strDoFcPath, &scl_da_bda , oXMLDoc, *pElement,pSclInfo->daTypeHead);
				}
				else if (0 == strcmp(scl_da->fc ,""))
#else
				if (strcmp_fc(scl_fcda->fc,scl_da->fc))//(0 == strcmp(scl_da->fc, scl_fcda->fc))
				{
					scl_da_bda.da_name = scl_da->name;
					scl_da_bda.type = scl_da->type;
					scl_da_bda.btype = scl_da->bType;
					scl_da_bda.nCount = scl_da->count;
					model_XmlWrite_SubDA(strModelName,strDoFcPath, &scl_da_bda , oXMLDoc, *pElement,pSclInfo->daTypeHead);
				}
				else if (0 == strcmp(scl_da->fc ,""))
#endif
				{
					SCL_DOTYPE *doTypeNew = NULL;
					SCL_DA *scl_daNew = NULL;

					for (doTypeNew = (SCL_DOTYPE *)list_find_last((DBL_LNK *)pSclInfo->doTypeHead);
						doTypeNew != NULL;
						doTypeNew = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)pSclInfo->doTypeHead, (DBL_LNK *)doTypeNew))
					{
#ifdef SCL_USE_MMS_STRING_
						if (0 == strcmp(mms_string(&doTypeNew->id), mms_string(&scl_da->type)))
#else
						if (0 == strcmp(doTypeNew->id, scl_da->type))
#endif
						{
							for (scl_daNew = (SCL_DA *)list_find_last((DBL_LNK *)doTypeNew->daHead);
								scl_daNew != NULL;
								scl_daNew = (SCL_DA *)list_find_prev((DBL_LNK *)doTypeNew->daHead, (DBL_LNK *)scl_daNew))
							{
#ifdef SCL_USE_MMS_STRING_
								if ((/*0 == strcmp(scl_daNew->fc, scl_fcda->fc)*/(strcmp_fc(mms_string(&scl_fcda->fc),scl_daNew->fc)))&&(strDaName.IsEmpty()))
								{
									CString strTmp;
									strTmp.Format("%s$%s",strDoFcPath.GetString(),mms_string(&scl_da->name));
									scl_da_bda.da_name = mms_string(&scl_daNew->name);
									scl_da_bda.type = mms_string(&scl_daNew->type);
									scl_da_bda.btype = mms_string(&scl_daNew->bType);
									scl_da_bda.nCount = scl_daNew->count;
									model_XmlWrite_SubDA(strModelName,strTmp, &scl_da_bda , oXMLDoc, *pElement,pSclInfo->daTypeHead);
								}
								else if ((strcmp_fc(mms_string(&scl_fcda->fc),scl_daNew->fc)/*0 == strcmp(scl_daNew->fc, scl_fcda->fc)*/)&&
									(0 == strcmp(pszDaName, mms_string(&scl_da->name))))
								{
									scl_da_bda.da_name = mms_string(&scl_daNew->name);
									scl_da_bda.type = mms_string(&scl_daNew->type);
									scl_da_bda.btype = mms_string(&scl_daNew->bType);
									scl_da_bda.nCount = scl_daNew->count;
									model_XmlWrite_SubDA(strModelName,strDoFcPath, &scl_da_bda , oXMLDoc, *pElement,pSclInfo->daTypeHead);
								}
#else
								if ((/*0 == strcmp(scl_daNew->fc, scl_fcda->fc)*/(strcmp_fc(scl_fcda->fc,scl_daNew->fc)))&&(strDaName.IsEmpty()))
								{
									CString strTmp;
									strTmp.Format("%s$%s",strDoFcPath.GetString(),scl_da->name);
									scl_da_bda.da_name = scl_daNew->name;
									scl_da_bda.type = scl_daNew->type;
									scl_da_bda.btype = scl_daNew->bType;
									scl_da_bda.nCount = scl_daNew->count;
									model_XmlWrite_SubDA(strModelName,strTmp, &scl_da_bda , oXMLDoc, *pElement,pSclInfo->daTypeHead);
								}
								else if ((strcmp_fc(scl_fcda->fc,scl_daNew->fc)/*0 == strcmp(scl_daNew->fc, scl_fcda->fc)*/)&&(0 == strcmp(pszDaName, scl_da->name)))
								{
									scl_da_bda.da_name = scl_daNew->name;
									scl_da_bda.type = scl_daNew->type;
									scl_da_bda.btype = scl_daNew->bType;
									scl_da_bda.nCount = scl_daNew->count;
									model_XmlWrite_SubDA(strModelName,strDoFcPath, &scl_da_bda , oXMLDoc, *pElement,pSclInfo->daTypeHead);
								}
#endif
							}

							break;
						}
					}
				}
			}
		}
	}

	delete pszDoCompare;
	delete pszDaName;
	return 0;
}

BOOL check_ModelValuePath_end(const CString &strModelValuePath,SCL_DOTYPE *doType,SCL_INFO *pSclInfo,CString &strDataType)
{
	CString strPath,strName;
	long nIndex = strModelValuePath.Find('$');
	strPath = strModelValuePath.Mid(nIndex+1);
	nIndex = strPath.Find('$');
	strPath = strPath.Mid(nIndex+1);
	nIndex = strPath.Find('$');

	if (nIndex == -1)
		return 0;

	strPath = strPath.Mid(nIndex+1);

	if (strPath.IsEmpty())
	{
		return 0;
	}

	nIndex = strPath.Find('$');

	if (nIndex == -1)
	{
		strName = strPath;
		strPath = "";
	} 
	else
	{
		strName = strPath.Left(nIndex);
		strPath = strPath.Mid(nIndex+1);
	}

	return check_ModelValuePath_DO_SD_end(strName,strPath,doType,pSclInfo,strDataType);
}

BOOL check_ModelValuePath_DO_SD_end(CString &strName,CString &strPath,SCL_DOTYPE *doType,SCL_INFO *pSclInfo,CString &strDataType)
{
	SCL_DA *scl_da = NULL;
	char* pszName = NULL;
	CString_to_char(strName, &pszName);

	for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)doType->daHead);//获取DOType中的DA及其对应的type
		scl_da != NULL;
		scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)doType->daHead, (DBL_LNK *)scl_da))
	{
#ifdef SCL_USE_MMS_STRING_
		if (0 == strcmp(mms_string(&scl_da->name) ,pszName))
#else
		if (0 == strcmp(scl_da->name ,pszName))
#endif
		{
			long nIndex = strPath.Find('$');

			if (nIndex == -1)
			{
				strName = strPath;
				strPath = "";
			} 
			else
			{
				strName = strPath.Left(nIndex);
				strPath = strPath.Mid(nIndex+1);
			}

#ifdef SCL_USE_MMS_STRING_
			if (0 == stricmp(mms_string(&scl_da->bType), ""))
#else
			if (0 == stricmp(scl_da->bType, ""))
#endif

			{
				if ((!strName.IsEmpty())&&(!strPath.IsEmpty()))
				{
					SCL_DOTYPE *doTypeNew = NULL;
					SCL_DA *scl_daNew = NULL;

					for (doTypeNew = (SCL_DOTYPE *)list_find_last((DBL_LNK *)pSclInfo->doTypeHead);
						doTypeNew != NULL;
						doTypeNew = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)pSclInfo->doTypeHead, (DBL_LNK *)doTypeNew))
					{
#ifdef SCL_USE_MMS_STRING_
						if (0 == strcmp(mms_string(&doTypeNew->id), mms_string(&scl_da->type)))
#else
						if (0 == strcmp(doTypeNew->id, scl_da->type))
#endif
						{
							delete pszName;
							return check_ModelValuePath_DO_SD_end(strName,strPath,doTypeNew,pSclInfo,strDataType);
						}
					}
				}
				else
				{
					delete pszName;
					return 0;
				}
			}
#ifdef SCL_USE_MMS_STRING_
			else if (0 == stricmp(mms_string(&scl_da->bType), "STRUCT" ))
#else
			else if (0 == stricmp(scl_da->bType, "STRUCT" ))
#endif
			{
				if (!strName.IsEmpty())
				{
					CString strType;
#ifdef SCL_USE_MMS_STRING_
					strType = mms_string(&scl_da->type);
#else
					strType = scl_da->type;
#endif
					return check_ModelValuePath_DA_end(strName,strPath,strType,pSclInfo,strDataType);
				}
				else
				{
					delete pszName;
					return 0;
				}
			}
			else
			{
#ifdef SCL_USE_MMS_STRING_
				strDataType = mms_string(&scl_da->bType);
#else
				strDataType = scl_da->bType;
#endif
				delete pszName;
				return 1;
			}

			break;
		}
	}

	delete pszName;
	return 0;
}

BOOL check_ModelValuePath_DA_end(CString &strName,CString &strPath,CString &strType,SCL_INFO *pSclInfo,CString &strDataType)
{
	SCL_DATYPE *pDaType = NULL;
	SCL_BDA *scl_bda = NULL;
	char* pszType = NULL;
	char* pszName = NULL;
	CString_to_char(strName, &pszName);
	CString_to_char(strType, &pszType);

	for (pDaType = (SCL_DATYPE *)list_find_last((DBL_LNK *)pSclInfo->daTypeHead);
		pDaType != NULL;
		pDaType = (SCL_DATYPE *)list_find_prev((DBL_LNK *)pSclInfo->daTypeHead, (DBL_LNK *)pDaType))
	{
#ifdef SCL_USE_MMS_STRING_
		if (0 == strcmp(mms_string(&pDaType->id), pszType))
#else
		if (0 == strcmp(pDaType->id, pszType))
#endif
		{
			for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)pDaType->bdaHead);
				scl_bda != NULL;
				scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)pDaType->bdaHead, (DBL_LNK *)scl_bda))
			{
#ifdef SCL_USE_MMS_STRING_
				if (0 == stricmp(mms_string(&scl_bda->name), pszName ))
				{
					if (0 == stricmp(mms_string(&scl_bda->bType), "STRUCT" ))
#else
				if (0 == stricmp(scl_bda->name, pszName ))
				{
					if (0 == stricmp(scl_bda->bType, "STRUCT" ))
#endif
					{
						long nIndex = strPath.Find('$');

						if (nIndex == -1)
						{
							strName = strPath;
							strPath = "";
						} 
						else
						{
							strName = strPath.Left(nIndex);
							strPath = strPath.Mid(nIndex+1);
						}

						if (!strName.IsEmpty())
						{
							CString strType;
#ifdef SCL_USE_MMS_STRING_
							strType = mms_string(&scl_bda->type);
#else
							strType = scl_bda->type;
#endif
							return check_ModelValuePath_DA_end(strName,strPath,strType,pSclInfo,strDataType);
						}
						else
							return 0;
					}
					else
					{
#ifdef SCL_USE_MMS_STRING_
						strDataType = mms_string(&scl_bda->bType);
#else
						strDataType = scl_bda->bType;
#endif
						return 1;
					}
				}
			}

			break;
		}
	}

	delete pszName;
	delete pszType;
	return 0;
}

BOOL strcmp_fc(char *pSrc,char *pDes)
{
	if (0 == strcmp(pDes, pSrc))
	{
		return 1;
	}

	CString strSrc = pSrc,strDes = pDes;

	if ((strSrc == _T("SP"))||(strSrc == _T("SG")))
	{
		if ((strDes == _T("SP"))||(strDes == _T("SG")))
		{
			return 1;
		}
	}

	return 0;
}

long model_XmlWrite_SubDA(const CString &strModelName , const CString &strDoFcPath,SCL_DA_BDA *pScl_da_bda,CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent,SCL_DATYPE *pDaTypeHead)
{
	CString strNewPath = strDoFcPath,strDataType = pScl_da_bda->btype;
	char* pszDataType = NULL;
	char* pszType = NULL;
	CString_to_char(strDataType, &pszDataType);
	CString_to_char(pScl_da_bda->type, &pszType);

	if (0 == stricmp(pszDataType, "STRUCT" ))
	{
		SCL_DATYPE *pDaType = NULL;
		SCL_BDA *scl_bda = NULL;
		SCL_DA_BDA scl_da_bda;
		CString strTmp;
		strTmp.Format("%s$%s",strDoFcPath.GetString(),pScl_da_bda->da_name.GetString());

		if (pScl_da_bda->nCount > 0)
		{
			CXmlRWElementBase *pElement1 = NULL;
			//MSXML2::IXMLDOMElementPtr oElement1 = NULL;
			pElement1 = oXMLDoc.CreateElement(G_BSTRKEY_VALUE,&oParent);

			if (oParent.IsValid())
				oParent.AppendChild(*pElement1);
			else
				oXMLDoc.AppendChild(*pElement1);

			xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pElement1, "STRUCT");
			xml_SetAttributeValue(G_BSTRKEY_ID, *pElement1, strTmp);
			xml_SetAttributeValue(G_BSTRKEY_NAME, *pElement1, strModelName);
			xml_SetAttributeValue(G_BSTRKEY_VALUE, *pElement1, "");
			xml_SetAttributeValue(G_BSTRKEY_PATH, *pElement1, strTmp);

			CXmlRWElementBase *pElement2 = NULL;
			//MSXML2::IXMLDOMElementPtr oElement2 = NULL;
			pElement2 = oXMLDoc.CreateElement(G_BSTRKEY_VALUE,pElement1);

			if (pElement1->IsValid())
				pElement1->AppendChild(*pElement2);
			else
				oXMLDoc.AppendChild(*pElement2);

			xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pElement2, "ARRAY");
			strTmp += "$";
			xml_SetAttributeValue(G_BSTRKEY_ID, *pElement2, strTmp);
			xml_SetAttributeValue(G_BSTRKEY_NAME, *pElement2, strModelName);
			xml_SetAttributeValue(G_BSTRKEY_VALUE, *pElement2, "");
			xml_SetAttributeValue(G_BSTRKEY_PATH, *pElement2, strTmp);

			long nTotalNum = 0;
			get_array_dataNUM(pScl_da_bda,pDaTypeHead,nTotalNum);

			for (int nCount = 0;nCount<pScl_da_bda->nCount;nCount++)
			{
				if (nTotalNum > 1)
				{
					CXmlRWElementBase *pElement3 = NULL;
					//MSXML2::IXMLDOMElementPtr oElement3 = NULL;
					pElement3 = oXMLDoc.CreateElement(G_BSTRKEY_VALUE,pElement2);

					if (pElement2->IsValid())
						pElement2->AppendChild(*pElement3);
					else
						oXMLDoc.AppendChild(*pElement3);

					xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pElement3, "STRUCT");
					xml_SetAttributeValue(G_BSTRKEY_ID, *pElement3, strTmp);
					xml_SetAttributeValue(G_BSTRKEY_NAME, *pElement3, strModelName);
					xml_SetAttributeValue(G_BSTRKEY_VALUE, *pElement3, "");
					xml_SetAttributeValue(G_BSTRKEY_PATH, *pElement3, strTmp);
					model_XmlWrite_ARRAY(strDoFcPath, pScl_da_bda , oXMLDoc, *pElement3,pDaTypeHead,nCount);
				} 
				else
				{
					model_XmlWrite_ARRAY(strDoFcPath, pScl_da_bda , oXMLDoc, *pElement2,pDaTypeHead,nCount);
				}
			}
			
		} 
		else
		{
			for (pDaType = (SCL_DATYPE *)list_find_last((DBL_LNK *)pDaTypeHead);
				pDaType != NULL;
				pDaType = (SCL_DATYPE *)list_find_prev((DBL_LNK *)pDaTypeHead, (DBL_LNK *)pDaType))
			{
#ifdef SCL_USE_MMS_STRING_
				if (0 == strcmp(mms_string(&pDaType->id), pszType))
#else
				if (0 == strcmp(pDaType->id, pszType))
#endif
				{
					for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)pDaType->bdaHead);
						scl_bda != NULL;
						scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)pDaType->bdaHead, (DBL_LNK *)scl_bda))
					{
#ifdef SCL_USE_MMS_STRING_
						scl_da_bda.da_name = mms_string(&scl_bda->name);
						scl_da_bda.type = mms_string(&scl_bda->type);
						scl_da_bda.btype = mms_string(&scl_bda->bType);
#else
						scl_da_bda.da_name = scl_bda->name;
						scl_da_bda.type = scl_bda->type;
						scl_da_bda.btype = scl_bda->bType;
#endif
						scl_da_bda.nCount = pScl_da_bda->nCount;
						model_XmlWrite_SubDA(strModelName,strTmp, &scl_da_bda , oXMLDoc, oParent,pDaTypeHead);
					}

					break;
				}
			}
		}
	}
	else
	{
		CXmlRWElementBase *pElement = NULL;
		//MSXML2::IXMLDOMElementPtr oElement = NULL;
		pElement = oXMLDoc.CreateElement(G_BSTRKEY_VALUE,&oParent);

		if (oParent.IsValid())
			oParent.AppendChild(*pElement);
		else
			oXMLDoc.AppendChild(*pElement);

		strNewPath += "$";
		strNewPath += pScl_da_bda->da_name;

		model_format(strDataType);

		xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pElement, strDataType);
		xml_SetAttributeValue(G_BSTRKEY_ID, *pElement, strNewPath);

		if ((strNewPath.Find("$stVal")>1)||(strNewPath.Find("$mag$f")>1)||(strNewPath.Find("$setMag$f")>1)||(strNewPath.Find("$setVal")>1)||(strNewPath.Find("$general")>1))
			xml_SetAttributeValue(G_BSTRKEY_NAME, *pElement, strModelName);
		else
			xml_SetAttributeValue(G_BSTRKEY_NAME, *pElement, "");

		if (strDataType == "UTC_TIME")
			xml_SetAttributeValue(G_BSTRKEY_VALUE, *pElement, "1970-1-1 8-0-0-0");
		else
			xml_SetAttributeValue(G_BSTRKEY_VALUE, *pElement, "");

		xml_SetAttributeValue(G_BSTRKEY_PATH, *pElement, strNewPath);
	}

	delete pszDataType;
	delete pszType;
	return 0;
}

void get_array_dataNUM(SCL_DA_BDA *pScl_da_bda,SCL_DATYPE *pDaTypeHead,long &nNum)
{
	CString strDataType = pScl_da_bda->btype;
	char* pszDataType = NULL;
	CString_to_char(strDataType, &pszDataType);
	char* pszType = NULL;
	CString_to_char(pScl_da_bda->type, &pszType);

	if (0 == stricmp(pszDataType, "STRUCT" ))
	{
		SCL_DATYPE *pDaType = NULL;
		SCL_BDA *scl_bda = NULL;
		SCL_DA_BDA scl_da_bda;

		for (pDaType = (SCL_DATYPE *)list_find_last((DBL_LNK *)pDaTypeHead);
			pDaType != NULL;
			pDaType = (SCL_DATYPE *)list_find_prev((DBL_LNK *)pDaTypeHead, (DBL_LNK *)pDaType))
		{
#ifdef SCL_USE_MMS_STRING_
			if (0 == strcmp(mms_string(&pDaType->id), pszType))
#else
			if (0 == strcmp(pDaType->id, pszType))
#endif
			{
				for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)pDaType->bdaHead);
					scl_bda != NULL;
					scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)pDaType->bdaHead, (DBL_LNK *)scl_bda))
				{
#ifdef SCL_USE_MMS_STRING_
					scl_da_bda.da_name = mms_string(&scl_bda->name);
					scl_da_bda.type = mms_string(&scl_bda->type);
					scl_da_bda.btype = mms_string(&scl_bda->bType);
#else
					scl_da_bda.da_name = scl_bda->name;
					scl_da_bda.type = scl_bda->type;
					scl_da_bda.btype = scl_bda->bType;
#endif
					scl_da_bda.nCount = pScl_da_bda->nCount;

					get_array_dataNUM(&scl_da_bda ,pDaTypeHead,nNum);
				}

				break;
			}
		}
	}
	else
		nNum++;

	delete pszType;
	delete pszDataType;
}

long model_XmlWrite_ARRAY(const CString &strDoFcPath,SCL_DA_BDA *pScl_da_bda,CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent,SCL_DATYPE *pDaTypeHead,int nCount)
{
	CString strNewPath,strDataType = pScl_da_bda->btype;
	char* pszDataType = NULL;
	CString_to_char(strDataType, &pszDataType);
	char* pszType = NULL;
	CString_to_char(pScl_da_bda->type, &pszType);

	if (0 == stricmp(pszDataType, "STRUCT" ))
	{
		SCL_DATYPE *pDaType = NULL;
		SCL_BDA *scl_bda = NULL;
		SCL_DA_BDA scl_da_bda;

		for (pDaType = (SCL_DATYPE *)list_find_last((DBL_LNK *)pDaTypeHead);
			pDaType != NULL;
			pDaType = (SCL_DATYPE *)list_find_prev((DBL_LNK *)pDaTypeHead, (DBL_LNK *)pDaType))
		{
#ifdef SCL_USE_MMS_STRING_
			if (0 == strcmp(mms_string(&pDaType->id), pszType))
#else
			if (0 == strcmp(pDaType->id, pszType))
#endif
			{
				for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)pDaType->bdaHead);
					scl_bda != NULL;
					scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)pDaType->bdaHead, (DBL_LNK *)scl_bda))
				{
					CString strTmp;
					strTmp.Format("%s$%s",strDoFcPath.GetString(),pScl_da_bda->da_name.GetString());
					strTmp.Replace("$$","$");//防止出现重复
#ifdef SCL_USE_MMS_STRING_
					scl_da_bda.da_name = mms_string(&scl_bda->name);
					scl_da_bda.type = mms_string(&scl_bda->type);
					scl_da_bda.btype = mms_string(&scl_bda->bType);
#else
					scl_da_bda.da_name = scl_bda->name;
					scl_da_bda.type = scl_bda->type;
					scl_da_bda.btype = scl_bda->bType;
#endif
					scl_da_bda.nCount = pScl_da_bda->nCount;

					model_XmlWrite_ARRAY(strTmp, &scl_da_bda , oXMLDoc, oParent,pDaTypeHead,nCount);
				}

				break;
			}
		}
	}
	else
	{
		CString strTmp;
//		for (int nCount = 0;nCount<pScl_da_bda->nCount;nCount++)
		{
			CXmlRWElementBase *pElement = NULL;
			//MSXML2::IXMLDOMElementPtr oElement = NULL;
			pElement = oXMLDoc.CreateElement(G_BSTRKEY_VALUE,&oParent);

			if (oParent.IsValid())
				oParent.AppendChild(*pElement);
			else
				oXMLDoc.AppendChild(*pElement);

			if (nCount == 0)
			{
				strNewPath.Format("%s$%s",strDoFcPath.GetString(),pScl_da_bda->da_name.GetString());
			}
			else
				strNewPath.Format("%s$%s%d",strDoFcPath.GetString(),pScl_da_bda->da_name.GetString(),nCount);
			
			strNewPath.Replace("$$","$");//防止出现重复

			model_format(strDataType);

			xml_SetAttributeValue(G_BSTRKEY_DATATYPE, *pElement, strDataType);
			xml_SetAttributeValue(G_BSTRKEY_ID, *pElement, strNewPath);
			strTmp.Format("%d次",(nCount));
			xml_SetAttributeValue(G_BSTRKEY_NAME, *pElement,strTmp);
			xml_SetAttributeValue(G_BSTRKEY_VALUE, *pElement, "");
			xml_SetAttributeValue(G_BSTRKEY_PATH, *pElement, strNewPath);
		}
	}

	delete pszType;
	delete pszDataType;
	return 0;
}

void model_format(CString &strDataType)
{
	char *pszDataType = NULL;
	CString_to_char(strDataType, &pszDataType);

	if (0 == stricmp(pszDataType, "Quality" ))
		strDataType = "BIT_STR";
	else if (0 == stricmp(pszDataType, "VisString255" ))
		strDataType = "V_STR";
	else if (0 == stricmp(pszDataType, "Timestamp" ))
		strDataType = "UTC_TIME";
	else if (0 == stricmp(pszDataType, "FLOAT32" ))
		strDataType = "FLOAT";
	else if (0 == stricmp(pszDataType, "INT128" ))
		strDataType = "INT";
	else if (0 == stricmp(pszDataType, "INT64" ))
		strDataType = "INT";
	else if (0 == stricmp(pszDataType, "INT32" ))
		strDataType = "INT";
	else if (0 == stricmp(pszDataType, "INT8" ))
		strDataType = "INT";
	else if (0 == stricmp(pszDataType, "INT8U" ))
		strDataType = "UINT";
	else if (0 == stricmp(pszDataType, "Enum" ))
		strDataType = "INT";
	else if (0 == stricmp(pszDataType, "BOOLEAN" ))
		strDataType = "BOOL";
	else if (0 == stricmp(pszDataType, "Dbpos" ))
		strDataType = "BIT_STR";
	else if (0 == stricmp(pszDataType, "Unicode255" ))
		strDataType = "UTF8_STR";
	else if (0 == stricmp(pszDataType, "Octet64" ))
		strDataType = "OVSTRING64";
	else if (0 == stricmp(pszDataType, "Check" ))
		strDataType = "BVSTRING2";

	delete pszDataType;
}
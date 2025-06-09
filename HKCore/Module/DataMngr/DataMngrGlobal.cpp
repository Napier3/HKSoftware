//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DataMngrGlobal.cpp

#include "stdafx.h"
#include "DataMngrGlobal.h"
#include "../API/FileApi.h"
#include <math.h>
#include "../API/GlobalConfigApi.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const DWORD g_dwDataMngrVersionID   = 0X80000001;
const DWORD g_dwDataMngrCurrVersion = DATAMNGR_VERSION_1_9;
const char* g_pszDataMngrVersionPrefix = "DMVersion";

//////////////////////////////////////////////////////////////////////////
//CDataMngrXmlRWKeys

CDataMngrXmlRWKeys* CDataMngrXmlRWKeys::g_pXmlKeys = NULL;
long CDataMngrXmlRWKeys::g_nDTMRef = 0;


CDataMngrXmlRWKeys::CDataMngrXmlRWKeys()
{
	m_nIsGroupUseDvmData = 0;
	m_nXmlOnlyWrite_Id_Value = 0;
	m_nXmlOnlyRead_MainAttr = 0;
	m_nIsEqualOwn_Id_Value = 0;

	m_strCDsvAppearForErrKey = L"appear-for-err";
	m_strCDvmLogControlKey = L"log-ctrl";
	m_strCDsvEliminateKey = L"eliminate";
	m_strCDsvInDatasetKey = L"dataset";
	m_strCDsvScriptKey = L"dsv-script";
	m_strCDsvElemAttrKey = L"attr";
	m_strCDsvChoiceKey = L"choice";
	m_strCDsvSequenceKey = L"sequence";
	m_strCDsvElementKey = L"element";
	m_strCDsvAnyElementKey = L"any-element";
	m_strCDvmDevicesKey = L"device-models";
	m_strCDvmDeviceKey = L"device-model";
	m_strCDvmLogicDeviceKey = L"ldevice";
	m_strCDvmLogicDeviceMapKey = L"ldevice-map";
	m_strCDvmDatasetKey = L"dataset";
	m_strCDvmDatasetGroupKey = L"dataset-group";
	m_strCDvmDataKey = L"data";

	m_strCRptCtrlKey = L"rpt-ctrl";
	m_strCRptCtrlsKey = L"rpt-ctrls";

	m_strCLogCtrlKey = L"log-ctrl";
	m_strCLogCtrlsKey = L"log-ctrls";
	m_strCDvmLogKey = L"log";
	m_strCDvmLogsKey = L"logs";

	m_strCDatSetKey = L"DatSet";//
	m_strCIntgPdKey = L"IntgPd";//
	m_strCRptIDKey = L"RptID";//
	m_strConfRevKey = L"ConfRev";//
	m_strCBufferedKey = L"Buffered";//
	m_strCBufTimeKey = L"BufTime";//
	m_strCTrgOpsKey = L"TrgOps";//
	m_strCOptFieldsKey = L"OptFields";//
	m_strCRptEnabledKey = L"RptEnabled";//

	m_strCLogNameKey = L"LogName";//
	m_strCLogEnaKey = L"LogEna";//
	m_strCReasonCodeKey = L"ReasonCode";//

	m_strCDvmBrcbKey = L"brcb";
	m_strCDvmValueKey = L"value";
	m_strCDataGroupKey = L"group";
	m_strCDataTypesKey = L"data-types";
	m_strCDataTypeKey = L"data-type";
	m_strCDataTypeValueKey = L"value";
	m_strCLongDatasMngrKey = L"data-mngr";
	m_strCLongDatasKey = L"datas";
	m_strCLongDataKey = L"data";
	m_strCShortDatasMngrKey = L"datas-mngr";
	m_strCShortDatasKey = L"datas";
	m_strCShortDataKey = L"data";
	m_strFolderKey = L"folder";
	m_strCTagsMngrKey = L"tags-mngr";
	m_strCTagsKey = L"tags";
	m_strCTagKey = L"tag";
	m_strCValuesMngrKey = L"values-mngr";
	m_strCValuesKey = L"values";
	m_strCValueKey = L"value";
	m_strValueKey = L"value";
	m_strDefaultValueKey2 = L"default-value";
	m_strDataTypeKey = L"data-type";
	m_strWriteModeKey = L"write-mode";
	m_strDataTypeIDKey = L"data-type-id";
	m_strUnitKey = L"unit";
	m_strFormatKey = L"format";
	m_strRemarkKey = L"remark";
	m_strDefaultValueKey = L"default";
	m_strReservedKey = L"reserved";
	m_strValueNameKey = L"val-name";
	m_strScriptKey = L"script";
	m_strMessageKey = L"msg";
	m_strTypeKey = L"type";
	m_strShowKey = L"show";
	m_strEnableKey = L"enable";
	m_strReserved2Key = L"reserved2";
	m_strIndexKey = L"index";
	m_strMinKey = L"min";
	m_strMaxKey = L"max";
	m_strChangeKey = L"change";
	m_strStepKey = L"step";
	m_strTextKey = L"text";
	m_strModeKey = L"mode";
	m_strOptionKey = L"option";
	m_strUnboundKey = L"unbound";
	m_strTimeKey = L"time";
	m_strOptrKey = L"optr";
	m_strValue2Key = L"value2";
	m_strMinOccKey = L"minocc";
	m_strMaxOccKey = L"maxocc";
	m_strInDatasetKey = L"in-dataset";
	m_strVariableKey = L"variable";
	m_strExprRcvKey = L"expr-rcv";
	m_strExprSendKey = L"expr-snd";

	m_strCDvmDeviceMapKey = L"device-map";
	m_strCDvmLDeviceMapKey = L"ldevice-map";
	m_strCDvmDatasetMapKey = L"dataset-map";
	m_strCDvmDataMapKey = L"data-map";
	m_strMapNameKey = L"map-name";
	m_strMapIDKey = L"map-id";
	m_strCDvmValueMapKey = L"value-map";

	m_strDescKey = L"desc";//
	m_strCmpWithIDKey = L"cmp-with-id";
	m_strDvmCmdDataNameFullKey = L"cmp-name-full";
	m_strDvmCmpToolConfigKey = L"dvm-cmp-tool-config";
	m_strReportModeKey = L"report-mode";
	
	//2023.11.15 lichao PNS331 ����
#ifdef _DVMDATASET_USE_ADDR_
	m_strAddrKey = L"addr";
#endif
}

CDataMngrXmlRWKeys::~CDataMngrXmlRWKeys()
{
}

CDataMngrXmlRWKeys* CDataMngrXmlRWKeys::Create()
{
	g_nDTMRef++;

	if (g_nDTMRef == 1)
	{
		g_pXmlKeys = new CDataMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CDataMngrXmlRWKeys::Release()
{
	g_nDTMRef--;

	if (g_nDTMRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}

void CDataMngrXmlRWKeys::Release(CDataMngrXmlRWKeys *pDataMngrXmlRWKeys)
{
	delete pDataMngrXmlRWKeys;
}

void CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value(CDataMngrXmlRWKeys *pXmlKeys, long nAdd)
{
    if (pXmlKeys == NULL)
    {
        g_pXmlKeys->m_nXmlOnlyWrite_Id_Value += nAdd;
    }
    else
    {
        pXmlKeys->m_nXmlOnlyWrite_Id_Value += nAdd;
    }
}

void CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value(CDataMngrXmlRWKeys *pXmlKeys, long nDec)
{
    if (pXmlKeys == NULL)
    {
        g_pXmlKeys->m_nXmlOnlyWrite_Id_Value -= nDec;
    }
    else
    {
        pXmlKeys->m_nXmlOnlyWrite_Id_Value -= nDec;
    }
}

void CDataMngrXmlRWKeys::IncIsEqualOwn_Id_Value(CDataMngrXmlRWKeys *pXmlKeys, long nAdd)
{
	if (pXmlKeys == NULL)
	{
		g_pXmlKeys->m_nIsEqualOwn_Id_Value += nAdd;
	}
	else
	{
		pXmlKeys->m_nIsEqualOwn_Id_Value += nAdd;
	}
}

void CDataMngrXmlRWKeys::DecIsEqualOwn_Id_Value(CDataMngrXmlRWKeys *pXmlKeys, long nDec)
{
	if (pXmlKeys == NULL)
	{
		g_pXmlKeys->m_nIsEqualOwn_Id_Value -= nDec;
	}
	else
	{
		pXmlKeys->m_nIsEqualOwn_Id_Value -= nDec;
	}
}

//lijunqing 2023-2-28  lijunqing ֻ��ȡ�����ԣ����data������ȡmin��max��unit��step��time��change��
void CDataMngrXmlRWKeys::IncXmlOnlyRead_MainAttr(CDataMngrXmlRWKeys *pXmlKeys, long nAdd)
{
	if (pXmlKeys == NULL)
	{
		g_pXmlKeys->m_nXmlOnlyRead_MainAttr += nAdd;
	}
	else
	{
		pXmlKeys->m_nXmlOnlyRead_MainAttr += nAdd;
	}
}

void CDataMngrXmlRWKeys::DecXmlOnlyRead_MainAttr(CDataMngrXmlRWKeys *pXmlKeys, long nDec)
{
	if (pXmlKeys == NULL)
	{
		g_pXmlKeys->m_nXmlOnlyRead_MainAttr -= nDec;
	}
	else
	{
		pXmlKeys->m_nXmlOnlyRead_MainAttr -= nDec;
	}
}


//////////////////////////////////////////////////////////////////////////
//CDataMngrConstGlobal

long CDataMngrConstGlobal::g_nGlobalRef = 0;
CDataMngrConstGlobal* CDataMngrConstGlobal::g_pGlobal = NULL;


CDataMngrConstGlobal::CDataMngrConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CDataMngrConstGlobal::~CDataMngrConstGlobal()
{
}

CDataMngrConstGlobal* CDataMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CDataMngrConstGlobal();
	}

	return g_pGlobal;
}

void CDataMngrConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

#ifndef _PSX_IDE_QT_
BOOL dvm_PopOpenDvmDlg(CString &strFile, CWnd *pParentWnd, const CString &strCaption)
{
	CString strFilePath, strSoft;

	if (strFile.GetLength() >= 4)
	{
		if (strFile.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
		{
			strFilePath = strFile;
		}
		else
		{
			strFilePath = GetPathFromFilePathName(strFile);
		}
	}
	else
	{
		strFilePath = _P_GetLibraryPath();
	}

	strFilePath += _T("*.xml");
	strSoft = _P_GetSystemSoftName();

#ifdef NOT_USE_XLANGUAGE
	CString strFilter = _T("�豸����ģ���ļ�(*.xml)|*.xml||");
#else
	CString strFilter = g_sLangTxt_DevDataFile/*_T("�豸����ģ���ļ�(*.xml)|*.xml||")*/;
#endif

	CString strPostFix = _T("xml");
	strFile.Empty();

	if (pParentWnd == NULL)
	{
		pParentWnd = AfxGetMainWnd();
	}

	if (PopupOpenFileDialog(pParentWnd, strFilePath, strFilter, strPostFix, strCaption) )
	{
		strFile = strFilePath;
		return TRUE;
	}

	return FALSE;
}
#endif

BOOL dsv_IsElement(UINT nClassID)
{
	return ((nClassID == DVMCLASSID_CDSVELEMENT) || (nClassID == DVMCLASSID_CDSVANYELEMENT));
}

BOOL dsv_IsElement(CExBaseObject *p)
{
	if (p == NULL)
	{
		return FALSE;
	}

	return dsv_IsElement(p->GetClassID());
}


BOOL dvm_IsValueEqual(const CString &strValue1, const CString &strValue2)
{
	if (strValue1.GetLength() == 0 || strValue2.GetLength() == 0)
	{
		return (strValue1 == strValue2);
	}

	double dVal1 = CString_To_double(strValue1);
	double dVal2 = CString_To_double(strValue2);

	return (fabs(dVal2 - dVal1) <= 0.0001);
}

#ifndef _PSX_QT_LINUX_
BOOL dvm_IsValueEqual(BSTR strValue1, BSTR strValue2)
{
	if (wcslen(strValue1) == 0 || wcslen(strValue2) == 0)
	{
		return FALSE;
	}

    double dVal1 = _wtof(strValue1);
    double dVal2 = _wtof(strValue2);

	return (fabs(dVal2 - dVal1) <= 0.0001);
}
#endif


//lijunqing 2021-8-11
void dvm_IncGroupUseDvmData(CDataMngrXmlRWKeys *pXmlKeys)
{
	if (pXmlKeys == NULL)
	{
		ASSERT (CDataMngrXmlRWKeys::g_pXmlKeys != NULL);

		if (CDataMngrXmlRWKeys::g_pXmlKeys == NULL)
		{
			return;
		}
		else
		{
			return dvm_IncGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
		}
	}

	pXmlKeys->m_nIsGroupUseDvmData++;
}

void dvm_DecGroupUseDvmData(CDataMngrXmlRWKeys *pXmlKeys)
{
	if (pXmlKeys == NULL)
	{
		ASSERT (CDataMngrXmlRWKeys::g_pXmlKeys != NULL);

		if (CDataMngrXmlRWKeys::g_pXmlKeys == NULL)
		{
			return;
		}
		else
		{
			return dvm_DecGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
		}
	}

	pXmlKeys->m_nIsGroupUseDvmData--;
}

void dvm_get_json_before(CDataMngrXmlRWKeys *pXmlKeys, bool bOnlyId_Value, BSTR &strValueKey)
{
	strValueKey = pXmlKeys->m_strValueKey;
	pXmlKeys->m_strValueKey = L"val";   //value��������� "value" ��Ϊ "val"

	if (bOnlyId_Value)
	{
		pXmlKeys->m_nXmlOnlyWrite_Id_Value++;
	}
}

void dvm_get_json_after(CDataMngrXmlRWKeys *pXmlKeys, bool bOnlyId_Value, BSTR &strValueKey)
{
	pXmlKeys->m_strValueKey = strValueKey;

	if (bOnlyId_Value)
	{
		pXmlKeys->m_nXmlOnlyWrite_Id_Value--;
	}
}

long dvm_get_json_ascii(CDataMngrXmlRWKeys *pXmlKeys, CExBaseObject *pDvmObj, char **ppszBuffer, long nOffset, bool bOnlyId_Value)
{
	BSTR strValueKey;
	dvm_get_json_before(pXmlKeys, bOnlyId_Value, strValueKey);
	long nRet = pDvmObj->GetXml_ASCII(pXmlKeys, ppszBuffer, nOffset, _JSON_TYPE_);
	dvm_get_json_after(pXmlKeys, bOnlyId_Value, strValueKey);

	return nRet;
}


long dvm_get_json_utf8(CDataMngrXmlRWKeys *pXmlKeys, CExBaseObject *pDvmObj, char **ppszBuffer, long nOffset, bool bOnlyId_Value)
{
	BSTR strValueKey;
	dvm_get_json_before(pXmlKeys, bOnlyId_Value, strValueKey);
	long nRet = pDvmObj->GetXml_UTF8(pXmlKeys, ppszBuffer, nOffset, _JSON_TYPE_);
	dvm_get_json_after(pXmlKeys, bOnlyId_Value, strValueKey);

	return nRet;
}


//lijunqing 2024-9-10
BOOL dvm_OpenBinaryFile(CExBaseObject *pDvmObj, const CString &strFile, bool bOnlyRead_MainAttr)
{
	CBinarySerialBuffer oBuffer;
	BOOL bRet = oBuffer.OpenFromFile(strFile);

	if (bRet)
	{
		dvm_InitDvmVersion(oBuffer);
		oBuffer.SetCharSet(CHAR_SET_ASCII);
		dvm_InitDvmVersion(oBuffer);
		oBuffer.SetReadMode();
		oBuffer.ReadVersion();
		oBuffer.SetVersionFind(oBuffer.m_dwVersion);
		pDvmObj->Serialize(oBuffer);
	}

	return TRUE;
}

BOOL dvm_SaveBinaryFile(CExBaseObject *pDvmObj, const CString &strFile, bool bOnlyRead_MainAttr)
{
	CBinarySerialBuffer oBuffer;
	dvm_InitDvmVersion(oBuffer);
	oBuffer.SetCharSet(CHAR_SET_ASCII);

	if (bOnlyRead_MainAttr)
	{
		oBuffer.m_dwVersion = DATAMNGR_VERSION_FF;
		oBuffer.SetVersionFind(DATAMNGR_VERSION_FF);
	}
	else
	{
		oBuffer.SetVersionFind(g_dwDataMngrCurrVersion);
	}

	oBuffer.SetCalSizeMode();
	oBuffer.WriteVersion();
	pDvmObj->Serialize(oBuffer);
	oBuffer.AllocBuffer(DATAMNGR_DATATYPE_ALLOCBUFFER);//dingxy 20240918 �������ļ��ϴ󣬷���ؼ����㵼�±�������˼Ӵ�

	oBuffer.SetWriteMode();
	oBuffer.WriteVersion();
	pDvmObj->Serialize(oBuffer);

	return oBuffer.WriteToFile(strFile);
}


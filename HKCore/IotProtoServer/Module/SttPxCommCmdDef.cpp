#include "stdafx.h"
#include "SttPxCommCmdDef.h"



const CString g_strPxDataSetID[PX_DSID_dsMaxCount] = {_T("dsParameter"),_T("dsSetting"),_T("dsEna"),_T("dsAin")
	, _T("dsDin"),_T("dsRec"),_T("dsTripInfo"),_T("dsAlarm")
	, _T("dsWarning"),_T("dsSoe"),_T("dsSV"),_T("dsGOOSE"), _T("dsDout")
    , _T("all"), _T("dsOwnDef"), _T("none"), _T("report"), _T("log"), _T("file"), _T("dsMatrix")};
const CString g_strPxDataSetIDKey[PX_DSID_dsMaxCount] = {_T("Parameter"),_T("Setting"),_T("Ena"),_T("Ain")
	, _T("Din"),_T("Rec"),_T("TripInfo"),_T("Alarm")
	, _T("Warning"),_T("Soe"),_T("SV"),_T("GOOSE"), _T("Dout")
    , _T("all"), _T("OwnDef"), _T("none"), _T("report"), _T("log"), _T("file"), _T("Matrix")};

const CString g_strPxDataSetName[PX_DSID_dsMaxCount] = {_T("װ�ò���"),_T("��ֵ"),_T("ѹ��"),_T("ң��")
, _T("ң��"),_T("���ϱ���"),_T("�����¼�"),_T("�����ź�")
, _T("�澯�ź�"),_T("SOE"),_T("����ֵ"),_T("GOOSE") , _T("ң��")
, _T("all"), _T("�Զ���"), _T("none"), _T("report"), _T("log"), _T("file"), _T("����")};


const CString& Px_GetDataSetName(const CString &strIDKey)
{
	long nIndex = 0;
	long nIndexFind = -1;

	for (nIndex=0; nIndex<PX_DSID_dsMaxCount; nIndex++)
	{
		if (g_strPxDataSetID[nIndex].GetLength() == 0)
		{
			break;
		}

		if (g_strPxDataSetID[nIndex].Find(strIDKey) >= 0)
		{
			nIndexFind = nIndex;
			break;
		}
	}

	if (nIndexFind != -1)
	{
		return g_strPxDataSetName[nIndexFind];
	}
	else
	{
		return _T("Error Dataset ID");
	}
}

const CString& Px_GetDataSetID(const CString &strID)
{
	long nIndex = 0;
	long nIndexFind = -1;

	for (nIndex=0; nIndex<PX_DSID_dsMaxCount; nIndex++)
	{
		if (g_strPxDataSetID[nIndex].GetLength() == 0)
		{
			break;
		}

		if (strID.Find(g_strPxDataSetID[nIndex]) >= 0)
		{
			nIndexFind = nIndex;
			break;
		}
	}

	if (nIndexFind != -1)
	{
		return g_strPxDataSetID[nIndexFind];
	}
	else
	{
		return g_strPxDataSetID[PX_DSID_dsAll];
	}
}

static const  CString g_strPxDataSetIDError = _T("Err_dsID");

const CString& Px_GetDataSetKey(const CString &strID)
{
	long nIndex = 0;
	long nIndexFind = -1;

	for (nIndex=0; nIndex<PX_DSID_dsMaxCount; nIndex++)
	{
		if (g_strPxDataSetID[nIndex].GetLength() == 0)
		{
			break;
		}

		if (g_strPxDataSetID[nIndex].Find(strID) >= 0)
		{
			nIndexFind = nIndex;
			break;
		}
	}

	if (nIndexFind != -1)
	{
		return g_strPxDataSetIDKey[nIndexFind];
	}
	else
	{
		return strID;
	}
}


void Px_GetDataSetKeyEx(const CString &strID, CStringArray &astrKeys)
{
	CString strKey = Px_GetDataSetKey(strID);

	if (!Px_IsDataSetIDError(strKey))
	{
		astrKeys.Add(strKey);
	}
}

long Px_GetDataSetKey(const CString &strID, CStringArray &astrKeys)
{
	astrKeys.RemoveAll();
	CString strTempID = strID;
	long nPos = 0;
	long nLen = strTempID.GetLength();
	CString strKey;

	while (TRUE)
	{
		nPos = strTempID.Find('#');

		if (nPos > 0)
		{
			strKey = strTempID.Left(nPos);
			strTempID = strTempID.Mid(nPos+1);
			Px_GetDataSetKeyEx(strKey, astrKeys);
		}
		else
		{
			break;
		}
	}

	Px_GetDataSetKeyEx(strTempID, astrKeys);

	return astrKeys.GetCount();
}

BOOL Px_IsDataSetIDError(const CString &strID)
{
	return (g_strPxDataSetIDError == strID);
}

BOOL Px_JdgDataset(const CString &strDatasetID, long nPxDsID)
{
	if (PX_DSID_dsParameter > nPxDsID || nPxDsID > PX_DSID_dsMatrix)
	{
		return FALSE;
	}
	else
	{
		return strDatasetID.Find(g_strPxDataSetIDKey[nPxDsID]) > 0;
	}
}

BOOL Px_JdgDataset(const CString &strDatasetID, const CString &strPxDsIDKey)
{
	return strDatasetID.Find(strPxDsIDKey) > 0;
}

BOOL Px_DatasetCanWrite(const CString &strDatasetID)
{
	if (Px_JdgDataset(strDatasetID, PX_DSID_dsParameter))
	{
		return TRUE;
	}

	if (Px_JdgDataset(strDatasetID, PX_DSID_dsSetting))
	{
		return TRUE;
	}

	if (Px_JdgDataset(strDatasetID, PX_DSID_dsEna))
	{
		return TRUE;
	}

	if (Px_JdgDataset(strDatasetID, PX_DSID_dsDout))
	{
		return TRUE;
	}

	return FALSE;
}



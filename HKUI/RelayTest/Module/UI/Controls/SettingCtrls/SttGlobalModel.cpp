#include "SttGlobalModel.h"
#include "../../../../../Module/Expression/EpExpression.h"
#include "../../../XLangResource_Native.h"

CExBaseList* g_pDvmDevice_AttachSetting = NULL;	//ģ��	20240820 huangliang 

CSttGlobalModel::CSttGlobalModel(void)
{
}

CSttGlobalModel::~CSttGlobalModel(void)
{
}

//20240806 huangliang ������ֵ����·��,�������ʽ����
bool CSttGlobalModel::AnalysisPath(const QString &strSrcPath, QString *strName, QString *strValue)
{
	if (strSrcPath == "")
		return false;

	if (IsStringNumber(strSrcPath.toLocal8Bit()))
	{
		return false;
	}

	if (g_pDvmDevice_AttachSetting == NULL)
	{
		return FALSE;
	}

	//20240909 huangliang �Ѿ�ȥ�����ڵ�ID�����Դ˴�����Ҫ��ת��
	//20240813 huangliang IDȫ·������ʼIDΪ�ļ�·������ʱ�滻
	//QString sRepaceHead = HL_REPACE_FULLPATH_HEAD;
	//QString sHeadPath = g_pDvmDevice_AttachSetting->m_strID;
	QString strNewSrcPath = strSrcPath;
	//strNewSrcPath.replace(sHeadPath, sRepaceHead);

	CEpExpression oEpExp;
	if (oEpExp.ChangeEpExpression(strNewSrcPath) == -1)
	{
		return false;
	}

	bool bCheckOk = false;
	QString sName = strNewSrcPath;
	QString sValue = strNewSrcPath;
	POS pos = oEpExp.GetHeadPosition();
	CEpExpVariable *pExpVar = NULL;
	while (pos != NULL)
	{
		pExpVar = oEpExp.GetNext(pos);

		QString sTempName, sTempValue, sTempID;
		sTempID = pExpVar->m_strVarID;
		//sTempID.replace(sRepaceHead, sHeadPath);	//20240813 huangliang ����ǰ�滻��ȫ·��ID
		bCheckOk |= FindNameFromDeviceModel(sTempID, &sTempName, &sTempValue);	//��һ���ҵ�����ɹ�

		//�滻���ʽ�е�·��
		sName = sName.replace(pExpVar->m_strVarID, sTempName);
		sValue = sValue.replace(pExpVar->m_strVarID, sTempValue);

		pExpVar->m_dValue = CString_To_double(sTempValue);
	}

	double dValue = 1;
	oEpExp.Value(dValue);
	sValue += "=";
	sValue += QString::number(dValue);

	*strName = sName;
	*strValue = QString::number(dValue); //sValue;ֻ��ʾ������ֵ
	return bCheckOk;
}

BOOL CSttGlobalModel::FindNameFromDeviceModel(const CString &strPath, QString *strName, QString *strValue)
{
	*strName = g_sLangTxt_Setting_NoFind;	//20240924 huangliang ��δ�ҵ�������³������룬��Ϊ������
	*strValue = "0";
	
	CExBaseObject *pFindItem = FindObjectFromDeviceModel(strPath);
	if (pFindItem == NULL)
		return FALSE;

	*strName = pFindItem->m_strName;

	//����ֵ
	if (pFindItem->GetClassID() == DVMCLASSID_CDVMDATA)
		*strValue = ((CDvmData*)pFindItem)->m_strValue;
	else if (pFindItem->GetClassID() == DVMCLASSID_CDVMVALUE)
		*strValue = ((CDvmValue*)pFindItem)->m_strValue;
	return TRUE;
}
CExBaseObject * CSttGlobalModel::FindObjectFromDeviceModel(const CString &strPath)
{
	if (strPath.GetLength() == 0)
	{
		return NULL;
	}

	if (g_pDvmDevice_AttachSetting == NULL)
	{
		return NULL;
	}

	CExBaseObject *pHeadChild = NULL;
	if (strPath.GetAt(0) == '$')
	{
		pHeadChild = g_pDvmDevice_AttachSetting->FindByID(strPath.Mid(1));
	}
	else
	{
		pHeadChild = g_pDvmDevice_AttachSetting;
		long nPos = MatchID(pHeadChild, strPath);
		if (nPos > 0)
		{
			pHeadChild = FindRptDataByPath((CExBaseList *)pHeadChild, strPath.Mid(nPos));
		}
		else
		{
			pHeadChild = FindRptDataByPath((CExBaseList *)pHeadChild, strPath);
		}
	}

	if (pHeadChild == NULL)
		return NULL;

	return pHeadChild;
}
long CSttGlobalModel::MatchID(CExBaseObject *pCurrItem, const CString &strPath)
{
	CString strID = pCurrItem->m_strID;
	strID += _T("$");

	if (strPath.GetLength() < strID.GetLength())
	{
		return -1;
	}

	if (strID == strPath.Left(strID.GetLength()))
	{
		return strID.GetLength();
	}
	else
	{
		return -1;
	}
}

CExBaseObject* CSttGlobalModel::FindRptDataByPath(CExBaseList *pCurrItem, const CString &strPath)
{
	POS pos = pCurrItem->GetHeadPosition();
	CExBaseObject *p = NULL;
	CString strID;
	long nPos = 0;
	CExBaseObject *pFind = NULL;
	CString strPath2;
	long nSubItemCount = 0;

	while (pos != NULL)
	{
		p = pCurrItem->GetNext(pos);
		if (p == NULL)
			return NULL;

		nSubItemCount++;
		nPos = MatchID(p, strPath);

		if (nPos < 0)
		{
			continue;
		}

		strPath2 = strPath.Mid(nPos);
		pFind = FindRptDataByPath((CExBaseList *)p, strPath2);

		if (pFind == NULL)
		{//û���ҵ���������Ŀp�в��ұ�������
			return ((CExBaseList *)p)->FindByID(strPath2);
		}
		else
		{
			return pFind;
		}
	}

	if (nSubItemCount == 0)
	{//û������Ŀ�����ʾ�����Ǹ��ڵ㣬���ұ�������
		return pCurrItem->FindByID(strPath);
	}
	else
	{
		return NULL;
	}
}
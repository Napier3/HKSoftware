#include "SttGlobalModel.h"
#include "../../../../../Module/Expression/EpExpression.h"
#include "../../../XLangResource_Native.h"

CExBaseList* g_pDvmDevice_AttachSetting = NULL;	//模板	20240820 huangliang 

CSttGlobalModel::CSttGlobalModel(void)
{
}

CSttGlobalModel::~CSttGlobalModel(void)
{
}

//20240806 huangliang 解析定值关联路径,包含表达式解析
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

	//20240909 huangliang 已经去掉根节点ID，所以此处不需要再转换
	//20240813 huangliang ID全路径，开始ID为文件路径，临时替换
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
		//sTempID.replace(sRepaceHead, sHeadPath);	//20240813 huangliang 查找前替换回全路径ID
		bCheckOk |= FindNameFromDeviceModel(sTempID, &sTempName, &sTempValue);	//有一个找到就算成功

		//替换表达式中的路径
		sName = sName.replace(pExpVar->m_strVarID, sTempName);
		sValue = sValue.replace(pExpVar->m_strVarID, sTempValue);

		pExpVar->m_dValue = CString_To_double(sTempValue);
	}

	double dValue = 1;
	oEpExp.Value(dValue);
	sValue += "=";
	sValue += QString::number(dValue);

	*strName = sName;
	*strValue = QString::number(dValue); //sValue;只显示计算后的值
	return bCheckOk;
}

BOOL CSttGlobalModel::FindNameFromDeviceModel(const CString &strPath, QString *strName, QString *strValue)
{
	*strName = g_sLangTxt_Setting_NoFind;	//20240924 huangliang 在未找到的情况下出现乱码，改为多语言
	*strValue = "0";
	
	CExBaseObject *pFindItem = FindObjectFromDeviceModel(strPath);
	if (pFindItem == NULL)
		return FALSE;

	*strName = pFindItem->m_strName;

	//设置值
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
		{//没有找到，就在项目p中查找报告数据
			return ((CExBaseList *)p)->FindByID(strPath2);
		}
		else
		{
			return pFind;
		}
	}

	if (nSubItemCount == 0)
	{//没有子项目，则表示可能是根节点，查找报告数据
		return pCurrItem->FindByID(strPath);
	}
	else
	{
		return NULL;
	}
}
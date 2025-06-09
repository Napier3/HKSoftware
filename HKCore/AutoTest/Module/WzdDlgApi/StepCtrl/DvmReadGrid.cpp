#include "stdafx.h"
#include "DvmReadGrid.h"
#include "../StepDlg/WzdDlg_DvmRead.h"
#include "../MmsApi/MmsGlobal.h"
#include "../../../../61850/Module/SclToModel/ModelWriteXml.h"

CDvmReadGrid::CDvmReadGrid()
{
	m_nType = Ain;
}

CDvmReadGrid::~CDvmReadGrid()
{

}

void CDvmReadGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CDvmReadGrid::InitGridTitle_Ain()
{
	SetColumnCount(3);
	CString cTempStr[10]={_T("序号"),
		_T("名称"),
		_T("路径")};
	int iWidth[3]={50,120,120};
	CWzdDlgStyleGrid::InitGridTitle(cTempStr, iWidth, 3);
}

void CDvmReadGrid::InitGridTitle_FileDir()
{
	SetColumnCount(5);
	CString cTempStr[5]={_T("序号"),
		_T("名称"),
		_T("路径"),
		_T("时间"),
		_T("大小")};
	int iWidth[5]={50,120,120, 50, 50};
	CWzdDlgStyleGrid::InitGridTitle(cTempStr, iWidth, 5);
}

void CDvmReadGrid::InitGridTitle_Normal()
{
	SetColumnCount(10);
	CString cTempStr[10]={_T("序号"),
		_T("名称"),
		_T("路径"),
		_T("类型"),
		_T("数值"),
		_T("步长"),
		_T("单位"),
		_T("修改"),
		_T("最小值"),
		_T("最大值")};
	int iWidth[10]={50,120,120,60,50,50,50,50,50,50};
	CWzdDlgStyleGrid::InitGridTitle(cTempStr, iWidth, 10);
}

void CDvmReadGrid::InitGridTitle_Journal()
{
	SetColumnCount(6);
	CString cTempStr[6]={_T("序号"),
		_T("EntryID"),
		_T("日志控制块"),
		_T("日志数据名称"),
		_T("数据索引(DataRef)"),
		_T("时间")};
	int iWidth[6]={50,100,100,100,80,80};
	CWzdDlgStyleGrid::InitGridTitle(cTempStr, iWidth, 6);
}

void CDvmReadGrid::InitGridTitle()
{
	switch(m_nType)
	{
	case 0: InitGridTitle_Ain(); break;
	case 1:	InitGridTitle_FileDir(); break;
	case 2:	InitGridTitle_Normal(); break;
	case 3: InitGridTitle_Journal(); break;
	default:
		break;
	}
}

//tagDA数据操作
CString CDvmReadGrid::mms_GetDAName(tagDA *pDA)
{
	CString strText;
#ifdef _use_mms_string
	strText = mms_string(&pDA->DADescri.Value.string);//mms_UTF8ToUnicode(pDA->DADescri.Value.name, strlen(pDA->DADescri.Value.name));
#else
	strText = pDA->DADescri.Value.string;//mms_UTF8ToUnicode(pDA->DADescri.Value.name, strlen(pDA->DADescri.Value.name));
#endif
	return strText;
}

CString CDvmReadGrid::mms_GetDADataType(tagDA *pDA)
{
	CString strText;
	return strText;
}

CString CDvmReadGrid::mms_GetDAPath(tagDA *pDA)
{
	CString strText;
	return strText;
}

CString CDvmReadGrid::mms_GetDAUnit(tagDA *pDA)
{
	CString strText;
	My_PareVarUnite(pDA->DAUnite.Value.i, strText);
	return strText;
}

long CDvmReadGrid::GetSubDACol(ST_CHAR *pmmsDAName, long nPos)
{
// 	CString strTemp;
// 	strTemp = pmmsDAName;
// 	strTemp = strTemp.Mid(nPos);
// 	CString strCol;
// 
// 	if (strTemp.GetLength() == 0)
// 	{
// 		strTemp = _T("值");
// 	}
// 
// 	long nCount = m_astrAinColName.GetSize();
// 	long nIndex = 0;
 	long nCol = -1;
// 
// 	for (nIndex=0; nIndex<nCount; nIndex++)
// 	{
// 		strCol = m_astrAinColName.GetAt(nIndex);
// 		if (strCol.Find(strTemp) >= 0 || strTemp.Find(strCol) >= 0)
// 		{
// 			nCol = nIndex;
// 			break;
// 		}
// 	}
// 
// 	if (nCol == -1)
// 	{
// 		m_astrAinColName.Add(strTemp);
// 		nCount = m_astrAinColName.GetCount();
// 		nCol = nCount + 2;
// 		m_ListCtrl.InsertColumn(nCol,strTemp,LVCFMT_LEFT,80);
// 	}
// 	else
// 	{
// 		nCol += 3;
// 	}

	return nCol;
}

void CDvmReadGrid::ShowAinText(long nRow, tagDA *pSubDA, long nPos)
{
#ifdef _use_mms_string
	long nCol = GetSubDACol(mms_string(&pSubDA->DAValue.mmsName), nPos);
#else
	long nCol = GetSubDACol(pSubDA->DAValue.mmsName, nPos);
#endif
	CString strText = mms_GetValue(&pSubDA->DAValue, pSubDA->DataType);
	//m_ListCtrl.SetItemText(nRow, nCol, strText);
}

void CDvmReadGrid::ShowData_Ain(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CTagDAObject* pObj = (CTagDAObject*)pData;
	tagDA* pDA = pObj->m_pData;
	//序号
	Show_Index(pObj, nRow, 0);
	//名称
	CString strText = mms_GetDADesc(pDA);
	if (strText.IsEmpty())
	{
		strText = mms_string(&pDA->DAValue.mmsName);
		mms_str_copy(&pDA->DADescri.mmsName,&pDA->DAValue.mmsName);
	}
	Show_StaticString(pObj, nRow, 1, strText);
	//路径
#ifdef _use_mms_string
	strText = mms_string(&pDA->DAValue.mmsName);
#else
	strText = pDA->DAValue.mmsName;
#endif
	Show_StaticString(pObj, nRow, 2, strText);
	//子tagDA?
	long nCount = pDA->nSubDANum;
	long nIndex = 0;
#ifdef _use_mms_string
	long nPos = mms_str_length(&pDA->DAValue.mmsName) + 1;
#else
	long nPos = strlen(pDA->DAValue.mmsName) + 1;
#endif

	if (nCount == 0)
	{
#ifdef _use_mms_string
		long nCol = GetSubDACol(mms_string(&pDA->DAValue.mmsName), nPos);
#else
		long nCol = GetSubDACol(pDA->DAValue.mmsName, nPos);
#endif

		if (nCol == -1)
		{
			nCol = 3;
		}
		strText = mms_GetValue(&pDA->DAValue, pDA->DataType);
		Show_StaticString(pObj, nRow, nCol, strText);
	}
	else
	{
		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			ShowAinText(nRow, &pDA->pSubDA[nIndex], nPos);
		}
	}

	nRow++;
}

void CDvmReadGrid::ShowData_FileDir(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{

}

void CDvmReadGrid::ShowData_Normal(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CTagDAObject* pObj = (CTagDAObject*)pData;
	tagDA* pDA = pObj->m_pData;

	//序号
	Show_Index(pObj, nRow, 0);
	//名称
	CString strText = mms_GetDADesc(pDA);
	if (strText.IsEmpty())
	{
		strText = mms_string(&pDA->DAValue.mmsName);
		mms_str_copy(&pDA->DADescri.mmsName,&pDA->DAValue.mmsName);
	}
	Show_StaticString(pObj, nRow, 1, strText);
	//路径
#ifdef _use_mms_string
	strText = mms_string(&pDA->DAValue.mmsName);
#else
	strText = pDA->DAValue.mmsName;
#endif
	Show_StaticString(pObj, nRow, 2, strText);
	//类型
 	strText = pDA->DataType;
	Show_StaticString(pObj, nRow, 3,strText);
	//数值
	strText = mms_GetDAValue(pDA);
	Show_StaticString(pObj, nRow, 4,strText);
	//步长
 	strText.Empty();
 #ifdef tagDA_use_UNIT_MIN_MAX_STEP
	if (mms_str_length(&pDA->StepSize.mmsName) > 0)
	{
		CString strDataType = "";

		if (mms_GetValueDataType(pDA,strDataType))
		{
			strText = mms_GetValueByDataType(&pDA->StepSize.Value ,strDataType);
		}
		//			strText.Format("%f",pDA->StepSize.Value.f);
	}
	else
		mms_GetDAStepSizeValue(pDA, strText);
#endif
 	Show_StaticString(pObj, nRow, 5, strText);
	//单位
	strText = mms_GetDAUnit(pDA);
	Show_StaticString(pObj, nRow, 6, strText);
	//修改
	if (pDA->bModify)
	{
		strText = _T("X");
	}
	else
	{
		strText = _T("");
	}
 	Show_StaticString(pObj, nRow, 7, strText);
	//最小值
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
 	Show_StaticString(pObj, nRow, 8, strText);
#endif
	//最大值
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
	Show_StaticString(pObj, nRow, 9, strText);
#endif

	nRow++;
}

void CDvmReadGrid::ShowData_Journal(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CTagDAObject* pObj = (CTagDAObject*)pData;
	tagDA* pDA = pObj->m_pData;

	Show_Index(pObj, nRow, 0);
	Show_StaticString(pObj, nRow, 1, pObj->m_strEntryID);
	Show_StaticString(pObj, nRow, 2, pObj->m_strLogEntryName);
	Show_StaticString(pObj, nRow, 3, mms_string(&pDA->DADescri.Value.string));
	Show_StaticString(pObj, nRow, 4, mms_string(&pDA->DAValue.mmsName));
	Show_StaticString(pObj, nRow, 5, pObj->m_strEntryTime);
	Show_StaticString(pObj, nRow, 1, pObj->m_strEntryID);

	nRow++;
}

void CDvmReadGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow /* = TRUE */)
{
	switch(m_nType)
	{
 	case 0: ShowData_Ain(pData, nRow, bInsertRow); break;
 	case 1:	ShowData_FileDir(pData, nRow, bInsertRow); break;
 	case 2:	ShowData_Normal(pData, nRow, bInsertRow); break;
 	case 3: ShowData_Journal(pData, nRow, bInsertRow); break;
	default:
		break;
	}
}
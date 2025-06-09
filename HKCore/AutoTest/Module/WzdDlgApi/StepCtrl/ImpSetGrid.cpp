#include "stdafx.h"
#include "ImpSetGrid.h"
#include "../WzdDlgDef.h"
#include "../../../../Module/API/Xmd5.h"
#include "../../../../Module/API/StringConvert/String_Gbk_To_Utf8.h"

CImpSetGrid::CImpSetGrid()
{
	m_pDataset = NULL;
	m_pDvmDataset = NULL;
}

CImpSetGrid::~CImpSetGrid()
{

}

void CImpSetGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(5);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CImpSetGrid::InitGridTitle()
{
	CString astrGridTitle[5] = {_T("编号"),_T("名称"), _T("省调发布定值"), _T("校验使用定值"), _T("校对结果")};
	int iGridWidth[5]={50, 300, 100, 100, 80};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, 5);
}
void CImpSetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CString strValue,strDefaultValue;
	CDataObj *pDataObj = (CDataObj *)pData;
	Show_Index(pDataObj, nRow, 0);
	Show_StaticString(pDataObj, nRow, 1, &pDataObj->m_strName);	
	if(pData->GetClassID() == DVMCLASSID_CDVMDATA)			//20231212 luozibing pdf与xml默认值与检验值存放地方不同
	{
		CDvmData *pDataDvm = (CDvmData *)pData;
		Show_StaticString(pData, nRow, 2, &pDataDvm->m_strValue);
		if(pData->m_strName == _T("")||m_pDataset == NULL)
		{
			nRow++;
			return;
		}
		CExBaseObject *pDataset = m_pDataset->FindByName(pData->m_strName);//20231218 luozibing  找到对应Map数据的值
		if(pDataset != NULL)
		{
			pDataObj = (CDataObj *)pDataset;
			Show_String(pDataObj, nRow, 3, &pDataObj->m_strValue, EndEditCell_String);
			strValue = pDataObj->m_strValue;
		}
		else
		{
			Show_StaticString(pData, nRow, 3, _T(""));
			strValue = "";
		}
		strDefaultValue = pDataDvm->m_strValue;
	}
	else
	{
		Show_StaticString(pData, nRow, 2, &pDataObj->m_strDefaultValue);
		Show_String(pDataObj, nRow, 3, &pDataObj->m_strValue, EndEditCell_String);
		strValue = pDataObj->m_strValue;
		strDefaultValue = pDataObj->m_strDefaultValue;
	}
	
	if(strValue == _T(""))
	{
		Show_StaticString(pData, nRow, 4, "");
	}
	else if(strValue == strDefaultValue)
	{
		Show_StaticString(pData, nRow, 4, "√");
	}
	else
	{
		Show_StaticString(pData, nRow, 4, "×");
	}

	nRow++;
}
//void CImpSetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
//{
//	//20230808 huangliang 以模板数据为基准显示
//	CDataObj *pDataObj = (CDataObj *)pData;
//	Show_Index(pDataObj, nRow, 0);
//	Show_StaticString(pDataObj, nRow, 1, &pDataObj->m_strName);
//	//Show_StaticString(pDataObj, nRow, 2, &pDataObj->m_strValue);
//	Show_String(pDataObj, nRow, 2, &pDataObj->m_strValue, EndEditCell_String);
//
//	if(m_pDataset == NULL || m_pDvmDataset == NULL)
//	{
//		Show_StaticString(pDataObj, nRow, 3, _T(""));
//		Show_StaticString(pDataObj, nRow, 4, _T(""));
//		nRow++;
//		return ;
//	}
//
//	CDvmData *pDvmData = NULL;
//	if(m_pDataset->m_strID == "Parameter" || m_pDataset->m_strID == "Ena")
//	{
//		POS pos = m_pDvmDataset->GetHeadPosition();
//		while (pos != NULL)
//		{
//			CDvmData* pType = (CDvmData *)m_pDvmDataset->GetNext(pos);
//			if (pType->m_strName == pDataObj->m_strName)
//			{
//				pDvmData = pType;
//				break;
//			}
//		}
//	}
//	else
//	{
//		POS pos = m_pDvmDataset->GetHeadPosition();
//		CExBaseList oListFind;
//		while (pos != NULL)
//		{
//			CDvmData *p = (CDvmData *)m_pDvmDataset->GetNext(pos);
//			if (p->m_strName == pDataObj->m_strName)
//			{
//				oListFind.AddTail(p);
//			}
//		}
//
//		if(oListFind.GetCount() == 1)
//		{
//			pDvmData = (CDvmData*)oListFind.GetHead();
//		}
//		else
//		{
//			POS posType = oListFind.GetHeadPosition();
//			while(posType)
//			{
//				CDvmData* pType = (CDvmData*)oListFind.GetNext(posType);
//				if(pDataObj->m_strID.Find("mms") != -1)
//				{
//					if(pType->m_strUnit == "s" || pType->m_strUnit == "ms")
//					{
//						pDvmData = pType;
//						break;
//					}
//				}
//				else if(pDataObj->m_strID.Find("Enable") != -1)
//				{
//					if(pType->m_strUnit != "")//认为控制字是没有单位的
//						continue;
//					if(CString_To_long(pType->m_strMin) == 0 && CString_To_long(pType->m_strMax) == 1)
//					{
//						pDvmData = pType;
//						break;
//					}
//				}
//				else
//				{
//					if(pType->m_strUnit == "s" || pType->m_strUnit == "ms")
//						continue;
//					if(CString_To_long(pType->m_strMin) == 0 && CString_To_long(pType->m_strMax) == 1)
//						continue;
//
//					pDvmData = pType;
//					break;
//				}
//			}
//		}
//		oListFind.RemoveAll();
//	}
//
//	if(pDvmData)
//	{
//		//Show_String(pDataObj, nRow, 3, &pDvmData->m_strValue, EndEditCell_String);
//		Show_StaticString(pDataObj, nRow, 3, &pDvmData->m_strValue);
//
//		if(pDataObj->m_strValue == _T(""))
//		{
//			Show_StaticString(pData, nRow, 4, "");
//		}
//		else if(pDataObj->m_strValue == pDvmData->m_strValue)
//		{
//			Show_StaticString(pData, nRow, 4, "√");
//		}
//		else
//		{
//			Show_StaticString(pData, nRow, 4, "×");
//		}
//	}
//	else
//	{
//		Show_StaticString(pDataObj, nRow, 3, _T(""));
//		Show_StaticString(pDataObj, nRow, 4, _T(""));
//	}
//
//	nRow++;
//}
//void CImpSetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
//{
//	CDvmData *pDvmData = (CDvmData*)pData;
//
//	Show_Index(pDvmData, nRow, 0);
//	Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strName);
//	Show_StaticString(pDvmData, nRow, 2, &pDvmData->m_strValue);
//
//	if(m_pDataset == NULL)
//	{
//		Show_StaticString(pDvmData, nRow, 3, _T(""));
//		Show_StaticString(pDvmData, nRow, 4, _T(""));
//		nRow++;
//		return ;
//	}
//
//	CDataObj* pObj = NULL;
//	if(m_pDataset->m_strID == "Parameter" || m_pDataset->m_strID == "Ena")
//	{
//		pObj = m_pDataset->FindByNameEx(pDvmData);
//	}
//	else
//	{
//		POS pos = m_pDataset->GetHeadPosition();
//		CExBaseList oListFind;
//		while (pos != NULL)
//		{
//			CDataObj *p = (CDataObj *)m_pDataset->GetNext(pos);
//			if (p->m_strName == pDvmData->m_strName)
//			{
//				oListFind.AddTail(p);
//			}
//		}
//
//		if(oListFind.GetCount() == 1)
//		{
//			pObj = (CDataObj*)oListFind.GetHead();
//		}
//		else
//		{
//			CString strType;
//			if(pDvmData->m_strUnit == "s" || pDvmData->m_strUnit == "ms")
//			{
//				strType = "mms";
//			}
//			else if (CString_To_long(pDvmData->m_strMin) == 0 && CString_To_long(pDvmData->m_strMax) == 1)
//			{
//				strType = "Enable";
//			}
//			else
//			{
//				strType = "OUTMATR";
//			}
//
//			POS posType = oListFind.GetHeadPosition();
//			while(posType)
//			{
//				CDataObj* pType = (CDataObj*)oListFind.GetNext(posType);
//				if(pType->m_strID.Find(strType) != -1)
//				{
//					pObj = pType;
//					break;
//				}
//			}
//		}
//
//		oListFind.RemoveAll();
//	}
//
//	if(pObj)
//	{
//		Show_String(pObj, nRow, 3, &pObj->m_strValue, EndEditCell_String);
//
//		if(pObj->m_strValue == _T(""))
//		{
//			Show_StaticString(pData, nRow, 4, "");
//		}
//		else if(pObj->m_strValue == pDvmData->m_strValue)
//		{
//			Show_StaticString(pData, nRow, 4, "√");
//		}
//		else
//		{
//			Show_StaticString(pData, nRow, 4, "×");
//		}
//	}
//	else
//	{
//		Show_StaticString(pDvmData, nRow, 3, _T(""));
//		Show_StaticString(pDvmData, nRow, 4, _T(""));
//	}
//
//	nRow++;
//}

void CImpSetGrid::CalMD5(CString& strMD5)
{
	strMD5 = _T("");
	for (int i = 1; i < GetRowCount(); i++)
	{
		strMD5 += GetItemText(i, 3);
	}

	char *pchVal = NULL;
	char *pszUtf8 = NULL;
	int nSize = CString_to_char(strMD5,&pchVal);
	int nDestLen = 0;
	gbk_to_utf8_r((unsigned char*)pchVal, nSize, (unsigned char**)&pszUtf8, &nDestLen, 0);

	CXMD5 oMD5;
	oMD5.update(pszUtf8, nDestLen);
	string str = oMD5.toString();
	strMD5 = str.c_str();

	delete []pchVal;
	delete []pszUtf8;
}

void CImpSetGrid::EndEditCell_String(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CWzdDlgStyleGrid::EndEditCell_String(nRow, nCol, pCell, pGrid);
	((CImpSetGrid*)pGrid)->GetParent()->SendMessage(WM_IMPSET_UPDATE, 0, 0);
}
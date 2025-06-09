#include "StdAfx.h"
#include "PdfXmlParseSets.h"
#include "PdfXmlData.h"

BOOL range_IsIntersect(float fMin, float fMax, float fDestMin, float fDestMax)
{
	if (fMin > fDestMax || fDestMin > fMax)
	{
		return FALSE;
	}

	//暂时确定为有交集
	//后续可以确定交集的大小为最小宽度，即包含
	return TRUE;
}


CPdfXmlStringRow::CPdfXmlStringRow()
{
	m_nCols = -1;
	m_fVpos = 0;
	m_fHeight = 0;
}

CPdfXmlStringRow::~CPdfXmlStringRow()
{

}


long CPdfXmlStringRow::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPdfParseXmlRWKeys *pXmlKeys = (CPdfParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strVposKey, oElement, m_fVpos);
	//xml_SetAttributeValue(pXmlKeys->m_strColsKey, oElement, m_fHeight);

	return 0;
}

long CPdfXmlStringRow::ValCmp(CBaseObject* pRightObj)
{
	float fVpos = ((CPdfXmlStringRow*)pRightObj)->m_fVpos;
	if(m_fVpos < fVpos)
		return -1;
	return 1;
}

long CPdfXmlStringRow::InitHeadRow()
{
	CPdfXmlData *p = NULL;
	POS pos = GetHeadPosition();
	long nCol = 0;

	while (pos != NULL)
	{
		p = (CPdfXmlData *)GetNext(pos);
		p->m_nCol = nCol;
		nCol++;
	}

	m_nCols = nCol;
	return nCol;
}

//分列后再合并列
void CPdfXmlStringRow::MergeCols(CPdfXmlStringRow *pHeadRow)
{
	POS pos = GetHeadPosition();
	CPdfXmlData *p = NULL, *pPev = NULL;
	pPev = (CPdfXmlData *)GetNext(pos);
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		p = (CPdfXmlData *)GetNext(pos);

		if (p->m_nCol == pPev->m_nCol)
		{
			//pPev->m_strName += p->m_strName;
			//pPev->m_fWidth = p->m_fHpos + p->m_fWidth - pPev->m_fHpos;
			pPev->AddColDataV(p);	//纵向合并
			DeleteAt(posPrev);
		}
		else
		{
			pPev = p;
		}
	}
}
//分行后合并列
void CPdfXmlStringRow::MergeCols_1()
{
	POS pos = GetHeadPosition();
	CPdfXmlData *p = NULL, *pPev = NULL;
	pPev = (CPdfXmlData *)GetNext(pos);
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		p = (CPdfXmlData *)GetNext(pos);
		if(range_IsIntersect(pPev->m_fHpos, pPev->m_fHpos2, p->m_fHpos, p->m_fHpos2))
		{
			pPev->AddColDataV(p);	//纵向合并
			DeleteAt(posPrev);
		}
		else
		{
			pPev = p;
		}
	}
}

//增加空的列
void CPdfXmlStringRow::AddEmptyCol(CPdfXmlStringRow *pHeadRow)
{
	POS pos = GetHeadPosition();
	CPdfXmlData *p = NULL, *pPev = NULL, *pNew = NULL, *pHeadCol = NULL;
	pPev = (CPdfXmlData *)GetNext(pos);
	POS posPrev = pos;
	long nColsAdd = 0;

	while (pos != NULL)
	{
		posPrev = pos;
		p = (CPdfXmlData *)GetNext(pos);
		nColsAdd = p->m_nCol - pPev->m_nCol - 1;

		if (nColsAdd > 0)
		{
			long k = 0;

			for (k=0; k<nColsAdd; k++)
			{
				pNew = new CPdfXmlData();
				pNew->m_nCol = pPev->m_nCol + k + 1;
				pHeadCol = (CPdfXmlData *)pHeadRow->GetAtIndex(pNew->m_nCol);
				pNew->m_fHpos = pHeadCol->m_fHpos;
				pNew->m_fWidth = pHeadCol->m_fWidth;
				pNew->m_fVpos = pPev->m_fVpos;
				pNew->m_fHeight = pPev->m_fHeight;
				InsertBefore(pos, pNew);
			}

			pPev = pNew;
		}
	}
}
void CPdfXmlStringRow::AddEmptyCol_1(CPdfXmlStringRow *pHeadRow)
{
	CPdfXmlData *p = NULL;

	int iStart = 0;
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		p = (CPdfXmlData *)GetNext(pos);
		AddEmptyCol_Data(iStart, p->m_nCol, p, pHeadRow, false);
		iStart = p->m_nCol + 1;
	}

	//添加后面列存在为空的情况
	AddEmptyCol_Data(iStart, m_nCols, p, pHeadRow, true);
}
void CPdfXmlStringRow::AddEmptyCol_Data(int iStart, int iCount, CPdfXmlData *pNext, CPdfXmlStringRow *pHeadRow, bool bAfter)
{
	CPdfXmlData *pNew = NULL;
	CPdfXmlData *pHeadCol = NULL;

	long k = 0;

	POS pos = Find(pNext);
	for (k=iStart; k<iCount; k++)
	{
		pNew = new CPdfXmlData();
		pNew->m_nCol = k;

		pHeadCol = (CPdfXmlData *)pHeadRow->GetAtIndex(pNew->m_nCol);
		pNew->m_fHpos = pHeadCol->m_fHpos;
		pNew->m_fWidth = pHeadCol->m_fWidth;
		pNew->m_fVpos = pNext->m_fVpos;
		pNew->m_fHeight = pNext->m_fHeight;

		if(!bAfter)
			InsertBefore(pos, pNew);
		else
			pos = InsertAfter(pos, pNew);
	}
}

void CPdfXmlStringRow::InitColIndex(CPdfXmlStringRow *pHeadRow)
{
	POS pos = pHeadRow->GetHeadPosition();
	CPdfXmlData *pHeadData = NULL;
	CPdfXmlData *pHeadPrev = NULL;
	CPdfXmlData *p = NULL;

	m_nCols = pHeadRow->m_nCols;

	int iPrevWith = 0;
	int iNowWith = 0;
	while (pos != NULL)
	{
		pHeadData = (CPdfXmlData *)pHeadRow->GetNext(pos);

		POS posCurr = GetHeadPosition();
		while (posCurr != NULL)
		{
			p = (CPdfXmlData *)GetNext(posCurr);
			
			if (range_IsIntersect(pHeadData->m_fHpos, pHeadData->m_fHpos2,
				 p->m_fHpos, p->m_fHpos2))
			{
				//已经划分所属列后，但又和后列又交集
				//p->m_fHpos2 > pHeadData->m_fHpos2 那必定属于此列
				if(p->m_bSetCol && pHeadPrev != NULL && p->m_fHpos2 < pHeadData->m_fHpos2)
				{
					iPrevWith = pHeadPrev->m_fHpos2 - p->m_fHpos;	//数据在前一列中所占宽度
					iNowWith = p->m_fHpos2 - pHeadPrev->m_fHpos;	//数据在本列中所占宽度
					if(iPrevWith > iNowWith)
						continue;
				}

				p->m_nCol = pHeadData->m_nCol;
				p->m_bSetCol = true;
			}
		}
		pHeadPrev = pHeadData;
	}
}
void CPdfXmlStringRow::InitColIndex_1(CPdfXmlStringRow *pHeadRow)
{
	POS pos = NULL;
	m_nCols = pHeadRow->m_nCols;

	CPdfXmlData *pHeadOneData = NULL;
	CPdfXmlData *pHeadTwoData = NULL;
	CPdfXmlData *p = NULL;

	POS posCurr = GetHeadPosition();
	while (posCurr != NULL)
	{
		p = (CPdfXmlData *)GetNext(posCurr);
		if(p->m_nCol == -1)
		{
			pos = pHeadRow->GetHeadPosition();
			pHeadOneData = (CPdfXmlData *)pHeadRow->GetNext(pos);
			if(p->m_fHpos2 < pHeadOneData->m_fHpos2)
			{
				p->m_nCol = pHeadOneData->m_nCol;//0
				continue;
			}

			while (pos != NULL)
			{
				pHeadTwoData = (CPdfXmlData *)pHeadRow->GetNext(pos);
				if(p->m_fHpos > pHeadOneData->m_fHpos2 && p->m_fHpos2 < pHeadTwoData->m_fHpos2)
				{
					p->m_nCol = pHeadTwoData->m_nCol;
					break;
				}
				pHeadOneData = pHeadTwoData;
			}
		}
	}
}
BOOL CPdfXmlStringRow::IsSameLine(CPdfXmlStringRow *pOneRow)
{
	if(pOneRow == NULL)
		return FALSE;
	if(pOneRow->GetCount() != GetCount())
		return FALSE;

	CString strOneData = "";
	CString strTwoData = "";
	for(int i=0; i<pOneRow->GetCount(); i++)
	{
		strOneData = ((CPdfXmlData*)pOneRow->GetAtIndex(i))->m_strName;
		strTwoData = ((CPdfXmlData*)GetAtIndex(i))->m_strName;
		if(strOneData != strTwoData)
		{
			return FALSE;
		}
	}

	return TRUE;
}
BOOL CPdfXmlStringRow::IsInvalidLine(CString strKey)
{
	vector<CString> oVecKey;
	SplitKey(&oVecKey, strKey, _T("&"));

	CPdfXmlData *pData = NULL;
	POS pos = NULL;
	vector<CString>::iterator attr;

	pos = GetHeadPosition();
	while (pos != NULL)
	{
		pData = (CPdfXmlData *)GetNext(pos);
		
		for(attr=oVecKey.begin(); attr!=oVecKey.end(); )
		{
			if(pData->m_strName.Find(*attr) != -1)
			{
				attr = oVecKey.erase(attr);
			}
			else
			{
				attr++;
			}
		}
	}

	if(oVecKey.size() <= 0)
		return TRUE;
	return FALSE;
}
void CPdfXmlStringRow::SplitKey(vector<CString> *pVecKey, const CString &strKey, const CString strSpace)
{
	CString strTemp, strValue;
	strValue = strKey;
	int p = strValue.Find(strSpace);
	if(p == -1)
	{
		pVecKey->push_back(strValue);
		return ;
	}

	int iSpLen = strSpace.GetLength();
	while(p != -1)
	{
		strTemp = strValue.Left(p);
		pVecKey->push_back(strTemp);
		strValue = strValue.Right(strValue.GetLength() - p - iSpLen);
		p = strValue.Find(strSpace);
	}
	if(strValue != _T(""))
		pVecKey->push_back(strValue);
}

BOOL CPdfXmlStringRow::IsLineData(CPdfXmlData *pData)
{
	CPdfXmlData *p = NULL;
	POS pos = NULL;

	pos = GetHeadPosition();
	while (pos != NULL)
	{
		p = (CPdfXmlData *)GetNext(pos);

		//与行中任一数据横向有交集，但纵向没交集，则认为不是本行数据
		if(range_IsIntersect(pData->m_fHpos, pData->m_fHpos2, p->m_fHpos, p->m_fHpos2)
			&& !range_IsIntersect(pData->m_fVpos, pData->m_fVpos2, p->m_fVpos, p->m_fVpos2))
		{
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CPdfXmlStringRow::AddSameLineData(CPdfXmlData *pData)
{
	CPdfXmlData *p = NULL;
	CPdfXmlData *pAdd = NULL;

	POS pos = NULL;

	int iMergeCount = 0;
	pos = GetHeadPosition();
	while (pos != NULL)
	{
		p = (CPdfXmlData *)GetNext(pos);

		//与行中任一数据横向有交集
		if(range_IsIntersect(pData->m_fHpos, pData->m_fHpos2, p->m_fHpos, p->m_fHpos2))
		{
			iMergeCount++;	
			if(iMergeCount > 1)		//只要包含多个交集列就不合并
			{
				return FALSE;
			}

			//起点或中心点相差小于0.5,
			if((fabs(pData->m_fHpos - p->m_fHpos) < 0.5 || fabs((pData->m_fHpos+pData->m_fWidth/2) - (p->m_fHpos+p->m_fWidth/2)) < 0.5))
			{
				pAdd = p;
			}
		}
	}

	if(iMergeCount == 1 && pAdd != NULL)
	{
		pAdd->AddColDataV(pData);	//纵向合并
		return TRUE;
	}
	
	return FALSE;
}
BOOL CPdfXmlStringRow::IsHeadRowLeft(CPdfXmlStringRow *pRow)
{
	int iCol = this->GetCount();

	CPdfXmlData *pHeadOne = NULL;
	CPdfXmlData *pDataCol = NULL;
	for(int i=0; i<iCol; i++)
	{		
		pHeadOne = (CPdfXmlData *)GetAt(i);
		pDataCol = (CPdfXmlData *)pRow->GetAt(i);
		if(pDataCol == NULL)
			continue;

		//只有首行居中或靠右才会比同列起点大，除非所有数据靠右
		if(pHeadOne->m_fHpos > pDataCol->m_fHpos+2)	
		{
			return FALSE;
		}
	}
	return TRUE;
}
void CPdfXmlStringRow::ReSetRowRang(CPdfXmlStringRow *pRow)
{
	int iCol = this->GetCount();
	CPdfXmlData *pColHead = (CPdfXmlData *)GetHead();
	CPdfXmlData *pColTail = (CPdfXmlData *)GetTail();
	pColHead->m_fHpos = 0;
	pColTail->m_fHpos2 += 500;

	CPdfXmlData *pHeadTwo = NULL;
	CPdfXmlData *pDataCol = NULL;

	int iMinH = 1000;
	int iMaxH = 0;
	for(int i=0; i<iCol; i++)
	{		
		pDataCol = (CPdfXmlData *)GetAt(i);	//数据列号只会比首列列号等或大
		if(pDataCol == NULL)
			continue;

		pHeadTwo = NULL;
		pHeadTwo = (CPdfXmlData *)GetAt(i);

		//与此列有交集比为同一列，直接设置列头范围
		if(range_IsIntersect(pDataCol->m_fHpos, pDataCol->m_fHpos2, pHeadTwo->m_fHpos, pHeadTwo->m_fHpos2))
		{
			if(pDataCol->m_fHpos < pHeadTwo->m_fHpos)
				pHeadTwo->m_fHpos = pDataCol->m_fHpos;
			if(pDataCol->m_fHpos2 > pHeadTwo->m_fHpos2)
				pHeadTwo->m_fHpos2 = pDataCol->m_fHpos2;
			continue;
		}

		//数据列起点比首列起点小
		if(pDataCol->m_fHpos < pHeadTwo->m_fHpos)
		{
			if(pDataCol->m_fHpos < pHeadTwo->m_fHpos)
				pHeadTwo->m_fHpos = pDataCol->m_fHpos;
			if(pDataCol->m_fHpos2 > pHeadTwo->m_fHpos2)
				pHeadTwo->m_fHpos2 = pDataCol->m_fHpos2;
			continue;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//CPdfXmlStringTable
CPdfXmlStringTable::CPdfXmlStringTable()
{
	m_nCols = 0;

	CString m_strIdentify = _T("");
	CString m_strIndetName = _T("");

	m_iNameHeadCol = -1;
	m_iDWHeadCol = -1;
	m_iValueHeadCol = -1;

	m_AddTile = false;
}

CPdfXmlStringTable::~CPdfXmlStringTable()
{

}

long CPdfXmlStringTable::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPdfParseXmlRWKeys *pXmlKeys = (CPdfParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strColsKey, oElement, m_nCols);

	return 0;
}

void CPdfXmlStringTable::ParseTable()
{
	CPdfXmlStringRow *pRow, *pHeadRow = NULL;
	POS pos = GetHeadPosition();

	if(pos == NULL)
		return ;

	ProssHeadRow();

	//////////////////////////////////////////////////////////////////////////
	//李俊庆算法
	//跳过标题列的分列
	pHeadRow = (CPdfXmlStringRow *)GetNext(pos);
	if(pHeadRow == NULL)
		return ;
	pHeadRow->InitHeadRow();  //2023-7-19 lijunqing 初始化标题行的列

	while (pos != NULL)
	{
		pRow = (CPdfXmlStringRow *)GetNext(pos);

		pRow->InitColIndex(pHeadRow);		//初始化行中各列编号
		pRow->InitColIndex_1(pHeadRow);

		pRow->MergeCols(pHeadRow);		
		pRow->AddEmptyCol_1(pHeadRow);
	}
}

//重新整理第一行：将最多行数的列数作为列数，并修改第一行位置信息
void CPdfXmlStringTable::ProssHeadRow()
{
	CPdfXmlStringRow *pRow, *pHeadRow, *pAddHRow = NULL;
	POS pos = NULL;

	pHeadRow = (CPdfXmlStringRow *)GetHead();
	m_nCols = pHeadRow->GetCount();

	if(m_nCols <= 3 && m_iNameHeadCol == -1)	//列数小于4且没有表头时，取最大列数
	{
		int iMaxCols = 0;
		pos = GetHeadPosition();
		while (pos != NULL)
		{
			pRow = (CPdfXmlStringRow *)GetNext(pos);
			if(iMaxCols < pRow->GetCount())
			{
				iMaxCols = pRow->GetCount();	
				pHeadRow = pRow;
			}
		}

		if(iMaxCols > m_nCols)	//首行列数小于3且不是最大列数
		{
			pAddHRow = (CPdfXmlStringRow *)GetHead();
			pAddHRow->AddEmptyCol_Data(m_nCols, iMaxCols, (CPdfXmlData *)pAddHRow->GetTail(), pHeadRow, true);
			m_nCols = iMaxCols;			
		}		
	}

	if(IsHeadRowLeft())	//列表头靠左
	{
		CPdfXmlData *pColOne = NULL;
		CPdfXmlData *pColTwo = NULL;

		pos = pHeadRow->GetHeadPosition();
		while (pos != NULL)
		{
			pColTwo = (CPdfXmlData *)pHeadRow->GetNext(pos);	
			if(pColOne != NULL)
			{
				pColOne->m_fHpos2 = pColTwo->m_fHpos - 1;
			}
			pColOne = pColTwo;
		}
		pColTwo->m_fHpos2 += 500;
	}
	else
	{
		//重新修订列表头的范围
		pHeadRow = (CPdfXmlStringRow *)GetHead();
		pos = GetHeadPosition();
		while (pos != NULL)
		{
			pRow = (CPdfXmlStringRow *)GetNext(pos);
			//if(m_nCols == pRow->GetCount())
			{
				pHeadRow->ReSetRowRang(pRow);
			}		
		}
	}
}
BOOL CPdfXmlStringTable::IsHeadRowLeft()
{
	CPdfXmlStringRow *pRow, *pHeadRow, *pAddHRow = NULL;
	POS pos = GetHeadPosition();
	pHeadRow = (CPdfXmlStringRow *)GetNext(pos);
	while (pos != NULL)
	{
		pRow = (CPdfXmlStringRow *)GetNext(pos);
		if(!pHeadRow->IsHeadRowLeft(pRow))
		{
			return FALSE;
		}		
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//CPdfXmlStringTables
CPdfXmlStringTables::CPdfXmlStringTables()
{
	
}

CPdfXmlStringTables::~CPdfXmlStringTables()
{

}

//////////////////////////////////////////////////////////////////////////
//CPdfXmlStringTableParse
CPdfXmlStringTableParse::CPdfXmlStringTableParse()
{
	m_LastRow = NULL;
}

CPdfXmlStringTableParse::~CPdfXmlStringTableParse()
{

}

void CPdfXmlStringTableParse::InitRows(CExBaseList *pStringList)
{
	POS pos = pStringList->GetHeadPosition();
	CPdfXmlData *p = NULL;

	while (pos != NULL)
	{
		p = (CPdfXmlData *)pStringList->GetNext(pos);

		if(AddToRow(p))
		{	//从原list中转移到行中后，清除原list中记录
			pStringList->Remove(p);
		}
	}

	//删除固定无效行
	DelTilteRows();

	//删除配置中剔除标题
	DelTilteName();

	//删除配置中剔除数据行
	DelRowName();

	//对行中数据排序
	pos = GetHeadPosition();
	CPdfXmlStringRow *pTwoRow = NULL;
	while (pos != NULL)
	{
		pTwoRow = (CPdfXmlStringRow*)GetNext(pos);
		pTwoRow->Sort(0, true);	//只按Hpos排序
	}

	//排序
	Sort(true);

	//删除内容重复行，表格处于分页时会产生两条内容相同，位置信息不同的数据
	DelSameLine();

	//删除重复表名数据及表头
	DelSameTable();
	Debug_SaveRowsFile();

	//合并行数据
	MergeRows();

	//合并列数据
	MergeCols();
}

void CPdfXmlStringTableParse::DelTilteRows()
{
	CString strHead;
	CString strTail;

	POS pos = GetHeadPosition();
	CPdfXmlStringRow *pTwoRow = NULL;
	while (pos != NULL)
	{
		pTwoRow = (CPdfXmlStringRow*)GetNext(pos);
		if(pTwoRow->GetCount() == 1)	//清除无效标题头
		{
			strTail = strHead = pTwoRow->GetHead()->m_strName;
			strTail.Replace(_T("日"), _T(""));	//日2209024
			strTail.Replace(_T(" "), _T(""));
			if(IsStringNumber(strTail))	//删除纯数字表头
			{
				Delete(pTwoRow);
			}
			else if(strHead.Find(_T("注")) != -1)	
			{
				Delete(pTwoRow);
			}
			else if(strHead.Find(_T("第")) != -1 && strHead.Find(_T("页")) != -1
				&& strHead.Find(_T("共")) != -1)	
			{
				Delete(pTwoRow);
			}
		}	
	}
}

//删除无效标题行标题
void CPdfXmlStringTableParse::DelTilteName()
{
	CDataType *pDataType = m_pPdfConfig->GetDelRowTilte();
	if(pDataType == NULL)
		return ;

	CDataTypeValue* pDataV = NULL;
	POS pos = pDataType->GetHeadPosition();
	while (pos != NULL)
	{
		pDataV = (CDataTypeValue *)pDataType->GetNext(pos);
		DelTilteRows(pDataV->m_strName);
	}
}
void CPdfXmlStringTableParse::DelTilteRows(CString strTile)
{
	CString strHead;
	POS pos = GetHeadPosition();
	CPdfXmlStringRow *pTwoRow = NULL;
	while (pos != NULL)
	{
		pTwoRow = (CPdfXmlStringRow*)GetNext(pos);
		if(pTwoRow->GetCount() == 1)	//清除无效标题头
		{
			strHead =  pTwoRow->GetHead()->m_strName;
			if(strHead == strTile)
			{
				Delete(pTwoRow);
			}
		}	
	}
}

//删除无效行
void CPdfXmlStringTableParse::DelRowName()
{
	CDataType *pDataType = m_pPdfConfig->GetDelRowData();
	if(pDataType == NULL)
		return ;

	CDataTypeValue* pDataV = NULL;
	POS pos = pDataType->GetHeadPosition();
	while (pos != NULL)
	{
		pDataV = (CDataTypeValue *)pDataType->GetNext(pos);
		DelDataRows(pDataV->m_strName);
	}
}
void CPdfXmlStringTableParse::DelDataRows(CString strTile)
{
	CString strHead;
	POS pos = GetHeadPosition();
	CPdfXmlStringRow *pTwoRow = NULL;
	while (pos != NULL)
	{
		pTwoRow = (CPdfXmlStringRow*)GetNext(pos);
		if(pTwoRow->IsInvalidLine(strTile))
		{
			Delete(pTwoRow);
		}
	}
}

void CPdfXmlStringTableParse::ParseTableData()
{
	//将各行都调整到表格中
	AdjRowsToTables();

	POS pos = m_listTable.GetHeadPosition();
	CPdfXmlStringTable *pTable = NULL;
	CPdfXmlStringRow *pRowHead = NULL;

	while (pos != NULL)
	{
		pTable = (CPdfXmlStringTable *)m_listTable.GetNext(pos);
		if(pTable->GetCount() <= 0)	//删掉没有数据的表
		{
			m_listTable.Delete(pTable);
		}
		else
		{
			pRowHead = (CPdfXmlStringRow *)pTable->GetHead();
			pTable->m_iNameHeadCol = IsHeadRowCheck(pRowHead);		//先查找名称列，找到认为有列表头
			pTable->ParseTable();
		}
	}
}

//将各行都调整到表格中
void CPdfXmlStringTableParse::AdjRowsToTables()
{
	POS pos = GetHeadPosition();
	CPdfXmlStringRow *pRow = NULL;
	CPdfXmlStringTable *pTable = NULL;
	CString strTableName = _T("");

	while (pos != NULL)
	{
		pRow = (CPdfXmlStringRow *)GetNext(pos);

		if (pRow->GetCount() == 1 || pTable == NULL) //只有一列，认为是表格的起始：标题
		{
			strTableName = pRow->GetHead()->m_strName;
			pTable = new CPdfXmlStringTable();
			m_listTable.AddTail(pTable);
			pTable->m_strName = strTableName;

			//虽然后面调用RemoveAll清除链表，
			//delete pRow; 
			this->Delete(pRow); //删除单独的行，数据整理完毕之后，所有的数据行都列入新的表格对象中，最后在RemoveAll
		}
		else
		{
			pTable->AddTail(pRow);
		}
	}

	//数据整理完毕之后，所有的数据行都列入新的表格对象中，最后在RemoveAll
	RemoveAll();
}

BOOL CPdfXmlStringTableParse::AddToRow(CPdfXmlData *pData)
{
	CPdfXmlStringRow *pRow = FindRow(pData);

	if (pRow == NULL)
	{
		//新行数据时，先判断和上一个数据的关系，因为第一列合并了多行，导致可能存在后面列找不到归属而新建了行
		if(m_LastRow != NULL)
		{
			CPdfXmlData *pTailData = (CPdfXmlData *)m_LastRow->GetTail();
			if(pTailData != NULL)
			{
				if (range_IsIntersect(pData->m_fVpos, pData->m_fVpos2, pTailData->m_fVpos, pTailData->m_fVpos2))
				{
					m_LastRow->AddTail(pData);
					return TRUE;
				}
			}
		}

		pRow = new CPdfXmlStringRow();
		pRow->m_fVpos = pData->m_fVpos;
		pRow->m_fHeight = pData->m_fHeight;
		AddTail(pRow);
	}

	pRow->AddTail(pData);
	m_LastRow = pRow;	//以此来记录上一个单元格所在行
	return TRUE;
}

CPdfXmlStringRow * CPdfXmlStringTableParse::FindRow(CPdfXmlData *pData)
{
	//在判断是否新行
	CPdfXmlStringRow *pRow = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pRow = (CPdfXmlStringRow *)GetNext(pos);

		//此方法使用时，原始数据处理时需把分页的高度添加到数据中
		if (range_IsIntersect(pData->m_fVpos, pData->m_fVpos2, pRow->m_fVpos, pRow->m_fVpos+pRow->m_fHeight))
		{
			//第一列合并了多行，导致某一行在两行的中间
			if(pRow->IsLineData(pData))
				continue;
			return pRow;
		}
	}

	return NULL;
}

void CPdfXmlStringTableParse::DelSameLine()
{
	POS pos = GetHeadPosition();
	CPdfXmlStringRow *pOneRow = NULL;
	CPdfXmlStringRow *pTwoRow = NULL;

	while (pos != NULL)
	{
		pTwoRow = (CPdfXmlStringRow*)GetNext(pos);
		if(pTwoRow->IsSameLine(pOneRow))
		{
			Delete(pTwoRow);
			continue;
		}	

		pOneRow = pTwoRow;
	}
}

//删除连续两个同名的表的名称行和表头行（表头行存在不止一行）
void CPdfXmlStringTableParse::DelSameTable()
{
	vector<CString> vecTableName;
	vector<CString>::iterator attr;

	POS pos = GetHeadPosition();
	CPdfXmlStringRow *pRow = NULL;
	CPdfXmlStringRow *pRowHead = NULL;
	CPdfXmlStringTable *pTable = NULL;

	CString strTableName = _T("");	

	bool bDelHead = false;
	while (pos != NULL)
	{
		pRow = (CPdfXmlStringRow *)GetNext(pos);
		if (pRow->GetCount() == 1) //只有一列，认为是表格的起始：标题
		{
			bDelHead = false;
			strTableName = pRow->GetHead()->m_strName;
			for(attr=vecTableName.begin(); attr!=vecTableName.end(); attr++)
			{
				if(strTableName == *attr)
				{
					bDelHead = true;
					break;
				}
			}

			if(bDelHead && pos != NULL)
			{
				pRowHead = (CPdfXmlStringRow *)GetNext(pos);
				if(pRowHead != NULL && IsHeadRowCheck(pRowHead) != -1)	//有表头才算是重名
				{
					this->Delete(pRow);	//删除表名行
					this->Delete(pRowHead); //删除表头行
					bDelHead = false;
				}
			}
			else
			{
				vecTableName.push_back(strTableName);
			}
		}
	}
}
int CPdfXmlStringTableParse::IsHeadRowCheck(CPdfXmlStringRow *pHeadRow)
{
	CPdfXmlData *pStringData = NULL;
	POS pos = pHeadRow->GetHeadPosition();

	int iCol = 0;
	while (pos != NULL)
	{
		pStringData = (CPdfXmlData *)pHeadRow->GetNext(pos);
		if(m_pPdfConfig->IsCheckHead(HEAD_NAME_COL, pStringData->m_strName))
		{
			return iCol;
		}
		iCol++;
	}
	return -1;
}

void CPdfXmlStringTableParse::MergeRows()
{
	POS posXml = NULL;
	POS pos = GetHeadPosition();

	CPdfXmlStringRow *pOneRow = (CPdfXmlStringRow *)GetNext(pos);
	CPdfXmlStringRow *pTwoRow = NULL;

	CPdfXmlData *pDelData = NULL;
	CPdfXmlData *pAddData = NULL;
	CString strTile = "";
	CString strKey = "";
	while (pos != NULL)
	{
		pTwoRow = (CPdfXmlStringRow*)GetNext(pos);
		if(pTwoRow->GetCount() == 1 && pOneRow != NULL)
		{
			pDelData = (CPdfXmlData*)pTwoRow->GetHead();
			strTile = pDelData->m_strName;
			if(!m_pPdfConfig->IsDatasetTitle(strTile, strKey))	//不是表头
			{
				if(pOneRow->AddSameLineData(pDelData))
				{
					Delete(pTwoRow);
					continue;
				}
			}
		}	

		pOneRow = pTwoRow;
	}
}
void CPdfXmlStringTableParse::MergeCols()
{
	POS posXml = NULL;
	POS pos = GetHeadPosition();

	CPdfXmlStringRow *pOneRow = NULL;
	while (pos != NULL)
	{
		pOneRow = (CPdfXmlStringRow*)GetNext(pos);
		pOneRow->MergeCols_1();	
	}
}

void CPdfXmlStringTableParse::Debug_SaveRowsFile()
{
	CString strFile = _P_GetDBPath();
	strFile += _T("Debug_RowsFile.xml");
	SaveXmlFile(strFile, CPdfParseXmlRWKeys::g_pXmlKeys);
}

void CPdfXmlStringTableParse::Debug_SaveTablesFile()
{
	CString strFile = _P_GetDBPath();
	strFile += _T("Debug_TablesFile.xml");
	m_listTable.SaveXmlFile(strFile, CPdfParseXmlRWKeys::g_pXmlKeys);
}

//////////////////////////////////////////////////////////////////////////
//CPdfXmlParseSets
CPdfXmlParseSets::CPdfXmlParseSets(void)
{
	m_pManualFrm = NULL;
}

CPdfXmlParseSets::~CPdfXmlParseSets(void)
{
}

void CPdfXmlParseSets::InitKeys()
{
	AddDatasetTitle(SETS_TITLE_ID_PARAMETER);
	AddDatasetTitle(SETS_TITLE_ID_SETTING);
	AddDatasetTitle(SETS_TITLE_ID_ENA);
	//AddDatasetTitle(SETS_TITLE_ID_CTRL);
	//AddDatasetTitle(SETS_TITLE_ID_PROT);
	//AddDatasetTitle(SETS_TITLE_ID_SETTING2);
	//AddDatasetTitle(SETS_TITLE_ID_MATRIX);

	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("PdfConfig.xml");

	m_oPdfConfig.LoadPdfConfig(strXMLPath);

	OpenKeyTextFile(_T("PdfToSetsKey.txt"));
	OpenInvalidKeyTextFile(_T("PdfToSetsInvalidKey.txt"));
	OpenFormatKeyTextFile(_T("PdfToSetsFormatKey.txt"));
	OpenMergeKeyTextFile(_T("PdfToSetsMergeKey.txt"));
}
BOOL CPdfXmlParseSets::IsWow64()
{
	typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process;
	BOOL bIsWow64 = FALSE;
	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(_T("kernel32")),
		"IsWow64Process");
	if(NULL != fnIsWow64Process)
	{
		fnIsWow64Process(GetCurrentProcess(), &bIsWow64);
	}
	return bIsWow64;
}
BOOL CPdfXmlParseSets::ParsePdfFile(const CString &strFile, BOOL bSaveTxtFile)
{
	InitKeys();

	int p = strFile.ReverseFind('\\');
	CString strPdfFileName = strFile.Right(strFile.GetLength() - p - 1);

	CString PdfDBUnknownTable;
	PdfDBUnknownTable = _P_GetConfigPath();
	PdfDBUnknownTable += _T("PdfDBUnknownTable.xml");
	m_PdfDBInfos.OpenXmlFile(PdfDBUnknownTable,CPdfHLParseXmlRWKeys::g_pXmlKeys);
	m_PdfDBInfo = (CPdfDBTable *)m_PdfDBInfos.FindByID(strPdfFileName);

	if(m_PdfDBInfo == NULL)
	{
		m_PdfDBInfo = new CPdfDBTable;
		m_PdfDBInfos.AddNewChild(m_PdfDBInfo);
		m_PdfDBInfo->m_strName = m_PdfDBInfo->m_strID = strPdfFileName;
	}

	
	//PDF转xml
	CString strExePath = _P_GetBinPath();
	if(IsWow64()) //20231016 luozibing 判断当前系统位数
	{
		strExePath += _T("pdfalto64\\");
	}
	else
	{
		strExePath += _T("pdfalto32\\");
	}
	

	CString strExe = strExePath + _T("pdfalto.exe"); 
	CString strTempPath = strExePath + _T("PdfTemp\\");
	{
		//20231023 huangliang 金建反馈部分电脑无法整个文件夹删除,所以先删除文件，再删除文件夹
		SetFileAttributes(strTempPath + _T("123456789.pdf"),FILE_ATTRIBUTE_NORMAL);		//20231024 luozibing 不能删除只读文件,将pdf将只读属性去掉
		X_DeleteFile(strTempPath + _T("123456789.pdf"));
		X_DeleteFile(strTempPath + _T("123456789.xml"));
		X_DeleteFile(strTempPath + _T("123456789_metadata.xml"));
		DeleteAllFiles(strTempPath + _T("123456789.xml_data"), _T("svg"));
	DeleteAllDirectorys(strTempPath);
	}

	//20231017 huangliang 文件名称太长，pdfalto.exe无法工作
	//CString strXmlFile = strTempPath + strPdfFileName;
	CString strXmlFile = strTempPath + _T("123456789.pdf");
	CreateAllDirectories(strTempPath);
	X_CopyFile(strFile, strXmlFile, FALSE);

	{
		SHELLEXECUTEINFO ShExecInfo = {0};
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = NULL;
		ShExecInfo.lpVerb = NULL;
		ShExecInfo.lpFile = strExe;
		ShExecInfo.lpParameters = strXmlFile;
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_HIDE;
		ShExecInfo.hInstApp = NULL;
		ShellExecuteEx(&ShExecInfo);
		WaitForSingleObject(ShExecInfo.hProcess,INFINITE);//此句等待，str 为程序的完整路径名
	}

	//读取xml
	strXmlFile.Replace(_T(".pdf"), _T(".xml"));
	CReadXmlData readXmlData;
	if(!readXmlData.OpenXmlFile(strXmlFile))
	{
		CString tmp;
		tmp.Format(_T("无法读取%s"),strXmlFile);
		::MessageBox(NULL, tmp, _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	CPdfStringDatas oStringDataList;	
	readXmlData.FindAllTextLine(&oStringDataList);

	//处理xml数据
	ParseLineData(&oStringDataList);

	oStringDataList.DeleteAll();

	m_PdfDBInfos.SaveXmlFile(PdfDBUnknownTable,CPdfHLParseXmlRWKeys::g_pXmlKeys);
	return TRUE;
}

//把所有数据分配到各行
void CPdfXmlParseSets::ParseLineData(CExBaseList* pStringList)
{
	//对单元格数据排序，先按行再按列
	pStringList->Sort(true);

	//初始化行数据
	m_oPdfTable.m_pPdfConfig = &m_oPdfConfig;
	m_oPdfTable.InitRows(pStringList);
	m_oPdfTable.Debug_SaveRowsFile();

	m_oPdfTable.ParseTableData();
	m_oPdfTable.Debug_SaveTablesFile();

	//设置表属性及列信息，自动识别数据，提示用户判断
	SetTableIdentify();

	//Table数据写入Device中
	ParseInDestLogicDevice();

	CString strFile = _P_GetDBPath();
	strFile += _T("Debug_Dvm.xml");
	m_pDestLogicDevice->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CPdfXmlParseSets::SetTableIdentify()
{
	CExBaseList oTableList;
	CExBaseList *plistTable = m_oPdfTable.GetAllTable();

	CPdfXmlStringTable* pXmlTable = NULL;
	CPdfXmlStringRow *pXmlRow = NULL;

	POS pos = plistTable->GetHeadPosition();
	plistTable->GetNext(pos);	//头表不加入分类

	while (pos != NULL)
	{
		pXmlTable = (CPdfXmlStringTable *)plistTable->GetNext(pos);
		pXmlRow = (CPdfXmlStringRow* )pXmlTable->GetHead();

		if(!CheckTableIdentify(pXmlTable))		
		{
			pXmlTable->m_strName += _T(" *");
			if(pXmlRow != NULL && pXmlRow->GetCount() < 30)	//列数大于30的表去掉
				oTableList.AddTail(pXmlTable);
		}		
		
		if(pXmlRow != NULL)
		{
			pXmlTable->m_iNameHeadCol = ParseTableNameHead(pXmlRow);
			pXmlTable->m_iDWHeadCol = ParseTableDWHead(pXmlRow);
			pXmlTable->m_iValueHeadCol = ParseTableValueHead(pXmlRow);
			if(pXmlTable->m_iNameHeadCol == -1)
			{
				QueTableHead(pXmlTable);
			}
		}

		if(pXmlTable->m_iNameHeadCol == -1 && NO_USE_TABLE != pXmlTable->m_strIdentify)
		{
			if(pXmlTable->m_strName.Find(_T(" *")) == -1)
			{
				pXmlTable->m_strName += _T(" *");

				if(pXmlRow != NULL && pXmlRow->GetCount() < 30)	//列数大于30的表去掉
					oTableList.AddTail(pXmlTable);
			}
		}
	}

	if(oTableList.GetCount() > 0)	//弹出确认框
	{
		//20240312 huangliang 显示对话框
		//SelTable tmpDlg;
		//tmpDlg.m_pPdfDBInfo = m_PdfDBInfo;
		//tmpDlg.m_plistTable = &oTableList;
		//tmpDlg.DoModal();
		if(m_pManualFrm != NULL)
		{
			m_pManualFrm->m_pPdfDBInfo = m_PdfDBInfo;
			m_pManualFrm->m_plistTable = &oTableList;
			m_pManualFrm->ShowManualConfirm();
		}
	}
	oTableList.RemoveAll();
}
BOOL CPdfXmlParseSets::CheckTableIdentify(CPdfXmlStringTable* pXmlTable)
{
	//存储了表的属性则直接使用
	if(!m_bCorrect)	//修正时，不使用数据库
	{
		CPdfDBHead *tmp_Head = (CPdfDBHead *)m_PdfDBInfo->FindByID(pXmlTable->m_strName);
		if(tmp_Head != NULL)
		{
			set_table_identify(pXmlTable, tmp_Head->m_strName);
			return TRUE;
		}
	}

	CString strKey = "";
	if(!m_oPdfConfig.IsDatasetTitle(pXmlTable->m_strName, strKey))
	{
		return FALSE;
	}

	set_table_identify(pXmlTable, strKey);
	return TRUE;
}
void CPdfXmlParseSets::QueTableHead(CPdfXmlStringTable* pXmlTable)
{
	if(m_bCorrect)//修正时，不使用数据库
		return ;

	CPdfDBHead *tmp_Head = (CPdfDBHead *)m_PdfDBInfo->FindByID(pXmlTable->m_strName);
	if(tmp_Head == NULL)
	{
		return ;
	}

	pXmlTable->m_iNameHeadCol = tmp_Head->m_nNameHead;
	pXmlTable->m_iDWHeadCol = tmp_Head->m_nDWHead;
	pXmlTable->m_iValueHeadCol = tmp_Head->m_nValueHead;

	//表格没有表头，按配置添加空表头
	if(tmp_Head->m_nExistHead == 1)	
	{
		CPdfXmlStringRow *pXmlTileRow = new CPdfXmlStringRow;
		pXmlTable->AddHead(pXmlTileRow);
	}
}

//xml数据写入Device中
void CPdfXmlParseSets::ParseInDestLogicDevice()
{
	CExBaseList *plistTable = m_oPdfTable.GetAllTable();

	bool bHeadPross = false;
	CPdfXmlStringTable* pXmlTable = NULL;
	POS pos = plistTable->GetHeadPosition();
	while (pos != NULL)
	{
		pXmlTable = (CPdfXmlStringTable *)plistTable->GetNext(pos);
		
		if(!bHeadPross)	//默认表头仅在第一个数据表中
		{	
			bHeadPross = true;
			ParseTableHead(pXmlTable);
		}
		else	//处理其他表格数据
		{
			ParseTableInDestLogicDevice(pXmlTable);
		}
	}
}

//处理表头数据
void CPdfXmlParseSets::ParseTableHead(CPdfXmlStringTable* pXmlTable)
{
	m_pCurrDataset = new CDvmDataset();
	m_pCurrDataset->m_strName = _T("Attrs");
	m_pDestLogicDevice->AddNewChild(m_pCurrDataset);

	CPdfXmlStringRow* pXmlRow = NULL;
	POS pos = pXmlTable->GetHeadPosition();
	while (pos != NULL)
	{
		pXmlRow = (CPdfXmlStringRow *)pXmlTable->GetNext(pos);
		ParseTableHeadRow(pXmlRow);
	}
}
void CPdfXmlParseSets::ParseTableHeadRow(CExBaseList* listXmlRow)
{
	int nIndex = 0;
	CPdfXmlData *pStringData = NULL;
	POS pos = listXmlRow->GetHeadPosition();
	while (pos != NULL)
	{
		pStringData = (CPdfXmlData *)listXmlRow->GetNext(pos);

		if (IsKey(pStringData->m_strName))
		{
			nIndex++;
		}
		else if(nIndex > 0)		//取Key值后面的一个数据
		{
			nIndex = 0;
			CDvmData *pData = new CDvmData();
			pData->m_strName = pStringData->m_strName;
			m_pCurrDataset->AddNewChild(pData);
		}
	}
}

//处理各数据表
void CPdfXmlParseSets::ParseTableInDestLogicDevice(CPdfXmlStringTable* pXmlTable)
{
	CString strKey = pXmlTable->m_strIndetName;
	if(NO_USE_TABLE == strKey)
		return ;

	m_pCurrDataset = (CDvmDataset *)m_pDestLogicDevice->FindByName(strKey);
	if (m_pCurrDataset == NULL)
	{
		m_pCurrDataset = new CDvmDataset();
		m_pCurrDataset->m_strName = strKey;
		m_pCurrDataset->m_strID = strKey;
		m_pDestLogicDevice->AddNewChild(m_pCurrDataset);
	}

	ParseTableColData(pXmlTable);
}

int CPdfXmlParseSets::ParseTableNameHead(CPdfXmlStringRow* listXmlRow)
{
	return ParseTableColHead(listXmlRow, HEAD_NAME_COL);
}
int CPdfXmlParseSets::ParseTableDWHead(CPdfXmlStringRow* listXmlRow)
{
	return ParseTableColHead(listXmlRow, HEAD_DW_COL);
}
int CPdfXmlParseSets::ParseTableValueHead(CPdfXmlStringRow* listXmlRow)
{
	return ParseTableColHead(listXmlRow, HEAD_VALUE_COL);
}
int CPdfXmlParseSets::ParseTableColHead(CPdfXmlStringRow* listXmlRow, const CString &strKey)
{
	CPdfXmlData *pStringData = NULL;
	POS pos = listXmlRow->GetHeadPosition();
	while (pos != NULL)
	{
		pStringData = (CPdfXmlData *)listXmlRow->GetNext(pos);
		if(m_oPdfConfig.IsCheckHead(strKey, pStringData->m_strName))
		{
			return pStringData->m_nCol;
		}
	}
	return -1;
}
void CPdfXmlParseSets::ParseTableColData(CPdfXmlStringTable* pXmlTable)
{
	//记录配置中各列的顺序编号，主要记录名称、单位、现定值
	int iHeadNameCol = pXmlTable->m_iNameHeadCol;
	int iDWCol = pXmlTable->m_iDWHeadCol;
	int iValueCol = pXmlTable->m_iValueHeadCol;

	if(iHeadNameCol < 0)
	{
		return ;
	}

	CString strName, strDW, strValue, strTempV, strTdw = _T("");
	POS posCol = NULL;

	CPdfXmlStringRow *pXmlRow = NULL;
	CPdfXmlData* pXmlData = NULL;
	POS pos = pXmlTable->GetHeadPosition();
	pXmlTable->GetNext(pos);
	while (pos != NULL)
	{
		pXmlRow = (CPdfXmlStringRow *)pXmlTable->GetNext(pos);
		if(pXmlRow != NULL)
		{
			strName = strDW = strValue = _T("");
			posCol = pXmlRow->GetHeadPosition();
			while (posCol != NULL)
			{
				pXmlData = (CPdfXmlData *)pXmlRow->GetNext(posCol);
				if(pXmlData->m_nCol == iHeadNameCol)
					strName = pXmlData->m_strName;
				else if(pXmlData->m_nCol == iDWCol)
					strDW = pXmlData->m_strName;
				else if(pXmlData->m_nCol == iValueCol)
					strValue = pXmlData->m_strName;
			}

			if(strName == _T(",") || strName == _T("，") || strName == _T(""))
				continue;
			strValue.Replace(_T(" "), _T(""));
			strName.Replace(_T(":"), _T(""));
			strName.Replace(_T("："), _T(""));

			//保护定值（除跳闸矩阵）为纯数字，去掉后面的单位
			if(pXmlTable->m_strIdentify == TALBE_TYPE_SETTING)
			{
				strTdw = _T("");
				strTempV = strValue;
				while(strTempV.GetLength() > 0)
				{
					if(IsStringNumber(strTempV))
						break;
					strTempV = strTempV.Left(strTempV.GetLength() -1);
					strTdw = strTempV.Right(1) + strTdw;
				}
				if(strTempV != _T(""))		//数字不为空
				{
					strValue = strTempV;
				}
				if(strDW == _T(""))	//单位为空的情况下，把取出的单位赋值过去
				{
					strDW = strTdw;
				}
			}

			CDvmData *pData = new CDvmData();
			pData->m_strID = pData->m_strName = strName;
			pData->m_strUnit = strDW;
			pData->m_strValue = strValue;

			//认为是控制字
			if(pData->m_strValue == _T("0") || pData->m_strValue == _T("1"))
			{
				pData->m_strMin = _T("0");
				pData->m_strMax = _T("1");
			}

			m_pCurrDataset->AddNewChild(pData);				
		}
	}
}
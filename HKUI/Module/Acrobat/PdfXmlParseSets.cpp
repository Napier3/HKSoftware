#include "StdAfx.h"
#include "PdfXmlParseSets.h"
#include "PdfXmlData.h"

BOOL range_IsIntersect(float fMin, float fMax, float fDestMin, float fDestMax)
{
	if (fMin > fDestMax || fDestMin > fMax)
	{
		return FALSE;
	}

	//��ʱȷ��Ϊ�н���
	//��������ȷ�������Ĵ�СΪ��С��ȣ�������
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

//���к��ٺϲ���
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
			pPev->AddColDataV(p);	//����ϲ�
			DeleteAt(posPrev);
		}
		else
		{
			pPev = p;
		}
	}
}
//���к�ϲ���
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
			pPev->AddColDataV(p);	//����ϲ�
			DeleteAt(posPrev);
		}
		else
		{
			pPev = p;
		}
	}
}

//���ӿյ���
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

	//��Ӻ����д���Ϊ�յ����
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
				//�Ѿ����������к󣬵��ֺͺ����ֽ���
				//p->m_fHpos2 > pHeadData->m_fHpos2 �Ǳض����ڴ���
				if(p->m_bSetCol && pHeadPrev != NULL && p->m_fHpos2 < pHeadData->m_fHpos2)
				{
					iPrevWith = pHeadPrev->m_fHpos2 - p->m_fHpos;	//������ǰһ������ռ���
					iNowWith = p->m_fHpos2 - pHeadPrev->m_fHpos;	//�����ڱ�������ռ���
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

		//��������һ���ݺ����н�����������û����������Ϊ���Ǳ�������
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

		//��������һ���ݺ����н���
		if(range_IsIntersect(pData->m_fHpos, pData->m_fHpos2, p->m_fHpos, p->m_fHpos2))
		{
			iMergeCount++;	
			if(iMergeCount > 1)		//ֻҪ������������оͲ��ϲ�
			{
				return FALSE;
			}

			//�������ĵ����С��0.5,
			if((fabs(pData->m_fHpos - p->m_fHpos) < 0.5 || fabs((pData->m_fHpos+pData->m_fWidth/2) - (p->m_fHpos+p->m_fWidth/2)) < 0.5))
			{
				pAdd = p;
			}
		}
	}

	if(iMergeCount == 1 && pAdd != NULL)
	{
		pAdd->AddColDataV(pData);	//����ϲ�
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

		//ֻ�����о��л��ҲŻ��ͬ�����󣬳����������ݿ���
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
		pDataCol = (CPdfXmlData *)GetAt(i);	//�����к�ֻ��������кŵȻ��
		if(pDataCol == NULL)
			continue;

		pHeadTwo = NULL;
		pHeadTwo = (CPdfXmlData *)GetAt(i);

		//������н�����Ϊͬһ�У�ֱ��������ͷ��Χ
		if(range_IsIntersect(pDataCol->m_fHpos, pDataCol->m_fHpos2, pHeadTwo->m_fHpos, pHeadTwo->m_fHpos2))
		{
			if(pDataCol->m_fHpos < pHeadTwo->m_fHpos)
				pHeadTwo->m_fHpos = pDataCol->m_fHpos;
			if(pDataCol->m_fHpos2 > pHeadTwo->m_fHpos2)
				pHeadTwo->m_fHpos2 = pDataCol->m_fHpos2;
			continue;
		}

		//�����������������С
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
	//����㷨
	//���������еķ���
	pHeadRow = (CPdfXmlStringRow *)GetNext(pos);
	if(pHeadRow == NULL)
		return ;
	pHeadRow->InitHeadRow();  //2023-7-19 lijunqing ��ʼ�������е���

	while (pos != NULL)
	{
		pRow = (CPdfXmlStringRow *)GetNext(pos);

		pRow->InitColIndex(pHeadRow);		//��ʼ�����и��б��
		pRow->InitColIndex_1(pHeadRow);

		pRow->MergeCols(pHeadRow);		
		pRow->AddEmptyCol_1(pHeadRow);
	}
}

//���������һ�У������������������Ϊ���������޸ĵ�һ��λ����Ϣ
void CPdfXmlStringTable::ProssHeadRow()
{
	CPdfXmlStringRow *pRow, *pHeadRow, *pAddHRow = NULL;
	POS pos = NULL;

	pHeadRow = (CPdfXmlStringRow *)GetHead();
	m_nCols = pHeadRow->GetCount();

	if(m_nCols <= 3 && m_iNameHeadCol == -1)	//����С��4��û�б�ͷʱ��ȡ�������
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

		if(iMaxCols > m_nCols)	//��������С��3�Ҳ����������
		{
			pAddHRow = (CPdfXmlStringRow *)GetHead();
			pAddHRow->AddEmptyCol_Data(m_nCols, iMaxCols, (CPdfXmlData *)pAddHRow->GetTail(), pHeadRow, true);
			m_nCols = iMaxCols;			
		}		
	}

	if(IsHeadRowLeft())	//�б�ͷ����
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
		//�����޶��б�ͷ�ķ�Χ
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
		{	//��ԭlist��ת�Ƶ����к����ԭlist�м�¼
			pStringList->Remove(p);
		}
	}

	//ɾ���̶���Ч��
	DelTilteRows();

	//ɾ���������޳�����
	DelTilteName();

	//ɾ���������޳�������
	DelRowName();

	//��������������
	pos = GetHeadPosition();
	CPdfXmlStringRow *pTwoRow = NULL;
	while (pos != NULL)
	{
		pTwoRow = (CPdfXmlStringRow*)GetNext(pos);
		pTwoRow->Sort(0, true);	//ֻ��Hpos����
	}

	//����
	Sort(true);

	//ɾ�������ظ��У�����ڷ�ҳʱ���������������ͬ��λ����Ϣ��ͬ������
	DelSameLine();

	//ɾ���ظ��������ݼ���ͷ
	DelSameTable();
	Debug_SaveRowsFile();

	//�ϲ�������
	MergeRows();

	//�ϲ�������
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
		if(pTwoRow->GetCount() == 1)	//�����Ч����ͷ
		{
			strTail = strHead = pTwoRow->GetHead()->m_strName;
			strTail.Replace(_T("��"), _T(""));	//��2209024
			strTail.Replace(_T(" "), _T(""));
			if(IsStringNumber(strTail))	//ɾ�������ֱ�ͷ
			{
				Delete(pTwoRow);
			}
			else if(strHead.Find(_T("ע")) != -1)	
			{
				Delete(pTwoRow);
			}
			else if(strHead.Find(_T("��")) != -1 && strHead.Find(_T("ҳ")) != -1
				&& strHead.Find(_T("��")) != -1)	
			{
				Delete(pTwoRow);
			}
		}	
	}
}

//ɾ����Ч�����б���
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
		if(pTwoRow->GetCount() == 1)	//�����Ч����ͷ
		{
			strHead =  pTwoRow->GetHead()->m_strName;
			if(strHead == strTile)
			{
				Delete(pTwoRow);
			}
		}	
	}
}

//ɾ����Ч��
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
	//�����ж������������
	AdjRowsToTables();

	POS pos = m_listTable.GetHeadPosition();
	CPdfXmlStringTable *pTable = NULL;
	CPdfXmlStringRow *pRowHead = NULL;

	while (pos != NULL)
	{
		pTable = (CPdfXmlStringTable *)m_listTable.GetNext(pos);
		if(pTable->GetCount() <= 0)	//ɾ��û�����ݵı�
		{
			m_listTable.Delete(pTable);
		}
		else
		{
			pRowHead = (CPdfXmlStringRow *)pTable->GetHead();
			pTable->m_iNameHeadCol = IsHeadRowCheck(pRowHead);		//�Ȳ��������У��ҵ���Ϊ���б�ͷ
			pTable->ParseTable();
		}
	}
}

//�����ж������������
void CPdfXmlStringTableParse::AdjRowsToTables()
{
	POS pos = GetHeadPosition();
	CPdfXmlStringRow *pRow = NULL;
	CPdfXmlStringTable *pTable = NULL;
	CString strTableName = _T("");

	while (pos != NULL)
	{
		pRow = (CPdfXmlStringRow *)GetNext(pos);

		if (pRow->GetCount() == 1 || pTable == NULL) //ֻ��һ�У���Ϊ�Ǳ�����ʼ������
		{
			strTableName = pRow->GetHead()->m_strName;
			pTable = new CPdfXmlStringTable();
			m_listTable.AddTail(pTable);
			pTable->m_strName = strTableName;

			//��Ȼ�������RemoveAll�������
			//delete pRow; 
			this->Delete(pRow); //ɾ���������У������������֮�����е������ж������µı������У������RemoveAll
		}
		else
		{
			pTable->AddTail(pRow);
		}
	}

	//�����������֮�����е������ж������µı������У������RemoveAll
	RemoveAll();
}

BOOL CPdfXmlStringTableParse::AddToRow(CPdfXmlData *pData)
{
	CPdfXmlStringRow *pRow = FindRow(pData);

	if (pRow == NULL)
	{
		//��������ʱ�����жϺ���һ�����ݵĹ�ϵ����Ϊ��һ�кϲ��˶��У����¿��ܴ��ں������Ҳ����������½�����
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
	m_LastRow = pRow;	//�Դ�����¼��һ����Ԫ��������
	return TRUE;
}

CPdfXmlStringRow * CPdfXmlStringTableParse::FindRow(CPdfXmlData *pData)
{
	//���ж��Ƿ�����
	CPdfXmlStringRow *pRow = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pRow = (CPdfXmlStringRow *)GetNext(pos);

		//�˷���ʹ��ʱ��ԭʼ���ݴ���ʱ��ѷ�ҳ�ĸ߶���ӵ�������
		if (range_IsIntersect(pData->m_fVpos, pData->m_fVpos2, pRow->m_fVpos, pRow->m_fVpos+pRow->m_fHeight))
		{
			//��һ�кϲ��˶��У�����ĳһ�������е��м�
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

//ɾ����������ͬ���ı�������кͱ�ͷ�У���ͷ�д��ڲ�ֹһ�У�
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
		if (pRow->GetCount() == 1) //ֻ��һ�У���Ϊ�Ǳ�����ʼ������
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
				if(pRowHead != NULL && IsHeadRowCheck(pRowHead) != -1)	//�б�ͷ����������
				{
					this->Delete(pRow);	//ɾ��������
					this->Delete(pRowHead); //ɾ����ͷ��
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
			if(!m_pPdfConfig->IsDatasetTitle(strTile, strKey))	//���Ǳ�ͷ
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

	
	//PDFתxml
	CString strExePath = _P_GetBinPath();
	if(IsWow64()) //20231016 luozibing �жϵ�ǰϵͳλ��
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
		//20231023 huangliang �𽨷������ֵ����޷������ļ���ɾ��,������ɾ���ļ�����ɾ���ļ���
		SetFileAttributes(strTempPath + _T("123456789.pdf"),FILE_ATTRIBUTE_NORMAL);		//20231024 luozibing ����ɾ��ֻ���ļ�,��pdf��ֻ������ȥ��
		X_DeleteFile(strTempPath + _T("123456789.pdf"));
		X_DeleteFile(strTempPath + _T("123456789.xml"));
		X_DeleteFile(strTempPath + _T("123456789_metadata.xml"));
		DeleteAllFiles(strTempPath + _T("123456789.xml_data"), _T("svg"));
	DeleteAllDirectorys(strTempPath);
	}

	//20231017 huangliang �ļ�����̫����pdfalto.exe�޷�����
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
		WaitForSingleObject(ShExecInfo.hProcess,INFINITE);//�˾�ȴ���str Ϊ���������·����
	}

	//��ȡxml
	strXmlFile.Replace(_T(".pdf"), _T(".xml"));
	CReadXmlData readXmlData;
	if(!readXmlData.OpenXmlFile(strXmlFile))
	{
		CString tmp;
		tmp.Format(_T("�޷���ȡ%s"),strXmlFile);
		::MessageBox(NULL, tmp, _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	CPdfStringDatas oStringDataList;	
	readXmlData.FindAllTextLine(&oStringDataList);

	//����xml����
	ParseLineData(&oStringDataList);

	oStringDataList.DeleteAll();

	m_PdfDBInfos.SaveXmlFile(PdfDBUnknownTable,CPdfHLParseXmlRWKeys::g_pXmlKeys);
	return TRUE;
}

//���������ݷ��䵽����
void CPdfXmlParseSets::ParseLineData(CExBaseList* pStringList)
{
	//�Ե�Ԫ�����������Ȱ����ٰ���
	pStringList->Sort(true);

	//��ʼ��������
	m_oPdfTable.m_pPdfConfig = &m_oPdfConfig;
	m_oPdfTable.InitRows(pStringList);
	m_oPdfTable.Debug_SaveRowsFile();

	m_oPdfTable.ParseTableData();
	m_oPdfTable.Debug_SaveTablesFile();

	//���ñ����Լ�����Ϣ���Զ�ʶ�����ݣ���ʾ�û��ж�
	SetTableIdentify();

	//Table����д��Device��
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
	plistTable->GetNext(pos);	//ͷ���������

	while (pos != NULL)
	{
		pXmlTable = (CPdfXmlStringTable *)plistTable->GetNext(pos);
		pXmlRow = (CPdfXmlStringRow* )pXmlTable->GetHead();

		if(!CheckTableIdentify(pXmlTable))		
		{
			pXmlTable->m_strName += _T(" *");
			if(pXmlRow != NULL && pXmlRow->GetCount() < 30)	//��������30�ı�ȥ��
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

				if(pXmlRow != NULL && pXmlRow->GetCount() < 30)	//��������30�ı�ȥ��
					oTableList.AddTail(pXmlTable);
			}
		}
	}

	if(oTableList.GetCount() > 0)	//����ȷ�Ͽ�
	{
		//20240312 huangliang ��ʾ�Ի���
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
	//�洢�˱��������ֱ��ʹ��
	if(!m_bCorrect)	//����ʱ����ʹ�����ݿ�
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
	if(m_bCorrect)//����ʱ����ʹ�����ݿ�
		return ;

	CPdfDBHead *tmp_Head = (CPdfDBHead *)m_PdfDBInfo->FindByID(pXmlTable->m_strName);
	if(tmp_Head == NULL)
	{
		return ;
	}

	pXmlTable->m_iNameHeadCol = tmp_Head->m_nNameHead;
	pXmlTable->m_iDWHeadCol = tmp_Head->m_nDWHead;
	pXmlTable->m_iValueHeadCol = tmp_Head->m_nValueHead;

	//���û�б�ͷ����������ӿձ�ͷ
	if(tmp_Head->m_nExistHead == 1)	
	{
		CPdfXmlStringRow *pXmlTileRow = new CPdfXmlStringRow;
		pXmlTable->AddHead(pXmlTileRow);
	}
}

//xml����д��Device��
void CPdfXmlParseSets::ParseInDestLogicDevice()
{
	CExBaseList *plistTable = m_oPdfTable.GetAllTable();

	bool bHeadPross = false;
	CPdfXmlStringTable* pXmlTable = NULL;
	POS pos = plistTable->GetHeadPosition();
	while (pos != NULL)
	{
		pXmlTable = (CPdfXmlStringTable *)plistTable->GetNext(pos);
		
		if(!bHeadPross)	//Ĭ�ϱ�ͷ���ڵ�һ�����ݱ���
		{	
			bHeadPross = true;
			ParseTableHead(pXmlTable);
		}
		else	//���������������
		{
			ParseTableInDestLogicDevice(pXmlTable);
		}
	}
}

//�����ͷ����
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
		else if(nIndex > 0)		//ȡKeyֵ�����һ������
		{
			nIndex = 0;
			CDvmData *pData = new CDvmData();
			pData->m_strName = pStringData->m_strName;
			m_pCurrDataset->AddNewChild(pData);
		}
	}
}

//��������ݱ�
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
	//��¼�����и��е�˳���ţ���Ҫ��¼���ơ���λ���ֶ�ֵ
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

			if(strName == _T(",") || strName == _T("��") || strName == _T(""))
				continue;
			strValue.Replace(_T(" "), _T(""));
			strName.Replace(_T(":"), _T(""));
			strName.Replace(_T("��"), _T(""));

			//������ֵ������բ����Ϊ�����֣�ȥ������ĵ�λ
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
				if(strTempV != _T(""))		//���ֲ�Ϊ��
				{
					strValue = strTempV;
				}
				if(strDW == _T(""))	//��λΪ�յ�����£���ȡ���ĵ�λ��ֵ��ȥ
				{
					strDW = strTdw;
				}
			}

			CDvmData *pData = new CDvmData();
			pData->m_strID = pData->m_strName = strName;
			pData->m_strUnit = strDW;
			pData->m_strValue = strValue;

			//��Ϊ�ǿ�����
			if(pData->m_strValue == _T("0") || pData->m_strValue == _T("1"))
			{
				pData->m_strMin = _T("0");
				pData->m_strMax = _T("1");
			}

			m_pCurrDataset->AddNewChild(pData);				
		}
	}
}
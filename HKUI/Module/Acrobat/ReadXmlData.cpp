#include "StdAfx.h"
#include "ReadXmlData.h"
#include "PdfXmlData.h"


CReadXmlData::CReadXmlData(void)
{
}

CReadXmlData::~CReadXmlData(void)
{
	DeleteAll();
	m_oXmlDoc.reset();
}

BOOL CReadXmlData::OpenXmlFile(const CString &strFile)
{	
	if (!IsFileExist(strFile))
	{
		//2022-11-25  lijunqing
#ifdef _DEBUG
		CString strMsg = _T("File error :") + strFile;
		CLogPrint::LogString(XLOGLEVEL_ERROR, strMsg);
#endif
		return FALSE;
	}

	DeleteAll();
	m_oXmlDoc.reset();

	BOOL bRet = FALSE;
	bRet = m_oXmlDoc.load_file(strFile.GetString());
	if(!bRet)
		return FALSE;

	ReadNode(&m_oXmlDoc);	

	return TRUE;
}

void CReadXmlData::ReadNode(BDNode *xmlNode)
{
	m_xmlNode = xmlNode;
	if(m_xmlNode == NULL)
		return ;

	m_strName = m_xmlNode->name();

	ReadNodeAttribte();

	BDNode cur = m_xmlNode->first_child();			
	while (cur && cur != *m_xmlNode)
	{
		CReadXmlData* pObj = new CReadXmlData();
		pObj->SetParent(this);		
		AddTail(pObj);

		pObj->ReadNode(&cur);

		cur = cur.next_sibling();
	}
}

void CReadXmlData::ReadNodeAttribte()
{
	if(m_xmlNode == NULL)
		return;

	m_vecAttri.clear();

	BDAttr *atttr = NULL;
	BDAttB attrTmp = m_xmlNode->first_attribute();
	for (; attrTmp; attrTmp = attrTmp.next_attribute())
	{
		atttr = attrTmp.internal_object();
		m_vecAttri.push_back(atttr);
	}
}

void CReadXmlData::FindAllTextLine(CExBaseList* pTextLineList)
{
	CPdfStringDatas* pStringList = (CPdfStringDatas *)pTextLineList;

	CReadXmlData* pTemp = NULL;
	CReadXmlData* pFind = NULL;
	CPdfXmlData *pXmlData = NULL;

	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		pTemp = (CReadXmlData*)GetNext(pos);
		if(pTemp->m_strName == _T("Page"))
		{
			pStringList->m_fPageVpos += 1000;	//计算新page
		}
		if(pTemp->m_strName == _T("TextBlock"))
		{
			CPdfXmlData oTwo;
			oTwo.AnalysisXmlData(pTemp, pStringList->m_fPageVpos);

			pStringList->m_iBlockCount = 0;
			pStringList->m_fBlockHeight = oTwo.m_fHeight;	//记录此Block的高度
			pStringList->m_bAddString = false;
		}

		if (pTemp->m_strName == COL_DATA || pTemp->m_strName == COL_SP)
		{			
			pStringList->ProssTextLine(pTemp);
		}
		else
		{
			pTemp->FindAllTextLine(pStringList);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//CPdfStringDatas
CPdfStringDatas::CPdfStringDatas()
{
	m_bAddString = false;
	m_fPageVpos = -1000;
	m_fBlockHeight = 0;
	m_iMinHpos = 100;
	m_iBlockCount = 0;
}
CPdfStringDatas::~CPdfStringDatas()
{
}
void CPdfStringDatas::ProssTextLine(CExBaseList *pData)
{
	CReadXmlData *pTemp = (CReadXmlData *)pData;

	CPdfXmlData * pOne = (CPdfXmlData *)GetTail();
	if (pTemp->m_strName == COL_DATA)
	{	
		if(m_bAddString)
		{
			CPdfXmlData oTwo;
			oTwo.AnalysisXmlData(pTemp, m_fPageVpos);

			//是否存在相同Hpos的数据
			if(!FindSameHposData(&oTwo))
			{
				BOOL bRet = pOne->AddColDataH(&oTwo, _T(""));			
				m_bAddString = false;

				if(bRet)
				{				
					return ;
				}
			}
		}
		
		CPdfXmlData *pTwo = new CPdfXmlData;
		pTwo->AnalysisXmlData(pTemp, m_fPageVpos);

		if(CheckXmlData(pOne, pTwo))
		{
			delete pTwo;
			return ;
		}	
		AddXmlData(pTwo);
	}
	else if (pTemp->m_strName == COL_SP)
	{
		if(pOne == NULL)
			return ;

		float fWordWith = pOne->CalWordWith();

		CPdfXmlData oTwo;
		oTwo.AnalysisXmlData(pTemp, m_fPageVpos);

		if(oTwo.m_fWidth < fWordWith)		//SP的宽度小于单个字符宽度
		{
			m_bAddString = true;
		}
	}
}

BOOL CPdfStringDatas::FindSameHposData(CExBaseObject *pParameter1)
{
	if(pParameter1 == NULL)
		return FALSE;

	CPdfXmlData *pOne = (CPdfXmlData *)pParameter1;

	CPdfXmlData *pData = NULL;
	POS pos = GetTailPosition();
	while (pos != NULL)
	{
		pData = (CPdfXmlData*)GetPrev(pos);

		//找到上一个横向有交集的单元格
		if (!(pOne->m_fHpos > pData->m_fHpos2 || pData->m_fHpos > pOne->m_fHpos2))
		{
			//起点相同，则认为是单独的单元格
			if(pData->m_fHpos == pOne->m_fHpos)
			{
				return TRUE;
			}
			break;
		}		
	}
	return FALSE;
}

BOOL CPdfStringDatas::CheckXmlData(CExBaseObject *pParameter1, CExBaseObject *pParameter2)
{
	if(pParameter1 == NULL)
		return FALSE;

	////合并单格分行数据，只能合并到第一列，以TextBlock的高度判断，TextBlock高度是记录第一个单元格值高度
	//if(CheckMergeData(pParameter1, pParameter2))
	//{
	//	return TRUE;
	//}

	//判断是否相同或包含关系
	if(CheckContainData(pParameter1, pParameter2))
	{
		return TRUE;
	}

	//判断是否交集关系
	if(CheckIntersectData(pParameter1, pParameter2))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CPdfStringDatas::CheckContainData(CExBaseObject *pParameter1, CExBaseObject *pParameter2)
{
	if(pParameter1 == NULL)
		return FALSE;

	CPdfXmlData *pOne = (CPdfXmlData *)pParameter1;
	CPdfXmlData *pTwo = (CPdfXmlData *)pParameter2;

	//前包含及完全相同
	float fHabs = fabs(pTwo->m_fHpos - pOne->m_fHpos);
	float fVabs = fabs(pTwo->m_fVpos - pOne->m_fVpos);			
	//20231016 huangliang 存在值刚好相差1却是同一个数据（PDF中加黑项）
	if(fVabs <= 1 && fHabs <= 1)	//相同内容,不添加进行中
	{
		if(pOne->m_fWidth < pTwo->m_fWidth)	//相同位置数据，使用字符最长数据
		{
			pOne->Copy(pTwo);
		}
		return TRUE;
	}
	
	//后包含
	float fWabs = fabs(pTwo->m_fHpos + pTwo->m_fWidth - pOne->m_fHpos - pOne->m_fWidth);		
	if(fVabs <= 1 && fWabs <= 1)	//相同内容,不添加进行中
	{
		if(pOne->m_fWidth < pTwo->m_fWidth)	//相同位置数据，使用字符最长数据
		{
			pOne->Copy(pTwo);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CPdfStringDatas::CheckMergeData(CExBaseObject *pParameter1, CExBaseObject *pParameter2)
{
	if(pParameter1 == NULL)
		return FALSE;

	CPdfXmlData *pOne = (CPdfXmlData *)pParameter1;
	CPdfXmlData *pTwo = (CPdfXmlData *)pParameter2;

	if(IsStringNumber(pTwo->m_strName))	//纯数字之间不适用此方法
	{
		return FALSE;
	}

	m_iBlockCount++;
	if(m_iBlockCount == 1 || pOne == NULL)	//第一个Block时不需要计算
	{
		if(m_fBlockHeight < pTwo->m_fHeight*4)	//暂定为是字符的4倍高度
		{
			m_iBlockCount = 0;	//之后字符不用合并
		}
		return FALSE;	
	}

	if(pOne->m_fHpos != pTwo->m_fHpos)	//不是相同的Hpos也不用合并
	{
		m_iBlockCount = 0;	//之后字符不用合并
		return FALSE;
	}

	return pOne->AddColDataH(pTwo, _T(""));
}

BOOL CPdfStringDatas::CheckIntersectData(CExBaseObject *pParameter1, CExBaseObject *pParameter2)
{
	if(pParameter1 == NULL)
		return FALSE;

	CPdfXmlData *pOne = (CPdfXmlData *)pParameter1;
	CPdfXmlData *pTwo = (CPdfXmlData *)pParameter2;

	if ((pOne->m_fVpos > pTwo->m_fVpos2 || pTwo->m_fVpos > pOne->m_fVpos2)
		|| (pOne->m_fHpos > pTwo->m_fHpos2 || pTwo->m_fHpos > pOne->m_fHpos2))
	{	//不存在半毛交集
		return FALSE;
	}

	return pOne->AddColDataH(pTwo, _T(""));
}


void CPdfStringDatas::AddXmlData(CExBaseObject *pParameter1)
{
	CPdfXmlData *pAddData = (CPdfXmlData *)pParameter1;
	AddTail(pAddData);

	if(pAddData->m_fHpos < m_iMinHpos)
		m_iMinHpos = pAddData->m_fHpos; 
}

BOOL CPdfStringDatas::CheckDataChangeAfter()
{
	CheckEnterLine();
	return TRUE;
}
//对除第一列的数据外进行换行合并
BOOL CPdfStringDatas::CheckEnterLine()
{
	if(GetCount() < 4)	//少于4个数据不处理
		return FALSE;
	
	POS pos = GetHeadPosition();
	CPdfXmlData *pZero = (CPdfXmlData *)GetPrev(pos);
	CPdfXmlData *pOne = (CPdfXmlData *)GetPrev(pos);
	CPdfXmlData *pTwo = (CPdfXmlData *)GetPrev(pos);
	CPdfXmlData *pEnd = (CPdfXmlData *)GetPrev(pos);

	if(IsStringNumber(pOne->m_strName))	//纯数字不算
	{
		return FALSE;
	}
	if(IsStringNumber(pTwo->m_strName))	//纯数字不算
	{
		return FALSE;
	}

	//1、2在同一行；3、4在同一行则认为不是一行数据
	if(pZero->m_fVpos == pOne->m_fVpos && pEnd->m_fVpos == pTwo->m_fVpos)
	{
		return FALSE;
	}

	if(pZero->m_fVpos2 < pOne->m_fVpos && pZero->m_fVpos2 < pTwo->m_fVpos)
	{
		pZero = NULL;
	}

	float fMinHabs = fabs(pOne->m_fHpos - m_iMinHpos);	
	float fHabs = fabs(pTwo->m_fHpos - pOne->m_fHpos);
	float fCenterHabs = fabs((pTwo->m_fHpos+pTwo->m_fWidth/2) - (pOne->m_fHpos+pOne->m_fWidth/2));
	if(fMinHabs > 20 && (fHabs < 2 || fCenterHabs< 2))//不是第一列，且起点或中心点小于2
	{
		pOne->AddColDataMaxH(pTwo, pZero);
		Delete(pTwo);
		return TRUE;
	}
	return FALSE;
}
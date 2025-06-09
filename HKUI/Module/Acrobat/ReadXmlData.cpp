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
			pStringList->m_fPageVpos += 1000;	//������page
		}
		if(pTemp->m_strName == _T("TextBlock"))
		{
			CPdfXmlData oTwo;
			oTwo.AnalysisXmlData(pTemp, pStringList->m_fPageVpos);

			pStringList->m_iBlockCount = 0;
			pStringList->m_fBlockHeight = oTwo.m_fHeight;	//��¼��Block�ĸ߶�
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

			//�Ƿ������ͬHpos������
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

		if(oTwo.m_fWidth < fWordWith)		//SP�Ŀ��С�ڵ����ַ����
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

		//�ҵ���һ�������н����ĵ�Ԫ��
		if (!(pOne->m_fHpos > pData->m_fHpos2 || pData->m_fHpos > pOne->m_fHpos2))
		{
			//�����ͬ������Ϊ�ǵ����ĵ�Ԫ��
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

	////�ϲ�����������ݣ�ֻ�ܺϲ�����һ�У���TextBlock�ĸ߶��жϣ�TextBlock�߶��Ǽ�¼��һ����Ԫ��ֵ�߶�
	//if(CheckMergeData(pParameter1, pParameter2))
	//{
	//	return TRUE;
	//}

	//�ж��Ƿ���ͬ�������ϵ
	if(CheckContainData(pParameter1, pParameter2))
	{
		return TRUE;
	}

	//�ж��Ƿ񽻼���ϵ
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

	//ǰ��������ȫ��ͬ
	float fHabs = fabs(pTwo->m_fHpos - pOne->m_fHpos);
	float fVabs = fabs(pTwo->m_fVpos - pOne->m_fVpos);			
	//20231016 huangliang ����ֵ�պ����1ȴ��ͬһ�����ݣ�PDF�мӺ��
	if(fVabs <= 1 && fHabs <= 1)	//��ͬ����,����ӽ�����
	{
		if(pOne->m_fWidth < pTwo->m_fWidth)	//��ͬλ�����ݣ�ʹ���ַ������
		{
			pOne->Copy(pTwo);
		}
		return TRUE;
	}
	
	//�����
	float fWabs = fabs(pTwo->m_fHpos + pTwo->m_fWidth - pOne->m_fHpos - pOne->m_fWidth);		
	if(fVabs <= 1 && fWabs <= 1)	//��ͬ����,����ӽ�����
	{
		if(pOne->m_fWidth < pTwo->m_fWidth)	//��ͬλ�����ݣ�ʹ���ַ������
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

	if(IsStringNumber(pTwo->m_strName))	//������֮�䲻���ô˷���
	{
		return FALSE;
	}

	m_iBlockCount++;
	if(m_iBlockCount == 1 || pOne == NULL)	//��һ��Blockʱ����Ҫ����
	{
		if(m_fBlockHeight < pTwo->m_fHeight*4)	//�ݶ�Ϊ���ַ���4���߶�
		{
			m_iBlockCount = 0;	//֮���ַ����úϲ�
		}
		return FALSE;	
	}

	if(pOne->m_fHpos != pTwo->m_fHpos)	//������ͬ��HposҲ���úϲ�
	{
		m_iBlockCount = 0;	//֮���ַ����úϲ�
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
	{	//�����ڰ�ë����
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
//�Գ���һ�е���������л��кϲ�
BOOL CPdfStringDatas::CheckEnterLine()
{
	if(GetCount() < 4)	//����4�����ݲ�����
		return FALSE;
	
	POS pos = GetHeadPosition();
	CPdfXmlData *pZero = (CPdfXmlData *)GetPrev(pos);
	CPdfXmlData *pOne = (CPdfXmlData *)GetPrev(pos);
	CPdfXmlData *pTwo = (CPdfXmlData *)GetPrev(pos);
	CPdfXmlData *pEnd = (CPdfXmlData *)GetPrev(pos);

	if(IsStringNumber(pOne->m_strName))	//�����ֲ���
	{
		return FALSE;
	}
	if(IsStringNumber(pTwo->m_strName))	//�����ֲ���
	{
		return FALSE;
	}

	//1��2��ͬһ�У�3��4��ͬһ������Ϊ����һ������
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
	if(fMinHabs > 20 && (fHabs < 2 || fCenterHabs< 2))//���ǵ�һ�У����������ĵ�С��2
	{
		pOne->AddColDataMaxH(pTwo, pZero);
		Delete(pTwo);
		return TRUE;
	}
	return FALSE;
}
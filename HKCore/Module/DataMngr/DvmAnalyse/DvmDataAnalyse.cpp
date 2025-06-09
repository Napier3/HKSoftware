//DvmDataAnalyse.cpp  CDvmDataAnalyse

#include "stdafx.h"
#include "DvmDataAnalyse.h"

CDvmDataAnalyse::CDvmDataAnalyse()
{
	m_pDvmDataRef = NULL;

}

CDvmDataAnalyse::~CDvmDataAnalyse()
{
	m_listAnlyseDestObject.RemoveAll();
}

void CDvmDataAnalyse::DvmAnalyse(CDvmData *pDvmData, CXKeyDB *pXKeyDB, CDvmAnalyseQueryInterface *pQuery)
{
	m_pDvmDataRef = pDvmData;
	pXKeyDB->QueryKeys(pDvmData->m_strName, &m_listMatchXKeys);

	ASSERT (pQuery != NULL);

	if (pQuery != NULL)
	{
		pQuery->QueryByKeys(&m_listMatchXKeys, m_listAnlyseDestObject);
	}
}


CString CDvmDataAnalyse::GetKeys()
{
	POS pos1 = m_listMatchXKeys.GetHeadPosition();
	CXKeyMatchRef  *p1 = NULL;
	CString   strKeyWords;

	while (pos1 != NULL)
	{	
		p1=m_listMatchXKeys.GetNext(pos1);

		if (p1->m_pXKeyRef !=NULL)
		{
			if (p1->m_pXKeyRef->IsArrayKey())
			{
				if (p1->m_nArrayIndex != -1)
				{
					strKeyWords.AppendFormat(_T("%s[%d]"), p1->m_pXKeyRef->m_strName, p1->m_nArrayIndex);
				}
				else

				strKeyWords+=p1->m_pXKeyRef->m_strName;
			}
			else
			{
				strKeyWords+=p1->m_pXKeyRef->m_strName;
			}

			strKeyWords+="     ";
		}
	}

	return strKeyWords;
}

CString CDvmDataAnalyse::GetTemps()
{
	CString strTempNames = _T("");
// 	POS pos = m_listTempFunc.GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 	
// 	while (pos != NULL)
// 	{	
// 		p=(CXTFFuncBase *)m_listTempFunc.GetNext(pos);
// 		ASSERT (pFuncBase->m_pTemplate != NULL);
// 
// 		if (pFuncBase->m_pTemplate != NULL)
// 		{
// 			strTempNames += pFuncBase->m_pTemplate->m_strName;
// 			strTempNames += _T(",");
// 		}
// 	
// 	}
// 
// 	strTempNames = strTempNames.Left(strTempNames.GetLength()-1);
	return strTempNames;
}


void CDvmDataAnalyse::DvmQueryFilter(CExBaseList &listTemplate)
{
	CExBaseObject *pTempl = NULL;
	POS pos = m_listAnlyseDestObject.GetHeadPosition();

	while (pos != NULL)
	{
		pTempl = m_listAnlyseDestObject.GetNext(pos);
		
		if (listTemplate.Find(pTempl) == NULL)
		{
			listTemplate.AddTail(pTempl);
		}
	}
}


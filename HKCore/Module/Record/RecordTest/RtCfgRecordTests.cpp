// RtCfgRecordTests.cpp: implementation of the CRtCfgRecordTests class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtCfgRecordTests.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRtCfgRecordTests *CRtCfgRecordTests::g_pRtCfgRecordTests = NULL;
long  CRtCfgRecordTests::m_nRtCfgRecordTestsRefCount = 0;

CRtCfgRecordTests* CRtCfgRecordTests::CrteateRtCfgRecordTests()
{
	m_nRtCfgRecordTestsRefCount++; 

	if (m_nRtCfgRecordTestsRefCount == 1)
	{
		g_pRtCfgRecordTests = new CRtCfgRecordTests();

	}

	return g_pRtCfgRecordTests;
}

void CRtCfgRecordTests::Release()
{
	m_nRtCfgRecordTestsRefCount--;

	if (m_nRtCfgRecordTestsRefCount == 0)
	{
		delete g_pRtCfgRecordTests;
		g_pRtCfgRecordTests = NULL;
	}
}

const char *CRtCfgRecordTests::g_pszKeyRecordTests = "record-tests";
const char *CRtCfgRecordTests::g_pszConfigFile     = "RecordTestConfig.xml";

CRtCfgRecordTests::CRtCfgRecordTests()
{
	m_strName = "RecordTestConfig";
	//m_pAppModels = NULL;
	m_pRtTypes   = NULL;
	m_pActiveRecordTest = NULL;
}

CRtCfgRecordTests::~CRtCfgRecordTests()
{
	//m_pAppModels->Release();
	m_pRtTypes->Release();
}
// 
// //重载的方法
// long CRtCfgRecordTests::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	return 0;
// }
// 
// long CRtCfgRecordTests::ReadChildrenXml(MSXML::IXMLDOMNodeListPtr &oNodes)
// {
// 	long nCount = oNodes->Getlength();
// 	long nIndex = 0;
// 	CExBaseObject *pNew = NULL;
// 	MSXML::IXMLDOMNodePtr oNode = NULL;
// 	CString strNodeName;
// 	
// 	for (nIndex=0; nIndex<nCount; nIndex++)
// 	{
// 		oNode = oNodes->Getitem(nIndex);
// 		strNodeName = (char*)oNode->GetnodeName();
// 		pNew = CreateNewChild(strNodeName);
// 		
// 		if (pNew != NULL)
// 		{
// 			pNew->SetParent(this);
// 			pNew->ReadXml(oNode);
// 		}
// 	}
// 	
// 	return 0;
// }
// 
// //CRtCfgRecordTests的子对象只有CRtCfgRecordTest
// CExBaseObject* CRtCfgRecordTests::CreateNewChild(LPCTSTR pszClassID)
// {
// 	CExBaseObject *pNew  = NULL;
// 	
// 	if (strcmp(pszClassID, CRtCfgRecordTest::g_pszKeyRecordTest) == 0) 
// 	{
// 		pNew = new CRtCfgRecordTest();
// 		AddTail(pNew);
// 	}
// 	else if (strcmp(pszClassID, CRtCfgAppModels::g_pszKeyAppModels) == 0) 
// 	{
// 		if (m_pAppModels == NULL)
// 		{
// 			m_pAppModels = CRtCfgAppModels::CreateRtCfgAppModels();
// 			pNew = m_pAppModels;
// 		}
// 	}
// 	else if (strcmp(pszClassID, CRtTypes::g_pszKeyTypes) == 0) 
// 	{
// 		if (m_pRtTypes == NULL) 
// 		{
// 			m_pRtTypes = CRtTypes::CreateRtTypes();
// 			pNew = m_pRtTypes;
// 		}
// 	}
// 	else
// 	{
// 	}
// 	
// 	return pNew;
// }
// 
// BOOL CRtCfgRecordTests::ReadRtConfigFile(const CString &strFile)
// {
// 	MSXML::IXMLDOMDocumentPtr oDoc = NULL;
// 	HRESULT hr = oDoc.CreateInstance(__uuidof(MSXML::DOMDocument));
// 	
// 	if(!SUCCEEDED(hr)) 
// 	{ 
// 		return FALSE;
// 	}
// 	
// 	MSXML::IXMLDOMNodePtr oRecordTests = NULL;
// 	BSTR bstrFile = strFile.AllocSysString();
// 	BOOL bTrue = oDoc->load(bstrFile);
// 	::SysFreeString(bstrFile);
// 	
// 	if (!bTrue)
// 	{
// 		TRACE("\nRead RecordTestConfig file failed......\n");
// 	}
// 	
// 	oRecordTests = oDoc->selectSingleNode(_bstr_t(g_pszKeyRecordTests));
// 	
// 	if (oRecordTests == NULL)
// 	{
// 		return FALSE;
// 	}
// 	
// 	ReadXml(oRecordTests);
// 	AdjustTestByType();
// 	return TRUE;
// }

void CRtCfgRecordTests::AdjustTestByType()
{
	POS pos  = GetHeadPosition();
	CRtCfgRecordTest *pRt = NULL;
	CRtType *pType = NULL;

	while (pos != NULL)
	{
		pRt = (CRtCfgRecordTest*)GetNext(pos);

		pType = (CRtType*)m_pRtTypes->FindByID(pRt->m_strTestGroupType);

		if (pType != NULL)
		{
			pType->AddTail(pRt); 
		}
		else
		{
			//LOG_WriteLawString("test type is not exist!");
		}
	}
}

void CRtCfgRecordTests::AdjustUniversalTest()
{
	POS pos  = GetHeadPosition();
	CRtCfgRecordTest *pRt = NULL;
	CRtType *pType = NULL;
	POS posPev = pos;
	
	while (pos != NULL)
	{
		posPev = pos;
		pRt = (CRtCfgRecordTest*)GetNext(pos);
		
		if (pRt != NULL)
		{
			if (pRt->IsUniversalTest())
			{
				BringToTail(pRt);
			}
			else
			{
			}
		}
		else
		{
			//LOG_WriteLawString("test is not exist!");
		}
	}
}

// BOOL CRtCfgRecordTests::ReadRtConfigFile()
// {
// 	CString strFile;
// 	strFile.Format("%s%s", _P_GetConfigPath(), g_pszConfigFile);
// 	return ReadRtConfigFile(strFile);
// }
// 
// long CRtCfgRecordTests::InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand)
// {
// 	m_pAppModels->InsertTreeCtrl(pTreeCtrl, htiParent, bParentExpand);
// 	CExBaseList::InsertChildrenTreeCtrl(pTreeCtrl, htiParent, bParentExpand);
// 	
// 	return 0;
// }
// 
// BOOL CRtCfgRecordTests::MatchTranslator(CHDMrDevice * pHDMrDevice)
// {
// 	ASSERT(pHDMrDevice != NULL);
// 	long nPos = 0;
// 	CRtCfgRecordTest *pRtCfgRecordTest = NULL;
// 	long nTransUCount, nTransICount;
// 	CExBaseList  oTransUChans, oTransIChans;
// 	pHDMrDevice->GetU_IChans(oTransUChans, oTransIChans);
// 	nTransUCount = oTransUChans.GetCount();
// 	nTransICount = oTransIChans.GetCount();
// 	double *pTransURange = NULL;
// 	double *pTransIRange = NULL;
// 	long nTrans = nTransUCount + nTransICount;
// 	
// 	pTransURange = new double [nTransUCount];
// 	pTransIRange = new double [nTransICount];
// 	SortTranRangeFromSmallToLarge(pTransURange, oTransUChans);
// 	SortTranRangeFromSmallToLarge(pTransIRange, oTransIChans);
// 	POS pos  = this->GetHeadPosition();
// 	
// 	while (pos != NULL) 
// 	{
// 		pRtCfgRecordTest = (CRtCfgRecordTest *)this->GetNext(pos);
// 		
// 		if (pRtCfgRecordTest != NULL)
// 		{
// 			if (pRtCfgRecordTest->m_strID == "")
// 			{
// 				pRtCfgRecordTest->SetRTStatus(RT_DEVALOPING);
// 			}
// 			else
// 			{
// 				if (pRtCfgRecordTest->IsUniversalTest()) //是否通用试验
// 				{
// 					int nCount = nTransUCount + nTransICount;
// 					if (nCount > 0)
// 					{
// 						pRtCfgRecordTest->SetRTStatus(RT_CANBEUSED);
// 					}
// 					else
// 					{
// 						pRtCfgRecordTest->SetRTStatus(RT_CANOTBEUSED);
// 					}
// 				}
// 				else
// 				{
// 					long nTestUCount = pRtCfgRecordTest->m_pVariables->m_oUVariList.GetCount();
// 					long nTestICount = pRtCfgRecordTest->m_pVariables->m_oIVariList.GetCount();			
// 					
// 					if ((nTransUCount >= nTestUCount) && (nTransICount >= nTestICount))
// 					{
// 						CRtCfgVariables *pRtCfgVariables = pRtCfgRecordTest->m_pVariables;
// 
// 						if (pRtCfgVariables == NULL)
// 						{
// 							return FALSE;
// 						}
// 						
// 						//比较电压通道的量程
// 						long nU_MatchCount = MatchChannelRange(pRtCfgVariables->m_oUVariList, pTransURange, nTransUCount);
// 						
// 						//比较电流通道的量程
// 						long nI_MatchCount = MatchChannelRange(pRtCfgVariables->m_oIVariList, pTransIRange, nTransICount);
// 						
// 						BOOL bMatchU = IsMatchFinish(nU_MatchCount, pRtCfgVariables->m_oUVariList);
// 						BOOL bMatchI = IsMatchFinish(nI_MatchCount, pRtCfgVariables->m_oIVariList);
// 						
// 						if (bMatchU && bMatchI)
// 						{
// 							pRtCfgRecordTest->SetRTStatus(RT_CANBEUSED);
// 						}
// 						else
// 						{
// 							pRtCfgRecordTest->SetRTStatus(RT_CANOTBEUSED);
// 						}					
// 					}
// 					else
// 					{
// 						pRtCfgRecordTest->SetRTStatus(RT_CANOTBEUSED);
// 					}				
// 				}				
// 			}
// 		}
// 	}
// 	
// 	oTransUChans.RemoveAll();
// 	oTransIChans.RemoveAll();
// 
// 	delete []pTransURange;
// 	delete []pTransIRange;
// 	pTransURange = NULL;
// 	pTransIRange = NULL;
// 	return TRUE;
// }

long CRtCfgRecordTests::MatchChannelRange(CExBaseList &oChannelList, double *dRange, long nTransUorICount)
{
	CRtCfgVariable *pRtCfgVariable = NULL;
	POS pos  = oChannelList.GetHeadPosition();
	long nMatchCount = 0;//匹配到的通道数
	long nHasBeMatch = -1;

	while (pos != NULL)
	{
		pRtCfgVariable = (CRtCfgVariable *)oChannelList.GetNext(pos);
		
		//匹配试验的通道量程
		if (pRtCfgVariable != NULL)
		{
			int nIndex;
			
			//循环遍历变换器的电压\电流通道的量程(按照从小到大的顺序排列),进行匹配,
			//试验的通道量程>变换器的电压\电流通道的量程则继续向后比较,否则匹配到
			for(nIndex = 0;nIndex < nTransUorICount; nIndex++)
			{
				if (nHasBeMatch == nIndex) 
				{
					continue;
				}
				else
				{
					//pRtCfgVariable->m_dRange是试验通道所需的量程
					//*(dRange + nIndex)是变换器的通道量程
					if (pRtCfgVariable->m_dRange > *(dRange + nIndex)) 
					{
						continue;
					}
					else
					{	
						nHasBeMatch = nIndex;
						nMatchCount++;
						break;
					}
				}				
			}
		}
	}
	return nMatchCount;
}

BOOL CRtCfgRecordTests::IsMatchFinish(long nMatchCount, CExBaseList &oChannelList)
{
	BOOL bTrue = FALSE;
	long nListCount = oChannelList.GetCount();

	if (nMatchCount >= nListCount)
	{
		bTrue = TRUE;
	}
	
	return bTrue;
}

void CRtCfgRecordTests::SortTranRangeFromSmallToLarge(double *dRange, CExBaseList &oTranChannelList)
{
	ASSERT (FALSE);
// 	CHDAnalogChannel *pHDAnalogChannel = NULL;
// 	int nIndex;
// 	int nCount = oTranChannelList.GetCount();
// 	
// 	for(nIndex = 0; nIndex < nCount; nIndex++)
// 	{
// 		pHDAnalogChannel = (CHDAnalogChannel *)oTranChannelList.GetAt(nIndex);
// 		*(dRange + nIndex) = pHDAnalogChannel->GetMaxRangeValue();
// 	}
//
//	SortTransChannelRange(dRange, nCount);
}

void CRtCfgRecordTests::SortTransChannelRange(double *dRange, int Count)
{
	Sort(dRange, 0, Count-1);
}

void CRtCfgRecordTests::Sort(double *dRange,int left,int right)
{
	int i,j;
	double middle, iTemp;
	i = left;
	j = right;
	middle = *(dRange + (left + right) / 2); 
	
	do{  
		while(((*(dRange + i)) < middle) && (i < right))                       
		{	
			i++; 
		}

		while(((*(dRange + j)) > middle) && (j > left))       
		{
			j--;  
		}
		
		if(i <= j)    
		{                      
			iTemp = *(dRange + i);             
            *(dRange + i) = *(dRange + j);         
			*(dRange + j) = iTemp;            
			i++;                  
			j--;                
		}
	}while(i <= j);

	if(left < j)  
	{
		Sort(dRange,left,j);
	}

	if(right>i)   
	{
		Sort(dRange,i,right);
	}
}

CRtCfgRecordTest *CRtCfgRecordTests::FindByTestType(const CString &strTestType)
{
	CRtCfgRecordTest *pCfgRecordTest = NULL;
	CRtCfgRecordTest *pFind = NULL;
	POS pos  = GetHeadPosition();

	while(pos != NULL)
	{
		pCfgRecordTest = (CRtCfgRecordTest *)GetNext(pos);
		ASSERT(pCfgRecordTest != NULL);

		if ( pCfgRecordTest->m_strTestType == strTestType )
		{
			pFind = pCfgRecordTest;
			break;
		}
	}

	return pFind;
}

//####################CRtTypes#############################
const char *CRtTypes::g_pszKeyTypes				= "rt-types";

const char *CRtTypes::g_pszKeyGenerTransformer	= "generator-transformer";
const char *CRtTypes::g_pszKeyCircuitGroup		= "circuit-group";
const char *CRtTypes::g_pszKeyOther				= "other";
const char *CRtTypes::g_pszKeyUniversal			= "universal";

CRtTypes* CRtTypes::g_pRtTypes      = NULL;
long  CRtTypes::m_nRtTypesRefCount	= 0;

CRtTypes* CRtTypes::CreateRtTypes()
{
	m_nRtTypesRefCount++;

	if (m_nRtTypesRefCount == 1)
	{
		g_pRtTypes = new CRtTypes();
	}

	return g_pRtTypes;
}

void CRtTypes::Release()
{
	m_nRtTypesRefCount--;

	if (m_nRtTypesRefCount == 0)
	{
		delete g_pRtTypes;
		g_pRtTypes = NULL;
	}
}

CRtTypes::CRtTypes()
{
	m_strName = "Rt_Types";
}

CRtTypes::~CRtTypes()
{
	
}
// 	
// long CRtTypes::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)	
// {
// 	return 0;
// }
// 	
// CExBaseObject* CRtTypes::CreateNewChild(LPCTSTR pszClassID)
// {
// 	CExBaseObject *pNew = NULL;
// 
// 	if (_stricmp(pszClassID, CRtType::g_pszKeyType) == 0)
// 	{
// 		pNew = new CRtType();
// 	}
// 
// 	return pNew;
// }
// 
// CRtType* CRtTypes::Clone(const CString &strID)
// {
// 	CRtType *pRtType = (CRtType *)FindByID(strID);
// 	CRtType *pNew = NULL;
// 
// 	if (pRtType != NULL)
// 	{
// 		pNew = pRtType->Clone();
// 	}
// 
// 	return pNew;
// }


//####################CRtType#############################
const char *CRtType::g_pszKeyType  = "rt-type";

CRtType::CRtType()
{
}

CRtType::~CRtType()
{
	RemoveAll();
}
// 	
// long CRtType::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CExBaseObject::ReadOwnXml(oNode);
// 	return 0;
// }
// 
// CRtType* CRtType::Clone()
// {
// 	CRtType *pNew = new CRtType();
// 
// 	pNew->m_strName = m_strName;
// 	pNew->m_strID   = m_strID;
// 
// 	return pNew;
// }
// 



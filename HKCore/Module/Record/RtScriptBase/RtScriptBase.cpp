// RtScriptBase.cpp: implementation of the CRtScriptBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtScriptBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const BSTR CRtScriptBase::g_pszKeyScript = L"script";
const BSTR CRtScriptBase::g_pszKeyLeft   = L"left";
const BSTR CRtScriptBase::g_pszKeyRight  = L"right";
const BSTR CRtScriptBase::g_pszKeyOptr   = L"optr";
const BSTR CRtScriptBase::g_pszKeyVal    = L"val";

const char* CRtScriptBase::g_pszOperator[35]= { "+" , "-" , "*" , "/" ,
"<" , "<=" , ">" , ">=" , "==" , "||" , "&&" , "!" , 
"sin" , "cos" , "exp" , "sqrt" , "log10" , "tan" , "ctan" , "asin" , "acos" , "atan2" ,
"abs" , "log" , "min" , "max" , "pow" , "ceil" , "floor" , "hypot" ,
"atan" , "fmod" , "digit" , "binary" , "mutation" };



CRtScriptBase::CRtScriptBase()
{
	m_pExpRoot = NULL;
	m_nIndex = 0;
	m_bHasError = FALSE;
}

CRtScriptBase::~CRtScriptBase()
{
	ReleaseExpNodes();
}

BOOL CRtScriptBase::ReleaseExpNodes()
{
	return FreeExpNode(m_pExpRoot);
}

void CRtScriptBase::ReadExpNodes(CXmlRWNodeBase &oScript)
{
//	MSXML2::IXMLDOMNodeListPtr oNodes = oScript->GetchildNodes();
//	m_pExpRoot = ReadExpNode(oNodes);
}

void CRtScriptBase::WriteExpNodes(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement)
{
	WriteExpNode(oXMLDoc, oElement, m_pExpRoot);
}

void CRtScriptBase::WriteExpNode(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, PEXPNODE pNode)
{
// 	MSXML2::IXMLDOMElementPtr oLeft = NULL;
// 	MSXML2::IXMLDOMElementPtr oRight = NULL;
// 	MSXML2::IXMLDOMElementPtr oOptr = NULL;
// 
// 	if(pNode == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (pNode->pLeft != NULL)
// 	{
// 		oLeft = oXMLDoc->createElement(_bstr_t(g_pszKeyLeft));
// 		oLeft->setAttribute((g_pszKeyVal), _bstr_t(pNode->pLeft->pszID));
// 		WriteExpNode(oXMLDoc, oLeft,pNode->pLeft);
// 		oElement->appendChild(oLeft);
// 	}
// 
// 	if (pNode->nOptrID > 0)
// 	{
// 		oOptr = oXMLDoc->createElement(_bstr_t(g_pszKeyOptr));
// 		oOptr->setAttribute(_bstr_t(g_pszKeyOptr), _bstr_t(m_strOptr));	
// 		WriteExpNode(oXMLDoc, oOptr, NULL);
// 		oElement->appendChild(oOptr);
// 	}
// 
// 	if (pNode->pRight != NULL)
// 	{
// 		oRight = oXMLDoc->createElement(_bstr_t(g_pszKeyRight));
// 		oRight->setAttribute(_bstr_t(g_pszKeyVal), _bstr_t(pNode->pRight->pszID));	
// 		WriteExpNode(oXMLDoc, oRight,pNode->pRight);
// 		oElement->appendChild(oRight);
// 	}
// 	

// 	if (pNode-> != NULL)
// 	{
// 		oRight = oXMLDoc->createElement(_bstr_t(CRtScript::g_pszKeyScript));
// 		oRight->setAttribute(_bstr_t(g_pszKeyVal), _bstr_t(pNode->pRight->pszID));	
// 		oElement->appendChild(oRight);
// 	}


}

BOOL CRtScriptBase::RunExpression(double &dValue)
{
	if (m_bHasError)
	{
		return FALSE;
	}

	if (m_pExpRoot != NULL)
	{
		dValue = CalNode(m_pExpRoot);
	}
	return TRUE;
}

BOOL CRtScriptBase::RunExpression(float &fValue)
{
	if (m_bHasError)
	{
		return FALSE;
	}
/*
	if (CalExpNode(m_pExpRoot))
	{
		fValue = *((float*)m_pExpRoot->pValue);
	}
	else
	{
		debug_trace("Run Expression failed!");//输出到调试监视日志文件
		return FALSE;
	}
*/
	fValue = (float)CalNode(m_pExpRoot);

	return TRUE;
}

BOOL CRtScriptBase::RunExpression(long &nValue)
{
	if (m_bHasError)
	{
		return FALSE;
	}

	nValue = (long)CalNode(m_pExpRoot);
	
	return TRUE;
}

BOOL CRtScriptBase::RunExpression(short &nValue)
{
	if (m_bHasError)
	{
		return FALSE;
	}

	if (CalExpNode(m_pExpRoot))
	{
		nValue = (short)*((long*)m_pExpRoot->pValue);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Run Expression failed!"));//输出到调试监视日志文件
		return FALSE;
	}
	
	return TRUE;
}

BOOL CRtScriptBase::RunExpression()
{
	if (m_bHasError)
	{
		return FALSE;
	}

	return CalExpNode(m_pExpRoot);
}

BOOL CRtScriptBase::BuildExpression()
{
	if (BuildExpNode(m_pExpRoot)) 
	{
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build Expression Nodes failed!"));
	}

	return TRUE;
}

CRtScriptBase::PEXPNODE CRtScriptBase::NewExpNode()
{
	PEXPNODE pNode = new EXPNODE();
	
	if (pNode != NULL)
	{
		memset(pNode, 0, sizeof(EXPNODE));
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("...................") );
	}
	
	return pNode;
}

long CRtScriptBase::ReadOwnXml(CXmlRWNodeBase &oNode)
{
	ReadExpNodes(oNode);
	
	return 0;
}

void CRtScriptBase::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand, HTREEITEM hAfter)
{
	CExBaseObject::InsertTreeCtrl(pTreeCtrl, htiParent, bParentExpand);
	InsertTreeCtrl(pTreeCtrl, (HTREEITEM)m_dwItemData, m_pExpRoot);
}

void CRtScriptBase::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, PEXPNODE pNode)
{
	HTREEITEM hItem = NULL;
	CString strTemp;

	if (pNode->nOptrID == RTSCRIPT_OPTRID_NUMBER)
	{
		strTemp.Format("%f", *(double*)pNode->pValue);
	}
	else if (pNode->nOptrID == RTSCRIPT_OPTRID_REFVALUE)
	{
		strTemp.Format("%s", pNode->pszID);
	}
	else if (pNode->nOptrID == RTSCRIPT_OPTRID_ERROR)
	{
		m_bHasError = TRUE;
		strTemp = "error";
	}
	else
	{
		strTemp.Format("%s", g_pszOperator[pNode->nOptrID-RTSCRIPT_OPTRID_ADD]);
	}

	hItem = pTreeCtrl->InsertItem(strTemp, 0, 0, htiParent);

	if (pNode->pLeft != NULL)
	{
		InsertTreeCtrl(pTreeCtrl, hItem, pNode->pLeft);
	}

	if (pNode->pRight != NULL)
	{
		InsertTreeCtrl(pTreeCtrl, hItem, pNode->pRight);
	}
}

CRtScriptBase::PEXPNODE CRtScriptBase::ReadExpNode(CXmlRWNodeListBase &oNodes)
{
	PEXPNODE pLeft = NULL, pRight = NULL, pOptr = NULL;
	
// 	MSXML2::IXMLDOMNodePtr oNode = NULL;
// 	long nCount = oNodes.Getlength();
// 	long nIndex = 0;
// 	CString strTag;
// 	
// 	for (nIndex=0; nIndex<nCount; nIndex++)
// 	{
// 		oNode  = oNodes.Getitem(nIndex);
// 		strTag = (char*)oNode->GetnodeName();
// 		
// 		if (strTag == g_pszKeyLeft)
// 		{
// 			pLeft = ReadOperandNode(oNode);
// 		}
// 		else if (strTag == g_pszKeyOptr)
// 		{
// 			pOptr = NewExpNode();
// 			pOptr->pValue = new double[1];
// 			pOptr->nOptrID = ReadOperatorNode(oNode);
// 		}
// 		else if (strTag == g_pszKeyRight)
// 		{
// 			pRight = ReadOperandNode(oNode);
// 		}
// 		else
// 		{
// 			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("..................."));
// 		}
// 		
// 	}	
// 	
// 	if (pOptr == NULL)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("....................") );
// 		if (pLeft != NULL)
// 		{
// 			FreeExpNode(pLeft);
// 		}
// 		if (pRight != NULL)
// 		{
// 			FreeExpNode(pRight);
// 		}
// 	}
// 	else
// 	{
// 		pOptr->pLeft = pLeft;
// 		pOptr->pRight = pRight;
// 	}
// 	
	return pOptr;
}

BOOL CRtScriptBase::CalExpNode(PEXPNODE pNode, UINT nIndex)
{
	if (pNode->nOptrID == RTSCRIPT_OPTRID_REFVALUE || pNode->nOptrID == RTSCRIPT_OPTRID_NUMBER)
	{
		return TRUE;
	}

	PEXPNODE pLeft		    = pNode->pLeft;
	PEXPNODE pRight			= pNode->pRight;
	unsigned long nOptrID   = pNode->nOptrID;
	double *pValue			= (double*)pNode->pValue;
	if(pLeft!=NULL)
	{
		if(!CalExpNode(pLeft))
		{
			TRACE("…………");
			return FALSE;
		}
	}
	
	if(pRight!=NULL)
	{
		if(!CalExpNode(pRight))
		{
			TRACE("…………");
			return FALSE;
		}
	}
	
	switch(nOptrID)
	{
	case RTSCRIPT_OPTRID_REFVALUE:
	case RTSCRIPT_OPTRID_NUMBER:
		break;
	case RTSCRIPT_OPTRID_ADD:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = (*((double*)pLeft->pValue)) + (*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_SUB:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue=(*((double*)pLeft->pValue)) - (*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_MUL:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue=(*((double*)pLeft->pValue)) * (*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_DIV:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			double absValue = fabs(*((double*)pRight->pValue));
			if (absValue > ZERO_VALUE)
			{
				*pValue = (*((double*)pLeft->pValue)) / (*((double*)pRight->pValue));
			}
			else
			{
				double absValue2 = fabs(*((double*)pLeft->pValue));
				if (absValue2 > ZERO_VALUE)
				{
					*pValue = *((double*)pLeft->pValue) / ZERO_VALUE;
				}
				else
				{
					*pValue = 0;
				}
			}
		}
		break;
	case RTSCRIPT_OPTRID_L:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = (*((double*)pLeft->pValue)) < (*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_LE:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = (*((double*)pLeft->pValue)) <= (*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_G:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = (*((double*)pLeft->pValue)) > (*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_GE:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = (*((double*)pLeft->pValue)) >= (*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_E:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = (*((double*)pLeft->pValue)) == (*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_OR:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = (*((double*)pLeft->pValue)) || (*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_AND:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = (*((double*)pLeft->pValue)) && (*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_NOT:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = !(*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_SIN:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = sin(*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_COS:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = cos(*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_EXP:
		{
			ASSERT(pRight != NULL);
			*pValue = exp(*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_SQRT:
		{
			ASSERT(pRight != NULL);
			*pValue = sqrt(*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_LOG10:
		{
			ASSERT(pRight != NULL);
			*pValue = log10(*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_TAN:
		{
			ASSERT(pRight != NULL);
			*pValue = tan(*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_CTAN:
		{
			ASSERT(pRight != NULL);
			double Value = tan(*((double*)pRight->pValue));
			if (Value>ZERO_VALUE || Value<(0-ZERO_VALUE))
			{
				*pValue = 1 / (tan(*((double*)pRight->pValue)));
			}
			else
			{
				if (Value >= 0)
				{
					*pValue = 1 / ZERO_VALUE;
				}
				else
				{
					*pValue = 0 - 1 / ZERO_VALUE;
				}
			}
		}
		break;
	case RTSCRIPT_OPTRID_ASIN:
		{
			ASSERT(pRight != NULL);
			*pValue = asin(*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_ACOS:
		{
			ASSERT(pRight != NULL);
			*pValue = acos(*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_ATAN2:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = atan2((*((double*)pLeft->pValue)), (*((double*)pRight->pValue)));
		}
		break;
	case RTSCRIPT_OPTRID_ABS:
		{
			ASSERT(pRight != NULL);
			*pValue = fabs(*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_LOG:
		{
			ASSERT(pRight != NULL);
			*pValue = log(*((double*)pRight->pValue));
		}
		break;
	case RTSCRIPT_OPTRID_MIN:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			double val = *((double*)pLeft->pValue);
			double val2 = *((double*)pRight->pValue);
			if (val < val2)
			{
				*pValue = val;
			}
			else
			{
				*pValue = val2;
			}
		}
		break;
	case RTSCRIPT_OPTRID_MAX:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			double val = *((double*)pLeft->pValue);
			double val2 = *((double*)pRight->pValue);
			if (val < val2)
			{
				*pValue = val2;
			}
			else
			{
				*pValue = val;
			}
		}
		break;
	case RTSCRIPT_OPTRID_POW:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = pow((*((double*)pLeft->pValue)), (*((double*)pRight->pValue)));
		}
		break;
	case RTSCRIPT_OPTRID_CEIL:
		{
			ASSERT(pRight != NULL);
			*pValue = ceil((*((double*)pRight->pValue)));
		}
		break;
	case RTSCRIPT_OPTRID_FLOOR:
		{
			ASSERT(pRight != NULL);
			*pValue = floor((*((double*)pRight->pValue)));
		}
		break;
	case RTSCRIPT_OPTRID_HYPOT:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = hypot((*((double*)pLeft->pValue)), (*((double*)pRight->pValue)));
		}
		break;
	case RTSCRIPT_OPTRID_ATAN:
		{
			ASSERT(pRight != NULL);
			*pValue = atan((*((double*)pRight->pValue)));
		}
		break;
	case RTSCRIPT_OPTRID_FMOD:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			*pValue = fmod((*((double*)pLeft->pValue)), (*((double*)pRight->pValue)));
		}
		break;
	default:
		break;
	}
	return TRUE;
}


double CRtScriptBase::CalNode(PEXPNODE pNode, UINT nIndex)
{
	if (pNode->pValue == NULL)
	{
		m_bHasError = TRUE;
		return 0;
	}
	
	if (pNode->nOptrID == RTSCRIPT_OPTRID_REFVALUE || pNode->nOptrID == RTSCRIPT_OPTRID_NUMBER)
	{
		return *((double*)pNode->pValue);
	}
	
//	PEXPNODE pLeft		    = pNode->pLeft;
//	PEXPNODE pRight			= pNode->pRight;
//	double *pValue			= (double*)pNode->pValue;
//	if(pLeft!=NULL)
//	{
//		if(!CalExpNode(pLeft))
//		{
//			TRACE("…………");
//			return FALSE;
//		}
//	}
//	
//	if(pRight!=NULL)
//	{
//		if(!CalExpNode(pRight))
//		{
//			TRACE("…………");
//			return FALSE;
//		}
//	}
	
	switch(pNode->nOptrID)
	{
//	case RTSCRIPT_OPTRID_REFVALUE:
//	case RTSCRIPT_OPTRID_NUMBER:
//		break;
	case RTSCRIPT_OPTRID_ADD:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			//*pValue = (*((double*)pNode->pLeft->pValue)) + (*((double*)pNode->pRight->pValue));
			return CalNode(pNode->pLeft) + CalNode(pNode->pRight);
		}
		break;
	case RTSCRIPT_OPTRID_SUB:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return CalNode(pNode->pLeft) - CalNode(pNode->pRight);
		}
		break;
	case RTSCRIPT_OPTRID_MUL:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return CalNode(pNode->pLeft) * CalNode(pNode->pRight);
		}
		break;
	case RTSCRIPT_OPTRID_DIV:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return CalNode(pNode->pLeft) / CalNode(pNode->pRight);
		}
		break;
	case RTSCRIPT_OPTRID_L:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return CalNode(pNode->pLeft) < CalNode(pNode->pRight);
		}
		break;
	case RTSCRIPT_OPTRID_LE:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return CalNode(pNode->pLeft) <= CalNode(pNode->pRight);
		}
		break;
	case RTSCRIPT_OPTRID_G:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return CalNode(pNode->pLeft) > CalNode(pNode->pRight);
		}
		break;
	case RTSCRIPT_OPTRID_GE:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return CalNode(pNode->pLeft) >= CalNode(pNode->pRight);
		}
		break;
	case RTSCRIPT_OPTRID_E:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return CalNode(pNode->pLeft) == CalNode(pNode->pRight);
		}
		break;
	case RTSCRIPT_OPTRID_OR:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return CalNode(pNode->pLeft) || CalNode(pNode->pRight);
		}
		break;
	case RTSCRIPT_OPTRID_AND:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return CalNode(pNode->pLeft) && CalNode(pNode->pRight);
		}
		break;
	case RTSCRIPT_OPTRID_NOT:
		{
			ASSERT(pNode->pRight != NULL);
			return CalNode(pNode->pRight) <= ZERO_VALUE;
		}
		break;
	case RTSCRIPT_OPTRID_SIN:
		{
			ASSERT(pNode->pRight != NULL);
			return sin(CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_COS:
		{
			ASSERT(pNode->pRight != NULL);
			return cos(CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_EXP:
		{
			ASSERT(pNode->pRight != NULL);
			return exp(CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_SQRT:
		{
			ASSERT(pNode->pRight != NULL);
			return sqrt(CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_LOG10:
		{
			ASSERT(pNode->pRight != NULL);
			return log10(CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_TAN:
		{
			ASSERT(pNode->pRight != NULL);
			return tan(CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_CTAN:
		{
			ASSERT(pNode->pRight != NULL);
			return 1 / tan(CalNode(pNode->pRight));			
		}
		break;
	case RTSCRIPT_OPTRID_ASIN:
		{
			ASSERT(pNode->pRight != NULL);
			return asin(CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_ACOS:
		{
			ASSERT(pNode->pRight != NULL);
			return acos(CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_ATAN2:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return atan2(CalNode(pNode->pLeft), CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_ABS:
		{
			ASSERT(pNode->pRight != NULL);
			return fabs(CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_LOG:
		{
			ASSERT(pNode->pRight != NULL);
			return log(CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_MIN:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return min(CalNode(pNode->pLeft), CalNode(pNode->pRight));
			
		}
		break;
	case RTSCRIPT_OPTRID_MAX:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return max(CalNode(pNode->pLeft), CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_POW:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return pow(CalNode(pNode->pLeft), CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_CEIL:
		{
			ASSERT(pNode->pRight != NULL);
			return min(CalNode(pNode->pLeft), CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_FLOOR:
		{
			ASSERT(pNode->pRight != NULL);
			return floor(CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_HYPOT:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return hypot(CalNode(pNode->pLeft), CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_ATAN:
		{
			ASSERT(pNode->pRight != NULL);
			return atan(CalNode(pNode->pRight));
		}
		break;
	case RTSCRIPT_OPTRID_FMOD:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
			return fmod(CalNode(pNode->pLeft), CalNode(pNode->pRight));
		}
		break;
	default:
		break;
	}

	return 0;
}

BOOL CRtScriptBase::FreeExpNode(PEXPNODE pNode)
{
	if (pNode == NULL)
	{
		return FALSE;
	}
	
	if (pNode->pLeft != NULL)
	{
		FreeExpNode(pNode->pLeft);
	}
	else
	{
	}

	if (pNode->pRight != NULL)
	{
		FreeExpNode(pNode->pRight);
	}
	else
	{		
	}

	if (pNode->pszID != NULL)
	{
		delete pNode->pszID;
		pNode->pszID = NULL;
	}
			
	if (pNode->nOptrID == -1||pNode->nOptrID == 0)
	{
	}
	else
	{
		delete pNode->pValue;
		pNode->pValue = NULL;
	}
	
	delete pNode;
	pNode = NULL;

	return TRUE;
}

CRtScriptBase::PEXPNODE CRtScriptBase::CloneExpNode(CRtScriptBase::PEXPNODE pNode)
{
	if (pNode == NULL)
	{
		return NULL;
	}
	
	PEXPNODE pNewNode = NewExpNode();
	*pNewNode = *pNode;

	if (pNode->pLeft != NULL)
	{
		pNewNode->pLeft = CloneExpNode(pNode->pLeft);
	}
	else
	{
	}
	
	if (pNode->pRight != NULL)
	{
		pNewNode->pRight = CloneExpNode(pNode->pRight);
	}
	else
	{		
	}
	
	if (pNode->pszID != NULL)
	{
		long nLen = strlen(pNode->pszID);
		pNewNode->pszID = new char[nLen+1];
		strcpy(pNewNode->pszID, pNode->pszID);
	}
	
	pNewNode->pValue = NULL;

	return pNewNode;	
}

BOOL CRtScriptBase::BuildExpNode(PEXPNODE pNode)
{
	if(pNode == NULL)
	{
		return FALSE;
	}
	
	if(pNode->pLeft != NULL)
	{
		BuildExpNode(pNode->pLeft);
	}
	
	if(pNode->pRight != NULL)
	{
		BuildExpNode(pNode->pRight);
	}
	
	if(pNode->pszID != NULL  && pNode->m_nIsRefValue == 1)
	{
		pNode->dCoef = GetCoefValueByID(pNode->pszID);
		//在此判断mutation函数调用		
		pNode->pValue = GetValueRefByID(pNode->pszID);
		
		if (pNode->pValue == NULL)
		{
			m_bHasError = TRUE;
		}	
	}
	else
	{
		
	}
	
	return TRUE;
}

BOOL CRtScriptBase::BuildExpNodeCoef(PEXPNODE pNode)
{
	if(pNode == NULL)
	{
		return FALSE;
	}
	
	if(pNode->pLeft != NULL)
	{
		BuildExpNodeCoef(pNode->pLeft);
	}
	
	if(pNode->pRight != NULL)
	{
		BuildExpNodeCoef(pNode->pRight);
	}
	
	if(pNode->pszID != NULL  && pNode->m_nIsRefValue == 1)
	{
		//在此判断mutation函数调用		
		pNode->dCoef = GetCoefValueByID(pNode->pszID);
	}
	
	return TRUE;
}

CRtScriptBase::PEXPNODE CRtScriptBase::ReadOperandNode(CXmlRWNodeBase &oOperand)
{
	PEXPNODE pOperand = NULL;
// 	CString strValue;
// 	xml_GetAttibuteValue(g_pszKeyVal, oOperand,strValue);
// 	
// 	if (strValue == "")//节点为表达式
// 	{
// 		MSXML2::IXMLDOMNodeListPtr oChildren = oOperand->GetchildNodes();
// 		pOperand = ReadExpNode(oChildren);	
// // 		if (pOperand != NULL)
// // 		{
// // 			pOperand->pValue = new double[1];
// // 		}
// 	}
// 	else if (IsStringNumber(strValue))//数字
// 	{
// 		pOperand = NewExpNode();
// 		pOperand->pValue = new double[1];
// 		pOperand->nOptrID = 1;
// 		*((double*)pOperand->pValue) = atof(strValue);
// 	}
// 	else //关联定值或者通道数据属性
// 	{		
// 		pOperand = NewExpNode();
// 		pOperand->pszID = new char[strValue.GetLength() + 1];
// 		strcpy(pOperand->pszID, strValue);
// 		pOperand->m_nIsRefValue = 1;
// 	}
	
	return pOperand;
}

unsigned long CRtScriptBase::ReadOperatorNode(CXmlRWNodeBase &oNode)
{	
	long nOptrID = -1;
	CString strValue;

	xml_GetAttibuteValue(g_pszKeyOptr, oNode,strValue);
	m_strOptr = strValue;

	for (long nIndex=0; nIndex<35; nIndex++)
	{
		if (strValue == g_pszOperator[nIndex])
		{
			nOptrID = nIndex + 2;
			break;
		}
	}
	
	return nOptrID;

}

long CRtScriptBase::RTUpdateOwnByAutofit(HDINFO &oHDInfo)
{
	RTUpdateExpNode(m_pExpRoot, oHDInfo);
	return 0;
}

long CRtScriptBase::RTUpdateExpNode(PEXPNODE pNode, HDINFO &oHDInfo)
{
	if (pNode == NULL)
	{
		return -1;
	}

	CString strTemp, strName;

	if (pNode->pLeft != NULL)
	{
		strName = pNode->pLeft->pszID;
		
		if (!oHDInfo.bDCTran)
		{
			strTemp.Format(strName, oHDInfo.nTranIndex + 1, oHDInfo.nTranChIndex + 1);
		}
		else
		{
			strTemp.Format(strName, oHDInfo.nDCUIChIndexInTran);
		}

		//2020-09-08 xiexiaoyong
		//strcpy(pNode->pLeft->pszID, strTemp);
		CString_to_char(strTemp, pNode->pLeft->pszID);
		RTUpdateExpNode(pNode->pLeft, oHDInfo);
	}
	else
	{
	}

	if (pNode->pRight!= NULL)
	{
		strName = pNode->pRight->pszID;

		if (!oHDInfo.bDCTran)
		{
			strTemp.Format(strName, oHDInfo.nTranIndex + 1, oHDInfo.nTranChIndex + 1);
		}
		else
		{
			strTemp.Format(strName, oHDInfo.nDCUIChIndexInTran);
		}

		//strcpy(pNode->pRight->pszID, strTemp);
		CString_to_char(strTemp, pNode->pRight->pszID);
		RTUpdateExpNode(pNode->pRight, oHDInfo);
	}
	else
	{
	}

	return 0;
}

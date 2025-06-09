// RtMemBufScript.cpp: implementation of the CRtMemBufScript class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtMemBufScript.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRtComplexBufLongScript::CRtComplexBufLongScript()
{

}

CRtComplexBufLongScript::~CRtComplexBufLongScript()
{
	ReleaseExpNodes();
}

BOOL CRtComplexBufLongScript::ReleaseExpNodes()
{
	if (m_pExpRoot->pLeft != NULL)
	{
		FreeExpNode(m_pExpRoot->pLeft);
	}
	else
	{
	}
	
	if (m_pExpRoot->pRight != NULL)
	{
		FreeExpNode(m_pExpRoot->pRight);
	}
	else
	{		
	}
	
	if (m_pExpRoot->pszID != NULL)
	{
		delete m_pExpRoot->pszID;
	}
	
	delete m_pExpRoot;
	m_pExpRoot = NULL;

	return TRUE;
}


BOOL CRtComplexBufLongScript::CalExpNode(CRtScriptBase::PEXPNODE pNode, UINT nIndex)
{
//	PEXPNODE pLeft		    = pNode->pLeft;
//	PEXPNODE pRight			= pNode->pRight;
//	unsigned long nOptrID   = pNode->nOptrID;
//	unsigned short *pValue	= ((unsigned short*)pNode->pValue) + m_nIndex;
//
//	if(pLeft!=NULL)
//	{
//		if (pLeft->nOptrID != RTSCRIPT_OPTRID_REFVALUE)
//		{
//			if(!CalExpNode(pLeft))
//			{
//				return FALSE;
//			}
//		}
//	}
//	
//	if(pRight!=NULL)
//	{
//		if (pRight->nOptrID != RTSCRIPT_OPTRID_REFVALUE)
//		{
//			if(!CalExpNode(pRight))
//			{
//				return FALSE;
//			}
//		}
//	}
//	
//	switch(nOptrID)
//	{
//	case 0: //RTSCRIPT_OPTRID_ERROR
//	case 1: //RTSCRIPT_OPTRID_REFVALUE
//		break;
//		
//	case RTSCRIPT_OPTRID_ADD:
//		{
//			ASSERT(pLeft != NULL && pRight != NULL);
//			int nLeft  = (short)*( (unsigned short*)pLeft->pValue + m_nIndex);
//			int nRight = (short)*( (unsigned short*)pRight->pValue + m_nIndex);
//			nLeft += nRight;
//			*pValue = nLeft;
//			//TRANS_TO_SHORT(nLeft, *pValue);
//		}
//		break;
//	case RTSCRIPT_OPTRID_SUB:
//		{
//			ASSERT(pLeft != NULL && pRight != NULL);
//			float fLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
//			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
//			fLeft -= fRight;
//			*pValue = fLeft;
//			//TRANS_TO_SHORT(fLeft, *pValue);
//		}
//		break;
//	case RTSCRIPT_OPTRID_MUL:
//		{
//			ASSERT(pLeft != NULL && pRight != NULL);
//			float fLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
//			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
//			fLeft *= fRight;
//			*pValue = fLeft;
//			//TRANS_TO_SHORT(fLeft, *pValue);
//		}
//		break;
//	case RTSCRIPT_OPTRID_DIV:
//		{
//			ASSERT(pLeft != NULL && pRight != NULL);
//			float fLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
//			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
//			fLeft /= fRight;
//			*pValue = fLeft;
//			//TRANS_TO_SHORT(fLeft, *pValue);
//		}
//		break;
//	case RTSCRIPT_OPTRID_EXP:
//		{
//			ASSERT(pRight != NULL);
//			float fValue = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
//			fValue = (float)exp(fValue);
//			TRANS_TO_SHORT(fValue, *pValue);
//		}
//		break;
//	case RTSCRIPT_OPTRID_SQRT:
//		{
//			ASSERT(pRight != NULL);
//			float fValue = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
//			fValue = (float)sqrt(fValue);
//			TRANS_TO_SHORT(fValue, *pValue);
//		}
//		break;
//	case RTSCRIPT_OPTRID_ABS:
//		{
//			ASSERT(pRight != NULL);
//			float fValue = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
//			fValue = (float)fabs(fValue);
//			TRANS_TO_SHORT(fValue, *pValue);
//		}
//		break;
//	case RTSCRIPT_OPTRID_MIN:
//		{
//			ASSERT(pLeft != NULL && pRight != NULL);
//			int nLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
//			int nRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
//
//			if (nLeft > nRight)
//			{
//				nLeft = nRight;
//			}
//
//			TRANS_TO_SHORT(nLeft, *pValue);
//		}
//		break;
//	case RTSCRIPT_OPTRID_MAX:
//		{
//			ASSERT(pLeft != NULL && pRight != NULL);
//			int nLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
//			int nRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
//			
//			if (nLeft < nRight)
//			{
//				nLeft = nRight;
//			}
//			
//			TRANS_TO_SHORT(nLeft, *pValue);
//		}
//		break;
//	case RTSCRIPT_OPTRID_POW:
//		{
//			ASSERT(pLeft != NULL && pRight != NULL);
//			float fLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
//			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
//			fLeft = (float)pow(fLeft, fRight);
//			TRANS_TO_SHORT(fLeft, *pValue);
//		}
//		break;
//	case RTSCRIPT_OPTRID_CEIL:
//		{
//			ASSERT(pRight != NULL);
//			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
//			fRight = (float)ceil(fRight);
//			TRANS_TO_SHORT(fRight, *pValue);
//		}
//		break;
//	case RTSCRIPT_OPTRID_FLOOR:
//		{
//			ASSERT(pRight != NULL);
//			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
//			fRight = (float)floor(fRight);
//			TRANS_TO_SHORT(fRight, *pValue);
//		}
//		break;
//	case RTSCRIPT_OPTRID_HYPOT:
//		{
//			ASSERT(pLeft != NULL && pRight != NULL);
//			float fLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
//			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
//			fLeft = (float)hypot(fLeft, fRight);
//			TRANS_TO_SHORT(fLeft, *pValue);
//		}
//		break;
//	default:
//		break;
//	}

	return TRUE;
}


double CRtComplexBufLongScript::CalNode(PEXPNODE pNode, UINT nIndex)
{
	if (pNode->nOptrID == RTSCRIPT_OPTRID_NUMBER)
	{
		return *((double*)pNode->pValue);
	}
	else if (pNode->nOptrID == RTSCRIPT_OPTRID_REFVALUE)
	{
		return *((unsigned short*)pNode->pValue+m_nIndex);
	}
	else
	{
	}
	
	switch(pNode->nOptrID)
	{
	case RTSCRIPT_OPTRID_ADD:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRtComplexBufUShortScript::CRtComplexBufUShortScript()
{

}

CRtComplexBufUShortScript::~CRtComplexBufUShortScript()
{
	ReleaseExpNodes();
}

BOOL CRtComplexBufUShortScript::ReleaseExpNodes()
{
	if (m_pExpRoot->pLeft != NULL)
	{
		FreeExpNode(m_pExpRoot->pLeft);
	}
	else
	{
	}
	
	if (m_pExpRoot->pRight != NULL)
	{
		FreeExpNode(m_pExpRoot->pRight);
	}
	else
	{		
	}
	
	if (m_pExpRoot->pszID != NULL)
	{
		delete m_pExpRoot->pszID;
	}
	
	delete m_pExpRoot;
	m_pExpRoot = NULL;

	return TRUE;
}


BOOL CRtComplexBufUShortScript::CalExpNode(CRtScriptBase::PEXPNODE pNode, UINT nIndex)
{
	PEXPNODE pLeft		    = pNode->pLeft;
	PEXPNODE pRight			= pNode->pRight;
	unsigned long nOptrID   = pNode->nOptrID;
	unsigned short *pValue	= ((unsigned short*)pNode->pValue) + m_nIndex;

	if(pLeft!=NULL)
	{
		if (pLeft->nOptrID != RTSCRIPT_OPTRID_REFVALUE)
		{
			if(!CalExpNode(pLeft))
			{
				return FALSE;
			}
		}
	}
	
	if(pRight!=NULL)
	{
		if (pRight->nOptrID != RTSCRIPT_OPTRID_REFVALUE)
		{
			if(!CalExpNode(pRight))
			{
				return FALSE;
			}
		}
	}
	
	switch(nOptrID)
	{
	case 0: //RTSCRIPT_OPTRID_ERROR
	case 1: //RTSCRIPT_OPTRID_REFVALUE
		break;
		
	case RTSCRIPT_OPTRID_ADD:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			int nLeft  = (short)*( (unsigned short*)pLeft->pValue + m_nIndex);
			int nRight = (short)*( (unsigned short*)pRight->pValue + m_nIndex);
			nLeft += nRight;
			TRANS_TO_SHORT(nLeft, *pValue);
		}
		break;
	case RTSCRIPT_OPTRID_SUB:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			float fLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
			fLeft -= fRight;
			TRANS_TO_SHORT(fLeft, *pValue);
		}
		break;
	case RTSCRIPT_OPTRID_MUL:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			float fLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
			fLeft *= fRight;
			TRANS_TO_SHORT(fLeft, *pValue);
		}
		break;
	case RTSCRIPT_OPTRID_DIV:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			float fLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
			fLeft /= fRight;
			TRANS_TO_SHORT(fLeft, *pValue);
		}
		break;
	case RTSCRIPT_OPTRID_EXP:
		{
			ASSERT(pRight != NULL);
			float fValue = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
			fValue = (float)exp(fValue);
			TRANS_TO_SHORT(fValue, *pValue);
		}
		break;
	case RTSCRIPT_OPTRID_SQRT:
		{
			ASSERT(pRight != NULL);
			float fValue = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
			fValue = (float)sqrt(fValue);
			TRANS_TO_SHORT(fValue, *pValue);
		}
		break;
	case RTSCRIPT_OPTRID_ABS:
		{
			ASSERT(pRight != NULL);
			float fValue = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
			fValue = (float)fabs(fValue);
			TRANS_TO_SHORT(fValue, *pValue);
		}
		break;
	case RTSCRIPT_OPTRID_MIN:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			int nLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
			int nRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);

			if (nLeft > nRight)
			{
				nLeft = nRight;
			}

			TRANS_TO_SHORT(nLeft, *pValue);
		}
		break;
	case RTSCRIPT_OPTRID_MAX:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			int nLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
			int nRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
			
			if (nLeft < nRight)
			{
				nLeft = nRight;
			}
			
			TRANS_TO_SHORT(nLeft, *pValue);
		}
		break;
	case RTSCRIPT_OPTRID_POW:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			float fLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
			fLeft = (float)pow(fLeft, fRight);
			TRANS_TO_SHORT(fLeft, *pValue);
		}
		break;
	case RTSCRIPT_OPTRID_CEIL:
		{
			ASSERT(pRight != NULL);
			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
			fRight = (float)ceil(fRight);
			TRANS_TO_SHORT(fRight, *pValue);
		}
		break;
	case RTSCRIPT_OPTRID_FLOOR:
		{
			ASSERT(pRight != NULL);
			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
			fRight = (float)floor(fRight);
			TRANS_TO_SHORT(fRight, *pValue);
		}
		break;
	case RTSCRIPT_OPTRID_HYPOT:
		{
			ASSERT(pLeft != NULL && pRight != NULL);
			float fLeft = (short)*((unsigned short*)pLeft->pValue+m_nIndex);
			float fRight = (short)*((unsigned short*)pRight->pValue+m_nIndex);
			fLeft = (float)hypot(fLeft, fRight);
			TRANS_TO_SHORT(fLeft, *pValue);
		}
		break;
	default:
		break;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CRtComplexBufUShortFloatScript::CRtComplexBufUShortFloatScript()
{

}

CRtComplexBufUShortFloatScript::~CRtComplexBufUShortFloatScript()
{
	
}

BOOL CRtComplexBufUShortFloatScript::ReleaseExpNodes()
{
	return FALSE;
}

double CRtComplexBufUShortFloatScript::GetCoefValueByID(char *pszID)
{
	double dValue = 1;
	long nChIndex = 0;
	
	return dValue;
}

double CRtComplexBufUShortFloatScript::CalNode(PEXPNODE pNode, UINT nIndex)
{
	if (pNode->nOptrID == RTSCRIPT_OPTRID_NUMBER)
	{
		return *((double*)pNode->pValue);
	}
	else if (pNode->nOptrID == RTSCRIPT_OPTRID_REFVALUE)
	{
		return pNode->dCoef* ((short)(*((unsigned short*)pNode->pValue+m_nIndex)));
	}
	else
	{
	}
	
	switch(pNode->nOptrID)
	{
	case RTSCRIPT_OPTRID_ADD:
		{
			ASSERT(pNode->pLeft != NULL && pNode->pRight != NULL);
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


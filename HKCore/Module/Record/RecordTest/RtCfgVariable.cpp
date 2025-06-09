// RtCfgVariable.cpp: implementation of the CRtCfgVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtCfgVariable.h"
#include "RtCfgVariables.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char *CRtCfgVariable::g_pszKeySingleVariable		= "single-variable";
const char *CRtCfgVariable::g_pszKeyBinaryVariable		= "binary-variable";
const char *CRtCfgVariable::g_pszKeyDCAC				= "dc-ac";
const char *CRtCfgVariable::g_pszKeyRange				= "range";

CRtCfgVariable::CRtCfgVariable()
{
	m_bIsBinaryVariable = FALSE;
}

CRtCfgVariable::~CRtCfgVariable()
{
}
// 
// long CRtCfgVariable::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CExBaseObject::ReadOwnXml(oNode);
// 	CRtCfgVariables *pRtCfgVariables = (CRtCfgVariables *)this->GetParent();
// 	CString strTemp;
// 	
// 	if (xml_GetAttibuteValue(g_pszKeyType, oNode, strTemp))
// 	{
// 		if (m_bIsBinaryVariable)
// 		{
// 			m_nType = InitBinaryVariableType(strTemp);
// 			pRtCfgVariables->m_oBVariList.AddTail(this);//qhy:2009-11-12
// 		}
// 		else
// 		{
// 			m_nType = RT_GetUibVariableType(strTemp);
// 
// 			if (RT_IsVariableTypeU(m_nType)) 
// 			{
// 				pRtCfgVariables->m_oUVariList.AddTail(this);//qhy:2009-11-12
// 			}
// 			else if (RT_IsVariableTypeI(m_nType))
// 			{
// 				pRtCfgVariables->m_oIVariList.AddTail(this);//qhy:2009-11-12
// 			}
// 		}
// 	}
// 	
// 	if(xml_GetAttibuteValue(g_pszKeyDCAC, oNode, m_strDCAC))
// 	{
// 		if (!m_bIsBinaryVariable)
// 		{
// 			m_nACDC = InitVariableACDC(m_strDCAC);
// 		}
// 		else
// 		{
// 
// 		}
// 	}
// 	
// 	if (xml_GetAttibuteValue(g_pszKeyRange, oNode, strTemp))
// 	{
// 		m_dRange = atof(strTemp);
// 	}
// 	
// 	
// 	return 0;
// }
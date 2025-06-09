// Function.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "math.h"
#include "AtlExpression.h"
#include <ctype.h>
#include "..\..\Common\SystemTool\Equation.h"
#include "..\..\Module\AtlMemBuffer\AnsiStringPrintf.h"

CAtlNodeValue __stdcall operator+(const CAtlNodeValue& v1, const CAtlNodeValue& v2)
{
	CAtlNodeValue v;
	if (v1.m_VT == v2.m_VT)
	{
		if (v1.m_VT == NodeValueDouble)
		{
			v.m_VT = NodeValueDouble;
			v.m_dValue = v1.m_dValue + v2.m_dValue;
		}
		else
		{
			long nLen = 0;
			if (v1.m_pszValue != NULL)
			{
				nLen = wcslen(v1.m_pszValue);
			}
			if (v2.m_pszValue != NULL)
			{
				nLen += wcslen(v2.m_pszValue);
			}
			v.m_pszValue = new wchar_t [nLen+1];
			memset(v.m_pszValue, 0, nLen*sizeof(wchar_t));
			
			if (v1.m_pszValue != NULL)
			{
				wcscpy(v.m_pszValue, v1.m_pszValue);
				if (v2.m_pszValue != NULL)
				{
					wcscat(v.m_pszValue, v2.m_pszValue);
				}
			}
			else
			{
				if (v2.m_pszValue != NULL)
				{
					wcscpy(v.m_pszValue, v2.m_pszValue);
				}
			}
		}
	}
	else
	{
		v = v1;
	}

	return v;
}


CAtlNodeValue __stdcall operator-(const CAtlNodeValue& v1, const CAtlNodeValue& v2)
{
	CAtlNodeValue v;
	if (v1.m_VT == v2.m_VT && v1.m_VT == NodeValueDouble)
	{
		v.m_dValue = v1.m_dValue - v2.m_dValue;
	}
	else
	{
		v = _T("");
	}
	
	return v;
}

CAtlNodeValue __stdcall operator*(const CAtlNodeValue& v1, const CAtlNodeValue& v2)
{
	CAtlNodeValue v;
	if (v1.m_VT == v2.m_VT && v1.m_VT == NodeValueDouble)
	{
		v.m_dValue = v1.m_dValue * v2.m_dValue;
	}
	else
	{
		v = "";
	}
	
	return v;
}

CAtlNodeValue __stdcall operator/(const CAtlNodeValue& v1, const CAtlNodeValue& v2)
{
	CAtlNodeValue v;
	if (v1.m_VT == v2.m_VT && v1.m_VT == NodeValueDouble)
	{
		v.m_dValue = v1.m_dValue / v2.m_dValue;
	}
	else
	{
		v = "";
	}
	
	return v;
}

CAtlNodeValue __stdcall operator!=(const CAtlNodeValue& v1, const CAtlNodeValue& v2)
{
	CAtlNodeValue v;
	if (v1.m_VT == v2.m_VT && v1.m_VT == NodeValueDouble)
	{
		//v = (fabs(v1.m_dValue - v2.m_dValue)> 0.00001);
		v = (v1.m_dValue != v2.m_dValue);
	}
	else
	{
		v = (0 != wcscmp(v1.m_pszValue, v2.m_pszValue));
	}
	
	return v;
}

CAtlNodeValue __stdcall operator&&(const CAtlNodeValue& v1, const CAtlNodeValue& v2)
{
	CAtlNodeValue v;
	if (v1.m_VT == v2.m_VT && v1.m_VT == NodeValueDouble)
	{
		long n1 = (long)v1.m_dValue;
		long n2 = (long)v2.m_dValue;
		v = (n1 && n2);
	}
	else
	{
		v = 1;
	}
	
	return v;
}

CAtlNodeValue __stdcall operator||(const CAtlNodeValue& v1, const CAtlNodeValue& v2)
{
	CAtlNodeValue v;
	if (v1.m_VT == v2.m_VT && v1.m_VT == NodeValueDouble)
	{
		long n1 = (long)v1.m_dValue;
		long n2 = (long)v2.m_dValue;
		v = (n1 || n2);
	}
	else
	{
		v = 1;
	}
	
	return v;
}

CAtlNodeValue __stdcall operator < (const CAtlNodeValue& v1, const CAtlNodeValue& v2)
{
	CAtlNodeValue v;
	if (v1.m_VT == v2.m_VT && v1.m_VT == NodeValueDouble)
	{
		v = v1.m_dValue < v2.m_dValue;
	}
	else
	{
		v = (wcscmp(v1.m_pszValue, v2.m_pszValue) < 0);
	}
	
	return v;
}

CAtlNodeValue __stdcall operator > (const CAtlNodeValue& v1, const CAtlNodeValue& v2)
{
	CAtlNodeValue v;
	if (v1.m_VT == v2.m_VT && v1.m_VT == NodeValueDouble)
	{
		v = v1.m_dValue > v2.m_dValue;
	}
	else
	{
		v = (wcscmp(v1.m_pszValue, v2.m_pszValue) > 0);
	}
	
	return v;
}


CAtlNodeValue __stdcall operator <= (const CAtlNodeValue& v1, const CAtlNodeValue& v2)
{
	CAtlNodeValue v;
	if (v1.m_VT == v2.m_VT && v1.m_VT == NodeValueDouble)
	{
		v = (v1.m_dValue <= v2.m_dValue);
	}
	else
	{
		v = (wcscmp(v1.m_pszValue, v2.m_pszValue) > 0);
	}
	
	return v;
}

CAtlNodeValue __stdcall operator >= (const CAtlNodeValue& v1, const CAtlNodeValue& v2)
{
	CAtlNodeValue v;
	if (v1.m_VT == v2.m_VT && v1.m_VT == NodeValueDouble)
	{
		v = (v1.m_dValue >= v2.m_dValue);
	}
	else
	{
		v = (wcscmp(v1.m_pszValue, v2.m_pszValue) < 0);
	}
	
	return v;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAtlNodeValue::CAtlNodeValue()
{
	m_pszValue = NULL;
	m_VT = NodeValueDouble;
	m_dValue = 0;	
}

CAtlNodeValue::CAtlNodeValue(const wchar_t* val)
{
	m_pszValue = NULL;
	if (val == m_pszValue)
	{
	}
	else
	{
		FreeValue();
		*this = val;
	}
}

CAtlNodeValue::CAtlNodeValue(const CComBSTR &val)
{
	m_pszValue = NULL;

	long nLen = val.Length();
	wchar_t *pTemp = new wchar_t[nLen+1];
	wcscpy(pTemp, val);
	FreeValue();
	*this = pTemp;
	delete pTemp;
}

CAtlNodeValue::CAtlNodeValue(double val)
{
	m_pszValue = NULL;
	FreeValue();
	*this = val;
}

CAtlNodeValue::CAtlNodeValue(int val)
{
	m_pszValue = NULL;
	FreeValue();
	*this = val;
}

CAtlNodeValue::CAtlNodeValue(long val)
{
	m_pszValue = NULL;
	FreeValue();
	*this = val;
}

CAtlNodeValue::CAtlNodeValue(const CAtlNodeValue &val)
{
	if (this == &val)
	{
		return;
	}
	
	*this = val;
}

CAtlNodeValue::~CAtlNodeValue()
{
	FreeValue();
}

void CAtlNodeValue::FreeValue()
{
	if (m_VT == NodeValueString && m_pszValue != NULL)
	{
		delete m_pszValue;
		m_pszValue = NULL;
	}
	else
	{
	}
}

const long CAtlNodeValue::g_nTempBufferLen = 32;

void CAtlNodeValue::ToString(CComBSTR &strValue)
{
	if (m_VT == NodeValueString)
	{
		strValue = m_pszValue;
	}
	else
	{
		char pszBuff[g_nTempBufferLen];
		CAnsiStringPrintf oBuffer(pszBuff);
		oBuffer.sprintf("%f", m_dValue);
		
		strValue = pszBuff;
	}
}

const CAtlNodeValue& CAtlNodeValue::GetNotValue()
{
	if (m_VT == NodeValueString)
	{
		if (wcslen(m_pszValue) > 0)
		{
			m_dValue = 0;
		}
		else
		{
			m_dValue = 1;
		}
	}
	else
	{
		if (m_dValue > 0)
		{
			m_dValue = 0;
		}
		else
		{
			m_dValue = 1;
		}
	}	
	
	m_VT = NodeValueDouble;
	
	return *this;
}

const CAtlNodeValue& CAtlNodeValue::operator= (const wchar_t* val)
{
	if (val == m_pszValue)
	{
		return *this;
	}
	
	FreeValue();
	m_VT = NodeValueString;
	if (val != NULL)
	{
		long nLen = wcslen(val) + 1;
		m_pszValue = new wchar_t [nLen];
		wcscpy(m_pszValue, val);
	}

	return *this;
}

const CAtlNodeValue& CAtlNodeValue::operator= (const CComBSTR &val)
{
	if (val == m_pszValue)
	{
		return *this;
	}
	
	FreeValue();
	m_VT = NodeValueString;

	long nLen = val.Length() + 1;
	m_pszValue = new wchar_t [nLen];
	wcscpy(m_pszValue, val);
	
	return *this;
}

const CAtlNodeValue& CAtlNodeValue::operator= (double val)
{
	FreeValue();
	m_VT = NodeValueDouble;
	m_dValue = val;
	return *this;
}

const CAtlNodeValue& CAtlNodeValue::operator = (float val)
{
	FreeValue();
	m_VT = NodeValueDouble;
	m_dValue = val;
	return *this;
}

const CAtlNodeValue& CAtlNodeValue::operator= (int val)
{
	FreeValue();
	m_VT = NodeValueDouble;
	m_dValue = val;
	return *this;
}

const CAtlNodeValue& CAtlNodeValue::operator= (long val)
{
	FreeValue();
	m_VT = NodeValueDouble;
	m_dValue = val;
	return *this;
}

const CAtlNodeValue& CAtlNodeValue::operator= (const CAtlNodeValue &val)
{ 
/*
	if (m_VT != val.m_VT)
	{
		return *this;
	} 
*/

	if (val.m_VT == NodeValueDouble)
	{
		m_dValue = val.m_dValue;
	}
	else
	{
		if (this != &val)
		{
			*this = val.m_pszValue;
		}
		else
		{
		}
	}
	m_VT = val.m_VT;
	return *this;
}

const CAtlNodeValue& CAtlNodeValue::operator+= (const CAtlNodeValue &val)
{ 
/*
	if (m_VT != val.m_VT)
	{
		return *this;
	} 
*/
	
	if (m_VT == NodeValueDouble)
	{
		m_dValue += val.m_dValue;
	}
	else
	{
		if (this != &val)
		{
			long nLen = wcslen(m_pszValue) + wcslen(val.m_pszValue);
			wchar_t *pTemp = new wchar_t[nLen+1];
			wcscpy(pTemp, m_pszValue);
			wcscat(pTemp, val.m_pszValue);
			FreeValue();
			m_pszValue = pTemp;
		}
		else
		{
		}
	}

	m_VT = val.m_VT;

	return *this;
}

const CAtlNodeValue& CAtlNodeValue::operator / (const CAtlNodeValue &val)
{
	if (m_VT != val.m_VT || m_VT != NodeValueDouble)
	{
		return *this;
	}

	m_dValue /= val.m_dValue;

	return *this;
}

BOOL CAtlNodeValue::operator== (double val)
{
	return (val == m_dValue);
}

BOOL CAtlNodeValue::operator == (float val)
{
	return (val == m_dValue);
}

BOOL CAtlNodeValue::operator== (int val)
{
	return (val == m_dValue);
}

BOOL CAtlNodeValue::operator== (long val)
{
	return (val == m_dValue);
}

BOOL CAtlNodeValue::operator== (const CAtlNodeValue &val)
{ 
	if (m_VT != val.m_VT)
	{
		return FALSE;
	} 
	
	if (m_VT == NodeValueDouble)
	{
		//return (fabs(m_dValue - val.m_dValue) <= 0.0001);
		return (m_dValue == val.m_dValue);
	}
	else
	{
		return (wcscmp(m_pszValue, val.m_pszValue) == 0);
	}
}

BOOL CAtlNodeValue::operator== (wchar_t* val)
{ 
	if (m_VT == NodeValueDouble)
	{
		return FALSE;
	}
	else
	{
		return (wcscmp(m_pszValue, val) == 0);
	}
}

BOOL CAtlNodeValue::operator== (const CComBSTR &val)
{ 
	if (m_VT == NodeValueDouble)
	{
		return FALSE;
	}
	else
	{
		return (wcscmp(m_pszValue, val) == 0);
	}
}

BOOL CAtlNodeValue::operator < (const CAtlNodeValue &val)
{ 
	if (m_VT != val.m_VT)
	{
		return FALSE;
	} 
	
	if (m_VT == NodeValueDouble)
	{
		return (m_dValue < val.m_dValue);
	}
	else
	{
		return (wcscmp(m_pszValue, val.m_pszValue) < 0);
	}
}


BOOL CAtlNodeValue::operator <= (const CAtlNodeValue &val)
{ 
	if (m_VT != val.m_VT)
	{
		return FALSE;
	} 
	
	if (m_VT == NodeValueDouble)
	{
		return (m_dValue <= val.m_dValue);
	}
	else
	{
		return (wcscmp(m_pszValue, val.m_pszValue) <= 0);
	}
}


BOOL CAtlNodeValue::operator > (const CAtlNodeValue &val)
{ 
	if (m_VT != val.m_VT)
	{
		return FALSE;
	} 
	
	if (m_VT == NodeValueDouble)
	{
		return (m_dValue > val.m_dValue);
	}
	else
	{
		return (wcscmp(m_pszValue, val.m_pszValue) > 0);
	}
}


BOOL CAtlNodeValue::operator >= (const CAtlNodeValue &val)
{ 
	if (m_VT != val.m_VT)
	{
		return FALSE;
	} 
	
	if (m_VT == NodeValueDouble)
	{
		return (m_dValue >= val.m_dValue);
	}
	else
	{
		return (wcscmp(m_pszValue, val.m_pszValue) >= 0);
	}
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
运算符			描述 

()				表达式分组 
!				一元运算符
* / %			乘法、除法、取模 
+ -				加法、减法
<< >>			移位 
< <= > >=		小于、小于等于、大于、大于等于
== !=			等于、不等于
&				按位与 
^				按位异或 
|				按位或 
&&				逻辑与 
||				逻辑或 
=				赋值

*/

//    !    *    /    +    -    <    <=    >    >=    ==    &&    ||    =    (    )   #
const wchar_t CAtlExpression::m_pszOptrSymbol[COUNT_OPTR][3] = 
{ 
	{'!', 0,   0},
	{'*', 0,   0},
	{'/', 0,   0},
	{'+', 0,   0},
	{'-', 0,   0},
	{'<', 0,   0},
	{'<', '=', 0},
	{'>', 0,   0},
	{'>', '=', 0},
	{'=', '=', 0},
	{'&', '&', 0},
	{'|', '|', 0},
	{'=', 0,   0},
	{'(', 0,   0},
	{')', 0,   0},
	{'@', 0,   0}
};

/*
1\2	!	*	/	+	-	<	<=	>	>=	==	&&	||	= 	(	)	@
!	>	>	>	>	>	>	>	>	>	>	>	>	>	<	>	>
*	<	>	>	>	>	>	>	>	>	>	>	>	>	<	>	>
/	<	>	>	>	>	>	>	>	>	>	>	>	>	<	>	>
+	<	<	<	>	>	>	>	>	>	>	>	>	>	<	>	>
-	<	<	<	>	>	>	>	>	>	>	>	>	>	<	>	>
<	<	<	<	<	<	<	<	<	<	>	>	>	>	<	>	>
<=	<	<	<	<	<	<	<	<	<	>	>	>	>	<	>	>
>	<	<	<	<	<	<	<	<	<	>	>	>	>	<	>	>
>=	<	<	<	<	<	<	<	<	<	>	>	>	>	<	>	>
==	<	<	<	<	<	<	<	<	<	<	>	>	>	<	>	>
&&	<	<	<	<	<	<	<	<	<	<	<	>	>	<	>	>
||	<	<	<	<	<	<	<	<	<	<	<	<	>	<	>	>
=	<	<	<	<	<	<	<	<	<	<	<	<	<	<	>	>
(	<	<	<	<	<	<	<	<	<	<	<	<	<	<	=	0
)	>	>	>	>	>	>	>	>	>	>	>	>	>	0	>	>
@	<	<	<	<	<	<	<	<	<	<	<	<	<	<	0	=
*/
const wchar_t CAtlExpression::m_pszOptrPriority[COUNT_OPTR][COUNT_OPTR] = 
{ 
	{'>','>','>','>','>','>','>','>','>','>','>','>','>','<','>','>'},
	{'<','>','>','>','>','>','>','>','>','>','>','>','>','<','>','>'},
	{'<','>','>','>','>','>','>','>','>','>','>','>','>','<','>','>'},
	{'<','<','<','>','>','>','>','>','>','>','>','>','>','<','>','>'},
	{'<','<','<','>','>','>','>','>','>','>','>','>','>','<','>','>'},
	{'<','<','<','<','<','<','<','<','<','>','>','>','>','<','>','>'},
	{'<','<','<','<','<','<','<','<','<','>','>','>','>','<','>','>'},
	{'<','<','<','<','<','<','<','<','<','>','>','>','>','<','>','>'},
	{'<','<','<','<','<','<','<','<','<','>','>','>','>','<','>','>'},
	{'<','<','<','<','<','<','<','<','<','<','>','>','>','<','>','>'},
	{'<','<','<','<','<','<','<','<','<','<','<','>','>','<','>','>'},
	{'<','<','<','<','<','<','<','<','<','<','<','<','>','<','>','>'},
	{'<','<','<','<','<','<','<','<','<','<','<','<','<','<','>','>'},
	{'<','<','<','<','<','<','<','<','<','<','<','<','<','<','=','0'},
	{'>','>','>','>','>','>','>','>','>','>','>','>','>','0','>','>'},
	{'<','<','<','<','<','<','<','<','<','<','<','<','<','<','0','='}
};

const wchar_t CAtlExpression::m_pszFunction[COUNT_FUNCTION][8] = 
{ 
	{'s','i','n',0  ,0  ,0  ,0,0},
	{'c','o','s',0  ,0  ,0  ,0,0},
	{'e','x','p',0  ,0  ,0  ,0,0},
	{'s','q','r','t',0  ,0  ,0,0},
	{'l','o','g','1','0',0  ,0,0},
	{'t','a','n',0  ,0  ,0  ,0,0},
	{'c','t','a','n',0  ,0  ,0,0},
	{'a','s','i','n',0  ,0  ,0,0},
	{'a','c','o','s',0  ,0  ,0,0},
	{'a','t','a','n','2',0  ,0,0},
	{'a','b','s',0  ,0  ,0  ,0,0},
	{'l','o','g',0  ,0  ,0  ,0,0},
	{'m','i','n',0  ,0  ,0  ,0,0},
	{'m','a','x',0  ,0  ,0  ,0,0},
	{'p','o','w',0  ,0  ,0  ,0,0},
	{'c','e','i','l',0  ,0  ,0,0},
	{'f','l','o','o','r',0  ,0,0},
	{'h','y','p','o','t',0  ,0,0},
	{'a','t','a','n',0  ,0  ,0,0},
	{'f','m','o','d',0  ,0  ,0,0},
	{'d','i','g','i','t',0  ,0,0},
	{'b','i','n','a','r','y',0,0}
};

bool CStringStack::Empty()
{
	CStringStackData *pNode = m_pHeadNode;
	CStringStackData *pTemp = NULL; 
	
	while (pNode != NULL)
	{
		pTemp = pNode->m_pNext;
		delete pNode;
		pNode = pTemp;
	}

	m_pHeadNode = NULL;
	m_nLength = 0;

	return true;
}

bool CStringStack::IsEmpty()
{
	return (m_pHeadNode == NULL);
}

bool CStringStack::Pop()
{
	CStringStackData *pNode = m_pHeadNode;
	if(m_pHeadNode == NULL)
		return false;
	
	m_nLength--;
	m_pHeadNode = pNode->m_pNext;
	delete pNode;
	
	return true;
}

bool CStringStack::Push(const wchar_t *pData)
{
	CStringStackData *pNode = new CStringStackData(pData, m_pHeadNode);
	
	m_nLength++;
	pNode->m_pNext = m_pHeadNode;
	m_pHeadNode = pNode;
	
	return true;
}

const wchar_t* CStringStack::Top()
{
	if (m_pHeadNode != NULL)
	{
		return m_pHeadNode->m_pData;
	}
	else
	{
		return NULL;
	}
}

bool CAtlExprStack::Empty()
{
	CAtlExprStackData *pNode = m_pHeadNode;
	CAtlExprStackData *pTemp = NULL; 
	
	while (pNode != NULL)
	{
		pTemp = pNode->m_pNext;
		delete pNode;
		pNode = pTemp;
	}

	m_pHeadNode = NULL;
	m_nLength = 0;
	
	return true;
}

bool CAtlExprStack::IsEmpty()
{
	return (m_pHeadNode == NULL);
}

bool CAtlExprStack::Pop()
{
	CAtlExprStackData *pNode = m_pHeadNode;
	if(m_pHeadNode == NULL)
		return false;
	
	m_nLength--;
	m_pHeadNode = pNode->m_pNext;
	delete pNode;
	
	return true;
}

bool CAtlExprStack::Push(CAtlExprNode *pData)
{
	CAtlExprStackData *pNode = new CAtlExprStackData(pData, m_pHeadNode);
	
	m_nLength++;
	pNode->m_pNext = m_pHeadNode;
	m_pHeadNode = pNode;
	
	return true;
}

CAtlExprNode* CAtlExprStack::Top()
{
	if (m_pHeadNode != NULL)
	{
		return m_pHeadNode->m_pData;
	}
	else
	{
		return NULL;
	}
}

CAtlExpression::CAtlExpression()
{
	SetExprCalMode();
	
	m_pScriptSyntaxs = new CAtlScriptSyntaxs();
	m_pConstVariables = NULL;
	m_pTempVariables = NULL;
	
	m_pszExprBuff = NULL;
	m_nExprBuffLen = 0;
	m_nCurrPos = 0;
	m_pExprRootNode = NULL;
	memset(m_pszKeyWord, 0, MAXSIZE_KEYWORD*sizeof(wchar_t));
}

void CAtlExpression::CreateConstVariables()
{
	if (m_pConstVariables != NULL)
	{
		return;
	}
	
	CComObject<CEquation> *pEquation = NULL;
	CComObject<CEquation>::CreateInstance(&pEquation);

	if (pEquation != NULL)
	{
		pEquation->QueryInterface(IID_IEquation, (void**)&m_pConstVariables);	
	}
}

void CAtlExpression::Release()
{
	if (m_pConstVariables != NULL)
	{
		m_pConstVariables->Release();
	}
	
	if (m_pTempVariables != NULL)
	{
		m_pTempVariables->Release();
	}
	
	m_pConstVariables = NULL;
	m_pTempVariables = NULL;
}

CAtlExpression::~CAtlExpression()
{
	if (m_pConstVariables != NULL)
	{
		m_pConstVariables->Release();
	}
	
	if (m_pTempVariables != NULL)
	{
		m_pTempVariables->Release();
	}
	
	FreeBuff();
	
	delete m_pScriptSyntaxs;
}

void CAtlExpression::FreeBuff()
{
	m_pScriptSyntaxs->m_listSyntax.DeleteAll();
	if (m_pszExprBuff != NULL)
	{
		delete m_pszExprBuff;
		m_pszExprBuff = NULL;
	}
	m_nExprBuffLen = 0;

	if (m_pExprRootNode != NULL)
	{
		delete m_pExprRootNode;
		m_pExprRootNode = NULL;
	}
}

long CAtlExpression::SetAtlExpression(const wchar_t *pszAtlExpression)
{
	CreateConstVariables();
	ClearError();
	FreeBuff();

	m_nExprBuffLen = wcslen(pszAtlExpression);
	m_pszExprBuff = new wchar_t[m_nExprBuffLen+2];
	wcscpy(m_pszExprBuff, pszAtlExpression);
	m_pszExprBuff[m_nExprBuffLen]='@';
	m_pszExprBuff[m_nExprBuffLen+1]=0;

	BuildAtlExpressionTree();
	
	return m_pScriptSyntaxs->m_listSyntax.GetCount();
}

long CAtlExpression::SetAtlExpression(const CComBSTR &strAtlExpression)
{
	CreateConstVariables();
	ClearError();
	FreeBuff();
	
	m_nExprBuffLen = strAtlExpression.Length();
	m_pszExprBuff = new wchar_t[m_nExprBuffLen+2];
	wcscpy(m_pszExprBuff, strAtlExpression);
	m_pszExprBuff[m_nExprBuffLen]='@';
	m_pszExprBuff[m_nExprBuffLen+1]=0;
	
	BuildAtlExpressionTree();

	return m_pScriptSyntaxs->m_listSyntax.GetCount();
}

int CAtlExpression::Value(double & dValue)
{
	CComBSTR strValue;
	Value(strValue);
	BSTR value = strValue.Copy();
	dValue = _wtol(value);
	return 0;
}

int CAtlExpression::Value(CComBSTR &strValue)
{
	CAtlNodeValue v = Solve(m_pExprRootNode);
	v.ToString(strValue);
	return 0;
}

void CAtlExpression::AttachConstVariables(IEquation* pVariables)
{
	if (m_pConstVariables != NULL)
	{
		m_pConstVariables->Release();
	}
	
	m_pConstVariables = pVariables;
	if (m_pConstVariables != NULL)
	{
		m_pConstVariables->AddRef();
	}
}


void CAtlExpression::AttachTempVariables(IEquation* pVariables)
{
	//2005年11月23日 23：11 修改
	//m_pTempVariables不为空的情况下需要对其进行释放
	//否则多次调用此函数后会造成内存泄露
	if (m_pTempVariables != NULL)
	{
		m_pTempVariables->Release();
		m_pTempVariables = NULL;
	}
	
	m_pTempVariables = pVariables;
	if (m_pTempVariables != NULL)
	{
		m_pTempVariables->AddRef();
	}
}

void CAtlExpression::AttachConstVariables(LPDISPATCH pVariables)
{
	if (m_pConstVariables != NULL)
	{
		m_pConstVariables->Release();
		m_pConstVariables = NULL;
	}

	if (pVariables != NULL)
	{
		pVariables->QueryInterface(IID_IEquation, (void**)&m_pConstVariables);
	}
}


void CAtlExpression::AttachTempVariables(LPDISPATCH pVariables)
{
	if (m_pTempVariables != NULL)
	{
		m_pTempVariables->Release();
		m_pTempVariables = NULL;
	}
	
	if (pVariables != NULL)
	{
		pVariables->QueryInterface(IID_IEquation, (void**)&m_pTempVariables);
	}
}

void CAtlExpression::SetConstVariables(const CComBSTR &strVariables, BOOL bAddNew)
{
	if (m_pConstVariables != NULL)
	{
		long nReturn = 0;
		if (bAddNew)
		{
//			m_pConstVariables->SetKeyValueEx(strVariables, 1, &nReturn);
		}
		else
		{
//			m_pConstVariables->SetEquation(strVariables, &nReturn);
		}
	}
}

void CAtlExpression::SetConstVariables(const wchar_t* strVariables, BOOL bAddNew)
{
	if (m_pConstVariables != NULL)
	{
		long nReturn = 0;
		if (bAddNew)
		{
//			m_pConstVariables->SetKeyValueEx((BSTR)strVariables, 1, &nReturn);
		}
		else
		{
//			m_pConstVariables->SetEquation((BSTR)strVariables, &nReturn);
		}
	}
}

void CAtlExpression::SetConstVariables(BSTR bstrVariables, BOOL bAddNew)
{
	if (m_pConstVariables != NULL)
	{
		long nReturn = 0;
		if (bAddNew)
		{
//			m_pConstVariables->SetKeyValueEx(bstrVariables, 1, &nReturn);
		}
		else
		{
			m_pConstVariables->SetEquation(bstrVariables, &nReturn);
		}
	}
}

void CAtlExpression::AddVariable(const CComBSTR &strVariavble,const CComBSTR &strValue)
{
	if (m_pConstVariables != NULL)
	{
		long nReturn = 0;
//		m_pConstVariables->SetKeyValue(strVariavble, strValue, 1, &nReturn);
	}
}



BOOL CAtlExpression::FindVariable(BSTR bstrVariable)
{
	BOOL bResult = FALSE;
	long nReturn = 0;

	if (m_pConstVariables != NULL)
	{
		m_pConstVariables->IsKeyExist(bstrVariable, &nReturn);
		bResult = nReturn;
	}
	
	if (!bResult && m_pTempVariables != NULL)
	{
		m_pTempVariables->IsKeyExist(bstrVariable, &nReturn);
		bResult = nReturn;
	}
	
	return bResult;
}

BOOL CAtlExpression::FindVariable(const wchar_t *pszVariable)
{
	CComBSTR strVariable = pszVariable;
	return FindVariable(strVariable);
}

BOOL CAtlExpression::FindVariable(const CComBSTR &strVariable)
{
	BOOL b = FindVariable(strVariable);

	return b;
}

BOOL CAtlExpression::IsTempVariable(BSTR bstrVariable)
{
	BOOL bTempVariable = FALSE;

	if (m_pTempVariables != NULL)
	{
		long nReturn = 0;
		m_pTempVariables->IsKeyExist(bstrVariable, &nReturn);
		bTempVariable = nReturn;
	}
	
	return bTempVariable;
}

BOOL CAtlExpression::IsTempVariable(const wchar_t *pszVariable)
{
	CComBSTR strVariable = pszVariable;
	return IsTempVariable(strVariable);
}

BOOL CAtlExpression::IsTempVariable(const CComBSTR &strVariable)
{
	BOOL b = IsTempVariable(strVariable);

	return b;
}

const wchar_t CAtlExpression::m_strOptrEnd[2] = {'@' ,0};

long CAtlExpression::BuildAtlExpressionTree()
{
	CStringStack stkOptr;	//操作符号
	CAtlExprStack   stkNode;	//节点
	
	m_nCurrPos = 0;

	CAtlExprNode *pNode = NULL;
	CAtlExprNode *pLeft = NULL;
	CAtlExprNode *pRight = NULL;
	const wchar_t *pszOperator = NULL;
	long nLength = 0;
	wchar_t chPreced = 0;
	stkOptr.Push(m_strOptrEnd);
	int t = ReadAKeyWord(nLength);
	
	while(wcscmp(stkOptr.Top(), m_strOptrEnd) != 0 || m_pszKeyWord[0]!=m_strOptrEnd[0])
	{
		switch(t) 
		{
		case KEYWORDTYPE_FUNCSPLIT: //函数参数分隔符号“,”
			m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_FUNCSLPIT);
			break;
		case KEYWORDTYPE_REAL:
		case KEYWORDTYPE_STRING:
		case KEYWORDTYPE_VARIABLE:
			pNode = new CAtlExprNode(m_pszKeyWord);
			stkNode.Push(pNode);

			if (IsExprConpileMode())
			{
				CompileKeyWord();
			}
			break;
		case KEYWORDTYPE_OPERATOR:
			pszOperator = stkOptr.Top();
			if (pszOperator == NULL)
			{
				m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);				
			}
			chPreced = PrecedOptr(pszOperator, m_pszKeyWord);
			if (chPreced == '>')
			{//当前运算符号比前一个运算符号优先级高
				if (*pszOperator == '!')
				{//单目运算符号
					if (stkOptr.GetSize() == 0)
					{
						m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);
						break;
					}

					pLeft = stkNode.Top();
					stkNode.Pop();
					pNode = new CAtlExprNode(pszOperator, pLeft, NULL);
					stkNode.Push(pNode);	
					stkOptr.Pop();
				}
				//else if (*pszOperator == '-' && *(pszOperator+1) == '')
				else
				{
					if (stkOptr.GetSize() == 0)
					{
						m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);
						break;
					}

					pRight = stkNode.Top();
					stkNode.Pop();
			
					if (stkOptr.GetSize() == 0)
					{
						delete pRight;
						m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);
						break;
					}

					pLeft = stkNode.Top();
					stkNode.Pop();
					pNode = new CAtlExprNode(pszOperator, pLeft, pRight);
					stkNode.Push(pNode);
					stkOptr.Pop();
				}
				continue;
			}
			else if (chPreced == '<')
			{
				stkOptr.Push(m_pszKeyWord);
			}
			else
			{
				stkOptr.Pop();
			}
			break;
		case KEYWORDTYPE_FUNCTION:
			pNode = new CAtlExprNode(m_pszKeyWord);
			stkNode.Push(pNode);
			ReadFunctionPara(pNode);
		break;
		default:
			m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);				
			break;
		}
		t = ReadAKeyWord(nLength);
		if (t == -1)
		{
			m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);
			break;
		}

		if (stkOptr.GetSize() == 0)
		{
			m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);
			break;
		}
	}

	if (stkOptr.GetSize() == 0)
	{
		m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);
	}
	m_pExprRootNode = stkNode.Top();
	if (m_pExprRootNode == NULL)
	{
		m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);
	}
	stkNode.Pop();
	
	stkOptr.Empty();

	while (!stkNode.IsEmpty())
	{
		pNode = stkNode.Top();
		delete pNode;
		stkNode.Pop();
	}
	
	return 0;
}

bool CAtlExpression::ReadFunctionPara(CAtlExprNode *pFuncNode)
{
	CAtlExprNode *pNode = NULL;
	CAtlExprNode *pLeft = NULL;
	CAtlExprNode *pRight = NULL;
	CStringStack stkOptr;	//操作符号
	CAtlExprStack   stkNode;	//节点
	const wchar_t *pszOperator = NULL;
	long nLength = 0;
	wchar_t chPreced = 0;
	
	Offset();
	stkOptr.Push(m_strOptrEnd);
	
	CAtlExprNode *pFuncNodeLeft = NULL;
	CAtlExprNode *pFuncNodeRight = NULL;
	
	int t = ReadAKeyWord(nLength);
	
	while (true)
	{
		switch(t) 
		{
		case KEYWORDTYPE_FUNCSPLIT: //函数参数分隔符号“,”
			if (stkOptr.GetSize() == 0)
			{
				m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);
				break;
			}
			pFuncNodeLeft = stkNode.Top();
			stkNode.Pop();
			break;
		case KEYWORDTYPE_REAL:
		case KEYWORDTYPE_STRING:
		case KEYWORDTYPE_VARIABLE:
			pNode = new CAtlExprNode(m_pszKeyWord);
			stkNode.Push(pNode);
			if (IsExprConpileMode())
			{
				CompileKeyWord();
			}
			break;
		case KEYWORDTYPE_OPERATOR:
			if (stkOptr.GetSize() == 0)
			{
				m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);
				break;
			}

			pszOperator = stkOptr.Top();
			if (pszOperator == NULL)
			{
				m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_FUNCPARAERR);
			}
			
			chPreced = PrecedOptr(pszOperator, m_pszKeyWord);
			if (chPreced == '>')
			{//当前运算符号比前一个运算符号优先级高
				if (stkOptr.GetSize() == 0)
				{
					m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);
					break;
				}

				pRight = stkNode.Top();
				stkNode.Pop();
				if (stkOptr.GetSize() == 0)
				{
					delete pRight;
					m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);
					break;
				}

				pLeft = stkNode.Top();
				stkNode.Pop();
				pNode = new CAtlExprNode(pszOperator, pLeft, pRight);
				stkNode.Push(pNode);
				stkOptr.Pop();
				continue;
			}
			else if (chPreced == '<')
			{
				stkOptr.Push(m_pszKeyWord);
			}
			else
			{
				stkOptr.Pop();
			}
			break;
		case KEYWORDTYPE_FUNCTION:
			pNode = new CAtlExprNode(m_pszKeyWord);
			stkNode.Push(pNode);
			ReadFunctionPara(pNode);
			break;
		default:
			m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_FUNCPARAERR);			
			break;
		}
		if (stkOptr.GetSize() == 1)
		{
			break;
		}
		
		t = ReadAKeyWord(nLength);
		if (t == -1)
		{
			m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);
		}
	}
	
	if (stkOptr.GetSize() == 0)
	{
		m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_EXPRERROR);
	}
	if (pFuncNodeLeft == NULL)
	{
		pFuncNodeLeft = stkNode.Top();
	}
	else
	{
		pFuncNodeRight = stkNode.Top();
	}
	stkNode.Pop();
	
	pFuncNode->m_pLeft = pFuncNodeLeft;
	pFuncNode->m_pRight = pFuncNodeRight;
	
	if (pFuncNodeLeft == NULL && pFuncNodeRight == NULL)
	{
		m_pScriptSyntaxs->AddNew(-1, "", SYNTAXERR_FUNCPARAERR);		
	}
	
	if (pFuncNodeLeft != NULL)
	{
		pFuncNodeLeft->m_pParent = pFuncNode;
	}
	if (pFuncNodeRight != NULL)
	{
		pFuncNodeRight->m_pParent = pFuncNode;
	}
	
	stkOptr.Empty();
	while (!stkNode.IsEmpty())
	{
		pNode = stkNode.Top();
		delete pNode;
		stkNode.Pop();
	}
	
	return true;
}

void CAtlExpression::Offset()
{
	while (IsIgnoreChar(m_pszExprBuff[m_nCurrPos]))
		m_nCurrPos++;
}

//判断一缓冲区的数据是否全部是数字
/*数字串的判断方法：
	只能包含一个符号，而且必须在开头的位置；
	只能有一个小数点；
	不能包含0~9以及“+”、“-”、“.”之外的所有字符
*/
bool CAtlExpression::IsStringAReal(const wchar_t *pszData)
{
	ATLASSERT(pszData != NULL);
	long nLen = wcslen(pszData);

	if (nLen == 0)
	{
		return false;
	}
	
	long nDotCount = 0;
	
	for(int i = 0; i < nLen; ++i)
	{
		if (pszData[i] == '.')
		{
			nDotCount++;
		}
		if(!(pszData[i]>='0' && pszData[i]<='9') )
		{
			if ((i == 0) && ((pszData[i] == '-') || (pszData[i] == '+')))
			{
			}
			else if ((pszData[i] != '.') )
			{
				return false;
			}
			else
			{
			}
		}
	}
	
	BOOL bNumber = TRUE;

	if (nLen == 1)
	{
		if (pszData[0] == '-' || pszData[0] == '+' || pszData[0] == '.' )
		{
			bNumber = FALSE;
		}
	}
	else
	{
		if (pszData[0] == '.')
		{
		}
		else if (pszData[0] == '-' || pszData[0] == '+')
		{
			if (pszData[1] == '.')
			{
				bNumber = FALSE;
			}
			else
			{
				if (pszData[0] == '0')
				{
					if (pszData[1] != '0')
					{
						if (pszData[1] == '.')
						{//0.
						}
						else
						{//01
							bNumber = FALSE;
						}
					}
					else
					{//  00
						bNumber = FALSE;
					}
				}
			}
		}
		else
		{
			if (pszData[0] == '0')
			{
				if (pszData[1] != '0')
				{
					if (pszData[1] == '.')
					{//0.
					}
					else
					{//01
						bNumber = FALSE;
					}
				}
				else
				{//  00
					bNumber = FALSE;
				}
			}
		}
	}

	if (!bNumber)
	{
		return FALSE;
	}
	
	if (nDotCount >= 2)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CAtlExpression::GetOperator(wchar_t *pszBuff, long &nLength)
{
	bool bFind = false;
	long nIndex = 0;
	
	//首先查找两个字符的操作符号
	for (nIndex=0; nIndex<COUNT_OPTR; nIndex++)
	{
		if (m_pszOptrSymbol[nIndex][1] != 0)
		{
			if (m_pszOptrSymbol[nIndex][0] == m_pszExprBuff[m_nCurrPos]
				&& m_pszOptrSymbol[nIndex][1] == m_pszExprBuff[m_nCurrPos+1])
			{
				wcscpy(pszBuff, m_pszOptrSymbol[nIndex]);
				bFind = true;
				nLength = 2;
				break;
			}
		}
	}
	
	if (bFind)
	{
		m_nCurrPos += nLength;
		return bFind;
	}
	
	for (nIndex=0; nIndex<COUNT_OPTR; nIndex++)
	{
		if (m_pszOptrSymbol[nIndex][0] == m_pszExprBuff[m_nCurrPos])
		{
			wcscpy(pszBuff, m_pszOptrSymbol[nIndex]);
			bFind = true;
			nLength = 1;
			break;
		}
	}
	
	m_nCurrPos += nLength;

	return bFind;
}

bool CAtlExpression::IsOperator(const wchar_t ch)
{
	bool bTrue = false;
	long nIndex = 0;
	for (nIndex=0; nIndex<COUNT_OPTR; nIndex++)
	{
		if (m_pszOptrSymbol[nIndex][0] == ch)
		{
			bTrue = true;
			break;
		}
	}
	return bTrue;	
}

bool CAtlExpression::GetFunction(wchar_t *pBuff, long &nLength)
{
	bool bTrue = false;
	long nIndex = 0;
	long nLen = 0;
	long nPosTemp = 0;

	Offset();

	for (nIndex=0; nIndex<COUNT_FUNCTION; nIndex++)
	{
		nLen = wcslen(m_pszFunction[nIndex]);
		if ( wcsncmp(m_pszFunction[nIndex], &m_pszExprBuff[m_nCurrPos], nLen) == 0)
		{
			nPosTemp = m_nCurrPos+nLen;

			//函数后面的第一个有效字符
			while (IsIgnoreChar(m_pszExprBuff[nPosTemp]) && m_nCurrPos <= m_nExprBuffLen)
			{
				nPosTemp++;
			}
			if (nPosTemp > m_nExprBuffLen || m_pszExprBuff[nPosTemp] != '(')
			{// error
				break;
			}
			wcscpy(pBuff, m_pszFunction[nIndex]);
			m_nCurrPos = nPosTemp;
			nLength = nLen;
			bTrue = true;
			break;
		}
	}

	return bTrue;
}

long CAtlExpression::GetFunctionID(wchar_t *pFuncName)
{
	long nIndex = 0;
	long nFuncID = -1;
	
	for (nIndex=0; nIndex<COUNT_FUNCTION; nIndex++)
	{
		if ( wcscmp(m_pszFunction[nIndex], pFuncName) == 0)
		{
			nFuncID = nIndex;
			break;
		}
	}
	
	return nFuncID;
}

bool CAtlExpression::GetReal(wchar_t *pBuff, long &nLength)
{
	Offset();
	
	long nPos = m_nCurrPos;
	//if (!isdigit(m_pszExprBuff[nPos]))
	if (!(m_pszExprBuff[nPos] >= '0' && m_pszExprBuff[nPos] <= '9'))
	{
		return false;
	}

	long nLastPos = m_nCurrPos;
	long nDotCount = 0;

	while (true)
	{
		if (m_pszExprBuff[nPos] == '.')
		{
			nDotCount++;
			if (nDotCount >= 2)
			{
				nLastPos = nPos;
				break;
			}
		}
		else if (!(m_pszExprBuff[nPos] >= '0' && m_pszExprBuff[nPos] <= '9'))
		//else if (!isdigit(m_pszExprBuff[nPos]))
		{
			nLastPos = nPos;
			break;
		}
		else
		{
		}
		nPos++;
		if (nPos > m_nExprBuffLen)
		{
			break;
		}
	}

	nLength = nLastPos-m_nCurrPos;
	memcpy(pBuff, &m_pszExprBuff[m_nCurrPos], nLength*sizeof(wchar_t));
	pBuff[nLength] = 0;
	m_nCurrPos = nPos;
	
	return true;
}

bool CAtlExpression::GetString(wchar_t *pBuff, long &nLength)
{
	if (m_pszExprBuff[m_nCurrPos] != '\"')
	{
		return false;
	}

	long nPos = m_nCurrPos + 1;
	while (m_pszExprBuff[nPos] != '\"' && nPos <= m_nExprBuffLen)
	{
		nPos++;
	}

	if (nPos > m_nExprBuffLen || m_pszExprBuff[nPos] != '\"')
	{
		return false;
	}

	nLength = nPos - m_nCurrPos + 1;
	memcpy(pBuff, &m_pszExprBuff[m_nCurrPos], nLength*sizeof(wchar_t));
	pBuff[nLength] = 0;
	m_nCurrPos = nPos + 1;

	return true;
}

bool CAtlExpression::GetVariable(wchar_t *pBuff, long &nLength)
{//获取变量
	Offset();
	long nPos = m_nCurrPos;

	while (true)
	{
		if (IsIgnoreChar(m_pszExprBuff[nPos])/*如果是无效字符*/
			|| IsOperator(m_pszExprBuff[nPos])/*如果是运算符号*/ 
			|| m_pszExprBuff[nPos] == '\"' /*字符串分隔符号*/
			|| m_pszExprBuff[nPos] == ',' /*函数参数分隔符号*/)
		{
			break;
		}

		if (nPos > m_nExprBuffLen)
		{
			break;
		}

		nPos++;
	}

	nLength = nPos - m_nCurrPos;
	if (nLength == 0)
	{
		return false;
	}

	memcpy(pBuff, &m_pszExprBuff[m_nCurrPos], nLength*sizeof(wchar_t));
	pBuff[nLength] = 0;
	m_nCurrPos = nPos;

	return true;
}

bool CAtlExpression::IsSplitChar(wchar_t ch)
{
	bool bTrue = FALSE;

	if (ch == VK_SPACE || ch == VK_TAB || ch == '\r' || ch == '\n')
	{
		bTrue = true;
	}
	else if (IsOperator(ch))
	{
		bTrue = true;
	}
	else
	{
	}
	
	return bTrue;
}

bool CAtlExpression::IsIgnoreChar(wchar_t ch)
{
	bool bTrue = FALSE;
	
	if (ch == VK_SPACE || ch == VK_TAB || ch == '\r' || ch == '\n')
	{
		bTrue = true;
	}
	
	return bTrue;
}

int CAtlExpression::GetOperatorLevel(const wchar_t *pOptr)
{
	long nLevel = -1;
	long nIndex = 0;
	for (nIndex=0; nIndex<COUNT_OPTR; nIndex++)
	{
		if (wcscmp(m_pszOptrSymbol[nIndex], pOptr) == 0)
		{
			nLevel = nIndex;
			break;
		}
	}
	return nLevel;
}

int CAtlExpression::GetOperatorParaCount(const wchar_t *pOptr)
{
	long nCount = 0;
	return nCount;
}

wchar_t CAtlExpression::PrecedOptr(const wchar_t *pOptr1, const wchar_t *pOptr2)
{
	int iLevel1 = GetOperatorLevel(pOptr1);
	int iLevel2 = GetOperatorLevel(pOptr2);
	
	if (iLevel1 == -1 || iLevel1 == -1)
	{
		return '=';
	}
	return m_pszOptrPriority[iLevel1][iLevel2];
}

long CAtlExpression::ReadAKeyWord(long &nLength)
{
	long nKeyWordType = KEYWORDTYPE_ERR;

	long nLen = 0;
	Offset();

	if (IsOperator(m_pszExprBuff[m_nCurrPos]))
	{//是否为操作符号
		GetOperator(m_pszKeyWord, nLength);
		nKeyWordType = KEYWORDTYPE_OPERATOR;
	}
	else if (GetFunction(m_pszKeyWord, nLength))
	{//获取函数
		nKeyWordType = KEYWORDTYPE_FUNCTION;
	}
	else if (GetString(m_pszKeyWord, nLength))
	{
		nKeyWordType = KEYWORDTYPE_STRING;
	}
	else if (GetReal(m_pszKeyWord, nLength))
	{
		nKeyWordType = KEYWORDTYPE_REAL;
	}
	else if (GetVariable(m_pszKeyWord, nLength))
	{
		nKeyWordType = KEYWORDTYPE_VARIABLE;
	}
	else if (m_pszExprBuff[m_nCurrPos] == ',')
	{
		nKeyWordType = KEYWORDTYPE_FUNCSPLIT;
		m_nCurrPos++;
		m_pszKeyWord[0] = ',';
		m_pszKeyWord[1] = 0;
	}

	return nKeyWordType;
}

CAtlNodeValue CAtlExpression::Solve(CAtlExprNode *pNode)
{
	CAtlNodeValue dValue(0);
	
	if (pNode == NULL)
	{
		return dValue;
	}

	if(pNode->m_pLeft == NULL && pNode->m_pRight == NULL)
	{//叶子节点
		if (IsStringAReal(pNode->m_pszID))
		{//实数
			//dValue = atof(pNode->m_pszID);
			dValue = _bstr_to_float(pNode->m_pszID);
		}
		else if (pNode->m_pszID[0] == '\"')
		{//字符串
			dValue = pNode->m_pszID;
		}
		else
		{//变量
			CComBSTR strValue;
			if (GetValueByVariable(pNode->m_pszID, strValue) )
			{
				if (strValue.Length() > 0)
				{
					if (strValue[0] == '\'')
					{//字符串
						dValue = strValue;
					}
					else
					{
						dValue = _bstr_to_float(strValue);
						//dValue = atof(strValue);
					}
				}
			}
			else//error
			{//缺省值
			}
		}
	}
	else
	{
		if (IsOperator(pNode->m_pszID[0]))
		{
			dValue = SolveOperator(pNode);
		}
		else
		{
			dValue = SolveFunction(pNode);
		}
	}

	return dValue;
}

CAtlNodeValue CAtlExpression::SolveOperator(CAtlExprNode *pNode)
{
	CAtlNodeValue dValue(0);

	long nOperatorLevel = GetOperatorLevel(pNode->m_pszID);

	switch (nOperatorLevel)
	{
	case 0:    //"!",
		if (pNode->m_pLeft != NULL)
		{
			dValue = Solve(pNode->m_pLeft);
		}
		else if (pNode->m_pRight != NULL)
		{
			dValue = Solve(pNode->m_pRight);
		}
		else
		{
		}
		dValue.GetNotValue();
		break;
	case 1:    //"*",
		dValue = Solve(pNode->m_pLeft) * Solve(pNode->m_pRight);
		break;
	case 2:    //"/",
		dValue = Solve(pNode->m_pLeft) / Solve(pNode->m_pRight);
		break;
	case 3:    //"+",
		dValue = Solve(pNode->m_pLeft) + Solve(pNode->m_pRight);
		break;
	case 4:    //"-",
		dValue = Solve(pNode->m_pLeft) - Solve(pNode->m_pRight);
		break;
	case 5:    //"<",
		dValue = Solve(pNode->m_pLeft) < Solve(pNode->m_pRight);
		break;
	case 6:    //"<=",
		dValue = Solve(pNode->m_pLeft) <= Solve(pNode->m_pRight);
		break;
	case 7:    //">",
		dValue = Solve(pNode->m_pLeft) > Solve(pNode->m_pRight);
		break;
	case 8:    //">=",
		dValue = Solve(pNode->m_pLeft) >= Solve(pNode->m_pRight);
		break;
	case 9:    //"==",
		dValue = Solve(pNode->m_pLeft) == Solve(pNode->m_pRight);
		break;
	case 10:    //"&&",
		dValue = Solve(pNode->m_pLeft) && Solve(pNode->m_pRight);
		break;
	case 11:    //"||",
		dValue = Solve(pNode->m_pLeft) || Solve(pNode->m_pRight);
		break;
	case 12:    //"=",
		//dValue = Solve(pNode->m_pLeft) * Solve(pNode->m_pRight);
		dValue = 1;
		break;
	default:
		break;
	}

	return dValue;
}

CAtlNodeValue CAtlExpression::SolveFunction(CAtlExprNode *pNode)
{
	CAtlNodeValue dValue(0);
	
	if (pNode == NULL)
	{
		return dValue;
	}
	
	long nFuncID = GetFunctionID(pNode->m_pszID);
	
	switch (nFuncID)
	{
	case FUNCID_SIN:    //0X00  //"sin",
		dValue = sin(Solve(pNode->m_pLeft).m_dValue);
		break;
	case FUNCID_COS:    //0X01  //"cos",
		dValue = cos(Solve(pNode->m_pLeft).m_dValue);
		break;
	case FUNCID_EXP:    //0X02  //"exp",
		dValue = exp(Solve(pNode->m_pLeft).m_dValue);
		break;
	case FUNCID_SQRT:   //0X03  //"sqrt",
		dValue = Solve(pNode->m_pLeft);
		if (dValue.m_dValue < 0)
		{
			dValue = 0;
		}
		else
		{
			dValue = sqrt(dValue.m_dValue);
		}
		break;
	case FUNCID_LOG:    //0X04  //"log",
		dValue = Solve(pNode->m_pLeft);
		if (dValue.m_dValue < 0)
		{
			dValue = 0;
		}
		else
		{
			dValue = sqrt(dValue.m_dValue);
		}
		break;
	case FUNCID_TAN:    //0X05  //"tan",
		dValue = tan(Solve(pNode->m_pLeft).m_dValue);
		break;
	case FUNCID_CTAN:   //0X06  //"ctan",
		dValue = 1 / tan(Solve(pNode->m_pLeft).m_dValue);
		break;
	case FUNCID_ASIN:   //0X07  //"asin",
		dValue = asin(Solve(pNode->m_pLeft).m_dValue);
		break;
	case FUNCID_ACOS:   //0X08  //"acos",
		dValue = acos(Solve(pNode->m_pLeft).m_dValue);
		break;
	case FUNCID_ATAN:   //0X09  //"atan",
		dValue = atan(Solve(pNode->m_pLeft).m_dValue);
		break;
	case FUNCID_ABS:    //0X0A  //"abs",
		dValue = fabs(Solve(pNode->m_pLeft).m_dValue);
		break;
	case FUNCID_LOG10:  //0X0B  //"log10",
		dValue = log10(Solve(pNode->m_pLeft).m_dValue);
		break;
	case FUNCID_MIN:    //0X0C  //"min",
		dValue = min(Solve(pNode->m_pLeft).m_dValue
			, Solve(pNode->m_pRight).m_dValue);
		break;
	case FUNCID_MAX:    //0X0D  //"max",
		dValue = max(Solve(pNode->m_pLeft).m_dValue
			, Solve(pNode->m_pRight).m_dValue);
		break;
	case FUNCID_POW:    //0X0E  //"pow",
		dValue = pow(Solve(pNode->m_pLeft).m_dValue
			, Solve(pNode->m_pRight).m_dValue);
		break;
	case FUNCID_CEIL:   //0X0F  //"ceil",
		dValue = ceil(Solve(pNode->m_pLeft).m_dValue);
		break;
	case FUNCID_FLOOR:  //0X10  //"floor",
		dValue = floor(Solve(pNode->m_pLeft).m_dValue);
		break;
	case FUNCID_HYPOT:  //0X11  //"hypot",
		dValue = hypot(Solve(pNode->m_pLeft).m_dValue
			, Solve(pNode->m_pRight).m_dValue);
		break;
	case FUNCID_ATAN2:  //0X12  //"atan2",
		dValue = atan2(Solve(pNode->m_pLeft).m_dValue
			, Solve(pNode->m_pRight).m_dValue);
		break;
	case FUNCID_FMOD:   //0X13  //"fmod"		
		dValue = hypot(Solve(pNode->m_pLeft).m_dValue
			, Solve(pNode->m_pRight).m_dValue);
		break;
	case FUNCID_DIGIT:    //0X14  //"digit",
		{
			long nIndex = 0;
			
			if (pNode->m_pRight != NULL && pNode->m_pLeft != NULL)
			{
				CAtlNodeValue dValueData(0);
				CAtlNodeValue dValueIndex(0);
				dValueIndex = Solve(pNode->m_pRight);
				nIndex = (long)dValueIndex.m_dValue;
				dValueData = Solve(pNode->m_pLeft);
				long nVal = 0;
				
				if (dValueData.m_VT == NodeValueDouble)
				{
					double dVal = pow(10.0, nIndex);
					dVal = dValueData.m_dValue / dVal;
					nVal = (long)dVal;
					nVal = nVal % 10;
				}
				
				dValue.m_dValue = nVal;
			}
		}
		break;
	case FUNCID_BINARY:    //0X15  //"binary",
		{
			long nIndex = 0;
			
			if (pNode->m_pRight != NULL && pNode->m_pLeft != NULL)
			{
				CAtlNodeValue dValueIndex(0);
				dValueIndex = Solve(pNode->m_pRight);
				nIndex = (long)dValueIndex.m_dValue;
				
				if (nIndex < 0)
				{
					nIndex = 0;
				}
				
				CAtlNodeValue dValueData(0);
				dValueData = Solve(pNode->m_pLeft);
				long nVal = 0;
				
				if (dValueData.m_VT == NodeValueDouble)
				{
					nVal = (long)dValueData.m_dValue;
					nVal = (nVal >> nIndex) & 0x01;
				}
				
				dValue.m_dValue = nVal;
			}
		}
		break;
	default:
		break;
	}
	return dValue;	
}


BOOL CAtlExpression::GetValueByVariable(BSTR bstrVariable, BSTR *pbstrValue)
{
	BOOL bResult = FALSE;
	long nReturn = 0;

	if (m_pConstVariables != NULL)
	{
		m_pConstVariables->IsKeyExist(bstrVariable, &nReturn);
		if (nReturn == 1)
		{
			bResult = TRUE;
			m_pConstVariables->GetString(bstrVariable,NULL, pbstrValue);
		}
	}
	
	if (!bResult && m_pTempVariables != NULL)
	{
		m_pTempVariables->IsKeyExist(bstrVariable, &nReturn);
		if (nReturn == 1)
		{
			bResult = TRUE;
			m_pTempVariables->GetString(bstrVariable,NULL,pbstrValue);
		}
	}
	
	if (!bResult)
	{
		m_pScriptSyntaxs->AddNew(0, bstrVariable, ERR_UNDEFINEDVARIABLE);
	}
	
	return bResult;
}

BOOL CAtlExpression::GetValueByVariable(const CComBSTR &strVariable, CComBSTR &strValue)
{
	BOOL bResult = FALSE;
	long nReturn = 0;
	BSTR bstrValue;
	
	if (m_pConstVariables != NULL)
	{
		m_pConstVariables->IsKeyExist(strVariable, &nReturn);
		if (nReturn == 1)
		{
			bResult = TRUE;
			m_pConstVariables->GetString(strVariable, NULL, &bstrValue);
			strValue = bstrValue;
		}
	}
	
	if (!bResult && m_pTempVariables != NULL)
	{
		m_pTempVariables->IsKeyExist(strVariable, &nReturn);
		if (nReturn == 1)
		{
			bResult = TRUE;
			m_pTempVariables->GetString(strVariable,NULL,&bstrValue);
			strValue = bstrValue;
		}
	}
	
	if (!bResult)
	{
		m_pScriptSyntaxs->AddNew(0, strVariable, ERR_UNDEFINEDVARIABLE);
	}
	
	return bResult;
}

void CAtlExpression::CompileKeyWord()
{
	if (IsStringAReal(m_pszKeyWord))
	{//实数
	}
	else if (*m_pszKeyWord == '\"')
	{//字符串
	}
	else
	{//变量
		if (FindVariable(m_pszKeyWord) )
		{
		}
		else
		{
			m_pScriptSyntaxs->AddNew(-1, m_pszKeyWord, SYNTAXERR_UNDEFVARIABLE);
		}
	}
}


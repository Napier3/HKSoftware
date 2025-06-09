// AtlExpression.h : main header file for the FUNCTION application
//
#if !defined(_ATLEXPRESSION_H__)
#define _ATLEXPRESSION_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\..\Module\AtlMemBuffer\WEquationBuffer.h"
#include "AtlScriptSyntax.h"
#include "..\..\Common\SystemTool\SystemTool_i.h"

#define MAXSIZE_KEYWORD	 100
#define COUNT_OPTR	     16
#define COUNT_FUNCTION	 22

#define FUNCID_SIN    0X00  //"sin",
#define FUNCID_COS    0X01  //"cos",
#define FUNCID_EXP    0X02  //"exp",
#define FUNCID_SQRT   0X03  //"sqrt",
#define FUNCID_LOG10  0X04  //"log10",
#define FUNCID_TAN    0X05  //"tan",
#define FUNCID_CTAN   0X06  //"ctan",
#define FUNCID_ASIN   0X07  //"asin",
#define FUNCID_ACOS   0X08  //"acos",
#define FUNCID_ATAN2  0X09  //"atan2",
#define FUNCID_ABS    0X0A  //"abs",
#define FUNCID_LOG    0X0B  //"log",
#define FUNCID_MIN    0X0C  //"min",
#define FUNCID_MAX    0X0D  //"max",
#define FUNCID_POW    0X0E  //"pow",
#define FUNCID_CEIL   0X0F  //"ceil",
#define FUNCID_FLOOR  0X10  //"floor",
#define FUNCID_HYPOT  0X11  //"hypot",
#define FUNCID_ATAN   0X12  //"atan",
#define FUNCID_FMOD   0X13  //"fmod"
#define FUNCID_DIGIT    0X14  //"digit",
#define FUNCID_BINARY   0X15  //"binary"

#define KEYWORDTYPE_ERR         -1
#define KEYWORDTYPE_REAL        0
#define KEYWORDTYPE_OPERATOR    1
#define KEYWORDTYPE_STRING      2
#define KEYWORDTYPE_VARIABLE    3
#define KEYWORDTYPE_FUNCTION    4
#define KEYWORDTYPE_FUNCSPLIT   5

#define SYNTAXERR_UNDEFVARIABLE     0
#define SYNTAXERR_FUNCPARAERR       1
#define SYNTAXERR_EXPRERROR         2
#define SYNTAXERR_FUNCSLPIT         3


#define NodeValueDouble 0
#define NodeValueString 1

#include <math.h>

class CAtlNodeValue  
{
public:
	long m_VT;
	union 
	{
		wchar_t   *m_pszValue;
		double	  m_dValue;
	};
	
public:
	CAtlNodeValue();
	CAtlNodeValue(const wchar_t *val);
	CAtlNodeValue(const CComBSTR &val);
	CAtlNodeValue(double val);
	CAtlNodeValue(int val);
	CAtlNodeValue(long val);
	CAtlNodeValue(const CAtlNodeValue &val);
	virtual ~CAtlNodeValue();
	void FreeValue();
	void ToString(CComBSTR &strValue);
	const CAtlNodeValue& GetNotValue();
	
public:
	const CAtlNodeValue& operator = (float val);
	const CAtlNodeValue& operator = (double val);
	const CAtlNodeValue& operator = (int val);
	const CAtlNodeValue& operator = (long val);
	const CAtlNodeValue& operator = (const wchar_t* val);		
	const CAtlNodeValue& operator = (const CComBSTR &val);		
	const CAtlNodeValue& operator = (const CAtlNodeValue &val);
	const CAtlNodeValue& operator += (const CAtlNodeValue &val);
	const CAtlNodeValue& operator / (const CAtlNodeValue &val);

	BOOL operator < (const CAtlNodeValue &val);
	BOOL operator <= (const CAtlNodeValue &val);
	BOOL operator > (const CAtlNodeValue &val);
	BOOL operator >= (const CAtlNodeValue &val);
	
	BOOL operator == (const CAtlNodeValue &val);
	BOOL operator == (int val);
	BOOL operator == (long val);
	BOOL operator == (double val);
	BOOL operator == (float val);
	BOOL operator == (wchar_t* val);
	BOOL operator == (const CComBSTR &val);
	
private:
	static const long g_nTempBufferLen;
	
};

CAtlNodeValue __stdcall operator +  (const CAtlNodeValue& v1, const CAtlNodeValue& v2);
CAtlNodeValue __stdcall operator -  (const CAtlNodeValue& v1, const CAtlNodeValue& v2);
CAtlNodeValue __stdcall operator *  (const CAtlNodeValue& v1, const CAtlNodeValue& v2);
CAtlNodeValue __stdcall operator /  (const CAtlNodeValue& v1, const CAtlNodeValue& v2);
CAtlNodeValue __stdcall operator != (const CAtlNodeValue& v1, const CAtlNodeValue& v2);
CAtlNodeValue __stdcall operator && (const CAtlNodeValue& v1, const CAtlNodeValue& v2);
CAtlNodeValue __stdcall operator || (const CAtlNodeValue& v1, const CAtlNodeValue& v2);
CAtlNodeValue __stdcall operator <  (const CAtlNodeValue& v1, const CAtlNodeValue& v2);
CAtlNodeValue __stdcall operator >  (const CAtlNodeValue& v1, const CAtlNodeValue& v2);
CAtlNodeValue __stdcall operator <= (const CAtlNodeValue& v1, const CAtlNodeValue& v2);
CAtlNodeValue __stdcall operator >= (const CAtlNodeValue& v1, const CAtlNodeValue& v2);

class CStringStack
{
public:
	class CStringStackData
	{
	private:
		CStringStackData()	{	m_pNext = NULL;	m_pData = NULL;	}
	public:
		CStringStackData(const wchar_t *pData, CStringStackData *pNext)
		{
			long nLen = wcslen(pData);
			m_pData = new wchar_t [nLen+1];
			wcscpy(m_pData, pData);
			m_pNext = pNext;
		}
		~CStringStackData()
		{
			delete m_pData;
		}
		wchar_t *m_pData;
		CStringStackData *m_pNext;
	};
public:
	CStringStack(){m_pHeadNode = NULL; m_nLength=0;}
	~CStringStack()
	{
		Empty();
	}
	bool Empty();
	bool IsEmpty();
	bool Pop();
	bool Push(const wchar_t *pData);
	const wchar_t* Top();
	int GetSize(){ return m_nLength;}

private:
	CStringStackData *m_pHeadNode;
	int      m_nLength;
};

class CAtlExprNode
{
public:
	CAtlExprNode(const CComBSTR & str="", CAtlExprNode *pLeft = NULL, CAtlExprNode *pRight = NULL, CAtlExprNode *pParent = NULL)
	{
		wcscpy(m_pszID, str);
		m_pLeft = pLeft;
		m_pRight = pRight;
		m_pParent = pParent;

		if (m_pLeft != NULL)
		{
			m_pLeft->m_pParent = this;
		}
		
		if (m_pRight != NULL)
		{
			m_pRight->m_pParent = this;
		}		
	}
	CAtlExprNode(const wchar_t *pszID, CAtlExprNode *pLeft = NULL, CAtlExprNode *pRight = NULL, CAtlExprNode *pParent = NULL)
	{
		wcscpy(m_pszID, pszID);
		m_pLeft=pLeft;
		m_pRight=pRight;

		if (m_pLeft != NULL)
		{
			m_pLeft->m_pParent = this;
		}
		
		if (m_pRight != NULL)
		{
			m_pRight->m_pParent = this;
		}

		m_pParent=pParent;
	}

	const CAtlExprNode& operator=(const CAtlExprNode& tn)
	{
		wcscpy(m_pszID,tn.m_pszID);
		m_pLeft   = tn.m_pLeft;
		m_pRight  = tn.m_pRight;
		m_pParent = tn.m_pParent;
	}

	virtual ~CAtlExprNode()
	{
		if (m_pLeft != NULL)
		{
			delete m_pLeft;
			m_pLeft = NULL;
		}
		if (m_pRight != NULL)
		{
			delete m_pRight;
			m_pRight = NULL;
		}
	}
	
	wchar_t m_pszID[MAXSIZE_KEYWORD];
	CAtlExprNode *m_pParent;
	CAtlExprNode *m_pLeft;
	CAtlExprNode *m_pRight;
};

class CAtlExprStack
{
public:
	class CAtlExprStackData
	{
	private:
		CAtlExprStackData()	{	m_pNext = NULL;	m_pData = NULL;	}
		
	public:
		CAtlExprStackData(CAtlExprNode *pData, CAtlExprStackData *pNext)
		{
			m_pData = pData;
			m_pNext = pNext;
		}
		~CAtlExprStackData()
		{
		}
		CAtlExprNode *m_pData;
		CAtlExprStackData *m_pNext;
	};
public:
	CAtlExprStack(){m_pHeadNode = NULL; m_nLength=0;}
	virtual ~CAtlExprStack()	{		Empty();	}
	bool Empty();
	bool IsEmpty();
	bool Pop();
	bool Push(CAtlExprNode *pData);
	CAtlExprNode* Top();
	int GetSize()	{ return m_nLength;	}
	
private:
	CAtlExprStackData *m_pHeadNode;
	int      m_nLength;
};

class CAtlExpression  
{
public:
	static const wchar_t m_pszOptrSymbol[COUNT_OPTR][3];
	static const wchar_t m_pszOptrPriority[COUNT_OPTR][COUNT_OPTR];
	static const wchar_t m_pszFunction[COUNT_FUNCTION][8];

public:
	CAtlExpression();
	virtual ~CAtlExpression();
	void CreateConstVariables();
	void Release();

	long SetAtlExpression(const wchar_t *pszAtlExpression);
	long SetAtlExpression(const CComBSTR &strAtlExpression);
	CAtlExprNode* GetExprRootNode(){return m_pExprRootNode;}

	int Value(double & dValue);	// gets the value of the expression
	int Value(CComBSTR &strValue);	// gets the value of the expression
	
public:
	//表达式的语法检测和运算，成功返回0，否则返回-1
	void AttachConstVariables(IEquation* pVariables);
	void AttachTempVariables(IEquation* pVariables);
	void AttachConstVariables(LPDISPATCH pVariables);
	void AttachTempVariables(LPDISPATCH pVariables);
	
	void SetConstVariables(const CComBSTR &strVariables, BOOL bAddNew);
	void SetConstVariables(const wchar_t* strVariables, BOOL bAddNew);
	void SetConstVariables(BSTR bstrVariables, BOOL bAddNew);
	void AddVariable(const CComBSTR &strVariavle,const CComBSTR &strValue);
	
	BOOL FindVariable(BSTR bstrVariable);
	BOOL FindVariable(const wchar_t *pszVariable);
	BOOL FindVariable(const CComBSTR &strVariable);
	BOOL IsTempVariable(BSTR bstrVariable);
	BOOL IsTempVariable(const wchar_t *pszVariable);
	BOOL IsTempVariable(const CComBSTR &strVariable);

	CAtlScriptSyntaxs* GetScriptSyntaxs()	{	return m_pScriptSyntaxs;	};
	void ClearError()	{	m_pScriptSyntaxs->ReleaseSyntaxs();	}
	
private:
	wchar_t *m_pszExprBuff;
	long m_nExprBuffLen;
	long m_nCurrPos;

	IEquation *m_pConstVariables;	//变量表
	IEquation *m_pTempVariables;	//扩展变量表

	void FreeBuff();
	//语法错误
	CAtlScriptSyntaxs *m_pScriptSyntaxs;
	
	//////////////////////////////////////////////////////////////////////////
	//构建二叉树
	CAtlExprNode *m_pExprRootNode;
	wchar_t m_pszKeyWord[MAXSIZE_KEYWORD];
	
	long BuildAtlExpressionTree();
	bool ReadFunctionPara(CAtlExprNode *pFuncNode);
	void Offset();
	bool IsStringAReal(const wchar_t *pszData);
	bool GetOperator(wchar_t *pBuff, long &nLength);
	bool IsOperator(const wchar_t ch);
	bool GetFunction(wchar_t *pBuff, long &nLength);
	long GetFunctionID(wchar_t *pFuncName);
	bool GetReal(wchar_t *pBuff, long &nLength);
	bool GetString(wchar_t *pBuff, long &nLength);
	bool GetVariable(wchar_t *pBuff, long &nLength);
	bool IsSplitChar(wchar_t ch);
	bool IsIgnoreChar(wchar_t ch);
	int GetOperatorLevel(const wchar_t *pOptr);
	int GetOperatorParaCount(const wchar_t *pOptr);
	wchar_t PrecedOptr(const wchar_t *pOptr1, const wchar_t *pOptr2);
	long ReadAKeyWord(long &nLength);
	CAtlNodeValue Solve(CAtlExprNode *pNode);
	CAtlNodeValue SolveOperator(CAtlExprNode *pNode);
	CAtlNodeValue SolveFunction(CAtlExprNode *pNode);

	BOOL GetValueByVariable(BSTR bstrVariable, BSTR *pbstrValue);
	BOOL GetValueByVariable(const CComBSTR &strVariable, CComBSTR &strValue);	

	//////////////////////////////////////////////////////////////////////////
	//表达式模式
private:
	long m_nExprMode;

public:
	bool IsExprCalMode()		{	return (m_nExprMode == 0); }
	bool IsExprConpileMode()	{	return (m_nExprMode == 1); }
	void SetExprCalMode()		{	m_nExprMode = 0; }
	void SetExprConpileMode()	{	m_nExprMode = 1; }
	void CompileKeyWord();

private:
	static const wchar_t m_strOptrEnd[2];
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_ATLEXPRESSION_H__)

#if !defined(_ATL_SCRIPTSYNTAX_H__)
#define _ATL_SCRIPTSYNTAX_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScriptSyntax.h : header file
//

#include "..\..\Module\AtlBaseClass\AtlBaseObjectList.h"

//possible erro occured when excuting expression
#define DIVISION_BY_0             1
#define ILEGAL_OPERATION          2
#define ERR_UNDEFINEDVARIABLE     3
#define INVALID_DOMAIN            4
//possible erro occured when compiling expression
#define ERR_UNDEFINEDVARIABLE     3
#define ERR_EXPRESSION_INCOMPLETE 5
#define BRACKET_INMATCH           6
#define MIN_MAX_ERROR             7
#define EXPRESSION_REDUNDANCY     8
//表达式错误id
#define  EXPRESSION_ERROR         -1

//possible error occured when compiling head file
//the error also possible occured when compiling init value sentence 
//in cpp file except the error whose id is 23.
#define ERR_MISS_EQUATIONMARK     9
#define EQUALSIGN_NUM_IS_TWO      10
#define ERR_MISS_SEMICOLON         11
#define EQUALSIGN_LEFTTOKEN_IS_CONSTVAL      12
#define EQUALSIGN_LEFTTOKEN_ISNOT_ONE        13
#define EQUALSIGN_RIGHTTOKEN_ISNOT_ONE       14
#define EQUALSIGN_RIGHTTOKEN_ISNOT_CONSTVAL  23

//possible error occured when compile cpp file
#define NEXT_LINE_OF_IF_ISNOT_LEFTBIGBRACKET 15
#define ERR_ELSE_MISS_IF                     16
#define BETWEEN_ELSE_IF_NOT_SPACE            17
#define BIGBRACKET_LEFT_MORE_RIGHT           18
#define BIGBRACKET_RIGHT_MORE_LEFT           19
#define SCRIPT_IS_EMPTY                      24
#define BIGBRACKET_LEFT_RIGHT_NOT_MATCH      25

//possible error occured when compile if sentence in cpp file
#define NEXT_CHAR_OF_IF_ISNOT_LEFTSMALLBRACKET       20
#define TAIL_CHAR_OF_IF_LINE_ISNOT_RIGHTSMALLBRACKET 21
#define IF_LINE_IS_EMPTY                             22

//possible error occured when compile for sentence in cpp file
#define NEXT_CHAR_OF_FOR_ISNOT_LEFTSMALLBRACKET      30
#define TAIL_CHAR_OF_FOR_ISNOT_RIGHTTSMALLBRACKET    31
#define FOR_LINE_IS_EMPTY                            32
#define FOR_LINE_SONSENTENCE_ISNOT_THREE             33
#define NEXT_LINE_OF_FOR_ISNOT_LEFTBIGBRACKET        34

//posssible error occured when compile jump sentence in cpp  file
#define JUMP_SENTENCE_WRONG                          40
#define JUMP_KEYWORD_ISNOT_IN_FOR_CIRCLE             41
//possible error occured when compile self_define function sentence in cpp file
#define NEXT_CHAR_OF_FUNCKEYWORD_ISNOT_LEFTSMALLBRACKET  46
#define TAIL_CHAR_OF_FUNCTION_ISNOT_RIGHTTSMALLBRACKET   47
#define FUNCTION_LINE_IS_EMPTY                           48
#define FUNCTION_LINE_PARAMETER_IS_EMPTY                 49

//2005.9.17增加的一个错误id
#define NEXT_LINE_OF_ELSE_ISNOT_LEFTBIGBRACKET  50

//2005.9.19增加的一个错误id，赋值语句左值未定义
#define LEFT_VARIABLE_OF_INIT_SENTENCE_UNDEFINE 51

//2005.9.20增加的一个错误id，for语句的分支语句不能为空
#define  FOR_SUBSENTENCE_IS_VOID                52

//construct error msg
void ConstructErrorMsg(CComBSTR &strMsg, int errID);


/////////////////////////////////////////////////////////////////////////////
// CAtlScriptSyntax command target

class CAtlScriptSyntax : public CAtlBaseObject
{

public:
	CAtlScriptSyntax();     
	CAtlScriptSyntax(long nLineIndex,const CComBSTR &strSyntax,long nErrorID);
	virtual ~CAtlScriptSyntax();
	
	void InitSyntaxError()
	{
		if (m_strSyntaxError.Length() == 0)
		{
			ConstructErrorMsg(m_strSyntaxError,m_nErrorID);
		}
	}
	
	void FormartVariableUndef(const CComBSTR &strVariable)
	{
		m_strSyntaxError = _T("Variable not defined:");
		m_strSyntaxError += strVariable;
	}
	
// Attributes
public:
	long m_nLineIndex;
	CComBSTR m_strSyntaxError;
	long m_nErrorID;

// Operations
public:
	const CAtlScriptSyntax& operator = (const CAtlScriptSyntax &val);
		
};


class CAtlScriptSyntaxs : public CAtlBaseObject
{
public:
	CAtlScriptSyntaxs();           // protected constructor used by dynamic creation
	virtual ~CAtlScriptSyntaxs();

	CAtlScriptSyntax* AddNew(long nLineIndex,const CComBSTR &strSyntax,long nErrorID=0);
	CAtlScriptSyntax* AddNew(CAtlScriptSyntax *pScriptSyntax);
	void Append(CAtlScriptSyntaxs *pScriptSyntaxs);
	void AddNew(CAtlScriptSyntaxs *pScriptSyntaxs,long nLineIndex);
	void ReleaseSyntaxs()	{	m_listSyntax.DeleteAll();	}
	
// Attributes
public:
	CAtlBaseObjectList m_listSyntax;

// Operations
public:
	long GetCount()	    {	return m_listSyntax.GetCount();	}
	CAtlScriptSyntax* GetItem(long nIndex)  {     return (CAtlScriptSyntax*)(m_listSyntax.GetAtIndex(nIndex));     }
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_ATL_SCRIPTSYNTAX_H__)

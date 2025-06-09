// ScriptSyntax.cpp : implementation file
//

#include "stdafx.h"
#include "AtlScriptSyntax.h"


/////////////////////////////////////////////////////////////////////////////
// CAtlScriptSyntax

CAtlScriptSyntax::CAtlScriptSyntax()
{
}

CAtlScriptSyntax::CAtlScriptSyntax(long nLineIndex,const CComBSTR &strSyntax,long nErrorID)
{
	m_nErrorID = nErrorID;
	m_nLineIndex = nLineIndex;
	
	if (ERR_UNDEFINEDVARIABLE == m_nErrorID)
	{
		FormartVariableUndef(strSyntax);
	}
	else
	{
		m_strSyntaxError = strSyntax;
	}
	
	InitSyntaxError();	
}

CAtlScriptSyntax::~CAtlScriptSyntax()
{
}

const CAtlScriptSyntax& CAtlScriptSyntax::operator = (const CAtlScriptSyntax &val)
{
	m_nErrorID = val.m_nErrorID;
	m_nLineIndex = val.m_nLineIndex;
	
	if (ERR_UNDEFINEDVARIABLE == m_nErrorID)
	{
		FormartVariableUndef(val.m_strSyntaxError);
	}
	else
	{
		m_strSyntaxError = val.m_strSyntaxError;
	}
	
	InitSyntaxError();
	
	return *this;
}

void ConstructErrorMsg(CComBSTR &strMsg, int errID)
{
	switch(errID) 
	{
	case DIVISION_BY_0:
		strMsg =_T( "除数为0");
		break;
	case ERR_UNDEFINEDVARIABLE:
		strMsg =_T( "变量没有定义");
		break;
	case ERR_EXPRESSION_INCOMPLETE:
		strMsg =_T( "表达式不完整");
		break;
	case BRACKET_INMATCH:
		strMsg =_T( "左右小括号不配对");
		break;
	case MIN_MAX_ERROR:
		strMsg =_T( "二元运算语法错误");
		break;
	case EXPRESSION_REDUNDANCY:
		strMsg =_T( "表达式冗余");
		break;
	case ERR_MISS_EQUATIONMARK:
		strMsg =_T( "缺少“=”");
		break;
	case ERR_MISS_SEMICOLON:
		strMsg =_T( "行末没有';'符");
		break;
	case EQUALSIGN_LEFTTOKEN_IS_CONSTVAL:
		strMsg =_T( "等式左边使用常量变量");
		break;
	case EQUALSIGN_LEFTTOKEN_ISNOT_ONE:
		strMsg =_T( "等号前面变量数不为1");
		break;
	case EQUALSIGN_RIGHTTOKEN_ISNOT_ONE:
		strMsg =_T( "等号后面变量数不为1");
		break;
	case EQUALSIGN_RIGHTTOKEN_ISNOT_CONSTVAL:
		strMsg =_T( "不支持字符串赋值");
		break;
	case NEXT_LINE_OF_IF_ISNOT_LEFTBIGBRACKET:
		strMsg =_T( "if模块必须用大括号封装");
		break;
	case NEXT_LINE_OF_ELSE_ISNOT_LEFTBIGBRACKET:
		strMsg =_T( "else模块必须用大括号封装");
		break;
	case ERR_ELSE_MISS_IF:
		strMsg =_T( "else缺少if");
		break;
	case BETWEEN_ELSE_IF_NOT_SPACE:
		strMsg =_T( "else模块前面不为if模块");
		break;
	case BIGBRACKET_LEFT_MORE_RIGHT:
		strMsg =_T( "脚本中缺少右大括号");
		break;
	case BIGBRACKET_RIGHT_MORE_LEFT:
		strMsg =_T( "脚本中缺少左大括号");
		break;
	case SCRIPT_IS_EMPTY:
		strMsg =_T( "脚本为空");
		break;
	case BIGBRACKET_LEFT_RIGHT_NOT_MATCH:
		strMsg =_T( "脚本左右括号不配对");
		break;
	case FOR_LINE_SONSENTENCE_ISNOT_THREE:
		strMsg =_T( "for语句必须只能为三个分支");
		break;
	case JUMP_SENTENCE_WRONG:
		strMsg =_T( "跳转语句不合法");
		break;
	case JUMP_KEYWORD_ISNOT_IN_FOR_CIRCLE:
		strMsg =_T( "跳转语句在for循环体之外");
		break;
	case NEXT_CHAR_OF_FUNCKEYWORD_ISNOT_LEFTSMALLBRACKET:
		strMsg =_T( "自定义函数缺少左括号");
		break;
	case TAIL_CHAR_OF_FUNCTION_ISNOT_RIGHTTSMALLBRACKET:
		strMsg =_T( "自定义函数缺少右括号");
		break;
	case FUNCTION_LINE_IS_EMPTY:
		strMsg =_T( "自定义函数不能为空");
		break;
	case FUNCTION_LINE_PARAMETER_IS_EMPTY:
		strMsg =_T( "自定义函数参数不能为空");
		break;
	default:
		;
	}
}



CAtlScriptSyntaxs::CAtlScriptSyntaxs()
{
}

CAtlScriptSyntaxs::~CAtlScriptSyntaxs()
{
}


/////////////////////////////////////////////////////////////////////////////
// CAtlScriptSyntaxs message handlers

CAtlScriptSyntax* CAtlScriptSyntaxs::AddNew(long nLineIndex,const CComBSTR &strSyntax,long nErrorID)
{
	CAtlScriptSyntax *pNew = new CAtlScriptSyntax(nLineIndex, strSyntax, nErrorID);
	m_listSyntax.AddTail(pNew);
	
	return pNew;
}


CAtlScriptSyntax* CAtlScriptSyntaxs::AddNew(CAtlScriptSyntax *pScriptSyntax)
{
	CAtlScriptSyntax *pNew = new CAtlScriptSyntax();
	*pNew = *pScriptSyntax;
	m_listSyntax.AddTail(pNew);
	
	return pNew;
}


void CAtlScriptSyntaxs::Append(CAtlScriptSyntaxs *pScriptSyntaxs)
{
	CAtlScriptSyntax *pScriptSyntax = NULL;
	POS pos = pScriptSyntaxs->m_listSyntax.GetHeadPosition();
	while (pos != NULL)
	{
		pScriptSyntax = (CAtlScriptSyntax*)pScriptSyntaxs->m_listSyntax.GetNext(pos);
		AddNew(pScriptSyntax);
	}
}

void CAtlScriptSyntaxs::AddNew(CAtlScriptSyntaxs *pScriptSyntaxs,long nLineIndex)
{
	CAtlScriptSyntax *pScriptSyntax = NULL;
	POS pos = pScriptSyntaxs->m_listSyntax.GetHeadPosition();
	
	while (pos != NULL)
	{
		pScriptSyntax = (CAtlScriptSyntax*)pScriptSyntaxs->m_listSyntax.GetNext(pos);
		pScriptSyntax->m_nLineIndex = nLineIndex;
		AddNew(pScriptSyntax);
	}
}

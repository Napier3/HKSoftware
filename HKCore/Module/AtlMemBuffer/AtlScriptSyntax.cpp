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
		strMsg =_T( "����Ϊ0");
		break;
	case ERR_UNDEFINEDVARIABLE:
		strMsg =_T( "����û�ж���");
		break;
	case ERR_EXPRESSION_INCOMPLETE:
		strMsg =_T( "���ʽ������");
		break;
	case BRACKET_INMATCH:
		strMsg =_T( "����С���Ų����");
		break;
	case MIN_MAX_ERROR:
		strMsg =_T( "��Ԫ�����﷨����");
		break;
	case EXPRESSION_REDUNDANCY:
		strMsg =_T( "���ʽ����");
		break;
	case ERR_MISS_EQUATIONMARK:
		strMsg =_T( "ȱ�١�=��");
		break;
	case ERR_MISS_SEMICOLON:
		strMsg =_T( "��ĩû��';'��");
		break;
	case EQUALSIGN_LEFTTOKEN_IS_CONSTVAL:
		strMsg =_T( "��ʽ���ʹ�ó�������");
		break;
	case EQUALSIGN_LEFTTOKEN_ISNOT_ONE:
		strMsg =_T( "�Ⱥ�ǰ���������Ϊ1");
		break;
	case EQUALSIGN_RIGHTTOKEN_ISNOT_ONE:
		strMsg =_T( "�Ⱥź����������Ϊ1");
		break;
	case EQUALSIGN_RIGHTTOKEN_ISNOT_CONSTVAL:
		strMsg =_T( "��֧���ַ�����ֵ");
		break;
	case NEXT_LINE_OF_IF_ISNOT_LEFTBIGBRACKET:
		strMsg =_T( "ifģ������ô����ŷ�װ");
		break;
	case NEXT_LINE_OF_ELSE_ISNOT_LEFTBIGBRACKET:
		strMsg =_T( "elseģ������ô����ŷ�װ");
		break;
	case ERR_ELSE_MISS_IF:
		strMsg =_T( "elseȱ��if");
		break;
	case BETWEEN_ELSE_IF_NOT_SPACE:
		strMsg =_T( "elseģ��ǰ�治Ϊifģ��");
		break;
	case BIGBRACKET_LEFT_MORE_RIGHT:
		strMsg =_T( "�ű���ȱ���Ҵ�����");
		break;
	case BIGBRACKET_RIGHT_MORE_LEFT:
		strMsg =_T( "�ű���ȱ���������");
		break;
	case SCRIPT_IS_EMPTY:
		strMsg =_T( "�ű�Ϊ��");
		break;
	case BIGBRACKET_LEFT_RIGHT_NOT_MATCH:
		strMsg =_T( "�ű��������Ų����");
		break;
	case FOR_LINE_SONSENTENCE_ISNOT_THREE:
		strMsg =_T( "for������ֻ��Ϊ������֧");
		break;
	case JUMP_SENTENCE_WRONG:
		strMsg =_T( "��ת��䲻�Ϸ�");
		break;
	case JUMP_KEYWORD_ISNOT_IN_FOR_CIRCLE:
		strMsg =_T( "��ת�����forѭ����֮��");
		break;
	case NEXT_CHAR_OF_FUNCKEYWORD_ISNOT_LEFTSMALLBRACKET:
		strMsg =_T( "�Զ��庯��ȱ��������");
		break;
	case TAIL_CHAR_OF_FUNCTION_ISNOT_RIGHTTSMALLBRACKET:
		strMsg =_T( "�Զ��庯��ȱ��������");
		break;
	case FUNCTION_LINE_IS_EMPTY:
		strMsg =_T( "�Զ��庯������Ϊ��");
		break;
	case FUNCTION_LINE_PARAMETER_IS_EMPTY:
		strMsg =_T( "�Զ��庯����������Ϊ��");
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

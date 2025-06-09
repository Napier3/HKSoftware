// EpExpression.h : main header file for the FUNCTION application
//
#if !defined(_EPEXPRESSION_H__)
#define _EPEXPRESSION_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// #include "..\BaseClass\TLinkList.h"
// #include "..\API\StringApi.h"
// 
// // Tree evaluation variables
// 
// #define DIVISION_BY_0 1
// #define ILEGAL_OPERATION 2
// #define UNDEFINED_VARIABLE 3
// #define INVALID_DOMAIN 4
// 
// 
// #define OPERATOR_SIN	150
// #define OPERATOR_COS	151
// #define OPERATOR_EXP	152
// #define OPERATOR_SQRT	153
// #define OPERATOR_LOG	154
// #define OPERATOR_TG		155
// #define OPERATOR_CTG	156
// #define OPERATOR_ASIN	157
// #define OPERATOR_ACOS	158
// #define OPERATOR_ATG	159
// 
// #define OPERATOR_NOTMORE	160	//is less than or equal to 小于或等于号
// #define OPERATOR_NOTLESS	161	//is more than or equal to 大于或等于号
#include "EpExpressionGlobal.h"


/////////////////////////////////////////////////////////////////////////////
class CEpExpVariable
{
public:
	CEpExpVariable()
	{
		m_dValue = 0;
	}

	virtual ~CEpExpVariable()	{};

	CString m_strVarID;
	double m_dValue;
};

class CEpExpression : public CTLinkList<CEpExpVariable>
{
public:
	CEpExpression(CEpExpression &expresie);
	CEpExpression(char *pszEpExpression);
	CEpExpression(const CString &strEpExpression);

protected:
	CEpExpVariable* FindVariable(const CString &strVarID)
	{
		POS pos = GetHeadPosition();
		CEpExpVariable *p = NULL;
		CEpExpVariable *pFind = NULL;

		while (pos != NULL)
		{
			p = GetNext(pos);

			if (p->m_strVarID == strVarID)
			{
				pFind = p;
				break;
			}
		}

		return pFind;
	}

	CEpExpVariable* AddVariable(const CString &strVarID, double dValue = 0)
	{
		CEpExpVariable *pVar = FindVariable(strVarID);

		if (pVar != NULL)
		{
			return pVar;
		}

		pVar = new CEpExpVariable();
		pVar->m_strVarID = strVarID;
		pVar->m_dValue = dValue;
		AddTail(pVar);

		return pVar;
	}

	BOOL _v_isdigit(char c)
	{
		return '0' <= c && c <= '9';
	}

	BOOL _v_isalpha(char c)
	{
		if (c < 0)
		{
			return TRUE;
		}

		if (isalpha(c))
		{
			return TRUE;
		}

		if (c == '_')
		{
			return TRUE;
		}

		return FALSE;
	}

	BOOL _v_isalpha_ex(char c)
	{
		if (_v_isalpha(c))
		{
			return TRUE;
		}

		if (c == '.')
		{
			return TRUE;
		}

		if (c == '$')
		{
			return TRUE;
		}

		if (c == '\\')
		{
			ASSERT (FALSE);
			return TRUE;
		}

		return isdigit(c);
	}

public:
	struct structBinaryTreeNode 
	{
		struct structBinaryTreeNode *left,*right;
		unsigned char operatie; 
		union 
		{ 
			double valoare;
			CString *valoarestr;
		};
	};
	
	typedef structBinaryTreeNode NOD;
	typedef structBinaryTreeNode* PNOD;

	PNOD _newnode()
	{
		PNOD pNode = new NOD;
		pNode->left = NULL;
		pNode->right = NULL;
		pNode->operatie = 0;
		pNode->valoare = 0;
		return pNode;
	};
	
	PNOD CloneTree(void);
	int UpdateArbore(void);		// Update the tree
	PNOD GetArbore();
	int Value(double & valoare);	// gets the value of the epexpression
	int ChangeEpExpression(const CString &strEpExpression);	// Change epexpression
	int ChangeEpExpression(char *pszEpExpression);	// Change epexpression
#ifndef _PSX_IDE_QT_
    virtual void Serialize(CArchive& ar);		// The serialization function
#endif
	
	CEpExpression();
//	CEpExpression(CMapVariabile * vars);
	virtual ~CEpExpression();

private:
	char *m_pszEpExpression;			// the epexpression in string
	int m_nCurrPosition;					// string parsing variable
	PNOD m_pBTreeEpExpression;					// the expresion as a binary tree
	
	void InitEpExpression();
	void GetValueFromEpExpression(double &dVal,long lBeginPos,long lEndPos);
	void GetValueFromEpExpression(CString &strValue,long lBeginPos,long lEndPos);
	PNOD sgOp();
	PNOD logicalOp();
	void SkipSpaces();
	
	double vexp ( PNOD a );
	PNOD factor (void);			// the partial expresion parsing functions
	BOOL max_min(PNOD &oLeft,PNOD &oRight);//zhouhj20190916 增加用于最大值 最小值计算识别
	PNOD identificator(void);
	void identificator_var(int &poz, PNOD &nod, PNOD &nod2, PNOD &result, PNOD &pResultTemp);
	PNOD putere(void);
	PNOD termen(void);
	PNOD expresie(void);
	void Delete ( PNOD a);
	PNOD clone(PNOD arb);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_EPEXPRESSION_H__)

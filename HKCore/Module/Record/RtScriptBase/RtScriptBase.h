// RtScriptBase.h: interface for the CRtScriptBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RTSCRIPTBASE_H__)
#define _RTSCRIPTBASE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include "../../BASECLASS/ExBaseObject.h"
#include "../RecordGlobalDefine.h"

#define RTSCRIPT_OPTRID_ERROR     -1   //Error
#define RTSCRIPT_OPTRID_REFVALUE   0   //ref value
#define RTSCRIPT_OPTRID_NUMBER     1   //number

#define RTSCRIPT_OPTRID_ADD        2   //+
#define RTSCRIPT_OPTRID_SUB        3   //-
#define RTSCRIPT_OPTRID_MUL        4   //*
#define RTSCRIPT_OPTRID_DIV        5   ///
#define RTSCRIPT_OPTRID_L          6   //<
#define RTSCRIPT_OPTRID_LE         7   //<=
#define RTSCRIPT_OPTRID_G          8   //>
#define RTSCRIPT_OPTRID_GE         9   //>=
#define RTSCRIPT_OPTRID_E          10  //==
#define RTSCRIPT_OPTRID_OR         11  //||
#define RTSCRIPT_OPTRID_AND        12  //&&
#define RTSCRIPT_OPTRID_NOT        13  //!

#define RTSCRIPT_OPTRID_SIN        14  //sin
#define RTSCRIPT_OPTRID_COS        15  //cos
#define RTSCRIPT_OPTRID_EXP        16  //exp
#define RTSCRIPT_OPTRID_SQRT       17  //sqrt
#define RTSCRIPT_OPTRID_LOG10      18  //log10
#define RTSCRIPT_OPTRID_TAN        19  //tan
#define RTSCRIPT_OPTRID_CTAN       20  //ctan
#define RTSCRIPT_OPTRID_ASIN       21  //asin
#define RTSCRIPT_OPTRID_ACOS       22  //acos
#define RTSCRIPT_OPTRID_ATAN2      23  //atan2
#define RTSCRIPT_OPTRID_ABS        24  //abs
#define RTSCRIPT_OPTRID_LOG        25  //log
#define RTSCRIPT_OPTRID_MIN        26  //min
#define RTSCRIPT_OPTRID_MAX        27  //max
#define RTSCRIPT_OPTRID_POW        28  //pow
#define RTSCRIPT_OPTRID_CEIL       29  //ceil
#define RTSCRIPT_OPTRID_FLOOR      30  //floor
#define RTSCRIPT_OPTRID_HYPOT      31  //hypot
#define RTSCRIPT_OPTRID_ATAN       32  //atan
#define RTSCRIPT_OPTRID_FMOD       33  //fmod

class CRtScriptBase  : public CExBaseObject
{
public:
	typedef struct ExpNode
	{
		void     *pValue;
		unsigned long nOptrID;
		char     *pszID;
		long     m_nIsRefValue;
		struct ExpNode  *pLeft;
		struct ExpNode  *pRight;
		double   dCoef;

		ExpNode() 
		{	
			pValue = NULL; 
			pLeft = NULL; 
			pRight =NULL ; 
			nOptrID = -1; 
			pszID = NULL;	
			m_nIsRefValue = -1;
			dCoef = 1;
		}
	}* PEXPNODE,EXPNODE;
		
	BOOL m_bHasError;
	CString m_strOptr;

#define ZERO_VALUE     0.0001

public:
	//可以被外部调用的方法
	BOOL BuildExpression();
	BOOL RunExpression(double &dValue);
	BOOL RunExpression(float &fValue);
	BOOL RunExpression(long &nValue);
	BOOL RunExpression(short &nValue);
	long CalLongValue()     {    return (long)CalNode(m_pExpRoot);   }
	BOOL RunExpression();
	void ReadExpNodes(CXmlRWNodeBase &oScript);
	void WriteExpNodes(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement);
	void WriteExpNode(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, PEXPNODE pNode);
	
public:
	//关键字
	static const BSTR g_pszKeyScript;
	static const BSTR g_pszKeyLeft;
	static const BSTR g_pszKeyRight;
	static const BSTR g_pszKeyOptr;
	static const BSTR g_pszKeyVal;
	static const char* g_pszOperator[35];

public:
	CRtScriptBase();
	virtual ~CRtScriptBase();
	
	BOOL Clone(CRtScriptBase *pDest)
	{
		pDest->FreeExpNode(pDest->m_pExpRoot);
		pDest->m_pExpRoot = CloneExpNode(m_pExpRoot);
		
		return (pDest->m_pExpRoot != NULL);
	}
	
	virtual void* GetValueRefByID(char *pszID) = 0;
	virtual double GetCoefValueByID(char *pszID)   {  return 1;   }
	virtual BOOL ReleaseExpNodes();

public:
	virtual long ReadOwnXml(CXmlRWNodeBase &oNode);


	//根据硬件信息更新脚本属性
	virtual long RTUpdateOwnByAutofit(HDINFO &oHDInfo);
	long RTUpdateExpNode(PEXPNODE pNode, HDINFO &oHDInfo);
	
	//树形控件相关的操作
	virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand, HTREEITEM hAfter = TVI_LAST);
	void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, PEXPNODE pNode);

public:
	PEXPNODE NewExpNode();
	PEXPNODE ReadExpNode(CXmlRWNodeListBase &oNodes);
	PEXPNODE ReadOperandNode(CXmlRWNodeBase &oOperand);
	unsigned long ReadOperatorNode(CXmlRWNodeBase &oNode);
	BOOL FreeExpNode(PEXPNODE pNode);
	PEXPNODE CloneExpNode(PEXPNODE pNode);
	virtual BOOL CalExpNode(PEXPNODE pNode, UINT nIndex=0);
	virtual double CalNode(PEXPNODE pNode, UINT nIndex=0);

	BOOL BuildExpNode(PEXPNODE pNode);
	BOOL BuildExpNodeCoef(PEXPNODE pNode);
	BOOL BuildExpNodeCoef()  {      return BuildExpNodeCoef(m_pExpRoot);     }

	PEXPNODE m_pExpRoot;
	long     m_nIndex;
};


#define  SHORTVAL_MIN   -32767
#define  SHORTVAL_MAX   32767

#define  TRANS_TO_SHORT(nSrcVal, nDestShortVal)   {  \
	if (nSrcVal < SHORTVAL_MIN)          \
	{                                    \
		nDestShortVal = SHORTVAL_MIN;    \
	}                                    \
	else if (nSrcVal > SHORTVAL_MAX)     \
	{                                    \
		nDestShortVal = SHORTVAL_MAX;    \
	}                                    \
	else                                 \
	{                                    \
		nDestShortVal = (short)nSrcVal;         \
	}                                    \
}                                        \
	

#endif // !defined(_RTSCRIPTBASE_H__)

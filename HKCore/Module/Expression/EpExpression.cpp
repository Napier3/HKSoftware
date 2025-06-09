// Function.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "math.h"
#include "EpExpression.h"
#include <ctype.h>
#include "../API/MathApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////////
// Eliberarea memorie ocupate de arbore

void CEpExpression::Delete (PNOD a)
{
	if (a==NULL) 
		return;

	if (a->left!=NULL) 
		Delete(a->left);

	if (a->right!=NULL)
		Delete(a->right);

	if (a->operatie == '`')
		delete a->valoarestr;
	delete a;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void CEpExpression::InitEpExpression()
{
	if (m_pszEpExpression != NULL)
	{
		delete m_pszEpExpression;
	}
	m_pszEpExpression = new char [2];
	m_pszEpExpression[0] = 0;

}
CEpExpression::CEpExpression()
{
	m_pszEpExpression = NULL;
	m_pBTreeEpExpression = NULL;
	InitEpExpression();
	m_nCurrPosition = 0;
}
CEpExpression::CEpExpression(char *pszEpExpression)
{
	m_pBTreeEpExpression = NULL;

	ChangeEpExpression(pszEpExpression);
}

CEpExpression::CEpExpression(const CString &strEpExpression)
{
	m_pBTreeEpExpression = NULL;
	ChangeEpExpression(strEpExpression);
}

CEpExpression::~CEpExpression()
{
	if (m_pszEpExpression != NULL)
	{
		delete m_pszEpExpression;
	}
	Delete(m_pBTreeEpExpression);
}

#ifndef _PSX_IDE_QT_
void CEpExpression::Serialize(CArchive & ar)
{

}
#endif


void CEpExpression::GetValueFromEpExpression(double &dVal,long lBeginPos,long lEndPos)
{
	//2020-03-12  lijq  如果输入的数字太长，就会导致程序崩溃
	//char pszNumber[20];
	long nLen = lEndPos - lBeginPos + 4;
	char *pszNumber = new char [nLen];

	char *pTemp = NULL;
	char *pTempNumber = pszNumber;
	pTemp = &m_pszEpExpression[lBeginPos];
	char *pBeginPos = pTemp;
	char *pEndPos = &m_pszEpExpression[lEndPos];

	while (pTemp < pEndPos)
	{
		*pTempNumber = *pTemp;
		pTempNumber++;
		pTemp++;
	}

	*pTempNumber = 0;
	dVal = atof(pszNumber);

	//2020-03-12  lijq
	delete pszNumber;
}

void CEpExpression::GetValueFromEpExpression(CString &strValue,long lBeginPos,long lEndPos)
{
	char *pszNumber = new char [lEndPos - lBeginPos + 3];
	char *pTemp = NULL;
	char *pTempNumber = pszNumber;
	pTemp = &m_pszEpExpression[lBeginPos];
	char *pBeginPos = pTemp;
	char *pEndPos = &m_pszEpExpression[lEndPos];

	while (pTemp < pEndPos)
	{
		*pTempNumber = *pTemp;
		pTempNumber++;
		pTemp++;
	}

	*pTempNumber = 0;
	strValue = pszNumber;	
	delete pszNumber;
}

int CEpExpression::ChangeEpExpression(const CString &strEpExpression)
{
	if (m_pszEpExpression != NULL)
	{
		delete m_pszEpExpression;
	}

	long nLen = strEpExpression.GetLength();

#ifdef _UNICODE
	nLen = nLen * 2 + 8;
#else
	nLen  = nLen + 8;
#endif

	m_pszEpExpression = new char [nLen];
	CString_to_char(strEpExpression, m_pszEpExpression);
	nLen = strlen(m_pszEpExpression);

	m_pszEpExpression[nLen] = '\0' ;
	m_pszEpExpression[nLen+1] = '\0' ;
	m_pszEpExpression[nLen+2] = '\0' ;
	m_pszEpExpression[nLen+3] = '\0' ;
	
	m_nCurrPosition = 0;

	return UpdateArbore();
}

int CEpExpression::ChangeEpExpression(char *pszEpExpression)
{
	if (pszEpExpression != NULL)
	{
		long lLen = 0;
		lLen = strlen(pszEpExpression);
		m_pszEpExpression = new char [lLen+4];
		strcpy(m_pszEpExpression,pszEpExpression);
		m_pszEpExpression[lLen] = '\0' ;
		m_pszEpExpression[lLen+1] = '\0' ;
		m_pszEpExpression[lLen+2] = '\0' ;
		m_pszEpExpression[lLen+3] = '\0' ;
	}
	else
	{
		InitEpExpression();		
	}

	m_nCurrPosition = 0;

	return UpdateArbore();
}
// Error code var
int g_nErrorCode;


int CEpExpression::Value(double& valoare)
{
	g_nErrorCode = 0;

	if (m_pBTreeEpExpression == NULL)
	{
		return -1;
	}

	valoare = vexp(m_pBTreeEpExpression);

	return (g_nErrorCode);
}


double CEpExpression::vexp ( PNOD a )
{
	double dValue = 0;
	double dValue1 = 0;

	if (a->operatie==NULL)
	{
		g_nErrorCode = 10;
		return 0;
	}

	switch(a->operatie) 
	{
	case '+' : 
		dValue = vexp(a->left)+vexp(a->right);
		break;
	case '-' : 
		dValue = vexp(a->left)-vexp(a->right);
		break;
	case '*' : 
		
	case '&' :  //mym 2021-7-17 add
		dValue = vexp(a->left)*vexp(a->right);
		break;
	case '/' : 
		dValue = vexp(a->right) ;
		if (dValue == 0)
		{
			g_nErrorCode = DIVISION_BY_0;
			dValue = -vexp(a->left)/0.001;
		}
		else
		{
			dValue = (vexp(a->left) / dValue);
		}
		break;
	case '%' : 
		dValue = vexp(a->right) ;
		if (dValue == 0)
		{
			g_nErrorCode = DIVISION_BY_0;
			dValue = 0;
		}
		else
		{
			dValue = ((long)vexp(a->left)) % ((long)dValue);
		}
		break;

	case OPERATOR_SIN : 
		dValue = sin(vexp(a->left));
		break;
	case OPERATOR_COS : 
		dValue = cos(vexp(a->left));
		break;
	case OPERATOR_EXP : 
		dValue = exp(vexp(a->left));
		break;
	case OPERATOR_SQRT : 
		dValue = vexp(a->left) ;
		if (dValue<0)
		{
			g_nErrorCode = INVALID_DOMAIN;
			dValue = 0;
		}
		else
		{
			dValue = sqrt(dValue);
		}
		break;
	case OPERATOR_LOG : 
		dValue=vexp(a->left) ;
		if (dValue<=0) 
		{
			g_nErrorCode = INVALID_DOMAIN;
			dValue = 0;
		}
		else 
		{
			dValue = log(dValue);
		}
		break;
	case OPERATOR_TG : 
		dValue = (tan (vexp(a->left)));
		break;
	case OPERATOR_CTG :
		dValue = (1 / tan (vexp(a->left)));
		break;
	case OPERATOR_ASIN :
		return (asin (vexp(a->left)));
		break;
	case OPERATOR_ACOS :
		dValue = (acos (vexp(a->left)));
		break;
	case OPERATOR_ATG : 
		dValue = (atan (vexp(a->left)));
		break;

		//////////////////////////////////////////////////////////////////////////
		//角度相关函数
	case OPERATOR_SIND : 
		dValue = sin(vexp(a->left) * _PI_D_180);
		break;
	case OPERATOR_COSD : 
		dValue = cos(vexp(a->left) * _PI_D_180);
		break;
	case OPERATOR_TGD : 
		dValue = (tan (vexp(a->left) * _PI_D_180));
		break;
	case OPERATOR_CTGD :
		dValue = (1 / tan (vexp(a->left) * _PI_D_180));
		break;
	case OPERATOR_ASIND :
		return (asin (vexp(a->left)) * _180_D_PI);
		break;
	case OPERATOR_ACOSD :
		dValue = (acos (vexp(a->left)) * _180_D_PI);
		break;
	case OPERATOR_ATGD : 
		dValue = (atan (vexp(a->left)) * _180_D_PI);
		break;
	case OPERATOR_ABS : 
		dValue =(fabs(vexp(a->left)));
		break;
	case OPERATOR_MAX : 
		dValue =(vexp(a->left));
		dValue1 = (vexp(a->right));

		if (dValue1>dValue)
		{
			dValue = dValue1;
		}

		break;
	case OPERATOR_MIN : 
		dValue =(vexp(a->left));
		dValue1 = (vexp(a->right));

		if (dValue1<dValue)
		{
			dValue = dValue1;
		}

		break;
		//////////////////////////////////////////////////////////////////////////

	case '|' : 
		dValue =(fabs(vexp(a->left)));
		break;
	case '^' : 
		dValue =(pow(vexp(a->left),vexp(a->right)));
		break;
	case '@' : 
		dValue = (a->valoare);
		//logical operations evaluation
		break;
	case '<' :
		dValue =( vexp(a->left)<vexp(a->right) );
		break;
	case '>' : 
		dValue =( vexp(a->left)>vexp(a->right) );
		break;
	case '!' : 
		dValue =(!vexp(a->right)) ;
		break;
	default  : 
		{
			CEpExpVariable *pVar = FindVariable(*(a->valoarestr));

			if ( pVar == NULL )
			{
				g_nErrorCode = UNDEFINED_VARIABLE;
				dValue = 0;
			}
			else
			{
				dValue = pVar->m_dValue;
			}
		}
		break;
	}

	return dValue;
}


CEpExpression::PNOD CEpExpression::GetArbore()
{
	return m_pBTreeEpExpression;
}

CEpExpression::PNOD CEpExpression::CloneTree()
{
	return clone(m_pBTreeEpExpression);	
}

CEpExpression::PNOD CEpExpression::clone(PNOD arb)
{
	if (arb == NULL)
		return NULL;
	PNOD clonArb = _newnode();
	*clonArb = *arb;
	clonArb->left = clone(arb->left);
	clonArb->right = clone(arb->right);
	return clonArb;
}


void CEpExpression::SkipSpaces()
{
	char *pTemp = &m_pszEpExpression[m_nCurrPosition];

	while (*pTemp != '\0')
	{
		if (*pTemp == 32/*空格*/ 
			|| *pTemp == 9/*TAB*/
			|| *pTemp == '\r' || *pTemp == '\n')
		{
			m_nCurrPosition++;
			pTemp++;
		}
		else
		{
			break;
		}
	}

//	while (m_pszEpExpression[m_nCurrPosition]==' ' && m_pszEpExpression[m_nCurrPosition]!='\0')
//		m_nCurrPosition ++;
}


///////////////////////////////////////////////////////////////////////
// the new inserted operations
// logical operations on the first level of priority
// warning: for operations with more than one character you nedd to modify sligthly the code
// See also the new inserted operations in the vexp function


int CEpExpression::UpdateArbore()
{
	if (strlen(m_pszEpExpression) == 0)
		return 0;
	
	Delete(m_pBTreeEpExpression);
	m_pBTreeEpExpression = NULL;
	m_nCurrPosition = 0;
	m_pBTreeEpExpression = expresie();

	if (m_pszEpExpression[m_nCurrPosition]!='\0') 
	{
		Delete(m_pBTreeEpExpression);
		m_pBTreeEpExpression = NULL;
	} 
	
	if (m_pBTreeEpExpression == NULL)
	{
		return -1;
	}
	else
	{
		return m_nCurrPosition;
	}
}

CEpExpression::PNOD CEpExpression::expresie()
{
	PNOD nod;
	PNOD arb1 = termen();
	PNOD arb2;
	if  (arb1 == NULL) return NULL;  // In caz de eroare terminate
	
	while ((m_pszEpExpression[m_nCurrPosition]=='-') || (m_pszEpExpression[m_nCurrPosition]=='+') || (m_pszEpExpression[m_nCurrPosition]=='|')||
		(m_pszEpExpression[m_nCurrPosition]=='&')/*|| (m_pszEpExpression[m_nCurrPosition]=='$')*/) // mym 2021-7-17 add | 
	{
		nod = _newnode();
		nod->left = arb1;
		nod->operatie = m_pszEpExpression[m_nCurrPosition];
		m_nCurrPosition++;
		arb2 = termen();
		nod->right=arb2;
		if  (arb2 == NULL) 
		{
			Delete(nod);
			return NULL;  // In caz de eroare terminate
		}
		arb1 = nod;
	}
	return arb1;
}

CEpExpression::PNOD CEpExpression::termen()
{
	PNOD nod;
	PNOD arb1 = putere();
	PNOD arb2;
	if  (arb1 == NULL) return NULL;  // In caz de eroare terminate
	
	while ((m_pszEpExpression[m_nCurrPosition]=='*') || 
			  (m_pszEpExpression[m_nCurrPosition]=='/') ||
		      (m_pszEpExpression[m_nCurrPosition]=='%'))// mym add 2021-8-17 
	{
		nod=_newnode();
		nod->left=arb1;
		nod->operatie = m_pszEpExpression[m_nCurrPosition];
		m_nCurrPosition++;
		arb2 = putere();
		nod->right=arb2;
		if  (arb2 == NULL) 
		{
			Delete(nod);
			return NULL;  // In caz de eroare terminate
		}
		arb1 = nod;
	}
	return arb1;
}

CEpExpression::PNOD CEpExpression::putere()
{
	PNOD nod = NULL;
	PNOD arb1 = logicalOp();
	PNOD arb2;
	if  (arb1 == NULL) 
		return NULL;  // In caz de eroare terminate
	
	while (m_pszEpExpression[m_nCurrPosition]=='^') 
	{
		nod=_newnode();
		nod->left=arb1;
		nod->operatie=m_pszEpExpression[m_nCurrPosition];
		m_nCurrPosition++;
		arb2 = logicalOp();
		nod->right=arb2;
		if  (arb2 == NULL) 
		{
			Delete(nod);
			return NULL;  // In caz de eroare terminate
		}
		arb1 = nod;
	}
	return arb1;
}


CEpExpression::PNOD CEpExpression::factor()
{
	PNOD nod = NULL,nod2 = NULL,left = NULL;
	while(m_pszEpExpression[m_nCurrPosition] == ' ' && m_pszEpExpression[m_nCurrPosition] != '\0')
		m_nCurrPosition++;
	
	if (m_pszEpExpression[m_nCurrPosition]=='-')
	{
		nod = _newnode();
		left = _newnode();
		left->operatie='@';
		left->valoare=-1;
		nod->left=left;
		nod->operatie='*';
		m_nCurrPosition++;
		nod->right = expresie();
		if (nod->right == NULL)
			return NULL;
		return nod;   
	}
	if (m_pszEpExpression[m_nCurrPosition]=='(')
    {
		m_nCurrPosition++;
		nod = expresie();
		if (nod == NULL) return NULL;
		SkipSpaces();
		if (m_pszEpExpression[m_nCurrPosition]!=')')
		{
			Delete(nod);
			return NULL;
		}
		m_nCurrPosition++;
		SkipSpaces();
		return nod;
    }
	else if (m_pszEpExpression[m_nCurrPosition]=='|')
	{
		m_nCurrPosition++;
		nod2 = expresie();
		if (nod2 == NULL) return NULL;
		if (m_pszEpExpression[m_nCurrPosition]!='|')
		{
			Delete(nod);
			return NULL;
		}
		nod = _newnode();
		nod->left=nod2;
		nod->right=NULL;
		nod->operatie='|';
		m_nCurrPosition++;
		return nod;
	}
	else 
		return identificator();
	return nod;
}

BOOL CEpExpression::max_min(PNOD &oLeft,PNOD &oRight)
{
	PNOD nod = NULL,nod2 = NULL,left = NULL;
	while(m_pszEpExpression[m_nCurrPosition] == ' ' && m_pszEpExpression[m_nCurrPosition] != '\0')
		m_nCurrPosition++;

	if (m_pszEpExpression[m_nCurrPosition]!='(')
	{
		return FALSE;   
	}

	if (m_pszEpExpression[m_nCurrPosition]=='(')
	{
		m_nCurrPosition++;
		nod = expresie();

		if (nod == NULL) return FALSE;

		SkipSpaces();

		if (m_pszEpExpression[m_nCurrPosition]!=',')
		{
			Delete(nod);
			return FALSE;
		}

		m_nCurrPosition++;
		SkipSpaces();
		oLeft = nod;

		nod2 = expresie();

		if (nod2 == NULL)
		{
			Delete(nod);
			return FALSE;
		}

		SkipSpaces();

		if (m_pszEpExpression[m_nCurrPosition]!=')')
		{
			Delete(nod);
			Delete(nod2);
			return FALSE;
		}

		oRight = nod2;
		m_nCurrPosition++;
		SkipSpaces();
	}

	return TRUE;
}

//2020-08-05  lijunqing 1$Prot$LLN0....多设备数据模型的处理
void CEpExpression::identificator_var(int &poz, PNOD &nod, PNOD &nod2, PNOD &result, PNOD &pResultTemp)
{
	while (_v_isalpha_ex(m_pszEpExpression[m_nCurrPosition])) 
		m_nCurrPosition++;

	CString id("");
	GetValueFromEpExpression(id,poz,m_nCurrPosition);
	CString nid = id;
	id.MakeUpper();

	if (id =="SIN")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_SIN;
		SkipSpaces();
		pResultTemp =  nod;
	}
	else if (id =="COS")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_COS;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="EXP")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_EXP;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="SQRT")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_SQRT;
		SkipSpaces();
		pResultTemp =  nod;
	}
	else if (id =="LOG")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_LOG;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="TG")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_TG;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="CTG")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_CTG;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="ASIN")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_ASIN;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="ACOS")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_ACOS;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="ATG")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_ATG;
		SkipSpaces();
		pResultTemp = nod;
	}
	//////////////////////////////////////////////////////////////////////////
	else if (id =="SIND")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_SIND;
		SkipSpaces();
		pResultTemp =  nod;
	}
	else if (id =="COSD")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_COSD;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="TGD")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_TGD;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="CTGD")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_CTGD;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="ASIND")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_ASIND;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="ACOSD")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_ACOSD;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="ATGD")		// Functia sinus CString
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_ATGD;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="ABS")		// zhouhj20190724
	{
		nod2 = factor();
		nod = _newnode();
		nod->left = nod2;
		nod->right=NULL;
		nod->operatie=OPERATOR_ABS;
		SkipSpaces();
		pResultTemp = nod;
	}
	else if (id =="MAX")		// zhouhj20190812
	{

		if (max_min(nod,nod2))
		{
			PNOD nod3 = _newnode();
			nod3->left = nod;
			nod3->right=nod2;
			nod3->operatie=OPERATOR_MAX;
			SkipSpaces();
			pResultTemp = nod3;
		}
	}
	else if (id =="MIN")		// zhouhj20190812
	{

		if (max_min(nod,nod2))
		{
			PNOD nod3 = _newnode();
			nod3->left = nod;
			nod3->right=nod2;
			nod3->operatie=OPERATOR_MIN;
			SkipSpaces();
			pResultTemp = nod3;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	else 
	{
		nod = _newnode();
		nod -> left = NULL;
		nod -> right = NULL;
		nod -> operatie = '`';
		nod -> valoarestr = new CString(nid); 
		pResultTemp = nod;
		AddVariable(nid);
	}
}


CEpExpression::PNOD CEpExpression::identificator()
{
	int poz;
	PNOD nod = NULL,nod2 = NULL;
	PNOD result = NULL;
	//李俊庆  2004/9/28  次函数会导致内存泄露
	//因此修改
	PNOD pResultTemp = NULL;
	poz = m_nCurrPosition;
	SkipSpaces();
	if (m_pszEpExpression[m_nCurrPosition]=='\0')
		result  = NULL;
	
	if (_v_isdigit(m_pszEpExpression[m_nCurrPosition]))	// Este numar ?
	{
		while ((_v_isdigit(m_pszEpExpression[m_nCurrPosition]) || (m_pszEpExpression[m_nCurrPosition]=='.')))
			m_nCurrPosition++;

		if (m_pszEpExpression[m_nCurrPosition] == '$')
		{
			identificator_var(poz, nod, nod2, result, pResultTemp);
		}
		else
		{
			nod = _newnode();
			nod->left = NULL; 
			nod->right = NULL;
			nod->operatie = '@';
			GetValueFromEpExpression(nod->valoare, poz, m_nCurrPosition);
			result = nod;
		}
	}

	if (_v_isalpha(m_pszEpExpression[m_nCurrPosition]))	// Am i an identifier ?
	{
		identificator_var(poz, nod, nod2, result, pResultTemp);
	}

	//李俊庆  2004/9/28
	if (pResultTemp != NULL)
	{
		Delete(result);
		result = pResultTemp;
	}

	SkipSpaces();

	return result;        
}

CEpExpression::PNOD CEpExpression::logicalOp()
{
	PNOD nod;
	PNOD arb1 = sgOp();
	PNOD arb2;
	if  (arb1 == NULL) return NULL;  // In caz de eroare terminate

	while ((m_pszEpExpression[m_nCurrPosition]=='<') || (m_pszEpExpression[m_nCurrPosition]=='>') /* || another same priority operations*/) 
	{
		nod=_newnode();
		nod->left=arb1;
		nod->operatie=m_pszEpExpression[m_nCurrPosition];
		m_nCurrPosition++;
		arb2 = sgOp();
		nod->right=arb2;
		if  (arb2 == NULL) 
		{
			Delete(nod);
			return NULL;  // In caz de eroare terminate
		}

		arb1 = nod;
	}
	return arb1;
}


CEpExpression::PNOD CEpExpression::sgOp()
{
	PNOD nod = NULL;
	PNOD arb2;
	if ((m_pszEpExpression[m_nCurrPosition] == '!') /* || another same priority operations*/) 
	{
		nod=_newnode();
		nod->left=NULL;
		nod->operatie = m_pszEpExpression[m_nCurrPosition];
		m_nCurrPosition++;
		arb2 = sgOp();
		nod->right=arb2;
		if  (arb2 == NULL) 
		{
			Delete(nod);
			return NULL;  // In caz de eroare terminate
		}
	}
	else 
	{
		nod = factor();
	}
	return nod;
}

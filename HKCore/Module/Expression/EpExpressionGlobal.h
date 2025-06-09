// EpExpressionGlobal.h : main header file for the FUNCTION application
//
#if !defined(_EpExpressionGlobal_GLOBAL_H__)
#define _EpExpressionGlobal_GLOBAL_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../BaseClass/TLinkList.h"
#include "../API/StringApi.h"

// Tree evaluation variables

#define DIVISION_BY_0 1
#define ILEGAL_OPERATION 2
#define UNDEFINED_VARIABLE 3
#define INVALID_DOMAIN 4

#define OPERATOR_ADD	1  //  +
#define OPERATOR_SUB	2  //  -
#define OPERATOR_MUL	3  //   *
#define OPERATOR_DIV	4  //   /
#define OPERATOR_REM	5  //  %   remainder
#define OPERATOR_GT		6  //  >  greater than
#define OPERATOR_GTE	7  //  >=  greater or equal to
#define OPERATOR_LT	    8  //  < less than
#define OPERATOR_LTE	9    //  < less or equal to
#define OPERATOR_AND	10  //  &&
#define OPERATOR_OR	    11  // || 
#define OPERATOR_NOT	 12  // !
#define OPERATOR_POW	 13  //^


#define OPERATOR_SIN	150
#define OPERATOR_COS	151
#define OPERATOR_EXP	152
#define OPERATOR_SQRT	153
#define OPERATOR_LOG	154
#define OPERATOR_TG		155
#define OPERATOR_CTG	156
#define OPERATOR_ASIN	157
#define OPERATOR_ACOS	158
#define OPERATOR_ATG	159

#define OPERATOR_NOTMORE	160	//is less than or equal to 小于或等于号
#define OPERATOR_NOTLESS	161	//is more than or equal to 大于或等于号

#define OPERATOR_SIND	162
#define OPERATOR_COSD	163
#define OPERATOR_TGD	164
#define OPERATOR_CTGD	165
#define OPERATOR_ASIND	166
#define OPERATOR_ACOSD	167
#define OPERATOR_ATGD	168

#define OPERATOR_ABS	169  //zhouhj20190724
#define OPERATOR_MAX	170  //zhouhj20190812
#define OPERATOR_MIN	171  //zhouhj20190812

#endif // !defined(_EpExpressionGlobal_GLOBAL_H__)

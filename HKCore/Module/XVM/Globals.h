
#if !defined(_GLOBALS_H__)
#define _GLOBALS_H__

#include "TAsmGlobal.h"
#include "stdio.h"
#include "string.h"

// ---- Program ---------------------------------------------------------------------------
//#define VERSION_MAJOR               0           // Major version number
//#define VERSION_MINOR               8           // Minor version number
// ---- Filename --------------------------------------------------------------------------

#define MAX_FILENAME_SIZE           2048        // Maximum filename length

static const char* FILE_EXT_TSS          = ".tss";      // Extension of a source code file

// ---- Source Code -----------------------------------------------------------------------

#define MAX_SOURCE_LINE_SIZE        4096        // Maximum source line length

#define MAX_IDENT_SIZE              256        // Maximum identifier size

/*
// ---- Priority Types --------------------------------------------------------------------

#define PRIORITY_USER               1           // User-defined priority
#define PRIORITY_LOW                2           // Low priority
#define PRIORITY_MED                3           // Medium priority
#define PRIORITY_HIGH               4           // High priority

static const char* PRIORITY_LOW_KEYWORD        = "Low";       // Low priority keyword
static const char* PRIORITY_MED_KEYWORD        = "Med";       // Low priority keyword
static const char* PRIORITY_HIGH_KEYWORD       = "High";      // Low priority keyword
*/

// ---- Functions -------------------------------------------------------------------------
//static const char* MAIN_FUNC_NAME              = "_Main";        // _Main ()'s name

// ---- Register Codes---------------------------------------------------------------------
#define REG_CODE_RETVAL             0           // _RetVal

// ---- Internal Script Entities ----------------------------------------------------------
static const char* TEMP_VAR_0                  = "_T0";       // Temporary variable 0
static const char* TEMP_VAR_1                  = "_T1";       // Temporary variable 1
static const char* TEMP_VAR_2                  = "_T2";       // Temporary variable 2

// ---- Constants -----------------------------------------------------------------------------

// ---- I-Code Node Types -----------------------------------------------------------------

#define ICODE_NODE_NONE            -1             
#define ICODE_NODE_INSTR           0               // An I-code instruction
#define ICODE_NODE_SOURCE_LINE     1               // Source-code annotation
#define ICODE_NODE_JUMP_TARGET     2               // A jump target

/*
// ---- I-Code Instruction Opcodes --------------------------------------------------------

// ---- Instruction Opcodes -----------------------------------------------------------
#define INSTRUCT_MOV               0
#define INSTRUCT_ADD               1
#define INSTRUCT_SUB               2
#define INSTRUCT_MUL               3
#define INSTRUCT_DIV               4
#define INSTRUCT_MOD               5
#define INSTRUCT_EXP               6
#define INSTRUCT_NEG               7
#define INSTRUCT_INC               8
#define INSTRUCT_DEC               9

#define INSTRUCT_AND               10
#define INSTRUCT_OR                11
#define INSTRUCT_XOR               12
#define INSTRUCT_NOT               13
#define INSTRUCT_SHL               14
#define INSTRUCT_SHR               15

#define INSTRUCT_CONCAT            16
#define INSTRUCT_GETCHAR           17
#define INSTRUCT_SETCHAR           18

#define INSTRUCT_JMP               19
#define INSTRUCT_JE                20
#define INSTRUCT_JNE               21
#define INSTRUCT_JG                22
#define INSTRUCT_JL                23
#define INSTRUCT_JGE               24
#define INSTRUCT_JLE               25

#define INSTRUCT_PUSH              26
#define INSTRUCT_POP               27

#define INSTRUCT_CALL              28
#define INSTRUCT_RET               29
#define INSTRUCT_CALLHOST          30

#define INSTRUCT_PAUSE             31
#define INSTRUCT_EXIT              32

//math instruct 
#define INSTRUCT_ABS                   33     //abs    dest, s1
#define INSTRUCT_POW                   34     //pow    dest, s1, s2
#define INSTRUCT_SQRT                  35     //sqrt   dest, s1
#define INSTRUCT_LOG10                 36     //log10  dest, s1
#define INSTRUCT_LOG                   37     //log    dest, s1
#define INSTRUCT_SIN                   38     //sin    dest, s1
#define INSTRUCT_COS                   39     //cos    dest, s1
#define INSTRUCT_TAN                   40     //tan    dest, s1
#define INSTRUCT_CTAN                  41     //ctan   dest, s1
#define INSTRUCT_ASIN                  42     //sain   dest, s1
#define INSTRUCT_ACOS                  43     //acos   dest, s1
#define INSTRUCT_ATAN                  44     //atan   dest, s1
#define INSTRUCT_ATAN2                 45     //atan2  dest, s1, s2
#define INSTRUCT_MIN                   46     //min    dest, s1, s2
#define INSTRUCT_MAX                   47     //max    dest, s1, s2
#define INSTRUCT_CEIL                  48     //ceil   dest, s1
#define INSTRUCT_FLOOR                 49     //floor  dest, s1
#define INSTRUCT_HYPOT                 50     //hypot  dest, s1, s2
#define INSTRUCT_FMOD                  51     //fmod   dest, s1, s2
#define INSTRUCT_DIGIT                 52     //digit  dest, s1, s2
#define INSTRUCT_BINARY                53     //binary dest, s1, s2
#define INSTRUCT_ATOF                  54     //atof   dest, s1
#define INSTRUCT_ATOL                  55     //atol   dest, s1
#define INSTRUCT_FTOA                  56     //ftoa   dest, s1
#define INSTRUCT_LTOA                  57     //ltoa   dest, s1
#define INSTRUCT_CMP                   58     //cmp    dest, s1, s2
#define INSTRUCT_CMPE                  59     //cmpe   dest, s1, s2
#define INSTRUCT_CMPNE                 60     //cmpne  dest, s1, s2
#define INSTRUCT_CMPG                  61     //cmpg   dest, s1, s2
#define INSTRUCT_CMPL                  62     //cmpl   dest, s1, s2
#define INSTRUCT_CMPGE                 63     //cmpge  dest, s1, s2
#define INSTRUCT_CMPLE                 64     //cmple  dest, s1, s2

// ---- Operand Types ---------------------------------------------------------------------

#define OPERAND_TYPE_INT                 0           // Integer literal value
#define OPERAND_TYPE_FLOAT               1           // Floating-point literal value
#define OPERAND_TYPE_STRING_INDEX        2           // String literal value
#define OPERAND_TYPE_VAR                 3           // Variable
#define OPERAND_TYPE_REG                 9           // Register
*/

#define OPERAND_TYPE_VAR                 9           // Variable
#define OPERAND_TYPE_ARRAY_INDEX_ABS     10           // Array with absolute index
#define OPERAND_TYPE_ARRAY_INDEX_VAR     11           // Array with relative index
#define OPERAND_TYPE_JUMP_TARGET_INDEX   12           // Jump target index



///////////////////////////////////////////////////////////////////////////////////////////////
// ---- Constants -----------------------------------------------------------------------------


// ---- Operators -------------------------------------------------------------------------
#define MAX_OP_STATE_COUNT              32      // Maximum number of operator states

// ---- Delimiters ------------------------------------------------------------------------
#define MAX_DELIM_COUNT                 24      // Maximum number of delimiters

// ---- Lexer States ----------------------------------------------------------------------
#define LEX_STATE_UNKNOWN               0       // Unknown lexeme type
#define LEX_STATE_START                 1       // Start state
#define LEX_STATE_INT                   2       // Integer
#define LEX_STATE_FLOAT                 3       // Float
#define LEX_STATE_IDENT                 4       // Identifier
#define LEX_STATE_OP                    5       // Operator
#define LEX_STATE_DELIM                 6       // Delimiter    
#define LEX_STATE_STRING                7       // String value
#define LEX_STATE_STRING_ESCAPE         8       // Escape sequence
#define LEX_STATE_STRING_CLOSE_QUOTE    9       // String closing quote

// ---- Token Types -----------------------------------------------------------------------
#define TOKEN_TYPE_END_OF_STREAM        0       // End of the token stream
#define TOKEN_TYPE_INVALID              1       // Invalid token

#define TOKEN_TYPE_INT                  2       // Integer
#define TOKEN_TYPE_FLOAT                3       // Float

#define TOKEN_TYPE_IDENT                4       // Identifier

#define TOKEN_TYPE_RSRVD_VAR            5       // var/var []
#define TOKEN_TYPE_RSRVD_TRUE           6       // true
#define TOKEN_TYPE_RSRVD_FALSE          7       // false
#define TOKEN_TYPE_RSRVD_IF             8       // if
#define TOKEN_TYPE_RSRVD_ELSE           9       // else
#define TOKEN_TYPE_RSRVD_BREAK          10      // break
#define TOKEN_TYPE_RSRVD_CONTINUE       11      // continue
#define TOKEN_TYPE_RSRVD_FOR            12      // for
#define TOKEN_TYPE_RSRVD_WHILE          13      // while
#define TOKEN_TYPE_RSRVD_FUNC           14      // func
#define TOKEN_TYPE_RSRVD_RETURN         15      // return
#define TOKEN_TYPE_RSRVD_HOST           16      // host

#define TOKEN_TYPE_OP                   18      // Operator

#define TOKEN_TYPE_DELIM_COMMA          19      // ,
#define TOKEN_TYPE_DELIM_OPEN_PAREN     20      // (
#define TOKEN_TYPE_DELIM_CLOSE_PAREN    21      // )
#define TOKEN_TYPE_DELIM_OPEN_BRACE     22      // [
#define TOKEN_TYPE_DELIM_CLOSE_BRACE    23      // ]
#define TOKEN_TYPE_DELIM_OPEN_CURLY_BRACE   24  // {
#define TOKEN_TYPE_DELIM_CLOSE_CURLY_BRACE  25  // }
#define TOKEN_TYPE_DELIM_SEMICOLON      26      // ;

#define TOKEN_TYPE_STRING               27      // String

//保留关键字－数学函数
#define TOKEN_TYPE_RSRVD_FUNC_ABS            28      //abs
#define TOKEN_TYPE_RSRVD_FUNC_POW            29      //pow
#define TOKEN_TYPE_RSRVD_FUNC_SQRT           30      //sqrt
#define TOKEN_TYPE_RSRVD_FUNC_LOG10          31      //log10
#define TOKEN_TYPE_RSRVD_FUNC_LOG            32      //log
#define TOKEN_TYPE_RSRVD_FUNC_SIN            33      //sin
#define TOKEN_TYPE_RSRVD_FUNC_COS            34      //cos
#define TOKEN_TYPE_RSRVD_FUNC_TAN            35      //tan
#define TOKEN_TYPE_RSRVD_FUNC_CTAN           36      //ctan
#define TOKEN_TYPE_RSRVD_FUNC_ASIN           37      //asin
#define TOKEN_TYPE_RSRVD_FUNC_ACOS           38      //acos
#define TOKEN_TYPE_RSRVD_FUNC_ATAN           39      //atan
#define TOKEN_TYPE_RSRVD_FUNC_ATAN2          40      //atan2
#define TOKEN_TYPE_RSRVD_FUNC_MIN            41      //min
#define TOKEN_TYPE_RSRVD_FUNC_MAX            42      //max
#define TOKEN_TYPE_RSRVD_FUNC_CEIL           43      //ceil
#define TOKEN_TYPE_RSRVD_FUNC_FLOOR          44      //floor
#define TOKEN_TYPE_RSRVD_FUNC_HYPOT          45      //hypot
#define TOKEN_TYPE_RSRVD_FUNC_FMOD           46      //fmod
#define TOKEN_TYPE_RSRVD_FUNC_DIGIT          47      //digit
#define TOKEN_TYPE_RSRVD_FUNC_BINARY         48      //binary
#define TOKEN_TYPE_RSRVD_FUNC_ATOF           49      //atof
#define TOKEN_TYPE_RSRVD_FUNC_ATOL           50      //atol
#define TOKEN_TYPE_RSRVD_FUNC_FTOA           51      //ftoa
#define TOKEN_TYPE_RSRVD_FUNC_LTOA           52      //ltoa

#define TOKEN_TYPE_RSRVD_EXPORT              53      //export

//
#define TOKEN_TYPE_RSRVD_LONG                54      //long    var/var []
#define TOKEN_TYPE_RSRVD_STRING              55      //string
#define TOKEN_TYPE_RSRVD_FLOAT               56      //float

// ---- Operators -------------------------------------------------------------------------
// ---- Arithmetic
#define OP_TYPE_ADD                     0       // +
#define OP_TYPE_SUB                     1       // -
#define OP_TYPE_MUL                     2       // *
#define OP_TYPE_DIV                     3       // /
#define OP_TYPE_MOD                     4       // %
#define OP_TYPE_EXP                     5       // ^
#define OP_TYPE_CONCAT                  35       // $

#define OP_TYPE_INC                     15      // ++
#define OP_TYPE_DEC                     17      // --

#define OP_TYPE_ASSIGN_ADD              14      // +=
#define OP_TYPE_ASSIGN_SUB              16      // -=
#define OP_TYPE_ASSIGN_MUL              18      // *=
#define OP_TYPE_ASSIGN_DIV              19      // /=
#define OP_TYPE_ASSIGN_MOD              20      // %=
#define OP_TYPE_ASSIGN_EXP              21      // ^=
#define OP_TYPE_ASSIGN_CONCAT           36      // $=

// ---- Bitwise
#define OP_TYPE_BITWISE_AND             6       // &
#define OP_TYPE_BITWISE_OR              7       // |
#define OP_TYPE_BITWISE_XOR             8       // #
#define OP_TYPE_BITWISE_NOT             9       // ~
#define OP_TYPE_BITWISE_SHIFT_LEFT      30      // <<
#define OP_TYPE_BITWISE_SHIFT_RIGHT     32      // >>

#define OP_TYPE_ASSIGN_AND              22      // &=
#define OP_TYPE_ASSIGN_OR               24      // |=
#define OP_TYPE_ASSIGN_XOR              26      // #=
#define OP_TYPE_ASSIGN_SHIFT_LEFT       33      // <<=
#define OP_TYPE_ASSIGN_SHIFT_RIGHT      34      // >>=

// ---- Logical
#define OP_TYPE_LOGICAL_AND             23      // &&
#define OP_TYPE_LOGICAL_OR              25      // ||
#define OP_TYPE_LOGICAL_NOT             10      // !

// ---- Relational
#define OP_TYPE_EQUAL                   28      // ==
#define OP_TYPE_NOT_EQUAL               27      // !=
#define OP_TYPE_LESS                    12      // <
#define OP_TYPE_GREATER                 13      // >
#define OP_TYPE_LESS_EQUAL              29      // <=
#define OP_TYPE_GREATER_EQUAL           31      // >=

// ---- Assignment
#define OP_TYPE_ASSIGN                  11      // =


//define script keys
static const char*  g_pstrScriptKey_var       = "var";
static const char*  g_pstrScriptKey_long      = "long";
static const char*  g_pstrScriptKey_string    = "string";
static const char*  g_pstrScriptKey_float     = "float";
static const char*  g_pstrScriptKey_export    = "export";
static const char*  g_pstrScriptKey_true      = "true";
static const char*  g_pstrScriptKey_false     = "false";
static const char*  g_pstrScriptKey_if        = "if";
static const char*  g_pstrScriptKey_else      = "else";
static const char*  g_pstrScriptKey_break     = "break";
static const char*  g_pstrScriptKey_continue  = "continue";
static const char*  g_pstrScriptKey_for       = "for";
static const char*  g_pstrScriptKey_while     = "while";
static const char*  g_pstrScriptKey_func      = "func";
static const char*  g_pstrScriptKey_return    = "return";
static const char*  g_pstrScriptKey_host      = "host";

static const char*  g_pstrScriptKey_Func_ABS             = "abs";
static const char*  g_pstrScriptKey_Func_POW             = "pow";
static const char*  g_pstrScriptKey_Func_SQRT            = "sqrt";
static const char*  g_pstrScriptKey_Func_LOG10           = "log10";
static const char*  g_pstrScriptKey_Func_LOG             = "log";
static const char*  g_pstrScriptKey_Func_SIN             = "sin";
static const char*  g_pstrScriptKey_Func_COS             = "cos";
static const char*  g_pstrScriptKey_Func_TAN             = "tan";
static const char*  g_pstrScriptKey_Func_CTAN            = "ctan";
static const char*  g_pstrScriptKey_Func_ASIN            = "asin";
static const char*  g_pstrScriptKey_Func_ACOS            = "acos";
static const char*  g_pstrScriptKey_Func_ATAN            = "atan";
static const char*  g_pstrScriptKey_Func_ATAN2           = "atan2";
static const char*  g_pstrScriptKey_Func_MIN             = "min";
static const char*  g_pstrScriptKey_Func_MAX             = "max";
static const char*  g_pstrScriptKey_Func_CEIL            = "ceil";
static const char*  g_pstrScriptKey_Func_FLOOR           = "floor";
static const char*  g_pstrScriptKey_Func_HYPOT           = "hypot";
static const char*  g_pstrScriptKey_Func_FMOD            = "fmod";
static const char*  g_pstrScriptKey_Func_DIGIT           = "digit";
static const char*  g_pstrScriptKey_Func_BINARY          = "binary";
static const char*  g_pstrScriptKey_Func_ATOF            = "atof";
static const char*  g_pstrScriptKey_Func_ATOL            = "atol";
static const char*  g_pstrScriptKey_Func_FTOA            = "ftoa";
static const char*  g_pstrScriptKey_Func_LTOA            = "ltoa";

#define MAX_FUNC_DECLARE_PARAM_COUNT        32      // The maximum number of parameters

// ---- Error Strings ---------------------------------------------------------------------
// The following macros are used to represent assembly-time error strings

static const char*  ERROR_MSG_UNEXPECTED_END_OF_FILE   = "Unexpected end of file";
static const char*  ERROR_MSG_INVALID_IDENTIFIER       = "Invalid identifier \"%s\" ";
static const char*  ERROR_MSG_UNEXPECTED_INPUT         = "Unexpected input";
static const char*  ERROR_MSG_CODE_IN_GLOBAL           = "Code blocks illegal in global scope";
static const char*  ERROR_MSG_IDENTIFIER_REDEFINE      = "Identifier \"%s\" redefinition";
static const char*  ERROR_MSG_FUNC_REDEFINE            = "Function \"%s\" redefinition";
static const char*  ERROR_MSG_FUNC_REDEFINE_HOST       = "Function name \"%s\" used by host api ";
static const char*  ERROR_MSG_NESTED_FUNCTIONS         = "Nested functions illegal";
static const char*  ERROR_MSG_MAIN_ACCEPT_PARA         = "_Main () cannot accept parameters";
static const char*  ERROR_MSG_INVALID_ARRAY            = "Invalid array";
static const char*  ERROR_MSG_INVALID_EXPRESSION       = "invalid expression";
static const char*  ERROR_MSG_ARRAY_MUST_BE_INDEXED    = "Arrays must be indexed";
static const char*  ERROR_MSG_INVALID_INPUT            = "Invalid input";
static const char*  ERROR_MSG_IF_IN_GLOBAL             = "if illegal in global scope";
static const char*  ERROR_MSG_STATEMENT_IN_GLOBAL      = "Statement illegal in global scope";
static const char*  ERROR_MSG_FOR_IN_GLOBAL            = "for illegal in global scope";
static const char*  ERROR_MSG_BREAK_OUTSIDE_LOOP       = "break illegal outside loops";
static const char*  ERROR_MSG_CONTINUE_OUTSIDE_LOOP    = "continue illegal outside loops";
static const char*  ERROR_MSG_RETURN_IN_GLOBAL         = "return illegal in global scope";
static const char*  ERROR_MSG_ASSIGNMENT_IN_GLOBAL     = "Assignment illegal in global scope";
static const char*  ERROR_MSG_ILLEGAL_ASSIGNMENT_OPTR  = "Illegal assignment operator";
static const char*  ERROR_MSG_TOO_MANY_PARAMETERS      = "Too many parameters";
static const char*  ERROR_MSG_MATH_FUNC_IN_GLOBAL      = "Math function call illegal in global scope";
static const char*  ERROR_MSG_EXPORT_IN_FUNC           = "can not export a local variable in function";
static const char*  ERROR_MSG_CANNT_EXPORT_ARRAY	   = "Can not export array";


static int g_iCurrJumpTargetIndex;
inline int GetNextJumpTargetIndex ()
{
	// Return and increment the current target index
	return g_iCurrJumpTargetIndex ++;
}

inline unsigned int TOKEN_TYPE_RSRVD_FUNC_to_INSTRUCT(unsigned int nTokenType)
{
	return nTokenType - TOKEN_TYPE_RSRVD_FUNC_ABS + INSTRUCT_ABS;
/*
	switch(nTokenType)
	{
	case TOKEN_TYPE_RSRVD_FUNC_ABS:
		return INSTRUCT_ABS;
	case TOKEN_TYPE_RSRVD_FUNC_SQRT:
		return INSTRUCT_SQRT;
	case TOKEN_TYPE_RSRVD_FUNC_LOG10:
		return INSTRUCT_LOG10;
	case TOKEN_TYPE_RSRVD_FUNC_LOG:
		return INSTRUCT_LOG;
	case TOKEN_TYPE_RSRVD_FUNC_SIN:
		return INSTRUCT_SIN;
	case TOKEN_TYPE_RSRVD_FUNC_COS:
		return INSTRUCT_COS;
	case TOKEN_TYPE_RSRVD_FUNC_TAN:
		return INSTRUCT_TAN;
	case TOKEN_TYPE_RSRVD_FUNC_CTAN:
		return INSTRUCT_CTAN;
	case TOKEN_TYPE_RSRVD_FUNC_ASIN:
		return INSTRUCT_ASIN;
	case TOKEN_TYPE_RSRVD_FUNC_ACOS:
		return INSTRUCT_ACOS;
	case TOKEN_TYPE_RSRVD_FUNC_ATAN:
		return INSTRUCT_ATAN;
	case TOKEN_TYPE_RSRVD_FUNC_CEIL:
		return INSTRUCT_CEIL;
	case TOKEN_TYPE_RSRVD_FUNC_FLOOR:
		return INSTRUCT_FLOOR;
	case TOKEN_TYPE_RSRVD_FUNC_ATOF:
		return INSTRUCT_ATOF;
	case TOKEN_TYPE_RSRVD_FUNC_ATOL:
		return INSTRUCT_ATOL;
	case TOKEN_TYPE_RSRVD_FUNC_FTOA:
		return INSTRUCT_FTOA;
	case TOKEN_TYPE_RSRVD_FUNC_LTOA:
		return INSTRUCT_LTOA;
	case TOKEN_TYPE_RSRVD_FUNC_POW:
		return INSTRUCT_POW;
	case TOKEN_TYPE_RSRVD_FUNC_ATAN2:
		return INSTRUCT_ATAN2;
	case TOKEN_TYPE_RSRVD_FUNC_MIN:
		return INSTRUCT_MIN;
	case TOKEN_TYPE_RSRVD_FUNC_MAX:
		return INSTRUCT_MAX;
	case TOKEN_TYPE_RSRVD_FUNC_HYPOT:
		return INSTRUCT_HYPOT;
	case TOKEN_TYPE_RSRVD_FUNC_FMOD:
		return INSTRUCT_FMOD;
	case TOKEN_TYPE_RSRVD_FUNC_DIGIT:
		return INSTRUCT_DIGIT;
	case TOKEN_TYPE_RSRVD_FUNC_BINARY:
		return INSTRUCT_BINARY;		
	default:
		return INSTRUCT_ABS;
		break;
	}
*/
}

#endif // !defined(_GLOBALS_H__)

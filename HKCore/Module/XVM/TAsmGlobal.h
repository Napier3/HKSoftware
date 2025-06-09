#ifndef _TASMGLOBALS_H__
#define _TASMGLOBALS_H__

// ---- Filename --------------------------------------------------------------------------
#define MAX_FILENAME_SIZE           2048        // Maximum filename length
static const char* FILE_EXT_TASM    = ".TASM";     // Extension of a source code file
static const char* FILE_EXT_TSE     = ".TSE";      // Extension of an executable code file

// ---- Lexemes ---------------------------------------------------------------------------
#define MAX_LEXEME_SIZE                 1024    // Maximum individual lexeme size

// ---- Source Code -----------------------------------------------------------------------
#define MAX_SOURCE_CODE_SIZE        65536       // Maximum number of lines in source
// code
#define MAX_SOURCE_LINE_SIZE        4096        // Maximum source line length

// ---- ,TSE Header -----------------------------------------------------------------------
static const char* TSE_ID_STRING               = "TSE0";      // Written to the file to state it's
#define TSE_ID_STRING_LEN                      4

// validity
#define VERSION_MAJOR               1           // Major version number
#define VERSION_MINOR               0           // Minor version number

// reached
#define MAX_IDENT_SIZE              256        // Maximum identifier size

// ---- Instruction Lookup Table ----------------------------------------------------------
#define MAX_INSTRUCT_LOOKUP_COUNT      256         // The maximum number of instructions
// the lookup table will hold
#define MAX_INSTRUCT_MNEMONIC_SIZE     16          // Maximum size of an instruction
// mnemonic's string


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
#define INSTRUCT_ABS               33
#define INSTRUCT_POW               34
#define INSTRUCT_SQRT              35
#define INSTRUCT_LOG10             36
#define INSTRUCT_LOG               37
#define INSTRUCT_SIN               38
#define INSTRUCT_COS               39
#define INSTRUCT_TAN               40
#define INSTRUCT_CTAN              41
#define INSTRUCT_ASIN              42
#define INSTRUCT_ACOS              43
#define INSTRUCT_ATAN              44
#define INSTRUCT_ATAN2             45
#define INSTRUCT_MIN               46
#define INSTRUCT_MAX               47
#define INSTRUCT_CEIL              48
#define INSTRUCT_FLOOR             49
#define INSTRUCT_HYPOT             50
#define INSTRUCT_FMOD              51
#define INSTRUCT_DIGIT             52
#define INSTRUCT_BINARY            53
#define INSTRUCT_ATOF              54
#define INSTRUCT_ATOL              55
#define INSTRUCT_FTOA              56
#define INSTRUCT_LTOA              57
#define INSTRUCT_CMP               58
#define INSTRUCT_CMPE              59
#define INSTRUCT_CMPNE             60
#define INSTRUCT_CMPG              61
#define INSTRUCT_CMPL              62
#define INSTRUCT_CMPGE             63
#define INSTRUCT_CMPLE             64


// ---- Operand Type Bitfield Flags ---------------------------------------------------

// The following constants are used as flags into an operand type bit field, hence
// their values being increasing powers of 2.
#define OPERAND_FLAG_TYPE_INT            0X0001       // Integer literal value
#define OPERAND_FLAG_TYPE_FLOAT          0X0002       // Floating-point literal value
#define OPERAND_FLAG_TYPE_STRING         0X0004       // Integer literal value
#define OPERAND_FLAG_TYPE_MEM_REF        0X0008       // Memory reference (variable or array
// index, both absolute and relative)
#define OPERAND_FLAG_TYPE_LINE_LABEL     0X0010      // Line label (used for jumps)
#define OPERAND_FLAG_TYPE_FUNC_NAME      0X0020      // Function table index (used for Call)
#define OPERAND_FLAG_TYPE_HOST_API_CALL  0X0040      // Host API Call table index (used for
// CallHost)
#define OPERAND_FLAG_TYPE_REG            0X0080     // Register


// ---- Assembled Instruction Stream ------------------------------------------------------
#define OPERAND_TYPE_NULL                -1          // Uninitialized/Null data
#define OPERAND_TYPE_INT                 0           // Integer literal value
#define OPERAND_TYPE_FLOAT               1           // Floating-point literal value
#define OPERAND_TYPE_STRING_INDEX        2           // String literal value
#define OPERAND_TYPE_STRING        2 
#define OPERAND_TYPE_ABS_STACK_INDEX     3           // Absolute array index
#define OPERAND_TYPE_REL_STACK_INDEX     4           // Relative array index
#define OPERAND_TYPE_INSTRUCT_INDEX      5           // Instruction index
#define OPERAND_TYPE_FUNC_INDEX          6           // Function index
#define OPERAND_TYPE_HOST_API_CALL_INDEX 7           // Host API call index
#define OPERAND_TYPE_REG                 8           // Register

#define OPERAND_TYPE_STACK_BASE_MARKER   9           // Marks a stack base

// ---- Priority Types --------------------------------------------------------------------

#define PRIORITY_NONE                    0           // A priority wasn't specified
#define PRIORITY_USER                    1           // User-defined priority
#define PRIORITY_LOW                     2           // Low priority
#define PRIORITY_MED                     3           // Medium priority
#define PRIORITY_HIGH                    4           // High priority

static const char* PRIORITY_LOW_KEYWORD       = "low";      // Low priority keyword
static const char* PRIORITY_MED_KEYWORD       = "med";      // Low priority keyword
static const char* PRIORITY_HIGH_KEYWORD      = "high";     // Low priority keyword

// ---- Functions -------------------------------------------------------------------------
static const char* MAIN_FUNC_NAME                     = "_main";     // _Main ()'s name

typedef int Token;                              // Tokenizer alias type

// ---- Instruction Lookup Table ----------------------------------------------------------
typedef int OperandTypes;                            // Operand type bitfield alias type

// ---- Keys -----------------------------------------------------------------------
static const char*  KEY_SETSTACKSIZE               = "setstacksize";
static const char*  KEY_SETPRIORITY                = "setpriority";
static const char*  KEY_VAR	                       = "var";
static const char*  KEY_FUNC	                   = "func";
static const char*  KEY_PARAM                      = "param";
static const char*  KEY__RETVAL	                   = "_retval";
static const char   KEY_OPEN_BRACE                 = '{';
static const char   KEY_CLOSE_BRACE                = '}';
static const char*  KEY_EXPORT	                   = "export";  //export variables

#define MENBUFFERLENEX  1024



#endif //_TASMGLOBALS_H__


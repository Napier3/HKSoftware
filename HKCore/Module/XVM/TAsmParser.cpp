// TAsm.cpp: implementation of the CTAsmParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TAsmParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

long CTAsmInstructs::m_nRefCount = 0;
CTAsmInstructs* CTAsmInstructs::g_pAsmInstructs = NULL;

CTAsmInstructs::CTAsmInstructs()
{
	InitInstructTable();
}

CTAsmInstructs:: ~CTAsmInstructs()
{

}

void CTAsmInstructs::Release()
{
	m_nRefCount--;

	if (m_nRefCount == 0)
	{
		delete g_pAsmInstructs;
		g_pAsmInstructs = NULL;
	}
}

void CTAsmInstructs::InitInstructTable()
{
	int iInstrIndex = 0;
	CTInstruct* p = NULL;
	
	// Mov          Destination, Source
	p = AddInstructLookup ( "mov", INSTRUCT_MOV, 2 );
	p->SetOpType( 0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// Add         Destination, Source
	p = AddInstructLookup ( "add", INSTRUCT_ADD, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// Sub          Destination, Source
	p = AddInstructLookup ( "sub", INSTRUCT_SUB, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// Mul          Destination, Source
	p = AddInstructLookup ( "mul", INSTRUCT_MUL, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// Div          Destination, Source
	p = AddInstructLookup ( "div", INSTRUCT_DIV, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// Mod          Destination, Source
	p = AddInstructLookup ( "mod", INSTRUCT_MOD, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// Exp          Destination, Source
	p = AddInstructLookup ( "exp", INSTRUCT_EXP, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// Neg          Destination
	p = AddInstructLookup ( "neg", INSTRUCT_NEG, 1 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// Inc          Destination
	p = AddInstructLookup ( "inc", INSTRUCT_INC, 1 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// Dec          Destination
	p = AddInstructLookup ( "Dec", INSTRUCT_DEC, 1 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// ---- Bitwise
	// And          Destination, Source
	p = AddInstructLookup ( "and", INSTRUCT_AND, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// Or           Destination, Source
	p = AddInstructLookup ( "or", INSTRUCT_OR, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// XOr          Destination, Source
	p = AddInstructLookup ( "xor", INSTRUCT_XOR, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// Not          Destination
	p = AddInstructLookup ( "not", INSTRUCT_NOT, 1 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// ShL          Destination, Source
	p = AddInstructLookup ( "shl", INSTRUCT_SHL, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// ShR          Destination, Source
	p = AddInstructLookup ( "shr", INSTRUCT_SHR, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// ---- String Manipulation
	// Concat       String0, String1
	p = AddInstructLookup ( "concat", INSTRUCT_CONCAT, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING );
	
	// GetChar      Destination, Source, Index
	p = AddInstructLookup ( "getchar", INSTRUCT_GETCHAR, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING );
	p->SetOpType (2, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_INT );
	
	// SetChar      Destination, Index, Source
	p = AddInstructLookup ( "setchar", INSTRUCT_SETCHAR, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_INT );
	p->SetOpType (2, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING );
	
	// ---- Conditional Branching
	// Jmp          Label
	p = AddInstructLookup ( "jmp", INSTRUCT_JMP, 1 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_LINE_LABEL );
	
	// JE           Op0, Op1, Label
	p = AddInstructLookup ( "je", INSTRUCT_JE, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_LINE_LABEL );
	
	// JNE          Op0, Op1, Label
	p = AddInstructLookup ( "jne", INSTRUCT_JNE, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_LINE_LABEL );
	
	// JG           Op0, Op1, Label
	p = AddInstructLookup ( "jg", INSTRUCT_JG, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_LINE_LABEL );
	
	// JL           Op0, Op1, Label
	p = AddInstructLookup ( "jl", INSTRUCT_JL, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_LINE_LABEL );
	
	// JGE          Op0, Op1, Label
	p = AddInstructLookup ( "jge", INSTRUCT_JGE, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_LINE_LABEL );
	
	// JLE           Op0, Op1, Label
	p = AddInstructLookup ( "jle", INSTRUCT_JLE, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_LINE_LABEL );
	
	// ---- The Stack Interface
	// Push          Source
	p = AddInstructLookup ( "push", INSTRUCT_PUSH, 1 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// Pop           Destination
	p = AddInstructLookup ( "pop", INSTRUCT_POP, 1 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// ---- The Function Interface
	// Call          FunctionName
	p = AddInstructLookup ( "call", INSTRUCT_CALL, 1 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_FUNC_NAME );
	
	// Ret
	p = AddInstructLookup ( "Ret", INSTRUCT_RET, 0 );
	
	// CallHost      FunctionName
	p = AddInstructLookup ( "callhost", INSTRUCT_CALLHOST, 1 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_HOST_API_CALL );
	
	// ---- Miscellaneous
	// Pause        Duration
	p = AddInstructLookup ( "pause", INSTRUCT_PAUSE, 1 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// Exit         Code
	p = AddInstructLookup ( "exit", INSTRUCT_EXIT, 1 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );

	//////////////////////////////////////////////////////////////////////////
	//math instructions
	// abs          Destination, Source   [abs val, 5]
	p = AddInstructLookup ( "abs", INSTRUCT_ABS, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );

	// pow          Destination, Source, Source   [pow val, 5, 2]
	p = AddInstructLookup ( "pow", INSTRUCT_POW, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// sqrt          Destination, Source   [sqrt val, 0.707]
	p = AddInstructLookup ( "sqrt", INSTRUCT_SQRT, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// log10          Destination, Source   [log10 val, 5]
	p = AddInstructLookup ( "log10", INSTRUCT_LOG10, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// log          Destination, Source   [log val, 5]
	p = AddInstructLookup ( "log", INSTRUCT_LOG, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// sin          Destination, Source   [sin val, 0.707]
	p = AddInstructLookup ( "sin", INSTRUCT_SIN, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// cos          Destination, Source   [cos val, 0.707]
	p = AddInstructLookup ( "cos", INSTRUCT_COS, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// tan          Destination, Source   [tan val, 0.707]
	p = AddInstructLookup ( "tan", INSTRUCT_TAN, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// ctan          Destination, Source   [ctan val, 0.707]
	p = AddInstructLookup ( "ctan", INSTRUCT_CTAN, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// asin          Destination, Source   [asin val, 0.707]
	p = AddInstructLookup ( "asin", INSTRUCT_ASIN, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// acos          Destination, Source   [acos val, 0.707]
	p = AddInstructLookup ( "acos", INSTRUCT_ACOS, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// atan          Destination, Source   [atan val, 0.707]
	p = AddInstructLookup ( "atan", INSTRUCT_ATAN, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// atan2          Destination, Source, Source   [atan2 val, 0.707, 1]
	p = AddInstructLookup ( "atan2", INSTRUCT_ATAN2, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// min          Destination, Source, Source   [min val, 0.707, 2]
	p = AddInstructLookup ( "min", INSTRUCT_MIN, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// max          Destination, Source, Source   [max val, 0.707, 2]
	p = AddInstructLookup ( "max", INSTRUCT_MAX, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// ceil          Destination, Source   [ceil val, 0.707]
	p = AddInstructLookup ( "ceil", INSTRUCT_CEIL, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// floor          Destination, Source   [floor val, 0.707]
	p = AddInstructLookup ( "floor", INSTRUCT_FLOOR, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// hypot          Destination, Source, Source   [hypot val, 0.707, 2]
	p = AddInstructLookup ( "hypot", INSTRUCT_HYPOT, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// fmod          Destination, Source, Source   [fmod val, 2.5, 1.2]
	p = AddInstructLookup ( "fmod", INSTRUCT_FMOD, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// digit          Destination, Source, Source   [digit val, 2.5, 1.2]
	p = AddInstructLookup ( "digit", INSTRUCT_DIGIT, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// binary          Destination, Source, Source   [binary val, 32, 5]
	p = AddInstructLookup ( "binary", INSTRUCT_BINARY, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// atof          Destination, Source   [atof val, "10"]
	p = AddInstructLookup ( "atof", INSTRUCT_ATOF, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// atol          Destination, Source   [atol val, "10"]
	p = AddInstructLookup ( "atol", INSTRUCT_ATOL, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// ftoa          Destination, Source   [ftoa val, 10.5]
	p = AddInstructLookup ( "ftoa", INSTRUCT_FTOA, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	
	// ltoa          Destination, Source   [ltoa val, 10.5]
	p = AddInstructLookup ( "ltoa", INSTRUCT_LTOA, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );

	// cmp          Destination, Source, Source   [cmp val, 32, 5]
	p = AddInstructLookup ( "cmp", INSTRUCT_CMP, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);

	// cmpe          Destination, Source, Source   [cmpe val, 32, 5]
	p = AddInstructLookup ( "cmpe", INSTRUCT_CMPE, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);

	// cmpne          Destination, Source, Source   [cmpne val, 32, 5]
	p = AddInstructLookup ( "cmpne", INSTRUCT_CMPNE, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);

	// cmpg          Destination, Source, Source   [cmpg val, 32, 5]
	p = AddInstructLookup ( "cmpg", INSTRUCT_CMPG, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);

	// cmpl          Destination, Source, Source   [cmpl val, 32, 5]
	p = AddInstructLookup ( "cmpl", INSTRUCT_CMPL, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);

	// cmpge          Destination, Source, Source   [cmpge val, 32, 5]
	p = AddInstructLookup ( "cmpge", INSTRUCT_CMPGE, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);

	// cmple          Destination, Source, Source   [cmple val, 32, 5]
	p = AddInstructLookup ( "cmple", INSTRUCT_CMPLE, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG );
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);
	p->SetOpType (2, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF |
		OPERAND_FLAG_TYPE_REG |
		OPERAND_FLAG_TYPE_STRING);
}


CTInstruct* CTAsmInstructs::Find(const char *pstrName)
{
	ASSERT (g_pAsmInstructs != NULL);
	return g_pAsmInstructs->In_Find(pstrName);
}

BOOL CTAsmInstructs::IsInstructExist (const char *pstrName)
{
	ASSERT (g_pAsmInstructs != NULL);
	return g_pAsmInstructs->In_IsInstructExist(pstrName);
}

CTAsmInstructs* CTAsmInstructs::Create()
{
	m_nRefCount++;

	if (m_nRefCount == 1)
	{
		g_pAsmInstructs = new CTAsmInstructs();
	}
	
	return g_pAsmInstructs;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTAsmParser::CTAsmParser()
{
	m_ppstrSourceCode = NULL;
	m_iSourceCodeLines = 0;
	m_iInstructStreamSize = 0;
	m_iCurrInstructIndex = 0;

	m_iIsFuncActive = 0;
	memset(m_pstrIdentTemp, 0, MAX_IDENT_SIZE);
	m_iCurrFuncIndex = 0;
	memset(m_pstrFuncNameTemp, 0, MAX_IDENT_SIZE);
	m_iCurrFuncParamCount = 0;
	m_iCurrFuncLocalDataSize = 0;
	
	// Set the current function's flags and variables
	m_pCurrFuncTemp = NULL;
	m_iIsSetPriorityFound = 0;
	m_oScriptHeader.m_uiTimesliceDuration = 0;
	m_pBuffer = new char[MENBUFFERLENEX];;
	ZeroMemory(m_pBuffer, MENBUFFERLENEX);
}

CTAsmParser::~CTAsmParser()
{
	FreeParser();
}

void CTAsmParser::FreeParser()
{
	if (m_ppstrSourceCode != NULL)
	{
		free(m_ppstrSourceCode);
		m_ppstrSourceCode = NULL;
	}
	
	Release();
	
	m_iSourceCodeLines = 0;
	m_iInstructStreamSize = 0;
	m_iCurrInstructIndex = 0;
	m_oTSyntaxs.DeleteAll();
	m_oInstructions.DeleteAll();
	m_oFuncTable.DeleteAll();
	m_oLabelTable.DeleteAll();
	m_oSymbolTable.DeleteAll();
	m_oStringTable.DeleteAll();
	m_oHostAPICallTable.DeleteAll();
	m_oExportSymbols.DeleteAll();
}

//*********************************************************************
//ReadFromFile				public
//*********************************************************************
//描述：	从文件中获取数据
//参数：	strFile：文件名称
//返回：	无
BOOL CTAsmParser::ReadFromFile(const CString &strFile)
{
	FreeParser();
	
	CFile file;
	BOOL bTrue = file.Open(strFile, CFile::modeRead);

	if(bTrue)
	{
		m_nLength = file.GetLength();
		AllocMemBuffer(m_nLength);
		file.Read(m_pBuffer,m_nLength*sizeof(char));
		m_pBuffer[m_nLength] = 0;
		file.Close();
	}
	
	return bTrue;
}

void CTAsmParser::InitBuffer(BSTR strBuff)
{
#ifndef _PSX_QT_LINUX_
	long nLen = 2*(wcslen(strBuff)+1);
	
	AllocMemBuffer(nLen);
	WideCharToMultiByte(CP_ACP, 0, strBuff, -1, m_pBuffer, nLen, NULL,NULL);
#endif
}

void CTAsmParser::InitBuffer(char* strBuff)
{
	long nLen = strlen(strBuff);
	
	AllocMemBuffer(nLen);
	strcpy(m_pBuffer,strBuff);
}


BOOL CTAsmParser::WriteToFile(const CString &strFile)
{
	CFile file;
    BOOL bOpen = file.Open(strFile, CFile::modeCreate|CFile::modeWrite);
	
	if (bOpen)
	{
		file.Write(m_pBuffer,m_nLength*sizeof(char));
		file.Close();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


void CTAsmParser::AllocMemBuffer(long nBufferLen)
{
	CXvmBuffer::InitBuffer(nBufferLen);
}


/******************************************************************************************
*
*	IsCharWhitespace ()
*
*	Returns a nonzero if the given character is whitespace, or zero otherwise.
*/

int CTAsmParser::IsCharWhitespace ( char cChar )
{
	// Return true if the character is a space or tab.
	
	if ( cChar == ' ' || cChar == '\t' )
		return TRUE;
	else
		return FALSE;
}

/******************************************************************************************
*
*	IsCharNumeric ()
*
*	Returns a nonzero if the given character is numeric, or zero otherwise.
*/

int CTAsmParser::IsCharNumeric ( char cChar )
{
	// Return true if the character is between 0 and 9 inclusive.
	
	if ( cChar >= '0' && cChar <= '9' )
		return TRUE;
	else
		return FALSE;
}

/******************************************************************************************
*
*	IsCharIdentifier ()
*
*	Returns a nonzero if the given character is part of a valid identifier, meaning it's an
*	alphanumeric or underscore. Zero is returned otherwise.
*/

int CTAsmParser::IsCharIdent ( char cChar )
{
	// Return true if the character is between 0 or 9 inclusive or is an uppercase or
	// lowercase letter or underscore
	
	if ( ( cChar >= '0' && cChar <= '9' ) ||
		( cChar >= 'A' && cChar <= 'Z' ) ||
		( cChar >= 'a' && cChar <= 'z' ) ||
		cChar == '_' )
		return TRUE;
	else
		return FALSE;
}

/******************************************************************************************
*
*	IsCharDelimiter ()
*
*	Return a nonzero if the given character is a token delimeter, and return zero otherwise
*/

int CTAsmParser::IsCharDelimiter ( char cChar )
{
	// Return true if the character is a delimiter
	
	if ( cChar == ':' || cChar == ',' || cChar == '"' ||
		cChar == '[' || cChar == ']' ||
		cChar == KEY_OPEN_BRACE || cChar == KEY_CLOSE_BRACE ||
		IsCharWhitespace ( cChar ) || cChar == '\n' )
		return TRUE;
	else
		return FALSE;
}

/******************************************************************************************
*
*	TrimWhitespace ()
*
*	Trims whitespace off both sides of a string.
*/

void CTAsmParser::TrimWhitespace ( char ** pstrString )
{
	unsigned int iStringLength = strlen ( *pstrString );
	char *pLeft = *pstrString;
	char *pRight = *pstrString + iStringLength - 1;
	
	if ( iStringLength >= 1 )
	{
		// First determine whitespace quantity on the left
		while (IsCharWhitespace ( *pLeft ) 
			&& *pLeft != 0  /*End of the string*/)
		{
			*pLeft = 0;
			pLeft++;
		}
		
		// Terminate string at the start of right hand whitespace
		while (IsCharWhitespace ( *pRight ) 
			&& (pRight > pLeft)  /*Begin of the string*/)
		{
			*pRight = 0;
			pRight--;
		}
	}

	*pstrString = pLeft;
}

/******************************************************************************************
*
*	IsStringWhitespace ()
*
*	Returns a nonzero if the given string is whitespace, or zero otherwise.
*/

int CTAsmParser::IsStringWhitespace ( char * pstrString )
{
	// If the string is NULL, return false
	
	if ( ! pstrString )
		return FALSE;
	
	// If the length is zero, it's technically whitespace
	unsigned int nStringLen = strlen(pstrString);

	if ( nStringLen == 0 )
		return TRUE;
	
	// Loop through each character and return false if a non-whitespace is found
	
	for ( unsigned int iCurrCharIndex = 0; iCurrCharIndex < nStringLen; ++ iCurrCharIndex )
	{
		if ( ! IsCharWhitespace ( pstrString [ iCurrCharIndex ] ) && pstrString [ iCurrCharIndex ] != '\n' )
			return FALSE;
	}
		
	// Otherwise return true
		
	return TRUE;
}

/******************************************************************************************
*
*	IsStringIdentifier ()
*
*	Returns a nonzero if the given string is composed entirely of valid identifier
*	characters and begins with a letter or underscore. Zero is returned otherwise.
*/

int CTAsmParser::IsStringIdent ( char * pstrString )
{
	// If the string is NULL return false
	if ( ! pstrString )
		return FALSE;
	
	unsigned int nStringLen = strlen ( pstrString );

	// If the length of the string is zero, it's not a valid identifier
	if ( nStringLen == 0 )
		return FALSE;
	
	// If the first character is a number, it's not a valid identifier
	
	if ( pstrString [ 0 ] >= '0' && pstrString [ 0 ] <= '9' )
		return FALSE;
	
	// Loop through each character and return zero upon encountering the first invalid identifier
	// character
	
	BOOL bIsStringIdent = TRUE;

	for ( unsigned int iCurrCharIndex = 0; iCurrCharIndex < nStringLen; ++ iCurrCharIndex )
	{
		if ( ! IsCharIdent ( pstrString [ iCurrCharIndex ] ) )
		{
			bIsStringIdent = FALSE;
			break;
		}
	}
		
	return bIsStringIdent;
}

/******************************************************************************************
*
*	IsStringInteger ()
*
*	Returns a nonzero if the given string is composed entire of integer characters, or zero
*	otherwise.
*/

int CTAsmParser::IsStringInteger ( char * pstrString )
{
	// If the string is NULL, it's not an integer
	if ( ! pstrString )
		return FALSE;
	
	// If the string's length is zero, it's not an integer
	unsigned int nStringLen = strlen(pstrString);

	if ( nStringLen == 0 )
		return FALSE;
	
	unsigned int iCurrCharIndex;
	
	// Loop through the string and make sure each character is a valid number or minus sign
	for ( iCurrCharIndex = 0; iCurrCharIndex < nStringLen; ++ iCurrCharIndex )
	{
		if ( ! IsCharNumeric ( pstrString [ iCurrCharIndex ] ) && ! ( pstrString [ iCurrCharIndex ] == '-' ) )
			return FALSE;
	}

	// Make sure the minus sign only occured at the first character
	for ( iCurrCharIndex = 1; iCurrCharIndex < nStringLen; ++ iCurrCharIndex )
	{
		if ( pstrString [ iCurrCharIndex ] == '-' )
			return FALSE;
	}
	
	return TRUE;
}

/******************************************************************************************
*
*	IsStringFloat ()
*
*	Returns a nonzero if the given string is composed entire of float characters, or zero
*	otherwise.
*/

int CTAsmParser::IsStringFloat( char * pstrString )
{
	if ( ! pstrString )
		return FALSE;
	
	unsigned int nStringLen = strlen(pstrString);

	if ( nStringLen == 0 )
		return FALSE;
	
	// First make sure we've got only numbers and radix points
	unsigned int iCurrCharIndex;
	
	for ( iCurrCharIndex = 0; iCurrCharIndex < nStringLen; ++ iCurrCharIndex )
	{
		if ( ! IsCharNumeric ( pstrString [ iCurrCharIndex ] ) && ! ( pstrString [ iCurrCharIndex ] == '.' ) && ! ( pstrString [ iCurrCharIndex ] == '-' ) )
		{
			return FALSE;
		}
	}
	
	// Make sure only one radix point is present
	int iRadixPointFound = 0;
	
	for ( iCurrCharIndex = 0; iCurrCharIndex < nStringLen; ++ iCurrCharIndex )
		
	{
		if ( pstrString [ iCurrCharIndex ] == '.' )
		{
			if ( iRadixPointFound )
				return FALSE;
			else
				iRadixPointFound = 1;
		}
	}
	
	// Make sure the minus sign only appears in the first character
	for ( iCurrCharIndex = 1; iCurrCharIndex < nStringLen; ++ iCurrCharIndex )
	{
		if ( pstrString [ iCurrCharIndex ] == '-' )
			return FALSE;
	}

	// If a radix point was found, return true; otherwise, it must be an integer so return false
	if ( iRadixPointFound )
		return TRUE;
	else
		return FALSE;
}


/******************************************************************************************
*
*	StripComments ()
*
*	Strips the comments from a given line of source code, ignoring comment symbols found
*	inside strings. The new string is shortended to the index of the comment symbol
*	character.
*/

void CTAsmParser::StripComments ( char * pstrSourceLine )
{
	int iCurrCharIndex = 0;
	int iInString = 0;
	
	// Scan through the source line and terminate the string at the first semicolon
	iInString = 0;
	long nLineLen = strlen ( pstrSourceLine );
	
	for ( iCurrCharIndex = 0; iCurrCharIndex < nLineLen/* - 1*/; ++ iCurrCharIndex )
	{
		// Look out for strings; they can contain semicolons
		if ( pstrSourceLine [ iCurrCharIndex ] == '"' )
		{
			if ( iInString )
				iInString = 0;
			else
				iInString = 1;
		}
		
		// If a non-string semicolon is found, terminate the string at it's position
		if ( pstrSourceLine [ iCurrCharIndex ] == ';' )
		{
			if ( ! iInString )
			{
				memset(pstrSourceLine+iCurrCharIndex, 0, nLineLen - iCurrCharIndex);
				break;
			}
		}
	}
}

void CTAsmParser::InitSourceCodeLines()
{
	char *p = m_pBuffer;
	char *pEnd = m_pBuffer + m_nLength;
	
	m_iSourceCodeLines = 0;
	free(m_ppstrSourceCode);
	
	while (p <= pEnd)
	{
		if (*p == '\n')
		{
			m_iSourceCodeLines++;
			p++;
		}
		else
		{
			p++;
		}
	}

	m_iSourceCodeLines++;
	
	m_ppstrSourceCode = new char* [m_iSourceCodeLines];
	char **ppstrSourceCode = m_ppstrSourceCode;

	p = m_pBuffer;
	*ppstrSourceCode = p;

	while (p <= pEnd)
	{
		if (*p == '\n')
		{
			*p = 0;
			StripComments ( *ppstrSourceCode );
			TrimWhitespace ( &(*ppstrSourceCode) );			
			p++;
			ppstrSourceCode++;
			*ppstrSourceCode = p;
		}
		else
		{
			if (*p == '\r')
			{
				*p = 0;
			}

			p++;
		}
	}

	StripComments ( *ppstrSourceCode );
	TrimWhitespace ( &(*ppstrSourceCode) );
}

void CTAsmParser::Assemble_FirstPass_SetStackSize()
{
	// SetStackSize can only be found in the global scope, so make sure we
	// aren't in a function.
	if ( m_iIsFuncActive )
	{
		AddCodeError ( ERROR_ASMMSG_LOCAL_SETSTACKSIZE );
	}
	
	// It can only be found once, so make sure we haven't already found it
	if ( m_iIsSetStackSizeFound )
	{
		AddCodeError ( ERROR_ASMMSG_MULTIPLE_SETSTACKSIZES );
	}
	
	// Read the next lexeme, which should contain the stack size
	if ( GetNextToken () != TASM_TOKEN_TYPE_INT )
	{
		AddCodeError ( ERROR_ASMMSG_INVALID_STACK_SIZE );
	}
	else
	{
		// Convert the lexeme to an integer value from its string
		// representation and store it in the script header
		m_oScriptHeader.m_iStackSize = atoi ( GetCurrLexeme () );
	}
	
	//if SetStackSize only end with int.
	m_oLexer.Backup();

	if (GetNextToken(FALSE) != TASM_TOKEN_TYPE_INVALID)
	{
		AddCodeError ( ERROR_ASMMSG_INVALID_STACK_LINE , FALSE);		
	}

	m_oLexer.Restore();

	// Mark the presence of SetStackSize for future encounters
	m_iIsSetStackSizeFound = TRUE;
}

void CTAsmParser::Assemble_FirstPass_SetPriority()
{
	// SetPriority can only be found in the global scope, so make sure we
	// aren't in a function.
	if ( m_iIsFuncActive )
	{
		AddCodeError ( ERROR_ASMMSG_LOCAL_SETSTACKSIZE );
	}
	
	// It can only be found once, so make sure we haven't already found it
	if ( m_iIsSetPriorityFound )
	{
		AddCodeError ( ERROR_ASMMSG_MULTIPLE_SETPRIORITYS );
	}
	
	GetNextToken ();
	
	switch ( m_oLexer.m_CurrToken )
	{
		// An integer lexeme means the user is defining a specific priority
	case TASM_TOKEN_TYPE_INT:
		// Convert the lexeme to an integer value from its string
		// representation and store it in the script header
		m_oScriptHeader.m_uiTimesliceDuration = atoi ( GetCurrLexeme () );
		
		// Set the user priority flag
		m_oScriptHeader.m_ucPriorityType = PRIORITY_USER;
		
		break;
		
		// An identifier means it must be one of the predefined priority
		// ranks
	case TASM_TOKEN_TYPE_IDENT:
		// Determine which rank was specified
		if ( stricmp ( m_oLexer.m_pstrCurrLexeme, PRIORITY_LOW_KEYWORD ) == 0 )
		{
			m_oScriptHeader.m_ucPriorityType = PRIORITY_LOW;
		}
		else if ( stricmp ( m_oLexer.m_pstrCurrLexeme, PRIORITY_MED_KEYWORD ) == 0 )
		{
			m_oScriptHeader.m_ucPriorityType = PRIORITY_MED;
		}
		else if ( stricmp ( m_oLexer.m_pstrCurrLexeme, PRIORITY_HIGH_KEYWORD ) == 0 )
		{
			m_oScriptHeader.m_ucPriorityType = PRIORITY_HIGH;
		}
		else
		{
			AddCodeError ( ERROR_MSSG_INVALID_PRIORITY );
		}
		
		break;
		
		// Anything else should cause an error
	default:
		AddCodeError ( ERROR_MSSG_INVALID_PRIORITY );
		break;
	}
	
	//if SetPriority only end with int.
	m_oLexer.Backup();
	
	if (GetNextToken(FALSE) != TASM_TOKEN_TYPE_INVALID)
	{
		AddCodeError ( ERROR_ASMMSG_INVALID_STACK_LINE , FALSE);		
	}
	
	m_oLexer.Restore();
	
	// Mark the presence of SetStackSize for future encounters
	m_iIsSetPriorityFound = TRUE;
}

void CTAsmParser::Assemble_FirstPass_Var()
{
	// Get the variable's identifier
	if ( GetNextToken () != TASM_TOKEN_TYPE_IDENT )
	{
		AddCodeError ( ERROR_ASMMSG_IDENT_EXPECTED );
	}
	else
	{
		char pstrVariableName [ MAX_IDENT_SIZE ];
		strcpy(pstrVariableName, m_oLexer.m_pstrCurrLexemeOrigin);
		strcpy ( m_pstrIdentTemp, GetCurrLexeme () );
		
		// Now determine its size by finding out if it's an array or not, otherwise
		// default to 1.
		int iSize = 1;
		
		// Find out if an opening bracket lies ahead
		if ( GetLookAheadChar () == '[' )
		{
			// Validate and consume the opening bracket
			if ( GetNextToken () != TASM_TOKEN_TYPE_OPEN_BRACKET )
			{
				AddCharExpectedError ( '[' );
			}
			else
			{
				// We're parsing an array, so the next lexeme should be an integer
				// describing the array's size
				if ( GetNextToken () != TASM_TOKEN_TYPE_INT )
				{
					AddCodeError ( ERROR_ASMMSG_INVALID_ARRAY_SIZE );
				}
				else
				{
					// Convert the size lexeme to an integer value
					iSize = atoi ( GetCurrLexeme () );
					
					// Make sure the size is valid, in that it's greater than zero
					if ( iSize <= 0 )
					{
						AddCodeError ( ERROR_ASMMSG_INVALID_ARRAY_SIZE );
					}
					
					// Make sure the closing bracket is present as well
					if ( GetNextToken () != TASM_TOKEN_TYPE_CLOSE_BRACKET )
					{
						AddCharExpectedError ( ']' );
					}
				}
			}
		}

		// Determine the variable's index into the stack
		// If the variable is local, then its stack index is always the local data
		// size + 2 subtracted from zero
		int iStackIndex = 0;
		
		if ( m_iIsFuncActive )
		{
			iStackIndex = -( m_iCurrFuncLocalDataSize + 2 );
		}
		else
		{// Otherwise it's global, so it's equal to the current global data size
			iStackIndex = m_oScriptHeader.m_iGlobalDataSize;
		}
		
		// Attempt to add the symbol to the table
		if ( AddSymbol ( m_pstrIdentTemp, iSize, iStackIndex, m_iCurrFuncIndex ) == -1 )
		{
			//if (m_oSymbolTable.Add(pstrIdent, iSize, iStackIndex, m_iCurrFuncIndex) == -1)
			AddCodeError ( ERROR_ASMMSG_IDENT_REDEFINITION );
		}
		
		// Depending on the scope, increment either the local or global data size
		// by the size of the variable
		if ( m_iIsFuncActive )
		{
			m_iCurrFuncLocalDataSize += iSize;
		}
		else
		{
			m_oScriptHeader.m_iGlobalDataSize += iSize;
		}

		//export symbols
		m_oLexer.Backup();
		if (GetNextToken() == TASM_TOKEN_TYPE_EXPORT)
		{
			bool bErr = FALSE;

			if (m_iIsFuncActive)
			{
				AddCodeError ( ERROR_ASMMSG_EXPORT_IN_FUNC );
				bErr = true;
			}
			
			if (iSize > 1)
			{
				AddCodeError ( ERROR_ASMMSG_EXPORT_IN_FUNC );
				bErr = true;
			}

			if (!bErr)
			{
				m_oExportSymbols.Add(pstrVariableName, iStackIndex);
			}
		}
		else
		{
			m_oLexer.Restore();
		}
	}
}

void CTAsmParser::Assemble_FirstPass_Func()
{
	// First make sure we aren't in a function already, since nested functions
	// are illegal
	if ( m_iIsFuncActive )
	{
		AddCodeError ( ERROR_ASMMSG_NESTED_FUNC );
	}
	else
	{
		// Read the next lexeme, which is the function name
		if ( GetNextToken () != TASM_TOKEN_TYPE_IDENT )
		{
			AddCodeError ( ERROR_ASMMSG_IDENT_EXPECTED );
		}
		else
		{
			char * pstrFuncName = GetCurrLexeme ();
			
			// Calculate the function's entry point, which is the instruction immediately
			// following the current one, which is in turn equal to the instruction stream
			// size
			int iEntryPoint = m_iInstructStreamSize;
			
			// Try adding it to the function table, and print an error if it's already
			// been declared
			int iFuncIndex = AddFunc ( pstrFuncName, iEntryPoint );
			
			if ( iFuncIndex == -1 )
			{
				AddCodeError ( ERROR_ASMMSG_FUNC_REDEFINITION );
			}
			
			// Is this the _Main () function?
			if ( stricmp ( pstrFuncName, MAIN_FUNC_NAME ) == 0 )
			{
				m_oScriptHeader.m_iIsMainFuncPresent = TRUE;
				m_oScriptHeader.m_iMainFuncIndex = iFuncIndex;
			}
			
			// Set the function flag to true for any future encounters and re-initialize
			// function tracking variables
			
			m_iIsFuncActive = TRUE;
			strcpy ( m_pstrFuncNameTemp, pstrFuncName );
			m_iCurrFuncIndex = iFuncIndex;
			m_iCurrFuncParamCount = 0;
			m_iCurrFuncLocalDataSize = 0;
			
			// Read any number of line breaks until the opening brace is found
			while ( GetNextToken () == TASM_TOKEN_TYPE_NEWLINE );
			
			// Make sure the lexeme was an opening brace
			if ( m_oLexer.m_CurrToken != TASM_TOKEN_TYPE_OPEN_BRACE )
			{
				AddCharExpectedError ( KEY_OPEN_BRACE );
			}
			
			// All functions are automatically appended with Ret, so increment the
			// required size of the instruction stream
			++ m_iInstructStreamSize;
		}
	}
}

void CTAsmParser::Assemble_FirstPass_ClosingBrace()
{
	// This should be closing a function, so make sure we're in one
	if ( ! m_iIsFuncActive )
	{
		AddCharExpectedError ( KEY_CLOSE_BRACE );
	}
	else
	{
		// Set the fields we've collected
		SetFuncInfo ( m_pstrFuncNameTemp, m_iCurrFuncParamCount, m_iCurrFuncLocalDataSize );
	}
	
	// Close the function
	m_iIsFuncActive = FALSE;

	//进入全局作用域
	m_iCurrFuncIndex = 0;
}

void CTAsmParser::Assemble_FirstPass_Param()
{
	// If we aren't currently in a function, print an error
	if ( ! m_iIsFuncActive )
	{
		AddCodeError ( ERROR_ASMMSG_GLOBAL_PARAM );
	}
	else
	{
		// _Main () can't accept parameters, so make sure we aren't in it
		if ( stricmp ( m_pstrFuncNameTemp, MAIN_FUNC_NAME ) == 0 )
		{
			AddCodeError ( ERROR_ASMMSG_MAIN_PARAM );
		}
		
		// The parameter's identifier should follow		
		if ( GetNextToken () != TASM_TOKEN_TYPE_IDENT )
		{
			AddCodeError ( ERROR_ASMMSG_IDENT_EXPECTED );
		}
		
		// Increment the current function's local data size
		++ m_iCurrFuncParamCount;				
	}
}

void CTAsmParser::Assemble_FirstPass_Instruction()
{
	// Make sure we aren't in the global scope, since instructions
	// can only appear in functions
	if ( ! m_iIsFuncActive )
	{
		AddCodeError ( ERROR_ASMMSG_GLOBAL_INSTRUCT );
	}
	
	// Increment the instruction stream size
	++ m_iInstructStreamSize;
}

void CTAsmParser::Assemble_FirstPass_Identifier()
{
	// Make sure it's a line label
	if ( GetLookAheadChar () != ':' )
	{
		AddCodeError ( ERROR_ASMMSG_INVALID_INSTRUCT );
	}
	
	// Make sure we're in a function, since labels can only appear there
	if ( ! m_iIsFuncActive )
	{
		AddCodeError ( ERROR_ASMMSG_GLOBAL_LINE_LABEL );
	}
	
	// The current lexeme is the label's identifier
	char * pstrLabel = GetCurrLexeme ();
	
	// The target instruction is always the value of the current
	// instruction count, which is the current size - 1
	int iTargetIndex = m_iInstructStreamSize - 1;
	
	// Save the label's function index as well
	int iFuncIndex = m_iCurrFuncIndex;
	
	// Try adding the label to the label table, and print an error if it
	// already exists
	if ( AddLabel ( pstrLabel, iTargetIndex, iFuncIndex ) == -1 )
	{
		AddCodeError ( ERROR_ASMMSG_LINE_LABEL_REDEFINITION );
	}
}

void CTAsmParser::Assemble_FirstPass()
{
	m_iIsFuncActive = 0;
	memset(m_pstrIdentTemp, 0, MAX_IDENT_SIZE);
	m_iCurrFuncIndex = 0;
	memset(m_pstrFuncNameTemp, 0, MAX_IDENT_SIZE);
	m_iCurrFuncParamCount = 0;
	m_iCurrFuncLocalDataSize = 0;
	
	// Set the current function's flags and variables
	m_pCurrFuncTemp = NULL;
					
	// ---- Perform first pass over the source
	// Reset the lexer
	m_oLexer.ResetLexer ();
	
	// Loop through each line of code
	while ( TRUE )
	{
		// Get the next token and make sure we aren't at the end of the stream
		if ( GetNextToken () == END_OF_TASM_TOKEN_STREAM )
			break;
		
		// Check the initial token
		switch ( m_oLexer.m_CurrToken )
		{
			// ---- Start by checking for directives
		case TASM_TOKEN_TYPE_SETSTACKSIZE:// SetStackSize
			Assemble_FirstPass_SetStackSize();
			break;
		case TASM_TOKEN_TYPE_SETPRIORITY:// SETPRIORITY
			Assemble_FirstPass_SetPriority();
			break;
		case TASM_TOKEN_TYPE_VAR:// Var/Var []
			Assemble_FirstPass_Var();
			break;
		case TASM_TOKEN_TYPE_FUNC:// Func
			Assemble_FirstPass_Func();
			break;
		case TASM_TOKEN_TYPE_CLOSE_BRACE:// Closing brace
			Assemble_FirstPass_ClosingBrace();
			break;
		case TASM_TOKEN_TYPE_PARAM:// Param
			Assemble_FirstPass_Param();
			break;
		case TASM_TOKEN_TYPE_INSTRUCT:// ---- Instructions
			Assemble_FirstPass_Instruction();
			break;
		case TASM_TOKEN_TYPE_IDENT:// ---- Identifiers (line labels)
			Assemble_FirstPass_Identifier();
			break;
		default:
			{
				// Anything else should cause an error, minus line breaks
				if ( m_oLexer.m_CurrToken != TASM_TOKEN_TYPE_NEWLINE )
				{
					AddCodeError ( ERROR_ASMMSG_INVALID_INPUT );
				}
				break;
			}
		}
		
		// Skip to the next line, since the initial tokens are all we're really worrid
		// about in this phase
		if ( ! SkipToNextLine () )
			break;
	}
}

void CTAsmParser::Assemble_SecondPass_Func()
{
	// We've encountered a Func directive, but since we validated the syntax
	// of all functions in the previous phase, we don't need to perform any
	// error handling here and can assume the syntax is perfect.
	// Read the identifier
	GetNextToken ();
	
	// Use the identifier (the current lexeme) to get it's corresponding function
	// from the table
	m_pCurrFuncTemp = GetFuncByName ( GetCurrLexeme () );
	
	// Set the active function flag
	m_iIsFuncActive = TRUE;
	
	// Set the parameter count to zero, since we'll need to count parameters as
	// we parse Param directives
	m_iCurrFuncParamCount = 0;
	
	// Save the function's index
	m_iCurrFuncIndex = m_pCurrFuncTemp->m_iIndex;
	
	// Read any number of line breaks until the opening brace is found
	while ( GetNextToken () == TASM_TOKEN_TYPE_NEWLINE );
}

void CTAsmParser::Assemble_SecondPass_ClosingBrace()
{
	// Clear the active function flag
	m_iIsFuncActive = FALSE;
	
	CInstruction *pInstruction = m_oInstructions[m_iCurrInstructIndex];
	
	// If the ending function is _Main (), append an Exit instruction
	if ( stricmp ( m_pCurrFuncTemp->m_pstrName, MAIN_FUNC_NAME ) == 0 )
	{
		// First set the opcode
		pInstruction->m_nOpcode = INSTRUCT_EXIT;
		
		// Now set the return code by allocating space for a single operand and
		// setting it to zero
		pInstruction->m_oOperands.Add(OPERAND_TYPE_INT, 0);
	}
	else
	{
		// Otherwise append a Ret instruction and make sure to NULLify the operand
		// list pointer
		pInstruction->m_nOpcode = INSTRUCT_RET;
	}
	
	++ m_iCurrInstructIndex;

	//全部作用域
	m_iCurrFuncIndex = 0;
}

void CTAsmParser::Assemble_SecondPass_Param()
{
	// Read the next token to get the identifier
	if ( GetNextToken () != TASM_TOKEN_TYPE_IDENT )
	{
		AddCodeError ( ERROR_ASMMSG_IDENT_EXPECTED );
	}
	else
	{
		// Read the identifier, which is the current lexeme
		char * pstrSymbol = GetCurrLexeme ();
		
		// Calculate the parameter's stack index
		int iStackIndex = -( m_pCurrFuncTemp->m_iLocalDataSize + 2 + ( m_iCurrFuncParamCount + 1 ) );
		
		// Add the parameter to the symbol table
		if ( AddSymbol ( pstrSymbol, 1, iStackIndex, m_iCurrFuncIndex ) == -1 )
		{
			AddCodeError ( ERROR_ASMMSG_IDENT_REDEFINITION );
		}
		
		// Increment the current parameter count
		++ m_iCurrFuncParamCount;
	}
}

void CTAsmParser::Assemble_SecondPass_Instruction()
{
	CInstruction *pInstruction = m_oInstructions[m_iCurrInstructIndex];
	// Create an instruction definition structure to hold instruction information when
	// dealing with instructions.
	CTInstruct *pInstSrc = NULL;
	
	// Get the instruction's info using the current lexeme (the mnemonic )
	pInstSrc = CTAsmInstructs::Find(GetCurrLexeme ());
	
	// Write the opcode to the stream
	pInstruction->m_nOpcode = pInstSrc->m_nOpcode;
	
	// Write the operand count to the stream
	// Allocate space to hold the operand list
	COperands *pOpList = &(pInstruction->m_oOperands);
	pOpList->Create(pInstSrc->m_nOpCount);
	
	// Loop through each operand, read it from the source and assemble it
	for ( int iCurrOpIndex = 0; iCurrOpIndex < pInstSrc->m_nOpCount; ++ iCurrOpIndex )
	{
		// Read the operand's type bitfield
		OperandTypes CurrOpTypes = pInstSrc->m_OpList [ iCurrOpIndex ];
		COperand *pOperand = (*pOpList)[iCurrOpIndex];

		// Read in the next token, which is the initial token of the operand
		Token InitOpToken = GetNextToken ();

		switch ( InitOpToken )
		{
		case TASM_TOKEN_TYPE_INT:// An integer literal
			// Make sure the operand type is valid
			Assemble_SecondPass_Instruction_Int(CurrOpTypes, pOperand);
			break;
		case TASM_TOKEN_TYPE_FLOAT:// A floating-point literal
			// Make sure the operand type is valid
			Assemble_SecondPass_Instruction_Float(CurrOpTypes, pOperand);
			break;
		case TASM_TOKEN_TYPE_QUOTE:// A string literal (since strings always start with quotes)
			Assemble_SecondPass_Instruction_Quote(CurrOpTypes, pOperand);
			break;
		case TASM_TOKEN_TYPE_REG_RETVAL:// _RetVal
			Assemble_SecondPass_Instruction_Retval(CurrOpTypes, pOperand);
			break;
			// Identifiers
			// These operands can be any of the following
			//      - Variables/Array Indices
			//      - Line Labels
			//      - Function Names
			//      - Host API Calls
		case TASM_TOKEN_TYPE_IDENT:
			Assemble_SecondPass_Instruction_Identifier(CurrOpTypes, pOperand);
			break;
		default:// Anything else
			
			AddCodeError ( ERROR_ASMMSG_INVALID_OPERAND );
			break;
		}
		
		// Make sure a comma follows the operand, unless it's the last one
		if ( iCurrOpIndex < pInstSrc->m_nOpCount - 1 )
		{
			if ( GetNextToken () != TASM_TOKEN_TYPE_COMMA )
			{
				AddCharExpectedError ( ',' );
			}
		}
    }
	
	// Make sure there's no extranous stuff ahead
	if ( GetNextToken (FALSE) != TASM_TOKEN_TYPE_INVALID )
		AddCodeError ( ERROR_ASMMSG_INVALID_INPUT );
	
    // Copy the operand list pointer into the assembled stream
    // Move along to the next instruction in the stream
	
    ++ m_iCurrInstructIndex;
}

void CTAsmParser::Assemble_SecondPass_Instruction_Int(OperandTypes CurrOpTypes, COperand *pOperand)
{
	if ( CurrOpTypes & OPERAND_FLAG_TYPE_INT )
	{
		// Set an integer operand type
		//pOperand->m_nType = OPERAND_TYPE_INT;
		pOperand->m_nType = OPERAND_TYPE_INT;
		
		// Copy the value into the operand list from the current
		// lexeme
		//pOperand->m_iIntLiteral = atoi ( GetCurrLexeme () );
		pOperand->m_iIntLiteral = atoi ( GetCurrLexeme () );
	}
	else
	{
		AddCodeError ( ERROR_ASMMSG_INVALID_OPERAND );
	}
}

void CTAsmParser::Assemble_SecondPass_Instruction_Float(OperandTypes CurrOpTypes, COperand *pOperand)
{
	if ( CurrOpTypes & OPERAND_FLAG_TYPE_FLOAT )
	{
		pOperand->m_nType = OPERAND_TYPE_FLOAT;
		pOperand->m_fFloatLiteral = ( float ) atof ( GetCurrLexeme () );
	}
	else
	{
		AddCodeError ( ERROR_ASMMSG_INVALID_OPERAND );
	}
}

void CTAsmParser::Assemble_SecondPass_Instruction_Quote(OperandTypes CurrOpTypes, COperand *pOperand)
{
	// Make sure the operand type is valid
	if ( CurrOpTypes & OPERAND_FLAG_TYPE_STRING )
	{
		GetNextToken ();
		
		// Handle the string based on its type
		switch ( m_oLexer.m_CurrToken )
		{
		case TASM_TOKEN_TYPE_QUOTE:// If we read another quote, the string is empty
			{
				// Convert empty strings to the integer value zero
				pOperand->m_nType = OPERAND_TYPE_INT;
				pOperand->m_iIntLiteral = 0;
				break;
			}
		case TASM_TOKEN_TYPE_STRING:// It's a normal string
			{
				// Get the string literal
				char * pstrString = GetCurrLexeme ();
				
				// Add the string to the table, or get the index of
				// the existing copy
				int iStringIndex = m_oStringTable.Add( pstrString );
				
				// Make sure the closing double-quote is present
				if ( GetNextToken () != TASM_TOKEN_TYPE_QUOTE )
					AddCharExpectedError ( '\\' );
				
				// Set the operand type to string index and set its
				// data field
				pOperand->m_nType = OPERAND_TYPE_STRING_INDEX;
				pOperand->m_iStringTableIndex = iStringIndex;
				break;
			}
		default:// The string is invalid
			AddCodeError ( ERROR_ASMMSG_INVALID_STRING );
			break;
		}
	}
	else
	{
		AddCodeError ( ERROR_ASMMSG_INVALID_OPERAND );	
	}
}

void CTAsmParser::Assemble_SecondPass_Instruction_Retval(OperandTypes CurrOpTypes, COperand *pOperand)
{
	// Make sure the operand type is valid
	if ( CurrOpTypes & OPERAND_FLAG_TYPE_REG )
	{
		// Set a register type
		pOperand->m_nType = OPERAND_TYPE_REG;
		pOperand->m_iReg = 0;
	}
	else
	{
		AddCodeError ( ERROR_ASMMSG_INVALID_OPERAND );
	}
}

void CTAsmParser::Assemble_SecondPass_Instruction_Identifier(OperandTypes CurrOpTypes, COperand *pOperand)
{
	// Find out which type of identifier is expected. Since no
	// instruction in XVM assebly accepts more than one type
	// of identifier per operand, we can use the operand types
	// alone to determine which type of identifier we're
	// parsing.
	
	// Parse a memory reference-- a variable or array index
	if ( CurrOpTypes & OPERAND_FLAG_TYPE_MEM_REF )
	{
		// Whether the memory reference is a variable or array
		// index, the current lexeme is the identifier so save a
		// copy of it for later
		char pstrIdent [ MAX_IDENT_SIZE ];
		strcpy ( pstrIdent, GetCurrLexeme () );
		
		// Make sure the variable/array has been defined
		if ( ! FindSymbol ( pstrIdent, m_iCurrFuncIndex ) )
		{
			AddCodeError ( ERROR_ASMMSG_UNDEFINED_IDENT );
		}
		
		// Get the identifier's index as well; it may either be
		// an absolute index or a base index
		int iBaseIndex = GetStackIndex ( pstrIdent, m_iCurrFuncIndex );
		
		// Use the lookahead character to find out whether or not
		// we're parsing an array
		if ( GetLookAheadChar () != '[' )
		{
			// It's just a single identifier so the base index we
			// already saved is the variable's stack index
			// Make sure the variable isn't an array
			if ( GetSize ( pstrIdent, m_iCurrFuncIndex ) > 1 )
			{
				AddCodeError ( ERROR_ASMMSG_INVALID_ARRAY_NOT_INDEXED );
			}
			
			// Set the operand type to stack index and set the data
			// field
			pOperand->m_nType = OPERAND_TYPE_ABS_STACK_INDEX;
			pOperand->m_iIntLiteral = iBaseIndex;
		}
		else
		{
			// It's an array, so lets verify that the identifier is
			// an actual array
			if ( GetSize ( pstrIdent, m_iCurrFuncIndex ) == 1 )
			{
				AddCodeError ( ERROR_ASMMSG_INVALID_ARRAY );
			}
			
			// First make sure the open brace is valid
			if ( GetNextToken () != TASM_TOKEN_TYPE_OPEN_BRACKET )
			{
				AddCharExpectedError ( '[' );
			}
			
			// The next token is the index, be it an integer literal
			// or variable identifier
			Token IndexToken = GetNextToken ();
			
			if ( IndexToken == TASM_TOKEN_TYPE_INT )
			{
				// It's an integer, so determine its value by
				// converting the current lexeme to an integer
				int iOffsetIndex = atoi ( GetCurrLexeme () );
				
				// Add the index to the base index to find the offset
				// index and set the operand type to absolute stack
				// index
				pOperand->m_nType = OPERAND_TYPE_ABS_STACK_INDEX;
				pOperand->m_iStackIndex = iBaseIndex + iOffsetIndex;
			}
			else if ( IndexToken == TASM_TOKEN_TYPE_IDENT )
			{
				// It's an identifier, so save the current lexeme
				char * pstrIndexIdent = GetCurrLexeme ();
				
				// Make sure the index is a valid array index, in
				// that the identifier represents a single variable
				// as opposed to another array
				if ( ! FindSymbol ( pstrIndexIdent, m_iCurrFuncIndex ) )
				{
					AddCodeError ( ERROR_ASMMSG_UNDEFINED_IDENT );
				}
				
				if ( GetSize ( pstrIndexIdent, m_iCurrFuncIndex ) > 1 )
				{
					AddCodeError ( ERROR_ASMMSG_INVALID_ARRAY_INDEX );
				}
				
				// Get the variable's stack index and set the operand
				// type to relative stack index
				int iOffsetIndex = GetStackIndex ( pstrIndexIdent, m_iCurrFuncIndex );
				
				pOperand->m_nType = OPERAND_TYPE_REL_STACK_INDEX;
				pOperand->m_iStackIndex = iBaseIndex;
				pOperand->m_iOffsetIndex = iOffsetIndex;
			}
			else
			{
				// Whatever it is, it's invalid
				AddCodeError ( ERROR_ASMMSG_INVALID_ARRAY_INDEX );
			}
			
			// Lastly, make sure the closing brace is present as well
			if ( GetNextToken () != TASM_TOKEN_TYPE_CLOSE_BRACKET )
				AddCharExpectedError ( '[' );
		}//end if ( GetLookAheadChar () != '[' )
	}
	
	// Parse a line label
	if ( CurrOpTypes & OPERAND_FLAG_TYPE_LINE_LABEL )
	{
		// Get the current lexeme, which is the line label
		char * pstrLabelIdent = GetCurrLexeme ();
		
		// Use the label identifier to get the label's information
		CLabelNode *pLabel = FindLabel ( pstrLabelIdent, m_iCurrFuncIndex );
		pOperand->m_nType = OPERAND_TYPE_INSTRUCT_INDEX;
		
		// Make sure the label exists
		if ( ! pLabel )
		{
			AddCodeError ( ERROR_ASMMSG_UNDEFINED_LINE_LABEL );
		}
		else
		{
			pOperand->m_iInstructIndex = pLabel->m_iTargetIndex;
		}
		// Set the operand type to instruction index and set the
		// data field
	}
	
	// Parse a function name
	if ( CurrOpTypes & OPERAND_FLAG_TYPE_FUNC_NAME )
	{
		// Get the current lexeme, which is the function name
		char * pstrFuncName = GetCurrLexeme ();
		
		// Use the function name to get the function's information
		CFunction * pFunc = GetFuncByName ( pstrFuncName );
		
		// Make sure the function exists
		if ( ! pFunc )
		{
			AddCodeError ( ERROR_ASMMSG_UNDEFINED_FUNC );
		}
		else
		{
			// Set the operand type to function index and set its data
			// field
			pOperand->m_nType = OPERAND_TYPE_FUNC_INDEX;
			pOperand->m_iFuncIndex = pFunc->m_iIndex;
		}
	}
	
	// Parse a host API call
	if ( CurrOpTypes & OPERAND_FLAG_TYPE_HOST_API_CALL )
	{
		// Get the current lexeme, which is the host API call
		char *pstrHostAPICall = GetCurrLexeme ();
		
		// Add the call to the table, or get the index of the
		// existing copy
		int iIndex = m_oHostAPICallTable.Add(pstrHostAPICall);//AddString ( & g_HostAPICallTable, pstrHostAPICall );
		
		// Set the operand type to host API call index and set its
		// data field
		pOperand->m_nType = OPERAND_TYPE_HOST_API_CALL_INDEX;
		pOperand->m_iHostAPICallIndex = iIndex;
	}
}

void CTAsmParser::Assemble_SecondPass()
{
	// Set the current function's flags and variables
	m_iIsFuncActive = FALSE;
	m_pCurrFuncTemp = NULL;
	m_iCurrFuncIndex;
	m_iCurrFuncParamCount = 0;
	m_iCurrFuncLocalDataSize = 0;
	
	// Create an instruction definition structure to hold instruction information when
	// dealing with instructions.
	CTInstruct *pInstSrc = NULL;
	
	m_oInstructions.m_nInstructs = m_iInstructStreamSize;
	m_oInstructions.Create();
	
	// Set the current instruction index to zero
	m_iCurrInstructIndex = 0;
	
	// ---- Perform the second pass over the source
	// Reset the lexer so we begin at the top of the source again
	m_oLexer.ResetLexer();
	
	// Loop through each line of code
	while ( TRUE )
	{
		// Get the next token and make sure we aren't at the end of the stream
		if ( GetNextToken () == END_OF_TASM_TOKEN_STREAM )
			break;
		
		// Check the initial token
		switch ( m_oLexer.m_CurrToken )
		{
		case TASM_TOKEN_TYPE_FUNC:// Func
			Assemble_SecondPass_Func();
			break;
		case TASM_TOKEN_TYPE_CLOSE_BRACE:// Closing brace
			Assemble_SecondPass_ClosingBrace();
			break;
		case TASM_TOKEN_TYPE_PARAM: // Param
			Assemble_SecondPass_Param();
			break;
		case TASM_TOKEN_TYPE_INSTRUCT:// Instructions
			Assemble_SecondPass_Instruction();
			break;
		}
		
		// Skip to the next line
		if ( ! SkipToNextLine () )
			break;
    }	
}


void CTAsmParser::Assemble ()
{
	// ---- Initialize the script header
	m_oScriptHeader.m_iStackSize = 0;
	m_oScriptHeader.m_iIsMainFuncPresent = FALSE;
	
	// ---- Set some initial variables
	m_iInstructStreamSize = 0;
	m_iIsSetStackSizeFound = FALSE;
	m_oScriptHeader.m_iGlobalDataSize = 0;
	
	Assemble_FirstPass();

	Assemble_SecondPass();
}

void CTAsmParser::BuildTSE(const CString &strFile)
{
	InitSourceCodeLines();
	Assemble();
	
	if (m_oTSyntaxs.GetCount() == 0)
	{
		Write(strFile);
	}
}

void CTAsmParser::BuildTSE()
{
	InitSourceCodeLines();
	Assemble();
	
	if (m_oTSyntaxs.GetCount() == 0)
	{
		//Write(strFile);
	}
}

Token CTAsmParser::GetNextToken (BOOL bCanSkipToNextLine)
{	// ---- Lexeme Extraction
	char *pstrSourceCode = m_ppstrSourceCode [ m_oLexer.m_iCurrSourceLine ];
	unsigned int nStringLen = strlen(pstrSourceCode);
	
	// Move the first index (Index0) past the end of the last token, which is marked
	// by the second index (Index1).	
	m_oLexer.m_iIndex0 = m_oLexer.m_iIndex1;
	
	// Make sure we aren't past the end of the current line. If a string is 8 characters long,
	// it's indexed from 0 to 7; therefore, indices 8 and beyond lie outside of the string and
	// require us to move to the next line. This is why I use >= for the comparison rather
	// than >. The value returned by strlen () is always one greater than the last valid
	// character index.
	
	if ( m_oLexer.m_iIndex0 >= nStringLen )
	{
		// If so, skip to the next line but make sure we don't go past the end of the file.
		// SkipToNextLine () will return FALSE if we hit the end of the file, which is
		// the end of the token stream.

		if (bCanSkipToNextLine)
		{
			if ( ! SkipToNextLine () )
			{
				return END_OF_TASM_TOKEN_STREAM;
			}
			else
			{
			}
			
			pstrSourceCode = m_ppstrSourceCode [ m_oLexer.m_iCurrSourceLine ];
			nStringLen = strlen(pstrSourceCode);
		}
		else
		{
		}
	}
	else
	{
	}

	// If we just ended a string, tell the lexer to stop lexing
	// strings and return to the normal state
	if ( m_oLexer.m_iCurrLexState == LEX_STATE_END_STRING )
		m_oLexer.m_iCurrLexState = LEX_STATE_NO_STRING;
	
	// Scan through the potential whitespace preceding the next lexeme, but ONLY if we're
	// not currently parsing a string lexeme (since strings can contain arbitrary whitespace
	// which must be preserved).
	if ( m_oLexer.m_iCurrLexState != LEX_STATE_IN_STRING )
	{
		// Scan through the whitespace and check for the end of the line
		SkipWitespace(pstrSourceCode, m_oLexer.m_iIndex0);
	}
	
	// Bring the second index (Index1) to the lexeme's starting character, which is marked by
	// the first index (Index0)
	m_oLexer.m_iIndex1 = m_oLexer.m_iIndex0;
	
	// Scan through the lexeme until a delimiter is hit, incrementing Index1 each time
	while ( TRUE )
	{
		if ( m_oLexer.m_iCurrLexState == LEX_STATE_IN_STRING )
		{// Are we currently scanning through a string?
			// If we're at the end of the line, return an invalid token since the string has no
			// ending double-quote on the line
			if ( m_oLexer.m_iIndex1 >= nStringLen )
			{
				m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_INVALID;
				return m_oLexer.m_CurrToken;
			}
			
			// If the current character is a backslash, move ahead two characters to skip the
			// escape sequence and jump to the next iteration of the loop
			if ( pstrSourceCode[ m_oLexer.m_iIndex1 ] == '\\' )
			{
				m_oLexer.m_iIndex1 += 2;
				continue;
			}
			
			// If the current character isn't a double-quote, move to the next, otherwise exit
			// the loop, because the string has ended.
			if ( pstrSourceCode[ m_oLexer.m_iIndex1 ] == '"' )
				break;
			
			++ m_oLexer.m_iIndex1;
		}
		else
		{	// We are not currently scanning through a string
			// If we're at the end of the line, the lexeme has ended so exit the loop
			if ( m_oLexer.m_iIndex1 >= nStringLen )
				break;
			
			// If the current character isn't a delimiter, move to the next, otherwise exit the loop
			if ( IsCharDelimiter ( pstrSourceCode[ m_oLexer.m_iIndex1 ] ) )
				break;
			
			++ m_oLexer.m_iIndex1;
		}
	}
	
	// Single-character lexemes will appear to be zero characters at this point (since Index1
	// will equal Index0), so move Index1 over by one to give it some noticable width
	if ( m_oLexer.m_iIndex1 == m_oLexer.m_iIndex0)
	{
		++ m_oLexer.m_iIndex1;
	}
	
	// The lexeme has been isolated and lies between Index0 and Index1 (inclusive), so make a local
	// copy for the lexer
	unsigned int iCurrDestIndex = 0;
	for ( unsigned int iCurrSourceIndex = m_oLexer.m_iIndex0; iCurrSourceIndex < m_oLexer.m_iIndex1; ++ iCurrSourceIndex )
	{
		// If we're parsing a string, check for escape sequences and just copy the character after
		// the backslash
		if ( m_oLexer.m_iCurrLexState == LEX_STATE_IN_STRING )
		{
			if ( pstrSourceCode[ iCurrSourceIndex ] == '\\' )
			{
				++ iCurrSourceIndex;
			}
		}
		
		// Copy the character from the source line to the lexeme
		m_oLexer.m_pstrCurrLexeme [ iCurrDestIndex ] = pstrSourceCode[ iCurrSourceIndex ];
		
		// Advance the destination index
		++ iCurrDestIndex;
	}
	
	// Set the null terminator
	m_oLexer.m_pstrCurrLexeme [ iCurrDestIndex ] = '\0';
	
	// Convert it to uppercase if it's not a string
	if ( m_oLexer.m_iCurrLexState != LEX_STATE_IN_STRING )
	{
		strcpy(m_oLexer.m_pstrCurrLexemeOrigin, m_oLexer.m_pstrCurrLexeme);
		//strupr ( m_oLexer.m_pstrCurrLexeme );
	}
	
	// ---- Token Identification
	// Let's find out what sort of token our new lexeme is
	// We'll set the type to invalid now just in case the lexer doesn't match any
	// token types
	m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_INVALID;
	unsigned int nCurrLexemeLen = strlen(m_oLexer.m_pstrCurrLexeme);
	
	// The first case is the easiest-- if the string lexeme state is active, we know we're
	// dealing with a string token. However, if the string is the double-quote sign, it
	// means we've read an empty string and should return a double-quote instead
	if ( nCurrLexemeLen > 1 || m_oLexer.m_pstrCurrLexeme [ 0 ] != '"' )
	{
		if ( m_oLexer.m_iCurrLexState == LEX_STATE_IN_STRING )
		{
			m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_STRING;
			return TASM_TOKEN_TYPE_STRING;
		}
	}
	
	// Now let's check for the single-character tokens
	if ( nCurrLexemeLen == 1 )
	{
		switch ( m_oLexer.m_pstrCurrLexeme [ 0 ] )
		{
		case '"':// Double-Quote
			{
				// If a quote is read, advance the lexing state so that strings are lexed
				// properly
				switch ( m_oLexer.m_iCurrLexState )
				{
					// If we're not lexing strings, tell the lexer we're now
					// in a string
				case LEX_STATE_NO_STRING:
					m_oLexer.m_iCurrLexState = LEX_STATE_IN_STRING;
					break;
					// If we're in a string, tell the lexer we just ended a string
				case LEX_STATE_IN_STRING:
					m_oLexer.m_iCurrLexState = LEX_STATE_END_STRING;
					break;
				}
				m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_QUOTE;
			}
			break;

		case ',':// Comma
			m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_COMMA;
			break;
		case ':':// Colon
			m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_COLON;
			break;
		case '[':// Opening Bracket
			m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_OPEN_BRACKET;
			break;
		case ']':// Closing Bracket
			m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_CLOSE_BRACKET;
			break;
		case KEY_OPEN_BRACE:// Opening Brace
			m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_OPEN_BRACE;
			break;
		case KEY_CLOSE_BRACE:// Closing Brace
			m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_CLOSE_BRACE;
			break;
		case '\n':// Newline
		case '\0':
			m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_NEWLINE;
			break;
		}

		//return if token success
		if (m_oLexer.m_CurrToken != TASM_TOKEN_TYPE_INVALID)
		{
			return m_oLexer.m_CurrToken;
		}
	}
	
	// Now let's check for the multi-character tokens
	
	if ( IsStringInteger ( m_oLexer.m_pstrCurrLexeme ) )
	{// Is it an integer?
		m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_INT;
	}
	else if ( IsStringFloat ( m_oLexer.m_pstrCurrLexeme ) )
	{// Is it a float?
		m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_FLOAT;
	}
	else if ( stricmp ( m_oLexer.m_pstrCurrLexeme, KEY_SETSTACKSIZE ) == 0 )
	{// Is it SetStackSize?
		m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_SETSTACKSIZE;
	}
	else if ( stricmp ( m_oLexer.m_pstrCurrLexeme, KEY_SETPRIORITY ) == 0 )
	{// Is it SetStackSize?
		m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_SETPRIORITY;
	}
	else if ( stricmp ( m_oLexer.m_pstrCurrLexeme, KEY_VAR ) == 0 )
	{// Is it Var/Var []?
		m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_VAR;
	}
	else if ( stricmp ( m_oLexer.m_pstrCurrLexeme, KEY_FUNC ) == 0 )
	{// Is it Func?
		m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_FUNC;
	}
	else if ( stricmp ( m_oLexer.m_pstrCurrLexeme, KEY_PARAM ) == 0 )
	{// Is it Param?
		m_oLexer.m_CurrToken =TASM_TOKEN_TYPE_PARAM;
	}
	else if ( stricmp ( m_oLexer.m_pstrCurrLexeme, KEY__RETVAL ) == 0 )
	{// Is it _RetVal?
		m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_REG_RETVAL;
	}
	else if ( stricmp ( m_oLexer.m_pstrCurrLexeme, KEY_EXPORT ) == 0 )
	{// Is it export?
		m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_EXPORT;
	}
	else if ( CTAsmInstructs::IsInstructExist ( m_oLexer.m_pstrCurrLexeme) )
	{// Is it an instruction?
		m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_INSTRUCT;
	}
	else if ( IsStringIdent ( m_oLexer.m_pstrCurrLexeme ) )
	{// Is it an identifier (which may also be a line label or instruction)?
		m_oLexer.m_CurrToken = TASM_TOKEN_TYPE_IDENT;
	}
	else
	{
	}
	
	return m_oLexer.m_CurrToken;
}


char CTAsmParser::GetLookAheadChar ()
{
	int iCurrSourceLine = m_oLexer.m_iCurrSourceLine;
	unsigned int iIndex = m_oLexer.m_iIndex1;
	unsigned int iSourceCodeLen = strlen ( m_ppstrSourceCode [ iCurrSourceLine ] );
	
	// If the next lexeme is not a string, scan past any potential leading whitespace
	if ( m_oLexer.m_iCurrLexState != LEX_STATE_IN_STRING )
	{
		// Scan through the whitespace and check for the end of the line
		while ( TRUE )
		{
			// If we've passed the end of the line, skip to the next line and reset the
			// index to zero
			if ( iIndex >= iSourceCodeLen )
			{
				// Increment the source code index
				iCurrSourceLine += 1;
				
				// If we've passed the end of the source file, just return a null character
				if ( iCurrSourceLine >= m_iSourceCodeLines )
					return 0;
				
				// Otherwise, reset the index to the first character on the new line
				iIndex = 0;
			}
			
			// If the current character is not whitespace, return it, since it's the first
			// character of the next lexeme and is thus the look-ahead
			if ( ! IsCharWhitespace ( m_ppstrSourceCode [ iCurrSourceLine ][ iIndex ] ) )
				break;
			
			// It is whitespace, however, so move to the next character and continue scanning
			++ iIndex;
		}
	}
	
	// Return whatever character the loop left iIndex at
	return m_ppstrSourceCode [ iCurrSourceLine ][ iIndex ];
}

int CTAsmParser::SkipToNextLine ()
{
	// Increment the current line
	++ m_oLexer.m_iCurrSourceLine;

	// Return FALSE if we've gone past the end of the source code
	if ( m_oLexer.m_iCurrSourceLine >= m_iSourceCodeLines )
		return FALSE;
	
	while (*m_ppstrSourceCode[m_oLexer.m_iCurrSourceLine] == 0)
	{
		++ m_oLexer.m_iCurrSourceLine;

		// Return FALSE if we've gone past the end of the source code
		if ( m_oLexer.m_iCurrSourceLine >= m_iSourceCodeLines )
			return FALSE;
	}

	// Return FALSE if we've gone past the end of the source code
	if ( m_oLexer.m_iCurrSourceLine >= m_iSourceCodeLines )
		return FALSE;
	
	// Set both indices to point to the start of the string
	m_oLexer.m_iIndex0 = 0;
	m_oLexer.m_iIndex1 = 0;
	
	// Turn off string lexeme mode, since strings can't span multiple lines
	m_oLexer.m_iCurrLexState = LEX_STATE_NO_STRING;
	
	// Return TRUE to indicate success
	return TRUE;
}


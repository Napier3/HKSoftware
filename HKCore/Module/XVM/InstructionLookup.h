// InstructionLookup.h: interface for the CInstructionLookup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INSTRUCTIONLOOKUP_H__946FBA9F_532D_47A1_9938_AAB7D9906DD7__INCLUDED_)
#define AFX_INSTRUCTIONLOOKUP_H__946FBA9F_532D_47A1_9938_AAB7D9906DD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../BaseClass/TLinkList.h"
#include "TAsmGlobal.h"


class  CTInstruct                     // An instruction lookup
{
public:
	char m_pstrInstruct[MAX_INSTRUCT_MNEMONIC_SIZE];  // Mnemonic string
	unsigned short m_nOpcode;                                // Opcode
	unsigned char  m_nOpCount;                               // Number of operands
	OperandTypes *m_OpList;                           // Pointer to operand list

	CTInstruct()
	{
		memset(m_pstrInstruct, 0, MAX_INSTRUCT_MNEMONIC_SIZE*sizeof(char));
		m_nOpcode = 0;
		m_nOpCount = NULL;
		m_OpList = NULL;
	}

	virtual ~CTInstruct()
	{
		if (m_OpList != NULL)
		{
			free(m_OpList);
			m_OpList = NULL;
		}
	}

	//Sets the operand type for the specified operand in the specified instruction.
	void SetOpType (int iOpIndex, OperandTypes iOpType )
	{
		m_OpList[ iOpIndex ] = iOpType;
	}

	void SetOpCount(int iOpCount)
	{
		m_nOpCount = iOpCount;

		if (m_nOpCount == 0)
		{
			return;
		}

		long nLen = iOpCount * sizeof ( OperandTypes );
		m_OpList = ( OperandTypes * ) malloc ( nLen );
		ZeroMemory(m_OpList, nLen);
	}
};


class CTInstructs
{
public:
	CTInstructs();
	virtual ~CTInstructs();

	long m_nInstructCount;
	CTInstruct* g_InstrTable[MAX_INSTRUCT_LOOKUP_COUNT];    // The master instruction

	CTInstruct* AddInstructLookup (const char *pstrMemonic, int iOpcode, int iOpCount );

protected:
	CTInstruct* In_Find(const char *pstrName);
	BOOL In_IsInstructExist (const char *pstrName);

};
#endif // !defined(AFX_INSTRUCTIONLOOKUP_H__946FBA9F_532D_47A1_9938_AAB7D9906DD7__INCLUDED_)

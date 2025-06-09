// AtlBaseObject.h: interface for the CAtlBaseObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ATLLISTDEF_H__)
#define _ATLLISTDEF_H__


struct __POS { };
typedef __POS* POS;

struct  CAtlPlex     // warning variable length structure
{
	CAtlPlex* pNext;
#if (_AFX_PACKING >= 8)
	DWORD dwReserved[1];    // align on 8 byte boundary
#endif
	// BYTE data[maxNum*elementSize];
	
	void* data() { return this+1; }
	
	static CAtlPlex* PASCAL Create(CAtlPlex*& head, UINT nMax, UINT cbElement);
	// like 'calloc' but no zero fill
	// may throw memory exceptions
	
	void FreeDataChain();       // free this one and links
};


#endif // !defined(_ATLLISTDEF_H__)

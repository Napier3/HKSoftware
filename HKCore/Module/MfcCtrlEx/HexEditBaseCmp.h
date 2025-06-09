#pragma once

#include "HexEditBase.h"
// CHexEditBaseCmp

class CHexEditBaseCmp
{
public:
	CHexEditBaseCmp(CHexEditBase *pHex1, CHexEditBase *pHex2);
	CHexEditBaseCmp();
	virtual ~CHexEditBaseCmp();

	void CmpHexEdit(CHexEditBase *pHex1, CHexEditBase *pHex2);
	
protected:
	CHexEditBase *m_pHex1;
	CHexEditBase *m_pHex2;

	void CmpHex(BYTE *pBuffer1, long nLength1, BYTE *pBuffer2, long nLength2);
	void CmpHex(BYTE *pBuffer1, BYTE *pBuffer2, long nLength);
	void AddCmpBlock(long nBegin, long nEnd);
};



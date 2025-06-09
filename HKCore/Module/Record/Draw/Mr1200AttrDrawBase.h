// Mr1200AttrDrawBase.h: interface for the CMr1200AttrDrawBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MR1200ATTRDRAWBASE_H__197DF21C_6C62_481D_BD0D_4691A40A5FD2__INCLUDED_)
#define AFX_MR1200ATTRDRAWBASE_H__197DF21C_6C62_481D_BD0D_4691A40A5FD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mr1200RecordDrawBase.h"//Mr1200DrawBase

class CMr1200AttrDrawBase : public CDrawMr1200RecordBase//CDrawMr1200Base  
{
public:
	CMr1200AttrDrawBase();
	virtual ~CMr1200AttrDrawBase();

	virtual BOOL CalCurrentDataPos(double dMax, double dMin);
	virtual void CalXPos(long nTotalPoints);
	
};

#endif // !defined(AFX_MR1200ATTRDRAWBASE_H__197DF21C_6C62_481D_BD0D_4691A40A5FD2__INCLUDED_)

#pragma once
#include "EpDeviceGlobal.h"

class CEpTag :public CExBaseObject
{
private:
#define EPDT_NULL		0
#define EPDT_UNSIGNEDCHAR		1
#define EPDT_SHORT		2
#define EPDT_LONG		3
#define EPDT_FLOAT		4
#define EPDT_DOUBLE		5
#define EPDT_INT		6
#define EPDT_STRING		7

public:
	CEpTag();
	virtual ~CEpTag();
	
	long vt;
	union 
	{
		unsigned char	*bVal;
		short	*nVal;
		long	*lVal; 
		float	*fltVal;
		double	*dblVal; 
		int	    *intVal;
		CString *pszString;
	};
public:
	virtual UINT GetClassID(){return EPDCLASSID_CEPTAG;};

public:

	CEpTag(unsigned char *val);
	CEpTag(short *val);
	CEpTag(long *val);
	CEpTag(float *val);
	CEpTag(double *val);
	CEpTag(int *val);
	CEpTag(CString *val);
	CEpTag(const CEpTag &val);

	void operator= (unsigned char *val);
	void operator= (short *val);
	void operator= (long *val);
	void operator= (float *val);
	void operator= (double *val);
	void operator= (int *val);
	void operator= (CString *val);
	void operator= (const CEpTag &val);
};

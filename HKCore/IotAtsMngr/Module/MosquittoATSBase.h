#pragma once

class CMosquittoATSBase : public CExBaseObject
{
public:
	long m_oIndex_Test;
	CExBaseList m_oDeviceList;

public:
	CMosquittoATSBase();
	virtual ~CMosquittoATSBase();

	void InitATSBase();
	void ExitATSBase();
};
// XTwoFlagCritical.h: interface for the XTwoFlagCritical class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XTwoFlagCritical_H__)
#define _XTwoFlagCritical_H__

class CXTwoFlagCritical
{
public:
	CXTwoFlagCritical( void );
	virtual ~CXTwoFlagCritical( void );

protected:
	BOOL m_bXValidate;  //�Ƿ���Ч�ı�־
	long m_nXOccupyRefCount;	//ռ�ü�����
	
public:
	void XOccupy()	{	m_nXOccupyRefCount++;	}
	void XFreeOccupy()	{	m_nXOccupyRefCount--;	}
	BOOL XWaitForNoOccupy(long nWiteTimeLong);
	
	BOOL XIsValidate()	{	return m_bXValidate;	}
	void XSetValidate(BOOL bValdate)	{	m_bXValidate = bValdate;	}
	BOOL XWaitForValidate(long nWiteTimeLong);
	
};

#endif // !defined(_XTwoFlagCritical_H__)

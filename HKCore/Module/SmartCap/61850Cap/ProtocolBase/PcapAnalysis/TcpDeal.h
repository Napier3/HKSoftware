#pragma once

class CTcpDeal
{
public:
	CTcpDeal(void);
	static CString GetValueFromByteArray(CByteArray &m_Array,int m_StartPos,int m_Length);
public:
	~CTcpDeal(void);
public:
	int deal(int d);
};

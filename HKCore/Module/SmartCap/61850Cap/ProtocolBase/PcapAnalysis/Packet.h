#pragma once
#include <vector>

class CPacket
{
public:
	~CPacket(void);
	CPacket(int nHead,  int nLength);
	CPacket(BYTE * pBuffer,  int nHead,  int nLength);

	void SetAbronamlType(int nType);

public:
	unsigned char * m_pBuffer;
	int m_nHeadStartPos;
	int m_nDataPackLength;
	int m_nAbnormalType;
	int m_nInvokeID;
	std::vector<int> m_AbnPosvector;
};

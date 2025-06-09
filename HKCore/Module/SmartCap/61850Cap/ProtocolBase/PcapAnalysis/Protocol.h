#pragma once
#include <vector>

class CProtocol
{
public:
	int m_headStartPos;
	int m_DataPackLength;
	int m_AbnormalType;
	int m_InvokeID;
	std::vector<int> m_AbnPosvector;
	CProtocol(int m_iHead,int m_iLength);
	void SetAbronamlType(int m_Type);
public:
	~CProtocol(void);
};

#pragma once
#include <vector>

class CTimeDifData
{
public:
	CTimeDifData(void);
	std::vector<int> m_DifDataVector;
	CString m_strMac;
	CString m_strAppID;
	int m_nPonitSize;
	int m_nASDUNum;
	int m_PreSecPointNum;
public:
	~CTimeDifData(void);
};

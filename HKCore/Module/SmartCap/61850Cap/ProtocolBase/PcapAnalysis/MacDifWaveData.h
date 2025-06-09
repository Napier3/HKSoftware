#pragma once
#include <vector>

class CMacDifWaveData
{
public:
	CMacDifWaveData(void);
public:
	~CMacDifWaveData(void);
	std::vector<CPoint *> p_WavePoint;
	std::vector<std::vector<int>> m_datavector;
	std::vector<CString> m_ChanDescVector;
	std::vector<int> m_UITypeVector;//0 延时：1 电压：2 电流：
	CPoint * pPoint;
	int m_WavetSize;
	int m_nPonitSize;
	std::vector<long>m_MaxValueVector;
	std::vector<float>m_FirstArcVector;
	CString m_strMac;
	CString m_AppID;
	std::vector<CPoint>m_WaveStartPosVector;
	int m_nASDUNum;
};

#ifndef CSTTCHARACTERDRAWPNG_H
#define CSTTCHARACTERDRAWPNG_H
#include "../../../../AutoTest/Module/Characteristic/SttCharacterDrawForTest.h"
#include "../../../../Module/QT/Png64/DrawPngBase64.h"

class CSttCharacterDrawPng : public CSttCharacterDrawForTest, public CDrawPngBase64
{
private:
	CXDrawList m_oSearchPoints;//整个特性曲线实际测得的点集合
	CXDrawList m_oCurSearchView;//特性曲线当前报文测试的线、点集合

public:
	CSttCharacterDrawPng();
	virtual ~CSttCharacterDrawPng();

private:
	void DrawSearchPoints(CDC *pDC);
	void DrawCurSearchView(CDC *pDC);
	void DrawCurTestPoint(CDC *pDC, CDataGroup* pSearchLine);
	void DrawCurLine(CDC *pDC, CDataGroup* pSearchLine);
	void DrawCurTestLine(CDC *pDC, CDataGroup* pSearchLine);
	double GetValueByID(CDataGroup* pSearchLine, const CString& strID);

public:
	void AddSearchPoint(double dx, double dy,BOOL bAct);//添加实际测得的点位
	void ClearSearchPoints_png(long nPtIndex = -1);
	void ClearSearchPointsFrom_png(long nPtIndex);
	void GetSearchPointsPng(CString& strBase64);//过程结束截图
	void GetSearchingPng(CDataGroup* pSearchLine, CString& strBase64);//过程中截图
	bool SavePngFile(const CString &strFilePath);//存储png文件

	//在此函数中,清除
	virtual void InitCharDrawTest(const CString &strCharID, long nIndex);
};

#endif//!CSTTCHARACTERDRAWPNG_H
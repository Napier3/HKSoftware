#ifndef CSTTCHARACTERDRAWPNG_H
#define CSTTCHARACTERDRAWPNG_H
#include "../../../../AutoTest/Module/Characteristic/SttCharacterDrawForTest.h"
#include "../../../../Module/QT/Png64/DrawPngBase64.h"

class CSttCharacterDrawPng : public CSttCharacterDrawForTest, public CDrawPngBase64
{
private:
	CXDrawList m_oSearchPoints;//������������ʵ�ʲ�õĵ㼯��
	CXDrawList m_oCurSearchView;//�������ߵ�ǰ���Ĳ��Ե��ߡ��㼯��

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
	void AddSearchPoint(double dx, double dy,BOOL bAct);//���ʵ�ʲ�õĵ�λ
	void ClearSearchPoints_png(long nPtIndex = -1);
	void ClearSearchPointsFrom_png(long nPtIndex);
	void GetSearchPointsPng(CString& strBase64);//���̽�����ͼ
	void GetSearchingPng(CDataGroup* pSearchLine, CString& strBase64);//�����н�ͼ
	bool SavePngFile(const CString &strFilePath);//�洢png�ļ�

	//�ڴ˺�����,���
	virtual void InitCharDrawTest(const CString &strCharID, long nIndex);
};

#endif//!CSTTCHARACTERDRAWPNG_H
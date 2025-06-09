#pragma once
#include "./PsuCharDrawView.h"
//#include "../../../../../Module/XDrawBase/XDrawTestPoint.h"
#include "./InternationalCharactInterface.h"

class CInternationalCharDrawView :public CPsuCharDrawView
{
public:
	CInternationalCharDrawView(void);
    virtual ~CInternationalCharDrawView(void);

	virtual void SetCurTestPoint(CXDrawPoint *pCurrTestPoint, BOOL bUpdateInstruct);
	virtual void ClearSearchPoints(long nPtIndex = -1);

	// ɾ�����Ե� / ��
	void DeleteTestData(const CString &strIDPath);
	//��Ӿ��뱣�������������Ӧ���Ե�,����1���ݵ�ǰ������·��,����2��3��Ӧ����ֵ���翹ֵ������4��Ӧ�������ͣ�����5��Ӧ����
	BOOL AddUpdateTestPoint_Imp(const CString &strIDPath, double dX, double dY, int nFaultType, int nZoneType, int nState = -1);
//	void AddUpdateTestPoint(const CString &strIDPath, double dX, double dY, int nFaultType, bool nState = -1);
    //20240821 wanmj ��Ӳ�����Ĳ����ߵ���������ͼ
    void AddUpdateTestLine_Imp(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nZoneType, int nState = -1);
	//���ݵ�ǰѡ�й���������ʾ��ͬ�������͵Ĳ��Ե�/��
	virtual void DrawAxisTestPoints(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	//ͬ�ڸ�������ѹ�����Ƶ�����,�������߽�����ʾ
	BOOL UpdateTestUI_Syn(CCharacteristics *pCharacteristics, double dX, double dY);
	CCharacterArea *GetElementLined_Syn(CCharacteristics *pCharacteristics, int nindex);
	//����Ƿ���ʾȫ����������,���������Ҫ���ݵ�ǰ������������͹���ֻ��ʾLN��LL��Ӧ������
	//BOOL m_bShowAllCharacts;	//�ƶ���CCharacterDrawView�� �������ø��������Ƿ�ʹ����ʾ���߻���ʾȫ������ 20240923 luozibing

    //20240829 wanmj
    virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd, BOOL bViewTestLines, BOOL bCalCharTemp);
	////20240919 luozibing ���غ��� �ж������Ƿ�ȫ����ʾ
	//virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);

    virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);

    //20240919 wanmj �����Ʋ����� ��¼��ʼ/�յ�����
    void SetTestLineBegin(const CPoint &point);
    void SetTestLineEnd(const CPoint &point);
    BOOL GetTestLineBegEndPos(double &dBegX, double &dBegY, double &dEndX, double &dEndY);
    void ClearTestLine();

    //20241011 wanmj ��ȡ/���������᷶Χ
    void GetAxisMinMax(double &dXmin, double &dYmin, double &dXmax, double &dYmax);
    void SetAxisMinMax(double dXmin, double dYmin, double dXmax, double dYmax);
	
	//add wangtao 20240918 ��Ӳ������, ���� �����ƶ�/г���ƶ� �������ߣ�����nDiffTestTypeѡ������һ���������
	BOOL AddUpdateTestLine(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nState = -1);
	//add wangtao 20240924	��Ӳ����ʱ����Ե�, ����nDiffTestType���ֱ����ƶ���ʾ
	BOOL AddUpdateTestPoint(const CString &strIDPath, double dX, double dY, int nFaultType, int nState = -1);
private:
    //20240919 wanmj �����Ʋ�����
    CXDrawLine m_oTestLineFromChar;
    double m_dBegX;
    double m_dBegY;
    double m_dEndX;
    double m_dEndY;

};

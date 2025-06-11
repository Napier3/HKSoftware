#pragma once
#include "../../../AutoTest/Module/Characteristic/CharacterDrawView.h"




class CPsuCharDrawView :public CCharacterDrawView
{
public:
	CPsuCharDrawView(void);
	virtual ~CPsuCharDrawView(void);

public:
	virtual void UI_OnMouseMove(UINT nFlags, CPoint point);
	virtual void UI_OnLButtonDblClk(UINT nFlags, CPoint point);

	void SetAxisInstruct_Point(const CPoint &point);//���µ�ǰ��Ľ�����ʾ

	void UI_ZoomIn();
	void UI_ZoomOut();

	void SetCurTestPoint(CXDrawPoint *pCurrTestPoint,BOOL bUpdateInstruct);
//	void SetTestPointLine(const double &dValueR,const double &dValueX);//�����������Ե��ֱ��

	CXDrawPoint* CreateNewTestPoint(const double &dR,const double &dX);//����һ���µĲ��Ե�
	void DeleteTestPoint(CXDrawPoint *pTestPoint);
	void GetAxisInterface(CAxisInterface **ppAxisInterface);

	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);
	virtual void AddTestResultPoint(double dX, double dY,BOOL bAct = TRUE);//��Ӳ��Խ����,����3����Ƿ���,������δ�������ò�ͬ����ɫ���
	virtual void ClearSearchPoints(long nPtIndex = -1);
	virtual long GetSearchPointsCount();
	virtual void CalVertHorzLine(long nIndex = 0, CString strType = CHAR_TESTLINE_MODE_ID_VERT);
	virtual void CalLinesPoints(long nIndex, CXDrawDatas* pDatas, CString strType);
    virtual void CalAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax);

	void SetXYUnitShow(CString strUnitMag,CString strUnitAng);
	void SetIsShowText(bool bIsShowText);
	void SetIsShowAng(bool bIsShowAng);
	void SetIsShowTestPoint(bool bIsShowTestPoint);
	void UpdateAxisType(const CString& strAxis,BOOL bLockXY);
	CXDrawLine* GetLeftButtonLine();

protected:
	virtual void InitCharDrawView(CCharacteristic *pCharTemp, CWnd *pParentWnd);
	//20230314 ����2����Ƿ��ʼ����������ɫ,����������,ϵͳ���û�,����ʱ,��������ɫ
	void InitDrawLineColor(const COLORREF &oColor);
	void InitDrawLineColor(const COLORREF &oLinesColor,const COLORREF &oTestLineColor_sys,const COLORREF &oTestLineColor_User);

//	virtual void SetAxisInstruct(const CString &strAxisInstruct1, const CString &strAxisInstruct2);//zhouhj 20210130 ������������������˵��������
	void DrawAxisInstruction(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));//zhouhj 20210203 ����ָʾ˵��
	void DrawCurrTestPointLine(CDC *pDC,float fZoomRatio,CPoint ptOffset);//���ƾ�������ԭ�㼰��ǰ���Ե��ֱ��

//	CXDrawLine *m_pCurrTestPointLine;

public:
	//2021-9-15  lijunqing
	//CXDrawList *m_pOtherDrawList;

	float m_fZoomCoef;
	XDRAWDATA_POINT m_oAxisInstruct_Point;//����������ʾ������ֵ    //sf �ⲿ���� 20211028

private:
	//��������˵����������ɫ,����
	LOGFONT   m_lfAxisInstruct_Font;		////˵������������
	COLORREF  m_crAxisInstructPoint_FontColor;//˵��:��ǰָʾ��������ɫ
	COLORREF  m_crAxisInstructInit_FontColor;//˵��:��ʼ���Ե�������ɫ
	COLORREF  m_crAxisInstructSelect_FontColor;//˵��:ѡ�в��Ե�������ɫ
	COLORREF  m_crAxisInstructEnd_FontColor;//˵��:����������Ե�������ɫ

	CString m_strUnitMag;//��ʾ�ĵ�λ 20211027 sf
	CString m_strUnitAng;
	bool m_bIsShowText;//���Ե��Ƿ���ʾ��־ 20211027 sf
	bool m_bIsShowAng;//�Ƿ�Ҫ���ѿ������껻��ɷ�ֵ����λ����ʾ
	bool m_bIsShowTestPoint;//dingxy 20250314 �Ƿ����ý����ʶ
// 	CString m_strInstruct1Text;
// 	CString m_strInstruct2Text;
	CString m_strInstructInit_Text;
	CString m_strInstructSelect_Text;
	CString m_strInstructEnd_Text;

	double	m_dInstructLeftGap;//˵������,�빤�������ľ���
	double	m_dInstructTopGap;//˵������,�빤���������ľ���
	double	m_dInstructSpaceGap;//˵������,�໥��Ĵ�ֱ���

	CXDrawList m_oCharDrawList;//����������صĲ��Ե㡢�����߻�ͼ����
	CXDrawList m_oTestPoints;//yizejun 2023-02-21 �����㼯��
	CXDrawLine m_oLeftButtonLine; //yizejun 2023-2-24 ��������Ӧ������
};

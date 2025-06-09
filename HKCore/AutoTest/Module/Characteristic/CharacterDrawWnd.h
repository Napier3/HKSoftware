#pragma once

#include "CharacteristicTmplate.h"
#include "CharacterDrawView.h"
// CCharacterDrawWnd

class CCharacterDrawWnd : public CStatic
{
	DECLARE_DYNAMIC(CCharacterDrawWnd)

public:
	CCharacterDrawWnd();
	virtual ~CCharacterDrawWnd();

protected:
	CCharacterDrawView *m_pCharacterDrawView;
	void CreateCharacterDrawView();

public:
	BOOL HasCharDrawCreated(CCharacteristic *pCharTemp);
	void InitCharacterDrawView(CCharacteristic *pCharTemp, BOOL bViewTestLines=TRUE, BOOL bCalCharTemp=TRUE);
	void InitCharacterDrawView(CCharacteristics *pChars, BOOL bViewTestLines=TRUE, BOOL bCalCharTemp=TRUE);
	void SetActiveElement(CCharElement *pElement, BOOL bRedraw=TRUE);

	void UpdateCurrTestPoint(double dX, double dY);
	void FreeCurrTestPoint();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};



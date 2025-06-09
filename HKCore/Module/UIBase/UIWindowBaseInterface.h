//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#include "UIBaseFont.h"

#pragma once

class CUIWindowBaseInterface
{
public:
	virtual BOOL IsWindowBase() = 0;
	virtual BOOL IsWindowList() = 0;
	virtual BOOL IsAncestorPageShow() = 0;
	
	//���ڷ���
	virtual void Show() = 0;
	virtual BOOL Show(long nShow) = 0;
	virtual void ShowChildren(long nShow) = 0;
	virtual BOOL IsShow() = 0;
	
	virtual void Enable(long nEnable, BOOL bEnableWindow=TRUE) = 0;
	virtual BOOL IsEnable() = 0;
	
	virtual void SetUIWndFocus(long xOff=5, long yOff=5) = 0;
	virtual void ReDrawWnd() = 0;
	virtual void SetWndText(CString strWndText) = 0;	
	virtual CString GetWndText() = 0;
	virtual CUIBaseFont* GetUIBaseFont() = 0;	
	
	
	//���ڵ�λ�ô�С
	virtual void SetWndHeight(long nHeight) = 0;
	virtual void SetWndWidth(long nWidth) = 0;
	virtual void SetWndWidthHeight(long nWidth, long nHeight) = 0;
	virtual void SetWndLeftTop(long nLeft, long nTop) = 0;
	virtual void SetWndPosition(long nLeft, long nTop, long nRight, long nBottom) = 0;
	virtual void SetWndPosition(CRect rcPos) = 0;
	virtual long GetWndHeight() = 0;
	virtual long GetWndWidth() = 0;
	virtual long GetWndLeft() = 0;
	virtual long GetWndTop() = 0;
	virtual long GetWndRight() = 0;
	virtual long GetWndBottom() = 0;
	virtual CRect GetWndPosition() = 0;
	virtual CPoint GetWndTopLeft() = 0;
	virtual CSize GetWndSize() = 0;
	
	//ϵͳ��Ϣ������
	//virtual long OnSystemMessage(UINT nSysMsgID, long &nImpCount, long &nRunCount) = 0;
	//virtual long OnSystemMessage(CSystemMessages *pSysMsgs, long &nImpCount, long &nRunCount) = 0;
	//virtual long OnChildrenSystemMessage(UINT nSysMsgID, long &nImpCount, long &nRunCount) = 0;

	//����/���ٷ���
	virtual BOOL UICreate(CWnd *pParent) = 0; //��ǰ׺��Ŀ����Ϊ��������CWnd�ĺ���Create
	virtual BOOL Destroy() = 0;
	virtual BOOL DestroyChildren() = 0;
	
	
		//�¼�����
	//virtual long OnSize();
	//virtual long OnShow();
	//virtual long OnHide();
	//virtual long OnInit();
	//virtual long UIOnDestroy();
	//virtual long OnPosChanged();

	//Timer�¼�����
	//virtual void UIOnTimer(UINT nTimerID);
	//virtual void UISetTimer(UINT nTimerID, UINT nTimerLong);

	//��ͼ����
	//virtual BOOL UIInvalidate();
	//virtual BOOL Draw();
	//virtual BOOL Draw(CDC *pDC);	
	
	static UINT  g_nWindowID;
	static UINT  GenerateWindowID()		{   g_nWindowID++;  return g_nWindowID;   }
	

};


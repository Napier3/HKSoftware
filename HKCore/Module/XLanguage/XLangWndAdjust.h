#pragma once

#include "XLanguageGlobal.h"
#include "../BaseClass/BaseList.h"
#include "XLanguageWndInterface.h"



class CXLangWndAdjBase : public CBaseObject
{
public:
	CXLangWndAdjBase();
	virtual ~CXLangWndAdjBase();

	//��ʼ�����Ե����ռ����
	void InitCXLangWndAdj(CXLanguageWndInterface *pWnd);
	void InitCXLangWndAdj(CWnd *pWnd);

protected:
	CXLanguageWndInterface *m_pXLangWnd;
	CWnd *m_pXLangWndRef;
	CRect m_rcOrigin;
	long  m_nWidthCal;
	long m_nWidthOrigin;

public:
	virtual UINT GetClassID() {        return LGUGCLASSID_WNDBASE;                               }

public:
	//����������
	virtual long AdjustCal();
	
	//����λ��
	virtual long Adjust(CWnd *pParent, long nOffset, CSize &szMax);
	
	//��ȡ��������Ŀ��
	virtual long Width()		{	return m_rcOrigin.Width();	}
	
	//��ȡ����λ�õ�ƫ��
	virtual long CalWidth()		{	return m_nWidthCal;			}
	virtual void ExpandColWidth(long nAdd)	{	m_nWidthCal += nAdd;	}
};

class CXLangWndAdjBaseList : public CXLangWndAdjBase, public CTLinkList<CXLangWndAdjBase>
{
public:
	CXLangWndAdjBaseList();
	virtual ~CXLangWndAdjBaseList();

public:
	CXLangWndAdjBase* AddNewChild(CXLangWndAdjBase *pNew);

public:
	//����λ��
	virtual long Adjust(CWnd *pParent, long nOffset, CSize &szMax);

	//��ȡ��������Ŀ��
	virtual long Width();

	//��õ�������ļ�����
	virtual long CalWidth();

	virtual long AdjustCal();

	//��ȡ����λ�õ�ƫ��
	virtual long GetOffset();
};


class CXLangWndAdjFrame;
class CXLangWndAdjCols;

class CXLangWndAdjCol : public CXLangWndAdjBaseList
{
public:
	CXLangWndAdjCol();
	virtual ~CXLangWndAdjCol();
	
public:
	virtual UINT GetClassID() {        return LGUGCLASSID_COL;                               }

public:
	//��ӿؼ�����
	CXLangWndAdjBase* RegisterWnd(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjBase* RegisterWnd(CWnd *pXLandWnd);

	//ע���ܴ��ڶ���
	CXLangWndAdjFrame* RegisterFrame(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjFrame* RegisterFrame(CWnd *pXLandWnd);
	
	virtual long Adjust(CWnd *pParent, long nOffset, CSize &szMax);
};

class CXLangWndAdjCols : public CXLangWndAdjBaseList
{
public:
	CXLangWndAdjCols();
	virtual ~CXLangWndAdjCols();
	
public:
	virtual UINT GetClassID() {        return LGUGCLASSID_COLS;                               }


public:
	//Ϊ�м������һ���ж���
	CXLangWndAdjCol* RegisterCol();

	//Ϊ��ǰ�ж���m_pCurrCol��ӿؼ�����
	//RegisterXWnd��RegisterWnd����һ�£��ڶԻ�������У��������CXLanguageTextWnd���󣬱������޷�ȷ��ʹ���ĸ�����
	CXLangWndAdjBase* RegisterXWnd(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjBase* RegisterWnd(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjBase* RegisterWnd(CWnd *pXLandWnd);

	//���õ�ǰm_pCurrCol��RegisterFrame
	CXLangWndAdjFrame* RegisterFrame(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjFrame* RegisterFrame(CWnd *pXLandWnd);
	
	virtual long Adjust(CWnd *pParent, CSize &szMax);

protected:
	CXLangWndAdjCol *m_pCurrCol;
	
};

//////////////////////////////////////////////////////////////////////////
//CXLangWndAdjFrame����ܶ���Ϊ�˸����ϵ����������Ӵ���
class CXLangWndAdjFrame : public CXLangWndAdjCols
{
public:
	CXLangWndAdjFrame();
	virtual ~CXLangWndAdjFrame();

public:
	virtual UINT GetClassID() {        return LGUGCLASSID_FRAME;                               }

public:
	//����ǰ������Frame��ԭʼ��С�͵�����Ĵ�С
	virtual long AdjustCal();

	//������ܶ���
	virtual long Adjust(CWnd *pParent, long nOffset, CSize &szMax);

	//Ϊ��ܶ���ע��ؼ���
	CXLangWndAdjBase* RegisterXCol(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjBase* RegisterColWnd(CWnd *pXLandWnd);

};

//////////////////////////////////////////////////////////////////////////
//CXLangWndAdjMngr:�����Կؼ���̬��������
class CXLangWndAdjMngr : public CBaseList
{
public:
	CXLangWndAdjMngr();
	virtual ~CXLangWndAdjMngr();
	void FreeAdjMngr();
	
public:
	virtual UINT GetClassID() {        return LGUGCLASSID_MNGR;                               }


public:
	CXLangWndAdjCols* RegisterCols();
// 	CXLangWndAdjBase* RegisterXCols(CXLanguageWndInterface *pXLandWnd);
// 	CXLangWndAdjBase* RegisterCols(CWnd *pXLandWnd);

	//ע��һ��
	CXLangWndAdjCol* RegisterCol();

	//ע��һ���ؼ��У�һ���ؼ�����һ��
	CXLangWndAdjBase* RegisterXCol(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjBase* RegisterCol(CWnd *pXLandWnd);

	//ע��ؼ�����ע�ᵽ��m_pCurrCols->m_pCurrCol
	CXLangWndAdjBase* RegisterXWnd(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjBase* RegisterWnd(CWnd *pXLandWnd);

	//���õ�ǰm_pCurrCols��RegisterFrame
	CXLangWndAdjFrame* RegisterXFrame(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjFrame* RegisterFrame(CWnd *pXLandWnd);

	//����λ�ã�����ǶԻ�����̬�����Ի����λ��
	void Adjust(CWnd *pParent, BOOL bDialog);
	
protected:
	CXLangWndAdjCols *m_pCurrCols;
	//CXLangWndAdjCol  *m_pCurrCol;
	
};

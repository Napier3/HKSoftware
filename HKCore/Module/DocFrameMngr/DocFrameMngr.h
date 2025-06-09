#pragma once

#include "../BaseClass/ExBaseList.h"

class CDocFrameObject : public CExBaseObject
{
public:
	CDocFrameObject(CMultiDocTemplate *pDocTempRef, CMDIChildWndEx *pFrameRef, CDocument *pDocRef, const CString &strName, const CString &strID);
	virtual ~CDocFrameObject();

	BOOL IsDataClassID(UINT nClassID);
public:
	CMultiDocTemplate *m_pDocTempRef;
	CMDIChildWndEx    *m_pFrameRef;
	CDocument         *m_pDocRef;
	CExBaseObject     *m_pDataRef;

private:
	CDocFrameObject()	{}
};


class CDocFrameMngr :public CExBaseList
{
private:
	CDocFrameMngr(void);
	virtual ~CDocFrameMngr(void);

	static CDocFrameMngr *g_pDocFrameMngr;
	static long g_nDocFrameMngrRef;

public:
	static CDocFrameMngr* Create();
	static void Release();
	static CDocFrameMngr* GetDocFrameMngr();

public:
	static CDocFrameObject* AddDocFrame(CMultiDocTemplate *pDocTempRef, CMDIChildWndEx *pFrameRef, CDocument *pDocRef, const CString &strName, const CString &strID, CExBaseObject *pDataRef = NULL);
	static void CloseFrame(CMDIChildWndEx *pFrameRef, BOOL bCloseFrame=FALSE);
	static void CloseFrameEx(CExBaseObject *pDataRef, BOOL bCloseFrame=TRUE);
	static void CloseDocFrame(const CString &strID);
	static void CloseDocFrame(CDocFrameObject *pDocFrameObject);  //2020-10-13  lijunqing
	static CDocFrameObject* FindDocFrameObject(const CString &strID);
	static CDocFrameObject* FindDocFrameObject(CExBaseObject *pDataRef);
	static CDocFrameObject* FindDocFrameObject(CExBaseObject *pDataRef, CDocTemplate *pTemplate);
	static CDocFrameObject* FindDocFrameObject(CDocument *pDoc);
	static CDocFrameObject* FindDocFrameObject(CMDIChildWndEx *pFrame);
	static CDocFrameObject* FindDocFrameObject_Has(const CString &strID);
	static long GetDocFrameCount();
	static CDocFrameObject* GetDocFrame(long nIndex);

	//20180914 lijq
	static CMDIChildWndEx* FindDocFrame(const CString &strID);
	static CMDIChildWndEx* FindDocFrame(CExBaseObject *pDataRef);
	static CMDIChildWndEx* FindDocFrame(CExBaseObject *pDataRef, CDocTemplate *pTemplate);
	static CMDIChildWndEx* FindDocFrame(CDocument *pDoc);
	static CMDIChildWndEx* FindDocFrame_Has(const CString &strID);

	//2020-10-13 lijq
	static CExBaseObject* FindRefData(CMDIChildWndEx *pFrame);

	//2021-7-19 shaolei
	static void CloseAllFrame();
};

CDocument* docfrm_OpenDocTemplate(CMultiDocTemplate *pDocTemplate, CView **pView, CMDIChildWndEx **pFrame, const CString &strFile=_T(""));
CDocument* docfrm_OpenDocTemplateEx(CExBaseObject *pDataRef, CMultiDocTemplate *pDocTemplate, CView **pView, CMDIChildWndEx **pFrame, const CString &strFile=_T(""));
CDocument* docfrm_OpenDocTemplateEx(CDocFrameObject **ppDocFrmObj, CMultiDocTemplate *pDocTemplate, CView **pView, CMDIChildWndEx **pFrame, const CString &strFile=_T(""));

CDocument* docfrm_OpenDocTemplate(CMultiDocTemplate *pDocTemplate, CExBaseObject *pDataRef);

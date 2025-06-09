// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// AutoTestDoc.h : CAutoTestDoc ��Ľӿ�
//

#include "..\XLanguageResourceAts_AutoTest.h"
#include "../GuideBook/ReportMap/RptFillInterface.h"
#include "..\UITestItem\GuideBookTreeCtrl.h"
#include "../TestControl\TestControl.h"
#include "../TestControl\TestControlOffline.h"

#pragma once


class CAutoTestBaseDoc : public CDocument
{
protected: // �������л�����
	CAutoTestBaseDoc();
	DECLARE_DYNCREATE(CAutoTestBaseDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
	virtual void SetTitle(LPCTSTR lpszTitle);

// ʵ��
public:
	virtual ~CAutoTestBaseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

};



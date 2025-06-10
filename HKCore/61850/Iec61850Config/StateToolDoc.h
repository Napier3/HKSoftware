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

// StateToolDoc.h : CStateToolDoc ��Ľӿ�
//


#pragma once


class CStateToolDoc : public CDocument
{
protected: // �������л�����
	CStateToolDoc();
	DECLARE_DYNCREATE(CStateToolDoc)

// ����
public:
	CIecCfgFile *m_pIecCfgFile;

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void SetTitle(LPCTSTR lpszTitle);


// ʵ��
public:
	virtual ~CStateToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileSave();
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);

	afx_msg void OnFileSaveAT02D();//�ܺ�� 20200616  ����AT02����
	afx_msg void OnUpdateFileSaveAT02D(CCmdUI *pCmdUI);
	afx_msg void OnFileSaveAsAT02D();
	afx_msg void OnUpdateFileSaveAsAT02D(CCmdUI *pCmdUI);
};



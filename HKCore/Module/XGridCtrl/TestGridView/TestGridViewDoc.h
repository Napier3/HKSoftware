
// TestGridViewDoc.h : CTestGridViewDoc ��Ľӿ�
//


#pragma once


class CTestGridViewDoc : public CDocument
{
protected: // �������л�����
	CTestGridViewDoc();
	DECLARE_DYNCREATE(CTestGridViewDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CTestGridViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};




// iSmartTestNewTestDoc.h : CiSmartTestNewTestDoc ��Ľӿ�
//

#pragma once

class CEdgeMqttServerDoc : public CDocument
{
protected: // �������л�����
	CEdgeMqttServerDoc();
	DECLARE_DYNCREATE(CEdgeMqttServerDoc)

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
	virtual ~CEdgeMqttServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};




// StationTestMainDoc.h : CStationTestMainDoc ��Ľӿ�
//


#pragma once


class CStationTestGraphDoc : public CDocument
{
protected: // �������л�����
	CStationTestGraphDoc();
	DECLARE_DYNCREATE(CStationTestGraphDoc)

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
	virtual ~CStationTestGraphDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};



#pragma once

#define PX_PKG_STATE_NOT_PROCESSED			0	//δ����ı���
#define PX_PKG_STATE_PROCESSED_MATCH		1	//�ڴ�Ӧ��
#define PX_PKG_STATE_PROCESSED_NOTMATCH		2	//δ�ҵ������ڵ��������
#define PX_PKG_STATE_CAN_DELETE				3	//Ӧ���ģ����̽�������ɾ����־
#define PX_PKG_STATE_ERROR			        4	//����ı��ģ�ֻ���滺��

class CPxPkgBase:public CExBaseList
{
public:
	CPxPkgBase();
	virtual ~CPxPkgBase();

public:
	__int64 m_n64Time;
	LPVOID m_pBuffer;//ָ������Ϣ

	long m_nCmdType;
	CString m_strCmdID;

	CExBaseList m_listDatas;//�����ı�����Ϣ�б��ݲ�����
	CExBaseList *m_pRefDataset;//���Ĺ��������ݼ�

public:
	void SetPkgState(long nPkgState){m_nPkgState = nPkgState;}
	BOOL IsPkgState_NotProcessed(){return m_nPkgState == PX_PKG_STATE_NOT_PROCESSED;}
	BOOL IsPkgState_Processed_Match(){return m_nPkgState == PX_PKG_STATE_PROCESSED_MATCH;}
	BOOL IsPkgState_Processed_NotMatch(){return m_nPkgState == PX_PKG_STATE_PROCESSED_NOTMATCH;}
	BOOL IsPkgState_HasProcessed(){return (IsPkgState_Processed_Match() || IsPkgState_Processed_NotMatch());}
	BOOL IsPkgState_CanDelete(){return m_nPkgState == PX_PKG_STATE_CAN_DELETE;}

	SYSTEMTIME m_tmPkg;			//���ձ��ĵ�ʱ��
	long m_nPkgState;			//���Ĵ���״̬
};
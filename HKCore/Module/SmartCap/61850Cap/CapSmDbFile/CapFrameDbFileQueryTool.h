//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CCapFrameDbFileQueryTool.h  CCapFrameDbFileQueryTool

#pragma once

#include "CapFrameDbFile.h"
#include "..\..\..\WinPcap\Include\File_Pcap.h"

//xujinqiang20200622add��������ʷ���ĵĹ�����
class CCapFrameDbFileQueryTool
{
public:
	CCapFrameDbFileQueryTool();
	~CCapFrameDbFileQueryTool();

public:
	__int64 m_nBeginPos;
	__int64 m_nEndPos;

public:
	void SetBeginEndPos(__int64 nBeginPos, __int64 nEndPos, BOOL bShowGrid=TRUE);

	BOOL GetShowGrid() { return m_bShowGrid; }

	CCapFrameDbArea *GetCapFrameDbArea() { return m_pCapFrameDbArea; }
	void SetCapFrameDbArea(CCapFrameDbArea *pCapFrameDbArea) { m_pCapFrameDbArea = pCapFrameDbArea; }

	CCapFrameIndexDbArea *CreateCapFrameIndexDbArea();
	CCapFrameIndexDbArea *GetCapFrameIndexDbArea() { return m_pCapFrameIndexDbArea; }
	void SetCapFrameIndexDbArea(CCapFrameIndexDbArea *pCapFrameIndexDbArea) { m_pCapFrameIndexDbArea = pCapFrameIndexDbArea; }

	BOOL CanClickLastPage(){ return m_nQueryCapFrameCurrPage>1; }
	BOOL CanClickNextPage(){ return m_nQueryCapFrameMaxPage>m_nQueryCapFrameCurrPage; }
	BOOL CanClickExportPcap(){ return m_nEndPos>m_nBeginPos; }
	BOOL CanDoQueryOptr();

	void GetPageBeginEndPos(long nPage, __int64 &nBeginPos, __int64 &nEndPos); //��ȡָ��ҳ�����ʼ��ֹ��
	__int64 GetPageLength(long nPage); //��ȡָ��ҳ������ݳ���
	void QueryPageCapFrame(long nPage); //��ȡָ��ҳ�������

	BOOL PopSaveAsPcapFileDlg(CString &strExportFile);
	void ExportAllPagePcap(const CString &strFile); //��������ҳ�������
	void ExportAllPagePcap(); //��������ҳ�������
	void ExportOnePagePcap(long nPage); //����ָ��ҳ�������
	void ExportOnePagePcap(long nPage, const CString &strExportFile);
	void CapoptrExportAT02D(); //����AT02D����

	//xujinqiang20200705add������ָ��ʱ�������ץȡ�ı��ĵ�pcap��ʽ
	BOOL Query(SYSTEMTIME tmBegin, SYSTEMTIME tmEnd);
	BOOL ExportPcap(SYSTEMTIME tmBegin, SYSTEMTIME tmEnd);
	BOOL ExportPcap(SYSTEMTIME tmBegin, SYSTEMTIME tmEnd, const CString &strExportFile);
	BOOL ExportPcap(const CString &strTmBegin, const CString &strTmEnd, const CString &strExportFile);

private:
	CCapFrameDbArea *m_pCapFrameDbArea;
	CCapFrameIndexDbArea *m_pCapFrameIndexDbArea;
	BOOL m_bShowGrid;

public:
	CSttRcdMemBufferMngr m_oSttRcdMemBufferMngr; //��ʷ���Ļ���
	CSttFrameMemBufferMngr m_oSttFrameMemBufferMngr; //��ʷ���ķ�֡

	long m_nQueryCapFrameMaxPage; //�������ı���һ���ж���ҳ
	long m_nQueryCapFrameCurrPage; //�������ı��ĵ�ǰ��ʾ����ҳ
	CString m_strQueryInfo;
};

extern CCapFrameDbFileQueryTool g_oCapFrameDbFileQueryTool; //������ȫ��Ψһ����

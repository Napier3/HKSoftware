//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CCapFrameDbFileQueryTool.h  CCapFrameDbFileQueryTool

#pragma once

#include "CapFrameDbFile.h"
#include "..\..\..\WinPcap\Include\File_Pcap.h"

//xujinqiang20200622add，检索历史报文的工具类
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

	void GetPageBeginEndPos(long nPage, __int64 &nBeginPos, __int64 &nEndPos); //获取指定页面的起始终止点
	__int64 GetPageLength(long nPage); //获取指定页面的数据长度
	void QueryPageCapFrame(long nPage); //获取指定页面的内容

	BOOL PopSaveAsPcapFileDlg(CString &strExportFile);
	void ExportAllPagePcap(const CString &strFile); //导出所有页面的内容
	void ExportAllPagePcap(); //导出所有页面的内容
	void ExportOnePagePcap(long nPage); //导出指定页面的内容
	void ExportOnePagePcap(long nPage, const CString &strExportFile);
	void CapoptrExportAT02D(); //导出AT02D报文

	//xujinqiang20200705add：导出指定时间区间的抓取的报文的pcap格式
	BOOL Query(SYSTEMTIME tmBegin, SYSTEMTIME tmEnd);
	BOOL ExportPcap(SYSTEMTIME tmBegin, SYSTEMTIME tmEnd);
	BOOL ExportPcap(SYSTEMTIME tmBegin, SYSTEMTIME tmEnd, const CString &strExportFile);
	BOOL ExportPcap(const CString &strTmBegin, const CString &strTmEnd, const CString &strExportFile);

private:
	CCapFrameDbArea *m_pCapFrameDbArea;
	CCapFrameIndexDbArea *m_pCapFrameIndexDbArea;
	BOOL m_bShowGrid;

public:
	CSttRcdMemBufferMngr m_oSttRcdMemBufferMngr; //历史报文缓存
	CSttFrameMemBufferMngr m_oSttFrameMemBufferMngr; //历史报文分帧

	long m_nQueryCapFrameMaxPage; //检索出的报文一共有多少页
	long m_nQueryCapFrameCurrPage; //检索出的报文当前显示多少页
	CString m_strQueryInfo;
};

extern CCapFrameDbFileQueryTool g_oCapFrameDbFileQueryTool; //工具类全局唯一对象

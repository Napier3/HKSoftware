#pragma once
#include "..\..\Module\GridBase\ExBaseListGrid.h"
#include "XLangFolderMngr.h"

#define XLANGFILE_COL_ID_INDEX         0
#define XLANGFILE_COL_ID_XLANGID       1

#define XLANGID_FILEDEV_DELETEITEMS                 35001
#define XLANGID_FILEDEV_COPYITEMS                    35002
#define XLANGID_FILEDEV_OVERWRITE_ID               35003
#define XLANGID_FILEDEV_OVERWRITE_SRCTEXT      35004
#define XLANGID_FILEDEV_MATCH_TRANSTEXT         35005

//资源文件管理、编辑表格，显示某一个资源文件的所有相关文字资源
//对不不同资源文件之间的字符串资源的差异化
class CXLangFileDevGrid : public CExBaseListGrid
{
public:
	CXLangFileDevGrid();
	virtual ~CXLangFileDevGrid();

	//隐藏相同的资源ID
	static BOOL g_bHideSameXLangItem;
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual BOOL UpdateData(CExBaseObject *pData);
	virtual BOOL OnCellRButtonUpEx(UINT nFlags, CPoint point);
	void NextError();
	void PrevError();

	long GetXLangFileIndex();

	CWnd *m_pMsgRcvWnd;

private:
	long GetXLangIndexByCol(long nCol);
	void InitGridRows();
	void ShowDatas(CExBaseList *pDatas, long nCol);
	CExBaseList *m_pListXLangFile;  //资源文件管理对象
	CXLanguage *m_pLanguageRef; //资源文件文字资源汇总管理对象
};


#pragma once
#include "..\..\Module\GridBase\ExBaseListGrid.h"
#include "XLangFolderMngr.h"

#define XLANGFILE_COL_ID_INDEX         0
#define XLANGFILE_COL_ID_FILE          1

//资源文件显示表格，第一列：编号；第二列：资源文件，汇总所有资源文件
//第三列开始，为不同语言的资源文件
//表格的消息响应对象为theApp
class CXLangFilesGrid : public CExBaseListGrid
{
public:
	CXLangFilesGrid();
	virtual ~CXLangFilesGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

private:
	void InitGridRows();
	void ShowDatas(CExBaseList *pDatas, long nCol);
	CXLangFolderMngr *m_pMngr;
};


#pragma once
#include "..\..\Module\GridBase\ExBaseListGrid.h"
#include "XLangFolderMngr.h"

#define XLANGFILE_COL_ID_INDEX         0
#define XLANGFILE_COL_ID_FILE          1

//��Դ�ļ���ʾ��񣬵�һ�У���ţ��ڶ��У���Դ�ļ�������������Դ�ļ�
//�����п�ʼ��Ϊ��ͬ���Ե���Դ�ļ�
//������Ϣ��Ӧ����ΪtheApp
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


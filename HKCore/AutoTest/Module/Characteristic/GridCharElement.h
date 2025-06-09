//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//StationTest.h  CStationTestListCtrl

#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "CharacteristicTmplate.h"


#define CHARELEMENT_COL_INDEX      0
#define CHARELEMENT_COL_TYPE       1
#define CHARELEMENT_COL_POINTS     2
#define CHARELEMENT_COL_ERROR      3
#define CHARELEMENT_COL_DETAIL     4

#define CHARELEMENT_COLS           5


class CGridCharElementDev : public CExBaseListGrid
{
public:
	CGridCharElementDev();
	virtual ~CGridCharElementDev();

	void SetViewElementDetail(BOOL b=TRUE)	{	m_bViewElementDetail = b;	}
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//���غ���
public: 
	
//˽�г�Ա����
private:
	BOOL m_bViewElementDetail;
	static void EndEditCell_ErrorLength (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_TestPoints(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
//˽�г�Ա�������ʷ���
public:
	//virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);

};


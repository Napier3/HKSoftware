//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#pragma once

#include "..\..\..\..\Module\DataMngr\UI\XDataGroupGridBase.h"

#include "..\SttAdjBase.h"

class CSttAdjModeGrid : public CXDvmGrid_DataRow
//class CSttAdjModeGrid : public CXDvmGrid_GroupRowDataCol
{
public:
	CSttAdjModeGrid();
	virtual ~CSttAdjModeGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	//virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//���غ���
public: 
	//virtual void ShowAttrCol(CDvmData *pData, const CString &strAttrID, long nRow, long nCol);  	//��ʾCDvmData������
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


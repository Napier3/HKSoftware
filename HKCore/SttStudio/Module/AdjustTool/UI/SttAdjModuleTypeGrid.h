//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#pragma once

#include "..\..\..\..\Module\DataMngr\UI\XDataGroupGridBase.h"


class CSttAdjModuleTypeGrid : public CExBaseListGrid
{
public:
	CSttAdjModuleTypeGrid();
	virtual ~CSttAdjModuleTypeGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

};


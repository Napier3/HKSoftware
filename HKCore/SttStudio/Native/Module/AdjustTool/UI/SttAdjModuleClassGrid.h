//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#pragma once

#include "..\..\..\..\Module\DataMngr\UI\XDataGroupGridBase.h"


class CSttAdjModuleClassGrid : public CXDvmGrid_GroupRowDataCol
{
public:
	CSttAdjModuleClassGrid();
	virtual ~CSttAdjModuleClassGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//���غ���
public: 

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual CDataType* FindDataType(const CString &strDataType);
};


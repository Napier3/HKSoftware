//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#pragma once

#include "..\..\..\..\Module\DataMngr\UI\XDataGroupGridBase.h"


class CSttAdjModulesGrid : public CXDvmGrid_GroupRowDataCol
{
public:
	CSttAdjModulesGrid();
	virtual ~CSttAdjModulesGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	//virtual void ShowAttrCol(CDataGroup *pDataGroup, const CString &strDataID, long nRow, long nCol) ;
//���غ���
public: 

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual CDataType* FindDataType(const CString &strDataType);
};


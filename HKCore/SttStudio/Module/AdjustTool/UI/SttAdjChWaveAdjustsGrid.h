//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#pragma once

#include "..\..\..\..\Module\DataMngr\UI\XDataGroupGridBase.h"


class CSttAdjChWaveAdjustsGrid : public CXDvmGrid_GroupRowDataCol
{
public:
	CSttAdjChWaveAdjustsGrid();
	virtual ~CSttAdjChWaveAdjustsGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//���غ���
public: 

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

//ɾȥ��λУ׼��
class CSttAdjChWaveAdjustsGrid2 : public CXDvmGrid_GroupRowDataCol
{
public:
	CSttAdjChWaveAdjustsGrid2();
	virtual ~CSttAdjChWaveAdjustsGrid2();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};

//��λУ׼�и�ΪӲ����Ư
class CSttAdjChWaveAdjustsGrid3 : public CXDvmGrid_GroupRowDataCol
{
public:
	CSttAdjChWaveAdjustsGrid3();
	virtual ~CSttAdjChWaveAdjustsGrid3();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};

//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#pragma once

#include "../GridBase/ExBaseListGrid.h"
#include "XSafenetBase.h"

#define SAFENET_AUTHORITY_COL_INDEX      0
#define SAFENET_AUTHORITY_COL_SEL          1
#define SAFENET_AUTHORITY_COL_NAME       2
#define SAFENET_AUTHORITY_COL_ID            3

#define SAFENET_AUTHORITY_COLS               4


class CSafenetAuthorityGrid : public CExBaseListGrid
{
public:
	CSafenetAuthorityGrid();
	virtual ~CSafenetAuthorityGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//���غ���
public: 
	BOOL m_bUseEnable;

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


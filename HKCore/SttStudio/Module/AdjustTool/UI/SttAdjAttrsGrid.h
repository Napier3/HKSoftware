//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#pragma once

#include "..\..\..\..\Module\DataMngr\UI\XDataGroupGridBase.h"


class CSttAdjAttrsGrid : public CXDvmGrid_DataRow
{
public:
	CSttAdjAttrsGrid();
	virtual ~CSttAdjAttrsGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	CDvmData *m_pModuleType;   //20210717  shaolei  ��¼ģ�����ͣ�����������ʾģ������
	//���غ���
public: 
	//virtual void ShowAttrCol(CDvmData *pData, const CString &strAttrID, long nRow, long nCol);  	//��ʾCDvmData������

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual CDataType* FindDataType(const CString &strDataType);
};


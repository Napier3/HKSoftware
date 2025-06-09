//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#pragma once

#include "..\..\GridBase\ExBaseListGrid.h"
#include "..\DataGroup.h"

//////////////////////////////////////////////////////////////////////////
//CXDataGroupGridBase
class CXDataGroupGridBase : public CExBaseListGrid
{
public:
	CXDataGroupGridBase();
	virtual ~CXDataGroupGridBase();

protected:
	DWORD m_dwChildClassID;        //�Ӷ�����ClassIDȷ��
	CString m_strChildDataTypeID;    //�Ӷ�����data-typeȷ��
	CStringArray m_astrColAttrs;       //��ʾ���е�����ID


//���غ���
public: 
	virtual void SetModifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowDatasEx(CExBaseList *pDatas, BOOL bResetScrollBars);
	virtual CDataType* FindDataType(const CString &strDataType)		{	return NULL;	}


public:
	//���������ԣ���ʾcell�ı�����ʱ��ʵ�ָ�������ʾ�ĸ�ʽ���⡿
	virtual void ShowAttr(CDvmData *pData, const CString &strAttrID, long nRow, long nCol);

	//�����������͵����ԣ��ж�CDvmData�ġ�value�������Ƿ�����޸ġ����硰HdVersion����SoftVersion���ȾͲ��ܱ��޸ġ�
	virtual BOOL IsValueCanEdit(const CString &strDataType); 

	//��ʼ������������
	virtual void InitGridColAttrs(CString *pStrColAttrs, long nCols);  

	//////////////////////////////////////////////////////////////////////////
	//��ʾ���ԡ��������Ӷ���
	virtual void ShowAttrCol(CDvmData *pData, const CString &strAttrID, long nRow, long nCol);  	//��ʾCDvmData������
	virtual void ShowAttrCol(CDataGroup *pDataGroup, const CString &strDataID, long nRow, long nCol);  	//��ʾDvmData�Ӷ���

	//////////////////////////////////////////////////////////////////////////
	//����m_astrColAttrs
	virtual void ShowAttrCol(CDvmData *pData, long nRow, long nCol);  	//��ʾCDvmData�����ԣ�
	virtual void ShowAttrCol(CDataGroup *pDataGroup, long nRow, long nCol);  	//��ʾDvmData�Ӷ���

};

//////////////////////////////////////////////////////////////////////////
//CXDvmGrid_DataRow
class CXDvmGrid_GroupRow : public CXDataGroupGridBase
{
public:
	CXDvmGrid_GroupRow();
	virtual ~CXDvmGrid_GroupRow();

	virtual void InitGrid();
	virtual void InitGridTitle();

public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

};

//////////////////////////////////////////////////////////////////////////
//CXDvmGrid_DataRow
class CXDvmGrid_DataRow : public CXDataGroupGridBase
{
public:
	CXDvmGrid_DataRow();
	virtual ~CXDvmGrid_DataRow();

public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

};

//////////////////////////////////////////////////////////////////////////
//CXDvmGrid_DataRow
class CXDvmGrid_GroupRowDataCol : public CXDataGroupGridBase
{
public:
	CXDvmGrid_GroupRowDataCol();
	virtual ~CXDvmGrid_GroupRowDataCol();

public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

};
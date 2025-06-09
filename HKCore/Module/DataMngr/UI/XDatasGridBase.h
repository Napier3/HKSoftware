//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#pragma once

#include "..\..\GridBase\ExBaseListGrid.h"
#include "..\ShortDatas.h"

//////////////////////////////////////////////////////////////////////////
//CXDatasGridBase
class CXDatasGridBase : public CExBaseListGrid
{
public:
	CXDatasGridBase();
	virtual ~CXDatasGridBase();

protected:
	DWORD m_dwChildClassID;        //�Ӷ�����ClassIDȷ��
	CString m_strChildDataTypeID;    //�Ӷ�����data-typeȷ��
	CStringArray m_astrColAttrs;       //��ʾ���е�����ID


//���غ���
public: 
	virtual void SetModifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowDatasEx(CExBaseList *pDatas, BOOL bResetScrollBars);


public:
	//���������ԣ���ʾcell�ı�����ʱ��ʵ�ָ�������ʾ�ĸ�ʽ���⡿
	virtual void ShowAttr(CShortData *pData, const CString &strAttrID, long nRow, long nCol);

	//�����������͵����ԣ��ж�CShortData�ġ�value�������Ƿ�����޸ġ����硰HdVersion����SoftVersion���ȾͲ��ܱ��޸ġ�
	virtual BOOL IsValueCanEdit(const CString &strDataType); 

	//��ʼ������������
	virtual void InitGridColAttrs(CString *pStrColAttrs, long nCols);  

	//////////////////////////////////////////////////////////////////////////
	//��ʾ���ԡ��������Ӷ���
	virtual void ShowAttrCol(CShortData *pData, const CString &strAttrID, long nRow, long nCol);  	//��ʾCShortData������

	//////////////////////////////////////////////////////////////////////////
	//����m_astrColAttrs
	virtual void ShowAttrCol(CShortData *pData, long nRow, long nCol);  	//��ʾCShortData�����ԣ�
};

//////////////////////////////////////////////////////////////////////////
//CXDatasGrid_DataRow
class CXDatasGrid_DataRow : public CXDatasGridBase
{
public:
	CXDatasGrid_DataRow();
	virtual ~CXDatasGrid_DataRow();

public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

};
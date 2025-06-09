//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	DWORD m_dwChildClassID;        //子对象有ClassID确定
	CString m_strChildDataTypeID;    //子对象由data-type确定
	CStringArray m_astrColAttrs;       //表示各列的属性ID


//重载函数
public: 
	virtual void SetModifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowDatasEx(CExBaseList *pDatas, BOOL bResetScrollBars);
	virtual CDataType* FindDataType(const CString &strDataType)		{	return NULL;	}


public:
	//【根据属性，显示cell文本。暂时不实现浮点数显示的格式问题】
	virtual void ShowAttr(CDvmData *pData, const CString &strAttrID, long nRow, long nCol);

	//根据数据类型的属性，判断CDvmData的“value”属性是否可以修改。例如“HdVersion”“SoftVersion”等就不能被修改。
	virtual BOOL IsValueCanEdit(const CString &strDataType); 

	//初始化属性列数组
	virtual void InitGridColAttrs(CString *pStrColAttrs, long nCols);  

	//////////////////////////////////////////////////////////////////////////
	//显示属性、或者是子对象
	virtual void ShowAttrCol(CDvmData *pData, const CString &strAttrID, long nRow, long nCol);  	//显示CDvmData的属性
	virtual void ShowAttrCol(CDataGroup *pDataGroup, const CString &strDataID, long nRow, long nCol);  	//显示DvmData子对象

	//////////////////////////////////////////////////////////////////////////
	//遍历m_astrColAttrs
	virtual void ShowAttrCol(CDvmData *pData, long nRow, long nCol);  	//显示CDvmData的属性，
	virtual void ShowAttrCol(CDataGroup *pDataGroup, long nRow, long nCol);  	//显示DvmData子对象

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
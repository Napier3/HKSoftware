//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	DWORD m_dwChildClassID;        //子对象有ClassID确定
	CString m_strChildDataTypeID;    //子对象由data-type确定
	CStringArray m_astrColAttrs;       //表示各列的属性ID


//重载函数
public: 
	virtual void SetModifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowDatasEx(CExBaseList *pDatas, BOOL bResetScrollBars);


public:
	//【根据属性，显示cell文本。暂时不实现浮点数显示的格式问题】
	virtual void ShowAttr(CShortData *pData, const CString &strAttrID, long nRow, long nCol);

	//根据数据类型的属性，判断CShortData的“value”属性是否可以修改。例如“HdVersion”“SoftVersion”等就不能被修改。
	virtual BOOL IsValueCanEdit(const CString &strDataType); 

	//初始化属性列数组
	virtual void InitGridColAttrs(CString *pStrColAttrs, long nCols);  

	//////////////////////////////////////////////////////////////////////////
	//显示属性、或者是子对象
	virtual void ShowAttrCol(CShortData *pData, const CString &strAttrID, long nRow, long nCol);  	//显示CShortData的属性

	//////////////////////////////////////////////////////////////////////////
	//遍历m_astrColAttrs
	virtual void ShowAttrCol(CShortData *pData, long nRow, long nCol);  	//显示CShortData的属性，
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
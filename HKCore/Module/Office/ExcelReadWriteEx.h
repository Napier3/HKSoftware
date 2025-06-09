// ExcelReadWrite.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ExcelReadWriteEx_H__)
#define _ExcelReadWriteEx_H__

#include "msexcel.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///用于OLE的方式的EXCEL读写，  
class CExcelReadWriteEx  
{  
protected:
	static COleVariant  covTrue;//((short)TRUE);
	static COleVariant  covFalse;//((short)FALSE);
	static COleVariant  covOptional;//((long)DISP_E_PARAMNOTFOUND, VT_ERROR);      

public:  
  
    //构造函数和析构函数  
    CExcelReadWriteEx();  
    virtual ~CExcelReadWriteEx();  
  
protected:  
    ///打开的EXCEL文件名称  
    CString       m_strExcelFile;  
  
    ///EXCEL BOOK集合，（多个文件时）  
	MSExcel::Workbooks		m_oBooks;   
    ///当前使用的BOOK，当前处理的文件  
    MSExcel::_Workbook		m_oBook;   
    ///EXCEL的sheets集合  
    MSExcel::Worksheets		m_oSheets;   
    ///当前使用sheet  
    MSExcel::_Worksheet		m_oSheet;   
    ///当前的操作区域  
    MSExcel::Range			m_oCurrentRange;   
  
    ///是否已经预加载了某个sheet的数据  
    BOOL          m_bAlreadyPreload;  

    ///Create the SAFEARRAY from the VARIANT ret.  
    COleSafeArray m_oOleSafeArray;  
  
protected:  
  
    ///EXCEL的进程实例  
    MSExcel::_Application	m_oApplication;  
public:  
  
    void ShowInExcel(BOOL bShow);  
  
	///打开文件  
	BOOL OpenExcelFile(const CString &file_name);  

	///关闭打开的Excel 文件，有时候打开EXCEL文件就要  
	void CloseExcelFile(BOOL if_save = FALSE);  

	//另存为一个EXCEL文件  
	void SaveasXSLFile(const CString& xls_file);  
	void SaveXSLFile();  

	///取得打开文件的路径  
	CString  GetOpenFileName();  

	///取得打开sheet的名称  
	CString  GetLoadSheetName();  

	BOOL     IsCellMerge(long iRow, long iColumn);		//检查一个CELL是否合并单元格
    BOOL	 IsCellString(long iRow, long iColumn);		//检查一个CELL是否是字符串  
    BOOL	 IsCellInt(long iRow, long iColumn);		//检查一个CELL是否是数值  

    CString  GetCellString(long iRow, long iColumn);	//取得一个CELL的String  
    int      GetCellInt(long iRow, long iColumn);		//取得一个CELL的int
    double   GetCellDouble(long iRow, long iColumn);	//取得一个CELL的double
	void	 GetCellFont(long iRow, long iColumn, CString& strFontName, long& lSize, long& lBold);	//取得一个CELL的字体信息
	COLORREF GetCellTextColor(long iRow, long iColumn);	//取得一个CELL的文本色
	COLORREF GetCellBKColor(long iRow, long iColumn);	//取得一个CELL的背景色
	void	 GetCellFontAndColor(long iRow, long iColumn, CString& strFontName, long& lSize, long& lBold, COLORREF& crText, COLORREF& crBK);
	void	 GetMergeCellInfo(long iRow, long iColumn, long& lStartRow, long& lStartColumn, long& lRows, long& lColumns);

    ///取得行的总数  
    int GetRowCount();  

    ///取得列的总数  
    int GetColumnCount();  
  
    ///使用某个sheet，shit，shit,按照序号加载sheet  
    BOOL LoadSheet(long table_index,BOOL pre_load = FALSE);  

    ///通过名称使用某个sheet，按照名称加载sheet  
    BOOL LoadSheet(const CString& sheet,BOOL pre_load = FALSE);  

    ///通过序号取得某个Sheet的名称  
    CString GetSheetName(long table_index);  
  
    ///得到Sheet的总数  
    int GetSheetCount();  
  
    void SetCellInt(long iRow, long iColumn, int nInt);			    //写入CELL一个int  
    void SetCellString(long iRow, long iColumn, const CString& strText);//写入CELL一个string 
	void SetCellFont(long iRow, long iColumn, const CString& strFont, long lSize, long lBold);	   //设置CELL的字体
    void SetCellTextColor(long iRow, long iColumn, COLORREF crColor); //设置CELL文本色 
	void SetCellBKColor(long iRow, long iColumn, COLORREF crColor);   //设置CELL背景色
	void SetCellFontAndColor(long iRow, long iColumn, const CString& strFontName, long lSize, long lBold, COLORREF crText, COLORREF crBK);

	void MergeCells(long iRow, long iColumn, long lMergeRows, long lMergeCols);
	void AutoFitColumns();
	void AutoFitRows();
	void FreezeFirstRow();
	void FreezeFirstCol();
	void CancelFreezePanes();

	//////////////////////////////////////////////////////////////////////////
	//20190831  addsheet
	void DeleteAllSheet();
	BOOL AddSheet(long nIndexAfter, const CString &strNewName);
	BOOL SetCurSheetName(const CString &strSheetName);

public:  
    ///初始化EXCEL OLE  
    BOOL InitExcel();  
    ///释放EXCEL的 OLE  
    void ReleaseExcel();  
    ///取得列的名称 
    char *GetColumnName(long lColumn);  
  
protected:  
    //预先加载  
    void PreLoadSheet();  
};  

#endif // !defined(_WORDBASECLASS_H__)

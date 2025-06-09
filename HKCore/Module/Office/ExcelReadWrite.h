// ExcelReadWrite.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ExcelReadWrite_H__)
#define _ExcelReadWrite_H__

#include "MsExcel9.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///用于OLE的方式的EXCEL读写，  
class CExcelReadWrite  
{  
protected:
	static COleVariant  covTrue;//((short)TRUE);
	static COleVariant  covFalse;//((short)FALSE);
	static COleVariant  covOptional;//((long)DISP_E_PARAMNOTFOUND, VT_ERROR);      

public:  
  
    //构造函数和析构函数  
    CExcelReadWrite();  
    virtual ~CExcelReadWrite();  
  
protected:  
    ///打开的EXCEL文件名称  
    CString       m_strExcelFile;  
  
    ///EXCEL BOOK集合，（多个文件时）  
	MSExcel::CWorkbooks    m_oBooks;   
    ///当前使用的BOOK，当前处理的文件  
    MSExcel::CWorkbook     m_oBook;   
    ///EXCEL的sheets集合  
   MSExcel:: CWorksheets   m_oSheets;   
    ///当前使用sheet  
    MSExcel::CWorksheet    m_oSheet;   
    ///当前的操作区域  
    MSExcel::CRange        m_oCurrentRange;   
  
  
    ///是否已经预加载了某个sheet的数据  
    BOOL          m_bAlreadyPreload;  
    ///Create the SAFEARRAY from the VARIANT ret.  
    COleSafeArray m_oOleSafeArray;  
  
protected:  
  
    ///EXCEL的进程实例  
    MSExcel::CApplication m_oApplication;  
public:  
  
    ///  
    void ShowInExcel(BOOL bShow);  
  
    ///检查一个CELL是否是字符串  
    BOOL    IsCellString(long iRow, long iColumn);  
    ///检查一个CELL是否是数值  
    BOOL    IsCellInt(long iRow, long iColumn);  
  
    ///得到一个CELL的String  
    CString GetCellString(long iRow, long iColumn);  
    ///得到整数  
    int     GetCellInt(long iRow, long iColumn);  
    ///得到double的数据  
    double  GetCellDouble(long iRow, long iColumn);  
  
    ///取得行的总数  
    int GetRowCount();  
    ///取得列的总数  
    int GetColumnCount();  
  
    ///使用某个shet，shit，shit,按照序号加载sheet  
    BOOL LoadSheet(long table_index,BOOL pre_load = FALSE);  
    ///通过名称使用某个sheet，按照名称加载sheet  
    BOOL LoadSheet(const CString & sheet,BOOL pre_load = FALSE);  
    ///通过序号取得某个Sheet的名称  
    CString GetSheetName(long table_index);  
  
    ///得到Sheet的总数  
    int GetSheetCount();  
  
    ///打开文件  
    BOOL OpenExcelFile(const CString &file_name);  
    ///关闭打开的Excel 文件，有时候打开EXCEL文件就要  
    void CloseExcelFile(BOOL if_save = FALSE);  
    //另存为一个EXCEL文件  
    void SaveasXSLFile(const CString &xls_file);  
	void SaveXSLFile();  
   ///取得打开文件的路径  
    CString GetOpenFileName();  
    ///取得打开sheet的名称  
    CString GetLoadSheetName();  
  
    ///写入一个CELL一个int,行、列、要写入的int  
    void SetCellInt(long irow, long icolumn,int new_int);  
    ///写入一个CELL一个string,行、列、要写入的CString  
    void SetCellString(long irow, long icolumn,CString new_string);  
      
	void AutoFit(long nColumn);
	void SetColWidth(long nColumn, long nWidth);
public:  
    ///初始化EXCEL OLE  
    BOOL InitExcel();  
    ///释放EXCEL的 OLE  
    void ReleaseExcel();  
    ///取得列的名称，比如27->AA  
    char *GetColumnName(long iColumn);  
  
protected:  
  
    //预先加载  
    void PreLoadSheet();  
};  

static const CString g_strExcelFileFilter = _T("Excel File (*.xls;*.xlsx)|*.xls;*.xlsx|Excel File (*.xls)|*.xls|Excel File (*.xlsx)|*.xlsx||");


#endif // !defined(_WORDBASECLASS_H__)

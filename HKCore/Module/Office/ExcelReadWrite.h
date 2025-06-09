// ExcelReadWrite.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ExcelReadWrite_H__)
#define _ExcelReadWrite_H__

#include "MsExcel9.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///����OLE�ķ�ʽ��EXCEL��д��  
class CExcelReadWrite  
{  
protected:
	static COleVariant  covTrue;//((short)TRUE);
	static COleVariant  covFalse;//((short)FALSE);
	static COleVariant  covOptional;//((long)DISP_E_PARAMNOTFOUND, VT_ERROR);      

public:  
  
    //���캯������������  
    CExcelReadWrite();  
    virtual ~CExcelReadWrite();  
  
protected:  
    ///�򿪵�EXCEL�ļ�����  
    CString       m_strExcelFile;  
  
    ///EXCEL BOOK���ϣ�������ļ�ʱ��  
	MSExcel::CWorkbooks    m_oBooks;   
    ///��ǰʹ�õ�BOOK����ǰ������ļ�  
    MSExcel::CWorkbook     m_oBook;   
    ///EXCEL��sheets����  
   MSExcel:: CWorksheets   m_oSheets;   
    ///��ǰʹ��sheet  
    MSExcel::CWorksheet    m_oSheet;   
    ///��ǰ�Ĳ�������  
    MSExcel::CRange        m_oCurrentRange;   
  
  
    ///�Ƿ��Ѿ�Ԥ������ĳ��sheet������  
    BOOL          m_bAlreadyPreload;  
    ///Create the SAFEARRAY from the VARIANT ret.  
    COleSafeArray m_oOleSafeArray;  
  
protected:  
  
    ///EXCEL�Ľ���ʵ��  
    MSExcel::CApplication m_oApplication;  
public:  
  
    ///  
    void ShowInExcel(BOOL bShow);  
  
    ///���һ��CELL�Ƿ����ַ���  
    BOOL    IsCellString(long iRow, long iColumn);  
    ///���һ��CELL�Ƿ�����ֵ  
    BOOL    IsCellInt(long iRow, long iColumn);  
  
    ///�õ�һ��CELL��String  
    CString GetCellString(long iRow, long iColumn);  
    ///�õ�����  
    int     GetCellInt(long iRow, long iColumn);  
    ///�õ�double������  
    double  GetCellDouble(long iRow, long iColumn);  
  
    ///ȡ���е�����  
    int GetRowCount();  
    ///ȡ���е�����  
    int GetColumnCount();  
  
    ///ʹ��ĳ��shet��shit��shit,������ż���sheet  
    BOOL LoadSheet(long table_index,BOOL pre_load = FALSE);  
    ///ͨ������ʹ��ĳ��sheet���������Ƽ���sheet  
    BOOL LoadSheet(const CString & sheet,BOOL pre_load = FALSE);  
    ///ͨ�����ȡ��ĳ��Sheet������  
    CString GetSheetName(long table_index);  
  
    ///�õ�Sheet������  
    int GetSheetCount();  
  
    ///���ļ�  
    BOOL OpenExcelFile(const CString &file_name);  
    ///�رմ򿪵�Excel �ļ�����ʱ���EXCEL�ļ���Ҫ  
    void CloseExcelFile(BOOL if_save = FALSE);  
    //���Ϊһ��EXCEL�ļ�  
    void SaveasXSLFile(const CString &xls_file);  
	void SaveXSLFile();  
   ///ȡ�ô��ļ���·��  
    CString GetOpenFileName();  
    ///ȡ�ô�sheet������  
    CString GetLoadSheetName();  
  
    ///д��һ��CELLһ��int,�С��С�Ҫд���int  
    void SetCellInt(long irow, long icolumn,int new_int);  
    ///д��һ��CELLһ��string,�С��С�Ҫд���CString  
    void SetCellString(long irow, long icolumn,CString new_string);  
      
	void AutoFit(long nColumn);
	void SetColWidth(long nColumn, long nWidth);
public:  
    ///��ʼ��EXCEL OLE  
    BOOL InitExcel();  
    ///�ͷ�EXCEL�� OLE  
    void ReleaseExcel();  
    ///ȡ���е����ƣ�����27->AA  
    char *GetColumnName(long iColumn);  
  
protected:  
  
    //Ԥ�ȼ���  
    void PreLoadSheet();  
};  

static const CString g_strExcelFileFilter = _T("Excel File (*.xls;*.xlsx)|*.xls;*.xlsx|Excel File (*.xls)|*.xls|Excel File (*.xlsx)|*.xlsx||");


#endif // !defined(_WORDBASECLASS_H__)

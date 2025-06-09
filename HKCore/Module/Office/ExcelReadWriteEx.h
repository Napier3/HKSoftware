// ExcelReadWrite.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ExcelReadWriteEx_H__)
#define _ExcelReadWriteEx_H__

#include "msexcel.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///����OLE�ķ�ʽ��EXCEL��д��  
class CExcelReadWriteEx  
{  
protected:
	static COleVariant  covTrue;//((short)TRUE);
	static COleVariant  covFalse;//((short)FALSE);
	static COleVariant  covOptional;//((long)DISP_E_PARAMNOTFOUND, VT_ERROR);      

public:  
  
    //���캯������������  
    CExcelReadWriteEx();  
    virtual ~CExcelReadWriteEx();  
  
protected:  
    ///�򿪵�EXCEL�ļ�����  
    CString       m_strExcelFile;  
  
    ///EXCEL BOOK���ϣ�������ļ�ʱ��  
	MSExcel::Workbooks		m_oBooks;   
    ///��ǰʹ�õ�BOOK����ǰ������ļ�  
    MSExcel::_Workbook		m_oBook;   
    ///EXCEL��sheets����  
    MSExcel::Worksheets		m_oSheets;   
    ///��ǰʹ��sheet  
    MSExcel::_Worksheet		m_oSheet;   
    ///��ǰ�Ĳ�������  
    MSExcel::Range			m_oCurrentRange;   
  
    ///�Ƿ��Ѿ�Ԥ������ĳ��sheet������  
    BOOL          m_bAlreadyPreload;  

    ///Create the SAFEARRAY from the VARIANT ret.  
    COleSafeArray m_oOleSafeArray;  
  
protected:  
  
    ///EXCEL�Ľ���ʵ��  
    MSExcel::_Application	m_oApplication;  
public:  
  
    void ShowInExcel(BOOL bShow);  
  
	///���ļ�  
	BOOL OpenExcelFile(const CString &file_name);  

	///�رմ򿪵�Excel �ļ�����ʱ���EXCEL�ļ���Ҫ  
	void CloseExcelFile(BOOL if_save = FALSE);  

	//���Ϊһ��EXCEL�ļ�  
	void SaveasXSLFile(const CString& xls_file);  
	void SaveXSLFile();  

	///ȡ�ô��ļ���·��  
	CString  GetOpenFileName();  

	///ȡ�ô�sheet������  
	CString  GetLoadSheetName();  

	BOOL     IsCellMerge(long iRow, long iColumn);		//���һ��CELL�Ƿ�ϲ���Ԫ��
    BOOL	 IsCellString(long iRow, long iColumn);		//���һ��CELL�Ƿ����ַ���  
    BOOL	 IsCellInt(long iRow, long iColumn);		//���һ��CELL�Ƿ�����ֵ  

    CString  GetCellString(long iRow, long iColumn);	//ȡ��һ��CELL��String  
    int      GetCellInt(long iRow, long iColumn);		//ȡ��һ��CELL��int
    double   GetCellDouble(long iRow, long iColumn);	//ȡ��һ��CELL��double
	void	 GetCellFont(long iRow, long iColumn, CString& strFontName, long& lSize, long& lBold);	//ȡ��һ��CELL��������Ϣ
	COLORREF GetCellTextColor(long iRow, long iColumn);	//ȡ��һ��CELL���ı�ɫ
	COLORREF GetCellBKColor(long iRow, long iColumn);	//ȡ��һ��CELL�ı���ɫ
	void	 GetCellFontAndColor(long iRow, long iColumn, CString& strFontName, long& lSize, long& lBold, COLORREF& crText, COLORREF& crBK);
	void	 GetMergeCellInfo(long iRow, long iColumn, long& lStartRow, long& lStartColumn, long& lRows, long& lColumns);

    ///ȡ���е�����  
    int GetRowCount();  

    ///ȡ���е�����  
    int GetColumnCount();  
  
    ///ʹ��ĳ��sheet��shit��shit,������ż���sheet  
    BOOL LoadSheet(long table_index,BOOL pre_load = FALSE);  

    ///ͨ������ʹ��ĳ��sheet���������Ƽ���sheet  
    BOOL LoadSheet(const CString& sheet,BOOL pre_load = FALSE);  

    ///ͨ�����ȡ��ĳ��Sheet������  
    CString GetSheetName(long table_index);  
  
    ///�õ�Sheet������  
    int GetSheetCount();  
  
    void SetCellInt(long iRow, long iColumn, int nInt);			    //д��CELLһ��int  
    void SetCellString(long iRow, long iColumn, const CString& strText);//д��CELLһ��string 
	void SetCellFont(long iRow, long iColumn, const CString& strFont, long lSize, long lBold);	   //����CELL������
    void SetCellTextColor(long iRow, long iColumn, COLORREF crColor); //����CELL�ı�ɫ 
	void SetCellBKColor(long iRow, long iColumn, COLORREF crColor);   //����CELL����ɫ
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
    ///��ʼ��EXCEL OLE  
    BOOL InitExcel();  
    ///�ͷ�EXCEL�� OLE  
    void ReleaseExcel();  
    ///ȡ���е����� 
    char *GetColumnName(long lColumn);  
  
protected:  
    //Ԥ�ȼ���  
    void PreLoadSheet();  
};  

#endif // !defined(_WORDBASECLASS_H__)

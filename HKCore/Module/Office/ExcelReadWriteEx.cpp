// ExcelReadWriteEx.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExcelReadWriteEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

COleVariant  CExcelReadWriteEx::covTrue((short)TRUE);
COleVariant  CExcelReadWriteEx::covFalse((short)FALSE);
COleVariant  CExcelReadWriteEx::covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);      
  
CExcelReadWriteEx::CExcelReadWriteEx(): m_bAlreadyPreload(FALSE)  
{ 
	m_oApplication = NULL;
}  
  
CExcelReadWriteEx::~CExcelReadWriteEx()  
{  
    CloseExcelFile();
	ReleaseExcel();
}  
  
//初始化EXCEL文件，  
BOOL CExcelReadWriteEx::InitExcel()  
{  
	if (m_oApplication != NULL)
	{
		return TRUE;
	}

    //启动Excel
    if (!m_oApplication.CreateDispatch(_T("Excel.Application")))   
    {   
        return FALSE;  
    }  
  
    m_oApplication.SetDisplayAlerts(FALSE);   
	
    return TRUE;  
}  
  
//  
void CExcelReadWriteEx::ReleaseExcel()  
{  
    m_oApplication.Quit();  
    m_oApplication.ReleaseDispatch();  
    m_oApplication=NULL;  
}  
  
//打开excel文件  
BOOL CExcelReadWriteEx::OpenExcelFile(const CString &file_name)  
{  
    //先关闭  
    CloseExcelFile();  
      
    //利用模板文件建立新文档   
    m_oBooks.AttachDispatch(m_oApplication.GetWorkbooks(),true);   
  
    LPDISPATCH lpDis = NULL;  
    lpDis = m_oBooks.Add(COleVariant(file_name));   

	if (lpDis)  
    {  
        m_oBook.AttachDispatch(lpDis);   
       
		//得到Worksheets   
        m_oSheets.AttachDispatch(m_oBook.GetWorksheets(),true);   
          
        //记录打开的文件名称  
        m_strExcelFile = file_name;  
  
        return TRUE;  
    }  
      
    return FALSE;  
}  
  
//关闭打开的Excel 文件,默认情况不保存文件  
void CExcelReadWriteEx::CloseExcelFile(BOOL if_save)  
{  
	try
	{
		m_oBook.Close(COleVariant(short(FALSE)),COleVariant(m_strExcelFile),covOptional);  
		m_oBooks.Close();  
	}
	catch (...)
	{
		
	}

	try
	{
		m_oSheets.ReleaseDispatch();  
		m_oSheet.ReleaseDispatch();  
		m_oCurrentRange.ReleaseDispatch();  
		m_oBook.ReleaseDispatch();  
		m_oBooks.ReleaseDispatch();  
	}
	catch (...)
	{

	}
}  
  
void CExcelReadWriteEx::SaveasXSLFile(const CString &xls_file)  
{  
	m_strExcelFile = xls_file;

    m_oBook.SaveAs(COleVariant(xls_file),  
        covOptional,  
        covOptional,  
        covOptional,  
        covOptional,  
        covOptional,  
        0,  
        covOptional,  
        covOptional,  
        covOptional,  
        covOptional,  
        covOptional);  
    return;  
}  
  
void CExcelReadWriteEx::SaveXSLFile()
{
	m_oBook.SaveAs(COleVariant(m_strExcelFile),  
		covOptional,  
		covOptional,  
		covOptional,  
		covOptional,  
		covOptional,  
		0,  
		covOptional,  
		covOptional,  
		covOptional,  
		covOptional,  
		covOptional);  
}
  
int CExcelReadWriteEx::GetSheetCount()  
{  
    return m_oSheets.GetCount();  
}  
  
//get sheet name,参数表示第几个sheet  
CString CExcelReadWriteEx::GetSheetName(long table_index)  
{  
    MSExcel::_Worksheet sheet;  
    sheet.AttachDispatch(m_oSheets.GetItem(COleVariant((long)table_index)),true);  
    CString name = sheet.GetName();  
    sheet.ReleaseDispatch();  
    return name;  
}  
  
//按照序号加载Sheet表格,可以提前加载所有的表格内部数据  
BOOL CExcelReadWriteEx::LoadSheet(long table_index,BOOL pre_load)  
{  
    LPDISPATCH lpDis = NULL;  
    m_oCurrentRange.ReleaseDispatch();  
    m_oSheet.ReleaseDispatch();  
    lpDis = m_oSheets.GetItem(COleVariant((long)table_index));  

    if (lpDis)  
    {  
        m_oSheet.AttachDispatch(lpDis,true);  
        m_oCurrentRange.AttachDispatch(m_oSheet.GetCells(), true);  
    }  
    else  
    {  
        return FALSE;  
    }  
      
    m_bAlreadyPreload = FALSE;  

    //如果进行预先加载  
    if (pre_load)  
    {  
        PreLoadSheet();  
        m_bAlreadyPreload = TRUE;  
    }  
  
    return TRUE;  
}  
  
//按照名称加载Sheet表格,可以提前加载所有的表格内部数据  
BOOL CExcelReadWriteEx::LoadSheet(const CString & sheet,BOOL pre_load)  
{  
    LPDISPATCH lpDis = NULL;  
    m_oCurrentRange.ReleaseDispatch();  
    m_oSheet.ReleaseDispatch();  
    lpDis = m_oSheets.GetItem(COleVariant(sheet));  
    if (lpDis)  
    {  
        m_oSheet.AttachDispatch(lpDis,true);  
        m_oCurrentRange.AttachDispatch(m_oSheet.GetCells(), true);  
          
    }  
    else  
    {  
        return FALSE;  
    }  
    //  
    m_bAlreadyPreload = FALSE;  
    //如果进行预先加载  
    if (pre_load)  
    {  
        m_bAlreadyPreload = TRUE;  
        PreLoadSheet();  
    }  
  
    return TRUE;  
}  

//20190831  addsheet
void CExcelReadWriteEx::DeleteAllSheet()
{

}

BOOL CExcelReadWriteEx::AddSheet(long nIndexAfter, const CString &strNewName)
{
	m_oCurrentRange.ReleaseDispatch();  
	m_oSheet.ReleaseDispatch();  
	
	COleVariant covIndex(nIndexAfter),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	LPDISPATCH lpDis = NULL;  

	try
	{
		lpDis = m_oSheets.GetItem(covIndex);
	}
	catch (...)
	{
	}

	_variant_t vActive;

	if (lpDis == NULL)
	{
		lpDis = m_oSheets.Add(covOptional, covOptional, covOptional, covOptional);
	}
	else
	{
		vActive = lpDis;
		lpDis = m_oSheets.Add(covOptional, vActive, covOptional, covOptional);
	}

	m_oSheet.AttachDispatch(lpDis,true);  
	m_oCurrentRange.AttachDispatch(m_oSheet.GetCells(), true);  
	m_oSheet.SetName(strNewName);

	m_bAlreadyPreload = FALSE;  

	return (m_oSheet != NULL);  
}

BOOL CExcelReadWriteEx::SetCurSheetName(const CString &strSheetName)
{
	ASSERT (m_oSheet != NULL);

	if (m_oSheet == NULL)
	{
		return FALSE;
	}

	m_oSheet.SetName(strSheetName);
	return TRUE;
}
  
//得到列的总数  
int CExcelReadWriteEx::GetColumnCount()  
{  
    MSExcel::Range range;  
    MSExcel::Range usedRange;  
    usedRange.AttachDispatch(m_oSheet.GetUsedRange(), true);  
    range.AttachDispatch(usedRange.GetColumns(), true);  
    int count = range.GetCount();  
    usedRange.ReleaseDispatch();  
    range.ReleaseDispatch();  
    return count;  
}  
  
//得到行的总数  
int CExcelReadWriteEx::GetRowCount()  
{  
    MSExcel::Range range;  
    MSExcel::Range usedRange;  
    usedRange.AttachDispatch(m_oSheet.GetUsedRange(), true);  
    range.AttachDispatch(usedRange.GetRows(), true);  
    int count = range.GetCount();  
    usedRange.ReleaseDispatch();  
    range.ReleaseDispatch();  
    return count;  
}  
  
BOOL CExcelReadWriteEx::IsCellMerge(long iRow, long iColumn)
{
	MSExcel::Range range;  
	range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)iRow),COleVariant((long)iColumn)).pdispVal, true);  
	VARIANT varMerge = range.GetMergeCells();
	if ( varMerge.boolVal == -1 )
		return TRUE;
	else
		return FALSE;
}

void CExcelReadWriteEx::GetMergeCellInfo(long iRow, long iColumn, long& lStartRow, long& lStartColumn, long& lRows, long& lColumns)
{
	if (!IsCellMerge(iRow, iColumn))
	{
		lRows = 0;
		lColumns = 0;
	}
		
	MSExcel::Range rangeArea;
	MSExcel::Range rangeRows;
	MSExcel::Range rangeColumns;
	MSExcel::Interior interiorMerge;
	MSExcel::Range range;  
	range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)iRow),COleVariant((long)iColumn)).pdispVal, true);  
	rangeArea.AttachDispatch( range.GetMergeArea(), TRUE );

	lStartRow = rangeArea.GetRow();
	lStartColumn = rangeArea.GetColumn();

	rangeRows.AttachDispatch( rangeArea.GetRows(), TRUE );
	lRows = rangeRows.GetCount();

	rangeColumns.AttachDispatch( rangeArea.GetColumns(), TRUE );
	lColumns = rangeColumns.GetCount();
}

//检查一个CELL是否是字符串  
BOOL CExcelReadWriteEx::IsCellString(long irow, long icolumn)  
{  
    MSExcel::Range range;  
    range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);  
    COleVariant vResult = range.GetValue2();  
    //VT_BSTR标示字符串  
    if(vResult.vt == VT_BSTR)         
    {  
        return TRUE;  
    }  
    return FALSE;  
}  
  
//检查一个CELL是否是数值  
BOOL CExcelReadWriteEx::IsCellInt(long irow, long icolumn)  
{  
    MSExcel::Range range;  
    range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);  
    COleVariant vResult = range.GetValue2();  

    //好像一般都是VT_R8  
    if(vResult.vt == VT_INT || vResult.vt == VT_R8)         
    {  
        return TRUE;  
    }  
    return FALSE;  
}  
  
CString CExcelReadWriteEx::GetCellString(long irow, long icolumn)  
{  
    COleVariant vResult ;  
    CString str;  

    //字符串  
    if (m_bAlreadyPreload == FALSE)  
    {  
        MSExcel::Range range;  
		try
		{
			range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);  
			vResult =range.GetValue2();  
		}
		catch (...)
		{
			int i = 0;
		}
		
        range.ReleaseDispatch();  
    }  
    //如果数据依据预先加载了  
    else  
    {  
        long read_address[2];  
        VARIANT val;  
        read_address[0] = irow;  
        read_address[1] = icolumn;  
        m_oOleSafeArray.GetElement(read_address, &val);  
        vResult = val;  
    }  
  
    if(vResult.vt == VT_BSTR)  
    {  
        str=vResult.bstrVal;  
    }  
    //整数  
    else if (vResult.vt==VT_INT)  
    {  
        str.Format(_T("%d"),vResult.pintVal);  
    }  
    //8字节的数字   
    else if (vResult.vt==VT_R8)       
    {  
        str.Format(_T("%0.0f"),vResult.dblVal);  
    }  
    //时间格式  
    else if(vResult.vt==VT_DATE)      
    {  
        SYSTEMTIME st;  
        VariantTimeToSystemTime(vResult.date, &st);  
        CTime tm(st);   
        str=tm.Format(_T("%Y-%m-%d"));  
    }  
    //单元格空的  
    else if(vResult.vt==VT_EMPTY)     
    {  
        str="";  
    }    
  
    return str;  
}  
  
double CExcelReadWriteEx::GetCellDouble(long irow, long icolumn)  
{  
    double rtn_value = 0;  
    COleVariant vresult;  
    //字符串  
    if (m_bAlreadyPreload == FALSE)  
    {  
        MSExcel::Range range;  
        range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);  
        vresult = range.GetValue2();  
        range.ReleaseDispatch();  
    }  
    //如果数据依据预先加载了  
    else  
    {  
        long read_address[2];  
        VARIANT val;  
        read_address[0] = irow;  
        read_address[1] = icolumn;  
        m_oOleSafeArray.GetElement(read_address, &val);  
        vresult = val;  
    }  
      
    if (vresult.vt==VT_R8)       
    {  
        rtn_value = vresult.dblVal;  
    }  
      
    return rtn_value;  
}  
  
//VT_R8  
int CExcelReadWriteEx::GetCellInt(long iRow, long iColumn)  
{  
    int num;  
    COleVariant vresult;  
  
    if (m_bAlreadyPreload == FALSE)  
    {  
        MSExcel::Range range;  
        range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)iRow),COleVariant((long)iColumn)).pdispVal, true);  
        vresult = range.GetValue2();  
        range.ReleaseDispatch();  
    }  
    else  
    {  
        long read_address[2];  
        VARIANT val;  
        read_address[0] = iRow;  
        read_address[1] = iColumn;  
        m_oOleSafeArray.GetElement(read_address, &val);  
        vresult = val;  
    }  
      
    num = static_cast<int>(vresult.dblVal);  
  
    return num;  
}  

void CExcelReadWriteEx::GetCellFont(long iRow, long iColumn, CString& strFontName, long& lSize, long& lBold)
{
	COleVariant vresult;

	MSExcel::Range range;  
	MSExcel::Font oFont;
	if (m_bAlreadyPreload == FALSE)  
	{  
		range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)iRow),COleVariant((long)iColumn)).pdispVal, true);  
		oFont = range.GetFont();  
		strFontName = oFont.GetName();
		lSize = oFont.GetSize().dblVal;
		lBold = oFont.GetBold().dblVal;
	}  
	else  
	{  
		long read_address[2];  
		VARIANT val;  
		read_address[0] = iRow;  
		read_address[1] = iColumn;  
//		m_oOleSafeArray.GetElement(read_address, &val);  
//		vresult = val;
	}  
	range.ReleaseDispatch(); 
	oFont.ReleaseDispatch();
}

COLORREF CExcelReadWriteEx::GetCellTextColor(long iRow, long iColumn)
{
	COLORREF colorText;
	COleVariant vresult;

	MSExcel::Range range;  
	MSExcel::Font oFont;
	if (m_bAlreadyPreload == FALSE)  
	{  
		range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)iRow),COleVariant((long)iColumn)).pdispVal, true);  
		oFont = range.GetFont();  
		COleVariant cellColor = oFont.GetColor();
		colorText = cellColor.dblVal;
	}  
	else  
	{  
		long read_address[2];  
		VARIANT val;  
		read_address[0] = iRow;  
		read_address[1] = iColumn;  
//		m_oOleSafeArray.GetElement(read_address, &val);  
//		vresult = val;
	}  
	range.ReleaseDispatch(); 
	oFont.ReleaseDispatch();

	return colorText;
}

COLORREF CExcelReadWriteEx::GetCellBKColor(long iRow, long iColumn)
{
	COLORREF colorBK;
	COleVariant vresult;

	MSExcel::Range range;  
	MSExcel::Interior interior;
	if (m_bAlreadyPreload == FALSE)  
	{  
		range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)iRow),COleVariant((long)iColumn)).pdispVal, true);  
		interior = range.GetInterior();
		COleVariant cellColor = interior.GetColor();
		colorBK = cellColor.dblVal;
	}  
	else  
	{  
		long read_address[2];  
		VARIANT val;  
		read_address[0] = iRow;  
		read_address[1] = iColumn;  
//		m_oOleSafeArray.GetElement(read_address, &val);  
//		vresult = val;
	}  
	range.ReleaseDispatch();
	interior.ReleaseDispatch();

	return colorBK;
}

void CExcelReadWriteEx::GetCellFontAndColor(long iRow, long iColumn, CString& strFontName, long& lSize, long& lBold, COLORREF& crText, COLORREF& crBK)
{
	COleVariant vresult;
	MSExcel::Font oFont;
	MSExcel::Range range;  
	MSExcel::Interior interior;
	if (m_bAlreadyPreload == FALSE)  
	{  
		range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)iRow),COleVariant((long)iColumn)).pdispVal, true);  
		oFont = range.GetFont();  
		strFontName = oFont.GetName();
		lSize = oFont.GetSize().dblVal;
		lBold = oFont.GetBold().dblVal;
		COleVariant cellTextColor = oFont.GetColor();
		crText = cellTextColor.dblVal;
		interior = range.GetInterior();
		COleVariant cellBKColor = interior.GetColor();
		crBK = cellBKColor.dblVal;
	}  
	else  
	{  
		long read_address[2];  
		VARIANT val;  
		read_address[0] = iRow;  
		read_address[1] = iColumn;  
//		m_oOleSafeArray.GetElement(read_address, &val);  
//		vresult = val;
	}  
	oFont.ReleaseDispatch();
	range.ReleaseDispatch();
	interior.ReleaseDispatch();
}

//行、列、要写入的CString  
void CExcelReadWriteEx::SetCellString(long iRow, long iColumn, const CString& strText)  
{  
	ASSERT (m_oSheet != NULL);

	if (m_oSheet == NULL)
	{
		return;
	}

    COleVariant oText(strText);  
    MSExcel::Range start_range = m_oSheet.GetRange(COleVariant(_T("A1")),covOptional);  
    MSExcel::Range write_range = start_range.GetOffset(COleVariant((long)iRow -1),COleVariant((long)iColumn -1) );  
    write_range.SetValue2(oText);  

	MSExcel::Borders oBorders = write_range.GetBorders();
	oBorders.SetLineStyle(_variant_t(1));

    start_range.ReleaseDispatch();  
    write_range.ReleaseDispatch();  
}  
//行、列、要写入的int 
void CExcelReadWriteEx::SetCellInt(long iRow, long iColumn, int nInt)  
{  
	ASSERT (m_oSheet != NULL);

	if (m_oSheet == NULL)
	{
		return;
	}

    COleVariant oInt((long)nInt);  
      
    MSExcel::Range start_range = m_oSheet.GetRange(COleVariant(_T("A1")),covOptional);  
    MSExcel::Range write_range = start_range.GetOffset(COleVariant((long)iRow -1),COleVariant((long)iColumn -1) );  
    write_range.SetValue2(oInt);  
    start_range.ReleaseDispatch();  
    write_range.ReleaseDispatch();  
}  
  
void CExcelReadWriteEx::SetCellFont(long iRow, long iColumn, const CString& strFont, long lSize, long lBold)
{
	ASSERT (m_oSheet != NULL);

	if (m_oSheet == NULL)
	{
		return;
	}

	MSExcel::Range range;  
	MSExcel::Font oFont;
	range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)iRow),COleVariant((long)iColumn)).pdispVal, true);  
	
	oFont = range.GetFont();     
	COleVariant oFontName(strFont);  
	oFont.SetName(oFontName);     
	COleVariant oFontSize(lSize); 
	oFont.SetSize(oFontSize);
	COleVariant oFontBold(lBold); 
	oFont.SetBold(oFontBold);

	range.ReleaseDispatch();
	oFont.ReleaseDispatch();
}

void CExcelReadWriteEx::SetCellTextColor(long iRow, long iColumn, COLORREF crColor)
{
	ASSERT (m_oSheet != NULL);

	if (m_oSheet == NULL)
	{
		return;
	}
 
	MSExcel::Range range; 
	MSExcel::Font oFont;
	range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)iRow),COleVariant((long)iColumn)).pdispVal, true);  
	
	COleVariant oColor((long)crColor); 
	oFont = range.GetFont();                             
	oFont.SetColor(oColor); 

	range.ReleaseDispatch();
	oFont.ReleaseDispatch();
}

void CExcelReadWriteEx::SetCellBKColor(long iRow, long iColumn, COLORREF crColor)
{
	ASSERT (m_oSheet != NULL);

	if (m_oSheet == NULL)
	{
		return;
	}

	MSExcel::Range range;  
	MSExcel::Interior interior;

	range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant((long)iRow),COleVariant((long)iColumn)).pdispVal, true);  
	
	COleVariant oColor((long)crColor);  
	interior = range.GetInterior();                             
	interior.SetColor(oColor); 

	range.ReleaseDispatch();
	interior.ReleaseDispatch();
}

void CExcelReadWriteEx::SetCellFontAndColor(long iRow, long iColumn, const CString& strFontName, long lSize, long lBold, COLORREF crText, COLORREF crBK)
{
	ASSERT (m_oSheet != NULL);

	if (m_oSheet == NULL)
	{
		return;
	}

	MSExcel::Range range;  
	MSExcel::Font oFont;
	MSExcel::Interior interior;

	range.AttachDispatch(m_oCurrentRange.GetItem (COleVariant(iRow),COleVariant(iColumn)).pdispVal, true);  

	oFont = range.GetFont();     
	COleVariant oFontName(strFontName);  
	oFont.SetName(oFontName);     
	COleVariant oFontSize(lSize); 
	oFont.SetSize(oFontSize);
	COleVariant oFontBold(lBold); 
	oFont.SetBold(oFontBold);
	COleVariant oTextColor((long)crText);  
	oFont.SetColor(oTextColor);

	interior = range.GetInterior();     
	COleVariant oBKColor((long)crBK);  
	interior.SetColor(oBKColor);

	range.ReleaseDispatch();
	oFont.ReleaseDispatch();
	interior.ReleaseDispatch();
}

void CExcelReadWriteEx::ShowInExcel(BOOL bShow)  
{  
    m_oApplication.SetVisible(bShow);  
    m_oApplication.SetUserControl(bShow);  
}  

void CExcelReadWriteEx::MergeCells(long iStartRow, long iStartColumn, long lMergeRows, long lMergeCols)
{
	MSExcel::Range beginCell;
	beginCell.AttachDispatch( m_oCurrentRange.GetItem( COleVariant(iStartRow),COleVariant(iStartColumn)).pdispVal, TRUE );
	MSExcel::Range endCell;
	endCell.AttachDispatch( m_oCurrentRange.GetItem( COleVariant((long)(iStartRow+lMergeRows-1)),COleVariant((long)(iStartColumn+lMergeCols-1))).pdispVal, TRUE );
	MSExcel::Range ExlRange;
	VARIANT beginVar,endVar;
	ExlRange.AttachDispatch(m_oSheet.GetRange((_variant_t)beginCell,(_variant_t)endCell),TRUE); 
	ExlRange.Merge(_variant_t((long)0)); 
}

void CExcelReadWriteEx::AutoFitColumns()
{
	MSExcel::Range range; 
	range = m_oSheet.GetColumns();
	range.AutoFit();
}

void CExcelReadWriteEx::AutoFitRows()
{
	MSExcel::Range range; 
	range = m_oSheet.GetRows();
	range.AutoFit();
}

void CExcelReadWriteEx::FreezeFirstRow()
{
	MSExcel::Window window;
	window = m_oApplication.GetActiveWindow();
	window.SetSplitRow(1);
	window.SetFreezePanes(TRUE);
}

void CExcelReadWriteEx::FreezeFirstCol()
{
	MSExcel::Window window;
	window = m_oApplication.GetActiveWindow();
	window.SetSplitColumn(1);
	window.SetFreezePanes(TRUE);
}

void CExcelReadWriteEx::CancelFreezePanes()
{
	MSExcel::Window window;
	window = m_oApplication.GetActiveWindow();
	window.SetFreezePanes(FALSE);
}

//返回打开的EXCEL文件名称  
CString CExcelReadWriteEx::GetOpenFileName()  
{  
    return m_strExcelFile;  
}  
  
//取得打开sheet的名称  
CString CExcelReadWriteEx::GetLoadSheetName()  
{  
    return m_oSheet.GetName();  
}  
  
//取得列的名称
char *CExcelReadWriteEx::GetColumnName(long lColumn)  
{     
    static char column_name[64];  
    size_t str_len = 0;  
      
    while(lColumn > 0)  
    {  
        int num_data = lColumn % 26;  
        lColumn /= 26;  
        if (num_data == 0)  
        {  
            num_data = 26;  
            lColumn--;  
        }  
        column_name[str_len] = (char)((num_data-1) + 'A' );  
        str_len ++;  
    }  
    column_name[str_len] = '\0';  
    //反转  
    _strrev(column_name);  
  
    return column_name;  
}  
  
//预先加载  
void CExcelReadWriteEx::PreLoadSheet()  
{  
    MSExcel::Range used_range;  
    used_range = m_oSheet.GetUsedRange();   
  
    VARIANT ret_ary = used_range.GetValue2();  
    if (!(ret_ary.vt & VT_ARRAY))  
    {  
        return;  
    }  
    //  
    m_oOleSafeArray.Clear();  
    m_oOleSafeArray.Attach(ret_ary);   
} 


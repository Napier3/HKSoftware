// ExcelReadWrite.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExcelReadWrite.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

  
COleVariant  CExcelReadWrite::covTrue((short)TRUE);
COleVariant  CExcelReadWrite::covFalse((short)FALSE);
COleVariant  CExcelReadWrite::covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);      
  
//  
//CApplication CExcelReadWrite::excel_application_;  
  
  
CExcelReadWrite::CExcelReadWrite():  
    m_bAlreadyPreload(FALSE)  
{ 
	m_oApplication = NULL;
}  
  
CExcelReadWrite::~CExcelReadWrite()  
{  
    CloseExcelFile();
	ReleaseExcel();
}  
  
  
//��ʼ��EXCEL�ļ���  
BOOL CExcelReadWrite::InitExcel()  
{  
	if (m_oApplication != NULL)
	{
		return TRUE;
	}

    //����Excel 2000������(����Excel)   
    if (!m_oApplication.CreateDispatch(_T("Excel.Application")))   
    {   
        return FALSE;  
    }  
  
    m_oApplication.put_DisplayAlerts(FALSE);   

    return TRUE;  
}  
  
//  
void CExcelReadWrite::ReleaseExcel()  
{  
    m_oApplication.Quit();  
    m_oApplication.ReleaseDispatch();  
    m_oApplication=NULL;  
}  
  
//��excel�ļ�  
BOOL CExcelReadWrite::OpenExcelFile(const CString &file_name)  
{  
    //�ȹر�  
    CloseExcelFile();  
      
    //����ģ���ļ��������ĵ�   
    m_oBooks.AttachDispatch(m_oApplication.get_Workbooks(),true);   
  
    LPDISPATCH lpDis = NULL;  

	try
	{
    lpDis = m_oBooks.Add(COleVariant(file_name));   
	}
	catch (...)
	{

	}
     

	if (lpDis)  
    {  
        m_oBook.AttachDispatch(lpDis);   
       
		//�õ�Worksheets   
        m_oSheets.AttachDispatch(m_oBook.get_Worksheets(),true);   
          
        //��¼�򿪵��ļ�����  
        m_strExcelFile = file_name;  
  
        return TRUE;  
    }  
      
    return FALSE;  
}  
  
//�رմ򿪵�Excel �ļ�,Ĭ������������ļ�  
void CExcelReadWrite::CloseExcelFile(BOOL if_save)  
{  
//     //����Ѿ��򿪣��ر��ļ�  
//     if (m_strExcelFile.IsEmpty() == FALSE)  
//     {  
//         //�������,�����û�����,���û��Լ��棬����Լ�SAVE�������Ī���ĵȴ�  
//         if (if_save)  
//         {  
//             ShowInExcel(TRUE);  
//             //ShowInExcel(FALSE);  
//         }  
//         else  
//         {  
//             //  
//             m_oBook.Close(COleVariant(short(FALSE)),COleVariant(m_strExcelFile),covOptional);  
//             m_oBooks.Close();  
//         }  
//   
//         //���ļ����������  
//         m_strExcelFile.Empty();  
//     }  
  
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
  
void CExcelReadWrite::SaveasXSLFile(const CString &xls_file)  
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
  
void CExcelReadWrite::SaveXSLFile()
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
  
int CExcelReadWrite::GetSheetCount()  
{  
    return m_oSheets.get_Count();  
}  
  
//get sheet name,������ʾ�ڼ���sheet  
CString CExcelReadWrite::GetSheetName(long table_index)  
{  
    MSExcel::CWorksheet sheet;  
    sheet.AttachDispatch(m_oSheets.get_Item(COleVariant((long)table_index)),true);  
    CString name = sheet.get_Name();  
    sheet.ReleaseDispatch();  
    return name;  
}  
  
//������ż���Sheet���,������ǰ�������еı���ڲ�����  
BOOL CExcelReadWrite::LoadSheet(long table_index,BOOL pre_load)  
{  
    LPDISPATCH lpDis = NULL;  
    m_oCurrentRange.ReleaseDispatch();  
    m_oSheet.ReleaseDispatch();  
    lpDis = m_oSheets.get_Item(COleVariant((long)table_index));  

    if (lpDis)  
    {  
        m_oSheet.AttachDispatch(lpDis,true);  
        m_oCurrentRange.AttachDispatch(m_oSheet.get_Cells(), true);  
    }  
    else  
    {  
        return FALSE;  
    }  
      
    m_bAlreadyPreload = FALSE;  

    //�������Ԥ�ȼ���  
    if (pre_load)  
    {  
        PreLoadSheet();  
        m_bAlreadyPreload = TRUE;  
    }  
  
    return TRUE;  
}  
  
//�������Ƽ���Sheet���,������ǰ�������еı���ڲ�����  
BOOL CExcelReadWrite::LoadSheet(const CString & sheet,BOOL pre_load)  
{  
    LPDISPATCH lpDis = NULL;  
    m_oCurrentRange.ReleaseDispatch();  
    m_oSheet.ReleaseDispatch();  
    lpDis = m_oSheets.get_Item(COleVariant(sheet));  
    if (lpDis)  
    {  
        m_oSheet.AttachDispatch(lpDis,true);  
        m_oCurrentRange.AttachDispatch(m_oSheet.get_Cells(), true);  
          
    }  
    else  
    {  
        return FALSE;  
    }  
    //  
    m_bAlreadyPreload = FALSE;  
    //�������Ԥ�ȼ���  
    if (pre_load)  
    {  
        m_bAlreadyPreload = TRUE;  
        PreLoadSheet();  
    }  
  
    return TRUE;  
}  
  
//�õ��е�����  
int CExcelReadWrite::GetColumnCount()  
{  
    MSExcel::CRange range;  
    MSExcel::CRange usedRange;  
    usedRange.AttachDispatch(m_oSheet.get_UsedRange(), true);  
    range.AttachDispatch(usedRange.get_Columns(), true);  
    int count = range.get_Count();  
    usedRange.ReleaseDispatch();  
    range.ReleaseDispatch();  
    return count;  
}  
  
//�õ��е�����  
int CExcelReadWrite::GetRowCount()  
{  
    MSExcel::CRange range;  
    MSExcel::CRange usedRange;  
    usedRange.AttachDispatch(m_oSheet.get_UsedRange(), true);  
    range.AttachDispatch(usedRange.get_Rows(), true);  
    int count = range.get_Count();  
    usedRange.ReleaseDispatch();  
    range.ReleaseDispatch();  
    return count;  
}  
  
//���һ��CELL�Ƿ����ַ���  
BOOL CExcelReadWrite::IsCellString(long irow, long icolumn)  
{  
    MSExcel::CRange range;  
    range.AttachDispatch(m_oCurrentRange.get_Item (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);  
    COleVariant vResult =range.get_Value2();  
    //VT_BSTR��ʾ�ַ���  
    if(vResult.vt == VT_BSTR)         
    {  
        return TRUE;  
    }  
    return FALSE;  
}  
  
//���һ��CELL�Ƿ�����ֵ  
BOOL CExcelReadWrite::IsCellInt(long irow, long icolumn)  
{  
    MSExcel::CRange range;  
    range.AttachDispatch(m_oCurrentRange.get_Item (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);  
    COleVariant vResult =range.get_Value2();  
    //����һ�㶼��VT_R8  
    if(vResult.vt == VT_INT || vResult.vt == VT_R8)         
    {  
        return TRUE;  
    }  
    return FALSE;  
}  
  
//  
CString CExcelReadWrite::GetCellString(long irow, long icolumn)  
{  
    COleVariant vResult ;  
    CString str;  
    //�ַ���  
    if (m_bAlreadyPreload == FALSE)  
    {  
        MSExcel::CRange range;  

		try
		{
			range.AttachDispatch(m_oCurrentRange.get_Item (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);  
			vResult =range.get_Value2();  
		}
		catch (...)
		{
			int i = 0;
		}
		
        range.ReleaseDispatch();  
    }  
    //�����������Ԥ�ȼ�����  
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
    //����  
    else if (vResult.vt==VT_INT)  
    {  
        str.Format(_T("%d"),vResult.pintVal);  
    }  
    //8�ֽڵ�����   
    else if (vResult.vt==VT_R8)       
    {  
        str.Format(_T("%0.0f"),vResult.dblVal);  
    }  
    //ʱ���ʽ  
    else if(vResult.vt==VT_DATE)      
    {  
        SYSTEMTIME st;  
        VariantTimeToSystemTime(vResult.date, &st);  
        CTime tm(st);   
        str=tm.Format(_T("%Y-%m-%d"));  
  
    }  
    //��Ԫ��յ�  
    else if(vResult.vt==VT_EMPTY)     
    {  
        str="";  
    }    
  
    return str;  
}  
  
double CExcelReadWrite::GetCellDouble(long irow, long icolumn)  
{  
    double rtn_value = 0;  
    COleVariant vresult;  
    //�ַ���  
    if (m_bAlreadyPreload == FALSE)  
    {  
        MSExcel::CRange range;  
        range.AttachDispatch(m_oCurrentRange.get_Item (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);  
        vresult =range.get_Value2();  
        range.ReleaseDispatch();  
    }  
    //�����������Ԥ�ȼ�����  
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
int CExcelReadWrite::GetCellInt(long irow, long icolumn)  
{  
    int num;  
    COleVariant vresult;  
  
    if (m_bAlreadyPreload == FALSE)  
    {  
        MSExcel::CRange range;  
        range.AttachDispatch(m_oCurrentRange.get_Item (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);  
        vresult = range.get_Value2();  
        range.ReleaseDispatch();  
    }  
    else  
    {  
        long read_address[2];  
        VARIANT val;  
        read_address[0] = irow;  
        read_address[1] = icolumn;  
        m_oOleSafeArray.GetElement(read_address, &val);  
        vresult = val;  
    }  
    //  
    num = static_cast<int>(vresult.dblVal);  
  
    return num;  
}  
//�С��С�Ҫд���CString  
void CExcelReadWrite::SetCellString(long irow, long icolumn,CString new_string)  
{  
	ASSERT (m_oSheet != NULL);

	if (m_oSheet == NULL)
	{
		return;
	}

    COleVariant new_value(new_string);  
    MSExcel::CRange start_range = m_oSheet.get_Range(COleVariant(_T("A1")),covOptional);  
    MSExcel::CRange write_range = start_range.get_Offset(COleVariant((long)irow -1),COleVariant((long)icolumn -1) );  
    write_range.put_Value2(new_value);  
    start_range.ReleaseDispatch();  
    write_range.ReleaseDispatch();  
  
}  
//�С��С�Ҫд���int  
void CExcelReadWrite::SetCellInt(long irow, long icolumn,int new_int)  
{  
    COleVariant new_value((long)new_int);  
      
    MSExcel::CRange start_range = m_oSheet.get_Range(COleVariant(_T("A1")),covOptional);  
    MSExcel::CRange write_range = start_range.get_Offset(COleVariant((long)irow -1),COleVariant((long)icolumn -1) );  
    write_range.put_Value2(new_value);  
    start_range.ReleaseDispatch();  
    write_range.ReleaseDispatch();  
}  
  
  
//  
void CExcelReadWrite::ShowInExcel(BOOL bShow)  
{  
    m_oApplication.put_Visible(bShow);  
    m_oApplication.put_UserControl(bShow);  
}  
  
//���ش򿪵�EXCEL�ļ�����  
CString CExcelReadWrite::GetOpenFileName()  
{  
    return m_strExcelFile;  
}  
  
//ȡ�ô�sheet������  
CString CExcelReadWrite::GetLoadSheetName()  
{  
    return m_oSheet.get_Name();  
}  
  
//ȡ���е����ƣ�����27->AA  
char *CExcelReadWrite::GetColumnName(long icolumn)  
{     
    static char column_name[64];  
    size_t str_len = 0;  
      
    while(icolumn > 0)  
    {  
        int num_data = icolumn % 26;  
        icolumn /= 26;  
        if (num_data == 0)  
        {  
            num_data = 26;  
            icolumn--;  
        }  
        column_name[str_len] = (char)((num_data-1) + 'A' );  
        str_len ++;  
    }  
    column_name[str_len] = '\0';  
    //��ת  
    _strrev(column_name);  
  
    return column_name;  
}  
  
//Ԥ�ȼ���  
void CExcelReadWrite::PreLoadSheet()  
{  
  
    MSExcel::CRange used_range;  
  
    used_range = m_oSheet.get_UsedRange();   
  
  
    VARIANT ret_ary = used_range.get_Value2();  
    if (!(ret_ary.vt & VT_ARRAY))  
    {  
        return;  
    }  
    //  
    m_oOleSafeArray.Clear();  
    m_oOleSafeArray.Attach(ret_ary);   
} 


//Columns("A:A").EntireColumn.AutoFit
void CExcelReadWrite::AutoFit(long nColumn)
{
	ASSERT (m_oSheet != NULL);

	if (m_oSheet == NULL)
	{
		return;
	}

	MSExcel::CRange start_range = m_oSheet.get_Range(COleVariant(_T("A1")),covOptional);  
	MSExcel::CRange write_range = start_range.get_Offset(COleVariant((long)0),COleVariant((long)nColumn-1) );  

	try
	{
		write_range.AutoFit();
	}
	catch (...)
	{
	}

	start_range.ReleaseDispatch();  
	write_range.ReleaseDispatch();  
}

void CExcelReadWrite::SetColWidth(long nColumn, long nWidth)
{
	ASSERT (m_oSheet != NULL);

	if (m_oSheet == NULL)
	{
		return;
	}

	MSExcel::CRange start_range = m_oSheet.get_Range(COleVariant(_T("A1")),covOptional);  
	MSExcel::CRange write_range = start_range.get_Offset(COleVariant((long)0),COleVariant((long)nColumn-1) );  

	try
	{
// 		COleVariant vWidth = write_range.get_ColumnWidth();
// 		vWidth = write_range.get_ColumnWidth();
// 		vWidth = write_range.get_ColumnWidth();
		write_range.put_ColumnWidth(COleVariant((long)nWidth));
	}
	catch (...)
	{
	}

	start_range.ReleaseDispatch();  
	write_range.ReleaseDispatch();  
}


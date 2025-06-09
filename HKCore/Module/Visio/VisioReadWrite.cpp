// ExcelReadWrite.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VisioReadWrite.h"
#include "../API/FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

  
COleVariant  CVisioReadWrite::covTrue((short)TRUE);
COleVariant  CVisioReadWrite::covFalse((short)FALSE);
COleVariant  CVisioReadWrite::covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);      
  
//  
//CApplication CExcelReadWrite::excel_application_;  
  
  
CVisioReadWrite::CVisioReadWrite()
{ 
	m_oCurDoc = NULL;
	m_oApplication = NULL;
	m_oPages = NULL;
	m_oCurPage = NULL;
}  
  
CVisioReadWrite::~CVisioReadWrite()  
{  
	m_oPageList.DeleteAll();
    CloseVisioFile();
	ReleaseVisio();
}  
  
  
//初始化Visio文件，  
BOOL CVisioReadWrite::InitVisio(BOOL bVisible)  
{  
	if (m_oApplication != NULL)
	{
		return TRUE;
	}

    //创建Excel 2000服务器(启动Excel)   
    if (!m_oApplication.CreateDispatch(_T("Visio.Application")))   
    {   
        return FALSE;  
    }  
  
	m_oApplication.put_Visible(bVisible);
   // m_oApplication.put_DisplayAlerts(FALSE);   

    return TRUE;  
}  
  
//  
void CVisioReadWrite::ReleaseVisio()  
{  
	m_oCurPage = NULL;
	m_oPages = NULL;
	m_oCurDoc = NULL;

	if (m_oApplication != NULL)
	{
		m_oApplication.Quit();  
		m_oApplication.ReleaseDispatch();  
		m_oApplication=NULL;  
	}
}  
  
//打开excel文件  
BOOL CVisioReadWrite::OpenVisioFile(const CString &file_name, BOOL bVisible)  
{  
    //先关闭  
    CloseVisioFile();  
	InitVisio(bVisible);
     
	if (!IsFileExist(file_name))
	{
		return FALSE;
	}

	if ( m_oApplication == NULL)
	{
		return FALSE;
	}

	MSVisio15::CVDocuments docs = NULL;
	docs =  m_oApplication.get_Documents();

	if (docs == NULL)
	{
		return FALSE;
	}

	BOOL bTrue = TRUE;

	try
	{
		//打开试验报告文件
		m_oCurDoc = docs.Open(file_name);
	}
	catch (...)
	{
		bTrue = FALSE;
	}

	if (bTrue)  
    {  
        //记录打开的文件名称  
        m_strVisioFile = file_name;  
		LoadPage_List();
        return TRUE;  
    }  
      
    return FALSE;  
}  
  
//关闭打开的Excel 文件,默认情况不保存文件  
void CVisioReadWrite::CloseVisioFile(BOOL if_save)  
{  
	if (m_oApplication == NULL)
	{
		return;
	}

	if (m_oCurDoc == NULL)
	{
		return;
	}

	try
	{
		m_oCurDoc.Close();  
		m_oCurDoc = NULL;
	}
	catch (...)
	{
		
	}
}  

void CVisioReadWrite::CloseApplication()
{
	if (m_oApplication == NULL)
	{
		return;
	}

	try
	{
		MSVisio15::CVDocuments oDocs = m_oApplication.get_Documents();

		if (oDocs.get_Count() > 0)
		{
			return;
		}

	}
	catch (...)
	{
		TRACE("catch error-----");
	}

	try
	{
		m_oApplication.Quit();
		m_oApplication = NULL;

	}
	catch (...)
	{
		TRACE("catch error-----");
	}
}
  
BOOL CVisioReadWrite::SaveasVsdFile(const CString &xls_file)  
{  
	if( m_oApplication == NULL || m_oCurDoc == NULL)
		return FALSE;

	m_strVisioFile = xls_file;

    m_oCurDoc.SaveAs(xls_file);  
    return TRUE;  
}  
  
BOOL CVisioReadWrite::SaveVsdFile()
{
	if( m_oApplication == NULL || m_oCurDoc == NULL || m_strVisioFile.IsEmpty())
		return FALSE;

	m_oCurDoc.SaveAs(m_strVisioFile);   
	return TRUE;
}
  
int CVisioReadWrite::GetPageCount()  
{  
	if (m_oPages == NULL)
	{
		return 0;
	}

    return m_oPages.get_Count();  
}  
  
//get sheet name,参数表示第几个sheet  
CString CVisioReadWrite::GetPageName(long page_index)  
{  
	if (m_oPages == NULL)
	{
		return _T("");
	}
 
	CString strName;
	VARIANT oVal;
	oVal.vt = VT_I4;
	oVal.lVal = page_index;
	MSVisio15::CVPage oPage = m_oPages.get_Item(oVal);

	if (oPage == NULL)
	{
		return _T("");
	}
 
	strName = oPage.get_Name();
    return strName;  
}  
  
//按照序号加载Sheet表格,可以提前加载所有的表格内部数据  
BOOL CVisioReadWrite::LoadPage(long nPageIndex)  
{  
	if (m_oCurDoc == NULL)
	{
		return FALSE;
	}

	if (m_oPages == NULL)
	{
		m_oPages = m_oCurDoc.get_Pages();
	}

	long nPageCount = m_oPages.get_Count();
	MSVisio15::CVPage oCurPage;
	VARIANT oVal;
	oVal.vt = VT_I4;
	oVal.lVal = nPageIndex;

	try
	{
		oCurPage = m_oPages.get_Item(oVal);
	}
	catch (...)
	{
		return FALSE;
	}
       
	m_oCurPage = oCurPage;
    return ActivePage(m_oCurPage.get_Name());  
}  
  
//按照名称加载Sheet表格,可以提前加载所有的表格内部数据  
BOOL CVisioReadWrite::LoadPage(const CString & strPageName)  
{  
	if (m_oCurDoc == NULL)
	{
		return FALSE;
	}

	if (m_oPages == NULL)
	{
		m_oPages = m_oCurDoc.get_Pages();
	} 
  
	long nPageCount = m_oPages.get_Count();
	MSVisio15::CVPage oCurPage;
	CString strTmp;
	VARIANT oVal;
	oVal.vt = VT_I4;

	for (int nIndex = 1;nIndex<=nPageCount;nIndex++)
	{
		oVal.lVal = nIndex;

		try
		{
			oCurPage = m_oPages.get_Item(oVal);
		}
		catch (...)
		{
			continue;
		}

		strTmp = oCurPage.get_Name();

		if (strTmp == strPageName)
		{
			m_oCurPage = oCurPage;
			return ActivePage(m_oCurPage.get_Name());  
		}
	}

    return FALSE;  
}   
  
void CVisioReadWrite::LoadPage_List()
{
	if (m_oCurDoc == NULL)
	{
		return;
	}

	if (m_oPages == NULL)
	{
		m_oPages = m_oCurDoc.get_Pages();
	} 

	m_oPageList.DeleteAll();

	long nPageCount = m_oPages.get_Count();
	MSVisio15::CVPage oCurPage;
	CString strTmp;
	VARIANT oVal;
	oVal.vt = VT_I4;

	for (int nIndex = 1;nIndex<=nPageCount;nIndex++)
	{
		oVal.lVal = nIndex;

		try
		{
			oCurPage = m_oPages.get_Item(oVal);
		}
		catch (...)
		{
			continue;
		}

		strTmp = oCurPage.get_Name();

		CExBaseObject *pPage = new CExBaseObject;
		pPage->m_strName = strTmp;
		pPage->m_strID = strTmp;

		m_oPageList.AddNewChild(pPage);
	}
}

//  
void CVisioReadWrite::ShowInVisio(BOOL bShow)  
{  
    m_oApplication.put_Visible(bShow);  
}  
  
//返回打开的EXCEL文件名称  
CString CVisioReadWrite::GetOpenFileName()  
{  
    return m_strVisioFile;  
}  
  
//取得打开sheet的名称  
CString CVisioReadWrite::GetLoadPageName()  
{  
	if (m_oCurPage == NULL)
	{
		return _T("");
	}

    return m_oCurPage.get_Name();  
}  
  
BOOL CVisioReadWrite::ActivePage(const CString strPageName)
{
	if (m_oApplication == NULL)
	{
		return FALSE;
	}

	MSVisio15::CVWindow oActiveWindow;
	try
	{
		oActiveWindow = m_oApplication.get_ActiveWindow();
	}
	catch(...)
	{
		return FALSE;
	}

	VARIANT oVal;
	oVal.vt = VT_I4;

	try
	{
		oActiveWindow.put_PageFromName(strPageName);
	}
	catch(...)
	{
		return FALSE;
	}

	return TRUE;
}

MSVisio15::CVShapes CVisioReadWrite::GetCurShapes()
{
	if (m_oCurPage == NULL)
	{
		return NULL;
	}

	return m_oCurPage.get_Shapes();
}

BOOL CVisioReadWrite::ActiveCurParsePage()
{
	if (m_oCurPage == NULL)
	{
		return FALSE;
	}

	CString strCurPageName;
	strCurPageName = m_oCurPage.get_Name();
	return ActivePage(strCurPageName);
}
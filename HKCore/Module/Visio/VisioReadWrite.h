// ExcelReadWrite.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_VisioReadWrite_H__)
#define _VisioReadWrite_H__

#include "MSVisio15.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///用于OLE的方式的EXCEL读写，  
class CVisioReadWrite  
{  
protected:
	static COleVariant  covTrue;//((short)TRUE);
	static COleVariant  covFalse;//((short)FALSE);
	static COleVariant  covOptional;//((long)DISP_E_PARAMNOTFOUND, VT_ERROR);      

public:  
  
    //构造函数和析构函数  
    CVisioReadWrite();  
    virtual ~CVisioReadWrite();  
  
protected:  
    ///打开的EXCEL文件名称  
    CString       m_strVisioFile;  
  
    ///当前使用的BOOK，当前处理的文件  
    MSVisio15::CVDocument     m_oCurDoc;   
    ///EXCEL的sheets集合  
   MSVisio15:: CVPages   m_oPages;   
    ///当前使用sheet  
    MSVisio15::CVPage    m_oCurPage;  //当前解析的页 
//     ///当前的操作区域  
//     MSExcel::CRange        m_oCurrentRange;   
  
    COleSafeArray m_oOleSafeArray;  
	CExBaseList m_oPageList;   //所有页面形成的链表，可以用于下拉框等控件显示；
  
protected:  
  
    ///EXCEL的进程实例  
    MSVisio15::CVApplication m_oApplication;  

public:   
    void ShowInVisio(BOOL bShow);  
	MSVisio15::CVPage GetCurPage(){return m_oCurPage;}
	MSVisio15::CVShapes GetCurShapes();//获取当前Shapes集合对象
	MSVisio15::CVDocument GetCurDoc()	{	return m_oCurDoc;	}
	MSVisio15::CVApplication GetApplication()	{	return m_oApplication;	}
    BOOL ActiveCurParsePage();//激活当前解析的页
  
    ///使用某个shet，shit，shit,按照序号加载sheet  
    BOOL LoadPage(long nPageIndex);  
    ///通过名称使用某个sheet，按照名称加载sheet  
    BOOL LoadPage(const CString &strPageName);  
	void LoadPage_List(); //遍历所有page，形成m_oPageList链表
    ///通过序号取得某个Sheet的名称  
    CString GetPageName(long page_index); 
	CExBaseList* GetPageList()	{	return &m_oPageList;	}
  
    ///得到Sheet的总数  
    int GetPageCount();  
  
    ///打开文件  
    BOOL OpenVisioFile(const CString &file_name, BOOL bVisible = TRUE);  
    ///关闭打开的Excel 文件，有时候打开EXCEL文件就要  
    void CloseVisioFile(BOOL if_save = FALSE);
	void CloseApplication();
    //另存为一个EXCEL文件  
    BOOL SaveasVsdFile(const CString &xls_file);  
	BOOL SaveVsdFile();  
   ///取得打开文件的路径  
    CString GetOpenFileName();  
    ///取得打开sheet的名称  
    CString GetLoadPageName();  
public:  
    ///初始化EXCEL OLE  
    BOOL InitVisio(BOOL bVisible = TRUE);  
    ///释放EXCEL的 OLE  
    void ReleaseVisio();  
	BOOL ActivePage(const CString strPageName);
};  

static const CString g_strVisioFileFilter = _T("Visio File (*.vsd;*.vsdx)|*.vsd;*.vsdx|Visio File (*.vsd)|*.vsd|Visio File (*.vsdx)|*.vsdx||");


#endif // !defined(_WORDBASECLASS_H__)

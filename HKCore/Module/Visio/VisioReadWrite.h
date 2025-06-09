// ExcelReadWrite.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_VisioReadWrite_H__)
#define _VisioReadWrite_H__

#include "MSVisio15.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///����OLE�ķ�ʽ��EXCEL��д��  
class CVisioReadWrite  
{  
protected:
	static COleVariant  covTrue;//((short)TRUE);
	static COleVariant  covFalse;//((short)FALSE);
	static COleVariant  covOptional;//((long)DISP_E_PARAMNOTFOUND, VT_ERROR);      

public:  
  
    //���캯������������  
    CVisioReadWrite();  
    virtual ~CVisioReadWrite();  
  
protected:  
    ///�򿪵�EXCEL�ļ�����  
    CString       m_strVisioFile;  
  
    ///��ǰʹ�õ�BOOK����ǰ������ļ�  
    MSVisio15::CVDocument     m_oCurDoc;   
    ///EXCEL��sheets����  
   MSVisio15:: CVPages   m_oPages;   
    ///��ǰʹ��sheet  
    MSVisio15::CVPage    m_oCurPage;  //��ǰ������ҳ 
//     ///��ǰ�Ĳ�������  
//     MSExcel::CRange        m_oCurrentRange;   
  
    COleSafeArray m_oOleSafeArray;  
	CExBaseList m_oPageList;   //����ҳ���γɵ�������������������ȿؼ���ʾ��
  
protected:  
  
    ///EXCEL�Ľ���ʵ��  
    MSVisio15::CVApplication m_oApplication;  

public:   
    void ShowInVisio(BOOL bShow);  
	MSVisio15::CVPage GetCurPage(){return m_oCurPage;}
	MSVisio15::CVShapes GetCurShapes();//��ȡ��ǰShapes���϶���
	MSVisio15::CVDocument GetCurDoc()	{	return m_oCurDoc;	}
	MSVisio15::CVApplication GetApplication()	{	return m_oApplication;	}
    BOOL ActiveCurParsePage();//���ǰ������ҳ
  
    ///ʹ��ĳ��shet��shit��shit,������ż���sheet  
    BOOL LoadPage(long nPageIndex);  
    ///ͨ������ʹ��ĳ��sheet���������Ƽ���sheet  
    BOOL LoadPage(const CString &strPageName);  
	void LoadPage_List(); //��������page���γ�m_oPageList����
    ///ͨ�����ȡ��ĳ��Sheet������  
    CString GetPageName(long page_index); 
	CExBaseList* GetPageList()	{	return &m_oPageList;	}
  
    ///�õ�Sheet������  
    int GetPageCount();  
  
    ///���ļ�  
    BOOL OpenVisioFile(const CString &file_name, BOOL bVisible = TRUE);  
    ///�رմ򿪵�Excel �ļ�����ʱ���EXCEL�ļ���Ҫ  
    void CloseVisioFile(BOOL if_save = FALSE);
	void CloseApplication();
    //���Ϊһ��EXCEL�ļ�  
    BOOL SaveasVsdFile(const CString &xls_file);  
	BOOL SaveVsdFile();  
   ///ȡ�ô��ļ���·��  
    CString GetOpenFileName();  
    ///ȡ�ô�sheet������  
    CString GetLoadPageName();  
public:  
    ///��ʼ��EXCEL OLE  
    BOOL InitVisio(BOOL bVisible = TRUE);  
    ///�ͷ�EXCEL�� OLE  
    void ReleaseVisio();  
	BOOL ActivePage(const CString strPageName);
};  

static const CString g_strVisioFileFilter = _T("Visio File (*.vsd;*.vsdx)|*.vsd;*.vsdx|Visio File (*.vsd)|*.vsd|Visio File (*.vsdx)|*.vsdx||");


#endif // !defined(_WORDBASECLASS_H__)

// CmdBarButton.cpp: implementation of the CXmlDocTransWord class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmlDocTransWord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define	DEBUG_USE_MSG

CXmlDocTransWord::CXmlDocTransWord()
{
	Enter();
}

CXmlDocTransWord::~CXmlDocTransWord()
{
	
}

void CXmlDocTransWord::XmlDocTrans(const CString &strDocFile)
{
	m_strXmlDocFile = strDocFile;


	Enter();

	if (IsXmlDocFile(strDocFile) != 1)
	{//�ж��ļ��Ƿ�xml��ʽ
		return;
	}

	MessageTickCount(_T("IsXmlDocFile"));

	//����OfficeWord
	GetWordApp(FALSE);

	if (m_WordApp == NULL)
	{
		return;
	}


	MessageTickCount(_T("Start Word:"));

	XmlDocTrans();

	GetTickCountLong(TRUE);
	try
	{
		if (m_WordApp != NULL)
		{//�ر�Word
			COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
				vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
			m_WordApp.Quit(vFalse,vOpt,vOpt);
			m_WordApp = NULL;
		}
	}
	catch (...) 
	{
	}

	MessageTickCount(_T("CloseWord"));
}

	
long CXmlDocTransWord::IsXmlDocFile(const CString &strDocFile)
{
#ifdef _UNICODE
	FILE *pFile = _wfopen(strDocFile.GetString(), _T("r"));
#else
	FILE *pFile = fopen(strDocFile.GetString(), _T("r"));
#endif

	if (pFile == NULL)
	{
		_tprintf(strDocFile);
		_tprintf(_T(" : is not exist!\n"));

		return -1;
	}

	char pszBuffer[32];
	
	long nRead = fread(pszBuffer, 5, 1, pFile);
	fclose(pFile);

	if (memcmp(pszBuffer, "<?xml", 5) == 0)
	{
		return 1;
	}
	else
	{
		_tprintf(strDocFile);
		_tprintf(_T(" : is not xml file\n"));
		return 0;
	}
}

void CXmlDocTransWord::GetWordApp(BOOL bShow)
{
	if (m_WordApp != NULL)
	{
		return ;
	}

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	
	try
	{
		if (!m_WordApp.CreateDispatch(_T("Word.Application")))
		{
			_tprintf(_T("û�а�װWord"));
			return ;
		}

		m_WordApp.SetVisible(bShow);  //This shows the application.
	}
	catch (...)
	{
		_tprintf(_T("******��WINWORD.EXE�쳣******"));
	}
}


void CXmlDocTransWord::XmlDocTrans()
{
	MSWord::Documents docs =  m_WordApp.GetDocuments();
	MSWord::_Document oDocSrc = NULL;
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant FileFormat((long)0);
	COleVariant Password(_T(""));
	COleVariant WritePassword(_T(""));
	CString strRptTmplFile;
	CString strPrjRptFile;

	COleVariant vRptFile(m_strXmlDocFile);	
	Enter();

	try
	{
		//�����鱨���ļ�
		oDocSrc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue);

	}
	catch (...)
	{
		return;
	}

	MessageTickCount(_T("OpenWord"));

	//�����ĵ�����
	MSWord::Selection wordSelection = m_WordApp.GetSelection();
	wordSelection.WholeStory();
	wordSelection.Copy();

	MessageTickCount(_T("Copy Src Data"));
	MSWord::_Document oDocDest = NULL;
	COleVariant vTmplFile(_T(""));			

	try
	{
		//��ӿ��ļ�
		oDocDest = docs.Add(&vTmplFile,&covFalse,&FileFormat,&covTrue);
	}
	catch (...)
	{
		return;
	}

	MessageTickCount(_T("AddNewDoc"));

	try
	{
		//ճ���ĵ�����
		oDocDest.Activate();
		wordSelection = m_WordApp.GetSelection();
		wordSelection.Paste();	

		wordSelection.WholeStory();
		MSWord::Range oRange = wordSelection.GetRange();
		MSWord::Options opt = m_WordApp.GetOptions();
		opt.SetDefaultHighlightColorIndex(MSWord::wdNoHighlight);
		oRange.SetHighlightColorIndex(MSWord::wdNoHighlight);
	}
	catch (...)
	{
		return;
	}

	MessageTickCount(_T("Paste"));

	try
	{
		//�ر�Դ�ĵ�
		oDocSrc.Close(covFalse,covOptional,covOptional);
	}
	catch (...)
	{	
	}
	
	MessageTickCount(_T("Close Src Doc"));

	try
	{
		//���Ϊ�������ĵ�
		oDocDest.SaveAs(vRptFile, covOptional, covOptional, covOptional,
			covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);
	}
	catch (...)
	{	
	}

	MessageTickCount(_T("SaveAs"));
	try
	{
		//�ر��ĵ�
		oDocDest.Close(covFalse,covOptional,covOptional);
	}
	catch (...)
	{	
	}

	MessageTickCount(_T("Close Doc"));
}

void CXmlDocTransWord::MessageTickCount(const CString &strTitle)
{
#ifndef DEBUG_USE_MSG
	return;
#endif

	CString strMsg;
	DWORD dwLong = GetTickCountLong(TRUE);
	strMsg.Format(_T("%s : %d\n"), strTitle, dwLong);
	_tprintf(strMsg);

	Enter();
}


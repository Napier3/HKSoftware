// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "PdfFileToText.h"

#include "acrobat.h"
#include "..\MemBuffer\ExpandMemBuf.h"
#include "..\API\FileApi.h"
#include "PdfTextParse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


bool PdfToTxt(const std::string &PdfFile,const std::string &TxtOutPath)
{	
	int i = 0;

	int LastDotPos=0,LastSlashPos=0;
	for (i=0; i<PdfFile.length(); i++)
		if (PdfFile[i] == '.')   LastDotPos = i;
		else if(PdfFile[i] == '\\')   LastSlashPos = i;
		std::string TxtFileName = TxtOutPath + PdfFile.substr(LastSlashPos+1,LastDotPos-LastSlashPos)+"txt";

		FILE *fp = fopen(TxtFileName.c_str(),"wb");
		if (fp==NULL)
			return false;

		COleException e;

		Adobe::CAcroApp app;
		app.CreateDispatch("AcroExch.App",&e);

		Adobe::CAcroHiliteList hl;
		hl.CreateDispatch("AcroExch.HiliteList",&e);
		hl.Add(0,32767);//范围是从0到最大

		Adobe::CAcroPDDoc pddoc;
		pddoc.CreateDispatch("AcroExch.PDDoc",&e);

		try{

			if(!pddoc.Open(PdfFile.c_str()))  
			{   
				app.ReleaseDispatch();
				pddoc.ReleaseDispatch();
				return false;
			}

			Adobe::CAcroPDPage pdp;
			Adobe::CAcroPDTextSelect pdts;
			long pagenums = pddoc.GetNumPages();//页数
			CString strText;

			for(i=0; i<pagenums; i++)
			{
				pdp = pddoc.AcquirePage(i);
				pdts = pdp.CreateWordHilite(hl);
				long n = pdts.GetNumText();	/*char buf[32];	MessageBox(itoa(n,buf,10));	显示选中的字符数*/

				for(long j=0; j<n; j++)
				{
					strText = pdts.GetText(j);
					//AfxMessageBox((LPSTR)(LPCTSTR)pdts.GetText(j));
					fputs((LPSTR)(LPCTSTR)strText, fp);
				}
			}
		}
		catch (...) {
			fclose(fp);
			pddoc.Close();
			pddoc.ReleaseDispatch();
			hl.ReleaseDispatch();
			app.Exit();
			app.ReleaseDispatch();
			return false;
		}

		fclose(fp);
		pddoc.Close();
		pddoc.ReleaseDispatch();
		hl.ReleaseDispatch();
		app.Exit();
		app.ReleaseDispatch();
		return true;
}

BOOL PdfToText(const std::string &PdfFile, CExpandMemBuf &oBuffer)
{	
	int i = 0;
	CString strFile;
	strFile = PdfFile.c_str();
	long nLen = file_GetFileSize(strFile);
	oBuffer.AllocBuffer(nLen / 40);
	COleException e;

	Adobe::CAcroApp app;
	app.CreateDispatch("AcroExch.App",&e);

	if (app == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("没有安装  AcroExch.App"));
		return FALSE;
	}

	Adobe::CAcroHiliteList hl;
	hl.CreateDispatch("AcroExch.HiliteList",&e);
	hl.Add(0,32767);//范围是从0到最大

	Adobe::CAcroPDDoc pddoc;
	pddoc.CreateDispatch("AcroExch.PDDoc",&e);

	try{

		if(!pddoc.Open(strFile))  
		{   
			app.ReleaseDispatch();
			pddoc.ReleaseDispatch();
			return false;
		}

		Adobe::CAcroPDPage pdp;
		Adobe::CAcroPDTextSelect pdts;
		long pagenums = pddoc.GetNumPages();//页数
		CString strText;

		for(i=0; i<pagenums; i++)
		{
			pdp = pddoc.AcquirePage(i);
			pdts = pdp.CreateWordHilite(hl);
			long n = pdts.GetNumText();

			for(long j=0; j<n; j++)
			{
				strText = pdts.GetText(j);
				oBuffer.AppendBuffer((BYTE*)strText.GetString(), strText.GetLength());
			}
		}
	}
	catch (...) 
	{
		pddoc.Close();
		pddoc.ReleaseDispatch();
		hl.ReleaseDispatch();
		app.Exit();
		app.ReleaseDispatch();
		return false;
	}

	pddoc.Close();
	pddoc.ReleaseDispatch();
	hl.ReleaseDispatch();
	app.Exit();
	app.ReleaseDispatch();

	return true;
}

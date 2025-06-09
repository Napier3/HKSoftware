#pragma once
#include "..\Office\msword9.h"
#include <WinSpool.h>  
#pragma comment(lib, "Winspool.lib")  

#include <shellapi.h>  
#pragma comment(lib, "shell32.lib") 

#include "..\..\Module\XfileMngrBase\XFileMngr.h"

class CStampPos
{
public:
	CStampPos(){
		m_nStampNo = 0;
		m_nPageNo = 0;
		m_nLeftMargin = 0;
		m_nTopMargin = 0;	
		m_nOffsetW = 0;
		m_nOffsetH = 0;
		m_bRotate = false;
	};
	virtual ~CStampPos(){};

public:
	int m_nStampNo;
	int m_nPageNo;
	int m_nLeftMargin;
	int m_nTopMargin;
	int m_nOffsetW;
	int m_nOffsetH;
	bool m_bRotate;
	bool m_bUse;
};

class CTesterSignPos
{
public:
	CTesterSignPos(){
		m_strMainTester = _T("");
		m_strSubTester = _T("");
		m_nMainPosX1 = 0;
		m_nMainPosY1 = 0;
		m_nMainPosX2 = 0;
		m_nMainPosY2 = 0;
		m_nSubPosX = 0;
		m_nSubPosY = 0;
		m_bReplace = false;
		m_bUse = false;
	};
	virtual ~CTesterSignPos(){};

public:
	CString m_strMainTester;
	CString m_strSubTester;
	int m_nMainPosX1;
	int m_nMainPosY1;
	int m_nMainPosX2;
	int m_nMainPosY2;
	int m_nSubPosX;
	int m_nSubPosY;
	bool m_bReplace;
	bool m_bUse;
};

class CAuditorSignPos
{
public:
	CAuditorSignPos(){
		m_strCurAuditor = _T("");
		m_strAuditTitle = _T("");
		m_nPosX = 0;
		m_nPosY = 0;
		m_bReplace = false;	
	};
	virtual ~CAuditorSignPos(){};

public:
	CString m_strCurAuditor;
	CString m_strAuditTitle;
	int m_nPosX;
	int m_nPosY;
	bool m_bReplace;
};

class CApproverSignPos
{
public:
	CApproverSignPos(){
		m_strCurApprover = _T("");
		m_strApproveTitle = _T("");
		m_nPosX = 0;
		m_nPosY = 0;
		m_bReplace = false;	
	};
	virtual ~CApproverSignPos(){};

public:
	CString m_strCurApprover;
	CString m_strApproveTitle;
	int m_nPosX;
	int m_nPosY;
	bool m_bReplace;
};

class CRevisionerSignPos
{
public:
	CRevisionerSignPos(){
		m_strCurRevisioner = _T("");
		m_strPrevRevisioner = _T("");
		m_strRevisionTitle = _T("");
		m_nPosX = 0;
		m_nPosY = 0;
		m_bReplace = false;	
	};
	virtual ~CRevisionerSignPos(){};

public:
	CString m_strCurRevisioner;
	CString m_strPrevRevisioner;
	CString m_strRevisionTitle;
	int m_nPosX;
	int m_nPosY;
	bool m_bReplace;
};

class CTypistSignPos
{
public:
	CTypistSignPos(){
		m_strTypeTitle = _T("");
		m_strCurTypist = _T("");
		m_nPosX = 0;
		m_nPosY = 0;
		m_bReplace = false;	
		m_bTypeErase = false;
	};
	virtual ~CTypistSignPos(){};

public:
	CString m_strTypeTitle;
	CString m_strCurTypist;
	int m_nPosX;
	int m_nPosY;
	bool m_bReplace;
	bool m_bTypeErase;
};

class CWordToPdf
{
public:
	CWordToPdf();
	virtual ~CWordToPdf();

	CString m_strPdfOutputPath;
	CWnd*   m_pWnd;
protected:
	MSWord::_Application m_WordApp;
	MSWord::_Document m_Doc;
	MSWord::Documents m_Docs;

public:
	void OpenWordFile(const CString& strWordFileName);
	void InsertEcptStamp(const CString& strEcptStampFile, CStampPos& stampPos);
	void InsertEcptTesterSign(const CString& strMainTesterSignFile,const CString& strSubTesterSignName,CTesterSignPos& testerSignPos);
	void InsertEcptAuditorSign(const CString& strAuditorSignFile,CAuditorSignPos& auditorSignPos);
	void InsertEcptApproverSign(const CString& strApproverSignFile,CApproverSignPos& approverSignPos);
	void InsertEcptRevisionerSign(const CString& strRevisionerSignFile,CRevisionerSignPos& revisionerSignPos);
	void InsertEcptTypistSign(const CString& strTypistSignFile,CTypistSignPos& typistSignPos);
	void SaveToPdf(const CString& strPdfFile);
	CString GetWildcards(CString strOperatorName);
	void CloseWordFile();
	BOOL CreatWordApplation(BOOL bVisible);
	BOOL ExitWordApplation();

	void GetDefaultPrinter(CString& strDefPrinter);
	void SetDefaultPrinter(const CString& strPrinterName);
	int  KillProcessByTitle(const CString& strWindowName);
	void CopyFolder(const CString& szFromPath,const CString& szToPath);
	BOOL PrintTransFile(const CString& strPrinterName,const CString& strPrintOutPath,const CString& strPdfFile);

public:
	virtual void PrintToPdf(const CString strWordFileName, const CString strPdfFileName);
	virtual bool ProcessPdfFilePrintOut(const CString& strSourceWordFileName, const CString & strDestPdfFile)	{	return false;	}
	BOOL WordToPdf(const CString& strFileDoc,CString& strFilePdf);
};

class CWordToPdf_AdobePrint : public CWordToPdf
{
public:
	CWordToPdf_AdobePrint();
	virtual ~CWordToPdf_AdobePrint();

public:
	virtual void PrintToPdf(const CString strWordFileName, const CString strPdfFileName);
	virtual bool ProcessPdfFilePrintOut(const CString& strSourceWordFileName, const CString & strDestPdfFile);
};

class CWordToPdf_MSPrint : public CWordToPdf
{
public:
	CWordToPdf_MSPrint();
	virtual ~CWordToPdf_MSPrint();

public:
	virtual void PrintToPdf(const CString strWordFileName, const CString strPdfFileName);
	virtual bool ProcessPdfFilePrintOut(const CString& strSourceWordFileName, const CString & strDestPdfFile);
};
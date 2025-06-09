// ContentHandleObject.cpp: implementation of the CContentHandleObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ContentHandleObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CContentHandleObject::CContentHandleObject()
{
	m_strErrorMessage.empty();
	m_strContent.empty();
	m_nErrorIndex = 0;
	m_nWarningIndex = 0;
	m_nFatalErrorIndex = 0;

	m_pResultsRec = NULL;
}

CContentHandleObject::~CContentHandleObject()
{
}
void CContentHandleObject::startDocument()
{

}
void CContentHandleObject::endDocument()
{

}

///////////////////////////////////////////////////////////////////////////////
void CContentHandleObject::warning(const SAXParseException& exc)
{
    this->SaveErrorMessage(exc.getMessage(),exc.getLineNumber(),exc.getColumnNumber(),exc.getPublicId(),exc.getSystemId() ,1);
}
void CContentHandleObject::error(const SAXParseException& exc)
{
    this->SaveErrorMessage(exc.getMessage(),exc.getLineNumber(),exc.getColumnNumber(),exc.getPublicId(),exc.getSystemId() ,2);
}
void CContentHandleObject::fatalError(const SAXParseException& exc)
{
	this->SaveErrorMessage(exc.getMessage(),exc.getLineNumber(),exc.getColumnNumber(),exc.getPublicId(),exc.getSystemId() ,3);
}
bool CContentHandleObject::SaveErrorMessage(const XMLCh* errorMessage,int rowNumber,int columnNumber,const XMLCh* publicId,const XMLCh* systemId  ,int nErrorType)
{
	bool rc = false;
	char* pTranscodeBuf = NULL;
	char buf[32] = "\0";

	CString strStr;

	CResultRec *pResultRec = new CResultRec;
	m_pResultsRec->AddNewChild(pResultRec);

	if (nErrorType == 1)
	{
		m_nWarningIndex++;
		strStr.Format("告警%d ",m_nWarningIndex);
		pResultRec->m_nWarningIndex = 1;
	}
	else if (nErrorType == 2)
	{
		m_nErrorIndex++;
		strStr.Format("错误%d",m_nErrorIndex);
		pResultRec->m_nErrorIndex = 1;
	}
	else if (nErrorType == 3)
	{
		m_nFatalErrorIndex++;
		strStr.Format("严重%d",m_nFatalErrorIndex);
		pResultRec->m_nFatalErrorIndex = 1;
	}

	pResultRec->m_strErrorType = strStr;
	pResultRec->m_strErrorText = errorMessage;
	
	if(publicId)
	{
		pResultRec->m_strErrorText += ";public id:";
#ifdef _PSX_IDE_QT_
		pResultRec->m_strErrorText += (const char *)publicId;
#else
		pResultRec->m_strErrorText += publicId;
#endif
	}

	pResultRec->m_strErrorPos.Format("行号=%d ,列号=%d" ,rowNumber,columnNumber );

	return rc;
}
#include "stdafx.h"
#include "CString_QT.h"
#include "../../API/StringApi.h"

CString::CString()
{

}

CString::CString(const char *pString)
{//2022-1-13  lijunqing
#ifdef _PSX_QT_SRCFILE_GBK_
#ifdef _PSX_QT_LINUX_
    *this = QObject::tr(pString);
#else
    *this = QString::fromLocal8Bit(pString);
#endif
#else
	*this = QObject::tr(pString);
#endif
}

CString::CString(char *pString)
{
	//2022-1-13  lijunqing
#ifdef _PSX_QT_SRCFILE_GBK_
#ifdef _PSX_QT_LINUX_
    *this = QObject::tr(pString);
#else
    *this = QString::fromLocal8Bit(pString);
#endif
#else
	*this = QObject::tr(pString);
#endif
}

CString::CString(const wchar_t *pString)
{
	*this = QString::fromWCharArray(pString);
}

CString::CString(const QString &str)
: QString(str)
{

}

CString::CString(const CString &str)
: QString((const QString&)str)
{
}

//const char* CString::GetString() const
//{
//    const std::string *pString = &m_oStdString;
//    *((std::string*)pString) = toStdString();
//    //m_oStdString = toStdString();
//    return m_oStdString.c_str();
//}

//const char* CString::GetString()
//{
//    m_oStdString = toStdString();
//    return m_oStdString.c_str();
//}

CString& CString::operator=(const char *pString)
{
	//2022-3-23  lijunqing
#ifdef _PSX_QT_SRCFILE_GBK_
#ifdef _PSX_QT_LINUX_
    //*this = QObject::tr(pString);
    *this = QString::fromLocal8Bit(pString);
#else
	*this = QString::fromLocal8Bit(pString);
#endif
#else
	*this = QObject::tr(pString);
#endif

	return *this;
	/*
    *this = QObject::tr(pString);
//		*this = CString(pString);	//yyj因Windows界面乱码改 2022.02.16
    //QString::operator=( QString::fromLocal8Bit(pString));
    return *this;
	*/
}

const char* CString::GetString() const
{
    const QByteArray *pQbytes = &m_oQbytes;
    *((QByteArray*)pQbytes) = toLocal8Bit();

    return m_oQbytes.data();
}

const char* CString::GetString()
{
// #ifdef _PSX_QT_LINUX_
//     m_oQbytes = toLatin1();
// #else
     m_oQbytes = toLocal8Bit();
// #endif

    return m_oQbytes.data();
}

//2023-2-7  lijunqing 清空m_oQbytes
void CString::ClearBytes()
{
	m_oQbytes.clear();
}


void CString::Trim()
{
	CString strTemp = QString::trimmed();
	*this = strTemp;
}

void CString::TrimRight(char ch)
{

}
void CString::TrimLeft(char ch)
{

}

 wchar_t* CString::AllocSysString()
 {
    wchar_t *pSysString = NULL;
    CString_to_wchar(*this, &pSysString);
    return pSysString;
 }

 wchar_t* CString::AllocSysString() const
 {
    wchar_t *pSysString = NULL;
    CString_to_wchar(*this, &pSysString);
    return pSysString;
 }

//format说明：这里不考虑非常长的字符串格式化
//2019-11-20
void CString::Format(const char *format, ...)
{
    va_list argList;
    //char pszBuffer[1024];

    va_start( argList, format );
    //memset(pszBuffer, 0, 1024);
    vsprintf(format, argList );
    //*this = pszBuffer;

    va_end( argList );
}

void CString::Format(const CString &format, ...) //const
{
    va_list argList;
    char pszFormat[250];
    //char pszBuffer[1024];
    CString_to_char(format, pszFormat);

    //memset(pszBuffer, 0, 1024);
    va_start( argList, pszFormat );
    vsprintf(pszFormat, argList );
    //*this = pszBuffer;
	va_end( argList );
}

void CString::AppendFormat(const char *format, ...) //const
{
    va_list argList;
    //char pszBuffer[1024];

    va_start( argList, format );
    CString str;
    //memset(pszBuffer, 0, 1024);
    str.vsprintf(format, argList );
    *this += str;
    va_end( argList );
}

void CString::AppendFormat(const CString &format, ...) //const
{
    va_list argList;
    char pszFormat[250];
    //char pszBuffer[1024];

    CString_to_char(format, pszFormat);
    va_start( argList, pszFormat );
    CString str;
    //memset(pszBuffer, 0, 1024);
    str.vsprintf( pszFormat, argList );
    *this += str;
    va_end( argList );
}

void SetLocalCodec(const CString &strCodecText)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    QTextCodec *codec = QTextCodec::codecForName(strCodecText.GetString());
	QTextCodec::setCodecForLocale(codec);
#else
	QTextCodec *codec = QTextCodec::codecForName(strCodecText.GetString());
    QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);	
#endif
}

void ResetLocalCodec(QTextCodec *pOldTextCodec)
{
	if (pOldTextCodec == NULL)
	{
		return;
	}

	QTextCodec *pCurrTextCodec = QTextCodec::codecForLocale();

	if (pCurrTextCodec != pOldTextCodec)
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		QTextCodec::setCodecForLocale(pOldTextCodec);
#else
		QTextCodec::setCodecForLocale(pOldTextCodec);
		QTextCodec::setCodecForCStrings(pOldTextCodec);
		QTextCodec::setCodecForTr(pOldTextCodec);
#endif
	}
}


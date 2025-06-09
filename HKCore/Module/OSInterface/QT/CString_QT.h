#ifndef _CString_qt_h__
#define _CString_qt_h__

#include <qstring.h>
#include <qbytearray.h>
#include <QObject>
#include <QTextCodec>

#include "XGlobalDataTypes_QT.h"

class CString : public QString
{
private:
    QByteArray m_oQbytes;

public:
    CString();
    CString(const char *pString);
    CString(char *pString);
    CString(const wchar_t *pString);
    CString(const QString &str);
    CString(const CString &str);

    const char* GetString() const;
    const char* GetString();
	void ClearBytes();    //2023-2-7  lijunqing «Âø’m_oQbytes

    inline int GetLength() const
    {
#ifdef _QT_IN_LINUX_//zhouhj 2024.5.11
        return length();
#else
#ifdef UNICODE
        return length();
#else
		return toLocal8Bit().length();
#endif
#endif
    }

    unsigned short GetAt(int nPos) const
    {
       return at(nPos).unicode();
    }
    void SetAt(int nPos, char ch)
    {
        insert(nPos, ch);
        remove(nPos+1, 1);
    }

    unsigned short operator [](int nPos) const
    {
       return at(nPos).unicode();
    }

    inline CString &operator=(CString &other)
    {
        QString::operator= ( (const QString &)other);
        return *this;
    }

    inline CString &operator=(const QString &other)
    {
        QString::operator=( other);
        return *this;
    }

    inline CString &operator=(const wchar_t *other)
    {
         *this = QString::fromWCharArray(other);
        return *this;
    }

    CString &operator=(const char *pString);

    inline bool operator==(const CString &str) const
    {
        return ((QString)*this) == ((QString)str);
    }

    inline bool operator==(const wchar_t *pString) const
    {
        CString str2(pString);
        return ((QString)*this) == (str2);
    }
    inline bool operator!=(const wchar_t *pString) const
    {
        CString str2(pString);
        return ((QString)*this) != (str2);
    }
	inline bool operator!=(const char *pString) const
	{
		CString str2(pString);
		return ((QString)*this) != (str2);
	}
	inline bool operator!=(const CString &str) const
	{
		return ((QString)*this) != ((QString)str);
	}

    inline int ReverseFind(char ch) const
    {
        QChar qch(ch);
        return lastIndexOf(qch);
    }
    inline CString Left(int nLen) const
    {
         QString str = left(nLen);
		 CString str2(str);
		 return str2;
    }
    inline CString Right(int nLen) const
    {
         QString str = right(nLen);
		 CString str2(str);
		 return str2;
    }
    inline CString Mid(int nPos, int nLen=-1) const
    {
        QString str = mid(nPos, nLen);
        CString str2(str);
        return str2;
    }

    inline bool IsEmpty()
    {
        return isEmpty();
    }
    inline bool IsEmpty() const
    {
        return isEmpty();
    }

    inline void Empty()
    {
        clear();
    }

    inline void MakeLower()
    {
        *this = toLower();
    }
    inline void MakeUpper()
    {
        *this = toUpper();
    }

    inline int Find(const CString &strFind, int from=0)
    {
        return QString::indexOf(strFind,from);
    }
    inline int Find(const CString &strFind, int from=0) const
    {
        return QString::indexOf(strFind,from);
    }
    inline int Find(wchar_t ch, int from = 0) const
    {
        return QString::indexOf((QChar)ch,from);
    }
    //lipenghui 
    inline int Find(char ch, int from = 0) const
    {
        return QString::indexOf(ch, from);
    }
    inline int Find(const char *pszString, int from = 0) const
    {
        return QString::indexOf(pszString,from);
    }
	inline int Find(const char *pszString, int from = 0)
	{
		return QString::indexOf(pszString,from);
	}
    inline int Find(char *pszString, int from = 0) const
    {
        return QString::indexOf(pszString,from);
    }
	inline int Find(char *pszString, int from = 0)
	{
		return QString::indexOf(pszString,from);
	}

	inline long FindOneOf(CString strString)
	{
		QChar ch;
		long nPos;
		for(int i=0; i<strString.size(); i++)
		{
			ch = strString.at(i);
			nPos = QString::indexOf(ch, 0);
			if(nPos>=0)
			{
				return nPos;
			}
		}
		return -1;
	}

    inline int CompareNoCase(const CString &strSrc)
    {
        return compare(strSrc, Qt::CaseInsensitive);
    }
    inline int CompareNoCase(const CString &strSrc) const
    {
        return compare(strSrc, Qt::CaseInsensitive);
    }
    inline int CompareNoCase(const char *strSrc)
    {
        return compare(strSrc, Qt::CaseInsensitive);
    }
    inline int CompareNoCase(const char *strSrc) const
    {
        return compare(strSrc, Qt::CaseInsensitive);
    }
    inline int CompareNoCase(const wchar_t *strSrc)
    {
        CString strTemp;
        strTemp = strSrc;
        return compare(strTemp, Qt::CaseInsensitive);
    }

    inline int Compare(const CString &strSrc)
    {
        return compare(strSrc, Qt::CaseSensitive);
    }
    inline int Compare(const CString &strSrc) const
    {
        return compare(strSrc, Qt::CaseSensitive);
    }
    inline int Compare(const char *strSrc)
    {
        return compare(strSrc, Qt::CaseSensitive);
    }
    inline int Compare(const char *strSrc) const
    {
        return compare(strSrc, Qt::CaseSensitive);
    }
    inline int Compare(const wchar_t *strSrc)
    {
        CString strTemp;
        strTemp = strSrc;
        return compare(strTemp, Qt::CaseSensitive);
    }

    inline void Insert(int i, char ch)
    {
        QString::insert(i, ch);
    }

    inline int Replace( const CString &pszOld, const CString &pszNew )
    {
        QString::replace(pszOld, pszNew);
        return 0;
    }

	inline int Replace( const char chOld, const char chNew )
	{

		QString::replace(chOld, QString(chNew));
		return 0;
	}

    void Trim();

	void Delete(int nPos, int nCount)
	{
		QString::remove(nPos, nCount);
	}

    void TrimRight(char ch=' ');
    void TrimLeft(char ch=' ');
    wchar_t* AllocSysString();
    wchar_t* AllocSysString() const ;

    void Format(const char *format, ...);
    void Format(const CString &format, ...);
    void AppendFormat(const char *format, ...);
    void AppendFormat(const CString &format, ...);

	int Remove(char ch)
	{
		QString::remove(ch);
		return 0;
	}
};

void SetLocalCodec(const CString &strCodecText);
void ResetLocalCodec(QTextCodec *pOldTextCodec);//∏¥πÈ±‡¬Î…Ë÷√

#ifdef _PSX_QT_LINUX_
inline void SysFreeString(wchar_t *pwString)
{
    delete pwString;
}

inline wchar_t* SysAllocString(wchar_t *pwszSrc)
{
    int nLen = wcslen(pwszSrc);
    wchar_t *pRet = new wchar_t[nLen+1];

    wcscpy(pRet, pwszSrc);
    pRet[nLen] = 0;

    return pRet;
}
#else
#include <OleAuto.h>
#endif

#endif   //_CString_qt_h__

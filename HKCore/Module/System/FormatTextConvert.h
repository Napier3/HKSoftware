#if !defined(_FORMATTEXTCONVERT_H__)
#define _FORMATTEXTCONVERT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const long MAX_OF_CONVERT_STRING = 40;
const long CONVERTTOFORMARTDATA = 0;
const long CONVERTTONORMALDATA = 1;

class CFormatTextConvert  
{
public:
	CFormatTextConvert(long lType);
	CFormatTextConvert(const char *pszSrca,long lType);
	CFormatTextConvert(const CString &strSrc,long lType);
	virtual ~CFormatTextConvert();

	void SetData(const char *pszSrc);
	void SetData(const CString &strSrc);
	const char* GetData() const;
	void GetData(CString &strDest);
	void Convert(const char *pszSrc,CString &strDest);
	void Convert(const CString &strSrc,CString &strDest);

public:
	virtual void InitKeyWords();

protected:
	int m_nKeyCount;
	char *m_arrKeyWord[MAX_OF_CONVERT_STRING];	//关键字
	char *m_arrKeyFormat[MAX_OF_CONVERT_STRING];	//格式化数据

	BOOL AddKeyWord(const char *pszKeyWord,const char *pszKeyFormat);
	BOOL AddKeyWord(const CString &strKeyWord,const CString &strKeyFormat);
	BOOL IsKeyWordExist(const char *pszKeyWord);
	BOOL IsKeyWordExist(const CString &strKeyWord);
	BOOL IsKeyFormatExist(const char *pszKeyFormat);
	BOOL IsKeyFormatExist(const CString &strKeyFormat);

	void InitIt();
	void FreeBuffer();
	void Convert();
	void AllocateBufferDest();
	long GetKeyWordCount(long lIndex);
	void Replace(long lIndex);
	void Replace(const char *pszOld,const char *pszNew);
private:
	char *m_pBufferSrc;	//源数据
	char *m_pBufferDest;	//转换后数据
	char *m_pBufferDestTemp;	//转换后数据
	long m_nConvertType;
	long m_nBufferLength;
};

#endif // !defined(_FORMATTEXTCONVERT_H__)

#pragma once

#define MAX_BUFFER_SIZE 2048;

class CIniFileException
{
public:
	CIniFileException() {};
	~CIniFileException() {};
};

class CIniFile  
{
public:
// 	CIniFile();
	CIniFile(CString FileName);
	void SetFile(CString FileName);
	virtual ~CIniFile();
	bool SectionExists(CString Section);

	CString		ReadString(CString Section, CString Ident, CString Default);
	void		WriteString(CString Section, CString Ident, CString Value);
	int			ReadInteger(CString Section, CString Ident, int Default);
	void		WriteInteger(CString Section, CString Ident, int Value);
	float		ReadFloat(CString Section, CString Ident, float Default);
	void		WriteFloat(CString Section, CString Ident, float Value);

	void ReadSection(CString Section, CStringArray &Strings);
	void ReadSections(CStringArray &Strings);
	void ReadSectionValues(CString Section, CStringArray &Strings);
	void EraseSection(CString Section);

	void LinkRealFile(const CString &strIniFile);

protected:
	CString m_strFileName;
};


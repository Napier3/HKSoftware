#if !defined(_X_MergeFiles_H__)
#define _X_MergeFiles_H__


class CMergeFiles
{
public:
	CMergeFiles();
	virtual ~CMergeFiles();

	BOOL MergeFiles(const CString &strSrcPath, const CString &strDestFile);
	
protected:
	CFile m_oFileDest;
	CFile m_oFileTxt;

	void MergeFiles(const CString &strSrcPath);
	
	CString m_strEndIF;
};



#endif
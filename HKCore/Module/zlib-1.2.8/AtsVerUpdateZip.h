#pragma once

// CAtsVerUpdateZip

class CAtsVerUpdateZip
{
	DECLARE_DYNAMIC(CAtsVerUpdateZip)

public:
	CAtsVerUpdateZip();
	virtual ~CAtsVerUpdateZip();

    int Zip(CStringArray& strFileArray,const CString& strZipFile);//strFileArray:被压缩文件的路径数组；strZipFile:压缩包文件.zip
	int Unzip(const CString& strZipFile,const CString& strDestPath);
};



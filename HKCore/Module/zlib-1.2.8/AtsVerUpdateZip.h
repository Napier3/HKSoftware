#pragma once

// CAtsVerUpdateZip

class CAtsVerUpdateZip
{
	DECLARE_DYNAMIC(CAtsVerUpdateZip)

public:
	CAtsVerUpdateZip();
	virtual ~CAtsVerUpdateZip();

    int Zip(CStringArray& strFileArray,const CString& strZipFile);//strFileArray:��ѹ���ļ���·�����飻strZipFile:ѹ�����ļ�.zip
	int Unzip(const CString& strZipFile,const CString& strDestPath);
};



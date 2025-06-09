#ifndef CCDFILE_READ_H
#define CCDFILE_READ_H

#include "../SCL/SclIecCfgDatas.h"
#include "../../../Module/BaseClass/ThreadProgressInterface.h"

#define SCL_FILE_PARSE_USE_XPUGI//zhouhj 2024.2.2 SCL解析采用xpugl方式,即采用char*方式

#ifdef SCL_FILE_PARSE_USE_XPUGI
#include "../../../Module/xml/XPugiXML/xpugixml.hpp"
#else
#include "../../../Module/xml/PugiXML/pugixml.hpp"
#endif

class CcdFileRead
{

public:
	CcdFileRead();
	virtual ~CcdFileRead();

    BOOL ReadSclFile(const CString &strSclFilePath, CSclStation *pSclStation);   //装载SCD文件
	void SetProgressInterface(CThreadProgressInterface *pProgressInterface){m_pProgressInterface = pProgressInterface;}
	static UINT ReadSCLThread (LPVOID pParam );//cgl：只为检测SCD读写文件用
	void ReadSclStation(const CString &strSclFilePath);//将SCL读取的内容存入m_pSclStation对象链表中
	BOOL IsInReadState()	{	return m_bIsInReadState;	}
	void FreeThreadAndDatas();
	void InitThreadProgress();

	CSclStation   *m_pSclStation;

protected:
	void FreeReadThread();
	DWORD GetHexValue(const QString &strHexText);

private:
	CThreadProgressInterface *m_pProgressInterface;

	BOOL m_bIsInReadState;
	CWinThread *m_pReadThread;
};

#endif // CCDFILE_READ_H

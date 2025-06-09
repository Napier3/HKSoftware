#ifndef STTFILEMNGRTOOL_H
#define STTFILEMNGRTOOL_H


#include "../../../../../Module/DataMngr/DataGroup.h"

#define STT_FILE_MNGR_SCD                  _T("SCD") //SCD文件
#define STT_FILE_MNGR_Comtrade             _T("Comtrade") //录波文件
#define STT_FILE_MNGR_Template             _T("Template") //模板文件
#define STT_FILE_MNGR_Workspace            _T("Workspace") //报告文件
#define STT_FILE_MNGR_IEC61850Config       _T("IEC61850Config") //IEC61850配置文件
#define STT_FILE_MNGR_PrintScreen          _T("PrintScreen") //截屏文件夹
#define STT_FILE_MNGR_PcapFile             _T("PcapFile") //数字录波文件
#define STT_FILE_MNGR_Other                _T("Other") //其它


class CSttFileMngrTool
{
	

public:
	CSttFileMngrTool();
	~CSttFileMngrTool();	
	
public:
	
	BOOL OpenConfigFile(CString strFilePath = _T(""));
	//获取标准文件夹路径,即文件管理系统定义的路径
	CString GetFolderPath_STD(const CString &strTypeId);
//	BOOL IsFolderPath(const CString &strPath,CString &strFilePath);

	CDataGroup m_oFileMngr;

};

extern CSttFileMngrTool g_oFileMngrTool;


#endif // STTFILEMNGRTOOL_H

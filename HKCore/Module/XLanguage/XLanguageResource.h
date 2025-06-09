//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLanguageResourceBase.h  CXLanguageResourceBase

#pragma once

#include "XLanguageGlobal.h"
#include "XLanguage.h"


class CXLanguageResourceBase : public CXLanguage
{
public:
	CXLanguageResourceBase();
	virtual ~CXLanguageResourceBase();
	
	void InitLangFileForDebug(const CString &strModule);

private:
	CXLanguage m_oXLangRsBase;

protected:
	CXLanguage *m_pXLangRsExe;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);
	CXLangItem* rs_AddString2(const CString &strID, const CString &strString);

	virtual void InitLangRsByFile();
	virtual void InitLangRsByFileEx(CXLanguage *pXLangRef, const CString &strFile);
	virtual void SaveXLangRsFile();

	virtual void RegisterLanguageResource();
	void LanguageChange(CString strFile,CXLanguage *pXLangRef);//20250122 suyang 增加语言替换，补充多语言没有的

	//2023-2-28  lijunqing LINUX QT下，编码模式的问题，还没设置编码模式的时候，全局静态变量会是乱码，所以增加此函数
	virtual void InitLangTxt();

};

	extern  CString  g_strXLangRsBaseFile;
	extern  CString g_sLangID_Chinese;
	extern  CString g_sLangID_English;

	extern  CString g_sLangID_File;
	extern  CString g_sLangTxt_File;
	extern  CString g_sLangID_FileNew;
	extern  CString g_sLangTxt_FileNew;
	extern  CString g_sLangID_FileNewTip;
	extern  CString g_sLangTxt_FileNewTip;
	extern  CString g_sLangID_FileOpen;
	extern  CString g_sLangTxt_FileOpen;
	extern  CString g_sLangID_Save;
	extern  CString g_sLangTxt_Save;
	extern  CString g_sLangID_SaveTip;
	extern  CString g_sLangTxt_SaveTip;
	extern  CString g_sLangID_SaveAs;
	extern  CString g_sLangTxt_SaveAs;
	extern  CString g_sLangID_SaveAsTip;
	extern  CString g_sLangTxt_SaveAsTip;
	extern  CString g_sLangID_Print;
	extern  CString g_sLangTxt_Print;
	extern  CString g_sLangID_FileClose;
	extern  CString g_sLangTxt_FileClose;
	extern  CString g_sLangID_Clipboard;
	extern  CString g_sLangTxt_Clipboard;
	extern  CString g_sLangID_Copy;
	extern  CString g_sLangTxt_Copy;
	extern  CString g_sLangID_View;
	extern  CString g_sLangTxt_View;
	extern  CString g_sLangID_SelAll;
	extern  CString g_sLangTxt_SelAll;
	extern  CString g_sLangID_PasteData;
	extern  CString g_sLangTxt_PasteData;
	extern  CString g_sLangID_Paste;
	extern  CString g_sLangTxt_Paste;
	extern  CString g_sLangID_PasteTip;
	extern  CString g_sLangTxt_PasteTip;
	extern  CString g_sLangID_Cut;
	extern  CString g_sLangTxt_Cut;
	extern  CString g_sLangID_Delete;
	extern  CString g_sLangTxt_Delete;
	extern  CString g_sLangID_OK;
	extern  CString g_sLangTxt_OK;
	extern  CString g_sLangID_Cancel;
	extern  CString g_sLangTxt_Cancel;
	extern  CString g_sLangID_AppExit;
	extern  CString g_sLangTxt_AppExit;
	extern  CString g_sLangID_AppExitTip;
	extern  CString g_sLangTxt_AppExitTip;
	extern  CString g_sLangID_Help;
	extern  CString g_sLangTxt_Help;
	extern  CString g_sLangID_HelpAbout;
	extern  CString g_sLangTxt_HelpAbout;
	extern  CString g_sLangID_Back;
	extern  CString g_sLangTxt_Back;
	//
	extern  CString g_sLangID_Name;
	extern  CString g_sLangTxt_Name;
	extern  CString g_sLangID_Index;
	extern  CString g_sLangTxt_Index;
	extern  CString g_sLangID_Type;
	extern  CString g_sLangTxt_Type;
	extern  CString g_sLangID_History;
	extern  CString g_sLangTxt_History;
	extern  CString g_sLangID_Open;
	extern  CString g_sLangTxt_Open;
	extern  CString g_sLangID_Location;
	extern  CString g_sLangTxt_Location;
	extern  CString g_sLangID_Path;
	extern  CString g_sLangTxt_Path;
	extern  CString g_sLangID_ModifiedTime;//修改时间
	extern  CString g_sLangTxt_ModifiedTime;
	extern  CString g_sLangID_Size;        //大小（KB）
	extern  CString g_sLangTxt_Size;

	extern  CString g_sLangID_Folder;        //文件夹
	extern  CString g_sLangTxt_Folder;
	extern  CString g_sLangID_SureDeleItem;        //确定要删除这 %d 个项目吗?
	extern  CString g_sLangTxt_SureDeleItem;
	extern  CString g_sLangID_SureDelete;        //删除确认
	extern  CString g_sLangTxt_SureDelete;
	extern  CString g_sLangID_SureAgain;        //删除后将无法恢复，请再次确认
	extern  CString g_sLangTxt_SureAgain;
	extern  CString g_sLangID_DeleteFail;        //文件正在被使用，删除失败
	extern  CString g_sLangTxt_DeleteFail;
	extern  CString g_sLangID_FileDeleteFail;        //删除文件失败
	extern  CString g_sLangTxt_FileDeleteFail;
	extern  CString g_sLangID_DeleteFailFold;        //文件夹中包含正在被使用的文件，删除失败
	extern  CString g_sLangTxt_DeleteFailFold;
	extern  CString g_sLangID_FolderDeleteFail;        //删除文件夹失败
	extern  CString g_sLangTxt_FolderDeleteFail;
	extern  CString g_sLangID_FoldAlrOpen;        //该文件夹中已被打开的文件
	extern  CString g_sLangTxt_FoldAlrOpen;
	extern  CString g_sLangID_ModifiedFail;        //修改文件夹名称失败
	extern  CString g_sLangTxt_ModifiedFail;
	extern  CString g_sLangID_FileOpened;        //该文件已被打开
	extern  CString g_sLangTxt_FileOpened;

	extern  CString g_sLangID_SerNumber;    //序号
	extern  CString g_sLangTxt_SerNumber;
	extern  CString g_sLangID_MinTime;    //最小次数
	extern  CString g_sLangTxt_MinTime;
	extern  CString g_sLangID_MaxTime;    //最大次数
	extern  CString g_sLangTxt_MaxTime;

	extern  CString g_sLangID_Filter;     //过滤
	extern  CString g_sLangTxt_Filter;
	extern  CString g_sLangID_CinKeyDb;   //合并文件
	extern  CString g_sLangTxt_CinKeyDb;
	extern  CString g_sLangID_BaseKeyNew;
	extern  CString g_sLangTxt_BaseKeyNew;
	extern  CString g_sLangID_MultiKeyNew;
	extern  CString g_sLangTxt_MultiKeyNew;
	extern  CString g_sLangID_DeleteKey;
	extern  CString g_sLangTxt_DeleteKey;
	extern  CString g_sLangID_SelectSameKey;
	extern  CString g_sLangTxt_SelectSameKey;
	extern  CString g_sLangID_AnalyzeKey;
	extern  CString g_sLangTxt_AnalyzeKey;
	extern  CString g_sLangID_AnalyzeKeyUnsu;       //关键字匹配不成功
	extern  CString g_sLangTxt_AnalyzeKeyUnsu;
	extern  CString g_sLangID_AnalyzeKeySu;
	extern  CString g_sLangTxt_AnalyzeKeySu;        //关键字匹配成功
	extern  CString g_sLangID_DeleteKeyObj;         //选择删除对象
	extern  CString g_sLangTxt_DeleteKeyObj;

	extern  CString g_sLangID_Data;//数据
	extern  CString g_sLangTxt_Data;
	extern  CString g_sLangID_OperIns;//作业指导书
	extern  CString g_sLangTxt_OperIns;
	extern  CString g_sLangID_PromptMessage;//提示信息
	extern  CString g_sLangTxt_PromptMessage;
	extern  CString g_sLangID_PleaseChoose;//请在 %s 下选择%s
	extern  CString g_sLangTxt_PleaseChoose;
	extern  CString g_sLangID_FileAlrExi;//文件 %s 已经存在
	extern  CString g_sLangTxt_FileAlrExi;
	extern  CString g_sLangID_StandardFileName;//标准文件名
	extern  CString g_sLangTxt_StandardFileName;
	extern  CString g_sLangID_ManagSave;//%s 管理---保存
	extern  CString g_sLangTxt_ManagSave;
	extern  CString g_sLangID_ManagOpen;//%s 管理---打开
	extern  CString g_sLangTxt_ManagOpen;
	extern  CString g_sLangID_FileExYN;//%s 文件已经存在，是否覆盖?
	extern  CString g_sLangTxt_FileExYN;
	extern  CString g_sLangID_FileDupliName;//文件重名
	extern  CString g_sLangTxt_FileDupliName;
	extern  CString g_sLangID_AlrOpenFail;//%s 已经被打开，文件覆盖失败
	extern  CString g_sLangTxt_AlrOpenFail;
	extern  CString g_sLangID_FileCoverFail;//文件覆盖失败
	extern  CString g_sLangTxt_FileCoverFail;

	extern  CString g_sLangID_AddDirectory;//添加目录
	extern  CString g_sLangTxt_AddDirectory;
	extern  CString g_sLangID_ImportDirectory;//导入目录
	extern  CString g_sLangTxt_ImportDirectory;
	extern  CString g_sLangID_ExportDirectory;//导出目录
	extern  CString g_sLangTxt_ExportDirectory;
	extern  CString g_sLangID_CopyFile;//拷贝文件
	extern  CString g_sLangTxt_CopyFile;
	extern  CString g_sLangID_PasteFile;//粘贴文件
	extern  CString g_sLangTxt_PasteFile;
	extern  CString g_sLangID_DeleteFile;//删除文件
	extern  CString g_sLangTxt_DeleteFile;
	extern  CString g_sLangID_FileRename;//修改文件名称
	extern  CString g_sLangTxt_FileRename;
	extern  CString g_sLangID_ImportFile;//导入文件
	extern  CString g_sLangTxt_ImportFile;
	extern  CString g_sLangID_ExportFile;//导出文件
	extern  CString g_sLangTxt_ExportFile;
	extern  CString g_sLangID_DeleteDirectory;//删除目录
	extern  CString g_sLangTxt_DeleteDirectory;
	extern  CString g_sLangID_DirectoryRename;//修改目录名称
	extern  CString g_sLangTxt_DirectoryRename;
	extern  CString g_sLangID_FileCover;//覆盖文件
	extern  CString g_sLangTxt_FileCover;
	extern  CString g_sLangID_ExiSaNameFileCov;//存在同名称的文件【%s】,覆盖吗？
	extern  CString g_sLangTxt_ExiSaNameFileCov;
	extern  CString g_sLangID_ExiFileOvwt;//文件【%s】已经存在,覆盖吗？
	extern  CString g_sLangTxt_ExiFileOvwt;
	extern  CString g_sLangID_Message;//提示
	extern  CString g_sLangTxt_Message;
	extern  CString g_sLangID_SureDeleFile;//你确实要删除文件【%s】吗？
	extern  CString g_sLangTxt_SureDeleFile;
	extern  CString g_sLangID_ExiSaNameFile;//存在同名称的文件夹【%s】
	extern  CString g_sLangTxt_ExiSaNameFile;
	extern  CString g_sLangID_ExiSmNmFile3;//存在同名称的文件【%s】
	extern  CString g_sLangTxt_ExiSmNmFile3;
	extern  CString g_sLangID_ExiSmNmFile2;//文件夹【%s】存在同名称的文件【%s】
	extern  CString g_sLangTxt_ExiSmNmFile2;
	extern  CString g_sLangID_ChoImpFile;//选择导入的配置文件夹
	extern  CString g_sLangTxt_ChoImpFile;
	extern  CString g_sLangID_ExpFileFin;//导出目标文件夹【%s】完成
	extern  CString g_sLangTxt_ExpFileFin;
	extern  CString g_sLangID_TargFolderExist;//目标文件夹【%s】已经存在
	extern  CString g_sLangTxt_TargFolderExist;
	extern  CString g_sLangID_ChoFoldExDir;//选择配置文件夹导出目标目录
	extern  CString g_sLangTxt_ChoFoldExDir;
	extern  CString g_sLangID_SureDeleFold;//确实要删除文件夹【%s】吗？
	extern  CString g_sLangTxt_SureDeleFold;
	extern  CString g_sLangID_DeleFold;//删除文件夹将删除此文件夹及其下的全部文件及文件夹。\r\n确实要删除文件夹【%s】吗？
	extern  CString g_sLangTxt_DeleFold;
	extern  CString g_sLangID_FoldCoverFold;//文件夹【%s】包含子文件夹或者文件\r\n请先删除子文件夹或者文件，然后再删除目录
	extern  CString g_sLangTxt_FoldCoverFold;
	extern  CString g_sLangID_ConfigFileManag;//配置文件管理
	extern  CString g_sLangTxt_ConfigFileManag;

	extern  CString g_sLangID_AtsPubFileManag;
	extern  CString g_sLangTxt_AtsPubFileManag;
	extern  CString g_sLangID_AddPubFile;
	extern  CString g_sLangTxt_AddPubFile;
	extern  CString g_sLangID_ModifyPubFile;
	extern  CString g_sLangTxt_ModifyPubFile;
	extern  CString g_sLangID_DeletePubFile;
	extern  CString g_sLangTxt_DeletePubFile;

	extern  CString g_sLangID_TraProtocol;
	extern  CString g_sLangTxt_TraProtocol;
	extern  CString g_sLangID_61850Protocol;
	extern  CString g_sLangTxt_61850Protocol;
	extern  CString g_sLangID_None;
	extern  CString g_sLangTxt_None;


	//故障、通用、结果参数
	extern  CString g_sLangID_FaultParameter;
	extern  CString g_sLangTxt_FaultParameter;
	extern  CString g_sLangID_GeneralParameter;
	extern  CString g_sLangTxt_GeneralParameter;
	extern  CString g_sLangID_ResultParameter;
	extern  CString g_sLangTxt_ResultParameter;
	extern  CString g_sLangID_AppBaseParameter;
	extern  CString g_sLangTxt_AppBaseParameter;

	extern  CString g_sLangID_ArbitrElement;//任意元素
	extern  CString g_sLangTxt_ArbitrElement;
	extern  CString g_sLangID_SpecifiedElement;//指定的元素
	extern  CString g_sLangTxt_SpecifiedElement;
	extern  CString g_sLangID_SequDefinElemIn;//序列定义中的元素
	extern  CString g_sLangTxt_SequDefinElemIn;
	extern  CString g_sLangID_SequDefinElemOut;//序列定义之外的元素
	extern  CString g_sLangTxt_SequDefinElemOut;
	extern  CString g_sLangID_ReferElements;//引用元素
	extern  CString g_sLangTxt_ReferElements;
	extern  CString g_sLangID_Values;//值
	extern  CString g_sLangTxt_Values;
	extern  CString g_sLangID_Time;//时间
	extern  CString g_sLangTxt_Time;
	extern  CString g_sLangID_Integer;//整数
	extern  CString g_sLangTxt_Integer;
	extern  CString g_sLangID_FloatNumber;//浮点数
	extern  CString g_sLangTxt_FloatNumber;
	extern  CString g_sLangID_CharacterString;//字符串
	extern  CString g_sLangTxt_CharacterString;
	extern  CString g_sLangID_Equal;//等于
	extern  CString g_sLangTxt_Equal;
	extern  CString g_sLangID_LessThan;//小于
	extern  CString g_sLangTxt_LessThan;
	extern  CString g_sLangID_LessOrEqual;//小于等于
	extern  CString g_sLangTxt_LessOrEqual;
	extern  CString g_sLangID_MoreThan;//大于
	extern  CString g_sLangTxt_MoreThan;
	extern  CString g_sLangID_MoreOrEqual;//大于等于
	extern  CString g_sLangTxt_MoreOrEqual;
	extern  CString g_sLangID_NotEqual;//不等于
	extern  CString g_sLangTxt_NotEqual;
	extern  CString g_sLangID_CharStringIncl;//字符串包含
	extern  CString g_sLangTxt_CharStringIncl;
	extern  CString g_sLangID_CharStringNIncl;//字符串不包含
	extern  CString g_sLangTxt_CharStringNIncl;
	extern  CString g_sLangID_NumberRange;//数值范围
	extern  CString g_sLangTxt_NumberRange;
	extern  CString g_sLangID_BoundNumRange;//数值范围带边界
	extern  CString g_sLangTxt_BoundNumRange;
	extern  CString g_sLangID_DataVarAss;//数据变量赋值
	extern  CString g_sLangTxt_DataVarAss;
	extern  CString g_sLangID_PropertyID;//属性ID
	extern  CString g_sLangTxt_PropertyID;
	extern  CString g_sLangID_DataType;//数据类型
	extern  CString g_sLangTxt_DataType;
	extern  CString g_sLangID_FunctionalSymbol;//操作符号
	extern  CString g_sLangTxt_FunctionalSymbol;
	extern  CString g_sLangID_Data2;//数据2
	extern  CString g_sLangTxt_Data2;
	extern  CString g_sLangID_ResultVariable;//结果变量
	extern  CString g_sLangTxt_ResultVariable;
	extern  CString g_sLangID_GnrtFileNm;//组合生成文件名称
	extern  CString g_sLangTxt_GnrtFileNm;
	extern  CString g_sLangID_OrgnFileNm;//原文件名称
	extern  CString g_sLangTxt_OrgnFileNm;
	extern  CString g_sLangID_TgetFileNm;//目标文件名称
	extern  CString g_sLangTxt_TgetFileNm;
	extern  CString g_sLangID_OverWrite;  //覆盖      
	extern  CString g_sLangTxt_OverWrite;
	extern  CString g_sLangID_FilePasteOprt;  //文件粘贴：操作处理      
	extern  CString g_sLangTxt_FilePasteOprt;
	extern  CString g_sLangID_SelFolder;  //选择文件夹      
	extern  CString g_sLangTxt_SelFolder;
	extern  CString g_sLangID_FileName;  //文件名      
	extern  CString g_sLangTxt_FileName;
	extern  CString g_sLangID_NewFolder;  //新建文件夹      
	extern  CString g_sLangTxt_NewFolder;
	extern  CString g_sLangID_FolderNmMdf;  //文件夹名称修改     
	extern  CString g_sLangTxt_FolderNmMdf;
	//
	extern  CString g_sLangID_NotAuthorized;      
	extern  CString g_sLangTxt_NotAuthorized;
// 	extern  CString g_sLangID_AuthorizedUserUnit;//版权所有：%s      授权用户单位：%s     授权用户名：%s      
// 	extern  CString g_sLangTxt_AuthorizedUserUnit;
	extern  CString g_sLangID_NotAuthorized2;      
	extern  CString g_sLangTxt_NotAuthorized2;
	extern  CString g_sLangID_Close; //关闭
	extern  CString g_sLangTxt_Close;
	extern  CString g_sLangID_DataSets; //数据集
	extern  CString g_sLangTxt_DataSets;
	extern  CString g_sLangID_EquipDataModel; //设备数据模型
	extern  CString g_sLangTxt_EquipDataModel;
	extern  CString g_sLangID_DevAtrbDefin; //设备属性定义
	extern  CString g_sLangTxt_DevAtrbDefin;
	extern  CString g_sLangID_LogicdevCPU; //逻辑设备(CPU)
	extern  CString g_sLangTxt_LogicdevCPU;
	extern  CString g_sLangID_LogicDevice; //逻辑设备
	extern  CString g_sLangTxt_LogicDevice;
	extern  CString g_sLangID_LogicDeviceMap; //逻辑设备MAP
	extern  CString g_sLangTxt_LogicDeviceMap;
	extern  CString g_sLangID_DataSetsMap; //数据集
	extern  CString g_sLangTxt_DataSetsMap;
	extern  CString g_sLangID_ParaTypeGroup; //参数类型【%s】组必须有一组
	extern  CString g_sLangTxt_ParaTypeGroup;
	extern  CString g_sLangID_NoParaTypeGroup; //不存在参数类型为【%s】的组
	extern  CString g_sLangTxt_NoParaTypeGroup;
	extern  CString g_sLangID_DevDataFile; //设备数据模型文件(*.xml)|*.xml||
	extern  CString g_sLangTxt_DevDataFile;
	extern  CString g_sLangID_RightsReserved; //版权所有：
	extern  CString g_sLangTxt_RightsReserved;
	extern  CString g_sLangID_LicensedTo; //授权给：
	extern  CString g_sLangTxt_LicensedTo;
	extern  CString g_sLangID_DataTypeUnExist; //Row=%d  Col=%d  数据类型对象不存在
	extern  CString g_sLangTxt_DataTypeUnExist;
	extern  CString g_sLangID_Sizes; //号
	extern  CString g_sLangTxt_Sizes;
	extern  CString g_sLangID_SourceDataObject; //源数据对象
	extern  CString g_sLangTxt_SourceDataObject;
	extern  CString g_sLangID_MatchDataObject; //匹配数据对象
	extern  CString g_sLangTxt_MatchDataObject;
	extern  CString g_sLangID_SelMatchDataObject; //选择匹配的数据对象
	extern  CString g_sLangTxt_SelMatchDataObject;
    //Sentinel LDK
	extern  CString g_sLangID_USBKey; //请插入授权加密狗！
	extern  CString g_sLangTxt_USBKey;
	extern  CString g_sLangID_USBKeyUpdate; //授权加密狗驱动程序版本过低，请更新驱动程序！
	extern  CString g_sLangTxt_USBKeyUpdate;
	extern  CString g_sLangID_NoUSBkey; //没有安装授权加密狗驱动程序，请安装驱动程序！
	extern  CString g_sLangTxt_NoUSBkey;
	extern  CString g_sLangID_SystemError; //系统错误！
	extern  CString g_sLangTxt_SystemError;
	extern  CString g_sLangID_SystemError2; //系统错误：HASP_INV_HND：Invalid login handle passed to function
	extern  CString g_sLangTxt_SystemError2;
	extern  CString g_sLangID_SystemError3; //系统错误：HASP_INV_FILEID：Specified File ID not recognized by API
	extern  CString g_sLangTxt_SystemError3;
	extern  CString g_sLangID_SystemError4; //系统错误：HASP_MEM_RANGE：Request exceeds memory range of a Sentinel file
	extern  CString g_sLangTxt_SystemError4;
// 	extern  CString g_sLangID_RightReservedS; //版权所有：%s
// 	extern  CString g_sLangTxt_RightReservedS;
	extern  CString g_sLangID_SystemDevelop; //系统开发：%s
	extern  CString g_sLangTxt_SystemDevelop;
	extern  CString g_sLangID_ClientUnit; //客户单位：%s
	extern  CString g_sLangTxt_ClientUnit;
	extern  CString g_sLangID_UserName; //使用用户：%s
	extern  CString g_sLangTxt_UserName;
	extern  CString g_sLangID_ServerLicense; //服务器授权
	extern  CString g_sLangTxt_ServerLicense;
	extern  CString g_sLangID_ServerLicense2; //从服务器获取授权信息，请稍候....
	extern  CString g_sLangTxt_ServerLicense2;
	extern  CString g_sLangID_LicenseCommun; //与授权服务器通信超时，请确保网络连接和服务器配置正确！
	extern  CString g_sLangTxt_LicenseCommun;
	//TestMacro
	extern  CString g_sLangID_TestInstSel; 
	extern  CString g_sLangTxt_TestInstSel;
	extern  CString g_sLangID_AddScriptFail; //加载功能脚本文件[%s]失败
	extern  CString g_sLangTxt_AddScriptFail;
	extern  CString g_sLangID_TestFctnUnExist; //测试功能\"%s\"不存在
	extern  CString g_sLangTxt_TestFctnUnExist;
	extern  CString g_sLangID_IEC61850SetFile; //IEC61850配置文件
	extern  CString g_sLangTxt_IEC61850SetFile;
	extern  CString g_sLangID_ComtradeFile; //ComtradeFile
	extern  CString g_sLangTxt_ComtradeFile;
	extern  CString g_sLangID_TestFctnFile; //测试功能标准文件
	extern  CString g_sLangTxt_TestFctnFile;
	extern  CString g_sLangID_CommunStraFile; //通讯标准文件
	extern  CString g_sLangTxt_CommunStraFile;
	extern  CString g_sLangID_Number2; //编号/条目号
	extern  CString g_sLangTxt_Number2;
	extern  CString g_sLangID_ALreadyExist; //【%s】在【%s】已经存在
	extern  CString g_sLangTxt_ALreadyExist;
	extern  CString g_sLangID_MdtInsert;    //插入
	extern  CString g_sLangTxt_MdtInsert;
	extern  CString g_sLangID_UpMove;    //上移
	extern  CString g_sLangTxt_UpMove;
	extern  CString g_sLangID_DownMove;    //下移
	extern  CString g_sLangTxt_DownMove;
	extern  CString g_sLangID_Unit;
	extern  CString g_sLangTxt_Unit;
	extern  CString g_sLangID_MinValue;//最小值
	extern  CString g_sLangTxt_MinValue;
	extern  CString g_sLangID_MaxValue;//最大值
	extern  CString g_sLangTxt_MaxValue;
	extern  CString g_sLangID_Step;//步长
	extern  CString g_sLangTxt_Step;
	extern  CString g_sLangID_Nonstandard;//非标
	extern  CString g_sLangTxt_Nonstandard;
	extern  CString g_sLangID_StatePower;//国电南京自动化股份有限公司
	extern  CString g_sLangTxt_StatePower;
	extern  CString g_sLangID_Aphase;//A相
	extern  CString g_sLangTxt_Aphase;
	extern  CString g_sLangID_Bphase;//B相
	extern  CString g_sLangTxt_Bphase;
	extern  CString g_sLangID_Cphase;//C相
	extern  CString g_sLangTxt_Cphase;
	extern  CString g_sLangID_ABphase;//AB相
	extern  CString g_sLangTxt_ABphase;
	extern  CString g_sLangID_BCphase;//BC相
	extern  CString g_sLangTxt_BCphase;
	extern  CString g_sLangID_CAphase;//CA相
	extern  CString g_sLangTxt_CAphase;
	extern  CString g_sLangID_Application;//应用程序向导生成的本地应用程序
	extern  CString g_sLangTxt_Application;
	extern  CString g_sLangID_FixedValueRegion;
	extern  CString g_sLangTxt_FixedValueRegion;
	extern  CString g_sLangID_CloseTip;
	extern  CString g_sLangTxt_CloseTip;
	extern  CString g_sLangID_Modify; //修改
	extern  CString g_sLangTxt_Modify;
	extern  CString g_sLangID_ItemPrtcFile; //设备点表文件(*.xml)|*.xml||
	extern  CString g_sLangTxt_ItemPrtcFile;
	extern  CString g_sLangID_SelDevDaModFile;//选择设备数据模型文件
	extern  CString g_sLangTxt_SelDevDaModFile;
	extern  CString g_sLangID_TemDataFileChange; //模板设备数据模型替换映射配置文件
	extern  CString g_sLangTxt_TemDataFileChange;
	extern  CString g_sLangID_ConServerFail; //连接服务器【%s】【%d】失败
	extern  CString g_sLangTxt_ConServerFail;
	extern CString g_sLangID_ConServerSucc;//= _T("sConServerSucc");
	extern CString g_sLangTxt_ConServerSucc;//= _T("连接服务器【%s】【%d】成功");
	extern  CString g_sLangID_UserUnExist; //用户名不存在
	extern  CString g_sLangTxt_UserUnExist;
	extern  CString g_sLangID_PasswordIncorrect; //密码不正确
	extern  CString g_sLangTxt_PasswordIncorrect;
	extern  CString g_sLangID_LoginError; //登录错误
	extern  CString g_sLangTxt_LoginError;
	extern  CString g_sLangID_StopTest; //停止测试
	extern  CString g_sLangTxt_StopTest;
	extern  CString g_sLangID_StartTest;//停止测试，停止测试
	extern  CString g_sLangTxt_StartTest;
	extern  CString g_sLangID_ExportReport;    //导出报告
	extern  CString g_sLangTxt_ExportReport;
	extern  CString g_sLangID_ExportReportBatch;    //导出报告
	extern  CString g_sLangTxt_ExportReportBatch;
	extern  CString g_sLangID_StatusBar; 
	extern  CString g_sLangTxt_StatusBar;
	extern  CString g_sLangID_TestStop2;//连接设备失败，测试终止
	extern  CString g_sLangTxt_TestStop2;
	extern  CString g_sLangID_DataOpreation;//数据操作
	extern  CString g_sLangTxt_DataOpreation;

	extern  CString g_sLangID_OpenTip;
	extern  CString g_sLangTxt_OpenTip;
	extern  CString g_sLangID_ModelTestTip;//开始测试，开始测试两个数设备数据模型
	extern  CString g_sLangTxt_ModelTestTip;
	extern  CString g_sLangID_DevModelTestTip;//装置模型测试，从装置枚举数据模型，然后进行测试
	extern  CString g_sLangTxt_DevModelTestTip;
	extern  CString g_sLangID_StopTestTip;//停止测试，停止测试
	extern  CString g_sLangTxt_StopTestTip;
	extern  CString g_sLangID_ExportReportTip;//导出报告，导出报告
	extern  CString g_sLangTxt_ExportReportTip;
	extern  CString g_sLangID_SaveFileTip;//保存文件，保存设备数据模型映射关系文件
	extern  CString g_sLangTxt_SaveFileTip;
	extern  CString g_sLangID_OutputBarTip;//切换输出栏，显示或隐藏输出栏
	extern  CString g_sLangTxt_OutputBarTip;
	extern  CString g_sLangID_StatusBarTip;//切换状态栏，显示或隐藏状态栏
	extern  CString g_sLangTxt_StatusBarTip;
	extern  CString g_sLangID_CompareDataTip;//比较ID，比较ID
	extern  CString g_sLangTxt_CompareDataTip;
	extern  CString g_sLangID_AboutTip;//关于，显示程序信息、版本号和版权
	extern  CString g_sLangTxt_AboutTip;
	extern  CString g_sLangID_TestMain;//测试主页(&H)
	extern  CString g_sLangTxt_TestMain;
	extern  CString g_sLangID_ModelTest;//模型测试
	extern  CString g_sLangTxt_ModelTest;
	extern  CString g_sLangID_ProtocolTest;//规约测试
	extern  CString g_sLangTxt_ProtocolTest;
	extern  CString g_sLangID_ModelFileTest;//模型文件测试
	extern  CString g_sLangTxt_ModelFileTest;	
	extern  CString g_sLangID_DevModelTest;//装置模型测试
	extern  CString g_sLangTxt_DevModelTest;
	extern  CString g_sLangID_ResultOpera;//结果操作
	extern  CString g_sLangTxt_ResultOpera;
	extern  CString g_sLangID_SaveFile;//保存映射文件
	extern  CString g_sLangTxt_SaveFile;
	extern  CString g_sLangID_OutputBar;//输出栏
	extern  CString g_sLangTxt_OutputBar;
	extern  CString g_sLangID_CompareData;//比较数据ID
	extern  CString g_sLangTxt_CompareData;
	extern  CString g_sLangID_CmpDataNameFull;//数据名称全字符串比较
	extern  CString g_sLangTxt_CmpDataNameFull;
	extern  CString g_sLangID_Browse;//浏览
	extern  CString g_sLangTxt_Browse;
	extern  CString g_sLangID_Home;//主页(&H)
	extern  CString g_sLangTxt_Home;
	extern  CString g_sLangID_CreatDataMap;//创建数据映射
	extern  CString g_sLangTxt_CreatDataMap;
	extern  CString g_sLangID_DeleteDataMap;//删除数据映射
	extern  CString g_sLangTxt_DeleteDataMap;
	extern  CString g_sLangID_CreatDataMap2;//创建数据映射
	extern  CString g_sLangTxt_CreatDataMap2;
	extern  CString g_sLangID_DeleteDataMap2;//删除数据映射
	extern  CString g_sLangTxt_DeleteDataMap2;
	extern  CString g_sLangID_SelStdDataFile;//请选择标准设备数据模型文件
	extern  CString g_sLangTxt_SelStdDataFile;
	extern  CString g_sLangID_DataSetNoOnly;//数据集【%s】不唯一
	extern  CString g_sLangTxt_DataSetNoOnly;
	extern  CString g_sLangID_User;
	extern  CString g_sLangTxt_User;
	extern  CString g_sLangID_Module;
	extern  CString g_sLangTxt_Module;
	extern  CString g_sLangID_RemotePort;
	extern  CString g_sLangTxt_RemotePort;
	extern  CString g_sLangID_LocalPort;
	extern  CString g_sLangTxt_LocalPort;
	extern  CString g_sLangID_State;
	extern  CString g_sLangTxt_State;
	extern  CString g_sLangID_ServerWorkPath;
	extern  CString g_sLangTxt_ServerWorkPath;

	extern  CString g_sLangID_New;
	extern  CString g_sLangTxt_New;
	extern  CString g_sLangID_TemNew;
	extern  CString g_sLangTxt_TemNew;
	extern  CString g_sLangID_NewTip;
	extern  CString g_sLangTxt_NewTip;
	extern  CString g_sLangID_OpenTips;
	extern  CString g_sLangTxt_OpenTips;
	extern  CString g_sLangID_SaveTips;
	extern  CString g_sLangTxt_SaveTips;
	extern  CString g_sLangID_SaveAsTips;
	extern  CString g_sLangTxt_SaveAsTips;
	extern  CString g_sLangID_RecentFile;
	extern  CString g_sLangTxt_RecentFile;

	extern  CString g_sLangID_TemplateDef;
	extern  CString g_sLangTxt_TemplateDef;
	extern  CString g_sLangID_TemplateProperty;
	extern  CString g_sLangTxt_TemplateProperty;
	extern  CString g_sLangID_CommDef;
	extern  CString g_sLangTxt_CommDef;
	extern  CString g_sLangID_InitDef;
	extern  CString g_sLangTxt_InitDef;
	extern  CString g_sLangID_Exist;
	extern  CString g_sLangTxt_Exist;
	extern  CString g_sLangID_NoDataNotInsert;
	extern  CString g_sLangTxt_NoDataNotInsert;
	extern  CString g_sLangID_Attention;
	extern  CString g_sLangTxt_Attention;
	extern  CString g_sLangID_KeySameId;
	extern  CString g_sLangTxt_KeySameId;

	extern  CString g_sLangID_InitiaErrors;  //初始化错误
	extern  CString g_sLangTxt_InitiaErrors;
	extern  CString g_sLangID_OtherStart;  //对方没有启动
	extern  CString g_sLangTxt_OtherStart;
	extern  CString g_sLangID_OtherClose;  //对方已经关闭
	extern  CString g_sLangTxt_OtherClose;
	extern  CString g_sLangID_ConnectRefuse;  //连接的尝试被拒绝
	extern  CString g_sLangTxt_ConnectRefuse;
	extern  CString g_sLangID_AttemptOperate;  //在一个非套接字上尝试了一个操作
	extern  CString g_sLangTxt_AttemptOperate;
	extern  CString g_sLangID_SpecificUse;  //特定的地址已在使用中
	extern  CString g_sLangTxt_SpecificUse;
	extern  CString g_sLangID_ConnectionClosed;  //与主机的连接被关闭
	extern  CString g_sLangTxt_ConnectionClosed;
	extern  CString g_sLangID_GenericError;  //一般错误
	extern  CString g_sLangTxt_GenericError;
	extern  CString g_sLangID_Add;       //添加
	extern  CString g_sLangTxt_Add;
	extern  CString g_sLangID_NoDataChangeMsg;       //没有注册节点[%d]数据改变消息
	extern  CString g_sLangTxt_NoDataChangeMsg;
	extern  CString g_sLangID_FileNameInclude;       //文件名【%s】包含【%s】等非法字符
	extern  CString g_sLangTxt_FileNameInclude;
	extern  CString g_sLangID_Add3;       
	extern  CString g_sLangTxt_Add3;
	extern  CString g_sLangID_Select;//选择
	extern  CString g_sLangTxt_Select;
	extern  CString g_sLangID_Value;
	extern  CString g_sLangTxt_Value;
	extern  CString g_sLangID_DefaultValue;
	extern  CString g_sLangTxt_DefaultValue;

	extern  CString g_sLangID_PrtcTempFile;     //规约模板文件
	extern  CString g_sLangTxt_PrtcTempFile;
	extern  CString g_sLangID_PrtcProjectFile;     //规约模板文件
	extern  CString g_sLangTxt_PrtcProjectFile;
	extern  CString g_sLangID_ModelFile;//模型文件
	extern  CString g_sLangTxt_ModelFile;

	extern  CString g_sLangID_PrtcTempFileMagn;     //规约模板文件管理
	extern  CString g_sLangTxt_PrtcTempFileMagn;
	extern  CString g_sLangID_Version;    
	extern  CString g_sLangTxt_Version;
	extern  CString g_sLangID_TimeLimit;     //时限
	extern  CString g_sLangTxt_TimeLimit;
	extern  CString g_sLangID_ComparaObject;     //比较项
	extern  CString g_sLangTxt_ComparaObject;
	extern  CString g_sLangID_StandardValue;     //标准值
	extern  CString g_sLangTxt_StandardValue;
	extern  CString g_sLangID_TureValue;     //实际值
	extern  CString g_sLangTxt_TureValue;
	extern  CString g_sLangID_Property;     //属性
	extern  CString g_sLangTxt_Property;
	extern  CString g_sLangID_UnStallWord;     //没有安装Word
	extern  CString g_sLangTxt_UnStallWord;
	extern  CString g_sLangID_Title;     //标题 %d
	extern  CString g_sLangTxt_Title;
	extern  CString g_sLangID_UserUnits;     //用户单位：
	extern  CString g_sLangTxt_UserUnits;
	extern  CString g_sLangID_User2;     //用户：
	extern  CString g_sLangTxt_User2;
	extern  CString g_sLangID_Develop;     //开发：
	extern  CString g_sLangTxt_Develop;
	extern  CString g_sLangID_ReName;     //重命名
	extern  CString g_sLangTxt_ReName;
	extern  CString g_sLangID_Variable;     
	extern  CString g_sLangTxt_Variable;
	extern  CString g_sLangID_DeleteFloder;     //删除文件夹
	extern  CString g_sLangTxt_DeleteFloder;
	extern  CString g_sLangID_SureDelFoldItem;     //确定要删除文件夹 %s 及其子项目吗?
	extern  CString g_sLangTxt_SureDelFoldItem;
	extern  CString g_sLangID_Size2;     //大小
	extern  CString g_sLangTxt_Size2;
	extern  CString g_sLangID_ModiftyFileNameFail;     //修改文件名称失败
	extern  CString g_sLangTxt_ModiftyFileNameFail;


//重庆研发新增
	extern CString g_sLangID_SCDFiles;
	extern CString g_sLangTxt_SCDFiles;           
	extern CString g_sLangID_RecordFiles;         
	extern CString g_sLangTxt_RecordFiles;
	extern CString g_sLangID_TemplateFiles;
	extern CString g_sLangTxt_TemplateFiles;
	extern CString g_sLangID_WorkspaceFiles;
	extern CString g_sLangTxt_WorkspaceFiles;
	extern CString g_sLangID_IEC61850SetFiles;
	extern CString g_sLangTxt_IEC61850SetFiles;
	extern CString g_sLangID_PcapFiles;
	extern CString g_sLangTxt_PcapFiles;
	extern CString g_sLangID_PrintScreen;
	extern CString g_sLangTxt_PrintScreen;
	extern CString g_sLangID_Others;
	extern CString g_sLangTxt_Others;
	extern CString g_sLangID_SavePcapFiles;
	extern CString g_sLangTxt_SavePcapFiles;	
	extern CString g_sLangID_SavePrintScreen;
	extern CString g_sLangTxt_SavePrintScreen;		
	extern CString g_sLangID_OtherTypeFiles;
	extern CString g_sLangTxt_OtherTypeFiles;




	extern  CString g_sLangID_Output;     
	extern  CString g_sLangTxt_Output;
	extern  CString g_sLangID_ConfirmDel;     
	extern  CString g_sLangTxt_ConfirmDel;
	extern  CString g_sLangID_NoSave;     
	extern  CString g_sLangTxt_NoSave;
	extern  CString g_sLangID_Increase;
	extern  CString g_sLangTxt_Increase;
	extern  CString g_sLangID_Decrease;
	extern  CString g_sLangTxt_Decrease;
	extern  CString g_sLangID_Export;      
	extern  CString g_sLangTxt_Export;
	extern  CString g_sLangID_Import;   
	extern  CString g_sLangTxt_Import;

	extern  CString g_sLangID_ClcltFmla;   
	extern  CString g_sLangTxt_ClcltFmla;

	extern  CString g_sLangID_GuideWizardFile;
	extern  CString g_sLangTxt_GuideWizardFile;

	extern  CString g_sLangID_IecConfigFile;//            = _T("sIecConfigFile");
	extern  CString g_sLangTxt_IecConfigFile;//           = _T("IEC61850配置文件");
	extern  CString g_sLangID_DvIecConfigFile;//            = _T("sDvIecConfigFile");
	extern  CString g_sLangTxt_DvIecConfigFile;//           = _T("智能设备测试仪IEC61850配置文件管理");
	extern  CString g_sLangID_DvIecConfigFileMngr;//            = _T("sDvIecConfigFileMngr");
	extern  CString g_sLangTxt_DvIecConfigFileMngr;//           = _T("智能设备测试仪IEC61850配置文件管理");

	extern  CString g_sLangID_NoTitle;//无标题
	extern  CString g_sLangTxt_NoTitle;
	extern  CString g_sLangID_FileNotExist;//文件【%s】不存在
	extern  CString g_sLangTxt_FileNotExist;

	extern  CString g_sLangID_YunDownFileFaild;//从云端下载文件失败
	extern  CString g_sLangTxt_YunDownFileFaild;

	extern  CString g_sLangID_UpLoad; 
	extern  CString g_sLangTxt_UpLoad;
	extern  CString g_sLangID_DownLoad; 
	extern  CString g_sLangTxt_DownLoad;

	extern  CString g_sLangID_TestItemParEdit; //测试项目参数编辑
	extern  CString g_sLangTxt_TestItemParEdit;
	extern  CString g_sLangID_ParaName; //参数名称
	extern  CString g_sLangTxt_ParaName;
	extern  CString g_sLangID_ParaValue; //参数值
	extern  CString g_sLangTxt_ParaValue;

	extern  CString g_sLangID_GlobalData;
	extern  CString g_sLangTxt_GlobalData;
	extern  CString g_sLangID_TestAppDef;
	extern  CString g_sLangTxt_TestAppDef;
	extern  CString g_sLangID_RepeatResultInfo;
	extern  CString g_sLangTxt_RepeatResultInfo;


	extern  CString g_sLangID_Login; 
	extern  CString g_sLangTxt_Login;
	extern  CString g_sLangID_Clear; 
	extern  CString g_sLangTxt_Clear;
	extern  CString g_sLangID_SyntaxCheck; 
	extern  CString g_sLangTxt_SyntaxCheck;
	extern  CString g_sLangID_SyntaxCheckTips; 
	extern  CString g_sLangTxt_SyntaxCheckTips;

	extern CString g_sLangID_OutputWnd;       //输出窗口
	extern CString g_sLangTxt_OutputWnd;

	extern CString g_sLangID_DataSet;
	extern CString g_sLangTxt_DataSet;

	extern CString g_sLangID_Quit; 
	extern CString g_sLangTxt_Quit;
	extern CString g_sLangID_QuitTip; 
	extern CString g_sLangTxt_QuitTip;

    //2024-1-4  shaolei
    extern CString g_sLangID_Voltage;       //电压
    extern CString g_sLangTxt_Voltage;
    extern CString g_sLangID_Current;       //电流
    extern CString g_sLangTxt_Current;
    extern CString g_sLangID_ActivePower;       //有功功率
    extern CString g_sLangTxt_ActivePower;
    extern CString g_sLangID_ReactivePower;       //无功功率
    extern CString g_sLangTxt_ReactivePower;
    extern CString g_sLangID_Frequency;       //频率
    extern CString g_sLangTxt_Frequency;
    extern CString g_sLangID_PowerFactor;       //功率因数
    extern CString g_sLangTxt_PowerFactor;


	extern CString g_sLangID_Native_StartOutput;
	extern CString g_sLangTxt_Native_StartOutput;		//开始输出
	//实际在CXLanguageResourceAtsBase中定义故删除  zhouhj 2024.5.25
//     extern CString g_sLangID_TestComplete               ;//= _T("sTestComplete");
//     extern CString g_sLangTxt_TestComplete                  ;//= _T("测试完成");
    extern CString g_sLangID_Native_TestAnomalies;     //= _T("Native_TestAnomalies");
    extern CString g_sLangTxt_Native_TestAnomalies;    //= _T("测试异常");
    extern CString g_sLangID_Native_RelieveTestAnomalies; //= _T("Native_RelieveTestAnomalies")
    extern CString g_sLangTxt_Native_RelieveTestAnomalies; //= _T("解除测试异常")
    extern CString g_sLangID_Native_StateSwitch;        //= _T("Native_StateSwitch");
    extern CString g_sLangTxt_Native_StateSwitch;       //= _T("状态切换");
    extern CString g_sLangID_Native_SupDCSwitch;        //= _T("Native_SupDCSwitch");
    extern CString g_sLangTxt_Native_SupDCSwitch;       //= _T("辅助直流切换");
    extern CString g_sLangID_Native_BinDisPlace;        // = _T("Native_BinDisPlace");
    extern CString g_sLangTxt_Native_BinDisPlace;       //= _T("开入变位");
    extern CString g_sLangID_Native_BoutDisPlace;       //= _T("Native_BoutDisPlace");
    extern CString g_sLangTxt_Native_BoutDisPlace;      //= _T("开出变位");
    extern CString g_sLangID_Native_ParaUpdata;         //= _T("Native_ParaUpdata");
    extern CString g_sLangTxt_Native_ParaUpdata;        //= _T("参数更新");


	extern CString g_sLangID_Native_Port;		// = _T("Native_Port")
	extern CString g_sLangTxt_Native_Port;        //= _T("口");

	extern CString g_sLangID_TestInstrumentConfig;
	extern CString g_sLangTxt_TestInstrumentConfig;
	extern CString g_sLangID_ScanLANTestInstrument;
	extern CString g_sLangTxt_ScanLANTestInstrument;
	extern CString g_sLangID_DirectConfigRemoteInstrument;
	extern CString g_sLangTxt_DirectConfigRemoteInstrument;
	extern CString g_sLangID_ScanRemoteTestInstrument;
	extern CString g_sLangTxt_ScanRemoteTestInstrument;
	extern CString g_sLangID_Setup;
	extern CString g_sLangTxt_Setup;
	extern CString g_sLangID_Upgrade;
	extern CString g_sLangTxt_Upgrade;
	extern CString g_sLangID_EnablePUDA;
	extern CString g_sLangTxt_EnablePUDA;
	extern CString g_sLangID_EnableTestSvr;
	extern CString g_sLangTxt_EnableTestSvr;
	extern CString g_sLangID_TestInstrumentModel;
	extern CString g_sLangTxt_TestInstrumentModel;
	extern CString g_sLangID_TestInstrumentID;
	extern CString g_sLangTxt_TestInstrumentID;
	extern CString g_sLangID_CloudIP;
	extern CString g_sLangTxt_CloudIP;
	extern CString g_sLangID_CloudPort;
	extern CString g_sLangTxt_CloudPort;
	extern CString g_sLangID_TestInstrumentSerialNumber;
	extern CString g_sLangTxt_TestInstrumentSerialNumber;
	extern CString g_sLangID_Password;
	extern CString g_sLangTxt_Password;
	extern CString g_sLangID_Unit2;
	extern CString g_sLangTxt_Unit2;
	extern CString g_sLangID_Bind;
	extern CString g_sLangTxt_Bind;
	extern CString g_sLangID_Query;
	extern CString g_sLangTxt_Query;
	extern CString g_sLangID_TestInstrumentConnectionError;
	extern CString g_sLangTxt_TestInstrumentConnectionError;
	extern CString g_sLangID_CloudServerConnectionError;
	extern CString g_sLangTxt_CloudServerConnectionError;
	extern CString g_sLangID_IPIsEmpty;
	extern CString g_sLangTxt_IPIsEmpty;
	extern CString g_sLangID_ConnectionTestInstrumentFailed;
	extern CString g_sLangTxt_ConnectionTestInstrumentFailed;
	extern CString g_sLangID_MulticastInitSuccess;
	extern CString g_sLangTxt_MulticastInitSuccess;
	extern CString g_sLangID_MulticastInitFailed;
	extern CString g_sLangTxt_MulticastInitFailed;
	extern CString g_sLangID_MulticastInitBindSuccess;
	extern CString g_sLangTxt_MulticastInitBindSuccess;
	extern CString g_sLangID_Disconnection;
	extern CString g_sLangTxt_Disconnection;
	extern CString g_sLangID_CloudConnectionFailed;
	extern CString g_sLangTxt_CloudConnectionFailed;
	extern CString g_sLangID_TestInstrumentUserInfoError;
	extern CString g_sLangTxt_TestInstrumentUserInfoError;
	extern CString g_sLangID_Connect;
	extern CString g_sLangTxt_Connect;
	extern CString g_sLangID_StopScanning;
	extern CString g_sLangTxt_StopScanning;
	extern CString g_sLangID_Scanning;
	extern CString g_sLangTxt_Scanning;
	extern CString g_sLangID_NanjingEnergyCloud;
	extern CString g_sLangTxt_NanjingEnergyCloud;
	extern CString g_sLangID_TestInstrumentConfigFileNotFound;
	extern CString g_sLangTxt_TestInstrumentConfigFileNotFound;
	extern CString g_sLangID_OAClientInitFail;
	extern CString g_sLangTxt_OAClientInitFail;
    //2024-10-22  wuxinyi
	extern CString g_sLangID_ResultBar;//结果栏
	extern CString g_sLangTxt_ResultBar;
	extern CString g_sLangID_StatusLight;
	extern CString g_sLangTxt_StatusLight;
	extern CString g_sLangID_WinwordProcessWarning;
	extern CString g_sLangTxt_WinwordProcessWarning;
	extern CString g_sLangID_CloseProcessWarning;
	extern CString g_sLangTxt_CloseProcessWarning;
	//2024-11-08 zhouyangyong
	extern CString g_sLangID_NotSupportVoltGather;
	extern CString g_sLangTxt_NotSupportVoltGather;

	extern CString g_sLangID_CreatReplaySocket;
	extern CString g_sLangTxt_CreatReplaySocket;//建立报文故障回放通道......
	extern CString g_sLangID_CreatCapRcdSocket;
	extern CString g_sLangTxt_CreatCapRcdSocket;//建立报文录波通道......
	extern CString g_sLangID_ConnectOKWaitTest;
	extern CString g_sLangTxt_ConnectOKWaitTest;//连接完成，准备开始测试......
	extern CString g_sLangID_RevReplayRequest;
	extern CString g_sLangTxt_RevReplayRequest;//收到回放数据请求
	extern CString g_sLangID_RevSendDataReply;
	extern CString g_sLangTxt_RevSendDataReply;//收到发送数据开始应答
	extern CString g_sLangID_ReplayData;
	extern CString g_sLangTxt_ReplayData;//回放数据
	extern CString g_sLangID_ReadyToSend;
	extern CString g_sLangTxt_ReadyToSend;//准备发送
	extern CString g_sLangID_SentComplete;
	extern CString g_sLangTxt_SentComplete;//已发送完成
	extern CString g_sLangID_SentAllReplayData;
	extern CString g_sLangTxt_SentAllReplayData;//回放数据全部发送完成

 	//extern CString g_sLangID_Qualified;
 	//extern CString g_sLangTxt_Qualified;//合格
	//extern CString g_sLangID_Unqualified;
	//extern CString g_sLangTxt_Unqualified;//不合格
	extern CString g_sLangID_ControlBlock;
	extern CString g_sLangTxt_ControlBlock;//控制块
	extern CString g_sLangID_Packet;
	extern CString g_sLangTxt_Packet;//报文
	extern CString g_sLangID_AxisUnitOmega;
	extern CString g_sLangTxt_AxisUnitOmega;//Ω
	extern CString g_sLangID_AxisUnitAng;
	extern CString g_sLangTxt_AxisUnitAng;//°
	extern CString g_sLangID_AxisUnitDeltaSmall;
	extern CString g_sLangTxt_AxisUnitDeltaSmall;//δ
	//extern CString g_sLangID_Diff_Variation;            //_T("Diff_Variation")
	//extern CString g_sLangTxt_Diff_Variation;           //_T("△")
	extern CString g_sLangID_AxisUnitPhi;            //_T("AxisUnitPhi")
	extern CString g_sLangTxt_AxisUnitPhi;           //_T("Φ")
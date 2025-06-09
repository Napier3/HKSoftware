#ifndef CSETTINGFILESTOXRIOTOOL_H
#define CSETTINGFILESTOXRIOTOOL_H

#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/MathApi.h"
#include "../../../Module/API/GlobalApi.h"
#include "../../../Module/MemBuffer/BufferBase.h"
#include "XDeviceModel/XDeviceModel.h"

//当前打开的文件类型
#define OPEN_FILE_TYPE_XRIO                              _T("xrio")
#define OPEN_FILE_TYPE_RIO                               _T("rio")
#define OPEN_FILE_TYPE_SET                               _T("set")
#define OPEN_FILE_TYPE_TXT                               _T("txt")
#define OPEN_FILE_TYPE_CSV                               _T("csv")

class CSettingFilesToXrioTool
{
public:
    CSettingFilesToXrioTool();
    virtual ~CSettingFilesToXrioTool();
    BOOL SettingFilesToXrio(const CString& strOpenFile, CDvmDevice *pDvmDevice,long& nModifyIndex,CExBaseList& oDvmGridList);
public:
    CString m_strFilePath;
private:
    //增加oUpdateList参数，现在对于如果名字重复的情况，都同时修改，而不是只修改查找到的第一个。
    CExBaseList m_oDvmUpdateListRef;//SettingFileFindChildByName函数查找到的更新对象。
    BOOL SettingFileFindChildByName(CExBaseList *pList,const CString &strName,CExBaseList &oUpdateList);

    //更新值
    BOOL UpdateDvmRefByData_Value(CExBaseObject *pObj, const CString& strValue);
    BOOL UpdateDvmRefByData(CDvmData *pDvmData, const CString& strValue);
    BOOL UpdateDvmRefByValue(CDvmValue *pDvmValue, const CString& strValue);
    CString GetNumberPart(const CString& input);
    void GetUpdateValue(const CString& strValue, CString& UpdateValue);
    BOOL GetCompareResult_DataType_Double(const double& dOldValue, const double& dNewValue, const double& dMinValue, const double& dMaxValue, CExBaseObject *pObj);
    BOOL GetCompareResult_DataType_Int(const int& nOldValue, const int& nNewValue, const int& nMinValue, const int& nMaxValue, CExBaseObject *pObj);
    BOOL GetCompareResult_DataType_Enumeration(CExBaseList *pList, const CString& strValue);

    //SET辅助函数
    enum SetFileLineType{EDIT_TYPE,COMBOX_TYPE};
    //该函数指针调用GetComboBoxTypeData_Value和GetEditTypeData_Value
    typedef BOOL(CSettingFilesToXrioTool::*SETTING_SET_FILE_FUNC)(CExBaseObject *,const CString&);
    SetFileLineType GetCurrStrType(const CString& CurrStr);
    BOOL ParseCurrLineType(const SetFileLineType& strLineType,const CString& strLine, CDvmLogicDevice *pCustomLogicDevice,SETTING_SET_FILE_FUNC pFunc, long& nModifyIndex, CExBaseList& oDvmGridList);
    BOOL ParseComboBoxType(const CString& strComboBox, CDvmLogicDevice *pCustomLogicDevice, long& nModifyIndex, CExBaseList& oDvmGridList);
    BOOL ParseEditType(const CString& strEdit, CDvmLogicDevice *pCustomLogicDevice, long& nModifyIndex, CExBaseList& oDvmGridList);
    BOOL GetComboBoxTypeData_Value(CExBaseObject *pObj ,const CString& strUpdateValue);
    BOOL GetEditTypeData_Value(CExBaseObject *pObj ,const CString& strUpdateValue);

    //SET
    BOOL SettingSETFileToXrio(CBufferBase& oBuffer, CDvmLogicDevice *pCustomLogicDevice,long& nModifyIndex, CExBaseList& oDvmGridList);
    //TXT
    BOOL SettingTXTFileToXrio(CBufferBase& oBuffer, CDvmLogicDevice *pCustomLogicDevice,long& nModifyIndex, CExBaseList& oDvmGridList);
    //CSV
    BOOL SettingCSVFileToXrio(CBufferBase& oBuffer, CDvmLogicDevice *pCustomLogicDevice,long& nModifyIndex, CExBaseList& oDvmGridList);

};

#endif // CSETTINGFILESTOXRIOTOOL_H

#include "SettingFilesToXrioTool.h"

CSettingFilesToXrioTool::CSettingFilesToXrioTool()
{

}

CSettingFilesToXrioTool::~CSettingFilesToXrioTool()
{
    m_oDvmUpdateListRef.RemoveAll();
}

BOOL CSettingFilesToXrioTool::SettingFilesToXrio(const CString& strOpenFile, CDvmDevice *pDvmDevice,long &nModifyIndex,CExBaseList &oDvmGridList)
{
    m_strFilePath = strOpenFile;
    CString strFilePostfix = ParseFilePostfix(m_strFilePath);

    if(strFilePostfix.CompareNoCase(OPEN_FILE_TYPE_SET) != 0 && strFilePostfix.CompareNoCase(OPEN_FILE_TYPE_TXT) != 0 && strFilePostfix.CompareNoCase(OPEN_FILE_TYPE_CSV) != 0)
    {
        return FALSE;
    }

    CBufferBase oBuffer;

    if (!oBuffer.ReadFromFile(strOpenFile))
    {
        return FALSE;
    }

    if(!pDvmDevice)
    {
        return FALSE;
    }

    CDvmLogicDevice *pCustomLogicDevice = (CDvmLogicDevice*)pDvmDevice->FindByID(XRIO_DEVICE_MODEL_ID_CUSTOM);
    if(pCustomLogicDevice == NULL)
    {
        return FALSE;
    }

    oBuffer.FormatBuffer('\r', 0);
    oBuffer.FormatBuffer('\n', 0);

    if(strFilePostfix.CompareNoCase(OPEN_FILE_TYPE_SET) == 0)
    {
        //SET文件解析
        return SettingSETFileToXrio(oBuffer,pCustomLogicDevice,nModifyIndex,oDvmGridList);
    }
    else if(strFilePostfix.CompareNoCase(OPEN_FILE_TYPE_TXT) == 0)
    {
        //TXT文件解析
        return SettingTXTFileToXrio(oBuffer,pCustomLogicDevice,nModifyIndex,oDvmGridList);
    }
    else if(strFilePostfix.CompareNoCase(OPEN_FILE_TYPE_CSV) == 0)
    {
        //CSV文件解析
        return SettingCSVFileToXrio(oBuffer,pCustomLogicDevice,nModifyIndex,oDvmGridList);
    }
    else
    {
        return FALSE;
    }
}

BOOL CSettingFilesToXrioTool::SettingFileFindChildByName(CExBaseList *pList,const CString &strName,CExBaseList &oUpdateList)
{
    //csv、txt、set文件均需要根据Name查找。
    CExBaseObject *p = NULL;

    for(POS startPos = pList->GetHeadPosition();startPos != NULL;)
    {
        p = pList->GetNext(startPos);
        if(p->m_strName == strName)
        {
            oUpdateList.AddTail(p);
        }

        if(p->IsBaseList())
            {
            SettingFileFindChildByName((CExBaseList*)p,strName,oUpdateList);
        }
    }

    return oUpdateList.IsEmpty();
}

BOOL CSettingFilesToXrioTool::UpdateDvmRefByData_Value(CExBaseObject *pObj, const CString &strValue)
{
    if(DVMCLASSID_CDVMDATA == pObj->GetClassID())
    {
        return UpdateDvmRefByData((CDvmData*)pObj,strValue);
    }
    else if(DVMCLASSID_CDVMVALUE == pObj->GetClassID())
    {
        return UpdateDvmRefByValue((CDvmValue*)pObj,strValue);
    }
    else
    {
        return FALSE;
    }
}

BOOL CSettingFilesToXrioTool::UpdateDvmRefByData(CDvmData *pDvmData, const CString &strValue)
{
    CString strNamePath = pDvmData->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
    CString strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pDvmData,FALSE);

    if(XRIO_CUSTOM_PARAMETER_DATATYPE_STRING == pDvmData->m_strDataType)
    {
        //字符串比较不适用CompareNoCase
        //csv文件在OMR中比较适用CompareNoCase，但是在txt文件关联中却不适用，现在统一按照 ==
        if(pDvmData->m_strValue == strValue)
        {
            return FALSE;
        }
        else
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
//            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Values.GetString(),pDvmData->m_strValue.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strValue.GetString());
            pDvmData->m_strValue = strValue;
            return TRUE;
        }
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == pDvmData->m_strDataType)
    {
        //此处无需考虑Nan和无穷的问题。
        //Nan和无穷已经被IsStringNumber和GetNumberPart过滤掉
        CDvmValue *pDvmValue = (CDvmValue*)GetAttrObj(pDvmData,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);
        ASSERT(pDvmValue);
        CString strTmp,strFormat;
        long nPrecision = CString_To_long(pDvmValue->m_strValue);
        strFormat.Format(_T("%%.%ldlf"), nPrecision);

        double dOldValue,dNewValue,dMinValue,dMaxValue;
        dMinValue = CString_To_double(pDvmData->m_strMin);
        dMaxValue = CString_To_double(pDvmData->m_strMax);
        dOldValue = CString_To_double(pDvmData->m_strValue);

        //直接从strValue中提取有效的数字部分，无需先考虑是否满足IsStringNumber。
        //300 s不是IsStringNumber，但是包含了数字和单位，提取出数字部分。
            CString strValidNumber = GetNumberPart(strValue);
            if(!IsStringNumber(strValidNumber) || strValidNumber.isEmpty())//IsStringNumber函数在输入为_T("")时仍然会返回TRUE
            {
                //"参数修改:(错误参数)-,-Path =【名称路径-%s(ID路径-%s)】无法设置导入的值:请输入一个数字。"
                return FALSE;
            }

        dNewValue = CString_To_double(strValidNumber);
            strTmp.Format(strFormat.GetString(), dNewValue);
            dNewValue = CString_To_double(strTmp);

            if(GetCompareResult_DataType_Double(dOldValue,dNewValue,dMinValue,dMaxValue,pDvmData))
            {
                //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
//                CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Values.GetString(),pDvmData->m_strValue.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strTmp.GetString());
                pDvmData->m_strValue = strTmp;
                return TRUE;
            }
            return FALSE;
        }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDvmData->m_strDataType)
    {
        return GetCompareResult_DataType_Enumeration(pDvmData,strValue);
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == pDvmData->m_strDataType)
    {
        int nOldValue,nNewValue,nMinValue,nMaxValue;
        nMinValue = CString_To_long(pDvmData->m_strMin);
        nMaxValue = CString_To_long(pDvmData->m_strMax);
        nOldValue = CString_To_long(pDvmData->m_strValue);

        //直接从strValue中提取有效的数字部分，无需先考虑是否满足IsStringNumber。
        CString strValidNumber = GetNumberPart(strValue);
        if(!IsStringInteger(strValidNumber) || strValidNumber.isEmpty())//IsStringInteger函数在输入为_T("")时仍然会返回TRUE
        {
            //"参数修改:(错误参数)-,-Path =【名称路径-%s(ID路径-%s)】无法设置导入的值:无效的整形值！"
//            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s:%s"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_Xrio_LogInfo_ErrParam.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_LogInfo_NotSetImpVal.GetString(),g_sLangTxt_Xrio_InvalidIntValue.GetString());
            return FALSE;
        }

        nNewValue = CString_To_long(strValidNumber);//此处无需考虑int溢出问题，CString_To_long函数会保证值处于INT_MAX和INT_MIN之间。

//        if(!bOk)
//        {
//            //"参数修改:(错误参数)-,-Path =【名称路径-%s(ID路径-%s)】无法设置导入的值:无效的整形值！"
//            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s:%s"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_Xrio_LogInfo_ErrParam.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_LogInfo_NotSetImpVal.GetString(),g_sLangTxt_Xrio_InvalidIntValue.GetString());
//            return FALSE;
//        }

            if(GetCompareResult_DataType_Int(nOldValue,nNewValue,nMinValue,nMaxValue,pDvmData))
            {
                //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
//                CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Values.GetString(),pDvmData->m_strValue.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strValidNumber.GetString());
                pDvmData->m_strValue = strValidNumber;
                return TRUE;
            }
            return FALSE;
        }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN == pDvmData->m_strDataType)
    {
        //布尔类型比较适用于CompareNoCase
        if(pDvmData->m_strValue.CompareNoCase(strValue) == 0 || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE_NUMERIC == pDvmData->m_strValue
                || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE_NUMERIC == pDvmData->m_strValue)
        {
            return FALSE;
        }
        else
        {
            if(strValue.CompareNoCase(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE) == 0 || strValue.CompareNoCase(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE) == 0
                    || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE_NUMERIC == strValue || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE_NUMERIC == strValue)
            {
                //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
//                CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Values.GetString(),pDvmData->m_strValue.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strValue.GetString());
                pDvmData->m_strValue = strValue;
                return TRUE;
            }
            //"参数修改:(错误参数)-,-Path =【名称路径-%s(ID路径-%s)】无法设置导入的值:无效的二进制值！"
//            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s:%s"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_Xrio_LogInfo_ErrParam.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_LogInfo_NotSetImpVal.GetString(),g_sLangTxt_Xrio_InvalidBinaryValue.GetString());
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

BOOL CSettingFilesToXrioTool::UpdateDvmRefByValue(CDvmValue *pDvmValue, const CString &strValue)
{
    CString strNamePath = pDvmValue->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
    CString strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pDvmValue,FALSE);

    if(XRIO_CUSTOM_PARAMETER_DATATYPE_STRING == pDvmValue->m_strDataType)
    {
        //字符串比较不适用CompareNoCase
        //csv文件在OMR中比较适合CompareNoCase，但是在txt文件关联中却不适用，现在统一按照 ==
        if(pDvmValue->m_strValue == strValue)
        {
            return FALSE;
        }
        else
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
//            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Values.GetString(),pDvmValue->m_strValue.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strValue.GetString());
            pDvmValue->m_strValue = strValue;
            return TRUE;
        }
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == pDvmValue->m_strDataType)
    {
        //此处无需考虑Nan和无穷的问题。
        //Nan和无穷已经被IsStringNumber和GetNumberPart过滤掉
        CDvmValue *pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);
        ASSERT(pAttrDvmValue);
        CString strTmp,strFormat;
        long nPrecision = CString_To_long(pAttrDvmValue->m_strValue);
        strFormat.Format(_T("%%.%ldlf"), nPrecision);

        double dOldValue,dNewValue,dMinValue,dMaxValue;

        pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_MinValue);
        if(pAttrDvmValue == NULL)
        {
            return FALSE;
        }
        dMinValue = CString_To_double(pAttrDvmValue->m_strValue);

        pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_MaxValue);
        if(pAttrDvmValue == NULL)
        {
            return FALSE;
        }
        dMaxValue = CString_To_double(pAttrDvmValue->m_strValue);

        dOldValue = CString_To_double(pDvmValue->m_strValue);

        //直接从strValue中提取有效的数字部分，无需先考虑是否满足IsStringNumber。
            //300 s不是IsStringNumber，但是包含了数字和单位，提取出数字部分
            CString strValidNumber = GetNumberPart(strValue);
            if(!IsStringNumber(strValidNumber) || strValidNumber.isEmpty())//IsStringNumber函数在输入为_T("")时仍然会返回TRUE
            {
                //"参数修改:(错误参数)-,-Path =【名称路径-%s(ID路径-%s)】无法设置导入的值:请输入一个数字。"
//                CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s:%s"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_Xrio_LogInfo_ErrParam.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_LogInfo_NotSetImpVal.GetString(),g_sLangTxt_Xrio_EnterNumbers.GetString());
                return FALSE;
            }

        dNewValue = CString_To_double(strValidNumber);
            strTmp.Format(strFormat.GetString(), dNewValue);
            dNewValue = CString_To_double(strTmp);

            if(GetCompareResult_DataType_Double(dOldValue,dNewValue,dMinValue,dMaxValue,pDvmValue))
            {
                //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
//                CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Values.GetString(),pDvmValue->m_strValue.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strTmp.GetString());
                pDvmValue->m_strValue = strTmp;
                return TRUE;
            }
            return FALSE;
        }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDvmValue->m_strDataType)
    {
        return GetCompareResult_DataType_Enumeration(pDvmValue,strValue);
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == pDvmValue->m_strDataType)
    {
        int nOldValue,nNewValue,nMinValue,nMaxValue;
        bool bOk;

        CDvmValue *pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_MinValue);
        if(pAttrDvmValue == NULL)
        {
            return FALSE;
        }
        nMinValue = CString_To_long(pAttrDvmValue->m_strValue);

        pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_MaxValue);
        if(pAttrDvmValue == NULL)
        {
            return FALSE;
        }
        nMaxValue = CString_To_long(pAttrDvmValue->m_strValue);

        nOldValue = CString_To_long(pDvmValue->m_strValue);

        //直接从strValue中提取有效的数字部分，无需先考虑是否满足IsStringNumber。
        CString strValidNumber = GetNumberPart(strValue);
        if(!IsStringInteger(strValidNumber) || strValidNumber.isEmpty())//IsStringInteger函数在输入为_T("")时仍然会返回TRUE
        {
            //"参数修改:(错误参数)-,-Path =【名称路径-%s(ID路径-%s)】无法设置导入的值:无效的整形值！"
//            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s:%s"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_Xrio_LogInfo_ErrParam.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_LogInfo_NotSetImpVal.GetString(),g_sLangTxt_Xrio_InvalidIntValue.GetString());
            return FALSE;
        }

        nNewValue = CString_To_long(strValidNumber);//此处无需考虑int溢出问题，CString_To_long函数会保证值处于INT_MAX和INT_MIN之间。

//        if(!bOk)
//        {
//            //"参数修改:(错误参数)-,-Path =【名称路径-%s(ID路径-%s)】无法设置导入的值:无效的整形值！"
//            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s:%s"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_Xrio_LogInfo_ErrParam.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_LogInfo_NotSetImpVal.GetString(),g_sLangTxt_Xrio_InvalidIntValue.GetString());
//            return FALSE;
//        }

            if(GetCompareResult_DataType_Int(nOldValue,nNewValue,nMinValue,nMaxValue,pDvmValue))
            {
                //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
//                CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Values.GetString(),pDvmValue->m_strValue.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strValidNumber.GetString());
                pDvmValue->m_strValue = strValidNumber;
                return TRUE;
            }
            return FALSE;
        }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN == pDvmValue->m_strDataType)
    {
        //布尔类型比较适用于CompareNoCase
        if(pDvmValue->m_strValue.CompareNoCase(strValue) == 0 || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE_NUMERIC == pDvmValue->m_strValue
                || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE_NUMERIC == pDvmValue->m_strValue)
        {
            return FALSE;
        }
        else
        {
            if(strValue.CompareNoCase(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE) == 0 || strValue.CompareNoCase(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE) == 0
                    || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE_NUMERIC == strValue || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE_NUMERIC == strValue)
            {
                //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
//                CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Values.GetString(),pDvmValue->m_strValue.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strValue.GetString());
                pDvmValue->m_strValue = strValue;
                return TRUE;
            }
            //"参数修改:(错误参数)-,-Path =【名称路径-%s(ID路径-%s)】无法设置导入的值:无效的二进制值！"
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

BOOL CSettingFilesToXrioTool::SettingSETFileToXrio(CBufferBase& oBuffer, CDvmLogicDevice *pCustomLogicDevice,long& nModifyIndex, CExBaseList& oDvmGridList)
{
    CHAR *pszLine = oBuffer.GetString();
    while(pszLine)
    {
        CString strTemp;
        strTemp.Format(_T("%s"),pszLine);
        int lastIndex = strTemp.ReverseFind(_T(';'));

        if (lastIndex != -1)
        {
            strTemp = strTemp.Left(lastIndex);
        }

        strTemp.Trim();

        if(GetCurrStrType(strTemp) == COMBOX_TYPE)//COMBOBOX类型
        {
            ParseComboBoxType(strTemp,pCustomLogicDevice,nModifyIndex,oDvmGridList);
        }
        else if(GetCurrStrType(strTemp) == EDIT_TYPE) //EDIT类型
        {
            ParseEditType(strTemp,pCustomLogicDevice,nModifyIndex,oDvmGridList);
        }

        pszLine = oBuffer.NextString();
    }
    return TRUE;
}

BOOL CSettingFilesToXrioTool::SettingTXTFileToXrio(CBufferBase& oBuffer, CDvmLogicDevice *pCustomLogicDevice ,long& nModifyIndex, CExBaseList& oDvmGridList)
{
    //SET_1.TXT
    //[1] 下一行为有效位置开始位置

    //    [INFO]
    //    RELAYTYPE=0351
    //    FID=SEL-351-RXXX-V0-Z000000-DXXXXXXXX
    //    BFID=SELBOOT-311-R101
    //    PARTNO=035101H45542XX
    //    [1]
    //    RID,"SEL-351"
    //    TID,"PONOVO LAB"
    //    CTR,"1"
    //    CTRN,"1"

    CString strTXTFileReadFlag;
    CString strTemp;
    CString strValue;
    CString strNamePath;
    CStringArray strLineArray;
    CExBaseObject *pObj = NULL;
    CHAR *pszLine = NULL;//有效位置指针

    BOOL GetReadStartFlag = FALSE;

    CString strOpenFileName = ParseFileName(m_strFilePath);
    int Pos = strOpenFileName.Find(_T('_'));
    if(Pos != -1)
    {
        strTXTFileReadFlag = _T("[") + strOpenFileName.Mid(Pos+1) + _T("]");
    }
    //查找有效数据开始位置
    CHAR *pszLineReadBefore = oBuffer.GetString();
    while(pszLineReadBefore)
    {
        strTemp.Format(_T("%s"),pszLineReadBefore);
        if(strTemp.CompareNoCase(strTXTFileReadFlag) == 0)
        {
            GetReadStartFlag = TRUE;
            pszLine = oBuffer.NextString();
            break;
        }

        pszLineReadBefore = oBuffer.NextString();
    }

    if(!GetReadStartFlag)
    {
        return FALSE;
    }

    //有效数据读取开始
    //    CHAR *pszLine = oBuffer.GetString();
    while(pszLine)
    {
        strTemp.Format(_T("%s"),pszLine);
        SplitCStringToArray(strTemp,strLineArray,',');

        if(strLineArray.GetCount() != 2)
        {
            pszLine = oBuffer.NextString();
            continue;
        }

        strNamePath = strLineArray.GetAt(0);
        strNamePath.Trim();
        GetUpdateValue(GetTrimValue(strLineArray.GetAt(1)),strValue);

        // strNamePath是ForeignId的值，需要得到父节点

        m_oDvmUpdateListRef.RemoveAll();
        if(SettingFileFindChildByName(pCustomLogicDevice,strNamePath,m_oDvmUpdateListRef))
        {
            pszLine = oBuffer.NextString();
            continue;
        }

        POS pos = m_oDvmUpdateListRef.GetHeadPosition();
        while(pos)
        {
            pObj = m_oDvmUpdateListRef.GetNext(pos);
            ASSERT(DVMCLASSID_CDVMVALUE == pObj->GetClassID());
        pObj = (CExBaseObject*)pObj->GetParent();
            ASSERT(NULL != pObj);
        if(UpdateDvmRefByData_Value(pObj,strValue))
        {
            ++nModifyIndex;
                oDvmGridList.AddTail(pObj);
            }
        }

        pszLine = oBuffer.NextString();
    }

    return TRUE;
}

BOOL CSettingFilesToXrioTool::SettingCSVFileToXrio(CBufferBase& oBuffer, CDvmLogicDevice *pCustomLogicDevice ,long& nModifyIndex, CExBaseList& oDvmGridList)
{
    //当前的CSV文件解析只涉及一种类型：
    //    FAULT REPORT
    //    , Fault Report 1 Source, 60kV (SRC 1)
    //    , Fault Report 1 Trigger, TRIP GRL B01 On (VO6)
    //    , Fault Report 1 Positive Seq (Z1) Mag, 7.63 ohms
    //    , Fault Report 1 Positive Seq (Z1) Angle, 67 deg
    //    , Fault Report 1 Zero Seq (Z0) Mag, 17.96 ohms
    //    , Fault Report 1 Zero Seq (Z0) Angle, 67 deg
    //    , Fault Report 1 Line Length Units, km
    //    , Fault Report 1 Line Length, 54.0
    //    , Fault Report 1 REM1-TAP Z1 Mag, 3.00 ohms
    CString strTemp;
    CString strValue;
    CString strNamePath;
    CStringArray strLineArray;
    //CStringArray strNamePathArray;
    CExBaseObject *pObj = NULL;
    CString strBlockName;
    CHAR *pszLine = NULL;
    CHAR *pDest = NULL;
    BOOL GetReadStartFlag = FALSE;

    //查找有效数据开始位置：
    CHAR *pszLineReadBefore = oBuffer.GetString();
    while(pszLineReadBefore)
    {
        if(*pszLineReadBefore == ',')
        {
            pDest = pszLineReadBefore;
            ASSERT(--pszLineReadBefore);
            pszLine = --pszLineReadBefore;
            GetReadStartFlag = TRUE;
            break;
        }
        else
        {
            pszLineReadBefore = oBuffer.NextString();
        }
    }

    if(!GetReadStartFlag)
    {
        return FALSE;
    }

    //有效数据开始
//    CHAR *pszLine = oBuffer.GetString();
    while(pDest)
    {
        strBlockName.Format(_T("%s"),pszLine);
        if(*pDest == ',')
        {
            strTemp.Format(_T("%s"),pDest);
            int Pos = strTemp.Find(_T(','));

            if (Pos != -1)
            {
                strTemp = strTemp.Mid(Pos+1);
            }
            strTemp.Trim();
            //分割每一行分别得到ForeignId路径和要更新的值。
            // ENCRYPTED PASSWORD: Command Password, 0
            SplitCStringToArray(strTemp,strLineArray,',');

            if(strLineArray.GetCount() != 2)
            {
                pDest = oBuffer.NextString();
                continue;
            }

            strValue = strLineArray.GetAt(1);
            strValue.Trim();

            strNamePath = GetTrimValue(strBlockName) + _T(" ") + GetTrimValue(strLineArray.GetAt(0));
            strNamePath.Trim();

            m_oDvmUpdateListRef.RemoveAll();
            if(SettingFileFindChildByName(pCustomLogicDevice,strNamePath,m_oDvmUpdateListRef))
            {
                pDest = oBuffer.NextString();
                continue;
            }

            POS pos = m_oDvmUpdateListRef.GetHeadPosition();
            while(pos)
            {
                pObj = m_oDvmUpdateListRef.GetNext(pos);
                ASSERT(DVMCLASSID_CDVMVALUE == pObj->GetClassID());
            pObj = (CExBaseObject*)pObj->GetParent();
                ASSERT(NULL != pObj);
            if(UpdateDvmRefByData_Value(pObj,strValue))
            {
                ++nModifyIndex;
                    oDvmGridList.AddTail(pObj);
                }
            }
        }
        else
        {
            pszLine = pDest;
        }
        pDest = oBuffer.NextString();
    }

    return TRUE;
}

CString CSettingFilesToXrioTool::GetNumberPart(const CString &input)
{
    CString trimmedInput = input;
    trimmedInput.Trim(); // 去除前后空白
    CString numberPart;

    BOOL foundDigit = FALSE;
    BOOL foundDecimal = FALSE;
    BOOL foundExponent = FALSE;

    for (int i = 0; i < trimmedInput.GetLength(); i++)
    {
        TCHAR ch = trimmedInput[i];

        // 跳过空白字符
        if (isspace(ch))
        {
            continue; // 如果是空白字符，跳过
        }

        // 检查是否为数字
        if (isdigit(ch))
        {
            numberPart += ch; // 使用 += 操作符添加字符
            foundDigit = true;
        }
        // 检查小数点
        else if (ch == '.' && foundDigit && !foundDecimal)
        {
            numberPart += ch; // 使用 += 操作符添加小数点
            foundDecimal = true;
        }
        // 检查符号
        else if ((ch == '+' || ch == '-') && (numberPart.IsEmpty() || (foundDigit && !foundExponent)))
        {
            numberPart += ch; // 使用 += 操作符添加符号
        }
        // 检查科学计数法符号
        else if ((ch == 'e' || ch == 'E') && foundDigit && !foundExponent)
        {
            numberPart += ch; // 使用 += 操作符添加 e 或 E
            foundExponent = true;
        }
        // 检查科学计数法后面的符号
        else if ((ch == '+' || ch == '-') && foundExponent)
        {
            int lastIndex = numberPart.GetLength() - 1;
            if (lastIndex >= 0 && (isdigit(numberPart[lastIndex]) || numberPart[lastIndex] == 'e' || numberPart[lastIndex] == 'E'))
            {
                numberPart += ch; // 使用 += 操作符添加科学计数法符号
            }
        }
    }

    // 检查是否有效的科学计数法
    if (foundExponent && numberPart.FindOneOf(L"0123456789") == -1)
    {
        numberPart.Empty(); // 如果没有找到数字部分，清空
    }

    return numberPart; // 返回提取的数字部分
}

void CSettingFilesToXrioTool::GetUpdateValue(const CString &strValue , CString& UpdateValue)
{
    // 提取右边 CString 中引号之间的内容
    int startPos = strValue.Find(_T('\"'));
    int endPos = strValue.Find(_T('\"'), startPos + 1);

    if (startPos != -1 && endPos != -1)
    {
        UpdateValue = strValue.Mid(startPos + 1, endPos - startPos - 1);
    }
    else
    {
        UpdateValue.Empty(); // 如果没有找到引号，清空 UpdateValue
    }
}

BOOL CSettingFilesToXrioTool::GetCompareResult_DataType_Double(const double &dOldValue, const double &dNewValue, const double &dMinValue, const double &dMaxValue, CExBaseObject *pObj)
{
    if(DOUBLE_EQUAL == DoubleFuzzyCompare(dOldValue,dNewValue))
    {
        return FALSE;
    }

    CString strNamePath = pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
    CString strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pObj,FALSE);

    if(DOUBLE_LESS == DoubleFuzzyCompare(dNewValue,dMinValue))
    {
        //"参数修改:(错误参数)-,-Path =【名称路径-%s(ID路径-%s)】无法设置导入的值:值必须 >= "
        return FALSE;
    }

    if(DOUBLE_GREATER == DoubleFuzzyCompare(dNewValue,dMaxValue))
    {
        //"参数修改:(错误参数)-,-Path =【名称路径-%s(ID路径-%s)】无法设置导入的值:值必须 <= "
        return FALSE;
    }

    return TRUE;
}

BOOL CSettingFilesToXrioTool::GetCompareResult_DataType_Int(const int &nOldValue, const int &nNewValue, const int &nMinValue, const int &nMaxValue, CExBaseObject *pObj)
{
    if(nOldValue == nNewValue)
    {
        return FALSE;
    }

    CString strNamePath = pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
    CString strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pObj,FALSE);

    if(nNewValue < nMinValue)
    {
        //"参数修改:(错误参数)-,-Path =【名称路径-%s(ID路径-%s)】无法设置导入的值:值必须 >= "
        return FALSE;
    }

    if(nNewValue > nMaxValue)
    {
        //"参数修改:(错误参数)-,-Path =【名称路径-%s(ID路径-%s)】无法设置导入的值:值必须 <= "
        return FALSE;
    }

    return TRUE;
}

BOOL CSettingFilesToXrioTool::GetCompareResult_DataType_Enumeration(CExBaseList *pList, const CString &strValue)
{
    CString strNamePath = pList->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
    CString strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pList,FALSE);
    CDvmValue *pDvmValue = NULL;
    POS pos = pList->GetHeadPosition();
    while(pos)
    {
        pDvmValue = (CDvmValue*)pList->GetNext(pos);
        if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION != pDvmValue->m_strDataType)
        {
            continue;
        }
        if(pDvmValue->m_strValue == strValue)
        {
            //枚举类型定值文件提供的strValue为其枚举值的Name(Value，两者相等，使用哪一个都可以)值，但是要更新的父节点的值是枚举值的ID最后一个$符后的值。
            CString strTemp = GetStringAfterLastDollar(pDvmValue->m_strID);
            if(DVMCLASSID_CDVMVALUE == pList->GetClassID())
            {
                CDvmData *pDvmData = (CDvmData*)pList;
                if(pDvmData->m_strValue == strTemp)
                {
                    return FALSE;
                }
                //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
                pDvmData->m_strValue = strTemp;
                return TRUE;
            }
            else if(DVMCLASSID_CDVMDATA == pList->GetClassID())
            {
                pDvmValue = (CDvmValue*)pList;
                if(pDvmValue->m_strValue == strTemp)
                {
                    return FALSE;
                }
                //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
                pDvmValue->m_strValue = strTemp;
                return TRUE;
            }
        }
    }

    //"参数修改:(错误参数)-,-Path =【名称路径-%s(ID路径-%s)】无法设置导入的值:无效的枚举值！"
    return FALSE;
}

CSettingFilesToXrioTool::SetFileLineType CSettingFilesToXrioTool::GetCurrStrType(const CString &CurrStr)
{
    int pos = CurrStr.Find(_T("Num"));
    return (pos != -1) ? COMBOX_TYPE:EDIT_TYPE;
}

BOOL CSettingFilesToXrioTool::ParseCurrLineType(const SetFileLineType& strLineType,const CString& strLine, CDvmLogicDevice *pCustomLogicDevice, CSettingFilesToXrioTool::SETTING_SET_FILE_FUNC pFunc, long& nModifyIndex, CExBaseList& oDvmGridList)
{
    CExBaseObject *pObj = NULL;
    CString CommaSeparatedStr;//被逗号分割后的单个CString
    CStringArray StrSeparatedByCommas;//逗号分隔
    CStringArray StrSeparatedByEqual;//等号分割
    SplitCStringToArray(strLine,StrSeparatedByCommas,_T(','));

    CommaSeparatedStr = StrSeparatedByCommas.GetAt(0);
    CommaSeparatedStr.Trim();
    SplitCStringToArray(CommaSeparatedStr,StrSeparatedByEqual,_T('='));

    if(StrSeparatedByEqual.GetCount() != 2)
    {
        return FALSE;
    }

    if(GetTrimValue(StrSeparatedByEqual.GetAt(0))!= _T("N"))
    {
        return FALSE;
    }

    m_oDvmUpdateListRef.RemoveAll();
    if(SettingFileFindChildByName(pCustomLogicDevice,GetTrimValue(StrSeparatedByEqual.GetAt(1)),m_oDvmUpdateListRef))
    {
        return FALSE;
    }

    if(COMBOX_TYPE == strLineType)
    {
        BOOL GetValueIndex = FALSE;
        BOOL GetUpdateValue = FALSE;
        CString strValueIndex;
        CString strUpdateValue;
        for(int i = 1; i < StrSeparatedByCommas.GetCount(); ++i)
        {
            if(GetUpdateValue)
            {
                break;
            }

            CommaSeparatedStr = StrSeparatedByCommas.GetAt(i);
            CommaSeparatedStr.Trim();
            //对逗号分割后的单个CString再次进行等号分割
            SplitCStringToArray(CommaSeparatedStr,StrSeparatedByEqual,_T('='));
            //pFunc(StrSeparatedByEqual,pDvmData);
            if(StrSeparatedByEqual.GetCount() != 2)
            {
                continue;
            }

            if(!GetValueIndex && (GetTrimValue(StrSeparatedByEqual.GetAt(0)) == _T("V")))
            {
                int nIndex = CString_To_long(GetTrimValue(StrSeparatedByEqual.GetAt(1)));
                nIndex += 1;
                strValueIndex.Format(_T("S%d"),nIndex);
                GetValueIndex = TRUE;
            }

            if(GetValueIndex && (GetTrimValue(StrSeparatedByEqual.GetAt(0)) == strValueIndex))
            {
                strUpdateValue = StrSeparatedByEqual.GetAt(1);
                strUpdateValue.Trim();
                GetUpdateValue = TRUE;
            }
        }

        POS pos = m_oDvmUpdateListRef.GetHeadPosition();
        while(pos)
        {
            pObj = m_oDvmUpdateListRef.GetNext(pos);
            if((this->*pFunc)(pObj,strUpdateValue))
            {
                ++nModifyIndex;
                oDvmGridList.AddTail(pObj);
            }
        }
        return TRUE;
    }
    else if(EDIT_TYPE == strLineType)
    {
        BOOL GetUpdateValue = FALSE;
        CString strUpdateValue;
        for(int i = 1; i < StrSeparatedByCommas.GetCount(); ++i)
        {
            if(GetUpdateValue)
            {
                break;
            }

            CommaSeparatedStr = StrSeparatedByCommas.GetAt(i);
            CommaSeparatedStr.Trim();
            //对逗号分割后的单个CString再次进行等号分割
            SplitCStringToArray(CommaSeparatedStr,StrSeparatedByEqual,_T('='));
            //pFunc(StrSeparatedByEqual,pDvmData);
            if(StrSeparatedByEqual.GetCount() != 2)
            {
                continue;
            }

            if(!GetUpdateValue && (GetTrimValue(StrSeparatedByEqual.GetAt(0)) == _T("V")))
            {
                strUpdateValue = GetTrimValue(StrSeparatedByEqual.GetAt(1));
                GetUpdateValue = TRUE;
            }
        }

        POS pos = m_oDvmUpdateListRef.GetHeadPosition();
        while(pos)
        {
            pObj = m_oDvmUpdateListRef.GetNext(pos);
            if((this->*pFunc)(pObj,strUpdateValue))
            {
                ++nModifyIndex;
                oDvmGridList.AddTail(pObj);
            }
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CSettingFilesToXrioTool::ParseComboBoxType(const CString &strComboBox, CDvmLogicDevice *pCustomLogicDevice, long &nModifyIndex, CExBaseList &oDvmGridList)
{
    return ParseCurrLineType(COMBOX_TYPE,strComboBox,pCustomLogicDevice,&CSettingFilesToXrioTool::GetComboBoxTypeData_Value,nModifyIndex,oDvmGridList);
}

BOOL CSettingFilesToXrioTool::ParseEditType(const CString &strEdit, CDvmLogicDevice *pCustomLogicDevice, long &nModifyIndex, CExBaseList &oDvmGridList)
{
    return ParseCurrLineType(EDIT_TYPE,strEdit,pCustomLogicDevice,&CSettingFilesToXrioTool::GetComboBoxTypeData_Value,nModifyIndex,oDvmGridList);
}

BOOL CSettingFilesToXrioTool::GetComboBoxTypeData_Value(CExBaseObject *pObj ,const CString& strUpdateValue)
{
    return UpdateDvmRefByData_Value(pObj,strUpdateValue);
}

BOOL CSettingFilesToXrioTool::GetEditTypeData_Value(CExBaseObject *pObj ,const CString& strUpdateValue)
{
    return UpdateDvmRefByData_Value(pObj,strUpdateValue);
}

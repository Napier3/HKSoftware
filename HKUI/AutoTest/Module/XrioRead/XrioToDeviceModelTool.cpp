#include "XrioToDeviceModelTool.h"

CXrioToDeviceModelTool::CXrioToDeviceModelTool()
{

}

CXrioToDeviceModelTool::~CXrioToDeviceModelTool()
{

}


BOOL CXrioToDeviceModelTool::XrioToDeviceModel(CXrio* pXrio, CDvmDevice* pDvmDevice)
{
    pDvmDevice->DeleteAll();
    CXrioCustom *pXrioCustom = pXrio->GetXrioCustom();
    CDvmLogicDevice *pSrcLogicDevice = NULL;
    CExBaseObject *pSubObj = NULL;

    //Custom解析
    if (pXrioCustom != NULL)
    {
        POS pos = pXrioCustom->GetHeadPosition();
        CXrioCustomBlock *pCXrioCustomBlock = NULL;
        pSrcLogicDevice = pDvmDevice->AddNewLogicDevice();
        pSrcLogicDevice->m_strName = GetTrimValue(pXrioCustom->m_strName);
        pSrcLogicDevice->m_strID = XRIO_DEVICE_MODEL_ID_CUSTOM;

        while (pos)
        {
            pSubObj = pXrio->GetNext(pos);

            if (pSubObj->GetClassID() != XRIOCLASSID_CUSTOMBLOCK)
            {
                continue;
            }
            if (((CXrioCustomBlock*)pSubObj)->m_strEnabled == _T("false"))
            {
                continue;
            }

            pCXrioCustomBlock = (CXrioCustomBlock*)pSubObj;
            CDvmDataset *pCDvmDataset = pSrcLogicDevice->AddNewDataset();

            pCDvmDataset->SetAttr(_T("name"), GetTrimValue(pCXrioCustomBlock->m_strName));
            pCDvmDataset->SetAttr(_T("id"), GetTrimValue(pCXrioCustomBlock->m_strID));
            ParseXrioCustomBlock(pCXrioCustomBlock, pCDvmDataset);
        }
    }
//    else    //参照OMR，如果XRIO文件中不存在COUSTOM节点和RIO节点就手动补充一个空的。
//    {
//        pSrcLogicDevice = pDvmDevice->AddNewLogicDevice();
//        pSrcLogicDevice->m_strName = _T("自定义");
//        pSrcLogicDevice->m_strID = XRIO_DEVICE_MODEL_ID_CUSTOM;
//    }

    //RIO解析
    CXrioRio *pXrioRio = pXrio->GetXrioRio();

    if (pXrioRio == NULL)
    {
//        pSrcLogicDevice = pDvmDevice->AddNewLogicDevice();
//        pSrcLogicDevice->m_strName = XRIO_DEVICE_MODEL_ID_RIO;
//        pSrcLogicDevice->m_strID = XRIO_DEVICE_MODEL_ID_RIO;
        return TRUE;
    }

    pSrcLogicDevice = pDvmDevice->AddNewLogicDevice();
    pSrcLogicDevice->m_strName = GetTrimValue(pXrioRio->m_strName);
    pSrcLogicDevice->m_strID = XRIO_DEVICE_MODEL_ID_RIO;
	
    //特性曲线节点
    POS RioPos = pXrioRio->GetHeadPosition();
    while (RioPos)
    {
        pSubObj = pXrioRio->GetNext(RioPos);
        if(ParseXrioRioDevice(pSrcLogicDevice, pSubObj))
        {
            continue;
        }
        else if(AddCharacteristicNode(pSrcLogicDevice, pSubObj))
        {
            continue;
        }
        else
        {
            ParseXrioRioCBConfiguration(pSrcLogicDevice, pSubObj);
        }
    }

    return TRUE;
}

BOOL CXrioToDeviceModelTool::IsXrioDataset_Device(CExBaseObject *pCurrObj)
{
	if (pCurrObj == NULL)
	{
		return FALSE;
	}

	if (pCurrObj->GetClassID() != DVMCLASSID_CDVMDATASET)
	{
		return FALSE;
	}

	if (pCurrObj->m_strID != XRIO_DEVICE_MODEL_ID_DEVICE)
	{
		return FALSE;
	}

	CExBaseObject *pCurrParent = (CExBaseObject*)pCurrObj->GetParent();

	if (pCurrParent == NULL)
	{
		return FALSE;
	}

	if (pCurrParent->m_strID != XRIO_DEVICE_MODEL_ID_RIO)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXrioToDeviceModelTool::IsXrioDataset_CBCONFIGURATION(CExBaseObject *pCurrObj)
{
	if (pCurrObj == NULL)
	{
		return FALSE;
	}

	if (pCurrObj->GetClassID() != DVMCLASSID_CDVMDATASET)
	{
		return FALSE;
	}

    CDvmDataset* pCurrDataset = (CDvmDataset*)pCurrObj;
    //ABB RET316 V6.6a DEU TU2.22 V1.100.xrio文件CB配置存在多个的情况，现在修改判别方式，改为DataType方式
    if (/*pCurrObj->m_strID != XRIO_DEVICE_MODEL_ID_CBCONFIGURATION*/pCurrDataset->m_strDataType != XRIO_DEVICE_MODEL_DATA_TYPE_CBCONFIGURATION)
	{
		return FALSE;
	}

	CExBaseObject *pCurrParent = (CExBaseObject*)pCurrObj->GetParent();

	if (pCurrParent == NULL)
	{
		return FALSE;
	}

	if (pCurrParent->m_strID != XRIO_DEVICE_MODEL_ID_RIO)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXrioToDeviceModelTool::IsXrioDataset_Characteristic(CExBaseObject *pCurrObj)
{
	if (pCurrObj == NULL)
	{
		return FALSE;
	}

	if (pCurrObj->GetClassID() != DVMCLASSID_CDVMDATASET)
    {
		return FALSE;
	}

    CDvmDataset* pCurrDataset = (CDvmDataset*)pCurrObj;
    if (pCurrDataset->m_strDataType != XRIO_DEVICE_MODEL_DATA_TYPE_DISTANCE && pCurrDataset->m_strDataType != XRIO_DEVICE_MODEL_DATA_TYPE_DIFFERENTIAL && pCurrDataset->m_strDataType != XRIO_DEVICE_MODEL_DATA_TYPE_OVERCURRENT)
	{
		return FALSE;
	}

	CExBaseObject *pCurrParent = (CExBaseObject*)pCurrObj->GetParent();

	if (pCurrParent == NULL)
	{
		return FALSE;
	}

	if (pCurrParent->m_strID != XRIO_DEVICE_MODEL_ID_RIO)
	{
		return FALSE;
    }

    return TRUE;
}

void CXrioToDeviceModelTool::InitDataType(CString &strDataType, CExBaseObject *pObj)
{
    if(XRIO_CUSTOM_PARAMETER_DATATYPE_STRING != strDataType && XRIO_CUSTOM_PARAMETER_DATATYPE_REAL != strDataType && XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION != strDataType
            && XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER != strDataType && XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN != strDataType)
    {
        //不属于以上五种数据类型默认赋值为字符串类型
        CString strNamePath = pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
        CString strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pObj,FALSE);
        //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】参数含无效数据类型！数据类型改为字符串型！"
        CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
        strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_LogInfo_InvalidParamDataType.GetString());

        strDataType = XRIO_CUSTOM_PARAMETER_DATATYPE_STRING;
    }
}

void CXrioToDeviceModelTool::InitValueByDataType(CString &strValue, const CString &strDataType, CExBaseList *pList)
{
    BOOL bOk;
    CString strNamePath,strIDPath;
    if(XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == strDataType)
    {
        double dValue;
        bOk = CString_To_double(strValue,dValue);
#ifdef _PSX_QT_LINUX_
    if(!bOk || (bOk &&std:: isnan(dValue)))
#else
        if(!bOk || (bOk && _isnan(dValue)))
#endif
        {
            strNamePath = pList->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pList,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】无效的双精度值！"
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_InvalidDoublePrecisionValue.GetString());

            strValue = XRIO_DEVICE_MODEL_DEFAULT_NUMERIC_VALUE;
        }
        //获取小数点位数节点，对于double类型，在初始化的时候就将值转换为相应的小数点位数对应的浮点数。
        dValue = CString_To_double(strValue);
        CDvmValue *pDvmValue = (CDvmValue*)GetAttrObj(pList,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);
        if(pDvmValue != NULL)
        {
            CString strTmp,strFormat;
            long nPrecision = CString_To_long(pDvmValue->m_strValue);
            strFormat.Format(_T("%%.%ldlf"), nPrecision);
            strTmp.Format(strFormat.GetString(), dValue);
            strValue = strTmp;
        }
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == strDataType)
    {
//        int nValue;
//        bool bOk;
//        nValue = strValue.toInt(&bOk);
//        if(!bOk)
//        {
//            strNamePath = pList->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
//            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pList,FALSE);
//            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】无效的整形值！"
//            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_InvalidIntValue.GetString());

//            strValue = XRIO_DEVICE_MODEL_DEFAULT_NUMERIC_VALUE;
//        }

        if(!IsStringInteger(strValue) || strValue.isEmpty())
        {
            strNamePath = pList->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pList,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】无效的整形值！"
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_InvalidIntValue.GetString());

            strValue = XRIO_DEVICE_MODEL_DEFAULT_NUMERIC_VALUE;
            return;
        }

        //此处使用CString_To_long 该函数在为字符串为浮点数数返回整形部分，在整形部分超出INT_MAX或者INT_MIN的时候会返回INT_MAX或者INT_MIN。
        //CString_To_long 一定能保证strValue处于INT_MAX和INT_MIN之间，如果值为空，返回0。
        long nValue;
        nValue = CString_To_long(strValue);
        strValue.Format(_T("%ld"),nValue);
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == strDataType)
    {
        CDvmValue *pDvmValue = NULL;
        CString strTmp;
        CString strFirstValue;
        int nIndex = 0;
        for(POS startPos = pList->GetHeadPosition();startPos != NULL;)
        {
            pDvmValue = (CDvmValue*)pList->GetNext(startPos);
            if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDvmValue->m_strDataType)
            {
                ++nIndex;
                if(1 == nIndex)
                {
                    strFirstValue = pDvmValue->m_strValue;//此处pDvmValue->m_strName也可以
                }
                strTmp = GetStringAfterLastDollar(pDvmValue->m_strID);
                if(strTmp == strValue)
                {
                    return;
                }
            }
        }
        strNamePath = pList->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
        strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pList,FALSE);
        //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】无效的枚举值！"
        CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
        strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_InvalidEnumValue.GetString());

        strValue = strFirstValue;
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN == strDataType)
    {
        if(0 != strValue.CompareNoCase(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE) && 0 != strValue.CompareNoCase(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE)
                && XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE_NUMERIC != strValue && XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE_NUMERIC != strValue)
        {
            strNamePath = pList->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pList,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】无效的二进制值！"
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_InvalidBinaryValue.GetString());

            strValue = XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE;
        }
    }
}

void CXrioToDeviceModelTool::InitUnitByDataType(CString &strUnitValue, const CString &strDataType)
{
    if(XRIO_CUSTOM_PARAMETER_DATATYPE_STRING == strDataType || XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == strDataType
            || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN == strDataType || XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == strDataType)
    {
        strUnitValue = strUnitValue.IsEmpty()?strUnitValue:XRIO_DEVICE_MODEL_DEFAULTVALUE;
    }
}

void CXrioToDeviceModelTool::InitUnitDecPlacesByDataType(CString &strUnitDecPlacesValue, const CString &strDataType)
{
    if(XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == strDataType)
    {
        strUnitDecPlacesValue = strUnitDecPlacesValue.IsEmpty()?XRIO_DEVICE_MODEL_UNIT_DEFAULT_DECIMALPLACES:strUnitDecPlacesValue;
        long nPrecision = CString_To_long(strUnitDecPlacesValue);
        if(nPrecision < 0)
        {
            strUnitDecPlacesValue = XRIO_DEVICE_MODEL_UNIT_DEFAULT_DECIMALPLACES;
        }
    }
}

void CXrioToDeviceModelTool::InitMinByDataType(CString &strMinValue, const CString &strDataType, CExBaseObject *pObj)
{
    BOOL bOk;
    CString strNamePath,strIDPath;
    if(XRIO_CUSTOM_PARAMETER_DATATYPE_STRING == strDataType || XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == strDataType || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN == strDataType)
    {
        strMinValue = strMinValue.IsEmpty()?strMinValue:XRIO_DEVICE_MODEL_DEFAULTVALUE;
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == strDataType)
    {
        double dMinValue;
        bOk = CString_To_double(strMinValue,dMinValue);
#ifdef _PSX_QT_LINUX_
    if(!bOk || (bOk &&std:: isnan(dMinValue)))
#else
        if(!bOk || (bOk && _isnan(dMinValue)))
#endif
        {
            if(!strMinValue.isEmpty())
            {
                strNamePath = pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
                strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pObj,FALSE);
                //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】无效的双精度值！"
                CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_InvalidDoublePrecisionValue.GetString());
            }

            strMinValue = XRIO_DEVICE_MODEL_NEGATIVE_INF_STRING;
        }
        //获取小数点位数节点，对于double类型，在初始化的时候就将值转换为相应的小数点位数对应的浮点数。
        dMinValue = CString_To_double(strMinValue);
        CDvmValue *pDvmValue = (CDvmValue*)GetAttrObj(pObj,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);
        if(pDvmValue != NULL)
        {
            CString strTmp,strFormat;
            long nPrecision = CString_To_long(pDvmValue->m_strValue);
            strFormat.Format(_T("%%.%ldlf"), nPrecision);
            strTmp.Format(strFormat.GetString(), dMinValue);
            strMinValue = strTmp;
        }
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == strDataType)
    {
//        bool bOk;
//        strMinValue.toInt(&bOk);
//        if(!bOk)
//        {
//            if(!strMinValue.isEmpty())
//            {
//                strNamePath = pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
//                strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pObj,FALSE);
//                //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】无效的整形值！"
//                CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_InvalidIntValue.GetString());
//            }

//            strMinValue = XRIO_DEVICE_MODEL_INT_MIN;
//        }

        if(!IsStringInteger(strMinValue))
            {
                strNamePath = pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
                strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pObj,FALSE);
                //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】无效的整形值！"
                CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_InvalidIntValue.GetString());

            strMinValue = XRIO_DEVICE_MODEL_INT_MIN;
            return;
            }

        if(strMinValue.isEmpty())
        {
            strMinValue = XRIO_DEVICE_MODEL_INT_MIN;
            return;
        }

        long nMinValue;
        nMinValue = CString_To_long(strMinValue);
        strMinValue.Format(_T("%ld"),nMinValue);
    }
}

void CXrioToDeviceModelTool::InitMaxByDataType(CString &strMaxValue, const CString &strDataType, CExBaseObject *pObj)
{
    BOOL bOk;
    CString strNamePath,strIDPath;
    if(XRIO_CUSTOM_PARAMETER_DATATYPE_STRING == strDataType || XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == strDataType || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN == strDataType)
    {
        strMaxValue = strMaxValue.IsEmpty()?strMaxValue:XRIO_DEVICE_MODEL_DEFAULTVALUE;
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == strDataType)
    {
        double dMaxValue;
        bOk = CString_To_double(strMaxValue,dMaxValue);
#ifdef _PSX_QT_LINUX_
    if(!bOk || (bOk &&std:: isnan(dMaxValue)))
#else
        if(!bOk || (bOk && _isnan(dMaxValue)))
#endif
        {
            if(!strMaxValue.isEmpty())
            {
                strNamePath = pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
                strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pObj,FALSE);
                //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】无效的双精度值！"
                CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_InvalidDoublePrecisionValue.GetString());
            }

            strMaxValue = XRIO_DEVICE_MODEL_POSITIVE_INF_STRING;
        }
        //获取小数点位数节点，对于double类型，在初始化的时候就将值转换为相应的小数点位数对应的浮点数。
        dMaxValue = CString_To_double(strMaxValue);
        CDvmValue *pDvmValue = (CDvmValue*)GetAttrObj(pObj,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);
        if(pDvmValue != NULL)
        {
            CString strTmp,strFormat;
            long nPrecision = CString_To_long(pDvmValue->m_strValue);
            strFormat.Format(_T("%%.%ldlf"), nPrecision);
            strTmp.Format(strFormat.GetString(), dMaxValue);
            strMaxValue = strTmp;
        }
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == strDataType)
    {
//        bool bOk;
//        strMaxValue.toInt(&bOk);
//        if(!bOk)
//        {
//            if(!strMaxValue.IsEmpty())
//            {
//                strNamePath = pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
//                strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pObj,FALSE);
//                //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】无效的整形值！"
//                CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
//                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_InvalidIntValue.GetString());
//            }

//            strMaxValue = XRIO_DEVICE_MODEL_INT_MAX;
//        }

        if(!IsStringInteger(strMaxValue))
            {
                strNamePath = pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
                strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pObj,FALSE);
                //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】无效的整形值！"
                CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_InvalidIntValue.GetString());

            strMaxValue = XRIO_DEVICE_MODEL_INT_MAX;
            return;
            }

        if(strMaxValue.isEmpty())
        {
            strMaxValue = XRIO_DEVICE_MODEL_INT_MAX;
            return;
        }

        long nMaxValue;
        nMaxValue = CString_To_long(strMaxValue);
        strMaxValue.Format(_T("%ld"),nMaxValue);
    }
}

void CXrioToDeviceModelTool::InitDvmDataAttrNormalize(CDvmData *pData)
{
    BOOL bOk;
    CString strNamePath,strIDPath;
    if(XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == pData->m_strDataType)
    {
        double dMinValue,dMaxValue,dValue;
        bOk = CString_To_double(pData->m_strMin,dMinValue);
        ASSERT(bOk);
        bOk = CString_To_double(pData->m_strMax,dMaxValue);
        ASSERT(bOk);
        bOk = CString_To_double(pData->m_strValue,dValue);
        ASSERT(bOk);
        //初始化后此处一定不会为Nan
        if(DOUBLE_GREATER == DoubleFuzzyCompare(dMinValue,dMaxValue))
        {
            strNamePath = pData->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pData,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】最小值大于最大值！"
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_LogInfo_MinGreaterThanMax.GetString());

            pData->m_strMin = pData->m_strMax;
            pData->m_strValue = pData->m_strMax;
            return;
        }

        if(DOUBLE_LESS == DoubleFuzzyCompare(dValue,dMinValue))
        {
            strNamePath = pData->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pData,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】值必须 >= "
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_ValueGreaterThanOREqual.GetString(),pData->m_strMin.GetString());

            pData->m_strValue = pData->m_strMin;
            return;
        }

        if(DOUBLE_GREATER == DoubleFuzzyCompare(dValue,dMaxValue))
        {
            strNamePath = pData->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pData,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】值必须 <= "
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_ValueLessThanOREqual.GetString(),pData->m_strMax.GetString());

            pData->m_strValue = pData->m_strMax;
            return;
        }
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == pData->m_strDataType)
    {
        int nMinValue,nMaxValue,nValue;
        nMinValue = CString_To_long(pData->m_strMin);
        nMaxValue = CString_To_long(pData->m_strMax);
        nValue = CString_To_long(pData->m_strValue);

        if(nMinValue > nMaxValue)
        {
            strNamePath = pData->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pData,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】最小值大于最大值！"
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_LogInfo_MinGreaterThanMax.GetString());

            pData->m_strMin = pData->m_strMax;
            pData->m_strValue = pData->m_strMax;
            return;
        }

        if(nValue < nMinValue)
        {
            strNamePath = pData->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pData,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】值必须 >= "
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_ValueGreaterThanOREqual.GetString(),pData->m_strMin.GetString());

            pData->m_strValue = pData->m_strMin;
            return;
        }

        if(nValue > nMaxValue)
        {
            strNamePath = pData->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pData,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】值必须 <= "
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_ValueLessThanOREqual.GetString(),pData->m_strMax.GetString());

            pData->m_strValue = pData->m_strMax;
            return;
        }
    }
}

void CXrioToDeviceModelTool::InitDvmValueAttrNormalize(CDvmValue *pValue)
{
    BOOL bOk;
    CString strNamePath,strIDPath;
    CDvmValue *pMinDvmValue = (CDvmValue*)GetAttrObj(pValue,XRIO_DEVICE_MODEL_ID_MinValue);
    ASSERT(pMinDvmValue);
    CDvmValue *pMaxDvmValue = (CDvmValue*)GetAttrObj(pValue,XRIO_DEVICE_MODEL_ID_MaxValue);
    ASSERT(pMaxDvmValue);
    if(XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == pValue->m_strDataType)
    {
        double dMinValue,dMaxValue,dValue;
        bOk = CString_To_double(pMinDvmValue->m_strValue,dMinValue);
        ASSERT(bOk);
        bOk = CString_To_double(pMaxDvmValue->m_strValue,dMaxValue);
        ASSERT(bOk);
        bOk = CString_To_double(pValue->m_strValue,dValue);
        ASSERT(bOk);
        //初始化后此处一定不会为Nan
        if(DOUBLE_GREATER == DoubleFuzzyCompare(dMinValue,dMaxValue))
        {
            strNamePath = pValue->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pValue,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】最小值大于最大值！"
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_LogInfo_MinGreaterThanMax.GetString());

            pMinDvmValue->m_strValue = pMaxDvmValue->m_strValue;
            pValue->m_strValue = pMaxDvmValue->m_strValue;
            return;
        }

        if(DOUBLE_LESS == DoubleFuzzyCompare(dValue,dMinValue))
        {
            strNamePath = pValue->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pValue,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】值必须 >= "
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_ValueGreaterThanOREqual.GetString(),pMinDvmValue->m_strValue.GetString());

            pValue->m_strValue = pMinDvmValue->m_strValue;
            return;
        }

        if(DOUBLE_GREATER == DoubleFuzzyCompare(dValue,dMaxValue))
        {
            strNamePath = pValue->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pValue,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】值必须 <= "
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_ValueLessThanOREqual.GetString(),pMaxDvmValue->m_strValue.GetString());

            pValue->m_strValue = pMaxDvmValue->m_strValue;
            return;
        }
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == pValue->m_strDataType)
    {
        int nMinValue,nMaxValue,nValue;
        nMinValue = CString_To_long(pMinDvmValue->m_strValue);
        nMaxValue = CString_To_long(pMaxDvmValue->m_strValue);
        nValue = CString_To_long(pValue->m_strValue);

        if(nMinValue > nMaxValue)
        {
            strNamePath = pValue->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pValue,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】最小值大于最大值！"
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_LogInfo_MinGreaterThanMax.GetString());

            pMinDvmValue->m_strValue = pMaxDvmValue->m_strValue;
            pValue->m_strValue = pMaxDvmValue->m_strValue;
            return;
        }

        if(nValue < nMinValue)
        {
            strNamePath = pValue->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pValue,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】值必须 >= "
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_ValueGreaterThanOREqual.GetString(),pMinDvmValue->m_strValue.GetString());

            pValue->m_strValue = pMinDvmValue->m_strValue;
            return;
        }

        if(nValue > nMaxValue)
        {
            strNamePath = pValue->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pValue,FALSE);
            //"参数数据类型:(警告)-,-Path =【名称路径-%s(ID路径-%s)】值必须 <= "
            CLogPrint::LogFormatString(XLOGLEVEL_WARNING,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s%s"),g_sLangTxt_Xrio_LogInfo_ParamDataType.GetString(),g_sLangTxt_warning.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_ValueLessThanOREqual.GetString(),pMaxDvmValue->m_strValue.GetString());

            pValue->m_strValue = pMaxDvmValue->m_strValue;
            return;
        }
    }
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelByXrioFile(CXrio *pXrio, CDvmDevice *pDvmDevice)
{
    CDvmDevice* pDvmDeviceTemp = new CDvmDevice;
    XrioToDeviceModel(pXrio,pDvmDeviceTemp);
    UpdateCustomLogicDeviceObject(pDvmDeviceTemp,pDvmDevice,XRIO_DEVICE_MODEL_ID_CUSTOM);
    UpdateRioLogicDeviceObject(pDvmDeviceTemp,pDvmDevice,XRIO_DEVICE_MODEL_ID_RIO);
    delete pDvmDeviceTemp;
    return TRUE;
}

BOOL CXrioToDeviceModelTool::AddCharacteristicNode(CDvmLogicDevice *pSrcLogicDevice, CExBaseObject* pObj)
{
    if(pObj->GetClassID() == XRIOCLASSID_DISTANCE || pObj->GetClassID() == XRIOCLASSID_DIFFERENTIAL || pObj->GetClassID() == XRIOCLASSID_OVERCURRENT)
    {
        CDvmDataset *pCDvmDataset = (CDvmDataset*)pSrcLogicDevice->CreateNewChild(DVMCLASSID_CDVMDATASET);
        pSrcLogicDevice->AddNewChild(pCDvmDataset);
        return InitCharacterNodeAttr(pCDvmDataset,pObj);
    }
    else
    {
        return FALSE;
    }
}

BOOL CXrioToDeviceModelTool::InitCharacterNodeAttr(CDvmDataset *pCDvmDataset, CExBaseObject *pObj)
{
    if(pObj->GetClassID() == XRIOCLASSID_DISTANCE)
    {
        return InitCharacterNodeAttrWithKey(pCDvmDataset,XRIO_DEVICE_MODEL_ID_DISTANCE,XRIO_DEVICE_MODEL_DATA_TYPE_DISTANCE,pObj);
    }
    else if(pObj->GetClassID() == XRIOCLASSID_DIFFERENTIAL)
    {
        return InitCharacterNodeAttrWithKey(pCDvmDataset,XRIO_DEVICE_MODEL_ID_DIFFERENTIAL,XRIO_DEVICE_MODEL_DATA_TYPE_DIFFERENTIAL,pObj);
    }
    else if(pObj->GetClassID() == XRIOCLASSID_OVERCURRENT)
    {
        return InitCharacterNodeAttrWithKey(pCDvmDataset,XRIO_DEVICE_MODEL_ID_OVERCURRENT,XRIO_DEVICE_MODEL_DATA_TYPE_OVERCURRENT,pObj);
    }
    return FALSE;
}

BOOL CXrioToDeviceModelTool::InitCharacterNodeAttrWithKey(CDvmDataset *pCDvmDataset, const CString &strIDValue, const CString &strDataType, CExBaseObject *pObj)
{
    InitAttr(pCDvmDataset->m_strName,strIDValue,GetTrimValue(pObj->m_strName));
    InitAttr(pCDvmDataset->m_strID,strIDValue,GetTrimValue(pObj->m_strID));
    pCDvmDataset->m_strDataType = strDataType;
    return TRUE;
}

BOOL CXrioToDeviceModelTool::InitAttr(CString &strDesAttrID, const CString &strDesAttrValue, const CString &strSrcAttrValue)
{
    strDesAttrID = strSrcAttrValue.isEmpty()?strDesAttrValue:strSrcAttrValue;
    return TRUE;
}

BOOL CXrioToDeviceModelTool::ParseXrioCustomBlock(CXrioCustomBlock *pXrioCustomBlock, CDvmDataset *pDataset)
{
    POS pos = pXrioCustomBlock->GetHeadPosition();
    CExBaseObject *pSubObj= NULL;
    CXrioCustomBlock *pChildCXrioCustomBlock = NULL;
    CXrioCustomParameter *pXrioCustomParameter = NULL;
    if(!pos)
    {
        if(pXrioCustomBlock->m_strEnabled!= _T("false"))
        {
            CDvmData *pCDvmData = (CDvmData*)pDataset->CreateNewChild(DVMCLASSID_CDVMDATA);
			pDataset->AddNewChild(pCDvmData);
            CString strTempIDPath;
            strTempIDPath = GetObjectIDPath(pDataset->m_strID,XRIO_DEVICE_MODEL_DEFAULTVALUE);
            pCDvmData->SetAttr(_T("name"),XRIO_DEVICE_MODEL_DEFAULTVALUE);
            pCDvmData->SetAttr(_T("id"),strTempIDPath);
            pCDvmData->SetAttr(_T("data-type"),XRIO_DEVICE_MODEL_DEFAULTVALUE);
            pCDvmData->SetAttr(_T("value"),XRIO_DEVICE_MODEL_DEFAULTVALUE);
            pCDvmData->SetAttr(_T("unit"),XRIO_DEVICE_MODEL_DEFAULTVALUE);
            pCDvmData->SetAttr(_T("min"),XRIO_DEVICE_MODEL_DEFAULTVALUE);
            pCDvmData->SetAttr(_T("max"),XRIO_DEVICE_MODEL_DEFAULTVALUE);
            //2024-9-27补充小数点位数节点
            strTempIDPath = GetObjectIDPath(pCDvmData->m_strID,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);
            pCDvmData->AddValue(XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);

            strTempIDPath = GetObjectIDPath(pCDvmData->m_strID,XRIO_DEVICE_MODEL_ID_ForeignId);
            pCDvmData->AddValue(XRIO_DEVICE_MODEL_ID_ForeignId,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_ID_ForeignId);

            strTempIDPath = GetObjectIDPath(pCDvmData->m_strID,XRIO_DEVICE_MODEL_ID_Description);
            pCDvmData->AddValue(XRIO_DEVICE_MODEL_ID_Description,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);

            strTempIDPath = GetObjectIDPath(pCDvmData->m_strID,XRIO_DEVICE_MODEL_ID_ValueFormula);
            pCDvmData->AddValue(XRIO_DEVICE_MODEL_ID_ValueFormula,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);

            //2024-9-29当为空节点的时候，之前是补充一个空的值，现在改为参考值，效果不变。
            strTempIDPath = GetObjectIDPath(pCDvmData->m_strID,XRIO_DEVICE_MODEL_ID_RefValue);
            pCDvmData->AddValue(XRIO_DEVICE_MODEL_ID_RefValue,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);

//            strTempIDPath = GetObjectIDPath(pCDvmData->m_strID,XRIO_DEVICE_MODEL_DEFAULTVALUE);
//            pCDvmData->AddValue(XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);
        }
        return TRUE;
    }

    while(pos)
    {
        pSubObj = pXrioCustomBlock->GetNext(pos);
        if(pSubObj->GetClassID() == XRIOCLASSID_CUSTOMBLOCK && ((CXrioCustomBlock*)pSubObj)->m_strEnabled != _T("false"))
        {
            pChildCXrioCustomBlock = (CXrioCustomBlock*)pSubObj;
            CDvmData *pCDvmData = (CDvmData*)pDataset->CreateNewChild(DVMCLASSID_CDVMDATA);
			pDataset->AddNewChild(pCDvmData);
            pCDvmData->SetAttr(_T("name"),GetTrimValue(pChildCXrioCustomBlock->m_strName));
            pCDvmData->SetAttr(_T("id"),GetTrimValue(pChildCXrioCustomBlock->m_strID));
            ParseXrioCustomParameter(pChildCXrioCustomBlock,pCDvmData);
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_CUSTOMPARAMETER && ((CXrioCustomParameter*)pSubObj)->m_strEnabled != _T("false"))
        {          
            pXrioCustomParameter = (CXrioCustomParameter*)pSubObj;
            CDvmData *pCDvmData = (CDvmData*)pDataset->CreateNewChild(DVMCLASSID_CDVMDATA);
            pDataset->AddNewChild(pCDvmData);

            pCDvmData->SetAttr(_T("name"),GetTrimValue(pXrioCustomParameter->m_strName));
            pCDvmData->SetAttr(_T("id"),GetTrimValue(pXrioCustomParameter->m_strID));
            pCDvmData->SetAttr(_T("value"),GetTrimValue(pXrioCustomParameter->m_strValue));

            pCDvmData->m_strDataType = GetTrimValue(pXrioCustomParameter->m_strDataType);
            InitDataType(pCDvmData->m_strDataType,pCDvmData);

            CString strUnitValue = GetTrimValue(pXrioCustomParameter->m_strUnit);
            InitUnitByDataType(strUnitValue,pCDvmData->m_strDataType);
            pCDvmData->SetAttr(_T("unit"),strUnitValue);

            //2024-9-27补充小数点位数节点
            AddParameterUnitDecimalPlaces(pXrioCustomParameter,pCDvmData);
            AddParameterForeignId(pXrioCustomParameter,pCDvmData);
            AddParameterDescription(pXrioCustomParameter,pCDvmData);
            AddParameterValueFormula(pXrioCustomParameter,pCDvmData);
            AddParameterValue(pXrioCustomParameter,pCDvmData);

            pCDvmData->m_strMin = GetTrimValue(pXrioCustomParameter->m_strMinValue);
            InitMinByDataType(pCDvmData->m_strMin,pCDvmData->m_strDataType,pCDvmData);

            pCDvmData->m_strMax = GetTrimValue(pXrioCustomParameter->m_strMaxValue);
            InitMaxByDataType(pCDvmData->m_strMax,pCDvmData->m_strDataType,pCDvmData);

            InitValueByDataType(pCDvmData->m_strValue,pCDvmData->m_strDataType,pCDvmData);
            InitDvmDataAttrNormalize(pCDvmData);
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::ParseXrioCustomParameter(CXrioCustomBlock *pChildXrioCustomBlock, CDvmData *pData)
{
    POS pos = pChildXrioCustomBlock->GetHeadPosition();
    CExBaseObject *pSubObj= NULL;
    CXrioCustomBlock *pChildCXrioCustomBlock = NULL;
    CXrioCustomParameter *pXrioCustomParameter = NULL;
    if(!pos)
    {
        if(pChildXrioCustomBlock->m_strEnabled!= _T("false"))
        {
            CString strTempIDPath;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_DEFAULTVALUE);
            CDvmValue *pCDvmValue =pData->AddValue(XRIO_DEVICE_MODEL_DEFAULTVALUE,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);
            SupplementEmptyNodeAttributes(pCDvmValue);
        }
        return TRUE;
    }
    while(pos)
    {
        pSubObj = pChildXrioCustomBlock->GetNext(pos);
        if(pSubObj->GetClassID() == XRIOCLASSID_CUSTOMBLOCK && ((CXrioCustomBlock*)pSubObj)->m_strEnabled != _T("false"))
        {
            pChildCXrioCustomBlock = (CXrioCustomBlock*)pSubObj;
            CString strTempIDPath;
            strTempIDPath = GetObjectIDPath(pData->m_strID,GetTrimValue(pChildCXrioCustomBlock->m_strID));
            CDvmValue *pCDvmValue = pData->AddValue(GetTrimValue(pChildCXrioCustomBlock->m_strName),strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);
            RecursionXrioCustomParameter(pChildCXrioCustomBlock,pCDvmValue);
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_CUSTOMPARAMETER && ((CXrioCustomParameter*)pSubObj)->m_strEnabled != _T("false"))
        {
            pXrioCustomParameter = (CXrioCustomParameter*)pSubObj;
            CString strTempIDPath;
            strTempIDPath = GetObjectIDPath(pData->m_strID,GetTrimValue(pXrioCustomParameter->m_strID));
            CDvmValue *pCDvmValue = pData->AddValue(GetTrimValue(pXrioCustomParameter->m_strName),strTempIDPath,GetTrimValue(pXrioCustomParameter->m_strDataType),GetTrimValue(pXrioCustomParameter->m_strValue));
            InitDataType(pCDvmValue->m_strDataType,pCDvmValue);

            //2024-9-27补充小数点位数节点
            AddParameterUnitDecimalPlaces(pXrioCustomParameter,pCDvmValue);
            AddParameterForeignId(pXrioCustomParameter,pCDvmValue);
            AddParameterDescription(pXrioCustomParameter,pCDvmValue);
            AddParameterUnit(pXrioCustomParameter,pCDvmValue);
            AddParameterMinValue(pXrioCustomParameter,pCDvmValue);
            AddParameterMaxValue(pXrioCustomParameter,pCDvmValue);
            AddParameterValueFormula(pXrioCustomParameter,pCDvmValue);
            AddParameterValue(pXrioCustomParameter,pCDvmValue);

            InitValueByDataType(pCDvmValue->m_strValue,pCDvmValue->m_strDataType,pCDvmValue);
            InitDvmValueAttrNormalize(pCDvmValue);
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::RecursionXrioCustomParameter(CXrioCustomBlock *pChildXrioCustomBlock, CDvmValue *pValue)
{
    POS pos = pChildXrioCustomBlock->GetHeadPosition();
    CExBaseObject *pSubObj= NULL;
    CXrioCustomBlock *pChildCXrioCustomBlock = NULL;
    CXrioCustomParameter *pXrioCustomParameter = NULL;
    if(!pos)
    {
        if(pChildXrioCustomBlock->m_strEnabled!= _T("false"))
        {
            CString strTempIDPath;
            strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_DEFAULTVALUE);
            CDvmValue *pCDvmValue =pValue->AddValue(XRIO_DEVICE_MODEL_DEFAULTVALUE,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);
            SupplementEmptyNodeAttributes(pCDvmValue);
        }
        return TRUE;
    }
    while(pos)
    {
        pSubObj = pChildXrioCustomBlock->GetNext(pos);
        if(pSubObj->GetClassID() == XRIOCLASSID_CUSTOMBLOCK && ((CXrioCustomBlock*)pSubObj)->m_strEnabled != _T("false"))
        {
            pChildCXrioCustomBlock = (CXrioCustomBlock*)pSubObj;
            CString strTempIDPath;
            strTempIDPath = GetObjectIDPath(pValue->m_strID,GetTrimValue(pChildCXrioCustomBlock->m_strID));
            CDvmValue *pCDvmValue = pValue->AddValue(GetTrimValue(pChildCXrioCustomBlock->m_strName),strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);
            RecursionXrioCustomParameter(pChildCXrioCustomBlock,pCDvmValue);
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_CUSTOMPARAMETER && ((CXrioCustomParameter*)pSubObj)->m_strEnabled != _T("false"))
        {
            pXrioCustomParameter = (CXrioCustomParameter*)pSubObj;
            CString strTempIDPath;
            strTempIDPath = GetObjectIDPath(pValue->m_strID,GetTrimValue(pXrioCustomParameter->m_strID));
            CDvmValue *pCDvmValue = pValue->AddValue(GetTrimValue(pXrioCustomParameter->m_strName),strTempIDPath,GetTrimValue(pXrioCustomParameter->m_strDataType),GetTrimValue(pXrioCustomParameter->m_strValue));
            InitDataType(pCDvmValue->m_strDataType,pCDvmValue);

            //2024-9-27补充小数点位数节点
            AddParameterUnitDecimalPlaces(pXrioCustomParameter,pCDvmValue);
            AddParameterForeignId(pXrioCustomParameter,pCDvmValue);
            AddParameterDescription(pXrioCustomParameter,pCDvmValue);
            AddParameterUnit(pXrioCustomParameter,pCDvmValue);
            AddParameterMinValue(pXrioCustomParameter,pCDvmValue);
            AddParameterMaxValue(pXrioCustomParameter,pCDvmValue);
            AddParameterValueFormula(pXrioCustomParameter,pCDvmValue);
            AddParameterValue(pXrioCustomParameter,pCDvmValue);

            InitValueByDataType(pCDvmValue->m_strValue,pCDvmValue->m_strDataType,pCDvmValue);
            InitDvmValueAttrNormalize(pCDvmValue);
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::SupplementEmptyNodeAttributes(CDvmValue *pValue)
{
    CString strTempIDPath;
    //2024-9-27补充小数点位数节点
    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);

    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_ForeignId);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_ForeignId,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_ID_ForeignId);

    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_Description);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_Description,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);

    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_Unit);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_Unit,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);

    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_MinValue);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_MinValue,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);

    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_MaxValue);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_MaxValue,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);

    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_ValueFormula);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_ValueFormula,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);

    //2024-9-29当为空节点的时候，之前是补充一个空的值，现在改为参考值，效果不变。
    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_RefValue);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_RefValue,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);

//    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_DEFAULTVALUE);
//    pValue->AddValue(XRIO_DEVICE_MODEL_DEFAULTVALUE,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::ParseXrioRioDeviceNamePlate(CRioNameplate *pRioNameplate, CDvmData *pData)
{
    CExBaseObject *pSubObj= NULL;
    POS NameplatePos = pRioNameplate->GetHeadPosition();
    CRioDeviceMode *pRioDeviceMode = NULL;
    CRioManufacturer *pRioManufacturer = NULL;
    CRioDeviceType *pRioDeviceType = NULL;
    CRioSerialnr *pRioSerialnr = NULL;
    CRioAdditionalINF02 *pRioAdditionalINF02 = NULL;

    while(NameplatePos)
    {
        pSubObj = pRioNameplate->GetNext(NameplatePos);
        CString strTempIDPath;
        if(pSubObj->GetClassID() == XRIOCLASSID_DEVICE_MODEL)
        {
            //第二层value节点DEVICE_MODEL
            pRioDeviceMode = (CRioDeviceMode*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_DEVICE_MODEL);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_DEVICE_MODEL,strTempIDPath,GetTrimValue(pRioDeviceMode->m_strType),GetTrimValue(pRioDeviceMode->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_MANUFACTURER)
        {
            //第二层data节点MANUFACTURER
            pRioManufacturer = (CRioManufacturer*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_MANUFACTURER);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_MANUFACTURER,strTempIDPath,GetTrimValue(pRioManufacturer->m_strType),GetTrimValue(pRioManufacturer->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_DEVICE_TYPE)
        {
            //第二层data节点DEVICE_TYPE
            pRioDeviceType = (CRioDeviceType*)pSubObj;
            strTempIDPath =GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_DEVICE_TYPE);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_DEVICE_TYPE,strTempIDPath,GetTrimValue(pRioDeviceType->m_strType),GetTrimValue(pRioDeviceType->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_SERIALNR)
        {
            //第二层data节点SERIALNR
            pRioSerialnr = (CRioSerialnr*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_SERIALNR);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_SERIALNR,strTempIDPath,GetTrimValue(pRioSerialnr->m_strType),GetTrimValue(pRioSerialnr->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_ADDITIONAL_INFO2)
        {
            //第二层data节点ADDITIONAL_INFO2
            pRioAdditionalINF02 = (CRioAdditionalINF02*)pSubObj;
            strTempIDPath =GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_ADDITIONAL_INFO2);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_ADDITIONAL_INFO2,strTempIDPath,GetTrimValue(pRioAdditionalINF02->m_strType),GetTrimValue(pRioAdditionalINF02->m_strValue));
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::ParseXrioRioDeviceLocation(CRioLocation *pRioLocation, CDvmData *pData)
{
    CExBaseObject *pSubObj= NULL;
    POS LocationPos = pRioLocation->GetHeadPosition();
    CRioDeviceAddress *pRioDeviceAddress = NULL;
    CRioSubstation *pRioSubstation = NULL;
    CRioSubstatioAddress *pRioSubstatioAddress = NULL;
    CRioBay *pRioBay = NULL;
    CRioBayAddress *pRioBayAddress = NULL;
    CRioProtectedObjectName *pRioProtectedObjectName = NULL;
    while(LocationPos)
    {
        CString strTempIDPath;
        pSubObj = pRioLocation->GetNext(LocationPos);
        if(pSubObj->GetClassID() == XRIOCLASSID_DEVICE_ADDRESS)
        {
            //第二层data节点DEVICE_ADDRESS
            pRioDeviceAddress = (CRioDeviceAddress*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_DEVICE_ADDRESS);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_DEVICE_ADDRESS,strTempIDPath,GetTrimValue(pRioDeviceAddress->m_strType),GetTrimValue(pRioDeviceAddress->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_SUBSTATION)
        {
            //第二层data节点SUBSTATION
            pRioSubstation = (CRioSubstation*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_SUBSTATION);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_SUBSTATION,strTempIDPath,GetTrimValue(pRioSubstation->m_strType),GetTrimValue(pRioSubstation->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_SUBSTATION_ADDRESS)
        {
            //第二层data节点SUBSTATION_ADDRESS
            pRioSubstatioAddress = (CRioSubstatioAddress*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_SUBSTATION_ADDRESS);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_SUBSTATION_ADDRESS,strTempIDPath,GetTrimValue(pRioSubstatioAddress->m_strType),GetTrimValue(pRioSubstatioAddress->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_BAY)
        {
            //第二层data节点BAY
            pRioBay = (CRioBay*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_BAY);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_BAY,strTempIDPath,GetTrimValue(pRioBay->m_strType),GetTrimValue(pRioBay->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_BAY_ADDRESS)
        {
            //第二层data节点BAY_ADDRESS
            pRioBayAddress = (CRioBayAddress*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_BAY_ADDRESS);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_BAY_ADDRESS,strTempIDPath,GetTrimValue(pRioBayAddress->m_strType),GetTrimValue(pRioBayAddress->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_PROTECTED_OBJECT_NAME)
        {
            //第二层data节点PROTECTED_OBJECT_NAME
            pRioProtectedObjectName = (CRioProtectedObjectName*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_PROTECTED_OBJECT_NAME);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_PROTECTED_OBJECT_NAME,strTempIDPath,GetTrimValue(pRioProtectedObjectName->m_strType),GetTrimValue(pRioProtectedObjectName->m_strValue));
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::ParseXrioRioDeviceNominalValues(CRioNominalValues *pRioNominalValues, CDvmData *pData)
{
    CExBaseObject *pSubObj= NULL;
    POS NominalValuesPos = pRioNominalValues->GetHeadPosition();
    CRioPhases *pRioPhases = NULL;
    CRioFNom *pRioFNom = NULL;
    CRioVNom *pRioVNom = NULL;
    CRioVPrimLL *pRioVPrimLL = NULL;
    CRioINom *pRioINom = NULL;
    CRioIPrim *pRioIPrim = NULL;
    while(NominalValuesPos)
    {
        CString strTempIDPath;
        pSubObj = pRioNominalValues->GetNext(NominalValuesPos);
        if(pSubObj->GetClassID() == XRIOCLASSID_PHASES)
        {
            //第二层data节点PHASES
            pRioPhases = (CRioPhases*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_PHASES);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_PHASES,strTempIDPath,GetTrimValue(pRioPhases->m_strType),GetTrimValue(pRioPhases->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_FNOM)
        {
            //第二层data节点FNOM
            pRioFNom = (CRioFNom*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_FNOM);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_FNOM,strTempIDPath,GetTrimValue(pRioFNom->m_strType),GetTrimValue(pRioFNom->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_VNOM)
        {
            //第二层data节点VNOM
            pRioVNom = (CRioVNom*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_VNOM);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_VNOM,strTempIDPath,GetTrimValue(pRioVNom->m_strType),GetTrimValue(pRioVNom->m_strValue));
        }
        if(pSubObj->GetClassID() == XRIOCLASSID_VPRIM_LL)
        {
            //第二层data节点VPRIM_LL
            pRioVPrimLL = (CRioVPrimLL*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_VPRIM_LL);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_VPRIM_LL,strTempIDPath,GetTrimValue(pRioVPrimLL->m_strType),GetTrimValue(pRioVPrimLL->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_INOM)
        {
            //第二层data节点INOM
            pRioINom = (CRioINom*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_INOM);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_INOM,strTempIDPath,GetTrimValue(pRioINom->m_strType),GetTrimValue(pRioINom->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_IPRIM)
        {
            //第二层data节点IPRIM
            pRioIPrim = (CRioIPrim*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_IPRIM);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_IPRIM,strTempIDPath,GetTrimValue(pRioIPrim->m_strType),GetTrimValue(pRioIPrim->m_strValue));
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::ParseXrioRioDeviceResiDualfactors(CRioResidualFactors *pRioResidualFactors, CDvmData *pData)
{
    CExBaseObject *pSubObj= NULL;
    POS ResidualFactorsPos = pRioResidualFactors->GetHeadPosition();
    CRioVLNVN *pRioVLNVN = NULL;
    CRioININOM *pRioININOM = NULL;
    while(ResidualFactorsPos)
    {
        CString strTempIDPath;
        pSubObj = pRioResidualFactors->GetNext(ResidualFactorsPos);
        if(pSubObj->GetClassID() == XRIOCLASSID_VLNVN)
        {
            //第二层data节点VLNVN
            pRioVLNVN = (CRioVLNVN*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_VLNVN);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_VLNVN,strTempIDPath,GetTrimValue(pRioVLNVN->m_strType),GetTrimValue(pRioVLNVN->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_ININOM)
        {
            //第二层data节点ININOM
            pRioININOM = (CRioININOM*)pSubObj;
            strTempIDPath =GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_ININOM);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_ININOM,strTempIDPath,GetTrimValue(pRioININOM->m_strType),GetTrimValue(pRioININOM->m_strValue));
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::ParseXrioRioDeviceLimits(CRioLimits *pRioLimits, CDvmData *pData)
{
    CExBaseObject *pSubObj= NULL;
    POS LimitsPos = pRioLimits->GetHeadPosition();
    CRioVMaxLL *pRioVMaxLL = NULL;
    CRioIMax *pRioIMax  = NULL;
    while(LimitsPos)
    {
        CString strTempIDPath;
        pSubObj = pRioLimits->GetNext(LimitsPos);
        if(pSubObj->GetClassID() == XRIOCLASSID_VMAX_LL)
        {
            //第二层data节点VMAX_LL
            pRioVMaxLL = (CRioVMaxLL*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_VMAX_LL);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_VMAX_LL,strTempIDPath,GetTrimValue(pRioVMaxLL->m_strType),GetTrimValue(pRioVMaxLL->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_IMAX)
        {
            //第二层data节点IMAX
            pRioIMax = (CRioIMax*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_IMAX);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_IMAX,strTempIDPath,GetTrimValue(pRioIMax->m_strType),GetTrimValue(pRioIMax->m_strValue));
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::ParseXrioRioDeviceMisc(CRioMisc *pRioMisc, CDvmData *pData)
{
    CExBaseObject *pSubObj= NULL;
    POS MiscPos = pRioMisc->GetHeadPosition();
    CRioDeBounceTime *pRioDeBounceTime = NULL;
    CRioDeGlitchTime *pRioDeGlitchTime  = NULL;
    CRioOverloadSupTime *pRioOverloadSupTime  = NULL;
    while(MiscPos)
    {
        CString strTempIDPath;
        pSubObj = pRioMisc->GetNext(MiscPos);
        if(pSubObj->GetClassID() == XRIOCLASSID_DEBOUNCETIME)
        {
            //第二层data节点DEBOUNCETIME
            pRioDeBounceTime = (CRioDeBounceTime*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_DEBOUNCETIME);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_DEBOUNCETIME,strTempIDPath,GetTrimValue(pRioDeBounceTime->m_strType),GetTrimValue(pRioDeBounceTime->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_DEGLITCHTIME)
        {
            //第二层data节点DEGLITCHTIME
            pRioDeGlitchTime = (CRioDeGlitchTime*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_DEGLITCHTIME);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_DEGLITCHTIME,strTempIDPath,GetTrimValue(pRioDeGlitchTime->m_strType),GetTrimValue(pRioDeGlitchTime->m_strValue));
        }
        else if(pSubObj->GetClassID() == XRIOCLASSID_OVERLOADSUPTIME)
        {
            //第二层data节点OVERLOADSUPTIME
            pRioOverloadSupTime = (CRioOverloadSupTime*)pSubObj;
            strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_OVERLOADSUPTIME);
            pData->AddValue(XRIO_DEVICE_MODEL_ID_OVERLOADSUPTIME,strTempIDPath,GetTrimValue(pRioOverloadSupTime->m_strType),GetTrimValue(pRioOverloadSupTime->m_strValue));
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::ParseXrioRioCBConfiguration(CDvmLogicDevice *pSrcLogicDevice, CExBaseObject *pObj)
{
    CExBaseObject *pSubObj = NULL;
    if(pObj->GetClassID() == XRIOCLASSID_CBCONFIGURATION)
    {
        CRioCBConfig *pRioCBConfig = (CRioCBConfig*)pObj;
        //group节点CBCONFIGURATION
        CDvmDataset *pCDvmDataset = (CDvmDataset*)pSrcLogicDevice->CreateNewChild(DVMCLASSID_CDVMDATASET);
        pSrcLogicDevice->AddNewChild(pCDvmDataset);
        CString strCBName = GetTrimValue(pRioCBConfig->m_strBlockType);
        pCDvmDataset->m_strName = pRioCBConfig->m_strName.isEmpty()? strCBName:pRioCBConfig->m_strName;
        pCDvmDataset->m_strID = pRioCBConfig->m_strID.isEmpty()? XRIO_DEVICE_MODEL_ID_CBCONFIGURATION:pRioCBConfig->m_strID;
        pCDvmDataset->m_strDataType = XRIO_DEVICE_MODEL_DATA_TYPE_CBCONFIGURATION;
//        pCDvmDataset->m_strName = GetTrimValue(pRioCBConfig->m_strBlockType)/*pRioCBConfig->m_strBlockType*/;
//        pCDvmDataset->m_strID = XRIO_DEVICE_MODEL_ID_CBCONFIGURATION;
//        pCDvmDataset->m_strDataType = GetTrimValue(pRioCBConfig->m_strType)/*pRioCBConfig->m_strType*/;

        POS CBConfigPos = pRioCBConfig->GetHeadPosition();
        CRioTripTime *pRioTripTime = NULL;
        CRioCloseTime *pRioCloseTime = NULL;
        CRioP52AB *pRioP52AB = NULL;
        CString strTemp;
        while (CBConfigPos)
        {
            pSubObj = pRioCBConfig->GetNext(CBConfigPos);
            if (pSubObj->GetClassID() == XRIOCLASSID_TRIPTIME)
            {
                //data节点TRIPTIME
                pRioTripTime = (CRioTripTime*)pSubObj;
                strTemp.Format(_T("%lf"),CString_To_double(pRioTripTime->m_strValue)*1000);
                CDvmData* pChildData = pCDvmDataset->AddNewData(_T("断路器跳闸时间"), XRIO_DEVICE_MODEL_ID_TRIPTIME, GetTrimValue(pRioTripTime->m_strType), strTemp);
                pChildData->m_strUnit = _T("ms");
                pChildData->m_strMin = _T("20.00");
                pChildData->m_strMax = _T("500.00");
                ParseXrioRioCBConfigurationTriptime(pRioTripTime, pChildData);
            }
            if (pSubObj->GetClassID() == XRIOCLASSID_CLOSETIME)
            {
                //data节点CLOSETIME
                pRioCloseTime = (CRioCloseTime*)pSubObj;
                strTemp.Format(_T("%lf"),CString_To_double(pRioCloseTime->m_strValue)*1000);
                CDvmData* pChildData = pCDvmDataset->AddNewData(_T("断路器合闸时间"), XRIO_DEVICE_MODEL_ID_CLOSETIME, GetTrimValue(pRioCloseTime->m_strType), strTemp);
                pChildData->m_strUnit = _T("ms");
                pChildData->m_strMin = _T("20.00");
                pChildData->m_strMax = _T("500000.00");
                ParseXrioRioCBConfigurationClosetime(pRioCloseTime, pChildData);
            }
            if (pSubObj->GetClassID() == XRIOCLASSID_P52AB)
            {
                //data节点P52AB
                pRioP52AB = (CRioP52AB*)pSubObj;
                strTemp.Format(_T("%lf"),CString_To_double(pRioP52AB->m_strValue));
                CDvmData* pChildData = pCDvmDataset->AddNewData(_T("断路器的 52a、52b %"), XRIO_DEVICE_MODEL_ID_P52AB, GetTrimValue(pRioP52AB->m_strType), strTemp);
                pChildData->m_strUnit = _T("%");
                pChildData->m_strMin = _T("0.00");
                pChildData->m_strMax = _T("45.00");
                ParseXrioRioCBConfigurationP52AB(pRioP52AB, pChildData);
            }
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CXrioToDeviceModelTool::ParseXrioRioCBConfigurationTriptime(CRioTripTime *pRioTripTime, CDvmData *pData)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_Description);
    pData->AddValue(XRIO_DEVICE_MODEL_ID_Description,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,_T("断路器跳闸时间"));

    strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_ValueFormula);
    pData->AddValue(XRIO_DEVICE_MODEL_ID_ValueFormula,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::ParseXrioRioCBConfigurationClosetime(CRioCloseTime *pRioCloseTime, CDvmData *pData)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_Description);
    pData->AddValue(XRIO_DEVICE_MODEL_ID_Description,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,_T("断路器合闸时间"));

    strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_ValueFormula);
    pData->AddValue(XRIO_DEVICE_MODEL_ID_ValueFormula,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::ParseXrioRioCBConfigurationP52AB(CRioP52AB *pRioP52AB, CDvmData *pData)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_Description);
    pData->AddValue(XRIO_DEVICE_MODEL_ID_Description,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,_T("以断路器时间百分比表示的 52a、52b 时间"));

    strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_ValueFormula);
    pData->AddValue(XRIO_DEVICE_MODEL_ID_ValueFormula,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,XRIO_DEVICE_MODEL_DEFAULTVALUE);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInDvmDataset(CDvmDataset *pSrcDataset, CDvmDataset *pDesDataset)
{
    CString strSrcObjIDPath;
    CExBaseObject *pSrcObj = NULL;
    CExBaseObject *pDesObj = NULL;
    POS pos = pSrcDataset->GetHeadPosition();
    while(pos)
    {
        pSrcObj = pSrcDataset->GetNext(pos);
        strSrcObjIDPath = pSrcObj->m_strID;
        pDesObj = pDesDataset->FindByID(strSrcObjIDPath);
        if(pDesObj != NULL )
        {
            if(IsFatherNode(pDesObj))
            {
                //说明存在这样的CDvmData，进入下轮函数查找
                UpdateDeviceModelInDvmData((CDvmData*)pSrcObj,(CDvmData*)pDesObj);
            }
            else
            {
                UpdateDataNode((CDvmData*)pSrcObj,(CDvmData*)pDesObj);
            }
        }
        else
        {
            CString strTempIDPath;
            strTempIDPath = GetObjectIDPath(pSrcDataset->m_strID,XRIO_DEVICE_MODEL_DEFAULTVALUE);
            if(pSrcObj->m_strID != strTempIDPath)
            {
                pDesDataset->AddNewData((CDvmData*)pSrcObj);
            }
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInDvmData(CDvmData *pSrcDvmData, CDvmData *pDesDvmData)
{
    CString strSrcObjIDPath;
    CExBaseObject *pSrcObj = NULL;
    CExBaseObject *pDesObj = NULL;
    POS pos = pSrcDvmData->GetHeadPosition();
    while(pos)
    {
        pSrcObj = pSrcDvmData->GetNext(pos);
        strSrcObjIDPath = pSrcObj->m_strID;
        pDesObj = pDesDvmData->FindByID(strSrcObjIDPath);
        if(pDesObj != NULL)
        {
            if(IsFatherNode(pDesObj))
            {
                //说明存在这样的CDvmValue，进入下轮函数查找
                UpdateDeviceModelInDvmValue((CDvmValue*)pSrcObj,(CDvmValue*)pDesObj);
            }
            else
            {
                UpdateValueNode((CDvmValue*)pSrcObj,(CDvmValue*)pDesObj);
            }
        }
        else
        {
            CString strTempIDPath;
            strTempIDPath = GetObjectIDPath(pSrcDvmData->m_strID,XRIO_DEVICE_MODEL_DEFAULTVALUE);
            if(pSrcObj->m_strID != strTempIDPath)
            {
                pDesDvmData->AddNewValue((CDvmValue*)pSrcObj);
            }
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInDvmValue(CDvmValue *pSrcDvmValue, CDvmValue *pDesDvmValue)
{
    CString strSrcObjIDPath;
    CExBaseObject *pSrcObj = NULL;
    CExBaseObject *pDesObj = NULL;
    POS pos = pSrcDvmValue->GetHeadPosition();
    while(pos)
    {
        pSrcObj = pSrcDvmValue->GetNext(pos);
        strSrcObjIDPath = pSrcObj->m_strID;
        pDesObj = pDesDvmValue->FindByID(strSrcObjIDPath);
        if(pDesObj != NULL)
        {
            if(IsFatherNode(pDesObj))
            {
                //说明存在这样的CDvmValue，进入下轮函数查找
                UpdateDeviceModelInDvmValue((CDvmValue*)pSrcObj,(CDvmValue*)pDesObj);
            }
            else
            {
                UpdateValueNode((CDvmValue*)pSrcObj,(CDvmValue*)pDesObj);
            }
        }
        else
        {   CString strTempIDPath;
            strTempIDPath = GetObjectIDPath(pSrcDvmValue->m_strID,XRIO_DEVICE_MODEL_DEFAULTVALUE);
            if(pSrcObj->m_strID != strTempIDPath)
            {
                CDvmValue* pSrcValue = (CDvmValue*)pSrcObj;
                pDesDvmValue->AddNewChild((CExBaseObject*)pSrcValue->Clone());
            }
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::AddAdditionalAttributes(CDvmValue* pSrcValue,CDvmValue* pDesValue,const CString& strID)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pSrcValue->m_strID,strID);
    CDvmValue* pSrcAttributeValue = (CDvmValue*)pSrcValue->FindByID(strTempIDPath);
    if(pSrcAttributeValue != NULL)
    {
        pDesValue->AddValue(strID,pSrcAttributeValue->m_strID,XRIO_DEVICE_MODEL_DEFAULTVALUE,pSrcAttributeValue->m_strValue);
        return TRUE;
    }
    return FALSE;
}

BOOL CXrioToDeviceModelTool::AddMultipleValues(CDvmValue* pSrcValue,CDvmValue* pDesValue,const CString& strID)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pSrcValue->m_strID,strID);
    CDvmValue* pSrcValues = NULL;
    POS pSrcValuePos = pSrcValue->FindPosByID(strTempIDPath);

    if(pSrcValuePos)
    {
        pSrcValue->GetNext(pSrcValuePos);
    }
    while(pSrcValuePos)
    {
        pSrcValues = (CDvmValue*)pSrcValue->GetNext(pSrcValuePos);
        if(pSrcValues != NULL)
        {
            pDesValue->AddValue(pSrcValues->m_strName,pSrcValues->m_strID,pSrcValues->m_strDataType,pSrcValues->m_strValue);
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInRioDevice(CDvmDataset *pSrcRioDevice, CDvmDataset *pDesRioDevice)
{
    UpdateRioDataObject(pSrcRioDevice,pDesRioDevice,XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE);
    UpdateRioDataObject(pSrcRioDevice,pDesRioDevice,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION);
    UpdateRioDataObject(pSrcRioDevice,pDesRioDevice,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES);
    UpdateRioDataObject(pSrcRioDevice,pDesRioDevice,XRIO_DEVICE_MODEL_ID_DEVICE_RESIDUALFACTORS);
    UpdateRioDataObject(pSrcRioDevice,pDesRioDevice,XRIO_DEVICE_MODEL_ID_DEVICE_LIMITS);
    UpdateRioDataObject(pSrcRioDevice,pDesRioDevice,XRIO_DEVICE_MODEL_ID_DEVICE_MISC);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInRioNameplate(CDvmData *pSrcRioNameplate, CDvmData *pDesRioNameplate)
{
    UpdateRioDeviceValueObject(pSrcRioNameplate,pDesRioNameplate,XRIO_DEVICE_MODEL_ID_DEVICE_MODEL);
    UpdateRioDeviceValueObject(pSrcRioNameplate,pDesRioNameplate,XRIO_DEVICE_MODEL_ID_MANUFACTURER);
    UpdateRioDeviceValueObject(pSrcRioNameplate,pDesRioNameplate,XRIO_DEVICE_MODEL_ID_DEVICE_TYPE);
    UpdateRioDeviceValueObject(pSrcRioNameplate,pDesRioNameplate,XRIO_DEVICE_MODEL_ID_SERIALNR);
    UpdateRioDeviceValueObject(pSrcRioNameplate,pDesRioNameplate,XRIO_DEVICE_MODEL_ID_ADDITIONAL_INFO2);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInRioLocation(CDvmData *pSrcRioLocation, CDvmData *pDesRioLocation)
{
    UpdateRioDeviceValueObject(pSrcRioLocation,pDesRioLocation,XRIO_DEVICE_MODEL_ID_DEVICE_ADDRESS);
    UpdateRioDeviceValueObject(pSrcRioLocation,pDesRioLocation,XRIO_DEVICE_MODEL_ID_SUBSTATION);
    UpdateRioDeviceValueObject(pSrcRioLocation,pDesRioLocation,XRIO_DEVICE_MODEL_ID_SUBSTATION_ADDRESS);
    UpdateRioDeviceValueObject(pSrcRioLocation,pDesRioLocation,XRIO_DEVICE_MODEL_ID_BAY);
    UpdateRioDeviceValueObject(pSrcRioLocation,pDesRioLocation,XRIO_DEVICE_MODEL_ID_BAY_ADDRESS);
    UpdateRioDeviceValueObject(pSrcRioLocation,pDesRioLocation,XRIO_DEVICE_MODEL_ID_PROTECTED_OBJECT_NAME);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInRioNominalValues(CDvmData *pSrcRioNominalValues, CDvmData *pDesRioNominalValues)
{
    UpdateRioDeviceValueObject(pSrcRioNominalValues,pDesRioNominalValues,XRIO_DEVICE_MODEL_ID_PHASES);
    UpdateRioDeviceValueObject(pSrcRioNominalValues,pDesRioNominalValues,XRIO_DEVICE_MODEL_ID_FNOM);
    UpdateRioDeviceValueObject(pSrcRioNominalValues,pDesRioNominalValues,XRIO_DEVICE_MODEL_ID_VNOM);
    UpdateRioDeviceValueObject(pSrcRioNominalValues,pDesRioNominalValues,XRIO_DEVICE_MODEL_ID_VPRIM_LL);
    UpdateRioDeviceValueObject(pSrcRioNominalValues,pDesRioNominalValues,XRIO_DEVICE_MODEL_ID_INOM);
    UpdateRioDeviceValueObject(pSrcRioNominalValues,pDesRioNominalValues,XRIO_DEVICE_MODEL_ID_IPRIM);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInRioResidualFactors(CDvmData *pSrcRioResidualFactors, CDvmData *pDesRioResidualFactors)
{
    UpdateRioDeviceValueObject(pSrcRioResidualFactors,pDesRioResidualFactors,XRIO_DEVICE_MODEL_ID_VLNVN);
    UpdateRioDeviceValueObject(pSrcRioResidualFactors,pDesRioResidualFactors,XRIO_DEVICE_MODEL_ID_ININOM);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInRioLimits(CDvmData *pSrcRioLimits, CDvmData *pDesRioLimits)
{
    UpdateRioDeviceValueObject(pSrcRioLimits,pDesRioLimits,XRIO_DEVICE_MODEL_ID_VMAX_LL);
    UpdateRioDeviceValueObject(pSrcRioLimits,pDesRioLimits,XRIO_DEVICE_MODEL_ID_IMAX);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInRioMisc(CDvmData *pSrcRioMisc, CDvmData *pDesRioMisc)
{
    UpdateRioDeviceValueObject(pSrcRioMisc,pDesRioMisc,XRIO_DEVICE_MODEL_ID_DEBOUNCETIME);
    UpdateRioDeviceValueObject(pSrcRioMisc,pDesRioMisc,XRIO_DEVICE_MODEL_ID_DEGLITCHTIME);
    UpdateRioDeviceValueObject(pSrcRioMisc,pDesRioMisc,XRIO_DEVICE_MODEL_ID_OVERLOADSUPTIME);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInRioCBConfig(CDvmDataset *pSrcRioCBConfig, CDvmDataset *pDesRioCBConfig)
{
    UpdateRioDataObject(pSrcRioCBConfig,pDesRioCBConfig,XRIO_DEVICE_MODEL_ID_TRIPTIME);
    UpdateRioDataObject(pSrcRioCBConfig,pDesRioCBConfig,XRIO_DEVICE_MODEL_ID_CLOSETIME);
    UpdateRioDataObject(pSrcRioCBConfig,pDesRioCBConfig,XRIO_DEVICE_MODEL_ID_P52AB);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInRioTripTime(CDvmData *pSrcRioTripTime, CDvmData *pDesRioTripTime)
{
    UpdateRioCBConfigValueObject(pSrcRioTripTime,pDesRioTripTime);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInRioCloseTime(CDvmData *pSrcRioCloseTime, CDvmData *pDesRioCloseTime)
{
    UpdateRioCBConfigValueObject(pSrcRioCloseTime,pDesRioCloseTime);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDeviceModelInRioP52AB(CDvmData *pSrcRioP52AB, CDvmData *pDesRioP52AB)
{
    UpdateRioCBConfigValueObject(pSrcRioP52AB,pDesRioP52AB);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::IsFatherNode(CExBaseObject *pNode)
{
    CExBaseObject* pObj = NULL;
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pNode->m_strID,XRIO_DEVICE_MODEL_ID_ForeignId);
    pObj = ((CExBaseList*)pNode)->FindByID(strTempIDPath);
    if(pObj != NULL)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

BOOL CXrioToDeviceModelTool::UpdateOwnAttrVal(const CString &strSrcValue, CString &strDesValue)
{
    if(strSrcValue == strDesValue)
    {
        return FALSE;
    }
    strDesValue = strSrcValue;
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateDataNode(CDvmData *pSrcDataNode, CDvmData *pDesDataNode)
{
    //2024-9-29修改值的更新根据数据类型
    if(pSrcDataNode->m_strDataType == pDesDataNode->m_strDataType)
    {
        if(XRIO_CUSTOM_PARAMETER_DATATYPE_STRING == pDesDataNode->m_strDataType || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN == pDesDataNode->m_strDataType)
        {
            //字符串类型和布尔类型无需更新单位，最小值，最大值，小数点位数
            UpdateOwnAttrVal(pSrcDataNode->m_strName,pDesDataNode->m_strName);
            UpdateOwnAttrVal(pSrcDataNode->m_strValue,pDesDataNode->m_strValue);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_RefValue);
            return TRUE;
        }
        else if(XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == pDesDataNode->m_strDataType)
        {
            UpdateOwnAttrVal(pSrcDataNode->m_strName,pDesDataNode->m_strName);
            UpdateOwnAttrVal(pSrcDataNode->m_strUnit,pDesDataNode->m_strUnit);
            UpdateValue_DataType_Double(pSrcDataNode->m_strMin,pDesDataNode->m_strMin);
            UpdateValue_DataType_Double(pSrcDataNode->m_strMax,pDesDataNode->m_strMax);
            UpdateValue_DataType_Double(pSrcDataNode->m_strValue,pDesDataNode->m_strValue);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces,FALSE);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_RefValue,FALSE,&CXrioToDeviceModelTool::UpdateValue_DataType_Double);
            return TRUE;
        }
        else if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDesDataNode->m_strDataType)
        {
            UpdateOwnAttrVal(pSrcDataNode->m_strName,pDesDataNode->m_strName);
            //枚举类型无需更新单位，最小值，最大值，小数点位数
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_RefValue);
            //更新枚举值
            UpdateEnumerationValues(pSrcDataNode,pDesDataNode);
            UpdateOwnAttrVal(pDesDataNode->m_strValue,pSrcDataNode->m_strValue);
            return TRUE;
        }
        else if(XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == pDesDataNode->m_strDataType)
        {
            UpdateOwnAttrVal(pSrcDataNode->m_strName,pDesDataNode->m_strName);
            //int类型无需更新单位，小数点位数
            UpdateValue_DataType_Int(pSrcDataNode->m_strMin,pDesDataNode->m_strMin);
            UpdateValue_DataType_Int(pSrcDataNode->m_strMax,pDesDataNode->m_strMax);
            UpdateValue_DataType_Int(pSrcDataNode->m_strValue,pDesDataNode->m_strValue);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_RefValue,FALSE,&CXrioToDeviceModelTool::UpdateValue_DataType_Int);
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else if(pSrcDataNode->m_strDataType != pDesDataNode->m_strDataType)
    {
        if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pSrcDataNode->m_strDataType && XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION != pDesDataNode->m_strDataType)
        {
            UpdateOwnAttrVal(pSrcDataNode->m_strName,pDesDataNode->m_strName);
            UpdateOwnAttrVal(pSrcDataNode->m_strValue,pDesDataNode->m_strValue);
            UpdateOwnAttrVal(pSrcDataNode->m_strDataType,pDesDataNode->m_strDataType);
            UpdateOwnAttrVal(pSrcDataNode->m_strUnit,pDesDataNode->m_strUnit);
            UpdateOwnAttrVal(pSrcDataNode->m_strMin,pDesDataNode->m_strMin);
            UpdateOwnAttrVal(pSrcDataNode->m_strMax,pDesDataNode->m_strMax);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);

            CDvmValue *pSrcValues = NULL;
            CExBaseObject *pObj = NULL;
            pObj = GetAttrObj(pDesDataNode,XRIO_DEVICE_MODEL_ID_RefValue);
            if(pObj != NULL)
            {
                pDesDataNode->Delete(pObj);//删除参考值节点
            }

            for(POS startPos = pSrcDataNode->GetHeadPosition();startPos != NULL;)
            {
                pSrcValues = (CDvmValue*)pSrcDataNode->GetNext(startPos);
                if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pSrcValues->m_strDataType)
                {
                    pDesDataNode->AddNewValue(pSrcValues);//增加枚举值和参考值
                }
            }
            return TRUE;
        }
        else if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION != pSrcDataNode->m_strDataType && XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDesDataNode->m_strDataType)
        {
            UpdateOwnAttrVal(pSrcDataNode->m_strName,pDesDataNode->m_strName);
            UpdateOwnAttrVal(pSrcDataNode->m_strValue,pDesDataNode->m_strValue);
            UpdateOwnAttrVal(pSrcDataNode->m_strDataType,pDesDataNode->m_strDataType);
            UpdateOwnAttrVal(pSrcDataNode->m_strUnit,pDesDataNode->m_strUnit);
            UpdateOwnAttrVal(pSrcDataNode->m_strMin,pDesDataNode->m_strMin);
            UpdateOwnAttrVal(pSrcDataNode->m_strMax,pDesDataNode->m_strMax);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);

            CDvmValue *pSrcRefValue = NULL;
            CDvmValue *pDesValues = NULL;

            for(POS startPos = pDesDataNode->GetHeadPosition();startPos != NULL;)
            {
                pDesValues = (CDvmValue*)pDesDataNode->GetNext(startPos);
                if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDesValues->m_strDataType)
                {
                    pDesDataNode->Delete(pDesValues);//删除枚举值和参考值
                }
            }

            pSrcRefValue = (CDvmValue*)GetAttrObj(pSrcDataNode,XRIO_DEVICE_MODEL_ID_RefValue);
            if(pSrcRefValue != NULL)
            {
                pDesDataNode->AddNewValue(pSrcRefValue);//增加参考值节点
            }
            return TRUE;
        }
        else if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION != pSrcDataNode->m_strDataType && XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION != pDesDataNode->m_strDataType)
        {
            UpdateOwnAttrVal(pSrcDataNode->m_strName,pDesDataNode->m_strName);
            UpdateOwnAttrVal(pSrcDataNode->m_strValue,pDesDataNode->m_strValue);
            UpdateOwnAttrVal(pSrcDataNode->m_strDataType,pDesDataNode->m_strDataType);
            UpdateOwnAttrVal(pSrcDataNode->m_strUnit,pDesDataNode->m_strUnit);
            UpdateOwnAttrVal(pSrcDataNode->m_strMin,pDesDataNode->m_strMin);
            UpdateOwnAttrVal(pSrcDataNode->m_strMax,pDesDataNode->m_strMax);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_RefValue);
            UpdateAdditionalAttributes(pSrcDataNode,pDesDataNode,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

BOOL CXrioToDeviceModelTool::UpdateValueNode(CDvmValue *pSrcValueNode, CDvmValue *pDesValueNode)
{
    //2024-9-29修改值的更新根据数据类型
    if(pSrcValueNode->m_strDataType == pDesValueNode->m_strDataType)
    {
        if(XRIO_CUSTOM_PARAMETER_DATATYPE_STRING == pDesValueNode->m_strDataType || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN == pDesValueNode->m_strDataType)
        {
            //字符串类型和布尔类型无需更新单位，最小值，最大值，小数点位数
            UpdateOwnAttrVal(pSrcValueNode->m_strName,pDesValueNode->m_strName);
            UpdateOwnAttrVal(pSrcValueNode->m_strValue,pDesValueNode->m_strValue);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_RefValue);
            return TRUE;
        }
        else if(XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == pDesValueNode->m_strDataType)
        {
            UpdateOwnAttrVal(pSrcValueNode->m_strName,pDesValueNode->m_strName);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Unit);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_MinValue,FALSE,&CXrioToDeviceModelTool::UpdateValue_DataType_Double);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_MaxValue,FALSE,&CXrioToDeviceModelTool::UpdateValue_DataType_Double);
            UpdateValue_DataType_Double(pSrcValueNode->m_strValue,pDesValueNode->m_strValue);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces,FALSE);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_RefValue,FALSE,&CXrioToDeviceModelTool::UpdateValue_DataType_Double);
            return TRUE;
        }
        else if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDesValueNode->m_strDataType)
        {
            UpdateOwnAttrVal(pSrcValueNode->m_strName,pDesValueNode->m_strName);
            //枚举类型无需更新单位，最小值，最大值，小数点位数
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_RefValue);
            //更新枚举值
            UpdateEnumerationValues(pSrcValueNode,pDesValueNode);
            UpdateOwnAttrVal(pSrcValueNode->m_strValue,pDesValueNode->m_strValue);
            return TRUE;
        }
        else if(XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == pDesValueNode->m_strDataType)
        {
            UpdateOwnAttrVal(pSrcValueNode->m_strName,pDesValueNode->m_strName);
            //int类型无需更新单位，小数点位数
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_MinValue,FALSE,&CXrioToDeviceModelTool::UpdateValue_DataType_Int);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_MaxValue,FALSE,&CXrioToDeviceModelTool::UpdateValue_DataType_Int);
            UpdateValue_DataType_Int(pSrcValueNode->m_strValue,pDesValueNode->m_strValue);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_RefValue,FALSE,&CXrioToDeviceModelTool::UpdateValue_DataType_Int);
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else if(pSrcValueNode->m_strDataType != pDesValueNode->m_strDataType)
    {
        if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pSrcValueNode->m_strDataType && XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION != pDesValueNode->m_strDataType)
        {
            UpdateOwnAttrVal(pSrcValueNode->m_strName,pDesValueNode->m_strName);
            UpdateOwnAttrVal(pSrcValueNode->m_strValue,pDesValueNode->m_strValue);
            UpdateOwnAttrVal(pSrcValueNode->m_strDataType,pDesValueNode->m_strDataType);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Unit);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_MinValue);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_MaxValue);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);

            CDvmValue *pSrcValues = NULL;
            CExBaseObject *pObj = NULL;
            pObj = GetAttrObj(pDesValueNode,XRIO_DEVICE_MODEL_ID_RefValue);
            if(pObj != NULL)
            {
                pDesValueNode->Delete(pObj);//删除参考值节点
            }

            for(POS startPos = pSrcValueNode->GetHeadPosition();startPos != NULL;)
            {
                pSrcValues = (CDvmValue*)pSrcValueNode->GetNext(startPos);
                if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pSrcValues->m_strDataType)
                {
                    pDesValueNode->AddNewChild((CExBaseObject*)pSrcValues->Clone());//增加枚举值和参考值
                }
            }
            return TRUE;
        }
        else if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION != pSrcValueNode->m_strDataType && XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDesValueNode->m_strDataType)
        {
            UpdateOwnAttrVal(pSrcValueNode->m_strName,pDesValueNode->m_strName);
            UpdateOwnAttrVal(pSrcValueNode->m_strValue,pDesValueNode->m_strValue);
            UpdateOwnAttrVal(pSrcValueNode->m_strDataType,pDesValueNode->m_strDataType);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Unit);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_MinValue);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_MaxValue);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);

            CDvmValue *pSrcRefValue = NULL;
            CDvmValue *pDesValues = NULL;

            for(POS startPos = pDesValueNode->GetHeadPosition();startPos != NULL;)
            {
                pDesValues = (CDvmValue*)pDesValueNode->GetNext(startPos);
                if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDesValues->m_strDataType)
                {
                    pDesValueNode->Delete(pDesValues);//删除枚举值和参考值
                }
            }

            pSrcRefValue = (CDvmValue*)GetAttrObj(pSrcValueNode,XRIO_DEVICE_MODEL_ID_RefValue);
            if(pSrcRefValue != NULL)
            {
                pDesValueNode->AddNewChild((CExBaseObject*)pSrcRefValue->Clone());//增加参考值节点
            }
            return TRUE;
        }
        else if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION != pSrcValueNode->m_strDataType && XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION != pDesValueNode->m_strDataType)
        {
            UpdateOwnAttrVal(pSrcValueNode->m_strName,pDesValueNode->m_strName);
            UpdateOwnAttrVal(pSrcValueNode->m_strValue,pDesValueNode->m_strValue);
            UpdateOwnAttrVal(pSrcValueNode->m_strDataType,pDesValueNode->m_strDataType);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Unit);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_MinValue);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_MaxValue);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ForeignId);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Description);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_ValueFormula);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_RefValue);
            UpdateAdditionalAttributes(pSrcValueNode,pDesValueNode,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

BOOL CXrioToDeviceModelTool::UpdateAdditionalAttributes(CExBaseList *pSrcList, CExBaseList *pDesList, const CString &strID, BOOL bIsNormal, UPDATE_VALUE_DATATYPE_FUNC pFunc)
{
    CDvmValue *pSrcAttributeValue = NULL;
    CDvmValue *pDesAttributeValue = NULL;

    pSrcAttributeValue = (CDvmValue*)GetAttrObj(pSrcList,strID);
    pDesAttributeValue = (CDvmValue*)GetAttrObj(pDesList,strID);

    if(pSrcAttributeValue == NULL)
    {
        return FALSE;
    }

    if(pDesAttributeValue == NULL)
    {
        return FALSE;
    }

    if(bIsNormal)
    {
        if(pDesAttributeValue->m_strValue == pSrcAttributeValue->m_strValue)
        {
            return FALSE;
        }

        pDesAttributeValue->m_strValue = pSrcAttributeValue->m_strValue;

        return TRUE;
    }

    if(XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces == strID)
    {
        long nSrcPrecision,nDesnPrecision;
        nSrcPrecision = CString_To_long(pSrcAttributeValue->m_strValue);
        nDesnPrecision = CString_To_long(pDesAttributeValue->m_strValue);

        if(nSrcPrecision == nDesnPrecision)
        {
            return FALSE;
        }

        pDesAttributeValue->m_strValue = pSrcAttributeValue->m_strValue;

        return TRUE;
    }
    else if(XRIO_DEVICE_MODEL_ID_MinValue == strID || XRIO_DEVICE_MODEL_ID_MaxValue == strID)
    {
        return (this->*pFunc)(pSrcAttributeValue->m_strValue,pDesAttributeValue->m_strValue);
    }
    else if(XRIO_DEVICE_MODEL_ID_RefValue == strID)
    {
        if(pSrcAttributeValue->m_strValue.isEmpty() || pDesAttributeValue->m_strValue.isEmpty())
        {
            pDesAttributeValue->m_strValue = pSrcAttributeValue->m_strValue;
            return TRUE;
        }

        return (this->*pFunc)(pSrcAttributeValue->m_strValue,pDesAttributeValue->m_strValue);
    }
    else
    {
        return FALSE;
    }
}

BOOL CXrioToDeviceModelTool::UpdateEnumerationValues(CExBaseList *pSrcList, CExBaseList *pDesList)
{
    CDvmValue* pDesValues = NULL;
    CDvmValue* pSrcValues = NULL;
    for(POS startPos = pSrcList->GetHeadPosition();startPos != pSrcList->GetTailPosition();)
    {
        pSrcValues = (CDvmValue*)pSrcList->GetNext(startPos);
        if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pSrcValues->m_strDataType)
        {
            pDesValues = (CDvmValue*)pDesList->FindByID(pSrcValues->m_strID);
            if(pDesValues != NULL)
            {
                if(pDesValues->m_strValue != pSrcValues->m_strValue)
                {
                    pDesValues->m_strValue = pSrcValues->m_strValue;
                }

                if(pDesValues->m_strName != pSrcValues->m_strName)
                {
                    pDesValues->m_strName = pSrcValues->m_strName;
                }
            }
            else
            {
                pDesList->AddNewChild((CExBaseObject*)pSrcValues->Clone());
            }
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateValue_DataType_Double(const CString &strSrcValue, CString &strDesValue)
{
    //初始化后一定不会为Nan
    BOOL bOk;
    double dSrcValue,dDesValue;
    bOk = CString_To_double(strSrcValue,dSrcValue);
    ASSERT(bOk);
    bOk = CString_To_double(strDesValue,dDesValue);
    ASSERT(bOk);
    if(DOUBLE_EQUAL != DoubleFuzzyCompare(dSrcValue,dDesValue))
    {
        strDesValue = strSrcValue;
        return TRUE;
    }
    return FALSE;
}

BOOL CXrioToDeviceModelTool::UpdateValue_DataType_Int(const CString &strSrcValue, CString &strDesValue)
{
    int nSrcValue,nDesValue;
    nSrcValue = CString_To_long(strSrcValue);
    nDesValue = CString_To_long(strDesValue);
    if(nSrcValue != nDesValue)
    {
        strDesValue = strSrcValue;
        return TRUE;
    }
    return FALSE;
}

BOOL CXrioToDeviceModelTool::UpdateCustomLogicDeviceObject(CDvmDevice *pSrcDeviceObject, CDvmDevice *pDesDeviceObject,const CString &strID)
{

    CDvmLogicDevice *pSrcCustomLogicDevice = NULL;
    CDvmLogicDevice *pDesCustomLogicDevice = NULL;

    pSrcCustomLogicDevice = (CDvmLogicDevice*)pSrcDeviceObject->FindByID(strID);
    pDesCustomLogicDevice = (CDvmLogicDevice*)pDesDeviceObject->FindByID(strID);

    if(pSrcCustomLogicDevice == NULL)
    {
        return FALSE;
    }

    if(pDesCustomLogicDevice == NULL)
    {
        return FALSE;
    }

    CExBaseObject *pSrcObj = NULL;
    CExBaseObject *pDesObj = NULL;
    CString strSrcObjIDPath;
    POS pos = pSrcCustomLogicDevice->GetHeadPosition();
    while(pos)
    {
        pSrcObj = pSrcCustomLogicDevice->GetNext(pos);
        strSrcObjIDPath = pSrcObj->m_strID;
        pDesObj = pDesCustomLogicDevice->FindByID(strSrcObjIDPath);
        if(pDesObj != NULL)
        {
            //说明存在这样的CDvmDataset，进入下轮函数查找
            UpdateDeviceModelInDvmDataset((CDvmDataset*)pSrcObj,(CDvmDataset*)pDesObj);
        }
        else
        {
            pDesCustomLogicDevice->AddNewDataset((CDvmDataset*)pSrcObj);
        }
    }
    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateRioLogicDeviceObject(CDvmDevice *pSrcDeviceObject, CDvmDevice *pDesDeviceObject, const CString &strID)
{
    CDvmLogicDevice *pSrcRioLogicDevice = NULL;
    CDvmLogicDevice *pDesRioLogicDevice = NULL;
    pSrcRioLogicDevice = (CDvmLogicDevice*)pSrcDeviceObject->FindByID(strID);
    pDesRioLogicDevice = (CDvmLogicDevice*)pDesDeviceObject->FindByID(strID);

    if(pSrcRioLogicDevice == NULL)
    {
        return FALSE;
    }

    if(pDesRioLogicDevice == NULL)
    {
        return FALSE;
    }

    return  UpdateRioDatasetObject(pSrcRioLogicDevice,pDesRioLogicDevice);
}

BOOL CXrioToDeviceModelTool::UpdateRioDatasetObject(CDvmLogicDevice *pSrcLogicDeviceObject, CDvmLogicDevice *pDesLogicDeviceObject, const CString &strID)
{
    CDvmDataset *pSrcRioDataset = NULL;
    CDvmDataset *pDesRioDataset = NULL;
    pSrcRioDataset = (CDvmDataset*)pSrcLogicDeviceObject->FindByID(strID);
    pDesRioDataset = (CDvmDataset*)pDesLogicDeviceObject->FindByID(strID);

    if(pSrcRioDataset == NULL)
    {
        return FALSE;
    }

    if(pDesRioDataset == NULL)
    {
        return FALSE;
    }

    return pDesRioDataset->UpdateDataValue(pSrcRioDataset);
}

BOOL CXrioToDeviceModelTool::UpdateRioDatasetObject(CDvmLogicDevice *pSrcLogicDeviceObject, CDvmLogicDevice *pDesLogicDeviceObject)
{
    CExBaseObject *pObj = NULL;
    CExBaseObject *pFind = NULL;
    POS pos = pSrcLogicDeviceObject->GetHeadPosition();

    while (pos != NULL)
    {
        pObj = pSrcLogicDeviceObject->GetNext(pos);
        ASSERT(pObj != NULL);
        pFind = (CExBaseObject*)pDesLogicDeviceObject->FindByID(pObj->m_strID);

        if (pFind != NULL)
        {
            pObj->Update(pFind);
        }
    }

    return TRUE;
}

BOOL CXrioToDeviceModelTool::UpdateRioDataObject(CDvmDataset *pSrcDatasetObject, CDvmDataset *pDesDatasetObject, const CString &strID)
{
    CDvmData *pSrcDataObject = NULL;
    CDvmData *pDesDataObject = NULL;

    pSrcDataObject = (CDvmData*)pSrcDatasetObject->FindByID(strID);
    pDesDataObject = (CDvmData*)pDesDatasetObject->FindByID(strID);
    if(pSrcDataObject != NULL)
    {
        if(pDesDataObject != NULL)
        {
            if(strID == XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE)
            {
                UpdateDeviceModelInRioNameplate(pSrcDataObject,pDesDataObject);
            }
            else if(strID == XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION)
            {
                UpdateDeviceModelInRioLocation(pSrcDataObject,pDesDataObject);
            }
            else if(strID == XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES)
            {
                UpdateDeviceModelInRioNominalValues(pSrcDataObject,pDesDataObject);
            }
            else if(strID == XRIO_DEVICE_MODEL_ID_DEVICE_RESIDUALFACTORS)
            {
                UpdateDeviceModelInRioResidualFactors(pSrcDataObject,pDesDataObject);
            }
            else if(strID == XRIO_DEVICE_MODEL_ID_DEVICE_LIMITS)
            {
                UpdateDeviceModelInRioLimits(pSrcDataObject,pDesDataObject);
            }
            else if(strID == XRIO_DEVICE_MODEL_ID_DEVICE_MISC)
            {
                UpdateDeviceModelInRioMisc(pSrcDataObject,pDesDataObject);
            }
            else if(strID == XRIO_DEVICE_MODEL_ID_TRIPTIME)
            {
                UpdateDeviceModelInRioTripTime(pSrcDataObject,pDesDataObject);
            }
            else if(strID == XRIO_DEVICE_MODEL_ID_CLOSETIME)
            {
                UpdateDeviceModelInRioCloseTime(pSrcDataObject,pDesDataObject);
            }
            else if(strID == XRIO_DEVICE_MODEL_ID_P52AB)
            {
                UpdateDeviceModelInRioP52AB(pSrcDataObject,pDesDataObject);
            }
            return TRUE;
        }
    }
    return FALSE;
}

BOOL CXrioToDeviceModelTool::UpdateRioDeviceValueObject(CDvmData *pSrcDataObject, CDvmData *pDesDataObject,const CString &strID)
{
    CDvmValue *pSrcValueObject = NULL;
    CDvmValue *pDesValueObject = NULL;

    CString strTempIDPath = GetObjectIDPath(pDesDataObject->m_strID,strID);
    pSrcValueObject = (CDvmValue*)pSrcDataObject->FindByID(strTempIDPath);
    pDesValueObject = (CDvmValue*)pDesDataObject->FindByID(strTempIDPath);
    if(pSrcValueObject != NULL)
    {
        if(pDesValueObject != NULL)
        {
            pDesValueObject->m_strName = pSrcValueObject->m_strName;
            pDesValueObject->m_strID = pSrcValueObject->m_strID;
            pDesValueObject->m_strDataType = pSrcValueObject->m_strDataType;
            pDesValueObject->m_strValue = pSrcValueObject->m_strValue;
            return TRUE;
        }
    }
    return FALSE;
}

BOOL CXrioToDeviceModelTool::UpdateRioCBConfigValueObject(CDvmData *pSrcDataObject, CDvmData *pDesDataObject)
{
    pDesDataObject->m_strName = pSrcDataObject->m_strName;
    pDesDataObject->m_strID = pSrcDataObject->m_strID;
    pDesDataObject->m_strDataType = pSrcDataObject->m_strDataType;
    pDesDataObject->m_strValue = pSrcDataObject->m_strValue;
    pDesDataObject->m_strUnit = pSrcDataObject->m_strUnit;
    pDesDataObject->m_strMax = pSrcDataObject->m_strMax;
    pDesDataObject->m_strMin = pSrcDataObject->m_strMin;
    UpdateAdditionalAttributes(pSrcDataObject,pDesDataObject,XRIO_DEVICE_MODEL_ID_Description);
    UpdateAdditionalAttributes(pSrcDataObject,pDesDataObject,XRIO_DEVICE_MODEL_ID_ValueFormula);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::AddParameterValue(CXrioCustomParameter *pXrioCustomParameter, CDvmData *pData)
{
    //2024-9-29如果存在CXrioEnumList链表，会存在多个值。其实是数据类型为枚举才这种情况，现在改为根据具体的数据类型进行判断。
    //DataType在进入该函数之前已经被赋值。
    //对于Data节点存在m_strDefaultValue默认值属性，当前不确定该属性是否适合作为参考值进行存储，直接增加一个参考值节点。
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_RefValue);

    if(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN == pData->m_strDataType)
    {
        //布尔类型默认参考值为false
        pData->AddValue(XRIO_DEVICE_MODEL_ID_RefValue,strTempIDPath,XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN,_T("false"));
        return TRUE;
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_STRING == pData->m_strDataType || XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == pData->m_strDataType || XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == pData->m_strDataType)
    {
        //字符串类型，double类型，int类型默认值参考值为_T("")
        pData->AddValue(XRIO_DEVICE_MODEL_ID_RefValue,strTempIDPath,pData->m_strDataType,XRIO_DEVICE_MODEL_DEFAULTVALUE);
        return TRUE;
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pData->m_strDataType)
    {
        CXrioEnumList *pCXrioEnumList = NULL;
        CXrioEnumValue *pXrioEnumValue = NULL;
        CExBaseObject *pSubObj= NULL;
        pCXrioEnumList = (CXrioEnumList*)pXrioCustomParameter->FindByClassID(XRIOCLASSID_ENUMLIST);
        if(pCXrioEnumList != NULL)
        {
            POS pos_EnumValue = pCXrioEnumList->GetHeadPosition();
            while(pos_EnumValue)
            {
                pSubObj = pCXrioEnumList->GetNext(pos_EnumValue);
                if(pSubObj->GetClassID() == XRIOCLASSID_ENUMVALUE)
                {
                    pXrioEnumValue = (CXrioEnumValue*)pSubObj;
                    strTempIDPath = GetObjectIDPath(pData->m_strID,pXrioEnumValue->m_strEnumId);
                    CDvmValue *pCDvmValue = pData->AddValue(GetTrimValue(pXrioEnumValue->m_strName),strTempIDPath,XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION,GetTrimValue(pXrioEnumValue->m_strName));
                }
            }
        }
        //枚举类型的默认参考值为_T("")
        strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_RefValue);
        pData->AddValue(XRIO_DEVICE_MODEL_ID_RefValue,strTempIDPath,pData->m_strDataType,XRIO_DEVICE_MODEL_DEFAULTVALUE);
        return TRUE;
    }
    else
    {
        //如果存在其他类型当前暂时不处理。
        return FALSE;
    }
}

BOOL CXrioToDeviceModelTool::ParseXrioRioDevice(CDvmLogicDevice *pSrcLogicDevice, CExBaseObject *pObj)
{
    CExBaseObject *pSubObj = NULL;
    if(pObj->GetClassID() == XRIOCLASSID_DEVICE)
    {
        CRioDevice *pRioDevice = (CRioDevice*)pObj;
        //group节点DEVICE
        CDvmDataset *pCDvmDataset = (CDvmDataset*)pSrcLogicDevice->CreateNewChild(DVMCLASSID_CDVMDATASET);
        pSrcLogicDevice->AddNewChild(pCDvmDataset);
        pCDvmDataset->m_strName = GetTrimValue(pRioDevice->m_strBlockType);
        pCDvmDataset->m_strID = GetTrimValue(pRioDevice->m_strBlockType);
        pCDvmDataset->m_strDataType = GetTrimValue(pRioDevice->m_strType);

        POS DevicePos = pRioDevice->GetHeadPosition();
        CRioNameplate *pRioNameplate = NULL;
        CRioLocation *pRioLocation = NULL;
        CRioNominalValues *pRioNominalValues = NULL;
        CRioResidualFactors *pRioResidualFactors = NULL;
        CRioLimits *pRioLimits = NULL;
        CRioMisc *pRioMisc = NULL;

        while (DevicePos)
        {
            pSubObj = pRioDevice->GetNext(DevicePos);
            if (pSubObj->GetClassID() == XRIOCLASSID_NAMEPLATE)
            {
                pRioNameplate = (CRioNameplate*)pSubObj;
                CDvmData* pChildData = pCDvmDataset->AddNewData(GetTrimValue(pRioNameplate->m_strBlockType), GetTrimValue(pRioNameplate->m_strBlockType), GetTrimValue(pRioNameplate->m_strType), XRIO_DEVICE_MODEL_DEFAULTVALUE);
                ParseXrioRioDeviceNamePlate(pRioNameplate, pChildData);
            }
            else if (pSubObj->GetClassID() == XRIOCLASSID_LOCATION)
            {
                pRioLocation = (CRioLocation*)pSubObj;
                CDvmData* pChildData = pCDvmDataset->AddNewData(GetTrimValue(pRioLocation->m_strBlockType), GetTrimValue(pRioLocation->m_strBlockType), GetTrimValue(pRioLocation->m_strType), XRIO_DEVICE_MODEL_DEFAULTVALUE);
                ParseXrioRioDeviceLocation(pRioLocation, pChildData);
            }
            else if (pSubObj->GetClassID() == XRIOCLASSID_NOMINALVALUES)
            {
                pRioNominalValues = (CRioNominalValues*)pSubObj;
                CDvmData* pChildData = pCDvmDataset->AddNewData(GetTrimValue(pRioNominalValues->m_strBlockType), GetTrimValue(pRioNominalValues->m_strBlockType), GetTrimValue(pRioNominalValues->m_strType), XRIO_DEVICE_MODEL_DEFAULTVALUE);
                ParseXrioRioDeviceNominalValues(pRioNominalValues, pChildData);
            }
            else if (pSubObj->GetClassID() == XRIOCLASSID_RESIDUALFACTORS)
            {
                pRioResidualFactors = (CRioResidualFactors*)pSubObj;
                CDvmData* pChildData = pCDvmDataset->AddNewData(GetTrimValue(pRioResidualFactors->m_strBlockType), GetTrimValue(pRioResidualFactors->m_strBlockType), GetTrimValue(pRioResidualFactors->m_strType), XRIO_DEVICE_MODEL_DEFAULTVALUE);
                ParseXrioRioDeviceResiDualfactors(pRioResidualFactors, pChildData);
            }
            else if (pSubObj->GetClassID() == XRIOCLASSID_LIMITS)
            {
                pRioLimits = (CRioLimits*)pSubObj;
                CDvmData* pChildData = pCDvmDataset->AddNewData(GetTrimValue(pRioLimits->m_strBlockType), GetTrimValue(pRioLimits->m_strBlockType), GetTrimValue(pRioLimits->m_strType), XRIO_DEVICE_MODEL_DEFAULTVALUE);
                ParseXrioRioDeviceLimits(pRioLimits, pChildData);
            }
            else if (pSubObj->GetClassID() == XRIOCLASSID_MISC)
            {
                pRioMisc = (CRioMisc*)pSubObj;
                CDvmData* pChildData = pCDvmDataset->AddNewData(GetTrimValue(pRioMisc->m_strBlockType), GetTrimValue(pRioMisc->m_strBlockType), GetTrimValue(pRioMisc->m_strType), XRIO_DEVICE_MODEL_DEFAULTVALUE);
                ParseXrioRioDeviceMisc(pRioMisc, pChildData);
            }
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CXrioToDeviceModelTool::AddParameterValueFormula(CXrioCustomParameter *pXrioCustomParameter, CDvmData *pData)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_ValueFormula);
    pData->AddValue(XRIO_DEVICE_MODEL_ID_ValueFormula,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,GetTrimValue(pXrioCustomParameter->m_strValueFormula));
    return TRUE;
}

BOOL CXrioToDeviceModelTool::AddParameterValueFormula(CXrioCustomParameter *pXrioCustomParameter, CDvmValue *pValue)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_ValueFormula);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_ValueFormula,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,GetTrimValue(pXrioCustomParameter->m_strValueFormula));
    return TRUE;
}

BOOL CXrioToDeviceModelTool::AddParameterUnitDecimalPlaces(CXrioCustomParameter *pXrioCustomParameter, CDvmData *pData)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);
    //2024-10-15修改单位小数点位数，根据数据类型进行初始化。
    CString strUnitDecPlacesValue = GetTrimValue(pXrioCustomParameter->m_strDecimalPlaces);
    InitUnitDecPlacesByDataType(strUnitDecPlacesValue,pData->m_strDataType);
    pData->AddValue(XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,strUnitDecPlacesValue);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::AddParameterUnitDecimalPlaces(CXrioCustomParameter *pXrioCustomParameter, CDvmValue *pValue)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);
    //2024-10-15修改单位小数点位数，根据数据类型进行初始化。
    CString strUnitDecPlacesValue = GetTrimValue(pXrioCustomParameter->m_strDecimalPlaces);
    InitUnitDecPlacesByDataType(strUnitDecPlacesValue,pValue->m_strDataType);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,strUnitDecPlacesValue);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::AddParameterForeignId(CXrioCustomParameter *pXrioCustomParameter, CDvmData *pData)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_ForeignId);
    pData->AddValue(GetTrimValue(pXrioCustomParameter->m_strForeignId),strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,GetTrimValue(pXrioCustomParameter->m_strForeignId));
    //txt文件更新时候会通过ForeignId的值进行查找
    return TRUE;
}

BOOL CXrioToDeviceModelTool::AddParameterForeignId(CXrioCustomParameter *pXrioCustomParameter, CDvmValue *pValue)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_ForeignId);
    pValue->AddValue(GetTrimValue(pXrioCustomParameter->m_strForeignId),strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,GetTrimValue(pXrioCustomParameter->m_strForeignId));
    //txt文件更新时候会通过ForeignId的值进行查找
    return TRUE;
}

BOOL CXrioToDeviceModelTool::AddParameterDescription(CXrioCustomParameter *pXrioCustomParameter, CDvmData *pData)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pData->m_strID,XRIO_DEVICE_MODEL_ID_Description);
    pData->AddValue(XRIO_DEVICE_MODEL_ID_Description,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,GetTrimValue(pXrioCustomParameter->m_strDescription));
    return TRUE;
}

BOOL CXrioToDeviceModelTool::AddParameterDescription(CXrioCustomParameter *pXrioCustomParameter, CDvmValue *pValue)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_Description);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_Description,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,GetTrimValue(pXrioCustomParameter->m_strDescription));
    return TRUE;
}

BOOL CXrioToDeviceModelTool::AddParameterValue(CXrioCustomParameter *pXrioCustomParameter, CDvmValue *pValue)
{
    //2024-9-29如果存在CXrioEnumList链表，会存在多个值。其实是数据类型为枚举才这种情况，现在改为根据具体的数据类型进行判断。
    //DataType在进入该函数之前已经被赋值。
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_RefValue);

    if(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN == pValue->m_strDataType)
    {
        //布尔类型默认参考值为false
        pValue->AddValue(XRIO_DEVICE_MODEL_ID_RefValue,strTempIDPath,XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN,_T("false"));
        return TRUE;
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_STRING == pValue->m_strDataType || XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == pValue->m_strDataType || XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == pValue->m_strDataType)
    {
        //字符串类型，double类型，int类型默认值参考值为_T("")
        pValue->AddValue(XRIO_DEVICE_MODEL_ID_RefValue,strTempIDPath,pValue->m_strDataType,XRIO_DEVICE_MODEL_DEFAULTVALUE);
        return TRUE;
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pValue->m_strDataType)
    {
        CXrioEnumList *pCXrioEnumList = NULL;
        CXrioEnumValue *pXrioEnumValue = NULL;
        CExBaseObject *pSubObj= NULL;
        pCXrioEnumList = (CXrioEnumList*)pXrioCustomParameter->FindByClassID(XRIOCLASSID_ENUMLIST);
        if(pCXrioEnumList != NULL)
        {
            POS pos_EnumValue = pCXrioEnumList->GetHeadPosition();
            while(pos_EnumValue)
            {
                pSubObj = pCXrioEnumList->GetNext(pos_EnumValue);
                if(pSubObj->GetClassID() == XRIOCLASSID_ENUMVALUE)
                {
                    pXrioEnumValue = (CXrioEnumValue*)pSubObj;
                    strTempIDPath = GetObjectIDPath(pValue->m_strID,pXrioEnumValue->m_strEnumId);
                    CDvmValue *pCDvmValue = pValue->AddValue(GetTrimValue(pXrioEnumValue->m_strName),strTempIDPath,XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION,GetTrimValue(pXrioEnumValue->m_strName));
                }
            }
        }
        //枚举类型的默认参考值为_T("")
        strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_RefValue);
        pValue->AddValue(XRIO_DEVICE_MODEL_ID_RefValue,strTempIDPath,pValue->m_strDataType,XRIO_DEVICE_MODEL_DEFAULTVALUE);
        return TRUE;
    }
    else
    {
        //如果存在其他类型当前暂时不处理。
        return FALSE;
    }
}

BOOL CXrioToDeviceModelTool::AddParameterUnit(CXrioCustomParameter *pXrioCustomParameter, CDvmValue *pValue)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_Unit);
    //2024-10-15修改单位，根据数据类型进行初始化。
    CString strUnitValue = GetTrimValue(pXrioCustomParameter->m_strUnit);
    InitUnitByDataType(strUnitValue,pValue->m_strDataType);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_Unit,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,strUnitValue);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::AddParameterMinValue(CXrioCustomParameter *pXrioCustomParameter, CDvmValue *pValue)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_MinValue);
    //2024-10-15修改最小值，根据数据类型进行初始化。
    CString strMinValue = GetTrimValue(pXrioCustomParameter->m_strMinValue);
    InitMinByDataType(strMinValue,pValue->m_strDataType,pValue);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_MinValue,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,strMinValue);
    return TRUE;
}

BOOL CXrioToDeviceModelTool::AddParameterMaxValue(CXrioCustomParameter *pXrioCustomParameter, CDvmValue *pValue)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pValue->m_strID,XRIO_DEVICE_MODEL_ID_MaxValue);
    //2024-10-15修改最大值，根据数据类型进行初始化。
    CString strMaxValue = GetTrimValue(pXrioCustomParameter->m_strMaxValue);
    InitMaxByDataType(strMaxValue,pValue->m_strDataType,pValue);
    pValue->AddValue(XRIO_DEVICE_MODEL_ID_MaxValue,strTempIDPath,XRIO_DEVICE_MODEL_DEFAULTVALUE,strMaxValue);
    return TRUE;
}

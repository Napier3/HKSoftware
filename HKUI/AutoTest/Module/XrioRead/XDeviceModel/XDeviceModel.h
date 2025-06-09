#pragma once
#include <float.h>
#include <cmath>
#include "../../../../Module/DataMngr/DvmDevice.h"
#include "../../../../AutoTest/Module/XrioRead/Xrio.h"
#include "../../../../AutoTest/Module/Characteristic/Characteristics.h"
#include "../../../../AutoTest/Module/Characteristic/CharacteristicLib.h"
//Custom
#define XRIO_DEVICE_MODEL_ID_CUSTOM                  _T("CUSTOM")
#define XRIO_DEVICE_MODEL_ID_ForeignId               _T("ForeignId")
#define XRIO_DEVICE_MODEL_ID_Description             _T("Description")
#define XRIO_DEVICE_MODEL_ID_Unit                    _T("Unit")
#define XRIO_DEVICE_MODEL_ID_MinValue                _T("MinValue")
#define XRIO_DEVICE_MODEL_ID_MaxValue                _T("MaxValue")
#define XRIO_DEVICE_MODEL_ID_ValueFormula            _T("ValueFormula")
#define XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces      _T("DecimalPlaces")//����Unit��λ��С����λ��
#define XRIO_DEVICE_MODEL_ID_RefValue                _T("RefValue")//���Ӳο�ֵ

//Rio
#define XRIO_DEVICE_MODEL_ID_RIO                     _T("RIO")

//DEVICE
#define XRIO_DEVICE_MODEL_ID_DEVICE                  _T("DEVICE")

#define XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE        _T("DEVICE_NAMEPLATE")
#define XRIO_DEVICE_MODEL_ID_DEVICE_MODEL            _T("DEVICE_MODEL")
#define XRIO_DEVICE_MODEL_ID_MANUFACTURER            _T("MANUFACTURER")
#define XRIO_DEVICE_MODEL_ID_DEVICE_TYPE             _T("DEVICE_TYPE")
#define XRIO_DEVICE_MODEL_ID_SERIALNR                _T("SERIALNR")
#define XRIO_DEVICE_MODEL_ID_ADDITIONAL_INFO2        _T("ADDITIONAL_INFO2")

#define XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION         _T("DEVICE_LOCATION")
#define XRIO_DEVICE_MODEL_ID_DEVICE_ADDRESS          _T("DEVICE_ADDRESS")
#define XRIO_DEVICE_MODEL_ID_SUBSTATION              _T("SUBSTATION")
#define XRIO_DEVICE_MODEL_ID_SUBSTATION_ADDRESS      _T("SUBSTATION_ADDRESS")
#define XRIO_DEVICE_MODEL_ID_BAY                     _T("BAY")
#define XRIO_DEVICE_MODEL_ID_BAY_ADDRESS             _T("BAY_ADDRESS")
#define XRIO_DEVICE_MODEL_ID_PROTECTED_OBJECT_NAME   _T("PROTECTED_OBJECT_NAME")

#define XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES    _T("DEVICE_NOMINALVALUES")
#define XRIO_DEVICE_MODEL_ID_PHASES                  _T("PHASES")
#define XRIO_DEVICE_MODEL_ID_FNOM                    _T("FNOM")
#define XRIO_DEVICE_MODEL_ID_VNOM                    _T("VNOM")
#define XRIO_DEVICE_MODEL_ID_VPRIM_LL                _T("VPRIM_LL")
#define XRIO_DEVICE_MODEL_ID_INOM                    _T("INOM")
#define XRIO_DEVICE_MODEL_ID_IPRIM                   _T("IPRIM")

#define XRIO_DEVICE_MODEL_ID_DEVICE_RESIDUALFACTORS  _T("DEVICE_RESIDUALFACTORS")
#define XRIO_DEVICE_MODEL_ID_VLNVN                   _T("VLNVN")
#define XRIO_DEVICE_MODEL_ID_ININOM                  _T("ININOM")

#define XRIO_DEVICE_MODEL_ID_DEVICE_LIMITS           _T("DEVICE_LIMITS")
#define XRIO_DEVICE_MODEL_ID_VMAX_LL                 _T("VMAX_LL")
#define XRIO_DEVICE_MODEL_ID_IMAX                    _T("IMAX")

#define XRIO_DEVICE_MODEL_ID_DEVICE_MISC             _T("DEVICE_MISC")
#define XRIO_DEVICE_MODEL_ID_DEBOUNCETIME            _T("DEBOUNCETIME")
#define XRIO_DEVICE_MODEL_ID_DEGLITCHTIME            _T("DEGLITCHTIME")
#define XRIO_DEVICE_MODEL_ID_OVERLOADSUPTIME         _T("OVERLOADSUPTIME")

//DISTANCE  ID OR NAME
#define XRIO_DEVICE_MODEL_ID_DISTANCE									_T("DISTANCE")
//DISTANCE  DATA-TYPE
#define XRIO_DEVICE_MODEL_DATA_TYPE_DISTANCE                            _T("DISTANCE-TYPE")

//DIFFERENTIAL  ID OR NAME
#define XRIO_DEVICE_MODEL_ID_DIFFERENTIAL								_T("DIFFERENTIAL")
//DIFFERENTIAL  DATA-TYPE
#define XRIO_DEVICE_MODEL_DATA_TYPE_DIFFERENTIAL                        _T("DIFFERENTIAL-TYPE")

//OVERCURRENT   ID OR NAME
#define XRIO_DEVICE_MODEL_ID_OVERCURRENT								_T("OVERCURRENT")
//OVERCURRENT   DATA-TYPE
#define XRIO_DEVICE_MODEL_DATA_TYPE_OVERCURRENT                         _T("OVERCURRENT-TYPE")

//CBCONFIGURATION
#define XRIO_DEVICE_MODEL_DATA_TYPE_CBCONFIGURATION  _T("CBCONFIGURATION-TYPE")//CB���ô��ڶ�����ڸ�Ϊ�����ж�
#define XRIO_DEVICE_MODEL_ID_CBCONFIGURATION         _T("CBCONFIGURATION")
#define XRIO_DEVICE_MODEL_ID_TRIPTIME                _T("TRIPTIME")
#define XRIO_DEVICE_MODEL_ID_CLOSETIME               _T("CLOSETIME")
#define XRIO_DEVICE_MODEL_ID_P52AB                   _T("P52AB")

//-----------------------------------------------------------------------------------------
//Rio�ļ���
#define RIO_DEVICE_MODEL_ID_NAME                        _T("NAME")
#define RIO_DEVICE_MODEL_ID_DEVICE_TYPE                 _T("DEVICE-TYPE")
#define RIO_DEVICE_MODEL_ID_SERIALNO                    _T("SERIALNO")
#define RIO_DEVICE_MODEL_ID_DEVICE_ADDRESS              _T("DEVICE-ADDRESS")
#define RIO_DEVICE_MODEL_ID_SUBSTATION_ADDRESS          _T("SUBSTATION-ADDRESS")
#define RIO_DEVICE_MODEL_ID_BAY_ADDRESS                 _T("BAY-ADDRESS")
#define RIO_DEVICE_MODEL_ID_PROTECTED_OBJECT_NAME       _T("PROTECTED-OBJECT-NAME")
#define RIO_DEVICE_MODEL_ID_VPRIM_LL                    _T("VPRIM-LL")
#define RIO_DEVICE_MODEL_ID_VMAX_LL                     _T("VMAX-LL")

//XrioCustomParameter��������
#define XRIO_CUSTOM_PARAMETER_DATATYPE_STRING            _T("String")
#define XRIO_CUSTOM_PARAMETER_DATATYPE_REAL              _T("Real")
#define XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION       _T("Enumeration")
#define XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER           _T("Integer")
#define XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN           _T("Boolean")

//��������ֵ
#define XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE      _T("true")
#define XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE     _T("false")
#define XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE_NUMERIC     _T("1")
#define XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE_NUMERIC    _T("0")

//Xrio�ļ��ĸ����ڵ㼤��״̬����������ʹ��
#define XRIO_DEVICE_MODEL_CHECK_ENABLED                   1
#define XRIO_DEVICE_MODEL_CHECK_DISENABLED                0

//С����Ĭ�Ͼ���Ϊ��2λ
#define XRIO_DEVICE_MODEL_UNIT_DEFAULT_DECIMALPLACES     _T("2")
#define XRIO_DEVICE_MODEL_PRECISION_COMPARE               1e-15

//20240-10-15���Ĭ��ֵ�Ƶ��˴�,��Ĭ��ֵΪ����ֵ����
#define XRIO_DEVICE_MODEL_DEFAULTVALUE                   _T("") //_T("---")Ĭ��ֵ�޸�Ϊ_T("") 2024-9-27
//��ֵ����Ĭ��ֵ
#define XRIO_DEVICE_MODEL_DEFAULT_NUMERIC_VALUE          _T("0")

//#define XRIO_DEVICE_MODEL_INF_STRING                     _T("inf")
#define XRIO_DEVICE_MODEL_POSITIVE_INF_STRING            _T("inf")
#define XRIO_DEVICE_MODEL_NEGATIVE_INF_STRING            _T("-inf")

#define XRIO_DEVICE_MODEL_POSITIVE_INF                   _T("+��")
#define XRIO_DEVICE_MODEL_NEGATIVE_INF                   _T("-��")

#define XRIO_DEVICE_MODEL_INT_MIN                        _T("-2147483648")
#define XRIO_DEVICE_MODEL_INT_MAX                        _T("2147483647")

// double���ͱȽϽ����ö������
enum DoubleCompareResult
{
    DOUBLE_EQUAL = 0,      // ��Ϊ���
    DOUBLE_GREATER = 1,    // p1 ���� p2
    DOUBLE_LESS = -1,      // p1 С�� p2
    DOUBLE_NAN_COMPARISON = -2 // ���� NaN
};
//������double�Ƚ�
inline DoubleCompareResult DoubleFuzzyCompare(double p1, double p2, double epsilon = XRIO_DEVICE_MODEL_PRECISION_COMPARE)
{
    // ����Ƿ�Ϊ NaN
#ifdef _PSX_QT_LINUX_
    // ����Ƿ�Ϊ NaN
    if (std::isnan(p1) || std::isnan(p2))
    {
        return DOUBLE_NAN_COMPARISON; // ָʾ���� NaN
    }
  // ����Ƿ�����������
    if (!std::isfinite (p1) || !std::isfinite (p2))
    {
        if (p1 == p2)
        {
            return DOUBLE_EQUAL; // ����������������������ڸ�����
        }
        // ������Ҫ���ڸ�����
        return (p1 > p2) ? DOUBLE_GREATER : DOUBLE_LESS;
    }
#else
    // ����Ƿ�Ϊ NaN
    if (/*isnan*/_isnan(p1) || /*isnan*/_isnan(p2))
    {
        return DOUBLE_NAN_COMPARISON; // ָʾ���� NaN
    }

    // ����Ƿ�����������
    if (/*isinf*/!_finite (p1) || /*isinf*/!_finite (p2))
    {
        if (p1 == p2)
        {
            return DOUBLE_EQUAL; // ����������������������ڸ�����
        }
        // ������Ҫ���ڸ�����
        return (p1 > p2) ? DOUBLE_GREATER : DOUBLE_LESS;
    }
#endif

    // ģ���Ƚ�
    if (fabs(p1 - p2) <= epsilon * /*fmin*/min(fabs(p1), fabs(p2)))
    {
        return DOUBLE_EQUAL; // ��Ϊ���
    }

    // ���ش�С�ȽϽ��
    return (p1 > p2) ? DOUBLE_GREATER : DOUBLE_LESS;
}
//���ȥ��ֵ���˿հ׺��ֵ
inline CString GetTrimValue(const CString& strValue)
{
    CString trimmedStr = strValue;
    trimmedStr.Trim();
    return trimmedStr;
}
//��ö���ID·��
inline CString GetObjectIDPath(const CString& strObjectID,const CString& strID)
{
    CString strTempIDPath;
    strTempIDPath.Format(_T("%s$%s"),strObjectID.GetString(),strID.GetString());
    return strTempIDPath;
}
//��ö�����ӵ����Զ���
inline CExBaseObject* GetAttrObj(CExBaseObject *pObj,const CString &strID)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pObj->m_strID,strID);
    CExBaseObject *pAttrObj = ((CExBaseList*)pObj)->FindByID(strTempIDPath);
    return pAttrObj;
}
//�ָ��
inline void SplitCStringToArray(const CString& input, CStringArray& output, TCHAR delimiter = '.')
{
    output.RemoveAll();
    int startPos = 0;
    int delimPos;
    // ѭ��ֱ���Ҳ����ָ���
    while ((delimPos = input.Find(delimiter, startPos)) != -1)
    {
        // ��ȡ�ָ���֮ǰ�����ַ���
        CString token = input.Mid(startPos, delimPos - startPos);
        // ��ӵ�������
        output.Add(token);

        // ������ʼλ���������Ѵ���ķָ���
        startPos = delimPos + 1;
    }
    // ������һ�����ַ���������ַ����Էָ����������򲻻���ӵ������У�
    if (startPos < input.GetLength())
    {
        CString lastToken = input.Mid(startPos);
        output.Add(lastToken);
    }
}
//��ȡ�ַ��������һ��$���ź�����ַ���
inline CString GetStringAfterLastDollar(const CString& input)
{
    int pos = input.ReverseFind('$'); // �ҵ����һ�� $ ��λ��
    if (pos != -1)
    {
        return input.Right(input.GetLength() - pos - 1); // ��ȡ $ ������ַ���
    }
//    return CString(""); // ���û���ҵ� $�����ؿ��ַ���
    return input;
}
//CExBaseObject���е�GetIDPathEx�����нṹ������ȫ���㣬�������·�����
inline CString GetObjIDPathEx(UINT nRootClassID, CExBaseObject *pObj, BOOL bHasRoot=TRUE, const CString &strSeperator=_T("$"))
{
    if(NULL == pObj)
    {
        return XRIO_DEVICE_MODEL_DEFAULTVALUE;
    }

    if(DVMCLASSID_CDVMDATA != pObj->GetClassID() && DVMCLASSID_CDVMVALUE != pObj->GetClassID())
    {
        return XRIO_DEVICE_MODEL_DEFAULTVALUE;
    }

    if(DVMCLASSID_CDVMDATA == pObj->GetClassID())
    {
        return pObj->GetIDPathEx(nRootClassID,bHasRoot,strSeperator);
    }

    //DVMCLASSID_CDVMVALUE == pObj->GetClassID()
    CString strPath;
    CExBaseObject *pParent = pObj;

    while(pParent)
    {
        if(DVMCLASSID_CDVMDATA == pParent->GetClassID())
        {
            pParent = (CExBaseObject *)pParent->GetParent();
            break;
        }

        pParent = (CExBaseObject *)pParent->GetParent();
    }

    strPath.Format(_T("%s$%s"),pParent->GetIDPathEx(nRootClassID,bHasRoot,strSeperator).GetString(),pObj->m_strID.GetString());

    return strPath;
}

class CXDeviceModel
{

public:
    CXDeviceModel();
    virtual ~CXDeviceModel();
    BOOL GetCharacteristics(CCharacteristics *pCharacteristics,CDvmDataset *pSelectDataset);
    CCharacterFolder* SetCharacteristics(CCharacteristics *pCharacteristics,CDvmDataset *pSelectDataset);
    //CDvmDevice
    CDvmDevice* m_pDvmDevice_Global;//��Ӧȫ�ֵ��豸����ģ��ָ��
	//�ڽ�������޸ģ�����Xrio�ļ�����󣬵��ȷ�Ϻ󣬲Ž�m_pDvmDevice_Show���µ�m_pDvmDevice_Global
	CDvmDevice* m_pDvmDevice_Show;//��ǰ������ʾʹ�õ��豸����ģ��ָ��
	CCharacteristicLib m_oCharacterLib_Global;
    CCharacteristicLib m_oCharacterLib_Show;

public:
	void InitDvmDevice(CDvmDevice* pDvmDevice_Global);
	void UpdateDvmRef();//���¿���ָ��ָ��,ָ��m_pDvmDevice_Show����
    CDvmDataset* GetDeviceAttrs();
    CDvmDataset* GetCBConfig();
	CDvmData* GetDeviceAttrsDataByID(const CString &strID);
	CDvmData* GetCBConfigDataByID(const CString &strID);
    CXrio m_oXrio;

protected:
	CDvmLogicDevice *m_pRioDatasets;
	CDvmDataset *m_pCBConfig_Dataset;
	CDvmDataset *m_pDeviceAttrs;
};


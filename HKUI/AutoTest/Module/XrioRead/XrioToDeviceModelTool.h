#pragma once
#include "RioDevice.h"
#include "XrioListCfg.h"
#include "XrioObjectCfg.h"
#include "XrioCustomBlock.h"
#include "XrioCustomParameter.h"
#include "../../Module/XrioRead/XDeviceModel/XDeviceModel.h"
#include "../XLanguageResourceAts.h"
class CXrioToDeviceModelTool
{
public:
    CXrioToDeviceModelTool();
    virtual ~CXrioToDeviceModelTool();
	//���غ���
public:
    BOOL XrioToDeviceModel(CXrio* pXrio, CDvmDevice* pDvmDevice);//Xrioת��ΪDeviceModel����
    //�����ļ�csv��txt��set�ļ����ӡ������ĸ�����������ǵ�ǰ�����xrio�ļ����µĻ��ݲ����Ǵ�ӡ��������������
    BOOL UpdateDeviceModelByXrioFile(CXrio* pXrio, CDvmDevice* pDvmDevice);//����Xrio�ļ���ͬ���������Ӧת����DeviceModel����
    BOOL IsXrioDataset_Device(CExBaseObject *pCurrObj);//�жϴ���ڵ��Ƿ�ΪDevice����
	BOOL IsXrioDataset_CBCONFIGURATION(CExBaseObject *pCurrObj);//�жϴ���ڵ��Ƿ�ΪCBCONFIGURATION����
	BOOL IsXrioDataset_Characteristic(CExBaseObject *pCurrObj);//�жϴ���ڵ��Ƿ�Ϊ�������߶���
private:
    //��ʼ�� �������ͣ�ֵ����λ����λС����λ������Сֵ�����ֵ
    void InitDataType(CString& strDataType, CExBaseObject *pObj);
    void InitValueByDataType(CString& strValue, const CString& strDataType, CExBaseList *pList);
    void InitUnitByDataType(CString& strUnitValue ,const CString& strDataType);
    void InitUnitDecPlacesByDataType(CString& strUnitDecPlacesValue ,const CString& strDataType);
    void InitMinByDataType(CString& strMinValue ,const CString& strDataType, CExBaseObject *pObj);
    void InitMaxByDataType(CString& strMaxValue ,const CString& strDataType, CExBaseObject *pObj);
    void InitDvmDataAttrNormalize(CDvmData *pData);
    void InitDvmValueAttrNormalize(CDvmValue *pValue);

	//���Ӿ��롢�����ʱ��Dataset�ڵ�
	BOOL AddCharacteristicNode(CDvmLogicDevice *pSrcLogicDevice,CExBaseObject* pObj);
    BOOL InitCharacterNodeAttr(CDvmDataset *pCDvmDataset,CExBaseObject* pObj);
    BOOL InitCharacterNodeAttrWithKey(CDvmDataset *pCDvmDataset,const CString& strIDValue,const CString& strDataType,CExBaseObject* pObj);
    BOOL InitAttr(CString &strDesAttrID, const CString &strDesAttrValue, const CString &strSrcAttrValue);
    //XrioToDeviceModel
    BOOL ParseXrioCustomBlock(CXrioCustomBlock* pXrioCustomBlock,CDvmDataset *pDataset);//����XRIO�ļ�CUSTOM�ڵ���Block����
    BOOL ParseXrioCustomParameter(CXrioCustomBlock* pXrioCustomBlock,CDvmData *pData);//����XRIO�ļ�CUSTOM�ڵ���Parameter����
    BOOL RecursionXrioCustomParameter(CXrioCustomBlock *pChildXrioCustomBlock, CDvmValue *pValue);//�ݹ����XRIO�ļ�CUSTOM�ڵ���Parameter����
    BOOL SupplementEmptyNodeAttributes(CDvmValue *pValue);

    BOOL AddParameterForeignId(CXrioCustomParameter* pXrioCustomParameter,CDvmData *pData);//����Data�ڵ��ForeignId����
    BOOL AddParameterForeignId(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//����Value�ڵ��ForeignId����
    BOOL AddParameterDescription(CXrioCustomParameter* pXrioCustomParameter,CDvmData *pData);//����Data�ڵ��Description����
    BOOL AddParameterDescription(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//����Value�ڵ��Description����

    BOOL AddParameterUnit(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//����Value�ڵ��Unit����
    BOOL AddParameterMinValue(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//����Value�ڵ��Min����
    BOOL AddParameterMaxValue(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//����Value�ڵ��Max����

    BOOL AddParameterValueFormula(CXrioCustomParameter* pXrioCustomParameter,CDvmData *pData);//����Data�ڵ��ValueFormula����
    BOOL AddParameterValueFormula(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//����Value�ڵ��ValueFormula����

    //2024-9-27����С����λ���ڵ�,�ýڵ����Ӳ�Ӱ��֮ǰ�����ݡ�
    BOOL AddParameterUnitDecimalPlaces(CXrioCustomParameter* pXrioCustomParameter,CDvmData *pData);//����Data�ڵ��Unit���Զ�Ӧ��С����λ��
    BOOL AddParameterUnitDecimalPlaces(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//����Value�ڵ��Unit���Զ�Ӧ��С����λ��

    BOOL AddParameterValue(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//����Value�ڵ�Ĳο�ֵ����
    BOOL AddParameterValue(CXrioCustomParameter* pXrioCustomParameter,CDvmData *pData);//����Data�ڵ�Ĳο�ֵ����

    //XRIO_RIO_DEVICE ����Rio�ڵ���Device�ڵ��DeviceNamePlate DeviceLocation DeviceNominalValues DeviceResiDualfactors DeviceLimits DeviceMisc����
    BOOL ParseXrioRioDevice(CDvmLogicDevice *pSrcLogicDevice,CExBaseObject* pObj);
    BOOL ParseXrioRioDeviceNamePlate(CRioNameplate *pRioNameplate,CDvmData *pData);//DeviceNamePlate
    BOOL ParseXrioRioDeviceLocation(CRioLocation *pRioLocation,CDvmData *pData);//DeviceLocation
    BOOL ParseXrioRioDeviceNominalValues(CRioNominalValues *pRioNominalValues,CDvmData *pData);//DeviceNominalValues
    BOOL ParseXrioRioDeviceResiDualfactors(CRioResidualFactors *pRioResidualFactors,CDvmData *pData);//DeviceResiDualfactors
    BOOL ParseXrioRioDeviceLimits(CRioLimits *pRioLimits,CDvmData *pData);//DeviceLimits
    BOOL ParseXrioRioDeviceMisc(CRioMisc *pRioMisc,CDvmData *pData);//DeviceMisc

    //XRIO_RIO_CB ����Rio�ڵ���CB�ڵ��Triptime Closetime P52AB����
    BOOL ParseXrioRioCBConfiguration(CDvmLogicDevice *pSrcLogicDevice, CExBaseObject* pObj);
    BOOL ParseXrioRioCBConfigurationTriptime(CRioTripTime *pRioTripTime,CDvmData *pData);
    BOOL ParseXrioRioCBConfigurationClosetime(CRioCloseTime *pRioCloseTime,CDvmData *pData);
    BOOL ParseXrioRioCBConfigurationP52AB(CRioP52AB *pRioP52AB,CDvmData *pData);

    //UpdateDeviceModelByXrioFile
    BOOL UpdateDeviceModelInDvmDataset(CDvmDataset *pSrcDataset,CDvmDataset *pDesDataset);//����Xrio�ļ�����Dataset�ڵ��в���
    BOOL UpdateDeviceModelInDvmData(CDvmData *pSrcDvmData,CDvmData *pDesDvmData);//����Xrio�ļ�����Data�ڵ��в���
    BOOL UpdateDeviceModelInDvmValue(CDvmValue *pSrcDvmValue,CDvmValue *pDesDvmValue);//����Xrio�ļ�����Value�ڵ��в���
    BOOL AddAdditionalAttributes(CDvmValue* pSrcValue,CDvmValue* pDesValue,const CString& strID);
    BOOL AddMultipleValues(CDvmValue* pSrcValue,CDvmValue* pDesValue,const CString& strID);

    //UpdateDeviceModelInRioDevice ����Xrio�ļ�����RIO�ڵ��Device�ڵ��в���
    BOOL UpdateDeviceModelInRioDevice(CDvmDataset *pSrcRioDevice,CDvmDataset *pDesRioDevice);
    BOOL UpdateDeviceModelInRioNameplate(CDvmData *pSrcRioNameplate,CDvmData *pDesRioNameplate);
    BOOL UpdateDeviceModelInRioLocation(CDvmData *pSrcRioLocation,CDvmData *pDesRioLocation);
    BOOL UpdateDeviceModelInRioNominalValues(CDvmData *pSrcRioNominalValues,CDvmData *pDesRioNominalValues);
    BOOL UpdateDeviceModelInRioResidualFactors(CDvmData *pSrcRioResidualFactors,CDvmData *pDesRioResidualFactors);
    BOOL UpdateDeviceModelInRioLimits(CDvmData *pSrcRioLimits,CDvmData *pDesRioLimits);
    BOOL UpdateDeviceModelInRioMisc(CDvmData *pSrcRioMisc,CDvmData *pDesRioMisc);
    //UpdateDeviceModelInRioCBConfig ����Xrio�ļ�����RIO�ڵ��CB�ڵ��в���
    BOOL UpdateDeviceModelInRioCBConfig(CDvmDataset *pSrcRioCBConfig,CDvmDataset *pDesRioCBConfig);
    BOOL UpdateDeviceModelInRioTripTime(CDvmData *pSrcRioTripTime,CDvmData *pDesRioTripTime);
    BOOL UpdateDeviceModelInRioCloseTime(CDvmData *pSrcRioCloseTime,CDvmData *pDesRioCloseTime);
    BOOL UpdateDeviceModelInRioP52AB(CDvmData *pSrcRioP52AB,CDvmData *pDesRioP52AB);

    BOOL IsFatherNode(CExBaseObject*pNode);
    BOOL UpdateOwnAttrVal(const CString& strSrcValue,CString& strDesValue);
    BOOL UpdateDataNode(CDvmData*pSrcDataNode,CDvmData*pDesDataNode);
    BOOL UpdateValueNode(CDvmValue*pSrcValueNode,CDvmValue*pDesValueNode);
    //���¸�������
    //�ú���ָ�����UpdateValue_DataType_Double��UpdateValue_DataType_Int
    typedef BOOL(CXrioToDeviceModelTool::*UPDATE_VALUE_DATATYPE_FUNC)(const CString&, CString&);
    BOOL UpdateAdditionalAttributes(CExBaseList* pSrcList, CExBaseList* pDesList, const CString& strID, BOOL bIsNormal = TRUE, UPDATE_VALUE_DATATYPE_FUNC pFunc = NULL);
    BOOL UpdateEnumerationValues(CExBaseList* pSrcList,CExBaseList* pDesList);
    BOOL UpdateValue_DataType_Double(const CString& strSrcValue ,CString& strDesValue);
    BOOL UpdateValue_DataType_Int(const CString& strSrcValue ,CString& strDesValue);


    BOOL UpdateCustomLogicDeviceObject(CDvmDevice *pSrcDeviceObject, CDvmDevice *pDesDeviceObject,const CString& strID);
    BOOL UpdateRioLogicDeviceObject(CDvmDevice *pSrcDeviceObject, CDvmDevice *pDesDeviceObject,const CString& strID);
    BOOL UpdateRioDatasetObject(CDvmLogicDevice *pSrcLogicDeviceObject,CDvmLogicDevice *pDesLogicDeviceObject,const CString& strID);
    BOOL UpdateRioDatasetObject(CDvmLogicDevice *pSrcLogicDeviceObject,CDvmLogicDevice *pDesLogicDeviceObject);


    BOOL UpdateRioDataObject(CDvmDataset *pSrcDatasetObject,CDvmDataset *pDesDatasetObject,const CString& strID);
    BOOL UpdateRioDeviceValueObject(CDvmData* pSrcDataObject,CDvmData* pDesDataObject,const CString &strID);
    BOOL UpdateRioCBConfigValueObject(CDvmData* pSrcDataObject,CDvmData* pDesDataObject);
};


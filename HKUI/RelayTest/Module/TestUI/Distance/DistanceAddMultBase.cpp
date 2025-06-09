#include "./DistanceAddMultBase.h"
#include "../../../../AutoTest/Module/Characteristic/Characteristics.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
extern void  Stt_Global_SettingParent(QWidget *parent);		//20240802 huangliang 

QDistanceAddMultBase::QDistanceAddMultBase(QWidget *parent) : QDialog(parent)
{
	Stt_Global_SettingParent(this);	//20240802 huangliang 
	m_pDistanceparas = NULL;
	m_pInitParas = NULL;
	m_pDataTypeLL = NULL;
	m_pDataTypeLN = NULL;
	InitUI();
}
QDistanceAddMultBase::~QDistanceAddMultBase()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
	if (m_pDataTypeLL != NULL)
	{
		m_pDataTypeLL->DeleteAll();
		delete m_pDataTypeLL;
		m_pDataTypeLL = NULL;
	}
	if (m_pDataTypeLN != NULL)
	{
		m_pDataTypeLN->DeleteAll();
		delete m_pDataTypeLN;
		m_pDataTypeLN = NULL;
	}
	if (m_pInitParas != NULL)
	{
		m_pInitParas->DeleteAll();
		delete m_pInitParas;
		m_pInitParas = NULL;
	}
}
void QDistanceAddMultBase::InitUI()
{

}
void QDistanceAddMultBase::SetValueToPage(CDvmData *pData)
{
	
}
void QDistanceAddMultBase::GetPageToValue(CDvmData *pData)
{

}
CString QDistanceAddMultBase::CheckDataMinMax(CString strValue,CString strID,float nMax,float nMin,int nAfterPoint)
{//20240613 luozibing 通过最大值 最小值 小数位数 检查输入框值是否格式正确
	CDvmData *pData = (CDvmData *)m_pDistanceparas->FindByID(strID);
	if(pData == NULL)
		return "";
	if (strValue == "")//输入框值为空时，值不改变
	{
		strValue = pData->m_strValue;
	}
	else//202740624 luozibing 保存对应ID数据
	{
		pData->m_strValue = strValue;
	}
	
	pData->m_strValue = CheckDataMinMax(strValue,nMax,nMin,nAfterPoint);
	return pData->m_strValue;
}
CString QDistanceAddMultBase::CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint)
{	
	float fvalue = strValue.toFloat();
	if (nMax != nMin)
	{
	if (fvalue<nMin)
	{
		fvalue = nMin;
	}
	else if (fvalue>nMax)
	{
		fvalue = nMax;
	}
	}
	return QString::number(fvalue,'f',nAfterPoint);
}
void QDistanceAddMultBase::GetDatas(CDataGroup *pParas)
{
	if (m_pDistanceparas == NULL)
	{
		return;
	}
	if (pParas == NULL)
	{//20241012 luozibing 传入参数为空 不保存当前界面设置
		m_pDistanceparas->DeleteAll();
		m_pDistanceparas->AppendCloneEx(*m_pInitParas);
		return;
	}
	POS posold = m_pDistanceparas->GetHeadPosition();
	while (posold != NULL)
	{
		CDvmData *pData = (CDvmData*)m_pDistanceparas->GetNext(posold);
		GetPageToValue(pData);
	}
	if (pParas != m_pDistanceparas)
	{
		pParas->DeleteAll();
		pParas->AppendCloneEx(*m_pDistanceparas);

		//CString strPath = this->windowTitle();
		//strPath += "_DeBug.xml";
		////20240614 luozibing 将页面数据保存到配置文件中 测试使用
		//dvm_IncGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
		//CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value(CDataMngrXmlRWKeys::g_pXmlKeys, 0x1FFFF);
		//pParas->SaveXmlFile(stt_ui_GetParasFile(strPath), CDataMngrXmlRWKeys::g_pXmlKeys);
		//CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value(CDataMngrXmlRWKeys::g_pXmlKeys, 0x1FFFF);
		//dvm_DecGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
	}
	m_pDistanceparas = NULL;
}
void QDistanceAddMultBase::SetDatas(CDataGroup *pDataset)
{//240612 luozibing 将传入的链表数据显示在页面上 
	if (pDataset == NULL)
		return;
	m_pDistanceparas = pDataset;

	if (m_pInitParas != NULL)
	{
		m_pInitParas->DeleteAll();
		delete m_pInitParas;
		m_pInitParas = NULL;
	}
	m_pInitParas = (CDataGroup*)pDataset->Clone();

	CheckAllPresence();
	UpdateCharacteristicParas();
	POS pos = pDataset->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)pDataset->GetNext(pos);
		SetValueToPage(pData);
	}
	MinCheckLeastOne();
}
void QDistanceAddMultBase::UpdateCharacteristicParas()
{//更新最新曲线参数[时间定值、绝对正负误差、相对误差]到链表
	if (m_pDistanceparas == NULL)
	{
		return;
	}
	CCharacteristics* pCharacteristics = stt_Frame_Characteristics();
	POS pos = pCharacteristics->GetHeadPosition();
	while (pos != NULL)
	{
		CExBaseObject *pObj = pCharacteristics->GetNext(pos);
		if (pObj->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;

		CCharacteristic *pCharTemp = (CCharacteristic *)pObj;
		//获取勾选使用的曲线
		if (pCharTemp->m_nUse != 1)
		{
			continue;
		}
		//根据曲线index和id得出对应链表参数id
		CString strTSetLL, strTSetLN, strRel, /*strLogic,*/ strPlus, strMinus, strCharID;
		int nZone = pCharTemp->m_strIndex.toInt();
		switch (nZone)
		{
		case STT_MULTI_MACRO_ZONE1:
			if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL)
			{
				strTSetLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1;
				strTSetLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1;
			}
			else if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_LL)
			{
				strTSetLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1;
			}
			else if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_LN)
			{
				strTSetLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1;
			}
			strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1;
			//strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1;
			strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1;
			strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1;
			break;
		case STT_MULTI_MACRO_ZONE2:
			if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL)
			{
				strTSetLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2;
				strTSetLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2;
			}
			else if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_LL)
			{
				strTSetLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2;
			}
			else if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_LN)
			{
				strTSetLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2;
			}
			strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2;
			//strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2;
			strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2;
			strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2;
			break;
		case STT_MULTI_MACRO_ZONE3:
			if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL)
			{
				strTSetLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3;
				strTSetLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3;
			}
			else if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_LL)
			{
				strTSetLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3;
			}
			else if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_LN)
			{
				strTSetLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3;
			}
			strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3;
			//strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3;
			strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3;
			strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3;
			break;
		case STT_MULTI_MACRO_ZONE4:
			if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL)
			{
				strTSetLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4;
				strTSetLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4;
			}
			else if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_LL)
			{
				strTSetLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4;
			}
			else if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_LN)
			{
				strTSetLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4;
			}
			strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4;
			//strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4;
			strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4;
			strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4;
			break;
		case STT_MULTI_MACRO_ZONE5:
			if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL)
			{
				strTSetLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5;
				strTSetLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5;
			}
			else if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_LL)
			{
				strTSetLL = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5;
			}
			else if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_LN)
			{
				strTSetLN = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5;
			}
			strRel = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5;
			//strLogic = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5;
			strPlus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5;
			strMinus = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5;
			break;
		}
		if (strRel == "")
		{//未找到对应链表
			continue;
		}
		//设置曲线对应参数到链表参数
		CExBaseList* pParas = (CExBaseList*)pCharTemp->GetCharInterface();
		POS posParas = m_pDistanceparas->GetHeadPosition();
		while (posParas != NULL)
		{
			CDvmData *pCheckZoneData = (CDvmData *)m_pDistanceparas->GetNext(posParas);
			if (pCheckZoneData->m_strID == strTSetLL || pCheckZoneData->m_strID == strTSetLN)//时间定值
			{
				CCharInterfaceVariable *pTSetPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);
				if (pTSetPara != NULL)
				{
					pCheckZoneData->m_strValue = pTSetPara->m_strValue;
					pCheckZoneData->m_strFormat = pCharTemp->m_strID;
				}				
			}
			else if (pCheckZoneData->m_strID == strRel)//相对误差
			{
				CCharInterfaceVariable *pRelPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR);
				if (pRelPara != NULL)
				{
					pCheckZoneData->m_strValue = pRelPara->m_strValue;
					pCheckZoneData->m_strFormat = pCharTemp->m_strID;
				}				
			}
			//20241012 luozibing 误差类型参数从特性曲线参数中移出
			//else if (pCheckZoneData->m_strID == strLogic)//误差类型
			//{
			//	CCharInterfaceVariable *pLogicPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC);
			//	if (pLogicPara != NULL)
			//	{
			//		pCheckZoneData->m_strValue = pLogicPara->m_strValue;
			//		pCheckZoneData->m_strFormat = pCharTemp->m_strID;
			//	}				
			//}
			else if (pCheckZoneData->m_strID == strPlus)//绝对正误差
			{
				CCharInterfaceVariable *pPlusPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS);
				if (pPlusPara != NULL)
				{
					pCheckZoneData->m_strValue = pPlusPara->m_strValue;
					pCheckZoneData->m_strFormat = pCharTemp->m_strID;
				}				
			}
			else if (pCheckZoneData->m_strID == strMinus)//绝对负误差
			{
				CCharInterfaceVariable *pMinusPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS);
				if (pMinusPara != NULL)
				{
					pCheckZoneData->m_strValue = pMinusPara->m_strValue;
					pCheckZoneData->m_strFormat = pCharTemp->m_strID;
				}				
			}
		}
		if (strTSetLL != "")
		{
			UpdateAddMultPageShow(nZone,false);
		}
		if (strTSetLN != "")
		{
			UpdateAddMultPageShow(nZone,true);
		}
	}
	InitPageShowByParas();
}
void QDistanceAddMultBase::UpdateAddMultPageShow(int nZone, bool bLN)
{
}
void QDistanceAddMultBase::InitPageShowByParas()
{//获取区段下拉框显示数据
	CString strLL, strLN;
	CString strTypeId = STT_MULTI_MACRO_PARAS_DATATYPE_ID_SystemZone;
	strTypeId += "_";
	strLL = strTypeId;
	strLL += "LL";
	strLN = strTypeId;
	strLN += "LN";
	if (m_pDataTypeLL != NULL)
	{
		m_pDataTypeLL->DeleteAll();
		delete m_pDataTypeLL;
		m_pDataTypeLL = NULL;
	}
	if (m_pDataTypeLN != NULL)
	{
		m_pDataTypeLN->DeleteAll();
		delete m_pDataTypeLN;
		m_pDataTypeLN = NULL;
	}
	m_pDataTypeLL = (CDataType *)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(strLL)->Clone();
	m_pDataTypeLN = (CDataType *)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(strLN)->Clone();

	//不存在区段1~5段 区段下拉框只显示线路长度
	if (m_pDataTypeLL->GetCount() == 2)
	{
		m_pDataTypeLL->DeleteTail();
	}
	if (m_pDataTypeLN->GetCount() == 2)
	{
		m_pDataTypeLN->DeleteTail();
	}
}
void QDistanceAddMultBase::MinCheckLeastOne()
{//检查check是否最少选中一个
}
void QDistanceAddMultBase::CheckAllPresence()
{//检查对应id参数是否存在 不存在则创建
	
}
void QDistanceAddMultBase::CheckForPresence(CString strID)
{
	//20240624 luozibing检查ID对应数据是否存在、不存在则添加
	if(m_pDistanceparas == NULL)
		return;
	CDvmData *pData = (CDvmData *)m_pDistanceparas->FindByID(strID);
	if(pData == NULL)
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strID;
		pNew->m_strID = strID;
		pNew->m_strValue = STT_MULTI_MACRO_DISTANCE_PARAS_ID_DEFAULT;
		m_pDistanceparas->AddNewChild(pNew);
	}
}
CString QDistanceAddMultBase::GetZsetByZAng(CString strZAng, int nZone, CString strFault)
{//根据阻抗角获取阻抗定值 
	double dZset = -1;
	int nFault;
	if (strFault == CHAR_DISTANCE_FAULT_TYPE_LL)
	{
		nFault = 3;
	}
	else
	{
		nFault = 0;
	}
	CString strTemp;
	strTemp.setNum(nZone);
	CString strNodeId = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZsetByZAng;
	strNodeId += "_";
	strNodeId += strFault;
	strNodeId += strTemp;
	CDvmData *pData = (CDvmData *)m_pDistanceparas->FindByID(strNodeId);
	if (pData == NULL)
	{
		pData = new CDvmData();
		pData->m_strID = strNodeId;
		pData->m_strFormat.setNum(STT_MULTI_MACRO_ZSet_MIN);
		m_pDistanceparas->AddNewChild(pData);
	}
	if (pData->m_strValue != strZAng)
	{//阻抗角改变 重新计算交点
		if (Global_GetZSettingValueFromCharacteristics(stt_Frame_Characteristics(), nZone, nFault, CString_To_double(strZAng), dZset))
		{
			//保存当前交点对应阻抗定值到参数
			pData->m_strValue = strZAng;
			if (fabs(CString_To_double(pData->m_strFormat) - dZset) > STT_MULTI_MACRO_ZSet_MIN)
			{//阻抗定值改变 更新阻抗定值参数
				pData->m_strFormat.setNum(dZset);
			}
		}
		return CheckDataMinMax(pData->m_strFormat, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3);
	}
	else
	{//阻抗角未改变 不需要更新阻抗定值参数
		return "";
	}
}
void QDistanceAddMultBase::UpdateErrorLogicValue(int nindex, int nZoneValue)
{//20241024 luozibing 根据cmb选择index与区段值 更新误差类型值
	CString strError;
	switch (nZoneValue)
	{
	case STT_MULTI_MACRO_ZONE1:
		strError = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC1;
		break;
	case STT_MULTI_MACRO_ZONE2:
		strError = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC2;
		break;
	case STT_MULTI_MACRO_ZONE3:
		strError = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC3;
		break;
	case STT_MULTI_MACRO_ZONE4:
		strError = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC4;
		break;
	case STT_MULTI_MACRO_ZONE5:
		strError = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC5;
		break;
	case STT_MULTI_MACRO_ZONELine:
		strError = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC6;
		break;
	case STT_MULTI_MACRO_ZONEAll:

		break;
	}
	//设置参数1值到 参数2对应参数 不设置最大值最小值且不保留小数
	CDvmData *pData = (CDvmData *)m_pDistanceparas->FindByID(strError);
	if (pData == NULL)
	{
		return;
	}
	pData->m_strValue.setNum(nindex);

}
CString QDistanceAddMultBase::GetZAngIDByZoneValue(int nZoneValue, CString strFault)
{//20241024 luozibing 根据区段值获取角阻抗对应id
	CString strZAng = "";
	if (strFault == CHAR_DISTANCE_FAULT_TYPE_LL)
	{
		switch (nZoneValue)
		{
		case STT_MULTI_MACRO_ZONE1:
			strZAng = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE1;
			break;
		case STT_MULTI_MACRO_ZONE2:
			strZAng = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE2;
			break;
		case STT_MULTI_MACRO_ZONE3:
			strZAng = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE3;
			break;
		case STT_MULTI_MACRO_ZONE4:
			strZAng = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE4;
			break;
		case STT_MULTI_MACRO_ZONE5:
			strZAng = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE5;
			break;
		case STT_MULTI_MACRO_ZONELine:
			strZAng = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLL_ZONE6;
			break;
		}
	}
	else if (strFault == CHAR_DISTANCE_FAULT_TYPE_LN)
	{
		switch (nZoneValue)
		{
		case STT_MULTI_MACRO_ZONE1:
			strZAng = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE1;
			break;
		case STT_MULTI_MACRO_ZONE2:
			strZAng = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE2;
			break;
		case STT_MULTI_MACRO_ZONE3:
			strZAng = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE3;
			break;
		case STT_MULTI_MACRO_ZONE4:
			strZAng = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE4;
			break;
		case STT_MULTI_MACRO_ZONE5:
			strZAng = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE5;
			break;
		case STT_MULTI_MACRO_ZONELine:
			strZAng = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANGLN_ZONE6;
			break;
		}
	}
	return strZAng;
}
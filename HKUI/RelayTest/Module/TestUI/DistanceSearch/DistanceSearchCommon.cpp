#include "DistanceSearchCommon.h"
#include "../../../../Module/TestMacro/TestMacro.h"
#include "../../../../Module/TestMacro/TestMacros.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"
#include "SttMultiMacroDistanceSearchParasDefine.h"
#include "../../../../AutoTest/Module/Characteristic/Characteristic.h"
#include "../../../../AutoTest/Module/Characteristic/Characteristics.h"
#include "../../Module/UI/SttTestCntrFrameApi.h"
#include <math.h>
#include <qmath.h>

CString DistanceSearchValueCheck(CString strValue,float nMax,float nMin,int nAfterPoint)
{	
	bool bOk = false;
	float fValue = strValue.toFloat(&bOk);

	if(!bOk)
    {
        fValue = 0;
        strValue.setNum(fValue);
    }

	if (fValue < nMin)
	{
		strValue.setNum(nMin);
	}
	if(fValue > nMax)
	{
		strValue.setNum(nMax);
	}

	int num = 0;
	int nPoint = strValue.indexOf(".");
	if(nPoint == -1)
	{
		if (strValue == "")
		{
			strValue = "0";
		}
		if(nAfterPoint>0)
			strValue += ".";
	}
	else
	{
		num = strValue.length()-nPoint-1;
		if (num > nAfterPoint)
		{
			if(nAfterPoint >0)
				strValue = strValue.left(nPoint + 1 + nAfterPoint);
			else
				strValue = strValue.left(nPoint + nAfterPoint);

			num = nAfterPoint;
		}
	}

	for (int i=num;i<nAfterPoint;i++)
	{
		strValue+="0";
	}

	return strValue;
}

void DistanceSearchCheckParaExist(CExBaseList *pParas,CString strID)
{
	if(pParas == NULL)
		return;

	CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pParas->FindByID(strID);
	if(pData == NULL)
	{
		CSttMacroTestParaData *pNew = new CSttMacroTestParaData();
		pNew->m_strName = STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_DEFAULT;
		pNew->m_strID = strID;
		pNew->m_strValue = STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_DEFAULT;
		pParas->AddNewChild(pNew);
	}
}

/*特性曲线添加测试项
返回值 是否可以添加测试项
参数1 故障类型(LN/LL/LLL)
参数2 起始点横坐标
参数3 起始点纵坐标
参数4 终点横坐标
参数5 终点纵坐标
参数6 首段阻抗数组(传出)
参数7 首段阻抗角数组(传出)
参数8 末端阻抗数组(传出)
参数9 末端阻抗角数组(传出)
参数10 区段数组(传出)
参数11 时间定值数组(传出)
参数12 相对误差数组(传出)
参数13 绝对误差数组(传出)
参数14 误差类型数组(传出)*/
BOOL CalDistanceSearchItemParas(CString strFaultType, double dBegX, double dBegY, double dEndX, double dEndY,
                                QVector<double> &dBegZArr, QVector<double> &dBegAngArr, QVector<double> &dEndZArr, QVector<double> &dEndAngArr,
                                QVector<int> &nZoneTypeArr, QVector<double> &dTSettingArr, QVector<double> &dRelErrArr, QVector<double> &dAbsErrArr,
                                QVector<int> &nErrTypeArr)
{
	CCharacteristic *pChar = NULL;
	CCharacteristics* pCharacteristics = stt_Frame_Characteristics();
	dBegZArr.clear();
	dBegAngArr.clear();
	dEndZArr.clear();
	dEndAngArr.clear();
	nZoneTypeArr.clear();

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
		if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL || pCharTemp->m_strID == strFaultType)
		{
			CExBaseList pTestLineList;
			bool bAdd = pCharTemp->GetIntersectTestLine(dBegX, dBegY, dEndX, dEndY, pTestLineList);
			if (!bAdd)
				continue;

            double dTSetting, dRelErr, dAbsErr;
            int nErrType;
            pChar = pCharTemp;
            CExBaseList* pParas = (CExBaseList*)pChar->GetCharInterface();
            CCharInterfaceVariable *pPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING);
            if (pPara != NULL)
            {
                dTSetting = pPara->m_strValue.toDouble();
            }

            pPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR);
            if (pPara != NULL)
            {
                dRelErr = pPara->m_strValue.toDouble();
            }

            pPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR);
            if (pPara != NULL)
            {
                dAbsErr = pPara->m_strValue.toDouble();
            }

            pPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC);
            if (pPara != NULL)
            {
                nErrType = CString_To_long(pPara->m_strValue);
            }

			POS pos = pTestLineList.GetHeadPosition();
			CCharTestLine *pLine = NULL;
			while (pos != NULL)
			{
				pLine = (CCharTestLine *)pTestLineList.GetNext(pos);
				if (pLine != NULL)
				{
					float fXb, fYb, fXe, fYe;
					double dZb, dAngb, dZe, dAnge;
					fXb = pLine->m_fXb;
					fYb = pLine->m_fYb;
					fXe = pLine->m_fXe;
					fYe = pLine->m_fYe;

					dZb = sqrt(fXb*fXb + fYb*fYb);
					dAngb = atan(fYb / fXb) * 180 / M_PI;
					if (fXb < 0)
						dAngb += 180;

					dZe = sqrt(fXe*fXe + fYe*fYe);
					dAnge = atan(fYe / fXe) * 180 / M_PI;
					if (fXe < 0)
						dAnge += 180;

					dBegZArr.push_back(dZb);
					dBegAngArr.push_back(dAngb);
					dEndZArr.push_back(dZe);
					dEndAngArr.push_back(dAnge);
					nZoneTypeArr.push_back(CString_To_long(pCharTemp->m_strIndex));
                    dTSettingArr.push_back(dTSetting);
                    dRelErrArr.push_back(dRelErr);
                    dAbsErrArr.push_back(dAbsErr);
                    nErrTypeArr.push_back(nErrType);
				}
			}
		}
	}

	if (dBegZArr.isEmpty())
		return FALSE;
	else
		return TRUE;
}

/*快速添加
返回值 是否可以添加测试项
参数1 故障类型(LN/LL/LLL)
参数2 起始点横坐标
参数3 起始点纵坐标
参数4 直线角度
参数5 首段阻抗数组(传出)
参数6 首段阻抗角数组(传出)
参数7 末端阻抗数组(传出)
参数8 末端阻抗角数组(传出)
参数9 区段数组(传出)
参数10 时间定值数组(传出)
参数11 相对误差数组(传出)
参数12 绝对误差数组(传出)
参数13 误差类型数组(传出)*/
BOOL CalDistanceSearchItemParas(CString strFaultType, double dBegX, double dBegY, double dAng,
                                QVector<double> &dBegZArr, QVector<double> &dBegAngArr, QVector<double> &dEndZArr, QVector<double> &dEndAngArr,
                                QVector<int> &nZoneTypeArr, QVector<double> &dTSettingArr, QVector<double> &dRelErrArr, QVector<double> &dAbsErrArr,
                                QVector<int> &nErrTypeArr)
{
	CCharacteristic *pChar = NULL;
	CCharacteristics* pCharacteristics = stt_Frame_Characteristics();
	dBegZArr.clear();
	dBegAngArr.clear();
	dEndZArr.clear();
	dEndAngArr.clear();
	nZoneTypeArr.clear();

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
		if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL || pCharTemp->m_strID == strFaultType)
		{
			CExBaseList pTestLineList;
			bool bAdd = pCharTemp->GetIntersectTestLine(dBegX, dBegY, dAng, pTestLineList);
			if (!bAdd)
				continue;

            double dTSetting, dRelErr, dAbsErr;
            int nErrType;
            pChar = pCharTemp;
            CExBaseList* pParas = (CExBaseList*)pChar->GetCharInterface();
            CCharInterfaceVariable *pPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING);
            if (pPara != NULL)
            {
                dTSetting = pPara->m_strValue.toDouble();
            }

            pPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR);
            if (pPara != NULL)
            {
                dRelErr = pPara->m_strValue.toDouble();
            }

            pPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR);
            if (pPara != NULL)
            {
                dAbsErr = pPara->m_strValue.toDouble();
            }

            pPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC);
            if (pPara != NULL)
            {
                nErrType = CString_To_long(pPara->m_strValue);
            }

			POS pos = pTestLineList.GetHeadPosition();
			CCharTestLine *pLine = NULL;
			while (pos != NULL)
			{
				pLine = (CCharTestLine *)pTestLineList.GetNext(pos);
				if (pLine != NULL)
				{
					float fXb, fYb, fXe, fYe;
					double dZb, dAngb, dZe, dAnge;
					fXb = pLine->m_fXb;
					fYb = pLine->m_fYb;
					fXe = pLine->m_fXe;
					fYe = pLine->m_fYe;

					dZb = sqrt(fXb*fXb + fYb*fYb);
					dAngb = atan(fYb / fXb) * 180 / M_PI;
					if (fXb < 0)
						dAngb += 180;

					dZe = sqrt(fXe*fXe + fYe*fYe);
					dAnge = atan(fYe / fXe) * 180 / M_PI;
					if (fXe < 0)
						dAnge += 180;

					dBegZArr.push_back(dZb);
					dBegAngArr.push_back(dAngb);
					dEndZArr.push_back(dZe);
					dEndAngArr.push_back(dAnge);
					nZoneTypeArr.push_back(CString_To_long(pCharTemp->m_strIndex));
                    dTSettingArr.push_back(dTSetting);
                    dRelErrArr.push_back(dRelErr);
                    dAbsErrArr.push_back(dAbsErr);
                    nErrTypeArr.push_back(nErrType);
				}
			}
		}
	}

	if (dBegZArr.isEmpty())
		return FALSE;
	else
		return TRUE;
}

/*添加系列
返回值 是否可以添加测试项
参数1 故障类型(LN/LL/LLL)
参数2 区段
参数3 起始点横坐标
参数4 起始点纵坐标
参数5 终点横坐标
参数6 终点纵坐标
参数7 首段阻抗(传出)
参数8 首段阻抗角(传出)
参数9 末端阻抗(传出)
参数10 区段数组(传出)
参数11 时间定值数组(传出)
参数12 相对误差数组(传出)
参数13 绝对误差数组(传出)
参数14 误差类型数组(传出)*/
BOOL CalDistanceSearchItemParas(CString strFaultType, int nZoneType, double dBegX, double dBegY, double dEndX, double dEndY,
                                QVector<double> &dBegZArr, QVector<double> &dBegAngArr, QVector<double> &dEndZArr, QVector<double> &dEndAngArr,
                                QVector<double> &dTSettingArr, QVector<double> &dRelErrArr, QVector<double> &dAbsErrArr,
                                QVector<int> &nErrTypeArr)
{
    if(nZoneType == 0)  //线路长度
    {
        double dBegZ, dBegAng, dEndZ, dEndAng;

        dBegZ = sqrt(dBegX*dBegX + dBegY*dBegY);
        dBegAng = atan(dBegY / dBegX) * 180 / M_PI;
        if (dBegX < 0)
            dBegAng += 180;

        dEndZ = sqrt(dEndX*dEndX + dEndY*dEndY);
        dEndAng = atan(dEndY / dEndX) * 180 / M_PI;
        if (dEndX < 0)
            dEndAng += 180;

        dBegZArr.clear();
        dBegAngArr.clear();
        dEndZArr.clear();
        dEndAngArr.clear();
        dBegZArr.push_back(dBegZ);
        dBegAngArr.push_back(dBegAng);
        dEndZArr.push_back(dEndZ);
        dEndAngArr.push_back(dEndAng);

        return TRUE;
    }

	CCharacteristic *pChar = NULL;
	CCharacteristics* pCharacteristics = stt_Frame_Characteristics();
	dBegZArr.clear();
	dBegAngArr.clear();
	dEndZArr.clear();
	dEndAngArr.clear();
    dTSettingArr.clear();
    dRelErrArr.clear();
    dAbsErrArr.clear();
    nErrTypeArr.clear();

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
		if ((pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL || pCharTemp->m_strID == strFaultType) &&
			CString_To_long(pCharTemp->m_strIndex) == nZoneType)
		{
			CExBaseList pTestLineList;
			bool bAdd = pCharTemp->GetIntersectTestLine(dBegX, dBegY, dEndX, dEndY, pTestLineList);
			if (!bAdd)
				continue;

            double dTSetting, dRelErr, dAbsErr;
            int nErrType;
            pChar = pCharTemp;
            CExBaseList* pParas = (CExBaseList*)pChar->GetCharInterface();
            CCharInterfaceVariable *pPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING);
            if (pPara != NULL)
            {
                dTSetting = pPara->m_strValue.toDouble();
            }

            pPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_RELERR);
            if (pPara != NULL)
            {
                dRelErr = pPara->m_strValue.toDouble();
            }

            pPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_CURVEERR_ABSERR);
            if (pPara != NULL)
            {
                dAbsErr = pPara->m_strValue.toDouble();
            }

            pPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC);
            if (pPara != NULL)
            {
                nErrType = CString_To_long(pPara->m_strValue);
            }

			POS pos = pTestLineList.GetHeadPosition();
			CCharTestLine *pLine = NULL;
			while (pos != NULL)
			{
				pLine = (CCharTestLine *)pTestLineList.GetNext(pos);
				if (pLine != NULL)
				{
					float fXb, fYb, fXe, fYe;
					double dZb, dAngb, dZe, dAnge;
					fXb = pLine->m_fXb;
					fYb = pLine->m_fYb;
					fXe = pLine->m_fXe;
					fYe = pLine->m_fYe;

					dZb = sqrt(fXb*fXb + fYb*fYb);
					dAngb = atan(fYb / fXb) * 180 / M_PI;
					if (fXb < 0)
						dAngb += 180;

					dZe = sqrt(fXe*fXe + fYe*fYe);
					dAnge = atan(fYe / fXe) * 180 / M_PI;
					if (fXe < 0)
						dAnge += 180;

					dBegZArr.push_back(dZb);
					dBegAngArr.push_back(dAngb);
					dEndZArr.push_back(dZe);
					dEndAngArr.push_back(dAnge);
                    dTSettingArr.push_back(dTSetting);
                    dRelErrArr.push_back(dRelErr);
                    dAbsErrArr.push_back(dAbsErr);
                    nErrTypeArr.push_back(nErrType);
				}
			}

            return TRUE;
		}
	}

	return FALSE;
}


BOOL CalDistanceSearchValSetting(int nFaultType, int nZoneType, double dBegZ, double dBegZAng,
                                 double dEndZ, double dEndZAng, double &dValSetting, double &dValSettingAng)
{
    if(nZoneType == 0)  //线路长度
        return FALSE;

    CString strFaultType;
    double dBegX, dBegY, dEndX, dEndY;

    if(nFaultType < 3)
        strFaultType = "LN";
    else if(nFaultType < 6)
        strFaultType = "LL";
    else if(nFaultType < 9)
        strFaultType = "LLN";
    else if(nFaultType < 10)
        strFaultType = "LLL";
    else
        strFaultType = "LN";

    dBegX = dBegZ * cos(dBegZAng * M_PI / 180.0);
    dBegY = dBegZ * sin(dBegZAng * M_PI / 180.0);
    dEndX = dEndZ * cos(dEndZAng * M_PI / 180.0);
    dEndY = dEndZ * sin(dEndZAng * M_PI / 180.0);

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
        if ((pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL || pCharTemp->m_strID == strFaultType) &&
            CString_To_long(pCharTemp->m_strIndex) == nZoneType)
        {
            CXDrawDatas oList;
            pCharTemp->GetIntersectPoint(dBegX, dBegY, dEndX, dEndY, oList);

            POS posTemp = oList.GetHeadPosition();
            if(posTemp == NULL)
                return FALSE;

            CXDrawData_Point *pPoint = (CXDrawData_Point *)oList.GetNext(posTemp);
            if (pPoint != NULL)
            {
                double dX = pPoint->m_fX;
                double dY = pPoint->m_fY;
                dValSetting = sqrt(dX*dX + dY*dY);
                dValSettingAng = atan(dY / dX) * 180 / M_PI;
                if (dX < 0)
                    dValSettingAng += 180;
            }

            break;
        }
    }

    return TRUE;
}

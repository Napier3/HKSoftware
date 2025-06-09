// CalcEngine.cpp : CCalcEngine 的实现

//----------------------------------------------------------------------
//增加新的计算接口函数步骤: 
//1. 私有函数 my_Calculate(...)
//   增加计算ID (nCalcID) 对应的计算分支(使用以类封装的结构体, 实现结构体的自动初始化)
//2. 接口函数 Calculate_...(BYTE* lpFaultCalc_...,LONG nSize)
//   实现计算(以结构体指针为传入参数)
//----------------------------------------------------------------------
//2013-3-20: 
//  1. 增加扩展的常规短路计算函数 Calculate_Fault_Ex(), 
//     根据 Ks_Mode (0-输入, 1-Ks=KL) 计算零序补偿系数 Ks;
//  2. 增加扩展的整组计算函数 Calculate_Shot_Ex(), 
//     根据 Ks_Mode (0-输入, 1-Ks=KL) 计算零序补偿系数 Ks;
//----------------------------------------------------------------------
//2013-7-19: 
//  1. 增加扩展的工频变化量短路计算函数 Calculate_GPFault_Ex(), 
//     增加 CalcuMode, 不同的计算公式;
//  2. 增加扩展的工频变化量定值校验 Calculate_GPDistance_Ex(), 
//     增加 CalcuMode, 不同的计算公式;
//----------------------------------------------------------------------

#include "stdafx.h"
#include "FaultCalcEngine.h"
#include "FaultDef_Calc.h"
#include "sub_calcu.h"
#include <math.h>
#include "FaultCalc_Include.h"


// CCalcEngine

STDMETHODIMP CCalcEngine::Calculate(IDispatch *lpGenericData)
{
	HRESULT hResult=S_OK;
// 	IGenericDataPtr ptrGenericData=lpGenericData;
// 	long nCalcID;
// 	Csub_calcu theCalcu;
// 
// 	//从 IGenericData 中提取 nCalcID, 据此解析 XML 数据 -> 结构体
// 	IGenericDataNodePtr ptrRoot;
// 	IEnumGenericNodesPtr ptrEnum;
// 	IGenericDataNodePtr ptrChild;
// 
// 	ptrGenericData->GetRootNode(&ptrRoot);
// 	ptrRoot->Children((IDispatch**)(&ptrEnum));
// 	if(ptrEnum)
// 	{
// 		BSTR bstrChildName;
// 		//枚举根节点下的各子节点(用于计算)
// 		while(ptrEnum->Next(&bstrChildName,&ptrChild)==S_OK)
// 		{
// 			//获取其计算 ID 
// 			if(ptrChild)
// 			{
// 				_variant_t var;
// 				ptrChild->GetValue(&var);
// 				nCalcID = my_GetCalcID(var);
// 				if(nCalcID>= 0)
// 					hResult=my_Calculate(nCalcID,ptrRoot,&bstrChildName);
// 			}
// 			SysFreeString(bstrChildName);
// 		}
// 	}

	return hResult;
}

//-----------------------------------------------------------------
long CCalcEngine::my_GetCalcID(VARIANT var)
{
	long nCalcID=-1;

	switch(var.vt)
	{
	case VT_BSTR:
		#if defined(_UNICODE) || defined(_MBCS)
		{
			nCalcID=(long)_wtoi(var.bstrVal);
		}
		#else
		{
			char strText[100+1];
			sprintf_s(strText,100,_T("%s"),var.bstrVal);
			nCalcID=(long)atoi(strText);
		}
		#endif
		break;
	case VT_I2:
	case VT_UI2:
		nCalcID=(long)(var.iVal);
		break;
	case VT_I4:
	case VT_UI4:
	case VT_INT:
	case VT_UINT:
		nCalcID=(long)(var.ulVal);
		break;		
	case VT_R4:	
		nCalcID=(long)(var.fltVal);
		break;		
	case VT_R8:
		nCalcID=(long)(var.dblVal);
		break;		
	default:
		break;
	}	

	return nCalcID;
}
// 
// HRESULT CCalcEngine::my_Calculate(long nCalcID,IDispatch *ptrRootNode,BSTR *bstrChildName)
// {
// 	if(ptrRootNode==NULL)
// 		return E_INVALIDARG;
// 
// 	HRESULT hResult=S_OK;
// 	CGenericNode root=(IGenericDataNodePtr)ptrRootNode;
// 	CComBSTR strNodeName=*bstrChildName;
// 	int nFlag=0;
// 
// 	switch(nCalcID)
// 	{
// 	case CALCID_LOADSTATE:	//正常运行负荷状态计算
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_LoadState CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_LoadState temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_LoadState((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_FAULT:		//计算短路: 常规计算模型
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_Fault CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Fault temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_Fault((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_GPFAULT:		//计算短路: 工频变化量计算模型
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_GPFault CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_GPFault temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_GPFault((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_ABCTOPP:		//根据ABC相量, 计算线分量: ABC -> PP
// 	case CALCID_PPTOABC:		//根据线分量, 计算ABC相量: PP -> ABC
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_ABCPP CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_ABCPP temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				if(nCalcID==CALCID_ABCTOPP)
// 					hResult=Calculate_ABCtoPP((BYTE*)(&CalcuPara),nSize);
// 				else
// 					hResult=Calculate_PPtoABC((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_ABCTO120:		//根据ABC相量, 计算序分量: ABC -> 120
// 	case CALCID_120TOABC:		//根据序分量, 计算ABC相量: 120 -> ABC
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_ABC120 CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_ABC120 temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				if(nCalcID==CALCID_ABCTO120)
// 					hResult=Calculate_ABCto120((BYTE*)(&CalcuPara),nSize);
// 				else
// 					hResult=Calculate_120toABC((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_ABCTOPQ:		//根据三相电压/电流计算三相功率 P,Q,COS
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_PQ CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_PQ temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_PQ((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_SHOT:		//整组试验计算: 根据界面参数计算3个状态下的电压电流(三相UI)
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_Shot CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Shot temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_Shot((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_DISTANCE:		//距离保护定值校验计算
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_Distance CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Distance temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_Distance((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_GPDISTANCE:	//工频变化量阻抗保护定值校验计算
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_GPDistance CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_GPDistance temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_GPDistance((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_OVERCURR:		//过流保护定值校验计算
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_OverCurr CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_OverCurr temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_OverCurr((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_NEGSEQCURR:	//负序过流保护定值校验计算
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_NegSeqCurr CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_NegSeqCurr temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_NegSeqCurr((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_ZEROSEQCURR:	//零序过流保护定值校验计算
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_ZeroSeqCurr CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_ZeroSeqCurr temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_ZeroSeqCurr((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_DIFF:			//差动计算: 根据 Id,Ir 计算两侧所加电流 Iabc,Ixyz
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_Diff CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Diff temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_Diff((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_DIFF_SHOT:	//差动计算: 差动整组
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_Diff_Shot CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Diff_Shot temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_Diff_Shot((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_DIFF_IRID:	//差动计算: 根据 I1[3], I2[3] 计算三相差流和制流
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_Diff_IrId CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Diff_IrId temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_Diff_IrId((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_DIFF_KP:		//差动计算: 补偿系数 KP123 辅助计算
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_Diff_KP CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Diff_KP temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_Diff_KP((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_DIFF5:		//电铁差动: 根据 Id,Ir 计算两侧所加电流 Iabc,Ixy
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_Diff5 CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Diff5 temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_Diff5((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_OSC:		//功率振荡: 当前发电机角下, 保护安装处 K 点的电压电流有效值
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_Osc CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Osc temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_Osc((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_OSC_ZK:		//功率振荡: 当前发电机角下, 保护安装处 K 点的测量阻抗
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_Osc_Zk CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Osc_Zk temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_Osc_Zk((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_FAULT_EX:		//计算短路: 常规计算模型, 扩展, 增加 Ks_Mode
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_Fault_Ex CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Fault_Ex temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_Fault_Ex((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_SHOT_EX:		//整组试验计算: 扩展, 增加 Ks_Mode
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_Shot_Ex CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Shot_Ex temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_Shot_Ex((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_GPFAULT_EX:		//计算短路: 工频变化量计算模型, 扩展, 增加 CalcuMode
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_GPFault_Ex CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_GPFault_Ex temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_GPFault_Ex((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	case CALCID_GPDISTANCE_EX:	//工频变化量阻抗保护定值校验计算
// 		{
// 			//1. 将 XML -> 解析为 struct
// 			FaultCalc_GPDistance_Ex CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_GPDistance_Ex temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. 计算
// 			{
// 				hResult=Calculate_GPDistance_Ex((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. 将 struct -> 保存为 XML
// 			if(hResult==S_OK)
// 			{
// 				temp.InitStruct(&CalcuPara);
// 				if(temp.AddStructToGD(root,strNodeName,nCalcID))
// 					hResult=S_OK;
// 				else
// 					hResult=S_FALSE;
// 			}
// 		}
// 		break;
// 	default:
// 		break;
// 	}
// 	//置计算是否成功的标志位: BSTR
// 	CComBSTR strNodeName_Result=*bstrChildName;
// 	strNodeName_Result+=".Result";
// 	IGenericDataNodePtr ptrChild;
// 	VARIANT var;
// 
// 	root->GetChild(strNodeName_Result,&ptrChild);
// 	var.vt=VT_BSTR;
// 	if(nFlag==1)
// 		var.bstrVal=_bstr_t("1");
// 	else
// 		var.bstrVal=_bstr_t("0");
// 	ptrChild->SetValue(var);
// 
// 	return hResult;
// }

//以下各分散的接口函数供内部组件直接使用, 以结构体的格式传入数据
//--------------------------------------------------------------------
//正常运行负荷状态计算
//传入参数: lpFaultCalc_LoadState -- FaultCalc_LoadState 结构体指针, 
//                                   负荷状态计算参数结构体
//                                   计算完毕, 将结果填写到结构体中
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_LoadState(BYTE* lpFaultCalc_LoadState, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_LoadState))
		return E_INVALIDARG;

	//根据短路计算的结构指针 pFaultPara, 计算故障状态
	FaultCalc_LoadState *pFaultPara=(FaultCalc_LoadState *)(lpFaultCalc_LoadState);

	Csub_calcu theCalcu;
	theCalcu.calcu_LoadState(pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang);
	//填写到结构中的短路计算结果
	int i;

	for(i=0;i<3;i++)
	{
		pFaultPara->Result.Up[i].Mag=theCalcu.m_Up[i].Mag;
		pFaultPara->Result.Up[i].Ang=theCalcu.m_Up[i].Ang;
		pFaultPara->Result.Ip[i].Mag=theCalcu.m_Ip[i].Mag;
		pFaultPara->Result.Ip[i].Ang=theCalcu.m_Ip[i].Ang;
	}

	return S_OK;
}

//--------------------------------------------------------------------
//常规短路计算
//传入参数: lpFaultCalc_Fault -- FaultCalc_Fault 结构体指针, 
//                                     短路计算参数结构体
//                                     计算完毕, 将结果填写到结构体中
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_Fault(BYTE *lpFaultCalc_Fault, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_Fault))
		return E_INVALIDARG;

	//根据短路计算的结构指针 pFaultPara, 计算故障状态
	FaultCalc_Fault *pFaultPara=(FaultCalc_Fault *)(lpFaultCalc_Fault);
	FaultCalc_Fault_Ex fault_Ex;
	
	fault_Ex.Us=pFaultPara->Us;					//额定电压
	fault_Ex.ILoad_Mag=pFaultPara->ILoad_Mag;	//负荷电流
	fault_Ex.ILoad_Ang=pFaultPara->ILoad_Ang;	//负荷电流角度(相对于对应相的电压, +为超前)
	//
	fault_Ex.FaultType=pFaultPara->FaultType;			//故障类型: 见 FaultEnum_FaultType
	fault_Ex.FaultDirection=pFaultPara->FaultDirection;	//故障方向: 0--正方向, 1--反方向
	fault_Ex.FaultUf=pFaultPara->FaultUf;				//短路电压(计算模型为定电压时有效)
	fault_Ex.FaultIf=pFaultPara->FaultIf;				//短路电流(计算模型为定电流时有效)
	fault_Ex.FaultZf_Mag=pFaultPara->FaultZf_Mag;		//短路阻抗
	fault_Ex.FaultZf_Ang=pFaultPara->FaultZf_Ang;
	//
	fault_Ex.CalcuMode=pFaultPara->CalcuMode;		//短路计算模型: 详见 FaultEnum_CalcuMode
	fault_Ex.Zs_Mag=pFaultPara->Zs_Mag;				//电源侧阻抗(定Zs模型有效)
	fault_Ex.Zs_Ang=pFaultPara->Zs_Ang;
	//---------------------------------------------------------------------------
	fault_Ex.Ks_Mode=0;					//电源阻抗的零序补偿系数设置方式: 0--Ks 输入, 1--Ks=KL;
	//---------------------------------------------------------------------------
	fault_Ex.Ks_Mag=pFaultPara->Ks_Mag;				//电源侧阻抗的零序补偿系数(幅值,角度)
	fault_Ex.Ks_Ang=pFaultPara->Ks_Ang;
	//
	fault_Ex.KL_Mode=pFaultPara->KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	fault_Ex.KL_Mag=pFaultPara->KL_Mag;				//线路阻抗的零序补偿系数(KL 方式有效)
	fault_Ex.KL_Ang=pFaultPara->KL_Ang;
	fault_Ex.KL_KR=pFaultPara->KL_KR;				//线路阻抗的零序补偿系数(KR,KX 方式有效)
	fault_Ex.KL_KX=pFaultPara->KL_KX;
	//
	fault_Ex.Result=pFaultPara->Result;

	HRESULT hr=Calculate_Fault_Ex((BYTE*)(&fault_Ex), sizeof(fault_Ex));
	if(hr!=S_OK)
		return E_FAIL;

	//填写计算结果
	pFaultPara->Result=fault_Ex.Result;

	return S_OK;
}

//--------------------------------------------------------------------
//工频变化量短路计算: 专用短路计算, 定电流 If (南瑞继保)
//传入参数: lpFaultCalc_GPFault -- FaultCalc_GPFault 结构体指针, 
//                                   工频变化量短路计算参数结构体
//                                   计算完毕, 将结果填写到结构体中
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_GPFault(BYTE *lpFaultCalc_GPFault, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_Fault))
		return E_INVALIDARG;

	//根据短路计算的结构指针 pFaultPara, 计算故障状态
	FaultCalc_GPFault *pFaultPara=(FaultCalc_GPFault *)(lpFaultCalc_GPFault);
	FaultCalc_GPFault_Ex fault_Ex;

	//-----------------------------------------------------------------------------
	fault_Ex.CalcuMode=0;			//0--南瑞继保公式,  1--许继公式
	//-----------------------------------------------------------------------------
	fault_Ex.Zzd_Mag=pFaultPara->Zzd_Mag;				//整定阻抗
	fault_Ex.Zzd_Ang=pFaultPara->Zzd_Ang;
	fault_Ex.m=pFaultPara->m;							//校验点: m=0.9, 1.1, ...
	fault_Ex.FaultIf=pFaultPara->FaultIf;				//短路电流(计算模型为定电流时有效)
	fault_Ex.FaultType=pFaultPara->FaultType;			//故障类型: 见 FaultEnum_FaultType
	fault_Ex.FaultDirection=pFaultPara->FaultDirection;	//故障方向: 0--正方向, 1--反方向
	//
	fault_Ex.Us=pFaultPara->Us;						//额定电压
	fault_Ex.ILoad_Mag=pFaultPara->ILoad_Mag;		//负荷电流
	fault_Ex.ILoad_Ang=pFaultPara->ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//
	fault_Ex.KL_Mode=pFaultPara->KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	fault_Ex.KL_Mag=pFaultPara->KL_Mag;				//线路阻抗的零序补偿系数(KL 方式有效)
	fault_Ex.KL_Ang=pFaultPara->KL_Ang;;
	fault_Ex.KL_KR=pFaultPara->KL_KR;				//线路阻抗的零序补偿系数(KR,KX 方式有效)
	fault_Ex.KL_KX=pFaultPara->KL_KX;
	//
	fault_Ex.Result=pFaultPara->Result;

	HRESULT hr=Calculate_Fault_Ex((BYTE*)(&fault_Ex), sizeof(fault_Ex));
	if(hr!=S_OK)
		return E_FAIL;

	//填写计算结果
	pFaultPara->Result=fault_Ex.Result;

	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_GPFault_Ex(BYTE *lpFaultCalc_GPFault_Ex, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_GPFault_Ex))
		return E_INVALIDARG;

	//根据短路计算的结构指针 pFaultPara, 计算故障状态
	struct FaultCalc_GPFault_Ex *pFaultPara=(FaultCalc_GPFault_Ex *)(lpFaultCalc_GPFault_Ex);
	Csub_calcu theCalcu;
	int phaseNo;
	int nCalcuMode;
	int nFaultType,nFaultDirection;
	float m,k;
	float DZset_Mag,DZset_Ang;
	float R,X;

	nCalcuMode=pFaultPara->CalcuMode;	//0--南瑞继保公式,  1--许继公式
	nFaultType=pFaultPara->FaultType;
	nFaultDirection=pFaultPara->FaultDirection;
	//校验点 m
	m=pFaultPara->m;
	DZset_Mag=pFaultPara->Zzd_Mag;
	DZset_Ang=pFaultPara->Zzd_Ang;
	//计算补偿系数 k
	switch(pFaultPara->KL_Mode)
	{
	case KL:	//(Z0-Z1)/3Z1
		k=pFaultPara->KL_Mag;
		break;
	case KR_KX:	//(R0-R1)/3R1, (X0-X1)/3X1
		//根据 m_Kl_KR, m_Kl_KX 和 短路阻抗 DZset_Mag, DZset_Ang 计算 k
		//k=sqrt(Kr*R*R+Kx*X*X)/Z
		theCalcu.po_to_xy(DZset_Mag,DZset_Ang,&R,&X);
		if(DZset_Mag>=0.001f)
		{
			k=(float)sqrt(pFaultPara->KL_KR*R*R+pFaultPara->KL_KX*X*X)/DZset_Mag;
		}
		else
		{
			k=0.0f;
		}
		break;
	case 2:	// Z0/Z1
		theCalcu.po_to_xy(pFaultPara->KL_Mag,pFaultPara->KL_Ang,&R,&X);
		k=(float)sqrt((R-1.0f)*(R-1.0f)+X*X)/3.0f;
		break;
	}
	switch(nFaultType)
	{
	case FAULT_A:
	case FAULT_B:
	case FAULT_C:   // A, B, C 单相短路 
		phaseNo=nFaultType;
		theCalcu.f1_gp(nCalcuMode,phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
			pFaultPara->FaultIf, 
			DZset_Mag,DZset_Ang,k,m);
		break;
	case FAULT_AB:
	case FAULT_BC:
	case FAULT_CA:   // AB, BC, CA 相间短路
		phaseNo=nFaultType-FAULT_AB;
		theCalcu.f2_gp(nCalcuMode,phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
			pFaultPara->FaultIf, 
			DZset_Mag,DZset_Ang,k,m);
		break;
	case FAULT_ABE:
	case FAULT_BCE:
	case FAULT_CAE:   // AB, BC, CA 两相接地: 暂时无此故障
		phaseNo=nFaultType-FAULT_ABE;
		theCalcu.f11_gp(nCalcuMode,phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
			pFaultPara->FaultIf, 
			DZset_Mag,DZset_Ang,k,m);
		break;
	case FAULT_ABC:   // ABC 三相短路: 作相间故障处理
		theCalcu.f3_gp(nCalcuMode,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
			pFaultPara->FaultIf, 
			DZset_Mag,DZset_Ang,k,m);
		break;
	default:
		break;
	}
	//填写到结构中的短路计算结果
	int i;
	for(i=0;i<3;i++)
	{
		pFaultPara->Result.Up[i].Mag=theCalcu.m_Up[i].Mag;
		pFaultPara->Result.Up[i].Ang=theCalcu.m_Up[i].Ang;
		pFaultPara->Result.Ip[i].Mag=theCalcu.m_Ip[i].Mag;
		pFaultPara->Result.Ip[i].Ang=theCalcu.m_Ip[i].Ang;
	}

	return S_OK;
}

//--------------------------------------------------------------------
//线分量计算: ABC -> PP
//传入参数: lpFaultCalc_ABCPP -- FaultCalc_ABCPP 结构体指针
//                                 计算完毕, 将结果填写到结构体中
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_ABCtoPP(BYTE *lpFaultCalc_ABCPP, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_ABCPP))
		return E_INVALIDARG;

	//根据计算的结构指针 pFaultPara, 计算
	struct FaultCalc_ABCPP *pFaultPara=(FaultCalc_ABCPP *)(lpFaultCalc_ABCPP);
	Csub_calcu theCalcu;
	float mag1,mag2,mag3;
	float ang1,ang2,ang3;
	float theMag[3],theAng[3];

	mag1=pFaultPara->Up[0].Mag;
	mag2=pFaultPara->Up[1].Mag;
	mag3=pFaultPara->Up[2].Mag;
	ang1=pFaultPara->Up[0].Ang;
	ang2=pFaultPara->Up[1].Ang;
	ang3=pFaultPara->Up[2].Ang;
	theCalcu.calcu_ABCtoPP(mag1,mag2,mag3,ang1,ang2,ang3,
		theMag,theAng);
	//填写到结构中的计算结果
	int i;
	for(i=0;i<3;i++)
	{
		pFaultPara->Result.Up[i].Mag=theMag[i];
		pFaultPara->Result.Up[i].Ang=theAng[i];
	}

	return S_OK;
}

//--------------------------------------------------------------------
//线分量计算: PP -> ABC
//传入参数: lpFaultCalc_ABCPP -- FaultCalc_ABCPP 结构体指针
//                                 计算完毕, 将结果填写到结构体中
//HRESULT: S_OK -- 成功;
//         E_INVALIDARG -- Uab+Ubc+Uca!=0, 无法执行计算
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_PPtoABC(BYTE *lpFaultCalc_ABCPP, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_ABCPP))
		return E_INVALIDARG;

	//根据计算的结构指针 pFaultPara, 计算
	struct FaultCalc_ABCPP *pFaultPara=(FaultCalc_ABCPP *)(lpFaultCalc_ABCPP);
	Csub_calcu theCalcu;
	float mag1,mag2,mag3;
	float ang1,ang2,ang3;
	float theMag[3],theAng[3];

	mag1=pFaultPara->Up[0].Mag;
	mag2=pFaultPara->Up[1].Mag;
	mag3=pFaultPara->Up[2].Mag;
	ang1=pFaultPara->Up[0].Ang;
	ang2=pFaultPara->Up[1].Ang;
	ang3=pFaultPara->Up[2].Ang;
	//检查 Uab+Ubc+Uca 是否 = 0, 否则无法执行计算
	{
		float tempMag,tempAng;

		tempMag=0.0f;
		tempAng=0.0f;
		theCalcu.comp_Add(mag1,ang1,mag2,ang2,&tempMag,&tempAng);
		theCalcu.comp_Add(tempMag,tempAng,mag3,ang3,&tempMag,&tempAng);
		if(fabs(tempMag)>=0.0001f)
			return E_INVALIDARG;
	}
	theCalcu.calcu_PPtoABC(mag1,mag2,mag3,ang1,ang2,ang3,
		theMag,theAng);
	//填写到结构中的计算结果
	int i;
	for(i=0;i<3;i++)
	{
		pFaultPara->Result.Up[i].Mag=theMag[i];
		pFaultPara->Result.Up[i].Ang=theAng[i];
	}

	return S_OK;
}

//--------------------------------------------------------------------
//序分量计算: ABC -> 120
//传入参数: lpFaultCalc_ABC120 -- FaultCalc_ABC120 结构体指针
//                                  计算完毕, 将结果填写到结构体中
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_ABCto120(BYTE *lpFaultCalc_ABC120, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_ABC120))
		return E_INVALIDARG;

	//根据计算的结构指针 pFaultPara, 计算
	struct FaultCalc_ABC120 *pFaultPara=(FaultCalc_ABC120 *)(lpFaultCalc_ABC120);
	Csub_calcu theCalcu;
	float mag1,mag2,mag3;
	float ang1,ang2,ang3;
	float theMag[3],theAng[3];

	mag1=pFaultPara->Up[0].Mag;
	mag2=pFaultPara->Up[1].Mag;
	mag3=pFaultPara->Up[2].Mag;
	ang1=pFaultPara->Up[0].Ang;
	ang2=pFaultPara->Up[1].Ang;
	ang3=pFaultPara->Up[2].Ang;
	theCalcu.calcu_ABCto120(mag1,mag2,mag3,ang1,ang2,ang3,
		theMag,theAng);
	//填写到结构中的计算结果
	int i;
	for(i=0;i<3;i++)
	{
		pFaultPara->Result.Up[i].Mag=theMag[i];
		pFaultPara->Result.Up[i].Ang=theAng[i];
	}

	return S_OK;
}

//--------------------------------------------------------------------
//序分量计算: 120 -> ABC
//传入参数: lpFaultCalc_ABC120 -- FaultCalc_ABC120 结构体指针
//                                  计算完毕, 将结果填写到结构体中
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_120toABC(BYTE *lpFaultCalc_ABC120, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_ABC120))
		return E_INVALIDARG;

	//根据计算的结构指针 pFaultPara, 计算
	struct FaultCalc_ABC120 *pFaultPara=(FaultCalc_ABC120 *)(lpFaultCalc_ABC120);
	Csub_calcu theCalcu;
	float mag1,mag2,mag3;
	float ang1,ang2,ang3;
	float theMag[3],theAng[3];

	mag1=pFaultPara->Up[0].Mag;
	mag2=pFaultPara->Up[1].Mag;
	mag3=pFaultPara->Up[2].Mag;
	ang1=pFaultPara->Up[0].Ang;
	ang2=pFaultPara->Up[1].Ang;
	ang3=pFaultPara->Up[2].Ang;
	theCalcu.calcu_120toABC(mag1,mag2,mag3,ang1,ang2,ang3,
		theMag,theAng);
	//填写到结构中的计算结果
	int i;
	for(i=0;i<3;i++)
	{
		pFaultPara->Result.Up[i].Mag=theMag[i];
		pFaultPara->Result.Up[i].Ang=theAng[i];
	}

	return S_OK;
}

//--------------------------------------------------------------------
//三相功率计算: U,Ip[3] -> P,Q,COS
//传入参数: lpFaultCalc_PQ -- FaultCalc_PQ 结构体指针
//                              计算完毕, 将结果填写到结构体中
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_PQ(BYTE *lpFaultCalc_PQ, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_PQ))
		return E_INVALIDARG;

	//根据计算的结构指针 pFaultPara, 计算
	struct FaultCalc_PQ *pFaultPara=(FaultCalc_PQ *)(lpFaultCalc_PQ);
	Csub_calcu theCalcu;
	float theP,theQ,theCos;

	theCalcu.calcu_PQ(pFaultPara->CalcuMode,
		pFaultPara->Up[0].Mag,pFaultPara->Up[0].Ang,
		pFaultPara->Up[1].Mag,pFaultPara->Up[1].Ang,
		pFaultPara->Up[2].Mag,pFaultPara->Up[2].Ang,
		pFaultPara->Ip[0].Mag,pFaultPara->Ip[0].Ang,
		pFaultPara->Ip[1].Mag,pFaultPara->Ip[1].Ang,
		pFaultPara->Ip[2].Mag,pFaultPara->Ip[2].Ang,
		&theP,&theQ,&theCos);

	//填写到结构中的计算结果
	pFaultPara->Result.P=theP;
	pFaultPara->Result.Q=theQ;
	pFaultPara->Result.COS=theCos;

	return S_OK;
}

//--------------------------------------------------------------------
//相量相加(极坐标)
//传入参数: 极坐标 (Mag1,Ang1), (Mag2,Ang2) 
//传出参数: 极坐标 theMag,theAng (以指针传入)
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Comp_Add(float Mag1, float Ang1, float Mag2, float Ang2, float *theMag, float *theAng)
{
	Csub_calcu theCalcu;

	theCalcu.comp_Add(Mag1,Ang1,Mag2,Ang2,theMag,theAng);

	return S_OK;
}

//--------------------------------------------------------------------
//相量相减(极坐标)
//传入参数: 极坐标 (Mag1,Ang1), (Mag2,Ang2) 
//传出参数: 极坐标 theMag,theAng (以指针传入)
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Comp_Sub(float Mag1, float Ang1, float Mag2, float Ang2, float *theMag, float *theAng)
{
	Csub_calcu theCalcu;

	theCalcu.comp_Sub(Mag1,Ang1,Mag2,Ang2,theMag,theAng);

	return S_OK;
}

//--------------------------------------------------------------------
//相量相乘(直角坐标)
//传入参数: 直角坐标 (x1,y1), (x2,y2) 
//传出参数: 直角坐标 theX,theY (以指针传入)
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Comp_Mul(float x1, float y1, float x2, float y2, float *theX, float *theY)
{
	Csub_calcu theCalcu;

	theCalcu.comp_Mult(x1,y1,x2,y2,theX,theY);

	return S_OK;
}

//--------------------------------------------------------------------
//相量相除(直角坐标)
//传入参数: 直角坐标 (x1,y1), (x2,y2) 
//传出参数: 直角坐标 theX,theY (以指针传入)
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Comp_Div(float x1, float y1, float x2, float y2, float *theX, float *theY)
{
	Csub_calcu theCalcu;

	theCalcu.comp_Divi(x1,y1,x2,y2,theX,theY);

	return S_OK;
}

//--------------------------------------------------------------------
//极坐标 -> 直角坐标
//传入参数: 极坐标 Mag,Ang 
//传出参数: 直角坐标 x,y (以指针传入)
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Comp_POtoXY(float Mag, float Ang, float *x, float *y)
{
	Csub_calcu theCalcu;

	theCalcu.po_to_xy(Mag,Ang,x,y);

	return S_OK;
}

//--------------------------------------------------------------------
//直角坐标 -> 极坐标
//传入参数: 直角坐标 x,y
//传出参数: 极坐标 Mag,Ang (以指针传入)
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Comp_XYtoPO(float x, float y, float *Mag, float *Ang)
{
	Csub_calcu theCalcu;

	theCalcu.xy_to_po(x,y,Mag,Ang);

	return S_OK;
}

//--------------------------------------------------------------------
//整组试验: 计算 3 个状态下的电压电流
//传入参数: lpFaultCalc_Shot -- FaultCalc_Shot 结构体指针, 
//                              计算完毕, 将结果填写到结构体中
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_Shot(BYTE* lpFaultCalc_Shot, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_Shot))
		return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);
	FaultCalc_Shot_Ex shot_Ex;

	shot_Ex.Us=pFaultPara->Us;					//额定电压
	shot_Ex.ILoad_Mag=pFaultPara->ILoad_Mag;	//负荷电流
	shot_Ex.ILoad_Ang=pFaultPara->ILoad_Ang;	//负荷电流角度(相对于对应相的电压, +为超前)
	//
	shot_Ex.FaultType=pFaultPara->FaultType;			//故障类型: 见 FaultEnum_FaultType
	shot_Ex.FaultDirection=pFaultPara->FaultDirection;	//故障方向: 0--正方向, 1--反方向
	shot_Ex.FaultUf=pFaultPara->FaultUf;				//短路电压(计算模型为定电压时有效)
	shot_Ex.FaultIf=pFaultPara->FaultIf;				//短路电流(计算模型为定电流时有效)
	shot_Ex.FaultZf_Mag=pFaultPara->FaultZf_Mag;		//短路阻抗
	shot_Ex.FaultZf_Ang=pFaultPara->FaultZf_Ang;
	//
	//故障转换
	shot_Ex.bFaultTrans=pFaultPara->bFaultTrans;			//是否发生故障转换: 0--否, 1--是;
	shot_Ex.TransFaultType=pFaultPara->TransFaultType;			//故障类型: 见 FaultEnum_FaultType
	shot_Ex.TransFaultDirection=pFaultPara->TransFaultDirection;	//故障方向: 0--正方向, 1--反方向
	shot_Ex.TransFaultUf=pFaultPara->TransFaultUf;				//短路电压(计算模型为定电压时有效)
	shot_Ex.TransFaultIf=pFaultPara->TransFaultIf;				//短路电流(计算模型为定电流时有效)
	shot_Ex.TransFaultZf_Mag=pFaultPara->TransFaultZf_Mag;		//短路阻抗
	shot_Ex.TransFaultZf_Ang=pFaultPara->TransFaultZf_Ang;
	//
	shot_Ex.CalcuMode=pFaultPara->CalcuMode;		//短路计算模型: 详见 FaultEnum_CalcuMode
	shot_Ex.Zs_Mag=pFaultPara->Zs_Mag;				//电源侧阻抗(定Zs模型有效)
	shot_Ex.Zs_Ang=pFaultPara->Zs_Ang;
	//---------------------------------------------------------------------------
	shot_Ex.Ks_Mode=0;					//电源阻抗的零序补偿系数设置方式: 0--Ks 输入, 1--Ks=KL;
	//---------------------------------------------------------------------------
	shot_Ex.Ks_Mag=pFaultPara->Ks_Mag;				//电源侧阻抗的零序补偿系数(幅值,角度)
	shot_Ex.Ks_Ang=pFaultPara->Ks_Ang;
	//
	shot_Ex.KL_Mode=pFaultPara->KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	shot_Ex.KL_Mag=pFaultPara->KL_Mag;				//线路阻抗的零序补偿系数(KL 方式有效)
	shot_Ex.KL_Ang=pFaultPara->KL_Ang;
	shot_Ex.KL_KR=pFaultPara->KL_KR;				//线路阻抗的零序补偿系数(KR,KX 方式有效)
	shot_Ex.KL_KX=pFaultPara->KL_KX;
	//
	shot_Ex.Result=pFaultPara->Result;

	HRESULT hr=Calculate_Shot_Ex((BYTE*)(&shot_Ex), sizeof(shot_Ex));
	if(hr!=S_OK)
		return E_FAIL;

	//填写计算结果
	pFaultPara->Result=shot_Ex.Result;

	return S_OK;
}

//--------------------------------------------------------------------
//距离保护定值校验: 计算 2 个状态下的电压电流(无故障转换, 固定计算模型为定电流)
//传入参数: lpFaultCalc_Distance -- FaultCalc_Distance 结构体指针, 
//                                  计算完毕, 将结果填写到结构体中
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_Distance(BYTE* lpFaultCalc_Distance, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_Distance))
		return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	FaultCalc_Distance *pFaultPara=(FaultCalc_Distance *)(lpFaultCalc_Distance);
	HRESULT hResult=S_OK;
	int i;

	//计算故障前
	{
		CFaultCalc_LoadState theState;

		theState.Us=pFaultPara->Us;
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;
		//
		hResult=Calculate_LoadState((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//获取计算结果
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_PreFault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_PreFault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_PreFault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_PreFault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//计算故障
	{
		CFaultCalc_Fault theState;

		theState.Us=pFaultPara->Us;					//额定电压
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//负荷电流
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//负荷电流角度(相对于对应相的电压, +为超前)
		//
		theState.FaultType=pFaultPara->FaultType;			//故障类型: 见 enum FaultFaultType
		theState.FaultDirection=pFaultPara->FaultDirection;	//故障方向: 0--正方向, 1--反方向
		theState.FaultIf=pFaultPara->FaultIf;				//短路电流(计算模型为定电流时有效)
		//
		//距离保护定值校验: 计算短路阻抗
		theState.FaultZf_Mag=pFaultPara->Zzd_Mag*pFaultPara->Zf_Ratio;		//短路阻抗
		theState.FaultZf_Ang=pFaultPara->Zzd_Ang;
		//
		theState.CalcuMode=CALCUMODE_IF;			//短路计算模型: 固定为定电流
		//
		theState.KL_Mode=pFaultPara->KL_Mode;		//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_Fault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//获取计算结果
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_Fault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_Fault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_Fault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_Fault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//故障转换: 无, 取其值 = 故障
	{
		for(i=0;i<3;i++)
		{
			pFaultPara->Result.Up_TransFault[i].Mag=pFaultPara->Result.Up_Fault[i].Mag;
			pFaultPara->Result.Up_TransFault[i].Ang=pFaultPara->Result.Up_Fault[i].Ang;
			pFaultPara->Result.Ip_TransFault[i].Mag=pFaultPara->Result.Ip_Fault[i].Mag;
			pFaultPara->Result.Ip_TransFault[i].Ang=pFaultPara->Result.Ip_Fault[i].Ang;
		}
	}

	return hResult;
}

//--------------------------------------------------------------------
//工频变化量距离保护定值校验: 计算 2 个状态下的电压电流(无故障转换)
//传入参数: lpFaultCalc_GPDistance -- FaultCalc_GPDistance 结构体指针, 
//                                    计算完毕, 将结果填写到结构体中
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_GPDistance(BYTE* lpFaultCalc_GPDistance, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_GPDistance))
		return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	FaultCalc_GPDistance *pFaultPara=(FaultCalc_GPDistance *)(lpFaultCalc_GPDistance);
	FaultCalc_GPDistance_Ex gpDistance_Ex;

	//-----------------------------------------------------------------------------
	gpDistance_Ex.CalcuMode=0;			//0--南瑞继保公式,  1--许继公式
	//-----------------------------------------------------------------------------
	gpDistance_Ex.Zzd_Mag=pFaultPara->Zzd_Mag;			//整定阻抗
	gpDistance_Ex.Zzd_Ang=pFaultPara->Zzd_Ang;
	gpDistance_Ex.m=pFaultPara->m;						//校验点: m=0.9, 1.1, ...
	gpDistance_Ex.FaultIf=pFaultPara->FaultIf;			//短路电流(计算模型: 定电流)
	gpDistance_Ex.FaultType=pFaultPara->FaultType;		//故障类型: 见 FaultEnum_FaultType
	gpDistance_Ex.FaultDirection=pFaultPara->FaultDirection;		//故障方向: 0--正方向, 1--反方向
	//
	gpDistance_Ex.Us=pFaultPara->Us;					//额定电压
	gpDistance_Ex.ILoad_Mag=pFaultPara->ILoad_Mag;		//负荷电流
	gpDistance_Ex.ILoad_Ang=pFaultPara->ILoad_Ang;		//负荷电流角度(相对于对应相的电压, +为超前)
	//
	gpDistance_Ex.KL_Mode=pFaultPara->KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
	gpDistance_Ex.KL_Mag=pFaultPara->KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
	gpDistance_Ex.KL_Ang=pFaultPara->KL_Ang;
	gpDistance_Ex.KL_KR=pFaultPara->KL_KR;				//线路阻抗的零序补偿系数(KR,KX 方式有效)
	gpDistance_Ex.KL_KX=pFaultPara->KL_KX;
	//
	gpDistance_Ex.Result=pFaultPara->Result;

	HRESULT hr=Calculate_GPDistance_Ex((BYTE*)(&gpDistance_Ex), sizeof(gpDistance_Ex));
	if(hr!=S_OK)
		return E_FAIL;

	//填写计算结果
	pFaultPara->Result=gpDistance_Ex.Result;

	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_GPDistance_Ex(BYTE* lpFaultCalc_GPDistance, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_GPDistance))
		return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	FaultCalc_GPDistance *pFaultPara=(FaultCalc_GPDistance *)(lpFaultCalc_GPDistance);
	HRESULT hResult=S_OK;
	int i;

	//计算故障前
	{
		CFaultCalc_LoadState theState;

		theState.Us=pFaultPara->Us;
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;
		//
		hResult=Calculate_LoadState((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//获取计算结果
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_PreFault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_PreFault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_PreFault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_PreFault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//计算故障
	{
		CFaultCalc_GPFault theState;

		theState.Zzd_Mag=pFaultPara->Zzd_Mag;		//整定阻抗
		theState.Zzd_Ang=pFaultPara->Zzd_Ang;
		theState.m=pFaultPara->m;					//校验点: m=0.9, 1.1, ...
		//
		theState.Us=pFaultPara->Us;					//额定电压
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//负荷电流
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//负荷电流角度(相对于对应相的电压, +为超前)
		//
		theState.FaultType=pFaultPara->FaultType;			//故障类型: 见 enum FaultFaultType
		theState.FaultDirection=pFaultPara->FaultDirection;	//故障方向: 0--正方向, 1--反方向
		theState.FaultIf=pFaultPara->FaultIf;				//短路电流(计算模型为定电流时有效)
		//
		theState.KL_Mode=pFaultPara->KL_Mode;		//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_GPFault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//获取计算结果
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_Fault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_Fault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_Fault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_Fault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//故障转换: 无, 取其值 = 故障
	{
		for(i=0;i<3;i++)
		{
			pFaultPara->Result.Up_TransFault[i].Mag=pFaultPara->Result.Up_Fault[i].Mag;
			pFaultPara->Result.Up_TransFault[i].Ang=pFaultPara->Result.Up_Fault[i].Ang;
			pFaultPara->Result.Ip_TransFault[i].Mag=pFaultPara->Result.Ip_Fault[i].Mag;
			pFaultPara->Result.Ip_TransFault[i].Ang=pFaultPara->Result.Ip_Fault[i].Ang;
		}
	}

	return hResult;
}

//--------------------------------------------------------------------
//过流保护定值校验: 计算 2 个状态下的电压电流(无故障转换, 固定计算模型为定电流)
//传入参数: lpFaultCalc_OverCurr -- FaultCalc_OverCurr 结构体指针, 
//                                  计算完毕, 将结果填写到结构体中
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_OverCurr(BYTE* lpFaultCalc_OverCurr, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_OverCurr))
		return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	FaultCalc_OverCurr *pFaultPara=(FaultCalc_OverCurr *)(lpFaultCalc_OverCurr);
	HRESULT hResult=S_OK;
	int i;

	//计算故障前
	{
		CFaultCalc_LoadState theState;

		theState.Us=pFaultPara->Us;
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;
		//
		hResult=Calculate_LoadState((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//获取计算结果
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_PreFault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_PreFault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_PreFault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_PreFault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//计算故障
	{
		CFaultCalc_Fault theState;

		theState.Us=pFaultPara->Us;					//额定电压
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//负荷电流
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//负荷电流角度(相对于对应相的电压, +为超前)
		//
		theState.FaultType=pFaultPara->FaultType;			//故障类型: 见 enum FaultFaultType
		theState.FaultDirection=pFaultPara->FaultDirection;	//故障方向: 0--正方向, 1--反方向
		//
		//过流, 计算短路电流
		theState.FaultIf=pFaultPara->Izd*pFaultPara->If_Ratio;
		//
		theState.FaultZf_Mag=pFaultPara->Zf_Mag;		//短路阻抗
		theState.FaultZf_Ang=pFaultPara->Zf_Ang;
		//
		theState.CalcuMode=CALCUMODE_IF;			//短路计算模型: 固定为定电流
		//
		theState.KL_Mode=pFaultPara->KL_Mode;		//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_Fault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//获取计算结果
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_Fault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_Fault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_Fault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_Fault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//故障转换: 无, 取其值 = 故障
	{
		for(i=0;i<3;i++)
		{
			pFaultPara->Result.Up_TransFault[i].Mag=pFaultPara->Result.Up_Fault[i].Mag;
			pFaultPara->Result.Up_TransFault[i].Ang=pFaultPara->Result.Up_Fault[i].Ang;
			pFaultPara->Result.Ip_TransFault[i].Mag=pFaultPara->Result.Ip_Fault[i].Mag;
			pFaultPara->Result.Ip_TransFault[i].Ang=pFaultPara->Result.Ip_Fault[i].Ang;
		}
	}

	return hResult;
}

STDMETHODIMP CCalcEngine::Calculate_NegSeqCurr(BYTE* lpFaultCalc_NegSeqCurr, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_NegSeqCurr))
		return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	FaultCalc_NegSeqCurr *pFaultPara=(FaultCalc_NegSeqCurr *)(lpFaultCalc_NegSeqCurr);
	if(pFaultPara->FaultType==FAULT_ABE
		|| pFaultPara->FaultType==FAULT_BCE
		|| pFaultPara->FaultType==FAULT_CAE
		||pFaultPara->FaultType==FAULT_ABC)	
	{
		//以上故障, 无法计算负序
		return E_INVALIDARG;
	}

	HRESULT hResult=S_OK;
	int i;

	//计算故障前
	{
		CFaultCalc_LoadState theState;

		theState.Us=pFaultPara->Us;
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;
		//
		hResult=Calculate_LoadState((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//获取计算结果
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_PreFault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_PreFault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_PreFault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_PreFault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//计算故障
	{
		CFaultCalc_Fault theState;

		theState.Us=pFaultPara->Us;					//额定电压
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//负荷电流
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//负荷电流角度(相对于对应相的电压, +为超前)
		//
		theState.FaultType=pFaultPara->FaultType;			//故障类型: 见 enum FaultFaultType
		theState.FaultDirection=pFaultPara->FaultDirection;	//故障方向: 0--正方向, 1--反方向
		//
		//负序过流, 计算短路电流
		theState.FaultIf=pFaultPara->Izd*pFaultPara->If_Ratio;
		switch(pFaultPara->FaultType)
		{
		case FAULT_A:
		case FAULT_B:
		case FAULT_C:	//单相接地: I1=I2=I0, 故障相电流 If = 3 * I1
			theState.FaultIf*=3.0f;
			break;
		case FAULT_AB:
		case FAULT_BC:
		case FAULT_CA:	//相间故障: I1=-I2, 故障相电流 If = √3 * I1
			theState.FaultIf*=(float)sqrt(3.0);
			break;
		case FAULT_ABE:
		case FAULT_BCE:
		case FAULT_CAE:	//两相接地: 没有一个固定的比例
			hResult=E_INVALIDARG;
			break;
		case FAULT_ABC:	//三相短路: 无负序
			hResult=E_INVALIDARG;
			break;
		default:
			hResult=E_INVALIDARG;
			break;
		}
		if(hResult!=S_OK)
			return hResult;
		theState.FaultZf_Mag=pFaultPara->Zf_Mag;		//短路阻抗
		theState.FaultZf_Ang=pFaultPara->Zf_Ang;
		//
		theState.CalcuMode=CALCUMODE_IF;			//短路计算模型: 固定为定电流
		//
		theState.KL_Mode=pFaultPara->KL_Mode;		//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_Fault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//获取计算结果
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_Fault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_Fault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_Fault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_Fault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//故障转换: 无, 取其值 = 故障
	{
		for(i=0;i<3;i++)
		{
			pFaultPara->Result.Up_TransFault[i].Mag=pFaultPara->Result.Up_Fault[i].Mag;
			pFaultPara->Result.Up_TransFault[i].Ang=pFaultPara->Result.Up_Fault[i].Ang;
			pFaultPara->Result.Ip_TransFault[i].Mag=pFaultPara->Result.Ip_Fault[i].Mag;
			pFaultPara->Result.Ip_TransFault[i].Ang=pFaultPara->Result.Ip_Fault[i].Ang;
		}
	}

	return hResult;
}

STDMETHODIMP CCalcEngine::Calculate_ZeroSeqCurr(BYTE* lpFaultCalc_ZeroSeqCurr, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_ZeroSeqCurr))
		return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	FaultCalc_ZeroSeqCurr *pFaultPara=(FaultCalc_ZeroSeqCurr *)(lpFaultCalc_ZeroSeqCurr);
	if(	pFaultPara->FaultType==FAULT_AB
		|| pFaultPara->FaultType==FAULT_BC
		|| pFaultPara->FaultType==FAULT_CA
		|| pFaultPara->FaultType==FAULT_ABE
		|| pFaultPara->FaultType==FAULT_BCE
		|| pFaultPara->FaultType==FAULT_CAE
		||pFaultPara->FaultType==FAULT_ABC)	
	{
		//以上故障, 无法计算零序
		return E_INVALIDARG;
	}

	HRESULT hResult=S_OK;
	int i;

	//计算故障前
	{
		CFaultCalc_LoadState theState;

		theState.Us=pFaultPara->Us;
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;
		//
		hResult=Calculate_LoadState((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//获取计算结果
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_PreFault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_PreFault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_PreFault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_PreFault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//计算故障
	if(hResult==S_OK)
	{
		CFaultCalc_Fault theState;

		theState.Us=pFaultPara->Us;					//额定电压
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//负荷电流
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//负荷电流角度(相对于对应相的电压, +为超前)
		//
		theState.FaultType=pFaultPara->FaultType;			//故障类型: 见 enum FaultFaultType
		theState.FaultDirection=pFaultPara->FaultDirection;	//故障方向: 0--正方向, 1--反方向
		//
		//零序过流, 计算短路电流
		theState.FaultIf=pFaultPara->Izd*pFaultPara->If_Ratio;
		switch(pFaultPara->FaultType)
		{
		case FAULT_A:
		case FAULT_B:
		case FAULT_C:	//单相接地: I1=I2=I0, 故障相电流 If = 3 * I1
			theState.FaultIf*=3.0f;
			break;
		case FAULT_AB:
		case FAULT_BC:
		case FAULT_CA:	//相间故障: I1=-I2, 无零序
			hResult=E_INVALIDARG;
			break;
		case FAULT_ABE:
		case FAULT_BCE:
		case FAULT_CAE:	//两相接地: 没有一个固定的比例
			hResult=E_INVALIDARG;
			break;
		case FAULT_ABC:	//三相短路: 无零序
			hResult=E_INVALIDARG;
			break;
		default:
			hResult=E_INVALIDARG;
			break;
		}
		if(hResult!=S_OK)
			return hResult;
		theState.FaultZf_Mag=pFaultPara->Zf_Mag;		//短路阻抗
		theState.FaultZf_Ang=pFaultPara->Zf_Ang;
		//
		theState.CalcuMode=CALCUMODE_IF;			//短路计算模型: 固定为定电流
		//
		theState.KL_Mode=pFaultPara->KL_Mode;		//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;			//线路阻抗的零序补偿系数(KL 方式有效)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_Fault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//获取计算结果
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_Fault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_Fault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_Fault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_Fault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//故障转换: 无, 取其值 = 故障
	{
		for(i=0;i<3;i++)
		{
			pFaultPara->Result.Up_TransFault[i].Mag=pFaultPara->Result.Up_Fault[i].Mag;
			pFaultPara->Result.Up_TransFault[i].Ang=pFaultPara->Result.Up_Fault[i].Ang;
			pFaultPara->Result.Ip_TransFault[i].Mag=pFaultPara->Result.Ip_Fault[i].Mag;
			pFaultPara->Result.Ip_TransFault[i].Ang=pFaultPara->Result.Ip_Fault[i].Ang;
		}
	}

	return hResult;
}

STDMETHODIMP CCalcEngine::Calculate_Diff(BYTE* lpFaultCalc_Diff, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//填写到结构中的计算结果



	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_Diff_KP(BYTE* lpFaultCalc_Diff_KP, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//填写到结构中的计算结果



	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_Diff_Shot(BYTE* lpFaultCalc_Diff_Shot, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//填写到结构中的计算结果



	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_Diff_IrId(BYTE* lpFaultCalc_Diff_IrId, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//填写到结构中的计算结果



	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_Diff5(BYTE* lpFaultCalc_Diff5, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//填写到结构中的计算结果



	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_Osc(BYTE* lpFaultCalc_Osc, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//填写到结构中的计算结果



	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_Osc_Zk(BYTE* lpFaultCalc_Osc_Zk, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//填写到结构中的计算结果



	return S_OK;
}

//--------------------------------------------------------------------
//常规短路计算
//传入参数: lpFaultCalc_Fault -- FaultCalc_Fault 结构体指针, 
//                                     短路计算参数结构体
//                                     计算完毕, 将结果填写到结构体中
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_Fault_Ex(BYTE *lpFaultCalc_Fault_Ex, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_Fault_Ex))
		return E_INVALIDARG;

	//根据短路计算的结构指针 pFaultPara, 计算故障状态
	FaultCalc_Fault_Ex *pFaultPara=(FaultCalc_Fault_Ex *)(lpFaultCalc_Fault_Ex);

	Csub_calcu theCalcu;
	int phaseNo;
	int nFaultType,nFaultDirection;
	float Zl_Mag,Zl_Ang;
	float KL_Re,KL_Im;	//计算短路阻抗的零序补偿系数的实部和虚部
	float Ks_Re,Ks_Im;
	float temp,R,X;

	nFaultType=pFaultPara->FaultType;
	nFaultDirection=pFaultPara->FaultDirection;
	Zl_Mag=pFaultPara->FaultZf_Mag;
	Zl_Ang=pFaultPara->FaultZf_Ang; 
	//计算补偿系数 KL
	switch(pFaultPara->KL_Mode)
	{
	case KL:		//(Z0-Z1)/3Z1
		theCalcu.po_to_xy(pFaultPara->KL_Mag,pFaultPara->KL_Ang,&R,&X);
		KL_Re=R;
		KL_Im=X;
		break;
	case KR_KX:		//(R0-R1)/3R1, (X0-X1)/3X1
		//根据 m_Kl_KR, m_Kl_KX 和 短路阻抗 Zl_Mag, Zl_Ang 计算 KL
		//Re=(Kr*R*R+Kx*X*X)/(Z*Z)
		//Im=(Kx-Kr)*R*X/(Z*Z)
		theCalcu.po_to_xy(Zl_Mag,Zl_Ang,&R,&X);
		if(Zl_Mag>=0.001f)
		{
			temp=Zl_Mag*Zl_Mag;
			KL_Re=(pFaultPara->KL_KR*R*R+pFaultPara->KL_KX*X*X)/temp;
			KL_Im=(pFaultPara->KL_KX-pFaultPara->KL_KR)*R*X/temp;
		}
		else
		{
			KL_Re=0.0f;
			KL_Im=0.0f;
		}
		break;
	case 2:		//Z0/Z1
		theCalcu.po_to_xy(pFaultPara->KL_Mag,pFaultPara->KL_Ang,&R,&X);
		KL_Re=(R-1.0f)/3.0f;
		KL_Im=X/3.0f;
		break;
	default:	//(Z0-Z1)/3Z1
		theCalcu.po_to_xy(pFaultPara->KL_Mag,pFaultPara->KL_Ang,&R,&X);
		KL_Re=R;
		KL_Im=X;
		break;
	}
	//计算 Ks, 根据 Ks_Mode: 0--Ks 输入, 1--Ks=KL;
	if(pFaultPara->Ks_Mode==0)
	{
		theCalcu.po_to_xy(pFaultPara->Ks_Mag,pFaultPara->Ks_Ang,&R,&X);
		Ks_Re=R;
		Ks_Im=X;
	}
	else
	{
		Ks_Re=KL_Re;
		Ks_Im=KL_Im;
	}
	switch(nFaultType)
	{
	case FAULT_A:
	case FAULT_B:
	case FAULT_C:   // A, B, C 单相短路 
		phaseNo=nFaultType;
		switch(pFaultPara->CalcuMode)
		{
		case CALCUMODE_IF:
			theCalcu.f1_If(phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
				pFaultPara->FaultIf, 
				Zl_Mag,Zl_Ang,KL_Re,KL_Im);
			break;
		case CALCUMODE_UF:
			theCalcu.f1_Uf(phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
				pFaultPara->FaultUf,
				Zl_Mag,Zl_Ang,KL_Re,KL_Im);
			break;
		case CALCUMODE_ZS:
			theCalcu.f1_Zs(phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
				pFaultPara->Zs_Mag,pFaultPara->Zs_Ang,Ks_Re,Ks_Im,
				Zl_Mag,Zl_Ang,KL_Re,KL_Im);
			break;
		}
		break;
	case FAULT_AB:
	case FAULT_BC:
	case FAULT_CA:   // AB, BC, CA 相间短路
		phaseNo=nFaultType-FAULT_AB;
		switch(pFaultPara->CalcuMode)
		{
		case CALCUMODE_IF:
			theCalcu.f2_If(phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
				pFaultPara->FaultIf,
				Zl_Mag,Zl_Ang,KL_Re,KL_Im);
			break;
		case CALCUMODE_UF:
			theCalcu.f2_Uf(phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
				pFaultPara->FaultUf,
				Zl_Mag,Zl_Ang,KL_Re,KL_Im);
			break;
		case CALCUMODE_ZS:
			theCalcu.f2_Zs(phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
				pFaultPara->Zs_Mag,pFaultPara->Zs_Ang,Ks_Re,Ks_Im,
				Zl_Mag,Zl_Ang,KL_Re,KL_Im);
			break;
		}
		break;
	case FAULT_ABE:
	case FAULT_BCE:
	case FAULT_CAE:   // AB, BC, CA 两相接地
		phaseNo=nFaultType-FAULT_ABE;
		switch(pFaultPara->CalcuMode)
		{
		case CALCUMODE_IF:
			theCalcu.f11_If(phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
				pFaultPara->FaultIf,
				Zl_Mag,Zl_Ang,KL_Re,KL_Im);
			break;
		case CALCUMODE_UF:
			theCalcu.f11_Uf(phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
				pFaultPara->FaultUf,
				Zl_Mag,Zl_Ang,KL_Re,KL_Im);
			break;
		case CALCUMODE_ZS:
			theCalcu.f11_Zs(phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
				pFaultPara->Zs_Mag,pFaultPara->Zs_Ang,Ks_Re,Ks_Im,
				Zl_Mag,Zl_Ang,KL_Re,KL_Im);
			break;
		}
		break;
	case FAULT_ABC:   // ABC 三相短路
		switch(pFaultPara->CalcuMode)
		{
		case CALCUMODE_IF:
			theCalcu.f3_If(nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
				pFaultPara->FaultIf,
				Zl_Mag,Zl_Ang,KL_Re,KL_Im);
			break;
		case CALCUMODE_UF:
			theCalcu.f3_Uf(nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
				pFaultPara->FaultUf,
				Zl_Mag,Zl_Ang,KL_Re,KL_Im);
			break;
		case CALCUMODE_ZS:
			theCalcu.f3_Zs(nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
				pFaultPara->Zs_Mag,pFaultPara->Zs_Ang,Ks_Re,Ks_Im,
				Zl_Mag,Zl_Ang,KL_Re,KL_Im);
			break;
		}
		break;
	default:
		break;
	}
	//填写到结构中的短路计算结果
	int i;
	for(i=0;i<3;i++)
	{
		pFaultPara->Result.Up[i].Mag=theCalcu.m_Up[i].Mag;
		pFaultPara->Result.Up[i].Ang=theCalcu.m_Up[i].Ang;
		pFaultPara->Result.Ip[i].Mag=theCalcu.m_Ip[i].Mag;
		pFaultPara->Result.Ip[i].Ang=theCalcu.m_Ip[i].Ang;
	}

	return S_OK;
}

//--------------------------------------------------------------------
//整组试验: 计算 3 个状态下的电压电流
//传入参数: lpFaultCalc_Shot -- FaultCalc_Shot 结构体指针, 
//                              计算完毕, 将结果填写到结构体中
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_Shot_Ex(BYTE* lpFaultCalc_Shot_Ex, LONG nSize)
{
	//检查数据结构 struct 的匹配性 (但无法保证数据全部被初始化)
	if(nSize!=sizeof(FaultCalc_Shot_Ex))
		return E_INVALIDARG;

	//根据结构指针 pFaultPara, 计算
	FaultCalc_Shot_Ex *pFaultPara=(FaultCalc_Shot_Ex *)(lpFaultCalc_Shot_Ex);
	HRESULT hResult=S_OK;
	int i;

	//计算故障前
	{
		CFaultCalc_LoadState theState;

		theState.Us=pFaultPara->Us;
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;
		//
		hResult=Calculate_LoadState((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//获取计算结果
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_PreFault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_PreFault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_PreFault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_PreFault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//计算故障
	{
		CFaultCalc_Fault_Ex theState;

		theState.Us=pFaultPara->Us;					//额定电压
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//负荷电流
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//负荷电流角度(相对于对应相的电压, +为超前)
		//
		theState.FaultType=pFaultPara->FaultType;			//故障类型: 见 enum FaultFaultType
		theState.FaultDirection=pFaultPara->FaultDirection;	//故障方向: 0--正方向, 1--反方向
		theState.FaultUf=pFaultPara->FaultUf;				//短路电压(计算模型为定电压时有效)
		theState.FaultIf=pFaultPara->FaultIf;				//短路电流(计算模型为定电流时有效)
		theState.FaultZf_Mag=pFaultPara->FaultZf_Mag;		//短路阻抗
		theState.FaultZf_Ang=pFaultPara->FaultZf_Ang;
		//
		theState.CalcuMode=pFaultPara->CalcuMode;		//短路计算模型: 详见 enum FaultCalcuMode
		theState.Zs_Mag=pFaultPara->Zs_Mag;				//电源侧阻抗(定Zs模型有效)
		theState.Zs_Ang=pFaultPara->Zs_Ang;
		theState.Ks_Mode=pFaultPara->Ks_Mode;			//电源侧阻抗的零序补偿系数设置方式: 0--输入, 1--Ks=KL
		theState.Ks_Mag=pFaultPara->Ks_Mag;	
		theState.Ks_Ang=pFaultPara->Ks_Ang;
		//
		theState.KL_Mode=pFaultPara->KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;				//线路阻抗的零序补偿系数(KL 方式有效)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;				//线路阻抗的零序补偿系数(KR,KX 方式有效)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_Fault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//获取计算结果
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_Fault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_Fault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_Fault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_Fault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//计算转换后故障
	if(pFaultPara->bFaultTrans)
	{
		CFaultCalc_Fault_Ex theState;

		theState.Us=pFaultPara->Us;					//额定电压
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//负荷电流
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//负荷电流角度(相对于对应相的电压, +为超前)
		//
		theState.FaultType=pFaultPara->TransFaultType;			//故障类型: 见 enum FaultFaultType
		theState.FaultDirection=pFaultPara->TransFaultDirection;	//故障方向: 0--正方向, 1--反方向
		theState.FaultUf=pFaultPara->TransFaultUf;				//短路电压(计算模型为定电压时有效)
		theState.FaultIf=pFaultPara->TransFaultIf;				//短路电流(计算模型为定电流时有效)
		theState.FaultZf_Mag=pFaultPara->TransFaultZf_Mag;		//短路阻抗
		theState.FaultZf_Ang=pFaultPara->TransFaultZf_Ang;
		//
		theState.CalcuMode=pFaultPara->CalcuMode;		//短路计算模型: 详见 enum FaultCalcuMode
		theState.Zs_Mag=pFaultPara->Zs_Mag;				//电源侧阻抗(定Zs模型有效)
		theState.Zs_Ang=pFaultPara->Zs_Ang;
		theState.Ks_Mode=pFaultPara->Ks_Mode;			//电源侧阻抗的零序补偿系数设置方式: 0--输入, 1--Ks=KL
		theState.Ks_Mag=pFaultPara->Ks_Mag;
		theState.Ks_Ang=pFaultPara->Ks_Ang;
		//
		theState.KL_Mode=pFaultPara->KL_Mode;			//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;				//线路阻抗的零序补偿系数(KL 方式有效)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;				//线路阻抗的零序补偿系数(KR,KX 方式有效)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_Fault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//获取计算结果
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_TransFault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_TransFault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_TransFault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_TransFault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}

	return hResult;
}

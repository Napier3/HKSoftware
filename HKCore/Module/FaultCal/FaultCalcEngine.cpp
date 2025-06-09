// CalcEngine.cpp : CCalcEngine ��ʵ��

//----------------------------------------------------------------------
//�����µļ���ӿں�������: 
//1. ˽�к��� my_Calculate(...)
//   ���Ӽ���ID (nCalcID) ��Ӧ�ļ����֧(ʹ�������װ�Ľṹ��, ʵ�ֽṹ����Զ���ʼ��)
//2. �ӿں��� Calculate_...(BYTE* lpFaultCalc_...,LONG nSize)
//   ʵ�ּ���(�Խṹ��ָ��Ϊ�������)
//----------------------------------------------------------------------
//2013-3-20: 
//  1. ������չ�ĳ����·���㺯�� Calculate_Fault_Ex(), 
//     ���� Ks_Mode (0-����, 1-Ks=KL) �������򲹳�ϵ�� Ks;
//  2. ������չ��������㺯�� Calculate_Shot_Ex(), 
//     ���� Ks_Mode (0-����, 1-Ks=KL) �������򲹳�ϵ�� Ks;
//----------------------------------------------------------------------
//2013-7-19: 
//  1. ������չ�Ĺ�Ƶ�仯����·���㺯�� Calculate_GPFault_Ex(), 
//     ���� CalcuMode, ��ͬ�ļ��㹫ʽ;
//  2. ������չ�Ĺ�Ƶ�仯����ֵУ�� Calculate_GPDistance_Ex(), 
//     ���� CalcuMode, ��ͬ�ļ��㹫ʽ;
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
// 	//�� IGenericData ����ȡ nCalcID, �ݴ˽��� XML ���� -> �ṹ��
// 	IGenericDataNodePtr ptrRoot;
// 	IEnumGenericNodesPtr ptrEnum;
// 	IGenericDataNodePtr ptrChild;
// 
// 	ptrGenericData->GetRootNode(&ptrRoot);
// 	ptrRoot->Children((IDispatch**)(&ptrEnum));
// 	if(ptrEnum)
// 	{
// 		BSTR bstrChildName;
// 		//ö�ٸ��ڵ��µĸ��ӽڵ�(���ڼ���)
// 		while(ptrEnum->Next(&bstrChildName,&ptrChild)==S_OK)
// 		{
// 			//��ȡ����� ID 
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
// 	case CALCID_LOADSTATE:	//�������и���״̬����
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_LoadState CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_LoadState temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_LoadState((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_FAULT:		//�����·: �������ģ��
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_Fault CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Fault temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_Fault((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_GPFAULT:		//�����·: ��Ƶ�仯������ģ��
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_GPFault CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_GPFault temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_GPFault((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_ABCTOPP:		//����ABC����, �����߷���: ABC -> PP
// 	case CALCID_PPTOABC:		//�����߷���, ����ABC����: PP -> ABC
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_ABCPP CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_ABCPP temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
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
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_ABCTO120:		//����ABC����, ���������: ABC -> 120
// 	case CALCID_120TOABC:		//���������, ����ABC����: 120 -> ABC
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_ABC120 CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_ABC120 temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
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
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_ABCTOPQ:		//���������ѹ/�����������๦�� P,Q,COS
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_PQ CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_PQ temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_PQ((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_SHOT:		//�����������: ���ݽ����������3��״̬�µĵ�ѹ����(����UI)
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_Shot CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Shot temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_Shot((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_DISTANCE:		//���뱣����ֵУ�����
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_Distance CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Distance temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_Distance((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_GPDISTANCE:	//��Ƶ�仯���迹������ֵУ�����
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_GPDistance CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_GPDistance temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_GPDistance((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_OVERCURR:		//����������ֵУ�����
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_OverCurr CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_OverCurr temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_OverCurr((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_NEGSEQCURR:	//�������������ֵУ�����
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_NegSeqCurr CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_NegSeqCurr temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_NegSeqCurr((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_ZEROSEQCURR:	//�������������ֵУ�����
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_ZeroSeqCurr CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_ZeroSeqCurr temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_ZeroSeqCurr((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_DIFF:			//�����: ���� Id,Ir �����������ӵ��� Iabc,Ixyz
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_Diff CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Diff temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_Diff((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_DIFF_SHOT:	//�����: �����
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_Diff_Shot CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Diff_Shot temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_Diff_Shot((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_DIFF_IRID:	//�����: ���� I1[3], I2[3] �����������������
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_Diff_IrId CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Diff_IrId temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_Diff_IrId((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_DIFF_KP:		//�����: ����ϵ�� KP123 ��������
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_Diff_KP CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Diff_KP temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_Diff_KP((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_DIFF5:		//�����: ���� Id,Ir �����������ӵ��� Iabc,Ixy
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_Diff5 CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Diff5 temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_Diff5((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_OSC:		//������: ��ǰ���������, ������װ�� K ��ĵ�ѹ������Чֵ
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_Osc CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Osc temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_Osc((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_OSC_ZK:		//������: ��ǰ���������, ������װ�� K ��Ĳ����迹
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_Osc_Zk CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Osc_Zk temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_Osc_Zk((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_FAULT_EX:		//�����·: �������ģ��, ��չ, ���� Ks_Mode
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_Fault_Ex CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Fault_Ex temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_Fault_Ex((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_SHOT_EX:		//�����������: ��չ, ���� Ks_Mode
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_Shot_Ex CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_Shot_Ex temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_Shot_Ex((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_GPFAULT_EX:		//�����·: ��Ƶ�仯������ģ��, ��չ, ���� CalcuMode
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_GPFault_Ex CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_GPFault_Ex temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_GPFault_Ex((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	case CALCID_GPDISTANCE_EX:	//��Ƶ�仯���迹������ֵУ�����
// 		{
// 			//1. �� XML -> ����Ϊ struct
// 			FaultCalc_GPDistance_Ex CalcuPara;
// 			long nSize=sizeof(CalcuPara);
// 			CFaultCalc_GPDistance_Ex temp;
// 			{
// 				temp.GetStructFromGD(root,strNodeName,nCalcID);
// 				temp.CopyStructTo(&CalcuPara);
// 			}
// 			//2. ����
// 			{
// 				hResult=Calculate_GPDistance_Ex((BYTE*)(&CalcuPara),nSize);
// 				if(hResult==S_OK)
// 					nFlag=1;
// 				else
// 					nFlag=0;
// 			}
// 			//3. �� struct -> ����Ϊ XML
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
// 	//�ü����Ƿ�ɹ��ı�־λ: BSTR
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

//���¸���ɢ�Ľӿں������ڲ����ֱ��ʹ��, �Խṹ��ĸ�ʽ��������
//--------------------------------------------------------------------
//�������и���״̬����
//�������: lpFaultCalc_LoadState -- FaultCalc_LoadState �ṹ��ָ��, 
//                                   ����״̬��������ṹ��
//                                   �������, �������д���ṹ����
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_LoadState(BYTE* lpFaultCalc_LoadState, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_LoadState))
		return E_INVALIDARG;

	//���ݶ�·����Ľṹָ�� pFaultPara, �������״̬
	FaultCalc_LoadState *pFaultPara=(FaultCalc_LoadState *)(lpFaultCalc_LoadState);

	Csub_calcu theCalcu;
	theCalcu.calcu_LoadState(pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang);
	//��д���ṹ�еĶ�·������
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
//�����·����
//�������: lpFaultCalc_Fault -- FaultCalc_Fault �ṹ��ָ��, 
//                                     ��·��������ṹ��
//                                     �������, �������д���ṹ����
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_Fault(BYTE *lpFaultCalc_Fault, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_Fault))
		return E_INVALIDARG;

	//���ݶ�·����Ľṹָ�� pFaultPara, �������״̬
	FaultCalc_Fault *pFaultPara=(FaultCalc_Fault *)(lpFaultCalc_Fault);
	FaultCalc_Fault_Ex fault_Ex;
	
	fault_Ex.Us=pFaultPara->Us;					//���ѹ
	fault_Ex.ILoad_Mag=pFaultPara->ILoad_Mag;	//���ɵ���
	fault_Ex.ILoad_Ang=pFaultPara->ILoad_Ang;	//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	fault_Ex.FaultType=pFaultPara->FaultType;			//��������: �� FaultEnum_FaultType
	fault_Ex.FaultDirection=pFaultPara->FaultDirection;	//���Ϸ���: 0--������, 1--������
	fault_Ex.FaultUf=pFaultPara->FaultUf;				//��·��ѹ(����ģ��Ϊ����ѹʱ��Ч)
	fault_Ex.FaultIf=pFaultPara->FaultIf;				//��·����(����ģ��Ϊ������ʱ��Ч)
	fault_Ex.FaultZf_Mag=pFaultPara->FaultZf_Mag;		//��·�迹
	fault_Ex.FaultZf_Ang=pFaultPara->FaultZf_Ang;
	//
	fault_Ex.CalcuMode=pFaultPara->CalcuMode;		//��·����ģ��: ��� FaultEnum_CalcuMode
	fault_Ex.Zs_Mag=pFaultPara->Zs_Mag;				//��Դ���迹(��Zsģ����Ч)
	fault_Ex.Zs_Ang=pFaultPara->Zs_Ang;
	//---------------------------------------------------------------------------
	fault_Ex.Ks_Mode=0;					//��Դ�迹�����򲹳�ϵ�����÷�ʽ: 0--Ks ����, 1--Ks=KL;
	//---------------------------------------------------------------------------
	fault_Ex.Ks_Mag=pFaultPara->Ks_Mag;				//��Դ���迹�����򲹳�ϵ��(��ֵ,�Ƕ�)
	fault_Ex.Ks_Ang=pFaultPara->Ks_Ang;
	//
	fault_Ex.KL_Mode=pFaultPara->KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	fault_Ex.KL_Mag=pFaultPara->KL_Mag;				//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	fault_Ex.KL_Ang=pFaultPara->KL_Ang;
	fault_Ex.KL_KR=pFaultPara->KL_KR;				//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	fault_Ex.KL_KX=pFaultPara->KL_KX;
	//
	fault_Ex.Result=pFaultPara->Result;

	HRESULT hr=Calculate_Fault_Ex((BYTE*)(&fault_Ex), sizeof(fault_Ex));
	if(hr!=S_OK)
		return E_FAIL;

	//��д������
	pFaultPara->Result=fault_Ex.Result;

	return S_OK;
}

//--------------------------------------------------------------------
//��Ƶ�仯����·����: ר�ö�·����, ������ If (����̱�)
//�������: lpFaultCalc_GPFault -- FaultCalc_GPFault �ṹ��ָ��, 
//                                   ��Ƶ�仯����·��������ṹ��
//                                   �������, �������д���ṹ����
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_GPFault(BYTE *lpFaultCalc_GPFault, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_Fault))
		return E_INVALIDARG;

	//���ݶ�·����Ľṹָ�� pFaultPara, �������״̬
	FaultCalc_GPFault *pFaultPara=(FaultCalc_GPFault *)(lpFaultCalc_GPFault);
	FaultCalc_GPFault_Ex fault_Ex;

	//-----------------------------------------------------------------------------
	fault_Ex.CalcuMode=0;			//0--����̱���ʽ,  1--��̹�ʽ
	//-----------------------------------------------------------------------------
	fault_Ex.Zzd_Mag=pFaultPara->Zzd_Mag;				//�����迹
	fault_Ex.Zzd_Ang=pFaultPara->Zzd_Ang;
	fault_Ex.m=pFaultPara->m;							//У���: m=0.9, 1.1, ...
	fault_Ex.FaultIf=pFaultPara->FaultIf;				//��·����(����ģ��Ϊ������ʱ��Ч)
	fault_Ex.FaultType=pFaultPara->FaultType;			//��������: �� FaultEnum_FaultType
	fault_Ex.FaultDirection=pFaultPara->FaultDirection;	//���Ϸ���: 0--������, 1--������
	//
	fault_Ex.Us=pFaultPara->Us;						//���ѹ
	fault_Ex.ILoad_Mag=pFaultPara->ILoad_Mag;		//���ɵ���
	fault_Ex.ILoad_Ang=pFaultPara->ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	fault_Ex.KL_Mode=pFaultPara->KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	fault_Ex.KL_Mag=pFaultPara->KL_Mag;				//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	fault_Ex.KL_Ang=pFaultPara->KL_Ang;;
	fault_Ex.KL_KR=pFaultPara->KL_KR;				//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	fault_Ex.KL_KX=pFaultPara->KL_KX;
	//
	fault_Ex.Result=pFaultPara->Result;

	HRESULT hr=Calculate_Fault_Ex((BYTE*)(&fault_Ex), sizeof(fault_Ex));
	if(hr!=S_OK)
		return E_FAIL;

	//��д������
	pFaultPara->Result=fault_Ex.Result;

	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_GPFault_Ex(BYTE *lpFaultCalc_GPFault_Ex, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_GPFault_Ex))
		return E_INVALIDARG;

	//���ݶ�·����Ľṹָ�� pFaultPara, �������״̬
	struct FaultCalc_GPFault_Ex *pFaultPara=(FaultCalc_GPFault_Ex *)(lpFaultCalc_GPFault_Ex);
	Csub_calcu theCalcu;
	int phaseNo;
	int nCalcuMode;
	int nFaultType,nFaultDirection;
	float m,k;
	float DZset_Mag,DZset_Ang;
	float R,X;

	nCalcuMode=pFaultPara->CalcuMode;	//0--����̱���ʽ,  1--��̹�ʽ
	nFaultType=pFaultPara->FaultType;
	nFaultDirection=pFaultPara->FaultDirection;
	//У��� m
	m=pFaultPara->m;
	DZset_Mag=pFaultPara->Zzd_Mag;
	DZset_Ang=pFaultPara->Zzd_Ang;
	//���㲹��ϵ�� k
	switch(pFaultPara->KL_Mode)
	{
	case KL:	//(Z0-Z1)/3Z1
		k=pFaultPara->KL_Mag;
		break;
	case KR_KX:	//(R0-R1)/3R1, (X0-X1)/3X1
		//���� m_Kl_KR, m_Kl_KX �� ��·�迹 DZset_Mag, DZset_Ang ���� k
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
	case FAULT_C:   // A, B, C �����· 
		phaseNo=nFaultType;
		theCalcu.f1_gp(nCalcuMode,phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
			pFaultPara->FaultIf, 
			DZset_Mag,DZset_Ang,k,m);
		break;
	case FAULT_AB:
	case FAULT_BC:
	case FAULT_CA:   // AB, BC, CA ����·
		phaseNo=nFaultType-FAULT_AB;
		theCalcu.f2_gp(nCalcuMode,phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
			pFaultPara->FaultIf, 
			DZset_Mag,DZset_Ang,k,m);
		break;
	case FAULT_ABE:
	case FAULT_BCE:
	case FAULT_CAE:   // AB, BC, CA ����ӵ�: ��ʱ�޴˹���
		phaseNo=nFaultType-FAULT_ABE;
		theCalcu.f11_gp(nCalcuMode,phaseNo,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
			pFaultPara->FaultIf, 
			DZset_Mag,DZset_Ang,k,m);
		break;
	case FAULT_ABC:   // ABC �����·: �������ϴ���
		theCalcu.f3_gp(nCalcuMode,nFaultDirection,pFaultPara->Us,pFaultPara->ILoad_Mag,pFaultPara->ILoad_Ang,
			pFaultPara->FaultIf, 
			DZset_Mag,DZset_Ang,k,m);
		break;
	default:
		break;
	}
	//��д���ṹ�еĶ�·������
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
//�߷�������: ABC -> PP
//�������: lpFaultCalc_ABCPP -- FaultCalc_ABCPP �ṹ��ָ��
//                                 �������, �������д���ṹ����
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_ABCtoPP(BYTE *lpFaultCalc_ABCPP, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_ABCPP))
		return E_INVALIDARG;

	//���ݼ���Ľṹָ�� pFaultPara, ����
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
	//��д���ṹ�еļ�����
	int i;
	for(i=0;i<3;i++)
	{
		pFaultPara->Result.Up[i].Mag=theMag[i];
		pFaultPara->Result.Up[i].Ang=theAng[i];
	}

	return S_OK;
}

//--------------------------------------------------------------------
//�߷�������: PP -> ABC
//�������: lpFaultCalc_ABCPP -- FaultCalc_ABCPP �ṹ��ָ��
//                                 �������, �������д���ṹ����
//HRESULT: S_OK -- �ɹ�;
//         E_INVALIDARG -- Uab+Ubc+Uca!=0, �޷�ִ�м���
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_PPtoABC(BYTE *lpFaultCalc_ABCPP, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_ABCPP))
		return E_INVALIDARG;

	//���ݼ���Ľṹָ�� pFaultPara, ����
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
	//��� Uab+Ubc+Uca �Ƿ� = 0, �����޷�ִ�м���
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
	//��д���ṹ�еļ�����
	int i;
	for(i=0;i<3;i++)
	{
		pFaultPara->Result.Up[i].Mag=theMag[i];
		pFaultPara->Result.Up[i].Ang=theAng[i];
	}

	return S_OK;
}

//--------------------------------------------------------------------
//���������: ABC -> 120
//�������: lpFaultCalc_ABC120 -- FaultCalc_ABC120 �ṹ��ָ��
//                                  �������, �������д���ṹ����
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_ABCto120(BYTE *lpFaultCalc_ABC120, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_ABC120))
		return E_INVALIDARG;

	//���ݼ���Ľṹָ�� pFaultPara, ����
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
	//��д���ṹ�еļ�����
	int i;
	for(i=0;i<3;i++)
	{
		pFaultPara->Result.Up[i].Mag=theMag[i];
		pFaultPara->Result.Up[i].Ang=theAng[i];
	}

	return S_OK;
}

//--------------------------------------------------------------------
//���������: 120 -> ABC
//�������: lpFaultCalc_ABC120 -- FaultCalc_ABC120 �ṹ��ָ��
//                                  �������, �������д���ṹ����
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_120toABC(BYTE *lpFaultCalc_ABC120, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_ABC120))
		return E_INVALIDARG;

	//���ݼ���Ľṹָ�� pFaultPara, ����
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
	//��д���ṹ�еļ�����
	int i;
	for(i=0;i<3;i++)
	{
		pFaultPara->Result.Up[i].Mag=theMag[i];
		pFaultPara->Result.Up[i].Ang=theAng[i];
	}

	return S_OK;
}

//--------------------------------------------------------------------
//���๦�ʼ���: U,Ip[3] -> P,Q,COS
//�������: lpFaultCalc_PQ -- FaultCalc_PQ �ṹ��ָ��
//                              �������, �������д���ṹ����
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_PQ(BYTE *lpFaultCalc_PQ, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_PQ))
		return E_INVALIDARG;

	//���ݼ���Ľṹָ�� pFaultPara, ����
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

	//��д���ṹ�еļ�����
	pFaultPara->Result.P=theP;
	pFaultPara->Result.Q=theQ;
	pFaultPara->Result.COS=theCos;

	return S_OK;
}

//--------------------------------------------------------------------
//�������(������)
//�������: ������ (Mag1,Ang1), (Mag2,Ang2) 
//��������: ������ theMag,theAng (��ָ�봫��)
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Comp_Add(float Mag1, float Ang1, float Mag2, float Ang2, float *theMag, float *theAng)
{
	Csub_calcu theCalcu;

	theCalcu.comp_Add(Mag1,Ang1,Mag2,Ang2,theMag,theAng);

	return S_OK;
}

//--------------------------------------------------------------------
//�������(������)
//�������: ������ (Mag1,Ang1), (Mag2,Ang2) 
//��������: ������ theMag,theAng (��ָ�봫��)
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Comp_Sub(float Mag1, float Ang1, float Mag2, float Ang2, float *theMag, float *theAng)
{
	Csub_calcu theCalcu;

	theCalcu.comp_Sub(Mag1,Ang1,Mag2,Ang2,theMag,theAng);

	return S_OK;
}

//--------------------------------------------------------------------
//�������(ֱ������)
//�������: ֱ������ (x1,y1), (x2,y2) 
//��������: ֱ������ theX,theY (��ָ�봫��)
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Comp_Mul(float x1, float y1, float x2, float y2, float *theX, float *theY)
{
	Csub_calcu theCalcu;

	theCalcu.comp_Mult(x1,y1,x2,y2,theX,theY);

	return S_OK;
}

//--------------------------------------------------------------------
//�������(ֱ������)
//�������: ֱ������ (x1,y1), (x2,y2) 
//��������: ֱ������ theX,theY (��ָ�봫��)
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Comp_Div(float x1, float y1, float x2, float y2, float *theX, float *theY)
{
	Csub_calcu theCalcu;

	theCalcu.comp_Divi(x1,y1,x2,y2,theX,theY);

	return S_OK;
}

//--------------------------------------------------------------------
//������ -> ֱ������
//�������: ������ Mag,Ang 
//��������: ֱ������ x,y (��ָ�봫��)
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Comp_POtoXY(float Mag, float Ang, float *x, float *y)
{
	Csub_calcu theCalcu;

	theCalcu.po_to_xy(Mag,Ang,x,y);

	return S_OK;
}

//--------------------------------------------------------------------
//ֱ������ -> ������
//�������: ֱ������ x,y
//��������: ������ Mag,Ang (��ָ�봫��)
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Comp_XYtoPO(float x, float y, float *Mag, float *Ang)
{
	Csub_calcu theCalcu;

	theCalcu.xy_to_po(x,y,Mag,Ang);

	return S_OK;
}

//--------------------------------------------------------------------
//��������: ���� 3 ��״̬�µĵ�ѹ����
//�������: lpFaultCalc_Shot -- FaultCalc_Shot �ṹ��ָ��, 
//                              �������, �������д���ṹ����
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_Shot(BYTE* lpFaultCalc_Shot, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_Shot))
		return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);
	FaultCalc_Shot_Ex shot_Ex;

	shot_Ex.Us=pFaultPara->Us;					//���ѹ
	shot_Ex.ILoad_Mag=pFaultPara->ILoad_Mag;	//���ɵ���
	shot_Ex.ILoad_Ang=pFaultPara->ILoad_Ang;	//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	shot_Ex.FaultType=pFaultPara->FaultType;			//��������: �� FaultEnum_FaultType
	shot_Ex.FaultDirection=pFaultPara->FaultDirection;	//���Ϸ���: 0--������, 1--������
	shot_Ex.FaultUf=pFaultPara->FaultUf;				//��·��ѹ(����ģ��Ϊ����ѹʱ��Ч)
	shot_Ex.FaultIf=pFaultPara->FaultIf;				//��·����(����ģ��Ϊ������ʱ��Ч)
	shot_Ex.FaultZf_Mag=pFaultPara->FaultZf_Mag;		//��·�迹
	shot_Ex.FaultZf_Ang=pFaultPara->FaultZf_Ang;
	//
	//����ת��
	shot_Ex.bFaultTrans=pFaultPara->bFaultTrans;			//�Ƿ�������ת��: 0--��, 1--��;
	shot_Ex.TransFaultType=pFaultPara->TransFaultType;			//��������: �� FaultEnum_FaultType
	shot_Ex.TransFaultDirection=pFaultPara->TransFaultDirection;	//���Ϸ���: 0--������, 1--������
	shot_Ex.TransFaultUf=pFaultPara->TransFaultUf;				//��·��ѹ(����ģ��Ϊ����ѹʱ��Ч)
	shot_Ex.TransFaultIf=pFaultPara->TransFaultIf;				//��·����(����ģ��Ϊ������ʱ��Ч)
	shot_Ex.TransFaultZf_Mag=pFaultPara->TransFaultZf_Mag;		//��·�迹
	shot_Ex.TransFaultZf_Ang=pFaultPara->TransFaultZf_Ang;
	//
	shot_Ex.CalcuMode=pFaultPara->CalcuMode;		//��·����ģ��: ��� FaultEnum_CalcuMode
	shot_Ex.Zs_Mag=pFaultPara->Zs_Mag;				//��Դ���迹(��Zsģ����Ч)
	shot_Ex.Zs_Ang=pFaultPara->Zs_Ang;
	//---------------------------------------------------------------------------
	shot_Ex.Ks_Mode=0;					//��Դ�迹�����򲹳�ϵ�����÷�ʽ: 0--Ks ����, 1--Ks=KL;
	//---------------------------------------------------------------------------
	shot_Ex.Ks_Mag=pFaultPara->Ks_Mag;				//��Դ���迹�����򲹳�ϵ��(��ֵ,�Ƕ�)
	shot_Ex.Ks_Ang=pFaultPara->Ks_Ang;
	//
	shot_Ex.KL_Mode=pFaultPara->KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	shot_Ex.KL_Mag=pFaultPara->KL_Mag;				//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	shot_Ex.KL_Ang=pFaultPara->KL_Ang;
	shot_Ex.KL_KR=pFaultPara->KL_KR;				//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	shot_Ex.KL_KX=pFaultPara->KL_KX;
	//
	shot_Ex.Result=pFaultPara->Result;

	HRESULT hr=Calculate_Shot_Ex((BYTE*)(&shot_Ex), sizeof(shot_Ex));
	if(hr!=S_OK)
		return E_FAIL;

	//��д������
	pFaultPara->Result=shot_Ex.Result;

	return S_OK;
}

//--------------------------------------------------------------------
//���뱣����ֵУ��: ���� 2 ��״̬�µĵ�ѹ����(�޹���ת��, �̶�����ģ��Ϊ������)
//�������: lpFaultCalc_Distance -- FaultCalc_Distance �ṹ��ָ��, 
//                                  �������, �������д���ṹ����
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_Distance(BYTE* lpFaultCalc_Distance, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_Distance))
		return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	FaultCalc_Distance *pFaultPara=(FaultCalc_Distance *)(lpFaultCalc_Distance);
	HRESULT hResult=S_OK;
	int i;

	//�������ǰ
	{
		CFaultCalc_LoadState theState;

		theState.Us=pFaultPara->Us;
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;
		//
		hResult=Calculate_LoadState((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//��ȡ������
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_PreFault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_PreFault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_PreFault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_PreFault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//�������
	{
		CFaultCalc_Fault theState;

		theState.Us=pFaultPara->Us;					//���ѹ
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//���ɵ���
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
		//
		theState.FaultType=pFaultPara->FaultType;			//��������: �� enum FaultFaultType
		theState.FaultDirection=pFaultPara->FaultDirection;	//���Ϸ���: 0--������, 1--������
		theState.FaultIf=pFaultPara->FaultIf;				//��·����(����ģ��Ϊ������ʱ��Ч)
		//
		//���뱣����ֵУ��: �����·�迹
		theState.FaultZf_Mag=pFaultPara->Zzd_Mag*pFaultPara->Zf_Ratio;		//��·�迹
		theState.FaultZf_Ang=pFaultPara->Zzd_Ang;
		//
		theState.CalcuMode=CALCUMODE_IF;			//��·����ģ��: �̶�Ϊ������
		//
		theState.KL_Mode=pFaultPara->KL_Mode;		//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_Fault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//��ȡ������
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_Fault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_Fault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_Fault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_Fault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//����ת��: ��, ȡ��ֵ = ����
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
//��Ƶ�仯�����뱣����ֵУ��: ���� 2 ��״̬�µĵ�ѹ����(�޹���ת��)
//�������: lpFaultCalc_GPDistance -- FaultCalc_GPDistance �ṹ��ָ��, 
//                                    �������, �������д���ṹ����
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_GPDistance(BYTE* lpFaultCalc_GPDistance, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_GPDistance))
		return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	FaultCalc_GPDistance *pFaultPara=(FaultCalc_GPDistance *)(lpFaultCalc_GPDistance);
	FaultCalc_GPDistance_Ex gpDistance_Ex;

	//-----------------------------------------------------------------------------
	gpDistance_Ex.CalcuMode=0;			//0--����̱���ʽ,  1--��̹�ʽ
	//-----------------------------------------------------------------------------
	gpDistance_Ex.Zzd_Mag=pFaultPara->Zzd_Mag;			//�����迹
	gpDistance_Ex.Zzd_Ang=pFaultPara->Zzd_Ang;
	gpDistance_Ex.m=pFaultPara->m;						//У���: m=0.9, 1.1, ...
	gpDistance_Ex.FaultIf=pFaultPara->FaultIf;			//��·����(����ģ��: ������)
	gpDistance_Ex.FaultType=pFaultPara->FaultType;		//��������: �� FaultEnum_FaultType
	gpDistance_Ex.FaultDirection=pFaultPara->FaultDirection;		//���Ϸ���: 0--������, 1--������
	//
	gpDistance_Ex.Us=pFaultPara->Us;					//���ѹ
	gpDistance_Ex.ILoad_Mag=pFaultPara->ILoad_Mag;		//���ɵ���
	gpDistance_Ex.ILoad_Ang=pFaultPara->ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	gpDistance_Ex.KL_Mode=pFaultPara->KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	gpDistance_Ex.KL_Mag=pFaultPara->KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	gpDistance_Ex.KL_Ang=pFaultPara->KL_Ang;
	gpDistance_Ex.KL_KR=pFaultPara->KL_KR;				//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	gpDistance_Ex.KL_KX=pFaultPara->KL_KX;
	//
	gpDistance_Ex.Result=pFaultPara->Result;

	HRESULT hr=Calculate_GPDistance_Ex((BYTE*)(&gpDistance_Ex), sizeof(gpDistance_Ex));
	if(hr!=S_OK)
		return E_FAIL;

	//��д������
	pFaultPara->Result=gpDistance_Ex.Result;

	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_GPDistance_Ex(BYTE* lpFaultCalc_GPDistance, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_GPDistance))
		return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	FaultCalc_GPDistance *pFaultPara=(FaultCalc_GPDistance *)(lpFaultCalc_GPDistance);
	HRESULT hResult=S_OK;
	int i;

	//�������ǰ
	{
		CFaultCalc_LoadState theState;

		theState.Us=pFaultPara->Us;
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;
		//
		hResult=Calculate_LoadState((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//��ȡ������
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_PreFault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_PreFault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_PreFault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_PreFault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//�������
	{
		CFaultCalc_GPFault theState;

		theState.Zzd_Mag=pFaultPara->Zzd_Mag;		//�����迹
		theState.Zzd_Ang=pFaultPara->Zzd_Ang;
		theState.m=pFaultPara->m;					//У���: m=0.9, 1.1, ...
		//
		theState.Us=pFaultPara->Us;					//���ѹ
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//���ɵ���
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
		//
		theState.FaultType=pFaultPara->FaultType;			//��������: �� enum FaultFaultType
		theState.FaultDirection=pFaultPara->FaultDirection;	//���Ϸ���: 0--������, 1--������
		theState.FaultIf=pFaultPara->FaultIf;				//��·����(����ģ��Ϊ������ʱ��Ч)
		//
		theState.KL_Mode=pFaultPara->KL_Mode;		//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_GPFault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//��ȡ������
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_Fault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_Fault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_Fault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_Fault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//����ת��: ��, ȡ��ֵ = ����
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
//����������ֵУ��: ���� 2 ��״̬�µĵ�ѹ����(�޹���ת��, �̶�����ģ��Ϊ������)
//�������: lpFaultCalc_OverCurr -- FaultCalc_OverCurr �ṹ��ָ��, 
//                                  �������, �������д���ṹ����
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_OverCurr(BYTE* lpFaultCalc_OverCurr, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_OverCurr))
		return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	FaultCalc_OverCurr *pFaultPara=(FaultCalc_OverCurr *)(lpFaultCalc_OverCurr);
	HRESULT hResult=S_OK;
	int i;

	//�������ǰ
	{
		CFaultCalc_LoadState theState;

		theState.Us=pFaultPara->Us;
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;
		//
		hResult=Calculate_LoadState((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//��ȡ������
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_PreFault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_PreFault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_PreFault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_PreFault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//�������
	{
		CFaultCalc_Fault theState;

		theState.Us=pFaultPara->Us;					//���ѹ
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//���ɵ���
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
		//
		theState.FaultType=pFaultPara->FaultType;			//��������: �� enum FaultFaultType
		theState.FaultDirection=pFaultPara->FaultDirection;	//���Ϸ���: 0--������, 1--������
		//
		//����, �����·����
		theState.FaultIf=pFaultPara->Izd*pFaultPara->If_Ratio;
		//
		theState.FaultZf_Mag=pFaultPara->Zf_Mag;		//��·�迹
		theState.FaultZf_Ang=pFaultPara->Zf_Ang;
		//
		theState.CalcuMode=CALCUMODE_IF;			//��·����ģ��: �̶�Ϊ������
		//
		theState.KL_Mode=pFaultPara->KL_Mode;		//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_Fault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//��ȡ������
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_Fault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_Fault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_Fault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_Fault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//����ת��: ��, ȡ��ֵ = ����
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
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_NegSeqCurr))
		return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	FaultCalc_NegSeqCurr *pFaultPara=(FaultCalc_NegSeqCurr *)(lpFaultCalc_NegSeqCurr);
	if(pFaultPara->FaultType==FAULT_ABE
		|| pFaultPara->FaultType==FAULT_BCE
		|| pFaultPara->FaultType==FAULT_CAE
		||pFaultPara->FaultType==FAULT_ABC)	
	{
		//���Ϲ���, �޷����㸺��
		return E_INVALIDARG;
	}

	HRESULT hResult=S_OK;
	int i;

	//�������ǰ
	{
		CFaultCalc_LoadState theState;

		theState.Us=pFaultPara->Us;
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;
		//
		hResult=Calculate_LoadState((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//��ȡ������
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_PreFault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_PreFault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_PreFault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_PreFault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//�������
	{
		CFaultCalc_Fault theState;

		theState.Us=pFaultPara->Us;					//���ѹ
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//���ɵ���
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
		//
		theState.FaultType=pFaultPara->FaultType;			//��������: �� enum FaultFaultType
		theState.FaultDirection=pFaultPara->FaultDirection;	//���Ϸ���: 0--������, 1--������
		//
		//�������, �����·����
		theState.FaultIf=pFaultPara->Izd*pFaultPara->If_Ratio;
		switch(pFaultPara->FaultType)
		{
		case FAULT_A:
		case FAULT_B:
		case FAULT_C:	//����ӵ�: I1=I2=I0, ��������� If = 3 * I1
			theState.FaultIf*=3.0f;
			break;
		case FAULT_AB:
		case FAULT_BC:
		case FAULT_CA:	//������: I1=-I2, ��������� If = ��3 * I1
			theState.FaultIf*=(float)sqrt(3.0);
			break;
		case FAULT_ABE:
		case FAULT_BCE:
		case FAULT_CAE:	//����ӵ�: û��һ���̶��ı���
			hResult=E_INVALIDARG;
			break;
		case FAULT_ABC:	//�����·: �޸���
			hResult=E_INVALIDARG;
			break;
		default:
			hResult=E_INVALIDARG;
			break;
		}
		if(hResult!=S_OK)
			return hResult;
		theState.FaultZf_Mag=pFaultPara->Zf_Mag;		//��·�迹
		theState.FaultZf_Ang=pFaultPara->Zf_Ang;
		//
		theState.CalcuMode=CALCUMODE_IF;			//��·����ģ��: �̶�Ϊ������
		//
		theState.KL_Mode=pFaultPara->KL_Mode;		//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_Fault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//��ȡ������
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_Fault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_Fault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_Fault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_Fault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//����ת��: ��, ȡ��ֵ = ����
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
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_ZeroSeqCurr))
		return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	FaultCalc_ZeroSeqCurr *pFaultPara=(FaultCalc_ZeroSeqCurr *)(lpFaultCalc_ZeroSeqCurr);
	if(	pFaultPara->FaultType==FAULT_AB
		|| pFaultPara->FaultType==FAULT_BC
		|| pFaultPara->FaultType==FAULT_CA
		|| pFaultPara->FaultType==FAULT_ABE
		|| pFaultPara->FaultType==FAULT_BCE
		|| pFaultPara->FaultType==FAULT_CAE
		||pFaultPara->FaultType==FAULT_ABC)	
	{
		//���Ϲ���, �޷���������
		return E_INVALIDARG;
	}

	HRESULT hResult=S_OK;
	int i;

	//�������ǰ
	{
		CFaultCalc_LoadState theState;

		theState.Us=pFaultPara->Us;
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;
		//
		hResult=Calculate_LoadState((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//��ȡ������
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_PreFault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_PreFault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_PreFault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_PreFault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//�������
	if(hResult==S_OK)
	{
		CFaultCalc_Fault theState;

		theState.Us=pFaultPara->Us;					//���ѹ
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//���ɵ���
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
		//
		theState.FaultType=pFaultPara->FaultType;			//��������: �� enum FaultFaultType
		theState.FaultDirection=pFaultPara->FaultDirection;	//���Ϸ���: 0--������, 1--������
		//
		//�������, �����·����
		theState.FaultIf=pFaultPara->Izd*pFaultPara->If_Ratio;
		switch(pFaultPara->FaultType)
		{
		case FAULT_A:
		case FAULT_B:
		case FAULT_C:	//����ӵ�: I1=I2=I0, ��������� If = 3 * I1
			theState.FaultIf*=3.0f;
			break;
		case FAULT_AB:
		case FAULT_BC:
		case FAULT_CA:	//������: I1=-I2, ������
			hResult=E_INVALIDARG;
			break;
		case FAULT_ABE:
		case FAULT_BCE:
		case FAULT_CAE:	//����ӵ�: û��һ���̶��ı���
			hResult=E_INVALIDARG;
			break;
		case FAULT_ABC:	//�����·: ������
			hResult=E_INVALIDARG;
			break;
		default:
			hResult=E_INVALIDARG;
			break;
		}
		if(hResult!=S_OK)
			return hResult;
		theState.FaultZf_Mag=pFaultPara->Zf_Mag;		//��·�迹
		theState.FaultZf_Ang=pFaultPara->Zf_Ang;
		//
		theState.CalcuMode=CALCUMODE_IF;			//��·����ģ��: �̶�Ϊ������
		//
		theState.KL_Mode=pFaultPara->KL_Mode;		//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_Fault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//��ȡ������
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_Fault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_Fault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_Fault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_Fault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//����ת��: ��, ȡ��ֵ = ����
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
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//��д���ṹ�еļ�����



	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_Diff_KP(BYTE* lpFaultCalc_Diff_KP, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//��д���ṹ�еļ�����



	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_Diff_Shot(BYTE* lpFaultCalc_Diff_Shot, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//��д���ṹ�еļ�����



	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_Diff_IrId(BYTE* lpFaultCalc_Diff_IrId, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//��д���ṹ�еļ�����



	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_Diff5(BYTE* lpFaultCalc_Diff5, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//��д���ṹ�еļ�����



	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_Osc(BYTE* lpFaultCalc_Osc, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//��д���ṹ�еļ�����



	return S_OK;
}

STDMETHODIMP CCalcEngine::Calculate_Osc_Zk(BYTE* lpFaultCalc_Osc_Zk, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	//if(nSize!=sizeof(FaultCalc_Shot))
	//	return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	//FaultCalc_Shot *pFaultPara=(FaultCalc_Shot *)(lpFaultCalc_Shot);




	//��д���ṹ�еļ�����



	return S_OK;
}

//--------------------------------------------------------------------
//�����·����
//�������: lpFaultCalc_Fault -- FaultCalc_Fault �ṹ��ָ��, 
//                                     ��·��������ṹ��
//                                     �������, �������д���ṹ����
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_Fault_Ex(BYTE *lpFaultCalc_Fault_Ex, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_Fault_Ex))
		return E_INVALIDARG;

	//���ݶ�·����Ľṹָ�� pFaultPara, �������״̬
	FaultCalc_Fault_Ex *pFaultPara=(FaultCalc_Fault_Ex *)(lpFaultCalc_Fault_Ex);

	Csub_calcu theCalcu;
	int phaseNo;
	int nFaultType,nFaultDirection;
	float Zl_Mag,Zl_Ang;
	float KL_Re,KL_Im;	//�����·�迹�����򲹳�ϵ����ʵ�����鲿
	float Ks_Re,Ks_Im;
	float temp,R,X;

	nFaultType=pFaultPara->FaultType;
	nFaultDirection=pFaultPara->FaultDirection;
	Zl_Mag=pFaultPara->FaultZf_Mag;
	Zl_Ang=pFaultPara->FaultZf_Ang; 
	//���㲹��ϵ�� KL
	switch(pFaultPara->KL_Mode)
	{
	case KL:		//(Z0-Z1)/3Z1
		theCalcu.po_to_xy(pFaultPara->KL_Mag,pFaultPara->KL_Ang,&R,&X);
		KL_Re=R;
		KL_Im=X;
		break;
	case KR_KX:		//(R0-R1)/3R1, (X0-X1)/3X1
		//���� m_Kl_KR, m_Kl_KX �� ��·�迹 Zl_Mag, Zl_Ang ���� KL
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
	//���� Ks, ���� Ks_Mode: 0--Ks ����, 1--Ks=KL;
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
	case FAULT_C:   // A, B, C �����· 
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
	case FAULT_CA:   // AB, BC, CA ����·
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
	case FAULT_CAE:   // AB, BC, CA ����ӵ�
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
	case FAULT_ABC:   // ABC �����·
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
	//��д���ṹ�еĶ�·������
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
//��������: ���� 3 ��״̬�µĵ�ѹ����
//�������: lpFaultCalc_Shot -- FaultCalc_Shot �ṹ��ָ��, 
//                              �������, �������д���ṹ����
//--------------------------------------------------------------------
STDMETHODIMP CCalcEngine::Calculate_Shot_Ex(BYTE* lpFaultCalc_Shot_Ex, LONG nSize)
{
	//������ݽṹ struct ��ƥ���� (���޷���֤����ȫ������ʼ��)
	if(nSize!=sizeof(FaultCalc_Shot_Ex))
		return E_INVALIDARG;

	//���ݽṹָ�� pFaultPara, ����
	FaultCalc_Shot_Ex *pFaultPara=(FaultCalc_Shot_Ex *)(lpFaultCalc_Shot_Ex);
	HRESULT hResult=S_OK;
	int i;

	//�������ǰ
	{
		CFaultCalc_LoadState theState;

		theState.Us=pFaultPara->Us;
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;
		//
		hResult=Calculate_LoadState((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//��ȡ������
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_PreFault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_PreFault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_PreFault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_PreFault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//�������
	{
		CFaultCalc_Fault_Ex theState;

		theState.Us=pFaultPara->Us;					//���ѹ
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//���ɵ���
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
		//
		theState.FaultType=pFaultPara->FaultType;			//��������: �� enum FaultFaultType
		theState.FaultDirection=pFaultPara->FaultDirection;	//���Ϸ���: 0--������, 1--������
		theState.FaultUf=pFaultPara->FaultUf;				//��·��ѹ(����ģ��Ϊ����ѹʱ��Ч)
		theState.FaultIf=pFaultPara->FaultIf;				//��·����(����ģ��Ϊ������ʱ��Ч)
		theState.FaultZf_Mag=pFaultPara->FaultZf_Mag;		//��·�迹
		theState.FaultZf_Ang=pFaultPara->FaultZf_Ang;
		//
		theState.CalcuMode=pFaultPara->CalcuMode;		//��·����ģ��: ��� enum FaultCalcuMode
		theState.Zs_Mag=pFaultPara->Zs_Mag;				//��Դ���迹(��Zsģ����Ч)
		theState.Zs_Ang=pFaultPara->Zs_Ang;
		theState.Ks_Mode=pFaultPara->Ks_Mode;			//��Դ���迹�����򲹳�ϵ�����÷�ʽ: 0--����, 1--Ks=KL
		theState.Ks_Mag=pFaultPara->Ks_Mag;	
		theState.Ks_Ang=pFaultPara->Ks_Ang;
		//
		theState.KL_Mode=pFaultPara->KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;				//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;				//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_Fault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//��ȡ������
			for(i=0;i<3;i++)
			{
				pFaultPara->Result.Up_Fault[i].Mag=theState.Result.Up[i].Mag;
				pFaultPara->Result.Up_Fault[i].Ang=theState.Result.Up[i].Ang;
				pFaultPara->Result.Ip_Fault[i].Mag=theState.Result.Ip[i].Mag;
				pFaultPara->Result.Ip_Fault[i].Ang=theState.Result.Ip[i].Ang;
			}
		}
	}
	//����ת�������
	if(pFaultPara->bFaultTrans)
	{
		CFaultCalc_Fault_Ex theState;

		theState.Us=pFaultPara->Us;					//���ѹ
		theState.ILoad_Mag=pFaultPara->ILoad_Mag;	//���ɵ���
		theState.ILoad_Ang=pFaultPara->ILoad_Ang;	//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
		//
		theState.FaultType=pFaultPara->TransFaultType;			//��������: �� enum FaultFaultType
		theState.FaultDirection=pFaultPara->TransFaultDirection;	//���Ϸ���: 0--������, 1--������
		theState.FaultUf=pFaultPara->TransFaultUf;				//��·��ѹ(����ģ��Ϊ����ѹʱ��Ч)
		theState.FaultIf=pFaultPara->TransFaultIf;				//��·����(����ģ��Ϊ������ʱ��Ч)
		theState.FaultZf_Mag=pFaultPara->TransFaultZf_Mag;		//��·�迹
		theState.FaultZf_Ang=pFaultPara->TransFaultZf_Ang;
		//
		theState.CalcuMode=pFaultPara->CalcuMode;		//��·����ģ��: ��� enum FaultCalcuMode
		theState.Zs_Mag=pFaultPara->Zs_Mag;				//��Դ���迹(��Zsģ����Ч)
		theState.Zs_Ang=pFaultPara->Zs_Ang;
		theState.Ks_Mode=pFaultPara->Ks_Mode;			//��Դ���迹�����򲹳�ϵ�����÷�ʽ: 0--����, 1--Ks=KL
		theState.Ks_Mag=pFaultPara->Ks_Mag;
		theState.Ks_Ang=pFaultPara->Ks_Ang;
		//
		theState.KL_Mode=pFaultPara->KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
		theState.KL_Mag=pFaultPara->KL_Mag;				//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
		theState.KL_Ang=pFaultPara->KL_Ang;
		theState.KL_KR=pFaultPara->KL_KR;				//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
		theState.KL_KX=pFaultPara->KL_KX;
		//
		hResult=Calculate_Fault((BYTE*)(&theState),sizeof(theState));
		if(hResult==S_OK)
		{
			//��ȡ������
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

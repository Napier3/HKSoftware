//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//LogicShapeMngrGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CVFLOWSHAPEBASE       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CVFLOWSHAPESBASE       (MngrCLASSID_EXLISTCLASS + 0X00000001)
#define MNGRCLASSID_CVFLOWSHAPELINE       (MngrCLASSID_EXLISTCLASS + 0X00000002)
#define MNGRCLASSID_CVFLOWSHAPE       (MngrCLASSID_EXLISTCLASS + 0X00000003)
#define MNGRCLASSID_CVFLOWSHAPE_DATA       (MngrCLASSID_EXLISTCLASS + 0X00000004)
#define MNGRCLASSID_CVFLOWSHAPE_LOGIC       (MngrCLASSID_EXLISTCLASS + 0X00000005)
#define MNGRCLASSID_CVFLOWSHAPE_BRANCH       (MngrCLASSID_EXLISTCLASS + 0X00000006)
#define MNGRCLASSID_CVFLOWSHAPE_EXPRESSION       (MngrCLASSID_EXLISTCLASS + 0X00000007)
#define MNGRCLASSID_CVFLOWSHAPE_THRESHOLD       (MngrCLASSID_EXLISTCLASS + 0X00000008)
#define MNGRCLASSID_CVFLOWSHAPES       (MngrCLASSID_EXLISTCLASS + 0X00000009)
#define MNGRCLASSID_CVFLOWSHAPELINES       (MngrCLASSID_EXLISTCLASS + 0X0000000A)
#define MNGRCLASSID_CVFLOWEXEC_VISIO       (MngrCLASSID_EXLISTCLASS + 0X0000000B)
#define MNGRCLASSID_CVFLOWSHAPEPROPERTY       (MngrCLASSID_BASECLASS + 0X0000000C)


#define VFLOW_VISIO_SHAPE_TYPE_DATA                                     _T("DATA")
#define VFLOW_VISIO_SHAPE_TYPE_LOGIC                                    _T("LOGIC")
#define VFLOW_VISIO_SHAPE_TYPE_EXPRESION                                _T("EXPRESION")
#define VFLOW_VISIO_SHAPE_TYPE_FLOW                                     _T("FLOW")
#define VFLOW_VISIO_SHAPE_TYPE_BRANCH                                   _T("BRANCH")
#define VFLOW_VISIO_SHAPE_TYPE_Threshold                                _T("Threshold")

#define VFLOW_VISIO_TAG_VALUE                                           _T("value")//���Զ�������Shape��Data3��ֵ����������ID,��Ҫ������ʾ
#define VFLOW_VISIO_SETTING_VALUE                                       _T("setting_value")//���Զ����е�����ֵ,��Ҫ���ڷ��Žڵ�
#define VFLOW_VISIO_REAL_VALUE                                          _T("real_value")//���Զ����е�ʵ��ֵ,��Ҫ���ڷ��Žڵ�
#define VFLOW_VISIO_ACT_TIME                                            _T("act_time")//���Զ����еĶ���ʱ��,һ�����ڽ���߼��ڵ���,���߼��ڵ��������жϣ�������и����ԣ����߼����Ϊ0�����ֵΪ"--"
#define VFLOW_VISIO_DATA_TYPE                                           _T("data_type")//���Զ����������ͣ��������Ͳ�����ʱ��Ĭ��Ϊ����
#define VFLOW_VISIO_UNIT                                                _T("unit")//���Զ���λ


class CLogicShapeMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CLogicShapeMngrXmlRWKeys();
	virtual ~CLogicShapeMngrXmlRWKeys();
	static long g_nMngrRef;

public:
	static CLogicShapeMngrXmlRWKeys* g_pXmlKeys;
	static CLogicShapeMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCVFlowShapePropertyKey; //shape-property
	BSTR m_strCVFlowExec_VisioKey; //flow-exec-visio
	BSTR m_strCVFlowShapeLinesKey; //flow-shape-lines
	BSTR m_strCVFlowShapesKey; //flow-shapes
	BSTR m_strCVFlowShape_ThresholdKey; //flow-shape-threshold
	BSTR m_strCVFlowShape_ExpressionKey; //flow-shape-expression
	BSTR m_strCVFlowShape_BranchKey; //flow-shape-branch
	BSTR m_strCVFlowShape_LogicKey; //flow-shape-logic
	BSTR m_strCVFlowShape_DataKey; //flow-shape-data
	BSTR m_strCVFlowShapeKey; //flow-shape
	BSTR m_strCVFlowShapeLineKey; //flow-shape-line
	BSTR m_strCVFlowShapesBaseKey; //flow-shapes-base
	BSTR m_strCVFlowShapeBaseKey; //flow-shape-base
	BSTR m_strVisioIDKey; //visio-id
	BSTR m_strDataTypeKey; //data-type
	BSTR m_strHelpKey; //help
	BSTR m_strData1Key; //data1
	BSTR m_strData2Key; //data2
	BSTR m_strData3Key; //data3
	BSTR m_strUnitKey; //unit
	BSTR m_strValueKey; //value
	BSTR m_strPathKey; //path
	BSTR m_strRowIndexKey; //row-index

public:
	static BSTR CVFlowShapePropertyKey()  {   return g_pXmlKeys->m_strCVFlowShapePropertyKey;  }
	static BSTR CVFlowExec_VisioKey()  {   return g_pXmlKeys->m_strCVFlowExec_VisioKey;  }
	static BSTR CVFlowShapeLinesKey()  {   return g_pXmlKeys->m_strCVFlowShapeLinesKey;  }
	static BSTR CVFlowShapesKey()  {   return g_pXmlKeys->m_strCVFlowShapesKey;  }
	static BSTR CVFlowShape_ThresholdKey()  {   return g_pXmlKeys->m_strCVFlowShape_ThresholdKey;  }
	static BSTR CVFlowShape_ExpressionKey()  {   return g_pXmlKeys->m_strCVFlowShape_ExpressionKey;  }
	static BSTR CVFlowShape_BranchKey()  {   return g_pXmlKeys->m_strCVFlowShape_BranchKey;  }
	static BSTR CVFlowShape_LogicKey()  {   return g_pXmlKeys->m_strCVFlowShape_LogicKey;  }
	static BSTR CVFlowShape_DataKey()  {   return g_pXmlKeys->m_strCVFlowShape_DataKey;  }
	static BSTR CVFlowShapeKey()  {   return g_pXmlKeys->m_strCVFlowShapeKey;  }
	static BSTR CVFlowShapeLineKey()  {   return g_pXmlKeys->m_strCVFlowShapeLineKey;  }
	static BSTR CVFlowShapesBaseKey()  {   return g_pXmlKeys->m_strCVFlowShapesBaseKey;  }
	static BSTR CVFlowShapeBaseKey()  {   return g_pXmlKeys->m_strCVFlowShapeBaseKey;  }
	static BSTR VisioIDKey()  {   return g_pXmlKeys->m_strVisioIDKey;  }
	static BSTR DataTypeKey()  {   return g_pXmlKeys->m_strDataTypeKey;  }
	static BSTR HelpKey()  {   return g_pXmlKeys->m_strHelpKey;  }
	static BSTR Data1Key()  {   return g_pXmlKeys->m_strData1Key;  }
	static BSTR Data2Key()  {   return g_pXmlKeys->m_strData2Key;  }
	static BSTR Data3Key()  {   return g_pXmlKeys->m_strData3Key;  }
	static BSTR UnitKey()  {   return g_pXmlKeys->m_strUnitKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR PathKey()  {   return g_pXmlKeys->m_strPathKey;  }
	static BSTR RowIndexKey()  {   return g_pXmlKeys->m_strRowIndexKey;  }
};



class CLogicShapeMngrConstGlobal
{
private:
	CLogicShapeMngrConstGlobal();
	virtual ~CLogicShapeMngrConstGlobal();

public:
	static CLogicShapeMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CLogicShapeMngrConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};

BOOL Global_GetValueUnit(const CString &strData,CString &strValue, CString &strUnit);

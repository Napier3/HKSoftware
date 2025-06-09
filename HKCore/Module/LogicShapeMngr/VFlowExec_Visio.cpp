//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowExec_Visio.cpp  CVFlowExec_Visio


#include "stdafx.h"
#include "VFlowExec_Visio.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVFlowExec_Visio::CVFlowExec_Visio()
{
	//初始化属性

	//初始化成员变量
}

CVFlowExec_Visio::~CVFlowExec_Visio()
{
	DeleteAllCalcShapes();
	m_oOrigDataPropertysRef.RemoveAll();
	m_oOrigDataShapesRef.RemoveAll();
}

void CVFlowExec_Visio::DeleteAllCalcShapes()
{
	POS pos = GetHeadPosition();
	CExBaseList *pCurList = NULL;

	while(pos)
	{
		pCurList = (CExBaseList *)GetNext(pos);
		pCurList->RemoveAll();
	}

	DeleteAll();
}

long CVFlowExec_Visio::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowExec_Visio::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowExec_Visio::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CVFlowExec_Visio::InitAfterRead()
{
}

BOOL CVFlowExec_Visio::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVFlowExec_Visio *p = (CVFlowExec_Visio*)pObj;

	return TRUE;
}

BOOL CVFlowExec_Visio::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CVFlowExec_Visio *p = (CVFlowExec_Visio*)pDest;

	return TRUE;
}

CBaseObject* CVFlowExec_Visio::Clone()
{
	CVFlowExec_Visio *p = new CVFlowExec_Visio();
	Copy(p);
	return p;
}

CBaseObject* CVFlowExec_Visio::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CVFlowExec_Visio *p = new CVFlowExec_Visio();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CVFlowExec_Visio::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CVFLOWSHAPELINES)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CVFLOWSHAPES)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CVFlowExec_Visio::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCVFlowShapeLinesKey)
	{
		pNew = new CVFlowShapeLines();
	}
	else if (strClassID == pXmlKeys->m_strCVFlowShapesKey)
	{
		pNew = new CVFlowShapes();
	}

	return pNew;
}

CExBaseObject* CVFlowExec_Visio::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CVFLOWSHAPELINES)
	{
		pNew = new CVFlowShapeLines();
	}
	else if (nClassID == MNGRCLASSID_CVFLOWSHAPES)
	{
		pNew = new CVFlowShapes();
	}

	return pNew;
}

BOOL CVFlowExec_Visio::OpenVisioFile(const CString &strVisioFilePath, BOOL bVisible)
{
	return m_oVisioReadWrite.OpenVisioFile(strVisioFilePath, bVisible);
}

BOOL CVFlowExec_Visio::SaveVisioFile()
{
	return m_oVisioReadWrite.SaveVsdFile();
}

void CVFlowExec_Visio::CloseFile()
{
	m_oVisioReadWrite.CloseVisioFile();
}

void CVFlowExec_Visio::QuitApp()
{
	m_oVisioReadWrite.CloseApplication();
}

BOOL CVFlowExec_Visio::InitFlowShapesFromPage(const CString &strPageName)
{
	if (!m_oVisioReadWrite.LoadPage(strPageName))
	{
		return FALSE;
	}

	return CreateAllShapesLines();
}

BOOL CVFlowExec_Visio::InitFlowShapesFromPage(long nPageIndex)
{
	if (!m_oVisioReadWrite.LoadPage(nPageIndex))
	{
		return FALSE;
	}

	return CreateAllShapesLines();
}

BOOL CVFlowExec_Visio::CreateAllShapesLines()
{
	MSVisio15::CVShapes oVisioShapes = m_oVisioReadWrite.GetCurShapes();
	DeleteAllCalcShapes();
	m_oLines.DeleteAll();
	m_oShapes.DeleteAll();

	if (oVisioShapes == NULL)
	{
		return FALSE;
	}

	long nCount = oVisioShapes.get_Count();
	MSVisio15::CVShape oCurVisioShape = NULL;
	VARIANT oVal;
	oVal.vt = VT_I4;
	CString strShapeID;
	CVFlowShapeBase *pShapeData = NULL;

	for (int nIndex = 1;nIndex<=nCount;nIndex++)
	{
		oVal.lVal = nIndex;
		pShapeData = NULL;

		try
		{
			oCurVisioShape = oVisioShapes.get_Item(oVal);
			strShapeID = oCurVisioShape.get_Help();

			if (strShapeID == VFLOW_VISIO_SHAPE_TYPE_DATA)
			{
				pShapeData = new CVFlowShape_Data;
				m_oShapes.AddNewChild(pShapeData);
				
			}
			else if (strShapeID == VFLOW_VISIO_SHAPE_TYPE_LOGIC)
			{
				pShapeData = new CVFlowShape_Logic;
				m_oShapes.AddNewChild(pShapeData);
			}
			else if (strShapeID == VFLOW_VISIO_SHAPE_TYPE_EXPRESION)
			{
				pShapeData = new CVFlowShape_Expression;
				m_oShapes.AddNewChild(pShapeData);
			}
			else if (strShapeID == VFLOW_VISIO_SHAPE_TYPE_FLOW)
			{
				pShapeData = new CVFlowShapeLine;
				m_oLines.AddNewChild(pShapeData);
			}
			else if (strShapeID == VFLOW_VISIO_SHAPE_TYPE_BRANCH)
			{
				pShapeData = new CVFlowShape_Branch;
				m_oShapes.AddNewChild(pShapeData);
			}
			else if (strShapeID == VFLOW_VISIO_SHAPE_TYPE_Threshold)
			{
				pShapeData = new CVFlowShape_Threshold;
				m_oShapes.AddNewChild(pShapeData);
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("未定义的形状ID(%s)."),strShapeID);
				continue;
			}

			pShapeData->m_strHelp = strShapeID;
			pShapeData->m_strData1 = oCurVisioShape.get_Data1();
			pShapeData->m_strData2 = oCurVisioShape.get_Data2();
			pShapeData->m_strData3 = oCurVisioShape.get_Data3();
			pShapeData->m_strName = oCurVisioShape.get_Name();
			pShapeData->m_nVisioID = oCurVisioShape.get_ID();
			pShapeData->m_strID = pShapeData->m_strName;
			pShapeData->m_oShape = oCurVisioShape;
		}
		catch (...)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GetAllShapesLines调用失败(nIndex=%dnCount=%ld;)."),nIndex,nCount);
			return FALSE;
		}
	}

	if (!AttachLinesInOut())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("关联全部线条形状失败."));
		return FALSE;
	}

	if (!CreateAllPropertys())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("创建全部Shapes对应的Propertys失败."));
		return FALSE;
	}

	InitOrigDataShapesPropertys();
	return CreateCalcFlowShapes();
}

// BOOL CVFlowExec_Visio::AttachAllShapeLineInOut()
// {
// 	BOOL bRetShapes,bRetLines;
// 	bRetShapes = AttachShapesInOut();
// 	bRetLines = AttachLinesInOut();
// 	return (bRetShapes&&bRetLines);
// }

// BOOL CVFlowExec_Visio::AttachShapesInOut()
// {
// 	POS pos = m_oShapes.GetHeadPosition();
// 	CVFlowShapeBase *pShapeData = NULL;
// 	VARIANT valID_List;
// 	SAFEARRAY *pSafeArray = NULL;
// 	long nValue = 0,nIndex = 0;
// 
// 	while(pos)
// 	{
// 		pShapeData = (CVFlowShapeBase*)m_oShapes.GetNext(pos);
// 
// 		try
// 		{
// 			ASSERT(pShapeData->m_oShape);
// 			valID_List = pShapeData->m_oShape.GluedShapes(MSVisio15::visGluedShapesAll1D,_T(""));
// 			pSafeArray/*rgsabound[0].cElements*/ = valID_List.parray;
// //			SafeArrayAccessData(pSafeArray, (void   **)&buf);
// 			// 			nIndex = 1;
// 			::SafeArrayGetElement(pSafeArray,&nIndex,&nValue);
// 			// 			nIndex = 2;
// 			// 			::SafeArrayGetElement(pSafeArray,&nIndex,&nValue);
// 			//			nValue = pSafeArray->pvData[0];
// 			//			valID_List = pShapeData->m_oShape.ConnectedShapes(MSVisio15::visConnectedShapesOutgoingNodes,_T(""));
// 		}
// 		catch(...)
// 		{
// 			//			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GetAllShapesLines调用失败(nIndex=%dnCount=%ld;)."),);
// 			return FALSE;
// 		}
// 	}
// }

BOOL CVFlowExec_Visio::AttachLinesInOut()
{
	POS pos = m_oLines.GetHeadPosition();
	CVFlowShapeBase *pShapeData = NULL;
	VARIANT valID_List;
	SAFEARRAY *pSafeArray = NULL;
	long nBeginShapeID = 0,nEndShapeID = 0,nIndex = 0;

	while(pos)
	{
		pShapeData = (CVFlowShapeBase*)m_oLines.GetNext(pos);

		try
		{
			ASSERT(pShapeData->m_oShape);
			valID_List = pShapeData->m_oShape.GluedShapes(MSVisio15::visGluedShapesIncoming2D,_T(""));//获取线条开始端形状ID
			pSafeArray = valID_List.parray;
 			::SafeArrayGetElement(pSafeArray,&nIndex,&nBeginShapeID);

			valID_List = pShapeData->m_oShape.GluedShapes(MSVisio15::visGluedShapesOutgoing2D,_T(""));//获取线条结束端形状ID
			pSafeArray = valID_List.parray;
			::SafeArrayGetElement(pSafeArray,&nIndex,&nEndShapeID);
			AttachLineInOut((CVFlowShapeLine*)pShapeData,nBeginShapeID,nEndShapeID);//关联首端和末端连接线
		}
		catch(...)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前line关联首端、末端Shape失败(Name=%s;VisioID=%ld;)."),pShapeData->m_strName,pShapeData->m_nVisioID);
			return FALSE;
		}
	}

	return TRUE;
}

void CVFlowExec_Visio::AttachLineInOut(CVFlowShapeLine *pShapeLineData,const long &nBeginShapeID,const long &nEndShapeID)
{
	CVFlowShape *pBeginShape = (CVFlowShape*)m_oShapes.FindByVisioID(nBeginShapeID);
	CVFlowShape *pEndShape = (CVFlowShape*)m_oShapes.FindByVisioID(nEndShapeID);

	if (pBeginShape != NULL)
	{
		pShapeLineData->m_pBeginShape = pBeginShape;
		pBeginShape->m_oOutLines.AddTail(pShapeLineData);
	}
	else
	{
		pShapeLineData->m_pBeginShape = NULL;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前线条(%s)连接的首端Shape(ShapeID=%ld)不存在,请确认."),pShapeLineData->m_strName,nBeginShapeID);
	}
	
	if (pEndShape != NULL)
	{
		pShapeLineData->m_pEndShape = pEndShape;
		pEndShape->m_oInLines.AddTail(pShapeLineData);
	}
	else
	{
		pShapeLineData->m_pEndShape = NULL;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前线条(%s)连接的末端Shape(ShapeID=%ld)不存在,请确认."),pShapeLineData->m_strName,nEndShapeID);
	}
}

BOOL CVFlowExec_Visio::CreateAllPropertys()
{
	POS pos = m_oShapes.GetHeadPosition();
	long nRowCount = 0;
	CString strTmp;
	CVFlowShape *pShapeData = NULL;

	while(pos)
	{
		pShapeData = (CVFlowShape*)m_oShapes.GetNext(pos);

		try
		{
			ASSERT(pShapeData->m_oShape);
			pShapeData->DeleteAll();
			nRowCount = pShapeData->m_oShape.get_RowCount(MSVisio15::visSectionProp);

			for (int nIndex = 0;nIndex<nRowCount;nIndex++)
			{
				pShapeData->AddNewProperty(nIndex);
			}
		}
		catch(...)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("CreateAllPropertys调用失败()."));
			return FALSE;
		}

		pShapeData->InitDataTypeUnit();//初始化Shape对象、其基类对象、及输出端line里的数据类型及属性
	}

	return TRUE;
}

BOOL CVFlowExec_Visio::CreateCalcFlowShapes()
{
	m_oShapes.InitShapes();//将所有shape中m_bHasAttachCalc标识置为0
	CVFlowShapes *pResultCalcShapes = new CVFlowShapes;
	m_oShapes.GetAllResultShapes(pResultCalcShapes);

	if (pResultCalcShapes->GetCount() == 0)
	{
		delete pResultCalcShapes;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前Visio形状中缺少结果Shape."));
		return FALSE;
	}

	AddTail(pResultCalcShapes);
	CreateCalcFlowShapes(pResultCalcShapes);
	return TRUE;
}

void CVFlowExec_Visio::CreateCalcFlowShapes(CVFlowShapes *pSrcCalcShapes)
{
	CVFlowShapes oCalcShapes;
	GetAllInShapes(pSrcCalcShapes,&oCalcShapes);

	if (oCalcShapes.GetCount() == 0)
	{
		return;
	}

	CVFlowShapes *pCalcShapes = new CVFlowShapes;
	pCalcShapes->Append(oCalcShapes);
	AddHead(pCalcShapes);//每次创建的都放在链表的首端
	oCalcShapes.RemoveAll();
	CreateCalcFlowShapes(pCalcShapes);
}

void CVFlowExec_Visio::GetAllInShapes(CVFlowShapes *pSrcShapes,CVFlowShapes *pDstShapesRef)
{
	CVFlowShape *pCurShape = NULL;
	CVFlowShape *pBeginShape = NULL;
	CVFlowShapeLine *pCurLine = NULL;
	POS pos = pSrcShapes->GetHeadPosition();

	while(pos)
	{
		pCurShape = (CVFlowShape *)pSrcShapes->GetNext(pos);

		POS pos_line = pCurShape->m_oInLines.GetHeadPosition();

		while(pos_line)
		{
			pCurLine = (CVFlowShapeLine *)pCurShape->m_oInLines.GetNext(pos_line);

			if (pCurLine->m_pBeginShape == NULL)
			{
				continue;
			}

			pBeginShape = (CVFlowShape *)pCurLine->m_pBeginShape;

			if (!pBeginShape->m_bHasAttachCalc)
			{
				pDstShapesRef->AddTail(pCurLine->m_pBeginShape);
				pBeginShape->m_bHasAttachCalc = TRUE;
			}
		}
	}
}

void CVFlowExec_Visio::ActivePage(const CString &strPage)
{
	m_oVisioReadWrite.ActivePage(strPage);
}

BOOL CVFlowExec_Visio::UpdataValue_AllOrigDatas()
{
	POS pos = m_oOrigDataDataset.GetHeadPosition();
	CDvmData *pCurData = NULL;
	CExBaseObject *pCurObj = NULL;
	CVFlowShapeProperty *pProperty = NULL;
	CVFlowShapeBase *pShape = NULL;

	while(pos)
		{
		pCurData = (CDvmData*)m_oOrigDataDataset.GetNext(pos);

			if (pCurData->m_nIndex == 0)
			{
				continue;
			}

			if (pCurData->m_dwItemData == 0)//该值不应该为0
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前原始数据(ID=%s;Ref=%s;)关联的DvmData对象中的指针为空."),pCurData->m_strID,pCurData->m_strName);
				continue;
			}

			pCurObj = (CExBaseObject *)pCurData->m_dwItemData;

			if (pCurObj->GetClassID() == MNGRCLASSID_CVFLOWSHAPEPROPERTY)//要么是属性要么是ShapeBase
			{
				pProperty = (CVFlowShapeProperty*)pCurObj;
				pProperty->SetValue_UI(pCurData->m_strValue);
				pCurData->m_nIndex = 0;
			} 
			else
			{
				pShape = (CVFlowShapeBase*)pCurObj;
				pShape->m_strData3 = pCurData->m_strValue;
				pShape->SetData3_UI(pCurData->m_strValue);
				pCurData->m_nIndex = 0;
			}
		}

	return TRUE;
}

BOOL CVFlowExec_Visio::UpdataDataTypeUnit_AllOrigDatas()
{
	POS pos = m_oOrigDataDataset.GetHeadPosition();
	CDvmData *pCurData = NULL;
	CExBaseObject *pCurObj = NULL;
	CVFlowShapeProperty *pProperty = NULL;
	CVFlowShapeBase *pShape = NULL;

	while(pos)
	{
		pCurData = (CDvmData*)m_oOrigDataDataset.GetNext(pos);

			if (pCurData->m_dwItemData == 0)//该值不应该为0
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前原始数据(ID=%s;Ref=%s;)关联的DvmData对象中的指针为空."),pCurData->m_strID,pCurData->m_strName);
				continue;
			}

			pCurObj = (CExBaseObject *)pCurData->m_dwItemData;

			if (pCurObj->GetClassID() == MNGRCLASSID_CVFLOWSHAPEPROPERTY)//要么是属性要么是ShapeBase
			{
				pProperty = (CVFlowShapeProperty*)pCurObj;
				pProperty->m_strDataType = pCurData->m_strDataType;
				pProperty->m_strUnit = pCurData->m_strUnit;
			} 
// 		else
// 		{
// 			pShape = (CVFlowShapeBase*)pCurObj;
// 			pShape->m_strData3 = pCurData->m_strValue;
// 			pCurData->m_nIndex = 0;
// 		}
	}

	return TRUE;
}

BOOL CVFlowExec_Visio::UpdateAllShapes()
{
	CVFlowShapes *pCurCalcShapes = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurCalcShapes = (CVFlowShapes*)GetNext(pos);
		pCurCalcShapes->UpdateAllShapes();
	}

	return TRUE;
}

void CVFlowExec_Visio::InitOrigDataShapesPropertys()
{
	m_oOrigDataDataset.DeleteAll();
	m_oOrigDataPropertysRef.RemoveAll();
	m_oOrigDataShapesRef.RemoveAll();
	POS pos_shape = m_oShapes.GetHeadPosition();
	POS pos_property = NULL;
	CVFlowShape *pShapeData = NULL;
	CVFlowShapeProperty *pProperty = NULL;
	CDvmData *pCurDvmData = NULL;

	while(pos_shape)
	{
		pShapeData = (CVFlowShape*)m_oShapes.GetNext(pos_shape);

		if (pShapeData->GetClassID() == MNGRCLASSID_CVFLOWSHAPE_DATA)
		{
			pCurDvmData = new CDvmData;
			pCurDvmData->m_strID = pShapeData->m_strID;
			pCurDvmData->m_strName = pShapeData->m_strData1;
			pCurDvmData->m_dwItemData = (DWORD)pShapeData;
			m_oOrigDataDataset.AddNewChild(pCurDvmData);
			m_oOrigDataShapesRef.AddTail(pShapeData);
		}

		pos_property = pShapeData->GetHeadPosition();

		while(pos_property)
		{
			pProperty = (CVFlowShapeProperty *)pShapeData->GetNext(pos_property);

			if (!pProperty->m_strPath.IsEmpty())
			{
				pCurDvmData = new CDvmData;
				pCurDvmData->m_strID = pProperty->m_strID;
				pCurDvmData->m_strName = pProperty->m_strPath;
				pCurDvmData->m_dwItemData = (DWORD)pProperty;
				m_oOrigDataDataset.AddNewChild(pCurDvmData);
				m_oOrigDataPropertysRef.AddTail(pProperty);
			}
		}
	}
}

BOOL CVFlowExec_Visio::SetOrigDataValue(const CString &strOrigDataRef,const CString &strValue)
{
	if (m_oOrigDataShapesRef.SetValueByData1(strOrigDataRef,strValue))
	{
		return TRUE;
	}

	return m_oOrigDataPropertysRef.SetPropertyValueByPath_UI(strOrigDataRef,strValue);
}

BOOL CVFlowExec_Visio::GetOrigDataValue(const CString &strOrigDataRef,CString &strValue)
{
	CVFlowShapeBase *pShapeBase = m_oOrigDataShapesRef.FindByData1(strOrigDataRef);

	if (pShapeBase != NULL)
	{
		strValue = pShapeBase->m_strData3;
		return TRUE;
	}

	return m_oOrigDataPropertysRef.GetPropertyValueByPath(strOrigDataRef,strValue);
}

BOOL CVFlowExec_Visio::SetOrigDataValue_UI(const CString &strOrigDataRef,const CString &strValue)
{
	if (m_oOrigDataShapesRef.SetValueByData1_UI(strOrigDataRef,strValue))
	{
		return TRUE;
	}

	return m_oOrigDataPropertysRef.SetPropertyValueByPath_UI(strOrigDataRef,strValue);
}

BOOL CVFlowExec_Visio::GetOrigDataValue_UI(const CString &strOrigDataRef,CString &strValue)
{
	if (m_oOrigDataShapesRef.GetValueByData1_UI(strOrigDataRef,strValue))
	{
		return TRUE;
	}

	return m_oOrigDataPropertysRef.GetPropertyValueByPath_UI(strOrigDataRef,strValue);
}

BOOL CVFlowExec_Visio::SetShapeValueByID(const CString &strShapeID,const CString &strValue)
{
	return m_oShapes.SetValueByID(strShapeID,strValue);
}

BOOL CVFlowExec_Visio::GetShapeValueByID(const CString &strShapeID,CString &strValue)
{
	return m_oShapes.GetValueByID(strShapeID,strValue);
}

CVFlowShape* CVFlowExec_Visio::FindShapeByID(const CString &strShapeID)
{
	CVFlowShape *pShape = (CVFlowShape*)m_oShapes.FindByID(strShapeID);
	return pShape;
}

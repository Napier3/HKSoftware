// WordBaseClass.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VisioBaseClass.h"
#include "..\..\Module\API\FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CVisioDocBase::CVisioDocBase(MSVisio15::CVApplication &oWordApp)
{
	m_oVisioApp = oWordApp;
//	m_oActiveWindow = NULL;
	m_oDoc = NULL;
	m_oCurPages = NULL;
	m_oCurPage = NULL;
	m_oCurShapes = NULL;
}

CVisioDocBase::CVisioDocBase()
{
	m_oVisioApp = NULL;
//	m_oActiveWindow = NULL;
	m_oDoc = NULL;
	m_oCurPages = NULL;
	m_oCurPage = NULL;
	m_oCurShapes = NULL;
}

CVisioDocBase::~CVisioDocBase()
{
	m_oVisioApp = NULL;
	m_oCurPages = NULL;
	m_oCurPage = NULL;
	m_oCurShapes = NULL;
///	m_oActiveWindow = NULL;
}

long CVisioDocBase::New(const CString &strTemplateFile, const CString &strWordFile, BOOL bAdjust)
{
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vTemplate(strTemplateFile);			
	COleVariant vRptFile(strWordFile);			
	BOOL bWordCreate = TRUE;

	ASSERT (m_oVisioApp != NULL);

	if (  m_oVisioApp == NULL)
	{
		return 0;
	}

	MSVisio15::CVDocuments docs;

	try
	{
		//如果打开了报告文档，则保存并关闭文档
		docs =   m_oVisioApp.get_Documents();

		//打开报告文档
		if (!Open(strWordFile, bAdjust))
		{
			try
			{
				//如果打开失败，则打开测试模板，并且填写试验报告
				AddNewReport(strTemplateFile);
				SaveAs(strWordFile);
			}
			catch (...)
			{
			}
		}

		if (bAdjust)
		{
			AdjustVisioWindow();
		}
	}
	catch(...)
	{
	}

	return TRUE;
}

long CVisioDocBase::New(const CString &strWordFile, BOOL bAdjust)
{
	return New(_T(""), strWordFile, bAdjust);
}

BOOL CVisioDocBase::Open(const CString  &strWordFile, BOOL bAdjust)
{
	//CFileFind find;

	//if (!find.FindFile(strWordFile))
	if (!IsFileExist(strWordFile))
	{
		return FALSE;
	}

	if ( m_oVisioApp == NULL)
	{
		return FALSE;
	}

	MSVisio15::CVDocuments docs = NULL;
	docs =  m_oVisioApp.get_Documents();

	if (docs == NULL)
	{
		return FALSE;
	}

//	COleVariant vRptFile(strWordFile);			
//	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	BOOL bTrue = TRUE;
	try
	{
		//打开试验报告文件
		m_oDoc = docs.Open(strWordFile);
	}
	catch (...)
	{
		bTrue = FALSE;
	}

	if (bAdjust)
	{
		AdjustVisioWindow();
	}

	return bTrue;
}

long CVisioDocBase::Save()
{
	if( m_oVisioApp == NULL)
		return FALSE;

	if(m_oDoc == NULL)
		return FALSE;

	m_oDoc.Save();

	return TRUE;
}

long CVisioDocBase::SaveAs(const CString  &strWordFile)
{
	if( m_oVisioApp == NULL || m_oDoc == NULL)
		return FALSE;

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
//	COleVariant vRptFile(strWordFile);
	m_oDoc.SaveAs(strWordFile);

	return TRUE;
}

long CVisioDocBase::Close(long nSave)
{
	if( m_oVisioApp == NULL || m_oDoc == NULL)
	{
		return TRUE;
	}

	if (nSave)
	{
		Save();
	}

	CloseVisioDocWindow();

	return TRUE;
}

BOOL CVisioDocBase::AddNewReport(const CString &strTemplateFile)
{
//	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
//	COleVariant FileFormat((long)0);
	COleVariant Password(_T(""));
	COleVariant WritePassword(_T(""));

	CString strWordRptFile;
//	CString strTmplFile(_T("BASIC_M.vssx")/*strTemplateFile*/);

	//CFileFind find;
	//if (!find.FindFile(strTemplateFile))
	//{
	//	//return FALSE;
	//}

	BOOL bTrue = TRUE;
	MSVisio15::CVDocuments docs =  m_oVisioApp.get_Documents();

// 	try
// 	{
// 		m_oDoc = docs.AddItem(&TmplFile/*,MSVisio::visMSDefault,0,1*/);
// 	}
// 	catch (...)
// 	{
// 		bTrue = FALSE;
// 	}

	try
	{
		m_oDoc = docs.Add(strTemplateFile/*,MSVisio::visMSDefault,0,1*/);
	}
	catch (...)
	{
		bTrue = FALSE;
	}

	return bTrue;
}


BOOL CVisioDocBase::CloseVisioDocWindow()
{
	try
	{
		if (m_oDoc != NULL)
		{
			m_oDoc.Close();
			m_oDoc = NULL;
			m_oCurPages = NULL;
			m_oCurPage = NULL;
			m_oCurShapes = NULL;
		}
	}
	catch (...) 
	{
		TRACE("CloseVisioDocWindow:Error");
	}

	return TRUE;
}

void CVisioDocBase::AdjustVisioWindow()
{
}

BOOL CVisioDocBase::SetColorByShapeID(unsigned long uLineID,const CString &strLineColor)
{
	return SetTypeColorByShapeID(uLineID,_T(""),strLineColor);
}

BOOL CVisioDocBase::SetTypeByShapeID(unsigned long uLineID,const CString &strLineType)
{
	return SetTypeColorByShapeID(uLineID,strLineType,_T(""));
}

BOOL CVisioDocBase::SetTypeColorByShapeID(unsigned long uLineID,const CString &strLineType,const CString &strLineColor)
{
	MSVisio15::CVShapes oCurShapes = GetCurShapes();

	if (oCurShapes != NULL)
	{
		MSVisio15::CVShape oCurShape = NULL;
		BOOL bSuccess = FALSE;
		try
		{
			oCurShape = oCurShapes.get_ItemFromID(uLineID);
			SetShapeType(oCurShape,strLineType);
			SetShapeColor(oCurShape,strLineColor);
			bSuccess = TRUE;
		}
		catch (...)
		{
		}

		return bSuccess;
	}

	return FALSE;
}

BOOL CVisioDocBase::SetTypeColorByShapeText(const CString &strLineText,const CString &strLineType,const CString &strLineColor)
{
	MSVisio15::CVShapes oCurShapes = GetCurShapes();

	if (oCurShapes != NULL)
	{
		long nLineCount = oCurShapes.get_Count();
		MSVisio15::CVShape oCurShape = NULL;
		CString strCurText;
		BOOL bFind = FALSE;
		VARIANT oVal;
		oVal.vt = VT_I4;

		for (int nLineID = 1;nLineID<= nLineCount;nLineID++)
		{
			oVal.lVal = nLineID;
			try
			{
				oCurShape = oCurShapes.get_Item(oVal);
			}
			catch (...)
			{
				continue;
			}

			if (oCurShape != NULL)
			{
				strCurText = oCurShape.get_Text();

				if (strCurText == strLineText)
				{
					bFind = TRUE;
					break;
				}
			}
		}

		if (!bFind)
		{
			return FALSE;
		}

		SetShapeType(oCurShape,strLineType);
		SetShapeColor(oCurShape,strLineColor);
		return TRUE;
	}

	return FALSE;
}

BOOL CVisioDocBase::AddShape(const CString &strTemplate,const CString &strShapeNameU,double dLength,double dWidth)
{
	if (m_oVisioApp != NULL)
	{
		MSVisio15::CVWindow oActiveWindow = m_oVisioApp.get_ActiveWindow();
 
 		if (oActiveWindow != NULL)
 		{
 			MSVisio15::CVPage oCurPage = oActiveWindow.get_Page().pdispVal;
 
 			if (oCurPage != NULL)
 			{

				MSVisio15::CVDocuments docs =  m_oVisioApp.get_Documents();
				COleVariant vTemplate(strTemplate);		
				MSVisio15::CVDocument oCurDoc = docs.Add(strTemplate);

				if (oCurDoc != NULL)
				{
					MSVisio15::CVMasters oMasters = oCurDoc.get_Masters();

					if (oMasters != NULL)
					{
						COleVariant vShapeName(strShapeNameU);	
						MSVisio15::CVShape oShape = oMasters.get_ItemU(vShapeName);

						if (oShape != NULL)
						{
							oCurPage.Drop(oShape,dLength,dWidth);
						}
					}
				}
 			}
 		}
	}

	return FALSE;
}

// int nType = 0, nObjType = 0,nStat = 0,nOneD = 0 ,nGeometryCount = 0 ,nIndex16 = 0 ,nForeignType = 0;
// CString strName,strNameID,strHelp,strNameU,strStyle,strLineStyle,strFillStyle;

// nStat = oCurShape.get_Stat();
// nType = oCurShape.get_Type();
// nObjType = oCurShape.get_ObjectType();
// strHelp = oCurShape.get_Help();
// strName = oCurShape.get_Name();
// strNameID = oCurShape.get_NameID();
// strNameU = oCurShape.get_NameU();
// nOneD = oCurShape.get_OneD();
// nGeometryCount = oCurShape.get_GeometryCount();
// nIndex16 = oCurShape.get_Index16();
// strStyle = oCurShape.get_Style();
// strLineStyle = oCurShape.get_LineStyle();
// strFillStyle = oCurShape.get_FillStyle();
// nForeignType = oCurShape.get_ForeignType();

BOOL CVisioDocBase::SetTypeColorByShapeType(const CString &strShapeType,long nLineType,const CString &strLineColor)
{
	MSVisio15::CVShapes oCurShapes = GetCurShapes();

	if (oCurShapes != NULL)
	{
		long nLineCount = oCurShapes.get_Count();
		MSVisio15::CVShape oCurShape = NULL;
		CString strNameU ,strTmp;
		VARIANT oVal;
		oVal.vt = VT_I4;

		for (int nLineID = 1;nLineID<= nLineCount;nLineID++)
		{
			try
			{
				oCurShape = oCurShapes.get_Item(oVal);
			}
			catch (...)
			{
				continue;
			}

			if (oCurShape != NULL)
			{
				strNameU = oCurShape.get_NameU();

				if (IsEqualShape(strShapeType ,strNameU))
				{
					strTmp.Format(_T("%ld"),nLineType);
					SetShapeType(oCurShape,strTmp);
					SetShapeColor(oCurShape,strLineColor);
				}
			}
		}

		return TRUE;
	}

	return FALSE;
}

BOOL CVisioDocBase::SetShapeColor(MSVisio15::CVShape &oCurShape,const CString &strLineColor)
{
	if ((oCurShape == NULL)||(strLineColor.IsEmpty()))
	{
		return FALSE;
	}

	MSVisio15::CVCell oCurCell = oCurShape.get_CellsSRC(MSVisio15::visSectionObject, MSVisio15::visRowLine, MSVisio15::visLineColor);

	if (oCurCell != NULL)
	{
		oCurCell.put_FormulaU(strLineColor);//THEMEGUARD(RGB(0,0,0))
	}

	return TRUE;
}

BOOL CVisioDocBase::SetShapeType(MSVisio15::CVShape &oCurShape,const CString &strLineType)
{
	if ((oCurShape == NULL)||(strLineType.IsEmpty()))
	{
		return FALSE;
	}

	MSVisio15::CVCell oCurCell = oCurShape.get_CellsSRC(MSVisio15::visSectionObject, MSVisio15::visRowLine, MSVisio15::visLinePattern);

	if (oCurCell != NULL)
	{
		oCurCell.put_FormulaU(strLineType);//THEMEGUARD(RGB(0,0,0))
	}

	return TRUE;
}

BOOL CVisioDocBase::IsEqualShape(const CString &strShapeType ,const CString &strNameU)
{
	long nIndex = strNameU.Find('.');
	CString strCurShapeType;

	if (nIndex != -1)
	{
		strCurShapeType = strNameU.Left(nIndex);
	}
	else
		strCurShapeType = strNameU;

	return(strCurShapeType == strShapeType);
}

MSVisio15::CVShape CVisioDocBase::GetShapeFromID(long nShapeID)
{
	MSVisio15::CVShapes oCurShapes = GetCurShapes();

	if (oCurShapes == NULL)
	{
		return NULL;
	}	
	
	MSVisio15::CVShape oCurShape = NULL;

	try
	{
		oCurShape = oCurShapes.get_ItemFromID(nShapeID);
	}
	catch (...)
	{
		
	}



// 	if (m_oVisioApp != NULL)
// 	{
// 		MSVisio15::CVWindow oActiveWindow = m_oVisioApp.get_ActiveWindow();
// 
// 		if (oActiveWindow != NULL)
// 		{
// 			MSVisio15::CVPage oCurPage = oActiveWindow.get_Page().pdispVal;
// 
// 			if (oCurPage != NULL)
// 			{
// 				MSVisio15::CVShapes oCurShapes = oCurPage.get_Shapes();
// 
// 				if (oCurShapes != NULL)
// 				{
// 					try
// 					{
// 						oCurShape = oCurShapes.get_ItemFromID(nShapeID);
// 					}
// 					catch (...)
// 					{
// 					}
// 				}
// 			}
// 		}
// 	}

	return oCurShape;
}

MSVisio15::CVShape CVisioDocBase::GetShapeFromName(const CString &strShapeName)
{
	MSVisio15::CVShape oCurShape = NULL;
	MSVisio15::CVShapes oCurShapes = GetCurShapes();

	if (oCurShapes != NULL)
	{
		long nCount = oCurShapes.get_Count();
		CString strCurShapeName;
		VARIANT oVal;
		oVal.vt = VT_I4;

		for (int nIndex = 1;nIndex<= nCount;nIndex++)
		{
			try
			{
				oVal.lVal = nIndex;
				oCurShape = oCurShapes.get_Item(oVal);

				if (oCurShape != NULL)
				{
					strCurShapeName = oCurShape.get_Name();
				}
			}
			catch (...)
			{
				strCurShapeName = _T("");
			}
		}
	}

	return oCurShape;
}

MSVisio15::CVShapes CVisioDocBase::GetCurShapes()
{
	if (m_oCurShapes == NULL)
	{
		if (m_oCurPage != NULL)
		{
			m_oCurShapes = m_oCurPage.get_Shapes();
		}
	}

	return m_oCurShapes;
}

BOOL CVisioDocBase::SelectCurPage(const CString &strPageName)
{
	if (m_oDoc == NULL)
	{
		return FALSE;
	}

	if (m_oCurPages == NULL)
	{
		m_oCurPages = m_oDoc.get_Pages();

		if (m_oCurPages == NULL)
		{
			return FALSE;
		}
	}

	long nPageCount = m_oCurPages.get_Count();
	CString strCurPageName;
	MSVisio15::CVPage oCurPage = NULL;
	VARIANT oVal;
	oVal.vt = VT_I4;

	for (int nIndex = 1;nIndex<=nPageCount;nIndex++)
	{
		oVal.lVal = nIndex;
		oCurPage = m_oCurPages.get_Item(oVal);

		if (oCurPage != NULL)
		{
			strCurPageName = oCurPage.get_Name();

			if (strCurPageName == strPageName)
			{
				m_oCurPage = oCurPage;
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CVisioDocBase::GetAssociateShapes(long nShapeID)
{
	BOOL bFind = FALSE;
	MSVisio15::CVShape oCurShape = GetShapeFromID(nShapeID);
	long nTmp = 0;
	CString strTmp;
	VARIANT oVal;
	SAFEARRAY *pSafeArray = NULL;

	if (oCurShape != NULL)
	{
		oVal = oCurShape.GluedShapes(MSVisio15::visGluedShapesOutgoing1D,_T(""));
//		nTmp = oCurShape.get_Index();
		
//		oVal = oCurShape.ConnectedShapes(MSVisio15::visConnectedShapesAllNodes,_T(""));

// 		MSVisio15::CVShape oContainShape  = oCurShape.get_ContainingShape();
// 		
// 		if (oContainShape != NULL)
// 		{
// 			strTmp = oContainShape.get_Text();
// 		}

// 		MSVisio15::CVConnects oConnects = oCurShape.get_Connects();
// 		MSVisio15::CVConnect oConnect = NULL;
// 		MSVisio15::CVCell oCurCell;
// 
// 		if (oConnects != NULL)
// 		{
// 			nTmp = oConnects.get_Count();
// 
// 			for (int nIndex = 1;nIndex<=nTmp;nIndex++)
// 			{
// 				oConnect = oConnects.get_Item(nIndex);
// 
// 				if (oConnect != NULL)
// 				{
// 					nTmp1 = oConnect.get_ContainingMasterID();
// 					nTmp1 = oConnect.get_ContainingPageID();
// 					nTmp1 = oConnect.get_Index();
// 					nTmp1 = oConnect.get_FromPart();
// 					nTmp1 = oConnect.get_ToPart();
// 					nTmp1 = oConnect.get_ObjectType();
// 					oCurCell = oConnect.get_FromCell();
// 
// 					if (oCurCell != NULL)
// 					{
// 						oCurCell.put_FormulaU(_T("THEMEGUARD(RGB(0,255,0))"));//THEMEGUARD(RGB(0,0,0))
// 					}
// 				}
// 			}
// 		}

// 		MSVisio15::CVShapes oCurShapes = oCurShape.get_Shapes();
// 		long nShapeCounts = oCurShapes.get_Count();
// 		MSVisio15::CVCharacters oCharacters = oCurShape.get_Characters();
// 
// 		if (oCharacters != NULL)
// 		{
// 			strTmp = oCharacters.get_TextAsString();
// 		}
	}

	return bFind;
}

BOOL CVisioDocBase::SetShapeRowValue(long nShapeID,const CString &strRowValue)
{
	MSVisio15::CVShape oCurShape = GetShapeFromID(nShapeID);
	MSVisio15::CVCell oCurCell = NULL;
	long nTmp = 0 ,nRowCount = 0;
	CString strTmp;
	SAFEARRAY *pSafeArray = NULL;

	if (oCurShape != NULL)
	{
		nRowCount = oCurShape.get_RowCount(MSVisio15::visSectionProp);

		for (int nIndex = 0;nIndex<nRowCount;nIndex++)
		{
			oCurCell = oCurShape.get_CellsSRC(MSVisio15::visSectionProp,nIndex,MSVisio15::visCustPropsValue);

			if (oCurCell != NULL)
			{
				strTmp = oCurCell.get_RowNameU();
				strTmp = oCurCell.get_RowName();
				strTmp = oCurCell.get_FormulaU();
				strTmp = oCurCell.get_Formula();
				strTmp = oCurCell.get_Name();
				strTmp = oCurCell.get_LocalName();
			}

			oCurCell = oCurShape.get_CellsSRC(MSVisio15::visSectionProp,nIndex,MSVisio15::visCustPropsLabel);

			if (oCurCell != NULL)
			{
				strTmp = oCurCell.get_RowNameU();
				strTmp = oCurCell.get_RowName();
				strTmp = oCurCell.get_FormulaU();
				strTmp = oCurCell.get_Formula();
				strTmp = oCurCell.get_Name();
				strTmp = oCurCell.get_LocalName();
			}

			oCurCell = oCurShape.get_CellsSRC(MSVisio15::visSectionProp,nIndex,MSVisio15::visCustPropsPrompt);

			if (oCurCell != NULL)
			{
				strTmp = oCurCell.get_RowNameU();
				strTmp = oCurCell.get_RowName();
				strTmp = oCurCell.get_FormulaU();
				strTmp = oCurCell.get_Formula();
				strTmp = oCurCell.get_Name();
				strTmp = oCurCell.get_LocalName();
			}
		}
	}

	return FALSE;
}


//////////////////////////////////////////////////////////////////////////
//CWordAppBase

CVisioAppBase::CVisioAppBase(MSVisio15::CVApplication &oWordApp)
{
	m_oVisioApp = oWordApp;
	m_bIsAppRef = TRUE;
}

CVisioAppBase::CVisioAppBase()
{
	m_oVisioApp = NULL;
	m_bIsAppRef = FALSE;
}

CVisioAppBase::~CVisioAppBase()
{
	
}
	
MSVisio15::CVApplication CVisioAppBase::GetVisioApp(BOOL bVisible)
{
	if (m_oVisioApp != NULL)
	{
		return m_oVisioApp;
	}

	m_bIsAppRef = FALSE;
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		if (!m_oVisioApp.CreateDispatch(_T("Visio.Application")))
		{
			return  NULL;
		}

		m_oVisioApp.put_Visible(bVisible);
	}
	catch (...)
	{
	}

	return m_oVisioApp;
}

BOOL CVisioAppBase::CloseVisioApplication()
{
	if (m_bIsAppRef)
	{
		m_oVisioApp = NULL;
		return TRUE;
	}

	if (m_oVisioApp == NULL)
	{
		return TRUE;
	}

	try
	{
		if(m_oVisioApp)
		{
			m_oVisioApp.Quit();
			m_oVisioApp = NULL;
		}
	}
	catch (...) 
	{
	}

	m_oVisioApp = NULL;

	return TRUE;
}

CVisioDocBase* CVisioAppBase::CreateVisioDocBase()
{
	CVisioDocBase *pNew = new CVisioDocBase(m_oVisioApp);
	return pNew;
}


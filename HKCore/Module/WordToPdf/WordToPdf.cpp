#include "StdAfx.h"
#include "WordToPdf.h"
#include "..\API\FileApi.h"

CWordToPdf::CWordToPdf()
{
	m_WordApp = NULL;
	m_Doc = NULL;
	m_Docs = NULL;
	m_strPdfOutputPath = _T("");
	m_pWnd = NULL;
}

CWordToPdf::~CWordToPdf()
{

}

void CWordToPdf::OpenWordFile(const CString& strWordFileName)
{
	COleVariant	FileName(strWordFileName);
	COleVariant	vTrue((short)TRUE);
	COleVariant	vFalse((short)FALSE);
	COleVariant	vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	m_Docs = (m_WordApp.GetDocuments());

	m_Doc = m_Docs.Open(FileName, 
		vTrue,				// Confirm Conversion.
		vFalse,				// ReadOnly.
		vFalse,				// AddToRecentFiles.
		vOptional,			// PasswordDocument.
		vOptional,			// PasswordTemplate.
		vOptional,			// Revert.
		vOptional,			// WritePasswordDocument.
		vOptional,			// WritePasswordTemplate.
		vOptional,			// Format.
		vOptional,			// Encoding.
		vTrue	);			// visible.
}

void CWordToPdf::InsertEcptStamp(const CString& strEcptStampFile, CStampPos& stampPos)
{
	if(m_WordApp == NULL||m_Doc == NULL)
	{
		return;
	}
	try
	{
		MSWord::Selection	 oWordSel;
		MSWord::InlineShapes oWordShapes;
		MSWord::InlineShape	 oWordShape;
		MSWord::Shapes		 oShapes;
		MSWord::Shape		 oShape;
		MSWord::WrapFormat	 oWordWrpFormat;
		MSWord::PictureFormat oPictureFormat;

		COleVariant vTrue((short)TRUE),vFalse((short)FALSE),vOpt((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
		long lTransTrue(TRUE),lTransFalse(FALSE);
		bool bUse = stampPos.m_bUse;
		if (!bUse)
		{
			return;
		}

		int nStampNo = stampPos.m_nStampNo;
		int nPageNo = stampPos.m_nPageNo;
		int nLeftMargin = stampPos.m_nLeftMargin;
		int nTopMargin = stampPos.m_nTopMargin;
		int nOffsetW = stampPos.m_nOffsetW;
		int nOffsetH = stampPos.m_nOffsetH;
		bool bRotate = stampPos.m_bRotate;
		if(nStampNo >0 && nPageNo > 0 && nLeftMargin >=0 && nTopMargin >= 0)
		{
			oWordSel.GoTo(COleVariant((short)MSWord::wdGoToPage),COleVariant((short)MSWord::wdGoToAbsolute),COleVariant((short)nPageNo),vOpt);
			oWordSel = m_WordApp.GetSelection();
			oWordShapes = oWordSel.GetInlineShapes();
			oWordShape = oWordShapes.AddPicture(strEcptStampFile,vFalse,vTrue,vOpt);
			oShape = oWordShape.ConvertToShape();
			oWordWrpFormat = oShape.GetWrapFormat();
			oWordWrpFormat.SetType((long)6);

			oPictureFormat = oShape.GetPictureFormat();
			oPictureFormat.SetTransparentBackground(lTransTrue);
			oPictureFormat.SetTransparencyColor(RGB(255,255,255));
			oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
			oShape.SetLeft(nLeftMargin);
			oShape.SetRelativeVerticalPosition(MSWord::wdRelativeVerticalPositionPage);
			oShape.SetTop(nTopMargin);
			Sleep(500);
			if (bRotate)
			{
				float fRotation = rand()%90 - 45;//-45~45之间
				oShape.SetRotation(fRotation);
			}
			float fWidth = oShape.GetWidth();
			oShape.SetWidth(fWidth + nOffsetW);
			float fHeight = oShape.GetHeight();
			oShape.SetHeight(fHeight + nOffsetH);
			MSWord::Tables oTables = oWordSel.GetTables();
			if (oTables.GetCount()>0)
			{
				MSWord::Table oTable = oTables.Item(1);
				oTable.Select();
				oWordSel = m_WordApp.GetSelection();
				MSWord::Cells oCells = oWordSel.GetCells();
				long lVertAlignment = oCells.GetVerticalAlignment();
				if (lVertAlignment != MSWord::wdCellAlignVerticalTop)
				{
					oCells.SetVerticalAlignment(MSWord::wdCellAlignVerticalTop);
					lVertAlignment = oCells.GetVerticalAlignment();
				}
			}

			oWordWrpFormat.ReleaseDispatch();
			oPictureFormat.ReleaseDispatch();
			oShape.ReleaseDispatch();
			oWordShape.ReleaseDispatch();
			oWordShapes.ReleaseDispatch();	
			oWordSel.ReleaseDispatch();
		}
		m_Doc.Save();
	}
	catch(...)
	{
	}
}

void CWordToPdf::InsertEcptTesterSign(const CString& strMainTesterSignFile,const CString& strSubTesterSignFile,CTesterSignPos& testerSignPos)
{
	if(m_WordApp == NULL||m_Doc == NULL)
	{
		return;
	}
	try
	{
		MSWord::Selection	 oWordSel;
		MSWord::InlineShapes oWordShapes;
		MSWord::InlineShape	 oWordShape;
		MSWord::Shapes		 oShapes;
		MSWord::Shape		 oShape;
		MSWord::WrapFormat	 oWordWrpFormat;
		MSWord::PictureFormat oPictureFormat;
		MSWord::Find		 oWordFind;

		COleVariant vTrue((short)TRUE),vFalse((short)FALSE),vOpt((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
		COleVariant vtWindWrap((short)MSWord::wdFindStop);
		long lTransTrue(TRUE),lTransFalse(FALSE);
		CString strMainTester = testerSignPos.m_strMainTester;
		strMainTester.Trim();
		CString strSubTester = testerSignPos.m_strSubTester;
		strSubTester.Trim();
		int nMainPosX1 = testerSignPos.m_nMainPosX1;
		int nMainPosY1 = testerSignPos.m_nMainPosY1;
		int nMainPosX2 = testerSignPos.m_nMainPosX2;
		int nMainPosY2 = testerSignPos.m_nMainPosY2;
		int nSubPosX = testerSignPos.m_nSubPosX;
		int nSubPosY = testerSignPos.m_nSubPosY;
		bool bReplace = testerSignPos.m_bReplace;

		CString strFind;
		CString strWildcards;
		int nCount = 0;
		bool bFind = true;
		oWordSel.GoTo(COleVariant((short)MSWord::wdGoToPage),COleVariant((short)MSWord::wdGoToAbsolute),COleVariant((short)2),vOpt);
		if(!strMainTester.IsEmpty()|| (!bReplace && nMainPosX1>0 && nMainPosY1>0))
		{
			//定位主测
			strWildcards = GetWildcards(strMainTester);
			while(bFind)
			{
				oWordSel = m_WordApp.GetSelection();
				oWordFind = oWordSel.GetFind();
				if (bReplace)
				{
					COleVariant varString(_T(""));
					bFind = oWordFind.Execute(COleVariant(strWildcards),vFalse,vFalse,vTrue,vFalse,
						vFalse,vTrue,&vtWindWrap,vFalse,varString,vOpt,vOpt,vOpt,vOpt,vOpt);
				}
				else
				{
					bFind = oWordFind.Execute(COleVariant(strWildcards),vFalse,vFalse,vTrue,vFalse,
						vFalse,vTrue,&vtWindWrap,vFalse,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
				}
				if (!bFind || nCount>=2)
				{
					break;
				}
				nCount++;
				
				oWordSel.GoTo(COleVariant((short)MSWord::wdGoToPage),COleVariant((short)MSWord::wdGoToAbsolute),COleVariant((short)2),vOpt);
				oWordShapes = oWordSel.GetInlineShapes();
				if (nCount==1 && nMainPosX1>0 && nMainPosY1>0 || nCount==2 && nMainPosX2>0 && nMainPosY2>0)
				{
					oWordShape = oWordShapes.AddPicture(strMainTesterSignFile,vFalse,vTrue,vOpt);
					oShape = oWordShape.ConvertToShape();
					oWordWrpFormat = oShape.GetWrapFormat();
					oWordWrpFormat.SetType((long)6);
					oPictureFormat = oShape.GetPictureFormat();
					oPictureFormat.SetTransparentBackground(lTransTrue);
					oPictureFormat.SetTransparencyColor(RGB(255,255,255));		
				
					if (nCount==1 && nMainPosX1>0 && nMainPosY1>0)
					{
						if (bReplace)
						{
							oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
							oShape.SetLeft(nMainPosX1-50);//左移50个像素，可调
						}
						else
						{
							oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
							oShape.SetLeft(nMainPosX1);
						}
						oShape.SetRelativeVerticalPosition(MSWord::wdRelativeVerticalPositionPage);
						oShape.SetTop(nMainPosY1);
					}
					else if (nMainPosX2>0 && nMainPosY2>0)
					{
						if (bReplace)
						{
							oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
							oShape.SetLeft(nMainPosX2-50);
						}
						else
						{
							oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
							oShape.SetLeft(nMainPosX2);
						}
						oShape.SetRelativeVerticalPosition(MSWord::wdRelativeVerticalPositionPage);
						oShape.SetTop(nMainPosY2);
					}
				}

				MSWord::Tables oTables = oWordSel.GetTables();
				if (oTables.GetCount()>0)
				{
					MSWord::Table oTable = oTables.Item(1);
					oTable.Select();
					oWordSel = m_WordApp.GetSelection();
					MSWord::Cells oCells = oWordSel.GetCells();
					long lVertAlignment = oCells.GetVerticalAlignment();
					if (lVertAlignment != MSWord::wdCellAlignVerticalTop)
					{
						oCells.SetVerticalAlignment(MSWord::wdCellAlignVerticalTop);
						lVertAlignment = oCells.GetVerticalAlignment();
					}
				}
			}
		}
		oWordSel.GoTo(COleVariant((short)MSWord::wdGoToPage),COleVariant((short)MSWord::wdGoToAbsolute),COleVariant((short)2),vOpt);
		if(!strSubTester.IsEmpty() || (!bReplace && nSubPosX>0 && nSubPosY>0))
		{
			//定位副测
			strWildcards = GetWildcards(strSubTester);	
			oWordSel = m_WordApp.GetSelection();
			oWordFind = oWordSel.GetFind();
			bool bFind = false;
			if (bReplace)
			{
				COleVariant varString(_T(""));
				bFind = oWordFind.Execute(COleVariant(strWildcards),vFalse,vFalse,vTrue,vFalse,
					vFalse,vTrue,&vtWindWrap,vFalse,varString,vOpt,vOpt,vOpt,vOpt,vOpt);
			}
			else
			{
				bFind = oWordFind.Execute(COleVariant(strWildcards),vFalse,vFalse,vTrue,vFalse,
					vFalse,vTrue,&vtWindWrap,vFalse,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
			}
			if (bFind)
			{
				oWordSel.GoTo(COleVariant((short)MSWord::wdGoToPage),COleVariant((short)MSWord::wdGoToAbsolute),COleVariant((short)2),vOpt);
				oWordShapes = oWordSel.GetInlineShapes();
				oWordShape = oWordShapes.AddPicture(strSubTesterSignFile,vFalse,vTrue,vOpt);
				oShape = oWordShape.ConvertToShape();
				oWordWrpFormat = oShape.GetWrapFormat();
				oWordWrpFormat.SetType((long)6);
				oPictureFormat = oShape.GetPictureFormat();
				oPictureFormat.SetTransparentBackground(lTransTrue);
				oPictureFormat.SetTransparencyColor(RGB(255,255,255));
				if (bReplace)
				{
					oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
					oShape.SetLeft(nSubPosX-40);//左移40个像素，可调
				}
				else
				{
					oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
					oShape.SetLeft(nSubPosX);
				}
				oShape.SetRelativeVerticalPosition(MSWord::wdRelativeVerticalPositionPage);
				oShape.SetTop(nSubPosY);
				MSWord::Tables oTables = oWordSel.GetTables();
				if (oTables.GetCount()>0)
				{
					MSWord::Table oTable = oTables.Item(1);
					oTable.Select();
					oWordSel = m_WordApp.GetSelection();
					MSWord::Cells oCells = oWordSel.GetCells();
					long lVertAlignment = oCells.GetVerticalAlignment();
					if (lVertAlignment != MSWord::wdCellAlignVerticalTop)
					{
						oCells.SetVerticalAlignment(MSWord::wdCellAlignVerticalTop);
						lVertAlignment = oCells.GetVerticalAlignment();
					}
				}
			}
		}
		oWordWrpFormat.ReleaseDispatch();
		oPictureFormat.ReleaseDispatch();
		oShape.ReleaseDispatch();
		oWordShape.ReleaseDispatch();
		oWordShapes.ReleaseDispatch();	
		oWordFind.ReleaseDispatch();
		oWordSel.ReleaseDispatch();
		
		m_Doc.Save();
	}
	catch(...){}
}

void CWordToPdf::InsertEcptAuditorSign(const CString& strAuditorSignFile,CAuditorSignPos& auditorSignPos)
{
	if(m_WordApp == NULL||m_Doc == NULL)
	{
		return;
	}
	try
	{
		MSWord::Selection	 oWordSel;
		MSWord::InlineShapes oWordShapes;
		MSWord::InlineShape	 oWordShape;
		MSWord::Shapes		 oShapes;
		MSWord::Shape		 oShape;
		MSWord::WrapFormat	 oWordWrpFormat;
		MSWord::PictureFormat oPictureFormat;
		MSWord::Find		 oWordFind;
		COleVariant vTrue((short)TRUE),vFalse((short)FALSE),vOpt((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
		COleVariant vtWindWrap((short)MSWord::wdFindStop);
		long lTransTrue(TRUE),lTransFalse(FALSE);
		CString strCurAuditor = auditorSignPos.m_strCurAuditor;
		strCurAuditor.Trim();
		CString strAuditTitle = auditorSignPos.m_strAuditTitle;
		int nPosX = auditorSignPos.m_nPosX;
		int nPosY = auditorSignPos.m_nPosY;
		bool bReplace = auditorSignPos.m_bReplace;
		oWordSel.GoTo(COleVariant((short)MSWord::wdGoToPage),COleVariant((short)MSWord::wdGoToAbsolute),COleVariant((short)2),vOpt);
		if(!strCurAuditor.IsEmpty() || (!bReplace && nPosX>0 && nPosY>0))
		{
			CString strWildcards = GetWildcards(strCurAuditor);
			oWordSel = m_WordApp.GetSelection();
			oWordFind = oWordSel.GetFind();
			bool bFind = false;
			if (bReplace)
			{
				COleVariant varString(_T(""));
				bFind = oWordFind.Execute(COleVariant(strWildcards),vFalse,vFalse,vTrue,vFalse,
					vFalse,vTrue,&vtWindWrap,vFalse,varString,vOpt,vOpt,vOpt,vOpt,vOpt);
			}
			else
			{
				bFind = oWordFind.Execute(COleVariant(strWildcards),vFalse,vFalse,vTrue,vFalse,
					vFalse,vTrue,&vtWindWrap,vFalse,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
			}
			if (bFind)
			{
				oWordSel.GoTo(COleVariant((short)MSWord::wdGoToPage),COleVariant((short)MSWord::wdGoToAbsolute),COleVariant((short)2),vOpt);
				oWordShapes = oWordSel.GetInlineShapes();
				oWordShape = oWordShapes.AddPicture(strAuditorSignFile,vFalse,vTrue,vOpt);
				oShape = oWordShape.ConvertToShape();
				oWordWrpFormat = oShape.GetWrapFormat();
				oWordWrpFormat.SetType((long)6);
				oPictureFormat = oShape.GetPictureFormat();
				oPictureFormat.SetTransparentBackground(lTransTrue);
				oPictureFormat.SetTransparencyColor(RGB(255,255,255));
				if (bReplace)
				{
					oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
					oShape.SetLeft(nPosX-50);//左移50个像素，可调
				}
				else
				{
					oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
					oShape.SetLeft(nPosX);
				}
				oShape.SetRelativeVerticalPosition(MSWord::wdRelativeVerticalPositionPage);
				oShape.SetTop(nPosY);
				MSWord::Tables oTables = oWordSel.GetTables();
				if (oTables.GetCount()>0)
				{
					MSWord::Table oTable = oTables.Item(1);
					oTable.Select();
					oWordSel = m_WordApp.GetSelection();
					MSWord::Cells oCells = oWordSel.GetCells();
					long lVertAlignment = oCells.GetVerticalAlignment();
					if (lVertAlignment != MSWord::wdCellAlignVerticalTop)
					{
						oCells.SetVerticalAlignment(MSWord::wdCellAlignVerticalTop);
						lVertAlignment = oCells.GetVerticalAlignment();
					}
				}
				oWordWrpFormat.ReleaseDispatch();
				oPictureFormat.ReleaseDispatch();
				oShape.ReleaseDispatch();
				oWordShape.ReleaseDispatch();
				oWordShapes.ReleaseDispatch();	
			}
			oWordFind.ReleaseDispatch();
			oWordSel.ReleaseDispatch();
		}

		m_Doc.Save();
	}
	catch(...){}
}

void CWordToPdf::InsertEcptApproverSign(const CString& strApproverSignFile,CApproverSignPos& approverSignPos)
{
	if(m_WordApp == NULL||m_Doc == NULL)
	{
		return;
	}
	try
	{
		MSWord::Selection	 oWordSel;
		MSWord::InlineShapes oWordShapes;
		MSWord::InlineShape	 oWordShape;
		MSWord::Shapes		 oShapes;
		MSWord::Shape		 oShape;
		MSWord::WrapFormat	 oWordWrpFormat;
		MSWord::PictureFormat oPictureFormat;
		MSWord::Find		 oWordFind;
		COleVariant vTrue((short)TRUE),vFalse((short)FALSE),vOpt((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
		COleVariant vtWindWrap((short)MSWord::wdFindStop);
		long lTransTrue(TRUE),lTransFalse(FALSE);
		CString strApprover = approverSignPos.m_strCurApprover;
		strApprover.Trim();
		CString strApproveTitle = approverSignPos.m_strApproveTitle;
		int nPosX = approverSignPos.m_nPosX;
		int nPosY = approverSignPos.m_nPosY;
		bool bReplace = approverSignPos.m_bReplace;
		oWordSel.GoTo(COleVariant((short)MSWord::wdGoToPage),COleVariant((short)MSWord::wdGoToAbsolute),COleVariant((short)2),vOpt);
		if(!strApprover.IsEmpty() || (!bReplace && nPosX>0 && nPosY>0))
		{
			CString strWildcards = GetWildcards(strApprover);
			oWordSel = m_WordApp.GetSelection();
			oWordFind = oWordSel.GetFind();
			bool bFind = false;
			if (bReplace)
			{
				COleVariant varString(_T(""));
				bFind = oWordFind.Execute(COleVariant(strWildcards),vFalse,vFalse,vTrue,vFalse,
					vFalse,vTrue,&vtWindWrap,vFalse,varString,vOpt,vOpt,vOpt,vOpt,vOpt);
			}
			else
			{
				bFind = oWordFind.Execute(COleVariant(strWildcards),vFalse,vFalse,vTrue,vFalse,
					vFalse,vTrue,&vtWindWrap,vFalse,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
			}
			if (bFind)
			{
				oWordSel.GoTo(COleVariant((short)MSWord::wdGoToPage),COleVariant((short)MSWord::wdGoToAbsolute),COleVariant((short)2),vOpt);
				oWordShapes = oWordSel.GetInlineShapes();
				oWordShape = oWordShapes.AddPicture(strApproverSignFile,vFalse,vTrue,vOpt);
				oShape = oWordShape.ConvertToShape();
				oWordWrpFormat = oShape.GetWrapFormat();
				oWordWrpFormat.SetType((long)6);
				oPictureFormat = oShape.GetPictureFormat();
				oPictureFormat.SetTransparentBackground(lTransTrue);
				oPictureFormat.SetTransparencyColor(RGB(255,255,255));
				if (bReplace)
				{
					oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
					oShape.SetLeft(nPosX-40);//左移40个像素，可调
				}
				else
				{
					oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
					oShape.SetLeft(nPosX);
				}
				oShape.SetRelativeVerticalPosition(MSWord::wdRelativeVerticalPositionPage);
				oShape.SetTop(nPosY);
				MSWord::Tables oTables = oWordSel.GetTables();
				if (oTables.GetCount()>0)
				{
					MSWord::Table oTable = oTables.Item(1);
					oTable.Select();
					oWordSel = m_WordApp.GetSelection();
					MSWord::Cells oCells = oWordSel.GetCells();
					long lVertAlignment = oCells.GetVerticalAlignment();
					if (lVertAlignment != MSWord::wdCellAlignVerticalTop)
					{
						oCells.SetVerticalAlignment(MSWord::wdCellAlignVerticalTop);
						lVertAlignment = oCells.GetVerticalAlignment();
					}
				}
				oWordWrpFormat.ReleaseDispatch();
				oPictureFormat.ReleaseDispatch();
				oShape.ReleaseDispatch();
				oWordShape.ReleaseDispatch();
				oWordShapes.ReleaseDispatch();	
			}
			oWordFind.ReleaseDispatch();
			oWordSel.ReleaseDispatch();
		}
		m_Doc.Save();
	}
	catch(...){}
}

void CWordToPdf::InsertEcptRevisionerSign(const CString& strRevisionerSignFile,CRevisionerSignPos& revisionerSignPos)
{
	if(m_WordApp == NULL||m_Doc == NULL)
	{
		return;
	}
	try
	{
		MSWord::Selection	 oWordSel;
		MSWord::InlineShapes oWordShapes;
		MSWord::InlineShape	 oWordShape;
		MSWord::Shapes		 oShapes;
		MSWord::Shape		 oShape;
		MSWord::WrapFormat	 oWordWrpFormat;
		MSWord::PictureFormat oPictureFormat;
		MSWord::Find		 oWordFind;
		COleVariant vTrue((short)TRUE),vFalse((short)FALSE),vOpt((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
		COleVariant vtWindWrap((short)MSWord::wdFindStop);
		long lTransTrue(TRUE),lTransFalse(FALSE);
		CString strCurRevisioner = revisionerSignPos.m_strCurRevisioner;
		strCurRevisioner.Trim();
		CString strPrevRevisioner = revisionerSignPos.m_strPrevRevisioner;
		strPrevRevisioner.Trim();
		CString strRevisionTitle = revisionerSignPos.m_strRevisionTitle;
		int nPosX = revisionerSignPos.m_nPosX;
		int nPosY = revisionerSignPos.m_nPosY;
		bool bReplace = revisionerSignPos.m_bReplace;
		oWordSel.GoTo(COleVariant((short)MSWord::wdGoToPage),COleVariant((short)MSWord::wdGoToAbsolute),COleVariant((short)2),vOpt);
		CString strFind;
		if(strCurRevisioner.CompareNoCase(strPrevRevisioner) != 0)
		{
			strFind = strPrevRevisioner;
		}
		else
		{
			strFind = strCurRevisioner;
		}
		if(!strFind.IsEmpty() || (!bReplace && nPosX>0 && nPosY>0))
		{
			CString strWildcards = GetWildcards(strFind);
			oWordSel = m_WordApp.GetSelection();
			oWordFind = oWordSel.GetFind();
			bool bFind = FALSE; 
			if (!bReplace && strFind == strPrevRevisioner)
			{
				COleVariant varString(strCurRevisioner);
				bFind = oWordFind.Execute(COleVariant(strWildcards),vFalse,vFalse,vTrue,vFalse,
					vFalse,vTrue,&vtWindWrap,vFalse,varString,vOpt,vOpt,vOpt,vOpt,vOpt);
			}
			else
			{
				COleVariant varString(_T(""));
				bFind = oWordFind.Execute(COleVariant(strWildcards),vFalse,vFalse,vTrue,vFalse,
					vFalse,vTrue,&vtWindWrap,vFalse,varString,vOpt,vOpt,vOpt,vOpt,vOpt);
			}
			if (bFind)
			{
				oWordSel.GoTo(COleVariant((short)MSWord::wdGoToPage),COleVariant((short)MSWord::wdGoToAbsolute),COleVariant((short)2),vOpt);
				oWordShapes = oWordSel.GetInlineShapes();
				oWordShape = oWordShapes.AddPicture(strRevisionerSignFile,vFalse,vTrue,vOpt);
				oShape = oWordShape.ConvertToShape();
				oWordWrpFormat = oShape.GetWrapFormat();
				oWordWrpFormat.SetType((long)6);
				oPictureFormat = oShape.GetPictureFormat();
				oPictureFormat.SetTransparentBackground(lTransTrue);
				oPictureFormat.SetTransparencyColor(RGB(255,255,255));
				if (bReplace)
				{
					oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
					oShape.SetLeft(nPosX-30);//左移30个像素，可调
				}
				else
				{
					oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
					oShape.SetLeft(nPosX);
				}
				oShape.SetRelativeVerticalPosition(MSWord::wdRelativeVerticalPositionPage);
				oShape.SetTop(nPosY);
				
				MSWord::Tables oTables = oWordSel.GetTables();
				if (oTables.GetCount()>0)
				{
					MSWord::Table oTable = oTables.Item(1);
					oTable.Select();
					oWordSel = m_WordApp.GetSelection();
					MSWord::Cells oCells = oWordSel.GetCells();
					long lVertAlignment = oCells.GetVerticalAlignment();
					if (lVertAlignment != MSWord::wdCellAlignVerticalTop)
					{
						oCells.SetVerticalAlignment(MSWord::wdCellAlignVerticalTop);
						lVertAlignment = oCells.GetVerticalAlignment();
					}
				}
				oWordWrpFormat.ReleaseDispatch();
				oPictureFormat.ReleaseDispatch();
				oShape.ReleaseDispatch();
				oWordShape.ReleaseDispatch();
				oWordShapes.ReleaseDispatch();	
			}
			oWordFind.ReleaseDispatch();
			oWordSel.ReleaseDispatch();
		}
		m_Doc.Save();
	}
	catch(...){}
}

void CWordToPdf::InsertEcptTypistSign(const CString& strTypistSignFile,CTypistSignPos& typistSignPos)
{
	if(m_WordApp == NULL||m_Doc == NULL)
	{
		return;
	}
	try
	{
		MSWord::Selection	 oWordSel;
		MSWord::InlineShapes oWordShapes;
		MSWord::InlineShape	 oWordShape;
		MSWord::Shapes		 oShapes;
		MSWord::Shape		 oShape;
		MSWord::WrapFormat	 oWordWrpFormat;
		MSWord::PictureFormat oPictureFormat;
		MSWord::Find		 oWordFind;
		COleVariant vTrue((short)TRUE),vFalse((short)FALSE),vOpt((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
		COleVariant vtWindWrap((short)MSWord::wdFindStop);
		long lTransTrue(TRUE),lTransFalse(FALSE);
		
		CString strTypeTitle = typistSignPos.m_strTypeTitle;
		CString strCurTypist = typistSignPos.m_strCurTypist;
		strCurTypist.Trim();
		int nPosX = typistSignPos.m_nPosX;
		int nPosY = typistSignPos.m_nPosY;
		bool bReplace = typistSignPos.m_bReplace;
		bool bErase = typistSignPos.m_bTypeErase;
		oWordSel.GoTo(COleVariant((short)MSWord::wdGoToPage),COleVariant((short)MSWord::wdGoToAbsolute),COleVariant((short)2),vOpt);

		CString strWildcards = GetWildcards(strCurTypist);
		oWordSel = m_WordApp.GetSelection();
		oWordFind = oWordSel.GetFind();

		if (bErase)
		{
			COleVariant varString(_T(""));
			oWordFind.Execute(COleVariant(strWildcards),vFalse,vFalse,vTrue,vFalse,
				vFalse,vTrue,&vtWindWrap,vFalse,varString,vOpt,vOpt,vOpt,vOpt,vOpt);

			oWordFind.ReleaseDispatch();
			oWordSel.ReleaseDispatch();
			m_Doc.Save();
			return;
		}
		
		if(!strCurTypist.IsEmpty() || (!bReplace && nPosX>0 && nPosY>0))
		{
			bool bFind = false;
			if (bReplace)
			{
				COleVariant varString(_T(""));
				bFind = oWordFind.Execute(COleVariant(strWildcards),vFalse,vFalse,vTrue,vFalse,
					vFalse,vTrue,&vtWindWrap,vFalse,varString,vOpt,vOpt,vOpt,vOpt,vOpt);
			}
			else
			{
				bFind = oWordFind.Execute(COleVariant(strWildcards),vFalse,vFalse,vTrue,vFalse,
					vFalse,vTrue,&vtWindWrap,vFalse,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
			}
			if (bFind)
			{
				oWordSel.GoTo(COleVariant((short)MSWord::wdGoToPage),COleVariant((short)MSWord::wdGoToAbsolute),COleVariant((short)2),vOpt);
				oWordShapes = oWordSel.GetInlineShapes();
				oWordShape = oWordShapes.AddPicture(strTypistSignFile,vFalse,vTrue,vOpt);
				oShape = oWordShape.ConvertToShape();
				oWordWrpFormat = oShape.GetWrapFormat();
				oWordWrpFormat.SetType((long)6);
				oPictureFormat = oShape.GetPictureFormat();
				oPictureFormat.SetTransparentBackground(lTransTrue);
				oPictureFormat.SetTransparencyColor(RGB(255,255,255));
				if (bReplace)
				{
					oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
					oShape.SetLeft(nPosX-50);//左移50个像素，可调
				}
				else
				{
					oShape.SetRelativeHorizontalPosition(MSWord::wdRelativeHorizontalPositionPage);
					oShape.SetLeft(nPosX);
				}
				oShape.SetRelativeVerticalPosition(MSWord::wdRelativeVerticalPositionPage);
				oShape.SetTop(nPosY);
				MSWord::Tables oTables = oWordSel.GetTables();
				if (oTables.GetCount()>0)
				{
					MSWord::Table oTable = oTables.Item(1);
					oTable.Select();
					oWordSel = m_WordApp.GetSelection();
					MSWord::Cells oCells = oWordSel.GetCells();
					long lVertAlignment = oCells.GetVerticalAlignment();
					if (lVertAlignment != MSWord::wdCellAlignVerticalTop)
					{
						oCells.SetVerticalAlignment(MSWord::wdCellAlignVerticalTop);
						lVertAlignment = oCells.GetVerticalAlignment();
					}
				}
				oWordWrpFormat.ReleaseDispatch();
				oPictureFormat.ReleaseDispatch();
				oShape.ReleaseDispatch();
				oWordShape.ReleaseDispatch();
				oWordShapes.ReleaseDispatch();	
			}
			oWordFind.ReleaseDispatch();
			oWordSel.ReleaseDispatch();
		}

		m_Doc.Save();
	}
	catch(...){}
}

CString CWordToPdf::GetWildcards(CString strOperatorName)
{
	CString strWildcards;
	CString strFind = strOperatorName;
	for (int i=0;i<strFind.GetLength();i++)
	{
		strWildcards += strFind[i];
		if (i<strFind.GetLength()-1)
		{
			strWildcards += "*";
		}
	}
	return strWildcards;
}

//默认选择Microsoft Print to PDF打印机打印转换,但打印出来的PDF文档中图片的清晰度可能受损
void CWordToPdf::PrintToPdf(const CString strWordFileName, const CString strPdfFileName)
{
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);  //代表可选参数

	long nVal = MSWord::wdPrintAllDocument;
	CComVariant vRange(nVal);
	CComVariant vTrue((long)TRUE);
	CComVariant vFalse((long)FALSE); 
	CComVariant vOutFile(strPdfFileName); 
	CComVariant vItem((long)MSWord::wdPrintDocumentWithMarkup);
	CComVariant vCopies((long)1);
	CComVariant vPageType((long)MSWord::wdPrintAllPages);
	CComVariant vPrintToFile((long)FALSE);
	CComVariant vCollate((long)FALSE);
	CComVariant vFileName(strWordFileName);  
	CComVariant vPrintZoomColumn((long)FALSE);
	CComVariant vPrintZoomRow((long)FALSE);
	CComVariant vManualDuplexPrint((long)FALSE);

	m_WordApp.PrintOut(&vTrue,  //BackGround，是否后台打印
		&vFalse,            //Append，是否追加到文件
		&vRange,            //Range，页码范围，wdPrintAllDocument打印全部
		&vOutFile,          //OutPutFileName，输出文件名
		&vOpt,              //From,起始页码
		&vOpt,				//To,结束页码
		&vItem,             //Item，打印内容，wdPrintDocumentWithMarkup为当前内容包括标记
		&vCopies,           //Coppies，打印份数
		&vOpt,              //Pages，页码范围
		&vPageType,         //PageType，打印页码类型，wdPrintAllPages为所有页面
		&vPrintToFile,      //PrintToFile，打印到文件
		&vCollate,          //Collate，是否分页
		&vFileName,         //FileName，Word文档名称
		&vOpt,              //ActivePrinterMacGX，Macintosh版，此参数仅在Microsoft Office Macintosh Edition中可用
		&vOpt,              //ManualDuplexPrint，是否双面打印
		&vPrintZoomColumn,  //vPrintZoomColumn，水平页数
		&vPrintZoomRow,     //vPrintZoomRow，垂直页数
		&vFalse,            //PrintZoomWidth，缩放宽度
		&vFalse);           //PrintZoomHeight，缩放高度
}

void CWordToPdf::SaveToPdf(const CString& strPdfFile)
{
	COleVariant varstrNull(_T(""));
	COleVariant vTrue(short(1),VT_BOOL),vFalse(short(0),VT_BOOL),varFalse(short(0),VT_BOOL);
	CComVariant FileName(strPdfFile);
	CComVariant FileFormat(17);//pdf格式
	m_Doc.SaveAs(&FileName,
		&FileFormat,
		&vFalse,
		varstrNull,
		&vTrue,		
		varstrNull,
		&vFalse,
		&vFalse,
		&vFalse,
		&vFalse,
		&vFalse
		/*&vOpt,&vOpt,&vOpt,&vOpt,&vOpt*/);
}

void CWordToPdf::CloseWordFile()
{
	COleVariant vTrue((long)TRUE), vFalse((long)FALSE),
		covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	if (m_Doc != NULL)
	{
		m_Doc.Close(vFalse,covOptional,covOptional);
		m_Doc.ReleaseDispatch();
	}

	m_Doc = NULL;
}

BOOL CWordToPdf::CreatWordApplation(BOOL bVisible)
{
	if (m_WordApp != NULL)
	{
		return TRUE;
	}

	//创建对象
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		IUnknown *pUnk;
		IDispatch *pDisp;
		CLSID clsid;
		CLSIDFromProgID(L"Word.Application", &clsid); 
		// 查看是否有已经打开的Word对象
		HRESULT hr = GetActiveObject(clsid, NULL, (IUnknown**)&pUnk);
		if (!FAILED(hr)) 
		{
			hr = pUnk->QueryInterface(IID_IDispatch, (void **)&pDisp);
			ASSERT(!FAILED(hr));
			m_WordApp.AttachDispatch(pDisp,TRUE);
			pUnk->Release();
		}
		else	// 若无，则新建一个Word对象
		{
			if(!m_WordApp.CreateDispatch(clsid,NULL))
			{
				AfxMessageBox(_T("创建Word对象失败!"));
				exit(1);
			}
		}
		m_WordApp.SetVisible(bVisible);  //This shows the application.
	}
	catch (...)
	{
	}

	return TRUE;
}

BOOL CWordToPdf::ExitWordApplation()
{
	//关闭文档
	try
	{
		CloseWordFile();
	}
	catch (...)
	{
		m_Doc = NULL;
		TRACE(L"Close word doc error...");
	}
	//退出WORD应用
	try
	{
		if(m_WordApp)
		{
			COleVariant covTrue((long)TRUE);
			COleVariant covFalse((long)FALSE);
			COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
			m_WordApp.ReleaseDispatch();
			m_WordApp.Quit(covFalse, covOptional, covOptional);
			m_WordApp = NULL;
		}
	}
	catch (...) 
	{
		TRACE("catch error-----");
	}

	return TRUE;
}

BOOL CWordToPdf::WordToPdf(const CString& strFileDoc,CString& strFilePdf)
{
	strFilePdf = ChangeFilePostfix(strFileDoc,_T("pdf"));
	if(IsFileExist(strFilePdf))
	{
		return TRUE;
	}

	if(!CreatWordApplation(FALSE))
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Word启动失败，不能完成Doc到Pdf的转换！"));
		return FALSE;
	}

	OpenWordFile(strFileDoc);
	SaveToPdf(strFilePdf);

	ExitWordApplation();

	return TRUE;
}

void CWordToPdf::GetDefaultPrinter(CString& csPrinter)
{
	HANDLE hPrinter = NULL;
	DWORD dwSize = 0;
	if((!::GetDefaultPrinter(NULL,&dwSize)) && GetLastError()==ERROR_INSUFFICIENT_BUFFER)
	{
		TCHAR *szPrinter = new TCHAR[dwSize+1];
		if(::GetDefaultPrinter(szPrinter, &dwSize))
		{
			csPrinter = szPrinter;
		}
		delete []szPrinter;
	}
}

void CWordToPdf::SetDefaultPrinter(const CString& strPrinterName)
{
	CString strDefPrinter;
	GetDefaultPrinter(strDefPrinter);

	if (strDefPrinter.IsEmpty() || strDefPrinter.CompareNoCase(strPrinterName)) //Foxit Reader PDF Printer/Adobe PDF
	{
		::SetDefaultPrinter(strPrinterName);
	}
}

int CWordToPdf::KillProcessByTitle(const CString& strWindowName)
{
	HWND hWindow = FindWindow(NULL, strWindowName);
	if (hWindow == NULL)
	{
		return -1;
	}

	PostMessage(hWindow, WM_CLOSE, 0, 0);

	DWORD dwProcessID;
	HANDLE hProcess;
	if (GetWindowThreadProcessId(hWindow, &dwProcessID) == 0)
	{
		return -2;
	}

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
	if (hProcess == NULL)
	{
		return -3;
	}

	if (!TerminateProcess(hProcess, 0))
	{
		return -4;
	}

	return 0;
}

void CWordToPdf::CopyFolder(const CString& szFromPath,const CString& szToPath)
{
	CXFileMngr rptMngr;

	CXFileType *pFileType = rptMngr.AddFileType(_T("PDF"), _T("PDF"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("PDF"), _T("pdf"));

	rptMngr.InitByXFileTypes();
	rptMngr.SetLibraryPath(szFromPath);

	POS pos = rptMngr.GetHeadPosition();
	while (pos)
	{
		CXFile* pFile = (CXFile*)rptMngr.GetNext(pos);
		rptMngr.XCopyFile(pFile,szToPath,FALSE);
	}

	DeleteAllDirectorys(szFromPath,FALSE);
}

BOOL CWordToPdf::PrintTransFile(const CString& strPrinterName,const CString& strPrintOutPath,const CString& strPdfFile)
{
	CString strTempFile = strPrintOutPath;
	CString strFileName;
	strFileName = GetPathFileNameFromFilePathName(strPdfFile);
	strTempFile.Append(strFileName);

	SHELLEXECUTEINFO ShExecInfo = {0};
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = TEXT("print");
	ShExecInfo.lpFile = strPdfFile;	
	ShExecInfo.lpParameters = NULL;	
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;	
	ShellExecuteEx(&ShExecInfo);

	PBYTE pJob = (PBYTE)new JOB_INFO_1;
	if(!pJob)
	{
		return FALSE;
	}

	BOOL bContinue = TRUE;	
	DWORD dwNeeded = 0,dwReturned =0;
	HANDLE hPrinter;

	if(!OpenPrinter((LPTSTR)(LPCTSTR)strPrinterName,&hPrinter,NULL))
	{
		return FALSE;
	}

	EnumJobs(hPrinter,0,1,1,pJob,sizeof(JOB_INFO_1),&dwNeeded,&dwReturned);
	MSG msg;
	while(bContinue)
	{	
		//check the result
		CFile PdfFile;
		if(PdfFile.Open(strTempFile, CFile::modeRead))
		{
			PdfFile.Close();
			break;
		}

		if(::PeekMessage(&msg,NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		Sleep(100);

		EnumJobs(hPrinter,0,1,1,pJob,sizeof(JOB_INFO_1),&dwNeeded,&dwReturned);
		if(dwNeeded > 0)
			bContinue = TRUE;
	}
	delete pJob;
	
	return TRUE;
}

// CWordToPdf_AdobePrint

CWordToPdf_AdobePrint::CWordToPdf_AdobePrint()
{

}

CWordToPdf_AdobePrint::~CWordToPdf_AdobePrint()
{

}

void CWordToPdf_AdobePrint::PrintToPdf(const CString strWordFileName, const CString strPdfFileName)
{
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);  //代表可选参数

	long nVal = MSWord::wdPrintAllDocument;
	CComVariant vRange(nVal);
	CComVariant vTrue((long)TRUE);
	CComVariant vFalse((long)FALSE); 
	CComVariant vOutFile(_T("")); 
	CComVariant vItem((long)MSWord::wdPrintDocumentWithMarkup);
	CComVariant vCopies((long)1);
	CComVariant vPageType((long)MSWord::wdPrintAllPages);
	CComVariant vPrintToFile((long)FALSE);
	CComVariant vCollate((long)FALSE);
	CComVariant vFileName(strWordFileName);  
	CComVariant vPrintZoomColumn((long)FALSE);
	CComVariant vPrintZoomRow((long)FALSE);
	CComVariant vManualDuplexPrint((long)FALSE);

	m_WordApp.PrintOut(&vTrue,  //BackGround，是否后台打印
		&vFalse,            //Append，是否追加到文件
		&vRange,            //Range，页码范围，wdPrintAllDocument打印全部
		&vOutFile,          //OutPutFileName，输出文件名
		&vOpt,              //From,起始页码
		&vOpt,				//To,结束页码
		&vItem,             //Item，打印内容，wdPrintDocumentWithMarkup为当前内容包括标记
		&vCopies,           //Coppies，打印份数
		&vOpt,              //Pages，页码范围
		&vPageType,         //PageType，打印页码类型，wdPrintAllPages为所有页面
		&vPrintToFile,      //PrintToFile，打印到文件
		&vCollate,          //Collate，是否分页
		&vFileName,         //FileName，Word文档名称
		&vOpt,              //ActivePrinterMacGX，Macintosh版，此参数仅在Microsoft Office Macintosh Edition中可用
		&vOpt,              //ManualDuplexPrint，是否双面打印
		&vPrintZoomColumn,  //vPrintZoomColumn，水平页数
		&vPrintZoomRow,     //vPrintZoomRow，垂直页数
		&vFalse,            //PrintZoomWidth，缩放宽度
		&vFalse);           //PrintZoomHeight，缩放高度
}

bool CWordToPdf_AdobePrint::ProcessPdfFilePrintOut(const CString& strSourceWordFileName, const CString& strDestPdfFile)
{
	int nWaitCount = 0;
	CString strPdfFile = _T("");

		strPdfFile = m_strPdfOutputPath;
		if (strPdfFile.Right(1) != "\\")
		{
			strPdfFile += _T("\\");
		}
		strPdfFile += strSourceWordFileName;
		strPdfFile = ChangeFilePostfix(strPdfFile, _T("pdf"));

	while (TRUE)
	{
		Sleep(500);
		nWaitCount ++;

		CFile PdfFile;
		if(PdfFile.Open(strPdfFile, CFile::modeRead))
		{
			PdfFile.Close();
			break;
		}

		if (nWaitCount >= 10*12)
		{
			return FALSE;
		}
	}
	MoveFile(strPdfFile,strDestPdfFile);
	return TRUE;
}

// CWordToPdf_MSPrint 

CWordToPdf_MSPrint::CWordToPdf_MSPrint()
{

}

CWordToPdf_MSPrint::~CWordToPdf_MSPrint()
{

}

void CWordToPdf_MSPrint::PrintToPdf(const CString strWordFileName, const CString strPdfFileName)
{
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);  //代表可选参数

	long nVal = MSWord::wdPrintAllDocument;
	CComVariant vRange(nVal);
	CComVariant vTrue((long)TRUE);
	CComVariant vFalse((long)FALSE); 
	CComVariant vOutFile(strPdfFileName); 
	CComVariant vItem((long)MSWord::wdPrintDocumentWithMarkup);
	CComVariant vCopies((long)1);
	CComVariant vPageType((long)MSWord::wdPrintAllPages);
	CComVariant vPrintToFile((long)FALSE);
	CComVariant vCollate((long)FALSE);
	CComVariant vFileName(strWordFileName);  
	CComVariant vPrintZoomColumn((long)FALSE);
	CComVariant vPrintZoomRow((long)FALSE);
	CComVariant vManualDuplexPrint((long)FALSE);

	m_WordApp.PrintOut(&vTrue,  //BackGround，是否后台打印
		&vFalse,            //Append，是否追加到文件
		&vRange,            //Range，页码范围，wdPrintAllDocument打印全部
		&vOutFile,          //OutPutFileName，输出文件名
		&vOpt,              //From,起始页码
		&vOpt,				//To,结束页码
		&vItem,             //Item，打印内容，wdPrintDocumentWithMarkup为当前内容包括标记
		&vCopies,           //Coppies，打印份数
		&vOpt,              //Pages，页码范围
		&vPageType,         //PageType，打印页码类型，wdPrintAllPages为所有页面
		&vPrintToFile,      //PrintToFile，打印到文件
		&vCollate,          //Collate，是否分页
		&vFileName,         //FileName，Word文档名称
		&vOpt,              //ActivePrinterMacGX，Macintosh版，此参数仅在Microsoft Office Macintosh Edition中可用
		&vOpt,              //ManualDuplexPrint，是否双面打印
		&vPrintZoomColumn,  //vPrintZoomColumn，水平页数
		&vPrintZoomRow,     //vPrintZoomRow，垂直页数
		&vFalse,            //PrintZoomWidth，缩放宽度
		&vFalse);           //PrintZoomHeight，缩放高度
}

bool CWordToPdf_MSPrint::ProcessPdfFilePrintOut(const CString& strSourceWordFileName, const CString& strDestPdfFile)
{
	int nWaitCount = 0;
	while (TRUE)
	{
		Sleep(500);
		nWaitCount ++;
		
		CFile PdfFile;
		if(PdfFile.Open(strDestPdfFile, CFile::modeRead))
		{
			PdfFile.Close();
			break;
		}

		if (nWaitCount >= 10*12)
		{
			return FALSE;
		}
	}
	return TRUE;
}

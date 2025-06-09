// TextEditDoc.cpp : 实现文件
//

#include "stdafx.h"
#include "..\..\SclFileTest\SCLCompareCheckDev.h"
#include "..\..\SclFileTest\MainFrm.h"
#include "AppGlobals.h"
#include "SclTextCCDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CSclTextCCDoc
IMPLEMENT_DYNCREATE(CSclTextCCDoc, CPfxEditDoc)
BEGIN_MESSAGE_MAP(CSclTextCCDoc, CPfxEditDoc)
END_MESSAGE_MAP()

CSclTextCCDoc::CSclTextCCDoc()
{
        m_nOpenConverter = PFX_EC_FILE_CONVERTER_AUTO_DETECT;
        m_nSaveConverter = PFX_EC_FILE_CONVERTER_ANSI;
		m_pPfxEditTypeInfo = NULL;
		m_bDircClose = FALSE;
}

CSclTextCCDoc::~CSclTextCCDoc()
{
	if (m_pPfxEditTypeInfo!= NULL)
	{
		delete m_pPfxEditTypeInfo;
		m_pPfxEditTypeInfo = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSclTextCCDoc 命令
BOOL CSclTextCCDoc::OnInitDocument(LPCTSTR pszPathName)
{
        // 一定要调用基类的实现。
    CPfxEditDoc::OnInitDocument(pszPathName);
	if (m_pPfxEditTypeInfo == NULL)
	{
		CString bstList[50] = {"id=","fc=","cdc=","xsi=","ext=","ord=","max=","name=","desc=","type=","unit=","inst=","dchg=","qchg=","dupd=","sAddr=","appID=","rptID=","xmlns=","bType=","seqNum=","period=","datSet=",
			"intgPd=","toolID=","cbName=","ldInst=","lnType=","prefix=","lnInst=","doName=","lnClass=","confRev=","bufTime=","version=","iedName=","buffered=","encoding=","revision=","configRef=","timeStamp=","fixLnInst=",
			"optFields=","reasonCode=","multiplier=","manufacturer=","configVersion=","maxAttributes=","nameStructure=","schemaLocation="};

		m_pPfxEditTypeInfo = new CPfxEditTypeInfo;
		LONG cls = 0;

		for (int nIndex=0;nIndex<50;nIndex++)
		{		
			CPfxEditKeyClass theClass(bstList[nIndex], RGB(255,0,0));
			cls = m_pPfxEditTypeInfo->SetKeyClass(theClass);
			m_pPfxEditTypeInfo->SetKeyword(cls,bstList[nIndex]);
		}

		CString strList[40] = {"SCL","Header","History","Hitem","Substation","Private","VoltageLevel","Voltage","Bay","Communication","SubNetwork","ConnectedAP","GSE","Address",
			"P","MinTime","MaxTime","SMV","IED","Services","AccessPoint","Server","LDevice","LN0","DataSet","FCDA","ReportControl","LN","DOI","DAI","Val","SDI","DataTypeTemplates",
			"LNodeType","DO","DOType","DA","EnumType","EnumVal","SDO"};

		for (int nIndex=0;nIndex<40;nIndex++)
		{		
			CPfxEditKeyClass theClass(strList[nIndex], RGB(0,0,255));
			cls = m_pPfxEditTypeInfo->SetKeyClass(theClass);
			m_pPfxEditTypeInfo->SetKeyword(cls,strList[nIndex]);
		}

	}
	SetTypeInfoPtr(m_pPfxEditTypeInfo);

	// 决定文档是否是只读状态，默认地我们不允许用户修改只读文件。
	if (pszPathName != NULL) 
	{
		CFileStatus status;
		CFile::GetStatus(pszPathName, status);
		SetReadOnly((status.m_attribute & CFile::readOnly) == CFile::readOnly);
	} 
	else
		SetReadOnly(0);
	return true;
}

LONG CSclTextCCDoc::OnEvent(UINT nCode, LPARAM lParam)
{
        CMainFrame* pAppFrame = GetAppFrame();
        ASSERT(pAppFrame != NULL);
        
        switch (nCode)
        {
        case PFX_EN_WORD_WRAPPING:
                break;
        
        case PFX_EN_SEARCH_PASSED_EOF:
                break;
        
        case PFX_EN_READ_ONLY_DOCUMENT:
                break;
        
        case PFX_EE_OUT_OF_MEMORY:
        case PFX_EE_OUT_OF_RESOURCE:
        case PFX_EE_UNKNOWN_ERROR:
        case PFX_EE_INTERNAL_ERROR:
        case PFX_EE_CONVERT_ERR_ON_LOADING:
        case PFX_EE_CONVERT_ERR_ON_SAVING:
                {
                        struct CErrMsg
                        {
                                UINT nIDCode;
                                UINT nIDString;
                        };
                        
                        static const CErrMsg s_arrErrMsg[] =
                        {
                                {PFX_EE_OUT_OF_MEMORY,   IDS_E_NOT_ENOUGH_MEMORY},
                                {PFX_EE_OUT_OF_RESOURCE, IDS_E_NOT_ENOUGH_RESOURCE},
                                //{PFX_EE_UNKNOWN_ERROR,   ??},
                                //{PFX_EE_INTERNAL_ERROR,  ??},
                                {PFX_EE_CONVERT_ERR_ON_LOADING, IDS_E_CONVERT_ERR_ON_LOADING},
                                {PFX_EE_CONVERT_ERR_ON_SAVING, IDS_E_CONVERT_ERR_ON_SAVING},
                        };

                        for (int i = 0; i < SIZEOF(s_arrErrMsg); i++)
                        {
                                if (s_arrErrMsg[i].nIDCode == nCode)
                                {
                                        nCode = s_arrErrMsg[i].nIDString;
                                        break;
                                }
                        }
                        
                        appAlert1(nCode, MB_OK | MB_ICONERROR);
                }
                break;

        default:
                break;
        }
        return 0;
}

BOOL CSclTextCCDoc::SaveModified()
{
        if ((!IsModified())||(m_bDircClose))
        {
                return true;
        }
        
        // 如果文档有路径名就获取完整的路径名，如果文档是新建的就用它的标题
        // 名。
        CString strPathName = GetPathName();
        if (strPathName.IsEmpty())
        {
                strPathName = GetTitle();
				
                strPathName.TrimRight(STR_MODIFIED_DOCUMENT_TITLE_FLAG);
        }
        
        CString strPrompt;
        strPrompt.Format("%s\n文档已经被修改，保存所作改动？", (LPCTSTR)strPathName);
        
        BOOL bRetVal;
        switch (AfxMessageBox(strPrompt, MB_YESNOCANCEL))
        {
        case IDCANCEL:
                bRetVal = false;
                break;
        
        case IDYES:
                bRetVal = DoSave(NULL,false);
                break;
        
        case IDNO: 
        default: // 贯通。
                bRetVal = true;
                break;
        }
        
        return bRetVal;
}

BOOL CSclTextCCDoc::DoSave(LPCTSTR pszPathName, BOOL bReplace)
// Save the document data to a file
// pszPathName = path name where to save document file
// if pszPathName is NULL then the user will be prompted (SaveAs)
// note: pszPathName can be different than 'm_strPathName'
// if 'bReplace' is true will change file name if successful (SaveAs)
// if 'bReplace' is false will not change path name (SaveCopyAs)
{

	// 示范程序：在这里获取当前的字符编码方案和换行方案。
	// 比字符编码方案是指ANSI，UNICODE，UTF8等。
	// 换行方案是指DOS，UNIX，MAC等。
	LONG nOldFileConverter = GetFileConverter();
	LONG nOldLineBreakType = GetLineBreakType();
	LONG nNewFileConverter = GetFileConverter();
	LONG nNewLineBreakType = GetLineBreakType();

	CString newName = pszPathName;
	if (newName.IsEmpty() || IsReadOnly())
	{
		if (IsReadOnly())
		{
			bReplace = true;
		}

		// 示范程序：在显示另存为对话框时让用户选择字符编码方案和换
		// 行方案。
		if (!GetSaveAsFileName(newName,
			bReplace,
			nNewFileConverter,
			nNewLineBreakType))
		{
			return false;
		}
	}

	// 示范程序：在这里设置用户新的编码方案和换行方案。
	SetFileConverter(nNewFileConverter);
	SetLineBreakType(nNewLineBreakType);
	BOOL bResult = false;

	try
	{
		bResult = OnSaveDocument(newName);
	}
	catch (CException* e)
	{
		TRACE("Failed to save file: %s\n", newName);
		e->Delete();
	}

	if (!bResult) // 如果保存失败，就要恢复原来的转换器和换行格式。
	{
		SetFileConverter(nOldFileConverter);
		SetLineBreakType(nOldLineBreakType);
	}

	// 如果保存失败，并且是“另存为”操作就要将刚才新建的文件删除掉。
	if (!bResult && (pszPathName == NULL))
	{
		// be sure to delete the file
		try
		{
			CFile::Remove(newName);
		}
		catch (CException* e)
		{
			TRACE("Warning: failed to delete file after failed SaveAs.\n");
			e->Delete();
		}
	}

	// reset the title and change the document name
	if (bResult && bReplace)
	{
		SetPathName(newName);
	}

	return bResult;
}
/////////////////////////////////////////////////////////////////////////////
// 当用户修改了文档后，我们需要在程序的标题栏添加一个“*”号来表示文档已经被
// 修改。
void CSclTextCCDoc::SetModifiedFlag(BOOL bModified)
{
        BOOL bDocModified = IsModified();
        if ((bModified && bDocModified) || (!bModified && !bDocModified))
        {
                return;
        }
        
        CPfxEditDoc::SetModifiedFlag(bModified);
        
        CString strTitle = GetTitle();
        if (bModified)
        {
                // 添加文档修改标志，一般是“*”。
                if (strTitle.Right(SIZEOF_NO_NULL(STR_MODIFIED_DOCUMENT_TITLE_FLAG))
                        != STR_MODIFIED_DOCUMENT_TITLE_FLAG)
                {
                        strTitle += STR_MODIFIED_DOCUMENT_TITLE_FLAG;
                }
        }
        else
        {
                if (strTitle.Right(SIZEOF_NO_NULL(STR_MODIFIED_DOCUMENT_TITLE_FLAG))
                        == STR_MODIFIED_DOCUMENT_TITLE_FLAG)
                {
                        strTitle.TrimRight(STR_MODIFIED_DOCUMENT_TITLE_FLAG);
                }
        }
        
        SetTitle(strTitle);
}

BOOL CSclTextCCDoc::GetSaveAsFileName(CString& strFileName,
                                   BOOL bReplace,
                                   LONG& nFileConverter,
                                   LONG& nLineBreakType)
{
        // 示范程序：这里没有处理nFileConverter和nLineBreakType。
        // 你应该自己编写“另存为”文件对话框扩展功能。

        CDocTemplate* pTemplate = GetDocTemplate();
        ASSERT(pTemplate != NULL);
        
        strFileName = m_strPathName;

		long nIndex = m_strPathName.ReverseFind('.');
		if (nIndex!=-1)
		{
			CString strExt = m_strPathName.Mid(nIndex);
			strFileName = m_strPathName.Left(nIndex);
			strFileName += "-文本视图";
			strFileName += strExt;
		}

        if (bReplace && strFileName.IsEmpty())
        {
                strFileName = m_strTitle;
                
                // 未命名且又被修改了的文档窗口标题最后有一个“*”。
                strFileName.TrimRight(STR_MODIFIED_DOCUMENT_TITLE_FLAG);
                
                // 删除最后的空白字符。
                strFileName.TrimRight();
                
                // 删除可能包含的非法字符。
                int iBad = strFileName.FindOneOf(_T("\\/:*?\"<>|"));
                if (iBad != -1)
                {
                        strFileName.ReleaseBuffer(iBad);
                }
                
                // 添加缺省文件扩展名如果已经在文档字符串中指出。
				CString strExt;
				if (pTemplate->GetDocString(strExt, CDocTemplate::filterExt)
					&& !strExt.IsEmpty())
				{
					ASSERT(strExt[0] == '.');
					strFileName += strExt;
				}

        }
        
        TCHAR szTitle[MAX_PATH];

        CFileDialog fd(false, // Save
                NULL, //pszDefExt,
                strFileName, // pszFileName
                OFN_EXPLORER | OFN_ENABLESIZING | OFN_HIDEREADONLY |
                OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, //dwFlags
                "all files(*.*)|*.*|", // pszFilter
                GetAppFrame());  // pParentWnd
        fd.m_ofn.lpstrTitle = szTitle;

        AfxLoadString((bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY),
                szTitle,
                SIZEOF(szTitle));

        strFileName.Empty();
        if (fd.DoModal() == IDOK)
        {
                POSITION pos = fd.GetStartPosition();
                if (pos != NULL)
                {
                        strFileName = fd.GetNextPathName(pos);
                }
        }

        if (!strFileName.IsEmpty())
        {
                CFileStatus status;
                if (CFile::GetStatus(strFileName, status)
                        && ((status.m_attribute & CFile::readOnly) == CFile::readOnly))
                {
                        appAlert2(IDS_E_CAN_NOT_OVERWRITE_READ_ONLY_FILE,
                                MB_OK | MB_ICONERROR,
                                strFileName);
                        strFileName.Empty();
                }
        }
        return !strFileName.IsEmpty();
}

BOOL CSclTextCCDoc::OnOpenDocument(LPCTSTR pszPathName) 
{
	if (CDocument::OnNewDocument())
	{
		return OnInitDocument(NULL);
	}
	return false;
}
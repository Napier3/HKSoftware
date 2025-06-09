// TextEditDoc.cpp : ʵ���ļ�
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
// CSclTextCCDoc ����
BOOL CSclTextCCDoc::OnInitDocument(LPCTSTR pszPathName)
{
        // һ��Ҫ���û����ʵ�֡�
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

	// �����ĵ��Ƿ���ֻ��״̬��Ĭ�ϵ����ǲ������û��޸�ֻ���ļ���
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
        
        // ����ĵ���·�����ͻ�ȡ������·����������ĵ����½��ľ������ı���
        // ����
        CString strPathName = GetPathName();
        if (strPathName.IsEmpty())
        {
                strPathName = GetTitle();
				
                strPathName.TrimRight(STR_MODIFIED_DOCUMENT_TITLE_FLAG);
        }
        
        CString strPrompt;
        strPrompt.Format("%s\n�ĵ��Ѿ����޸ģ����������Ķ���", (LPCTSTR)strPathName);
        
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
        default: // ��ͨ��
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

	// ʾ�������������ȡ��ǰ���ַ����뷽���ͻ��з�����
	// ���ַ����뷽����ָANSI��UNICODE��UTF8�ȡ�
	// ���з�����ָDOS��UNIX��MAC�ȡ�
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

		// ʾ����������ʾ���Ϊ�Ի���ʱ���û�ѡ���ַ����뷽���ͻ�
		// �з�����
		if (!GetSaveAsFileName(newName,
			bReplace,
			nNewFileConverter,
			nNewLineBreakType))
		{
			return false;
		}
	}

	// ʾ�����������������û��µı��뷽���ͻ��з�����
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

	if (!bResult) // �������ʧ�ܣ���Ҫ�ָ�ԭ����ת�����ͻ��и�ʽ��
	{
		SetFileConverter(nOldFileConverter);
		SetLineBreakType(nOldLineBreakType);
	}

	// �������ʧ�ܣ������ǡ����Ϊ��������Ҫ���ղ��½����ļ�ɾ������
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
// ���û��޸����ĵ���������Ҫ�ڳ���ı��������һ����*��������ʾ�ĵ��Ѿ���
// �޸ġ�
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
                // ����ĵ��޸ı�־��һ���ǡ�*����
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
        // ʾ����������û�д���nFileConverter��nLineBreakType��
        // ��Ӧ���Լ���д�����Ϊ���ļ��Ի�����չ���ܡ�

        CDocTemplate* pTemplate = GetDocTemplate();
        ASSERT(pTemplate != NULL);
        
        strFileName = m_strPathName;

		long nIndex = m_strPathName.ReverseFind('.');
		if (nIndex!=-1)
		{
			CString strExt = m_strPathName.Mid(nIndex);
			strFileName = m_strPathName.Left(nIndex);
			strFileName += "-�ı���ͼ";
			strFileName += strExt;
		}

        if (bReplace && strFileName.IsEmpty())
        {
                strFileName = m_strTitle;
                
                // δ�������ֱ��޸��˵��ĵ����ڱ��������һ����*����
                strFileName.TrimRight(STR_MODIFIED_DOCUMENT_TITLE_FLAG);
                
                // ɾ�����Ŀհ��ַ���
                strFileName.TrimRight();
                
                // ɾ�����ܰ����ķǷ��ַ���
                int iBad = strFileName.FindOneOf(_T("\\/:*?\"<>|"));
                if (iBad != -1)
                {
                        strFileName.ReleaseBuffer(iBad);
                }
                
                // ���ȱʡ�ļ���չ������Ѿ����ĵ��ַ�����ָ����
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
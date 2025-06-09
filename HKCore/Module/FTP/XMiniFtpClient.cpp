/*/////////////////////////////////////////////////////////////////////
FTPclient.cpp (c) GDI 1999
V1.0.0 (10/4/99)
Phil Anderson. philip@gd-ind.com
Download by http://www.codefans.net
Simple FTP client functionality. If you have any problems with it,
please tell me about them (or better still e-mail me the fixed
code). Please feel free to use this code however you wish, although
if you make changes please put your name in the source & comment what
you did.

Nothing awesome going on here at all (all sockets are used in // 同步阻塞模式
synchronous blocking mode), but it does the following
things WinInet doesn't seem to:
* Supports loads of different firewalls (I think, I don't
  have access to all types so they haven't all been fully
  tested yet)
* Allows you to execute any command on the FTP server
* Adds 10K to your app install rather than 1Mb #;-)

Functions return TRUE if everything went OK, FALSE if there was an,
error. A message describing the outcome (normally the one returned
from the server) will be in m_retmsg on return from the function.
There are a few error msgs in the app's string table that you'll
need to paste into your app, along with this file & FTPclient.h

If you created your app without checking the "Use Windows Sockets"
checkbox in AppWizard, you'll need to add the following bit of code
to you app's InitInstance()

if(!AfxSocketInit())
{
	AfxMessageBox(_T("Could not initialize Windows Sockets!"));
	return FALSE;
}

To use:

1/ Create an object of CFTPclient.

2/ Use LogOnToServer() to connect to the server. Any arguments
not used (e.g. if you're not using a firewall), pass an empty
string or zero for numeric args. You must pass a server port
number, use the FTP default of 21 if you don't know what it is.

3/ Use MoveFile() to upload/download a file, 1st arg is local file
path, 2nd arg is remote file path, 3rd arg is TRUE for a PASV
connection (required by some firewalls), FALSE otherwise, 4th arg
is TRUE to upload, FALSE to download file. MoveFile only works in
synchronous mode (ie the function will not return 'till the transfer
is finished). File transfers are always of type BINARY.

4/ You can use FTPcommand() to execute FTP commands (eg
FTPcommand(_T("CWD /home/mydir")) to change directory on the server),
note that this function will return FALSE unless the server response
is a 200 series code. This should work fine for most FTP commands, 
otherwise you can use WriteStr() and ReadStr() to send commands & 
interpret the response yourself. Use LogOffServer() to disconnect
when done.

/////////////////////////////////////////////////////////////////////*/


#include "stdafx.h"
#include "XMiniFtpClient.h"
#include "..\..\Module\System\TickCount32.h"
#include "..\..\Module\API\FileApi.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BOOL g_bXMiniFtpLogInfor = FALSE;

CString CXMiniFtpFileItem::g_strServerRootDir = _T("/");

CXMiniFtpFileItem::CXMiniFtpFileItem()
{
	m_strName = _T("/");
	m_bDirectory = TRUE;
}

CXMiniFtpFileItem::~CXMiniFtpFileItem()
{
}

CString CXMiniFtpFileItem::GetDirectory()
{
	if (m_pParent == NULL)
	{
		return g_strServerRootDir;//_T("/");
	}
	else
	{
		if (IsDirectory())
		{
			return ((CXMiniFtpFileItem*)m_pParent)->GetDirectory() + m_strName + _T("/");
		}
		else
		{ 
			return ((CXMiniFtpFileItem*)m_pParent)->GetDirectory() + m_strName;
		}
	}
}

void CXMiniFtpFileItem::Compare(CXMiniFtpFileItem *pCurrItem, CExBaseList &oListNewFileItem, const CString &strFileType)
{
	POS pos = pCurrItem->GetHeadPosition();
	CXMiniFtpFileItem *pSrc = NULL;
	CXMiniFtpFileItem *pFind = NULL;

	while (pos != NULL)
	{
		pSrc = (CXMiniFtpFileItem*)pCurrItem->GetNext(pos);
		pFind = (CXMiniFtpFileItem*)FindByName(pSrc->m_strName); // FindByName从哪个数据结构里去查找

		//如果当前的对象与之前的对比，不一样，则找到不一致的对象
		if (pFind == NULL)
		{
			pSrc->GetAllFile(oListNewFileItem, strFileType);
		}
		else
		{
			//如果是路径，则继续找
			if (pSrc->IsDirectory())
			{
				pSrc->Compare(pFind, oListNewFileItem, strFileType);
			}
		}
	}
}

void CXMiniFtpFileItem::GetAllFile(CExBaseList &oListNewFileItem, const CString &strFileType)
{
	if (!IsDirectory())
	{
		if (IsFileType(strFileType))
		{
			oListNewFileItem.AddTail(this);
		}

		return;
	}

	POS pos = GetHeadPosition();
	CXMiniFtpFileItem *p = NULL;

	while (pos != NULL)
	{
		p = (CXMiniFtpFileItem *)GetNext(pos);

		if (p->IsDirectory())
		{
			p->GetAllFile(oListNewFileItem, strFileType);

		}
		else
		{
			if (p->IsFileType(strFileType))
			{
				oListNewFileItem.AddTail(p);
			}
		}
	}
}

BOOL CXMiniFtpFileItem::IsFileType(const CString &strFileType)
{
	if (strFileType.GetLength() == 0)
	{
		return TRUE;
	}

	CString strTemp = m_strName;
	strTemp.MakeUpper();
	
	return (strTemp.Right(strFileType.GetLength()) == strFileType);
}

BOOL CXMiniFtpFileItem::ParseLine(const CString &strLine)
{
	if(strLine.IsEmpty())
		return FALSE;

	if(strLine.GetLength() < 40)
		return FALSE;

	long nPos = strLine.ReverseFind(' ');

	m_fileName = strLine.Mid(nPos+1); // m_strName就是ftp服务器中文件的名称
	m_strName = strLine.Mid(nPos+1); 

	if (m_strName.Find(_T(".")) > 0)
	{
		m_bDirectory = FALSE;
	}
	else
	{
		m_bDirectory = TRUE;
	}

	return TRUE;

	char ch = strLine.GetAt(0);

	if(ch == 'd' || ch == 'D')
	{
		m_bDirectory = TRUE;
	}
	else
	{
		if(ch == '-')
		{
			m_bDirectory = FALSE;
		}
		else
		{
			if(strLine.Find(_T("<DIR>")) != -1 || strLine.Find(_T("<dir>")) != -1)
				m_bDirectory = TRUE;
			else
				m_bDirectory = FALSE;

			if(strLine.GetLength() < 40)
				return FALSE;

			m_strName = strLine.Mid(39);
			m_strDate = strLine.Left(18);
			m_strName.TrimLeft();
			m_strName.TrimRight();

			return TRUE;
		}

		m_bSec = 0;

		for(int i = 0; i < 9; i++)
		{
			ch = strLine.GetAt(i);
			if(ch == '-')
				m_bSec |= 0x01;
			m_bSec <<= 1;
		}

		m_strSec = strLine.Mid(1, 9);
		int ndx = strLine.Find(':');

		if(ndx == -1)
		{
			if(strLine.GetLength() > 56)
				ndx = 51;
			else
				return FALSE;
		}

		m_index = ndx;
		m_strName = strLine.Mid(ndx + 3);
		m_strName.TrimLeft();
		m_strName.TrimRight();
		m_strDate = strLine.Mid(ndx - 9, 12);

		return TRUE;
	}

	return TRUE;
}

// 
// BOOL CXMiniFtpFileItem::ParseLine(const CString &strLine)
// {
// 	if(strLine.IsEmpty())
// 		return FALSE;
// 
// 	char ch = strLine.GetAt(0);
// 
// 	if(ch == 'd' || ch == 'D')
// 	{
// 		m_bDirectory = TRUE;
// 	}
// 	else
// 	{
// 		if(ch == '-')
// 		{
// 			m_bDirectory = FALSE;
// 		}
// 		else
// 		{
// 			if(strLine.Find(_T("<DIR>")) != -1 || strLine.Find(_T("<dir>")) != -1)
// 				m_bDirectory = TRUE;
// 			else
// 				m_bDirectory = FALSE;
// 
// 			if(strLine.GetLength() < 40)
// 				return FALSE;
// 
// 			m_strName = strLine.Mid(39);
// 			m_strDate = strLine.Left(18);
// 			m_strName.TrimLeft();
// 			m_strName.TrimRight();
// 
// 			return TRUE;
// 		}
// 
// 		m_bSec = 0;
// 
// 		for(int i = 0; i < 9; i++)
// 		{
// 			ch = strLine.GetAt(i);
// 			if(ch == '-')
// 				m_bSec |= 0x01;
// 			m_bSec <<= 1;
// 		}
// 
// 		m_strSec = strLine.Mid(1, 9);
// 		int ndx = strLine.Find(':');
// 
// 		if(ndx == -1)
// 		{
// 			if(strLine.GetLength() > 56)
// 				ndx = 51;
// 			else
// 				return FALSE;
// 		}
// 
// 		m_index = ndx;
// 		m_strName = strLine.Mid(ndx + 3);
// 		m_strName.TrimLeft();
// 		m_strName.TrimRight();
// 		m_strDate = strLine.Mid(ndx - 9, 12);
// 
// 		return TRUE;
// 	}
// 
// 	return TRUE;
// }
// 


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//构造函数，变量初始化
CXMiniFtpClient::CXMiniFtpClient()
{
	m_pCtrlsokfile=NULL;
	m_pCtrlTxarch=NULL;
	m_pCtrlRxarch=NULL;
	m_Ctrlsok=NULL;
	m_isLogOn = FALSE;
}


CXMiniFtpClient::~CXMiniFtpClient()
{
	CloseControlChannel();
	m_isLogOn = FALSE;
}

//////////////////////////////////////////////////////////////////////
// Public Functions
//////////////////////////////////////////////////////////////////////


// 登录到服务器
BOOL CXMiniFtpClient::LogOnToServer(CString hostname,int hostport,const CString &username
									, const CString &password, const CString &acct
									, const CString &fwhost,const CString &fwusername,const  CString &fwpassword,int fwport,int logontype)
{
	int port,logonpoint=0;
	const int LO=-2, ER=-1;
	CString buf,temp;
	const int NUMLOGIN=9; // 支持9种不同的登录方式

	int logonseq[NUMLOGIN][100] = 
	{
		// 下面的数组保存了针对不同防火墙的登录序列
		{0,LO,3, 1,LO,6, 2,LO,ER}, // 没有防火墙
		{3,6,3, 4,6,ER, 5,ER,9, 0,LO,12, 1,LO,15, 2,LO,ER}, // 主机名
		{3,6,3, 4,6,ER, 6,LO,9, 1,LO,12, 2,LO,ER}, // USER after logon
		{7,3,3, 0,LO,6, 1,LO,9, 2,LO,ER}, //proxy OPEN
		{3,6,3, 4,6,ER, 0,LO,9, 1,LO,12, 2,LO,ER}, // Transparent
		{6,LO,3, 1,LO,6, 2,LO,ER}, // USER with no logon
		{8,6,3, 4,6,ER, 0,LO,9, 1,LO,12, 2,LO,ER}, //USER fireID@remotehost
		{9,ER,3, 1,LO,6, 2,LO,ER}, //USER remoteID@remotehost fireID
		{10,LO,3, 11,LO,6, 2,LO,ER} // USER remoteID@fireID@remotehost
	};

	if(logontype<0||logontype>=NUMLOGIN) return FALSE; // illegal connect code

	if(!logontype) 
	{
		temp=hostname;
		port=hostport;
	}
	else 
	{
		temp=fwhost;
		port=fwport;
	}

	 // 如果端口不是默认端口21，则设定端口
	if(hostport!=21) hostname.Format(hostname+_T(":%d"),hostport);
	
	if(!OpenControlChannel(temp,port))
		return false;

	// 获得连接服务器初始化信息
	if(!FTPcommand(_T(""))) 
		return FALSE; 

	// 获得登录类型
	while(1) 
	{
		switch(logonseq[logontype][logonpoint]) 
		{
		case 0:
			temp=_T("USER ")+username;
			break;
		case 1:
			temp=_T("PASS ")+password;
			break;
		case 2:
			temp=_T("ACCT ")+acct;
			break;
		case 3:
			temp=_T("USER ")+fwusername;
			break;
		case 4:
			temp=_T("PASS ")+fwpassword;
			break;
		case 5:
			temp=_T("SITE ")+hostname;
			break;
		case 6:
			temp=_T("USER ")+username+_T("@")+hostname;
			break;
		case 7:
			temp=_T("OPEN ")+hostname;
			break;
		case 8:
			temp=_T("USER ")+fwusername+_T("@")+hostname;
			break;
		case 9:
			temp=_T("USER ")+username+_T("@")+hostname+" "+fwusername;
			break;
		case 10:
			temp=_T("USER ")+username+_T("@")+fwusername+_T("@")+hostname;
			break;
		case 11:
			temp=_T("PASS ")+password+_T("@")+fwpassword;
			break;
		}

		// 发出命令，获得响应
		if(!WriteStr(temp)) 
		{
			return FALSE;
		}

		if(!ReadStr()) 
		{
			return FALSE;
		}

		// 只有这些响应是合法的
		if(m_fc!=2&&m_fc!=3)
		{
			return FALSE;
		}

		logonpoint=logonseq[logontype][logonpoint+m_fc-1]; //get next command from array

		switch(logonpoint)
		{
		case ER: // 出现错误
			m_retmsg = IDS_FTPMSG1;
			return FALSE;
		case LO: // L0表示成功登录
			m_isLogOn = TRUE;
			return TRUE;
		}
	} // end of while(1)
}


// 退出服务器
void CXMiniFtpClient::LogOffServer() 
{
	WriteStr(_T("QUIT"));
	Sleep(100);		//quit【异步操作】之后延时一段时间才close,防止Socket 10053错误
	CloseControlChannel();
	m_oXMiniFtpRoot.RemoveAll();
	m_isLogOn = FALSE;
}


// 发送命令到服务器
BOOL CXMiniFtpClient::FTPcommand(const CString &command) 
{
	if(command!=_T("") && !WriteStr(command))
		return FALSE;

	if((!ReadStr())||(m_fc!=2)) 
		return FALSE;

	return TRUE;
}


// 上载或者下载文件
BOOL CXMiniFtpClient::MoveFile(const CString &remotefile, const CString &localfile,BOOL pasv,BOOL get) 
{
	CString lhost,temp,rhost;
	UINT localsock,serversock,i,j;
	CFile datafile;
	CSocket sockSrvr;
	CAsyncSocket datachannel;
	int num,numread,numsent;
	const int BUFSIZE=4096;
	char cbuf[BUFSIZE];
	DWORD lpArgument=0;
	
	// 打开本地文件
	if(!datafile.Open(localfile,(get?CFile::modeWrite|CFile::modeCreate:CFile::modeRead))) {
		m_retmsg = IDS_FTPMSG4;
		return FALSE;
	}
	if(!FTPcommand(_T("TYPE I"))) return FALSE; // 请求二进制传输
	if(pasv) { // 建立被动传输方式
		if(!FTPcommand(_T("PASV"))) return FALSE;
		// 分析出服务器传回的临时IP地址以及端口号
		if((i=m_retmsg.Find(_T("(")))==-1||(j=m_retmsg.Find(_T(")")))==-1)
			return FALSE;

		temp=m_retmsg.Mid(i+1,(j-i)-1);
		i=temp.ReverseFind(',');

#ifdef _UNICODE
		serversock=_wtol(temp.Right(temp.GetLength()-(i+1))); //get ls byte of server socket
#else
		serversock=atol(temp.Right(temp.GetLength()-(i+1))); //get ls byte of server socket
#endif
		temp=temp.Left(i);

		i=temp.ReverseFind(',');

#ifdef _UNICODE
		serversock+=256*_wtol(temp.Right(temp.GetLength()-(i+1))); // add ms byte to server socket
#else
		serversock+=256*atol(temp.Right(temp.GetLength()-(i+1))); // add ms byte to server socket
#endif
		rhost=temp.Left(i);

		while(1) { // 将逗号转化成点
			if((i=rhost.Find(_T(",")))==-1) break;
			rhost.SetAt(i,'.');
		}
	}
	else { // 设置主动的传输模式
		m_retmsg = IDS_FTPMSG6;
		//获取本地的ip地址，发送到服务器
		if(!m_Ctrlsok->GetSockName(lhost,localsock)) return FALSE;;
		while(1) { // 将IP地址中的点转化成逗号
			if((i=lhost.Find(_T(".")))==-1) break;
			lhost.SetAt(i,',');
		}
		// 创建本地侦听进程
		if((!sockSrvr.Create(0,SOCK_STREAM,NULL))||(!sockSrvr.Listen())) return FALSE;
		if(!sockSrvr.GetSockName(temp,localsock)) return FALSE;// get the port that MFC chose
		// 将端口转化成2字节，然后加入到本地IP地址中
		lhost.Format(lhost+",%d,%d",localsock/256,localsock%256);
		if(!FTPcommand(_T("PORT ")+lhost)) return FALSE;// 发送端口到服务器
	}
	// 发送 RETR/STOR 命令到服务器
	if(!WriteStr((get ? _T("RETR "):_T("STOR "))+remotefile)) return FALSE;
	if(pasv) {// 如果是PASV模式，则创建socket并初始化外部数据连接，即数据传输通道
		if(!datachannel.Create()) {
			m_retmsg = IDS_FTPMSG6;
			return FALSE;
		}
		datachannel.Connect(rhost,serversock); // 试图异步连接服务器
	}
	if(!ReadStr()||m_fc!=1) return FALSE; // 获得服务器响应
	if(!pasv&&!sockSrvr.Accept(datachannel)) return FALSE; // 接收从服务器来的内部绑定数据
	// 连接成功，然后进行阻塞式数据传输
	if((!datachannel.AsyncSelect(0))||(!datachannel.IOCtl(FIONBIO,&lpArgument))) {
		m_retmsg = IDS_FTPMSG6;
		return FALSE;
	}
	while(1) 
	{ // 开始传输数据
		TRY 
		{
			if(get) 
			{
				num=datachannel.Receive(cbuf,BUFSIZE,0);
				if((num == 0)|| (num==SOCKET_ERROR)) 
					break; // (EOF||network error)
				else
					datafile.Write(cbuf,num);
			}
			else
			{
				numread=datafile.Read(cbuf,BUFSIZE);

				if(!(numread))
					break; //EOF

				numsent=datachannel.Send(cbuf,numread,0);

				if((numsent)==SOCKET_ERROR)
					break;

				// 如果发送出去的字节少于从文件读取的字节，则调整发送指针，以使得数据发送正确
				if(numread!=numsent)
					datafile.Seek(numsent-numread,CFile::current);
			}
		}
		CATCH (CException,e)
		{
			m_retmsg = IDS_FTPMSG5;
			return FALSE;
		}

		END_CATCH
	}

	datachannel.Close();
	datafile.Close();
	if(!FTPcommand(_T(""))) return FALSE; // 检查从服务器发送的传输结果信息
	return TRUE; // 传输成功
}


// 通过控制通道向服务器发送命令
BOOL CXMiniFtpClient::WriteStr(const CString &outputstring) 
{
	m_retmsg = IDS_FTPMSG6; // pre-load "network error" msg (in case there is one) #-)

	if (g_bXMiniFtpLogInfor)
	{
 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">>%s"), outputstring);
	}

	TRY 
	{
		m_pCtrlTxarch->WriteString(outputstring+_T("\r\n"));
		m_pCtrlTxarch->Flush();
	}
	CATCH(CException,e) 
	{
		return FALSE;
	}
	END_CATCH

	return TRUE;
}


// 获得服务器的响应
BOOL CXMiniFtpClient::ReadStr() 
{
	int retcode;

	if(!ReadStr2()) return FALSE;

	if(m_retmsg.GetLength()<4||m_retmsg.GetAt(3)!='-') return TRUE;

#ifdef _UNICODE
	retcode=_wtol(m_retmsg);
#else
	retcode=atol(m_retmsg);
#endif

	while(1) 
	{ //处理多行服务器响应
#ifdef _UNICODE
		if((m_retmsg.GetLength()>3)
			&& ( (m_retmsg.GetAt(3)==' ')&&(_wtol(m_retmsg)==retcode))) 
#else
		if((m_retmsg.GetLength()>3)
			&& ( (m_retmsg.GetAt(3)==' ')&&(atol(m_retmsg)==retcode))) 
#endif
			return TRUE;

		if(!ReadStr2()) 
			return FALSE;
	}
}



//////////////////////////////////////////////////////////////////////
// Private functions
//////////////////////////////////////////////////////////////////////


// 从服务器控制通道获取一行响应
BOOL CXMiniFtpClient::ReadStr2() 
{
	TRY
	{
		if(!m_pCtrlRxarch->ReadString(m_retmsg))
		{
			m_retmsg = IDS_FTPMSG6;
			return FALSE;
		}
	}
	CATCH(CException,e) 
	{
		m_retmsg = IDS_FTPMSG6;
		return FALSE;
	}
	END_CATCH

	if(m_retmsg.GetLength()>0)
	{
		if (g_bXMiniFtpLogInfor)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("--%s"), m_retmsg);
		}

		m_fc=m_retmsg.GetAt(0)-48; // get 1st digit of the return code (indicates primary result)
	}
	else
	{
	}

	return TRUE;
}


// 打开控制通道
BOOL CXMiniFtpClient::OpenControlChannel(const CString &serverhost,int serverport)
{
	m_retmsg = IDS_FTPMSG2;

	if (m_Ctrlsok == NULL)
	{
		m_Ctrlsok=new CSocket;

		if (m_Ctrlsok == NULL)	return FALSE;
	}

	if(!(m_Ctrlsok->Create()))
	{
		return FALSE;
	}

	m_retmsg = IDS_FTPMSG3;

	if(!(m_Ctrlsok->Connect(serverhost,serverport)))
	{
		return FALSE;
	}

	m_retmsg = IDS_FTPMSG2;

	if (m_pCtrlsokfile == NULL)
	{
		m_pCtrlsokfile=new CSocketFile(m_Ctrlsok);
	}
	if(m_pCtrlsokfile == NULL) return FALSE;

	if (m_pCtrlRxarch == NULL)
	{
		m_pCtrlRxarch=new CArchive(m_pCtrlsokfile,CArchive::load);
	}
	if(m_pCtrlRxarch == NULL) return FALSE;

	if (m_pCtrlTxarch == NULL)
	{
		m_pCtrlTxarch=new CArchive(m_pCtrlsokfile,CArchive::store);
	}
	if(m_pCtrlTxarch == NULL) return FALSE;

	return TRUE;
}


// 关闭控制通道
void CXMiniFtpClient::CloseControlChannel() 
{
	if(m_pCtrlTxarch) delete m_pCtrlTxarch;
	m_pCtrlTxarch=NULL;
	if(m_pCtrlRxarch) delete m_pCtrlRxarch;
	m_pCtrlRxarch=NULL;
	if(m_pCtrlsokfile) delete m_pCtrlsokfile;
	m_pCtrlsokfile=NULL;
	if(m_Ctrlsok) 
	{
		m_Ctrlsok->Close(); 
		delete m_Ctrlsok;
	}
	m_Ctrlsok=NULL;
	return;
}


//列出文件列表
BOOL CXMiniFtpClient::List()
{
	CString lhost,temp,rhost;
	UINT localsock,i;
	CFile datafile;
	CSocket sockSrvr;
	CAsyncSocket datachannel;
	int num, sum;
	const int BUFSIZE = 4096;
	DWORD lpArgument=0;
	
	m_buf.RemoveAll();
	m_buf.SetSize(BUFSIZE);
	if(!FTPcommand(_T("TYPE I"))) 
		return FALSE; // 请求二进制模式

	m_retmsg = IDS_FTPMSG6;

	// 获取本地IP地址
	if(!m_Ctrlsok->GetSockName(lhost,localsock)) 
		return FALSE;;

	while(1)
	{
		// 将点转化成逗号
		if((i=lhost.Find(_T(".")))==-1) break;
		lhost.SetAt(i,',');
	}

	if((!sockSrvr.Create(0, SOCK_STREAM, NULL)) || (!sockSrvr.Listen()) )
		return FALSE;

	if(!sockSrvr.GetSockName(temp,localsock))
		return FALSE;

	lhost.Format(lhost+",%d,%d", localsock / 256, localsock % 256);

	if(!FTPcommand(_T("PORT ")+lhost)) 
		return FALSE;

	if(!WriteStr(_T("LIST")) )
		return FALSE;

	if(!ReadStr())
		return FALSE; 

	if(!sockSrvr.Accept(datachannel)) 
		return FALSE; 

	if((!datachannel.AsyncSelect(0)) || (!datachannel.IOCtl(FIONBIO,&lpArgument)))
	{
		m_retmsg = IDS_FTPMSG6;
		return FALSE;
	}

	sum = 0;

	while(1) 
	{ // 获得数据
		TRY 
		{
			num = datachannel.Receive(m_buf.GetData() + sum, BUFSIZE, 0); // m_buf在此获得数据

			if((num == 0) || (num == SOCKET_ERROR))
				break;

			TRACE(_T("Received :%d\n"), num);
			Sleep(0);
			sum += num;

			m_buf.SetSize(sum + BUFSIZE);
		}

		CATCH (CException,e) 
		{
			m_retmsg = IDS_FTPMSG5;
			return FALSE;
		}
		END_CATCH
	}

	datachannel.Close();
	return TRUE;
}


void CXMiniFtpClient::ProcessList()
{
}

BOOL CXMiniFtpClient::GetLine(int& ndx)
{
	return GetLine(ndx, m_strLine);
}

void CXMiniFtpClient::Dir()
{
	// Dir(&m_oXMiniFtpRoot);
}

BOOL CXMiniFtpClient::GetLine(int& ndx, CString &strLine)
{
	strLine.Empty();
	int nBytes = m_buf.GetSize(); // m_buf的数据有问题，数据里有大量的重复 
	BOOL bLine = FALSE;
	
	while ( bLine == FALSE && ndx < nBytes )
	{
		char ch = (char)(m_buf.GetAt( ndx ));

		switch( ch )
		{
		case '\n': // 行尾
			bLine = TRUE;
			break;

		default:   // 其他情况
			strLine += ch;
			break;
		}

		++ndx; 
	}

	strLine = strLine.Left(strLine.GetLength() - 1);

	return bLine;
}

void CXMiniFtpClient::Dir(CXMiniFtpFileItem *pItem, const CString &subDir) 
{
	CString cmd = _T("CWD ") + subDir; 
	FTPcommand(cmd);
	FTPcommand(_T("PWD"));
	List(); // 获得m_buf数据
	
	int ndx = 0;
	CString strLine;
	CXMiniFtpFileItem *pNew = NULL;

	while(GetLine(ndx, strLine)) // m_buf -> 分割行得到 strLine
	{
		pNew = new CXMiniFtpFileItem();

		if (pNew->ParseLine(strLine)) // 获得m_fileName(即实际的文件名或者文件夹名)
		{
			pItem->AddNewChild(pNew);
		}
		else
		{
			delete pNew;
		}
	}

	FTPcommand(_T("")); 

	POS pos = pItem->GetHeadPosition();
	while (pos != NULL)
	{
		pNew = (CXMiniFtpFileItem*)pItem->GetNext(pos);

		if (pNew->IsDirectory())
		{
			CString currentPath = subDir + pNew->m_fileName;

			if ( currentPath.Right(1) != "/" )
			{
				currentPath += "/";
			}

			Dir(pNew, currentPath); 
		}
	}
}

void CXMiniFtpClient::GetAllNewFile(CExBaseList &oListFiles, const CString &strFileType)
{
	CXMiniFtpFileItem oRoot;
	oRoot.DeleteAll();
	CString rootPath = oRoot.GetDirectory();
	if ( rootPath.Right(1) != "/" )
	{
		rootPath += "/";
	}

	Dir(&oRoot, rootPath); 

	m_oXMiniFtpRoot.Compare(&oRoot, oListFiles, strFileType);

	if (oListFiles.GetCount() > 0) 
	{
		m_oXMiniFtpRoot.DeleteAll();
		m_oXMiniFtpRoot.AppendEx(oRoot);
		oRoot.RemoveAll();
	}
}

void CXMiniFtpClient::DownFile(CXMiniFtpFileItem *pItem, const CString &strLocalPath)
{
	if (pItem->IsDirectory())
	{
		return;
	}

	//LocalFile
	CString strLocalFile;
	strLocalFile = strLocalPath;

	if (strLocalFile.Right(1) != "\\")
		strLocalFile+="\\";
	
	strLocalFile += pItem->m_strName; 

	//ServerFile
	CString strServerFile = pItem->GetDirectory();

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【%s】>>【%s】"),strServerFile, strLocalFile);
	MoveFile (strServerFile, strLocalFile, FALSE, TRUE);

	AddFile(strLocalFile);
}

void CXMiniFtpClient::DownAllNewFile(const CString &strLocalPath, CExBaseList &oListFiles, const CString &strFileType)
{
	if( m_isLogOn == FALSE )
	{
		// CMainFrame::OnTimer() 会定时获取文件，没有连接到服务器则直接返回，
		// 在没有连接到服务器的情况下去请求文件，会出错。
		return;  
	}

	CTickCount32 oTickCount32;
	oListFiles.RemoveAll();
	GetAllNewFile(oListFiles, strFileType);

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("读取服务器目录耗时【%dms】"), oTickCount32.GetTickCountLong(TRUE));

	if (oListFiles.GetCount() == 0)
	{
		return;
	}

	POS pos = oListFiles.GetHeadPosition();
	CXMiniFtpFileItem *pFile = NULL;

	while (pos != NULL)
	{
		pFile = (CXMiniFtpFileItem *)oListFiles.GetNext(pos);
		DownFile(pFile, strLocalPath);
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("下载最新文件耗时【%d ms】"), oTickCount32.GetTickCountLong(TRUE));
}

void CXMiniFtpClient::Init(const CString &strSvrIP,const CString &strFtpUser,const CString &strFtpPsw,CWnd *pWnd)
{
	m_strSvrIP = strSvrIP;
	m_strFtpUser = strFtpUser;
	m_strFtpPsw = strFtpPsw;
	m_pMainWnd = pWnd;
}

 
BOOL CXMiniFtpClient::InitXMiniFtp(const CString &strSvrIP,const CString &strFtpUser
								   ,const CString &strFtpPsw,CWnd *pWnd)
{
	if (m_isLogOn)
	{
		return TRUE;
	}

	CloseControlChannel();

	Init(strSvrIP,strFtpUser,strFtpPsw,m_pMainWnd);

	BOOL bRet = LogOnToServer(strSvrIP,21,strFtpUser, strFtpPsw,_T(""),_T(""),_T(""),_T(""),1080,0) ;

	if(!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s FTP登录失败"), strSvrIP);
		CloseControlChannel();
		m_isLogOn = FALSE;
		return FALSE;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s FTP登陆成功"), strSvrIP);
	}

	AttachMainWnd(pWnd);
	return TRUE;
}

BOOL CXMiniFtpClient::InitXMiniFtp()
{
	return InitXMiniFtp(m_strSvrIP,m_strFtpUser,m_strFtpPsw,m_pMainWnd);
}

void CXMiniFtpClient::ExitXMiniFtp()
{
	if (!m_isLogOn)
	{
		return;
	}

	LogOffServer();
}

BOOL CXMiniFtpClient::XFtpProcFun(BOOL bShowProgress)
{
	if (bShowProgress && m_pFtpProgress != NULL)
	{
		CStringArray strArray;
		strArray.Add(m_strLocalFile);
		m_pFtpProgress->Init(strArray);
	}

	m_pXFtpThread = AfxBeginThread(XFtpProc,this);

	CTickCount32 oTickCount32;
	long nCnt = 0;
	while(m_pXFtpThread != NULL)
	{
		nCnt++;
		if (nCnt % 5 == 0)
		{
			if (m_pFtpProgress != NULL)
			{
				m_pFtpProgress->TransferStep(1);
			}
		}

		oTickCount32.DoEvents(20);
	}

	if (m_pFtpProgress != NULL)
	{
		if (m_bXFptResult)
		{
			m_pFtpProgress->TransferFinish(m_strLocalFile);
		}
		else
		{
			m_pFtpProgress->TransferError(m_strLocalFile,0);
		}	
	}

	return m_bXFptResult;
}

BOOL CXMiniFtpClient::UploadFile(const CString &strRemoteFile, const CString &strLocalFile,BOOL bShowProgress)
{
	if (m_pXFtpThread != NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("XMiniFtp busy"));
		return FALSE;
	}

	m_bXFptResult = FALSE;
	m_bDownload = FALSE;
	m_strRemoteFile = strRemoteFile;
	m_strLocalFile = strLocalFile;

	return XFtpProcFun(bShowProgress);
}

BOOL CXMiniFtpClient::DownLoadFile(const CString &strRemoteFile, const CString &strLocalFile,BOOL bShowProgress)
{
	if (m_pXFtpThread != NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("XMiniFtp busy"));
		return FALSE;
	}

	m_bXFptResult = FALSE;
	m_bDownload = TRUE;
	m_strRemoteFile = strRemoteFile;
	m_strLocalFile = strLocalFile;

	return XFtpProcFun(bShowProgress);
}

BOOL CXMiniFtpClient::UploadFileFun()
{
	if (!InitXMiniFtp())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("InitXMiniFtp failed"));
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Start:Upload File [%s]"), m_strLocalFile);

	//上传文件
	BOOL bRet = MoveFile(m_strRemoteFile, m_strLocalFile, FALSE, FALSE);
	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Upload File [%s] succeed"), m_strLocalFile);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Upload File [%s] failed"), m_strLocalFile);
	}

	ExitXMiniFtp();
	return bRet;
}

BOOL CXMiniFtpClient::DownLoadFileFun()
{
	if (!InitXMiniFtp())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("InitXMiniFtp failed"));
		return FALSE;
	}

	CString strLocalFilePath = GetPathFromFilePathName(m_strLocalFile);
	CreateAllDirectories(strLocalFilePath);

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Start:Download File [%s]"), m_strLocalFile);
	//下载文件
	BOOL bRet = MoveFile(m_strRemoteFile, m_strLocalFile, FALSE, TRUE);
	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Download File [%s] succeed"), m_strLocalFile);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Download File [%s] failed"), m_strLocalFile);
		DeleteFile(m_strLocalFile);
	}

	ExitXMiniFtp();
	return bRet;
}

int CXMiniFtpClient::DownloadSvrFile(HWND hWnd, const CString& strRemoteFile)
{
	if (strRemoteFile.IsEmpty())
	{
		return -1;
	}

	CString strLocalPath,strFileName;
	strFileName = GetPathFileNameFromFilePathName(strRemoteFile);

	if(strFileName.IsEmpty())
	{
		MessageBox(hWnd,_T("服务端文件路径错误;"),_T("提示"),MB_OK);
		return -1;
	}

	if(FGetDirectory(hWnd, strLocalPath, _T("请选择文件存放路径")))
	{
		strLocalPath.AppendFormat(_T("\\%s"),strFileName);

		return DownLoadFile(strRemoteFile,strLocalPath);
	}

	return -1;
}

UINT CXMiniFtpClient::XFtpProc(LPVOID lParam)
{
	CXMiniFtpClient *pClient = (CXMiniFtpClient *)lParam;

	if (!AfxSocketInit())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("AfxSocketInit fail"));
		return 0;
	}

	if (pClient->m_bDownload)
	{
		pClient->m_bXFptResult = pClient->DownLoadFileFun();
	}
	else
	{
		pClient->m_bXFptResult = pClient->UploadFileFun();
	}

	pClient->m_pXFtpThread = NULL;
	return pClient->m_bXFptResult;
}

void CXMiniFtpClient::XFtpInit(CStringArray &strArray)
{
	if(m_pFtpProgress != NULL)
	{
		m_pFtpProgress->Init(strArray);
	}
}

void CXMiniFtpClient::TransferFinish(const CString &strFile)
{
	if(m_pFtpProgress != NULL)
	{
		m_pFtpProgress->TransferFinish(strFile);
	}
}
void CXMiniFtpClient::TransferError(const CString &strFile,long nErrNo)
{
	if(m_pFtpProgress != NULL)
	{
		m_pFtpProgress->TransferError(strFile,nErrNo);
	}
}

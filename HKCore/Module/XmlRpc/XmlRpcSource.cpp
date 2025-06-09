#include "stdafx.h"

#include "XmlRpcSource.h"
#include "XmlRpcSocket.h"
#include "XmlRpcUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace XmlRpc {


  XmlRpcSource::XmlRpcSource(int fd /*= -1*/, bool deleteOnClose /*= false*/) 
    : _fd(fd), _deleteOnClose(deleteOnClose), _keepOpen(false)
  {
	  m_pMsgWnd = NULL;
  }

  XmlRpcSource::~XmlRpcSource()
  {
  }


  void
  XmlRpcSource::close()
  {
    if (_fd != -1) {
#ifdef _DEBUG
		XmlRpcUtil::log(2,"XmlRpcSource::close: closing socket %d.", _fd);
#endif
      XmlRpcSocket::close(_fd);
#ifdef _DEBUG
	  XmlRpcUtil::log(2,"XmlRpcSource::close: done closing socket %d.", _fd);
#endif
      _fd = -1;
    }
    if (_deleteOnClose) {
#ifdef _DEBUG
		XmlRpcUtil::log(2,"XmlRpcSource::close: deleting this");
#endif
      _deleteOnClose = false;
      delete this;
    }
  }
  
  void XmlRpcSource::closeSocket()	
  {	
	  if (_fd != -1)
	  {
		  XmlRpcSocket::close(_fd);
		  _fd = -1;
	  }	
  }
} 

// namespace XmlRpc

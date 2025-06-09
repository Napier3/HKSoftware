#include "stdafx.h"

#include "XmlRpcServerConnection.h"

#include "XmlRpcSocket.h"
#include "XmlRpc.h"

#include "..\CriticalSection\SynCriticalSection.h"

#ifndef MAKEDEPEND
# include <stdio.h>
# include <stdlib.h>
#endif

#include<string.h>

using namespace XmlRpc;

// Static data
const char XmlRpcServerConnection::METHODNAME_TAG[] = "<methodName>";
const char XmlRpcServerConnection::PARAMS_TAG[] = "<params>";
const char XmlRpcServerConnection::PARAMS_ETAG[] = "</params>";
const char XmlRpcServerConnection::PARAM_TAG[] = "<param>";
const char XmlRpcServerConnection::PARAM_ETAG[] = "</param>";

const std::string XmlRpcServerConnection::SYSTEM_MULTICALL = "system.multicall";
const std::string XmlRpcServerConnection::METHODNAME = "methodName";
const std::string XmlRpcServerConnection::PARAMS = "params";

const std::string XmlRpcServerConnection::FAULTCODE = "faultCode";
const std::string XmlRpcServerConnection::FAULTSTRING = "faultString";

// char* getstr(char *p,int index,int len)
// {
// 	char*  str = p+index;
// 	char des[32]={};
// 	strncpy(des,str,len);
// 	des[len]='\0';
// 	return des;
// 	
// }

// The server delegates handling client requests to a serverConnection object.
XmlRpcServerConnection::XmlRpcServerConnection(int fd, XmlRpcServer* server, bool deleteOnClose /*= false*/) :
  XmlRpcSource(fd, deleteOnClose)
{
#ifdef _DEBUG
	XmlRpcUtil::log(2,"XmlRpcServerConnection: new socket %d.", fd);
#endif
  _server = server;
  _connectionState = READ_HEADER;
  _keepAlive = true;
}


XmlRpcServerConnection::~XmlRpcServerConnection()
{
#ifdef _DEBUG
	XmlRpcUtil::log(4,"XmlRpcServerConnection dtor.");
#endif
  _server->removeConnection(this);
}


// Handle input on the server socket by accepting the connection
// and reading the rpc request. Return true to continue to monitor
// the socket for events, false to remove it from the dispatcher.
unsigned
XmlRpcServerConnection::handleEvent(unsigned /*eventType*/)
{
  if (_connectionState == READ_HEADER)
    if ( ! readHeader()) return 0;

  if (_connectionState == READ_REQUEST)
    if ( ! readRequest()) return 0;

  if (_connectionState == WRITE_RESPONSE)
    if ( ! writeResponse()) return 0;

  return (_connectionState == WRITE_RESPONSE) 
        ? XmlRpcDispatch::WritableEvent : XmlRpcDispatch::ReadableEvent;
}


bool
XmlRpcServerConnection::readHeader()
{
  // Read available data
  bool eof;
  if ( ! XmlRpcSocket::nbRead(this->getfd(), _header, &eof)) {
    // Its only an error if we already have read some data
    if (_header.length() > 0)
	{
#ifdef _DEBUG
      XmlRpcUtil::error("XmlRpcServerConnection::readHeader: error while reading header (%s).",XmlRpcSocket::getErrorMsg().c_str());
#endif
	}

    return false;
  }

#ifdef _DEBUG
  XmlRpcUtil::log(4, "XmlRpcServerConnection::readHeader: read %d bytes.", _header.length());
#endif

  //string str = "Hello";  
  int len = _header.size();
  //char p[4096];   
  //_header.copy(p,len,0); //这里5，代表复制几个字符，0代表复制的位置  
  //*(p+len)='\0';     //要手动加上结束符 


  char *hp = (char*)_header.c_str();  // Start of header
  char *ep = hp + _header.length();   // End of string
  char *bp = 0;                       // Start of body
  char *lp = 0;                       // Start of content-length value
  char *kp = 0;                       // Start of connection value

  int ilp =0;
  int ikp=0;
  int ibp=0;

  for (int i=0;(ibp == 0) && (i<len);i++)
  {
	  if (((len-i)>16) && (_header.substr(i,16).compare(0,16, "Content-length: ") == 0) )
	   {
			ilp= i+16;
	   }
	   else if (((len-i) > 12) && (_header.substr(i,12).compare(0,12, "Connection: ") == 0))
		ikp = i + 12;
	   else if (((len-i)>4) && (_header.substr(i,4).compare(0,4, "\r\n\r\n") == 0))
		ibp = i + 4;
	   else if (((len-i)>2) && (_header.substr(i,2).compare(0,2, "\n\n") == 0))
		ibp = i + 2;
   
  }

  // If we haven't gotten the entire header yet, return (keep reading)
  if (ibp == 0) {
	  // EOF in the middle of a request is an error, otherwise its ok
	  if (eof) {
#ifdef _DEBUG
		  XmlRpcUtil::log(4, "XmlRpcServerConnection::readHeader: EOF");
#endif
		  if (_header.length() > 0)
		  {
#ifdef _DEBUG
			  XmlRpcUtil::error("XmlRpcServerConnection::readHeader: EOF while reading header");
#endif
		  }

		  return false;   // Either way we close the connection
	  }

	  return true;  // Keep reading
  }

 // for (char *cp = hp; (bp == 0) && (cp < ep); ++cp) {
	//if ((ep - cp > 16) && (strncasecmp(cp, "Content-length: ", 16) == 0))
	//  lp = cp + 16;
	//else if ((ep - cp > 12) && (strncasecmp(cp, "Connection: ", 12) == 0))
	//  kp = cp + 12;
	//else if ((ep - cp > 4) && (strncmp(cp, "\r\n\r\n", 4) == 0))
	//  bp = cp + 4;
	//else if ((ep - cp > 2) && (strncmp(cp, "\n\n", 2) == 0))
	//  bp = cp + 2;
 // }

  //// If we haven't gotten the entire header yet, return (keep reading)
  //if (bp == 0) {
  //  // EOF in the middle of a request is an error, otherwise its ok
  //  if (eof) {
  //    XmlRpcUtil::log(4, "XmlRpcServerConnection::readHeader: EOF");
  //    if (_header.length() > 0)
  //      XmlRpcUtil::error("XmlRpcServerConnection::readHeader: EOF while reading header");
  //    return false;   // Either way we close the connection
  //  }
  //  
  //  return true;  // Keep reading
  //}

  // Decode content length
  if (ilp == 0) {
	  XmlRpcUtil::error("XmlRpcServerConnection::readHeader: No Content-length specified");
	  return false;   // We could try to figure it out by parsing as we read, but for now...
  }

  //if (lp == 0) {
  //  XmlRpcUtil::error("XmlRpcServerConnection::readHeader: No Content-length specified");
  //  return false;   // We could try to figure it out by parsing as we read, but for now...
  //}


  _contentLength = atoi(_header.substr(ilp,12).c_str());
  if (_contentLength <= 0) {
#ifdef _DEBUG
	  XmlRpcUtil::error("XmlRpcServerConnection::readHeader: Invalid Content-length specified (%d).", _contentLength);
#endif
	  return false;
  }
  //_contentLength = atoi(lp);
  //if (_contentLength <= 0) {
  //  XmlRpcUtil::error("XmlRpcServerConnection::readHeader: Invalid Content-length specified (%d).", _contentLength);
  //  return false;
  //}
  	
#ifdef _DEBUG
  XmlRpcUtil::log(3, "XmlRpcServerConnection::readHeader: specified content length is %d.", _contentLength);
#endif

  // Otherwise copy non-header data to request buffer and set state to read request.
	//_request = bp;
    _request = _header.substr(ibp,len-ibp);

  // Parse out any interesting bits from the header (HTTP version, connection)
  _keepAlive = true;
  if (_header.find("HTTP/1.0") != std::string::npos) {
    if (kp == 0 || strncasecmp(kp, "keep-alive", 10) != 0)
      _keepAlive = false;           // Default for HTTP 1.0 is to close the connection
  } else {
    if (kp != 0 && strncasecmp(kp, "close", 5) == 0)
      _keepAlive = false;
  }
#ifdef _DEBUG
  XmlRpcUtil::log(3, "KeepAlive: %d", _keepAlive);
#endif


  _header = ""; 
  _connectionState = READ_REQUEST;
  return true;    // Continue monitoring this source
}

bool
XmlRpcServerConnection::readRequest()
{
  // If we dont have the entire request yet, read available data
  if (int(_request.length()) < _contentLength) {
    bool eof;
    if ( ! XmlRpcSocket::nbRead(this->getfd(), _request, &eof)) {
#ifdef _DEBUG
		XmlRpcUtil::error("XmlRpcServerConnection::readRequest: read error (%s).",XmlRpcSocket::getErrorMsg().c_str());
#endif
      return false;
    }

    // If we haven't gotten the entire request yet, return (keep reading)
    if (int(_request.length()) < _contentLength) {
      if (eof) {
#ifdef _DEBUG
        XmlRpcUtil::error("XmlRpcServerConnection::readRequest: EOF while reading request");
#endif
        return false;   // Either way we close the connection
      }
      return true;
    }
  }

  // Otherwise, parse and dispatch the request
#ifdef _DEBUG
  XmlRpcUtil::log(3, "XmlRpcServerConnection::readRequest read %d bytes.", _request.length());
#endif
  //XmlRpcUtil::log(5, "XmlRpcServerConnection::readRequest:\n%s\n", _request.c_str());

  _connectionState = WRITE_RESPONSE;

  return true;    // Continue monitoring this source
}


bool
XmlRpcServerConnection::writeResponse()
{
  if (_response.length() == 0) {
    executeRequest();
    _bytesWritten = 0;
    if (_response.length() == 0) {
#ifdef _DEBUG
      XmlRpcUtil::error("XmlRpcServerConnection::writeResponse: empty response.");
#endif
      return false;
    }
  }

  // Try to write the response
  if ( ! XmlRpcSocket::nbWrite(this->getfd(), _response, &_bytesWritten))
  {
#ifdef _DEBUG
    XmlRpcUtil::error("XmlRpcServerConnection::writeResponse: bwrite error (%s).",XmlRpcSocket::getErrorMsg().c_str());
#endif
    return false;
  }
#ifdef _DEBUG
  XmlRpcUtil::log(3, "XmlRpcServerConnection::writeResponse: wrote %d of %d bytes.", _bytesWritten, _response.length());
#endif

  // Prepare to read the next request
  if (_bytesWritten == int(_response.length())) {
    _header = "";
    _request = "";
    _response = "";
    _connectionState = READ_HEADER;
  }

  return _keepAlive;    // Continue monitoring this source if true
}

// Run the method, generate _response string
void
XmlRpcServerConnection::executeRequest()
{
  XmlRpcValue params, resultValue;
  std::string methodName = parseRequest(params);
#ifdef _DEBUG
  XmlRpcUtil::log(2, "XmlRpcServerConnection::executeRequest: server calling method '%s'", 
	  methodName.c_str());
#endif

  try {

    if ( ! executeMethod(methodName, params, resultValue) &&
         ! executeMulticall(methodName, params, resultValue))
      generateFaultResponse(methodName + ": unknown method name");
    else
      generateResponse(resultValue.toXml());

  } catch (const XmlRpcException& fault) {
#ifdef _DEBUG
	  XmlRpcUtil::log(2, "XmlRpcServerConnection::executeRequest: fault %s.",
		  fault.getMessage().c_str()); 
#endif
    generateFaultResponse(fault.getMessage(), fault.getCode());
  }
}

// Parse the method name and the argument values from the request.
std::string
XmlRpcServerConnection::parseRequest(XmlRpcValue& params)
{
  int offset = 0;   // Number of chars parsed from the request

  std::string methodName = XmlRpcUtil::parseTag(METHODNAME_TAG, _request, &offset);

  if (methodName.size() > 0 && XmlRpcUtil::findTag(PARAMS_TAG, _request, &offset))
  {
    int nArgs = 0;
    while (XmlRpcUtil::nextTagIs(PARAM_TAG, _request, &offset)) {
      params[nArgs++] = XmlRpcValue(_request, &offset);
      (void) XmlRpcUtil::nextTagIs(PARAM_ETAG, _request, &offset);
    }

    (void) XmlRpcUtil::nextTagIs(PARAMS_ETAG, _request, &offset);
  }

  return methodName;
}

static CAutoCriticSection g_oXmlRpcCallAutoCriticSection;

// Execute a named method with the specified params.
bool
XmlRpcServerConnection::executeMethod(const std::string& methodName, 
                                      XmlRpcValue& params, XmlRpcValue& result)
{
	CAutoSimpleLock oLock(g_oXmlRpcCallAutoCriticSection);
	XmlRpcServerMethod* method = _server->findMethod(methodName);

	if ( ! method) return false;


	method->execute(params, result,this);//zhangsen 20170402

	// Ensure a valid result value
	if ( ! result.valid())
		result = std::string();

	return true;
}

// Execute multiple calls and return the results in an array.
bool
XmlRpcServerConnection::executeMulticall(const std::string& methodName, 
                                         XmlRpcValue& params, XmlRpcValue& result)
{
  if (methodName != SYSTEM_MULTICALL) return false;

  // There ought to be 1 parameter, an array of structs
  if (params.size() != 1 || params[0].getType() != XmlRpcValue::TypeArray)
    throw XmlRpcException(SYSTEM_MULTICALL + ": Invalid argument (expected an array)");

  int nc = params[0].size();
  result.setSize(nc);

  for (int i=0; i<nc; ++i) {

    if ( ! params[0][i].hasMember(METHODNAME) ||
         ! params[0][i].hasMember(PARAMS)) {
      result[i][FAULTCODE] = -1;
      result[i][FAULTSTRING] = SYSTEM_MULTICALL +
              ": Invalid argument (expected a struct with members methodName and params)";
      continue;
    }

    const std::string& methodName = params[0][i][METHODNAME];
    XmlRpcValue& methodParams = params[0][i][PARAMS];

    XmlRpcValue resultValue;
    resultValue.setSize(1);
    try {
      if ( ! executeMethod(methodName, methodParams, resultValue[0]) &&
           ! executeMulticall(methodName, params, resultValue[0]))
      {
        result[i][FAULTCODE] = -1;
        result[i][FAULTSTRING] = methodName + ": unknown method name";
      }
      else
        result[i] = resultValue;

    } catch (const XmlRpcException& fault) {
        result[i][FAULTCODE] = fault.getCode();
        result[i][FAULTSTRING] = fault.getMessage();
    }
  }

  return true;
}


// Create a response from results xml
void
XmlRpcServerConnection::generateResponse(std::string const& resultXml)
{
  const char RESPONSE_1[] = 
    "<?xml version=\"1.0\"?>\r\n"
    "<methodResponse><params><param>\r\n\t";
  const char RESPONSE_2[] =
    "\r\n</param></params></methodResponse>\r\n";

  std::string body = RESPONSE_1 + resultXml + RESPONSE_2;
  std::string header = generateHeader(body);

  _response = header + body;
#ifdef _DEBUG
  XmlRpcUtil::log(5, "XmlRpcServerConnection::generateResponse:\n%s\n", _response.c_str()); 
#endif
}

// Prepend http headers
std::string
XmlRpcServerConnection::generateHeader(std::string const& body)
{
  std::string header = 
    "HTTP/1.1 200 OK\r\n"
    "Server: ";
  header += XMLRPC_VERSION;
  header += "\r\n"
    "Content-Type: text/xml\r\n"
    "Content-length: ";

  char buffLen[40];
  sprintf(buffLen,"%d\r\n\r\n", body.size());

  return header + buffLen;
}


void XmlRpcServerConnection::generateFaultResponse(std::string const& errorMsg, int errorCode)
{
  const char RESPONSE_1[] = 
    "<?xml version=\"1.0\"?>\r\n"
    "<methodResponse><fault>\r\n\t";
  const char RESPONSE_2[] =
    "\r\n</fault></methodResponse>\r\n";

  XmlRpcValue faultStruct;
  faultStruct[FAULTCODE] = errorCode;
  faultStruct[FAULTSTRING] = errorMsg;
  std::string body = RESPONSE_1 + faultStruct.toXml() + RESPONSE_2;
  std::string header = generateHeader(body);

  _response = header + body;
}

#pragma once

#include <xercesc/dom/DOM.hpp>

#pragma comment(lib, "xerces-c_3.lib")
#include <xercesc/util/xercesversion.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>

namespace XERCES_CPP_NAMESPACE
{
	class XercesDOMParser;
	class DOMDocument;
	class DOMElement;
	class DOMNode;
	class DOMNodeList;
	class DOMWriter;
	class DOMImplementation;
}

typedef XERCES_CPP_NAMESPACE::XercesDOMParser INTERNAL_PARSER;
typedef XERCES_CPP_NAMESPACE::DOMDocument INTERNAL_DOCUMENT;
typedef XERCES_CPP_NAMESPACE::DOMElement INTERNAL_ELEMENT;
typedef XERCES_CPP_NAMESPACE::DOMNode INTERNAL_NODE;
typedef XERCES_CPP_NAMESPACE::DOMNodeList INTERNAL_NODELIST;
typedef XERCES_CPP_NAMESPACE::DOMWriter	INTERNAL_DOMWRITER;
typedef XERCES_CPP_NAMESPACE::DOMImplementation INTERNAL_DOMIMPL;


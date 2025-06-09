#ifndef COMMON_H
#define COMMON_H

#include <exception>
#include <string>
#include <algorithm>
#include <cctype>
#include <locale>
#include <cstring>
#include <memory>
#include <map>
#include <string.h>
#include <set>
#include "pugixml/pugixml.hpp"

using namespace pugi;
using namespace std;


#ifdef _MSC_VER 
//not #if defined(_WIN32) || defined(_WIN64) because we have strncasecmp in mingw
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

#define NPRINTF(...) printf(__VA_ARGS__)

namespace scd {

struct ScdConfig {
    set<string> ignoreIeds;
};

class ParseException : public exception
{
public:
    ParseException(const string &errorMsg)
        : mError(errorMsg)
    {

    }

    ParseException(xml_node node, const string &errorMsg) : mError(errorMsg), offset(node.offset_debug()) {
    }

    virtual const char *what() const noexcept override;
    inline ptrdiff_t getOffset() const { return offset; }

private:
    string mError;
    ptrdiff_t offset;
};

}
#endif // COMMON_H

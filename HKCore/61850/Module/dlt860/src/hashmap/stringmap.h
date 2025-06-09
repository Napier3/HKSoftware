#ifndef STRING_MAP
#define STRING_MAP
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

template<typename T, typename K = std::string>
class StrHashMap : public unordered_map<K, T>
{
public:
    StrHashMap()
    {
    }
};

#endif

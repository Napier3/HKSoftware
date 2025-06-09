#ifndef LOG_H
#define LOG_H

#include "common.h"
namespace scd {

class Log
{
public:
    Log(xml_node node);
    const char *getName() const;

private:
    const char *name;
};

}
#endif // LOG_H

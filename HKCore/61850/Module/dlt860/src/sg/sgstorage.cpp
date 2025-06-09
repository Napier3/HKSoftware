#include "sgstorage.h"
#include "sqlitesgstorage.h"

SgStorage *SgStorage::create(const string &filePath)
{
    static SqliteSgStorage storage(filePath);
    return &storage;
}

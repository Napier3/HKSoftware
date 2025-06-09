#ifndef SG_STORAGE
#define SG_STORAGE

#include <string>
#include <vector>
#include "gsp_mms_value.h"

using namespace std;

struct Sgcb
{
    int id;
    string ldName;
    int actSg;
    int editSg;
    int sgNumber;
    uint64_t laTime;
};

struct SgRawValue
{
    int id;
    string ldName;
    string reference;
    int valueType;
    vector<char> value;
    int sgNumber;
};

struct SgValue
{
    string reference;
    GspMmsValue *value;
};

using SgValueVec = vector<SgValue>;

class SgStorage
{
public:

    static SgStorage *create(const string &filePath);
    virtual void selectActiveSg(const string &ldName, uint8_t actSg, uint64_t laTime) = 0;
    virtual bool insertSgcb(const string &ldName, uint8_t actSg, uint8_t editSg, uint8_t sgNumber, uint64_t laTime) = 0;
    virtual void getAllSgcbValues(vector<Sgcb> &sgcbs) = 0;
    virtual void getSgValues(const string &ldName, uint8_t editSg, SgValueVec &valueVec) = 0;
    virtual void selectEditSg(const string &ldName, uint8_t editSg) = 0;
    virtual void setEditSgValue(const SgValue &value) = 0;

    virtual void getSgValues(const string &ldName, uint8_t editSg, vector<GspMmsValue *> &values) = 0;
    virtual void setEditSgValues(const string &ldName, uint8_t editSg, const SgValueVec &valueVec) = 0;
protected:
    SgStorage(const string &filePath) : _filePath(filePath)
    {

    }

    string _filePath;
};

#endif

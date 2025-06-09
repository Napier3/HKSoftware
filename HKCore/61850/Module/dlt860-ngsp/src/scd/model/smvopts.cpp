#include "smvopts.h"

namespace scd {

SmvOpts::SmvOpts(xml_node node)
{
    mRefreshTime = node.attribute("refreshTime").as_bool();
    mSampleRate = node.attribute("sampleRate").as_bool();
    mDataSet = node.attribute("dataSet").as_bool();
    mSecurity = node.attribute("security").as_bool();
    mSampleSync = node.attribute("sampleSynchronized").as_bool();


}

}

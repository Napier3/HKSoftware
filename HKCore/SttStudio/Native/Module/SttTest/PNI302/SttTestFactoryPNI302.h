#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPNI302 : public CSttTestFactory
{
public:
        static CSttTestFactoryPNI302 *Create();
	static void Release();

private:
        CSttTestFactoryPNI302(void);
        virtual ~CSttTestFactoryPNI302(void);

    static int g_nTestFactoryPNI302Ref;
    static CSttTestFactoryPNI302 *g_pTestFactoryPNI302;

};

#ifndef _OPTIONS_
#define _OPTIONS_

#include "Unknown.h"

class Options : public Unknown
{
public:
    Options();

    virtual void			Show() = 0;
    virtual void			Hide() = 0;

protected:
    ~Options();
};

#endif

#ifndef _UNKNOWN_H_
#define _UNKNOWN_H_

#include <deque>
using namespace std;

/*
	Everything should be an unknown, hopefully.  Except the math classes probably.
*/	
class Unknown
{
public:
    Unknown();

    virtual void        AddRef();
    int                 GetRefCount() const         { return m_RefCount; }
    virtual void        Release();

protected:
    virtual ~Unknown();

    int m_RefCount;

private:

    void Init();

};

#endif

#ifndef _C_DIASCREENCAPTURE
#define _C_DIASCREENCAPTURE

#ifdef _MSC_VER
#pragma once
#endif

#include <CDiaTask.h>


class CDiaScreenCapture : public CDiaTask
{
public:
	CDiaScreenCapture();
	virtual void TaskEnd(){}
	virtual bool IsDone() { return false; }
protected:
	virtual void RunInternal();
private:

};



#endif

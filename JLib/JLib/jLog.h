#pragma once
#include "jAnonymousVariable.h"
#include <string>
#include "boost/lexical_cast.hpp"
#include "boost/timer.hpp"
#include "boost/noncopyable.hpp"
#include <iomanip>

#define  JLOG() jProgressLog ANONYMOUS_VARIABLE(jFileInfo((const char*)__FILE__, (const char*)__FUNCTION__, (const char*)__DATE__, (const char*)__TIME__, __LINE__))

class jFileInfo {
public:    
    jFileInfo(const char* file, const char* func, const char* date, const char* time, int line) 
        :mFile(file), mFunc(func), mDate(date), mTime(time), mLine(line)
    {}
    std::string formatFileInfo() {
        return std::string() + "[Time] : " + mDate + ", " + mTime + ", [Line] : " + boost::lexical_cast<std::string>(mLine) + 
            ", [Function] : " + mFunc + "\n";
    }
private:
    const char *mFile, *mFunc, *mDate, *mTime;
    int mLine;
};

class jProgressLog : boost::noncopyable
{
public:
    jProgressLog(jFileInfo fileInfo, std::ostream &os = std::cout)
        : mfileInfo(fileInfo), osPtr(&os)
    {
        theTimer.restart();
    }
    ~jProgressLog() {
        double timeElapsed = theTimer.elapsed();
        (*osPtr) << std::setprecision(4) << mfileInfo.formatFileInfo()
                 << "Time elapsed in this scope: " << timeElapsed << "s\n";
    }
private:
    boost::timer theTimer;
    jFileInfo mfileInfo;
    std::ostream *osPtr;
};

#ifndef IIOTSCANNER_H_INCLUDED
#define IIOTSCANNER_H_INCLUDED

#include "IIoTMonitor.h"
#include <iostream>

using namespace std;

class IIoTMonitor;

class IIoTScanner{
public:
    void Scan(IIoTMonitor& objMonitor);
};

#endif
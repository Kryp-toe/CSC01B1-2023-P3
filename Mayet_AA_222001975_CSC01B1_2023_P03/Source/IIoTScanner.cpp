#include "IIoTScanner.h"
#include <sstream>
#include <iostream>

using namespace std;

void IIoTScanner::Scan(IIoTMonitor& objMonitor)
{
    IIoTSensor objSensor;
    
    for(int r=0; r<objMonitor.getRows(); r++)
    {
        for(int c=0; c<objMonitor.getCols(); c++)
        {
            objSensor = objMonitor.getSensorData(r, c);
            
            if(objSensor.dblLightIntensity == 0 
                || objSensor.dblTemperature == 0 
                || objSensor.intHumidity == 0 
                || objSensor.dblPressure == 0 )
            {
                objSensor.IsActive = false;
                objMonitor.NotActive(objSensor.IsActive, r, c);
            } 
        }
    }
}
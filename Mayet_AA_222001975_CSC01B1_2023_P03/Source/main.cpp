#include "IIoTMonitor.h"
#include <ctime>

//using namespace IOTSpace;

int main()
{
    srand(time(nullptr));
    
    IIoTSensor sensors;
    sensors.IsActive = false;
    sensors.dblTemperature = 0;
    sensors.dblLightIntensity = 0;
    sensors.dblPressure = 0;
    sensors.intHumidity = 0;
    
    IIoTMonitor monitor(25, 25, sensors);
    monitor.Scan();
    cout << monitor.toString();
    
    return 0;
}





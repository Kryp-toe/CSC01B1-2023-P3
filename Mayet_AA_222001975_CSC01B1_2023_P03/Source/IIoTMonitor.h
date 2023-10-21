#ifndef IIOTMONITOR_H_INCLUDED
#define IIOTMONITOR_H_INCLUDED
#include <iostream>

using namespace std;

// IIoTSensor struct
struct IIoTSensor{
    bool IsActive = false;
    double dblTemperature; // (Double – [0, 50])
    int intHumidity; // (Integer – [0, 40])
    double dblPressure; // (Double – [0, 40])
    double dblLightIntensity; // Lux (number of lumens), (Double – [10000, 30000])
};

//Forward declaration
class IIoTScanner;

// Class
class IIoTMonitor{
public:
    IIoTMonitor();
    IIoTMonitor(int, int, IIoTSensor);
    IIoTMonitor(const IIoTMonitor&);
    ~IIoTMonitor();
    
    string toString() const;
    void Scan();
    int getRows();
    int getCols();
    IIoTSensor getSensorData(int r, int c);
    void NotActive(bool Active, int r, int c);
    
    // Constant Values / Default
    static constexpr bool ISACTIVE = true;
    static constexpr double TEMPERATURE = 10.0;
    static const int HUMIDITY = 20;
    static constexpr double PRESSURE = 20.0;
    static constexpr double LIGHT_INTENSITY = 10000;
    static const int DEFAULT_ROWS = 50;
    static const int DEFAULT_COLS = 50;

private:
    IIoTSensor** sensors;
    IIoTScanner* scanner;
    int intRows;
    int intCols;
    
    void clone(const IIoTMonitor&);
    void deallocMem();
    int generateRandomNumber(int, int) const;
    void allocateMem(int, int, IIoTSensor);
    void setSensorData();
};

#endif // IIOTMONITOR_H_INCLUDED



#include "IIoTMonitor.h"
#include "IIoTScanner.h"
#include <sstream>

IIoTMonitor::IIoTMonitor() : IIoTMonitor(DEFAULT_ROWS, DEFAULT_COLS, {ISACTIVE, TEMPERATURE, HUMIDITY, PRESSURE, LIGHT_INTENSITY}){
    
    
}

IIoTMonitor::IIoTMonitor(int _intRows, int _intCols, IIoTSensor _sensor){
    // allocate memory
    allocateMem(_intRows, _intCols, _sensor);
    
    // setSensorData
    setSensorData();
}

IIoTMonitor::IIoTMonitor(const IIoTMonitor& objMonitor){

    allocateMem(objMonitor.intRows, objMonitor.intCols, {ISACTIVE, TEMPERATURE, HUMIDITY, PRESSURE,LIGHT_INTENSITY});
    // Make a deep copy
    clone(objMonitor);
}

void IIoTMonitor::allocateMem(int _intRows, int _intCols, IIoTSensor _sensors){

    // Set Private Properties
    intRows = _intRows;
    intCols = _intCols;
    
    // Lifecycle management: creation//allocation
    scanner = new IIoTScanner;
    
    // Allocate Memory for 2D Array
    sensors = new IIoTSensor*[intRows];

    for(int r = 0; r < intRows; r++){
        
        sensors[r] = new IIoTSensor[intCols];
        
        for(int c = 0; c < intCols; c++){
            
            sensors[r][c].IsActive = true;
            sensors[r][c].dblTemperature = _sensors.dblTemperature;
            sensors[r][c].intHumidity = _sensors.intHumidity;
            sensors[r][c].dblPressure = _sensors.dblPressure;
            sensors[r][c].dblLightIntensity = _sensors.dblLightIntensity;
        }
    }
}

void IIoTMonitor::clone(const IIoTMonitor& objMonitor){

    for(int r = 0; r < intRows; r++){
        for(int c = 0; c < intCols; c++){
            
            sensors[r][c].IsActive = objMonitor.sensors[r][c].IsActive;
            sensors[r][c].dblTemperature = objMonitor.sensors[r][c].dblTemperature;
            sensors[r][c].intHumidity = objMonitor.sensors[r][c].intHumidity;
            sensors[r][c].dblPressure = objMonitor.sensors[r][c].dblPressure;
            sensors[r][c].dblLightIntensity = objMonitor.sensors[r][c].dblLightIntensity;
        }
    }
}

void IIoTMonitor::deallocMem(){
    
    // Lifecycle management: destruction/deallocation
    delete scanner;
    
    for(int r = 0; r < intRows; r++){
            delete [] sensors[r];
    }
    
    delete [] sensors;
    sensors = nullptr;
}   

void IIoTMonitor::setSensorData(){
    
    for(int r = 0; r < intRows; r++){
        for(int c = 0; c < intCols; c++){
            sensors[r][c].IsActive = true;
            sensors[r][c].dblTemperature = (double) generateRandomNumber(0, 50);
            sensors[r][c].intHumidity = generateRandomNumber(0, 40);
            sensors[r][c].dblPressure = (double) generateRandomNumber(0, 40);
            sensors[r][c].dblLightIntensity = (double) generateRandomNumber(0, 300000);
        }
    }
}

IIoTSensor IIoTMonitor::getSensorData(int r, int c)
{
    return sensors[r][c];
}


int IIoTMonitor::generateRandomNumber(int intLower, int intUpper) const{
    
    int intRange = (intUpper - intLower) + 1;
    return rand() % intRange + intLower;
}

int IIoTMonitor::getRows()
{
    return intRows;
}

int IIoTMonitor::getCols()
{
    return intCols;
}

void IIoTMonitor::Scan()
{
   //"this" means the current instance
   scanner -> Scan(*this);
}

void IIoTMonitor::NotActive(bool Active, int r, int c)
{
    sensors[r][c].IsActive = Active;
}

string IIoTMonitor::toString() const{
    
    stringstream ss;
    
    for(int r = 0; r < intRows; r++){
        for(int c = 0; c < intCols; c++){
            int numFaultySensors = 0;
            char sensorChar = '.';
            
            // If more than one, print 'M' for multi/many
            // Malfunctioning if
            // temperature sensor -> if temp <=0 || > 40
            // humidity sensor -> if humidity <= 0 || > 30.7
            // temperature sensor -> if Pressure <= 0 || > 30.2
            // lightIntensity -> if lightIntensity < 0 || > 100000
            
            if(sensors[r][c].dblTemperature < 0 || sensors[r][c].dblTemperature > 40){
                numFaultySensors++;
                sensorChar = 'T';
            }
                
            if( sensors[r][c].intHumidity < 0 || sensors[r][c].intHumidity > 30){
                numFaultySensors++;
                sensorChar = 'H';
            }
        
            if(sensors[r][c].dblPressure < 0 || sensors[r][c].dblPressure > 30.2){
                numFaultySensors++;
                sensorChar = 'P';
            }
        
            if(sensors[r][c].dblLightIntensity < 100000 || sensors[r][c].dblLightIntensity > 300000){
                numFaultySensors++;
                sensorChar = 'L';
            }
            
            // Assign characters
            if(numFaultySensors = 0){
                sensorChar = '.';
            }else if(numFaultySensors > 1){
                sensorChar = 'M';
            }
            
            if(sensors[r][c].IsActive == false)
            {
                sensorChar = 'X';
            }
            
            ss << sensorChar << ' ';
        }
        
        ss << endl;
    }
    
    return ss.str();
}


IIoTMonitor::~IIoTMonitor(){    
    
    deallocMem();
}






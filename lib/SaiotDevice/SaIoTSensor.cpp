#include "SaIoTSensor.h"

SaIoTSensor::~SaIoTSensor() {}

SaIoTSensor::SaIoTSensor(String _jsonConfig){
    setJsonConfig(_jsonConfig);
}
SaIoTSensor::SaIoTSensor(String _key, String _tag, String _unit, String _type){
    jConf += ("{\"key\":\"" + _key + "\",\"unit\":\"" + _unit + "\",\"type\":\"" + _type + "\",\"tag\":\"" + _tag + "\"}");
    key = _key;
}
String SaIoTSensor::getJsonConfig(void){
    return jConf;
}
String SaIoTSensor::getKey(void){
    return key;
}
String SaIoTSensor::getSerial(void){
    return serial;
}
double SaIoTSensor::getValue(void){
    return value;
}
String SaIoTSensor::getByField(String _field){
    int idxField = jConf.indexOf(_field); //field
	int init, end;
	
	if(idxField != -1){
		init = jConf.indexOf(":", idxField) + 1; 
    if(jConf[init] == '\"'){ //nesse caso o dado sera string e precisamos que o index aponte para o inicio do dado
      init = init+1;
      end = jConf.indexOf("\"", init);
    }else{//nesse caso o dado sera um valor numerico
      end = jConf.indexOf(",", init);
      if(end == -1){ //nesse caso o dado se encontra no final do JSON
			    end = jConf.indexOf("}", init);
        }
	}
    return jConf.substring(init,end); 
    }else{ //caso o campo n seja encontrado
		return "-1";
	}
}

String SaIoTSensor::getUnit(void){
    return getByField("unit");
}
String SaIoTSensor::getTag(void){
    return getByField("tag");
}
String SaIoTSensor::getType(void){
    return getByField("type");
}

void SaIoTSensor::setJsonConfig(String _jsonConfig){
    jConf = _jsonConfig;
    key = getByField("key");
    serial = getByField("serial");
}
void SaIoTSensor::setValue(double _value){
    value = _value;
}

void SaIoTSensor::verify(void){
    
    if(deadband != NULL_VALUE){
        if(exceededDeadband()){
            sendValue();
        }
    }
    if(timeout != NULL_VALUE){
        if(exceededTimeout()){
            sendValue();
        }
    }
}

bool SaIoTSensor::exceededDeadband(){
    bool ret = value>deadband ? true : false;
    return ret;
}
bool SaIoTSensor::exceededTimeout(){
    unsigned long int currentTime = millis();
    if(lastTimeout == 0){
        lastTimeout = currentTime; //equivalente ao start
        return false;
    }
    bool ret = (currentTime - lastTimeout) > timeout ? true : false;
    return ret;
}

int SaIoTSensor::sendValue(void){ 
    lastTimeout = millis();

    double value = getReadValueFunction();
    Serial.println("VALOR LIDO: " + value);
    return 0;
}

void SaIoTSensor::setTimeout(long int _timeout){
 timeout = _timeout;
}
void SaIoTSensor::setDeadBand(long int _deadband){
 deadband = _deadband;
}

void SaIoTSensor::setReadValueFunction(verifyfunct readValue){
    readValueFunction = readValue;
}

double SaIoTSensor::getReadValueFunction(){ //[Dani] Dá um jeito de colocar uma função default pra caso o usuário queira sacanear
    return readValueFunction();
}
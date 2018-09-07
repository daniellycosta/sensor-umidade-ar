#include "SaIoTDeviceLib.h"

SaIoTDeviceLib::SaIoTDeviceLib(String _name, String _serial, String _email)
{
  name = _name;
  serial = _serial;
  email = _email;

};
SaIoTDeviceLib::SaIoTDeviceLib(String _name, String _serial){
  name = _name;
  serial = _serial;
}

SaIoTDeviceLib::SaIoTDeviceLib(){
};

void SaIoTDeviceLib::preSetCom(WiFiClient& espClient, fptr _function){
  objCom.setClientw(espClient);
  objCom.setCallbackz(_function);
}
void SaIoTDeviceLib::startDefault(String s){
  startCom(HOST, PORT, hostHttp, POSTDISPOSITIVO, s);
}
void SaIoTDeviceLib::startCom(const char* hostSend, uint16_t portSend, const char* hostTok, const char* hostCd, String pUser){
  objCom.setServerPort(hostSend, portSend);
  //objCom.setCallbackz(SaIoTDeviceLib::callback);
  //objCom.getObj().setCallback(SaIoTDeviceLib::callback);
  WiFi.begin("Tech_D0010220", "santacruz1701");
  //WiFi.begin("LII","wifiLI2Rn");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.print("Conectado na Rede " + WiFi.SSID());
  //wifi.autoConnect(this->serial);
  this->setToken(objCom.getToken(hostTok, email, pUser, serial));
  objCom.registerDevice(serial, email, token, this->makeJconf(), hostCd);
}

void SaIoTDeviceLib::setToken(String _token){
  token = _token;
}
void SaIoTDeviceLib::setEmail(String _email){
  email = _email;
}
/*void SaIoTDeviceLib::handle(void){
  for(int i=0;i<qtdSensors;i++){
    sensors[i]->verify();
  }
}*/
boolean SaIoTDeviceLib::loopLoko(){
  return objCom.handleCom();
}
String SaIoTDeviceLib::getName(void){
  return name;
}
String SaIoTDeviceLib::getSerial(void){
  return serial;
}
String SaIoTDeviceLib::getToken(void){
  return token;
}
String SaIoTDeviceLib::getEmail(void){
  return email;
}
String SaIoTDeviceLib::makeJconf(void){
  String JSON;
  JSON += "{\"token\":\""+token+"\",\"data\":{\"name\":\""+name +"\",\"serial\":\""+ serial+"\"";
  if(qtdControllers>0){
    JSON += ",\"controllers\":[";
    for(int i=0; i<qtdControllers; i++){
      JSON += controllers[i]->getJsonConfig();
      if(i==qtdControllers-1){
        JSON += "]";
      }else{
        JSON += ",";
      }
    }
  }  
  if(qtdSensors>0){
    JSON += ",\"sensors\":[";
    for(int i=0; i<qtdSensors; i++){
      JSON += sensors[i]->getJsonConfig();
      if(i==qtdSensors-1){
        JSON += "]";
      }else{
        JSON += ",";
      }
    }
  }
  JSON +="}}"; 
  return JSON;
}

int SaIoTDeviceLib::getNSensors(void){
  return qtdSensors;
}

int SaIoTDeviceLib::getNControllers(void){
  return qtdControllers;
}

void SaIoTDeviceLib::addSensor(SaIoTSensor &newSensor)
{
  sensors[qtdSensors++] = &newSensor;
}
/*void SaIoTDeviceLib::addSensor(String _key, String _unit)
{
  sensors[qtdSensors++] = new SaIoTSensor(_key, _unit);
}*/
/*void SaIoTDeviceLib::addSensor(String _key, int _deadbandMin, int _deadbandMax, int _timeout, int _resolution, bool _isAcumm, String _tag, String _unit)
{
  sensors[qtdSensors++] = new SaIoTSensor(_key, _deadbandMin, _deadbandMax, _timeout, _resolution, _isAcumm, _tag, _unit);
}*/

void SaIoTDeviceLib::addController(SaIoTController &newController)
{
  controllers[qtdControllers++] = &newController;
}

/*void SaIoTDeviceLib::addController(String _key, String _type)
{
  controllers[qtdControllers++] = new SaIoTController(_key, _type);
}
void SaIoTDeviceLib::addController(String _key, String _type, String _tag, String _description, double _min, double _step, double _max)
{
  controllers[qtdControllers++] = new SaIoTController(_key, _type, _tag, _description, _min, _step, _max);
}*/





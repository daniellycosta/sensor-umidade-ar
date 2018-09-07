#ifndef SaIoTDeviceLib_h
#define SaIoTDeviceLib_h
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "SaIoTSensor.h"
#include "SaIoTController.h"
#include "SaIoTCom.h"

#define maxSensors 5
#define maxControllers 1
//FALTA PENSAR NOS CONTROLADORES, NA HORA DO SUBSCRIBE

//Params conexão SaIoT server v1.7
#define HOST "api.saiot.ect.ufrn.br" 
#define hostHttp "http://api.saiot.ect.ufrn.br/v1/device/auth/login" 
#define PORT  8000 //MQTT 
#define POSTDISPOSITIVO "/manager/post/device/" 

//typedef void (*fncpt)(String); //ponteiro pra função
typedef void (*fptr)(char* topic, byte* payload, unsigned int length);

class SaIoTDeviceLib
{
private:

  /*
    Tudo que for do device deve ser guardado na EEPROM futuramente, pra caso de atualização via OTA 
  */
  String name;
  String serial;
  String token;
  String email; 

  unsigned int qtdSensors = 0;
  unsigned int qtdControllers = 0;
  SaIoTSensor *sensors[maxSensors];
  SaIoTController *controllers[maxControllers];
  SaIoTCom objCom;
  //WiFiManager wifi;
public:
  /* criar um construtor  e passar a start para o produto talvez*/
  //Editar após discussão de conexão
  SaIoTDeviceLib(String _name, String _serial, String _email);
  SaIoTDeviceLib(String _name, String _serial);
  SaIoTDeviceLib();

  void preSetCom(WiFiClient&, fptr _function);
  void startDefault(String s);
  void startCom(const char* hostSend, uint16_t portSend, const char* hostTok, const char* hostCd, String pUser);//poderia ser setParams e só depois o Start
  void setToken(String _token);
  void setEmail(String _email);
  void handle(void);
  boolean loopLoko();
  

  String getName();
  String getSerial();
  String getToken();
  String getEmail();
  String getProtocol();

  int getNSensors();
  int getNControllers();

  String makeJconf();

  void addSensor(SaIoTSensor &newSensor);
  /*void addSensor(String _key, int _deadbandMin, int _deadbandMax, int _timeout, int _resolution, bool _isAcumm, String _label, String _unit);
  void addSensor(String _key, String _unit);*/

  void addController(SaIoTController &newController);
  /*void addController(String _key, String _type);
  void addController(String _key, String _type, String _tag, String _description, double _min, double _step, double _max);*/
};
#endif

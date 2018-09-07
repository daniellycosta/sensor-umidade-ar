#ifndef SaIoTCom_h
#define SaIoTCom_h

#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

typedef void (*functionPointer)(char*, uint8_t*, unsigned int); //definido assim pelo MQTT_CALLBACK_SIGNATURE;

class SaIoTCom
{
  private:  
    //WiFiClient espClient;
    PubSubClient mqttClient;
  public:
    SaIoTCom();
    SaIoTCom(WiFiClient& espClient);
    String getToken(String hostHttp,String user, String password, String serial);
    void setServerPort(const char * server, uint16_t port);
    void setCallbackz(functionPointer f);
    void registerDevice(String serial,String user,String token,String jsonConf,const char* hostReg);
    void setClientw(WiFiClient& espClient);

    boolean handleCom();
    //PubSubClient getObj(void);
    //void subscribeController(String topic);
    //void doHandle();


};

#endif
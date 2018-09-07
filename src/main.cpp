#include <Arduino.h>
#include <DHT.h>
#include<SaIoTDeviceLib.h>
#include<SaIoTSensor.h>
#include<SaIoTCom.h>

#define EMAIL "daniellycmcosta@gmail.com"
#define SENHA "0123456789"
#define SERIALKEY "sensUmTemp"
#define NOME "sensorUmidadeTemperatura"

#define KEYSENSOR "umdSensor"
#define TAG "sensorUmidade"
#define UNIDADE "unidade"
#define TIPO "tipo"

SaIoTCom deviceCommunication;

void setup() {
    SaIoTDeviceLib umidadeTemp(NOME,SERIALKEY, EMAIL);
    SaIoTSensor umidade(KEYSENSOR,TAG,UNIDADE,TIPO);
    String token = deviceCommunication.getToken(hostHttp,EMAIL,SENHA,SERIALKEY);

    
}

void loop() {
    // put your main code here, to run repeatedly:
}
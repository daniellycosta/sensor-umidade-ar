#include "SaIoTController.h"

SaIoTController::SaIoTController() {}

SaIoTController::~SaIoTController() {
}

SaIoTController::SaIoTController(String _jsonConfig){
  setJsonConfig(_jsonConfig);
}

SaIoTController::SaIoTController(String _key, String _tClass) //esse método é necessário?
{
  jConf += ("{\"key\":\"" + _key + "\",\"class\":\"" + _tClass + "\"}");
  key = _key;
}

SaIoTController::SaIoTController(String _key, String _tClass, String _tag)
{
  jConf += ("{\"key\":\"" + _key + "\",\"class\":\"" + _tClass + "\",\"tag\":\"" + _tag + "\"}");
  key = _key;
}

String SaIoTController::getKey(void)
{
  return key;
}

String SaIoTController::getClass(void)
{
  return getByField("class");
}

String SaIoTController::getTag(void)
{
  return getByField("tag");
}

String SaIoTController::getByField(String _field){
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

void SaIoTController::setJsonConfig(String _jConf){
  jConf = _jConf;
  key = getByField("key");

}

String SaIoTController::getJsonConfig(void){
  return jConf;
}

void SaIoTController::setAction(func_pointer _function){
  actFoo = _function;
}



#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <Array.h>

using namespace std;


void* t; 






void setup() {
  //Serial.setTimeout(10000);
  Serial.begin(9600);
  // put your setup code here, to run once:
  //while (Serial.available() == 0){
  //}
  //int thing = Serial.read();
  



  const int ONE_WIRE_BUS = 4;
  const int DHTPIN = 2;
  const int DHTTYPE = DHT11;

  DHT dht(DHTPIN, DHTTYPE);
  OneWire oneWire(ONE_WIRE_BUS);
  DallasTemperature sensors(&oneWire);

  t = &sensors;

  
  sensors.begin();
  dht.begin();
  
}

void loop() {
  
    
    //float h = dht.readHumidity();
    //float t = dht.readTemperature();
    
    //Serial.println(h);
    //Serial.println(t);

  String str = Serial.readStringUntil('/');
  // String str = "";

  // while ( Serial.available() > 0 ) {                
  //   char received = Serial.read();
  //   if ( received == '/' ) {                      
  //     break;
  //   } else {                                       // add to receive buffer
  //     str += received;        
  //   }
  // }
    //String str = "potatis;hej;gron;frukt";

  
  String arr[100];  

  if(str.length() > 0){
    split(str, arr);


    if(arr[0] == "initialize"){
      //puting all constants in voidsetup here instead
      //putting the initializesation of onewire and dallas here aswell
    }


    if(arr[0] == "readsensor"){
      if(arr[1] == "dallas"){
        sendthermal(arr[2].toInt());
      }
    }
  }
    
    
    //if(s == "temp1"){
      //sendthermal(0);
    //}else if(s == "temp2"){
      //sendthermal(1);
    //}
    //Serial.println(s);
    
    
    
        

    //delay(3000);
    
}

int sendthermal(int i){

  DallasTemperature *s = (DallasTemperature*) t;
  s->requestTemperaturesByIndex(i);
  
  String data = String("temp") + String(":") + (i+1) + String(":") + s->getTempCByIndex(i);
  Serial.print(data);
}
    

bool split(String str, String* arr){
  
  int start = 0;
  int end = 0;
  int i = 0;
  
  while (end < (str.length() -1)) {

      
    end = str.indexOf(";",start);
    if( end == -1 ){
      // I get a of by one error when using string.length() -1
      end = str.length();
    }
    String s = str.substring(start, end);
    arr[i] = s;
    start = ++end;
    i++;

  }

 
} 


//460 = 100 grader

//960 = 0 grader

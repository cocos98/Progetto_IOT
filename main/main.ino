
#include <Wire.h>
#define ph_sensor A7   //ph
#define TdsSensorPin A3
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);


unsigned long int avgValue;
float b;
int buf[10], temp;
unsigned long int avgval_ADC;
int buffer_tds[10],temp1;
int sensorPin = A0;       //torbidità
float volt;


void setup()
{
    Serial.begin(9600);
    pinMode(TdsSensorPin,INPUT);
    sensor.begin();
}

void loop()
{
  float ntu;
  float TDS;
  float temperature;
  float ph;

  TDS=calculate_tds();
  ntu=calculate_torbidita();
  temperature=calculate_temp();
  ph=calculate_ph();
  Serial.print(temperature); 
  Serial.print(",");
  Serial.print(ntu);
  Serial.print(",");
  Serial.print(TDS);
  Serial.print(",");
  Serial.println(ph);
  delay(5000);
}







float calculate_temp(){

  sensor.requestTemperatures();
  float tempCelsius = sensor.getTempCByIndex(0);
  return tempCelsius;
}



float calculate_ph(){
  float phValue;
  float avgValue=0;;
  for (int i = 0; i < 10; i++) {
    buf[i] = analogRead(ph_sensor);
    delay(10);
  }
  
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue; 
   
  return phValue;
}



  float calculate_tds(){
  float TDS;
  for(int i=0;i<10;i++) 
  { 
    buffer_tds[i]=analogRead(TdsSensorPin);
    delay(30);
  }
  for(int i=0;i<9;i++)
  {
    for(int j=i+1;j<10;j++)
      {
        if(buffer_tds[i]>buffer_tds[j])
          {
            temp1=buffer_tds[i];
            buffer_tds[i]=buffer_tds[j];
            buffer_tds[j]=temp1;
          }
        }
   }

  avgval_ADC=0;
  for(int i=2;i<8;i++){
    avgval_ADC+=buffer_tds[i];
  }
  float voltage_value = (float)avgval_ADC*5.0/1024.0/6;
  TDS = (133.42/voltage_value*voltage_value-255.86*voltage_value*voltage_value + 857.39*voltage_value)*0.5;
  
  
  return TDS;   

  
}


float calculate_torbidita(){
  volt = ((float)analogRead(sensorPin)/1024)*5;
  volt = round_to_dp(volt,2);
  float ntu=0;
  if(volt < 2.5){
    ntu = 3000;
  }else{
    ntu = -1120.4*square(volt)+5742.3*volt-4353.8;
  }
  return volt;
}



float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

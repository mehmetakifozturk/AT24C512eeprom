/*
------------------------------------------------------------
pins 
            -----------
            *
        A0=|            |=VCC 
        A1=| AT24C      |=WP 
        A2=|   512      |=SCL 
       GND=|            |=SDA
            -----------
AT24C512.h librariy for using arduino boards with AT24C512 external eeprom.
there are three important functions dedfined. 
begin(X); X is how many eeprom connected to the i2c bus ? and begin  will return boolean is ok or not;
put(address,data); address is eeprom adres but there is 0 to 65536 address for one device . if device quantity (for example 4) 65536*4=262144   address size . it lineer . just write function and run it
pul(address,data); pul same locig with put but it brings data


-------------------------------------------------------------
*/





#include <AT24C512.h>
#define forexample_address 1256
AT24C512 eprom; // object of at24c512
struct some_data{
  int dataint;
  byte databyte;
  double datadouble;
  String str;
};
struct some_data data_in{-512,127,22.8,"arsra"};
struct some_data data_out{0,0,0,"0"};

void setup(){
  pinMode(5,OUTPUT);pinMode(18,OUTPUT);
  digitalWrite(5,0); digitalWrite(18,1);//kulladığım çihgazdaki enable pinleri
Serial.begin(9600);
eprom.begin(4);// how many eeprom connected the i2c bus ? put the number  inside of 'begin(x)'fonction. it is defaultly 1
struct some_data data_in{-512,127,22.8,"arsra"};// some data for put the eeprom.
struct some_data data_out{0,0,0,"0"};// and some data is coming back from eprom.this is  example  for structs you can use any type data
eprom.put(forexample_address,data_in); // put function is sending   data to eeprom
eprom.pul(forexample_address,data_out);// pul function is bringing   data from eeprom

Serial.print("data_out.databyte= ");Serial.println(data_out.databyte);
Serial.print("data_out.datadouble= ");Serial.println(data_out.datadouble);
Serial.print("data_out.dataint= ");Serial.println(data_out.dataint);
Serial.print("data_out.str= ");Serial.println(data_out.str);
///// other data types //////////////////////////

int data_int=52;
int data_int_back=0;
//or 
float data_float=12.45;
// we can use any type data put and pul functions
eprom.put(0,data_int);
eprom.pul(0,data_int_back);
Serial.print("data_int_back= ");Serial.println(data_int_back);
delay(100);
}


void loop() {



}

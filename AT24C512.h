#ifndef AT24C512_H
#define AT24C512_H
#include <Arduino.h>
#include <Wire.h>
#define entegre_memory_size 65536 // tek bir at24c512 entegresinin hafıza boyutu
class AT24C512
{
private:
    const uint8_t device_i2c_address_offset =80;//at24c512 adres ofsetleri 80 
    uint16_t device_i2c_address=80;
    uint32_t eeprom_address=0;
    uint32_t next_address=0;
    uint8_t entegre_quantity=1;// how many eeprom connected the i2c bus ?
    uint32_t total_eeprom_size=65536;
	
    //////////////////////////////////////////
 

    
     bool write_byte(uint16_t device_number, uint16_t data_address, uint8_t *pointer_of_byte);//i2c protokolu ile veri yazacaz
	 bool read_byte(uint16_t device_number, uint16_t data_address, uint8_t *pointer_of_byte);//i2c protokolu ile veri okuycaz
     bool put_byte_by_byte(uint32_t data_size, uint32_t  address, uint8_t *pointer_of_byte);//veriyi parçalayıp write fon gonderiyor
	 bool pul_byte_by_byte(uint32_t data_size, uint32_t  address, uint8_t *pointer_of_byte);//veriyi parçalarını birleştiriyor

public:
    AT24C512(/* args */);
    ~AT24C512();
bool begin(uint8_t quantity=1);
	 uint32_t get_next_addres();
template<typename T> bool put(uint32_t  address, const T &t){
               uint32_t data_size=sizeof(t);
			   unsigned char *pointer_of_data;
               pointer_of_data=(unsigned char*) &t;
               return put_byte_by_byte(data_size,address,pointer_of_data);
               
            }
			
template<typename T> bool pul(uint32_t  address, const T &t){
				uint32_t data_size=sizeof(t);
			   unsigned char *pointer_of_data;
               pointer_of_data=(unsigned char*) &t;
               return pul_byte_by_byte(data_size,address,pointer_of_data);
            }
          
  

};


























#endif
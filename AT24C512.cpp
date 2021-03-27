#include "AT24C512.h"

AT24C512::AT24C512(/* args */)
{
}

AT24C512::~AT24C512()
{
}
bool AT24C512::begin(uint8_t quantity){
	   if(quantity>8||quantity<1){
		return false;
        
		}else if(Wire.begin()){
			entegre_quantity=quantity;
          total_eeprom_size=entegre_quantity*entegre_memory_size;
          return true;
		}else{
            return false;
        }   
   }

bool AT24C512::write_byte(uint16_t device_number, uint16_t data_address, uint8_t *pointer_of_byte){
            	if(device_number>8||device_number<0){
            	return false;	
				}
               device_i2c_address=device_number+device_i2c_address_offset;

                 Wire.beginTransmission(device_i2c_address);
                 Wire.write((int)(data_address >> 8));   // MSB
                 Wire.write((int)(data_address & 0xFF)); // LSB

                 Wire.write(*pointer_of_byte);
 
                 Wire.endTransmission();
                 delay(5);
            	return true;
			}
			
bool AT24C512::read_byte(uint16_t device_number, uint16_t data_address, uint8_t *pointer_of_byte){
            	if(device_number>8||device_number<0){
            	return false;	
				}
            
                 byte rcvData = 0xFF;
                 device_i2c_address=device_number+device_i2c_address_offset;

                 Wire.beginTransmission(device_i2c_address);

                 Wire.write((int)(data_address >> 8));   // MSB
                 Wire.write((int)(data_address & 0xFF)); // LSB

                 Wire.endTransmission();
 
                 Wire.requestFrom(device_i2c_address, 1);
 
                 rcvData =  Wire.read();
                *pointer_of_byte=rcvData;
 
            	return true;
			}

            uint32_t AT24C512::get_next_addres(){
                return next_address;
            }
             
bool AT24C512:: put_byte_by_byte(uint32_t data_size, uint32_t  address, uint8_t *p){
              
                uint32_t real_data_address=address%entegre_memory_size;
                uint16_t device_number=address/entegre_memory_size;
                next_address=(data_size+address)%total_eeprom_size;
              
               if(data_size+address>total_eeprom_size||real_data_address+data_size>=entegre_memory_size||address<0){
               	if(data_size+address>total_eeprom_size||address<0){
               		next_address=0;
               		
               		return false;
				   }else{
				   	
				   	   while(real_data_address!=entegre_memory_size){
				   	
				   	   	      write_byte(device_number,real_data_address,p);
								   
				   	   	     data_size--;
				   	   	     p++;
				   	   	     real_data_address++;
						  }
						  real_data_address=0;
						  device_number++;
						  device_number=device_number%entegre_quantity;
				   }
				   
				}
				for( ;data_size>0;data_size--){
					  write_byte(device_number,real_data_address,p);
					
					p++;
					real_data_address++;
				}
				
				
				return true;
}
bool AT24C512::pul_byte_by_byte(uint32_t data_size, uint32_t  address, uint8_t *p){
     
               uint32_t real_data_address=address%entegre_memory_size;
               uint16_t device_number=address/entegre_memory_size;
              

            if(data_size+address>total_eeprom_size||real_data_address+data_size>=entegre_memory_size||address<0){
               	if(data_size+address>total_eeprom_size||address<0){
               		next_address=0;
               		
               		return 0;
				   }else{
				   	
				   	   while(real_data_address!=entegre_memory_size){
				   	   	     read_byte(device_number,real_data_address,p);
				   	   	     data_size--;
				   	   	     p++;
				   	   	     real_data_address++;
						  }
						  real_data_address=0;
						  device_number++;
						  device_number=device_number%entegre_quantity;
				   }
				   
				}
		for( ;data_size>0;data_size--){
		read_byte(device_number,real_data_address,p);
		     p++;
		     real_data_address++;
			}
				
				
	return true;
}

     
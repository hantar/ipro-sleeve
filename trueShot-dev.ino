//Libraries
#include <Wire.h>
#include <CurieBLE.h>
#include "Adafruit_DRV2605.h"
//Variables
const int effect=44;//Effect # - Page 60: https://goo.gl/rSMYH7
const int transition=86;
const bool debug=true;//Set to 'true' to debug code
const int btLED=3;//Flora LED
const int flexPin=2;
int bendValue=0;
bool btStatus=false;
//Curie
String cmdInput; String lastCmd="";
BLEPeripheral blePeripheral;
BLEService uartService=BLEService("6E400001B5A3F393E0A9E50E24DCCA9E");
BLECharacteristic rxCharacteristic=BLECharacteristic("6E400002B5A3F393E0A9E50E24DCCA9E",BLEWriteWithoutResponse,20);//TX on central
BLECharacteristic txCharacteristic=BLECharacteristic("6E400003B5A3F393E0A9E50E24DCCA9E",BLENotify,20);//RX on central
//I2C
Adafruit_DRV2605 drv;

void setup(){
	Serial.begin(9600);
	if(debug==true){Serial.println("DEBUG ACTIVE - Welcome to TRUE Shot\nCreated by IIT Students for IPRO - Spring 2017");}
	// DRV2605L
	drv.begin();
	delayMicroseconds(10000);
	drv.setMode(DRV2605_MODE_INTTRIG);
	drv.selectLibrary(1);
	if(debug==true){Serial.println("Haptic Feedback Ready!");}
	// Curie
	Wire.begin();
	delayMicroseconds(10000);
	blePeripheral.setLocalName("TRUEShot");
  blePeripheral.setAdvertisedServiceUuid(uartService.uuid());
  blePeripheral.addAttribute(uartService);
  blePeripheral.addAttribute(rxCharacteristic);
  blePeripheral.addAttribute(txCharacteristic);
  blePeripheral.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  blePeripheral.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  rxCharacteristic.setEventHandler(BLEWritten, rxCharacteristicWritten);
  blePeripheral.begin();
  if(debug==true){Serial.println("BLE UART...\nLoading...");}
  delay(5000);
  if(debug==true){Serial.println("BLE UART Ready!");delay(500);}
}

void loop(){
	blePeripheral.poll();
  bendValue=analogRead(flexPin);//Serial.println(bendValue);
  /*bendValue=700;
  if(bendValue<820){
    goodFollowThrough();
  }*/
	if(btStatus){
		digitalWrite(btLED, HIGH);
		if(String(cmdInput)=="1"){
			goodFollowThrough();
		} else if(String(cmdInput)=="2"){
      badMotion();
		}
		cmdInput="0";
	}else{
		if(debug==true){Serial.print("No Connection - ");Serial.println(random(0,9999));}
		digitalWrite(btLED, LOW);
	}
}

void goodFollowThrough(){//Adafruit DRV2605L Haptic Feedback Microcontroller
	if(debug==true){Serial.print("\nEffect # ");Serial.println(effect);}
  drv.setWaveform(0,14);//Transition to Effect
  drv.setWaveform(1,44);
  drv.setWaveform(2,0);//End of Waveform
	drv.go();//Play Effect
  if(debug==true){Serial.println("\nPlayed");}
}

void badMotion(){//Adafruit DRV2605L Haptic Feedback Microcontroller
  if(debug==true){Serial.print("\nEffect # ");Serial.println(effect);}
  drv.setWaveform(0,86);//Transition to Effect
  drv.setWaveform(1,52);//Effects
  drv.setWaveform(2,7);
  drv.setWaveform(3,52);
  drv.setWaveform(4,0);//End of Waveform
  drv.go();//Play Effect
  if(debug==true){Serial.println("\nPlayed");}
  delay(2000);
}

void blePeripheralConnectHandler(BLECentral& central){
  if(debug==true){Serial.print("Connected event, central: ");Serial.println(central.address());}
  btStatus=true;
}

void blePeripheralDisconnectHandler(BLECentral& central){
  if(debug==true){Serial.print("Disconnected event, central: ");Serial.println(central.address());}
  btStatus=false;
}

void rxCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic){
  if(characteristic.value()){
    int len=characteristic.valueLength();
    if(cmdInput){
      lastCmd=cmdInput;
    }
    cmdInput="";
    for(int i=0;i<len;i++){
      cmdInput+=(char)*(characteristic.value()+i);
    }
    if(debug==true){Serial.print("Characteristic event, written: ");Serial.println(cmdInput);}
  }
}

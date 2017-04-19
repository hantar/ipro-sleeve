//Libraries
#include <Wire.h>
#include <CurieBLE.h>
#include <Adafruit_DRV2605.h>
//Variables
uint8_t effect=1;//Effect # - Page 60: https://goo.gl/rSMYH7
const bool debug=false;//Set to 'true' to debug code
const int vibrationDisc=3;//Will have to be PWM based on effect
const int btLED=4;//Flora LED
const int flexSensor=A2;
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
	if(debug==true){Serial.println("DEBUG ACTIVE - Welcome to TRUE Shot\nCreated by IIT Students for IPRO\tSpring 2017")}
	// DRV2605L
	drv.begin();
	delayMicroseconds(10000);
	drv.selectLibrary(1);
	drv.setMode(DRV2605_MODE_INTTRIG);
	if(debug==true){Serial.println("Haptic Feedback Ready!")}
	// Curie
	Wire.being();
	delayMicroseconds(10000);
	blePeripheral.setLocalName("TRUE Shot");
  blePeripheral.setAdvertisedServiceUuid(uartService.uuid());
  blePeripheral.addAttribute(uartService);
  blePeripheral.addAttribute(rxCharacteristic);
  blePeripheral.addAttribute(txCharacteristic);
  blePeripheral.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  blePeripheral.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  rxCharacteristic.setEventHandler(BLEWritten, rxCharacteristicWritten);
  blePeripheral.begin();
  if(debug==true){Serial.println("BLE UART...\nLoading...")}
  delay(5000);
  if(debug==true){Serial.println("BLE UART Ready!");delay(500)}
}

void loop(){
	blePeripheral.poll();
	if(btStatus){
		digitalWrite(btLED, HIGH);
		if(String(cmdInput)=="1"){
			hapticFeedback();
		}
		lastCmd=cmdInput;
	}else{
		if(debug==true){Serial.println("No Connection - ");Serial.println(randomSeed(bendValue))}
		digitalWrite(btLED, LOW);
	}
}

void hapticFeedback(){//Adafruit DRV2605L Haptic Feedback Microcontroller
	if(debug==true){Serial.print("\nEffect # ");Serial.println(effect)}
	drv.setWaveform(0, effect);//Start of Effect
	drv.setWaveform(1, 0);//End of Waveform
	drv.go();//Play Effect
}

void blePeripheralConnectHandler(BLECentral& central){
  if(debug==true){Serial.print("Connected event, central: ");Serial.println(central.address())}
  digitalWrite(btLED,HIGH);
  btStatus=true;
}

void blePeripheralDisconnectHandler(BLECentral& central){
  if(debug==true){Serial.print("Disconnected event, central: ");Serial.println(central.address())}
  digitalWrite(btLED,LOW);
  btStatus=false;
}

void rxCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic){
  
  if(characteristic.value()){
    int len=characteristic.valueLength();
    if(cmdInput){
      lastCmd=cmdInput
    }
    cmdInput="";
    for(inti=0;i<len;i++){
      cmdInput+=(char)*(characteristic.value()+i)
    }
    if(debug==true){Serial.print("Characteristic event, written: ");Serial.println(cmdInput)}
  }
}

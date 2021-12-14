#define _GNU_SOURCE
#include "MicroBit.h"
#include "NEPODefs.h"
#include <stdlib.h>

class Roboter {
	public:
	    MicroBit* uBit;		// Objekt der Klasse uBit;
	    MicroBitI2C *i2c;
		char buf[5] = { 0, 0, 0, 0, 0 };
	
	public:
		Roboter(){
		    uBit = new MicroBit();
		    uBit->init();
		    i2c = new MicroBitI2C (MICROBIT_PIN_P20, MICROBIT_PIN_P19);
			_cbInit(buf, i2c, uBit);
		    }
	
	public:
		~Roboter() {
		    release_fiber();
		    }
		    
//ALT
//		void plusAusgeben() {
//		    uBit->display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
//		    uBit->display.print(MicroBitImage("0,0,255,0,0\n0,0,255,0,0\n255,255,255,255,255\n0,0,255,0,0\n0,0,255,0,0\n"));
//		    uBit->sleep(500);
//		    }
//		
//		void kreuzAusgeben() {
//		    uBit->display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
//		    uBit->display.print(MicroBitImage("255,0,0,0,255\n0,255,0,255,0\n0,0,255,0,0\n0,255,0,255,0\n255,0,0,0,255\n"));
//		    uBit->sleep(500);
//		    }
//		
//		void minusAusgeben() {
//		    uBit->display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
//		    uBit->display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n255,255,255,255,255\n0,0,0,0,0\n0,0,0,0,0\n"));
//		    uBit->sleep(500);
//		}
//		
//		
//		
//		void runTemperatureProgram(){
//			while (!uBit->buttonB.isPressed()){
//				if (uBit->buttonA.isPressed()){
//					int temperature = uBit->thermometer.getTemperature();
//					uBit->display.scroll(temperature);
//					uBit->display.scroll("C");
//				}
//			}
//		}
//		
//		void runTemperatureProgram2(){
//					int temperature = uBit->thermometer.getTemperature();
//					uBit->display.scroll(temperature);
//					uBit->display.scroll("C");
//		}
//		
//		void runMoveForward(){
//			while(!uBit->buttonA.isPressed()){
//				_cbSetMotors(buf,i2c,60,30);
//			}
//		}
//		
//		void runUltrasonic(){
//			int ultrasonic = _cbGetSampleUltrasonic(buf, i2c);
//			uBit->display.scroll(ultrasonic);
//		}
//ENDE ALT
		
		//11.11.: Mikrofon verstehen und richtig verwenden.
		void tryMicrophone(){													//Erstes Stück Code zum Implementieren --> Fehlgeschlagen; Funktioniert nur bei Stetigem Ton direkt nach dem Start, kann nicht später Ton erkennen
			uBit->display.scroll(uBit->io.P21.getMicrophoneValue());
			if(uBit->io.P21.getMicrophoneValue() > 1){
			uBit->display.scroll(uBit->io.P21.getMicrophoneValue());
			uBit->display.print(MicroBitImage("255,0,0,0,255\n0,255,0,255,0\n0,0,255,0,0\n0,255,0,255,0\n255,0,0,0,255\n"));	
			}
		}
		
		void tryMicrophone2(){													//Ausgabe der Messdaten; Messwerte????? 
			while (true){
				uBit->display.scroll(uBit->io.P21.getMicrophoneValue());
		                uBit->display.print(" |");
		                uBit->sleep(500);
		
			}
		}
		
		void tryMicrophone3(){													//09.12.
			while(true){
				uBit->display.scroll(uBit->io.P21.getMicrophoneValue());
				if(uBit->io.P21.getMicrophoneValue() > 1){
			//	uBit->display.scroll(uBit->io.P21.getMicrophoneValue());
				uBit->display.print(MicroBitImage("255,0,0,0,255\n0,255,0,255,0\n0,0,255,0,0\n0,255,0,255,0\n255,0,0,0,255\n"));	
				}
			}
		}
		
		void micAuswahl(){
		    while(true){
		    int i = 0;
		    uBit->display.print(i);	
		    for(int x; x<5;x++){
		            if(uBit->io.P21.getMicrophoneValue()>20){
		                uBit->display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
		                uBit->display.print(MicroBitImage("255,0,0,0,255\n0,255,0,255,0\n0,0,255,0,0\n0,255,0,255,0\n255,0,0,0,255\n"));	
		            }
		            else{
		                uBit->sleep(10);
		                i++;
		
		            }
		           
		        }
		    }
		
		}
		//11.11.:Ende
		
		//void holdDistance(){		//Überarbeitet
		//    while(true){
		//            while(_cbGetSampleUltrasonic(buf, i2c)>100){
		//                _cbSetMotors(buf,i2c,100,100);
		//            }
		//            while(_cbGetSampleUltrasonic(buf, i2c)<50){
		//                    _cbSetMotors(buf,i2c,50,50);
		//            }
		//            while(_cbGetSampleUltrasonic(buf, i2c)<10){
		//                _cbSetMotors(buf,i2c,0,0);
		//            }
		//    }
		//}
		
		void holdDistance(){									//18.11. CHECK :ThumbsUp:
			bool b = true;
		    while(b){
		            if (_cbGetSampleUltrasonic(buf, i2c)>50){
		                _cbSetMotors(buf,i2c,100,100);
		            }
		            else if (_cbGetSampleUltrasonic(buf, i2c)>25){
		                _cbSetMotors(buf,i2c,30,30);
		            }
		            else{
		                _cbSetMotors(buf,i2c,0,0);
		                uBit->display.print(ManagedString("W"));
		                b = false;
		
		            }
		    }
		}
		
		void showDistance(){				//2.12.21
			while(!uBit->buttonA.isPressed()){
				uBit->display.scroll(_cbGetSampleUltrasonic(buf, i2c));				
			}
			
		}
		
		void showDirection(){			//Aufgegeben
		    while(true){
			uBit->accelerometer.updateSample();
		    uBit->display.scroll(ManagedString(uBit->compass.heading()));
		    }
		}
		
		void linieFolgen(){
			while(true){
				_cbSetMotors(buf,i2c,30,40);
				if(_cbGetSampleInfrared(buf, i2c, 2)){		//Sensor Links
					_cbSetMotors(buf,i2c,0,30);
					uBit->sleep(5);			
				}
				else if(_cbGetSampleInfrared(buf, i2c, 1)){    //Sensor Rechts
					_cbSetMotors(buf,i2c,30,0);
					uBit->sleep(5);			
		
				}
			}
		}
		
//		void wecker(){
//			int count;
//			while(!uBit->buttonA.isPressed() && !uBit->buttonB.isPressed()){
//				if(uBit->buttonA.isPressed()){
//					count++;
//					count%61;
//					uBit->display.scroll(count);
//				}
//				else if(uBit->buttonB.isPressed()){
//					count++;
//					count%61;
//					uBit->display.scroll(count);
//				}
//						
//			}
//			uBit->sleep(count*1000);
//		    while(!uBit->buttonA.isPressed() || !uBit->buttonB.isPressed()){
//		    _cbSetMotors(buf,i2c,100,100);
//		
//		    }
//		}
		
		void wecker2(){                                //Done
			int count, count2, multiplier = 0;
			uBit->sleep(200);
		
			while(!uBit->buttonB.isPressed()){
				switch(count2%3){
					case 0:
						uBit->display.print("s");
						multiplier = 1000;
						uBit->sleep(100);
						break;
					case 1:
						uBit->display.print("m");
						multiplier = 60000;
						uBit->sleep(100);
						break;
					case 2:
						uBit->display.print("h");
						multiplier = 360000;
						uBit->sleep(100);
						break;
					default:
						uBit->display.scroll("Broken!!");
						break;
				}
				
				if(uBit->buttonA.isPressed()){
					count2++;
					uBit->sleep(100);
				}
			}
			uBit->sleep(2000);
		    uBit->display.scroll(count);
			while(!uBit->buttonB.isPressed()){
				if(uBit->buttonA.isPressed()){
					count++;
					count = count%61;
					uBit->display.scroll(count);
				}
			}
		    uBit->display.print(MicroBitImage("255,0,0,0,255\n0,255,0,255,0\n0,0,255,0,0\n0,255,0,255,0\n255,0,0,0,255\n"));	
		    
		    count = count*multiplier;
		    uBit->sleep(count);
		    uBit->display.print(MicroBitImage("0,0,255,0,0\n0,255,0,255,0\n0,255,255,255,0\n255,0,0,0,255\n255,0,0,0,255\n"));
		    while(!uBit->buttonA.isPressed()){
		        _cbSetMotors(buf,i2c,100,100);
		        uBit->soundmotor.soundOn(261.626); uBit->sleep(2000); uBit->soundmotor.soundOff();
		        uBit->sleep(1000);
		    }
		    _cbSetMotors(buf,i2c,0,0);
		    uBit->display.clear();
		}
		
		void kurve(std::string letter){		//noch testen
			while(!uBit->buttonB.isPressed()){
				if(letter == "l" || letter == "L"){
						_cbSetMotors(buf,i2c,80,100);
				}
				else if(letter == "r" || letter == "R"){
					_cbSetMotors(buf,i2c,100,80);
				}
				else{
		        _cbSetMotors(buf,i2c,100,100);	
				}
			}
			_cbSetMotors(buf,i2c,0,0);
		}
		
		void fahren(int v){			//v = Geschwindigkeit
			if(v > 100 || v < -100){
				uBit->display.print("?");
			}
			else{
				_cbSetMotors(buf,i2c,v,v);
				if(uBit->buttonB.isPressed()){
					_cbSetMotors(buf,i2c,0,0);
				}
			}
		}
		
		void runMenueSelection(){
			int auswahl = 0;
			while(!uBit->buttonB.isPressed()){
					uBit->display.print(ManagedString(auswahl%4));
		            uBit->sleep(100);
		
				if(uBit->buttonA.isPressed()){
					auswahl++;
		
					uBit->display.print(ManagedString(auswahl%4));
		            uBit->sleep(100);
				}
			}
			switch(auswahl%4){
				case 0:
					wecker2();
					uBit->sleep(2000);
					runMenueSelection();
					break;
				case 1: 
					runTemperatureProgram2();
					uBit->sleep(2000);
					runMenueSelection();
					break;
				case 2: 
					holdDistance();
					uBit->sleep(2000);
					runMenueSelection();
					break;
				case 3: 
					linieFolgen();
					uBit->sleep(2000);
					runMenueSelection();
					break;
				default:
					uBit->display.scroll("ERROR  /418:I’m a teapot");
					runMenueSelection();
					break;
			}
		}
};

int main(){

    Roboter meinRoboter;
    meinRoboter.runMenueSelection();
    //meinRoboter.runMoveForward();
    //meinRoboter.micAuswahl();
    //meinRoboter.showDistance();
    //meinRoboter.linieFolgen();
    //meinRoboter.wecker2();
    release_fiber();
}

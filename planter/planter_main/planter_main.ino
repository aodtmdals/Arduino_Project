#include "planter_library.h"
#include "planter_pin_setting.h"
#include "planter_library_setting.h"

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600); 
  DigitShield.begin();
  dht.begin();  

                                                                                /*LED 세팅*/
  pixels.begin();  // 네오픽셀 제어 시작
  pixels.show();  // 네오픽셀 초기화
  
  pinMode(MOTOR, OUTPUT); //motor setting


                                                                                /*센서값 통신 세팅*/
  time_previous = millis();
  time_bluetooth_previous = millis();
}

void loop() {
  
                                                                                  //센서값 갱신 시간(delay를 쓰면 동시 진행 X -> 블루투스 통신에 지연이 생김)
  time_current = millis();

  
                                                                                  /*각종 센서값 받아오기*/
  h = dht.readHumidity();                                                         //습도값을 h에 저장
  t = dht.readTemperature();                                                      //온도값을 t에 저장
  hic = dht.computeHeatIndex(t, h, false);                                        //섭씨 온도값을 hic에 저장
  Touch_State = digitalRead(Touch_Pin);                                           //터치센서 값을 Touch_State에 저장


                                                                                  
                                                                                  /*토양 습도 값 받아와 보정 (1의자리 수를 0으로)*/
  water = analogRead(Soil_PIN);                                                   //토양 습도 센서값 water에 저장
  water = water / 10;                                                             //1의 자리 수를 덜어냄 
  water = water * 10;




  cdsValue = map(analogRead(cds_Pin),0,1023,0,255);                               //조도센서 값을 받아와 0~255까지 값으로 나타낼 수 있게 변환
  dustVal = analogRead(Dust_PIN);                                                 //먼지센서 값 받아와 dustVal에 저장



                    
  bluetoothSignal();                                                              /*bluetooth 값 받아오기*/
  ECSetting();                                                                    /*EC sensor 세팅*/
  ledControl();                                                                   /*led 색 변환*/
  MotorMove();                                                                    /*모터 구동*/



  

                                                                                  /*자동 밝기 조절*/
                                                                                  //보정된 밝기 값을 받아와 밝기 조절
  ledBright();
  BrightR = cdsCorrR;
  BrightG = cdsCorrG;
  BrightB = cdsCorrB;


                                                                                  /*현실시간 1초가 지나면 세븐세그먼트 모니터에 토양습도 값 표기*/
  if(time_current - time_previous >= 1000){
    DigitShield.setPrecision(0);
    DigitShield.setValue(water);
  }

                                                                                  /*2초마다 센서값을 받아와 시리얼 모니터에 표시*/
  if(time_current - time_previous >= 2000){
  printLED();
  printDHT();
  paintEC();
  paintDust();
  Serial.print("Water : ");
  Serial.println(water);

                                                                                    //EC센서값을 세븐세그먼트 모니터에 표기(소수점 둘째자리까지)
  DigitShield.setPrecision(2);
  DigitShield.setValue(ecValue);


  Serial.print("WaterMax : ");
  Serial.println(waterMax);
  
  Serial.println();

                                                                                    //타이머 초기화
  time_previous = time_current;
  }

}

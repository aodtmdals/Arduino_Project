                                                                                      /*LED 제어 함수를 모아둠*/
void ledControl() {
                                                                                      /*터치센서로 LED 색깔 조절*/
  if (Touch_State != Touch_last) {                                                    //터치센서를 한 번 터치할 때마다 색이 변함
    if (Touch_State == HIGH) {
      Touch_count++;
    }
    else {
    }
    delay(10);
  }
  Touch_last = Touch_State;

  bluetoothControl();

  if (Touch_count == 0)                                                                 //LED OFF
  {
    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)  ); // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }
  }

  if (Touch_count == 1)                                                                 //RED
  {
    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color(BrightR, 0, 0)  ); // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }
  }

  if (Touch_count == 2)                                                                  //ORANGE
  {
    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color(BrightR, BrightG, 0) ); // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }
  }

  if (Touch_count == 3)                                                                  //YELLO
  {
    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color(BrightR, BrightG, 0) ); // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }
  }
  if (Touch_count == 4)                                                                  //GREEN
  {
    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color(0, BrightG, 0) ); // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }
  }
  if (Touch_count == 5)                                                                  //BLUE
  {
    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color(0, 0, BrightB) ); // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }
  }
  if (Touch_count  == 6)                                                                //PERPLE
  {
    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color(BrightR, 0, BrightB) ); // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }
  }
  if (Touch_count  == 7)  //WHITE
  {
    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color(BrightR, BrightG, BrightB) ); // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }
  }
  if (Touch_count == 8)                                                                 //LED OFF
  {
    Touch_count = 0;
  }
}

                                                                                          /*Bluetooth를 이용해 LED 값을 바꿔줌*/
                                                                                          /*블루투스 통신으로 특정 값이 들어오면 Touch_count변수 자체를 바꿔 색을 바꾸어준다.*/
void bluetoothControl() {
  if (LED_color == "LED OFF") {
    Touch_count = 0;
  }
  if (LED_color == "RED") {
    Touch_count = 1;
  }
  if (LED_color == "ORANGE") {
    Touch_count = 2;
  }
  if (LED_color == "YELLO") {
    Touch_count = 3;
  }
  if (LED_color == "GREEN") {
    Touch_count = 4;
  }
  if (LED_color == "BLUE") {
    Touch_count = 5;
  }
  if (LED_color == "PERPLE") {
    Touch_count = 6;
  }
  if (LED_color == "WHITE") {
    Touch_count = 7;
  }
}


                                                                                                                  /*LED 밝기 조절 함수*/
void ledBright() {
  if (autoLED == "Auto LED ON") {                                                                                //블루투스 통신을 통해 자동 밝기 조절이 켜지면 실행 (defalut: OFF)
    ledBrightCorr();                                                                                             //LED 밝가 너무 중구난방해지지 않게 보정해주는 함수
    cdsCorrR = cdsCorr;       
    cdsCorrG = cdsCorr;
    cdsCorrB = cdsCorr;
    if (Touch_count == 2) {                                                                                      //ORNGE, YELLO, PERPLE은 R, G, B의 최대 값이 255가 아니기 때문에 각각의 최댓값으로 보정해주는 작업을 거침
      cdsCorrG = map(cdsCorr, 0, 255, 0, 50);
    }
    if (Touch_count == 3) {
      cdsCorrG = map(cdsCorr, 0, 255, 0, 150);
    }
    if (Touch_count == 6) {
      cdsCorrR = map(cdsCorr, 0, 255, 0, 100);
      cdsCorrG = map(cdsCorr, 0, 255, 0, 200);
    }
  }
  else if (autoLED == "Auto LED OFF") {
    cdsCorr = 255;
    cdsCorrR = cdsCorr;
    cdsCorrG = cdsCorr;
    cdsCorrB = cdsCorr;
    if (Touch_count == 2) {
      cdsCorrG = 50;
    }
    if (Touch_count == 3) {
      cdsCorrG = 150;
    }
    if (Touch_count == 6) {
      cdsCorrR = 100;
      cdsCorrB = 200;
    }
  }
  else {
    cdsCorr = 255;
    cdsCorrR = cdsCorr;
    cdsCorrG = cdsCorr;
    cdsCorrB = cdsCorr;
    if (Touch_count == 2) {
      cdsCorrG = 50;
    }
    if (Touch_count == 3) {
      cdsCorrG = 150;
    }
    if (Touch_count == 6) {
      cdsCorrR = 100;
      cdsCorrB = 200;
    }
  }
}

                                                              /*LED 밝기 보정 함수*/
                                                              /*어두워지면 LED 밝기도 덩달아 어두워지게끔 설정해둠*/
void ledBrightCorr() {

  if (cdsValue >= 200) {
    cdsCorr = 50;
  } else if (cdsValue >= 150 && cdsValue < 200) {
    cdsCorr = 80;
  } else if (cdsValue >= 120 && cdsValue < 150) {
    cdsCorr = 100;
  } else if (cdsValue >= 50 && cdsValue < 120) {
    cdsCorr = 150;
  } else if (cdsValue >= 30 && cdsValue < 50) {
    cdsCorr = 200;
  } else if (cdsValue >= 10 && cdsValue < 30) {
    cdsCorr = 255;
  }
}

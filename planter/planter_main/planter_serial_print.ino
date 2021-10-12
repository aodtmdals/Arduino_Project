                                                                                    /*시리얼 모니터에 센서값 출력하는 걸 모아둔 곳*/
void printLED() {
  Serial.print("LED Color : ");
  if (Touch_count == 0 || Touch_count == 8) {
    Serial.println("LED Off");
  } else if (Touch_count == 1) {
    Serial.println("Red");
  } else if (Touch_count == 2) {
    Serial.println("Orange");
  } else if (Touch_count == 3) {
    Serial.println("Yello");
  } else if (Touch_count == 4) {
    Serial.println("Green");
  } else if (Touch_count == 5) {
    Serial.println("Blue");
  } else if (Touch_count == 6) {
    Serial.println("Perple");
  } else if (Touch_count == 7) {
    Serial.println("White");
  }
}

void paintDust() {                                                                       //미세먼지 보정값 출력
  Serial.print("Dust Density : ");
  Serial.print(dustVal);
  Serial.print("ug/m3");
  Serial.print("      ");

  if (dustVal >= 0 && dustVal <= 15) {
    Serial.println("공기질 좋음");
  } else if (dustVal > 15 && dustVal <= 35) {
    Serial.println("공기질 보통");
  } else if (dustVal > 35 && dustVal <= 75) {
    Serial.println("공기질 나쁨");
  } else {
    Serial.println("공기질 매우 나쁨");
  }

}
/*EC 센서 값 나타내기*/
void paintEC() {
  //시리얼 모니터 출력
  Serial.print("EC:");
  Serial.print(ecValue, 2);
  Serial.print("ms/cm");
  Serial.print("                   ");


  if (ecValue >= 1.2) {                                         //EC센서 값 1.2 이상 : 양호
    Serial.println("영양상태 양호");
  } else if (ecValue >= 0.7 && ecValue < 1.2) {                 //EC센서 값 1.2 미만 ~ 0.7 이상 : 주의
    Serial.println("영양상태 주의");
  } else if (ecValue < 0.7) {                                   //EC센서 값 0.7 미만 : 위험
    Serial.println("영양상태 위험");
  }
}

void printDHT() {
  Serial.print("temperature:");
  Serial.print(hic);
  Serial.print(" C deg");
  Serial.print("       ");
  Serial.print(" humidity:");
  Serial.print(h);
  Serial.print(" %");
  Serial.println();
}

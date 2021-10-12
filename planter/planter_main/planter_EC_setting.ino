                                                                                            /*EC 센서 값 보정*/
void ECSetting() {
  EC = analogRead(EC_PIN);                                                                  //EC센서에서 값 받아옴
  static unsigned long timepoint = millis();
  if (millis() - timepoint > 1000U) //time interval: 1s                                     //센서 값 보정
  {
    timepoint = millis();
    voltage = EC / 1024.0 * 5000; // read the voltage
    temperature = hic;          // read your temperature sensor to execute temperature compensation
    ecValue =  ec.readEC(voltage, temperature); // convert voltage to EC with temperature compensation
  }
  ec.calibration(voltage, temperature);         // calibration process by Serail CMD
}

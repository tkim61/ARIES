// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4.
//IO32/T9/OUT1/J4-Tummy, IO33/OUT2/T8/J5-Back, IO27/OUT4/T7/J7-left cheek, IO14/OUT3/T6/J6-right cheek, IO13/T4/OUT5/J8-head


int tum, back, leftCheek, rightCheek, head;

void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");

  
  pinMode(T9, INPUT);
  pinMode(T8, INPUT);
  pinMode(T7, INPUT);
  pinMode(T6, INPUT);
  pinMode(T4, INPUT);

}

void loop()
{
  tum = digitalRead(T9);
  back = digitalRead(T8);
  leftCheek = digitalRead(T7);
  rightCheek = digitalRead(T6);
  head = digitalRead(T4);

  Serial.print(rightCheek);
  Serial.print(',');

  Serial.print(leftCheek);
  Serial.print(',');

  Serial.print(head);
  Serial.print(',');

  Serial.print(back);
  Serial.print(',');

  Serial.print(tum);
  Serial.print('\n');

//  json = {
//    " 
//  }
     

  delay(1000);
  
}

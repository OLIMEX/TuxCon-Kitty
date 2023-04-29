// This displays the name BELLA in morse code
// on the Olimex Kitty badge
// See the morse code reference here https://math.hws.edu/eck/cs225/s03/code.txt

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  l(); s(); s(); s(); //B
  delay(2000);
  s(); //E
  delay(2000);
  s(); l(); s(); s(); //L
  delay(2000);
  s(); l(); s(); s(); //L
  delay(2000);
  s(); l(); //A
  delay(10000);
}

void s()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}

void l()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}

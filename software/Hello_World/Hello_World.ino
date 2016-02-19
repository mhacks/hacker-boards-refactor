//MHR Hello World LED Example

const static int LED_PIN = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Hello World!");

  pinMode(LED_PIN, OUTPUT);
  turn_led_off();

}

void loop() {
  // put your main code here, to run repeatedly:
  turn_led_on();
  Serial.println("Activated LED");
  delay(500);
  turn_led_off();
  Serial.println("Deactivated LED");
  delay(500);
}

void turn_led_on() {
  digitalWrite(LED_PIN, LOW);
}

void turn_led_off() {
  digitalWrite(LED_PIN, HIGH);
}


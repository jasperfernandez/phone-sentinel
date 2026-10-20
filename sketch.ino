#define BUZZER_PIN 25
#define LED_PIN 2
#define BUTTON_PIN 27
#define DISTANCE_PIN 34

const float ALARM_DISTANCE = 3.0;

bool armed = true;
bool alarmActive = false;

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.println();
  Serial.println("==========================");
  Serial.println("      PHONE SENTINEL");
  Serial.println("==========================");
  Serial.println("System started");
  Serial.println("System ARMED");
}

void loop() {

  // Read potentiometer
  int rawValue = analogRead(DISTANCE_PIN);

  // Convert potentiometer to 0-6 meters
  float distance = (rawValue / 4095.0) * 6.0;

  Serial.print("Distance: ");
  Serial.print(distance, 2);
  Serial.println(" m");

  // Phone is safe
  if (distance < ALARM_DISTANCE) {

    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    alarmActive = false;

    Serial.println("Status: SAFE");
  }

  // Phone is too far
  else {

    digitalWrite(LED_PIN, HIGH);

    if (!alarmActive) {

      Serial.println("!!! PHONE TOO FAR !!!");
      Serial.println("!!! ALARM !!!");

      alarmActive = true;
    }

    // Make buzzer sound
    tone(BUZZER_PIN, 2000);
  }

  // Button toggles armed state
  if (digitalRead(BUTTON_PIN) == LOW) {

    delay(50);

    if (digitalRead(BUTTON_PIN) == LOW) {

      armed = !armed;

      if (!armed) {

        noTone(BUZZER_PIN);
        digitalWrite(LED_PIN, LOW);

        Serial.println("SYSTEM DISARMED");

      } else {

        Serial.println("SYSTEM ARMED");
      }

      while (digitalRead(BUTTON_PIN) == LOW) {
        delay(10);
      }
    }
  }

  if (!armed) {
    noTone(BUZZER_PIN);
    digitalWrite(LED_PIN, LOW);
  }

  delay(500);
}
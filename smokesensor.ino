const int GAS_PIN = 46;
const int LED_PIN = 9;
const int TONE_PIN = 15;

// The ESP32 has 16 channels which can generate 16 independent waveforms
// We'll just choose PWM channel 0 here
const int TONE_PWM_CHANNEL = 0;
const int PWM_FREQUENCY = 5000;  // 5 kHz frequency for the PWM
const int PWM_RESOLUTION = 8;    // 8-bit resolution for the PWM (range: 0-255)

void setup() {
    Serial.begin(115200);

    // Attach the pin to the LEDC channel with frequency and resolution
    bool success = ledcAttach(TONE_PIN, PWM_FREQUENCY, PWM_RESOLUTION);  // Use ledcAttach
    if (!success) {
        Serial.println("LEDC attach failed");
        while (1); // Stop execution if there's an error
    }

    pinMode(GAS_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    //stores the gas level read to a variable
    int gasLevel = analogRead(GAS_PIN);

    Serial.print("Gas Level: ");
    Serial.print(gasLevel);
    Serial.print("\t");
    Serial.print("\t");

    //checks if the read gas levels exceeds the set value(1000)
    if (gasLevel > 300) {
        Serial.println("Gas");
        digitalWrite(LED_PIN, HIGH); // Turn LED on
        ledcWriteTone(TONE_PWM_CHANNEL, NOTE_C);  // Play a tone on the channel
        delay(1000);
        digitalWrite(LED_PIN, LOW);  // Turn LED off
    } else {
        Serial.println("No Gas");
    }

    delay(100);
}

#include <IRremote.hpp>

const int IR_RECEIVE_PIN = 7;
const int ledPin1 = 8;
const int ledPin2 = 9;
const int ledPin3 = 10;

void setup() {
  Serial.begin(9600);

  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
}

void loop() {
  /*
     * Check if received data is available and if yes, try to decode it.
     * Decoded result is in the IrReceiver.decodedIRData structure.
     *
     * E.g. command is in IrReceiver.decodedIRData.command
     * address is in command is in IrReceiver.decodedIRData.address
     * and up to 32 bit raw data in IrReceiver.decodedIRData.decodedRawData
     */
  if (IrReceiver.decode()) {

    /*
    * Print a short summary of received data
    */
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();

    /*
    * !!!Important!!! Enable receiving of the next value,
    * since receiving has stopped after the end of the current received data packet.
    */
    IrReceiver.resume();  // Enable receiving of the next value

    /*
    * Finally, check the received data and perform actions according to the received command
    */
    if (IrReceiver.decodedIRData.command == 0xA) {
      digitalWrite(ledPin1, HIGH);
      delay(2000);
      digitalWrite(ledPin1, LOW);
      Serial.println("1");
    } else if (IrReceiver.decodedIRData.command == 0x1B) {
      digitalWrite(ledPin2, HIGH);
      delay(2000);
      digitalWrite(ledPin2, LOW);
      Serial.println("2");
    } else if (IrReceiver.decodedIRData.command == 0x1F) {
      digitalWrite(ledPin3, HIGH);
      delay(2000);
      digitalWrite(ledPin3, LOW);
      Serial.println("3");
    }else if (IrReceiver.decodedIRData.command == 0x12) { //All LEDs or power button
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
      delay(2000);
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      Serial.println("All");
    }
  }
}

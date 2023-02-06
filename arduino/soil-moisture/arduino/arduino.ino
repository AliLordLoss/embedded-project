#define moistureLED 6
#define sensorPinMoisture A0
int miostureThreshold = 20;


#define  gasLED 7
#define sensorPinGas A1
int gasThreshold = 250;

int moisture = 0;
int gas = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);

  Serial1.println("moisture: " + String(moisture));
  Serial1.println("gas: " + String(gas));

  pinMode(sensorPinMoisture, INPUT);
  pinMode(moistureLED, OUTPUT);
  
  pinMode(sensorPinGas, INPUT);
  pinMode(gasLED, OUTPUT);
  
  digitalWrite(moistureLED, LOW);
  digitalWrite(gasLED, LOW);

  Serial.println("MQ5 Heating Up!");
  delay(20000); // allow the MQ5 to warm up
}

void loop() {
  int newMoisture = readSensorMoisture();
  if (newMoisture != moisture) {
    moisture = newMoisture;
    Serial1.println("moisture: " + String(moisture));
  }
  
  int newGas = readSensorGas();
  if (newGas != gas) {
    gas = newGas;
    Serial1.println("gas: " + String(gas));
  }

  Serial.println("");
  delay(10000);
}


//  This function returns the analog data to calling function
int readSensorMoisture() {
  int outputValue= analogRead(sensorPinMoisture);
  Serial.print("Moisture Sensore Value = ");
  Serial.println(outputValue);
  outputValue = map(outputValue,1023,10,0,100);
  Serial.print("Mositure = ");
  Serial.print(outputValue);
  Serial.println("%");
  if (outputValue < miostureThreshold)
    digitalWrite(moistureLED, HIGH);
  else
    digitalWrite(moistureLED, LOW);
  return outputValue;             // Return analog moisture value
}

int readSensorGas() {
  int gasValue = analogRead(sensorPinGas);
  Serial.print("Gas Sensor Value = ");
  Serial.print(gasValue);
  Serial.println(" ppm");

  if (gasValue > gasThreshold) {
    digitalWrite(gasLED, HIGH);
  }
  else { 
    digitalWrite(gasLED, LOW);
  }
  return gasValue;
}

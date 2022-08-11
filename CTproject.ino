#include <DHT.h> /* Librería para el sensor DHT11 */
#define DHTTYPE DHT11 /* Definimos el tipo de sensor */

#define sensor_humedad_pin A0 /* Sensor de humedad de tierra en el pin A0 */
#define fotorresistor_pin A5 /* Fotorresistor en el pin A5 */

int pinDHT11 = 2; /* Sensor de humedad y temperatura en el pin 2 */
DHT dht(pinDHT11,DHTTYPE);

int fotorresistor_value = 0; /* valor de la fotorresistencia */
int agua_pin = 3; /* Bomba o valvula de agua conectada en el pin 3 */
int agua_speed = 255; /* Velocidad a la que trabajará la bomba o valvula */ 
                      /* Este valor dependerá del tipo de bomba que utilicemos 
                       * y la cantidad de flujo de agua que se quiera
                       */
void setup(){
  Serial.begin(9600);
  dht.begin();

}

void loop(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
      //Serial.println("Error");
      //return;
  }

  int valor_humedad_tierra = map(analogRead(sensor_humedad_pin), 0, 1023, 100, 0);
  int fotorresistor_value = map(analogRead(fotorresistor_pin), 0, 1023, 100, 0);

  /* Monitoreo de valores */
  Serial.println(" ");
  Serial.println("Humedad: ");
  Serial.println(h);  /* Imprimimos valor de humedad */
  Serial.println(" %\t ");
  Serial.println("Temperatura: ");
  Serial.println(t);  /* Imprimimos el valor de la temperatura */
  Serial.println(" *C ");

  Serial.println("Humedad en el suelo: ");
  Serial.println(valor_humedad_tierra);
  Serial.println("%");

  Serial.println("Luz: ");
  Serial.println(fotorresistor_value);
  Serial.println("%");

  /*Esta parte corresponde a la configuración de las condiciones de riego con los datos
   * obtenidos.
   * El sistema de riego se activa si:
   *  - La humedad en el suelo es igual o menor al 50%
   *  - La luminosidad es inferior al 30%
   *  - La temperatura es inferior al 30%
   */
   /*if(valor_humedad_tierra <= 50 && fotorresistor_value < 30 && t < 30){*/
   if(valor_humedad_tierra <= 50 && fotorresistor_value < 30){
    digitalWrite(agua_pin, HIGH);
    analogWrite(agua_pin, agua_speed);
   }
    else{
      digitalWrite(agua_pin, LOW);
    }
   delay(2000);
}

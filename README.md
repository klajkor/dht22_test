# DHT22 Test Example

This test code shows how to use DHT22/AM2302 temperature and humidity sensor.
Code is based on 
 *  Ricardo Timmermann's DHT22 library (https://github.com/gosouth/DHT22) 
 * and Jonathan Hartsuiker <https://github.com/jsuiker> & Ruslan V. Uss <unclerus@gmail.com> dht library (https://github.com/UncleRus/esp-idf-lib/tree/master/components/dht).

## Framework
 * ESP-IDF + FreeRTOS

## GPIO functions:

 * GPIO27: DHT22 data pin
 
## Test:
 * Connect DHT22 data pin with proper pull-up resistor (e.g. 4,7 kohm) to GPIO27
 
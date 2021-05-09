/**
 * Brief:
 * This test code shows how to use DHT22/AM2302 temperature and humidity sensor.
 * Code is based on 
 *  Ricardo Timmermann's DHT22 library (https://github.com/gosouth/DHT22) 
 *  and Jonathan Hartsuiker <https://github.com/jsuiker> & Ruslan V. Uss <unclerus@gmail.com> dht library (https://github.com/UncleRus/esp-idf-lib/tree/master/components/dht).
 *
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp32/rom/ets_sys.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "dht.h"
#include "DHT22.h"

#define DHT_GPIO_PIN 27

void DHT_task(void *pvParameter)
{
	float dht_temp_val;
	float dht_humi_val;
	printf( "Starting DHT Task\n\n");
	// Required for DHT22 library:
	setDHTgpio( DHT_GPIO_PIN );
	
	while(1) {
	
		dht_temp_val=0;
		dht_humi_val=0;
		printf(">>>--- Reading DHT via dht library ---\n" );
		dht_read_float_data(DHT_TYPE_AM2301, DHT_GPIO_PIN, &dht_humi_val, &dht_temp_val);
		printf( ">>>--- Temp: %.1f", dht_temp_val );
		printf( "  Hum: %.1f\n\n", dht_humi_val );
		// -- wait at least 2 sec before reading again ------------
		vTaskDelay( 5000 / portTICK_RATE_MS );

		printf("=== Reading DHT via DHT22 library ===\n" );
		int ret = readDHT();
		errorHandler(ret);
		printf( "=== Temp: %.1f", getTemperature() );
		printf( "  Hum: %.1f\n\n", getHumidity() );
		// -- wait at least 2 sec before reading again ------------
		vTaskDelay( 5000 / portTICK_RATE_MS );
		
	}
}

void app_main()
{
	nvs_flash_init();
	vTaskDelay( 1000 / portTICK_RATE_MS );
	xTaskCreate( &DHT_task, "DHT_task", 2048, NULL, 5, NULL );
}


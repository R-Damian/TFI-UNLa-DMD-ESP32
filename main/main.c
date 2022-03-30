/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"


#include "esp_wifi.h"
#include "nvs_flash.h"

#include "esp_log.h"
#include "freertos/event_groups.h"
#include "esp_http_client.h"

#include "adc/ads1115/ads1115.h"
#include "sensors/lm35/lm35.h"
#include "sensors/mock/mock_sensor.h"
#include "data_transmitter.h"



#include "wifi.h"


void app_main(void)
{

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    wifi_init_sta("SSID", "PASSWORD");



    ads1155_t * pAds1115= ads1115Init(0, 0x4A, 27, 26);
    lm35_t * pLm35 = lm35Init(pAds1115, ads1115GenericRead, 0);

    mock_sensor_t * pMockSensor1 = mockSensorInit(70);
    mock_sensor_t * pMockSensor2 = mockSensorInit(50);
    mock_sensor_t * pMockSensor3 = mockSensorInit(220);


    dataTransmitterInit();
    dataTransmitterRegisterSensor("temperaturaAmbiente", pLm35, lm35GenericRead);
    dataTransmitterRegisterSensor("temperaturaMotor", pMockSensor1, mockSensorGenericRead);
    dataTransmitterRegisterSensor("presion", pMockSensor2, mockSensorGenericRead);
    dataTransmitterRegisterSensor("voltaje", pMockSensor3, mockSensorGenericRead);


    dataTransmitterStart();

}



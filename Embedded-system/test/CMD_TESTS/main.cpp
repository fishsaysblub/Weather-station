#include "unity.h"

#include <CMDData.h>
#include "freertos/FreeRTOS.h"

extern "C" void app_main();

void GarbageTest();
void ConfigureCMD(CMDData * data, uint8_t* buffer, const int output_len);

void app_main(void)
{
    UNITY_BEGIN();

    RUN_TEST(GarbageTest);

    UNITY_END();
};

void GarbageTest()
{
    uint32_t hpSize = esp_get_free_heap_size();

    CMDData* data = new CMDData();
    uint8_t data_buffer[] = {0xF3};
    ConfigureCMD(data, data_buffer, 2);
    delete data;   

    TEST_ASSERT_TRUE(hpSize == esp_get_free_heap_size());
    
}

void ConfigureCMD(CMDData * data, uint8_t* buffer, const int output_len)
{
    data->Address = 0x40;
    data->Buffer = (uint8_t *)buffer;
    data->Len = sizeof(data) / sizeof(uint8_t);

    data->OutputBuffer = (uint8_t*)calloc(output_len, sizeof(uint8_t));
    data->OutputLen = output_len;
}

adc_oneshot_unit_handle_t adc1_handle;

adc_cali_handle_t adc1_cali_handle;


spi_device_handle_t spi_handle;

Void app_main(void) {

    spi_bus_config spi_bus_init = {
    .mosi_io_num = PIN_NUM_MOSI,
    .miso_io_num = PIN_NUM_MISO,
    .sclk_io_num = PIN_NUM_SCLK,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1

    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };
    adc_oneshot_new_unit(&init_config, &adc1_handle);

    adc_oneshot_chan_cfg_t chan_config = {
        .atten = ADC_ATTEN_DB_18,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_6, &chan_config);

    int raw;
    adc_oneshot_read(adc1_handle, ADC_CHANNEL_6, &raw);

    timer_config_t timer_config = { 
        .divider = 80, // 1 us per tick
        .counter_dir = TIMER_COUNT_UP,
        .counter_en = TIMER_PAUSE,
        .alarm_en = TIMER_ALARM_EN,
    }

    
}



void mcp4132_read_register (uint8_t reg_addr, uint8_t *data) {
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 16; // es de 16 bits el mensaje
    t.tx_buffer = (uint8_t[]){0x00 | (reg_addr & 0x7F), 0x00}; 
    t.rx_buffer = data; // Buffer to store the read data

    spi_device_transmit(spi_handle, &t);
}

void mcp4132_write_register (uint8_t reg_addr, uint8_t value) {
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 16; 
    t.tx_buffer = (uint8_t[]){0x80 | (reg_addr & 0x7F), value}; 
}


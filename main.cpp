#include "mbed.h"

//Serial pc(USBTX, USBRX);
RawSerial device(UART1_TX, UART1_RX);
char message;

namespace {
#define PERIOD_MS 1000
}

static DigitalOut led1(LED1);
static AnalogIn adc_hum(PC_2);
I2C i2c(I2C1_SDA, I2C1_SCL);
uint8_t lm75_adress = 0x48 << 1;




// main() runs in its own thread in the OS
// (note the calls to Thread::wait below for delays)
int main()
{
	while(1){
		char cmd[2];
		cmd[0] = 0x00;
		i2c.write(lm75_adress, cmd, 1);
		i2c.read(lm75_adress, cmd, 2);

		float measure = adc_hum.read();
		float hum = (measure - 0) * 100.0 / (3.3 - 0);
		float temperature = ((cmd[0] << 8 | cmd[1] ) >> 7) * 0.5;




		printf("Humidité = %f pourcent \n", hum*3.3);
		printf("Temperature : %f\n", temperature);
		wait(1);

	}
}

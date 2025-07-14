#include "project_config.h"

void initSPI3(bool mode, uint8_t dataFrameFormat, uint16_t clkPrescaler);
uint16_t writeSPI3(uint16_t TxData);								//for master
void writeTxBufSPI3(uint16_t TxData);						//for slave
uint16_t readRxBufSPI3();								//for slave
bool SPIAvailable3();

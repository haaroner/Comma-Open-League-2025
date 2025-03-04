#include "SPI3_DOT.h"

uint16_t _RxData3[2];
bool _available3[2];
uint8_t num3 = 1;

void initSPI3(bool mode, uint8_t dataFrameFormat, uint16_t clkPrescaler)
{
  _RxData3[num3] = 0;														
	_available3[num3] = 0;
	
	SPI_TypeDef *spi;
	uint8_t afNumber = 5;
  
  spi = SPI3;
	RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;

  if(mode == 1)
  {
    spi->CR1 &= ~SPI_CR1_BR;
    
    switch(clkPrescaler){
			case 4: spi->CR1 |= SPI_CR1_BR_0; break;
			case 8: spi->CR1 |= SPI_CR1_BR_1; break;
			case 16: spi->CR1 |= SPI_CR1_BR_1 | SPI_CR1_BR_0; break;
			case 32: spi->CR1 |= SPI_CR1_BR_2; break;
			case 64: spi->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_0; break;
			case 128: spi->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1; break;
			case 256: spi->CR1 |= SPI_CR1_BR; break;
		}	
    spi->CR1 |= SPI_CR1_SSM;
		spi->CR1 |= SPI_CR1_SSI;
  }
  
  if(dataFrameFormat == 16) spi->CR1 |= SPI_CR1_DFF;		
	else spi->CR1 &= ~SPI_CR1_DFF;
  
  spi->CR1 &= ~SPI_CR1_CPOL;						
	spi->CR1 &= ~SPI_CR1_CPHA;
  
  spi->CR1 &= ~SPI_CR1_LSBFIRST;		
  
  if(mode == 0)spi->CR2 |= SPI_CR2_RXNEIE;
  
  if(mode == 1)spi->CR1 |= SPI_CR1_MSTR;		
	else spi->CR1 &= ~SPI_CR1_MSTR;
  
  spi->CR1 |= SPI_CR1_SPE;	
}


uint16_t writeSPI3(uint16_t TxData){						//for master
	
	//select SPI register name
	SPI_TypeDef * spi;								
	spi = SPI3;
	
	//write data
	while(!(spi->SR & SPI_SR_TXE));		
	spi->DR = TxData;
	
	//read data
	while(!(spi->SR & SPI_SR_RXNE));
	return spi->DR;		
	
}

void writeTxBufSPI3(unsigned int num, uint16_t TxData){					//for slave
	
	//select SPI register name
	SPI3->DR = TxData;
	
}


uint16_t readRxBufSPI3(unsigned int num){
	
	_available3[num] = 0;
	return _RxData3[num];
	
}

bool SPIAvailable3(unsigned int num){
		return _available3[num];
}

void SPIInterruptHandler3(unsigned int num){					//actual interrupt handler
	
	//select SPI register name
	SPI_TypeDef * spi;								
	spi = SPI3;
	
	if(spi->SR & SPI_SR_RXNE){
		_RxData3[num] = spi->DR;
		_available3[num] = 1;
	}
	
}



/************************************ interrupt handlers ************************************/


#ifdef __cplusplus
extern "C"{
#endif

void SPI3_IRQHandler(void) {
	SPIInterruptHandler3(2);//_spi3 = 2
}

#ifdef __cplusplus
}
#endif
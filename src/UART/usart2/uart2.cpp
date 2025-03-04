#include "usart2.h"

extern "C"
{
	void USART2_IRQHandler(void)
	{
		volatile uint8_t data = USART2->SR;
		if(data & USART_SR_RXNE)
		{
			usart2::rx[usart2::_rxCnt] = USART2->DR;
			usart2::_rxCnt++;
			if(usart2::_rxCnt == 25)
			{
				usart2::_rxCnt = 0;
			}
		}
		if(data &USART_SR_TC)
		{
			USART_ClearITPendingBit(USART2, USART_IT_TC);
			if(usart2::_txCnt != 0)
			{
				(USART2->DR) = usart2::tx[usart2::_sendCnt];
				usart2::_sendCnt++;
				if(usart2::_sendCnt == 25)
				{
					usart2::_sendCnt = 0;
				}
			}
			else
			{
				usart2::flag = 1;
			}
		}
		if(USART2 -> SR & USART_SR_ORE)
		{
			uint8_t a = USART2 -> DR;
			(void)a;
		}
	}
}

namespace usart2
{
  volatile uint8_t tx[25];
  volatile uint8_t rx[25];
  volatile uint16_t _rxCnt;
  volatile uint16_t _txCnt;
  volatile bool flag;
  volatile uint16_t _readCnt;
  volatile uint16_t _sendCnt;
  
	
	void usart2Init(uint32_t speed, uint8_t word_length, float stop_bits)
		{
		flag = 1;
		_txCnt = 0;
		_rxCnt = 0;
		_readCnt = 0;
		_sendCnt = 0;
      
    rx[0] = 0;  

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		USART_InitTypeDef u;
		u.USART_BaudRate = speed;
    
    if(word_length == 9) u.USART_WordLength = USART_WordLength_9b;
    else u.USART_WordLength = USART_WordLength_8b;

    if(stop_bits == 2) u.USART_StopBits = USART_StopBits_2;
    else if(stop_bits == 0.5) u.USART_StopBits = USART_StopBits_0_5;
    else if(stop_bits == 1.5) u.USART_StopBits = USART_StopBits_1_5;
    else u.USART_StopBits = USART_StopBits_1;
      
		u.USART_Parity = USART_Parity_No;
		u.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		u.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART2, &u);
		USART_ITConfig(USART2, USART_IT_TC, ENABLE);
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
		USART_Cmd(USART2, ENABLE);
		NVIC_SetPriority(USART2_IRQn, 0);
		NVIC_EnableIRQ(USART2_IRQn);
	}  
		 
	uint16_t read()
	{  
		uint16_t dt;
		ENTER_CRITICAL_SECTION();
		dt = rx[_readCnt];
		_readCnt++;
		if(_readCnt == 25)
		{
		 _readCnt = 0;
		}
		EXIT_CRITICAL_SECTION();
		return dt;
	}  
		 
	uint16_t available()
	{  
		uint16_t size;
		ENTER_CRITICAL_SECTION();
		size = _rxCnt - _readCnt;
		EXIT_CRITICAL_SECTION();
		return size;
	}  
		 
	void write(uint8_t _byte)
	{  
		ENTER_CRITICAL_SECTION();
		if(!flag)
		{
		 tx[_txCnt] = _byte;
		 _txCnt++;
		 if(_txCnt == 25)
		 {
		 _txCnt = 0;
		 }
		}
		else
		{
		 flag = 0;
		 (USART2->DR) = _byte;
		}
		EXIT_CRITICAL_SECTION();
	}
}

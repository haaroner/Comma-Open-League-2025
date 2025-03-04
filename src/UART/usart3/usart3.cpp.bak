#include "usart3.h"

extern "C"
{
	void USART3_IRQHandler(void)
	{
		volatile uint8_t data = USART3->SR;
		if(data & USART_SR_RXNE)
		{
			usart3::rx[usart3::_rxCnt] = USART3->DR;
			usart3::_rxCnt++;
			if(usart3::_rxCnt == 8)
			{
				usart3::_rxCnt = 0;
			}
		}
		if(data &USART_SR_TC)
		{
			USART_ClearITPendingBit(USART3, USART_IT_TC);
			if(usart3::_txCnt != 0)
			{
				(USART3->DR) = usart3::tx[usart3::_sendCnt];
				usart3::_sendCnt++;
				if(usart3::_sendCnt == 8)
				{
					usart3::_sendCnt = 0;
				}
			}
			else
			{
				usart3::flag = 1;
			}
		}
		if(USART3->SR & USART_SR_ORE)
		{
			uint8_t a = USART3 -> DR;
			(void)a;
		}
	}
}

namespace usart3
{
  volatile uint8_t tx[8];
  volatile uint8_t rx[8];
  volatile uint16_t _rxCnt;
  volatile uint16_t _txCnt;
  volatile bool flag;
  volatile uint16_t _readCnt;
  volatile uint16_t _sendCnt;
	
	void usart3Init(uint32_t speed, uint8_t word_length, float stop_bits)
	{
		flag = 1;
		_txCnt = 0;
		_rxCnt = 0;
		_readCnt = 0;
		_sendCnt = 0;
      
    rx[0] = 0;  

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
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
		USART_Init(USART3, &u);
		USART_ITConfig(USART3, USART_IT_TC, ENABLE);
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		USART_Cmd(USART3, ENABLE);
		NVIC_SetPriority(USART3_IRQn, 0);
		NVIC_EnableIRQ(USART3_IRQn);
	}  
		 
	uint16_t read()
	{  
		uint16_t dt;
		ENTER_CRITICAL_SECTION();
		dt = rx[_readCnt];
		_readCnt++;
		if(_readCnt == 8)
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
		 if(_txCnt == 8)
		 {
		 _txCnt = 0;
		 }
		}
		else
		{
		 flag = 0;
		 (USART3->DR) = _byte;
		}
		EXIT_CRITICAL_SECTION();
	}
}

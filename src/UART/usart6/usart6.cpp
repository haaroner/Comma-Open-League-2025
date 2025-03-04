#include "usart6.h"

extern "C"
{
	void USART6_IRQHandler(void)
	{
		volatile uint8_t data = USART6->SR;
		if(data & USART_SR_RXNE)
		{
			usart6::rx[usart6::_rxCnt] = USART6->DR;
			usart6::_rxCnt++;
			if(usart6::_rxCnt == 16)
			{
				usart6::_rxCnt = 0;
			}
		}
		if(data &USART_SR_TC)
		{
			USART_ClearITPendingBit(USART6, USART_IT_TC);
			if(usart6::_txCnt != 0)
			{
				(USART6->DR) = usart6::tx[usart6::_sendCnt];
				usart6::_sendCnt++;
				if(usart6::_sendCnt == 16)
				{
					usart6::_sendCnt = 0;
				}
			}
			else
			{
				usart6::flag = 1;
			}
		}
		if(USART6->SR & USART_SR_ORE)
		{
			uint8_t a = USART6 -> DR;
			(void)a;
		}
	}
}

namespace usart6
{
  volatile uint8_t tx[16];
  volatile uint8_t rx[16];
  volatile uint16_t _rxCnt;
  volatile uint16_t _txCnt;
  volatile bool flag;
  volatile uint16_t _readCnt;
  volatile uint16_t _sendCnt;
	
    void usart6Init(uint32_t speed, uint8_t word_length, float stop_bits)
		{
		flag = 1;
		_txCnt = 0;
		_rxCnt = 0;
		_readCnt = 0;
		_sendCnt = 0;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
		USART_InitTypeDef u;
		u.USART_BaudRate = speed;
    
    if(word_length == 9) u.USART_WordLength = USART_WordLength_9b;
    else u.USART_WordLength = USART_WordLength_8b;

    if(stop_bits == 2) u.USART_StopBits = USART_StopBits_2;
    else if(stop_bits == 0.5) u.USART_StopBits = USART_StopBits_0_5;
    else if(stop_bits == 1.5) u.USART_StopBits = USART_StopBits_1_5;
    else u.USART_StopBits = USART_StopBits_1;
		u.USART_WordLength = USART_WordLength_8b;
		u.USART_StopBits = USART_StopBits_1;
		u.USART_Parity = USART_Parity_No;
		u.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		u.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART6, &u);
		USART_ITConfig(USART6, USART_IT_TC, ENABLE);
		USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
		USART_Cmd(USART6, ENABLE);
		NVIC_SetPriority(USART6_IRQn, 0);
		NVIC_EnableIRQ(USART6_IRQn);
	}  
		 
	uint16_t read()
	{  
		uint16_t dt;
		ENTER_CRITICAL_SECTION();
		dt = rx[_readCnt];
		_readCnt++;
		if(_readCnt == 16)
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
		 if(_txCnt == 16)
		 {
		 _txCnt = 0;
		 }
		}
		else
		{
		 flag = 0;
		 (USART6->DR) = _byte;
		}
		EXIT_CRITICAL_SECTION();
	}
}

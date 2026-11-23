#include "usart4.h"

extern "C" void UART4_IRQHandler(void)
{
  if(USART_GetITStatus(UART4, USART_IT_TXE) == SET)
  {
    if(usart4::_bytesToSend > 0)
    {
      --usart4::_bytesToSend;
      USART_SendData(UART4, usart4::tx[usart4::_sendCnt++]);
      if(usart4::_sendCnt == 30)
        usart4::_sendCnt = 0;
    }
    else
    {
       USART_ITConfig(UART4, USART_IT_TXE, DISABLE);
    }
  }
  
  if(USART_GetITStatus(UART4, USART_IT_RXNE) == SET)
  {
    usart4::_tets = 1;
    if((UART4->SR & (USART_FLAG_NE || USART_FLAG_FE || USART_FLAG_PE || USART_FLAG_ORE)) != 0)
    {
      USART_ReceiveData(UART4);//skip byte
    }
    else
    {
      usart4::_bytesToRead++;
      usart4::rx[usart4::_rxCnt] = USART_ReceiveData(UART4);
      
      usart4::_rxCnt++;
      if(usart4::_rxCnt == 30)
        usart4::_rxCnt = 0;
    }
  }
}

namespace usart4
{
  volatile uint8_t tx[30];
  volatile uint8_t rx[30];
  volatile uint16_t _rxCnt;
  volatile uint16_t _txCnt;
  volatile bool flag;
  volatile uint16_t _readCnt;
  volatile uint16_t _sendCnt;
  volatile uint8_t _bytesToSend;
  volatile uint8_t _bytesToRead;
  volatile uint32_t _tets;
  volatile bool _receiver_buffer_overflow_warning;
  
	
    void usart4Init(uint32_t speed, uint8_t word_length, float stop_bits)
		{
		flag = 1;
		_txCnt = 0;
		_rxCnt = 0;
		_readCnt = 0;
		_sendCnt = 0;
    _bytesToSend = 0;
    _bytesToRead = 0;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
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
		u.USART_Mode =  USART_Mode_Rx;
		u.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(UART4, &u);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //?????? ????????? ? ??????
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //?????? ????????? ? ?????????
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //????????? ??????????
    NVIC_Init(&NVIC_InitStructure); //??????????????
    USART_Cmd(UART4, ENABLE);
    USART_ITConfig(UART4, USART_IT_TXE, DISABLE);
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	}  
		 
	uint16_t read()
	{  
		uint16_t dt;
		ENTER_CRITICAL_SECTION();
		dt = rx[_readCnt];
    if(_bytesToRead > 0)
    {
      _readCnt++;
      _bytesToRead--;
    }
		if(_readCnt == 30)
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
		return _bytesToRead;
	}  
		 
	void write(uint8_t _byte)
	{  
    //while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);
    //USART_SendData(USART6,_byte);
		ENTER_CRITICAL_SECTION();
    if(_bytesToSend < 29)
    {
      USART_ITConfig(UART4, USART_IT_TXE, ENABLE);
		 tx[_txCnt] = _byte;
		 _txCnt++;
      _bytesToSend += 1;
		 if(_txCnt == 30)
		 {
		 _txCnt = 0;
		 }
   }
		EXIT_CRITICAL_SECTION();
	}
}

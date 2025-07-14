
#include "usart3.h"

extern "C" void USART3_IRQHandler(void)
{
  if(USART_GetITStatus(USART3, USART_IT_TXE) == SET)
  {
    if(usart3::_bytesToSend > 0)
    {
      --usart3::_bytesToSend;
      USART_SendData(USART3, usart3::tx[usart3::_sendCnt++]);
      if(usart3::_sendCnt == 99)
        usart3::_sendCnt = 0;
    }
    else
    {
      USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
    }
  }
  
  if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
  {
    usart3::_tets = 1;
    if((USART3->SR & (USART_FLAG_NE || USART_FLAG_FE || USART_FLAG_PE || USART_FLAG_ORE)) != 0)
    {
      USART_ReceiveData(USART3);//skip byte
    }
    else
    {
      usart3::rx[usart3::_rxCnt] = USART_ReceiveData(USART3);
      
      //if write counter reached read, and not read counter reached write
      if((usart3::_receiver_buffer_overflow_warning == true) && (usart3::_readCnt == usart3::_rxCnt))
        usart3::_readCnt++;
      if(usart3::_readCnt == 99)
        usart3::_readCnt = 0;
      
      if(usart3::_readCnt > usart3::_rxCnt)//if write counter can reach read cnt
        usart3::_receiver_buffer_overflow_warning = true;
      else
        usart3::_receiver_buffer_overflow_warning = false;
      
      usart3::_rxCnt++;
      if(usart3::_rxCnt == 99)
        usart3::_rxCnt = 0;
    }
  }
}

namespace usart3
{
  volatile uint8_t tx[100];
  volatile uint8_t rx[100];
  volatile uint16_t _rxCnt;
  volatile uint16_t _txCnt;
  volatile bool flag;
  volatile uint16_t _readCnt;
  volatile uint16_t _sendCnt;
  volatile uint8_t _bytesToSend;
  volatile uint32_t _tets;
  volatile bool _receiver_buffer_overflow_warning;
  
	
    void usart3Init(uint32_t speed, uint8_t word_length, float stop_bits)
		{
		flag = 1;
		_txCnt = 0;
		_rxCnt = 0;
		_readCnt = 0;
		_sendCnt = 0;
    _bytesToSend = 0;
    _receiver_buffer_overflow_warning = false;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
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
		u.USART_Mode =  USART_Mode_Rx | USART_Mode_Tx;
		u.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART3, &u);
////		USART_ITConfig(USART3, USART_IT_TC, ENABLE);
////		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
////		USART_Cmd(USART3, ENABLE);
////		NVIC_SetPriority(USART3_IRQn, 0);
////		NVIC_EnableIRQ(USART3_IRQn);

 NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //?????? ????????? ? ??????
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //?????? ????????? ? ?????????
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //????????? ??????????
  NVIC_Init(&NVIC_InitStructure); //??????????????
  USART_Cmd(USART3, ENABLE);
  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  
	}  
		 
	uint16_t read()
	{  
		uint16_t dt;
		ENTER_CRITICAL_SECTION();
		dt = rx[_readCnt];
		_readCnt++;
		if(_readCnt == 99)
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
    if(_bytesToSend < 99)
    {
      USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
		 tx[_txCnt] = _byte;
		 _txCnt++;
      _bytesToSend += 1;
		 if(_txCnt == 99)
		 {
		 _txCnt = 0;
		 }
   }
		EXIT_CRITICAL_SECTION();
	}
  
  void reset_uart()
  {
    _bytesToSend = 0;
  }
  
//void write(uint8_t _byte)
//{
  //while(!(USART3->SR & USART_SR_TC)); //???????? ?????????? ???????? ?????????? ??????
  ///USART3->DR = _byte; //???????? ??????
//}
  
//  void write(uint8_t _byte)
//{
//while (_bytesToSend == 30);
//USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
//if (_bytesToSend || (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET))
//   {
//   tx[_txCnt++]=_byte;
//   if (_txCnt == 30) _txCnt=0;
//   ++_bytesToSend;
//    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
//   }
//else
//   USART_SendData(USART3,_byte);

//}
}

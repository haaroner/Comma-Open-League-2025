#include "usartik2.h"

extern "C"
{
  void USART2_IRQHandler(void)
  {
    volatile uint8_t data = USART2->SR;
    if(data & USART_SR_RXNE)
    {
      usartik2::rx[usartik2::_rxCnt] = USART2->DR;
      usartik2::_rxCnt++;
      if(usartik2::_rxCnt == usartik2::_buffer_size)
      {
        usartik2::_rxCnt = 0;
      }
    }
    if(data &USART_SR_TC)
    {
      USART_ClearITPendingBit(USART2, USART_IT_TC);
      if(usartik2::_txCnt != 0)
      {
        (USART2->DR) = usartik2::tx[usartik2::_sendCnt];
        usartik2::_sendCnt++;
        if(usartik2::_sendCnt == usartik2::_buffer_size)
        {
          usartik2::_sendCnt = 0;
        }
      }
      else
      {
        usartik2::flag = 1;
      }
    }
    if(USART2 -> SR & USART_SR_ORE)
    {
      uint8_t a = USART2 -> DR;
      (void)a;
    }
  }
}

namespace usartik2
{
  volatile uint8_t tx[25];
  volatile uint8_t rx[25];
  volatile uint16_t _rxCnt;
  volatile uint16_t _txCnt;
  volatile bool flag;
  volatile uint16_t _readCnt;
  volatile uint16_t _sendCnt;
  volatile uint16_t _buffer_size;
  
  void USART2Init(uint32_t speed, uint8_t word_length, float stop_bits, uint16_t buff_size)
    {
    flag = 1;
    _txCnt = 0;
    _rxCnt = 0;
    _readCnt = 0;
    _sendCnt = 0;
    if(buff_size <= 25 && buff_size > 0) _buffer_size = buff_size;
    else _buffer_size = 25;
      
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
    return;
  }  
     
  uint16_t read()
  {  
    uint16_t dt;
    ENTER_CRITICAL_SECTION();
    dt = rx[_readCnt];
    _readCnt++;
    if(_readCnt == _buffer_size)
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
  
  void abcde(uint8_t _data)
  {
   ENTER_CRITICAL_SECTION();
    if(!flag)
    {
     tx[_txCnt] = _data;
     _txCnt++;
     if(_txCnt == _buffer_size)
     {
     _txCnt = 0;
     }
    }
    else
    {
     flag = 0;
     (USART2->DR) = _data;
    }
    EXIT_CRITICAL_SECTION();
    return;
  }    
  
  void write_uart2(uint8_t _byte)
  {  
//    ENTER_CRITICAL_SECTION();
//    if(!flag)
//    {
//     tx[_txCnt] = _byte;
//     _txCnt++;
//     if(_txCnt == 25)
//     {
//     _txCnt = 0;
//     }
//    }
//    else
//    {
//     flag = 0;
//     (USART2->DR) = _byte;
//    }
//    EXIT_CRITICAL_SECTION();
  }
}

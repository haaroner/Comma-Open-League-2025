#include "time_service.h"

#ifndef TIME_SERVICE_H
#define TIME_SERVICE_H



namespace time_service
{
  void startTime(void)
	{
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	}
	
	void stopTime(void)
	{
		SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
	}
	
	void delay_ms(float delta)
	{
		uint32_t start = getCurTime();
		while(getCurTime() - start <= delta);
	}
	
	void init()
	{
		if(SysTick_Config(SystemCoreClock/1000))
		{
			while(true);
		}
	}
  volatile uint32_t systemTime;
  void startTime_DOT(void)
  {
    RCC->CFGR &= ~RCC_CFGR_SW;									//clear
    RCC->CFGR |= RCC_CFGR_SW_HSI;								//select source SYSCLK = HSI
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);		//wait till HSI is used
    
    RCC->CR &= ~RCC_CR_PLLON;					//turn PLL off to configure it
    while((RCC->CR & RCC_CR_PLLRDY));			//wait till PLL is off
    
    RCC->CR |= RCC_CR_HSEON;					//enable HSE
    while(!(RCC->CR & RCC_CR_HSERDY));			//wait till HSE is ready
      
    RCC->CFGR &= ~RCC_CFGR_HPRE;						//CLEAR
    RCC->CFGR &= ~RCC_CFGR_PPRE1;
    RCC->CFGR &= ~RCC_CFGR_PPRE2;
    
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;				//AHB = SYSCLK / 1
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;				//APB1 = HCLK / 4
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;				//APB2 = HCLK / 2
    
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ;				//CLEAR
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;

    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;				//SOURCE HSE
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLQ_2;																							//SOURCE HSE = 8 MHz
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_2;																							//8 / 4 = 2MHz
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_3 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_7;		//2 * 168 = 336MHz
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP; 																							//336 / 2 = 168MHz
    
    RCC->CR |= RCC_CR_PLLON;								//enable PLL
    while(!(RCC->CR & RCC_CR_PLLRDY));			//wait till PLL is ready
    
    RCC->CFGR &= ~RCC_CFGR_SW;					//clear
    RCC->CFGR |= RCC_CFGR_SW_PLL;				//select source SYSCLK = PLL
    while((RCC->CFGR & RCC_CFGR_SWS) == 2);		//wait till PLL is used
    
    //TIM7 configuration for delay functions
//    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;		
//    TIM7->PSC = 84 - 1;
//    TIM7->ARR = 1000;
//    TIM7->CR1 |= TIM_CR1_ARPE;
//    TIM7->CR1 &= ~TIM_CR1_CMS;
//    TIM7->CR1 &= ~TIM_CR1_DIR;
//    TIM7->DIER |= TIM_DIER_UIE;
//    NVIC_EnableIRQ(TIM7_IRQn);
//    NVIC_SetPriority(TIM7_IRQn, 1);
//    //start counting
//    TIM7->CR1 |= TIM_CR1_CEN;	
      RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM7EN, ENABLE);
      TIM_TimeBaseInitTypeDef time;
      time.TIM_Prescaler = 83; 
      time.TIM_CounterMode = TIM_CounterMode_Up;
      time.TIM_Period = 1000;
      time.TIM_ClockDivision = TIM_CKD_DIV1;
      TIM_TimeBaseInit(TIM7, &time);
      TIM_Cmd(TIM7,ENABLE);
      TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
      NVIC_EnableIRQ(TIM7_IRQn);   
  }
  
  uint32_t getCurTime(void)
  {
    return systemTime;
  }
  
  uint32_t getCurTime_micros(void)
  {
    return systemTime * 1000 + TIM7->CNT;;
  }
  
  void delay_ms(uint32_t t)
  {
    unsigned long timer = getCurTime();
    while(getCurTime() - timer < t);
  }


  void delay_micros(uint32_t t)
  {
    unsigned long timer = getCurTime_micros();
    while(getCurTime_micros() - timer < t);
  }
}

extern "C"{
//  void TIM7_IRQHandler(void) //handler for delay functions
//  {			
//    if(TIM7->SR & TIM_SR_UIF)
//    {
//        TIM7->SR &= ~TIM_SR_UIF;
//        time_service::systemTime++;
//    }
//  }
  void SysTick_Handler(void)
	{
		time_service::systemTime++;
	}
}

#endif

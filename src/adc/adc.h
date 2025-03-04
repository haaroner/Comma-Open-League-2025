#pragma once
#include "project_config.h"
#include "pin_setup.h"

class Adc
{
	public:
		Adc(ADC_TypeDef* ADCx,
				uint8_t numberOfChannels,
				uint8_t curChannel,
				uint32_t RCC_APB2Periph_ADCx,
				pin &sig,
        uint8_t num_of_cycles);
		void adcInit(uint8_t _num_of_cycles);
		void startAdc();
		void setChannel();
		void sendMeChannel(uint8_t chan);
		ADC_TypeDef* getAdc();
		void adcDmaInit();
	private:
		ADC_TypeDef* m_ADCx;
		uint8_t m_numberOfChannels;
		uint8_t m_curChannel;
	  uint8_t m_ADC_Channel_x;
		uint32_t m_RCC_APB2Periph_ADCx;
		pin m_sig;
		uint8_t channel[50];
		uint8_t cur;
};
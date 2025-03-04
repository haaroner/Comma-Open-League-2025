#include <IRlocator.h>

IRlocator::IRlocator(soft_i2c &irI2C, uint32_t addres):m_irI2C(irI2C)
{
	m_irI2C.softI2cInit();
	m_addres = addres;
}

int16_t IRlocator::getData(uint8_t data)
{
	m_irI2C.generateStart();
    m_irI2C.send(m_addres<<1);
    if(m_irI2C.readAch())
    {
            // return true;
    }
    else
    {
              //return false;
    }
    m_irI2C.send(data);
    if(m_irI2C.readAch())
    {
       //return true;
    }
    else
    {
              //return false;
    }
		m_irI2C.generateStop();
    m_irI2C.generateStart();
    volatile uint32_t tmp1 = m_addres<<1;
    tmp1 = tmp1 |= 0x01;
    m_irI2C.send(tmp1);
    if(m_irI2C.readAch())
    {
     //return true;
    }
    else
    {
        //return false;
    }
    volatile uint32_t tmp2 = m_irI2C.read();
    //tmp2 |= m_irI2C.read()<<8;
    //uint32_t tmp3 = tmp2*0.02 -273.5;
    //volatile uint32_t pec = m_irI2C.read();
    m_irI2C.generateStop();
    return tmp2;
}
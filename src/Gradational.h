#ifndef Gradational_h
#define Gradational_h

#include <stdint.h>
#include <Arduino.h>

#define INCREMENT true
#define DECREMENT false

#define __IR__(i) *(IntegralType*)i

enum INTEGRAL_TYPES
{
	I_FLOAT,
	I_DOUBLE,
	I_S8,
	I_U8,
	I_S16,
	I_U16,
	I_S32,
	I_S64,
	I_U64
};

class Gradational
{
public:
	Gradational();

	template <typename IntegralType>
	void set(IntegralType* pointer, IntegralType low, IntegralType high, IntegralType step, INTEGRAL_TYPES type, bool wrap = false)
	{
		m_Value = pointer;
		m_Low = *(uint64_t*)&low;
		m_High = *(uint64_t*)&high;
		m_Step = *(uint64_t*)&step;
		m_Type = type;
		m_Wrap = wrap;
	}

	void gradate(bool increase);

	template <typename IntegralType>
	void gradate(bool increase)
	{
		if (m_Value == nullptr)
			return;

		if (increase)
		{
			if (__IR__(m_Value) + __IR__(&m_Step) <= __IR__(&m_High))
				__IR__(m_Value) += __IR__(&m_Step);
			else if (m_Wrap)
				__IR__(m_Value) = __IR__(&m_Low);
			else
				__IR__(m_Value) = __IR__(&m_High);
		}
		else
		{
			if (__IR__(m_Value) - __IR__(&m_Step) >= __IR__(&m_Low))
				__IR__(m_Value) -= __IR__(&m_Step);
			else if (m_Wrap)
				__IR__(m_Value) = __IR__(&m_High);
			else
				__IR__(m_Value) = __IR__(&m_Low);
		}
	}

	void* current();
private:
	void* m_Value;
	uint64_t m_Low, m_High, m_Step;
	bool m_Wrap;
	INTEGRAL_TYPES m_Type;
};

#endif
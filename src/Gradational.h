#ifndef Gradational_h
#define Gradational_h

#define INCREMENT true
#define DECREMENT false

class AnyGradational
{
public:
    virtual void gradate(bool increment) = 0;
};

template <typename IntegralType>
class Gradational : public AnyGradational
{
public:
    using int_type = IntegralType;

    Gradational(IntegralType initial = 0, IntegralType low = 0, IntegralType high = 0, IntegralType step = 0, bool wrap = false)
        : m_Value(initial), m_Low(low), m_High(high), m_Step(step), m_Wrap(wrap) {}

    void set(IntegralType low, IntegralType high, IntegralType step, bool wrap)
    {
        m_Low = low;
        m_High = high;
        m_Step = step;
        m_Wrap = wrap;
    }

    void gradate(bool increment) override
    {
		if (increment)
		{
			if (m_Value + m_Step <= m_High)
				m_Value += m_Step;
			else if (m_Wrap)
				m_Value = m_Low;
			else
				m_Value = m_High;
		}
		else
		{
			if (m_Value - m_Step >= m_Low)
				m_Value -= m_Step;
			else if (m_Wrap)
				m_Value = m_High;
			else
				m_Value = m_Low;
		}
    }

    IntegralType& current()
    {
        return m_Value;
    }

    const IntegralType& current() const
    {
        return m_Value;
    }
private:
	IntegralType m_Value;
	IntegralType m_Low, m_High, m_Step;
	bool m_Wrap;
};

#endif

#include "Gradational.h"

Gradational::Gradational()
    : m_Value(nullptr), m_Low(0), m_High(0), m_Step(0), m_Wrap(false), m_Type(I_FLOAT)
{
}

void Gradational::increment(bool increase)
{
    switch (m_Type)
    {
        case I_FLOAT:
            increment<float>(increase);
            break;
	    case I_DOUBLE:
            increment<double>(increase);
            break;
	    case I_S8:
            increment<int8_t>(increase);
            break;
	    case I_U8:
            increment<uint8_t>(increase);
            break;
	    case I_S16:
            increment<int16_t>(increase);
            break;
	    case I_U16:
            increment<uint16_t>(increase);
            break;
	    case I_S32:
            increment<int32_t>(increase);
            break;
	    case I_S64:
            increment<int64_t>(increase);
            break;
	    case I_U64:
            increment<uint64_t>(increase);
            break;
    }
}
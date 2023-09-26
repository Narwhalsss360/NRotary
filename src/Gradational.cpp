#include "Gradational.h"

Gradational::Gradational()
    : m_Value(nullptr), m_Low(0), m_High(0), m_Step(0), m_Wrap(false), m_Type(I_FLOAT)
{
}

void Gradational::gradate(bool increase)
{
    switch (m_Type)
    {
        case I_FLOAT:
            gradate<float>(increase);
            break;
	    case I_DOUBLE:
            gradate<double>(increase);
            break;
	    case I_S8:
            gradate<int8_t>(increase);
            break;
	    case I_U8:
            gradate<uint8_t>(increase);
            break;
	    case I_S16:
            gradate<int16_t>(increase);
            break;
	    case I_U16:
            gradate<uint16_t>(increase);
            break;
	    case I_S32:
            gradate<int32_t>(increase);
            break;
	    case I_S64:
            gradate<int64_t>(increase);
            break;
	    case I_U64:
            gradate<uint64_t>(increase);
            break;
    }
}

void* Gradational::current()
{
    return m_Value;
}
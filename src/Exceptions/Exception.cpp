#include <AudioPlusPlus/Exceptions/Exception.h>

namespace AudioPlusPlus
{
    Exception::Exception(const std::string& message)
        : message(message)
    {
    }

    const char* Exception::what() const noexcept
    {
        return message.c_str();
    }

    const std::string& Exception::GetMessage() const
    {
        return message;
    }

    void Exception::SetMessage(const std::string& message)
    {
        this->message = message;
    }
}
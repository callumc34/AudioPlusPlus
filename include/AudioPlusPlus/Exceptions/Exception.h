#pragma once
#include <exception>
#include <string>

namespace AudioPlusPlus
{
    /** Template exception class for errors occurring during AudioPlusPlus execution. */
    class Exception : public std::exception
    {
        public:
            /**
             * @brief      Default constructor for a custom exception.
             */
            Exception() = default;

            /**
             * @brief      Construct an exception with a message.
             *
             * @param[in]  message  The exception message.
             */
            Exception(const std::string& message);
            virtual ~Exception() = default;

            /**
             * @brief      Get the exception message.
             *
             * @return     The exception message.
             */
            const char* what() const noexcept;

            /**
             * @brief      Gets the exception message.
             *
             * @return     The exception message.
             */
            const std::string& GetMessage() const;

            /**
             * @brief      Sets the exception message.
             *
             * @param[in]  message  The exception message
             */
            void SetMessage(const std::string& message);

        private:
            /** Exception message */
            std::string message;
    };
}
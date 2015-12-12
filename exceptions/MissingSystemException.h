#ifndef H_MISSING_COMPONENT_EXCEPTION
#define H_MISSING_COMPONENT_EXCEPTION

#include <exception>
#include <typeindex>
#include <string>

namespace zen
{
    class MissingSystemException : public std::exception
    {
        public:
            MissingSystemException(std::type_index type)
                : type(type)
            {
            }

            virtual const char* what() const throw() override
            {
                std::string msg;
                msg.append("EntityGroup did not contain requested system");
                msg.append(type.name());

                return msg.data();
            }
        private:
            std::type_index type;
    };
}
#endif

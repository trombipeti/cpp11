#include <iostream>

#include "string.h"

String::String( const char * str )
{
#ifdef _DEBUG_
    std::cout << ">> String::String(const char*), param: " << str;
    ++_Num_Instances;
    std::cout << " (" << _Num_Instances << ") " << std::endl;
#endif // _DEBUG_
    m_stringValue = new StringValue { str };
}

String::String( String const& other )
{
#ifdef _DEBUG_
    std::cout << ">> String::String(String const&), param: " << other;
    ++_Num_Instances;
    std::cout << " (" << _Num_Instances << ") " << std::endl;
#endif // _DEBUG_
    m_stringValue = other.obtain_stringValue();
}

String::String( String && rval )
{
#ifdef _DEBUG_
    std::cout << ">> String::String(String&&), param: " << rval;
    ++_Num_Instances;
    std::cout << " (" << _Num_Instances << ") " << std::endl;
#endif // _DEBUG_
    m_stringValue = rval.obtain_stringValue();
}

String & String::operator=( String const & other )
{
#ifdef _DEBUG_
    std::cout << ">> String::operator=(String const&), param: " << other;
    std::cout << " (" << _Num_Instances << ") " << std::endl;
#endif // _DEBUG_
    if( this != &other )
    {
        abandon_stringValue();
        m_stringValue = other.obtain_stringValue();
    }
    return *this;
}

String & String::operator=( const char* str )
{
#ifdef _DEBUG_
    std::cout << ">> String::operator=(const char*), param: " << str;
    std::cout << " (" << _Num_Instances << ") " << std::endl;
#endif // _DEBUG_
    abandon_stringValue();
    m_stringValue = new StringValue { str };
    return *this;
}

String & String::operator=( String && rval )
{
#ifdef _DEBUG_
    std::cout << ">> String::operator=(String&&) param: " << rval;
    std::cout << " (" << _Num_Instances << ") " << std::endl;
#endif // _DEBUG_
    if( this != &rval )
    {
        abandon_stringValue();
        m_stringValue = rval.obtain_stringValue();
        rval.m_stringValue = nullptr;
    }
    return *this;
}

String::~String()
{
#ifdef _DEBUG_
    std::cout << ">> String::~String()";
    --_Num_Instances;
    std::cout << " (" << _Num_Instances << ") " << std::endl;
#endif // _DEBUG_
    abandon_stringValue();
}


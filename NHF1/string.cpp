#include <iostream>

#include "string.h"

String::String( const char * str )
{
#ifdef _DEBUG_
    std::cout << "\e[1;32m";
    std::cout << ">> String::String(const char*), param: " << str;
    ++_Num_Instances;
    std::cout << " (" << _Num_Instances << ") " << std::endl;
    std::cout << "\e[0m";
#endif // _DEBUG_
    m_stringValue = new StringValue { str };
}

String::String( String const& other )
{
#ifdef _DEBUG_
    std::cout << "\e[1;32m";
    std::cout << ">> String::String(String const&), param: " << other;
    ++_Num_Instances;
    std::cout << " (" << _Num_Instances << ") " << std::endl;
    std::cout << "\e[0m";
#endif // _DEBUG_
    m_stringValue = other.obtain_stringValue();
}

String::String( String && rval )
{
#ifdef _DEBUG_
    std::cout << "\e[1;32m";
    std::cout << ">> String::String(String&&), param: " << rval;
    ++_Num_Instances;
    std::cout << " (" << _Num_Instances << ") " << std::endl;
    std::cout << "\e[0m";
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
    std::cout << ">> String::operator=(String&&), param: " << rval;
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
    std::cout << "\e[1;31m";
    std::cout << ">> String::~String()";
    --_Num_Instances;
    std::cout << " (" << _Num_Instances << ") " << std::endl;
    std::cout << "\e[0m";
#endif // _DEBUG_
    abandon_stringValue();
}

String operator+( String const& lhs, String const& rhs )
{
#ifdef _DEBUG_
    std::cout << ">> operator+(String const&, String const&), params: " << lhs << " " << rhs << std::endl;
#endif // _DEBUG_
    std::string a = ( const char* )lhs;
    a.append( ( const char* )rhs );
    return String {a.c_str()};
}

String operator+=( String & lhs, String const& rhs )
{
#ifdef _DEBUG_
    std::cout << ">> operator+=(String &, String const&), params: " << lhs << " " << rhs << std::endl;
#endif // _DEBUG_
    lhs = lhs + rhs;
    return lhs;
}

String operator+( String const& lhs, char rhs )
{
#ifdef _DEBUG_
    std::cout << ">> operator+(String const&, char), params: " << lhs << " " << rhs << std::endl;
#endif // _DEBUG_
    std::string a = ( const char* )lhs;
    a.append( 1, rhs );
    return String {a.c_str()};
}

String operator+=( String & lhs, char rhs )
{
#ifdef _DEBUG_
    std::cout << ">> operator+=(String &, char), params: " << lhs << " " << rhs;
#endif // _DEBUG_
    lhs = lhs + rhs;
    return lhs;
}

std::ostream& operator<<( std::ostream& os, String const& str )
{
    os << ( const char* ) str;
    return os;
}

std::istream& operator>>( std::istream& is, String & str )
{
    std::string temp;
    is >> temp;
    str = temp.c_str();
    return is;
}


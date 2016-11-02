#include "RPNParser.h"

#include <iostream>
#include <cmath>
#include <stack>
#include <stdexcept>

RPNParser::RPNParser(std::string expression) : m_expression {expression}
{
    TwoOps =
    {
        {"+", [](double left, double right)
            {
                return left + right;
            }
        },
        {"-", [](double left, double right)
            {
                return right - left; // Fordított sorrend a stack miatt!
            }
        },
        {"*", [](double left, double right)
            {
                return left * right;
            }
        },
        {"/", [](double left, double right)
            {
                if(right == 0) {
                    throw std::logic_error("Division rrequested by zero");
                }
                return right / left;
            }
        },
        {"^", [](double left, double right)
            {
                return pow(right, left); // Fordított sorrend a stack miatt!
            }
        },
    };

    OneOps =
    {
        {"sin", [](double value)
            {
                return sin(value);
            }
        },
        {"cos", [](double value)
            {
                return cos(value);
            }
        },
        {"sqrt", [](double value)
            {
                if(value < 0) {
                    throw std::logic_error("Invalid expression, wanted to get sqrt() for negative number");
                }
                return sqrt(value);
            }
        },
        {"abs", [](double value)
            {
                return std::abs(value);
            }
        },
        {"sgn", [](double value)
            {
                return (value < 0 ? -1 : (value == 0 ? 0 : 1));
            }
        }
    };
}

bool RPNParser::handle_token(std::string token, double at_value)
{
    if(OneOps.find(token) != OneOps.end()) // valami függvény
    {
        double arg = m_stack.top();
        double newval = (OneOps[token])(arg);
        m_stack.pop();
        m_stack.push(newval);
    }
    else if(TwoOps.find(token) != TwoOps.end()) // kétoperandusú kifejezés
    {
        if(m_stack.size() < 2)
        {
            throw std::invalid_argument("Invalid expression, want to eval a two-operand expression with one or less value on stack");
        }
        double arg1 = m_stack.top();
        m_stack.pop();
        double arg2 = m_stack.top();
        m_stack.pop();

        double newval = (TwoOps[token])(arg1, arg2);
        m_stack.push(newval);
    }
    else if(token == "x")
    {
        m_stack.push(at_value);
    }
    else if( !std::isnan(toNumber(token)) ) // Szám
    {
        m_stack.push(toNumber(token));
    }
    else
    {
        return false;
    }
    return true;
}

double RPNParser::evaluate(double x)
{
    size_t last_match_start = 0;
    size_t last_match_end = 0;
    while(last_match_end != std::string::npos)
    {
        last_match_end = m_expression.find(' ', last_match_start);
        std::string token = m_expression.substr(last_match_start, last_match_end - last_match_start);
        last_match_start = last_match_end + 1;
        // Evaluate it
        if( ! handle_token(token, x))
        {
            return nan("");
        }
    }
    return m_stack.top();
}

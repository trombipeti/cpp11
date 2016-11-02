#ifndef PARSER_H
#define PARSER_H

#include <cstdlib>
#include <string>
#include <stack>
#include <utility>
#include <memory>
#include <iostream>
#include <functional>

using match_range = std::pair< std::string::iterator, std::string::iterator >;
using semantic_action = std::function< void(std::string const &) >;

class base_rule
{
private:
    virtual bool test(match_range &context, match_range &matching_range) = 0;

protected:
    semantic_action the_semantic_action;

public:
    virtual ~base_rule() {}
    base_rule() = default;
    base_rule(base_rule const &) = default;


    bool match(match_range &context, match_range &matching_range)
    {
        match_range local = context, result;

        if (test(local, result))
        {
            context = local;
            matching_range = result;

            if (the_semantic_action)
            {
                the_semantic_action(std::string(result.first, result.second));
            }

            return true;
        }

        return false;
    }

    base_rule &operator[] (semantic_action const &an_action)
    {
        the_semantic_action = an_action;
        return *this;
    }

    virtual std::shared_ptr<base_rule> clone() const = 0;
};

class rule : public base_rule
{
private:
    std::shared_ptr< std::shared_ptr<base_rule> > the_rule;

    virtual bool test(match_range &context, match_range &matching_range) override
    {
        if (!(*the_rule)) throw "Undefined rule";
        return (*the_rule)->match(context, matching_range);
    }

public:
    rule(std::shared_ptr<base_rule> a_rule = nullptr) :
        the_rule(new std::shared_ptr<base_rule>(a_rule)) {}

    void set_rule(std::shared_ptr<base_rule> a_rule)
    {
        *the_rule = a_rule;
    }

    rule &operator<<=(base_rule const &a_rule)
    {
        set_rule(a_rule.clone());
        return *this;
    }

    virtual std::shared_ptr<base_rule> clone() const override
    {
        return std::shared_ptr<base_rule>(new rule(*this));
    }
};

class succession : public base_rule
{
private:
    std::shared_ptr<base_rule> first_rule;
    std::shared_ptr<base_rule> second_rule;

    virtual bool test(match_range &context, match_range &matching_range) override
    {
        match_range local = context, first_match, second_match;

        if (first_rule->match(local, first_match) && second_rule->match(local, second_match))
        {
            context = local;
            matching_range.first = first_match.first;
            matching_range.second = second_match.second;
            return true;
        }

        return false;
    }

public:
    succession(std::shared_ptr<base_rule> first_rule, std::shared_ptr<base_rule> second_rule) :
        first_rule(first_rule),
        second_rule(second_rule) {}

    virtual std::shared_ptr<base_rule> clone() const override
    {
        return std::shared_ptr<base_rule>(new succession(*this));
    }
};

class alternation : public base_rule
{
private:
    std::shared_ptr<base_rule> first_rule;
    std::shared_ptr<base_rule> second_rule;

    virtual bool test(match_range &context, match_range &matching_range) override
    {
        match_range local = context, the_match;

        if (first_rule->match(local, the_match))
        {
            matching_range = the_match;
            context = local;
            return true;
        }
        if (second_rule->match(local, the_match))
        {
            matching_range = the_match;
            context = local;
            return true;
        }

        return false;
    }

public:
    alternation(std::shared_ptr<base_rule> first_rule, std::shared_ptr<base_rule> second_rule) :
        first_rule(first_rule),
        second_rule(second_rule) {}

    virtual std::shared_ptr<base_rule> clone() const override
    {
        return std::shared_ptr<base_rule>(new alternation(*this));
    }
};

class repetition : public base_rule
{
private:
    std::shared_ptr<base_rule> the_rule;

    virtual bool test(match_range &context, match_range &matching_range) override
    {
        match_range local = context, the_match;

        if (the_rule->match(local, the_match))
        {
            while (the_rule->match(local, the_match));

            matching_range.first = context.first;
            matching_range.second = the_match.second;
            context = local;

            return true;
        }

        return false;
    }

public:
    repetition(std::shared_ptr<base_rule> a_rule) : the_rule(a_rule) {}

    virtual std::shared_ptr<base_rule> clone() const override
    {
        return std::shared_ptr<base_rule>(new repetition(*this));
    }

};

rule operator <<(base_rule const &first_rule, base_rule const &second_rule);

rule operator |(base_rule const &first_rule, base_rule const &second_rule);

rule operator +(base_rule const &a_rule);

class character : public base_rule
{
private:
    std::string values;

    virtual bool test(match_range &context, match_range &matching_range) override
    {
        if (context.first == context.second) return false;

        for (auto c : values)
        {
            if (*context.first == c)
            {
                matching_range = std::make_pair(context.first, context.first + 1);

                ++context.first;

                return true;
            }
        }

        return false;
    }

public:
    character(std::string const &values) : values(values) {}

    virtual std::shared_ptr<base_rule> clone() const override
    {
        return std::shared_ptr<base_rule>(new character(*this));
    }
};

float parse_ize(std::string cucc, float at_x);

class Expression
{
private:
public:
    Expression() {}
    virtual double evaluate(double x) const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual ~Expression() {};
};

inline std::ostream& operator<<(std::ostream& os, Expression const& e)
{
    e.print(os);
    return os;
}

class Constant final : public Expression
{
private:
    double val;
public:
    Constant(double value) : val {value} {}
    virtual void print(std::ostream& os) const override
    {
        os << val;
    }


    virtual double evaluate(double x) const override
    {
        return val;
    }
};

class Variable final: public Expression
{
public:
    virtual void print(std::ostream& os) const override
    {
        os << 'x';
    }

    virtual double evaluate(double x) const override
    {
        return x;
    }
};

class TwoOperand : public Expression
{
public:
    TwoOperand(Expression *lhs, Expression *rhs) : lhs_ {lhs}, rhs_ {rhs} {}

    TwoOperand(TwoOperand const&) = delete;
    TwoOperand& operator=(TwoOperand const&) = delete;

    virtual void print(std::ostream &os) const override final
    {
        os << '(' << *lhs_ << get_operator() << *rhs_ << ')';
    }

    virtual double evaluate(double x) const override final
    {
        return do_operator(lhs_->evaluate(x), rhs_->evaluate(x));
    }

    TwoOperand(std::string RPN);

private:
    virtual char get_operator() const = 0;
    virtual double do_operator(double lhs, double rhs) const = 0;

    std::unique_ptr<Expression> lhs_, rhs_;
};

class Sum final : public TwoOperand
{
public:
    using TwoOperand::TwoOperand;

private:
    virtual char get_operator() const override
    {
        return '+';
    }

    virtual double do_operator(double lhs, double rhs) const override
    {
        return lhs + rhs;
    }
};

class Product final : public TwoOperand
{
public:
    using TwoOperand::TwoOperand;

private:
    virtual char get_operator() const override
    {
        return '*';
    }

    virtual double do_operator(double lhs, double rhs) const override
    {
        return lhs * rhs;
    }
};

class Difference final : public TwoOperand
{
public:
    using TwoOperand::TwoOperand;

private:
    virtual char get_operator() const override
    {
        return '-';
    }

    virtual double do_operator(double lhs, double rhs) const override
    {
        return lhs - rhs;
    }
};

class Quotient final : public TwoOperand
{
public:
    using TwoOperand::TwoOperand;

private:
    virtual char get_operator() const override
    {
        return '/';
    }

    virtual double do_operator(double lhs, double rhs) const override
    {
        return lhs / rhs;
    }
};

class Function : public Expression
{
public:
    Function(Expression *expr, std::function<double(double)> func, std::string funcname) : expr_ {expr}, func_ {func}, func_name{funcname} {}

    Function(Function const&) = delete;
    Function& operator=(Function const&) = delete;

    virtual void print(std::ostream &os) const override final
    {
        os << get_name() << "(" << *expr_ << ")";
    }

    virtual double evaluate(double x) const override final
    {
        return func_(expr_->evaluate(x));
    }
private:
    virtual std::string get_name() const
    {
        return func_name;
    }


    std::unique_ptr<Expression> expr_;
    std::function<double(double)> func_;
    std::string func_name;
};

auto toNumber = [](std::string str)
{
//    if(str.size() > 1 && str.data()[0] == '0')
//    {
//        return false;
//    }
    double val = 0.0;
    std::istringstream num(str);

    num >> val;

    if(!num.fail() && num.eof())
    {
        return val;
    }
    else
    {
        return nan("");
    }
};

double parse_and_eval(std::string expression);

#endif // PARSER_H

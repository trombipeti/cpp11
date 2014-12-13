#ifndef PARSER_H
#define PARSER_H
#include <functional>

using matchingRange = std::pair<std::string::iterator, std::string::iterator>;
using onMatch = std::function<void(std::string const&)>;

class ParseRuleBase
{
private:
    virtual bool doTest(matchingRange in_range, matchingRange context) = 0;
protected:
public:
    ParseRuleBase() = default;
    ParseRuleBase(ParseRuleBase const&) = default;

    bool isMatching() {};
};

class Parser
{
    public:
        Parser();
        virtual ~Parser();
    protected:
    private:
};

#endif // PARSER_H

#ifndef RULE_H_INCLUDED
#define RULE_H_INCLUDED

using matchingRange = std::pair<std::string::iterator, std::string::iterator>;
using onMatch = std::function<void(std::string const&)>;

class RuleBase
{
private:
    virtual bool doTest(matchingRange in_range, matchingRange context) = 0;
protected:
public:
    RuleBase() = default;
    RuleBase(RuleBase const&) = default;

    bool isMatching();
};

class DigitRule : public RuleBase
{

};

#endif // RULE_H_INCLUDED

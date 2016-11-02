#ifndef RPNPARSER_H_INCLUDED
#define RPNPARSER_H_INCLUDED

#include <cmath>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <functional>
#include <sstream>
#include <memory>


/**\brief Reverse Polish Notation formában leírt kifejezéseket kiértékelni képes osztály.
 * Az értelmezni tudott kifejezések halmaza egyszerûen bõvíthetõ, ugyanis lambda kifejezéseket használ.
 * A teljes kifejezésre lényeges kikötés, hogy a tokeneket szóközzel elválasztva kell szerepeltetni benne,
 * pl 4 5 + stb.
 */
class RPNParser
{
private:
    /** A kifejezésben eddig feldolgozott, kiértékelt értékek számára fentartott verem. */
    std::stack<double> m_stack;
    std::string m_expression;

    /** Egyoperandusú mûveletek neveit a meghívandó függvénnyel összerendelõ táblázat.*/
    std::map<std::string, std::function<double(double)>> OneOps;
    std::map<std::string, std::function<double(double, double)>> TwoOps;

    /** \brief A szóközök közt talált szövegtokent értelmezi.
     * Ez háromféle lehet (+1, értelmezhetetlen):
     * - Konstans szám
     * - Változó ( 'x' )
     * - Mûveletet jelölõ kulcsszó
     * \param at_value Ha a token típus változó, akkor ez az érték lesz a stackre rakva.
     * \return Értelmezte-e a tokent.
     */
    bool handle_token(std::string token, double at_value);

public:
    RPNParser(std::string expression);

    /** \brief Kiértékeli a kifejezést az adott helyen
     * \param x Ez az érték lesz az 'x' változó helyére behelyettesítve.
     * \return Sikeres kiértékelés esetén a kifejezés eredménye, egyébként NaN.
     */
    double evaluate(double x);
};

auto toNumber = [](std::string str)
{
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

#endif // RPNPARSER_H_INCLUDED

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


/**\brief Reverse Polish Notation form�ban le�rt kifejez�seket ki�rt�kelni k�pes oszt�ly.
 * Az �rtelmezni tudott kifejez�sek halmaza egyszer�en b�v�thet�, ugyanis lambda kifejez�seket haszn�l.
 * A teljes kifejez�sre l�nyeges kik�t�s, hogy a tokeneket sz�k�zzel elv�lasztva kell szerepeltetni benne,
 * pl 4 5 + stb.
 */
class RPNParser
{
private:
    /** A kifejez�sben eddig feldolgozott, ki�rt�kelt �rt�kek sz�m�ra fentartott verem. */
    std::stack<double> m_stack;
    std::string m_expression;

    /** Egyoperandus� m�veletek neveit a megh�vand� f�ggv�nnyel �sszerendel� t�bl�zat.*/
    std::map<std::string, std::function<double(double)>> OneOps;
    std::map<std::string, std::function<double(double, double)>> TwoOps;

    /** \brief A sz�k�z�k k�zt tal�lt sz�vegtokent �rtelmezi.
     * Ez h�romf�le lehet (+1, �rtelmezhetetlen):
     * - Konstans sz�m
     * - V�ltoz� ( 'x' )
     * - M�veletet jel�l� kulcssz�
     * \param at_value Ha a token t�pus v�ltoz�, akkor ez az �rt�k lesz a stackre rakva.
     * \return �rtelmezte-e a tokent.
     */
    bool handle_token(std::string token, double at_value);

public:
    RPNParser(std::string expression);

    /** \brief Ki�rt�keli a kifejez�st az adott helyen
     * \param x Ez az �rt�k lesz az 'x' v�ltoz� hely�re behelyettes�tve.
     * \return Sikeres ki�rt�kel�s eset�n a kifejez�s eredm�nye, egy�bk�nt NaN.
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

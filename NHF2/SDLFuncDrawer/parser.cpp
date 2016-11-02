#include "parser.h"

#include <string>
#include <utility>
#include <memory>
#include <iostream>
#include <functional>

rule operator <<(base_rule const &first_rule, base_rule const &second_rule) {
	return rule(
			std::shared_ptr<base_rule>(
				new succession(
					first_rule.clone(),
					second_rule.clone()
					)
				)
			);
}


rule operator |(base_rule const &first_rule, base_rule const &second_rule) {
	return rule(
			std::shared_ptr<base_rule>(
				new alternation(
					first_rule.clone(),
					second_rule.clone()
					)
				)
			);
}

rule operator +(base_rule const &a_rule) {
	return rule(
		std::shared_ptr<base_rule>(
			new repetition(
				a_rule.clone()
				)
			)
		);
}

float parse_ize(std::string cucc, float at_x)
{
    float result = 0;
    std::stack<float> szamok;
    std::string akt_szam = "";
    for (char& c : cucc)
    {
        if(c == 'x')
        {
            szamok.push(at_x);
        }
        else if(isdigit(c) || c == '.')
        {
            akt_szam += c;
        }
        else if (isspace(c))
        {
            if(akt_szam != "")
            {
                szamok.push(atof(akt_szam.c_str()));
            }
            akt_szam = "";
        }
        else if(c == '*')
        {
            if(szamok.size() < 2)
            {
                std::cout << "Error * without at least 2 numbers" << std::endl;
            }
            else
            {
                float szam1 = szamok.top();
                szamok.pop();
                float szam2 = szamok.top();
                szamok.pop();
                float ujszam = szam1 * szam2;
                szamok.push(ujszam);
                result = ujszam;

            }
        }
        else if(c == '/')
        {
            if(szamok.size() < 2)
            {
                std::cout << "Error / without at least 2 numbers" << std::endl;
            }
            else
            {
                float szam1 = szamok.top();
                szamok.pop();
                float szam2 = szamok.top();
                szamok.pop();
                float ujszam = szam1 / szam2;
                szamok.push(ujszam);
                result = ujszam;

            }
        }
        else if(c == '+')
        {
            if(szamok.size() < 2)
            {
                std::cout << "Error + without at least 2 numbers" << std::endl;
            }
            else
            {
                float szam1 = szamok.top();
                szamok.pop();
                float szam2 = szamok.top();
                szamok.pop();
                float ujszam = szam1 + szam2;
                szamok.push(ujszam);
                result = ujszam;

            }
        }
        else if(c == '-')
        {
            if(szamok.size() < 2)
            {
                std::cout << "Error - without at least 2 numbers" << std::endl;
            }
            else
            {
                float szam1 = szamok.top();
                szamok.pop();
                float szam2 = szamok.top();
                szamok.pop();
                float ujszam = szam1 - szam2;
                szamok.push(ujszam);
                result = ujszam;

            }
        }
    }
    return result;
}


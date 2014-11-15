#include <iostream>
#include <cstring>


unsigned long long operator"" _binary(const char* s)
{
	unsigned long long ret = 0;
	int len = strlen(s);
	for(int i = len - 1; i>=0; --i)
	{
		ret += (s[i] - '0') << (len - i - 1);
	}
	return ret;
}

int main()
{
    std::cout << 1111_binary << std::endl;      /* 15 */
    std::cout << 10000000_binary << std::endl;  /* 128 */
}
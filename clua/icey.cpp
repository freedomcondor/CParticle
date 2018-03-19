#include <stdio.h>
class Icey
{
public:
	int value;

	Icey();
	~Icey();

	int cry();
	int angry();
};

Icey::Icey()
{
	value = 0;
}

Icey::~Icey()
{
}

int Icey::cry()
{
	value += 1;
	if (value == 5)
		angry();
	printf("in cry, value = %d\n",value);

	return value;
}

int Icey::angry()
{
	value = 0;
	printf("QianQian died!\n");
	return 0;
}

int cry(lua_State* L)
{
	Icey* icey = (Icey*)lua_touserdata(L,1);
	icey->cry();
	printf("in luacry, value = %d\n",icey->value);
	return 0;
}

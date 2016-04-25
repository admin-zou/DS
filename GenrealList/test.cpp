#define _CRT_SECURE_NO_WARNINGS
#include "GeneralLists.h"

int main()
{
	GeneralList gl3("()");
	GeneralList gl2("(a,b)");
	GeneralList gl1("(a,b,c,(d,(e),f),g,h)");
	GeneralList gl4(gl1);
	gl4.Print();
	gl4.Deep();
	gl4.Length();
	gl1.Print();
	gl2.Print();
	gl3.Print();
	gl1.Deep();
	gl2.Deep();
	gl3.Deep();
	gl1.Length();
	gl2.Length();
	gl3.Length();
	
	return 0;
}

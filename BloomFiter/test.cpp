#include "BloomFiter.h"
#include <string>

int main()
{
	BloomFiter<string> Bf(100);
	Bf.Add("peter");
	Bf.Add("信鸽");

	cout<<"peter:"<<Bf.Check("peter")<<endl;
	cout<<"信鸽"<<Bf.Check("信鸽")<<endl;
	cout<<"jack:"<<Bf.Check("jack")<<endl;

	return 0;
}


#include <iostream>
#include <vector>
void main(void)
{
	int a[2]={1,2};
	int b[2]={3,4};
	std::vector< int>v1(a, a+2);
	std::vector<int>v2(b, b+2);
	v2 = std::move(v1);
	std::cout<<v2[1]<<v1.size()<<std::endl;

	while(1);
}
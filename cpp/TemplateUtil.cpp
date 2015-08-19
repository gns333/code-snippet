/*
模板相关小工具
*/

#include <cstdio>
#include <cstddef>

//return size of an array as a compile-time constant
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N])
{
	return N;
}

//////////////////////////////////////////////////////////////////////////

#include <cassert>

int main(int argc, char const *argv[])
{
	// test arraySize
	int testArray1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int testArray2[arraySize(testArray1)];
	assert(arraySize(testArray1) == 10);
	assert(arraySize(testArray2) == 10);

	printf("test ok!\n");

	return 0;
}
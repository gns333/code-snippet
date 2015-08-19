/*
追踪对象是否为堆上对象
非线程安全
*/

#include <cstdio>
#include <list>
#include <algorithm>

class HeapTrackable
{
public:
	static void* operator new(size_t size)
	{
		void* newPtr = ::operator new(size);
		heapAddressList_.push_front(newPtr);
		return newPtr;
	}
	static void operator delete(void* ptr)
	{
		auto ptrIt = std::find(heapAddressList_.begin(), heapAddressList_.end(), ptr);
		if (ptrIt != heapAddressList_.end())
		{
			heapAddressList_.erase(ptrIt);
			::operator delete(ptr);
		}
		else 
		{
			throw "valid address";
		}
	}
	bool isOnHeap(void) const
	{
		const void* rawAddress = dynamic_cast<const void*>(this);
		auto ptrIt = std::find(heapAddressList_.begin(), heapAddressList_.end(), rawAddress);
		return ptrIt != heapAddressList_.end();
	}
	virtual ~HeapTrackable() = 0;
private:
	static std::list<const void*> heapAddressList_;
};
std::list<const void*> HeapTrackable::heapAddressList_;
HeapTrackable::~HeapTrackable() {};

//////////////////////////////////////////////////////////////////////////

#include <cassert>

class Test : public HeapTrackable 
{

};

int main(int argc, char const *argv[])
{
	Test t1;
	assert(t1.isOnHeap() == false);

	Test* t2 = new Test();
	assert(t2->isOnHeap() == true);
	delete(t2);

	static Test t3;
	assert(t3.isOnHeap() == false);

	printf("test ok!\n");

	return 0;
}
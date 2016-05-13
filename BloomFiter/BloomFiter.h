/*                            布隆过滤器
 * 
 * Bloom Filter 是一种空间效率很高的随机数据结构，Bloom filter 可以看做是对bit-map 的扩展, 它的原理是：
 *当一个元素被加入集合时，通过K个Hash函数将这个元素映射成一个位阵列（Bit array）中的 K 个点，把它们置为 1。检索时，我们只要看看这些点是不是都是 1 就（大约）知道集合中有没有它了：
 *    如果这些点有任何一个 0，则被检索元素一定不在；
 *    如果都是 1，则被检索元素很可能在。
 * 
 * create by admin-zou in 2016/5/13
*/

#pragma once
#include <iostream>
#include <string>
#include "BitMap.h"
#include "common.h"
using namespace std;

template <class K, 
		 class HashFuncer1 = hashFunc1<K>,
		 class HashFuncer2 = hashFunc2<K>,
		 class HashFuncer3 = hashFunc3<K>,
		 class HashFuncer4 = hashFunc4<K>,
		 class HashFuncer5 = hashFunc5<K> 
		 >
class BloomFiter
{
public:
	BloomFiter(size_t size)
			:_capacity(GetNextPrimeNum(size))
			 ,_bt(_capacity)
		{}

	void Add(const K& key)
	{
		size_t index1 = HashFuncer1()(key.c_str()) % _capacity;
		_bt.Set(index1);
		//cout<<index1<<endl;

		size_t index2 = HashFuncer2()(key.c_str()) % _capacity;
		_bt.Set(index2);
		//cout<<index2<<endl;
		
		size_t index3 = HashFuncer3()(key.c_str()) % _capacity;
		_bt.Set(index3);
		//cout<<index3<<endl;
		
		size_t index4 = HashFuncer4()(key.c_str()) % _capacity;
		_bt.Set(index4);
		//cout<<index4<<endl;
		
		size_t index5 = HashFuncer5()(key.c_str()) % _capacity;
		_bt.Set(index5);
		//cout<<index5<<endl;
	}

	bool Check(const K& key)
	{
		size_t index1 = HashFuncer1()(key.c_str()) % _capacity;
		//cout<<index1<<endl;
		if(! _bt.Test(index1))
		{
			return false;
		}

		size_t index2 = HashFuncer2()(key.c_str()) % _capacity;
		//cout<<index2<<endl;
		if(! _bt.Test(index2))
		{
			return false;
		}

		size_t index3 = HashFuncer3()(key.c_str()) % _capacity;
		//cout<<index3<<endl;
		if(! _bt.Test(index3))
		{
			return false;
		}

		size_t index4 = HashFuncer4()(key.c_str()) % _capacity;
		//cout<<index4<<endl;
		if(! _bt.Test(index4))
		{
			return false;
		}

		size_t index5 = HashFuncer5()(key.c_str()) % _capacity;
		//cout<<index5<<endl;
		if(! _bt.Test(index5))
		{
			return false;
		}
	
		return true;
	}

private:
	size_t  _capacity;
	BitMap  _bt;
};

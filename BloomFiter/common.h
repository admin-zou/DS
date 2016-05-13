/*	
 *	commom 头文件主要存放公共接口函数，提高代码的复用性，例如常见的字符哈系函数
 *
 *create by admin-zou in 2015/5/13
 * 
*/

#pragma once

//素数表
const int HashSize = 28;
static const unsigned long PrimeList[HashSize] = {
	53ul, 97ul, 193ul, 389ul, 769ul, 1543ul, 3079ul, 6151ul,12289ul,
	24593ul, 49157ul, 98317ul, 196613ul, 393241ul, 786433ul,1572869ul,
	3145739ul, 6291469ul, 12582917ul, 25165843ul, 50331653ul,100663319ul, 
	201326611ul, 402653189ul, 805306457ul, 1610612741ul, 3221225473ul,4294967291ul
};

size_t GetNextPrimeNum(size_t size)
{
	 for(size_t i = 0; i < HashSize; ++i)
	 {
  			 if(size < PrimeList[i])
			{
                 return PrimeList[i];
            }
	 }

	 return PrimeList[HashSize-1];
}


// 字符哈系函数
template<class K>
size_t BKDRHash(const K *str)
{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)	
		{
				hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..            
		}
		return hash;
}
template<class K>
struct hashFunc1
{
	size_t operator() (const char* key)
	{
		return BKDRHash(key);		
	}
};

template<class K>
size_t SDBMHash(const K *str)
{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
				hash = 65599 * hash + ch;
				//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		}
		return hash;
}
template<class K>
struct hashFunc2
{
	size_t operator() (const char* key)
	{
		return SDBMHash(key);
	}
};

template<class K>
size_t RSHash(const K *str)
{
	register size_t hash = 0;
	size_t magic = 63689;
	while (size_t ch = (size_t)*str++)
	{
			hash = hash * magic + ch;
			magic *= 378551;
	}
	return hash;
}
template<class K>
struct hashFunc3
{
	size_t operator() (const char* key)
	{
		return RSHash(key);
	}
};

template<class K>
size_t APHash(const K *str)
{
	register size_t hash = 0;
	size_t ch;
	for (long i = 0; ch = (size_t)*str++; i++)
	{
			if ((i & 1) == 0)
			{
					hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
					hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
	}
	return hash;
}
template<class K>
struct hashFunc4
{
	size_t operator() (const char* key)
	{
		return APHash(key);
	}
};

template<class K>
size_t JSHash(const K *str)
{
	if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
		return 0;
	register size_t hash = 1315423911;
	while (size_t ch = (size_t)*str++)
	{
			hash ^= ((hash << 5) + ch + (hash >> 2));
	}
	return hash;
}
template<class K>
struct hashFunc5
{
	size_t operator() (const char* key)
	{
		return JSHash(key);
	}
};




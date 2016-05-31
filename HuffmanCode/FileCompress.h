#pragma once

#include <iostream>
#include "Huffman.h"
#include <string>
#include <assert.h>
#include <stdio.h>
using namespace  std;

typedef unsigned long long FileLen;

struct FileInfo
{ //文件节点信息
	unsigned char _ch;
	FileLen       _appeartimes;
	string 	      _coding;

	FileInfo(unsigned char ch = '\0')
			: _ch(ch)
			, _appeartimes(0)
			, _coding("")
	{}

	FileInfo(FileLen times)
			: _ch('\0')
			, _appeartimes(times)
			, _coding("")
	{}
	/* 重载以下函数是为了哈夫曼树节点的构造（因为我们要是用字符出现的次数作为权值）*/
	bool operator < (const FileInfo &I)const
	{ 
		return this->_appeartimes < I._appeartimes;
	}

	bool operator != (const FileInfo& I)const
	{
		return this->_appeartimes != I._appeartimes;
	}

	FileInfo operator + (const FileInfo& I)const
	{
		return FileInfo(_appeartimes + I._appeartimes);
	}
};


class FileCompress
{
public:
	FileCompress()
	{
		for(int i = 0; i < 256; ++i)
		{
			_Info[i]._ch = (unsigned char)i;
		}
	}
	
	//文件压缩
	void Compress(const char* Filename)
	{
		FILE *fr = fopen(Filename,"rb"); //以二进制读的方式打开文件
		assert(fr);
		//注意为什么要用unsigned char
		unsigned char ch = 0;
		ch = fgetc(fr);
	#ifdef _DEBUG_
		int sum = 0;
	#endif
		while(!feof(fr))
		{//linux底下在末尾会加上换行符,所以在输入只有一行的时候需要好好注意
	#ifdef _DEBUG_
			++sum;
			cout<<ch<<">";
	#endif
			if(ch == '\n')
			{
				unsigned char tmp = fgetc(fr);
				if(feof(fr))
				{
					break;	
				}
				else
				{ /* 主要是为了处理最后一行的内容，Linux下会默认给它加上'\n'这会影响到编码，所以我们必须处理掉 */
					++_Info[ch]._appeartimes;
					++_Info[tmp]._appeartimes;
					ch = fgetc(fr);
					continue;
				}
			}
			++_Info[ch]._appeartimes;
			ch = fgetc(fr);
		}
		cout<<sum<<endl;
	#ifdef _DEBUG_
		cout<<"find All char"<<endl;
	#endif
		//文件指针回到原点，因为读文件两次
		fseek(fr, 0, SEEK_SET);	
		//设置非法值，提供过滤功能（过滤出现次数为0的字符）
		const FileInfo filter((FileLen)0);
	#ifdef _DEBUG_
		cout<<filter._ch<<","<<filter._appeartimes<<","<<filter._coding.c_str()<<endl;
	#endif
		//建立哈夫曼树
		HuffmanTree<FileInfo> Ht(_Info,256,filter);
		HuffmanTreeNode<FileInfo> *Top = Ht.Top();	
		//生成哈夫曼编码
		string coding="";
		_MakingCode(Top,coding);
	#ifdef _DEBUG_
		cout<<"making code success"<<endl;
	#endif
		//生成编码后就开始压缩
		string compress = Filename;		
		//compress
		compress+=".huffman";
		FILE *fw = fopen(compress.c_str(),"wb");
		assert(fw);
		//按位写进文件
		char value = 0;
		int pos = 8;
		ch = fgetc(fr);
		while(!feof(fr))
		{
			for(size_t i = 0; i<_Info[ch]._coding.size(); ++i)
			{
				value <<= 1;
				if(_Info[ch]._coding[i] == '1')
				{
					value |= 1;	
				}
				--pos;
				if(pos == 0)
				{
					fputc(value,fw);
					value = 0;
					pos = 8;
				}
			}
			ch = fgetc(fr);
		}
		//这里需要注意一下，最后一位可能有冗余信息*注意怎么处理它*
		if(pos)
		{
			fputc(value<<(pos),fw);
		}	
	#ifdef _DEBUG_
		cout<<"compress success"<<endl;
	#endif
		//写配置文件，将‘char，times’写进配置文件中，以便重建哈夫曼树
		char strInfo[32]={0};
		string conf = Filename;
		conf+=".config";
		FILE *fc = fopen(conf.c_str(),"wb");
		assert(fc);
		for(size_t i=0; i < 256; ++i)
		{
			if(_Info[i]._appeartimes != 0)
			{
			#ifdef _DEBUG_
				cout<<i<<":"<<_Info[i]._ch<<endl;
			#endif			
				string info = "";
			    info.push_back(_Info[i]._ch);
				info += ",";
				sprintf(strInfo,"%d",_Info[i]._appeartimes);
				info += strInfo;
			#ifdef _DEBUG_
				cout<<info.c_str()<<endl;
			#endif			
				fputs(info.c_str(),fc);
				fputc('\n',fc);
				info.clear();
			}
		}	
	#ifdef _DEBUG_
		cout<<"making config success"<<endl;
	#endif
		fclose(fc);
		fclose(fw);
		fclose(fr);		
	}

	void Uncompress(const char* Filename)
	{
		// 读配置文件重建哈夫曼树
		string conf = Filename;
		conf += ".config";
		FILE *fc = fopen(conf.c_str(),"rb");
        assert(fc);
		unsigned char ch = 0;
		string oneline="";
	#ifdef _DEBUG_
		cout<<"get Info..."<<endl;
	#endif
		while(Readline(fc,oneline))
		{
			if(!oneline.empty())
			{
				ch = oneline[0];
				_Info[ch]._appeartimes = atoi(oneline.substr(2).c_str());
				oneline.clear();
			}
			else
			{
				/*这个判断在这里是告诉我们,\n可能是文件中一部分，我们必须将它考虑进来*/
				oneline = '\n';
			}
		}
	#ifdef _DEBUG_
		cout<<"get Info success!"<<endl;
	#endif
		const FileInfo filter((FileLen)0);
		HuffmanTree<FileInfo> Ht(_Info,256,filter);
		HuffmanTreeNode<FileInfo> *Top = Ht.Top();	
	#ifdef _DEBUG_
		cout<<"rebuilt HuffmanTree success"<<endl;
	#endif
		//很巧妙的一点是，跟节点的权值就是文件的长度
		FileLen textLength = Top->_weight._appeartimes;		
		string comp = Filename;
		comp += ".huffman";
		FILE *fr = fopen(comp.c_str(),"rb");
		assert(fr);
        //通过压缩文件和编码解压出原文件
		string uncomp = Filename;
		uncomp += ".uncompress";
		FILE *fw = fopen(uncomp.c_str(),"wb");
		assert(fw);
		HuffmanTreeNode<FileInfo> *cur = Top;
		FileLen Length = Top->_weight._appeartimes;
	#ifdef _DEBUG_
				cout<<"Length:"<<Length<<endl;
	#endif
		//利用哈夫曼树恢复文件
		ch = fgetc(fr);
		int pos = 8;		
		while(Length>0)
		{
			while(cur->_left && cur->_right)
			{
				if(pos == 0)
				{
					ch = fgetc(fr);
					pos = 8;
				}
				--pos;
				if((1<<pos) & ch)
				{
					cur = cur->_right;
				}
				else
				{
					cur = cur->_left;
				}				
			}
			
			if(cur && Length--)
			{
				unsigned char tmp = cur->_weight._ch;
			#ifdef _DEBUG_
				cout<<tmp<<",";
			#endif
				fputc(tmp,fw);
				cur = Top;
			}
		}
		//记得关闭
		fclose(fw);
		fclose(fr);
		fclose(fc);
	}

protected:
	void _MakingCode(HuffmanTreeNode<FileInfo>* root, string coding)
	{ //递归的方式生成哈夫曼编码，往左‘0’，往右‘1’
		if(root == NULL)
		{
			return ;
		}
		else if(root->_left == NULL && root->_right == NULL)
		{
			_Info[root->_weight._ch]._coding = coding;
		#ifdef _DEBUG_
			cout<<root->_weight._ch<<":"<<coding.c_str()<<endl;
		#endif
		}
		else 
		{	
			if(root->_left)
			{
				coding.push_back('0');
				_MakingCode(root->_left,coding);
				coding.pop_back();
			}
			if(root->_right)
			{
				coding.push_back('1');
				_MakingCode(root->_right,coding);
				coding.pop_back();
			}
		}
	}

	bool Readline(FILE* pr,string &info)
	{ /*该函数读取文件中的一行，Linux下的格式不同，*/
		unsigned char ch = 0;
		ch = fgetc(pr);
		if(feof(pr))
		{
			return false;
		}

		while(ch != '\n')
		{
			info.push_back(ch);
			ch = fgetc(pr);
		}
		return true;
	}

private:
	FileInfo  _Info[256];
};



void TestFilecompress()
{
	FileCompress Fc;
	Fc.Compress("input");

	Fc.Uncompress("input");
}

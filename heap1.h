#include <iostream>
using namespace std;
class heap
{
private:
	int *arr;
	int last;
	int size;
public:
	heap()
	{
		size=500;
		last=0;
		arr=new int[size];
		for(int i=0;i<size;++i)
		{
			arr[i]=0;
		}
	}
	void clearheap()
	{
		for(int i=0;i<size;++i)
			arr[i]=0;
		last=0;
	}
	void insert(const int &num)
	{
		if(last==size)
		{
			cout<<"Heap filled";
		}
		else
		{
			last++;
			int i;
			for(i=last;true;)
			{
				if(i==1)
					break;
				if(num>arr[i/2])
					break;
				arr[i]=arr[i/2];
				i=i/2;
			}
			arr[i]=num;
		}

	}
	int* remove(int &num)
	{
		int i=1;
		if(last==0)return nullptr;
		else
		{
			num=arr[i];
			int k=arr[last--];
			for(int j=2;j<=last;)
			{
				if(j>last)
				{
					if(arr[j]>arr[j+1])j++;
				}
				if(k<=arr[j])break;
				arr[i]=arr[j];
				i=j;
				j=j*2;
			}
			arr[i]=k;
		}
	}
	void print()
	{
		for(int i=1;i<=last;i++)
			cout<<arr[i]<<" ";
	}
};
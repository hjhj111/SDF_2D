
#pragma once
#include<vector>

using namespace std;

template<typename T>
class SinVector
{
public:
	

	SinVector():
		i_size_(0),
		j_size_(0),
		k_size_(0),
		jk_size_(0),
		len_(0)
	{
		;
	}

	SinVector(long long i_size,long long j_size, long long k_size, T default_value):
		i_size_(i_size),
		j_size_(j_size),
		k_size_(k_size),
		jk_size_(j_size*k_size),
		len_(i_size*j_size*k_size)
	{
		raw_vector.resize(len_,default_value);
	}	

	~SinVector()
	{
		;
	}

	T& at(long long i, long long j, long long k)
	{
		return raw_vector[i * jk_size_ + j * k_size_ + k];
	}

	long long i_size()
	{
		return i_size_;
	}

	long long j_size()
	{
		return j_size_;
	}

	long long k_size()
	{
		return k_size_;
	}

	void clear()
	{
		raw_vector.clear();
	}
private:
	vector<T> raw_vector;
	long long i_size_;
	long long j_size_;
	long long k_size_;
	long long jk_size_;
	long long len_;
};

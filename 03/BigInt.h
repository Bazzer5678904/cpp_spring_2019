#include<algorithm>
#include<memory>
#include<iostream>
class BigInt
{
private:
	char* number;
	bool sign;
	size_t size;
public:
	BigInt()
	{
		this->size = 1;
		this->number = new char[size];
		this->number[0] = '0';
		this->sign = true;
	}

	BigInt(const int64_t n)
	{
		if (n == 0)
		{
			this->size = 1;
			this->number = new char[size];
			this->number[0] = '0';
			this->sign = true;
		}
		else
		{
			size = 0;
			int64_t number_ = n;
			if (number_ < 0)
			{
				number_ *= -1;
				sign = false;
			}
			else
				sign = true;
			while (number)
			{
				size++;
				number_ /= 10;
			}
			number_ = n;
			this->number = new char[size];
			for (size_t i = 0; i < size; i++)
			{
				number[i] = abs(number_) % 10 + '0';
				number_ /= 10;
			}
		}
	}

	BigInt(const BigInt& copied)
		:size(copied.size), number(new char[copied.size]), sign(copied.sign)
	{
		std::copy(copied.number, copied.number + size, number);
	}

	~BigInt()
	{
		delete[] number;
	}

	BigInt& operator=(const BigInt& other)
	{
		if (this == &other)
			return *this;
		delete[] number;
		number = new char[other.size];
		size = other.size;
		sign = other.sign;
		std::copy(other.number, other.number + size, number);
		return *this;
	}

	BigInt& operator=(const int64_t& n)
	{
		if (n == 0)
		{
			sign = true;
			size = 1;
			number = new char[size];
			number[0] = '0';
		}
		size = 0;
		size = 0;
		int64_t number_ = n;
		if (number_ < 0)
		{
			number_ *= -1;
			sign = false;
		}
		else
			sign = true;
		while (number)
		{
			size++;
			number_ /= 10;
		}
		number_ = n;
		this->number = new char[size];
		for (size_t i = 0; i < size; i++)
		{
			number[i] = abs(number_) % 10 + '0';
			number_ /= 10;
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream &out, const BigInt &BigInt) {
		if (!BigInt.sign)
			out << "-";
		for (size_t i = BigInt.size; i > 0; i--)
			out << BigInt.number[i - 1];
		return out;
	}

	BigInt operator-() const
	{
		BigInt tmp(*this);
		if (this->number[0] == '0'  && this->size == 1)
			return tmp;
		tmp.sign = !sign;
		return tmp;
	}

	bool operator>(const BigInt& other) const {
		if (this == &other)
			return false;
		if (this->sign > other.sign || this->size > other.size)
			return true;
		if (this->sign < other.sign || this->size < other.size)
			return false;
		for (size_t i = this->size; i > 0; i--) {
			{
				if (this->number[i - 1] < other.number[i - 1])
				{
					if (this->sign == false)
						return true;
					else return false;
				}
				else if (this->number[i - 1] > other.number[i - 1])
				{
					if (this->sign == false)
						return false;
					else return true;
				}
			}
		}
		return false;
	}

	bool operator==(const BigInt& other) const
	{
		if (this == &other)
			return true;
		if (this->sign != other.sign || this->size != other.size)
			return false;
		for (size_t i = 0; i < size; ++i) {
			if (number[i] != other.number[i])
				return false;
		}
		return true;
	}

	bool operator!=(const BigInt& other) const 
	{
		return !(*this == other);
	}

	bool operator<(const BigInt& other) const
	{
		if (this == &other)
			return false;
		return !(*this > other && *this == other);
	}

	bool operator<=(const BigInt& other) const 
	{
		return *this < other || *this == other;
	}

	bool operator>=(const BigInt& other) const 
	{
		return *this > other || *this == other;
	}

	bool operator>(const int64_t& num) const
	{
		BigInt other = num;
		if (this == &other)
			return false;
		if (this->sign > other.sign || this->size > other.size)
			return true;
		if (this->sign < other.sign || this->size < other.size)
			return false;
		for (size_t i = this->size; i > 0; i--) 
		{
			if (this->number[i - 1] < other.number[i - 1])
			{
				if (this->sign == false)
					return true;
				else return false;
			}
			else if (this->number[i - 1] > other.number[i - 1])
			{
				if (this->sign == false)
					return false;
				else return true;
			}
		}
		return false;
	}

	bool operator==(const int64_t& n) const
	{
		BigInt other = n;
		if (this == &other)
			return true;
		if (this->sign != other.sign)
			return false;
		for (size_t i = 0; i < size; ++i)
			if (number[i] != other.number[i])
				return false;
		return true;
	}

	bool operator!=(const int64_t& n) const 
	{
		BigInt other = n;
		return !(*this == other);
	}

	bool operator<(const int64_t& n) const 
	{
		BigInt other = n;
		return !(*this > other && *this == other);
	}

	bool operator<=(const int64_t& n) const
	{
		BigInt other = n;
		return *this < other || *this == other;
	}

	bool operator>=(const int64_t& n) const 
	{
		BigInt other = n;
		return *this > other || *this == other;
	}

	BigInt absBig() const 
	{
		BigInt tmp(*this);
		tmp.sign = true;
		return tmp;
	}

	BigInt operator+(const BigInt& other) const {
		BigInt sum;
		sum.size = 0;
		sum.sign = true;
		delete[]sum.number;
		size_t newsize = 1;
		if (this->size > other.size)
			newsize += this->size;
		else
			newsize += other.size;
		std::unique_ptr<char[]>sum_(new char[newsize]);
		for (size_t i = 0; i < newsize; i++) 
			sum_[i] = '0';
		
		std::unique_ptr<char[]>newthis(new char[newsize - 1]);
		for (size_t i = 0; i < this->size; i++) 
			newthis[i] = this->number[i];
		
		for (size_t i = this->size; i < newsize - 1; i++) 
			newthis[i] = '0';

		std::unique_ptr<char[]>newother(new char[newsize - 1]);
		for (size_t i = 0; i < other.size; i++) 
			newother[i] = other.number[i];

		for (size_t i = other.size; i < newsize - 1; i++)
			newother[i] = '0';

		if (this->number[0] == '0' && other.number[0] == '0' && this->size == 1 && other.size == 1)
		{
			sum.sign = 1;
			sum.number[0] = '0';
			sum.size = 1;
			return sum;
		}
		if (this->sign != other.sign && *this == -other) 
		{
			newsize = 1;
			sum_[0] = '0';
			sum.sign = true;
			sum.size = newsize;
			sum.number = new char[newsize];
			sum.number[0] = sum_[0];
			return sum;
		}
		char tmp = '0';
		if (this->sign == other.sign) 
		{
			sum.sign = this->sign;
			for (size_t i = 0; i < newsize - 1; i++) 
			{
				tmp += (newthis[i] - '0') + (newother[i] - '0');
				sum_[i] = (tmp - '0') % 10 + '0';
				tmp = (tmp - '0') / 10 + '0';
			}
			if ((tmp - '0') == 1)
				sum_[newsize - 1] = 1 + '0';
			size_t s = 0;
			while (sum_[newsize - s - 1] == '0' && (newsize - s - 1) >= 0)
				s++;
			newsize -= s;
			sum.size = newsize;
			sum.number = new char[newsize];
			for (size_t i = 0; i < newsize; i++) 
				sum.number[i] = sum_[i];

			return sum;
		}
		else {
			if (absBig() > other.absBig()) 
			{
				sum.sign = this->sign;
				for (size_t i = 0; i < this->size; i++) 
					newthis[i] = '9' - newthis[i] + '0';
			}
			else 
			{
				sum.sign = other.sign;
				for (size_t i = 0; i < other.size; i++) 
					newother[i] = '9' - newother[i] + '0';
			}
			for (size_t i = 0; i < newsize - 1; i++) 
			{
				tmp += (newthis[i] - '0') + (newother[i] - '0');
				sum_[i] = (tmp - '0') % 10 + '0';
				tmp = (tmp - '0') / 10 + '0';

			}
			size_t s = 0;
			if ((tmp - '0') == 0)  s = 1;
			for (size_t i = 0; i < newsize - s; i++) 
				sum_[i] = '9' - sum_[i] + '0';
	
			while (sum_[newsize - s - 1] == '0' && (newsize - s - 1) >= 0)
				s++;
			newsize -= s;
		}
		size_t s = 0;
		while (sum_[newsize - s - 1] == '0' && (newsize - s - 1) >= 0)
			s++;
		newsize -= s;
		sum.size = newsize;
		sum.number = new char[newsize];
		for (size_t i = 0; i < newsize; i++) {
			sum.number[i] = sum_[i];
		}
		return sum;
	}
	BigInt operator+(const int64_t& n) const {
		BigInt other = n;
		return this->operator+(other);
	}
	BigInt operator-(const BigInt& other) const {
		return this->operator+(-(other));
	}
	BigInt operator-(const int64_t& n) const {
		BigInt other = n;
		return this->operator-(-(other));
	}
};

class proxy
{
private:
	size_t size;
	int* mas = nullptr;
public:
	proxy(){}
	proxy(size_t columns)
		:size(columns)
	{
		mas = new int[columns];
	}
	~proxy()
	{
		delete[](mas);
	}
	int& operator[](size_t i)
	{
		if (i >= size)
			throw std::out_of_range("");
		return mas[i];
	}
	const int& operator[](size_t i) const
	{
		if (i >= size)
			throw std::out_of_range("");
		return mas[i];
	}
};

class Matrix
{
private:
	size_t rows;
	size_t columns;
	proxy *mas_1 = nullptr;
public:
	Matrix(size_t rows, size_t columns)
		:rows(rows), columns(columns)
	{
		mas_1 = static_cast<proxy*>(operator new[](rows * sizeof(proxy)));
		for (size_t i = 0; i < rows; i++)
		{
			new (mas_1 + i) proxy(columns);
		}
	}
	~Matrix()
	{
		for (size_t i = 0; i < rows; i++)
		{
			mas_1[i].~proxy();
		}
		operator delete[](mas_1);
	}
	size_t getRows()
	{
		return rows;
	}
	size_t getColumns()
	{
		return columns;
	}
	proxy& operator[](size_t i)
	{
		if (i >= rows)
			throw std::out_of_range("");
		return mas_1[i];
	}
	const proxy& operator[](size_t i) const
	{
		if (i >= rows)
			throw std::out_of_range("");
		return mas_1[i];
	}
	Matrix &operator*=(int digit)
	{
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < columns; j++)
				mas_1[i][j] = mas_1[i][j] * digit;
		}
		return *this;
	}
	bool operator==(const Matrix& another)
	{
		if (columns != another.columns || rows != another.rows)
			return false;
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < columns; j++)
			{
				if (mas_1[i][j] != another.mas_1[i][j])
					return false;
			}
		}
		return true;
	}
	bool operator!=(const Matrix& another)
	{
		return !(mas_1 == another.mas_1);
	}
};

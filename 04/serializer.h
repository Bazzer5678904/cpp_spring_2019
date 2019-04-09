#pragma once
#include<iostream>
#include<string>

enum class Error
{
	NoError,
	CorruptedArchive
};

class Serializer
{
public:
	explicit Serializer(std::ostream& out)
		: out_(out) {}
	template <class T>
	Error save(T& obj)
	{
		return obj.serialize(*this);
	}
	template <class... Args>
	Error operator()(Args&&... args)
	{
		return execution(std::forward<Args>(args)...);
	}

private:
	std::ostream& out_;
	template <class T, class... Args>

	Error execution(T&& val, Args&&... args)
	{
		if (execution(std::forward<T>(val)) == Error::CorruptedArchive) {
			return Error::CorruptedArchive;
		}
		return execution(std::forward<Args>(args)...);
	}

	Error execution(bool val)
	{
		out_ << (val ? "true" : "false") << ' ';
		return Error::NoError;
	}

	Error execution(uint64_t val)
	{
		out_ << val << ' ';
		return Error::NoError;
	}
};

class Deserializer
{
public:
	explicit Deserializer(std::istream& in)
		: in_(in) {}
	template <class T>
	Error load(T& obj)
	{
		return obj.serialize(*this);
	}

	template <class... Args>
	Error operator()(Args&&... args)
	{
		return execution(std::forward<Args>(args)...);
	}

private:
	std::istream& in_;
	template <class T, class ...Args>
	Error execution(T&& val, Args&&... args)
	{
		if (execution(std::forward<T>(val)) == Error::CorruptedArchive)
			return Error::CorruptedArchive;
		else return execution(std::forward<Args>(args)...);
	}

	Error process(bool& val)
	{
		std::string text;
		in_ >> text;
		if (text == "true")
			val = true;
		else if (text == "false")
			val = false;
		else
			return Error::CorruptedArchive;
		return Error::NoError;
	}

	Error execution(uint64_t& val)
	{
		std::string text;
		in_ >> text;
		val = 0;
		for (size_t i = 0; i < text.size(); i++)
			if (isdigit(text[i]))
				val = val * 10 + text[i] - '0';
			else
				return Error::CorruptedArchive;
		return Error::NoError;
	}
};

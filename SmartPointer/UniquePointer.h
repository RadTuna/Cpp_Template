#pragma once


template<typename T>
class UniquePointer
{
public:

	explicit UniquePointer() = default;
	explicit UniquePointer(const UniquePointer& other) = delete;
	UniquePointer(UniquePointer&& other) noexcept; // lRef -> rRef의 암시적 호출을 이용함.
	~UniquePointer();

	inline T* operator->() noexcept { return RawPointer; }
	inline UniquePointer<T>& operator=(const UniquePointer& other) = delete;
	inline UniquePointer<T>&& operator=(UniquePointer&& other) noexcept;

private:

	template<typename ...Args>
	void NewPointer(Args&&... InArgs);

	template<typename T, typename ...Args>
	friend UniquePointer<T> MakeUniquePointer(Args&&... InArgs);

private:

	T* RawPointer;

};

template<typename T>
UniquePointer<T>::UniquePointer(UniquePointer&& other) noexcept
{
	RawPointer = other.RawPointer;
	other.RawPointer = nullptr;
}

template<typename T>
UniquePointer<T>::~UniquePointer()
{
	if (RawPointer != nullptr)
	{
		delete RawPointer;
		RawPointer = nullptr;
	}
}

template<typename T>
inline UniquePointer<T>&& UniquePointer<T>::operator=(UniquePointer&& other) noexcept
{
	RawPointer = other.RawPointer;
	other.RawPointer = nullptr;
	return std::move(*this);
}

template<typename T>
template<typename ...Args>
void UniquePointer<T>::NewPointer(Args&& ...InArgs)
{
	RawPointer = new T(InArgs...);
}

template<typename T, typename ...Args>
UniquePointer<T> MakeUniquePointer(Args&&... InArgs)
{
	UniquePointer<T> TempUnique;
	TempUnique.NewPointer(InArgs...);
	return TempUnique;
}


#pragma once

#include <typeinfo>

template<typename Fn, typename... Args>
class Delegate
{
public:

	Delegate();
	~Delegate() = default;
	Delegate(const Delegate& other) = delete;

	void Execute(Args... InArgs);
	void BindDelegate(Fn InFunc);
	void UnBindDelegate();

private:

	Fn* FuncPtr;

};

template<typename Fn, typename ...Args>
inline Delegate<Fn, Args...>::Delegate()
	: FuncPtr(nullptr)
{
}

template<typename Fn, typename ...Args>
void Delegate<Fn, Args...>::Execute(Args... InArgs)
{
	if (FuncPtr == nullptr)
	{
		return;
	}

	FuncPtr(InArgs...);
}

template<typename Fn, typename ...Args>
void Delegate<Fn, Args...>::BindDelegate(Fn InFunc)
{
	if (InFunc == nullptr)
	{
		return;
	}

	FuncPtr = InFunc;
}

template<typename Fn, typename ...Args>
void Delegate<Fn, Args...>::UnBindDelegate()
{
	FuncPtr = nullptr;
}


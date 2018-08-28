/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ISafeQueue
*/

#ifndef ISafeQueue_hpp
	#define ISafeQueue_hpp

# include <iostream>

template<typename U>
class ISafeQueue
{
public:
	virtual ~ISafeQueue() = default;
	virtual void push(U) = 0;
	virtual U pop() = 0;
	virtual bool tryPop(U &) = 0;
	virtual bool waitPop(U &) = 0;
	virtual bool empty() const = 0;
	virtual void clear() = 0;
	virtual bool isValidate() const = 0;
	virtual void destroy() = 0;
private:
};

#endif /* ISafeQueue_hpp */

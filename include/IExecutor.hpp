/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** IExecutor
*/

#ifndef IExecutor_hpp
	#define IExecutor_hpp

# include <iostream>

class IExecutor
{
public:
	IExecutor(void) = default;
	virtual ~IExecutor() = default;
	IExecutor(const IExecutor& rhs) = delete;
	IExecutor& operator=(const IExecutor& rhs) = delete;
	IExecutor(IExecutor&& other) = default;
	IExecutor& operator=(IExecutor&& other) = default;
	virtual void run() = 0;
private:
};

#endif /* IExecutor_hpp */

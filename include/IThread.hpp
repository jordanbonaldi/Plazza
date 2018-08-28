/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** IThread
*/

#ifndef IThread_hpp
	#define IThread_hpp

template<class U>
class IThread
{
public:
	virtual ~IThread() = default;

	virtual IThread &action(U) = 0;
	virtual IThread &run() = 0;
	virtual IThread &join() = 0;
	virtual bool isJoinable() const = 0;
private:
};

#endif /* IThread_hpp */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:53:37 by gpetit            #+#    #+#             */
/*   Updated: 2021/10/22 13:58:52 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

Warlock::Warlock(void){
	std::cout << "Shouldn't be there" << std::endl;
	return;
}
		
Warlock::Warlock(std::string const name, std::string const title) : _name(name), _title(title)
{
	std::cout << _name << ": This looks like another boring day." << std::endl;
	return ;
}
		
Warlock::~Warlock( void ){
	std::cout << _name << ": My job here is done!" << std::endl;
	return ;
}

Warlock::Warlock ( Warlock const & src){
	*this = src;
}

Warlock & Warlock::operator=( Warlock const & rhs){
	if (&rhs == this)
		return *this;
	_title = rhs.getTitle();
	_name = rhs.getName();
	return *this;
}
		
std::string const & Warlock::getName( void ) const{
	return (this->_name);
}

std::string const & Warlock::getTitle( void ) const{
	return (this->_title);
}

void Warlock::setTitle( std::string const & src){
	_title = src;
}

void	Warlock::introduce( void ) const{
	std::cout << _name << ": I am " << _name << ", " << _title << " !" << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpellBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:32:51 by gpetit            #+#    #+#             */
/*   Updated: 2021/10/26 23:08:10 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SpellBook.hpp"

using std::string;
typedef std::map<std::string, ASpell*>::iterator iterator;

SpellBook::SpellBook( void ){
	return ;
}

SpellBook::~SpellBook( void ){
	iterator itstart = _spellBook.begin();
	iterator itend = _spellBook.end();

	for (; itstart != itend; itstart++)
	{
		delete itstart->second;
		_spellBook.erase(itstart);
	}
	return ;
}
	
void	SpellBook::learnSpell(ASpell * ptr){
	if (!ptr)
		return;
	
	iterator it = _spellBook.find(ptr->getName());
	if (it == _spellBook.end())
		_spellBook.insert(std::pair<string, ASpell*>(ptr->getName(), ptr->clone()));
}


void	SpellBook::forgetSpell(std::string const &str){

	iterator it = _spellBook.find(str);
	if (it != _spellBook.end())
	{
		delete it->second;
		_spellBook.erase(it);
	}
}

ASpell*	SpellBook::createSpell(std::string const & spell)
{
	iterator it = _spellBook.find(spell);
	if (it != _spellBook.end())
		return it->second->clone();
	return NULL;
}


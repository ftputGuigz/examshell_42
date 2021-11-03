/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpellBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:29:01 by gpetit            #+#    #+#             */
/*   Updated: 2021/10/26 23:01:43 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "ASpell.hpp"
# include <vector>
# include <map>
# include "Fireball.hpp"
# include "Polymorph.hpp"
# include "Fwoosh.hpp"

class SpellBook{
	public:
		SpellBook( void );
		virtual ~SpellBook( void );

	
		void	learnSpell(ASpell *);
		void	forgetSpell(std::string const & spell);
		ASpell * createSpell(std::string const & spell);

	private:
		std::map<std::string, ASpell *> _spellBook;

		SpellBook & operator=( SpellBook const & rhs );
		SpellBook( SpellBook const & cpy );
};

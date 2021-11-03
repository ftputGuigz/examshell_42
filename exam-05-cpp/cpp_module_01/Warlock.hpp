/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:40:28 by gpetit            #+#    #+#             */
/*   Updated: 2021/10/22 16:10:24 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <string>
# include <iostream>
# include <vector>
# include "ATarget.hpp"

class Warlock{

	public:
		Warlock(std::string const name, std::string const title);
		virtual ~Warlock( void );
		Warlock ( Warlock const & src);

		Warlock & operator=( Warlock const & rhs);
		
		std::string const & getName( void ) const;
		std::string const & getTitle( void ) const;
		void setTitle( std::string const & src);
	
		void	introduce( void ) const;

		void	learnSpell(ASpell * ptr);
		void	forgetSpell(std::string str);
		void	launchSpell(std::string spell, ATarget const & target);

	private :
		Warlock( void );
		std::string			_name;
		std::string			_title;
		std::vector<ASpell *> _spellBook;
};

#endif


#ifndef ATARGET_HPP
# define ATARGET_HPP

# include <string>
# include <iostream>
# include "ASpell.hpp"

class ASpell;

class ATarget{

	public:
		ATarget(void);
		ATarget(std::string const name);
		virtual ~ATarget( void );
		ATarget ( ATarget const & src);

		ATarget & operator=( ATarget const & rhs);
		
		std::string const & getType( void ) const;
		
		void	getHitBySpell(ASpell const & src) const;
		
		virtual ATarget * clone( void ) const = 0;

	protected :
		std::string _type;
};

#endif

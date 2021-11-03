#pragma once

# include "ASpell.hpp"

class Fwoosh : public ASpell
{
	public:
	Fwoosh( void ) : ASpell("Fwoosh", "fwooshed"){};
	virtual ~Fwoosh(){};
	Fwoosh(Fwoosh const & src){*this = src;};

	Fwoosh & operator=(Fwoosh const & rhs){
		(void) rhs;
		return *this;
	};

	Fwoosh * clone( void ) const{
		Fwoosh *cpy = new Fwoosh(*this);
		return cpy;
	};
};


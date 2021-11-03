#pragma once

# include "ASpell.hpp"

class Fireball : public ASpell
{
	public:
	Fireball( void ) : ASpell("Fireball", "burnt to a crisp"){};
	virtual ~Fireball(){};
	Fireball(Fireball const & src): ASpell("Fireball", "burnt to a crisp"){*this = src;};

	Fireball & operator=(Fireball const & rhs){
		(void) rhs;
		return *this;
	};

	ASpell * clone( void ) const{
		return (new Fireball());
	};
};

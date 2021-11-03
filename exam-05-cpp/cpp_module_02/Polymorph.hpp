#pragma once

# include "ASpell.hpp"

class Polymorph : public ASpell
{
	public:
	Polymorph( void ) : ASpell("Polymorph", "turned into a critter"){};
	virtual ~Polymorph(){};
	Polymorph(Polymorph const & src) : ASpell("Polymorph", "turned into a critter"){*this = src;};

	Polymorph & operator=(Polymorph const & rhs){
		(void) rhs;
		return *this;
	};

	ASpell * clone( void ) const{
		return (new Polymorph());
	};
};

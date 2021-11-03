
#pragma once

# include "ATarget.hpp"

class Dummy : public ATarget
{
	public :
		Dummy( void ) : ATarget("Target Practice Dummy"){};
		virtual ~Dummy(){};
		Dummy(Dummy const & src){*this = src;};

		Dummy & operator=(Dummy const & rhs){
			(void) rhs;
			return *this;
		};

		Dummy * clone( void ) const{
			Dummy *cpy = new Dummy(*this);
			return cpy;
		};
};


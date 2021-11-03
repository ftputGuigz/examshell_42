#pragma once

# include "ATarget.hpp"

class BrickWall : public ATarget
{
	public :
		BrickWall( void ) : ATarget("Inconspicuous Red-brick Wall"){};
		virtual ~BrickWall(){};
		BrickWall(BrickWall const & src) : ATarget("Inconspicuous Red-brick Wall"){*this = src;};

		BrickWall & operator=(BrickWall const & rhs){
			(void) rhs;
			return *this;
		};

		ATarget * clone( void ) const{
			return (new BrickWall(*this));
		};
};


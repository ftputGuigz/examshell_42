#include "ATarget.hpp"

ATarget::ATarget(void){
	return;
}
		
ATarget::ATarget(std::string const name) : _type(name)
{
	return ;
}
		
ATarget::~ATarget( void ){
	return ;
}

ATarget::ATarget ( ATarget const & src){
	*this = src;
}

ATarget & ATarget::operator=( ATarget const & rhs){
	if (&rhs == this)
		return *this;
	_type = rhs.getType();
	return *this;
}

std::string const & ATarget::getType( void ) const{
	return (this->_type);
}

void	ATarget::getHitBySpell(ASpell const & src) const
{
	std::cout << _type << " has been " << src.getEffects() << std::endl;
}

#include "ASpell.hpp"

ASpell::ASpell(void){
	return;
}
		
ASpell::ASpell(std::string const name, std::string const effects) : _name(name), _effects(effects)
{
	return ;
}
		
ASpell::~ASpell( void ){
	return ;
}

ASpell::ASpell ( ASpell const & src){
	*this = src;
}

ASpell & ASpell::operator=( ASpell const & rhs){
	if (&rhs == this)
		return *this;
	_effects = rhs.getEffects();
	_name = rhs.getName();
	return *this;
}
		
std::string ASpell::getName( void ) const{
	return (this->_name);
}

std::string ASpell::getEffects( void ) const{
	return (this->_effects);
}

void	ASpell::launch(ATarget const & rhs){
	rhs.getHitBySpell(*this);
}

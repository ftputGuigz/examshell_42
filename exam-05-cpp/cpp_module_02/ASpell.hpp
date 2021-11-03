#ifndef ASPELL_HPP
# define ASPELL_HPP

# include <string>
# include <iostream>
# include "ATarget.hpp"

class ATarget;

class ASpell{

	public:
		ASpell(void);
		ASpell(std::string const name, std::string const effects);
		virtual ~ASpell( void );
		ASpell ( ASpell const & src);

		ASpell & operator=( ASpell const & rhs);
		
		std::string getName( void ) const;
		std::string getEffects( void ) const;
		
		void	launch(ATarget const & rhs);


		virtual ASpell * clone( void ) const = 0;

	protected :
		std::string _name;
		std::string	_effects;
};

	
#endif

#pragma once

class TargetGenerator{
	public :
		TargetGenerator(void){};
		~TargetGenerator(void){
			std::vector<ATarget *>::iterator it = _targetPool.begin();
			std::vector<ATarget *>::iterator itend = _targetPool.end();
	
			for (; it != itend; it++)
			{
				if (*it)
					delete *it;
			}
			_targetPool.clear();
		};

		void	learnTargetType( ATarget* trg){
			_targetPool.push_back(trg->clone());
		};

		void	forgetTargetType( std::string const & str){
			std::vector<ATarget *>::iterator it = _targetPool.begin();
			std::vector<ATarget *>::iterator itend = _targetPool.end();
	
			for (; it != itend; it++)
			{
				ATarget *tmp = *it;
				if (tmp->getType() == str)
				{
					delete *it;
					_targetPool.erase(it);
					return ;
				}
			}
		};
		
		ATarget *	createTarget( std::string const & str){
			typedef std::vector<ATarget *>::iterator iterator;

			iterator it = _targetPool.begin();
			iterator it_end = _targetPool.end();
			for (; it != it_end; it++)
			{
				if (str == (*it)->getType())
					return ((*it)->clone());
			}
			return NULL;
		};

	private:
		std::vector<ATarget *> _targetPool;
		TargetGenerator(TargetGenerator const & src){(void) src; return;};
		TargetGenerator & operator=(TargetGenerator  const & rhs) {(void) rhs; return *this;}
};


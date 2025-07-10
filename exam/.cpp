Warlock();
Warlock(Warlock const &other)
Warlock &operator=(Warlock const &other)



Warlock(std::string & name, std::string & title)
~Warlock();

std::string const & getName() const;
std::string const & getTitle() const;

void setTitle(std::string const & title);

void introduce() const;

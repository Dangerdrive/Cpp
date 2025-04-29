#ifndef IDENTIFICATION_HPP
#define IDENTIFICATION_HPP

class Base {
public:
    virtual ~Base();
};

class A;
class B;
class C;

Base* generate(void);
void identify(Base* p);
void identify(Base& p);

#endif
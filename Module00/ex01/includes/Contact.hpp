#ifndef CONTACT_CLASS_H
# define CONTACT_CLASS_H

#include <string>

class Contact {

private:
    std::string name;
    std::string last_name;
    std::string nickname;
    std::string phonenumber;
    std::string darkest_secret;

public:
    Contact();
    ~Contact();

    void setFirstName(const std::string& name);
    void setLastName(const std::string& name);
    void setNickname(const std::string& name);
    void setPhoneNumber(const std::string& number);
    void setDarkestSecret(const std::string& secret);

    void setField(const std::string& field);

    std::string getName() const;
    std::string getLastName() const;
    std::string getNickname() const;
    std::string getPhoneNumber() const;
    std::string getDarkestSecret() const;
};

#endif

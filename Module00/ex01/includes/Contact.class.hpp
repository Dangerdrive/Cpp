#ifndef CONTACT_CLASS_H
# define CONTACT_CLASS_H

#include <string>

class Contact {

private:
    int ContactIndex;
    std::string first_name;
    std::string last_name;
    std::string nickname;
    std::string phonenumber;
    std::string darkest_secret;

public:
    Contact();
    ~Contact();

    // Setters
    void setFirstName(const std::string& name);
    void setLastName(const std::string& name);
    void setNickname(const std::string& name);
    void setPhoneNumber(const std::string& number);
    void setDarkestSecret(const std::string& secret);

    void setField(const std::string& field);

    // Getters
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getNickname() const;
    std::string getPhoneNumber() const;
    std::string getDarkestSecret() const;
};

#endif
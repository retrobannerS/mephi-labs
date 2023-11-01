#ifndef LAB3_PERSON_H
#define LAB3_PERSON_H
#include <string>
#include <iostream>

using namespace std;

namespace lab3 {

    struct PersonID {
        int serial;
        int number;
    };

    class Person {
    private:
        PersonID id_{};
        string first_name_;
        string middle_name_;
        string last_name_;
        string address_;
        string phone_number_;
    public:
        Person();
        Person(const PersonID &id, string first_name, string middle_name, string last_name,
               string address, string phone_number);
        Person(const Person &other);
        ~Person();

        Person &operator=(const Person &other);

        [[nodiscard]] const PersonID &id() const;
        [[nodiscard]] const string &first_name() const;
        [[nodiscard]] const string &middle_name() const;
        [[nodiscard]] const string &last_name() const;
        [[nodiscard]] const string &address() const;
        [[nodiscard]] const string &phone_number() const;

        void set_id(const PersonID &id);
        void set_first_name(const string &first_name);
        void set_middle_name(const string &middle_name);
        void set_last_name(const string &last_name);
        void set_address(const string &address);
        void set_phone_number(const string &phone_number);

        friend ostream &operator<<(ostream &os, const Person &p) {
            os << "ID: " << p.id_.serial << "-" << p.id_.number << endl;
            os << "Name: " << p.first_name_ << " " << p.middle_name_ << " " << p.last_name_ << endl;
            os << "Address: " << p.address_ << endl;
            os << "Phone number: " << p.phone_number_ << endl;
            return os;
        }
        friend istream &operator>>(istream &is, Person &p) {
            cout << "Enter ID: ";
            is >> p.id_.serial >> p.id_.number;
            cout << "Enter first name: ";
            is >> p.first_name_;
            cout << "Enter middle name: ";
            is >> p.middle_name_;
            cout << "Enter last name: ";
            is >> p.last_name_;
            cout << "Enter address: ";
            is >> p.address_;
            cout << "Enter phone number: ";
            is >> p.phone_number_;
            return is;
        }

        friend bool operator==(const Person &lhs, const Person &rhs) {
            return lhs.id_.serial == rhs.id_.serial && lhs.id_.number == rhs.id_.number;
        }
        friend bool operator!=(const Person &lhs, const Person &rhs) {
            return !(lhs == rhs);
        }
        bool operator <(const Person &rhs) const {
            return id_.serial < rhs.id_.serial or (id_.serial == rhs.id_.serial and id_.number < rhs.id_.number);
        }
        bool operator >(const Person &rhs) const {
            return rhs < *this;
        }
    };

} // lab3

#endif //LAB3_PERSON_H

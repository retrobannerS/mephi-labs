#include "Person.h"
#include <string>
#include <utility>

namespace lab3 {
    Person::Person() {
        id_ = {0, 0};
        first_name_ = "";
        middle_name_ = "";
        last_name_ = "";
        address_ = "";
        phone_number_ = "";
    }
    Person::Person(const lab3::PersonID &id, std::string first_name, std::string middle_name,
                   std::string last_name, std::string address, std::string phone_number) :
        id_(id), first_name_(std::move(first_name)), middle_name_(std::move(middle_name)),
        last_name_(std::move(last_name)), address_(std::move(address)),
        phone_number_(std::move(phone_number)) {}

    Person::Person(const Person &other) = default;
    Person::~Person() = default;

    Person &Person::operator=(const Person &other) = default;

    const PersonID &Person::id() const {
        return id_;
    }
    const std::string &Person::first_name() const {
        return first_name_;
    }
    const std::string &Person::middle_name() const {
        return middle_name_;
    }
    const std::string &Person::last_name() const {
        return last_name_;
    }
    const std::string &Person::address() const {
        return address_;
    }
    const std::string &Person::phone_number() const {
        return phone_number_;
    }

    void Person::set_id(const PersonID &id) {
        id_ = id;
    }
    void Person::set_first_name(const std::string &first_name) {
        first_name_ = first_name;
    }
    void Person::set_middle_name(const std::string &middle_name) {
        middle_name_ = middle_name;
    }
    void Person::set_last_name(const std::string &last_name) {
        last_name_ = last_name;
    }
    void Person::set_address(const std::string &address) {
        address_ = address;
    }
    void Person::set_phone_number(const std::string &phone_number) {
        phone_number_ = phone_number;
    }
} // lab3
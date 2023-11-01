#include "gtest/gtest.h"
#include "Data_types/Person.h"
#include "Collections/PriorityQueue.hpp"
#include "Collections/Set.hpp"

using namespace lab3;
using namespace std;

TEST(Person, allTests) {
    //arrange&act
    PersonID id = {6288, 738287};
    Person p1(id, "Ivan", "Ivanovich", "Ivanov", "Moscow", "+7999299");
    //assert
    EXPECT_EQ(p1.id().serial, 6288);
    EXPECT_EQ(p1.id().number, 738287);
    EXPECT_EQ(p1.first_name(), "Ivan");
    EXPECT_EQ(p1.middle_name(), "Ivanovich");
    EXPECT_EQ(p1.last_name(), "Ivanov");
    EXPECT_EQ(p1.address(), "Moscow");
    EXPECT_EQ(p1.phone_number(), "+7999299");
}

TEST(PersonWithPriorityQueue, allTests) {
    //arrange
    PersonID id = {6288, 738287};
    Person p1(id, "Ivan", "Ivanovich", "Ivanov", "Moscow", "+7999329");
    Person p2(id, "Alexander", "Ivanovich", "Ivanov", "Saratov", "+79312");
    Person p3(id, "Inokentiy", "Ivanovich", "Ivanov", "SPB", "+7992321");
    pair<Person, int> pairs[3] = {make_pair(p1, 3), make_pair(p2, 2), make_pair(p3, 1)};
    //act
    PriorityQueue<Person> queue(3, pairs);
    //assert
    EXPECT_EQ(queue.top().first, p3);
    queue.pop();
    EXPECT_EQ(queue.top().first, p2);
    queue.pop();
    EXPECT_EQ(queue.top().first, p1);
}

TEST(PersonsWithSet, allTests) {
    Set<Person> set;
    PersonID id = {6288, 738287};
    PersonID id2 = {6288, 738288};
    PersonID id3 = {6288, 738289};
    Person p1(id, "Ivan", "Ivanovich", "Ivanov", "Moscow", "+7999329");
    Person p2(id2, "Alexander", "Ivanovich", "Ivanov", "Saratov", "+79312");
    Person p3(id3, "Inokentiy", "Ivanovich", "Ivanov", "SPB", "+7992321");
    set.add(p1);
    set.add(p2);
    set.add(p3);
    EXPECT_EQ(set.power(), 3);
    EXPECT_EQ(set.contains(p1), true);
    EXPECT_EQ(set.contains(p2), true);
    EXPECT_EQ(set.contains(p3), true);
}


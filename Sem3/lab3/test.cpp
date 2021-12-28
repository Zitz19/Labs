#include <gtest/gtest.h>
#include "include/table.h"

TEST(Constructors_Test, test1)
{
    Table table1;
    Daytime daytime1 = Daytime(0, 12, 4, "ICT", 14, 2800, 3) ;
    Evening evening1 = Evening(1, 22, 4, "PI", 8, 25, "Engineering");
    Commercial commercial1 = Commercial(2, 42, 4, "IS", 7, 2021, 70000);
}

TEST(Functions_Test, test1)
{
    Table table;
    table.addGroup("Daytime", 18, 12, 4, "ICS", "30000 5");
    table.printTable();
}

TEST(SettersGetters_Test, test1)
{
    Daytime daytime1 = Daytime(0, 12, 4, "ICT", 14, 2800, 3);
    EXPECT_EQ(daytime1.getIndex(), 0);
    EXPECT_EQ(daytime1.getSpecialization(), "ICT");
    EXPECT_EQ(daytime1.getTerm(), 4);
    EXPECT_EQ(daytime1.getKaf(), 12);
    daytime1.setNum(15);
    EXPECT_EQ(daytime1.getNum(), 15);
    daytime1.setScholarship(3200);
    EXPECT_EQ(daytime1.getScholarship(), 3200);
    Commercial commercial1 = Commercial(2, 42, 4, "IS", 7, 2021, 70000);
    commercial1.setPrice(50000);
    EXPECT_EQ(commercial1.getPrice(), 50000);
}

TEST(MapTest, test1)
{
    Map<int, std::string> myMap;
    myMap.emplaceMap(1, "One");
    myMap.emplaceMap(2, "Two");
    myMap.emplaceMap(3, "Three");
    Iterator<int, std::string> it = myMap.begin();
    EXPECT_EQ((*it).second, "One");
    EXPECT_EQ((*(++it)).second, "Two");
    EXPECT_EQ((*(++it)).second, "Three");
    myMap.eraseMap(myMap.findMap(2));
    it = myMap.begin();
    EXPECT_EQ((*it).second, "One");
    EXPECT_EQ((*(++it)).second, "Three");
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
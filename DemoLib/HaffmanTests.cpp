#include <iostream>
#include <gtest/gtest.h>
#include "HaffmanClass.h"

using namespace std;

TEST(HaffManTest, FirstTest) {
    string input = "beep boop beer!";
    string newString, newString2;
    HaffmanAlgothrim testValue(input);
    newString = testValue.codding();
    newString2 = testValue.haffmanDecrypt(newString);
    ASSERT_EQ(input, newString2);
}

TEST(HaffManTest, SecondTest) {
    string input = "The Battle of the Kerch Peninsula, which commenced with the Soviet Kerch-Feodosia landing operation";
    string newString, newString2;
    HaffmanAlgothrim testValue(input);
    newString = testValue.codding();
    newString2 = testValue.haffmanDecrypt(newString);
    ASSERT_EQ(input, newString2);
}

TEST(HaffManTest, ThirdTest) {
    string input = "'My uncle, man of firm convictions By falling gravely ill, he's won A due respect for his afflictions The only clever thing he's done. May his example profit others; But God, what deadly boredom, brothers, To tend a sick man night and day, Not daring once to steal away! And, oh, how base to pamper grossly And entertain the nearly dead, To fluff the pillows for his head, And pass him medicines morosely While thinking under every sigh: The devil take you, Uncle. Die!' ";
    string newString, newString2;
    HaffmanAlgothrim testValue(input);
    newString = testValue.codding();
    newString2 = testValue.haffmanDecrypt(newString);
    ASSERT_EQ(input, newString2);
}

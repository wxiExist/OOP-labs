#include "laba5.cpp"
#include "gtest/gtest.h"

struct A {
    int a;
    int b;
    int c;
    A(int a, int b, int c) : a(a), b(b), c(c) {}
    bool operator==(const A& other) const {
        return a == other.a && b == other.b && c == other.c;
    }
};

TEST(DynamicArrayTest, Test1) {
  
  DynamicArray<int> v;

    for (auto i = 0; i < 100; ++i) v.push_back(i);

  ASSERT_EQ(100, v.size());
  ASSERT_EQ(99, v[99]);
  ASSERT_EQ(0, v[0]);

}

TEST(DynamicArrayTest, Test2) {
  DynamicArray<int> v;

  v.reserve(10);
  ASSERT_EQ(0, v.size());

}



TEST(DynamicArrayTest, Test3) {
   
   DynamicArray<int> v;

    int a = 0;

  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);


  for (int i : v) {
    ASSERT_EQ(i, a++);
  }
}


TEST(DynamicArrayTest, Test4) {
   
   DynamicArray<A> v;

    v.push_back((A{1, 2, 3}));
    v.push_back((A{2, 4, 5}));

    ASSERT_EQ(2, v.size());
    ASSERT_EQ((A{1, 2, 3}), v[0]);
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

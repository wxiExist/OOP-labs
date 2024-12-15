
#include "gtest/gtest.h"

#include "src/npc.hpp"

TEST(NPCTest, Test1) {
    
    auto a = std::make_shared<Dragon>("a", 0, 0);
    auto b = std::make_shared<Princess>("b", 1, 0);
    auto c = std::make_shared<Knight>("c", 0, 1);

    ASSERT_TRUE(a->accept(c));
    ASSERT_FALSE(a->accept(b));
    ASSERT_FALSE(c->accept(b));

    ASSERT_FALSE(c->accept(c));
    ASSERT_FALSE(b->accept(b));
    ASSERT_FALSE(a->accept(a));
}


TEST(NPCTest, Test2) {
    
    auto a = std::make_shared<Dragon>("a", 0, 0);
    auto b = std::make_shared<Princess>("b", 100, 100);
    auto c = std::make_shared<Princess>("c", 1, 1);

    ASSERT_FALSE(a->is_close(b, 50));
    ASSERT_TRUE(a->is_close(c, 100));
}


TEST(VTest, Test3) {
    
    auto a = std::make_shared<Dragon>("a", 0, 0);
    auto b = std::make_shared<Princess>("b", 1, 0);
    auto c = std::make_shared<Knight>("c", 0, 1);

    std::shared_ptr<Visitor> dv, pv, kv;

    ASSERT_TRUE(kv->visit(std::static_pointer_cast<Dragon>(a)));
    ASSERT_FALSE(dv->visit(std::static_pointer_cast<Princess>(b)));
    ASSERT_FALSE(pv->visit(std::static_pointer_cast<Knight>(c)));

    ASSERT_FALSE(pv->visit(std::static_pointer_cast<Dragon>(a)));
    ASSERT_FALSE(pv->visit(std::static_pointer_cast<Princess>(b)));
    ASSERT_FALSE(pv->visit(std::static_pointer_cast<Knight>(c)));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
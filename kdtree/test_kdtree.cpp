#define EXCLUDE_MAIN
#include "kdtree.c"
#include <gtest/gtest.h>


class KDTest : public testing::Test {
  protected:
    kd_node_t *root=nullptr;
    void SetUp() override {
    }
    void TearDown() override{
      kd_destroy(root);  
    }
};

TEST_F(KDTest, InsertRoot){
  ASSERT_EQ(root,nullptr);
  kd_key_t key={1,2};
  root=kd_insert(root,&key,42.0);
}

TEST_F(KDTest, Insert){
}

TEST_F(KDTest, Delete){
}

TEST_F(KDTest, Find){
}
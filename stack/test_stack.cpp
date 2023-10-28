#define EXCLUDE_MAIN
#include "stack.c"
#include <gtest/gtest.h>

DEFINE_STACK(int)

class StackTest : public testing::Test {
  protected:
    int_stack_t *s=nullptr;
    void SetUp() override {
      s=int_stack_create();
    }
    void TearDown() override{
      int_stack_destroy(s);  
    }
};

TEST_F(StackTest, Creation){
  ASSERT_NE(s,nullptr);
  ASSERT_EQ(s->size, 0);
  ASSERT_EQ(s->max_size, DEFAULT_MAX_STACK_SIZE);
}

TEST_F(StackTest, PushPop){
  int_stack_push(s,1);
  int_stack_push(s,2);
  int_stack_push(s,3);
  ASSERT_EQ(int_stack_pop(s),3);
  ASSERT_EQ(int_stack_pop(s),2);
  ASSERT_EQ(int_stack_pop(s),1);
}

TEST_F(StackTest, Expand){
  for(int i=0; i<DEFAULT_MAX_STACK_SIZE; i++){
    int_stack_push(s,i);
  }
  ASSERT_EQ(s->max_size,DEFAULT_MAX_STACK_SIZE);
  int_stack_push(s,DEFAULT_MAX_STACK_SIZE);
  ASSERT_GT(s->max_size,DEFAULT_MAX_STACK_SIZE);
}
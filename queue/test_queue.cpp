#define EXCLUDE_MAIN
#include "queue.c"
#include <gtest/gtest.h>

DEFINE_QUEUE(int)

class QueueTest : public testing::Test {
  protected:
    int_queue_t *q=nullptr;
    void SetUp() override {
      q=int_queue_create();
    }
    void TearDown() override{
      int_queue_destroy(q);  
    }
};

TEST_F(QueueTest, Creation){
  ASSERT_NE(q,nullptr);
  ASSERT_EQ(q->size, 0);
  ASSERT_EQ(q->max_size, DEFAULT_MAX_QUEUE_SIZE);
}

TEST_F(QueueTest, PushPop){
  int_queue_push(q,1);
  int_queue_push(q,2);
  int_queue_push(q,3);
  ASSERT_EQ(int_queue_pop(q),1);
  ASSERT_EQ(int_queue_pop(q),2);
  ASSERT_EQ(int_queue_pop(q),3);
}

TEST_F(QueueTest, Expand){
  for(int i=0; i<DEFAULT_MAX_QUEUE_SIZE; i++){
    int_queue_push(q,i);
  }
  ASSERT_EQ(q->max_size,DEFAULT_MAX_QUEUE_SIZE);
  int_queue_push(q,DEFAULT_MAX_QUEUE_SIZE);
  ASSERT_GT(q->max_size,DEFAULT_MAX_QUEUE_SIZE);
}

TEST_F(QueueTest, BufferWrap){
    for(int i=0; i<DEFAULT_MAX_QUEUE_SIZE; i++){
        int_queue_push(q,i);
    }
    ASSERT_EQ(q->max_size,DEFAULT_MAX_QUEUE_SIZE);
    ASSERT_EQ(int_queue_pop(q),0);
    ASSERT_EQ(q->max_size,DEFAULT_MAX_QUEUE_SIZE);
    int_queue_push(q,DEFAULT_MAX_QUEUE_SIZE);
    ASSERT_EQ(q->max_size,DEFAULT_MAX_QUEUE_SIZE);
    ASSERT_GT(q->front,q->back);
    int_queue_push(q,DEFAULT_MAX_QUEUE_SIZE+1);
    ASSERT_GT(q->max_size,DEFAULT_MAX_QUEUE_SIZE);
    int start=1;
    while( q->size > 0){
        ASSERT_EQ(int_queue_pop(q),start++);
    }
}
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;

class IFace
{
public:
  virtual ~IFace() {}

  virtual int DoThis(int) = 0;
};

class MockIFace : public IFace
{
public:
  MOCK_METHOD1(DoThis,int(int));
};

TEST(Hello,World)
{
  using ::testing::Return;
  using ::testing::_;
  MockIFace mockIFace;
  EXPECT_CALL(mockIFace, DoThis(_))
    .WillRepeatedly(Return(0));
  EXPECT_CALL(mockIFace, DoThis(23))
    .WillOnce(Return(42));
  EXPECT_EQ(42,mockIFace.DoThis(23));
  EXPECT_EQ(0,mockIFace.DoThis(0));
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

#include "gmock/gmock.h"

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

class ConcreteClass
{
public:
  ConcreteClass(IFace* pIFace, int val)
  {
    _value = pIFace->DoThis(val);
  }
  int GetValue() const
  {
    return _value;
  }
private:
  int _value;
};

TEST(Hello,World)
{
  using ::testing::Return;
  using ::testing::_;
  MockIFace mockIFace;
  ON_CALL(mockIFace, DoThis(_))
    .WillByDefault(Return(0));
  EXPECT_CALL(mockIFace, DoThis(23))
    .WillOnce(Return(42));
  ConcreteClass concrete(&mockIFace, 23);
  EXPECT_EQ(42, concrete.GetValue());
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

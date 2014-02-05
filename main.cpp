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

class IFaceEx : public IFace
{
public:
  virtual ~IFaceEx() {}

  virtual double DoOtherStuff(double) = 0;
};

template <typename T>
class MockIFaceT : public T
{
public:
  MOCK_METHOD1_T(DoThis,int(int));
};

class MockIFaceEx : public MockIFaceT<IFaceEx>
{
public:
  MOCK_METHOD1(DoOtherStuff,double(double));
};

class ConcreteClassEx
{
public:
  ConcreteClassEx(IFaceEx* pIFace, int val)
  {
    _value = val + 2 * pIFace->DoOtherStuff(val);
  }
  int GetValue() const
  {
    return _value;
  }
private:
  int _value;
};

TEST(Hello,WorldT)
{
  using ::testing::Return;
  using ::testing::_;
  MockIFaceEx mockIFaceEx;
  ON_CALL(mockIFaceEx, DoThis(_))
    .WillByDefault(Return(0));
  ON_CALL(mockIFaceEx, DoOtherStuff(_))
    .WillByDefault(Return(0));
  EXPECT_CALL(mockIFaceEx, DoOtherStuff(123))
    .WillOnce(Return(111));
  ConcreteClassEx concreteEx(&mockIFaceEx, 123);
  EXPECT_EQ(345, concreteEx.GetValue());
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

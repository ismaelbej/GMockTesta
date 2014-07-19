// -*- utf8 -*-
#include "gmock/gmock.h"
#include <boost/regex.hpp>
//#include <regex>
#include <string>
#include <iostream>

// Interfaces

class IFace
{
public:
  virtual ~IFace() {}

  virtual int DoThis(int) = 0;
};

class IFaceEx : public IFace
{
public:
  virtual ~IFaceEx() {}

  virtual int DoOtherStuff(int) = 0;
};

// Mocks

template <typename TFace>
class MockIFaceT : public TFace
{
public:
  MOCK_METHOD1_T(DoThis,int(int));
};

template <typename TFace>
class MockIFaceExT : public MockIFaceT<TFace>
{
public:
  MOCK_METHOD1_T(DoOtherStuff,int(int));
};

class MockIFace : public MockIFaceT<IFace>
{
public:
  virtual ~MockIFace() { Die(); }
  MOCK_METHOD0(Die,void(void));
};

class MockIFaceEx : public MockIFaceExT<IFaceEx>
{
public:
  virtual ~MockIFaceEx() { Die(); }
  MOCK_METHOD0(Die,void(void));
};

// Test

class Concrete
{
public:
  Concrete(IFace* pIFace, int val)
    :_pIFace(pIFace), _val(val)
  {
  }

  int GetValue() const
  {
    return _val+_pIFace->DoThis(_val);
  }

private:
  int _val;
  IFace* _pIFace;
};

TEST(Test,Concrete)
{
  using ::testing::Return;
  using ::testing::_;
  MockIFace mockIFace;
  EXPECT_CALL(mockIFace, DoThis(111))
    .WillOnce(Return(123));
  EXPECT_CALL(mockIFace, Die());
  Concrete concrete(&mockIFace, 111);
  EXPECT_EQ(234, concrete.GetValue());
}

class ConcreteEx
{
public:
  ConcreteEx(IFaceEx* pIFaceEx, int val)
    :_pIFaceEx(pIFaceEx), _val(val)
  {
  }

  int GetValue() const
  {
    return _pIFaceEx->DoThis(_pIFaceEx->DoOtherStuff(_val));
  }

private:
  int _val;
  IFaceEx* _pIFaceEx;
};

TEST(Test, ConcreteEx)
{
  using ::testing::Return;
  using ::testing::_;
  MockIFaceEx mockIFaceEx;
  EXPECT_CALL(mockIFaceEx, DoThis(100))
    .WillOnce(Return(321));
  EXPECT_CALL(mockIFaceEx, DoOtherStuff(123))
    .WillOnce(Return(100));
  EXPECT_CALL(mockIFaceEx, Die());
  ConcreteEx concreteEx(&mockIFaceEx, 123);
  EXPECT_EQ(321, concreteEx.GetValue());
}

TEST(Test, RegexIPAddress)
{
  try {
    std::string ex = "(\\d){1,3}\\.(\\d){1,3}\\.(\\d){1,3}\\.(\\d){1,3}:(\\d){1,5}";
    boost::regex e(ex);
    //std::regex e(ex, std::regex_constants::grep);
    //std::cerr << "1" << std::endl;
    boost::cmatch res;
    //std::cmatch res;
    //std::cerr << "2" << std::endl;
    boost::regex_match("1.2.3.3:4", res, e);
    //std::regex_match("1.2.3.4:5", res, e);
    //std::cerr << res.size() << std::endl;
    EXPECT_EQ(6, res.size());
    //for(auto s : res) {
    //  std::cout << "x: " << s << std::endl;
    //}
  }
  catch (boost::regex_error& ex) {
    std::cout << "4" << std::endl;
    std::cout << ex.what() << ex.code() << std::endl;
  }
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

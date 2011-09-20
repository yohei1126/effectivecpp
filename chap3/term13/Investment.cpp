#include <iostream>
#include <memory>
#include <boost/shared_ptr.hpp>

class Investment{
public:
  Investment(){ std::cout << "construct" << std::endl; }
  ~Investment(){ std::cout << "destruct" << std::endl; }
};

Investment* createInvestment() {
  return new Investment; 
}

// an example of memory leak
void f1(){
  std::cout << "f1" << std::endl;
  try {
    Investment *pInv = createInvestment();

    //If some one write code that can throws error,
    //destructor of Investment may not be called.
    throw 1;

    delete pInv;
  } catch(...) {
    std::cout << "catch" << std::endl;
  }
}

//an example of auto_ptr
void f2(){
  std::cout << "f2" << std::endl;

  try {
    //If you pass a pointer to auto_ptr,
    //auto_ptr frees it when the control flow leaves the scope.
    std::auto_ptr<Investment> pInv(createInvestment()); 
    throw 1;
  } catch (...) {
    std::cout << "catch" << std::endl; 
  }
}

void f3(){
  std::cout << "f3" << std::endl;
  //several auto_ptr cannot contain the same pointer.
  //If you copy auto_ptr, then the source becomes null pointer and 
  //the destination can contain the pointer. 
  Investment* pInv1 = createInvestment();
  std::auto_ptr<Investment> pInv2(pInv1);
  std::auto_ptr<Investment> pInv3(pInv2);
}

void f4(){
  //several shared_ptr objects can have the same pointer. 
  boost::shared_ptr<Investment> pInv1(createInvestment());
  boost::shared_ptr<Investment> pInv2(pInv1);

  //If every shared_ptr objects are freed, then the pointer
  //that they have also freed. 
}

int main(){
  f1();
  f2();
  f3();
  return 0;
}

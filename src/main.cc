#include <iostream>
#include <Eigen/Dense>
#include <matrix.hh>

int main(int argc, char** argv) {

  Matrix a(20, 20);
  Matrix v(20, 1);

  std::cout << a << std::endl;

  auto f = []{return 2.0;};
  a.init_values(f);

  auto f2 = []{return 4.0;};
  v.init_values(f2);

  std::cout << a%v << std::endl;

  std::cout << v.transpose()%v << std::endl;

  return 0;
}
// The MIT License (MIT)
//
// Copyright (c) 2016 Northeastern University
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "Eigen/Dense"
#include "gtest/gtest.h"
#include "include/cpu_operations.h"
#include "include/matrix.h"

template<class T>
class GetOrthogonalMatrixTest : public ::testing::Test {
 public:
  Nice::Matrix<T> a_;
  Nice::Vector<T> b_;
};

typedef ::testing::Types<float, double> MyTypes;
TYPED_TEST_CASE(GetOrthogonalMatrixTest, MyTypes);

TYPED_TEST(GetOrthogonalMatrixTest, Test1) {
  this->a_.resize(3, 3);
  this-> a_<< 3.0, 0.0, 0.0,
              0.0, 0.0, 2.0,
              0.0, 1.0, 0.0;
  this->b_ = Nice:: CpuOperations<TypeParam>::GetOrthogonal(this->a_);
  for (int j = 0; j < this->a_.cols(); j++) {
    float Dotproduct = this->a_.col(j).dot(this->b_);
    ASSERT_NEAR(Dotproduct, 0, 0.0001);
  }
}

TYPED_TEST(GetOrthogonalMatrixTest, Test2) {
  this->a_.resize(3, 3);
  this-> a_<< 1.0, 1.0, 1.0,
              0.0, sqrt(2.0), -1*sqrt(2.0),
             -1.0, 1.0, 1.0;
  this->b_ = Nice:: CpuOperations<TypeParam>::GetOrthogonal(this->a_);
  for (int j = 0; j < this->a_.cols(); j++) {
    float Dotproduct = this->a_.col(j).dot(this->b_);
    ASSERT_NEAR(Dotproduct, 0, 0.0001);
  }
}


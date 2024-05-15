#include <gtest/gtest.h>

#include "../Libs/sle/Headers/s21_sle.h"
#include "s21_test.h"
#include "../Libs/sle/Headers/s21_gauss_default.h"
#include "../Libs/sle/Headers/s21_gauss_advanced.h"


TEST(SleTest, SleInit) {
  s21::Sle sle;
  EXPECT_EQ(sle.GetSize(), 0);
  EXPECT_TRUE(sle.GetAugmentedMatrix().empty());
}

TEST(SleTest, SleLoadMatrix) {
  s21::Sle sle;
  sle.LoadMatrixFromFile(sleMatrixPath);
  EXPECT_EQ(sle.GetSize(), sleMatrixSize);
  EXPECT_TRUE(AreMatricesEqual(sle.GetAugmentedMatrix(), sleMatrix));
}

TEST(SleTest, SleLoadDoesntExists) {
  s21::Sle sle;
  sle.LoadMatrixFromFile(doesntExistPath);
  EXPECT_EQ(sle.GetSize(), 0);
  EXPECT_TRUE(sle.GetAugmentedMatrix().empty());
}

TEST(SleTest, SleLoadIncorrect) {
  s21::Sle sle;
  sle.LoadMatrixFromFile(incorrectPath);
  EXPECT_EQ(sle.GetSize(), 0);
  EXPECT_TRUE(sle.GetAugmentedMatrix().empty());
}

TEST(SleTest, SleLoadEmpty) {
  s21::Sle sle;
  sle.LoadMatrixFromFile(emptyPath);
  EXPECT_EQ(sle.GetSize(), 0);
  EXPECT_TRUE(sle.GetAugmentedMatrix().empty());
}

TEST(SleTest, SleDefault) {
  s21::Sle sle;
  sle.LoadMatrixFromFile(slePath);
  EXPECT_TRUE(AreVectorsEqual(sle.GetResultDefault(), sleResult));
}

TEST(SleTest, SleAdvanced) {
  s21::Sle sle;
  sle.LoadMatrixFromFile(slePath);
  EXPECT_TRUE(AreVectorsEqual(sle.GetResultAdvanced(), sleResult));
}





#include <gtest/gtest.h>

#include "../Libs/winograd/Headers/s21_winograd.h"
#include "s21_test.h"
#include "../Libs/winograd/Headers/s21_winograd_default.h"
#include "../Libs/winograd/Headers/s21_winograd_classic.h"
#include "../Libs/winograd/Headers/s21_winograd_pipeline.h"


TEST(WinogradTest, WinogradInit) {
  s21::Winograd winograd;
  EXPECT_TRUE(winograd.GetLeftMatrix().empty());
  EXPECT_TRUE(winograd.GetRightMatrix().empty());
}

TEST(WinogradTest, WinogradLoadMatrices) {
  s21::Winograd winograd;
  winograd.LoadMatricesFromFile(winogradMatricesPath);
  EXPECT_TRUE(AreMatricesEqual(winograd.GetLeftMatrix(), winogradLeftMatrix));
  EXPECT_TRUE(AreMatricesEqual(winograd.GetRightMatrix(), winogradRightMatrix));
}

TEST(WinogradTest, WinogradLoadDoesntExists) {
  s21::Winograd winograd;
  winograd.LoadMatricesFromFile(doesntExistPath);
  EXPECT_TRUE(winograd.GetLeftMatrix().empty());
  EXPECT_TRUE(winograd.GetRightMatrix().empty());
}

TEST(WinogradTest, WinogradLoadIncorrect) {
  s21::Winograd winograd;
  winograd.LoadMatricesFromFile(incorrectPath);
  EXPECT_TRUE(winograd.GetLeftMatrix().empty());
  EXPECT_TRUE(winograd.GetRightMatrix().empty());
}

TEST(WinogradTest, WinogradLoadEmpty) {
  s21::Winograd winograd;
  winograd.LoadMatricesFromFile(emptyPath);
  EXPECT_TRUE(winograd.GetLeftMatrix().empty());
  EXPECT_TRUE(winograd.GetRightMatrix().empty());
}

TEST(WinogradTest, WinogradDefault) {
  s21::Winograd winograd;
  winograd.LoadMatricesFromFile(winogradPath);
  EXPECT_TRUE(AreMatricesEqual(winograd.GetResultDefault(), winogradResult));
}

TEST(WinogradTest, WinogradClassic) {
  s21::Winograd winograd;
  winograd.LoadMatricesFromFile(winogradPath);
  EXPECT_TRUE(AreMatricesEqual(winograd.GetResultClassic(2), winogradResult));
}

TEST(WinogradTest, WinogradPipeline) {
  s21::Winograd winograd;
  winograd.LoadMatricesFromFile(winogradPath);
  EXPECT_TRUE(AreMatricesEqual(winograd.GetResultPipeline(), winogradResult));
}

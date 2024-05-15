#include <gtest/gtest.h>

#include "../Libs/aco/Headers/s21_aco.h"
#include "s21_test.h"
#include "../Libs/aco/Headers/s21_ant_algorithm_default.h"
#include "../Libs/aco/Headers/s21_ant_algorithm_advanced.h"


TEST(AcoTest, AcoInit) {
  s21::Aco aco;
  EXPECT_EQ(aco.GetSize(), 0);
  EXPECT_TRUE(aco.GetAdjacencyMatrix().empty());
}

TEST(AcoTest, AcoLoadMatrix) {
  s21::Aco aco;
  aco.LoadMatrixFromFile(acoMatrixPath);
  EXPECT_EQ(aco.GetSize(), acoMatrixSize);
  EXPECT_TRUE(AreMatricesEqual(aco.GetAdjacencyMatrix(), acoMatrix));
}

TEST(AcoTest, AcoLoadDoesntExists) {
  s21::Aco aco;
  aco.LoadMatrixFromFile(doesntExistPath);
  EXPECT_EQ(aco.GetSize(), 0);
  EXPECT_TRUE(aco.GetAdjacencyMatrix().empty());
}

TEST(AcoTest, AcoLoadIncorrect) {
  s21::Aco aco;
  aco.LoadMatrixFromFile(incorrectPath);
  EXPECT_EQ(aco.GetSize(), 0);
  EXPECT_TRUE(aco.GetAdjacencyMatrix().empty());
}

TEST(AcoTest, AcoLoadEmpty) {
  s21::Aco aco;
  aco.LoadMatrixFromFile(emptyPath);
  EXPECT_EQ(aco.GetSize(), 0);
  EXPECT_TRUE(aco.GetAdjacencyMatrix().empty());
}

TEST(AcoTest, AcoDefault) {
  s21::Aco aco;
  aco.LoadMatrixFromFile(acoPath);
  s21::TsmResult result = aco.GetResultDefault();
  EXPECT_EQ(result.distance, acoDistace);
  EXPECT_TRUE(AreVectorsEqual(result.vertices, acoResult1)|| AreVectorsEqual(result.vertices, acoResult2));
}

TEST(AcoTest, AcoAdvanced) {
  s21::Aco aco;
  aco.LoadMatrixFromFile(acoPath);
  s21::TsmResult result = aco.GetResultAdvanced();
  EXPECT_EQ(result.distance, acoDistace);
  EXPECT_TRUE(AreVectorsEqual(result.vertices, acoResult1) || AreVectorsEqual(result.vertices, acoResult2));
}

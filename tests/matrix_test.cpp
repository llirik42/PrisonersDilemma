#include "gtest/gtest.h"
#include "../src/matrix.h"

TEST(MatrixTest, test0){ // empty file
    const char* path = "../matrices/empty_matrix";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}
TEST(MatrixTest, test1){ // incorrect path
    const char* path = "<incorrect path>";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}
TEST(MatrixTest, test2){ // correct matrix with spaces, empty lines and negative numbers
    const char* path = "../matrices/complex_correct_matrix";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_TRUE(matrix.is_consistent());

    EXPECT_EQ(matrix.get_row("CCC"), Row(2, 2, 2));
    EXPECT_EQ(matrix.get_row("CCD"), Row(-4, -4, 3));
    EXPECT_EQ(matrix.get_row("CDC"), Row(-4, 3, -4));
    EXPECT_EQ(matrix.get_row("CDD"), Row(3, -4, -4));
    EXPECT_EQ(matrix.get_row("DCC"), Row(-6, 0, 0));
    EXPECT_EQ(matrix.get_row("DCD"), Row(0, -6, 0));
    EXPECT_EQ(matrix.get_row("DDC"), Row(0, 0, -6));
    EXPECT_EQ(matrix.get_row("DDD"), Row(-5, -5, -5));
}
TEST(MatrixTest, test3){
    const char* path = "../matrices/complex_incorrect_matrix_1";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}
TEST(MatrixTest, test4){
    const char* path = "../matrices/complex_incorrect_matrix_2";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}
TEST(MatrixTest, test5){
    const char* path = "../matrices/complex_incorrect_matrix_3";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}
TEST(MatrixTest, test6){
    const char* path = "../matrices/complex_incorrect_matrix_4";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}
TEST(MatrixTest, test7){
    const char* path = "../matrices/example_matrix";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_TRUE(matrix.is_consistent());

    EXPECT_EQ(matrix.get_row("CCC"), Row(7, 7, 7));
    EXPECT_EQ(matrix.get_row("CCD"), Row(3, 3, 9));
    EXPECT_EQ(matrix.get_row("CDC"), Row(3, 9, 3));
    EXPECT_EQ(matrix.get_row("CDD"), Row(9, 3, 3));
    EXPECT_EQ(matrix.get_row("DCC"), Row(0, 5, 5));
    EXPECT_EQ(matrix.get_row("DCD"), Row(5, 0, 5));
    EXPECT_EQ(matrix.get_row("DDC"), Row(5, 5, 0));
    EXPECT_EQ(matrix.get_row("DDD"), Row(1, 1, 1));
}
TEST(MatrixTest, test8){
    const char* path = "../matrices/simple_mixed_correct_matrix";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_TRUE(matrix.is_consistent());

    EXPECT_EQ(matrix.get_row("CCC"), Row(2, 2, 2));
    EXPECT_EQ(matrix.get_row("CCD"), Row(-4, -4, 3));
    EXPECT_EQ(matrix.get_row("CDC"), Row(-4, 3, -4));
    EXPECT_EQ(matrix.get_row("CDD"), Row(3, -4, -4));
    EXPECT_EQ(matrix.get_row("DCC"), Row(-6, 0, 0));
    EXPECT_EQ(matrix.get_row("DCD"), Row(0, -6, 0));
    EXPECT_EQ(matrix.get_row("DDC"), Row(0, 0, -6));
    EXPECT_EQ(matrix.get_row("DDD"), Row(-5, -5, -5));
}
TEST(MatrixTest, test9){
    const char* path = "../matrices/simple_negative_correct_matrix";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_TRUE(matrix.is_consistent());

    EXPECT_EQ(matrix.get_row("CCC"), Row(-2, -2, -2));
    EXPECT_EQ(matrix.get_row("CCD"), Row(-4, -4, -1));
    EXPECT_EQ(matrix.get_row("CDC"), Row(-4, -1, -4));
    EXPECT_EQ(matrix.get_row("CDD"), Row(-1, -4, -4));
    EXPECT_EQ(matrix.get_row("DCC"), Row(-6, -3, -3));
    EXPECT_EQ(matrix.get_row("DCD"), Row(-3, -6, -3));
    EXPECT_EQ(matrix.get_row("DDC"), Row(-3, -3, -6));
    EXPECT_EQ(matrix.get_row("DDD"), Row(-5, -5, -5));
}
TEST(MatrixTest, test10){
    const char* path = "../matrices/simple_positive_correct_matrix";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_TRUE(matrix.is_consistent());

    EXPECT_EQ(matrix.get_row("CCC"), Row(8, 8, 8));
    EXPECT_EQ(matrix.get_row("CCD"), Row(6, 6, 10));
    EXPECT_EQ(matrix.get_row("CDC"), Row(6, 10, 6));
    EXPECT_EQ(matrix.get_row("CDD"), Row(10, 6, 6));
    EXPECT_EQ(matrix.get_row("DCC"), Row(4, 7, 7));
    EXPECT_EQ(matrix.get_row("DCD"), Row(7, 4, 7));
    EXPECT_EQ(matrix.get_row("DDC"), Row(7, 7, 4));
    EXPECT_EQ(matrix.get_row("DDD"), Row(5, 5, 5));
}
TEST(MatrixTest, test11){ // first inequality is wrong (3 * c0 > 2 * c1 + d0)
    const char* path = "../matrices/simple_incorrect_matrix_1";
    const Matrix matrix = Matrix(path);
    EXPECT_FALSE(matrix.has_error());
    EXPECT_FALSE(matrix.is_consistent());
}
TEST(MatrixTest, test12){ // third inequality is wrong (d0 > c0 > d1 > c1 > d2 > c2)
    const char* path = "../matrices/simple_incorrect_matrix_2";
    const Matrix matrix = Matrix(path);
    EXPECT_FALSE(matrix.has_error());
    EXPECT_FALSE(matrix.is_consistent());
}

#include "gtest/gtest.h"
#include "../src/matrix.h"

// incorrect path
TEST(MatrixTest, test0){
    const char* path = "<incorrect path>";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// example matrix
TEST(MatrixTest, test1){
    const char* path = "../matrices/matrix_1";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// example matrix
TEST(MatrixTest, test2){
    const char* path = "../matrices/matrix_2";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_TRUE(matrix.is_consistent());

    EXPECT_EQ(matrix.get_row("CCC"), Row({7, 7, 7}));
    EXPECT_EQ(matrix.get_row("CCD"), Row({3, 3, 9}));
    EXPECT_EQ(matrix.get_row("CDC"), Row({3, 9, 3}));
    EXPECT_EQ(matrix.get_row("DCC"), Row({9, 3, 3}));
    EXPECT_EQ(matrix.get_row("CDD"), Row({0, 5, 5}));
    EXPECT_EQ(matrix.get_row("DCD"), Row({5, 0, 5}));
    EXPECT_EQ(matrix.get_row("DDC"), Row({5, 5, 0}));
    EXPECT_EQ(matrix.get_row("DDD"), Row({1, 1, 1}));
}

// correct matrix with only positive numbers
TEST(MatrixTest, test3){
    const char* path = "../matrices/matrix_3";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_TRUE(matrix.is_consistent());

    EXPECT_EQ(matrix.get_row("CCC"), Row({8, 8, 8}));
    EXPECT_EQ(matrix.get_row("CCD"), Row({6, 6, 10}));
    EXPECT_EQ(matrix.get_row("CDC"), Row({6, 10, 6}));
    EXPECT_EQ(matrix.get_row("DCC"), Row({10, 6, 6}));
    EXPECT_EQ(matrix.get_row("CDD"), Row({4, 7, 7}));
    EXPECT_EQ(matrix.get_row("DCD"), Row({7, 4, 7}));
    EXPECT_EQ(matrix.get_row("DDC"), Row({7, 7, 4}));
    EXPECT_EQ(matrix.get_row("DDD"), Row({5, 5, 5}));
}

// correct matrix with only negative numbers
TEST(MatrixTest, test4){
    const char* path = "../matrices/matrix_4";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_TRUE(matrix.is_consistent());

    EXPECT_EQ(matrix.get_row("CCC"), Row({-2, -2, -2}));
    EXPECT_EQ(matrix.get_row("CCD"), Row({-4, -4, -1}));
    EXPECT_EQ(matrix.get_row("CDC"), Row({-4, -1, -4}));
    EXPECT_EQ(matrix.get_row("DCC"), Row({-1, -4, -4}));
    EXPECT_EQ(matrix.get_row("CDD"), Row({-6, -3, -3}));
    EXPECT_EQ(matrix.get_row("DCD"), Row({-3, -6, -3}));
    EXPECT_EQ(matrix.get_row("DDC"), Row({-3, -3, -6}));
    EXPECT_EQ(matrix.get_row("DDD"), Row({-5, -5, -5}));
}

// correct matrix with positive and negative numbers
TEST(MatrixTest, test5){
    const char* path = "../matrices/matrix_5";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_TRUE(matrix.is_consistent());

    EXPECT_EQ(matrix.get_row("CCC"), Row({2, 2, 2}));
    EXPECT_EQ(matrix.get_row("CCD"), Row({-4, -4, 3}));
    EXPECT_EQ(matrix.get_row("CDC"), Row({-4, 3, -4}));
    EXPECT_EQ(matrix.get_row("DCC"), Row({3, -4, -4}));
    EXPECT_EQ(matrix.get_row("CDD"), Row({-6, 0, 0}));
    EXPECT_EQ(matrix.get_row("DCD"), Row({0, -6, 0}));
    EXPECT_EQ(matrix.get_row("DDC"), Row({0, 0, -6}));
    EXPECT_EQ(matrix.get_row("DDD"), Row({-5, -5, -5}));
}

// first inequality is wrong (3 * c0 > 2 * c1 + d0)
TEST(MatrixTest, test6){
    const char* path = "../matrices/matrix_6";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_FALSE(matrix.is_consistent());
}

// third inequality is wrong (d0 > c0 > d1 > c1 > d2 > c2)
TEST(MatrixTest, test7){
    const char* path = "../matrices/matrix_7";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_FALSE(matrix.is_consistent());
}

// matrix is not symmetric (in some especial way)
TEST(MatrixTest, test8){
    const char* path = "../matrices/matrix_8";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_FALSE(matrix.is_consistent());
}

// correct matrix with only positive numbers and unusual order of rows
TEST(MatrixTest, test9){
    const char* path = "../matrices/matrix_9";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_TRUE(matrix.is_consistent());

    EXPECT_EQ(matrix.get_row("CCC"), Row({8, 8, 8}));
    EXPECT_EQ(matrix.get_row("CCD"), Row({6, 6, 10}));
    EXPECT_EQ(matrix.get_row("CDC"), Row({6, 10, 6}));
    EXPECT_EQ(matrix.get_row("DCC"), Row({10, 6, 6}));
    EXPECT_EQ(matrix.get_row("CDD"), Row({4, 7, 7}));
    EXPECT_EQ(matrix.get_row("DCD"), Row({7, 4, 7}));
    EXPECT_EQ(matrix.get_row("DDC"), Row({7, 7, 4}));
    EXPECT_EQ(matrix.get_row("DDD"), Row({5, 5, 5}));
}

// correct matrix with spaces, empty lines, negative numbers and comments
TEST(MatrixTest, test10){
    const char* path = "../matrices/matrix_10";
    const Matrix matrix = Matrix(path);

    EXPECT_FALSE(matrix.has_error());
    EXPECT_TRUE(matrix.is_consistent());

    EXPECT_EQ(matrix.get_row("CCC"), Row({2, 2, 2}));
    EXPECT_EQ(matrix.get_row("CCD"), Row({-4, -4, 3}));
    EXPECT_EQ(matrix.get_row("CDC"), Row({-4, 3, -4}));
    EXPECT_EQ(matrix.get_row("DCC"), Row({3, -4, -4}));
    EXPECT_EQ(matrix.get_row("CDD"), Row({-6, 0, 0}));
    EXPECT_EQ(matrix.get_row("DCD"), Row({0, -6, 0}));
    EXPECT_EQ(matrix.get_row("DDC"), Row({0, 0, -6}));
    EXPECT_EQ(matrix.get_row("DDD"), Row({-5, -5, -5}));
}

// unsupported comment section (/* */) is considered as error
TEST(MatrixTest, test11){
    const char* path = "../matrices/matrix_11";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// unsupported comment (/) is considered as error
TEST(MatrixTest, test12){
    const char* path = "../matrices/matrix_12";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// incorrect number of rows (9 instead of 8) though row was duplicated
TEST(MatrixTest, test13){
    const char* path = "../matrices/matrix_13";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// incorrect number of rows (7 instead of 8)
TEST(MatrixTest, test14){
    const char* path = "../matrices/matrix_14";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// no space between letters in row
TEST(MatrixTest, test15){
    const char* path = "../matrices/matrix_15";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// incorrect number of letters in a row (2 instead of 3)
TEST(MatrixTest, test16){
    const char* path = "../matrices/matrix_16";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// incorrect number of letters in a row (4 instead of 3)
TEST(MatrixTest, test17){
    const char* path = "../matrices/matrix_17";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// incorrect number of numbers in a row (2 instead of 3)
TEST(MatrixTest, test18){
    const char* path = "../matrices/matrix_18";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// incorrect number of numbers in a row (4 instead of 3)
TEST(MatrixTest, test19){
    const char* path = "../matrices/matrix_19";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// random line (not a comment)
TEST(MatrixTest, test20){
    const char* path = "../matrices/matrix_20";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// (--a) is not supported in a table
TEST(MatrixTest, test21){
    const char* path = "../matrices/matrix_21";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// random symbols in the table
TEST(MatrixTest, test22){
    const char* path = "../matrices/matrix_22";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// 2 rows in one line
TEST(MatrixTest, test23){
    const char* path = "../matrices/matrix_23";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// row that was split in 2 lines
TEST(MatrixTest, test24){
    const char* path = "../matrices/matrix_24";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}
// number "00" in rows
TEST(MatrixTest, test25){
    const char* path = "../matrices/matrix_25";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// number "-0" in rows
TEST(MatrixTest, test26){
    const char* path = "../matrices/matrix_26";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// non-integer numbers
TEST(MatrixTest, test27){
    const char* path = "../matrices/matrix_27";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// incorrect number (07) in first row (it's supposed that numbers must be "0" or non-zero)
TEST(MatrixTest, test28){
    const char* path = "../matrices/matrix_28";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// 8 rows, but first row is doubled so one row is missing
TEST(MatrixTest, test29){
    const char* path = "../matrices/matrix_29";
    const Matrix matrix = Matrix(path);

    EXPECT_TRUE(matrix.has_error());
}

// Default matrix
TEST(MatrixTest, test30){
    const Matrix matrix = Matrix();

    EXPECT_FALSE(matrix.has_error());
    EXPECT_TRUE(matrix.is_consistent());

    EXPECT_EQ(matrix.get_row("CCC"), Row({7, 7, 7}));
    EXPECT_EQ(matrix.get_row("CCD"), Row({3, 3, 9}));
    EXPECT_EQ(matrix.get_row("CDC"), Row({3, 9, 3}));
    EXPECT_EQ(matrix.get_row("DCC"), Row({9, 3, 3}));
    EXPECT_EQ(matrix.get_row("CDD"), Row({0, 5, 5}));
    EXPECT_EQ(matrix.get_row("DCD"), Row({5, 0, 5}));
    EXPECT_EQ(matrix.get_row("DDC"), Row({5, 5, 0}));
    EXPECT_EQ(matrix.get_row("DDD"), Row({1, 1, 1}));
}

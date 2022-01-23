#include "TritSet.h"
#include "gtest/gtest.h"
#include "iostream"

TEST(Tests, _and) {
    TritSet a(7);
    a[0] = True;
    a[1] = False;
    a[3] = True;
    a[4] = False;
    a[5] = True;
    TritSet b(50);
    b[0] = False;
    b[1] = False;
    b[2] = False;
    b[3] = True;
    b[4] = True;
    b[30] = True;
    b[41] = False;
    TritSet c = a & b;
    EXPECT_EQ(b.Capacity(), c.Capacity());
    EXPECT_EQ(c[0], False);
    EXPECT_EQ(c[1], False);
    EXPECT_EQ(c[2], False);
    EXPECT_EQ(c[3], True);
    EXPECT_EQ(c[4], False);
    EXPECT_EQ(c[5], Unknown);
    EXPECT_EQ(c[6], Unknown);
    EXPECT_EQ(c[20], Unknown);
    EXPECT_EQ(c[30], Unknown);
    EXPECT_EQ(c[41], False);
}

TEST(Tests, _or) {
    TritSet a(10);
    a[0] = True;
    a[1] = False;
    a[3] = True;
    a[4] = False;
    a[5] = True;
    TritSet b(50);
    b[0] = False;
    b[1] = False;
    b[2] = False;
    b[3] = True;
    b[4] = True;
    b[20] = True;
    TritSet c = b | a;
    EXPECT_EQ(b.Capacity(), c.Capacity());
    EXPECT_EQ(c[0], True);
    EXPECT_EQ(c[1], False);
    EXPECT_EQ(c[2], Unknown);
    EXPECT_EQ(c[3], True);
    EXPECT_EQ(c[4], True);
    EXPECT_EQ(c[5], True);
    EXPECT_EQ(c[6], Unknown);
    EXPECT_EQ(c[20], True);
    EXPECT_EQ(c[21], Unknown);
    EXPECT_EQ(c[22], Unknown);
}


TEST(Tests, _not) {
    TritSet a(4);
    a[0] = True;
    a[1] = False;
    a = ~a;
    EXPECT_EQ(a[0], False);
    EXPECT_EQ(a[1], True);
    EXPECT_EQ(a[3], Unknown);
}

TEST(Tests, _capasity) {
    TritSet set (1000);
    int capacity = set.Capacity();
    set[0] = True;
    set[10000] = False;
    EXPECT_GE(capacity, 1000 * 2 / 8 / sizeof(uint));
    EXPECT_EQ(set[0], True);
    EXPECT_EQ(set[10000], False);
    EXPECT_EQ(set[100], Unknown);
    capacity = set.Capacity();
    EXPECT_EQ(set.Capacity(), capacity);
}

TEST(Tests, _shrink) {
    TritSet set (10);
    int capacity = set.Capacity();
    set[100] = True;
    set[100] = Unknown;
    EXPECT_GT(set.Capacity(), capacity);
    set.Shrink();
    EXPECT_EQ(set.Capacity(), capacity);
    set[100] = True;
    capacity = set.Capacity();
    set[1000] = False;
    EXPECT_GT(set.Capacity(), capacity);
    set[1000] = Unknown;
    set.Shrink();
    EXPECT_EQ(set.Capacity(), capacity);
}

int main (int argc, char* argv[]) {


    /// конструктор копирования работает:
    TritSet a(1);
    a[0] = True;
    TritSet(b) = a;
    b[0] = False;
    std::cout << a << ' ' << b;



    /// перегрузка оператора вывода:
    TritSet set(100);
    cout << set << '\n';

    for(int i = 0; i < 50; i++)
        set[i] = False;
    for(int i = 51; i < 100; i++)
        set[i] = Unknown;

    cout << set << '\n';

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

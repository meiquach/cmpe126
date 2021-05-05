#include "gtest/gtest.h"
#include "doubly_linked_list.h"
#include <algorithm>

class Lab06Fixture : public ::testing::Test {

protected:
    virtual void SetUp() {
        dll_UT = new lab6::doubly_linked_list();
    }

    virtual void TearDown() {
        delete dll_UT;
    }

public:
    lab6::doubly_linked_list * dll_UT;
};


TEST(Lab06crsh, crash_test_dll) {
    std::vector <int> number_list;
    lab6::doubly_linked_list *list;

    for(int i=0; i < 20; i++){
        number_list.push_back(i);
    }

    list = new lab6::doubly_linked_list();
    delete list;
    list = new lab6::doubly_linked_list(73);
    delete list;
    list = new lab6::doubly_linked_list(number_list);
}


TEST_F(Lab06Fixture, append_get_data_get_set_test) {
    std::vector <int> expected_set;
    EXPECT_TRUE(dll_UT->is_empty());
    for (int i = 1; i < 200; ++i) {
        dll_UT->append(i);
        ASSERT_EQ(i,dll_UT->size());
        expected_set.push_back(i);
        for (int j = 0; j < i; ++j) {
            ASSERT_EQ(expected_set[j],dll_UT->get_data(j)) << "Iteration: i= " << i << " j= " << j;
        }
    }

    ASSERT_EQ(expected_set, dll_UT->get_set(0,dll_UT->size()-1));
    ASSERT_EQ(std::vector<int>(expected_set.begin(),expected_set.begin()+expected_set.size()/2),dll_UT->get_set(0,dll_UT->size()/2-1));//first half of data
    ASSERT_EQ(std::vector<int> (expected_set.begin()+expected_set.size()/2+1,expected_set.end()),dll_UT->get_set(dll_UT->size()/2+1,dll_UT->size()-1));//second half of data
}


TEST_F(Lab06Fixture, insert_remove_test) {
    EXPECT_NO_THROW(dll_UT->insert(3,0));
    EXPECT_NO_THROW(dll_UT->insert(6,0));
    EXPECT_NO_THROW(dll_UT->insert(4,1));

    EXPECT_EQ(6,dll_UT->get_data(0));
    EXPECT_EQ(4,dll_UT->get_data(1));
    EXPECT_EQ(3,dll_UT->get_data(2));

    dll_UT->remove(0);
    dll_UT->remove(0);
    dll_UT->remove(0); // make sure both head and tail are set to nullptr when the last node is removed

    dll_UT->append(16);
    EXPECT_EQ(16, dll_UT->get_data(0));

}

TEST_F(Lab06Fixture, opEq_insert_append_value_test) {
    auto dll_UT_copy = new lab6::doubly_linked_list;

    for(int i=0; i<200; ++i) {
        EXPECT_NO_THROW(dll_UT->insert(i)) << "failed on iteration: " << i << "\n";
        EXPECT_EQ(i, dll_UT->get_data(0)) << "failed on iteration: " << i << "\n";
    }
    dll_UT_copy->operator=(*dll_UT);
    EXPECT_EQ(dll_UT_copy->size(),dll_UT->size());

    for (int i = 0; i < 200; ++i) {//ensure full copy
        EXPECT_EQ(199-i, dll_UT_copy->get_data(i)) << "failed on iteration: " << i << "\n";
    }

    for(int i=0; i<300; i+=2) {//alter copy
        EXPECT_NO_THROW(dll_UT_copy->insert(i*2, i)) << "failed on iteration: " << i << "\n";
    }

    for (int i = 0; i < 200; ++i) {//check values of original after altering copy to ensure mutual exclusive nodes
        EXPECT_EQ(199-i, dll_UT->get_data(i)) << "failed on iteration: " << i << "\n";
    }
}


TEST_F(Lab06Fixture, split_split_set_test) {
    for (int i = 0; i < 100; ++i) {
        dll_UT->append(i);
    }

    lab6::doubly_linked_list * split_list = new lab6::doubly_linked_list;
    *split_list = dll_UT->split(50); //50 should be the head value of the returned list
    EXPECT_EQ(49, dll_UT->get_data(dll_UT->size()-1));//49 should be the tail value of  the original list

    for (int i = 0; i < split_list->size(); ++i) {
        ASSERT_EQ(i+50, split_list->get_data(i)) << "failed on iteration: " << i << "\n";;
    }

    for (int i = 0; i < dll_UT->size(); ++i) {
        ASSERT_EQ(i, dll_UT->get_data(i)) << "failed on iteration: " << i << "\n";;
    }

    EXPECT_EQ(0,dll_UT->split(0).get_data(0)); //edge case, be careful
    EXPECT_TRUE(dll_UT->is_empty());

    delete dll_UT;
    delete split_list;
    dll_UT = new lab6::doubly_linked_list;
    split_list = new lab6::doubly_linked_list;

    for (int i = 0; i < 100; ++i) {
        dll_UT->append(i);
    }

    *split_list = dll_UT->split_set(25,74);
    EXPECT_EQ(50, dll_UT->size());
    EXPECT_EQ(50, split_list->size());

    for (int i = 0; i < 50; ++i) {
        ASSERT_EQ(i+25, split_list->get_data(i)) << "failed on iteration: " << i << "\n";
    }
    for (int i = 0; i < 50; ++i) {
        if(i < 25)
            ASSERT_EQ(i, dll_UT->get_data(i)) << "failed on iteration: " << i << "\n";
        else
            ASSERT_EQ(i+50, dll_UT->get_data(i)) << "failed on iteration: " << i << "\n";
    }
}


TEST_F(Lab06Fixture, swap_swap_set_test) {
    for (int i = 0; i < 100; ++i) {
        dll_UT->append(i);
    }
    for (unsigned i = 0; i < 50; ++i) {
        dll_UT->swap(i,99-i);
        for (int j = 0; j < 100; ++j) {
            if(j <= i || j >= 99-i){
                ASSERT_EQ(99-j,dll_UT->get_data(j))<< "failed on iteration: i = " << i << " j = " << j << "\n";
            } else{
                ASSERT_EQ(j,dll_UT->get_data(j))<< "failed on iteration: i = " << i << " j = " << "\n";
            }
        }
    }

    for (unsigned i = 0; i < 50; ++i) {
        dll_UT->swap_set(i,i,99-i,99-i);//should perform single swap
        for (int j = 0; j < 100; ++j) {
            if(j <= i || j >= 99-i){
                ASSERT_EQ(j,dll_UT->get_data(j))<< "failed on iteration: i = " << i << " j = " << "\n";
            } else{
                ASSERT_EQ(99-j,dll_UT->get_data(j))<< "failed on iteration: i = " << i << " j = " << j << "\n";
            }
        }
    }

    dll_UT->swap_set(0,49,50,99);

    for (unsigned i = 0; i < 100; ++i) {
        if(i < 50)
            ASSERT_EQ(i+50,dll_UT->get_data(i))<< "failed on iteration: " << i << "\n";
        else
            ASSERT_EQ(i-50,dll_UT->get_data(i))<< "failed on iteration: " << i << "\n";
    }
}


TEST_F(Lab06Fixture, op_plus_op_plus_eq_test) {
    lab6::doubly_linked_list * dll_UT_2 = new lab6::doubly_linked_list;
    lab6::doubly_linked_list * merged_list = new lab6::doubly_linked_list;

    for (unsigned i = 0; i < 50; ++i) {
        dll_UT->append(i);
        dll_UT_2->append(i+50);
    }

    *merged_list = *dll_UT + *dll_UT_2;

    *dll_UT += *dll_UT_2;
    delete dll_UT_2; // make sure a copy is appended in +=

    for (int i = 0; i < 100; ++i) {
        ASSERT_EQ(i,dll_UT->get_data(i))<< "failed on iteration: " << i << "\n";
    }

    delete dll_UT; // make sure a copy is returned in +
    dll_UT = nullptr;//avoid deleting a bad address is tear down

    for (int i = 0; i < 100; ++i) {
        ASSERT_EQ(i,merged_list->get_data(i))<< "failed on iteration: " << i << "\n";
    }
}


TEST_F(Lab06Fixture, compare_op_test) {
    for (int i = 0; i < 100; ++i) {
        dll_UT->append(i);
    }
    EXPECT_TRUE(*dll_UT==*dll_UT);

    lab6::doubly_linked_list * comp_list = new lab6::doubly_linked_list;

    for (int i = 0; i < 100; ++i) {
        comp_list->append(dll_UT->get_data(i));
    }
    EXPECT_TRUE(*dll_UT == *comp_list);
    delete comp_list;
    comp_list = new lab6::doubly_linked_list;


    for (int i = 0; i < 100; ++i) {
        comp_list->append(dll_UT->get_data(99-i));
    }
    EXPECT_FALSE(*dll_UT == *comp_list);

    delete comp_list;
    comp_list = new lab6::doubly_linked_list;


    for (int i = 0; i < 50; ++i) {
        comp_list->append(dll_UT->get_data(i));
    }
    EXPECT_FALSE(*dll_UT == *comp_list);

    delete comp_list;
    comp_list = new lab6::doubly_linked_list;


    for (int i = 0; i < 100; ++i) {
        comp_list->append(dll_UT->get_data(99-i));
    }
    for (int i = 100; i < 150; ++i) {
        comp_list->append(i);
    }
    EXPECT_FALSE(*dll_UT == *comp_list);
}


TEST_F(Lab06Fixture, insertion_extraction_op_test) {
    std::string expected_output;
    std::string input("50");
    std::stringstream stream(input);

    stream >> *dll_UT;
    EXPECT_EQ(stoi(input),dll_UT->get_data(0));
    expected_output = input + " -> ";

    for(int i =1; i < 49; ++i) {
        input = std::to_string(i);
        expected_output = input + " <-> " + expected_output;
        EXPECT_NO_THROW(dll_UT->insert(i)) << "failed on iteration: " << i << "\n";
    }
    expected_output = "NULL <- " + expected_output;
    expected_output += "NULL";

    testing::internal::CaptureStdout();
    std::cout << *dll_UT;
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expected_output,output);
}

TEST_F(Lab06Fixture, sort_test) {
    unsigned const list_length_count = 100;
    auto container1 = new std::vector<int>;
    container1->reserve(30);
    //srand((unsigned )time(NULL)); //Used to randomize test, seed with constant to make test repeatable
    srand(0);

    for (int i = 0; i < list_length_count; ++i) {
        int input = rand()%200;
        container1->emplace_back(input);
        dll_UT->append(input);
    }

    std::sort(container1->begin(),container1->end());
    dll_UT->sort();

    for (int i = 0; i < list_length_count; ++i) {
        ASSERT_EQ((*container1)[i],dll_UT->get_data(i));
    }

}
/*#include "gtest/gtest.h"
#include "doubly_linked_list.h"
#include <algorithm>
#include <random>

class doubly_linked_listTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        doubly_linked_listUT = new lab6::doubly_linked_list();
    }

public:
    lab6::doubly_linked_list *doubly_linked_listUT;
};

TEST(CrashTest, doubly_linked_list_crashTest) {
    auto *doubly_linked_listUT = new lab6::doubly_linked_list();
    delete doubly_linked_listUT;
}

TEST_F(doubly_linked_listTest, append_doesNotCrash) {
    ASSERT_NO_FATAL_FAILURE(doubly_linked_listUT->append(1));
}

TEST_F(doubly_linked_listTest, append_is_emptyList_addsValueToList) {
    doubly_linked_listUT->append(10);
    doubly_linked_listUT->append(11);
    doubly_linked_listUT->append(12);
    EXPECT_EQ(11, doubly_linked_listUT->get_data(1));
}

TEST_F(doubly_linked_listTest, append_populatedList_addsValueToEnd) {
    doubly_linked_listUT->append(10);
    ASSERT_EQ(10, doubly_linked_listUT->get_data(0));

    doubly_linked_listUT->append(11);
    EXPECT_EQ(10, doubly_linked_listUT->get_data(0));
    EXPECT_EQ(11, doubly_linked_listUT->get_data(1));

    doubly_linked_listUT->append(12);
    EXPECT_EQ(10, doubly_linked_listUT->get_data(0));
    EXPECT_EQ(11, doubly_linked_listUT->get_data(1));
    EXPECT_EQ(12, doubly_linked_listUT->get_data(2));

    for (int i = 13; i < 1000; i++) doubly_linked_listUT->append(i);
    for (int i = 0; i < 990; i++) ASSERT_EQ(i + 10, doubly_linked_listUT->get_data(i));
}

TEST_F(doubly_linked_listTest, get_data_doesNotCrash) {
    doubly_linked_listUT->append(10);
    doubly_linked_listUT->append(11);
    doubly_linked_listUT->append(12);
    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT->get_data(1));
}

TEST_F(doubly_linked_listTest, get_data_validIndex_getsDataAtIndex) {
    doubly_linked_listUT->append(10);
    ASSERT_EQ(10, doubly_linked_listUT->get_data(0));

    doubly_linked_listUT->append(11);
    EXPECT_EQ(10, doubly_linked_listUT->get_data(0));
    EXPECT_EQ(11, doubly_linked_listUT->get_data(1));
}

TEST_F(doubly_linked_listTest, get_data_invalidIndex_throws) {
    doubly_linked_listUT->append(10);
    ASSERT_NO_THROW(doubly_linked_listUT->get_data(0));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(10));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(-1));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(1000000));
}

TEST_F(doubly_linked_listTest, get_data_is_emptyList_throws) {
    ASSERT_ANY_THROW(doubly_linked_listUT->get_data(0));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(10));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(-1));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(1000000));
}

TEST_F(doubly_linked_listTest, get_set_doesNotCrash) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);

    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT->get_set(2, 7));
}

TEST_F(doubly_linked_listTest, get_set_validIndices_getsSetAtIndices) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);

    ASSERT_EQ(std::vector<int>({12, 13, 14, 15, 16, 17}), doubly_linked_listUT->get_set(2, 7));
    EXPECT_EQ(std::vector<int>({14}), doubly_linked_listUT->get_set(4, 4));
    EXPECT_EQ(std::vector<int>({10, 11, 12, 13, 14, 15, 16, 17, 18, 19}), doubly_linked_listUT->get_set(0, 9));
}


//TEST_F(doubly_linked_listTest, get_set_invalidIndices_throws) {
//    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
//
//    ASSERT_ANY_THROW(doubly_linked_listUT->get_set(0, 10));
//    EXPECT_ANY_THROW(doubly_linked_listUT->get_set(10, 0));
//    EXPECT_ANY_THROW(doubly_linked_listUT->get_set(100, 200));
//    EXPECT_ANY_THROW(doubly_linked_listUT->get_set(200, 100));
//}

TEST_F(doubly_linked_listTest, get_set_is_emptyList_throws) {
    ASSERT_ANY_THROW(doubly_linked_listUT->get_set(0, 1));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_set(0, 10));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_set(0, -1));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_set(0, 1000000));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_set(0, 0));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_set(1, 0));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_set(10, 0));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_set(-1, 0));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_set(1000000, 0));
}

TEST_F(doubly_linked_listTest, insert_doesNotCrash) {
    doubly_linked_listUT->append(10);
    doubly_linked_listUT->append(11);
    doubly_linked_listUT->append(12);
    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT->insert(100, 1));
}

TEST_F(doubly_linked_listTest, insert_validIndex_addsValueAtIndex) {
    doubly_linked_listUT->append(10);
    doubly_linked_listUT->append(11);
    doubly_linked_listUT->append(12);
    doubly_linked_listUT->insert(100, 1);
    ASSERT_EQ(10, doubly_linked_listUT->get_data(0));
    EXPECT_EQ(100, doubly_linked_listUT->get_data(1));
    EXPECT_EQ(11, doubly_linked_listUT->get_data(2));
    EXPECT_EQ(12, doubly_linked_listUT->get_data(3));

    doubly_linked_listUT->insert(200, 0);
    ASSERT_EQ(200, doubly_linked_listUT->get_data(0));
    EXPECT_EQ(10, doubly_linked_listUT->get_data(1));
    EXPECT_EQ(100, doubly_linked_listUT->get_data(2));
    EXPECT_EQ(11, doubly_linked_listUT->get_data(3));
    EXPECT_EQ(12, doubly_linked_listUT->get_data(4));

    doubly_linked_listUT->insert(300, 5);
    ASSERT_EQ(200, doubly_linked_listUT->get_data(0));
    EXPECT_EQ(10, doubly_linked_listUT->get_data(1));
    EXPECT_EQ(100, doubly_linked_listUT->get_data(2));
    EXPECT_EQ(11, doubly_linked_listUT->get_data(3));
    EXPECT_EQ(12, doubly_linked_listUT->get_data(4));
    EXPECT_EQ(300, doubly_linked_listUT->get_data(5));
}

TEST_F(doubly_linked_listTest, insert_is_emptyList_addsValue) {
    doubly_linked_listUT->insert(100, 0);
    EXPECT_EQ(100, doubly_linked_listUT->get_data(0));
}

TEST_F(doubly_linked_listTest, insert_invalidIndex_throws) {
    ASSERT_ANY_THROW(doubly_linked_listUT->insert(100, 2));

    doubly_linked_listUT->append(10);
    doubly_linked_listUT->append(11);
    doubly_linked_listUT->append(12);

    EXPECT_ANY_THROW(doubly_linked_listUT->insert(200, 10));
}

TEST_F(doubly_linked_listTest, remove_doesNotCrash) {
    doubly_linked_listUT->append(10);
    doubly_linked_listUT->append(11);
    doubly_linked_listUT->append(12);
    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT->remove(1));
}

TEST_F(doubly_linked_listTest, remove_validIndex_removesValueAtIndex) {
    doubly_linked_listUT->append(10);
    doubly_linked_listUT->append(11);
    doubly_linked_listUT->append(12);
    doubly_linked_listUT->append(13);

    doubly_linked_listUT->remove(1);
    ASSERT_EQ(10, doubly_linked_listUT->get_data(0));
    EXPECT_EQ(12, doubly_linked_listUT->get_data(1));
    EXPECT_EQ(13, doubly_linked_listUT->get_data(2));

    doubly_linked_listUT->remove(0);
    EXPECT_EQ(12, doubly_linked_listUT->get_data(0));
    EXPECT_EQ(13, doubly_linked_listUT->get_data(1));

    doubly_linked_listUT->remove(1);
    EXPECT_EQ(12, doubly_linked_listUT->get_data(0));

    doubly_linked_listUT->remove(0);
    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(0));
}

TEST_F(doubly_linked_listTest, remove_invalidIndex_throws) {
    doubly_linked_listUT->append(10);
    doubly_linked_listUT->append(11);
    doubly_linked_listUT->append(12);

    ASSERT_ANY_THROW(doubly_linked_listUT->remove(3));
    EXPECT_ANY_THROW(doubly_linked_listUT->remove(10));
    EXPECT_ANY_THROW(doubly_linked_listUT->remove(-1));
    EXPECT_ANY_THROW(doubly_linked_listUT->remove(1000000));
}

TEST_F(doubly_linked_listTest, remove_is_emptyList_throws) {
    ASSERT_ANY_THROW(doubly_linked_listUT->remove(0));
    EXPECT_ANY_THROW(doubly_linked_listUT->remove(3));
    EXPECT_ANY_THROW(doubly_linked_listUT->remove(10));
    EXPECT_ANY_THROW(doubly_linked_listUT->remove(-1));
    EXPECT_ANY_THROW(doubly_linked_listUT->remove(1000000));
}

TEST_F(doubly_linked_listTest, initialValueConstructor_doesNotCrash) {
    delete doubly_linked_listUT;
    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT = new lab6::doubly_linked_list(10));
}

TEST_F(doubly_linked_listTest, initialValueConstructor_addsValue) {
    delete doubly_linked_listUT;
    doubly_linked_listUT = new lab6::doubly_linked_list(10);
    EXPECT_EQ(10, doubly_linked_listUT->get_data(0));
}

TEST_F(doubly_linked_listTest, vectorConstructor_doesNotCrash) {
    delete doubly_linked_listUT;
    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT = new lab6::doubly_linked_list(std::vector<int>({10, 11, 12, 13, 14})));
}

TEST_F(doubly_linked_listTest, vectorConstructor_addsValue) {
    delete doubly_linked_listUT;
    doubly_linked_listUT = new lab6::doubly_linked_list(std::vector<int>({10, 11, 12, 13, 14}));
    ASSERT_EQ(10, doubly_linked_listUT->get_data(0));
    EXPECT_EQ(11, doubly_linked_listUT->get_data(1));
    EXPECT_EQ(12, doubly_linked_listUT->get_data(2));
    EXPECT_EQ(13, doubly_linked_listUT->get_data(3));
    EXPECT_EQ(14, doubly_linked_listUT->get_data(4));
}

TEST_F(doubly_linked_listTest, copyConstructor_doesNotCrash) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    EXPECT_NO_FATAL_FAILURE(auto *copy = new lab6::doubly_linked_list(*doubly_linked_listUT));
}

TEST_F(doubly_linked_listTest, copyConstructor_copiesValues) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    lab6::doubly_linked_list *copy = new lab6::doubly_linked_list(*doubly_linked_listUT);

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(i + 10, doubly_linked_listUT->get_data(i));
        ASSERT_EQ(i + 10, copy->get_data(i));
    }
}

TEST_F(doubly_linked_listTest, copyConstructor_hardCopiesValues) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    lab6::doubly_linked_list *copy = new lab6::doubly_linked_list(*doubly_linked_listUT);

    doubly_linked_listUT->append(20);
    ASSERT_EQ(20, doubly_linked_listUT->get_data(10));
    EXPECT_ANY_THROW(copy->get_data(10));

    doubly_linked_listUT->insert(100, 3);
    EXPECT_EQ(100, doubly_linked_listUT->get_data(3));
    EXPECT_EQ(13, copy->get_data(3));

    copy->append(20);
    EXPECT_EQ(19, doubly_linked_listUT->get_data(10));
    EXPECT_EQ(20, copy->get_data(10));

    copy->remove(5);
    EXPECT_EQ(14, doubly_linked_listUT->get_data(5));
    EXPECT_EQ(16, copy->get_data(5));
}

TEST_F(doubly_linked_listTest, split_doesNotCrash) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT->split(5));
}

TEST_F(doubly_linked_listTest, split_validIndex_splitsListAtIndex) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);

    auto *doubly_linked_list2UT = new lab6::doubly_linked_list(doubly_linked_listUT->split(5));
    for (int i = 0; i < 5; i++) ASSERT_EQ(i + 10, doubly_linked_listUT->get_data(i));
    for (int i = 0; i < 5; i++) ASSERT_EQ(i + 15, doubly_linked_list2UT->get_data(i));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(5));
    EXPECT_ANY_THROW(doubly_linked_list2UT->get_data(5));

    auto *doubly_linked_list3UT = new lab6::doubly_linked_list(doubly_linked_list2UT->split(3));
    for (int i = 0; i < 5; i++) ASSERT_EQ(i + 10, doubly_linked_listUT->get_data(i));
    for (int i = 0; i < 3; i++) ASSERT_EQ(i + 15, doubly_linked_list2UT->get_data(i));
    for (int i = 0; i < 2; i++) ASSERT_EQ(i + 18, doubly_linked_list3UT->get_data(i));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(5));
    EXPECT_ANY_THROW(doubly_linked_list2UT->get_data(3));
    EXPECT_ANY_THROW(doubly_linked_list3UT->get_data(2));

    auto *doubly_linked_list4UT = new lab6::doubly_linked_list(doubly_linked_list3UT->split(1));
    for (int i = 0; i < 5; i++) ASSERT_EQ(i + 10, doubly_linked_listUT->get_data(i));
    for (int i = 0; i < 3; i++) ASSERT_EQ(i + 15, doubly_linked_list2UT->get_data(i));
    EXPECT_EQ(18, doubly_linked_list3UT->get_data(0));
    EXPECT_EQ(19, doubly_linked_list4UT->get_data(0));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(5));
    EXPECT_ANY_THROW(doubly_linked_list2UT->get_data(3));
    EXPECT_ANY_THROW(doubly_linked_list3UT->get_data(1));
    EXPECT_ANY_THROW(doubly_linked_list4UT->get_data(1));
}

TEST_F(doubly_linked_listTest, split_index0_splitsOffEntireList) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);

    auto *doubly_linked_list2UT = new lab6::doubly_linked_list(doubly_linked_listUT->split(0));
    ASSERT_ANY_THROW(doubly_linked_listUT->get_data(0));
    for (int i = 0; i < 10; i++) ASSERT_EQ(i + 10, doubly_linked_list2UT->get_data(i));
    EXPECT_ANY_THROW(doubly_linked_list2UT->get_data(10));

    auto *doubly_linked_list3UT = new lab6::doubly_linked_list(doubly_linked_list2UT->split(3));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(0));
    for (int i = 0; i < 3; i++) ASSERT_EQ(i + 10, doubly_linked_list2UT->get_data(i));
    for (int i = 0; i < 7; i++) ASSERT_EQ(i + 13, doubly_linked_list3UT->get_data(i));
    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(0));
    EXPECT_ANY_THROW(doubly_linked_list2UT->get_data(3));
    EXPECT_ANY_THROW(doubly_linked_list2UT->get_data(7));
}

TEST_F(doubly_linked_listTest, split_invalidIndex_throws) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    ASSERT_ANY_THROW(doubly_linked_listUT->split(10));
    EXPECT_ANY_THROW(doubly_linked_listUT->split(-1));
    EXPECT_ANY_THROW(doubly_linked_listUT->split(1000000));
}

TEST_F(doubly_linked_listTest, split_is_emptyList_throws) {
    ASSERT_ANY_THROW(doubly_linked_listUT->split(0));
    EXPECT_ANY_THROW(doubly_linked_listUT->split(10));
    EXPECT_ANY_THROW(doubly_linked_listUT->split(-1));
    EXPECT_ANY_THROW(doubly_linked_listUT->split(1000000));
}

TEST_F(doubly_linked_listTest, split_set_doesNotCrash) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT->split_set(2, 5));
}

//TEST_F(doubly_linked_listTest, split_set_validIndices_splitsSetOffList) {
//    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
//
//    auto *doubly_linked_list2UT = new lab6::doubly_linked_list(doubly_linked_listUT->split_set(2, 4));
//    for (int i = 0; i < 2; i++) ASSERT_EQ(i + 10, doubly_linked_listUT->get_data(i));
//    for (int i = 2; i < 5; i++) ASSERT_EQ(i + 13, doubly_linked_listUT->get_data(i));
//    for (int i = 0; i < 3; i++) ASSERT_EQ(i + 12, doubly_linked_list2UT->get_data(i));
//    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(7));
//    EXPECT_ANY_THROW(doubly_linked_list2UT->get_data(3));
//
//    auto *doubly_linked_list3UT = new lab6::doubly_linked_list(doubly_linked_list2UT->split_set(0, 0));
//    for (int i = 0; i < 2; i++) ASSERT_EQ(i + 10, doubly_linked_listUT->get_data(i));
//    for (int i = 2; i < 5; i++) ASSERT_EQ(i + 13, doubly_linked_listUT->get_data(i));
//    for (int i = 0; i < 2; i++) ASSERT_EQ(i + 13, doubly_linked_list2UT->get_data(i));
//    ASSERT_EQ(12, doubly_linked_list3UT->get_data(0));
//    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(7));
//    EXPECT_ANY_THROW(doubly_linked_list2UT->get_data(2));
//    EXPECT_ANY_THROW(doubly_linked_list3UT->get_data(1));
//}

//TEST_F(doubly_linked_listTest, split_set_wronglyOrderedIndices_splitsSetOffList) {
//    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
//
//    auto *doubly_linked_list2UT = new lab6::doubly_linked_list(doubly_linked_listUT->split_set(4, 2));
//    for (int i = 0; i < 2; i++) ASSERT_EQ(i + 10, doubly_linked_listUT->get_data(i));
//    for (int i = 2; i < 5; i++) ASSERT_EQ(i + 13, doubly_linked_listUT->get_data(i));
//    for (int i = 0; i < 3; i++) ASSERT_EQ(i + 12, doubly_linked_list2UT->get_data(i));
//    EXPECT_ANY_THROW(doubly_linked_listUT->get_data(7));
//    EXPECT_ANY_THROW(doubly_linked_list2UT->get_data(3));
//}

//TEST_F(doubly_linked_listTest, split_set_invalidIndices_throws) {
//    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
//
//    ASSERT_ANY_THROW(doubly_linked_listUT->split_set(0, 10));
//    EXPECT_ANY_THROW(doubly_linked_listUT->split_set(2, 10));
//    EXPECT_ANY_THROW(doubly_linked_listUT->split_set(100, 200));
//    EXPECT_ANY_THROW(doubly_linked_listUT->split_set(10, 10));
//    EXPECT_ANY_THROW(doubly_linked_listUT->split_set(10, 0));
//    EXPECT_ANY_THROW(doubly_linked_listUT->split_set(10, 2));
//    EXPECT_ANY_THROW(doubly_linked_listUT->split_set(200, 100));
//}

TEST_F(doubly_linked_listTest, size_doesNotCrash) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT->size());
}

TEST_F(doubly_linked_listTest, size_tracksAppendsInsertionsRemovalsAndSplits) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    ASSERT_EQ(10, doubly_linked_listUT->size());

    doubly_linked_listUT->insert(100, 1);
    EXPECT_EQ(11, doubly_linked_listUT->size());

    doubly_linked_listUT->remove(2);
    EXPECT_EQ(10, doubly_linked_listUT->size());

    doubly_linked_listUT->split(8);
    EXPECT_EQ(8, doubly_linked_listUT->size());

    doubly_linked_listUT->split_set(2, 4);
    EXPECT_EQ(5, doubly_linked_listUT->size());
}

TEST_F(doubly_linked_listTest, size_is_emptyList_0) {
    EXPECT_EQ(0, doubly_linked_listUT->size());
}

TEST_F(doubly_linked_listTest, isis_empty_doesNotCrash) {
    doubly_linked_listUT->append(10);
    doubly_linked_listUT->append(11);
    doubly_linked_listUT->append(12);
    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT->is_empty());
}

TEST_F(doubly_linked_listTest, isis_empty_tracksAppendsInsertionsRemovalsAndSplits) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    EXPECT_FALSE(doubly_linked_listUT->is_empty());

    doubly_linked_listUT->insert(100, 1);
    EXPECT_FALSE(doubly_linked_listUT->is_empty());

    doubly_linked_listUT->remove(2);
    EXPECT_FALSE(doubly_linked_listUT->is_empty());

    doubly_linked_listUT->split(8);
    EXPECT_FALSE(doubly_linked_listUT->is_empty());

    doubly_linked_listUT->split_set(2, 4);
    EXPECT_FALSE(doubly_linked_listUT->is_empty());

    for (int i = 0; i < 5; i++) doubly_linked_listUT->remove(0);
    EXPECT_TRUE(doubly_linked_listUT->is_empty());
}

TEST_F(doubly_linked_listTest, isis_empty_is_emptyList_true) {
    EXPECT_TRUE(doubly_linked_listUT->is_empty());
}

TEST_F(doubly_linked_listTest, swap_doesNotCrash) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT->swap(3, 6));
}

TEST_F(doubly_linked_listTest, swap_validIndices_swapsValues) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);

    doubly_linked_listUT->swap(3, 6);
    ASSERT_EQ(16, doubly_linked_listUT->get_data(3));
    EXPECT_EQ(13, doubly_linked_listUT->get_data(6));

    doubly_linked_listUT->swap(0, 9);
    EXPECT_EQ(19, doubly_linked_listUT->get_data(0));
    EXPECT_EQ(10, doubly_linked_listUT->get_data(9));

    doubly_linked_listUT->swap(4, 4);
    EXPECT_EQ(14, doubly_linked_listUT->get_data(4));
}

TEST_F(doubly_linked_listTest, swap_wronglyOrderedIndices_swapsValues) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);

    doubly_linked_listUT->swap(6, 3);
    ASSERT_EQ(16, doubly_linked_listUT->get_data(3));
    EXPECT_EQ(13, doubly_linked_listUT->get_data(6));

    doubly_linked_listUT->swap(9, 0);
    EXPECT_EQ(19, doubly_linked_listUT->get_data(0));
    EXPECT_EQ(10, doubly_linked_listUT->get_data(9));
}

TEST_F(doubly_linked_listTest, swap_invalidIndices_throws) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);

    ASSERT_ANY_THROW(doubly_linked_listUT->swap(0, 10));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap(2, 10));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap(100, 200));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap(10, 10));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap(10, 0));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap(10, 2));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap(200, 100));
}

TEST_F(doubly_linked_listTest, swap_set_doesNotCrash) {
    for (int i = 10; i < 60; i++) doubly_linked_listUT->append(i);
    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT->swap_set(2, 4, 6, 8));
}

TEST_F(doubly_linked_listTest, swap_set_validIndices_swapsValues) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);

    doubly_linked_listUT->swap(3, 6);
    ASSERT_EQ(16, doubly_linked_listUT->get_data(3));
    EXPECT_EQ(13, doubly_linked_listUT->get_data(6));

    doubly_linked_listUT->swap(0, 9);
    EXPECT_EQ(19, doubly_linked_listUT->get_data(0));
    EXPECT_EQ(10, doubly_linked_listUT->get_data(9));

    doubly_linked_listUT->swap(4, 4);
    EXPECT_EQ(14, doubly_linked_listUT->get_data(4));
}

TEST_F(doubly_linked_listTest, swap_set_wronglyOrderedIndices_swapsValues) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);

    doubly_linked_listUT->swap(6, 3);
    ASSERT_EQ(16, doubly_linked_listUT->get_data(3));
    EXPECT_EQ(13, doubly_linked_listUT->get_data(6));

    doubly_linked_listUT->swap(9, 0);
    EXPECT_EQ(19, doubly_linked_listUT->get_data(0));
    EXPECT_EQ(10, doubly_linked_listUT->get_data(9));
}

TEST_F(doubly_linked_listTest, swap_set_overlappingIndices_throws) {
    for (int i = 10; i < 30; i++) doubly_linked_listUT->append(i);

    ASSERT_ANY_THROW(doubly_linked_listUT->swap_set(7, 10, 8, 12));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap_set(10, 7, 8, 12));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap_set(7, 10, 12, 8));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap_set(10, 7, 12, 8));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap_set(0, 20, 5, 15));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap_set(0, 20, 0, 20));
}

TEST_F(doubly_linked_listTest, swap_set_invalidIndices_throws) {
    for (int i = 10; i < 30; i++) doubly_linked_listUT->append(i);

    ASSERT_ANY_THROW(doubly_linked_listUT->swap_set(0, 12, 18, 24));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap_set(12, 0, 18, 24));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap_set(0, 12, 24, 18));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap_set(12, 0, 24, 18));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap_set(0, 40, 55, 80));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap_set(40, 0, 55, 80));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap_set(0, 40, 80, 55));
    EXPECT_ANY_THROW(doubly_linked_listUT->swap_set(40, 0, 80, 55));
}

TEST_F(doubly_linked_listTest, sort_doesNotCrash) {
    std::vector<int> unsorted;
    for (int val = 10; val < 110; val++) unsorted.push_back(val);
    std::shuffle(unsorted.begin(), unsorted.end(), std::random_device());

    delete doubly_linked_listUT;
    doubly_linked_listUT = new lab6::doubly_linked_list(unsorted);

    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT->sort());
}

TEST_F(doubly_linked_listTest, sort_populatedList_sortsList) {
    std::vector<int> unsorted;
    for (int val = 10; val < 110; val++) unsorted.push_back(val);
    std::shuffle(unsorted.begin(), unsorted.end(), std::random_device());

    delete doubly_linked_listUT;
    doubly_linked_listUT = new lab6::doubly_linked_list(unsorted);

    doubly_linked_listUT->sort();

    for (unsigned i = 0; i < 100; i++) ASSERT_EQ(i + 10, doubly_linked_listUT->get_data(i));
}

TEST_F(doubly_linked_listTest, sort_is_emptyList_doesNothing) {
    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT->sort());
}

TEST_F(doubly_linked_listTest, operatorPlus_doesNotCrash) {
    auto *doubly_linked_list2UT = new lab6::doubly_linked_list;
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    for (int i = 20; i < 30; i++) doubly_linked_list2UT->append(i);

    EXPECT_NO_FATAL_FAILURE(*doubly_linked_listUT + *doubly_linked_list2UT);
}

TEST_F(doubly_linked_listTest, operatorPlus_populatedLists_combinesLists) {
    auto *doubly_linked_list2UT = new lab6::doubly_linked_list;
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    for (int i = 20; i < 30; i++) doubly_linked_list2UT->append(i);

    auto *doubly_linked_list3UT = new lab6::doubly_linked_list(*doubly_linked_listUT + *doubly_linked_list2UT);
    for (unsigned i = 0; i < 20; i++) ASSERT_EQ(i + 10, doubly_linked_list3UT->get_data(i));
}

TEST_F(doubly_linked_listTest, operatorPlus_sameLists_combinesLists) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);

    auto *doubly_linked_list3UT = new lab6::doubly_linked_list(*doubly_linked_listUT + *doubly_linked_listUT);
    for (unsigned i = 0; i < 10; i++) ASSERT_EQ(i + 10, doubly_linked_list3UT->get_data(i));
    for (unsigned i = 10; i < 20; i++) ASSERT_EQ(i, doubly_linked_list3UT->get_data(i));
}

TEST_F(doubly_linked_listTest, operatorPlus_is_emptyLists_doesNothing) {
    auto *doubly_linked_list2UT = new lab6::doubly_linked_list;
    auto *doubly_linked_list3UT = new lab6::doubly_linked_list(*doubly_linked_listUT + *doubly_linked_list2UT);
    EXPECT_ANY_THROW(doubly_linked_list3UT->get_data(0));
}

TEST_F(doubly_linked_listTest, operatorEquals_doesNotCrash) {
    auto *doubly_linked_list2UT = new lab6::doubly_linked_list(2);
    EXPECT_NO_FATAL_FAILURE(*doubly_linked_listUT = *doubly_linked_list2UT);
}

TEST_F(doubly_linked_listTest, operatorEquals_populatedLists_copiesValues) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    lab6::doubly_linked_list *copy = &*doubly_linked_listUT;

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(i + 10, doubly_linked_listUT->get_data(i));
        ASSERT_EQ(i + 10, copy->get_data(i));
    }
}

TEST_F(doubly_linked_listTest, operatorEquals_populatedLists_hardCopiesValues) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    auto *copy = new lab6::doubly_linked_list;
    copy->operator=(*doubly_linked_listUT);

    doubly_linked_listUT->append(20);
    ASSERT_EQ(20, doubly_linked_listUT->get_data(10));
    EXPECT_ANY_THROW(copy->get_data(10));

    doubly_linked_listUT->insert(100, 3);
    EXPECT_EQ(100, doubly_linked_listUT->get_data(3));
    EXPECT_EQ(13, copy->get_data(3));

    copy->append(20);
    EXPECT_EQ(19, doubly_linked_listUT->get_data(10));
    EXPECT_EQ(20, copy->get_data(10));

    copy->remove(5);
    EXPECT_EQ(14, doubly_linked_listUT->get_data(5));
    EXPECT_EQ(16, copy->get_data(5));
}

TEST_F(doubly_linked_listTest, operatorEquals_selfAssignment_doesNothing) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    doubly_linked_listUT->operator=(*doubly_linked_listUT);

    doubly_linked_listUT->append(20);
    ASSERT_EQ(20, doubly_linked_listUT->get_data(10));

    doubly_linked_listUT->insert(100, 3);
    EXPECT_EQ(100, doubly_linked_listUT->get_data(3));

    doubly_linked_listUT->append(20);
    EXPECT_EQ(19, doubly_linked_listUT->get_data(10));

    doubly_linked_listUT->remove(5);
    EXPECT_EQ(15, doubly_linked_listUT->get_data(5));
}

TEST_F(doubly_linked_listTest, operatorPlusEquals_doesNotCrash) {
    auto *doubly_linked_list2UT = new lab6::doubly_linked_list(2);
    EXPECT_NO_FATAL_FAILURE(*doubly_linked_listUT += *doubly_linked_list2UT);
}

TEST_F(doubly_linked_listTest, operatorPlusEquals_populatedLists_appendsList) {
    auto *doubly_linked_list2UT = new lab6::doubly_linked_list;
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    for (int i = 20; i < 30; i++) doubly_linked_list2UT->append(i);

    doubly_linked_listUT->operator+=(*doubly_linked_list2UT);
    for (int i = 0; i < 20; i++) ASSERT_EQ(i + 10, doubly_linked_listUT->get_data(i));
}

TEST_F(doubly_linked_listTest, operatorEqualsComparison_doesNotCrash) {
    auto *doubly_linked_list2UT = new lab6::doubly_linked_list(2);
    EXPECT_NO_FATAL_FAILURE(doubly_linked_listUT->operator==(*doubly_linked_list2UT));
}

TEST_F(doubly_linked_listTest, operatorEqualsComparison_populatedLists_comparesLists) {
    auto *doubly_linked_list2UT = new lab6::doubly_linked_list;
    for (int i = 10; i < 20; i++) {
        doubly_linked_listUT->append(i);
        doubly_linked_list2UT->append(i);
    }
    ASSERT_TRUE(*doubly_linked_listUT == *doubly_linked_list2UT);

    doubly_linked_listUT->append(100);
    EXPECT_FALSE(*doubly_linked_listUT == *doubly_linked_list2UT);

    doubly_linked_list2UT->append(100);
    EXPECT_TRUE(*doubly_linked_listUT == *doubly_linked_list2UT);

    doubly_linked_list2UT->append(200);
    doubly_linked_list2UT->append(300);
    EXPECT_FALSE(*doubly_linked_listUT == *doubly_linked_list2UT);
}

TEST_F(doubly_linked_listTest, operatorEqualsComparison_sameLists_true) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    EXPECT_TRUE(*doubly_linked_listUT == *doubly_linked_listUT);
}

TEST_F(doubly_linked_listTest, operatorEqualsComparison_is_emptyLists_true) {
    auto *doubly_linked_list2UT = new lab6::doubly_linked_list;
    EXPECT_TRUE(*doubly_linked_listUT == *doubly_linked_list2UT);
}

TEST_F(doubly_linked_listTest, operatorInsertion_doesNotCrash) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    testing::internal::CaptureStdout();
    EXPECT_NO_FATAL_FAILURE(std::cout << *doubly_linked_listUT);
    testing::internal::GetCapturedStdout();
}

TEST_F(doubly_linked_listTest, operatorInsertion_outputsList) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);

    testing::internal::CaptureStdout();
    std::cout << *doubly_linked_listUT;
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("NULL <- 10 <-> 11 <-> 12 <-> 13 <-> 14 <-> 15 <-> 16 <-> 17 <-> 18 <-> 19 -> NULL", output);
}

TEST_F(doubly_linked_listTest, operatorExtraction_doesNotCrash) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    EXPECT_NO_FATAL_FAILURE(std::stringstream("100") >> *doubly_linked_listUT);
}

TEST_F(doubly_linked_listTest, operatorExtraction_appendsInput) {
    for (int i = 10; i < 20; i++) doubly_linked_listUT->append(i);
    for (int i = 20; i < 30; i++) std::stringstream(std::to_string(i)) >> *doubly_linked_listUT;
    for (int i = 0; i < 20; i++) ASSERT_EQ(i + 10, doubly_linked_listUT->get_data(i));
}*/
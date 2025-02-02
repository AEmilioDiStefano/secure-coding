// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
  ~Environment() override {}

  // Override this to define how to set up the environment.
  void SetUp() override
  {
    //  initialize random seed
    srand(time(nullptr));
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
  // create a smart point to hold our collection
  std::unique_ptr<std::vector<int>> collection;

  void SetUp() override
  { // create a new collection to be used in the test
    collection.reset( new std::vector<int>);
  }

  void TearDown() override
  { //  erase all elements in the collection, if any remain
    collection->clear();
    // free the pointer
    collection.reset(nullptr);
  }

  // helper function to add random values from 0 to 99 count times to the collection
  void add_entries(int count)
  {
    assert(count > 0);
    for (auto i = 0; i < count; ++i)
      collection->push_back(rand() % 100);
  }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, VerifyCollectionSmartPointerIsNotNull)
{
  // is the collection created
  ASSERT_TRUE(collection);

  // if empty, the size must be 0
  ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, VerifyIsEmptyOnCreate)
{
  // is the collection empty?
  ASSERT_TRUE(collection->empty());

  // if empty, the size must be 0
  ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
// TEST_F(CollectionTest, AlwaysFail)
// {
//   FAIL();
// }

// This test verifies adding a single value to an empty collection.
TEST_F(CollectionTest, VerifyCanAddToEmptyVector)
{

  // is the collection empty?
  ASSERT_TRUE(collection->empty());

  // if empty, the size must be 0
  ASSERT_EQ(collection->size(), 0);

  // add an entry to the collection
  add_entries(1);

  // is the collection still empty?
  ASSERT_FALSE(collection->empty());

  // if not empty, the size must be 1
  ASSERT_EQ(collection->size(), 1);

}

// This test verifies adding five values to collection.
TEST_F(CollectionTest, VerifyCanAddFiveValuesToVector)
{
  
    // Check to see if the collection is empty.
    ASSERT_TRUE(collection->empty());

    // If the collection is empty, the size must be 0.
    ASSERT_EQ(collection->size(), 0);

    // Add 5 entries to the collection.
    add_entries(5);

    // Check to see if the collection is still empty.
    ASSERT_FALSE(collection->empty());

    // If the collection is not empty, the size should be 5.
    ASSERT_EQ(collection->size(), 5);

}

// This test verifies that max size is greater than or equal 
// to size for 0, 1, 5, 10 entries.
TEST_F(CollectionTest, VerifyMaxSize)
{
    // Check to see if the collection is empty.
    ASSERT_TRUE(collection->empty());

    // If the collection is empty, the size must be 0.
    ASSERT_EQ(collection->size(), 0);

    // Add mote than 10 entries to the collection.
    add_entries(11);

    // Check to see if the collection is greater than or equal to 0.
    ASSERT_GE(collection->max_size(), 0);

    // Check to see if the collection is greater than or equal to 1.
    ASSERT_GE(collection->max_size(), 1);

    // Check to see if the collection greater than or equal to 5.
    ASSERT_GE(collection->max_size(), 5);

    // Check to see if the collection is greater than or equal to 10.
    ASSERT_GE(collection->max_size(), 10);
}

// This test verifies that capacity is greater than or equal to size for 0, 1, 5, 10 entries.
TEST_F(CollectionTest, VerifyCapacityEqualToSize)
{
    // Check to see if the collection is empty.
    ASSERT_TRUE(collection->empty());

    // If the collection is empty, the size must be 0.
    ASSERT_EQ(collection->size(), 0);

    // Check if the capacity is greate than or equal to o.
    ASSERT_GE(collection->capacity(), 0);

    // Add more than 10 entries to the collection.
    add_entries(11);

    // Check if capacity is greater than or equal to 1.
    ASSERT_GE(collection->capacity(), 1);

    // Check if the capacity is greater than or equal to 5.
    ASSERT_GE(collection->capacity(), 5);

    // Check if the capacity is greater than or equal to 10.
    ASSERT_GE(collection->capacity(), 10);
}

// This test will verify that resizing increases the collection
TEST_F(CollectionTest, VerifyResizingIncreases) {
    add_entries(1);

    // Set the starting value of the 'startingSize' variable 
    // to the current size of the collection. 
    int startingSize = collection->size();

    // Resize the collection.
    collection->resize(10);

    // Check to see that the collection size is greater than 
    // the value of the 'startingSize' variable.
    ASSERT_TRUE(collection->size() > startingSize);
}

// This test verifies that resizing decreases the collection.
TEST_F(CollectionTest, VerifyResizingDecreases) {

    // Add 10 entries to the collection.
    add_entries(10);

    // Set the starting value of the 'startingSize' variable 
    // to the current size of the collection.
    int startingSize = collection->size();

    // Check to see that the collection size is greater than 
    // the value of the 'startingSize' variable.
    collection->resize(1);
    ASSERT_TRUE(collection->size() < startingSize);
}

// This test verifies that resizing decreases the collection to zero
TEST_F(CollectionTest, VerifyResizeDecreasesToZero) {

    // Add 10 entries to the collection.
    add_entries(10);

    // Set the starting value of the 'startingSize' variable 
    // to the current size of the collection.
    int startingSize = collection->size();

    // Check to see that the collection size is greater than 
    // the value of the 'startingSize' variable.
    collection->resize(0);
    ASSERT_EQ(collection->size(), 0);
}

// This test verifies that clear erases the collection.
TEST_F(CollectionTest, VerifyClearErasesCollection)
{

    // Add 5 entries to the collection.
    add_entries(5);

    // Assert that the size of the collection was 
    // successfully set to 5.
    ASSERT_EQ(collection->size(), 5);

    // Clear the collection.
    collection->clear();

    // Check that the collection is empty.
    ASSERT_EQ(collection->size(), 0);
    ASSERT_TRUE(collection->empty());
}

// This test verifies that erase(begin, end) erases the collection.
TEST_F(CollectionTest, VerifyEraseAllWithBeginEnd) {

    // Add 10 entries to the collection.
    add_entries(10);

    // Erase the collection using erase(begin, end).
    collection->erase(collection->begin(), collection->end());

    // Check to see that the size of the erased collection is 0.
    ASSERT_EQ(collection->size(), 0);
}

// This test verifies that reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, VerifyReserveIncreaseWithoutSizeIncrease) {

    // Add 10 entries to the collection.
    add_entries(5);

    // capacity will be increased by reserve, size will stay 10
    int startingCapacity = collection->capacity();

    // Set the value of the 'startingSize' variable to the size 
    // of the collection.
    int startingSize = collection->size();

    // Reserve space for 20 entreies.
    collection->reserve(10);

    ASSERT_TRUE(collection->size() == startingSize);
    ASSERT_TRUE(collection->capacity() > startingCapacity);
}

// This test verifies that the std::out_of_range exception is thrown when calling at() with an index out of bounds.
// NOTE: This is a negative test

TEST_F(CollectionTest, VerifyAtOutOfRangeNegative) 
{

    // Add 5 entries to the collection.
    add_entries(5);

    // Check that referencing an index which is out of bounds (10)
    // throws an out of range exception.
    EXPECT_THROW(collection->at(10), std::out_of_range);
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

// Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative

// This positive test verifies that the 'push_back()' function successfully adds
// one entry to the collection.
TEST_F(CollectionTest, VerifyPushAddsAnEntry)
{
    // Add 10 entries to the collection.
    add_entries(10);

    // Use the 'push_back()' function, which should add another entry,
    // which should make the number of entries 11.
    collection->push_back(1);

    // Check to make sure that the size of the collection is now 11 after
    // using the 'push_back()' function.
    ASSERT_TRUE(collection->size() == 11);
}

// This test verifies that the 'pop_back()' function successfully removes
// one entry from the collection.
// (NEGATIVE TEST)
TEST_F(CollectionTest, VerifyPopBackRemovesEntryNegative) {

    // Add 10 entries to the collection.
    add_entries(10);

    // Use 'pop_back()' which should remove the last entry,
    //which should make the number of entries 9.
    collection->pop_back();

    // Make sure that referencing the 10th item in the collection,
    // which is now only 9 items long, throws an 'out_of_range' 
    // exception.
    EXPECT_THROW(collection->at(10), std::out_of_range);
}

// EXTRA POSITIVE TEST
// This test verifies that the 'pop_back()' function successfully removes
// one entry from the collection.

TEST_F(CollectionTest, VerifyPopBackRemovesEntry) {

    // Add 10 entries to the collection.
    add_entries(10);

    // Use 'pop_back()' which should remove the last entry,
    //which should make the number of entries 9.
    collection->pop_back();

    // Make sure that after using the 'pop_back' function the size of the
    // collection is 9.
    ASSERT_EQ(collection->size(), 9);
}

// EXTRA NEGATIVE TEST
// This negative test verifies that the 'push_back()' function only adds one
// entry to the collection.
// (NEGATIVE TEST)
TEST_F(CollectionTest, VerifyPushOnlyAddsOneEntryNegative)
{
    // Add 10 entries to the collection.
    add_entries(10);

    // Use the 'push_back()' function, which should add another entry,
    // which should make the number of entries 11.
    collection->push_back(1);

    // Check that there is no 12th entry after using the 'puh_back()' function
    // to add one entry to the collection which originally had 10 entries.
    EXPECT_THROW(collection->at(12), std::out_of_range);
}

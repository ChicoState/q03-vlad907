/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}

TEST(GuesserTest, Constructor_Truncates_Secret) {
	Guesser g("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"); // 36 chars
	ASSERT_FALSE(g.match("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890")); // should not match
  }
  
  TEST(GuesserTest, Distance_ExactMatch_IsZero) {
	Guesser g("hello");
	ASSERT_EQ(g.distance("hello"), 0);
  }
  
  TEST(GuesserTest, Distance_CharacterDifferences) {
	Guesser g("hello");
	ASSERT_EQ(g.distance("hxlxo"), 2); // 2 chars different
  }
  
  TEST(GuesserTest, Distance_ExtraCharactersCount) {
	Guesser g("hello");
	ASSERT_EQ(g.distance("hellooooooo"), 5); // only counts up to length of secret
  }
  
  TEST(GuesserTest, Match_CorrectGuess_ResetsRemaining) {
	Guesser g("pass");
	g.match("pasm"); // distance = 1
	g.match("pasa"); // distance = 1
	ASSERT_EQ(g.remaining(), 1);
	g.match("pass"); // correct
	ASSERT_EQ(g.remaining(), 3); // now should reset
  }
  
  
  TEST(GuesserTest, Match_BruteForce_LocksSecret) {
	Guesser g("pass");
	g.match("abcdefgh"); // very different → should lock
	ASSERT_FALSE(g.match("pass")); // now locked
	ASSERT_EQ(g.remaining(), 3); // doesn't change
  }
  
  TEST(GuesserTest, Match_LocksAfter3BadGuesses) {
	Guesser g("pass");
	g.match("pasa"); // 1 diff
	g.match("pasa"); // 1 diff
	g.match("pasa"); // 1 diff
	ASSERT_FALSE(g.match("pass")); // now locked
	ASSERT_EQ(g.remaining(), 0);
  }
  
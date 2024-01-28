#include <moving_average.h>
#include <unity.h>

void setUp(void)
{
    // N/A
}

void tearDown(void)
{
    // N/A
}

void test_is_initialised_updates_correctly(void)
{
    // Setup a moving average that stores 3 samples
    MovingAverage moving_average = MovingAverage(3);

    // After constructor, is_initialised should be false
    TEST_ASSERT_EQUAL(false, moving_average.is_initialised());

    // After pushing sample #1, is_initialised should be false
    moving_average.push(1);
    TEST_ASSERT_EQUAL(false, moving_average.is_initialised());

    // After pushing sample #2, is_initialised should be false
    moving_average.push(2);
    TEST_ASSERT_EQUAL(false, moving_average.is_initialised());

    // After pushing sample #3 and beyond, is_initialised should be true
    for (uint16_t i = 3; i <= 10; i++)
    {
        moving_average.push(i);
        TEST_ASSERT_EQUAL(true, moving_average.is_initialised());
    }
}

void test_average_updates_correctly()
{
    // Setup a moving average that stores 4 samples
    MovingAverage moving_average = MovingAverage(4);

    // Push 4 values in order: 2, 4, 6, 8
    // After pushing 8, the average should be (2 + 4 + 6 + 8) / 4 = 20 / 4 = 5
    moving_average.push(2);
    moving_average.push(4);
    moving_average.push(6);

    // After pushing 8, the correct average should be returned
    // It should also be stored in MovingAverage::current_average()
    uint16_t current_average = moving_average.push(8);
    TEST_ASSERT_EQUAL(5, current_average);
    TEST_ASSERT_EQUAL(5, moving_average.current_average());

    // Push another value which will overwrite the first entry: 10
    // After pushing 10, the average should be (4 + 6 + 8 + 10) / 4 = 28 / 4 = 7
    current_average = moving_average.push(10);
    TEST_ASSERT_EQUAL(7, current_average);
    TEST_ASSERT_EQUAL(7, moving_average.current_average());

    // Push another value which will overwrite the second entry: 3
    // After pushing 12, the average should be (6 + 8 + 10 + 3) / 4 = 27 / 4 = 6
    current_average = moving_average.push(3);
    TEST_ASSERT_EQUAL(6, current_average);
    TEST_ASSERT_EQUAL(6, moving_average.current_average());

    // Push another value which will overwrite the third entry: 5
    // After pushing 5, the average should be (8 + 10 + 3 + 5) / 4 = 26 / 4 = 6
    current_average = moving_average.push(5);
    TEST_ASSERT_EQUAL(6, current_average);
    TEST_ASSERT_EQUAL(6, moving_average.current_average());

    // Push another value which will overwrite the fourth entry: 20
    // After pushing 5, the average should be (10 + 3 + 5 + 20) / 4 = 38 / 4 = 9
    current_average = moving_average.push(20);
    TEST_ASSERT_EQUAL(9, current_average);
    TEST_ASSERT_EQUAL(9, moving_average.current_average());
}

void process()
{
    UNITY_BEGIN();
    RUN_TEST(test_is_initialised_updates_correctly);
    RUN_TEST(test_average_updates_correctly);
    UNITY_END();
}

#ifdef ARDUINO
#include <Arduino.h>

void setup()
{
    // NOTE: Wait for > 2 secs, mainly for boards that don't support software reset via Serial.DTR/RTS
    delay(2000);

    process();
}

void loop()
{
    digitalWrite(25, HIGH);
    delay(500);
    digitalWrite(25, LOW);
    delay(500);
}
#else
int main(int argc, char **argv)
{
    process();
    return 0;
}
#endif
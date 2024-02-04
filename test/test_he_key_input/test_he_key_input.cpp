#include <unity.h>

#include <he_key_input.h>

void setUp(void)
{
    // N/A
}

void tearDown(void)
{
    // N/A
}

void test_update_key_state_rt_upper_deadzone(void)
{
    HEKeyConfiguration config = {.rapid_trigger = true,
                                 .upper_deadzone_mm = 0.5};

    HEKeyState state = {.highest_position_mm = 0.4};

    update_key_state_rt(config, state, 0.3);

    TEST_ASSERT_EQUAL_DOUBLE(0.3, state.last_position_mm);
    TEST_ASSERT_EQUAL_DOUBLE(0.3, state.highest_position_mm);
    TEST_ASSERT_FALSE(state.pressed);
}

void test_update_key_state_rt_lower_deadzone(void)
{
    HEKeyConfiguration config = {.rapid_trigger = true,
                                 .lower_deadzone_mm = 0.5};

    HEKeyState state = {.lowest_position_mm = AIR_GAP_RANGE - 0.4};

    update_key_state_rt(config, state, AIR_GAP_RANGE - 0.2);

    TEST_ASSERT_EQUAL_DOUBLE(AIR_GAP_RANGE - 0.2, state.last_position_mm);
    TEST_ASSERT_EQUAL_DOUBLE(AIR_GAP_RANGE - 0.2, state.lowest_position_mm);
    TEST_ASSERT_TRUE(state.pressed);
}

void test_update_key_state_rt_pressed_below_lowest_point(void)
{
    TEST_FAIL();
}

void test_update_key_state_rt_pressed_within_up_sensitivity_range(void)
{
    TEST_FAIL();
}

void test_update_key_state_rt_pressed_outside_up_sensitivity_range(void)
{
    TEST_FAIL();
}

void test_update_key_state_rt_released_above_highest_point(void)
{
    TEST_FAIL();
}

void test_update_key_state_rt_released_within_down_sensitivity_range(void)
{
    TEST_FAIL();
}

void test_update_key_state_rt_released_outside_down_sensitivity_range(void)
{
    TEST_FAIL();
}

void test_update_key_state_fixed_above_actuation_point(void)
{
    HEKeyConfiguration config = {.rapid_trigger = false, .actuation_point_mm = 1.5};
    HEKeyState state = {};

    update_key_state_fixed(config, state, 1.2);

    TEST_ASSERT_EQUAL_DOUBLE(1.2, state.last_position_mm);
    TEST_ASSERT_FALSE(state.pressed);
}

void test_update_key_state_fixed_below_actuation_point(void)
{
    HEKeyConfiguration config = {.rapid_trigger = false, .actuation_point_mm = 1.5};
    HEKeyState state = {};

    update_key_state_fixed(config, state, 1.8);

    TEST_ASSERT_EQUAL_DOUBLE(1.8, state.last_position_mm);
    TEST_ASSERT_TRUE(state.pressed);
}

void process()
{
    UNITY_BEGIN();

    RUN_TEST(test_update_key_state_rt_upper_deadzone);
    RUN_TEST(test_update_key_state_rt_lower_deadzone);
    RUN_TEST(test_update_key_state_rt_pressed_below_lowest_point);
    RUN_TEST(test_update_key_state_rt_pressed_within_up_sensitivity_range);
    RUN_TEST(test_update_key_state_rt_pressed_outside_up_sensitivity_range);
    RUN_TEST(test_update_key_state_rt_released_above_highest_point);
    RUN_TEST(test_update_key_state_rt_released_within_down_sensitivity_range);
    RUN_TEST(test_update_key_state_rt_released_outside_down_sensitivity_range);

    RUN_TEST(test_update_key_state_fixed_above_actuation_point);
    RUN_TEST(test_update_key_state_fixed_below_actuation_point);

    UNITY_END();
}

#ifdef ARDUINO
#include <Arduino.h>

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    // Wait for serial connection to establish
    while (!Serial)
    {
        delay(10);
    }

    process();
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
#else
int main(void)
{
    process();
    return 0;
}
#endif

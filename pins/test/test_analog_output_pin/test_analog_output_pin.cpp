#include <unity.h>
#include <Pin.h>

void test_initialize_initializes()
{
    InMemoryBoard board = InMemoryBoard();
    AnalogOutputPin pin = AnalogOutputPin(&board, PIN_PD6);
    bool results[2] = {0};

    results[0] = pin.initialize();
    results[1] = pin.get_is_initialized();

    TEST_ASSERT_TRUE(results[0]);
    TEST_ASSERT_TRUE(results[1]);
}

void test_initialize_does_not_initialize_when_pin_does_not_pwm()
{
    InMemoryBoard board = InMemoryBoard();
    AnalogOutputPin pin = AnalogOutputPin(&board, PIN_PB0);
    bool results[2] = {0};

    results[0] = pin.initialize();
    results[1] = pin.get_is_initialized();

    TEST_ASSERT_FALSE(results[0]);
    TEST_ASSERT_FALSE(results[1]);
}

void test_initialize_does_not_initialize_when_pin_does_not_exist()
{
    InMemoryBoard board = InMemoryBoard();
    AnalogOutputPin pin = AnalogOutputPin(&board, 50);
    bool results[2] = {0};

    results[0] = pin.initialize();
    results[1] = pin.get_is_initialized();

    TEST_ASSERT_FALSE(results[0]);
    TEST_ASSERT_FALSE(results[1]);
}

void test_set_value_updates_value()
{
    InMemoryBoard board = InMemoryBoard();
    AnalogOutputPin pin = AnalogOutputPin(&board, PIN_PD6);
    bool initialized = pin.initialize();
    TEST_ASSERT_TRUE(initialized);
    int results[2] = {0};

    pin.set_value(1);
    results[0] = board.get_pin_value(pin.get_pin());
    pin.set_value(0.5);
    results[1] = board.get_pin_value(pin.get_pin());
    pin.set_value(0);
    results[2] = board.get_pin_value(pin.get_pin());

    TEST_ASSERT_EQUAL_INT(1023, results[0]);
    TEST_ASSERT_EQUAL_INT(509, results[1]);
    TEST_ASSERT_EQUAL_INT(0, results[2]);
}

void test_set_value_updates_value_when_invalid()
{
    InMemoryBoard board = InMemoryBoard();
    AnalogOutputPin pin = AnalogOutputPin(&board, PIN_PD6);
    bool initialized = pin.initialize();
    TEST_ASSERT_TRUE(initialized);
    int results[2] = {0};

    pin.set_value(-1);
    results[0] = board.get_pin_value(pin.get_pin());
    pin.set_value(2);
    results[1] = board.get_pin_value(pin.get_pin());

    TEST_ASSERT_EQUAL_INT(0, results[0]);
    TEST_ASSERT_EQUAL_INT(1023, results[1]);
}

void test_set_value_does_not_update_value_when_not_initialized()
{
    InMemoryBoard board = InMemoryBoard();
    AnalogOutputPin pin = AnalogOutputPin(&board, PIN_PD6);
    bool initialized = pin.get_is_initialized();
    TEST_ASSERT_FALSE(initialized);
    int results[1] = {0};

    pin.set_value(0.5);
    results[0] = board.get_pin_value(pin.get_pin());

    TEST_ASSERT_EQUAL_INT(0, results[0]);
}

int runUnityTests()
{
    UNITY_BEGIN();

    RUN_TEST(test_initialize_initializes);
    RUN_TEST(test_initialize_does_not_initialize_when_pin_does_not_pwm);
    RUN_TEST(test_initialize_does_not_initialize_when_pin_does_not_exist);
    RUN_TEST(test_set_value_updates_value);
    RUN_TEST(test_set_value_updates_value_when_invalid);
    RUN_TEST(test_set_value_does_not_update_value_when_not_initialized);

    return UNITY_END();
}

void setup()
{
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);

    runUnityTests();
}

void loop() {}

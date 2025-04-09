#include <unity.h>
#include <Pin.h>

void test_initialize_initializes()
{
    InMemoryBoard board = InMemoryBoard();
    AnalogInputPin pin = AnalogInputPin(&board, PIN_A0);
    bool results[2] = {0};

    results[0] = pin.initialize();
    results[1] = pin.get_is_initialized();

    TEST_ASSERT_TRUE(results[0]);
    TEST_ASSERT_TRUE(results[1]);
}

void test_initialize_does_not_initialize_when_pin_does_not_have_analog_input()
{
    InMemoryBoard board = InMemoryBoard();
    AnalogInputPin pin = AnalogInputPin(&board, PIN_PB0);
    bool results[2] = {0};

    results[0] = pin.initialize();
    results[1] = pin.get_is_initialized();

    TEST_ASSERT_FALSE(results[0]);
    TEST_ASSERT_FALSE(results[1]);
}

void test_initialize_does_not_initialize_when_pin_does_not_exist()
{
    InMemoryBoard board = InMemoryBoard();
    AnalogInputPin pin = AnalogInputPin(&board, 50);
    bool results[2] = {0};

    results[0] = pin.initialize();
    results[1] = pin.get_is_initialized();

    TEST_ASSERT_FALSE(results[0]);
    TEST_ASSERT_FALSE(results[1]);
}

void test_get_value_returns_value()
{
    InMemoryBoard board = InMemoryBoard();
    AnalogInputPin pin = AnalogInputPin(&board, PIN_A0);
    bool initialized = pin.initialize();
    TEST_ASSERT_TRUE(initialized);
    float results[2] = {0};

    board.set_pin_value(pin.get_pin(), 1023);
    results[0] = pin.get_value();
    board.set_pin_value(pin.get_pin(), 509);
    results[1] = pin.get_value();
    board.set_pin_value(pin.get_pin(), 0);
    results[2] = pin.get_value();

    TEST_ASSERT_EQUAL_FLOAT(1, results[0]);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, results[1]);
    TEST_ASSERT_EQUAL_FLOAT(0, results[2]);
}

void test_get_value_returns_false_when_not_initialized()
{
    InMemoryBoard board = InMemoryBoard();
    AnalogInputPin pin = AnalogInputPin(&board, PIN_A0);
    bool initialized = pin.get_is_initialized();
    TEST_ASSERT_FALSE(initialized);
    float results[1] = {0};

    board.set_pin_value(pin.get_pin(), 508);
    results[0] = pin.get_value();

    TEST_ASSERT_EQUAL_FLOAT(0, results[0]);
}

int runUnityTests()
{
    UNITY_BEGIN();

    RUN_TEST(test_initialize_initializes);
    RUN_TEST(test_initialize_does_not_initialize_when_pin_does_not_have_analog_input);
    RUN_TEST(test_initialize_does_not_initialize_when_pin_does_not_exist);
    RUN_TEST(test_get_value_returns_value);
    RUN_TEST(test_get_value_returns_false_when_not_initialized);

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

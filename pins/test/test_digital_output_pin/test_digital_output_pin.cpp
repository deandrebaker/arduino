#include <unity.h>
#include <Pin.h>

void test_initialize_initializes()
{
    InMemoryBoard board = InMemoryBoard();
    DigitalOutputPin pin = DigitalOutputPin(&board, PIN_PB0);
    bool results[2] = {0};

    results[0] = pin.initialize();
    results[1] = pin.get_is_initialized();

    TEST_ASSERT_TRUE(results[0]);
    TEST_ASSERT_TRUE(results[1]);
}

void test_initialize_does_not_initialize_when_pin_does_not_exist()
{
    InMemoryBoard board = InMemoryBoard();
    DigitalOutputPin pin = DigitalOutputPin(&board, 50);
    bool results[2] = {0};

    results[0] = pin.initialize();
    results[1] = pin.get_is_initialized();

    TEST_ASSERT_FALSE(results[0]);
    TEST_ASSERT_FALSE(results[1]);
}

void test_set_value_updates_value()
{
    InMemoryBoard board = InMemoryBoard();
    DigitalOutputPin pin = DigitalOutputPin(&board, PIN_PB0);
    bool initialized = pin.initialize();
    TEST_ASSERT_TRUE(initialized);
    bool results[2] = {0};

    pin.set_value(HIGH);
    results[0] = board.get_pin_value(pin.get_pin());
    pin.set_value(LOW);
    results[1] = board.get_pin_value(pin.get_pin());

    TEST_ASSERT_EQUAL_INT(HIGH, results[0]);
    TEST_ASSERT_EQUAL_INT(LOW, results[1]);
}

void test_set_value_does_not_update_value_when_not_initialized()
{
    InMemoryBoard board = InMemoryBoard();
    DigitalOutputPin pin = DigitalOutputPin(&board, PIN_PB0);
    bool initialized = pin.get_is_initialized();
    TEST_ASSERT_FALSE(initialized);
    bool results[1] = {0};

    pin.set_value(HIGH);
    results[0] = board.get_pin_value(pin.get_pin());

    TEST_ASSERT_EQUAL_INT(LOW, results[0]);
}

int runUnityTests()
{
    UNITY_BEGIN();

    RUN_TEST(test_initialize_initializes);
    RUN_TEST(test_initialize_does_not_initialize_when_pin_does_not_exist);
    RUN_TEST(test_set_value_updates_value);
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

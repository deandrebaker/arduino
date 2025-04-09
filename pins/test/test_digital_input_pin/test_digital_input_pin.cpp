#include <unity.h>
#include <Pin.h>

void test_initialize_initializes()
{
    InMemoryBoard board = InMemoryBoard();
    DigitalInputPin pin = DigitalInputPin(&board, PIN_PB0, false);
    bool results[2] = {0};

    results[0] = pin.initialize();
    results[1] = pin.get_is_initialized();

    TEST_ASSERT_TRUE(results[0]);
    TEST_ASSERT_TRUE(results[1]);
}

void test_initialize_initializes_when_pin_is_led_builtin()
{
    InMemoryBoard board = InMemoryBoard();
    DigitalInputPin pin = DigitalInputPin(&board, LED_BUILTIN, false);
    bool results[2] = {0};

    results[0] = pin.initialize();
    results[1] = pin.get_is_initialized();

    TEST_ASSERT_TRUE(results[0]);
    TEST_ASSERT_TRUE(results[1]);
}

void test_initialize_initializes_when_pin_is_pullup()
{
    InMemoryBoard board = InMemoryBoard();
    DigitalInputPin pin = DigitalInputPin(&board, PIN_PB0, true);
    bool results[2] = {0};

    results[0] = pin.initialize();
    results[1] = pin.get_is_initialized();

    TEST_ASSERT_TRUE(results[0]);
    TEST_ASSERT_TRUE(results[1]);
}

void test_initialize_does_not_initialize_when_pin_is_led_builtin_and_pullup()
{
    InMemoryBoard board = InMemoryBoard();
    DigitalInputPin pin = DigitalInputPin(&board, LED_BUILTIN, true);
    bool results[2] = {0};

    results[0] = pin.initialize();
    results[1] = pin.get_is_initialized();

    TEST_ASSERT_FALSE(results[0]);
    TEST_ASSERT_FALSE(results[1]);
}

void test_initialize_does_not_initialize_when_pin_does_not_exist()
{
    InMemoryBoard board = InMemoryBoard();
    DigitalInputPin pin = DigitalInputPin(&board, 50, true);
    bool results[2] = {0};

    results[0] = pin.initialize();
    results[1] = pin.get_is_initialized();

    TEST_ASSERT_FALSE(results[0]);
    TEST_ASSERT_FALSE(results[1]);
}

void test_get_value_returns_value()
{
    InMemoryBoard board = InMemoryBoard();
    DigitalInputPin pin = DigitalInputPin(&board, PIN_PB0, false);
    bool initialized = pin.initialize();
    TEST_ASSERT_TRUE(initialized);
    bool results[2] = {0};

    board.set_pin_value(pin.get_pin(), HIGH);
    results[0] = pin.get_value();
    board.set_pin_value(pin.get_pin(), LOW);
    results[1] = pin.get_value();

    TEST_ASSERT_EQUAL_INT(HIGH, results[0]);
    TEST_ASSERT_EQUAL_INT(LOW, results[1]);
}

void test_get_value_returns_false_when_not_initialized()
{
    InMemoryBoard board = InMemoryBoard();
    DigitalInputPin pin = DigitalInputPin(&board, PIN_PB0, false);
    bool initialized = pin.get_is_initialized();
    TEST_ASSERT_FALSE(initialized);
    bool results[1] = {0};

    board.set_pin_value(pin.get_pin(), HIGH);
    results[0] = pin.get_value();

    TEST_ASSERT_EQUAL_INT(LOW, results[0]);
}

int runUnityTests()
{
    UNITY_BEGIN();

    RUN_TEST(test_initialize_initializes);
    RUN_TEST(test_initialize_initializes_when_pin_is_led_builtin);
    RUN_TEST(test_initialize_initializes_when_pin_is_pullup);
    RUN_TEST(test_initialize_does_not_initialize_when_pin_is_led_builtin_and_pullup);
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

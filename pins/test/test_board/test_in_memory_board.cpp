#include <unity.h>
#include <Board.h>

void test_digital_read_when_pin_mode_is_input()
{
    InMemoryBoard board = InMemoryBoard();
    byte pin = PIN_PB0;
    int results[3] = {};
    board.set_pin_mode(pin, INPUT);

    results[0] = board.digital_read(pin);
    board.set_pin_value(pin, HIGH);
    results[1] = board.digital_read(pin);
    board.set_pin_value(pin, LOW);
    results[2] = board.digital_read(pin);

    TEST_ASSERT_EQUAL(LOW, results[0]);
    TEST_ASSERT_EQUAL(HIGH, results[1]);
    TEST_ASSERT_EQUAL(LOW, results[2]);
}

void test_digital_read_when_pin_mode_is_input_pullup()
{
    InMemoryBoard board = InMemoryBoard();
    byte pin = PIN_PB0;
    int results[3] = {};
    board.set_pin_mode(pin, INPUT_PULLUP);

    results[0] = board.digital_read(pin);
    board.set_pin_value(pin, HIGH);
    results[1] = board.digital_read(pin);
    board.set_pin_value(pin, LOW);
    results[2] = board.digital_read(pin);

    TEST_ASSERT_EQUAL(HIGH, results[0]);
    TEST_ASSERT_EQUAL(HIGH, results[1]);
    TEST_ASSERT_EQUAL(LOW, results[2]);
}

void test_digital_read_when_pin_mode_is_output()
{
    InMemoryBoard board = InMemoryBoard();
    byte pin = PIN_PB0;
    int results[3] = {};
    board.set_pin_mode(pin, OUTPUT);

    results[0] = board.digital_read(pin);
    board.set_pin_value(pin, HIGH);
    results[1] = board.digital_read(pin);
    board.set_pin_value(pin, LOW);
    results[2] = board.digital_read(pin);

    TEST_ASSERT_EQUAL(LOW, results[0]);
    TEST_ASSERT_EQUAL(HIGH, results[1]);
    TEST_ASSERT_EQUAL(LOW, results[2]);
}

void test_digital_write_when_state_is_valid()
{
    InMemoryBoard board = InMemoryBoard();
    byte pin = PIN_PB0;
    int results[2] = {};
    board.set_pin_mode(pin, OUTPUT);

    board.digital_write(pin, HIGH);
    results[0] = board.get_pin_value(pin);
    board.digital_write(pin, LOW);
    results[1] = board.get_pin_value(pin);

    TEST_ASSERT_EQUAL(HIGH, results[0]);
    TEST_ASSERT_EQUAL(LOW, results[1]);
}

void test_digital_write_when_state_is_invalid()
{
    InMemoryBoard board = InMemoryBoard();
    byte pin = PIN_PB0;
    int results[2] = {};
    board.set_pin_mode(pin, OUTPUT);

    board.digital_write(pin, -1);
    results[0] = board.get_pin_value(pin);
    board.digital_write(pin, 2);
    results[1] = board.get_pin_value(pin);

    TEST_ASSERT_EQUAL(HIGH, results[0]);
    TEST_ASSERT_EQUAL(HIGH, results[1]);
}

void test_analog_read_when_pin_mode_is_input()
{
    InMemoryBoard board = InMemoryBoard();
    byte pin = PIN_A0;
    int results[3] = {};
    board.set_pin_mode(pin, INPUT);

    results[0] = board.analog_read(pin);
    board.set_pin_value(pin, 1023);
    results[1] = board.analog_read(pin);
    board.set_pin_value(pin, 511);
    results[2] = board.digital_read(pin);

    TEST_ASSERT_EQUAL(0, results[0]);
    TEST_ASSERT_EQUAL(1023, results[1]);
    TEST_ASSERT_EQUAL(511, results[2]);
}

void test_analog_read_when_pin_mode_is_not_input()
{
    InMemoryBoard board = InMemoryBoard();
    byte pin = PIN_A0;
    int results[2] = {};

    board.set_pin_mode(pin, INPUT_PULLUP);
    board.set_pin_value(pin, 511);
    results[0] = board.analog_read(pin);
    board.set_pin_mode(pin, OUTPUT);
    board.set_pin_value(pin, 511);
    results[1] = board.analog_read(pin);

    TEST_ASSERT_EQUAL(0, results[0]);
    TEST_ASSERT_EQUAL(0, results[1]);
}

void test_analog_read_when_pin_does_not_have_analog_input()
{
    InMemoryBoard board = InMemoryBoard();
    byte pin = PIN_PB0;
    int results[1] = {};
    board.set_pin_mode(pin, INPUT);

    board.set_pin_value(pin, 511);
    results[0] = board.analog_read(pin);

    TEST_ASSERT_EQUAL(0, results[0]);
}

void test_analog_write_when_value_is_valid()
{
    InMemoryBoard board = InMemoryBoard();
    byte pin = PIN_PD6;
    int results[3] = {};
    board.set_pin_mode(pin, OUTPUT);

    board.analog_write(pin, 255);
    results[0] = board.get_pin_value(pin);
    board.analog_write(pin, 127);
    results[1] = board.get_pin_value(pin);
    board.analog_write(pin, 0);
    results[2] = board.get_pin_value(pin);

    TEST_ASSERT_EQUAL(1023, results[0]);
    TEST_ASSERT_EQUAL(509, results[1]);
    TEST_ASSERT_EQUAL(0, results[2]);
}

void test_analog_write_when_value_is_invalid()
{
    InMemoryBoard board = InMemoryBoard();
    byte pin = PIN_PD6;
    int results[2] = {};
    board.set_pin_mode(pin, OUTPUT);

    board.analog_write(pin, -1);
    results[0] = board.get_pin_value(pin);
    board.analog_write(pin, 256);
    results[1] = board.get_pin_value(pin);

    TEST_ASSERT_EQUAL(0, results[0]);
    TEST_ASSERT_EQUAL(1023, results[1]);
}

void test_analog_write_when_pin_does_not_have_pwm()
{
    InMemoryBoard board = InMemoryBoard();
    byte pin = PIN_PB0;
    int results[1] = {};
    board.set_pin_mode(pin, OUTPUT);

    board.analog_write(pin, 511);
    results[0] = board.get_pin_value(pin);

    TEST_ASSERT_EQUAL(0, results[0]);
}

int runUnityTests()
{
    UNITY_BEGIN();

    RUN_TEST(test_digital_read_when_pin_mode_is_input);
    RUN_TEST(test_digital_read_when_pin_mode_is_input_pullup);
    RUN_TEST(test_digital_read_when_pin_mode_is_output);
    RUN_TEST(test_digital_write_when_state_is_valid);
    RUN_TEST(test_digital_write_when_state_is_invalid);
    RUN_TEST(test_analog_read_when_pin_mode_is_input);
    RUN_TEST(test_analog_read_when_pin_mode_is_not_input);
    RUN_TEST(test_analog_read_when_pin_does_not_have_analog_input);
    RUN_TEST(test_analog_write_when_value_is_valid);
    RUN_TEST(test_analog_write_when_value_is_invalid);
    RUN_TEST(test_analog_write_when_pin_does_not_have_pwm);

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

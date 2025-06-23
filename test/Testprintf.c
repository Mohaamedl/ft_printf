#include "../unity/src/unity.h"
#include <stdio.h>

int ft_printf(const char *format, ...);

void setUp(void) {}
void tearDown(void) {}

void test_example(void)
{
	int len = ft_printf("Hello %s!\n", "world");
	TEST_ASSERT_EQUAL_INT(13, len); // Adjust depending on your ft_printf
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_example);
	return UNITY_END();
}


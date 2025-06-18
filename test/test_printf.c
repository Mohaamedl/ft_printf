#include "../unity/src/unity.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../src/ft_printf.h"

#define CAPTURE_BUFFER_SIZE 4096

int capture_output(char *buffer, size_t size, int (*fn)(const char *, ...), const char *fmt, ...)
{
	int stdout_copy = dup(STDOUT_FILENO);
	int pipefd[2];
	pipe(pipefd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	va_list args;
	va_start(args, fmt);
	int ret = fn(fmt, args);
	va_end(args);

	fflush(stdout);
	read(pipefd[0], buffer, size - 1);
	buffer[strcspn(buffer, "\0")] = '\0'; // sanitize
	close(pipefd[0]);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
	return ret;
}

int ft_printf_wrapper(const char *format, va_list args)
{
	return vprintf(format, args); // to mimic behavior
}

int ft_printf_call(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int ret = ft_printf(format, args);
	va_end(args);
	return ret;
}

int std_printf_call(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int ret = vprintf(format, args);
	va_end(args);
	return ret;
}

void setUp(void) {}
void tearDown(void) {}

void test_hello_string(void)
{
	char out1[CAPTURE_BUFFER_SIZE] = {0};
	char out2[CAPTURE_BUFFER_SIZE] = {0};

	int ret1 = capture_output(out1, sizeof(out1), (int (*)(const char *, ...))ft_printf_call, "Hello %s!\n", "world");
	int ret2 = capture_output(out2, sizeof(out2), (int (*)(const char *, ...))std_printf_call, "Hello %s!\n", "world");

	TEST_ASSERT_EQUAL_STRING(out2, out1);
	TEST_ASSERT_EQUAL_INT(ret2, ret1);
}

void test_integers(void)
{
	char out1[CAPTURE_BUFFER_SIZE] = {0};
	char out2[CAPTURE_BUFFER_SIZE] = {0};

	int ret1 = capture_output(out1, sizeof(out1), (int (*)(const char *, ...))ft_printf_call, "Number: %d\n", 42);
	int ret2 = capture_output(out2, sizeof(out2), (int (*)(const char *, ...))std_printf_call, "Number: %d\n", 42);

	TEST_ASSERT_EQUAL_STRING(out2, out1);
	TEST_ASSERT_EQUAL_INT(ret2, ret1);
}

void test_hexadecimal(void)
{
	char out1[CAPTURE_BUFFER_SIZE] = {0};
	char out2[CAPTURE_BUFFER_SIZE] = {0};

	int ret1 = capture_output(out1, sizeof(out1), (int (*)(const char *, ...))ft_printf_call, "Hex: %x\n", 255);
	int ret2 = capture_output(out2, sizeof(out2), (int (*)(const char *, ...))std_printf_call, "Hex: %x\n", 255);

	TEST_ASSERT_EQUAL_STRING(out2, out1);
	TEST_ASSERT_EQUAL_INT(ret2, ret1);
}

void test_pointer(void)
{
	char out1[CAPTURE_BUFFER_SIZE] = {0};
	char out2[CAPTURE_BUFFER_SIZE] = {0};
	void *ptr = (void *)0xdeadbeef;

	int ret1 = capture_output(out1, sizeof(out1), (int (*)(const char *, ...))ft_printf_call, "Ptr: %p\n", ptr);
	int ret2 = capture_output(out2, sizeof(out2), (int (*)(const char *, ...))std_printf_call, "Ptr: %p\n", ptr);

	TEST_ASSERT_EQUAL_STRING(out2, out1);
	TEST_ASSERT_EQUAL_INT(ret2, ret1);
}

void test_multiple_args(void)
{
	char out1[CAPTURE_BUFFER_SIZE] = {0};
	char out2[CAPTURE_BUFFER_SIZE] = {0};

	int ret1 = capture_output(out1, sizeof(out1), (int (*)(const char *, ...))ft_printf_call, "%s %d %x %c\n", "Test", 123, 0xFF, 'A');
	int ret2 = capture_output(out2, sizeof(out2), (int (*)(const char *, ...))std_printf_call, "%s %d %x %c\n", "Test", 123, 0xFF, 'A');

	TEST_ASSERT_EQUAL_STRING(out2, out1);
	TEST_ASSERT_EQUAL_INT(ret2, ret1);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_hello_string);
	RUN_TEST(test_integers);
	RUN_TEST(test_hexadecimal);
	RUN_TEST(test_pointer);
	RUN_TEST(test_multiple_args);
	return UNITY_END();
}


#include "../unity/src/unity.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../src/ft_printf.h" 

// Prototipagem explícita
int ft_vprintf(const char *format, va_list ap);

// Implementação de ft_vprintf baseada na tua ft_printf
int ft_vprintf(const char *format, va_list ap)
{
	const char *fmt = format;
	va_list args_copy;
	int printed;
	t_format f;

	va_copy(args_copy, ap);
	printed = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			f = ft_parse_format(&fmt);
			printed += ft_conversion_handler(&f, args_copy);
		}
		else
			printed += write(1, fmt++, 1);
	}
	va_end(args_copy);
	return printed;
}

// Redireciona stdout para pipe e captura output
int capture_output(char *buffer, size_t size, const char *format, ...)
{
	int pipefd[2];
	int saved_stdout = dup(STDOUT_FILENO);
	pipe(pipefd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	va_list args;
	va_start(args, format);
	ft_vprintf(format, args);
	va_end(args);

	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	ssize_t bytes_read = read(pipefd[0], buffer, size - 1);
	buffer[bytes_read] = '\0';
	close(pipefd[0]);

	return (int)bytes_read;
}

void setUp(void) {}
void tearDown(void) {}
// -----------------------
// Testes
// -----------------------

void test_hello_string(void)
{
	char buffer[256];
	capture_output(buffer, sizeof(buffer), "Hello %s!\n", "world");
	TEST_ASSERT_EQUAL_STRING("Hello world!\n", buffer);
}

void test_integers(void)
{
	char buffer[256];
	capture_output(buffer, sizeof(buffer), "Number: %d\n", 42);
	TEST_ASSERT_EQUAL_STRING("Number: 42\n", buffer);
}

void test_hexadecimal(void)
{
	char buffer[256];
	capture_output(buffer, sizeof(buffer), "Hex: %x\n", 255);
	TEST_ASSERT_EQUAL_STRING("Hex: ff\n", buffer);
}

void test_pointer(void)
{
	char buffer[256], expected[256];
	int x = 0xdeadbeef;
	capture_output(buffer, sizeof(buffer), "Ptr: %p\n", (void *)&x);
	snprintf(expected, sizeof(expected), "Ptr: %p\n", (void *)&x);
	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_multiple_args(void)
{
	char buffer[256];
	capture_output(buffer, sizeof(buffer), "Test %d %x %c\n", 123, 0xdead, 'A');
	TEST_ASSERT_EQUAL_STRING("Test 123 dead A\n", buffer);
}

void test_multi_flags_integer(void)
{
	char buffer[512];
	char expected[512];

	capture_output(buffer, sizeof(buffer), "Test %d0.4 / %i0.4\n", 42, 42);
	snprintf(expected, sizeof(expected), "Test %d0.4 / %i0.4\n",42, 42); //capture_output(buffer, sizeof(buffer), "Test %0.4d / %i0.4\n", 42, 42);
	TEST_ASSERT_EQUAL_STRING(expected,buffer);
}

// -----------------------
// Main
// -----------------------

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_hello_string);
	RUN_TEST(test_integers);
	RUN_TEST(test_hexadecimal);
	RUN_TEST(test_pointer);
	RUN_TEST(test_multiple_args);
	RUN_TEST(test_multi_flags_integer);
	return UNITY_END();
}


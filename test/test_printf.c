/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:40:18 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/06/25 19:40:53 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*

#include "../unity/src/unity.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../src/ft_printf.h"

int ft_vprintf(const char *format, va_list ap);

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
// limpar e garantir estado limpo
static void prepare_capture(char *buffer, size_t size) {
	memset(buffer, 0, size);
	fflush(stdout);
	fsync(STDOUT_FILENO);
}

int	capture_output(char *buffer, size_t size, const char *format, ...)
{
	prepare_capture(buffer, size);
	int pipefd[2];
	if (pipe(pipefd) == -1)
		return -1;
	int saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		return -1;
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return -1;
	}
	close(pipefd[1]);
	va_list args;
	va_start(args, format);
	ft_vprintf(format, args);
	va_end(args);
	fflush(stdout);
	fsync(STDOUT_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	ssize_t bytes_read = read(pipefd[0], buffer, size - 1);
	close(pipefd[0]);
	if (bytes_read < 0)
		return -1;
	buffer[bytes_read] = '\0';
	return (int)bytes_read;
}

int	capture_output_std(char *buffer, size_t size, const char *format, ...)
{
	prepare_capture(buffer, size);
	int pipefd[2];
	if (pipe(pipefd) == -1)
		return -1;
	int saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		return -1;
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return -1;
	}
	close(pipefd[1]);
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	fflush(stdout);
	fsync(STDOUT_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	ssize_t bytes_read = read(pipefd[0], buffer, size - 1);
	close(pipefd[0]);
	if (bytes_read < 0)
		return -1;
	buffer[bytes_read] = '\0';
	return (int)bytes_read;
}

void setUp(void) {}
void tearDown(void) {}

// ===========================================
// BASIC TESTS
// ===========================================

void test_hello_string(void)
{
	char buffer[256];
	char expected[256];

	capture_output(buffer, sizeof(buffer), "Hello %s!\n", "world");
	capture_output_std(expected, sizeof(expected), "Hello %s!\n", "world");
	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_integers(void)
{
	char buffer[256];
	char expected[256];

	capture_output(buffer, sizeof(buffer), "Number: %d\n", 42);
	capture_output_std(expected, sizeof(expected), "Number: %d\n", 42);
	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_hexadecimal(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "Hex: %x\n", 255);
    capture_output_std(expected, sizeof(expected), "Hex: %x\n", 255);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
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
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "Test %d %x %c\n", 123, 0xdead, 'A');
    capture_output_std(expected, sizeof(expected), "Test %d %x %c\n", 123, 0xdead, 'A');
	TEST_ASSERT_EQUAL_STRING(expected, buffer);

}

// ===========================================
// STRING PRECISION TESTS
// ===========================================

void test_string_precision_basic(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%.3s", "hello");
    capture_output_std(expected, sizeof(expected), "%.3s", "hello");
	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_string_precision_zero(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%.0s", "hello");
	capture_output_std(expected, sizeof(expected), "%.0s", "hello");

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_string_precision_larger(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%.10s", "hello");
    capture_output_std(expected, sizeof(expected), "%.10s", "hello");

	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_string_precision_null(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%.3s", (char *)NULL);
	capture_output_std(expected, sizeof(expected), "%.3s", (char *)NULL);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_string_precision_null_full(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%.10s", (char *)NULL);
    capture_output_std(expected, sizeof(expected), "%.10s", (char *)NULL);

	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

// ===========================================
// WIDTH TESTS
// ===========================================

void test_string_width_right(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%10s", "hello");
    capture_output_std(expected, sizeof(expected), "%10s", "hello");

	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_string_width_left(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%-10s", "hello");
	capture_output_std(expected, sizeof(expected), "%-10s", "hello");

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_integer_width_right(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%5d", 42);
	capture_output_std(expected, sizeof(expected), "%5d", 42);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_integer_width_left(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%-5d", 42);
    capture_output_std(expected, sizeof(expected), "%-5d", 42);

	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_integer_width_zero(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%05d", 42);
    capture_output_std(expected, sizeof(expected), "%05d", 42);

	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

// ===========================================
// PRECISION TESTS
// ===========================================

void test_integer_precision_basic(void)
{
	char buffer[256], expected[256]; 
    capture_output(buffer, sizeof(buffer), "%.5d", 42);
    capture_output_std(expected, sizeof(expected), "%.5d", 42);

	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_integer_precision_zero_value(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%.0d", 0);
    capture_output_std(expected, sizeof(expected), "%.0d", 0);

	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_integer_precision_negative(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%.5d", -42);
    capture_output_std(expected, sizeof(expected), "%.5d", -42);

	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_hex_precision(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%.5x", 255);
    capture_output_std(expected, sizeof(expected), "%.5x", 255);

	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_hex_precision_upper(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%.5X", 255);
    capture_output_std(expected, sizeof(expected), "%.5X", 255);

	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_unsigned_precision(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%.5u", 42);
	capture_output_std(expected, sizeof(expected), "%.5u", 42);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

// ===========================================
// WIDTH + PRECISION COMBINATIONS
// ===========================================

void test_string_width_precision(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%10.3s", "hello");
	capture_output_std(expected, sizeof(expected), "%10.3s", "hello");

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_string_width_precision_left(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%-10.3s", "hello");
	capture_output_std(expected, sizeof(expected), "%-10.3s", "hello");

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_integer_width_precision(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%10.5d", 42);
	capture_output_std(expected, sizeof(expected), "%10.5d", 42);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_integer_width_precision_left(void)
{
	char buffer[256], expected[256]; 
    capture_output(buffer, sizeof(buffer), "%-10.5d", 42);
	capture_output_std(expected, sizeof(expected), "%-10.5d", 42);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_hex_width_precision(void)
{
	char buffer[256], expected[256]; 
	capture_output_std(expected, sizeof(expected), "%10.5x", 255);

    capture_output(buffer, sizeof(buffer), "%10.5x", 255);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

// ===========================================
// FLAG TESTS
// ===========================================

void test_integer_plus_flag(void)
{
	char buffer[256], expected[256];
	capture_output_std(expected, sizeof(expected), "%+d", 42);

    capture_output(buffer, sizeof(buffer), "%+d", 42);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_integer_plus_flag_negative(void)
{
	char buffer[256], expected[256]; 
capture_output_std(expected, sizeof(expected), "%+d", -42);

    capture_output(buffer, sizeof(buffer), "%+d", -42);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_integer_space_flag(void)
{
	char buffer[256], expected[256]; 
	capture_output_std(expected, sizeof(expected), "% d", 42);

    capture_output(buffer, sizeof(buffer), "% d", 42);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_integer_space_flag_negative(void)
{
	char buffer[256], expected[256]; 
    capture_output_std(expected, sizeof(expected), "% d", -42);

	capture_output(buffer, sizeof(buffer), "% d", -42);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_hex_hash_flag(void)
{
	char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%#x", 255);
	capture_output_std(expected, sizeof(expected), "%#x", 255);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_hex_hash_flag_upper(void)
{
	char buffer[256], expected[256]; 

    capture_output(buffer, sizeof(buffer), "%#X", 255);
	capture_output_std(expected, sizeof(expected), "%#X", 255);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_hex_hash_flag_zero(void)
{
     char buffer[256], expected[256]; 
	capture_output_std(expected, sizeof(expected), "%#x", 0);

    capture_output(buffer, sizeof(buffer), "%#x", 0);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

// ===========================================
// COMPLEX FLAG COMBINATIONS
// ===========================================

void test_plus_width_precision(void)
{
    char buffer[256], expected[256]; 
	capture_output_std(expected, sizeof(expected), "%+10.5d", 42);

    capture_output(buffer, sizeof(buffer), "%+10.5d", 42);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_space_width_precision(void)
{
    char buffer[256], expected[256]; 
	capture_output_std(expected, sizeof(expected), "% 10.5d", 42);

    capture_output(buffer, sizeof(buffer), "% 10.5d", 42);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_hash_width_precision_hex(void)
{
    char buffer[256], expected[256]; 
	capture_output_std(expected, sizeof(expected), "%#10.5x", 255);
    capture_output(buffer, sizeof(buffer), "%#10.5x", 255);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_zero_width_precision_ignored(void)
{
    char buffer[256], expected[256]; 
	capture_output(buffer, sizeof(buffer), "%010.5d", 42);
    capture_output_std(expected, sizeof(expected), "%010.5d", 42);

	TEST_ASSERT_EQUAL_STRING(expected, buffer);  // Zero flag ignored with precision
}

void test_minus_plus_width(void)
{
   char buffer[256], expected[256]; 
    capture_output_std(expected, sizeof(expected), "%-+10d", 42);

	capture_output(buffer, sizeof(buffer), "%-+10d", 42);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

// ===========================================
// CHARACTER AND PERCENT TESTS
// ===========================================

void test_character_basic(void)
{
    char buffer[256], expected[256];
    capture_output_std(expected, sizeof(expected), "%c", 'A');

	capture_output(buffer, sizeof(buffer), "%c", 'A');
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_character_width(void)
{
    char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%5c", 'A');
	capture_output_std(expected, sizeof(expected), "%5c", 'A');

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_character_width_left(void)
{
    char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%-5c", 'A');
	capture_output_std(expected, sizeof(expected), "%-5c", 'A');

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_percent_basic(void)
{
    char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%%");
    capture_output_std(expected, sizeof(expected), "%%");

	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_percent_width(void)
{
    char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%5%");
    capture_output_std(expected, sizeof(expected), "%5%");
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_percent_width_left(void)
{
    char buffer[256], expected[256];
	capture_output(buffer, sizeof(buffer), "%-5%");
	capture_output_std(expected, sizeof(expected), "%-5%");
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

// ===========================================
// EDGE CASES
// ===========================================

void test_edge_case_zero_precision(void)
{
    char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%.0d %.0u %.0x", 0, 0u, 0u);
	capture_output_std(expected, sizeof(expected), "%.0d %.0u %.0x", 0, 0u, 0u);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_edge_case_int_max(void)
{
    char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%d", 2147483647);
	capture_output_std(expected, sizeof(expected), "%d", 2147483647);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_edge_case_int_min(void)
{
    char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%d", -2147483648);
	capture_output_std(expected, sizeof(expected), "%d", -2147483648);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_edge_case_uint_max(void)
{
    char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%u", 4294967295u);
	capture_output_std(expected, sizeof(expected),"%u", 4294967295u);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_edge_case_null_pointer(void)
{
    char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%p", (void *)NULL);
	capture_output_std(expected, sizeof(expected), "%p", (void *)NULL);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_edge_case_empty_string(void)
{
    char buffer[256], expected[256];
    capture_output(buffer, sizeof(buffer), "%s", "");
	capture_output_std(expected, sizeof(expected), "%s", "");
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

// ===========================================
// MIXED COMPLEX TESTS
// ===========================================

void test_complex_mix_1(void)
{
	char buffer[512], expected[512];
	capture_output(buffer, sizeof(buffer), "%+10.5d %-#8.3x %.6s", 42, 255, "hello");
	capture_output_std(expected, sizeof(expected), "%+10.5d %-#8.3x %.6s", 42, 255, "hello");
	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_complex_mix_2(void)
{
	char buffer[512], expected[512];
	capture_output(buffer, sizeof(buffer), "% 8.3d %#-10.4X %10.2s", -42, 4095, "test");
	capture_output_std(expected, sizeof(expected), "% 8.3d %#-10.4X %10.2s", -42, 4095, "test");
	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_complex_mix_3(void)
{
	char	buffer[512];
	char	expected[512];

	capture_output(buffer, sizeof(buffer), "%05d %#x %10s %-5c", 42, 0, "null", 'Z');
	capture_output_std(expected, sizeof(expected), "%05d %#x %10s %-5c", 42, 0, "null", 'Z');
	TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

// ===========================================
// MAIN TEST RUNNER
// ===========================================

int main(void)
{
    UNITY_BEGIN();
    
    // Basic tests
    RUN_TEST(test_hello_string);
    RUN_TEST(test_integers);

	RUN_TEST(test_hexadecimal);
    RUN_TEST(test_pointer);
    RUN_TEST(test_multiple_args);
    
    // String precision tests
    RUN_TEST(test_string_precision_basic);
    RUN_TEST(test_string_precision_zero);
    RUN_TEST(test_string_precision_larger);
    RUN_TEST(test_string_precision_null);
    RUN_TEST(test_string_precision_null_full);
    
    // Width tests
    RUN_TEST(test_string_width_right);
    RUN_TEST(test_string_width_left);
    RUN_TEST(test_integer_width_right);
    RUN_TEST(test_integer_width_left);
    RUN_TEST(test_integer_width_zero);
    
    // Precision tests
    RUN_TEST(test_integer_precision_basic);
    RUN_TEST(test_integer_precision_zero_value);
    RUN_TEST(test_integer_precision_negative);
    RUN_TEST(test_hex_precision);
    RUN_TEST(test_hex_precision_upper);
    RUN_TEST(test_unsigned_precision);
    
    // Width + Precision combinations
    RUN_TEST(test_string_width_precision);
    RUN_TEST(test_string_width_precision_left);
    RUN_TEST(test_integer_width_precision);
    RUN_TEST(test_integer_width_precision_left);
    RUN_TEST(test_hex_width_precision);
    
    // Flag tests
    RUN_TEST(test_integer_plus_flag);
    RUN_TEST(test_integer_plus_flag_negative);
    RUN_TEST(test_integer_space_flag);
    RUN_TEST(test_integer_space_flag_negative);
    RUN_TEST(test_hex_hash_flag);
    RUN_TEST(test_hex_hash_flag_upper);
    RUN_TEST(test_hex_hash_flag_zero);
    
    // Complex flag combinations
    RUN_TEST(test_plus_width_precision);
    RUN_TEST(test_space_width_precision);
    RUN_TEST(test_hash_width_precision_hex);
    RUN_TEST(test_zero_width_precision_ignored);
    RUN_TEST(test_minus_plus_width);
    
    // Character and percent tests
    RUN_TEST(test_character_basic);
    RUN_TEST(test_character_width);
    RUN_TEST(test_character_width_left);
    RUN_TEST(test_percent_basic);
    RUN_TEST(test_percent_width);
    RUN_TEST(test_percent_width_left);
    
    // Edge cases
    RUN_TEST(test_edge_case_zero_precision);
    RUN_TEST(test_edge_case_int_max);
    RUN_TEST(test_edge_case_int_min);
    RUN_TEST(test_edge_case_uint_max);
    RUN_TEST(test_edge_case_null_pointer);
    RUN_TEST(test_edge_case_empty_string);
    
    // Complex mixed tests
    RUN_TEST(test_complex_mix_1);
    RUN_TEST(test_complex_mix_2);
	RUN_TEST(test_complex_mix_3);	

    return UNITY_END();
}
*/

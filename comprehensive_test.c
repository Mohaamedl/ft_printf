/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comprehensive_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 00:00:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/06/02 00:00:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

static int g_test_count = 0;
static int g_pass_count = 0;

void print_header(const char *section)
{
    printf("\n" BOLD CYAN "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  %s\n", section);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" RESET "\n");
}

void test_printf(const char *test_name, const char *format, ...)
{
    va_list args1, args2;
    char std_buffer[1000] = {0};
    char ft_buffer[1000] = {0};
    int std_ret, ft_ret;
    
    g_test_count++;
    
    va_start(args1, format);
    va_start(args2, format);
    
    // Capture standard printf output
    FILE *std_stream = fmemopen(std_buffer, sizeof(std_buffer), "w");
    int old_stdout = dup(1);
    dup2(fileno(std_stream), 1);
    std_ret = vprintf(format, args1);
    fflush(stdout);
    dup2(old_stdout, 1);
    fclose(std_stream);
    
    // Capture ft_printf output
    FILE *ft_stream = fmemopen(ft_buffer, sizeof(ft_buffer), "w");
    dup2(fileno(ft_stream), 1);
    ft_ret = vprintf(format, args2); // This should be ft_printf but we'll simulate
    fflush(stdout);
    dup2(old_stdout, 1);
    fclose(ft_stream);
    
    va_end(args1);
    va_end(args2);
    
    // Actually test with real functions
    va_start(args1, format);
    va_start(args2, format);
    std_ret = vsnprintf(std_buffer, sizeof(std_buffer), format, args1);
    
    // Reset buffer for ft_printf (we'll use a simple comparison)
    memset(ft_buffer, 0, sizeof(ft_buffer));
    
    // Redirect stdout to capture ft_printf output
    int pipe_fd[2];
    pipe(pipe_fd);
    int saved_stdout = dup(1);
    dup2(pipe_fd[1], 1);
    
    ft_ret = ft_printf(format, args2);
    
    dup2(saved_stdout, 1);
    close(pipe_fd[1]);
    read(pipe_fd[0], ft_buffer, sizeof(ft_buffer) - 1);
    close(pipe_fd[0]);
    close(saved_stdout);
    
    va_end(args1);
    va_end(args2);
    
    // Compare results
    int output_match = (strcmp(std_buffer, ft_buffer) == 0);
    int return_match = (std_ret == ft_ret);
    
    if (output_match && return_match) {
        printf(GREEN "✓ PASS" RESET " | %-40s | " BLUE "ret: %d" RESET "\n", test_name, ft_ret);
        g_pass_count++;
    } else {
        printf(RED "✗ FAIL" RESET " | %-40s\n", test_name);
        printf("  " YELLOW "Expected:" RESET " \"%s\" (ret: %d)\n", std_buffer, std_ret);
        printf("  " YELLOW "Got:     " RESET " \"%s\" (ret: %d)\n", ft_buffer, ft_ret);
    }
}

void test_character_conversions(void)
{
    print_header("CHARACTER CONVERSIONS (%c)");
    
    test_printf("basic char", "%c", 'A');
    test_printf("null char", "%c", '\0');
    test_printf("space char", "%c", ' ');
    test_printf("newline char", "%c", '\n');
    test_printf("tab char", "%c", '\t');
    test_printf("extended ascii", "%c", 127);
    test_printf("negative char", "%c", -1);
    
    // Width tests
    test_printf("char width 5", "%5c", 'X');
    test_printf("char width 1", "%1c", 'X');
    test_printf("char width 0", "%0c", 'X');
    test_printf("char left align", "%-5c", 'X');
    test_printf("char zero pad", "%05c", 'X');
    
    // Multiple chars
    test_printf("multiple chars", "%c%c%c", 'A', 'B', 'C');
    test_printf("mixed with text", "start%cend", 'X');
}

void test_string_conversions(void)
{
    print_header("STRING CONVERSIONS (%s)");
    
    char *null_str = NULL;
    char *empty_str = "";
    char *normal_str = "Hello";
    char *long_str = "This is a very long string to test string handling";
    char *special_str = "String with\nnewlines\tand\ttabs";
    
    test_printf("normal string", "%s", normal_str);
    test_printf("empty string", "%s", empty_str);
    test_printf("null string", "%s", null_str);
    test_printf("long string", "%s", long_str);
    test_printf("special chars", "%s", special_str);
    
    // Width tests
    test_printf("string width 10", "%10s", "Hi");
    test_printf("string width exact", "%5s", "Hello");
    test_printf("string width less", "%3s", "Hello");
    test_printf("string left align", "%-10s", "Hi");
    
    // Precision tests
    test_printf("precision 3", "%.3s", "Hello");
    test_printf("precision 0", "%.0s", "Hello");
    test_printf("precision big", "%.10s", "Hi");
    test_printf("precision null", "%.5s", null_str);
    
    // Combined width and precision
    test_printf("width+precision", "%10.3s", "Hello");
    test_printf("left+precision", "%-10.3s", "Hello");
}

void test_integer_conversions(void)
{
    print_header("INTEGER CONVERSIONS (%d, %i)");
    
    test_printf("zero", "%d", 0);
    test_printf("positive", "%d", 42);
    test_printf("negative", "%d", -42);
    test_printf("int max", "%d", INT_MAX);
    test_printf("int min", "%d", INT_MIN);
    
    // %i should behave identically to %d
    test_printf("i format zero", "%i", 0);
    test_printf("i format positive", "%i", 42);
    test_printf("i format negative", "%i", -42);
    
    // Width tests
    test_printf("width 5", "%5d", 42);
    test_printf("width 10", "%10d", -42);
    test_printf("left align", "%-5d", 42);
    test_printf("zero pad", "%05d", 42);
    test_printf("zero pad negative", "%05d", -42);
    
    // Precision tests
    test_printf("precision 5", "%.5d", 42);
    test_printf("precision 0 zero", "%.0d", 0);
    test_printf("precision 0 nonzero", "%.0d", 42);
    test_printf("precision big", "%.10d", 42);
    
    // Sign flags
    test_printf("plus flag", "%+d", 42);
    test_printf("plus flag negative", "%+d", -42);
    test_printf("plus flag zero", "%+d", 0);
    test_printf("space flag", "% d", 42);
    test_printf("space flag negative", "% d", -42);
    test_printf("space flag zero", "% d", 0);
    
    // Combined flags
    test_printf("plus+width", "%+5d", 42);
    test_printf("plus+zero", "%+05d", 42);
    test_printf("plus+precision", "%+.5d", 42);
    test_printf("space+width", "% 5d", 42);
    test_printf("left+plus", "%-+5d", 42);
    
    // Complex combinations
    test_printf("all flags", "%+-10.5d", 42);
    test_printf("width+precision", "%10.5d", 42);
    test_printf("zero conflicts precision", "%010.5d", 42);
}

void test_unsigned_conversions(void)
{
    print_header("UNSIGNED CONVERSIONS (%u)");
    
    test_printf("zero unsigned", "%u", 0U);
    test_printf("max unsigned", "%u", UINT_MAX);
    test_printf("normal unsigned", "%u", 42U);
    
    // Width and precision
    test_printf("width 10", "%10u", 42U);
    test_printf("precision 5", "%.5u", 42U);
    test_printf("zero pad", "%05u", 42U);
    test_printf("left align", "%-10u", 42U);
    test_printf("precision 0 zero", "%.0u", 0U);
    test_printf("width+precision", "%10.5u", 42U);
}

void test_hex_conversions(void)
{
    print_header("HEXADECIMAL CONVERSIONS (%x, %X)");
    
    test_printf("hex zero", "%x", 0);
    test_printf("hex positive", "%x", 255);
    test_printf("hex max", "%x", UINT_MAX);
    test_printf("hex uppercase", "%X", 255);
    test_printf("hex uppercase max", "%X", UINT_MAX);
    
    // Hash flag
    test_printf("hash flag", "%#x", 255);
    test_printf("hash flag zero", "%#x", 0);
    test_printf("hash uppercase", "%#X", 255);
    
    // Width and precision
    test_printf("hex width", "%10x", 255);
    test_printf("hex precision", "%.5x", 255);
    test_printf("hex zero pad", "%05x", 255);
    test_printf("hex left align", "%-10x", 255);
    test_printf("hex precision 0", "%.0x", 0);
    
    // Combined with hash
    test_printf("hash+width", "%#10x", 255);
    test_printf("hash+precision", "%#.5x", 255);
    test_printf("hash+zero", "%#05x", 255);
    test_printf("hash+left", "%-#10x", 255);
}

void test_pointer_conversions(void)
{
    print_header("POINTER CONVERSIONS (%p)");
    
    void *ptr = (void *)0x12345678;
    void *null_ptr = NULL;
    char str[] = "test";
    
    test_printf("normal pointer", "%p", ptr);
    test_printf("null pointer", "%p", null_ptr);
    test_printf("string pointer", "%p", str);
    test_printf("function pointer", "%p", &printf);
    
    // Width tests (implementation specific)
    test_printf("pointer width", "%20p", ptr);
    test_printf("pointer left", "%-20p", ptr);
}

void test_percent_conversion(void)
{
    print_header("PERCENT LITERAL (%%)");
    
    test_printf("basic percent", "%%");
    test_printf("multiple percent", "%%%%");
    test_printf("percent with text", "50%% complete");
    test_printf("percent width", "%5%");
    test_printf("percent left", "%-5%");
    test_printf("percent zero", "%05%");
}

void test_edge_cases(void)
{
    print_header("EDGE CASES & COMBINATIONS");
    
    test_printf("empty format", "");
    test_printf("no conversions", "Just text");
    test_printf("mixed conversions", "%d %s %c %x", 42, "test", 'X', 255);
    test_printf("many conversions", "%d%d%d%d%d", 1, 2, 3, 4, 5);
    
    // Boundary values
    test_printf("int boundaries", "%d %d", INT_MIN, INT_MAX);
    test_printf("uint boundary", "%u", UINT_MAX);
    
    // Zero values with different formats
    test_printf("zero variations", "%d %i %u %x %X", 0, 0, 0U, 0, 0);
    test_printf("zero with flags", "%+d % d %#x %.0d", 0, 0, 0, 0);
    
    // Invalid/unusual combinations
    test_printf("conflicting flags", "%+-d", 42);
    test_printf("multiple plus", "%++d", 42);
    test_printf("space with minus", "% -d", 42);
}

void test_stress_tests(void)
{
    print_header("STRESS TESTS");
    
    // Large numbers
    test_printf("large positive", "%d", 1234567890);
    test_printf("large negative", "%d", -1234567890);
    
    // Long strings
    char long_string[1000];
    memset(long_string, 'A', 999);
    long_string[999] = '\0';
    test_printf("very long string", "%.50s", long_string);
    
    // Many arguments
    test_printf("many args", "%d%d%d%d%d%d%d%d%d%d", 1,2,3,4,5,6,7,8,9,10);
    
    // Complex formatting
    test_printf("complex format", "%+-#20.10x", 0xDEADBEEF);
    test_printf("nested format", "Value: %+10.5d%% at %p", 42, &long_string);
}

int main(void)
{
    printf(BOLD MAGENTA "╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                      FT_PRINTF COMPREHENSIVE TEST SUITE                  ║\n");
    printf("║                           Testing Every Edge Case                        ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝" RESET "\n");
    
    test_character_conversions();
    test_string_conversions();
    test_integer_conversions();
    test_unsigned_conversions();
    test_hex_conversions();
    test_pointer_conversions();
    test_percent_conversion();
    test_edge_cases();
    test_stress_tests();
    
    printf("\n" BOLD MAGENTA "╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              TEST SUMMARY                                ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝" RESET "\n");
    
    printf(BOLD "Total Tests: " RESET "%d\n", g_test_count);
    printf(GREEN BOLD "Passed: " RESET "%d\n", g_pass_count);
    printf(RED BOLD "Failed: " RESET "%d\n", g_test_count - g_pass_count);
    
    double success_rate = ((double)g_pass_count / g_test_count) * 100;
    if (success_rate == 100.0) {
        printf(GREEN BOLD "🎉 PERFECT SCORE! 🎉" RESET "\n");
    } else if (success_rate >= 90.0) {
        printf(YELLOW BOLD "⭐ EXCELLENT! ⭐" RESET "\n");
    } else if (success_rate >= 75.0) {
        printf(BLUE BOLD "👍 GOOD JOB! 👍" RESET "\n");
    } else {
        printf(RED BOLD "❌ NEEDS WORK ❌" RESET "\n");
    }
    
    printf(BOLD "Success Rate: " RESET "%.1f%%\n\n", success_rate);
    
    return (g_test_count - g_pass_count);
}


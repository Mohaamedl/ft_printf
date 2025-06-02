/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_case_tests.c                                  :+:      :+:    :+:   */
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
#include <unistd.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

static int g_tests = 0;
static int g_passed = 0;

void print_test_header(const char *category)
{
    printf("\n" BOLD CYAN "╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║  %-64s  ║\n", category);
    printf("╚════════════════════════════════════════════════════════════════════╝" RESET "\n");
}

int compare_outputs(const char *test_name, const char *format, ...)
{
    va_list ap1, ap2;
    int std_ret, ft_ret;
    
    g_tests++;
    
    printf(YELLOW "Testing: " RESET "%-50s ", test_name);
    
    // Standard printf
    va_start(ap1, format);
    printf(BLUE "[STD] " RESET);
    std_ret = vprintf(format, ap1);
    va_end(ap1);
    
    printf("\n%-58s", "");
    
    // ft_printf
    va_start(ap2, format);
    printf(GREEN "[FT_] " RESET);
    ft_ret = ft_printf(format, ap2);
    va_end(ap2);
    
    // Compare return values
    if (std_ret == ft_ret) {
        printf(" " GREEN "✓ PASS" RESET " (ret: %d)\n", ft_ret);
        g_passed++;
        return 1;
    } else {
        printf(" " RED "✗ FAIL" RESET " (std: %d, ft: %d)\n", std_ret, ft_ret);
        return 0;
    }
}

void test_character_edge_cases(void)
{
    print_test_header("CHARACTER CONVERSION EDGE CASES");
    
    compare_outputs("null character", "%c", '\0');
    compare_outputs("negative char cast", "%c", -1);
    compare_outputs("high ascii", "%c", 255);
    compare_outputs("char with width", "%5c", 'X');
    compare_outputs("char left aligned", "%-5c", 'X');
    compare_outputs("char zero padding", "%05c", 'X');
    compare_outputs("multiple chars", "%c%c%c", 'A', 'B', 'C');
    compare_outputs("char in text", "Hello %c World", '!');
}

void test_string_edge_cases(void)
{
    print_test_header("STRING CONVERSION EDGE CASES");
    
    char *null_str = NULL;
    char *empty_str = "";
    char long_str[100];
    memset(long_str, 'X', 99);
    long_str[99] = '\0';
    
    compare_outputs("null string", "%s", null_str);
    compare_outputs("empty string", "%s", empty_str);
    compare_outputs("normal string", "%s", "Hello");
    compare_outputs("string with width", "%10s", "Hi");
    compare_outputs("string left align", "%-10s", "Hi");
    compare_outputs("string precision", "%.3s", "Hello");
    compare_outputs("string precision 0", "%.0s", "Hello");
    compare_outputs("width + precision", "%10.3s", "Hello");
    compare_outputs("precision on null", "%.5s", null_str);
    compare_outputs("long string", "%.20s", long_str);
}

void test_integer_edge_cases(void)
{
    print_test_header("INTEGER CONVERSION EDGE CASES");
    
    compare_outputs("zero", "%d", 0);
    compare_outputs("int max", "%d", INT_MAX);
    compare_outputs("int min", "%d", INT_MIN);
    compare_outputs("plus flag positive", "%+d", 42);
    compare_outputs("plus flag negative", "%+d", -42);
    compare_outputs("plus flag zero", "%+d", 0);
    compare_outputs("space flag positive", "% d", 42);
    compare_outputs("space flag negative", "% d", -42);
    compare_outputs("space flag zero", "% d", 0);
    compare_outputs("width padding", "%10d", 42);
    compare_outputs("zero padding", "%010d", 42);
    compare_outputs("left align", "%-10d", 42);
    compare_outputs("precision", "%.5d", 42);
    compare_outputs("precision zero", "%.0d", 0);
    compare_outputs("precision nonzero", "%.0d", 42);
    compare_outputs("width + precision", "%10.5d", 42);
    compare_outputs("all flags", "%+-10.5d", 42);
    compare_outputs("zero conflicts prec", "%010.5d", 42);
}

void test_unsigned_edge_cases(void)
{
    print_test_header("UNSIGNED INTEGER EDGE CASES");
    
    compare_outputs("unsigned zero", "%u", 0U);
    compare_outputs("unsigned max", "%u", UINT_MAX);
    compare_outputs("unsigned normal", "%u", 42U);
    compare_outputs("unsigned width", "%10u", 42U);
    compare_outputs("unsigned precision", "%.5u", 42U);
    compare_outputs("unsigned zero pad", "%05u", 42U);
    compare_outputs("unsigned left align", "%-10u", 42U);
    compare_outputs("unsigned prec zero", "%.0u", 0U);
    compare_outputs("unsigned w+p", "%10.5u", 42U);
}

void test_hex_edge_cases(void)
{
    print_test_header("HEXADECIMAL CONVERSION EDGE CASES");
    
    compare_outputs("hex zero", "%x", 0);
    compare_outputs("hex positive", "%x", 255);
    compare_outputs("hex max", "%x", UINT_MAX);
    compare_outputs("hex uppercase", "%X", 255);
    compare_outputs("hash flag", "%#x", 255);
    compare_outputs("hash flag zero", "%#x", 0);
    compare_outputs("hash uppercase", "%#X", 255);
    compare_outputs("hex width", "%10x", 255);
    compare_outputs("hex precision", "%.5x", 255);
    compare_outputs("hex zero pad", "%05x", 255);
    compare_outputs("hex left align", "%-10x", 255);
    compare_outputs("hex prec zero", "%.0x", 0);
    compare_outputs("hash + width", "%#10x", 255);
    compare_outputs("hash + zero", "%#05x", 255);
    compare_outputs("hash + left", "%-#10x", 255);
}

void test_pointer_edge_cases(void)
{
    print_test_header("POINTER CONVERSION EDGE CASES");
    
    void *ptr = (void *)0x12345678;
    void *null_ptr = NULL;
    char str[] = "test";
    
    compare_outputs("normal pointer", "%p", ptr);
    compare_outputs("null pointer", "%p", null_ptr);
    compare_outputs("string address", "%p", str);
    compare_outputs("pointer width", "%20p", ptr);
    compare_outputs("pointer left", "%-20p", ptr);
}

void test_percent_edge_cases(void)
{
    print_test_header("PERCENT LITERAL EDGE CASES");
    
    compare_outputs("simple percent", "%%");
    compare_outputs("double percent", "%%%%");
    compare_outputs("percent in text", "Progress: 50%%");
    compare_outputs("percent with width", "%5%");
    compare_outputs("percent left", "%-5%");
    compare_outputs("percent zero", "%05%");
}

void test_complex_combinations(void)
{
    print_test_header("COMPLEX FORMAT COMBINATIONS");
    
    void *ptr = (void *)0x12345678;
    
    compare_outputs("mixed types", "%d %s %c %x", 42, "test", 'X', 255);
    compare_outputs("many integers", "%d%d%d%d%d", 1, 2, 3, 4, 5);
    compare_outputs("all zero", "%d %i %u %x %X", 0, 0, 0U, 0, 0);
    compare_outputs("boundaries", "%d %d %u", INT_MIN, INT_MAX, UINT_MAX);
    compare_outputs("signs and zeros", "%+d % d %#x %.0d", 0, 0, 0, 0);
    compare_outputs("complex format", "Value: %+10.5d%% at %p", 42, &ptr);
}

void test_extreme_edge_cases(void)
{
    print_test_header("EXTREME EDGE CASES");
    
    compare_outputs("empty format", "");
    compare_outputs("just text", "No conversions here!");
    compare_outputs("conflicting flags", "%+-d", 42);
    compare_outputs("space + plus", "% +d", 42);
    compare_outputs("multiple zeros", "%00000d", 42);
    compare_outputs("huge width", "%50d", 42);
    compare_outputs("huge precision", "%.50d", 42);
    compare_outputs("zero width", "%0d", 42);
}

int main(void)
{
    printf(BOLD MAGENTA "╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                        FT_PRINTF EDGE CASE TEST SUITE                    ║\n");
    printf("║                     Comprehensive Testing Framework                      ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝" RESET "\n");
    
    test_character_edge_cases();
    test_string_edge_cases();
    test_integer_edge_cases();
    test_unsigned_edge_cases();
    test_hex_edge_cases();
    test_pointer_edge_cases();
    test_percent_edge_cases();
    test_complex_combinations();
    test_extreme_edge_cases();
    
    printf("\n" BOLD MAGENTA "╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               FINAL RESULTS                              ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝" RESET "\n");
    
    printf(BOLD "Total Tests Run: " RESET "%d\n", g_tests);
    printf(GREEN BOLD "Tests Passed: " RESET "%d\n", g_passed);
    printf(RED BOLD "Tests Failed: " RESET "%d\n", g_tests - g_passed);
    
    double success_rate = ((double)g_passed / g_tests) * 100.0;
    printf(BOLD "Success Rate: " RESET "%.1f%%\n", success_rate);
    
    if (success_rate == 100.0) {
        printf(GREEN BOLD "\n🎉 PERFECT IMPLEMENTATION! 🎉\n" RESET);
        printf(GREEN "Your ft_printf handles all edge cases correctly!\n" RESET);
    } else if (success_rate >= 95.0) {
        printf(YELLOW BOLD "\n⭐ EXCELLENT WORK! ⭐\n" RESET);
        printf(YELLOW "Nearly perfect with only minor issues.\n" RESET);
    } else if (success_rate >= 85.0) {
        printf(BLUE BOLD "\n👍 VERY GOOD! 👍\n" RESET);
        printf(BLUE "Good implementation with room for improvement.\n" RESET);
    } else {
        printf(RED BOLD "\n❌ NEEDS IMPROVEMENT ❌\n" RESET);
        printf(RED "Several edge cases need attention.\n" RESET);
    }
    
    printf("\n" CYAN "Run this test frequently during development!\n" RESET);
    return (g_tests - g_passed);
}
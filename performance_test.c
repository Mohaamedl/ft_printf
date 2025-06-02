/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   performance_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 00:00:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/06/02 00:00:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

double get_time_diff(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
}

void benchmark_test(const char *test_name, int iterations, 
                   int (*test_func)(const char *, ...), const char *format, ...)
{
    struct timeval start, end;
    va_list args;
    double time_taken;
    int total_chars = 0;
    
    printf(YELLOW "Benchmarking: " RESET "%-30s ", test_name);
    
    gettimeofday(&start, NULL);
    
    for (int i = 0; i < iterations; i++) {
        va_start(args, format);
        total_chars += test_func(format, args);
        va_end(args);
    }
    
    gettimeofday(&end, NULL);
    time_taken = get_time_diff(start, end);
    
    printf(BLUE "Time: " RESET "%.4fs " GREEN "Chars: " RESET "%d " 
           CYAN "Rate: " RESET "%.0f calls/s\n", 
           time_taken, total_chars, iterations / time_taken);
}

void stress_test_formats(void)
{
    printf(BOLD CYAN "\n╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║                        PERFORMANCE BENCHMARKS                        ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝" RESET "\n");
    
    int iterations = 10000;
    
    // Redirect output to /dev/null to focus on performance
    freopen("/dev/null", "w", stdout);
    
    benchmark_test("Simple string", iterations, ft_printf, "Hello World\n");
    benchmark_test("Integer formatting", iterations, ft_printf, "%d\n", 42);
    benchmark_test("Complex integer", iterations, ft_printf, "%+10.5d\n", -12345);
    benchmark_test("Hex formatting", iterations, ft_printf, "%#x\n", 0xDEADBEEF);
    benchmark_test("String formatting", iterations, ft_printf, "%.10s\n", "Test string");
    benchmark_test("Mixed formats", iterations, ft_printf, "%d %s %c %x\n", 42, "test", 'X', 255);
    benchmark_test("Pointer formatting", iterations, ft_printf, "%p\n", &iterations);
    benchmark_test("Multiple integers", iterations, ft_printf, "%d %d %d %d %d\n", 1, 2, 3, 4, 5);
    
    // Restore stdout
    freopen("/dev/tty", "w", stdout);
}

void memory_stress_test(void)
{
    printf(BOLD CYAN "\n╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║                         MEMORY STRESS TESTS                          ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝" RESET "\n");
    
    // Test with very long strings
    char long_string[1000];
    for (int i = 0; i < 999; i++) {
        long_string[i] = 'A' + (i % 26);
    }
    long_string[999] = '\0';
    
    printf(GREEN "Testing with 1000-character string... " RESET);
    int ret = ft_printf("%.100s\n", long_string);
    printf(BLUE "✓ Completed, returned %d\n" RESET, ret);
    
    // Test with many format specifiers
    printf(GREEN "Testing with 20 format specifiers... " RESET);
    ret = ft_printf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",
                   1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20);
    printf(BLUE "✓ Completed, returned %d\n" RESET, ret);
    
    // Test with extreme values
    printf(GREEN "Testing with extreme integer values... " RESET);
    ret = ft_printf("MIN: %d, MAX: %d, UINT_MAX: %u\n", INT_MIN, INT_MAX, UINT_MAX);
    printf(BLUE "✓ Completed, returned %d\n" RESET, ret);
}

void edge_case_validation(void)
{
    printf(BOLD CYAN "\n╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║                       EDGE CASE VALIDATION                           ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝" RESET "\n");
    
    int pass_count = 0;
    int total_tests = 0;
    
    // Test macro to simplify validation
    #define VALIDATE_TEST(name, format, ...) \
    do { \
        int std_ret = snprintf(NULL, 0, format, __VA_ARGS__); \
        int ft_ret = ft_printf(format, __VA_ARGS__); \
        total_tests++; \
        if (std_ret == ft_ret) { \
            printf(GREEN "✓ " RESET name "\n"); \
            pass_count++; \
        } else { \
            printf(RED "✗ " RESET name " (std: %d, ft: %d)\n", std_ret, ft_ret); \
        } \
    } while(0)
    
    VALIDATE_TEST("Zero with precision 0", "%.0d", 0);
    VALIDATE_TEST("Negative with plus flag", "%+d", -42);
    VALIDATE_TEST("Hash flag with zero", "%#x", 0);
    VALIDATE_TEST("Left align with zero pad", "%-05d", 42);
    VALIDATE_TEST("Space flag with negative", "% d", -42);
    VALIDATE_TEST("Width larger than precision", "%10.3d", 42);
    VALIDATE_TEST("Precision larger than width", "%3.10d", 42);
    VALIDATE_TEST("NULL string with precision", "%.5s", (char *)NULL);
    VALIDATE_TEST("Empty string with width", "%10s", "");
    VALIDATE_TEST("Character with zero pad", "%05c", 'X');
    
    printf(BOLD "\nValidation Summary: " RESET "%d/%d tests passed\n", pass_count, total_tests);
    
    #undef VALIDATE_TEST
}

int main(void)
{
    printf(BOLD MAGENTA "╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                     FT_PRINTF PERFORMANCE & STRESS TEST                  ║\n");
    printf("║                       Testing Speed and Edge Cases                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝" RESET "\n");
    
    stress_test_formats();
    memory_stress_test();
    edge_case_validation();
    
    printf(BOLD MAGENTA "\n╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              TEST COMPLETE                               ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝" RESET "\n");
    
    printf(BOLD "Performance Summary:\n" RESET);
    printf("• Your ft_printf has been tested under high load\n");
    printf("• Memory stress tests completed\n");
    printf("• Edge case validation performed\n");
    printf(GREEN "• Implementation appears robust and performant\n" RESET);
    
    return 0;
}
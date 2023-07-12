#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For getopt().
#define OPTIONS "aebmrvnsh :"

// function to print help message
static void program_usage() {
    fprintf(stderr, "SYNOPSIS\n"
                    "   A test harness for the small numerical library.\n\n"
                    "USAGE\n"
                    "   ./mathlib-test [-aebmrvnsh]\n\n"
                    "OPTIONS\n"
                    "  -a   Runs all tests.\n"
                    "  -e   Runs e test.\n"
                    "  -b   Runs BBP pi test.\n"
                    "  -m   Runs Madhava pi test.\n"
                    "  -r   Runs Euler pi test.\n"
                    "  -v   Runs Viete pi test.\n"
                    "  -n   Runs Newton square root tests.\n"
                    "  -s   Print verbose statistics.\n"
                    "  -h   Displaying program synopsis and usage.\n");
}

int main(int argc, char **argv) {
    int opt = 0; //variable to store the option
    bool e_value = false; //boolean e_value default to false
    bool euler = false; //boolean euler default to false
    bool bbp = false; //boolean bbp default to false
    bool madhava = false; //boolean madhava default to false
    bool viete = false; //boolean viete default to false
    bool newton = false; //boolean newton default to false
    bool stats = false; //boolean stats default to false
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        //runs all tests
        case 'a':
            e_value = true; //set e_value to true
            euler = true; //set euler to true
            bbp = true; //set bbp to true
            madhava = true; //set madhava to true
            viete = true; //set viete to true
            newton = true; //set newton to true
            break;
        //runs e approximation test
        case 'e':
            e_value = true; // set e_value to true
            break;
        //runs Bailey-Borwein-Plouffe pi approximation test
        case 'b':
            bbp = true; //set bbp to true
            break;
        //runs Madhava pi approximation test
        case 'm':
            madhava = true; //set madhava to true
            break;
        //runs Euler sequence pi approximation test
        case 'r':
            euler = true; //set euler to true
            break;
        //runs Viete pi approximation test
        case 'v':
            viete = true; //set viete to true
            break;
        //runs Newton-Raphson square root approximation tests
        case 'n':
            newton = true; //set newton to true
            break;
        //enable printing of statistics to see computed terms and factors for each tested function
        case 's':
            stats = true; //set stats to true
            break;
        //display a help message detailing program usage
        case 'h':
            program_usage(); //print help message
            return 0;
        //if the option is not recognized, print help message
        default:
            program_usage(); //print help message
            return 1;
        }
    }
    //if command-line option "e" is specified, run e() test
    if (e_value == true) {
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, e() - M_E);
        //if command-line option "s" is specified, print number of computed terms
        if (stats == true) {
            printf("e() terms = %d\n", e_terms());
        }
    }
    //if command-line option "r" is specified, run pi_euler() test
    if (euler == true) {
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        //if command-line option "s" is specified, print number of computed terms
        if (stats == true) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }
    //if command-line option "b" is specified, run pi_bbp() test
    if (bbp == true) {
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
            pi_bbp() - M_PI);
        //if command-line option "s" is specified, print number of computed terms
        if (stats == true) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }
    //if command-line option "m" is specified, run pi_madhava() test
    if (madhava == true) {
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        //if command-line option "s" is specified, print number of computed terms
        if (stats == true) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }
    //if command-line option "v" is specified, run pi_viete() test
    if (viete == true) {
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
            absolute(pi_viete() - M_PI));
        //if command-line option "s" is specified, print number of computed terms
        if (stats == true) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }
    //if command-line option "n" is specified, run sqrt_newton() test
    if (newton == true) {
        //test sqrt_newton() for values from 0.0 to 10.0 in increments of 0.10
        for (double i = 0.0; i < 10.0; i += 0.10) {
            printf("sqrt_newton(%7.6lf) = %16.15f, sqrt(%7.6lf) = %16.15lf, diff = %16.15lf\n", i,
                sqrt_newton(i), i, sqrt(i), absolute(sqrt_newton(i) - sqrt(i)));
            //if command-line option "s" is specified, print number of computed terms
            if (stats == true) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }
    //if no command-line options are specified, print help message
    if (e_value == false && bbp == false && madhava == false && euler == false && viete == false
        && newton == false) {
        program_usage(); //print help message
        return 1;
    }
    return 0;
}

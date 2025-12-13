#include "Config.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

static void writeConfigFile(const std::string& fileName,
                            const std::string& contents)
{
    std::ofstream out(fileName.c_str());
    if (!out)
    {
        throw std::runtime_error(
            "Unable to create temporary config file: " + fileName);
    }
    out << contents;
}

static bool testDefaultConstructor()
{
    Config c;
    return c.getHitDuration() == 20 &&
           c.getPaintBlobLimit() == 30 &&
           c.getRockLowerBound() == 10 &&
           c.getRockUpperBound() == 20 &&
           c.getFogLowerBound() == 5 &&
           c.getFogUpperBound() == 10 &&
           c.getLongRangeLimit() == 30;
}

static bool testBadFileName()
{
    try
    {
        Config c("this_file_does_not_exist.cfg");
    }
    catch (const std::exception&)
    {
        return true;
    }
    return false;
}

static bool testValidAllParameters()
{
    const std::string fileName = "config_all.cfg";
    writeConfigFile(fileName,
                    "# Example configuration file\n"
                    "HIT_DURATION = 28\n"
                    "PAINTBLOB_LIMIT = 40\n"
                    "ROCK_LOWER_BOUND = 11\n"
                    "ROCK_UPPER_BOUND = 19\n"
                    "FOG_LOWER_BOUND = 3\n"
                    "FOG_UPPER_BOUND = 7\n"
                    "LONG_RANGE_LIMIT = 15\n");

    Config c(fileName);

    return c.getHitDuration() == 28 &&
           c.getPaintBlobLimit() == 40 &&
           c.getRockLowerBound() == 11 &&
           c.getRockUpperBound() == 19 &&
           c.getFogLowerBound() == 3 &&
           c.getFogUpperBound() == 7 &&
           c.getLongRangeLimit() == 15;
}

static bool testValidMissingParameters()
{
    const std::string fileName = "config_missing.cfg";
    writeConfigFile(fileName,
                    "HIT_DURATION = 25\n"
                    "ROCK_LOWER_BOUND = 12\n");

    Config c(fileName);

    return c.getHitDuration() == 25 &&
           c.getPaintBlobLimit() == 30 &&
           c.getRockLowerBound() == 12 &&
           c.getRockUpperBound() == 20 &&
           c.getFogLowerBound() == 5 &&
           c.getFogUpperBound() == 10 &&
           c.getLongRangeLimit() == 30;
}

static bool testInvalidNoEquals()
{
    const std::string fileName = "config_no_equals.cfg";
    writeConfigFile(fileName,
                    "HIT_DURATION 28\n");

    try
    {
        Config c(fileName);
    }
    catch (const std::exception&)
    {
        return true;
    }
    return false;
}

static bool testInvalidNonInteger()
{
    const std::string fileName = "config_non_integer.cfg";
    writeConfigFile(fileName,
                    "PAINTBLOB_LIMIT = notanumber\n");

    try
    {
        Config c(fileName);
    }
    catch (const std::exception&)
    {
        return true;
    }
    return false;
}

static bool testUnknownKeyword()
{
    const std::string fileName = "config_unknown_key.cfg";
    writeConfigFile(fileName,
                    "UNKNOWN_KEY = 10\n");

    try
    {
        Config c(fileName);
    }
    catch (const std::exception&)
    {
        return true;
    }
    return false;
}

static bool testCaseInsensitiveKeyword()
{
    const std::string fileName = "config_case.cfg";
    writeConfigFile(fileName,
                    "hit_duration = 22\n"
                    "PaintBlob_Limit = 35\n");

    Config c(fileName);

    return c.getHitDuration() == 22 &&
           c.getPaintBlobLimit() == 35;
}

static bool testWhitespaceAndBlankLines()
{
    const std::string fileName = "config_whitespace.cfg";
    writeConfigFile(fileName,
                    "   \n"
                    "   # Comment line\n"
                    "HIT_DURATION = 26   \n"
                    "\n");

    Config c(fileName);

    return c.getHitDuration() == 26;
}

static bool testCommentsIgnored()
{
    const std::string fileName = "config_comments.cfg";
    writeConfigFile(fileName,
                    "# This is a comment\n"
                    "# HIT_DURATION = 99\n"
                    "HIT_DURATION = 24\n");

    Config c(fileName);

    return c.getHitDuration() == 24;
}

int main()
{
    int passed = 0;
    int total = 0;

    struct TestCase
    {
        const char* name;
        bool (*func)();
    } tests[] = {
        {"default constructor", testDefaultConstructor},
        {"bad file name", testBadFileName},
        {"valid config file, all parameters", testValidAllParameters},
        {"valid config file, missing parameters", testValidMissingParameters},
        {"invalid config file (no equals)", testInvalidNoEquals},
        {"invalid config file (non-integer)", testInvalidNonInteger},
        {"invalid config file (unknown keyword)", testUnknownKeyword},
        {"case-insensitive keywords", testCaseInsensitiveKeyword},
        {"whitespace and blank lines", testWhitespaceAndBlankLines},
        {"comments ignored", testCommentsIgnored},
    };

    const int numTests = sizeof(tests) / sizeof(tests[0]);

    std::cout << "Config class unit tests\n";

    for (int i = 0; i < numTests; ++i)
    {
        ++total;
        bool ok = false;
        try
        {
            ok = tests[i].func();
        }
        catch (const std::exception& ex)
        {
            std::cout << "Checking " << tests[i].name
                      << ": FAIL (unexpected exception: "
                      << ex.what() << ")\n";
            continue;
        }
        catch (...)
        {
            std::cout << "Checking " << tests[i].name
                      << ": FAIL (unknown exception)\n";
            continue;
        }

        if (ok)
        {
            ++passed;
            std::cout << "Checking " << tests[i].name << ": PASS\n";
        }
        else
        {
            std::cout << "Checking " << tests[i].name << ": FAIL\n";
        }
    }

    std::cout << passed << " of " << total << " tests passed.\n";
    return (passed == total) ? 0 : 1;
}

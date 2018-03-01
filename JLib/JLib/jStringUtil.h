#pragma once
#include "jUtility.h"
#include <string>
#include <vector>

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jStringUtil)

extern const std::vector<size_t> findAll(const std::string& Whole, const std::string& part);

extern const size_t count(const std::string& Whole, const std::string& part);

extern const std::string escape(const std::string& prime);

extern const std::string trim(const std::string& prime);

extern const std::string reverse(const std::string& prime);

extern const std::string toLower(const std::string& prime);

extern const std::string toUpper(const std::string& prime);

extern const std::string head(const std::string& prime, size_t num);

extern const std::string tail(const std::string& prime, size_t num);

extern const std::vector<std::string> split(const std::string& prime, const std::string& sep);

extern const std::string join(const std::vector<std::string> &strVec, const std::string& joiner);

extern const std::string replace(const std::string & prime, const std::string& oldSub, const std::string & newSub);

extern const bool constains(const std::string& Whole, const std::string& part);

extern const bool endsWith(const std::string& Whole, const std::string& part);

extern const bool startsWith(const std::string& Whole, const std::string& part);

extern const std::vector<size_t> KMP_match(const std::string& Whole, const std::string &part);

extern const double calExpressionValue(const std::string& expression);

NAME_SPACE_END
NAME_SPACE_END


////////////// Unit Test //////////////
#include "jTestBase.h"
JTEST_BEGIN(jStringUtilTest)
{
    using namespace jStringUtil;
    std::string s = "Helllo, world.";
    auto &l = split(s, "ll");
    for (auto &str : l)
    {
        std::cout << "(" << str << ")" << ",";
    }
    std::cout << "\b " << std::endl;
    std::cout << tail(s, 5) << std::endl << head(s, 6) << std::endl;
    auto &posVec = KMP_match(s, "ll");
    for (auto & pos : posVec)
    {
        std::cout << pos << " ";
    }
    std::cout << std::endl;
    auto newStr = replace(s, "l", "s");
    std::cout << newStr << std::endl;

    std::string valStr = "(1 + 2^2) *3  - 2 / 3";   //Output : 14.333
    std::cout << calExpressionValue(valStr) << std::endl;
}
JTEST_END
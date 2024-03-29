#pragma once
#include "jUtility.h"
#include <string>
#include <vector>

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jNum)

class jIntString {
public:
	jIntString(const std::string initString, const unsigned char initRadix = 10);
	jIntString(const std::vector<char>& numVec, bool sign, unsigned char radix);
	jIntString(const jIntString& rhs);
	jIntString(jIntString && rhs) noexcept;
	const jIntString& operator=(const jIntString& rhs);
	const jIntString& operator= (jIntString && rhs) noexcept;

	jIntString& changeRadix(const unsigned char toRadix);

	inline const std::vector<char>& numVecRef() const {
		return numVec_;
	}
	inline const bool sign() const {
		return sign_;
	}
	inline const unsigned char radix() const { return radix_; }
	inline const std::string& toString() const {
		return mstring_;
	}

private:
	std::string mstring_;
	std::vector<char> numVec_;
	unsigned char radix_;
	bool sign_;

	void binaryToHex();
	void rebuiltString();
}; 

extern std::ostream& operator << (std::ostream &output, const jIntString &jis);

NAME_SPACE_END
NAME_SPACE_END

////////////// Unit Test //////////////
#include "jTestBase.h"

JTEST_BEGIN(jIntStringTest)
{
    try
    {
        jLib::jNum::jIntString jis("001396348573");
        jis.changeRadix(7);
        std::cout << jis << std::endl;
        jis.changeRadix(10);
        std::cout << jis << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
JTEST_END
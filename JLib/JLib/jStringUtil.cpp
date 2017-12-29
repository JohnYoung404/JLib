#include "jStringUtil.h"
#include "jTestBase.h"

namespace jLib
{

namespace jStringUtil
{

	const std::vector<size_t> findAll(const std::string& Whole, const std::string& part)
	{
		std::vector<size_t> ret;
		std::size_t found = Whole.find(part, 0);
		while (found != std::string::npos)
		{
			ret.push_back(found);
			found = Whole.find(part, found + 1);
		}
		return ret;
	}

	const size_t count(const std::string& Whole, const std::string& part) {
		return findAll(Whole, part).size();
	}

	const std::string escape(const std::string& prime) {
		std::string ret;
		for (auto orig_elem : prime)
		{
			unsigned char elem = (unsigned char)orig_elem;
			if (isdigit(elem) || islower(elem) || isupper(elem))
				ret.push_back(elem);
			else if (elem < 256) {
				ret.push_back('%');
				if (elem < 16)	ret.push_back('0');
				char buffer[4];
				_itoa_s(elem, buffer, 16);
				std::string toAppend = buffer;
				ret.append(toAppend);
			}
		}
		return ret;
	}

	const std::string trim(const std::string& prime) {
		std::string ret;
		auto itr_head = prime.begin();
		auto itr_end = prime.end();
		while ((itr_head != prime.end())) {
			if (!isspace((unsigned char)*itr_head))
				break;
			++itr_head;
		}
		while ((itr_end != prime.begin())) {
			--itr_end;
			if (!isspace((unsigned char)*itr_end))
				break;
		}
		if (itr_head < itr_end)
			ret = std::string(itr_head, ++itr_end);
		return ret;
	}

	const std::string reverse(const std::string& prime)
	{
		return std::string(prime.rbegin(), prime.rend());
	}

	const std::string toLower(const std::string& prime) {
		std::string ret;
		std::for_each(prime.begin(), prime.end(), [&ret](auto chr) {
			ret.push_back(tolower(chr));
		});
		return ret;
	}

	const std::string toUpper(const std::string& prime) {
		std::string ret;
		std::for_each(prime.begin(), prime.end(), [&ret](auto chr) {
			ret.push_back(toupper(chr));
		});
		return ret;
	}

	const std::string head(const std::string& prime, size_t num)
	{
		return (num >= prime.size()) ? prime : std::string(prime.begin(), prime.begin() + num);
	}

	const std::string tail(const std::string& prime, size_t num)
	{
		return (num >= prime.size()) ? prime : reverse(std::string(prime.rbegin(), prime.rbegin() + num));
	}

	const std::vector<std::string> split(const std::string& prime, const std::string& sep) {
		std::vector<std::string> ret;
		std::string sepString;

		if (sep.size() == 0) {
			for (auto chr : prime)
			{
				std::string tmp;
				tmp.insert(tmp.begin(), chr);
				ret.push_back(std::move(tmp));
			}
			return ret;
		}

		auto& sep_pos_vec = findAll(prime, sep);
		jRange<size_t> r;
		for (auto pos : sep_pos_vec)
		{
			r.addRange(pos, pos + sep.size() - 1);
		}

		for (size_t i = 0; i < prime.size(); ++i)
		{
			if (!r.contains(i)) {
				sepString.push_back(prime[i]);
			}
			else {
				if (sepString.size()) {
					ret.push_back(std::move(sepString));
					sepString.clear();
				}
			}
		}
		if (sepString.size()) {
			ret.push_back(std::move(sepString));
			sepString.clear();
		}
		return ret;
	}

	const std::string join(const std::vector<std::string> &strVec, const std::string& joiner) {
		std::string ret;
		for (auto& str : strVec) {
			if (str.size()) {
				ret.append(str);
				ret.append(joiner);
			}
		}
		if (ret.size())
		{
			for (auto i = 0; i < joiner.size(); ++i)
			{
				ret.pop_back();
			}
		}
		return ret;
	}

	const std::string replace(const std::string & prime, const std::string& oldSub, const std::string & newSub)
	{
		std::string ret = prime;
		std::size_t found = ret.find(oldSub, 0);
		while (found != std::string::npos)
		{
			ret.replace(found, oldSub.size(), newSub);
			found = ret.find(oldSub, found + newSub.size());
		}
		return ret;
	}

	const bool constains(const std::string& Whole, const std::string& part) {
		std::size_t found = Whole.find(part, 0);
		return found != std::string::npos;
	}

	const bool endsWith(const std::string& Whole, const std::string& part) {
		auto itrWhole = Whole.rbegin();
		auto itrPart = part.rbegin();
		while (itrPart != part.rend())
		{
			if (itrWhole == Whole.rend())
			{
				return false;
			}
			if (*itrWhole != *itrPart)
			{
				return false;
			}
			++itrWhole, ++itrPart;
		}
		return true;
	}

	const bool startsWith(const std::string& Whole, const std::string& part) {
		auto itrWhole = Whole.begin();
		auto itrPart = part.begin();
		while (itrPart != part.end())
		{
			if (itrWhole == Whole.end())
			{
				return false;
			}
			if (*itrWhole != *itrPart)
			{
				return false;
			}
			++itrWhole, ++itrPart;
		}
		return true;
	}

namespace
{
	const std::vector<size_t> PrefixFunc(const std::string & inputStr)
	{
		size_t k = 0;
		std::vector<size_t> ret;
		ret.resize(inputStr.size());
		ret[0] = 0;
		for (size_t q = 1; q < inputStr.size(); ++q)
		{
			while (k > 0 && inputStr[k] != inputStr[q])
			{
				k = ret[k - 1];
			}
			if (inputStr[k] == inputStr[q])
			{
				k = k + 1;
			}
			ret[q] = k;
		}
		return ret;
	}
}

	const std::vector<size_t> KMP_match(const std::string& Whole, const std::string &part) {
		size_t n = Whole.size();
		size_t m = part.size();
		auto & prefixFunc = PrefixFunc(part);
		size_t q = 0;
		std::vector<size_t> ret;
		for (size_t i = 0; i < n; ++i)
		{
			while (q > 0 && part[q] != Whole[i])
			{
				q = prefixFunc[q - 1];
			}
			if (part[q] == Whole[i])
			{
				q = q + 1;
			}
			if (q == m)
			{
				ret.push_back(i - m + 1);
				q = prefixFunc[q - 1];
			}
		}
		return ret;
	}

}

}
#pragma once

#include <string>
#include <vector>
#include <cctype>
#include "jRange.h"

namespace jLib {

namespace jStringUtil {

	const std::vector<size_t> findAll(const std::string& Whole, const std::string& part) {
		std::vector<size_t> ret;
		std::size_t found = Whole.find(part, 0);
		while (found != std::string::npos)
		{
			ret.push_back(found);
			found = Whole.find(part, found + 1);
		}
		return std::move(ret);
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
		return std::move(ret);
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
		return std::move(ret);
	}

	std::vector<std::string> split(const std::string& prime, const std::string& sep) {
		std::vector<std::string> ret;
		std::string sepString;

		if (sep.size() == 0) {
			for (auto chr : prime)
			{
				std::string tmp;
				tmp.insert(tmp.begin(), chr);
				ret.push_back(std::move(tmp));
			}
			return std::move(ret);
		}

		auto sep_pos_vec = findAll(prime, sep);
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
		return std::move(ret);
	}

	const std::string join(const std::vector<std::string> &strVec, const std::string& joiner) {
		std::string ret;
		for (auto str : strVec) {
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
		return std::move(ret);
	}

	const std::string replace(const std::string & prime, const std::string& oldSub, const std::string & newSub){
		std::string ret = prime;
		std::size_t found = ret.find(oldSub, 0);
		while (found != std::string::npos)
		{
			ret.replace(found, oldSub.size(), newSub);
			found = ret.find(oldSub, found + newSub.size());
		}
		return std::move(ret);
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
}

}
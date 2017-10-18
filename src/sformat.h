//	功能：String Format
//	作者：mmc
//	日期：2017/10/18

#pragma once

#include <tuple>
#include <string>
#include <cstdint>
#include <algorithm>

#if defined(WIN32)
#define snprintf	sprintf_s
#endif

//	uint
inline std::string & ToString(std::string & ret, uint64_t val)
{
	char buf[24] = { 0 };
	auto ptr = &buf[sizeof(buf)-2];
	do {
		*ptr = val % 10;
		*ptr-- += '0';
		val /= 10;
	} while (0 != val);
	ret.append(ptr + 1);
	return ret;
}
inline std::string & ToString(std::string & ret, uint32_t val) { return ToString(ret, (uint64_t)val); }
inline std::string & ToString(std::string & ret, uint16_t val) { return ToString(ret, (uint64_t)val); }
inline std::string & ToString(std::string & ret, uint8_t val) { return ToString(ret, (uint64_t)val); }

//	int
inline std::string & ToString(std::string & ret, int64_t val)
{
	if (val < 0) ret.append(1, '-');
	return ToString(ret, (uint64_t)val);
}
inline std::string & ToString(std::string & ret, int32_t val) { return ToString(ret, (int64_t)val); }
inline std::string & ToString(std::string & ret, int16_t val) { return ToString(ret, (int64_t)val); }
inline std::string & ToString(std::string & ret, int8_t val) { return ToString(ret, (int64_t)val); }

//	double
inline std::string & ToString(std::string & ret, double val)
{
	char buf[24] = { 0 };
	snprintf(buf, sizeof(buf), "%lf", val);
	ret.append(buf);
	return ret;
}
inline std::string & ToString(std::string & ret, float val) { return ToString(ret, (double)val); }
inline std::string & ToString(std::string & ret, const char * val) { ret.append(val); return ret; }
inline std::string & ToString(std::string & ret, const std::string & val) { ret.append(val); return ret; }
inline std::string & ToString(std::string & ret, bool val) { ret.append(val ? "true" : "false"); return ret; }

template <int N>
struct SFormatN {
	static std::string Format(const char * fmt)
	{
		static_assert(false, "");
	}
};

template <>
struct SFormatN<0> {
	template <class ...ARGS>
	static std::string Format(const char * fmt, const std::tuple<ARGS...> &)
	{
		return fmt;
	}
};

template <class ...ARGS>
std::string SFormat(const char * fmt, const ARGS &...args)
{
	const auto tuple = std::make_tuple(args...);
	return SFormatN<sizeof...(args)>::Format(fmt, tuple);
}

#define FMT_N(idx)	case idx: ToString(ret, std::get<idx>(args)); break;

#define FMT_PARSE(N, ...)															\
template <>																			\
struct SFormatN<N> {																\
	template <class... ARGS>														\
	static std::string Format(const char * fmt, const std::tuple<ARGS...> & args)	\
	{	std::string ret;															\
		while (*fmt != '\0') { auto idx = -1;										\
			if (*fmt == '{') { idx = 0; ++fmt;										\
				while (*fmt >= '0' && *fmt <= '9')									\
					{ idx *= 10; idx += (int)(*fmt++ - '0'); }						\
				if (*fmt != '}') idx = -1; else ++fmt;								\
			}																		\
			switch (idx) { __VA_ARGS__ default: ret.append(1, *fmt++); break; }		\
		}																			\
		return ret;																	\
	}																				\
};

FMT_PARSE(1, FMT_N(0))
FMT_PARSE(2, FMT_N(0) FMT_N(1))
FMT_PARSE(3, FMT_N(0) FMT_N(1) FMT_N(2))
FMT_PARSE(4, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3))
FMT_PARSE(5, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4))
FMT_PARSE(6, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5))
FMT_PARSE(7, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6))
FMT_PARSE(8, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7))
FMT_PARSE(9, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8))
FMT_PARSE(10, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9))
FMT_PARSE(11, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10))
FMT_PARSE(12, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10) FMT_N(11))
FMT_PARSE(13, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10) FMT_N(11) FMT_N(12))
FMT_PARSE(14, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10) FMT_N(11) FMT_N(12) FMT_N(13))
FMT_PARSE(15, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10) FMT_N(11) FMT_N(12) FMT_N(13) FMT_N(14))
FMT_PARSE(16, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10) FMT_N(11) FMT_N(12) FMT_N(13) FMT_N(14) FMT_N(15))
FMT_PARSE(17, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10) FMT_N(11) FMT_N(12) FMT_N(13) FMT_N(14) FMT_N(15) FMT_N(16))
FMT_PARSE(18, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10) FMT_N(11) FMT_N(12) FMT_N(13) FMT_N(14) FMT_N(15) FMT_N(16) FMT_N(17))
FMT_PARSE(19, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10) FMT_N(11) FMT_N(12) FMT_N(13) FMT_N(14) FMT_N(15) FMT_N(16) FMT_N(17) FMT_N(18))
FMT_PARSE(20, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10) FMT_N(11) FMT_N(12) FMT_N(13) FMT_N(14) FMT_N(15) FMT_N(16) FMT_N(17) FMT_N(18) FMT_N(19))
FMT_PARSE(21, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10) FMT_N(11) FMT_N(12) FMT_N(13) FMT_N(14) FMT_N(15) FMT_N(16) FMT_N(17) FMT_N(18) FMT_N(19) FMT_N(20))
FMT_PARSE(22, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10) FMT_N(11) FMT_N(12) FMT_N(13) FMT_N(14) FMT_N(15) FMT_N(16) FMT_N(17) FMT_N(18) FMT_N(19) FMT_N(20) FMT_N(21))
FMT_PARSE(23, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10) FMT_N(11) FMT_N(12) FMT_N(13) FMT_N(14) FMT_N(15) FMT_N(16) FMT_N(17) FMT_N(18) FMT_N(19) FMT_N(20) FMT_N(21) FMT_N(22))
FMT_PARSE(24, FMT_N(0) FMT_N(1) FMT_N(2) FMT_N(3) FMT_N(4) FMT_N(5) FMT_N(6) FMT_N(7) FMT_N(8) FMT_N(9) FMT_N(10) FMT_N(11) FMT_N(12) FMT_N(13) FMT_N(14) FMT_N(15) FMT_N(16) FMT_N(17) FMT_N(18) FMT_N(19) FMT_N(20) FMT_N(21) FMT_N(22) FMT_N(23))


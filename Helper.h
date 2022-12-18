#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>

inline std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> result;
	std::stringstream ss (s);
	std::string item;

	while (getline (ss, item, delim)) {
		result.push_back (item);
	}

	return result;
}

static inline void trimLeft(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}

#ifdef __linux__
template<typename T>
inline std::ostream& operator<<(std::ostream& stream, const std::chrono::duration<T> duration) {
    stream << duration.count() << " ticks";
    return stream;
}
#endif

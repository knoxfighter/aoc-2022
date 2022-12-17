#pragma once

#include <string>
#include <utility>
#include <list>
#include <optional>
#include <memory>

class FileEntry {
public:
	enum class Type {
		DIR,
		FILE
	};

	FileEntry(Type pType, std::string  pName, uint64_t pSize) : mType(pType), mName(std::move(pName)), mSize(pSize) {}

	void AddElement(Type pType, const std::string& pName, uint64_t pSize = 0);
	std::shared_ptr<FileEntry> GetElement(const std::string& pName);
	uint64_t CalculateSizes();
	uint64_t GetSmallSizes();
	void GetSmallestDirSize(uint64_t& pCurrentVal, uint64_t pTarget);

	std::strong_ordering operator<=>(const FileEntry& pOther) const = default;
	std::strong_ordering operator<=>(const std::string& pOther) const {
		return mName <=> pOther;
	}
	bool operator==(const std::string& pOther) const {
		return mName == pOther;
	}

private:
	Type mType;
	std::string mName;
	uint64_t mSize;

	std::list<std::shared_ptr<FileEntry>> mElements;
};

#include "FileEntry.h"

#include <algorithm>

void FileEntry::AddElement(FileEntry::Type pType, const std::string& pName, uint64_t pSize) {
	mElements.emplace_back(new FileEntry(pType, pName, pSize));
}

std::shared_ptr<FileEntry> FileEntry::GetElement(const std::string& pName) {
	auto elem = std::ranges::find_if(mElements, [pName](const auto& a) {
		return *a == pName;
	});
	return *elem;
}

uint64_t FileEntry::CalculateSizes() {
	if (mType == Type::DIR) {
		for (const auto &item : mElements) {
			mSize += item->CalculateSizes();
		}
	}

	return mSize;
}

uint64_t FileEntry::GetSmallSizes() {
	uint64_t num = 0;
	if (mType == Type::DIR) {
		for (const auto& item: mElements) {
			num += item->GetSmallSizes();
		}
		if (mSize <= 100000) {
			num += mSize;
		}
	}
	return num;
}

void FileEntry::GetSmallestDirSize(uint64_t& pCurrentVal, uint64_t pTarget) {
	if (mType == Type::DIR) {
		if (mSize >= pTarget && mSize < pCurrentVal) {
			pCurrentVal = mSize;
		}
		for (const auto &item : mElements) {
			item->GetSmallestDirSize(pCurrentVal, pTarget);
		}
	}
}

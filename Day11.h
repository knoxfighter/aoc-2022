#include <utility>
#include <vector>
#include <memory>
#include <string>
#include <optional>

namespace Day11 {

	void Day11();

	enum class Operator {
		MULTIPLICATION = '*',
		ADDITION = '+'
	};

	struct Value {
		virtual uint64_t GetValue(uint64_t pValue) = 0;
	};

	struct LiteralValue : public Value {
		uint64_t GetValue(uint64_t pValue) override {
			return mValue;
		}

		explicit LiteralValue(uint64_t pValue) : mValue(pValue) {}

	private:
		uint64_t mValue = 0;
	};

	struct DirectValue : public Value {
		uint64_t GetValue(uint64_t pValue) override {
			return pValue;
		}
	};

	class Operation {
	public:
		Operation(Operator pOperator, const std::string& pPre, const std::string& pPost);

		uint64_t operator()(const uint64_t& pValue) {
			switch (mOperator) {
				case Operator::MULTIPLICATION:
					return mPreValue->GetValue(pValue) * mPostValue->GetValue(pValue);
				case Operator::ADDITION:
					return mPreValue->GetValue(pValue) + mPostValue->GetValue(pValue);
			}
		}

	private:
		Operator mOperator;
		std::unique_ptr<Value> mPreValue;
		std::unique_ptr<Value> mPostValue;
	};

	class Item {
	public:
		explicit Item(uint64_t pWorryLevel) : WorryLevel(pWorryLevel) {}

		uint64_t WorryLevel = 0;
	};

	class Monkey {
	public:
		void ParseItems(const std::string& pLine);
		void ParseOperation(const std::string& pLine);
		void ParseTest(const std::string& pLine);
		void ParseTarget(const std::string& pLine);

		void Round();
		void CatchItem(const Item& pItem);

		[[nodiscard]] uint64_t GetInspectedCount() const {
			return mInspectedCount;
		}

//	private:
		std::vector<Item> mItems;
		std::optional<Operation> mOperation;
		uint64_t mTestValue = 0;
		uint64_t mTrueTarget = 0;
		uint64_t mFalseTarget = 0;
		uint64_t mInspectedCount = 0;
	};

	static inline std::vector<Monkey> monkeys;
	static inline uint64_t MaxTestValue = 1;
}

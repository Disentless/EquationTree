#include <iostream>
#include <iomanip>
#include <list>

template<class T>
class tree {
private:
	struct leaf {
		T m_val = 0;
		leaf* m_left = 0, *m_right = 0;

		leaf(T v) :m_val(v) {}

		~leaf() {
			if (m_left) delete m_left;
			if (m_right) delete m_right;
		}
	};

	leaf* m_beg = 0;

	bool insert_after(T& v, leaf* source) {
		if (v < source->m_val) {
			if (source->m_left) return insert_after(v, source->m_left);
			source->m_left = new leaf(v);
			return true;
		}
		if (v > source->m_val) {
			if (source->m_right) return insert_after(v, source->m_right);
			source->m_right = new leaf(v);
			return true;
		}
		return false;
	}

public:
	tree() {}

	bool insert(T v) {
		if (!m_beg) {
			m_beg = new leaf(v);
			return true;
		}
		return insert_after(v, m_beg);
	}

	void push_top(T v) {
		if (!m_beg) {
			m_beg = new leaf(v);
			return;
		}
		leaf* temp = new leaf(v);
		temp->m_left = m_beg;
		m_beg = temp;
	}

	~tree() {
		if (m_beg) delete m_beg;
	}
};

//equation without parenthesses
std::list<char>* sub_parse(const char* source, int offset, int len) {
	std::list<char>* res = new std::list<char>();
	std::list<char>::iterator it = res->begin();
	for (int i = offset; i - offset < len; ++i) {
		switch (source[i]) {
		case '+': case'-': {
			auto k = sub_parse(source, offset + i, len - offset - i);
		} break;
		case '*': case '\\': {
			res->push_back(source[i]);
			it = res->end();
			it--;
			it--;
		} break;
		default:
			res->insert(it, source[i]);
			break;
		}
	}
	return res;
}

char* parse(const char* source) {
	char* line = "";
	char buf = 0;
	int size = 0;
	for (int i = 0; source[i] != 0; ++i) {
		switch (source[i]) {
		default: line[size - 1] = source[i]; buf = source[i]; size++; break;
		case '+': case '-': {
			char* ptr = line + 1;
			while (*ptr++ = *line++);
			*ptr = 0;
			line[0] = source[i];
		}
				  break;
		case '*': case '/': {

		}
				  break;
		}
	}
	return line;
}

int main() {
	char* input = "1-2+3-4+5"; // 4 2 5 / - 1 3 * + <> + * 1 3 - 4 / 2 5
	// * 1 3 +4- / 2 5
	// + * 1 3 - 4 / 2 5
	auto res = sub_parse(input, 0, strlen(input));
	std::cin.seekg(0);
	std::cin.ignore();
	return 0;
}
#pragma once

#include "SPL/Utils.hpp"
#include <initializer_list>
#include <type_traits>


namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

template<class T, int capacity = 32>
class SmallVector{
public:
	inline constexpr SmallVector() noexcept;

	inline constexpr SmallVector(const int size) noexcept;

	inline constexpr SmallVector(const std::initializer_list<T> initList) noexcept;

	template<int cap>
	inline constexpr SmallVector(const SmallVector<T, cap> &initList) noexcept;

	template<class Container>
	inline constexpr SmallVector(const Container &initList) noexcept;


	template<int cap>
	inline constexpr SmallVector &operator =(const SmallVector<T, cap> &initList) noexcept;

	template<class Container>
	inline constexpr SmallVector &operator =(const Container &initList) noexcept;

	inline constexpr operator T *();

	
	inline constexpr T &operator [](const int index) noexcept;

	[[nodiscard]] inline constexpr const T &operator [](const int index) const noexcept;

	inline constexpr void push(T &&arg) noexcept;

	inline constexpr void pop(const int count = 1) noexcept;


	[[nodiscard]] inline constexpr T *begin() noexcept;

	[[nodiscard]] inline constexpr T *end() noexcept;

	inline constexpr void resize(const int size) noexcept;

	[[nodiscard]] inline constexpr int size() noexcept;

	[[nodiscard]] inline constexpr int getCapacity() const noexcept;

private:
	T beginPtr[capacity];
	T *endPtr;
};



template<class T>
class LookUp16Map{
public:
	LookUp16Map() = default;
	LookUp16Map(const LookUp16Map &) = default;
	LookUp16Map(LookUp16Map &&) = default;
	LookUp16Map &operator =(const LookUp16Map &) = default;
	LookUp16Map &operator =(LookUp16Map &&) = default;
	~LookUp16Map() = default;

	inline constexpr LookUp16Map(const int maxId, const int size) noexcept;
	
	inline constexpr T &operator [](const int index) noexcept;

	[[nodiscard]] inline constexpr const T &operator [](const int index) const noexcept;

	inline constexpr void push(const T& data, const int index) noexcept;

	inline constexpr void swap(const int index1, const int index2) noexcept;

	std::vector<ushort> keyArray;
	std::vector<T> dataArray;
};



template<class T>
class ForwardList{
public:
	inline ForwardList() noexcept;
	ForwardList(const ForwardList &list) noexcept;
	inline ForwardList(ForwardList &&list) noexcept;
	~ForwardList();

	ForwardList &operator =(const ForwardList &list) noexcept;
	inline ForwardList &operator =(ForwardList &&list) noexcept;

	T &operator [](const int index) noexcept;
	[[nodiscard]] const T &operator [](const int index) const noexcept;
	[[nodiscard]] int size() const;
	void resize(const int size) noexcept;

	inline void pushFront(const T &newData);
	inline void popFront();

private:
	struct Node{
		T data;
		Node *next;
	};
	Node *head;

public:
	class It : public std::iterator<std::forward_iterator_tag ,T>{
	public:
		inline It();
		inline It(const It &iterator) noexcept;
		inline It(const ForwardList &list) noexcept;

		inline It &operator =(const It &iterator) noexcept;
		inline It &operator =(const ForwardList &list) noexcept;
		
		[[nodiscard]] inline It operator +(const int steps) noexcept;
		inline It &operator +=(const int steps) noexcept;
		inline It &operator ++() noexcept;
		inline T &operator *() noexcept;
		T &operator [](const int index) noexcept;

		[[nodiscard]] inline int operator -(const It iter) const noexcept;

		[[nodiscard]] bool operator ==(const It iterator) const;
		[[nodiscard]] bool operator !=(const It iterator) const;

		inline void insertBefore(const T &newData) noexcept;
		inline void removeNext() noexcept;

		Node *ptr;
	};

	[[nodiscard]] inline constexpr It begin() const noexcept;
	[[nodiscard]] inline constexpr It end() const noexcept;
};

template<class T>
class LinkedList{
public:
	inline LinkedList() noexcept;
	LinkedList(const LinkedList &list) noexcept;
	inline LinkedList(LinkedList &&list) noexcept;
	~LinkedList();

	LinkedList &operator =(const LinkedList &list) noexcept;
	inline LinkedList &operator =(LinkedList &&list) noexcept;

	T &operator [](const int index) noexcept;
	[[nodiscard]] const T &operator [](const int index) const noexcept;
	[[nodiscard]] int size() const;
	void resize(const int size) noexcept; 

	inline void pushFront(const T &newData);
	inline void popFront();

private:
	struct Node{
		T data;
		Node *next;
		Node *prev;
	};
	Node *head;

public:
	class It : public std::iterator<std::random_access_iterator_tag, T>{
	public:
		inline It();
		inline It(const It &iterator) noexcept;
		inline It(const LinkedList &list) noexcept;

		inline It &operator =(const It &iterator) noexcept;
		inline It &operator =(const LinkedList &list) noexcept;
		
		[[nodiscard]] inline It operator +(const int steps) const noexcept;
		[[nodiscard]] inline It operator -(const int steps) const noexcept;
		inline It &operator +=(const int steps) noexcept;
		inline It &operator -=(const int steps) noexcept;
		inline It &operator ++() noexcept;
		inline It &operator --() noexcept;
		inline T &operator *() noexcept;
		T &operator [](const int index) noexcept;

		[[nodiscard]] inline int operator -(const It iter) const noexcept;

		[[nodiscard]] bool operator ==(const It iterator) const;
		[[nodiscard]] bool operator !=(const It iterator) const;

		inline void insertBefore(const T &newData) noexcept;
		inline void removeNext() noexcept;
		inline void insertBehind(const T &newData) noexcept;
		inline void removePrev() noexcept;

		Node *ptr;
	};

	[[nodiscard]] inline constexpr It begin() const noexcept;
	[[nodiscard]] inline constexpr It end() const noexcept;
};





#define TPL template<class T, int capacity>
#define CLS SmallVector<T, capacity>

TPL inline constexpr CLS::SmallVector() noexcept : endPtr{beginPtr} {}

TPL inline constexpr CLS::SmallVector(const int size) noexcept : endPtr{beginPtr + size} {}

TPL inline constexpr CLS::SmallVector(const std::initializer_list<T> initList) noexcept : endPtr{beginPtr+initList.size()} {
	std::copy(initList.begin(), initList.end(), beginPtr);
}

TPL template<int cap>
inline constexpr CLS::SmallVector(const SmallVector<T, cap> &initList) noexcept : endPtr{beginPtr+initList.size()} {
	std::copy(initList.begin(), initList.end(), beginPtr);
}

TPL template<class Container>
inline constexpr CLS::SmallVector(const Container &initList) noexcept : endPtr{beginPtr+initList.size()} {
	std::copy(initList.begin(), initList.end(), beginPtr);
}

TPL template<int cap>
inline constexpr CLS &CLS::operator =(const SmallVector<T, cap> &initList) noexcept{
	std::copy(initList.begin(), initList.end(), beginPtr);
	endPtr = beginPtr + initList.getSize();
	return *this;
}

TPL template<class Container>
inline constexpr CLS &CLS::operator =(const Container &initList) noexcept{
	std::copy(initList.begin(), initList.end(), beginPtr);
	endPtr = beginPtr + initList.size();
	return *this;
}

TPL inline constexpr CLS::operator T *(){
	return beginPtr;
}

TPL inline constexpr T &CLS::operator [](const uint32_t index) noexcept{
	return beginPtr[index];
}

TPL constexpr const inline T &CLS::operator [](const uint32_t index) const noexcept{
	return beginPtr[index];
}

TPL inline constexpr void CLS::push(T &&arg) noexcept{
	*endPtr = std::forward<T>(arg);
	++endPtr;
}

TPL inline constexpr void CLS::pop(const uint32_t count) noexcept{
	endPtr -= count;
}

TPL inline constexpr T *CLS::begin() noexcept{
	return beginPtr;
}

TPL inline constexpr T *CLS::end() noexcept{
	return endPtr;
}

TPL inline constexpr void CLS::resize(const uint32_t size) noexcept{
	endPtr = beginPtr + size;
}

TPL inline constexpr int CLS::size() noexcept{
	return endPtr - beginPtr;
}

TPL inline constexpr int CLS::getCapacity() const noexcept{
	return capacity;
}

#undef TPL
#undef CLS



#define TPL template<class T>
#define CLS LookUp16Map<T>

TPL inline constexpr CLS::LookUp16Map(const int maxId, const int size) noexcept {
	keyArray.resize(maxId);
	dataArray.resize(size);
}

TPL inline constexpr T &CLS::operator [](const int index) noexcept {
	return dataArray[keyArray[index]];
}

TPL inline constexpr const T &CLS::operator [](const int index) const noexcept {
	return dataArray[keyArray[index]];
}

TPL inline constexpr void CLS::push(const T& data, const int index) noexcept{
	keyArray[index] = dataArray.size();
	dataArray.push_back(data);
}

TPL inline constexpr void CLS::swap(const int index1, const int index2) noexcept{
	swap(keyArray.data()+index1, keyArray.data()+index2);
}

#undef TPL
#undef CLS



#define TPL template<class T>
#define CLS ForwardList<T>

TPL inline CLS::ForwardList() noexcept : head{nullptr} {}

TPL CLS::ForwardList(const CLS &list) noexcept{
	Node *I = head;
	if (list.head){
		I = (Node *)malloc(sizeof(Node));
		I->data = list.head->data;
		for (Node *J=list.head->next; J!=nullptr; J=J->next){
			I->next = (Node *)malloc(sizeof(Node));
			I = I->next;
			I->data = J->data;
		}
	}
	I = nullptr;
}

TPL inline CLS::ForwardList(CLS &&list) noexcept : head{list.head}{
	~ForwardList();
	list.head = nullptr;
}

TPL CLS::~ForwardList(){
	Node *I = head;
	while (I){
		Node *const toDelete = I;
		I = I->next;
		free(toDelete);
	}
}

TPL CLS &CLS::operator =(const CLS &list) noexcept{
	Node *I = head;
	Node *J = list.head;
	Node *lastNode = head;
	for (; I && J; I=I->next, J=J->next){
		I->data = J->data;
		lastNode = I;
	}

	if (I){
		while (I){
			J = I;
			I = I->next;
			free(J);
		}
	} else{
		if (!head & J){
			head = (Node *)malloc(sizeof(Node));
			head->data = J->data;
			lastNode = head;
			J = J->next;
		}
		for (; J; J=J->next){
			I = (Node *)malloc(sizeof(Node));
			I->data = J->data;
			lastNode->next = I;
			lastNode = I;
		}
	}
	lastNode->next = nullptr;
	return *this;
}

TPL inline CLS &CLS::operator =(CLS &&list) noexcept{
	~ForwardList();
	head = list.head;
	list.head = nullptr;
	return *this;
}

TPL inline void CLS::pushFront(const T &newData){
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = newData;
	newNode->next = head;
	head = newNode;
}

TPL inline void CLS::popFront(){
	Node *toDelete = head;
	head = head->next;
	free(toDelete);
}

TPL T &CLS::operator [](const int index) noexcept{
	Node *I = head;
	for (int i=0; i<index; ++i)
		I = I->next;
	return I->data;
}

TPL T const &CLS::operator [](const int index) const noexcept{
	Node *I = head;
	for (int i=0; i<index; ++i)
		I = I->next;
	return I->data;
}

TPL int CLS::size() const{
	int i = 0;
	for (Node *I=head; I; I=I->next, ++i);
	return i;
}

TPL void CLS::resize(const int size) noexcept{
	int lenght = 0;
	Node *I = head;
	Node *lastNode = head;
	for (; lenght<size && I; ++lenght, I=I->next)
		lastNode = I;

	if (I){
		lastNode->next = nullptr;
		while (I){
			lastNode = I;
			I = I->next;
			free(lastNode);
		}
	} else{
		if (!head && size){
			I = (Node *)malloc(sizeof(Node));
			lastNode = I;
			++lenght;
		}
		for (;lenght<size; ++lenght){
			I = (Node *)malloc(sizeof(Node));
			lastNode->next = I;
			lastNode = I;
		}
		lastNode->next = nullptr;
	}
}

TPL inline constexpr typename CLS::It CLS::begin() const noexcept{
	return CLS::It(*this);
};

TPL inline constexpr typename CLS::It CLS::end() const noexcept{
	CLS::It result;
	result.ptr = nullptr;
	return result;
};


TPL inline CLS::It::It() {}

TPL inline CLS::It::It(const It &iterator) noexcept{
	ptr = iterator.ptr;
}

TPL inline CLS::It::It(const CLS &list) noexcept{
	ptr = list.head;
}

TPL inline typename CLS::It &CLS::It::operator =(const It &iterator) noexcept{
	ptr = iterator.ptr;
	return *this;
}

TPL inline typename CLS::It &CLS::It::operator =(const CLS &list) noexcept{
	ptr = list.head;
	return *this;
}

TPL inline typename CLS::It CLS::It::operator +(const int steps) noexcept{
	CLS::It result;
	result.ptr = this->ptr;
	for (int i=0; i<steps; ++i)
		result.ptr = result.ptr->next;
	return result;
}

TPL inline typename CLS::It &CLS::It::operator +=(const int steps) noexcept{
	for (int i=0; i<steps; ++i)
		this->ptr = this->ptr->next;
	return *this;
}

TPL inline typename CLS::It &CLS::It::operator ++() noexcept{
	ptr = ptr->next;
	return *this;
}

TPL inline T &CLS::It::operator *() noexcept{
	return ptr->data;
}

TPL T &CLS::It::operator [](const int index) noexcept{
	Node *I = ptr;
	for (int i=0; i<index; ++i)
		I = I->next;
	return I->data;
}

TPL inline int CLS::It::operator -(const It iter) const noexcept{
	int result = 0;
	for (Node *I=iter.ptr; I!=this->ptr; I=I->next, ++result);
	return result;
}

TPL inline bool CLS::It::operator ==(const It iterator) const{
	return ptr == iterator.ptr;
}

TPL inline bool CLS::It::operator !=(const It iterator) const{
	return ptr != iterator.ptr;
}

TPL inline void CLS::It::insertBefore(const T &newData) noexcept{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = newData;
	newNode->next = ptr->next;
	ptr->next = newNode;
}

TPL inline void CLS::It::removeNext() noexcept{
	Node *nodePtr = ptr->next;
	ptr->next = nodePtr->next;
	free(nodePtr);
}

#undef TPL
#undef CLS



#define TPL template<class T>
#define CLS LinkedList<T>

TPL inline CLS::LinkedList() noexcept{
	head = nullptr;
}

TPL CLS::LinkedList(const CLS &list) noexcept{
	Node *I = head;
	if (list.head){
		I = (Node *)malloc(sizeof(Node));
		I->prev = nullptr;
		I->data = list.head->data;
		for (Node *J=list.head->next; J; J=J->next){
			I->next = (Node *)malloc(sizeof(Node));
			I->next->prev = I;
			I = I->next;
			I->data = J->data;
		}
	}
	I = nullptr;
}

TPL inline CLS::LinkedList(CLS &&list) noexcept :head{list.head}{
	~LinkedList();
	list.head = nullptr;
}

TPL CLS::~LinkedList(){
	Node *I = head;
	while (I){
		Node *const toDelete = I;
		I = I->next;
		free(toDelete);
	}
}

TPL CLS &CLS::operator =(const CLS &list) noexcept{
	Node *I = head;
	Node *J = list.head;
	Node *lastNode = head;
	for (; I && J; I=I->next, J=J->next){
		I->data = J->data;
		lastNode = I;
	}

	if (I){
		while (I){
			J = I;
			I = I->next;
			free(J);
		}
	} else{
		if (!head && J){
			head = (Node *)malloc(sizeof(Node));
			head->data = J->data;
			head->prev = nullptr;
			lastNode = head;
			J = J->next;
		}
		for (; J; J=J->next){
			I = (Node *)malloc(sizeof(Node));
			I->data = J->data;
			I->prev = lastNode;
			lastNode->next = I;
			lastNode = I;
		}
	}
	lastNode->next = nullptr;
	return *this;
}

TPL inline CLS &CLS::operator =(CLS &&list) noexcept{
	~LinkedList();
	head = list.head;
	list.head = nullptr;
	return *this;
}

TPL inline void CLS::pushFront(const T &newData){
	Node *const newNode = (Node *)malloc(sizeof(Node));
	newNode->data = newData;
	newNode->next = head;
	newNode->prev = nullptr;
	if (head)
		head->prev = newNode;
	head = newNode;
}

TPL inline void CLS::popFront(){
	Node *const toDelete = head;
	head = head->next;
	head->prev = nullptr;
	free(toDelete);
}

TPL T &CLS::operator [](const int index) noexcept{
	Node *I = head;
	for (int i=0; i<index; ++i)
		I = I->next;
	return I->data;
}

TPL T const &CLS::operator [](const int index) const noexcept{
	Node *I = head;
	for (int i=0; i<index; ++i)
		I = I->next;
	return I->data;
}

TPL int CLS::size() const{
	int i = 0;
	for (Node *I=head; I; I=I->next, ++i);
	return i;
}

TPL void CLS::resize(const int size) noexcept{
	int lenght = 0;
	Node *I = head;
	Node *lastNode = head;
	for (; lenght<size && I; ++lenght, I=I->next)
		lastNode = I;

	if (I){
		lastNode->next = nullptr;
		while (I){
			lastNode = I;
			I = I->next;
			free(lastNode);
		}
	} else{
		if (!head && size){
			head = (Node *)malloc(sizeof(Node));
			head->prev = nullptr;
			lastNode = head;
			++lenght;
		}
		for (;lenght<size; ++lenght){
			I = (Node *)malloc(sizeof(Node));
			I->prev = lastNode;
			lastNode->next = I;
			lastNode = I;
		}
		lastNode->next = nullptr;
	}
}

TPL inline constexpr typename CLS::It CLS::begin() const noexcept{
	return CLS::It(*this);
};

TPL inline constexpr typename CLS::It CLS::end() const noexcept{
	CLS::It result;
	result.ptr = nullptr;
	return result;
};


TPL inline CLS::It::It() {}

TPL inline CLS::It::It(const It &iterator) noexcept{
	ptr = iterator.ptr;
}

TPL inline CLS::It::It(const CLS &list) noexcept{
	ptr = list.head;
}

TPL inline typename CLS::It &CLS::It::operator =(const It &iterator) noexcept{
	ptr = iterator.ptr;
	return *this;
}

TPL inline typename CLS::It &CLS::It::operator =(const CLS &list) noexcept{
	ptr = list.head;
	return *this;
}

TPL inline typename CLS::It CLS::It::operator +(const int steps) const noexcept{
	CLS::It result;
	result.ptr = this->ptr;
	for (int i=0; i<steps; ++i)
		result.ptr = result.ptr->next;
	return result;
}

TPL inline typename CLS::It CLS::It::operator -(const int steps) const noexcept{
	CLS::It result;
	result.ptr = this->ptr;
	for (int i=0; i<steps; ++i)
		result.ptr = result.ptr->prev;
	return result;
}

TPL inline typename CLS::It &CLS::It::operator +=(const int steps) noexcept{
	for (int i=0; i<steps; ++i)
		this->ptr = this->ptr->next;
	return *this;
}

TPL inline typename CLS::It &CLS::It::operator -=(const int steps) noexcept{
	for (int i=0; i<steps; ++i)
		this->ptr = this->ptr->prev;
	return *this;
}

TPL inline typename CLS::It &CLS::It::operator ++() noexcept{
	ptr = ptr->next;
	return *this;
}

TPL inline typename CLS::It &CLS::It::operator --() noexcept{
	ptr = ptr->prev;
	return *this;
}

TPL inline T &CLS::It::operator *() noexcept{
	return ptr->data;
}

TPL T &CLS::It::operator [](const int index) noexcept{
	Node *I = ptr;
	if (index >= 0){
		for (int i=0; i<index; ++i)
			I = I->next;
	} else{
		for (int i=-index; i>=0; --i)
			I = I->prev;
	}
	return I->data;
}

TPL inline int CLS::It::operator -(const It iter) const noexcept{
	int result = 0;
	for (Node *I=iter.ptr; I!=this->ptr; I=I->next, ++result);
	return result;
}

TPL inline bool CLS::It::operator ==(const It iterator) const{
	return ptr == iterator.ptr;
}

TPL inline bool CLS::It::operator !=(const It iterator) const{
	return ptr != iterator.ptr;
}

TPL inline void CLS::It::insertBefore(const T &newData) noexcept{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = newData;
	newNode->next = ptr->next;
	newNode->prev = ptr;
	ptr->next = newNode;
}

TPL inline void CLS::It::removeNext() noexcept{
	Node *nodePtr = ptr->next;
	ptr->next = nodePtr->next;
	nodePtr->next->prev = ptr;
	free(nodePtr);
}

TPL inline void CLS::It::insertBehind(const T &newData) noexcept{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = newData;
	newNode->next = ptr;
	newNode->prev = ptr->prev;
	ptr->prev = newNode;
}

TPL inline void CLS::It::removePrev() noexcept{
	Node *nodePtr = ptr->prev;
	ptr->prev = nodePtr->prev;
	nodePtr->prev->next = ptr;
	free(nodePtr);
}

#undef TPL
#undef CLS

}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////
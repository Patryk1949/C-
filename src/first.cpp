#include "SPL/Utils.hpp"
#include <exception>

class Data{
public:
	inline Data() noexcept;
	inline Data(const Data &x) noexcept;
	inline Data(Data &&x) noexcept;

	inline Data &operator =(const Data &x) noexcept;
	inline Data &operator =(Data &&x) noexcept;

	inline ~Data();

	template<bool print=false>
	Data *operator &();

	void randInit(int amount);
	inline void setValue(const int x);
	inline int getValue() const;

private:
	int value;
	char *string;

	friend FILE *operator <<(FILE *, const Data &);
};

Data foo(){
	Data x;
	x.randInit(12);
	return x;
}




struct Base{
	inline constexpr Base() noexcept : data{} {
		printf("Base constructor!\n");
	}
	inline constexpr Base(const int number) noexcept : data{} {
		data = number << 1;
		printf("Base contructor with argument\n");
	}


	int data;
};

struct Derived : public Base{
	inline constexpr Derived() noexcept : number{21.37f} {
		printf("Derived Constructor\n");
	}

	Derived &func1(){
		printf("func1 was called!\n");
		return *this;
	}
	Derived &func2(){
		printf("func2 was called!\n");
		return *this;
	}
	Derived &func3(){
		printf("func3 was called!\n");
		return *this;
	}


	float number;
};



int main(){
	// {
	// Base A{};
	// Derived D{};
	// Base B{};
	// B = A;
	// }

	// Derived der;
	
	// der.func1().func2().func3().func1();

	
	int a;
	scanf("%d", &a);

	std::initializer_list<int> A{a, a+2, a+3, a+4};

	for (auto &I : A)
		printf("%d\n", I);

	return 0; 
}






inline Data::Data() noexcept : value{0}, string{nullptr} {}

inline Data::Data(const Data &x) noexcept : value{x.value} {
	string = (char *)malloc((strlen(x.string)+1)*sizeof(char));
	strcpy(string, x.string);
}

inline Data::Data(Data &&x) noexcept : value{x.value}, string{x.string} {
	x.string = nullptr;
}

inline Data &Data::operator =(const Data &x) noexcept{
	if (!string){
		string = (char *)malloc((strlen(x.string)+1)*sizeof(char));
	} else if (strlen(string) < strlen(x.string)){
		free(string);
		string = (char *)malloc((strlen(x.string)+1)*sizeof(char));
	}
	strcpy(string, x.string);
	value = x.value;
	return *this;
}

inline Data &Data::operator =(Data &&x) noexcept{
	value = x.value;
	string = x.string;
	x.string = nullptr;
	return *this;
}

inline Data::~Data(){
	static int times = 1;
	printf("Destructor Called %d time.\n", times++);
	if (string)
		free(string);
}

template<bool print>
Data *Data::operator &(){
	if (print)
		printf("\n\n{print was called!}\n\n");
	else
		printf("\n\n{print wasn't called!}\n\n");
	return this;
}

void Data::randInit(int amount){
	if (!string){
		string = (char *)malloc((amount+1)*sizeof(char));
	} else if (strlen(string) < amount){
		free(string);
		string = (char *)malloc((amount+1)*sizeof(char));
	}
	srand(clock());
	for (char *I=string+amount-1; I>=string; --I)
		*I = 'a' + rand()%('z'-'a'+1);
}

inline void Data::setValue(const int x){
	value = x;
}
inline int Data::getValue() const{
	return value;
}

inline FILE *operator <<(FILE *output, const Data &x){
	fprintf(output, "string: %s\nvalue: %d\n", x.string, x.value);
	return output;
}
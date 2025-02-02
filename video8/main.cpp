template<typename T>
T  function(T arg){
	//implementation
	return arg;	
}

auto also_fun(auto arg) {
	return arg;
}

template<typename T>
concept Incrementable = requires(T x){ x++; ++x; };

//using the concept:
template<Incrementable I>
I foo(I t) {
	return t;
}

//or like this:
auto foo_foo(Incrementable auto t) {
	return t;
}

int main() {
	int a = function<int>(5);
	int b = also_fun(6);
	int c = foo<int>(55);
	int d = foo_foo<int>(66);

	// mark a and b as unused (ignore the warning)
	(void) a;
	(void) b;
	(void) c;
	(void) d;
}
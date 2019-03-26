#ifndef HTTP__PROPERTY__
#define HTTP__PROPERTY__

template <typename T>
class Property
{
public:
	Property(T (*getter)(), void (*setter)(T)) : getter{getter}, setter{setter} {};
	Property(T (*getter)()) : getter{getter} {};
	operator T() { return getter(); }
	T operator() () { return getter(); }
	void operator= (const T &val) { setter(val); }

protected:
	T (*getter)();
	void (*setter)(T);
};

#endif
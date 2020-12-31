#ifndef SOURCE_H
#define SOURCE_H

#define SOURCE_TYPE_ALL 0
#define SOURCE_TYPE_ENTITY 1
#define SOURCE_TYPE_KEYBOARD 2

class Source
{
private:
	unsigned short type;
public:
	Source(unsigned short t) {
		type = t;
	}
	unsigned short GetType() {
		return type;
	}
};

#endif
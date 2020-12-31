#if !defined( CIMAGEAREABUFFERPOOL_H )
#define CIMAGEAREABUFFERPOOL_H

#pragma warning(disable : 4786)

#include <string>
#include "utils\CBufferPool.h"

#define EXTENSION ".png"

struct ImageAreaData {
	unsigned char *imgareapx;
	float *zimgareapx;
};

class CImageAreaBufferPool : public CBufferPool
{
private:
	CImageAreaBufferPool();
	~CImageAreaBufferPool();
	bool	InitBuffers(BufferData *);
	bool	Load(BufferData *, const char *);
	bool	DeleteBuffers(unsigned int, BufferData *);
public:
	static	CImageAreaBufferPool *getInstance();
	static void	Close();

private:
	static CImageAreaBufferPool	*pool;
public:
};

#endif	// #if !defined( CIMAGEAREABUFFERPOOL_H )
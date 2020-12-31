#if !defined( CTEXTUREBUFFERPOOL_H )
#define CTEXTUREBUFFERPOOL_H

#include "utils\CBufferPool.h"

class CTextureBufferPool : public CBufferPool
{
private:
	static CTextureBufferPool *pool;
public:

private:
	CTextureBufferPool();
	~CTextureBufferPool();
	bool	InitBuffers(BufferData *);
	bool	Load(BufferData*, const char *);
	bool	DeleteBuffers(unsigned int, BufferData *);
public:
	static	CTextureBufferPool *getInstance();
	static void	Close();
};

#endif
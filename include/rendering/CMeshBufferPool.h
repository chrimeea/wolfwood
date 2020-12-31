#if !defined( CMESHBUFFERPOOL )
#define CMESHBUFFERPOOL

#include "utils\CBufferPool.h"

class CMeshBufferPool : public CBufferPool
{
private:
	static CMeshBufferPool *pool;
public:

private:
	CMeshBufferPool();
	~CMeshBufferPool();
	bool	InitBuffers(BufferData *);
	bool	Load(BufferData *, const char *);
	bool	DeleteBuffers(unsigned, BufferData *);
public:
	static	CMeshBufferPool *getInstance();
	static void	Close();
};

#endif

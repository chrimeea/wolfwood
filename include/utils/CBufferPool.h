#if !defined( CBUFFERPOOL_H )
#define CBUFFERPOOL_H

#pragma warning(disable : 4786)

#include "utils\LinkedList.h"
#include <map>
#include <string>
#include "utils\Config.h"

#define CBPOOL_MAX_FILE_NAME 25

struct BufferData {
	unsigned	bufferId;
	void		*data;		
};

struct BData {
	BufferData	buffData;
	unsigned	fileId;
	char		filename[CBPOOL_MAX_FILE_NAME];
	unsigned	usages;
};

typedef LinkedList<BData> BDataList;

class CBufferPool
{
private:
	BDataList		*buffers_on;
	BDataList		*buffers_off;
	unsigned		total;
protected:
	unsigned		max_buffers, min_buffers;
	FileIdMap		*mappings;

private:
	static BData		*findFileId(BDataList *, unsigned int);
	static BData		*findFileName(BDataList *, const char *);
	void				delBuffers(BDataList *);
protected:
	CBufferPool();
	virtual ~CBufferPool();
	virtual bool InitBuffers(BufferData *) { return true; };
	virtual bool Load(BufferData *, const char *) { return true; };
	virtual bool DeleteBuffers(unsigned int, BufferData *) { return true; };
	void freeAll();
public:
	BufferData		*getBuffer(unsigned int);
	BufferData		*getBuffer(const char *);
	void			closeBuffer(unsigned int);
	void			closeBuffer(const char *);
	void			freeMemory();
};

#endif
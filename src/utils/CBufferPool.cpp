#include "utils\CBufferPool.h"
#include <fstream>
#include "utils\Logger.h"

void CBufferPool::freeMemory()
{
	delBuffers(buffers_off);
}

void CBufferPool::delBuffers(BDataList *list)
{
	if(list->getCount() != 0)
	{
		BufferData *bufs = (BufferData *) malloc(list->getCount() * sizeof(BufferData));
		unsigned int i = 0;
		list->head();
		while(!list->isAtEnd())
		{
			BData *buff = list->getData();
			bufs[i++] = buff->buffData;
			list->delCurrentNode();
			delete buff;
			total--;
		}
		if(bufs != NULL)
		{
			DeleteBuffers(i, bufs);
			free(bufs);
		}
	}
}

CBufferPool::CBufferPool()
{
	total = 0;
	buffers_on = new BDataList();
	buffers_off = new BDataList();
	mappings = new FileIdMap();
}

CBufferPool::~CBufferPool()
{
}

void CBufferPool::freeAll()
{
	delBuffers(buffers_on);
	delete buffers_on;
	delBuffers(buffers_off);
	delete buffers_off;
	delete mappings;
}

BData *CBufferPool::findFileId(BDataList *list, unsigned int id)
{
	if(!list->isEmpty())
	{
		list->head();
		while(!list->isAtEnd())
		{
			BData *buff = list->getData();
			if(buff->fileId == id) return buff;
			list->next();
		}
	}
	return NULL;
}

BData *CBufferPool::findFileName(BDataList *list, const char *name)
{
		if(!list->isEmpty())
		{
			list->head();
			while(!list->isAtEnd())
			{
				BData *buff = list->getData();
				if(strcmp(buff->filename, name) == 0) return buff;
				list->next();
			}
		}
		return NULL;
}

BufferData* CBufferPool::getBuffer(unsigned int fileId)
{

	//***********************************************************************
	//
	//TODO : daca fileId e -1, cauta in mappings si update-eaza corespunzator
	//
	//***********************************************************************

	BData *buff = NULL;
	buff = findFileId(buffers_on, fileId);
	if (buff != NULL)
	{
		buff->usages++;
		return &(buff->buffData);
	}
	buff = findFileId(buffers_off, fileId);
	if (buff != NULL)
	{
		buff->usages++;
		buffers_off->delCurrentNode();
		buffers_on->addNode(buff);
		return &(buff->buffData);
	}
	if (total < max_buffers || !buffers_off->isEmpty())
	{
		BData *buff;
		buffers_off->head();
		if (total >= min_buffers && !buffers_off->isEmpty())
		{
			total--;
			buff = buffers_off->getData();
			buffers_off->delCurrentNode();
		} else {
			buff = new BData();
			if(InitBuffers(&(buff->buffData)) == false) return NULL;
		}
		buff->fileId = fileId;
		buff->usages = 1;
		strcpy(buff->filename, Config::FindMappingById(mappings, fileId).c_str());
		if(Load(&(buff->buffData), buff->filename) == false) return NULL;
		total++;
		buffers_on->addNode(buff);
		return &(buff->buffData);
	} else {
		//eroare
		//numarul maxim de bufere atins
	}

	return NULL;
}

BufferData *CBufferPool::getBuffer(const char *name)
{
	BData *buff = NULL;
	buff = findFileName(buffers_on, name);
	if (buff != NULL)
	{
		buff->usages++;
		return &(buff->buffData);
	}
	buff = findFileName(buffers_off, name);
	if (buff != NULL)
	{
		buff->usages++;
		buffers_off->delCurrentNode();
		buffers_on->addNode(buff);
		return &(buff->buffData);
	}
	if (total < max_buffers || !buffers_off->isEmpty())
	{
		BData *buff;
		buffers_off->head();
		if (total >= min_buffers && !buffers_off->isEmpty())
		{
			total--;
			buff = buffers_off->getData();
			buffers_off->delCurrentNode();
		} else {
			buff = new BData;
			if(InitBuffers(&(buff->buffData)) == false) return NULL;
		}
		buff->fileId = -1;
		buff->usages = 1;
		strcpy(buff->filename, name);
		if(Load(&(buff->buffData), name) == false) return NULL;
		total++;
		buffers_on->addNode(buff);
		return &(buff->buffData);
	} else {
		//eroare
		//numarul maxim de bufere atins
	}

	return NULL;
}

void CBufferPool::closeBuffer(unsigned int fileId)
{
	BData *buff = NULL;
	buff = findFileId(buffers_on, fileId);
	if(buff != NULL)
	{
		buff->usages--;
		if(buff->usages == 0)
		{
			buffers_on->delCurrentNode();
			buffers_off->addNode(buff);
			if(total > min_buffers)
			{
				total--;
				buffers_off->head();
				buff = buffers_off->getData();
				buffers_off->delCurrentNode();
				DeleteBuffers(1, &(buff->buffData));
			}
		}
	} else {
		//eroare
		//invalid fileId
	}
}

void CBufferPool::closeBuffer(const char *name)
{
	BData *buff = NULL;
	buff = findFileName(buffers_on, name);
	if(buff != NULL)
	{
		buff->usages--;
		if(buff->usages == 0)
		{
			buffers_on->delCurrentNode();
			buffers_off->addNode(buff);
			if(total > min_buffers)
			{
				total--;
				buffers_off->head();
				buff = buffers_off->getData();
				buffers_off->delCurrentNode();
				DeleteBuffers(1, &(buff->buffData));
			}
		}
	} else {
		//eroare
		//invalid fileId
	}
}
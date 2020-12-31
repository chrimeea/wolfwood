#if !defined( FONTSET_H )
#define FONTSET_H

#define LET_WIDTH 8
#define LET_HEIGHT 13
#define LET_COUNT 256

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

class FontSet
{
private:
	GLuint fontOffset;
	GLubyte letters[LET_COUNT][LET_HEIGHT];
	void LoadLetters(const char *);
	void MakeRasterFont(void);
public:
    FontSet();
    ~FontSet();
	void DrawLetter(const char *);
};

#endif
#pragma warning(disable : 4786)

#include <fstream>
#include "rendering\FontSet.h"
#include "utils\Config.h"

FontSet::FontSet() {
	char *f = Config::GetValue("config/fontset/file");
	LoadLetters(f);
	MakeRasterFont();
}

FontSet::~FontSet() {
}

void FontSet::MakeRasterFont(void)
{
   GLuint i;
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   fontOffset = glGenLists(LET_COUNT);
   for (i = 0; i < LET_COUNT; i++) {
      glNewList(fontOffset + i, GL_COMPILE);
      glBitmap(LET_WIDTH, LET_HEIGHT, 0.0, 2.0, 10.0, 0.0, letters[i]);
      glEndList();
   }
}

void FontSet::LoadLetters(const char *f) {
	unsigned int c;
	std::ifstream ifs(f);
	for (int i = 0; i < LET_COUNT; i++) {
		for (int j = 0; j < LET_HEIGHT; j++) {
			ifs >> c;
			letters[i][j] = c;
		}
	}
}

void FontSet::DrawLetter(const char *s) {
	glPushAttrib(GL_LIST_BIT);
	glListBase(fontOffset);
	glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *) s);
	glPopAttrib();
}
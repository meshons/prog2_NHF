#include "f10.h"
#include <iostream>

F10::F10() {
  line = NULL;
  len = 0;
}

F10::F10(const F10 &f) {
  line = new char[f.len + 1];
  len = f.len;
  int i;
  for (i = 0; i < f.len; i++)
    line[i] = f.line[i];
  line[i] = 0;
}

F10 &F10::operator=(const F10 &f) {

  if (&f != this) {
    if (this->line != NULL)
      delete[] this->line;
    this->line = new char[f.len + 1];
    this->len = f.len;
    int i;
    for (i = 0; i < f.len; i++)
      this->line[i] = f.line[i];
    this->line[i] = 0;
  }
  return *this;
}

F10::~F10() {
  if (line != NULL)
    delete[] line;
  line = NULL;
}

const char *F10::ident() const {
  return "Stork Gábor,1MI,IMSC3,L3p <storkgaborka98@gmail.com> NO047V";
}

static bool strcmp_spec(const char *s1, const char *s2) {
  int len;
  for (len = 0; s2[len]; len++)
    ;
  for (int i = 0; i < len; i++)
    if (s1[i] != s2[i])
      return false;
  return true;
}

bool F10::match(const char *line) {
  int le;
  for (le = 0; line[le]; le++)
    ;
  bool gotcha = false;
  for (int i = 0; i < le; i++) {
    if (i + 5 < le) // alakra
      if (strcmp_spec(line + i, "alakra"))
        gotcha = true;
    if (i + 11 < le) // alakra
      if (strcmp_spec(line + i, "definialnunk"))
        gotcha = true;
    if (i + 9 < le) // alakra
      if (strcmp_spec(line + i, "sebesseget"))
        gotcha = true;
  }

  if (gotcha) {
    if (this->line != NULL)
      delete[] this->line;
    this->line = new char[le + 1];
    int i;
    for (i = 0; i < le; i++)
      this->line[i] = line[i];
    this->len = le;
    this->line[i] = 0;
    return true;
  }
  return false;
}

const char *F10::getLine() const { return line != NULL ? line : NULL; }
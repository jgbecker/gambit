//
// FILE: gstream.cc -- Implementation of I/O streaming functions
//
// $Id$
//

#ifdef __GNUG__
#pragma implementation "gstream.h"
#endif   // __GNUG__

#include <assert.h>
#include "gstream.h"

//--------------------------------------------------------------------------
//                         gInput member functions
//--------------------------------------------------------------------------

gInput::gInput(void)   { }

gInput::~gInput()   { }


//--------------------------------------------------------------------------
//                       gFileInput member functions
//--------------------------------------------------------------------------

#include "gtext.h"

gFileInput::OpenFailed::OpenFailed(int line, char *file)
  :gException(line, file)
{ }

gText gFileInput::OpenFailed::Description(void) const
{
  return "Open failed in gFileInput";
}

gFileInput::ReadFailed::ReadFailed(int line, char *file)
  :gException(line, file)
{ }

gText gFileInput::ReadFailed::Description(void) const
{
  return "Read failed in gFileInput";
}

gFileInput::gFileInput(const char *in) : f(fopen(in, "r"))
{
  if (!f)  throw OpenFailed(__LINE__, __FILE__);
}

gFileInput::gFileInput(FILE *in) : f(in)
{
  if (!f)  throw OpenFailed(__LINE__, __FILE__);
}

gFileInput::~gFileInput()
{
  if (f)   fclose(f);
}

gInput &gFileInput::operator>>(int &x)
{
  if (fscanf(f, "%d", &x) != 1)   throw ReadFailed(__LINE__, __FILE__);
  return *this;
}

gInput &gFileInput::operator>>(unsigned int &x)
{
  if (fscanf(f, "%d", &x) != 1)   throw ReadFailed(__LINE__, __FILE__);
  return *this;
}

gInput &gFileInput::operator>>(long &x)
{
  if (fscanf(f, "%ld", &x) != 1)   throw ReadFailed(__LINE__, __FILE__);
  return *this;
}

gInput &gFileInput::operator>>(char &x)
{
  x = fgetc(f);
  return *this;
}

gInput &gFileInput::operator>>(double &x)
{
  if (fscanf(f, "%lf", &x) != 1)   throw ReadFailed(__LINE__, __FILE__);
  return *this;
}

gInput &gFileInput::operator>>(float &x)
{
  if (fscanf(f, "%f", &x) != 1)   throw ReadFailed(__LINE__, __FILE__);
  return *this;
}

gInput &gFileInput::operator>>(char *x)
{
  if (fscanf(f, "%s", x) != 1)   throw ReadFailed(__LINE__, __FILE__);
  return *this;
}

int gFileInput::get(char &c)
{
  c = fgetc(f);
  return (!feof(f));
}

void gFileInput::unget(char c)
{
  ::ungetc(c, f);
}

bool gFileInput::eof(void) const
{
  return feof(f);
}

void gFileInput::seekp(long pos) const
{
  fseek(f, pos, 0);
}

long gFileInput::getpos(void) const
{
  return ftell(f);
}

void gFileInput::setpos(long x) const
{
  fseek(f, x, 0);
}

//--------------------------------------------------------------------------
//                         gNullInput member functions
//--------------------------------------------------------------------------

gNullInput::gNullInput(void)    { }

gNullInput::~gNullInput()    { }

gInput &gNullInput::operator>>(int &x)
{
  x = 0;
  return *this;
}

gInput &gNullInput::operator>>(unsigned int &x)
{
  x = 0;
  return *this;
}

gInput &gNullInput::operator>>(long &x)
{
  x = 0L;
  return *this;
}

gInput &gNullInput::operator>>(char &x)
{
  x = '\0';
  return *this;
}

gInput &gNullInput::operator>>(double &x)
{
  x = 0.0;
  return *this;
}

gInput &gNullInput::operator>>(float &x)
{
  x = 0.0;
  return *this;
}

gInput &gNullInput::operator>>(char *x)
{
  if (x)   *x = '\0';
  return *this;
}

int gNullInput::get(char &)   { return 0; }

void gNullInput::unget(char)  { }

bool gNullInput::eof(void) const   { return true; }

void gNullInput::seekp(long) const   { }

long gNullInput::getpos(void) const { return 0; }

void gNullInput::setpos(long) const { }


//--------------------------------------------------------------------------
//                          gOutput member functions
//--------------------------------------------------------------------------

gOutput::gOutput(void)   { }

gOutput::~gOutput()   { }

//--------------------------------------------------------------------------
//                         gFileOutput member functions
//--------------------------------------------------------------------------

gFileOutput::OpenFailed::OpenFailed(int line, char *file)
  :gException(line, file)
{ }

gText gFileOutput::OpenFailed::Description(void) const
{
  return "Open failed in gFileOutput";
}

gFileOutput::WriteFailed::WriteFailed(int line, char *file)
  :gException(line, file)
{ }

gText gFileOutput::WriteFailed::Description(void) const
{
  return "Write failed in gFileOutput";
}

gFileOutput::gFileOutput(const char *out, bool append /* = false */)
  : f(fopen(out, (append) ? "a" : "w")), Width(0), Prec(6), Represent('f')
{
  if (!f)   throw OpenFailed(__LINE__, __FILE__);
}

gFileOutput::gFileOutput(FILE *out)
  : f(out), Width(0), Prec(6), Represent('f')
{
  if (!f)   throw OpenFailed(__LINE__, __FILE__);
}

gFileOutput::~gFileOutput()
{
  if (f)   fclose(f);
}

int gFileOutput::GetWidth(void) 
{
  return Width;
}

gOutput &gFileOutput::SetWidth(int w) 
{
  Width = w;
  return *this;
}

int gFileOutput::GetPrec(void) 
{
  return Prec;
}

gOutput &gFileOutput::SetPrec(int p) 
{
  Prec = p;
  return *this;
}

gOutput &gFileOutput::SetExpMode(void) 
{
  Represent = 'e';
  return *this;
}

gOutput &gFileOutput::SetFloatMode(void) 
{
  Represent = 'f';
  return *this;
}

char gFileOutput::GetRepMode(void)
{
  return Represent;
}

gOutput &gFileOutput::operator<<(int x)
{
  if (fprintf(f, "%*d", Width, x) < 0)   throw WriteFailed(__LINE__, __FILE__);
  return *this;
}

gOutput &gFileOutput::operator<<(unsigned int x)
{
  if (fprintf(f, "%*d", Width, x) < 0)   throw WriteFailed(__LINE__, __FILE__);
  return *this;
}

gOutput &gFileOutput::operator<<(bool x)
{
  if (fprintf(f, "%c", (x) ? 'T' : 'F') < 0)   throw WriteFailed(__LINE__, __FILE__);
  return *this;
}

gOutput &gFileOutput::operator<<(long x)
{
  if (fprintf(f, "%*ld", Width, x) < 0)   throw WriteFailed(__LINE__, __FILE__);
  return *this;
}

gOutput &gFileOutput::operator<<(char x)
{
  if (fprintf(f, "%c", x) < 0)   throw WriteFailed(__LINE__, __FILE__);
  return *this;
}

gOutput &gFileOutput::operator<<(double x)
{
  if (Represent == 'f')   {
    if (fprintf(f, "%*.*f", Width, Prec, x) < 0)   throw WriteFailed(__LINE__, __FILE__);
  }
  else   {   // Represent == 'e'
    if (fprintf(f, "%*.*e", Width, Prec, x) < 0)   throw WriteFailed(__LINE__, __FILE__);
  }
  return *this;
}

gOutput &gFileOutput::operator<<(float x)
{
  if (Represent == 'f')   {
    if (fprintf(f, "%*.*f", Width, Prec, x) < 0)   throw WriteFailed(__LINE__, __FILE__);
  }
  else   {   // Represent == 'e'
    if (fprintf(f, "%*.*e", Width, Prec, x) < 0)   throw WriteFailed(__LINE__, __FILE__);
  }
  return *this;
}

gOutput &gFileOutput::operator<<(const char *x)
{
  if (fprintf(f, "%s", x) < 0)   throw WriteFailed(__LINE__, __FILE__);
  return *this;
}

gOutput &gFileOutput::operator<<(const void *x)
{
  if (fprintf(f, "%p", x) < 0)   throw WriteFailed(__LINE__, __FILE__);
  return *this;
}


//--------------------------------------------------------------------------
//                         gNullOutput member functions
//--------------------------------------------------------------------------

gNullOutput::gNullOutput(void)   { }

gNullOutput::~gNullOutput()   { }

int gNullOutput::GetWidth(void) { return true; }

gOutput &gNullOutput::SetWidth(int) { return *this; }

int gNullOutput::GetPrec(void) { return true; }

gOutput &gNullOutput::SetPrec(int) { return *this; }

gOutput &gNullOutput::SetExpMode(void) { return *this; }

gOutput &gNullOutput::SetFloatMode(void) { return *this; }

char gNullOutput::GetRepMode(void) { return true; }

gOutput &gNullOutput::operator<<(int)    { return *this; }

gOutput &gNullOutput::operator<<(unsigned int)   { return *this; }

gOutput &gNullOutput::operator<<(bool)    { return *this; }

gOutput &gNullOutput::operator<<(long)   { return *this; }

gOutput &gNullOutput::operator<<(char)   { return *this; }

gOutput &gNullOutput::operator<<(double)   { return *this; }

gOutput &gNullOutput::operator<<(float)    { return *this; }

gOutput &gNullOutput::operator<<(const char *)  { return *this; }

gOutput &gNullOutput::operator<<(const void *)  { return *this; }


gNullInput _gzero;
gInput &gzero = _gzero;

gNullOutput _gnull;
gOutput &gnull = _gnull;



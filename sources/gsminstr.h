//
// FILE: gsminstr.h -- definition of Instruction classes for GSM's
//                     instruction queue subsystem
//                     companion to GSM
//
// $Id$
//



#ifndef GSMINSTR_H
#define GSMINSTR_H


#include "gstring.h"
#include "gmisc.h"

//-------------------------------------------------------------------
//                      Opcodes
//-------------------------------------------------------------------

typedef enum
{
  iUNDEFINED,

  iNOP,

  iQUIT, iIF_GOTO, iGOTO, iCLEAR,

  iPUSH_BOOL, iPUSH_FLOAT, iPUSH_RATIONAL, iPUSH_INTEGER, iPUSH_TEXT,
  iPUSHINPUT, iPUSHOUTPUT, iPUSH_PREC,
  iPUSHLIST, iPUSHREF,
  iASSIGN, iUNASSIGN,

  iINIT_CALL_FUNCTION, iBIND, iBINDREF, iBINDVAL, iCALL_FUNCTION,

  iPOP, iDUMP, iFLUSH,
  iHELP
} Opcode;


//--------------------------------------------------------------------
//                       NewInstr class
//--------------------------------------------------------------------
//   This is the new general purpose instruction class.
//   The instructions are decoded and run by GSM::Execute().
//   GSM::Execute() is located in gsm.h,cc
//

class NewInstr
{
public:
  Opcode Code;
  union 
  {
    bool      BoolVal;
    long      IntVal;
    double    FloatVal;
    gInput*   InputVal;
    gOutput*  OutputVal;
    Precision PrecVal;
  };
  gString TextVal;
  long LineNumber;
  
  NewInstr(Opcode code, const bool& v = false)
    : Code(code), BoolVal(v), LineNumber(0) {}
  NewInstr(Opcode code, const long& v)
    : Code(code), IntVal(v), LineNumber(0) {}
  NewInstr(Opcode code, const double& v)
    : Code(code), FloatVal(v), LineNumber(0) {}
  NewInstr(Opcode code, const gString& v)
    : Code(code), TextVal(v), LineNumber(0) {}
  NewInstr(Opcode code, const Precision& v)
    : Code(code), PrecVal(v), LineNumber(0) {}
  NewInstr(Opcode code, gInput* v)
    : Code(code), InputVal(v), LineNumber(0) {}
  NewInstr(Opcode code, gOutput* v)
    : Code(code), OutputVal(v), LineNumber(0) {}
  ~NewInstr() {}
};

class gOutput;
gOutput& operator << ( gOutput& s, NewInstr* p );


#endif // GSMINSTR_H

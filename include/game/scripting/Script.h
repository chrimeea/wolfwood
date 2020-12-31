#ifndef SCRIPT_H
#define SCRIPT_H

class Script
{
 protected:
  bool finished;
 public:
  Script()
  {
	  finished = false;
  }
  virtual ~Script() {}
  virtual void execute() = 0;
  bool isFinished()
  {
	  return finished;
  }
};

#endif